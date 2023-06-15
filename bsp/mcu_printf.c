/*
 * mcu_printf.c
 *
 *  Created on: 2023 Mar 7
 *      Author: ruffman
 */

#include "mcu_printf.h"

/* For GCC compiler revise _write() function for printf functionality */
int _write(int file, char *ptr, int len) {
	int i;

	for (i = 0; i < len; i++) {
		while (usart_flag_get(PRINT_UART, USART_TDBE_FLAG) == RESET)
			;
		usart_data_transmit(PRINT_UART, ptr[i]);
	}
	return len;
}

/**
 * @brief  initialize uart
 * @param  baudrate: uart baudrate
 * @retval none
 */
void uart_print_init(uint32_t baudrate) {
	gpio_init_type gpio_init_struct;

	/* enable the uart and gpio clock */
	crm_periph_clock_enable(PRINT_UART_CRM_CLK, TRUE);
	crm_periph_clock_enable(PRINT_UART_TX_GPIO_CRM_CLK, TRUE);

	gpio_default_para_init(&gpio_init_struct);

	/* configure the uart tx pin */
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = PRINT_UART_TX_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init(PRINT_UART_TX_GPIO, &gpio_init_struct);

	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pins = PRINT_UART_RX_PIN;
	gpio_init_struct.gpio_pull = GPIO_PULL_UP;
	gpio_init(PRINT_UART_RX_GPIO, &gpio_init_struct);

	gpio_pin_mux_config(PRINT_UART_TX_GPIO, PRINT_UART_TX_PIN_SOURCE,
			PRINT_UART_TX_PIN_MUX_NUM);
	gpio_pin_mux_config(PRINT_UART_RX_GPIO, PRINT_UART_RX_PIN_SOURCE,
			PRINT_UART_RX_PIN_MUX_NUM);

	/* configure uart param */
	usart_init(PRINT_UART, baudrate, USART_DATA_8BITS, USART_STOP_1_BIT);
	usart_parity_selection_config(PRINT_UART, USART_PARITY_NONE);

	usart_transmitter_enable(PRINT_UART, TRUE);
	usart_receiver_enable(PRINT_UART, TRUE);

	usart_interrupt_enable(PRINT_UART, USART_RDBF_INT, TRUE);
	usart_interrupt_enable(PRINT_UART, USART_IDLE_INT, FALSE);

	usart_enable(PRINT_UART, TRUE);

	/* config  usart1 nvic interrupt */
	nvic_irq_enable(USART1_IRQn, 2, 0);
}

void USART1_IRQHandler(void) {
	if (USART1->ctrl1_bit.rdbfien != RESET) {
		if (usart_flag_get(USART1, USART_RDBF_FLAG) != RESET) {
			/* read one byte from the receive data register */
			at_rx_take(usart_data_receive(USART1));

			// usart_interrupt_enable(USART1, USART_IDLE_INT, TRUE);

		}
//		else if (usart_flag_get(USART1, USART_IDLEF_FLAG) != RESET) {
//
//			at_rx_check();
//
//			usart_interrupt_enable(USART1, USART_IDLE_INT, FALSE);
//		}
	}
}

