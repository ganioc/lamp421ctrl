/*
 * at_parser.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#include "at_cmds.h"
#include "at_parser.h"

#include <string.h>
#include <ctype.h>

enum PARSE_STATE at_state = AT_S_DUMMY;

uint8_t name_index;
uint8_t args_index;

uint8_t AT_in_handling = 0;


struct AT_CMD cmd_for_one_byte={
		.type = _AT_UNKNOWN,
		.name = {0},
		.args = {0}
};

void reset_parse_state() {
	name_index = 0;
	args_index = 0;
	at_state = AT_S_DUMMY;
}
void parserTimerCallback() {
	// at32_led_toggle(LED3);
	PRINT_LOG("+");
	PRINT_LOG("timeout counter:%d\r\n", (AT_TIMEOUT_DUR*65535/(1000*109)));
	SEND_RESPONSE_TIMEOUT(AT_ERROR_TIMEOUT);

	reset_parse_state();
}

void enter_handling() {
	START_TIMER();
}
void exit_handling(char *code) {
	reset_parse_state();
	STOP_TIMER();
	SEND_RESPONSE_ERROR(code);
}

void end_handling(struct AT_CMD *cmd) {
	STOP_TIMER();
	handle_at_cmd(*cmd);
	reset_parse_state();
}

// AT+CDATE="2022-02-21T16:31:01.001"
// AT+CDATE="2022-02-22T10:53:55.001"
// AT+CDATE?
void parse_at_cmd(char *str, uint16_t *head, uint16_t *tail,
		uint16_t at_rx_buffer_len) {
	struct AT_CMD cmd;
	cmd.type = _AT_UNKNOWN;

	while (*head != *tail) {
		uint8_t ch = str[*tail];
		switch (at_state) {
		case AT_S_DUMMY:
			if (ch == 'A' || ch == 'a') {
				at_state = AT_S_HEAD;
				name_index = 0;
				args_index = 0;
			}
			break;
		case AT_S_HEAD:
			if (ch == 'T' || ch == 't') {
				at_state = AT_S_PLUS;
				enter_handling();
			} else {
				PRINT_LOG("parse head fail");
				at_state = AT_S_DUMMY;
			}
			break;
		case AT_S_PLUS:
			if (ch == '+') {
				at_state = AT_S_TAG;
			} else if (ch == '\r') {
				cmd.type = _AT_EXEC;
				sprintf(cmd.name, "");
				end_handling(&cmd);
				break;
			} else {
				exit_handling(AT_ERROR_POSITION);

			}
			break;
		case AT_S_TAG:
			if (ch == '?' && name_index > 0) {
				cmd.name[name_index] = 0;
				cmd.type = _AT_GET;
				at_state = AT_S_CARRIAGE;
			} else if (ch == '=' && name_index > 0) {
				cmd.name[name_index] = 0;
				at_state = AT_S_OPERATOR;
			} else if (ch == '\r' && name_index > 0) {
				cmd.name[name_index] = 0;
				cmd.type = _AT_EXEC;
				end_handling(&cmd);
				break;
			} else if (isalpha(ch) != 0) {
				cmd.name[name_index++] = toupper(ch);
			} else {
				exit_handling(AT_ERROR_POSITION);
			}
			break;
		case AT_S_OPERATOR:
			if (ch == '?' && args_index == 0) {
				cmd.type = _AT_TEST;
				at_state = AT_S_CARRIAGE;
			} else if (ch == '\r' && args_index > 0) {
				cmd.args[args_index] = 0;
				end_handling(&cmd);
				break;
			} else if (isalpha(ch) != 0 ||
			isupper(ch) != 0 ||
			isdigit(ch) != 0 || ch == '"' || ch == '-' || ch == '.' || ch == ':'
					|| ch == ',') {
				cmd.type = _AT_SET;
				cmd.args[args_index++] = ch;
			} else {
				exit_handling(AT_ERROR_PARAMETER);
			}
			break;
		case AT_S_CARRIAGE:
			if (ch == '\r') {
				end_handling(&cmd);
				break;
			} else {
				exit_handling(AT_ERROR_POSITION);
			}
			break;
		default:
			break;
		}

		(*tail)++;
		if ((*tail) >= at_rx_buffer_len) {
			(*tail) = 0;
		}
	}

}

void parse_at_cmd_one_byte(char ch) {

	switch (at_state) {
	case AT_S_DUMMY:
		if (ch == 'A' || ch == 'a') {
			at_state = AT_S_HEAD;
			name_index = 0;
			args_index = 0;
		}
		break;
	case AT_S_HEAD:
		if (ch == 'T' || ch == 't') {
			at_state = AT_S_PLUS;
			enter_handling();
		} else {
			PRINT_LOG("parse head fail");
			at_state = AT_S_DUMMY;
		}
		break;
	case AT_S_PLUS:
		if (ch == '+') {
			at_state = AT_S_TAG;
		} else if (ch == '\r') {
			cmd_for_one_byte.type = _AT_EXEC;
			sprintf(cmd_for_one_byte.name, "");
			end_handling(&cmd_for_one_byte);
			break;
		} else {
			exit_handling(AT_ERROR_POSITION);

		}
		break;
	case AT_S_TAG:
		if (ch == '?' && name_index > 0) {
			cmd_for_one_byte.name[name_index] = 0;
			cmd_for_one_byte.type = _AT_GET;
			at_state = AT_S_CARRIAGE;
		} else if (ch == '=' && name_index > 0) {
			cmd_for_one_byte.name[name_index] = 0;
			at_state = AT_S_OPERATOR;
		} else if (ch == '\r' && name_index > 0) {
			cmd_for_one_byte.name[name_index] = 0;
			cmd_for_one_byte.type = _AT_EXEC;
			end_handling(&cmd_for_one_byte);
			break;
		} else if (isalpha(ch) != 0) {
			cmd_for_one_byte.name[name_index++] = toupper(ch);
		} else {
			exit_handling(AT_ERROR_POSITION);
		}
		break;
	case AT_S_OPERATOR:
		if (ch == '?' && args_index == 0) {
			cmd_for_one_byte.type = _AT_TEST;
			at_state = AT_S_CARRIAGE;
		} else if (ch == '\r' && args_index > 0) {
			cmd_for_one_byte.args[args_index] = 0;
			end_handling(&cmd_for_one_byte);
			break;
		} else if (isalpha(ch) != 0 ||
		isupper(ch) != 0 ||
		isdigit(ch) != 0 || ch == '"' || ch == '-' || ch == '.' || ch == ':'
				|| ch == ',') {
			cmd_for_one_byte.type = _AT_SET;
			cmd_for_one_byte.args[args_index++] = ch;
		} else {
			exit_handling(AT_ERROR_PARAMETER);
		}
		break;
	case AT_S_CARRIAGE:
		if (ch == '\r') {
			end_handling(&cmd_for_one_byte);
			break;
		} else {
			exit_handling(AT_ERROR_POSITION);
		}
		break;
	default:
		break;
	}
}

