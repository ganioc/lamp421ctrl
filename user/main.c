/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.6
  * @date     2022-05-20
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f421_board.h"
#include "at32f421_clock.h"

#include "i2c_application.h"
#include "at_cmds.h"

/** @addtogroup AT32F421_periph_template
  * @{
  */

/** @addtogroup 421_LED_toggle LED_toggle
  * @{
  */
#define BUF_SIZE             8

uint8_t tx_buf1[BUF_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t tx_buf2[BUF_SIZE] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
uint8_t tx_buf3[BUF_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
uint8_t rx_buf1[BUF_SIZE] = {0};
uint8_t rx_buf2[BUF_SIZE] = {0};
uint8_t rx_buf3[BUF_SIZE] = {0};

extern i2c_handle_type hi2cx;

extern uint8_t at_rx_buffer[];
extern uint16_t at_rx_buffer_head;
extern uint16_t at_rx_buffer_tail;

//#define DELAY                            100
//#define FAST                             1
//#define SLOW                             4
//
//uint8_t g_speed = FAST;

void button_exint_init(void);
void button_isr(void);

/**
  * @brief  configure button exint
  * @param  none
  * @retval none
  */
void button_exint_init(void)
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_SCFG_PERIPH_CLOCK, TRUE);

  scfg_exint_line_config(SCFG_PORT_SOURCE_GPIOA, SCFG_PINS_SOURCE0);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_0;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);

  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT1_0_IRQn, 0, 0);
}

/**
  * @brief  button handler function
  * @param  none
  * @retval none
  */
void button_isr(void)
{
  /* delay 5ms */
  delay_ms(5);

  /* clear interrupt pending bit */
  exint_flag_clear(EXINT_LINE_0);

  /* check input pin state */
  if(SET == gpio_input_data_bit_read(USER_BUTTON_PORT, USER_BUTTON_PIN))
  {
//    if(g_speed == SLOW)
//      g_speed = FAST;
//    else
//      g_speed = SLOW;
  }
}

/**
  * @brief  exint0 interrupt handler
  * @param  none
  * @retval none
  */
void EXINT1_0_IRQHandler(void)
{
  button_isr();
}


/**
  * @brief  error handler program
  * @param  i2c_status
  * @retval none
  */
void error_handler(uint32_t error_code)
{
  while(1)
  {
	  led_run_toggle();
    delay_ms(100);
  }
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void) {
	i2c_status_type i2c_status;
	char str_buf[128];
	int  str_buf_index = 0;

	/* config vector table offset */
  // nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x4000);

	system_clock_config();

	at32_board_init();

	init_at_callback();

	print_welcome();

	// print system information
	print_at_info();

	while (1) {
		wdt_reload();

		// delay_ms(100);

		at_rx_check();

//		if(get_at_rx_flag() == 1){
//			// printf("*\r\n");
//			parse_at_cmd(at_rx_buffer,
//					&at_rx_buffer_head,
//					&at_rx_buffer_tail,
//					AT_RX_BUFFER_LEN);
//
//			reset_at_rx_flag();
//		}

		check_pwm_freq_duty();

	}
}

/**
  * @}
  */

/**
  * @}
  */
