/*
 * cmd_iopwmduty.c
 *
 *  Created on: 2023 Mar 10
 *      Author: ruffman
 */

#include "at_cmds.h"
#include <string.h>
#include <stdlib.h>


void cmd_iopwmduty_read(){
	char temp[32];

	uint16_t freq = get_pwm_duty1();

	sprintf(temp, "+IOPWMDUTY:1,%d",freq);

	SEND_RESPONSE_STR(temp);

	freq = get_pwm_duty2();

	sprintf(temp, "+IOPWMDUTY:2,%d\r\n",freq);

	SEND_RESPONSE_STR_RAW(temp);

	SEND_RESPONSE_OK();

}
void cmd_iopwmduty_write(char*str , int len){
	uint16_t duty, channel;
	struct AT_DUAL_INT_PARAM param;

	PRINT_LOG("%s\r\n",str);

	parse_dual_int_param(str, len, &param);

	channel = param.id;
	duty    = param.value;


	if(channel < 0 || channel > 2){
		PRINT_LOG("channeL:%d\r\n", channel);
		SEND_RESPONSE_ERROR(AT_ERROR_PARAMETER);
		return;
	}

	if(duty > 100){
		PRINT_LOG("duty:%d\r\n", duty);
		SEND_RESPONSE_ERROR(AT_ERROR_PARAMETER);
		return;
	}

	set_pwm_channel_duty(channel, duty);
	SEND_RESPONSE_OK();
}


