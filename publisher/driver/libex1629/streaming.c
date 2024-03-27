/*******************************************************************************
 *
 * Module Name: streaming.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 4 March 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides data streaming control.
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


ex1629_result_t libex1629_streaming_connect(struct ex1629_client *cl, uint16_t port)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_port);

  rpc_arg.port = port;
  LIBEX1629_CALL_RPC(streaming_connect);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_streaming_disconnect(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_disconnect);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_net_decimation(struct ex1629_client *cl, uint32_t dec)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint32);

  rpc_arg.value = dec;
  LIBEX1629_CALL_RPC(set_net_decimation);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_net_decimation(struct ex1629_client *cl, uint32_t *dec)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint32);

  LIBEX1629_CALL_SIMPLE_RPC(get_net_decimation);
  if(dec)
    *dec = result.value;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_connect(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_connect);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_disconnect(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_disconnect);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_stop(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_stop);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_record(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_record);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_erase(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_erase);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_play(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_play);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_seek(struct ex1629_client *cl,
                                            unsigned sec, unsigned nanosec)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_time);
  
  rpc_arg.sec = sec;
  rpc_arg.nanosec = nanosec;
  LIBEX1629_CALL_RPC(streaming_hd_seek);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_stat(struct ex1629_client *cl,
                                            int *exists, time_t *modified,
                                            uint64_t *bytes, int32_t *samples,
                                            uint32_t *sec, int32_t *nanosec,
                                            uint64_t *disk_size, uint64_t *disk_free)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_hd_statistics);
  
  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_stat);
  *exists = result.exists;
  *modified = (time_t)result.modified;
  *bytes = result.bytes;
  *samples = result.samples;
  *sec = result.sec;
  *nanosec = result.nanosec;
  *disk_size = result.disk_size;
  *disk_free = result.disk_free;
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_streaming_hd_get_state(struct ex1629_client *cl,
                                            enum streaming_hd_state *hd_state)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_hd_state);
  
  LIBEX1629_CALL_SIMPLE_RPC(streaming_hd_get_state);
  *hd_state = result.hd_state;
  
  LIBEX1629_FUNCTION_END();
}

