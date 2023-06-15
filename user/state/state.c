/*
 * state.c
 *
 *  Created on: 2023 Mar 10
 *      Author: ruffman
 */

#include "at32f421_board.h"
#include "flash.h"

uint16_t data_buf[16];

void check_param_pwm(){
	flash_read(PARAM_PWM_ADDRESS, data_buf,  3);

	cust_printf("PWM freq: %d, duty: %d  %d\r\n",
			data_buf[0],
			data_buf[1],
			data_buf[2]);

	if(data_buf[0] == 0xFFFF){
		pwm_set_default_value();
	}else{
		pwm_load_value(data_buf[0], data_buf[1], data_buf[2]);
	}
}
void save_param_pwm(uint16_t freq, uint16_t duty1, uint16_t duty2){
	data_buf[0] = freq;
	data_buf[1] = duty1;
	data_buf[2] = duty2;

	flash_write(PARAM_PWM_ADDRESS, data_buf, 3);
}

/*  vo   */
void check_param_vo_relay(){
	flash_read(PARAM_VO_ADDRESS, data_buf,  5);

	cust_printf("VO state, 52V: %d, 12V: %d, R1:%d, R2:%d, R3:%d\r\n",
			data_buf[0],
			data_buf[1],
			data_buf[2],
			data_buf[3],
			data_buf[4]);

	if(data_buf[0] == 0xFFFF){
		vo_relay_set_default_value();
	}else{
		vo_relay_load_value(data_buf[0],
				data_buf[1],
				data_buf[2],
				data_buf[3],
				data_buf[4]);
	}
}
void save_param_vo_relay(uint16_t* state, uint16_t len){
	for(int i =0; i < len ;i++){
		data_buf[i] = state[i];
	}

	flash_write(PARAM_VO_ADDRESS, data_buf, len);
}

void check_params(){
	check_param_pwm();

	check_param_vo_relay();
}

void restore_default_value(){
	pwm_set_default_value();
}
