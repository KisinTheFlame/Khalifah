/*******************************************************************************
 *
 * Module Name: filter.c
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
 *   This wrapper provides analog board filter control.
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


ex1629_result_t libex1629_set_filter(struct ex1629_client *cl, 
    int32_t numchannels, int32_t channels[], int type, double fp,
    int32_t transform, uint32_t user_order)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setfilter);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(type, numchannels);
  LIBEX1629_CREATE_ARRAY(fp, numchannels);
  LIBEX1629_CREATE_ARRAY(transform, numchannels);
  LIBEX1629_CREATE_ARRAY(user_order, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.type.type_val[i] = type;
    rpc_arg.fp.fp_val[i] = fp;
    rpc_arg.transform.transform_val[i] = transform;
    rpc_arg.user_order.user_order_val[i] = user_order;
  }

  LIBEX1629_CALL_RPC(set_filter);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_filter(struct ex1629_client *cl,
    int32_t channel, int *type, double *fp, uint32_t *transform, uint32_t *user_order,
    uint32_t *calc_order, float *overshoot, uint32_t *risetime, float *grp_delay)
{
  LIBEX1629_FUNCTION_INIT(rpc_getfilter, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_filter);

  *type = result.type;
  *fp = result.fp;
  *transform = result.transform;
  *user_order = result.user_order;
  *calc_order = result.calc_order;
  *overshoot = result.overshoot;
  *risetime = result.risetime;
  *grp_delay = result.grp_delay;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_settling_time(struct ex1629_client *cl,
    int32_t channel, float *settling_time)
{
  LIBEX1629_FUNCTION_INIT(rpc_settlingtime, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_settling_time);

  *settling_time = result.settling_time;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_samp_freq(struct ex1629_client *cl, double fs)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_sampfreq);

  rpc_arg.fs = fs;

  LIBEX1629_CALL_RPC(set_samp_freq);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_samp_freq(struct ex1629_client *cl, double *fs)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_sampfreq);

  LIBEX1629_CALL_SIMPLE_RPC(get_samp_freq);

  *fs = result.fs;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_cic_decimation(struct ex1629_client *cl,
    uint32_t *r, float *gain_comp)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_getcicdecimation);

  LIBEX1629_CALL_SIMPLE_RPC(get_cic_decimation);

  *r = result.r;
  *gain_comp = result.gain_comp;

  LIBEX1629_FUNCTION_END();
}
