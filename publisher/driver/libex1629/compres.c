/*******************************************************************************
 *
 * Module Name: compres.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on April 5, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides analog board compensation resistor control.
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


ex1629_result_t libex1629_set_compres(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], enum compres res)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setcompres);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(res, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.res.res_val[i] = res;
  }

  LIBEX1629_CALL_RPC(set_compres);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_compres(struct ex1629_client *cl, int32_t channel,
                                      enum compres *res, float *user_value,
                                      float *compres_350_value, 
                                      float *compres_120_value)
{
  LIBEX1629_FUNCTION_INIT(rpc_getcompres, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_compres);

  *res = result.res;
  *user_value = result.user_value;
  *compres_350_value = result.compres_350_value;
  *compres_120_value = result.compres_120_value;

  LIBEX1629_FUNCTION_END();
}
