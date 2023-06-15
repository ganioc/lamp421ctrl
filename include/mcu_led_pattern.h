/*
 * mcu_led_pattern.h
 *
 *  Created on: 2023 Mar 14
 *      Author: ruffman
 */

#ifndef INCLUDE_MCU_LED_PATTERN_H_
#define INCLUDE_MCU_LED_PATTERN_H_


#ifdef AT_START_F421_V1
#include "at32f421_board.h"
#endif

#ifdef AT_START_F415_V1
#include "at32f415_board.h"
#endif

// 100 ms
#define  BLINK_RESOLUTION     (100)

#define  MULTI_PATTERN_LEN    2

enum LED_PATTERN_TYPE{
	LED_PATTERN_SINGLE = 1,
	LED_PATTERN_DOUBLE = 2
};

struct LED_PATTERN{
	uint32_t patterns[2];
	uint32_t counter;
	uint32_t last_bit;
	enum LED_PATTERN_TYPE type;
};

void init_led_pattern_single(struct LED_PATTERN* pattern, uint32_t bits_1);
void init_led_pattern_double(struct LED_PATTERN* pattern, uint32_t bits_1, uint32_t bits_2);
uint32_t get_led_pattern(struct LED_PATTERN* pattern);

void check_led_pattern(struct LED_PATTERN* pattern, void(*on)(), void(*off)());

#endif /* INCLUDE_MCU_LED_PATTERN_H_ */
