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
 * First written on October 12, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides device configuration control.
 *
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "libex1629.h"
#include "libex1629_internal.h"


ex1629_result_t libex1629_store_current_config(struct ex1629_client *cl, uint8_t digest[])
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configdigest);

  LIBEX1629_CALL_SIMPLE_RPC(store_current_config);
  memcpy(digest, result.digest, sizeof(result.digest));
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_load_stored_config(struct ex1629_client *cl, uint8_t digest[])
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configdigest);

  LIBEX1629_CALL_SIMPLE_RPC(load_stored_config);
  memcpy(digest, result.digest, sizeof(result.digest));
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_clear_stored_config(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(clear_stored_config);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_current_config_digest(struct ex1629_client *cl, uint8_t digest[])
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configdigest);

  LIBEX1629_CALL_SIMPLE_RPC(get_current_config_digest);
  memcpy(digest, result.digest, sizeof(result.digest));
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_stored_config_digest(struct ex1629_client *cl, uint8_t digest[])
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configdigest);

  LIBEX1629_CALL_SIMPLE_RPC(get_stored_config_digest);
  memcpy(digest, result.digest, sizeof(result.digest));
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_current_config(struct ex1629_client *cl, rpc_configfile *configfile)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configfile);

  LIBEX1629_CALL_SIMPLE_RPC(get_current_config);
  memcpy(configfile, &result, sizeof(rpc_configfile));
  /* The client is responsible to call libex1629_free_config_data after it has
   *   processed the data. */
  LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE();
}


ex1629_result_t libex1629_get_stored_config(struct ex1629_client *cl, rpc_configfile *configfile)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_configfile);

  LIBEX1629_CALL_SIMPLE_RPC(get_stored_config);
  memcpy(configfile, &result, sizeof(rpc_configfile));
  /* The client is responsible to call libex1629_free_config_data after it has
   *   processed the data. */
  LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE();
}


ex1629_result_t libex1629_free_config_data(rpc_configfile *configfile)
{
  if(configfile != NULL)
    LIBEX1629_XDR_FREE(rpc_configfile, configfile);
  return EX1629_SUCCESS;
}


ex1629_result_t libex1629_store_config(struct ex1629_client *cl, uint8_t *data, uint32_t data_len)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_configfile);

  rpc_arg.data.data_val = (char *) data;
  rpc_arg.data.data_len = data_len;
  LIBEX1629_CALL_RPC(store_config);
  LIBEX1629_FUNCTION_END();
}
