/*
 * flash.h
 *
 *  Created on: 2023 Mar 10
 *      Author: ruffman
 */

#ifndef BSP_FLASH_FLASH_H_
#define BSP_FLASH_FLASH_H_

#include "at32f421_board.h"

/** @addtogroup AT32F421_periph_examples
  * @{
  */

/** @addtogroup 421_FLASH_write_read
  * @{
  */


/** @defgroup FLASH_write_read_functions
  * @{
  */

void flash_read(uint32_t read_addr, uint16_t *p_buffer, uint16_t num_read);
error_status flash_write_nocheck(uint32_t write_addr, uint16_t *p_buffer, uint16_t num_write);
error_status flash_write(uint32_t write_addr,uint16_t *p_Buffer, uint16_t num_write);

#endif /* BSP_FLASH_FLASH_H_ */
