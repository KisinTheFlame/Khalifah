/*******************************************************************************
 *
 * Module Name: scanlist.c
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
 *   This wrapper provides scanlist control.
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


ex1629_result_t libex1629_allow_bad_channels(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(allow_bad_channels);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_scanlist(struct ex1629_client *cl,
				       int32_t numchannels, int32_t channels[])
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_scanlist);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
  }

  LIBEX1629_CALL_RPC(set_scanlist);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_scanlist(struct ex1629_client *cl,
				       int32_t *numchannels, int32_t channels[])
{
  int i;

  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_scanlist);

  LIBEX1629_CALL_SIMPLE_RPC(get_scanlist);

  *numchannels = result.channels.channels_len;

  for( i = 0; i < *numchannels; i++ ){
    channels[i] = result.channels.channels_val[i];
  }

  LIBEX1629_FUNCTION_END();
}

