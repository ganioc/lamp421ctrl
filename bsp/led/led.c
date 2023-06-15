/*
 * led.c
 *
 *  Created on: 2023 Mar 8
 *      Author: ruffman
 */

#include "at32f421_board.h"
#include "mcu_gpio.h"
#include "mcu_led_pattern.h"

struct LED_PATTERN run_pattern, net_pattern;

void led_gpio_init(){
	init_gpio_output(LED_RUN_GPIO_CLK,
			LED_RUN_GPIO_PORT,
			LED_RUN_PIN,
			GPIO_PULL_UP);
	init_gpio_output(LED_ETH_GPIO_CLK,
			LED_ETH_GPIO_PORT,
			LED_ETH_PIN,
			GPIO_PULL_UP);
	init_gpio_output(LED_NET_GPIO_CLK,
			LED_NET_GPIO_PORT,
			LED_NET_PIN,
			GPIO_PULL_UP);

	init_led_pattern_single(&run_pattern, 0x01010101);
	// init_led_pattern_double(&net_pattern, 0xCCACCACC, 0xAAAACCCC);

}
void led_run_on(){
	gpio_on(LED_RUN_GPIO_PORT,
			LED_RUN_PIN);
}
void led_run_off(){
	gpio_off(LED_RUN_GPIO_PORT,
			LED_RUN_PIN);
}
void led_run_toggle(){
	gpio_toggle(LED_RUN_GPIO_PORT,
			LED_RUN_PIN);
}
void led_eth_on(){
	gpio_on(LED_ETH_GPIO_PORT,
			LED_ETH_PIN);
}
void led_eth_off(){
	gpio_off(LED_ETH_GPIO_PORT,
			LED_ETH_PIN);
}
void led_eth_toggle(){
	gpio_toggle(LED_ETH_GPIO_PORT,
			LED_ETH_PIN);
}
void led_net_on(){
	gpio_on(LED_NET_GPIO_PORT,
			LED_NET_PIN);
}
void led_net_off(){
	gpio_off(LED_NET_GPIO_PORT,
			LED_NET_PIN);
}
void led_net_toggle(){
	gpio_toggle(LED_NET_GPIO_PORT,
			LED_NET_PIN);
}

void led_shining_pattern(){
	// led_run_toggle();
	check_led_pattern(&run_pattern, led_run_on, led_run_off);
	// check_led_pattern(&net_pattern, led_net_on, led_net_off);
}
