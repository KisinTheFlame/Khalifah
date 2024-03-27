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

/*******************************************************************************
 * IOCTL Wrapper Function Declarations
 ******************************************************************************/
ex1629_result_t libex1629_dio_reset(void) {
  return EX1629_SUCCESS;
}

ex1629_result_t libex1629_dio_set_bank_0_direction(struct ex1629_client *cl, enum io_direction dir) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_direction);
  rpc_arg.direction = dir;
  LIBEX1629_CALL_RPC(dio_set_bank_0_direction);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_bank_0_direction(struct ex1629_client *cl, enum io_direction *dir) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_direction);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_bank_0_direction);
  *dir = result.direction;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_bank_1_direction(struct ex1629_client *cl, enum io_direction dir) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_direction);
  rpc_arg.direction = dir;
  LIBEX1629_CALL_RPC(dio_set_bank_1_direction);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_bank_1_direction(struct ex1629_client *cl, enum io_direction *dir) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_direction);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_bank_1_direction);
  *dir = result.direction;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_bank_0_output_type(struct ex1629_client *cl, enum io_output_type type) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_outputtype);
  rpc_arg.output_type = type;
  LIBEX1629_CALL_RPC(dio_set_bank_0_output_type);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_bank_0_output_type(struct ex1629_client *cl, enum io_output_type *type) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_outputtype);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_bank_0_output_type);
  *type = result.output_type;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_bank_1_output_type(struct ex1629_client *cl, enum io_output_type type) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_outputtype);
  rpc_arg.output_type = type;
  LIBEX1629_CALL_RPC(dio_set_bank_1_output_type);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_bank_1_output_type(struct ex1629_client *cl, enum io_output_type *type) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_outputtype);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_bank_1_output_type);
  *type = result.output_type;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_output(struct ex1629_client *cl, uint32_t value) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint32);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(dio_set_output);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_output(struct ex1629_client *cl, uint32_t *value) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint32);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_output);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_input(struct ex1629_client *cl, uint32_t *value) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint32);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_input);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_send_pulse(struct ex1629_client *cl, uint32_t value) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint32);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(dio_send_pulse);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_output_polarity(struct ex1629_client *cl, uint32_t value) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint32);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(dio_set_output_polarity);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_output_polarity(struct ex1629_client *cl, uint32_t *value) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint32);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_output_polarity);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_set_input_polarity(struct ex1629_client *cl, uint32_t value) {
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint32);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(dio_set_input_polarity);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_input_polarity(struct ex1629_client *cl, uint32_t *value) {
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint32);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_input_polarity);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_dio_set_config_events (struct ex1629_client *cl, int inputLine, int inputTrigType, int numActions, int *outputLine, int *outputActionType) {
  
  int i; 
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_dio_eventconfig);
  rpc_arg.inputLine = inputLine;
  rpc_arg.inputTriggerType = inputTrigType;
  rpc_arg.numActions = numActions;
  for(i=0;i<numActions;i++)
  {
  rpc_arg.outputLine[i] =  outputLine[i]; 
  rpc_arg.outputActionType[i] = outputActionType[i];
  }
  LIBEX1629_CALL_RPC(dio_set_config_events);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_dio_get_config_events (struct ex1629_client *cl, int inputLine, int inputTrigType, int *numActions, int *outputLine, int *outputActionType) {
  int i; 
  LIBEX1629_FUNCTION_INIT(rpc_dio_eventconfig, rpc_dio_eventconfig);
  rpc_arg.inputLine = inputLine;
  rpc_arg.inputTriggerType = inputTrigType;
  LIBEX1629_CALL_RPC(dio_get_config_events);
  *numActions = result.numActions;
  for (i=0;i<(*numActions); i++)
  {
  outputLine[i] = result.outputLine[i];
  outputActionType[i] = result.outputActionType[i];
  }
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_clear_events (struct ex1629_client *cl, int16_t inputLine){
  LIBEX1629_FUNCTION_INIT(rpc_result,rpc_int16);
  rpc_arg.value = inputLine;
  LIBEX1629_CALL_RPC(dio_clear_events);
  LIBEX1629_FUNCTION_END();
} 

ex1629_result_t libex1629_dio_clear_events_all (struct ex1629_client *cl){
    LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
    LIBEX1629_CALL_SIMPLE_RPC(dio_clear_events_all);
    LIBEX1629_FUNCTION_END();
} 

ex1629_result_t libex1629_dio_set_action_control (struct ex1629_client *cl, int32_t enabled){
    LIBEX1629_FUNCTION_INIT(rpc_result, rpc_int32);
    rpc_arg.value = enabled;
    LIBEX1629_CALL_RPC(dio_set_action_control);
    LIBEX1629_FUNCTION_END();
} 

ex1629_result_t libex1629_dio_get_action_control (struct ex1629_client *cl, int32_t *enabled){
    LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_int32);
    LIBEX1629_CALL_SIMPLE_RPC(dio_get_action_control);
    *enabled = result.value;
    LIBEX1629_FUNCTION_END(); 
}

ex1629_result_t libex1629_dio_set_fifo(struct ex1629_client *cl, int enabled)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_dio_fifo);
  rpc_arg.enabled = enabled;
  LIBEX1629_CALL_RPC(dio_set_fifo);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_dio_get_fifo(struct ex1629_client *cl, int* enabled)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_dio_fifo);
  LIBEX1629_CALL_SIMPLE_RPC(dio_get_fifo);
  *enabled = result.enabled;
  LIBEX1629_FUNCTION_END();
}
