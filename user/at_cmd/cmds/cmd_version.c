/*
 * cmd_version.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#include <string.h>

#include "at_cmds.h"

extern char version[];
extern char model[];

void cmd_version_exec(void){
	char str[32];
	sprintf(str, "%s_V%s", model, version);

	SEND_RESPONSE_STR(str);
	SEND_RESPONSE_OK();
}
void cmd_version_read(void){
	SEND_RESPONSE_STR(version);
	SEND_RESPONSE_OK();
}
void cmd_version_test(void){
	SEND_RESPONSE_STR("test VERSION");
	SEND_RESPONSE_OK();
}
void cmd_version_write(char*str, int len){
	PRINT_LOG("received set cmd\r\n");
	PRINT_LOG(str);
	SEND_RESPONSE_OK();
}
