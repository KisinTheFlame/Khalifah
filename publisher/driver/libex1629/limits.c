/*******************************************************************************
 *
 * Module Name: limits.c
 *
 * Copyright 2005 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on May 9, 2006 by James Jurack
 *
 * Module Description:
 *   This wrapper provides controls for bridge and confidence limit checking
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


ex1629_result_t libex1629_set_conf_limit_reporting_mode(struct ex1629_client *cl,
        conf_limit_reporting_mode mode)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_conflimitreportingmode);

  rpc_arg.reporting_mode = mode;

  LIBEX1629_CALL_RPC(set_conf_limit_reporting_mode);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_conf_limit_reporting_mode(struct ex1629_client *cl,
        conf_limit_reporting_mode *mode)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_conflimitreportingmode);

  LIBEX1629_CALL_SIMPLE_RPC(get_conf_limit_reporting_mode);

  *mode = result.reporting_mode;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_conf_limit(struct ex1629_client *cl,
        int32_t num_channels, int32_t channels[], int32_t conf_channel,
        double min[], double max[])
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setconflimit);
  LIBEX1629_CREATE_ARRAY(channels, num_channels);
  LIBEX1629_CREATE_ARRAY(min, num_channels);
  LIBEX1629_CREATE_ARRAY(max, num_channels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ) {
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.min.min_val[i] = min[i];
    rpc_arg.max.max_val[i] = max[i];
  }

  rpc_arg.conf_channel = conf_channel;

  LIBEX1629_CALL_RPC(set_conf_limit);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_conf_limit(struct ex1629_client *cl,
        int32_t channel, int32_t conf_channel, double *min, double *max)
{
  LIBEX1629_FUNCTION_INIT(rpc_getconflimitresult, rpc_getconflimitarg);

  rpc_arg.ch = channel;
  rpc_arg.conf_channel = conf_channel;
  LIBEX1629_CALL_RPC(get_conf_limit);

  *min = result.min;
  *max = result.max;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_bridge_limit_enabled(struct ex1629_client *cl,
        int enabled)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_bridgelimitenabled);

  rpc_arg.enabled = enabled;

  LIBEX1629_CALL_RPC(set_bridge_limit_enabled);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_bridge_limit_enabled(struct ex1629_client *cl,
        int *enabled)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_bridgelimitenabled);

  LIBEX1629_CALL_SIMPLE_RPC(get_bridge_limit_enabled);

  *enabled = result.enabled;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_bridge_limit(struct ex1629_client *cl,
        int32_t num_channels, int32_t channels[], double min[], double max[])
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setbridgelimit);
  LIBEX1629_CREATE_ARRAY(channels, num_channels);
  LIBEX1629_CREATE_ARRAY(min, num_channels);
  LIBEX1629_CREATE_ARRAY(max, num_channels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ) {
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.min.min_val[i] = min[i];
    rpc_arg.max.max_val[i] = max[i];
  }

  LIBEX1629_CALL_RPC(set_bridge_limit);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_bridge_limit(struct ex1629_client *cl,
        int32_t channel, double *min, double *max)
{
  LIBEX1629_FUNCTION_INIT(rpc_getbridgelimit, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_bridge_limit);

  *min = result.min;
  *max = result.max;

  LIBEX1629_FUNCTION_END();
}

