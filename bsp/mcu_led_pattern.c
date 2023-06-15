/*
 * led_pattern.c
 *
 *  Created on: 2023 Mar 14
 *      Author: ruffman
 */
#include "mcu_led_pattern.h".h"

void init_led_pattern_single(struct LED_PATTERN* pattern, uint32_t bits_1){
	(*pattern).patterns[0] = bits_1;
	pattern->counter = 0;
	pattern->type = LED_PATTERN_SINGLE;
}
void init_led_pattern_double(struct LED_PATTERN* pattern, uint32_t bits_1, uint32_t bits_2){
	(*pattern).patterns[0] = bits_1;
	(*pattern).patterns[1] = bits_2;
	pattern->counter = 0;
	pattern->type = LED_PATTERN_DOUBLE;
}
uint32_t get_led_pattern_single(struct LED_PATTERN* pattern){
	uint32_t shift_bit, val;

	shift_bit = *(pattern->patterns) & 0x00000001;

	val = *(pattern->patterns) & 0x00000003;

	*(pattern->patterns) = *(pattern->patterns) >> 1;

	*(pattern->patterns) |= shift_bit << 31;

	return val;
}
uint32_t get_led_pattern_double(struct LED_PATTERN* pattern){
	uint32_t shift_bit, val;

	shift_bit = *(pattern->patterns) & 0x00000001;

	val = *(pattern->patterns) & 0x00000003;

	*(pattern->patterns) = *(pattern->patterns) >> 1;

	*(pattern->patterns) |= (*(pattern->patterns + 1) & 0x01) << 31;

	*(pattern->patterns + 1) = *(pattern->patterns +1) >> 1;

	*(pattern->patterns + 1) |= shift_bit << 31;

	return val;
}

uint32_t get_led_pattern(struct LED_PATTERN* pattern){
	pattern->counter++;

	if(pattern->counter >= BLINK_RESOLUTION){
		pattern->counter = 0;

		if(pattern->type == LED_PATTERN_SINGLE){
			return get_led_pattern_single(pattern);
		}else{
			return get_led_pattern_double(pattern);
		}
	}

	return 0;

}
void check_led_pattern(struct LED_PATTERN* pattern, void(*on)(), void(*off)()){
	uint32_t bits = get_led_pattern(pattern);

	switch(bits){
	case 0b01:
		off();
		break;
	case 0b10:
		on();
		break;
	case 0b00:
	case 0b11:
	default:
		break;
	}

}

