/*
 * cmd_at.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#include "at_cmds.h"

void cmd_at_exec(){
	PRINT_LOG("[AT] received\r\n");
	SEND_RESPONSE_STR("OK");
}
