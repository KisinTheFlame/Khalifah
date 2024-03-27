/*******************************************************************************
 *             File Name: leadwire.c
 *             $Author: lawrencej $
 *             $Revision: 1.1 $
 *             $Date: 2006-07-12 00:39:08 $
 *
 *   Description: This module provides the wrapper functions for
 *   the leadwire, for the rpc client
 *
 *   Copyright 2006 VXI Technology Inc. as an unpublished work.
 *   All rights reserved.  The information contained herein is 
 *   confidential property of VXI Technology, Inc.  The use, copying,
 *   transfer, or disclosure of such information is prohibited except
 *   by express written agreement with VXI Technology, Inc.
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
 * Function name: libex1629_measure_lead_wire_resistance 
 *   Returns      error code
 * Created by:    Lawrence Jacob
 * Description:   Measures the Lead wire resistance for the quarter bridge configuration  
 * Notes:          N/A
  ******************************************************************************/
ex1629_result_t libex1629_measure_lead_wire_resistance(struct ex1629_client *cl,
				       int32_t numchannels, int32_t channels[],
           int32_t num_samples, bool_t set_euconv, 
                                       float resistance[])
{
    int i;

     LIBEX1629_FUNCTION_INIT(rpc_measureddata, rpc_measureleadwireresistance);

     /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
     LIBEX1629_CREATE_ARRAY(channels, numchannels);
     
    for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
        rpc_arg.channels.channels_val[i] = channels[i];
     }
     
     rpc_arg.num_samples = num_samples;
     rpc_arg.set_euconv = set_euconv;

     LIBEX1629_CALL_RPC(measure_lead_wire_resistance);     

    for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
          resistance[i] = result.data.data_val[i];
    }

    LIBEX1629_FUNCTION_END();
    
}

  /*******************************************************************************
  * Function name: libex1629_set_lead_wire_resistance 
  *   Returns      error code
  * Created by:    Lawrence Jacob
  * Description:   Sets the Lead wire resistance for the quarter bridge configuration  
  * Notes:         N/A
  ******************************************************************************/
  ex1629_result_t libex1629_set_lead_wire_resistance (struct ex1629_client *cl,
            int32_t numchannels, int32_t channels[],  float  resistance[])
{
     int i;

     LIBEX1629_FUNCTION_INIT(rpc_result, rpc_setleadwireresistance);

     /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
     LIBEX1629_CREATE_ARRAY(channels, numchannels);
     LIBEX1629_CREATE_ARRAY(resistance, numchannels);

     for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
          rpc_arg.channels.channels_val[i] = channels[i];
          rpc_arg.resistance.resistance_val[i] = resistance[i];
     }
     
     LIBEX1629_CALL_RPC(set_lead_wire_resistance);

     LIBEX1629_FUNCTION_END();
}
 /*******************************************************************************
  * Function name: libex1629_get_lead_wire_resistance 
  *   Returns      error code
  * Created by:    Lawrence Jacob
  * Description:   gets the Lead wire resistance for the quarter bridge configuration  
  * Notes:         N/A
    ******************************************************************************/
  ex1629_result_t libex1629_get_lead_wire_resistance (struct ex1629_client *cl,
            int32_t channel, float  *resistance)
{
     LIBEX1629_FUNCTION_INIT(rpc_getleadwireresistance, rpc_channel);
     rpc_arg.ch = channel;
     LIBEX1629_CALL_RPC(get_lead_wire_resistance);
     *resistance = result.resistance;
     LIBEX1629_FUNCTION_END(); 
}

 /*******************************************************************************
  * Function name: libex1629_set_half_bridge_lead_wire_desensitization  
  *   Returns      error code
  * Created by:    Lawrence Jacob
  * Description:  Sets the lead_wie desensitation for the half bridge configuration
  * Notes:         N/A
  ******************************************************************************/
ex1629_result_t libex1629_set_half_bridge_lead_wire_desensitization (struct ex1629_client *cl,
          int32_t numchannels, int32_t channels[], float  factor[])
{
     int i;

     LIBEX1629_FUNCTION_INIT(rpc_result, rpc_sethalfbridgeleadwiredesensitization);

     /* Create the necessary arrays, memory is freed by the FUNCTION_END macro. */
     LIBEX1629_CREATE_ARRAY(channels, numchannels);
     LIBEX1629_CREATE_ARRAY(factor, numchannels);

     for( i = 0; i < rpc_arg.channels.channels_len; i++ ){
          rpc_arg.channels.channels_val[i] = channels[i];
          rpc_arg.factor.factor_val[i] = factor[i];
     }
     
     LIBEX1629_CALL_RPC(set_half_bridge_lead_wire_desensitization);

     LIBEX1629_FUNCTION_END();
}
 /*******************************************************************************
  * Function name: libex1629_get_half_bridge_lead_wire_desensitization 
  *   Returns      error code
  * Created by:    Lawrence Jacob
  * Description:   gets the lead_wie desensitation factor for the half bridge configuration 
  * Notes:         N/A
 ******************************************************************************/
ex1629_result_t libex1629_get_half_bridge_lead_wire_desensitization (struct ex1629_client *cl,
          int32_t channel, float   *factor)
{
     LIBEX1629_FUNCTION_INIT(rpc_gethalfbridgeleadwiredesensitization, rpc_channel);
     rpc_arg.ch = channel;
     LIBEX1629_CALL_RPC(get_half_bridge_lead_wire_desensitization);
     *factor = result.factor;
     LIBEX1629_FUNCTION_END(); 
}
  

