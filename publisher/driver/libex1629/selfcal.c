/*******************************************************************************
 *
 * Module Name: cal.c
 *
 * Copyright 2005 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 08 June 2005 by Lars Harrison as a stub.
 *
 * Module Description:
 *   This wrapper provides self calibration functionality.
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

//self_calibration_init
//self_calibration_clear
//self_calibration_clear_stored
//self_calibration_load
//self_calibration_store
//self_calibration_is_stored

ex1629_result_t libex1629_self_calibration_init(struct ex1629_client *cl,
        int *magic, int *recommended_uptime, int *current_uptime)
{
  LIBEX1629_FUNCTION_INIT(rpc_calresult, rpc_calmagic);
  rpc_arg.magic = (*magic);
  rpc_arg.lid = cl->lid;
  LIBEX1629_CALL_RPC(self_calibration_init);
  *magic = result.magic;
  *recommended_uptime = result.recommended_uptime;
  *current_uptime = result.current_uptime;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_zero_calibration_init(struct ex1629_client *cl,
        int *magic, int *recommended_uptime, int *current_uptime)
{
  LIBEX1629_FUNCTION_INIT(rpc_calresult, rpc_calmagic);
  rpc_arg.magic = (*magic);
  rpc_arg.lid = cl->lid;
  LIBEX1629_CALL_RPC(zero_calibration_init);
  *magic = result.magic;
  *recommended_uptime = result.recommended_uptime;
  *current_uptime = result.current_uptime;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_calibration_clear(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(self_calibration_clear);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_calibration_clear_stored(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(self_calibration_clear_stored);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_calibration_load(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(self_calibration_load);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_calibration_store(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(self_calibration_store);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_calibration_is_stored(struct ex1629_client *cl, int *has_stored_cal)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_storedselfcal);
  LIBEX1629_CALL_SIMPLE_RPC(self_calibration_is_stored);

  *has_stored_cal = result.has_stored_cal;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_self_calibration_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[])
{
  int i;
  
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_selfcal_status);
  LIBEX1629_CALL_SIMPLE_RPC(get_selfcal_status);
  
  *numfailedchannels = result.failedchannels.failedchannels_len;
  
  for( i = 0; i < *numfailedchannels; i++ ){
    failedchannels[i] = result.failedchannels.failedchannels_val[i];
  }
  
  LIBEX1629_FUNCTION_END();
}

