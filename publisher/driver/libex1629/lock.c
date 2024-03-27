/*******************************************************************************
 *
 * Module Name: lock.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 14 January 2005 by Nick Barendt
 *
 * Module Description:
 *   This wrapper provides locking control
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


ex1629_result_t libex1629_lock(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT( rpc_result );

  LIBEX1629_CALL_SIMPLE_RPC(lock);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_unlock(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT( rpc_result );

  LIBEX1629_CALL_SIMPLE_RPC(unlock);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_break_lock(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT( rpc_result );

  LIBEX1629_CALL_SIMPLE_RPC(break_lock);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_check_lock(struct ex1629_client *cl, int *locked, int *lid)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT( rpc_lockstatus );

  LIBEX1629_CALL_SIMPLE_RPC(check_lock);
  if( locked )
    *locked = result.locked;
  if( lid )
    *lid = result.lid;
  LIBEX1629_FUNCTION_END();
}
