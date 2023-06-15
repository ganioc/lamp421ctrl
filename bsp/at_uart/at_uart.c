/*
 * at_uart.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */
#include "at32f421_board.h"



uint8_t at_rx_buffer[AT_RX_BUFFER_LEN];
uint16_t at_rx_buffer_head = 0;
uint16_t at_rx_buffer_tail = 0;

uint8_t at_rx_flag = 0;




void at_rx_take(uint8_t data){
	at_rx_buffer[at_rx_buffer_head++] = data;


	if(at_rx_buffer_head >= AT_RX_BUFFER_LEN){
		at_rx_buffer_head = 0;
	}
}
void at_rx_check(){

	if (at_rx_buffer_head != at_rx_buffer_tail) {

		// printf("%c", usart1_rx_buffer[usart1_rx_ptr]);
		parse_at_cmd_one_byte(at_rx_buffer[at_rx_buffer_tail]);

		at_rx_buffer_tail++;

		if (at_rx_buffer_tail >= AT_RX_BUFFER_LEN) {
			at_rx_buffer_tail = 0;
		}
	}

}
uint8_t get_at_rx_flag(){
	return at_rx_flag;
}
uint8_t reset_at_rx_flag(){
	at_rx_flag = 0;
}
uint8_t check_at_rx_empty(){
	if(at_rx_buffer_head != at_rx_buffer_tail){
		return 1;
	}else{
		return 0;
	}
}
uint8_t read_at_rx_tail(){
	uint8_t temp;
	temp = at_rx_buffer[at_rx_buffer_tail++];
	if(at_rx_buffer_tail >= AT_RX_BUFFER_LEN){
		at_rx_buffer_tail = 0;
	}
	return temp;
}

void send_response_str(char *str){
	char temp[128];
	sprintf(temp, "\r\n%s\r\n", str);
	printf(temp);
}
void send_response_ok(){
	printf("\r\nOK\r\n");
}
void send_response_timeout(char* code){
	printf("\r\nERROR:%s\r\n", code);
}
void send_response_error(char* code){
	printf("\r\nERROR:%s\r\n",code);
}
void send_response_str_raw(char* str){
	printf(str);
}

