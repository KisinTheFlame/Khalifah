/*******************************************************************************
 *
 * Module Name: excitation.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on March 11, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides analog board excitation control.
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


ex1629_result_t libex1629_set_excitation_volt(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float posvalue, float negvalue)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setexcitationvolt);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(posvalue, numchannels);
  LIBEX1629_CREATE_ARRAY(negvalue, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.posvalue.posvalue_val[i] = posvalue;
    rpc_arg.negvalue.negvalue_val[i] = negvalue;
  }

  LIBEX1629_CALL_RPC(set_excitation_volt);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_excitation_enbl(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], int posenabled, int negenabled)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setexcitationenbl);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(posenabled, numchannels);
  LIBEX1629_CREATE_ARRAY(negenabled, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.posenabled.posenabled_val[i] = posenabled;
    rpc_arg.negenabled.negenabled_val[i] = negenabled;
  }

  LIBEX1629_CALL_RPC(set_excitation_enbl);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_excitation(struct ex1629_client *cl, int32_t channel,
                                         float *posvalue, float *negvalue,
                                         int *posenabled, int *negenabled)
{
  LIBEX1629_FUNCTION_INIT(rpc_getexcitation, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_excitation);

  *posvalue = result.posvalue;
  *negvalue = result.negvalue;
  *posenabled = result.posenabled;
  *negenabled = result.negenabled;

  LIBEX1629_FUNCTION_END();
}
