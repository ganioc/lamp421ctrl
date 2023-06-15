/*
 * cmd_iovo.c
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */

#include "at_cmds.h"
#include <string.h>


void cmd_iovo_read(){
	char temp[32];
	uint16_t state_52v;
	uint16_t state_12v;


	PRINT_LOG("iovo read\r\n");
	state_52v = get_state_pwr_52v();
	state_12v = get_state_pwr_12v();

	sprintf(temp, "+IOVO:1,%d", state_52v);
	SEND_RESPONSE_STR(temp);
	sprintf(temp, "+IOVO:2,%d\r\n", state_12v);
	SEND_RESPONSE_STR_RAW(temp);

	SEND_RESPONSE_OK();

}
void cmd_iovo_write(char*str , int len){
	struct AT_DUAL_INT_PARAM param;

	parse_dual_int_param(str, len, &param);

	PRINT_LOG("%d,%d\r\n", param.id, param.value);

	if(param.id < 1 ||
			param.id > 2||
			param.value < 0 ||
			param.value > 1){
		SEND_RESPONSE_ERROR(AT_ERROR_PARAMETER);
	}else{
		vo_set_gpio(param.id, param.value);
		SEND_RESPONSE_OK();
	}
}
