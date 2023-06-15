/*
 * mcu_uid.h
 *
 *  Created on: 2023 Mar 13
 *      Author: ruffman
 */

#ifndef INCLUDE_MCU_UID_H_
#define INCLUDE_MCU_UID_H_


#ifdef AT_START_F421_V1
#include "at32f421_board.h"
#endif

#ifdef AT_START_F415_V1
#include "at32f415_board.h"
#endif


#define UIDBASE    0x1FFFF7E0
#define UID31_BASE 0x1FFFF7E8
#define UID63_BASE 0x1FFFF7EC
#define UID95_BASE 0x1FFFF7F0

uint32_t get_UID();


#endif /* INCLUDE_MCU_UID_H_ */
