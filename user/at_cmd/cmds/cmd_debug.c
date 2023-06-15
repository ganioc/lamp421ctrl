/*
 * cmd_debug.c
 *
 *  Created on: 2023 Mar 15
 *      Author: ruffman
 */

#include "at_cmds.h"
#include <string.h>

void cmd_debug_exec(void){
	char temp[32];
	PRINT_LOG("debug\r\n");

	sprintf(temp, "AT_TIMEOUT: %d ms", AT_TIMEOUT_DUR);

	SEND_RESPONSE_STR(temp);

	sprintf(temp, "SRAM: %d KB\r\n", 16);

	SEND_RESPONSE_STR_RAW(temp);

	sprintf(temp, "FLASH: %d KB\r\n", 64);

	SEND_RESPONSE_STR_RAW(temp);

	sprintf(temp,"Timer3 freq 1/600 s\r\n");

	SEND_RESPONSE_STR_RAW(temp);

	SEND_RESPONSE_OK();
}
