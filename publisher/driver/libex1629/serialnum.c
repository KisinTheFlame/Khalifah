/*******************************************************************************
 *
 * Module Name: serialnumber.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 15 February 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides serial number query ability
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


ex1629_result_t libex1629_get_serial_num(struct ex1629_client *cl, char *serial)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_serial_num);
  LIBEX1629_CALL_SIMPLE_RPC(get_serial_num);

  /* Copy the results */
  strncpy(serial, result.serial, MAX_SERIAL_NUM_LENGTH);

  LIBEX1629_FUNCTION_END();
}
