/*
 * cmds.h
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#ifndef INCLUDE_AT_CMD_AT_CMDS_H_
#define INCLUDE_AT_CMD_AT_CMDS_H_

#ifdef AT_START_F421_V1

#include "at32f421_board.h"
#include "at32f421_clock.h"

#endif

#ifdef AT_START_F415_V1

#include "at32f415_board.h"
#include "at32f415_clock.h"

#endif

#include "at_struct.h"

#include "at_parser.h"

#define AT_ERROR_POSITION   "100"
#define AT_ERROR_PARAMETER  "101"
#define AT_ERROR_EXEC       "102"
#define AT_ERROR_TIMEOUT    "103"

#define PRINT_LOG(...)                cust_printf(__VA_ARGS__)
#define SEND_RESPONSE_STR(str)        send_response_str(str)
#define SEND_RESPONSE_STR_RAW(str)    send_response_str_raw(str)
#define SEND_RESPONSE_OK()            send_response_ok()
#define SEND_RESPONSE_TIMEOUT(code)   send_response_error(code)
#define SEND_RESPONSE_ERROR(code)     send_response_error(code)
#define HOME_WORK_BEFORE_RESET()      delay_ms(1000)


/* AT cmd timer out duration */
#define AT_TIMEOUT_DUR        30000
#define START_TIMER()		  start_timer()
#define STOP_TIMER()          stop_timer()

void    parserTimerCallback();
extern  uint8_t AT_in_handling;

void parse_at_cmd_one_byte(char ch);
void parse_at_cmd(char *str, uint16_t *head, uint16_t *tail,
		uint16_t at_rx_buffer_len);

// AT
void cmd_at_exec(void);


// VERSION
void cmd_version_exec(void);
void cmd_version_read(void);
void cmd_version_test(void);
void cmd_version_write(char*str, int len);

// RST
#define RST_DELAY  1000
void cmd_rst_exec();

// init at callback
void init_at_callback();

// PWM
void cmd_iopwmfreq_read();
void cmd_iopwmfreq_write(char*str , int len);
void cmd_iopwmduty_read();
void cmd_iopwmduty_write(char*str , int len);

// CGSN
void cmd_cgsn();

// RESTORE
void cmd_restore();

// IOVO
void cmd_iovo_read();
void cmd_iovo_write(char*str , int len);

// RLY
void cmd_iorly_read();
void cmd_iorly_write(char*str , int len);

// DEBUG
void cmd_debug_exec(void);

#endif /* INCLUDE_AT_CMD_AT_CMDS_H_ */
