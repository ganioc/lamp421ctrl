/*
 * cmd_rst.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#include "at_cmds.h"

void cmd_rst_exec(){
	SEND_RESPONSE_OK();
	PRINT_LOG("system reset\r\n");

	HOME_WORK_BEFORE_RESET();

	nvic_system_reset();
}
