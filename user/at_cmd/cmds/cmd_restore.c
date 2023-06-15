/*
 * cmd_restore.c
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */

#include "at_cmds.h"


void cmd_restore(){

	cust_printf("restore default\r\n");
	restore_default_value();

	SEND_RESPONSE_OK();
}
