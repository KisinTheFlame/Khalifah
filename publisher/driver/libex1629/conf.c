/*******************************************************************************
 *
 * Module Name: conf.c
 *
 * Copyright 2005 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on June 8, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides analog board confidence scanlist control.
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


ex1629_result_t libex1629_set_conf_scanlist(struct ex1629_client *cl,
                                            int32_t numsources, int32_t sources[])
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_confscanlist);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(confscanlist, numsources);

  for( i = 0; i < rpc_arg.confscanlist.confscanlist_len; i++ ){
    rpc_arg.confscanlist.confscanlist_val[i] = sources[i];
  }

  LIBEX1629_CALL_RPC(set_conf_scanlist);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_conf_scanlist(struct ex1629_client *cl,
                                            int32_t *numsources, int32_t sources[])
{
  int i;

  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_confscanlist);

  LIBEX1629_CALL_SIMPLE_RPC(get_conf_scanlist);

  *numsources = result.confscanlist.confscanlist_len;

  for( i = 0; i < *numsources; i++ ){
    sources[i] = result.confscanlist.confscanlist_val[i];
  }

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_conf_filter_wt(struct ex1629_client *cl,
  uint32_t *board, float *wt)
{
  LIBEX1629_FUNCTION_INIT(rpc_conf_filter_wt, rpc_uint32);
  
  rpc_arg.value = *board;
  
  LIBEX1629_CALL_RPC(get_conf_filter_wt);
  
  *board = result.board;
  *wt = result.wt;
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_conf_filter_wt(struct ex1629_client *cl,
  uint32_t board, float wt)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_conf_filter_wt);
  
  rpc_arg.board = board;
  rpc_arg.wt = wt;
  
  LIBEX1629_CALL_RPC(set_conf_filter_wt);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_measure_confidence(struct ex1629_client *cl,
    int32_t confValue, int32_t numChannels, int32_t channels[], int32_t sampleCount,
    float data[]) 

{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_measureddata, rpc_measureconfidence);

  LIBEX1629_CREATE_ARRAY(channels, numChannels);

  for (i = 0; i < rpc_arg.channels.channels_len; i++) {
    rpc_arg.channels.channels_val[i] = channels[i];
  }
  rpc_arg.num_samples = sampleCount;
  rpc_arg.confidence_source = confValue;

  LIBEX1629_CALL_RPC(measure_confidence_values);

  for (i = 0; i < result.data.data_len; i++) {
    data[i] = result.data.data_val[i];
  }
  
  /* If less data than twice the number of channels is returned, 
   * clear the rest */
  for ( ; i < rpc_arg.channels.channels_len; i++) {
    data[i] = 0;
  }

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_excite_curr_supported(struct ex1629_client *cl,
        int* supported)
{
    LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_excitecurrsupported);
    LIBEX1629_CALL_SIMPLE_RPC(get_excite_curr_supported);
    *supported = result.supported;
    LIBEX1629_FUNCTION_END();
}
