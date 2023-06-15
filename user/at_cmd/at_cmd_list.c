/*
 * at_cmd_list.c
 *
 *  Created on: 2023 Mar 9
 *      Author: ruffman
 */


#include "at_struct.h"

#include "at_cmds.h"

struct AT_CALLBACK at_cmd_list[] = {
	{
		name:     "",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_at_exec
	},
	{
		name:     "VER",
		hash:     0,
		test_cb:  cmd_version_test,
		read_cb:  cmd_version_read,
		write_cb: cmd_version_write,
		exec_cb:  cmd_version_exec
	},
	{
		name:     "RST",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_rst_exec
	},
	{
		name:     "IOPWMFREQ",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_iopwmfreq_read,
		write_cb: cmd_iopwmfreq_write,
		exec_cb:  NULL
	},
	{
		name:     "IOPWMDUTY",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_iopwmduty_read,
		write_cb: cmd_iopwmduty_write,
		exec_cb:  NULL
	},
	{
		name:     "CGSN",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_cgsn
	},
	{
		name:     "RESTORE",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_restore
	},
	{
		name:     "IOVO",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_iovo_read,
		write_cb: cmd_iovo_write,
		exec_cb:  NULL
	},
	{
		name:     "IORLY",
		hash:     0,
		test_cb:  NULL,
		read_cb:  cmd_iorly_read,
		write_cb: cmd_iorly_write,
		exec_cb:  NULL
	},
	{
		name:     "DEBUG",
		hash:     0,
		test_cb:  NULL,
		read_cb:  NULL,
		write_cb: NULL,
		exec_cb:  cmd_debug_exec
	}
};


int NUM_AT_CALLBACK = sizeof(at_cmd_list)/sizeof(at_cmd_list[0]);


