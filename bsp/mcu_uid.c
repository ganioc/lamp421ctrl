/*
 * mcu_uid.c
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */

#include "mcu_uid.h"




uint32_t get_UID(){

	uint32_t m1 = *(uint32_t  *)UID31_BASE;
	uint32_t m2 = *(uint32_t  *)UID63_BASE;
	uint32_t m3 = *(uint32_t  *)UID95_BASE;

	uint32_t m = (m1 & 0x1FFFF)|((m1 & 0xF0000000)>>9)|((m2 & 0x3) << 21)| ((m3 & 0xFF8000) << 8);

	return m;
}
