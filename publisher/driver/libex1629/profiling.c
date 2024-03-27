/*******************************************************************************
 *
 * Module Name: config.c
 *
 * Copyright 2005 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on November 15, 2005 by Nick Barendt
 *
 * Module Description:
 *   This wrapper provides device profiling.
 *
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "libex1629.h"
#include "libex1629_internal.h"


ex1629_result_t libex1629_set_profiling_enabled(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(set_profiling_enabled);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_profiling_disabled(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(set_profiling_disabled);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_reset_profiling(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(reset_profiling);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_profiling(struct ex1629_client *cl, rpc_profresult *profresult)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_profresult);

  LIBEX1629_CALL_SIMPLE_RPC(get_profiling);
  memcpy(profresult, &result, sizeof(rpc_profresult));
  /* The client is responsible to call libex1629_free_config_data after it has
   *   processed the data. */
  LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE();
}


ex1629_result_t libex1629_free_profiling_data(rpc_profresult *profdata)
{
  if(profdata != NULL)
    LIBEX1629_XDR_FREE(rpc_profresult, profdata);
  return EX1629_SUCCESS;
}

