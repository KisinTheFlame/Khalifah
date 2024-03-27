/*******************************************************************************
 *
 * Module Name: libex1629.h
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
 *   This module is a thin wrapper around the EX1629 RPCs.
 *
 ******************************************************************************/

#ifndef _LIBEX1629_HDR
#define _LIBEX1629_HDR

/*******************************************************************************
 * Includes
 ******************************************************************************/
#ifndef _WRS_KERNEL // VxWorks doesn't have this header
#include <inttypes.h>
#endif
#include <ex1629_errors.h>
#include "ex1629.h"


/*******************************************************************************
 * Macro name:    DECLARE_FUNCTION and DECLARE_VOID_FUNCTION
 *   fnname       Name of the function to be declared.
 *   type         Data type of the argument (not present in the case of void
 *                functions).
 * Created by:    Gary Bernhardt
 * Description:   These macros declare the prototypes for libex1629 functions.
 * Notes:         The only difference between the void and non-void versions
 *                is that functions generated using the void version take no
 *                arguments.
 ******************************************************************************/
#define DECLARE_FUNCTION(fnname, type) \
  ex1629_result_t libex1629_##fnname(type *value);
#define DECLARE_VOID_FUNCTION(fnname) \
  ex1629_result_t libex1629_##fname(void);


/*******************************************************************************
 * ex1629_client Struct
 ******************************************************************************/
typedef struct ex1629_client {
  CLIENT *rpc_cl;
  int lid;
  int manual_lid; /* was the lid passed in manually? */
  const char *host;
} EX1629_CLIENT;


/*******************************************************************************
 * General libex1629 Functions
 ******************************************************************************/
EX1629_CLIENT *ex1629_clnt_create( const char *host, int lid );
void ex1629_clnt_destroy( EX1629_CLIENT *cl );
EX1629_CLIENT *core_clnt_create( const char *host );
void core_clnt_destroy( EX1629_CLIENT *cl );


/*******************************************************************************
 * Version Functions
 ******************************************************************************/
ex1629_result_t libex1629_get_firmware_version(struct ex1629_client *cl, char *prefix,
                                               int *major, int *minor, int *build);
ex1629_result_t libex1629_get_dspversion(struct ex1629_client *cl, int board, char *manufstr,
	char *modelstr, char *version_prefix, uint32_t *version_major, uint32_t *version_minor,
	uint32_t *version_build, char *date, char *time, uint32_t *fpga_ver, uint32_t *board_rev);
ex1629_result_t libex1629_get_backplaneversion(struct ex1629_client *cl, uint16_t *backplane_version);
ex1629_result_t libex1629_get_digitalversion(struct ex1629_client *cl, unsigned int *digital_version, uint32_t *cpu_version, char *cpu_desc);

/*******************************************************************************
 * DIO Functions
 ******************************************************************************/
ex1629_result_t libex1629_dio_reset(void);
ex1629_result_t libex1629_dio_set_bank_0_direction(struct ex1629_client *cl, const enum io_direction dir);
ex1629_result_t libex1629_dio_get_bank_0_direction(struct ex1629_client *cl, enum io_direction *dir);
ex1629_result_t libex1629_dio_set_bank_1_direction(struct ex1629_client *cl, const enum io_direction dir);
ex1629_result_t libex1629_dio_get_bank_1_direction(struct ex1629_client *cl, enum io_direction *dir);
ex1629_result_t libex1629_dio_set_bank_0_output_type(struct ex1629_client *cl, const enum io_output_type type);
ex1629_result_t libex1629_dio_get_bank_0_output_type(struct ex1629_client *cl, enum io_output_type *type);
ex1629_result_t libex1629_dio_set_bank_1_output_type(struct ex1629_client *cl, const enum io_output_type type);
ex1629_result_t libex1629_dio_get_bank_1_output_type(struct ex1629_client *cl, enum io_output_type *type);
ex1629_result_t libex1629_dio_set_output          (struct ex1629_client *cl, const uint32_t value);
ex1629_result_t libex1629_dio_get_output          (struct ex1629_client *cl, uint32_t *value);
ex1629_result_t libex1629_dio_get_input           (struct ex1629_client *cl, uint32_t *value);
ex1629_result_t libex1629_dio_send_pulse          (struct ex1629_client *cl, const uint32_t value);
ex1629_result_t libex1629_dio_set_output_polarity (struct ex1629_client *cl, const uint32_t value);
ex1629_result_t libex1629_dio_get_output_polarity (struct ex1629_client *cl, uint32_t *value);
ex1629_result_t libex1629_dio_set_input_polarity  (struct ex1629_client *cl, const uint32_t value);
ex1629_result_t libex1629_dio_get_input_polarity  (struct ex1629_client *cl, uint32_t *value);

ex1629_result_t libex1629_dio_set_config_events	(struct ex1629_client *cl, int inputLine, int inputTrigType, int numActions, int *outLine, int *outputActionTyp);
ex1629_result_t libex1629_dio_get_config_events (struct ex1629_client *cl, int inputLine, int inputTrigType,int *numActions, int *outLine, int *outputActionTyp);
ex1629_result_t libex1629_dio_clear_events (struct ex1629_client *cl, int16_t inputLine);
ex1629_result_t libex1629_dio_clear_events_all (struct ex1629_client *cl);
ex1629_result_t libex1629_dio_set_action_control (struct ex1629_client *cl, int32_t enabled);
ex1629_result_t libex1629_dio_get_action_control (struct ex1629_client *cl, int32_t *enabled);

/*******************************************************************************
 * Register Interface Functions
 ******************************************************************************/
ex1629_result_t libex1629_reg_set_reg(struct ex1629_client *cl,
				      uint32_t board, uint32_t address, uint32_t value);
ex1629_result_t libex1629_reg_get_reg(struct ex1629_client *cl,
				      uint32_t board, uint32_t address, uint32_t *value);
ex1629_result_t libex1629_reg_set_cal_src           (struct ex1629_client *cl, enum calsrc src);
ex1629_result_t libex1629_reg_get_cal_src           (struct ex1629_client *cl, enum calsrc *src);

ex1629_result_t libex1629_reg_set_cal_out           (struct ex1629_client *cl, enum calout src);
ex1629_result_t libex1629_reg_get_cal_out           (struct ex1629_client *cl, enum calout *src);

/*******************************************************************************
 * Scanlist Functions
 ******************************************************************************/
ex1629_result_t libex1629_allow_bad_channels(struct ex1629_client *cl);
ex1629_result_t libex1629_set_scanlist(struct ex1629_client *cl,
				       int32_t numchannels, int32_t channels[]);
ex1629_result_t libex1629_get_scanlist(struct ex1629_client *cl,
				       int32_t *numchannels, int32_t channels[]);

/*******************************************************************************
 * Device Configuration Functions
 ******************************************************************************/
ex1629_result_t libex1629_store_current_config(struct ex1629_client *cl, uint8_t digest[]);
ex1629_result_t libex1629_load_stored_config(struct ex1629_client *cl, uint8_t digest[]);
ex1629_result_t libex1629_clear_stored_config(struct ex1629_client *cl);
ex1629_result_t libex1629_get_current_config_digest(struct ex1629_client *cl, uint8_t digest[]);
ex1629_result_t libex1629_get_stored_config_digest(struct ex1629_client *cl, uint8_t digest[]);
ex1629_result_t libex1629_get_current_config(struct ex1629_client *cl, rpc_configfile *configfile);
ex1629_result_t libex1629_get_stored_config(struct ex1629_client *cl, rpc_configfile *configfile);
ex1629_result_t libex1629_free_config_data(rpc_configfile *configfile);
ex1629_result_t libex1629_store_config(struct ex1629_client *cl, uint8_t *data, uint32_t data_len);

/*******************************************************************************
 * Trigger Functions
 ******************************************************************************/
ex1629_result_t libex1629_triginit(struct ex1629_client *cl);
ex1629_result_t libex1629_trigabort(struct ex1629_client *cl);

ex1629_result_t libex1629_trig_reset(struct ex1629_client *cl);
ex1629_result_t libex1629_soft_trig(struct ex1629_client *cl);
ex1629_result_t libex1629_soft_arm(struct ex1629_client *cl);
ex1629_result_t libex1629_soft_sync(struct ex1629_client *cl);

ex1629_result_t libex1629_set_lxi_config(struct ex1629_client *cl,
    uint8_t direction, uint8_t scope);
ex1629_result_t libex1629_get_lxi_config(struct ex1629_client *cl,
    uint8_t *direction, uint8_t *scope);
ex1629_result_t libex1629_set_lxi_wiredor(struct ex1629_client *cl,
    uint8_t enabled);
ex1629_result_t libex1629_get_lxi_wiredor(struct ex1629_client *cl,
    uint8_t *enabled);
ex1629_result_t libex1629_set_lxi_output(struct ex1629_client *cl, uint8_t value);
ex1629_result_t libex1629_get_lxi_output(struct ex1629_client *cl, uint8_t *value);
ex1629_result_t libex1629_get_lxi_input(struct ex1629_client *cl, uint8_t *value);
ex1629_result_t libex1629_send_lxi_pulse(struct ex1629_client *cl, uint8_t value);
ex1629_result_t libex1629_get_system_time(struct ex1629_client *cl,
    uint32_t *seconds, int32_t *nanoseconds);
ex1629_result_t libex1629_get_ptp_info(struct ex1629_client *cl,
    uint32_t *master, uint32_t *synchronized);

ex1629_result_t libex1629_set_trigger_param(struct ex1629_client *cl,
    uint32_t pretrig_sample_count, uint32_t sample_count, uint32_t trig_delay,
    uint32_t arm_delay, uint32_t trig_count, uint32_t arm_count,
    uint32_t trig_timer_period, uint32_t init_cont);
ex1629_result_t libex1629_set_trigger_src(struct ex1629_client *cl,
    uint32_t trig_src, uint32_t trig_timer,
    uint32_t trig_lxi_masks[4], uint32_t trig_dio_masks[4],
    uint32_t lxi_pattern_output, uint32_t lxi_pattern_input);
ex1629_result_t libex1629_set_arm_src(struct ex1629_client *cl,
    uint32_t arm_src, uint32_t arm_timer,
    uint32_t arm_lxi_masks[4], uint32_t arm_dio_masks[4],
    uint32_t lxi_pattern_output, uint32_t lxi_pattern_input);
ex1629_result_t libex1629_set_sync_src(struct ex1629_client *cl,
    enum sync_mode mode, enum lxi_line lxi_input, enum lxi_line lxi_output);
ex1629_result_t libex1629_set_samp_clk_src(struct ex1629_client *cl,
    enum samp_clk_mode mode, enum lxi_line lxi_input, enum lxi_line lxi_output);

ex1629_result_t libex1629_get_trigger_param(struct ex1629_client *cl,
    uint32_t *pretrig_sample_count, uint32_t *sample_count, uint32_t *trig_delay,
    uint32_t *arm_delay, uint32_t *trig_count, uint32_t *arm_count,
    uint32_t *trig_timer_period, uint32_t *init_cont);
ex1629_result_t libex1629_get_trigger_src(struct ex1629_client *cl,
    uint32_t *trig_src, uint32_t *trig_timer,
    uint32_t trig_lxi_masks[4], uint32_t trig_dio_masks[4],
    uint32_t *lxi_pattern_output, uint32_t *lxi_pattern_input);
ex1629_result_t libex1629_get_arm_src(struct ex1629_client *cl,
    uint32_t *arm_src, uint32_t *arm_timer,
    uint32_t arm_lxi_masks[4], uint32_t arm_dio_masks[4],
    uint32_t *lxi_pattern_output, uint32_t *lxi_pattern_input);
ex1629_result_t libex1629_get_sync_src(struct ex1629_client *cl,
    enum sync_mode *mode, enum lxi_line *lxi_input, enum lxi_line *lxi_output);
ex1629_result_t libex1629_get_samp_clk_src(struct ex1629_client *cl,
    enum samp_clk_mode *mode, enum lxi_line *lxi_input, enum lxi_line *lxi_output);

/*******************************************************************************
 * Gain Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_gain(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], int gain);
ex1629_result_t libex1629_get_gain(struct ex1629_client *cl, int32_t channel, int *gain);

/*******************************************************************************
 * Filter Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_filter(struct ex1629_client *cl, 
    int32_t numchannels, int32_t channels[], int type, double fp,
    int32_t transform, uint32_t user_order);
ex1629_result_t libex1629_get_filter(struct ex1629_client *cl,
    int32_t channel, int *type, double *fp, uint32_t *transform, uint32_t *user_order,
    uint32_t *calc_order, float *overshoot, uint32_t *risetime, float *grp_delay);
ex1629_result_t libex1629_get_settling_time(struct ex1629_client *cl,
    int32_t channel, float *settling_time);
ex1629_result_t libex1629_set_samp_freq(struct ex1629_client *cl, double fs);
ex1629_result_t libex1629_get_samp_freq(struct ex1629_client *cl, double *fs);
ex1629_result_t libex1629_get_cic_decimation(struct ex1629_client *cl,
    uint32_t *r, float *gain_comp);

/*******************************************************************************
 * Excitation Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_excitation_volt(struct ex1629_client *cl,
                                             int32_t numchannels, int32_t channels[],
                                             float posvalue, float negvalue);
ex1629_result_t libex1629_set_excitation_enbl(struct ex1629_client *cl,
                                             int32_t numchannels, int32_t channels[],
                                             int posenabled, int negenabled);
ex1629_result_t libex1629_get_excitation(struct ex1629_client *cl, int32_t channel,
                                         float *posvalue, float *negvalue,
                                         int *posenabled, int *negenabled);


/*******************************************************************************
 * Confidence Scanlist Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_conf_scanlist(struct ex1629_client *cl,
                                            int32_t numsources, int32_t sources[]);
ex1629_result_t libex1629_get_conf_scanlist(struct ex1629_client *cl,
                                            int32_t *numsources, int32_t sources[]);
ex1629_result_t libex1629_get_conf_filter_wt(struct ex1629_client *cl,
  uint32_t *board, float *wt);
ex1629_result_t libex1629_set_conf_filter_wt(struct ex1629_client *cl,
  uint32_t board, float wt);
ex1629_result_t libex1629_get_excite_curr_supported(struct ex1629_client *cl, 
                                                        int* supported);

/*******************************************************************************
 * Lead wire compensation Functions
 ******************************************************************************/
ex1629_result_t libex1629_measure_lead_wire_resistance(struct ex1629_client *cl,
          int32_t numchannels, int32_t channels[], int32_t num_samples, bool_t set_euconv, float resistance[]);
ex1629_result_t libex1629_set_lead_wire_resistance (struct ex1629_client *cl,
            int32_t numchannels, int32_t channels[], float  resistance[]);
ex1629_result_t libex1629_get_lead_wire_resistance (struct ex1629_client *cl,
          int32_t channel, float  *resistance);
ex1629_result_t libex1629_set_half_bridge_lead_wire_desensitization (struct ex1629_client *cl,
          int32_t num_channels, int32_t channels[], float   factor[]);
ex1629_result_t libex1629_get_half_bridge_lead_wire_desensitization (struct ex1629_client *cl,
          int32_t channel, float   *factor);

/*******************************************************************************
 * Limit Checking Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_conf_limit_reporting_mode(struct ex1629_client *cl,
        conf_limit_reporting_mode mode);
ex1629_result_t libex1629_get_conf_limit_reporting_mode(struct ex1629_client *cl,
        conf_limit_reporting_mode *mode);
ex1629_result_t libex1629_set_conf_limit(struct ex1629_client *cl,
        int32_t num_channels, int32_t channels[], int32_t conf_channel,
        double min[], double max[]);
ex1629_result_t libex1629_get_conf_limit(struct ex1629_client *cl,
        int32_t channels, int32_t conf_channel, double *min, double *max);

ex1629_result_t libex1629_set_bridge_limit_enabled(struct ex1629_client *cl,
        int enabled);
ex1629_result_t libex1629_get_bridge_limit_enabled(struct ex1629_client *cl,
        int *enabled);
ex1629_result_t libex1629_set_bridge_limit(struct ex1629_client *cl,
        int32_t num_channels, int32_t channels[], double min[], double max[]);
ex1629_result_t libex1629_get_bridge_limit(struct ex1629_client *cl,
        int32_t channel, double *min, double *max);

ex1629_result_t libex1629_set_lxi_limit_events(struct ex1629_client *cl,
        int32_t lxi_ch, uint32_t a, uint32_t b, uint32_t c);
ex1629_result_t libex1629_get_lxi_limit_events(struct ex1629_client *cl,
        int32_t lxi_ch, uint32_t *a, uint32_t *b, uint32_t *c);
ex1629_result_t libex1629_set_lxi_limit_latches(struct ex1629_client *cl, uint8_t value);
ex1629_result_t libex1629_get_lxi_limit_latches(struct ex1629_client *cl, uint8_t *value);


/*******************************************************************************
 * Timestamp Functions
 ******************************************************************************/
ex1629_result_t libex1629_get_trigger_timestamp(struct ex1629_client *cl,
        uint32_t *board, uint32_t *sec, uint32_t *nanosec, uint32_t *femtosec);
ex1629_result_t libex1629_get_sync_timestamp(struct ex1629_client *cl,
        uint32_t *board, uint32_t *sec, uint32_t *nanosec, uint32_t *femtosec);
ex1629_result_t libex1629_set_sync_timestamp(struct ex1629_client *cl,
        uint32_t board, uint32_t sec, uint32_t nanosec, uint32_t femtosec);


/*******************************************************************************
 * Self-test Functions
 ******************************************************************************/

ex1629_result_t libex1629_self_test_init(struct ex1629_client *cl, int *magic);
ex1629_result_t libex1629_self_test_query_simple (struct ex1629_client * cl,
       cal_simple_status_t *status);

/*******************************************************************************
 * Self-Calibration Functions 
 ******************************************************************************/

ex1629_result_t libex1629_self_calibration_init(struct ex1629_client *cl, 
    int *magic, int *recommended_uptime, int *current_uptime);
ex1629_result_t libex1629_zero_calibration_init(struct ex1629_client *cl, 
    int *magic, int *recommended_uptime, int *current_uptime);

ex1629_result_t libex1629_cal_query_simple (struct ex1629_client * cl,
       cal_simple_status_t *status);

ex1629_result_t libex1629_is_cal_running (struct ex1629_client *cl, int *is_running);
ex1629_result_t libex1629_self_calibration_clear(struct ex1629_client *cl);
ex1629_result_t libex1629_self_calibration_clear_stored(struct ex1629_client *cl);
ex1629_result_t libex1629_self_calibration_load(struct ex1629_client *cl);
ex1629_result_t libex1629_self_calibration_store(struct ex1629_client *cl);
ex1629_result_t libex1629_self_calibration_is_stored(struct ex1629_client *cl,
    int *has_stored_cal);
ex1629_result_t libex1629_calfile_get(struct ex1629_client *cl,enum cal_file_type cal, char** file);
ex1629_result_t libex1629_get_self_calibration_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[]);

/*******************************************************************************
 * Self-Calibration Functions 
 ******************************************************************************/
ex1629_result_t libex1629_zero_calibration_init(struct ex1629_client *cl, 
    int *magic, int *recommended_uptime, int *current_uptime);
/*******************************************************************************
 * CGI Calibration Functions and structures
 ******************************************************************************/

#define STATUSSTRING_MAX_LENGTH 20

typedef struct {
  char desc[DESCRIPTION_MAX_LENGTH];
  char error[ERRORSTRING_MAX_LENGTH];
  int statuscode;
} libex1629_cal_op_status_t;

typedef struct {
  libex1629_cal_op_status_t *list;
  int numops;
} libex1629_cal_statuslist_t;

typedef struct {
  char dmmname[DMM_MAX_LENGTH];
  int dmmid;
} libex1629_dmm_name;

ex1629_result_t libex1629_send_cal_prompt_response(struct ex1629_client * cl,
						   char * prompt_value);
ex1629_result_t libex1629_cal_query(struct ex1629_client *cl,
				    libex1629_cal_statuslist_t **status);
ex1629_result_t libex1629_cal_free(libex1629_cal_statuslist_t **status);
ex1629_result_t libex1629_factory_calibration_init(struct ex1629_client *cl,
        int *magic, int *recommended_uptime, int *current_uptime);
ex1629_result_t libex1629_selfcal_start(struct ex1629_client *cl, int *magic);
ex1629_result_t libex1629_get_factory_cal_date (struct ex1629_client *cl,
        char datestring[], int datestring_len);
ex1629_result_t libex1629_dmm_get(struct ex1629_client *cl, libex1629_dmm_name** list,int* size);
ex1629_result_t libex1629_get_factory_calibration_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[]);
ex1629_result_t libex1629_get_bad_channel_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[]);

/*******************************************************************************
 * EU Conversion Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_conversion(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], uint32_t type);
ex1629_result_t libex1629_get_conversion(struct ex1629_client *cl,
    int32_t channel, uint32_t *type);
ex1629_result_t libex1629_set_unstrained_voltage(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float volt_unstrained);
ex1629_result_t libex1629_get_unstrained_voltage(struct ex1629_client *cl,
    int32_t channel, float *volt_unstrained);
ex1629_result_t libex1629_set_gage_factor(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float gage_factor);
ex1629_result_t libex1629_get_gage_factor(struct ex1629_client *cl,
    int32_t channel, float *gage_factor);
ex1629_result_t libex1629_set_poisson_ratio(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float poisson_ratio);
ex1629_result_t libex1629_get_poisson_ratio(struct ex1629_client *cl,
    int32_t channel, float *poisson_ratio);
ex1629_result_t libex1629_set_tare(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], float tare);
ex1629_result_t libex1629_get_tare(struct ex1629_client *cl,
    int32_t channel, float *tare);
ex1629_result_t libex1629_set_conv_units(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], enum euconv_units units);
ex1629_result_t libex1629_get_conv_units(struct ex1629_client *cl,
    int32_t channel, enum euconv_units *units);
ex1629_result_t libex1629_measure_unstrained_voltage(struct ex1629_client *cl,
    int32_t num_samples, int32_t numchannels, int32_t channels[], float data[],
    int set_euconv);
ex1629_result_t libex1629_measure_excitation_voltage(struct ex1629_client *cl,
    int32_t num_samples, int32_t numchannels, int32_t channels[], float data[],
    int source, int set_euconv);
ex1629_result_t libex1629_get_euconv_excitation_voltage(struct ex1629_client *cl,
        int channel, float *volt_excite);
ex1629_result_t libex1629_set_euconv_excitation_voltage(struct ex1629_client *cl,
        int32_t numchannels, int32_t channels[], float volt_excite); 
ex1629_result_t libex1629_get_euconv_excitation_volt_src(struct ex1629_client *cl,
        int channel, int32_t *volt_src);
ex1629_result_t libex1629_set_euconv_excitation_volt_src(struct ex1629_client *cl,
        int32_t numchannels, int32_t channels[], int32_t volt_src); 

/*******************************************************************************
 * Confidence value testing functions
 ******************************************************************************/
ex1629_result_t libex1629_measure_confidence(struct ex1629_client *cl,
    int32_t confValue, int32_t numChannels, int32_t channels[], int32_t sampleCount,
    float returnedValues[]); 
 
/*******************************************************************************
 * Compensation Resistor Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_compres(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], enum compres res);
ex1629_result_t libex1629_get_compres(struct ex1629_client *cl, int32_t channel,
    enum compres *res, float *user_value, float *compres_350_value,
    float *compres_120_value);

/*******************************************************************************
 * Input Mux Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_inputmux(struct ex1629_client *cl, int32_t numchannels,
    int32_t channels[], enum inputmux_bridge_type bridge_type);
ex1629_result_t libex1629_get_inputmux(struct ex1629_client *cl, int32_t channel,
    enum inputmux_bridge_type *bridge_type);

/*******************************************************************************
 * Shunt Resistor Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_shunt(struct ex1629_client *cl, 
    int32_t numchannels, int32_t channels[], enum shunt_source src,
    float front_panel_val, float internal_val, float teds_val);
ex1629_result_t libex1629_get_shunt(struct ex1629_client *cl, int32_t channel,
    enum shunt_source *src, float *front_panel_val, float *internal_val, float *teds_val);
ex1629_result_t libex1629_set_shunt_enable(struct ex1629_client *cl,
    int32_t numchannels, int32_t channels[], uint32_t enabled);
ex1629_result_t libex1629_get_shunt_enable(struct ex1629_client *cl,
    int32_t channel, uint32_t *enabled);

/*******************************************************************************
 * TEDS Functions
 ******************************************************************************/
#define CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN (EX1629_TEDS_INFO_LEN - 16)

struct cal_block_teds_data_elements {
  uint8_t  checksum;
  uint8_t  id  : 4;
  uint8_t  ver : 4;
  uint16_t dummy_variable;
  uint32_t cal_date;
  double   res_value;
  char     dmm_info[CAL_BLOCK_TEDS_DATA_DMM_INFO_LEN];
};

union  cal_block_teds_info {
  uint8_t data[EX1629_TEDS_INFO_LEN];
  struct cal_block_teds_data_elements elements;
};

ex1629_result_t libex1629_set_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t teds_id[], uint8_t teds_info[]);
ex1629_result_t libex1629_get_teds_data(struct ex1629_client *cl,
    int32_t channel, uint8_t teds_id[], uint8_t teds_info[]);
ex1629_result_t libex1629_erase_teds_data(struct ex1629_client *cl, int32_t channel);
ex1629_result_t libex1629_set_cal_block_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t id, uint8_t ver, double res_value, char dmm_info[]);
ex1629_result_t libex1629_get_cal_block_teds_data(struct ex1629_client *cl, 
    int32_t channel, uint8_t teds_id[], uint8_t *id,
    uint8_t *ver, time_t *cal_date, double *res_value, char dmm_info[]);

ex1629_result_t libex1629_get_mlan_teds_urn(struct ex1629_client *cl, 
    int32_t channel, int32_t maxlen, uint8_t teds_urn[]);
ex1629_result_t libex1629_read_mlan_teds(struct ex1629_client *cl, 
    int32_t channel, int32_t maxlen, uint8_t data[]);
ex1629_result_t libex1629_write_mlan_teds(struct ex1629_client *cl, 
    int32_t channel, int32_t data_len, uint8_t data[]);

/*******************************************************************************
 * Streaming Functions
 ******************************************************************************/
ex1629_result_t libex1629_streaming_connect(struct ex1629_client *cl, uint16_t port);
ex1629_result_t libex1629_streaming_disconnect(struct ex1629_client *cl);
ex1629_result_t libex1629_set_net_decimation(struct ex1629_client *cl, uint32_t dec);
ex1629_result_t libex1629_get_net_decimation(struct ex1629_client *cl, uint32_t *dec);

ex1629_result_t libex1629_streaming_hd_connect(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_disconnect(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_stop(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_record(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_erase(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_play(struct ex1629_client *cl);
ex1629_result_t libex1629_streaming_hd_seek(struct ex1629_client *cl,
                                            unsigned sec, unsigned nanosec);
ex1629_result_t libex1629_streaming_hd_stat(struct ex1629_client *cl,
                                            int *exists, time_t *modified,
                                            uint64_t *bytes, int32_t *samples,
                                            uint32_t *sec, int32_t *nanosec,
                                            uint64_t *disk_size, uint64_t *disk_free);
ex1629_result_t libex1629_streaming_hd_get_state(struct ex1629_client *cl,
                                            enum streaming_hd_state *hd_state);


/*******************************************************************************
 * Locking Functions
 ******************************************************************************/
ex1629_result_t libex1629_lock(struct ex1629_client *cl);
ex1629_result_t libex1629_unlock(struct ex1629_client *cl);
ex1629_result_t libex1629_break_lock(struct ex1629_client *cl);
ex1629_result_t libex1629_check_lock(struct ex1629_client *cl, int *locked, int *lid);

/*******************************************************************************
 * System Status Functions
 ******************************************************************************/
ex1629_result_t libex1629_get_serial_num(struct ex1629_client *cl, char *serial);

/*******************************************************************************
 * FIFO Functions
 ******************************************************************************/
ex1629_result_t libex1629_readfifo(struct ex1629_client *cl,
				   int num_pages, int *fifo_count, 
				   rpc_fifoarray *fifoarray);
ex1629_result_t libex1629_free_fifoarray(rpc_fifoarray *fifoarray);
ex1629_result_t  libex1629_resetfifo(struct ex1629_client *cl);
const char *build_eu_float_format (void);
ex1629_result_t libex1629_dio_set_fifo(struct ex1629_client *cl, int enabled);
ex1629_result_t libex1629_dio_get_fifo(struct ex1629_client *cl, int* enabled);

/*******************************************************************************
 * Reset Functions
 ******************************************************************************/
ex1629_result_t libex1629_exreset(struct ex1629_client *cl);

/*******************************************************************************
 * Profiling Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_profiling_enabled(struct ex1629_client *cl);
ex1629_result_t libex1629_set_profiling_disabled(struct ex1629_client *cl);
ex1629_result_t libex1629_reset_profiling(struct ex1629_client *cl);
ex1629_result_t libex1629_get_profiling(struct ex1629_client *cl, rpc_profresult *profdata);
ex1629_result_t libex1629_free_profiling_data(rpc_profresult *profdata);

/*******************************************************************************
 * Front Panel LED Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_fp_leds(struct ex1629_client *cl, enum rpc_lan_led_state lan, 
                                      enum rpc_1588_led_state ieee_1588);
ex1629_result_t libex1629_get_fp_leds(struct ex1629_client *cl, enum rpc_lan_led_state *lan, 
                                      enum rpc_1588_led_state *ieee_1588);

/*******************************************************************************
 * SENSOR LED Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_sensor_led(struct ex1629_client *cl, int channel, bool_t LEDOn);
/*******************************************************************************
 * Core Voltage Regulator Functions
 ******************************************************************************/
ex1629_result_t libex1629_set_corevoltreg(struct ex1629_client *cl,
                                          uint32_t parm1, uint32_t parm2,
                                          uint32_t parm3, uint32_t parm4,
                                          uint32_t parm5);
ex1629_result_t libex1629_get_corevoltreg(struct ex1629_client *cl,
                                          uint32_t *parm1, uint32_t *parm2,
                                          uint32_t *parm3, uint32_t *parm4,
                                          uint32_t *parm5);

#endif //_LIBEX1629_HDR
