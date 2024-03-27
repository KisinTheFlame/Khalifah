/*******************************************************************************
 *
 * Module Name: corevolt.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 16 February 2006 by James Jurack
 *
 * Module Description:
 *   This module is used to control the core voltage regulator interfaces
 *
 ******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <ex1629_errors.h>
#include "libex1629.h"
#include "libex1629_internal.h"


ex1629_result_t libex1629_set_corevoltreg(struct ex1629_client *cl,
                                          uint32_t parm1, uint32_t parm2,
                                          uint32_t parm3, uint32_t parm4,
                                          uint32_t parm5)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_corevoltreg);
  
  rpc_arg.parm1 = parm1;
  rpc_arg.parm2 = parm2;
  rpc_arg.parm3 = parm3;
  rpc_arg.parm4 = parm4;
  rpc_arg.parm5 = parm5;
  LIBEX1629_CALL_RPC(set_corevoltreg);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_corevoltreg(struct ex1629_client *cl,
                                          uint32_t *parm1, uint32_t *parm2,
                                          uint32_t *parm3, uint32_t *parm4,
                                          uint32_t *parm5)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_corevoltreg);
  
  LIBEX1629_CALL_SIMPLE_RPC(get_corevoltreg);
  *parm1 = result.parm1;
  *parm2 = result.parm2;
  *parm3 = result.parm3;
  *parm4 = result.parm4;
  *parm5 = result.parm5;
  
  LIBEX1629_FUNCTION_END();
}

