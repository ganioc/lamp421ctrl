/*
 * at_struct.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

/*
 * at_struct.c
 *
 *  Created on: 2023 Feb 20
 *      Author: ruffman
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "at_struct.h"
#include "at_parser.h"
#include "at_cmds.h"

extern struct AT_CALLBACK at_cmd_list[];
extern int NUM_AT_CALLBACK;


error_status parse_dual_int_param(char* str,
		int len,
		struct AT_DUAL_INT_PARAM* param){
	char temp[32];
	int i = 0;
	uint16_t duty, channel;

	temp[0] = str[0];
	temp[1] = 0;

	channel = atoi(temp);

	for(i = 2; i < len; i++){
		temp[i-2] =  str[i];
	}
	temp[i-2] = 0;
	duty = atoi(temp);

	param->id = channel;
	param->value = duty;

	return SUCCESS;
}

uint32_t makeHash( char *pCmd )
{
    uint16_t ch;
    uint32_t hash;
    uint16_t i=0;

    ch = 0;
    hash = 0x05;

    while((ch = *pCmd++))
        hash += (ch << (i++));
    return (hash);
}

void init_at_callback(){

//	printf("size of lst:%d\r\n", NUM_AT_CALLBACK);
//	printf("size of ele:%d\r\n", sizeof(at_cmd_list[0]));

	for(int i=0; i< NUM_AT_CALLBACK; i++){
		at_cmd_list[i].hash = makeHash(at_cmd_list[i].name);
	}

	// check duplicate names��
	for(int i =0; i< NUM_AT_CALLBACK; i++){
		for(int j=0; j<NUM_AT_CALLBACK; j++){
			if(i != j && at_cmd_list[i].hash == at_cmd_list[j].hash){
				printf("Hash is duplicate! exit!\r\n");
				PRINT_LOG("Duplicate:");
				PRINT_LOG(at_cmd_list[i].name);
			}
		}
	}
}

struct AT_CALLBACK* search_at_callback(uint32_t hash){
	struct AT_CALLBACK *lst = at_cmd_list;

	for(int i=0; i< NUM_AT_CALLBACK; i++){
		if(lst[i].hash == hash){
			return &lst[i];
		}
	}
	return NULL;
}
struct AT_CALLBACK* search_at_callback_by_name(char* name){
	uint32_t hash = makeHash(name);

	return search_at_callback(hash);
}

void handle_at_cmd(struct AT_CMD cmd){
	struct AT_CALLBACK * cb = search_at_callback_by_name(cmd.name);
	if(cb == NULL){
		SEND_RESPONSE_ERROR(AT_ERROR_POSITION);
		return;
	}
	switch (cmd.type) {
	case _AT_UNKNOWN:
		SEND_RESPONSE_ERROR(AT_ERROR_POSITION);
		break;
	case _AT_TEST:
		cb->test_cb();
		break;
	case _AT_SET:
		cb->write_cb(cmd.args, strlen(cmd.args));
		break;
	case _AT_GET:
		cb->read_cb();
		break;
	case _AT_URC:
		SEND_RESPONSE_ERROR(AT_ERROR_POSITION);
		break;
	case _AT_EXEC:
		cb->exec_cb();
		break;
	default:
		SEND_RESPONSE_ERROR(AT_ERROR_POSITION);
	}
}

