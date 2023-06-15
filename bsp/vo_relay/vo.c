/*
 * vo.c
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */

#include "at32f421_board.h"
#include "mcu_gpio.h"

/* PB1 52V
 * PB2 12V
 */

uint16_t state_vo_relay[5] = {0};

uint16_t vo_relay_pins[5] = {
		PWR_52V_PIN,
		PWR_12V_PIN,
		RELAY_1_PIN,
		RELAY_2_PIN,
		RELAY_3_PIN
};

uint16_t get_state_pwr_52v(){
	return state_vo_relay[PWR_52V_ID];
}
uint16_t get_state_pwr_12v(){
	return state_vo_relay[PWR_12V_ID];
}
uint16_t get_state_relay(uint16_t channel){
	return state_vo_relay[channel + 1];
}
void vo_relay_on(uint16_t id){
	if(state_vo_relay[id] == 0){

		state_vo_relay[id] = 1;
		save_param_vo_relay(state_vo_relay, 5);
	}
	gpio_on(VO_RELAY_GPIO_PORT,vo_relay_pins[id]);
}
void vo_relay_off(uint16_t id){
	if(state_vo_relay[id] == 1){

		state_vo_relay[id] = 0;
		save_param_vo_relay(state_vo_relay, 5);
	}
	gpio_off(VO_RELAY_GPIO_PORT,vo_relay_pins[id]);
}
void vo_52v_on(){
	vo_relay_on(PWR_52V_ID);
}
void vo_52v_off(){
	vo_relay_off(PWR_52V_ID);
}
void vo_12v_on(){
	vo_relay_on(PWR_12V_ID);
}
void vo_12v_off(){
	vo_relay_off(PWR_12V_ID);
}
void relay_1_on(){
	vo_relay_on(RELAY_1_ID);
}
void relay_1_off(){
	vo_relay_off(RELAY_1_ID);
}
void relay_2_on(){
	vo_relay_on(RELAY_2_ID);
}
void relay_2_off(){
	vo_relay_off(RELAY_2_ID);
}
void relay_3_on(){
	vo_relay_on(RELAY_3_ID);
}
void relay_3_off(){
	vo_relay_off(RELAY_3_ID);
}
void vo_gpio_init(){
	init_gpio_output(PWR_52V_GPIO_CLK,
			PWR_52V_GPIO_PORT,
			PWR_52V_PIN,
			GPIO_PULL_DOWN);
	init_gpio_output(PWR_12V_GPIO_CLK,
			PWR_12V_GPIO_PORT,
			PWR_12V_PIN,
			GPIO_PULL_DOWN);
	init_gpio_output(RELAY_1_GPIO_CLK,
			RELAY_1_GPIO_PORT,
			RELAY_1_PIN,
			GPIO_PULL_DOWN);
	init_gpio_output(RELAY_2_GPIO_CLK,
			RELAY_2_GPIO_PORT,
			RELAY_2_PIN,
			GPIO_PULL_DOWN);
	init_gpio_output(RELAY_3_GPIO_CLK,
			RELAY_3_GPIO_PORT,
			RELAY_3_PIN,
			GPIO_PULL_DOWN);

}

static void vo_relay_set_value(uint16_t id){
	if(state_vo_relay[id] == 0){
		gpio_off(RELAY_GPIO_PORT, vo_relay_pins[id]);
	}else{
		gpio_on(RELAY_GPIO_PORT, vo_relay_pins[id]);
	}
}
void vo_relay_load_value(uint16_t p52,
		uint16_t p12,
		uint16_t r1,
		uint16_t r2,
		uint16_t r3){
	state_vo_relay[PWR_52V_ID] = p52;
	state_vo_relay[PWR_12V_ID] = p12;
	state_vo_relay[RELAY_1_ID] = r1;
	state_vo_relay[RELAY_2_ID] = r2;
	state_vo_relay[RELAY_3_ID] = r3;

	vo_relay_set_value(PWR_52V_ID);
	vo_relay_set_value(PWR_12V_ID);
	vo_relay_set_value(RELAY_1_ID);
	vo_relay_set_value(RELAY_2_ID);
	vo_relay_set_value(RELAY_3_ID);
}
void vo_relay_set_default_value(){

	vo_relay_load_value(PWR_52V_DEFAULT,
			PWR_12V_DEFAULT,
			RELAY_1_DEFAULT,
			RELAY_2_DEFAULT,
			RELAY_3_DEFAULT);

	save_param_vo_relay(state_vo_relay, 5);
}

void vo_set_gpio(uint16_t channel, uint16_t value){
	if(channel == 1){
		if(value == 0){
			vo_52v_off();
		}else{
			vo_52v_on();
		}
	}else{
		if(value == 0){
			vo_12v_off();
		}else{
			vo_12v_on();
		}
	}
}
void relay_set_gpio(uint16_t channel, uint16_t value){
	if(channel == 1){
		if(value == 0){
			relay_1_off();
		}else{
			relay_1_on();
		}

	}else if(channel == 2){
		if(value == 0){
			relay_2_off();
		}else{
			relay_2_on();
		}
	}else{
		if(value == 0){
			relay_3_off();
		}else{
			relay_3_on();
		}
	}
}
