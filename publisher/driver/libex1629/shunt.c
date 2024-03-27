/*******************************************************************************
 *
 * Module Name: shunt.c
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
 *   This wrapper provides analog board shunt control.
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


ex1629_result_t libex1629_set_shunt(struct ex1629_client *cl, 
    int32_t numchannels, int32_t channels[], enum shunt_source src,
    float front_panel_val, float internal_val, float teds_val)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setshunt);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(src, numchannels);
  LIBEX1629_CREATE_ARRAY(front_panel_val, numchannels);
  LIBEX1629_CREATE_ARRAY(internal_val, numchannels);
  LIBEX1629_CREATE_ARRAY(teds_val, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.src.src_val[i] = src;
    rpc_arg.front_panel_val.front_panel_val_val[i] = front_panel_val;
    rpc_arg.internal_val.internal_val_val[i] = internal_val;
    rpc_arg.teds_val.teds_val_val[i] = teds_val;
  }

  LIBEX1629_CALL_RPC(set_shunt);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_shunt(struct ex1629_client *cl, int32_t channel,
    enum shunt_source *src, float *front_panel_val, float *internal_val, float *teds_val)
{
  LIBEX1629_FUNCTION_INIT(rpc_getshunt, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_shunt);

  *src = result.src;
  *front_panel_val = result.front_panel_val;
  *internal_val = result.internal_val;
  *teds_val = result.teds_val;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_shunt_enable(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], uint32_t enabled)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setshuntenable);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(enabled, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.enabled.enabled_val[i] = enabled;
  }

  LIBEX1629_CALL_RPC(set_shunt_enable);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_shunt_enable(struct ex1629_client *cl,
    int32_t channel, uint32_t *enabled)
{
  LIBEX1629_FUNCTION_INIT(rpc_getshuntenable, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_shunt_enable);

  *enabled = result.enabled;

  LIBEX1629_FUNCTION_END();
}
