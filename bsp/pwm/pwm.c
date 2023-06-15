/*
 * pwm.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */
#include "at32f421_board.h"

static uint16_t freq = 1000;
static uint8_t pwm_duty1 = 10;
static uint8_t pwm_duty2 = 10;

static uint16_t pwm_freq_list[PWM_FREQ_POINTS] = {
		20000, 10000, 5000, 2000 ,1000, 500, 250
};

void pwm_set_default_value(){
	freq = PWM_DEFAULT_FREQ;
	pwm_duty1 = PWM_DEFAULT_DUTY;
	pwm_duty2 = PWM_DEFAULT_DUTY;

	save_param_pwm(freq, pwm_duty1, pwm_duty2);
}
void pwm_load_value(uint16_t in_freq, uint16_t duty1, uint16_t duty2){
	freq = in_freq;
	pwm_duty1 = duty1;
	pwm_duty2 = duty2;
}

uint16_t get_timer_period(uint16_t frequency){
	switch(frequency){
	case 20000:
		return PWM_REF_FREQ/20;
	case 10000:
		return PWM_REF_FREQ/10;
	case 5000:
		return PWM_REF_FREQ/2;
	case 2000:
		return PWM_REF_FREQ/5;
	case 1000:
		return PWM_REF_FREQ ;
	case 500:
		return PWM_REF_FREQ*2;
	case 250:
		return PWM_REF_FREQ*4;
	default:
		return PWM_REF_FREQ;
	}
}
uint16_t get_channel_pulse(uint16_t freq, uint8_t duty){
	return (uint16_t)(((uint16_t)duty * (get_timer_period(freq))) / 100);
}
static uint16_t get_channel_pulse_from_period(uint8_t duty, uint16_t period){
	return (uint16_t)(((uint32_t)duty * (period - 1)) / 100);
}

uint8_t set_pwm_duty(uint8_t duty){
	if(duty > 100){
		return 100;
	}else{
		return duty;
	}
}
void set_pwm_duty1(uint8_t duty){
	pwm_duty1 = set_pwm_duty(duty);
	save_param_pwm(freq, pwm_duty1, pwm_duty2);
}
void set_pwm_duty2(uint8_t duty){
	pwm_duty2 = set_pwm_duty(duty);
	save_param_pwm(freq, pwm_duty1, pwm_duty2);
}
uint8_t get_pwm_duty1(){
	return pwm_duty1;
}
uint8_t get_pwm_duty2(){
	return pwm_duty2;
}
void set_pwm_freq(uint16_t frequency){
	freq = frequency;
	save_param_pwm(freq, pwm_duty1, pwm_duty2);
}
void set_pwm_channel_duty(uint8_t channel, uint8_t duty){
	if(channel == 1){
		set_pwm_duty1(duty);
	}else if(channel  == 2){
		set_pwm_duty2(duty);
	}
}
uint16_t get_pwm_freq(){
	return freq;
}
uint16_t check_pwm_freq(uint16_t frequency){
	int i;
	for(i=0; i< PWM_FREQ_POINTS; i++){
		if(frequency == pwm_freq_list[i]){
			return frequency;
		}
	}
	return 0;
}


// void timer_pwm_config(uint16_t freq) {
void timer_pwm_config() {

	gpio_init_type gpio_init_struct = { 0 };
	tmr_output_config_type tmr_output_struct_en;
	crm_clocks_freq_type crm_clocks_freq_struct_en = { 0 };

	uint16_t timer_period = 0;
	uint16_t channel1_pulse;
	uint16_t channel4_pulse;

	/* get system clock */
	crm_clocks_freq_get(&crm_clocks_freq_struct_en);

	cust_printf("sclk:%d\r\n", crm_clocks_freq_struct_en.sclk_freq);
	cust_printf("ahb:%d\r\n", crm_clocks_freq_struct_en.ahb_freq);
	cust_printf("apb2:%d\r\n", crm_clocks_freq_struct_en.apb2_freq);
	cust_printf("apb1:%d\r\n", crm_clocks_freq_struct_en.apb1_freq);

	/* enable tmr1/gpioa/gpiob clock */
	crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
	crm_periph_clock_enable(PWM_1_GPIO_CLK, TRUE);

	/* timer1 output pin Configuration */
	gpio_init_struct.gpio_pins = PWM_1_PIN | PWM_2_PIN;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init(PWM_1_GPIO_PORT, &gpio_init_struct);

	gpio_pin_mux_config(GPIOA, PWM_1_PIN_SOURCE, GPIO_MUX_2);
	gpio_pin_mux_config(GPIOA, PWM_2_PIN_SOURCE, GPIO_MUX_2);

	/* compute the value to be set in arr regiter to generate signal frequency */
	timer_period = get_timer_period(freq) - 1;
	// timer_period =
	cust_printf("timer_period: %d\r\n", timer_period);

	/* compute c1dt value to generate a duty cycle at 50% for channel 1 and 1c */
	channel1_pulse = get_channel_pulse(freq, pwm_duty1);
	/* compute c4dt value to generate a duty cycle at 12.5%  for channel 4 */
	channel4_pulse = get_channel_pulse(freq, pwm_duty2);

	tmr_base_init(TMR1, timer_period, 120);
	tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

	/* channel 1 and 4 configuration in output mode */
	tmr_output_default_para_init(&tmr_output_struct_en);
	tmr_output_struct_en.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
	tmr_output_struct_en.oc_output_state = TRUE;
	tmr_output_struct_en.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
	tmr_output_struct_en.oc_idle_state = TRUE;
	tmr_output_struct_en.occ_output_state = TRUE;
	tmr_output_struct_en.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
	tmr_output_struct_en.occ_idle_state = FALSE;

	/* channel 1 */
	tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1,
			&tmr_output_struct_en);
	tmr_channel_value_set(TMR1,
			TMR_SELECT_CHANNEL_1,
			channel1_pulse);

	/* channel 4 */
	tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_4,
			&tmr_output_struct_en);
	tmr_channel_value_set(TMR1,
			TMR_SELECT_CHANNEL_4,
			channel4_pulse);


	tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR1_BRK_OVF_TRG_HALL_IRQn, 0 , 0);

	/* output enable */
	tmr_output_enable(TMR1, TRUE);

	/* enable tmr1 */
	tmr_counter_enable(TMR1, TRUE);

}
void check_pwm_freq_duty(){
	uint16_t preload_value;
	uint16_t required_preload, new_period;
	uint16_t channel1_value, channel4_value;
	uint16_t  required_value1, required_value2;

	preload_value = tmr_period_value_get(TMR1);
	required_preload = get_timer_period(freq)-1;

	if(required_preload == preload_value){
		;
	}else{
		tmr_period_value_set(TMR1, required_preload);
		return;
	}

	channel1_value = tmr_channel_value_get(TMR1, TMR_SELECT_CHANNEL_1);
	channel4_value = tmr_channel_value_get(TMR1, TMR_SELECT_CHANNEL_4);

	required_value1 = get_channel_pulse(freq, pwm_duty1);
	required_value2 = get_channel_pulse(freq, pwm_duty2);

	// set duty value
	if(required_value1  == channel1_value){
		;
	}else{
//		cust_printf("freq: %d, pwm:duty1: %d\r\n", freq, pwm_duty1);
//		cust_printf("c:%d, r:%d\r\n", channel1_value, required_value1);

		if(required_value1  > channel1_value){
			new_period = channel1_value + PWM_DUTY_STEP;
		}else{
			new_period = channel1_value - PWM_DUTY_STEP;
		}
		tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, required_value1);
	}

	if(required_value2  == channel4_value){
		;
	}else{
//		cust_printf("freq: %d, pwm:duty1: %d\r\n", freq, pwm_duty2);
//		cust_printf("c:%d, r:%d\r\n", channel4_value, required_value2);

		if(required_value2  > channel4_value){
			new_period = channel4_value + PWM_DUTY_STEP;
		}else{
			new_period = channel4_value - PWM_DUTY_STEP;
		}
		tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_4, required_value2);
	}
}

void TMR1_BRK_OVF_TRG_HALL_IRQHandler(void) {


	if (tmr_flag_get(TMR1, TMR_OVF_FLAG) != RESET) {

		tmr_flag_clear(TMR1, TMR_OVF_FLAG);

	}
}
