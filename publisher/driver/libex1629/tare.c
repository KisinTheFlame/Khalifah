/*******************************************************************************
 *
 * Module Name: tare.c
 *
 * Copyright 2005 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 14 June 2005 by Kendall Correll as a stub.
 *
 * Module Description:
 *   STUB
 *
 ******************************************************************************/
#ifndef _WRS_KERNEL //VxWorks can't find rpc_tarespec, and won't build this
#include <ex1629_errors.h>
#include "libex1629.h"
#include "libex1629_internal.h"

ex1629_result_t libex1629_tare_init(struct ex1629_client *cl,
				       int32_t numchannels, int32_t channels[])
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_tarespec);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
  }

  LIBEX1629_CALL_RPC(tare_init);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_tare_status(struct ex1629_client *cl, uint32_t *percent)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_tarestatusresult);
  LIBEX1629_CALL_SIMPLE_RPC(tare_status);
  *percent = result.percent_completed;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_tare_store(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(tare_store);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_tare_erase_stored(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(tare_erase_stored);
  LIBEX1629_FUNCTION_END();
}
#endif
