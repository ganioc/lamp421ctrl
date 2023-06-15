/*
 * at_struct.h
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */

#ifndef INCLUDE_AT_CMD_AT_STRUCT_H_
#define INCLUDE_AT_CMD_AT_STRUCT_H_

#ifdef AT_START_F421_V1

#include "at32f421_board.h"
#include "at32f421_clock.h"

#endif

#ifdef AT_START_F415_V1

#include "at32f415_board.h"
#include "at32f415_clock.h"

#endif

#include "at_cmds.h"

/** End of response time between characters in ms */
#define _AT_ST_TIMER                                5
/** Max command size excluding command args */
#define _AT_CMD_MAXSIZE                             15
/** 0 HFC disabled / 1 HFC enabled */
#define _AT_HFC_CONTROL                             0

/** Global termintation character */
#define _AT_TERMINATE                               0x0D
/** Special termination character */
#define _AT_TERMINATE_ADD                           0x1A


/**
 * @name                 AT Command Types
 *
 * Command types provided as second argument during the handler call.
 *
 * @note Use this values to decide which type of command made handler call.
 *
 ******************************************************************************/
#define _AT_UNKNOWN                                 (0)
#define _AT_TEST                                    (1)
#define _AT_SET                                     (2)
#define _AT_GET                                     (3)
#define _AT_URC                                     (4)
#define _AT_EXEC                                    (5)

/**
 * @typedef Handler Prototype
 */
typedef void ( *T_AT_handler )( char *buffer, uint8_t len );
typedef void (*T_AT_exec_handler)(void);
typedef void (*T_AT_read_handler)(void);
typedef void (*T_AT_test_handler)(void);
typedef void (*T_AT_write_handler)(char* buffer, int len);

typedef void (*at_callback)(void);

struct AT_CALLBACK{
	char*        name;
	uint32_t     hash;
	T_AT_test_handler  test_cb;
	T_AT_read_handler  read_cb;
	T_AT_write_handler write_cb;
	T_AT_exec_handler  exec_cb;
};

struct AT_CMD {
	uint8_t      type;
	char         name[_AT_CMD_MAXSIZE];
	char         args[48];
};

struct AT_DUAL_INT_PARAM{
	uint8_t      id;
	uint16_t     value;
};

// for quick search of callback cmd
uint32_t makeHash( char *pCmd );
void init_at_callback();
//struct AT_CALLBACK* search_at_callback_by_name(char* name);
void handle_at_cmd(struct AT_CMD cmd);
error_status parse_dual_int_param(char* str,
		int len,
		struct AT_DUAL_INT_PARAM* param);


#endif /* INCLUDE_AT_CMD_AT_STRUCT_H_ */
