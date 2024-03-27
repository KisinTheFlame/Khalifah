/*******************************************************************************
 *
 * Module Name: trigger.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 19 January 2005 by Nick Barendt
 *
 * Module Description:
 *   This wrapper provides trigger control.
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


ex1629_result_t libex1629_triginit(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(trig_init);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_trigabort(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);

  LIBEX1629_CALL_SIMPLE_RPC(trig_abort);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_trig_reset(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(trig_reset);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_soft_trig(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(soft_trig);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_soft_arm(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(soft_arm);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_soft_sync(struct ex1629_client *cl)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_result);
  LIBEX1629_CALL_SIMPLE_RPC(soft_sync);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_lxi_config(struct ex1629_client *cl,
    uint8_t direction, uint8_t scope)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_lxiconfig);
  rpc_arg.direction = direction;
  rpc_arg.scope = scope;
  LIBEX1629_CALL_RPC(set_lxi_config);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_lxi_config(struct ex1629_client *cl,
    uint8_t *direction, uint8_t *scope)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_lxiconfig);
  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_config);
  *direction = result.direction;
  *scope = result.scope;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_lxi_wiredor(struct ex1629_client *cl,
    uint8_t enabled)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_lxiwiredor);
  rpc_arg.enabled = enabled;
  LIBEX1629_CALL_RPC(set_lxi_wiredor);
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_lxi_wiredor(struct ex1629_client *cl,
    uint8_t *enabled)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_lxiwiredor);
  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_wiredor);
  *enabled = result.enabled;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_system_time(struct ex1629_client *cl,
    uint32_t *seconds, int32_t *nanoseconds)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_time);
  LIBEX1629_CALL_SIMPLE_RPC(get_system_time);
  *seconds = result.sec;
  *nanoseconds = result.nanosec;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_ptp_info(struct ex1629_client *cl,
    uint32_t *master, uint32_t *synchronized)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_ptpinfo);
  LIBEX1629_CALL_SIMPLE_RPC(get_ptp_info);
  *master = result.master;
  *synchronized = result.synchronized;
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_set_lxi_output(struct ex1629_client *cl, uint8_t value)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint8);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(set_lxi_output);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_lxi_output(struct ex1629_client *cl, uint8_t *value)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint8);
  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_output);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_lxi_input(struct ex1629_client *cl, uint8_t *value)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_uint8);
  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_input);
  *value = result.value;
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_send_lxi_pulse(struct ex1629_client *cl, uint8_t value)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_uint8);
  rpc_arg.value = value;
  LIBEX1629_CALL_RPC(send_lxi_pulse);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_trigger_param(struct ex1629_client *cl,
    uint32_t pretrig_sample_count, uint32_t sample_count, uint32_t trig_delay,
    uint32_t arm_delay, uint32_t trig_count, uint32_t arm_count,
    uint32_t trig_timer_period, uint32_t init_cont)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_trigparam);

  rpc_arg.pretrig_sample_count = pretrig_sample_count;
  rpc_arg.sample_count = sample_count;
  rpc_arg.trig_delay = trig_delay;
  rpc_arg.arm_delay = arm_delay;
  rpc_arg.trig_count = trig_count;
  rpc_arg.arm_count = arm_count;
  rpc_arg.trig_timer_period = trig_timer_period;
  rpc_arg.init_cont = init_cont;

  LIBEX1629_CALL_RPC(set_trig_param);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_trigger_src(struct ex1629_client *cl,
    uint32_t trig_src, uint32_t trig_timer,
    uint32_t trig_lxi_masks[4], uint32_t trig_dio_masks[4],
    uint32_t lxi_pattern_output, uint32_t lxi_pattern_input)
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_trigsrc);

  rpc_arg.trig_src = trig_src;
  rpc_arg.trig_timer = trig_timer;
  
  for( i=0; i<NUM_TRIG_MASKS; i++ ) {
    rpc_arg.trig_lxi_masks[i] = trig_lxi_masks[i];
    rpc_arg.trig_dio_masks[i] = trig_dio_masks[i];
  }
  rpc_arg.lxi_pattern_output = lxi_pattern_output;
  rpc_arg.lxi_pattern_input = lxi_pattern_input;

  LIBEX1629_CALL_RPC(set_trig_src);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_arm_src(struct ex1629_client *cl,
    uint32_t arm_src, uint32_t arm_timer,
    uint32_t arm_lxi_masks[4], uint32_t arm_dio_masks[4],
    uint32_t lxi_pattern_output, uint32_t lxi_pattern_input)
{
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_armsrc);

  rpc_arg.arm_src = arm_src;
  rpc_arg.arm_timer = arm_timer;
  
  for( i=0; i<NUM_TRIG_MASKS; i++ ) {
    rpc_arg.arm_lxi_masks[i]  = arm_lxi_masks[i];
    rpc_arg.arm_dio_masks[i]  = arm_dio_masks[i];
  }
  rpc_arg.lxi_pattern_output = lxi_pattern_output;
  rpc_arg.lxi_pattern_input = lxi_pattern_input;

  LIBEX1629_CALL_RPC(set_arm_src);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_sync_src(struct ex1629_client *cl,
    enum sync_mode mode, enum lxi_line lxi_input, enum lxi_line lxi_output)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_syncsrc);

  rpc_arg.mode = mode;
  rpc_arg.lxi_input = lxi_input;
  rpc_arg.lxi_output = lxi_output;

  LIBEX1629_CALL_RPC(set_sync_src);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_samp_clk_src(struct ex1629_client *cl,
    enum samp_clk_mode mode, enum lxi_line lxi_input, enum lxi_line lxi_output)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_sampclksrc);

  rpc_arg.mode = mode;
  rpc_arg.lxi_input = lxi_input;
  rpc_arg.lxi_output = lxi_output;

  LIBEX1629_CALL_RPC(set_samp_clk_src);

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_trigger_param(struct ex1629_client *cl,
    uint32_t *pretrig_sample_count, uint32_t *sample_count, uint32_t *trig_delay,
    uint32_t *arm_delay, uint32_t *trig_count, uint32_t *arm_count,
    uint32_t *trig_timer_period, uint32_t *init_cont)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_trigparam);

  LIBEX1629_CALL_SIMPLE_RPC(get_trig_param);

  *pretrig_sample_count = result.pretrig_sample_count;
  *sample_count = result.sample_count;
  *trig_delay = result.trig_delay;
  *arm_delay = result.arm_delay;
  *trig_count = result.trig_count;
  *arm_count = result.arm_count;
  *trig_timer_period = result.trig_timer_period;
  *init_cont = result.init_cont;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_trigger_src(struct ex1629_client *cl,
    uint32_t *trig_src, uint32_t *trig_timer,
    uint32_t trig_lxi_masks[4], uint32_t trig_dio_masks[4],
    uint32_t *lxi_pattern_output, uint32_t *lxi_pattern_input)
{
  int i;

  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_trigsrc);

  LIBEX1629_CALL_SIMPLE_RPC(get_trig_src);

  *trig_src = result.trig_src;
  *trig_timer = result.trig_timer;

  for( i=0; i<NUM_TRIG_MASKS; i++ ) {
    trig_lxi_masks[i] = result.trig_lxi_masks[i];
    trig_dio_masks[i] = result.trig_dio_masks[i];
  }
  *lxi_pattern_output = result.lxi_pattern_output;
  *lxi_pattern_input = result.lxi_pattern_input;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_arm_src(struct ex1629_client *cl,
    uint32_t *arm_src, uint32_t *arm_timer,
    uint32_t arm_lxi_masks[4], uint32_t arm_dio_masks[4],
    uint32_t *lxi_pattern_output, uint32_t *lxi_pattern_input)
{
  int i;

  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_armsrc);

  LIBEX1629_CALL_SIMPLE_RPC(get_arm_src);

  *arm_src = result.arm_src;
  *arm_timer = result.arm_timer;
  
  for( i=0; i<NUM_TRIG_MASKS; i++ ) {
    arm_lxi_masks[i]  = result.arm_lxi_masks[i];
    arm_dio_masks[i]  = result.arm_dio_masks[i];
  }
  *lxi_pattern_output = result.lxi_pattern_output;
  *lxi_pattern_input = result.lxi_pattern_input;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_sync_src(struct ex1629_client *cl,
    enum sync_mode *mode, enum lxi_line *lxi_input, enum lxi_line *lxi_output)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_syncsrc);

  LIBEX1629_CALL_SIMPLE_RPC(get_sync_src);

  *mode = result.mode;
  *lxi_input = result.lxi_input;
  *lxi_output = result.lxi_output;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_samp_clk_src(struct ex1629_client *cl,
    enum samp_clk_mode *mode, enum lxi_line *lxi_input, enum lxi_line *lxi_output)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_sampclksrc);

  LIBEX1629_CALL_SIMPLE_RPC(get_samp_clk_src);

  *mode = result.mode;
  *lxi_input = result.lxi_input;
  *lxi_output = result.lxi_output;

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_lxi_limit_events(struct ex1629_client *cl,
        int32_t lxi_ch, uint32_t a, uint32_t b, uint32_t c)
{
  ex1629_result_t e = EX1629_SUCCESS;
  int i;
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_lxilimitevents);

  for (i = 0; i < 8 && e == EX1629_SUCCESS; i++) {
    e = libex1629_get_lxi_limit_events(cl, i,
            &rpc_arg.channel_events[i].events[0],
            &rpc_arg.channel_events[i].events[1],
            &rpc_arg.channel_events[i].events[2]);
  }

  if (e == EX1629_SUCCESS) {
    rpc_arg.channel_events[lxi_ch].events[0] = a;
    rpc_arg.channel_events[lxi_ch].events[1] = b;
    rpc_arg.channel_events[lxi_ch].events[2] = c;

    LIBEX1629_CALL_RPC(set_lxi_limit_events);
  }

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_lxi_limit_events(struct ex1629_client *cl,
        int32_t lxi_ch, uint32_t *a, uint32_t *b, uint32_t *c)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_lxilimitevents);

  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_limit_events);

  *a = result.channel_events[lxi_ch].events[0];
  *b = result.channel_events[lxi_ch].events[1];
  *c = result.channel_events[lxi_ch].events[2];

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_set_lxi_limit_latches(struct ex1629_client *cl, uint8_t value)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_lxilimitlatches);
  rpc_arg.latch = value;
  LIBEX1629_CALL_RPC(set_lxi_limit_latches);
  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_get_lxi_limit_latches(struct ex1629_client *cl, uint8_t *value)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_lxilimitlatches);
  LIBEX1629_CALL_SIMPLE_RPC(get_lxi_limit_latches);
  *value = result.latch;
  LIBEX1629_FUNCTION_END();
}
