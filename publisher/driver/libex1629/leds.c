/*******************************************************************************
 *
 * Module Name: leds.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 2006-01-39 by Eric Diven
 *
 * Module Description:
 *   This module is used to control the front panel LEDS from userland
 *
 ******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <ex1629_errors.h>
#include "libex1629.h"
#include "libex1629_internal.h"


ex1629_result_t libex1629_set_fp_leds(struct ex1629_client *cl, 
                                      enum rpc_lan_led_state lan, enum rpc_1588_led_state ieee_1588)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_fp_led_state);
  
  rpc_arg.lan = lan;
  rpc_arg.ieee_1588 = ieee_1588;
  LIBEX1629_CALL_RPC(set_fp_leds);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_fp_leds(struct ex1629_client *cl, 
                                      enum rpc_lan_led_state *lan, enum rpc_1588_led_state *ieee_1588)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_fp_led_state);
  
  LIBEX1629_CALL_SIMPLE_RPC(get_fp_leds);
  *lan = result.lan;
  *ieee_1588 = result.ieee_1588;
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_sensor_led(struct ex1629_client *cl, 
                                      int channel, bool_t LEDOn)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_sensor_LED);
  
  rpc_arg.channel = channel;
  rpc_arg.LEDOn = LEDOn;
  LIBEX1629_CALL_RPC(set_sensor_led_status);
  
  LIBEX1629_FUNCTION_END();
}
