/*******************************************************************************
 *
 * Module Name: dio.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 6 October 2004 by Gary Bernhardt
 *
 * Module Description:
 *   This wrapper provides the DIO functions for libex1629.
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

ex1629_result_t libex1629_reg_set_reg(struct ex1629_client *cl,
					     uint32_t board, uint32_t address, uint32_t value)
{
  LIBEX1629_FUNCTION_INIT(rpc_dspreg, rpc_dspreg);
  rpc_arg.board = board;
  rpc_arg.address = address;
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(dsp_reg_set);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_reg_get_reg(struct ex1629_client *cl,
					     uint32_t board, uint32_t address, uint32_t *value)
{
  LIBEX1629_FUNCTION_INIT(rpc_dspreg, rpc_dspreg);
  rpc_arg.board = board;
  rpc_arg.address = address;
  LIBEX1629_CALL_RPC(dsp_reg_get);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}



ex1629_result_t libex1629_reg_set_cal_src(struct ex1629_client *cl, enum calsrc src) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_regsetcalsrc);
  rpc_arg.type = src;
  LIBEX1629_CALL_RPC(reg_set_cal_src);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_reg_get_cal_src(struct ex1629_client *cl, enum calsrc *src) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_reggetcalsrc);
  LIBEX1629_CALL_SIMPLE_RPC(reg_get_cal_src);
  *src = result.type;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_reg_set_cal_out(struct ex1629_client *cl, enum calout src) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_regsetcalout);
  rpc_arg.type = src;
  LIBEX1629_CALL_RPC(reg_set_cal_out);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_reg_get_cal_out(struct ex1629_client *cl, enum calout *src) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_reggetcalout);
  LIBEX1629_CALL_SIMPLE_RPC(reg_get_cal_out);
  *src = result.type;
  LIBEX1629_FUNCTION_END();
}
