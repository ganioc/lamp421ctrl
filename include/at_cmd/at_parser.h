/*
 * at_parser.h
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#ifndef INCLUDE_AT_CMD_AT_PARSER_H_
#define INCLUDE_AT_CMD_AT_PARSER_H_


#include "at_struct.h"
#include "at_cmds.h"




enum PARSE_STATE{
	AT_S_DUMMY,
	AT_S_HEAD,
	AT_S_PLUS,
	AT_S_TAG,
	AT_S_OPERATOR,
	AT_S_ARG,
	AT_S_CARRIAGE
};

void parse_at_cmd(char* str, uint16_t* head, uint16_t* tail,uint16_t at_rx_buffer_len);


/* Use FreeRTOS soft timer, or use MCU hardware timer  */
void parserTimerCallback();

#endif /* INCLUDE_AT_CMD_AT_PARSER_H_ */
