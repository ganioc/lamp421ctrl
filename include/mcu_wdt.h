/*
 * mcu_wdt.h
 *
 *  Created on: 2023 Mar 7
 *      Author: ruffman
 */

#ifndef INCLUDE_MCU_WDT_H_
#define INCLUDE_MCU_WDT_H_

#ifdef AT_START_F421_V1
#include "at32f421_board.h"
#endif

#ifdef AT_START_F415_V1
#include "at32f415_board.h"
#endif

void init_wdt();

void wdt_reload();

#endif /* INCLUDE_MCU_WDT_H_ */
