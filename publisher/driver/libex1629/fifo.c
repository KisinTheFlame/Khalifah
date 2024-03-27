/*******************************************************************************
 *
 * Module Name: fifo.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 19 January 2005 by Nick Barendt
 *
 * Module Description:
 *   This wrapper provides fifo control.
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

ex1629_result_t libex1629_readfifo(struct ex1629_client *cl,
				   int num_pages, int *fifo_count, 
				   rpc_fifoarray *fifoarray)
{
  LIBEX1629_FUNCTION_INIT(rpc_fifoarray, rpc_pagecount);
  
  rpc_arg.page_count = num_pages;

  LIBEX1629_CALL_RPC(read_fifo);

/*   printf("%s fifocount = %d\n", __FUNCTION__, result.fifo_count); */
  *fifo_count = result.fifo_count;
  memcpy(fifoarray, &result, sizeof(rpc_fifoarray));

  /* The client is responsible to call libex1629_free_fifoarray after it has
   *   processed the rpc_fifoarray array. */
  LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE();
}

ex1629_result_t libex1629_free_fifoarray(rpc_fifoarray *fifoarray)
{
  LIBEX1629_XDR_FREE(rpc_fifoarray, fifoarray);
  return EX1629_SUCCESS;
}

ex1629_result_t  libex1629_resetfifo(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(reset_fifo);

  LIBEX1629_FUNCTION_END();
}

const char *build_eu_float_format (void) {
    return "%+2.13e"; 
}

