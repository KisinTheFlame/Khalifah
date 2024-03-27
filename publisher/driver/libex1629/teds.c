/*******************************************************************************
 *
 * Module Name: teds.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on May 17, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides TEDS communication functionality.
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


ex1629_result_t libex1629_set_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t teds_id[], uint8_t teds_info[])
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_tedsdata);

  rpc_arg.ch = channel;
  memcpy( rpc_arg.teds_id, teds_id, sizeof(rpc_arg.teds_id) );
  memcpy( rpc_arg.teds_info, teds_info, sizeof(rpc_arg.teds_info) );

  LIBEX1629_CALL_RPC(set_teds_data);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_teds_data(struct ex1629_client *cl,
    int32_t channel, uint8_t teds_id[], uint8_t teds_info[])
{
  LIBEX1629_FUNCTION_INIT(rpc_tedsdata, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_teds_data);

  memcpy( teds_id, result.teds_id, sizeof(result.teds_id) );
  memcpy( teds_info, result.teds_info, sizeof(result.teds_info) );

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_erase_teds_data(struct ex1629_client *cl, int32_t channel)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(erase_teds_data);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_cal_block_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t id, uint8_t ver, double res_value, char dmm_info[])
{
  int i;
  ex1629_result_t result;
  uint8_t teds_id[EX1629_TEDS_ID_LEN] = {0};
  union cal_block_teds_info teds_info;

  /* Read the data currently in the device */
  result = libex1629_get_teds_data(cl, channel, teds_id, teds_info.data);
  if (result != EX1629_SUCCESS) {
    return result;
  }

  /* Fill in the information structure with the data */
  teds_info.elements.id = id & 0x0F;
  teds_info.elements.ver = ver & 0x0F;
  teds_info.elements.cal_date = (uint32_t)time(NULL);
  teds_info.elements.res_value = res_value;
  for (i=0; i<CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN; i++)
    teds_info.elements.dmm_info[i] = 0;

  /* Copy the DMM info string */
  strncpy(teds_info.elements.dmm_info, dmm_info, CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN);
  /* Null terminate the DMM info string if it is not already terminated */
  teds_info.elements.dmm_info[CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN-1] = 0;

  /* Write the data back to the device */
  result = libex1629_set_teds_data(cl, channel, teds_id, teds_info.data);
  if (result != EX1629_SUCCESS) {
    return result;
  }

  return EX1629_SUCCESS;
}

ex1629_result_t libex1629_get_cal_block_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t teds_id[], uint8_t *id,
    uint8_t *ver, time_t *cal_date, double *res_value, char dmm_info[])
{
  ex1629_result_t result;
  union cal_block_teds_info teds_info;

  result = libex1629_get_teds_data(cl, channel, teds_id, teds_info.data);
  if (result != EX1629_SUCCESS) {
    return result;
  }


  *id = teds_info.elements.id;
  *ver = teds_info.elements.ver;
  *cal_date = (time_t)teds_info.elements.cal_date;
  *res_value = teds_info.elements.res_value;

  strncpy(dmm_info, teds_info.elements.dmm_info, CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN);
  /* Null terminate the DMM info string if it is not already terminated */
  teds_info.elements.dmm_info[CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN-1] = 0;

  return EX1629_SUCCESS;
}

ex1629_result_t libex1629_get_mlan_teds_urn(struct ex1629_client *cl,
    int32_t channel, int32_t maxlen, uint8_t teds_urn[])
{
  LIBEX1629_FUNCTION_INIT(rpc_mlan_teds_urn, rpc_mlan_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_mlan_teds_urn);

  if( sizeof(result.teds_urn) > maxlen ) {
    LIBEX1629_RETURN(EX1629_ERROR_OUT_OF_MEMORY);
  }

  memcpy( teds_urn, result.teds_urn, sizeof(result.teds_urn) );

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_read_mlan_teds(struct ex1629_client *cl,
    int32_t channel, int32_t maxlen, uint8_t data[])
{
  LIBEX1629_FUNCTION_INIT(rpc_mlan_data, rpc_mlan_channel);

  rpc_arg.ch = channel;
  rpc_arg.maxlen = maxlen;
  LIBEX1629_CALL_RPC(read_mlan_teds);

  if( result.buffer.buffer_len > maxlen ) {
    LIBEX1629_RETURN(EX1629_ERROR_OUT_OF_MEMORY);
  }

  memcpy( data, result.buffer.buffer_val, sizeof(data[0]) * result.buffer.buffer_len );

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_write_mlan_teds(struct ex1629_client *cl,
    int32_t channel, int32_t data_len, uint8_t data[])
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_mlan_data);

  rpc_arg.ch = channel;

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(buffer, data_len);

  memcpy( rpc_arg.buffer.buffer_val, data, data_len );

  LIBEX1629_CALL_RPC(write_mlan_teds);

  LIBEX1629_FUNCTION_END();
}

