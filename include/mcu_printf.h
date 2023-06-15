/*
 * mcu_printf.h
 *
 *  Created on: 2023 Mar 7
 *      Author: ruffman
 */

#ifndef INCLUDE_MCU_PRINTF_H_
#define INCLUDE_MCU_PRINTF_H_

#ifdef AT_START_F421_V1
#include "at32f421_board.h"
#endif

#ifdef AT_START_F415_V1
#include "at32f415_board.h"
#endif

/* printf uart init function */
void uart_print_init(uint32_t baudrate);

#endif /* INCLUDE_MCU_PRINTF_H_ */
