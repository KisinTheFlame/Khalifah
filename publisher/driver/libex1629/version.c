/*******************************************************************************
 *
 * Module Name: version.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 17 February 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides firmware and DSP version query ability
 *
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <ex1629_errors.h>
#include "libex1629.h"
#include "libex1629_internal.h"


ex1629_result_t libex1629_get_firmware_version(struct ex1629_client *cl, char *prefix,
                                               int *major, int *minor, int *build)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_firmware_version);
  LIBEX1629_CALL_CORE_RPC(get_firmware_version);

  /* Copy the results */
  strncpy(prefix, result.prefix, MAX_FIRMWARE_STRING_LENGTH);
  *major = result.major;
  *minor = result.minor;
  *build = result.build;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_dspversion(struct ex1629_client *cl, int board, char *manufstr,
	char *modelstr, char *version_prefix, uint32_t *version_major, uint32_t *version_minor,
	uint32_t *version_build, char *date, char *time, uint32_t *fpga_ver, uint32_t *board_rev)
{
  LIBEX1629_FUNCTION_INIT(rpc_getdspversion, rpc_board);
  rpc_arg.board = board;
  LIBEX1629_CALL_RPC(get_dspversion);

  /* Copy the results */
  strncpy(manufstr, result.manufstr, EX1629_MAX_DSPVERSION_STR_LEN);
  strncpy(modelstr, result.modelstr, EX1629_MAX_DSPVERSION_STR_LEN);
  strncpy(version_prefix, result.version_prefix, EX1629_MAX_DSPVERSION_STR_LEN);
  *version_major = result.version_major;
  *version_minor = result.version_minor;
  *version_build = result.version_build;
  strncpy(date, result.date, EX1629_MAX_DSPVERSION_STR_LEN);
  strncpy(time, result.time, EX1629_MAX_DSPVERSION_STR_LEN);
  *fpga_ver = result.fpga_ver;
  *board_rev = result.board_rev;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_backplaneversion(struct ex1629_client *cl, uint16_t *backplane_version)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_getbackplaneversion);
  LIBEX1629_CALL_SIMPLE_RPC(get_backplaneversion);

  /* Copy the results */
  *backplane_version = result.backplane_version;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_digitalversion(struct ex1629_client *cl, unsigned int *digital_version, uint32_t *cpu_version, char *cpu_desc)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_getdigitalversion);
  LIBEX1629_CALL_SIMPLE_RPC(get_digitalversion);

  /* Copy the results */
  *digital_version = result.digital_version;
  *cpu_version = result.cpu_version;
  strncpy(cpu_desc, result.cpu_desc, EX1629_MAX_HWVERSION_STR_LEN);

  LIBEX1629_FUNCTION_END();
}
