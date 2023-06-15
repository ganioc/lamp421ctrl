/*
 * cmd_iopwmfreq.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */


#include "at_cmds.h"
#include <string.h>
#include <stdlib.h>


void cmd_iopwmfreq_read(){
	char temp[32];

	uint16_t freq = get_pwm_freq();

	sprintf(temp, "+IOPWMFREQ:1,%d",freq);

	SEND_RESPONSE_STR(temp);

	sprintf(temp, "+IOPWMFREQ:2,%d\r\n",freq);

	SEND_RESPONSE_STR_RAW(temp);

	SEND_RESPONSE_OK();

}
void cmd_iopwmfreq_write(char*str , int len){
	uint16_t frequency;
	struct AT_DUAL_INT_PARAM param;

	parse_dual_int_param(str, len, &param);

	PRINT_LOG(str);

	frequency = param.value;

	PRINT_LOG("freq£º%d\r\n", frequency);

	if(check_pwm_freq(frequency) == 0){
		SEND_RESPONSE_ERROR(AT_ERROR_PARAMETER);
	}else{
		set_pwm_freq(frequency);
		SEND_RESPONSE_OK();
	}
}
