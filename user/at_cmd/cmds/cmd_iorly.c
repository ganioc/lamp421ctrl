/*
 * cmd_iorly.c
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */
#include "at_cmds.h"

void cmd_iorly_read(){
	char temp[32];
	uint16_t state;


	PRINT_LOG("iorly read\r\n");
	state = get_state_relay(1);

	sprintf(temp, "+IORLY:1,%d", state);
	SEND_RESPONSE_STR(temp);

	state = get_state_relay(2);
	sprintf(temp, "+IORLY:2,%d\r\n", state);
	SEND_RESPONSE_STR_RAW(temp);

	state = get_state_relay(3);
	sprintf(temp, "+IORLY:3,%d\r\n", state);
	SEND_RESPONSE_STR_RAW(temp);

	SEND_RESPONSE_OK();

}
void cmd_iorly_write(char*str , int len){
	struct AT_DUAL_INT_PARAM param;

	parse_dual_int_param(str, len, &param);

	PRINT_LOG("%d,%d\r\n", param.id, param.value);

	if(param.id < 1 ||
			param.id > 3||
			param.value < 0 ||
			param.value > 1){
		SEND_RESPONSE_ERROR(AT_ERROR_PARAMETER);
	}else{
		relay_set_gpio(param.id, param.value);
		SEND_RESPONSE_OK();
	}
}
