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
 * First written on 8 Dec, 2005 be Kendal Correll
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


ex1629_result_t libex1629_get_trigger_timestamp(struct ex1629_client *cl,
        uint32_t *board, uint32_t *sec, uint32_t *nanosec, uint32_t *femtosec)
{
  LIBEX1629_FUNCTION_INIT(rpc_timestamp, rpc_uint32);
  
  rpc_arg.value = *board;
  
  LIBEX1629_CALL_RPC(get_trigger_timestamp);
  
  *board = result.board;
  *sec = result.sec;
  *nanosec = result.nanosec;
  *femtosec = result.femtosec;
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_sync_timestamp(struct ex1629_client *cl,
        uint32_t *board, uint32_t *sec, uint32_t *nanosec, uint32_t *femtosec)
{
  LIBEX1629_FUNCTION_INIT(rpc_timestamp, rpc_uint32);
  
  rpc_arg.value = *board;
  
  LIBEX1629_CALL_RPC(get_sync_timestamp);
  
  *board = result.board;
  *sec = result.sec;
  *nanosec = result.nanosec;
  *femtosec = result.femtosec;
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_sync_timestamp(struct ex1629_client *cl,
        uint32_t board, uint32_t sec, uint32_t nanosec, uint32_t femtosec)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_timestamp);
  
  rpc_arg.board = board;
  rpc_arg.sec = sec;
  rpc_arg.nanosec = nanosec;
  rpc_arg.femtosec = femtosec;
  
  LIBEX1629_CALL_RPC(set_sync_timestamp);
  
  LIBEX1629_FUNCTION_END();
}
