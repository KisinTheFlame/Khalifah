/*******************************************************************************
 *
 * Module Name: euconv.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on March 18, 2005 by Joe Miller
 *
 * Module Description:
 *   This wrapper provides analog board EU conversion control.
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


ex1629_result_t libex1629_set_conversion(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], uint32_t type)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setconversion);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(type, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.type.type_val[i] = type;
  }

  LIBEX1629_CALL_RPC(set_conversion);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_conversion(struct ex1629_client *cl,
    int32_t channel, uint32_t *type)
{
  LIBEX1629_FUNCTION_INIT(rpc_getconversion, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_conversion);

  *type = result.type;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_unstrained_voltage(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float volt_unstrained)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setunstrainedvoltage);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(volt_unstrained, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.volt_unstrained.volt_unstrained_val[i] = volt_unstrained;
  }

  LIBEX1629_CALL_RPC(set_unstrained_voltage);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_unstrained_voltage(struct ex1629_client *cl,
    int32_t channel, float *volt_unstrained)
{
  LIBEX1629_FUNCTION_INIT(rpc_getunstrainedvoltage, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_unstrained_voltage);

  *volt_unstrained = result.volt_unstrained;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_gage_factor(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float gage_factor)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setgagefactor);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(gage_factor, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.gage_factor.gage_factor_val[i] = gage_factor;
  }

  LIBEX1629_CALL_RPC(set_gage_factor);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_gage_factor(struct ex1629_client *cl,
    int32_t channel, float *gage_factor)
{
  LIBEX1629_FUNCTION_INIT(rpc_getgagefactor, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_gage_factor);

  *gage_factor = result.gage_factor;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_poisson_ratio(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float poisson_ratio)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setpoissonratio);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(poisson_ratio, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.poisson_ratio.poisson_ratio_val[i] = poisson_ratio;
  }

  LIBEX1629_CALL_RPC(set_poisson_ratio);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_poisson_ratio(struct ex1629_client *cl,
    int32_t channel, float *poisson_ratio)
{
  LIBEX1629_FUNCTION_INIT(rpc_getpoissonratio, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_poisson_ratio);

  *poisson_ratio = result.poisson_ratio;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_tare(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float tare)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_settare);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(tare, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.tare.tare_val[i] = tare;
  }

  LIBEX1629_CALL_RPC(set_tare);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_tare(struct ex1629_client *cl,
    int32_t channel, float *tare)
{
  LIBEX1629_FUNCTION_INIT(rpc_gettare, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_tare);

  *tare = result.tare;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_conv_units(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], enum euconv_units units)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setconvunits);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(units, numchannels);

  for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.units.units_val[i] = units;
  }

  LIBEX1629_CALL_RPC(set_conv_units);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_conv_units(struct ex1629_client *cl,
    int32_t channel, enum euconv_units *units)
{
  LIBEX1629_FUNCTION_INIT(rpc_getconvunits, rpc_channel);

  rpc_arg.ch = channel;
  LIBEX1629_CALL_RPC(get_conv_units);

  *units = result.units;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_measure_unstrained_voltage(struct ex1629_client *cl,
    int32_t num_samples, int32_t numchannels, int32_t channels[], float data[],
    int set_euconv)
{
  int i;
  
  LIBEX1629_FUNCTION_INIT(rpc_measureddata, rpc_measureunstrainedvoltage);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);

  for (i = 0; i < rpc_arg.channels.channels_len; i++)
    rpc_arg.channels.channels_val[i] = channels[i];
  rpc_arg.num_samples = num_samples;
  rpc_arg.set_euconv = set_euconv;

  LIBEX1629_CALL_RPC(measure_unstrained_voltage);

  for (i = 0; i < result.data.data_len; i++)
    data[i] = result.data.data_val[i];
  /* If less data than the number of channels is returned, clear the rest */
  for ( ; i < rpc_arg.channels.channels_len; i++)
    data[i] = 0;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_measure_excitation_voltage(struct ex1629_client *cl,
    int32_t num_samples, int32_t numchannels, int32_t channels[], float data[], 
    int source, int set_euconv)
{
  int i;

  LIBEX1629_FUNCTION_INIT(rpc_measureddata, rpc_measureexcitationvoltage);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);

  for (i = 0; i < rpc_arg.channels.channels_len; i++) {
    rpc_arg.channels.channels_val[i] = channels[i];
  }
  rpc_arg.num_samples = num_samples;
  rpc_arg.conf_val_src = source;
  rpc_arg.set_euconv = set_euconv;

  LIBEX1629_CALL_RPC(measure_excitation_voltage);

  for (i = 0; i < result.data.data_len; i++) {
    data[i] = result.data.data_val[i];
  }
  
  /* If less data than twice the number of channels is returned, 
   * clear the rest */
  for ( ; i < rpc_arg.channels.channels_len; i++) {
    data[i] = 0;
  }

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_euconv_excitation_voltage(struct ex1629_client *cl, 
    int channel, float *volt_excite)
{
  LIBEX1629_FUNCTION_INIT(rpc_geteuconvexcitationvoltage, rpc_channel);

  rpc_arg.ch = channel;

  LIBEX1629_CALL_RPC(get_euconv_excitationvoltage);

  *volt_excite = result.volt_excite;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_euconv_excitation_voltage(struct ex1629_client *cl,
        int32_t numchannels, int32_t channels[], float volt_excite)
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_seteuconvexcitationvoltage);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(volt_excite, numchannels);

  for(i = 0; i < rpc_arg.channels.channels_len; i++) {
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.volt_excite.volt_excite_val[i] = volt_excite;
  }

  LIBEX1629_CALL_RPC(set_euconv_excitationvoltage);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_euconv_excitation_volt_src(struct ex1629_client *cl, 
    int channel, int32_t *volt_src)
{
  LIBEX1629_FUNCTION_INIT(rpc_geteuconvexcitationvoltsrc, rpc_channel);

  rpc_arg.ch = channel;

  LIBEX1629_CALL_RPC(get_euconv_excitationvolt_src);

  *volt_src = result.volt_src;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_euconv_excitation_volt_src(struct ex1629_client *cl,
        int32_t numchannels, int32_t channels[], int32_t volt_src)
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_seteuconvexcitationvoltsrc);

  /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
  LIBEX1629_CREATE_ARRAY(channels, numchannels);
  LIBEX1629_CREATE_ARRAY(volt_src, numchannels);

  for(i = 0; i < rpc_arg.channels.channels_len; i++) {
    rpc_arg.channels.channels_val[i] = channels[i];
    rpc_arg.volt_src.volt_src_val[i] = volt_src;
  }

  LIBEX1629_CALL_RPC(set_euconv_excitationvolt_src);
  LIBEX1629_FUNCTION_END();
}

