/*******************************************************************************
 *
 * Module Name: gain.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on March 11, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides analog board gain control.
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


ex1629_result_t libex1629_set_gain(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], int gain)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setgain);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(gain, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.gain.gain_val[i] = gain;
  }

  LIBEX1629_CALL_RPC(set_gain);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_gain(struct ex1629_client *cl, int32_t channel, int *gain)
{
  LIBEX1629_FUNCTION_INIT(rpc_getgain, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_gain);

  *gain = result.gain;

  LIBEX1629_FUNCTION_END();
}
