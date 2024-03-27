/******************************************************************************
                   Name :     ex1629.x
                   $Author: jjurack $
                   $Revision: 1.153 $
                   $Date: 2010-03-09 21:38:41 $

 Description : This file contains the RPC definitions

          Copyright 2006 VXI Technology Inc. All rights reserved.
Disclosure, copy, transfer ot use of the information contained
in this document is prohibitted except without a written consent
from VXI Technology Inc.
******************************************************************************/

%/* macros for extracting interface number and "real" version number from
%   RPC version numbers */
%#define EXTRACT_RPC_INTERFACE(v) ((v >> 8) & 0xFFFF)
%#define EXTRACT_RPC_VERSION(v) (v & 0xFF)

%#include "ex1629_errors.h"

%#ifdef _WRS_KERNEL // VxWorks doesn't define the xdr_*int*_t functions
%// We don't get xdr_u_longlong, so we'll make due with xdr_double, as it should be the same size as a long long
%#define xdr_uint64_t xdr_double
%#define xdr_int32_t xdr_int
%#define xdr_uint32_t xdr_u_int
%#define xdr_int16_t xdr_short
%#define xdr_uint16_t xdr_u_short
%#define xdr_int8_t xdr_char
%#define xdr_uint8_t xdr_u_char
%#undef LOCAL // VxWorks has #define LOCAL static in a system header, which collides with one of our enum values
%#endif

struct rpc_result {
	int error_code;
};

struct rpc_interface {
	int iface;
	int versions<>;
};

struct rpc_versions {
	int error_code;
	int lid;
	rpc_interface interfaces<>;
};

const MAX_FIRMWARE_STRING_LENGTH = 64;
struct rpc_firmware_version {
	int error_code;
	int lid;
	string prefix<>;
	int major;
	int minor;
	int build;
};

const MAX_SYSTEM_ERROR_LENGTH = 2048;
struct rpc_error_status {
	int error_code;
	int lid;
	string error_string<MAX_SYSTEM_ERROR_LENGTH>;
};

const EX1629_NUM_CHANNELS = 48;
const EX1629_MAX_SCANLIST_LENGTH = 48;
const EX1629_MAX_DATASET_LENGTH = 16;
const EX1629_MAX_CONFIDENCE_VALUES = 13;
/* number of channels * number of confidence measurements per node */
const EX1629_MAX_CONF_DATASET_LENGTH = 208;
const EX1629_NUM_DATASETS_PER_PAGE = 3;
const EX1629_MAX_FIFO_RESPONSE = 10000;
const EX1629_NUM_DIO_LINES = 16;
const MAX_ETH_ADDR_LEN = 32;
const MAX_SAMPLE_FREQ = 25000;
const MAX_MULTI_BOARD_SAMPLE_FREQ = 10000;

typedef int rpc_linkid;

%#define LID_NONE (-1)

struct rpc_link {
	int error_code;
	int lid;
};

struct rpc_uint32 {
	int error_code;
	int lid;
	uint32_t value;
};

struct rpc_int32 {
	int error_code;
	int lid;
	int32_t value;
};

struct rpc_uint16 {
	int error_code;
	int lid;
	uint16_t value;
};

struct rpc_int16 {
	int error_code;
	int lid;
	int16_t value;
};
struct rpc_uint8 {
	int error_code;
	int lid;
	uint8_t value;
};

struct rpc_int8 {
	int error_code;
	int lid;
	int8_t value;
};

struct rpc_void {
	int error_code;
};

struct rpc_port {
	int error_code;
	int lid;
	uint16_t port;
};

struct rpc_channel {
	int error_code;
	int lid;
	int ch;
};

struct rpc_time {
        int error_code;
	int lid;
	uint32_t sec;
	int32_t nanosec;
};

struct rpc_time_offset {
        int error_code;
	int lid;
        int direction;
	uint32_t sec;
	int32_t nanosec;
};

/* The values for the io_direction enumerated type must match the values
 *   expected by the digital board FPGA for the DIO direction. */
enum io_direction {
	DIR_INPUT = 0,
	DIR_OUTPUT = 1
};

struct rpc_direction {
	int error_code;
	int lid;
	io_direction direction;
};

/* The values for the io_output_type enumerated type must match the values
 *   expected by the digital board FPGA for the output type (pullup). */
enum io_output_type {
	OUTPUT_TYPE_PASSIVE = 0,
	OUTPUT_TYPE_ACTIVE = 1
};

struct rpc_outputtype {
	int error_code;
	int lid;
	io_output_type output_type;
};

struct rpc_lxiconfig {
	int error_code;
	int lid;
	uint8_t direction; /* bitmask: 0 = input, 1= output */
	uint8_t scope;     /* bitmask: 0 = internal only, 1 = internal and external */
};

struct rpc_lxiwiredor {
	int error_code;
	int lid;
	uint8_t enabled; /* bitmask: 0 = disabled, 1 = enabled */
};

struct rpc_ptpinfo {
  int error_code;
  int lid;
  uint32_t master;
  uint32_t synchronized;
};

/* The following enumeration must match the values from dspcommands.h */
enum filter_type {
	IIRFILTER_TYPE_NONE        = 0,
	IIRFILTER_TYPE_BUTTERWORTH = 1,
	IIRFILTER_TYPE_BESSEL      = 2
};

struct rpc_setfilter
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	filter_type type<EX1629_NUM_CHANNELS>;
	double fp<EX1629_NUM_CHANNELS>;
	uint32_t transform<EX1629_NUM_CHANNELS>;
	uint32_t user_order<EX1629_NUM_CHANNELS>;
};

struct rpc_getfilter {
	int error_code;
	int lid;
	filter_type type;
	double fp;
	uint32_t transform;
	uint32_t user_order;
	uint32_t calc_order;
	float overshoot;
	uint32_t risetime;
	float grp_delay;
};

struct rpc_settlingtime {
	int error_code;
	int lid;
	float settling_time;
};

struct rpc_sampfreq {
	int error_code;
	int lid;
	double fs;
};

struct rpc_getcicdecimation {
	int error_code;
	int lid;
	uint32_t r;
	float gain_comp;
};

struct rpc_trigparam
{
	int error_code;
	int lid;
	uint32_t pretrig_sample_count;
	uint32_t sample_count;
	uint32_t trig_delay;
	uint32_t arm_delay;
	uint32_t trig_count;
	uint32_t arm_count;
	uint32_t trig_timer_period;
	uint32_t init_cont;
};

/* The following enumeration is used for both the trigger and arm sources. */
/* It is re-mapped by a static structures in liblocal/trigger.c and */
/*   client/trigger.c */
enum trigger_source {
	TRIG_SRC_IMMEDIATE = 0,
	TRIG_SRC_PATTERN = 1,
	TRIG_SRC_LXI0_POS = 2,
	TRIG_SRC_LXI1_POS = 3,
	TRIG_SRC_LXI2_POS = 4,
	TRIG_SRC_LXI3_POS = 5,
	TRIG_SRC_LXI4_POS = 6,
	TRIG_SRC_LXI5_POS = 7,
	TRIG_SRC_LXI6_POS = 8,
	TRIG_SRC_LXI7_POS = 9,
	TRIG_SRC_LXI0_NEG = 10,
	TRIG_SRC_LXI1_NEG = 11,
	TRIG_SRC_LXI2_NEG = 12,
	TRIG_SRC_LXI3_NEG = 13,
	TRIG_SRC_LXI4_NEG = 14,
	TRIG_SRC_LXI5_NEG = 15,
	TRIG_SRC_LXI6_NEG = 16,
	TRIG_SRC_LXI7_NEG = 17
};

/* The following enumeration must match the TRIGBUS0 - TRIGBUS7 values from
 *   dspcommands.h. */
enum lxi_line {
	LXI0 = 0,
	LXI1 = 1,
	LXI2 = 2,
	LXI3 = 3,
	LXI4 = 4,
	LXI5 = 5,
	LXI6 = 6,
	LXI7 = 7,
	LXI_NONE = 8
};

/* Trigger mask index into trig_lxi_masks, trig_dio_masks, arm_lxi_masks and arm_dio_masks */
const TRIG_MASK_POS_EDGE  = 0;
const TRIG_MASK_NEG_EDGE  = 1;
const TRIG_MASK_POS_LEVEL = 2;
const TRIG_MASK_NEG_LEVEL = 3;
const NUM_TRIG_MASKS      = 4;

struct rpc_trigsrc
{
	int error_code;
	int lid;
	trigger_source trig_src;
	/* The following variables are only used when trig_src = TRIG_SRC_PATTERN */
	uint32_t trig_timer;
	uint32_t trig_lxi_masks[NUM_TRIG_MASKS];
	uint32_t trig_dio_masks[NUM_TRIG_MASKS];
	lxi_line lxi_pattern_output;
	lxi_line lxi_pattern_input;
};

struct rpc_armsrc
{
	int error_code;
	int lid;
	trigger_source arm_src;
	/* The following variables are only used arm trig_src = TRIG_SRC_PATTERN */
	uint32_t arm_timer;
	uint32_t arm_lxi_masks[NUM_TRIG_MASKS];
	uint32_t arm_dio_masks[NUM_TRIG_MASKS];
	lxi_line lxi_pattern_output;
	lxi_line lxi_pattern_input;
};


enum sync_mode {
	SYNC_MODE_MASTER = 0,
	SYNC_MODE_SLAVE = 1
};

struct rpc_syncsrc
{
	int error_code;
	int lid;
	sync_mode mode;
	lxi_line lxi_input;
	lxi_line lxi_output;
};


enum samp_clk_mode {
	SAMP_CLK_MODE_MASTER = 0,
	SAMP_CLK_MODE_SLAVE = 1
};


struct rpc_sampclksrc
{
	int error_code;
	int lid;
	samp_clk_mode mode;
	lxi_line lxi_input;
	lxi_line lxi_output;
};

struct rpc_setexcitationvolt
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float posvalue<EX1629_NUM_CHANNELS>;
	float negvalue<EX1629_NUM_CHANNELS>;
};

struct rpc_setexcitationenbl
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	int posenabled<EX1629_NUM_CHANNELS>;
	int negenabled<EX1629_NUM_CHANNELS>;
};

struct rpc_getexcitation
{
	int error_code;
	int lid;
	float posvalue;
	float negvalue;
	int posenabled;
	int negenabled;
};


struct rpc_setgain
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	int gain<EX1629_NUM_CHANNELS>;
};

struct rpc_getgain {
	int error_code;
	int lid;
	int gain;
};


/* The following enumeration must match the values from dspcommands.h */
enum confsrc {
	CONFSRC_POS_BUF_IN = 0,
	CONFSRC_CMD = 1,
	CONFSRC_NEG_BUF_IN = 2,
	CONFSRC_POS_EXCITEOUT = 3,
	CONFSRC_NEG_EXCITEOUT = 4,
	CONFSRC_NEG_SENSE = 5,
	CONFSRC_POS_SENSE = 6,
	CONFSRC_POS_EXCITECURR = 7,
	CONFSRC_NEG_EXCITECURR = 8,
	CONFSRC_POS_CAL = 9,
	CONFSRC_NEG_CAL = 10,
	CONFSRC_GND = 11,
        CONFSRC_EXCITEOUT_BUFF=12,
	CONFSRC_LEN = 13
};

struct rpc_confscanlist
{
	int lid;
	int error_code;
	confsrc confscanlist<CONFSRC_LEN>;
};

const EX1629_CONFIG_DIGEST_LEN = 16;
struct rpc_configdigest
{
	int lid;
	int error_code;
	uint8_t digest[EX1629_CONFIG_DIGEST_LEN];
};

/* A typical config file is 57KB. */
const EX1629_MAX_CONFIG_FILE_LEN = 1313072;
struct rpc_configfile
{
	int lid;
	int error_code;
	opaque data<EX1629_MAX_CONFIG_FILE_LEN>;
};

enum calsrc {
	CALSRC_0 = 0,
	CALSRC_P_0_07 = 1,  CALSRC_N_0_07 = 2,
	CALSRC_P_0_11 = 3,  CALSRC_N_0_11 = 4,
	CALSRC_P_0_14 = 5,  CALSRC_N_0_14 = 6,
	CALSRC_P_0_7  = 7,  CALSRC_N_0_7  = 8,
	CALSRC_P_1_1  = 9,  CALSRC_N_1_1  = 10,
	CALSRC_P_1_4  = 11, CALSRC_N_1_4  = 12,
	CALSRC_P_7_0  = 13, CALSRC_N_7_0  = 14,
	CALSRC_P_11_0 = 15, CALSRC_N_11_0 = 16,
	CALSRC_P_14_0 = 17, CALSRC_N_14_0 = 18
};
const NUMCALSRC = 19;

struct rpc_regsetcalsrc {
	int lid;
	calsrc type;
};
struct rpc_reggetcalsrc {
	int error_code;
	int lid;
	calsrc type;
};

enum calout {
	CALOUT_OFF = 0,
	CALOUT_ON = 1,
	CALOUT_SHORT = 2,
	CALOUT_VREF = 3
};
struct rpc_regsetcalout {
	int lid;
	calout type;
};
struct rpc_reggetcalout {
	int error_code;
	int lid;
	calout type;
};

enum confgain {
	CONFGAIN_1 = 0,
	CONFGAIN_0_1 = 1,
	CONFGAIN_GND = 2
};
struct rpc_board {
	int error_code;
	int lid;
	int board;
};

struct rpc_dspreg {
	int error_code;
	int lid;
	unsigned int board;
	unsigned int address;
	unsigned int value;
};

struct rpc_scanlist {
	int error_code;
	int lid;
	int channels<EX1629_MAX_SCANLIST_LENGTH>;
};

struct rpc_dataset
{
	int error_code;
	unsigned int timestamp_sec;
	unsigned int timestamp_nsec;
	unsigned int limits;
	float data<EX1629_MAX_DATASET_LENGTH>;
	unsigned int conf_channel_limits;
	unsigned int conf_limits<EX1629_MAX_DATASET_LENGTH>;
	float conf_data<EX1629_MAX_CONF_DATASET_LENGTH>;
};

typedef rpc_dataset* rpc_dataset_p;

struct rpc_diostate
{
	unsigned int dio_data;
	unsigned int timestamp_sec;
	unsigned int timestamp_nsec;
};

struct rpc_datapage
{
	rpc_dataset_p dataset<EX1629_NUM_DATASETS_PER_PAGE>;
	rpc_diostate diostate;
};

struct rpc_fifoarray
{
	int error_code;
	unsigned int fifo_count;
	rpc_datapage datapages<EX1629_MAX_FIFO_RESPONSE>;
};

struct rpc_pagecount {
	int error_code;
	int lid;
	int page_count;
};

struct rpc_lockstatus {
	int error_code;
	int lid;
	int locked;
};

const MAX_SERIAL_NUM_LENGTH = 64;
struct rpc_serial_num {
	int error_code;
	int lid;
	string serial<>;
};

const CAL_CLOSE_CONNECTION = 0xBADD10DE;
struct rpc_calmagic {
	int error_code;
	int lid;
	int magic;
};

struct rpc_calresult {
	int error_code;
	int lid;
	int magic;
	int recommended_uptime;
	int current_uptime;
};

struct rpc_storedselfcal {
	int error_code;
	int lid;
	int has_stored_cal;
};

/*struct rpc_calibrationstatus {
	int error_code;
	int lid;
	int percent_completed;
};*/

struct rpc_calibrationrunning {
	int error_code;
	int lid;
	int cal_running;
};

/*BEGIN CGI CAL STUFF*/

const DESCRIPTION_MAX_LENGTH = 80;
const ERRORSTRING_MAX_LENGTH = 80;
const CALTYPE_MAX_LENGTH = 80;
const DMMADDR_MAX_LENGTH = 80;
const GPIBADDR_MAX_LENGTH = 80;
const CAL_PROMPT_VALUE_MAX_LENGTH = 80; /* same as DESCRIPTION_MAX_LENGTH */

struct rpc_cal_prompt_response {
	int error_code;
	int lid;
	string prompt_value<CAL_PROMPT_VALUE_MAX_LENGTH>;
};

enum cal_status_t {
	CAL_NOTYET                    = -1,
	CAL_OKAY                      = 0,
	CAL_FAIL                      = 1,
	CAL_PENDING                   = 2,
	CAL_ABORT                     = 3,
	CAL_PROMPT                    = 4,
	CAL_PROMPT_VALUE              = 5,
	CAL_PROMPT_VALUE_WITH_CONFIRM = 6,
	CAL_NONFATAL                  = 7,
	CAL_PROMPT_OPT_VALUE_WITH_CONFIRM = 8,
	CAL_SKIP                      = 9,
	CAL_PROMPT_DMM_GET            = 10,
	CAL_PROMPT_BAD_CHANNEL        = 11,
	CAL_UNDEF                     = 999
};

enum cal_type_t {
	CAL_TYPE_NONE = -2,
	CAL_TYPE_NOMINAL = -1,
	CAL_TYPE_FACTORY = 0,
	CAL_TYPE_SELF = 1,
	CAL_TYPE_ZERO = 2,
	CAL_TYPE_SELF_TEST = 101
};

enum cal_simple_status_t {
	CAL_SIMPLE_STATUS_NO_STATUS = 0,
	CAL_SIMPLE_STATUS_RUNNING = 1,
	CAL_SIMPLE_STATUS_SUCCESS = 2,
	CAL_SIMPLE_STATUS_FAILURE = 3,
	CAL_SIMPLE_STATUS_SOME_CHANNELS_FAILED = 4
};

struct rpc_cal_simple_status {
	int error_code;
	int lid;
	cal_simple_status_t status;
};

struct rpc_cal_op {
	int error_code;
	int lid;
	string name<DESCRIPTION_MAX_LENGTH>;
	string error<ERRORSTRING_MAX_LENGTH>;
	cal_status_t status;
};

struct rpc_cal_statuslist {
	int error_code;
	int lid;
	rpc_cal_op ops<>;
};

const CALMETA_BUFSIZE = 80;

struct rpc_cal_date {
	int error_code;
	int lid;
	string when<CALMETA_BUFSIZE>;
};

/*END CGI CAL STUFF*/

/* The following enumeration is re-mapped to the DSP values by a static structure
 *   in liblocal/euconv.c */
enum euconv_type {
	EUCONV_VOLT_OUTPUT = 0,
	EUCONV_QTR_BRIDGE_120 = 1,
	EUCONV_QTR_BRIDGE_350 = 2,
	EUCONV_QTR_BRIDGE_USER = 3,
	EUCONV_HALF_BRIDGE_BEND = 4,
	EUCONV_HALF_BRIDGE_POIS = 5,
	EUCONV_FULL_BRIDGE_BEND = 6,
	EUCONV_FULL_BRIDGE_POIS = 7,
	EUCONV_FULL_BRIDGE_BPOIS = 8,
	EUCONV_RATIOMETRIC = 9,
	EUCONV_LINEAR = 10,
	EUCONV_DUMMY_GAGE = 11
};

struct rpc_setconversion
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	euconv_type type<EX1629_NUM_CHANNELS>;
};

struct rpc_getconversion {
	int error_code;
	int lid;
	euconv_type type;
};

struct rpc_seteuconvexcitationvoltage
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float volt_excite<EX1629_NUM_CHANNELS>;
};

struct rpc_geteuconvexcitationvoltage {
	int error_code;
	int lid;
	float volt_excite;
};

/* The following enumeration must match the values from dspcommands.h */
enum euconv_excitation_volt_src {
	EUCONV_STATIC_EXCITE_VOLT = 0,
	EUCONV_DYNAMIC_EXCITE_VOLT = 1
};

struct rpc_seteuconvexcitationvoltsrc
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
  euconv_excitation_volt_src volt_src<EX1629_NUM_CHANNELS>;
};

struct rpc_geteuconvexcitationvoltsrc {
	int error_code;
	int lid;
	euconv_excitation_volt_src volt_src;
};

/* The volt_unstrained parameter is also used for c of y=mx+c for EUCONV_LINEAR. */
struct rpc_setunstrainedvoltage
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float volt_unstrained<EX1629_NUM_CHANNELS>;
};

struct rpc_getunstrainedvoltage {
	int error_code;
	int lid;
	float volt_unstrained;
};

/* The gage_factor parameter is also used for m of y=mx+c for EUCONV_LINEAR. */
struct rpc_setgagefactor
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float gage_factor<EX1629_NUM_CHANNELS>;
};

struct rpc_getgagefactor {
	int error_code;
	int lid;
	float gage_factor;
};

struct rpc_setpoissonratio
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float poisson_ratio<EX1629_NUM_CHANNELS>;
};

struct rpc_getpoissonratio {
	int error_code;
	int lid;
	float poisson_ratio;
};

struct rpc_settare
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float tare<EX1629_NUM_CHANNELS>;
};

struct rpc_gettare {
	int error_code;
	int lid;
	float tare;
};

/* The following enumeration must match the values from dspcommands.h */
enum euconv_units {
	EUCONV_UNIT_STRAIN = 0,
	EUCONV_UNIT_MICROSTRAIN = 1
};

struct rpc_setconvunits
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	euconv_units units<EX1629_NUM_CHANNELS>;
};

struct rpc_getconvunits {
	int error_code;
	int lid;
	euconv_units units;
};

struct rpc_measureunstrainedvoltage {
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	int num_samples;
	bool set_euconv;
};

enum conf_src {
	BUFFERED_INPUT = 0,
	EXCITATION_CURRENT = 1,
	COMMON_MODE_VOLTAGE = 2
};

struct rpc_measureconfidence {
	int lid;
	conf_src confidence_source;
	int channels<EX1629_NUM_CHANNELS>;
	int num_samples;
};

enum excitation_src {
	LOCAL = 0,
	REMOTE = 1
};

struct rpc_measureexcitationvoltage {
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	int num_samples;
	bool set_euconv;
	excitation_src conf_val_src;
};

struct rpc_measureddata {
	int error_code;
	int lid;
	float data<EX1629_NUM_CHANNELS>;
};

/* The following enumeration must match the values from dspcommands.h */
enum compres {
	COMPRES_FULL = 0,
	COMPRES_350 = 350,
	COMPRES_120 = 120,
	COMPRES_USER = 3,
	COMPRES_OFF = 4
};

struct rpc_setcompres
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	compres res<EX1629_NUM_CHANNELS>;
};

struct rpc_getcompres {
	int error_code;
	int lid;
	compres res;
	float user_value;
	float compres_350_value;
	float compres_120_value;
};

/* The following enumeration must match the values from dspcommands.h */
enum inputmux_bridge_type {
	INPUTMUX_BRIDGE_TYPE_FULL = 0,
	INPUTMUX_BRIDGE_TYPE_HALF = 1,
	INPUTMUX_BRIDGE_TYPE_QUARTER = 2,
	INPUTMUX_BRIDGE_TYPE_CAL = 3,
	INPUTMUX_BRIDGE_TYPE_GND = 4
};

struct rpc_setinputmux
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	inputmux_bridge_type bridge_type<EX1629_NUM_CHANNELS>;
};

struct rpc_getinputmux {
	int error_code;
	int lid;
	uint32_t bridge_type;
};

/* The following enumeration must match the values from dspcommands.h */
/* It is re-mapped by a static structure in client/shunt.c */
enum shunt_source {
	SHUNT_SOURCE_FPS_REMOTE = 0,
	SHUNT_SOURCE_FPS_LOCAL = 1,
	SHUNT_SOURCE_IS_REMOTE = 2,
	SHUNT_SOURCE_IS_LOCAL = 3,
	SHUNT_SOURCE_TEDS = 4
};

struct rpc_setshunt
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	shunt_source src<EX1629_NUM_CHANNELS>;
	float front_panel_val<EX1629_NUM_CHANNELS>;
	float internal_val<EX1629_NUM_CHANNELS>;
	float teds_val<EX1629_NUM_CHANNELS>;
};

struct rpc_getshunt {
	int error_code;
	int lid;
	shunt_source src;
	float front_panel_val;
	float internal_val;
	float teds_val;
};

struct rpc_setshuntenable
{
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	uint32_t enabled<EX1629_NUM_CHANNELS>;
};

struct rpc_getshuntenable {
	int error_code;
	int lid;
	uint32_t enabled;
};

const EX1629_MAX_DSPVERSION_STR_LEN = 32;
struct rpc_getdspversion {
	int error_code;
	int lid;
	string manufstr<EX1629_MAX_DSPVERSION_STR_LEN>;
	string modelstr<EX1629_MAX_DSPVERSION_STR_LEN>;
	string version_prefix<EX1629_MAX_DSPVERSION_STR_LEN>;
	uint32_t version_major;
	uint32_t version_minor;
	uint32_t version_build;
	string date<EX1629_MAX_DSPVERSION_STR_LEN>;
	string time<EX1629_MAX_DSPVERSION_STR_LEN>;
	uint32_t fpga_ver;
	uint32_t board_rev;
};

struct rpc_getbackplaneversion {
	int error_code;
	int lid;
	uint16_t backplane_version;
};

const EX1629_MAX_HWVERSION_STR_LEN = 32;
struct rpc_getdigitalversion {
	int error_code;
	int lid;
	unsigned int digital_version;
	uint32_t cpu_version;
	string cpu_desc<EX1629_MAX_HWVERSION_STR_LEN>;
};

const EX1629_TEDS_ID_LEN = 8;
const EX1629_TEDS_INFO_LEN = 32;
/* The firmware (liblocal/teds.c) automatically calculates a CRC for the
 *   teds_info array and stores it in teds_info[0] when writing data to the
 *   TEDS device.  This overwrites the value for that byte that was sent with
 *   the RPC call. */
struct rpc_tedsdata {
	int error_code;
	int lid;
	uint32_t ch;
	uint8_t teds_id[EX1629_TEDS_ID_LEN];
	uint8_t teds_info[EX1629_TEDS_INFO_LEN];
};

struct rpc_mlan_teds_urn {
	int error_code;
	int lid;
	uint8_t teds_urn[EX1629_TEDS_ID_LEN];
};

struct rpc_mlan_channel {
  int error_code;
  int lid;
  uint32_t ch;
  uint32_t maxlen;
};

/* The maximum amount of data that can be written to or read from a device
 *   via the MLAN interface is limited by the capability of the MLAN repeater.
 *   In our case, this is the DSP.  The value for EX1629_MLAN_DATA_MAX_LEN is
 *   determined by the MAX_INFRAME and MAX_OUTFRAME values in dspcommands.h. */
const EX1629_MLAN_DATA_MAX_LEN = 49;
struct rpc_mlan_data {
	int error_code;
	int lid;
	uint32_t ch;
	uint8_t buffer<EX1629_MLAN_DATA_MAX_LEN>;
};

struct rpc_timestamp {
	int error_code;
	int lid;
        uint32_t board;
	uint32_t sec;
	uint32_t nanosec;
	uint32_t femtosec;
};

struct rpc_conf_filter_wt {
	int error_code;
	int lid;
        uint32_t board;
	float wt;
};

enum streaming_hd_state {
  HD_NULL = 0,
  HD_CONNECT = 1,
  HD_DISCONNECT = 2,
  HD_STOP = 3,
  HD_ERASE = 4,
  HD_RECORD = 5,
  HD_PLAY = 6
};

struct rpc_hd_state {
	int error_code;
	int lid;
        enum streaming_hd_state hd_state;
};

struct rpc_hd_statistics {
	int error_code;
	int lid;
        bool exists;
        uint32_t modified;
        uint64_t bytes;
        int32_t samples;
        uint32_t sec;
        int32_t nanosec;
        uint64_t disk_size;
        uint64_t disk_free;
};

const EX1629_MAX_PROFILE_LEN = 65536;
struct rpc_profresult {
	int lid;
	int error_code;
	string data<EX1629_MAX_PROFILE_LEN>;
};

/* DMM identification members */
const DMM_MAX_LENGTH =255;

struct rpc_dmm_id {
	string dmmname<DMM_MAX_LENGTH>;
	int dmmid;
};

struct rpc_dmm_list {
	rpc_dmm_id alldmms<>;
	int error_code;
};

enum cal_file_type
{
  CAL_FILE_COMBINED = 0,
  CAL_FILE_SELF = 1,
  CAL_FILE_FACTORY = 2,
  CAL_FILE_COMBINED_XML = 3,
  CAL_FILE_FACT_NOMINAL = 4
};

struct rpc_cal_file_type
{
  int lid;
  cal_file_type file;
};

struct rpc_calfile {
  string file<>;
  int file_len;
  int error_code;
};

/* The following enumeration must match the values from dspcommands.h */
/* control of front panel LED's */
enum rpc_lan_led_state {
  LAN_LED_NOSTATE = -1,
  LAN_LED_GREEN_PERSIST = 0,
  LAN_LED_GREEN_FLASHING = 1,
  LAN_LED_RED_PERSIST = 2,
  /* all other values excpet above three are also viewed as
   * hardware controlled
   */
  LAN_LED_HW = 3
};

enum rpc_1588_led_state {
  IEEE_LED_NOSTATE = -1,
  IEEE_LED_OFF = 0,
  IEEE_LED_GREEN_PERSIST = 1,
  IEEE_LED_GREEN_FLASHING_SHORT = 2,
  IEEE_LED_GREEN_FLASHING_LONG = 3,
  IEEE_LED_RED_PERSIST = 4,
  /* all other values excpet above five are also viewed as
   * hardware controlled
   */
  IEEE_LED_HW = 5
};
struct rpc_fp_led_state {
  int lid;
  int error_code;
  rpc_lan_led_state lan;
  rpc_1588_led_state ieee_1588;
};

struct rpc_corevoltreg {
  int error_code;
  int lid;
  uint32_t parm1;
  uint32_t parm2;
  uint32_t parm3;
  uint32_t parm4;
  uint32_t parm5;
};

const DIO_MAX_ACTIONS_PER_EVENT = 8;
const DIO_MAX_INPUT_EVENTS = 16;
const DIO_BANK0_OFFSET = 0;
const DIO_BANK1_OFFSET = 8;

enum DI_Trigger_Type {
        DI_LOW_TO_HIGH = 0,
        DI_HIGH_TO_LOW = 1
};

enum DO_Action_Type {
        DO_LOW = 0,
        DO_HIGH = 1,
        DO_PULSE = 2,
        DO_TOGGLE = 3

};

enum DI_LineNum {
        DI_NONE = -1,
        DI_LINE_0 = 0,
        DI_LINE_1 = 1,
        DI_LINE_2 = 2,
        DI_LINE_3 = 3,
        DI_LINE_4 = 4,
        DI_LINE_5 = 5,
        DI_LINE_6 = 6,
        DI_LINE_7 = 7,
        DI_LINE_MAX = 8
};

enum DO_LineNum {
        DO_NONE = -1,
        DO_LINE_0 = 0,
        DO_LINE_1 = 1,
        DO_LINE_2 = 2,
        DO_LINE_3 = 3,
        DO_LINE_4 = 4,
        DO_LINE_5 = 5,
        DO_LINE_6 = 6,
        DO_LINE_7 = 7,
        DO_LINE_MAX = 8
};

struct rpc_dio_fifo {
	int error_code;
        int lid;
	bool enabled;
};

struct rpc_dio_eventconfig {
        int lid;
        int error_code;
        int inputLine;
        int inputTriggerType;
        int numActions;
        int outputLine[DIO_MAX_ACTIONS_PER_EVENT];
        int outputActionType[DIO_MAX_ACTIONS_PER_EVENT];
};


struct rpc_bridgelimitenabled {
  int error_code;
  int lid;
  bool enabled;
};

struct rpc_setbridgelimit {
  int lid;
  int channels<EX1629_NUM_CHANNELS>;
  float min<EX1629_NUM_CHANNELS>;
  float max<EX1629_NUM_CHANNELS>;
};

struct rpc_getbridgelimit {
  int error_code;
  int lid;
  float min;
  float max;
};

enum conf_limit_reporting_mode {
  CONF_LIMIT_DISABLE_REPORT_MODE = 0,
  CONF_LIMIT_SUMMARY_REPORT_ONLY_MODE = 1,
  CONF_LIMIT_DETAILED_REPORT_MODE = 2
};

struct rpc_conflimitreportingmode {
  int error_code;
  int lid;
  conf_limit_reporting_mode reporting_mode;
};

struct rpc_setconflimit {
  int lid;
  int channels<EX1629_NUM_CHANNELS>;
  int conf_channel;
  float min<EX1629_NUM_CHANNELS>;
  float max<EX1629_NUM_CHANNELS>;
};

struct rpc_getconflimitarg {
  int lid;
  int ch;
  int conf_channel;
};

struct rpc_getconflimitresult {
  int error_code;
  int lid;
  float min;
  float max;
};

struct rpc_measureleadwireresistance {
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	int num_samples;
	bool set_euconv;
};

struct rpc_setleadwireresistance  {
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float  resistance<EX1629_NUM_CHANNELS>;
};

struct rpc_getleadwireresistance {
	int error_code;
	int lid;
	float resistance;
};

struct rpc_sethalfbridgeleadwiredesensitization {
	int lid;
	int channels<EX1629_NUM_CHANNELS>;
	float factor<EX1629_NUM_CHANNELS>;
};

struct rpc_gethalfbridgeleadwiredesensitization {
	int error_code;
	int lid;
	float factor;
};

struct rpc_selfcal_status{
       int error_code;
       int failedchannels<EX1629_NUM_CHANNELS>;
       };

struct rpc_factorycal_status{
       int error_code;
       int failedchannels<EX1629_NUM_CHANNELS>;
       };

struct rpc_badchannel_status{
       int error_code;
       int failedchannels<EX1629_NUM_CHANNELS>;
       };

struct rpc_sensor_LED{
       int lid;
       int channel;
       int LEDOn;
       };

const EX1629_NUM_LXI_LINES = 8;
struct rpc_lxilimitchannelevents {
  uint32_t events[EX1629_NUM_DATASETS_PER_PAGE];
};
struct rpc_lxilimitevents {
        int error_code;
        int lid;
        rpc_lxilimitchannelevents channel_events[EX1629_NUM_LXI_LINES];
};

struct rpc_lxilimitlatches {
        int error_code;
        int lid;
        uint8_t latch;
};

struct rpc_excitecurrsupported {
    int error_code;
    int lid;
    bool supported;
};

program VXITECH_PROG{
	version CORE_VERS{
		/* VERSION REQUEST FUNCTIONS */
		rpc_versions GET_RPC_VERSION( void ) = 0x200;
		rpc_firmware_version GET_FIRMWARE_VERSION( void ) = 0x201;

		/* ERROR STATUS FUNCTIONS */
		rpc_error_status GET_ERROR_STATUS( void ) = 0x300;
	} = 0x00000001;
} = 100416;

program VXITECH_PROG
{
	version EX1629_PROG_VERS
	{
		/* register level interfaces
		 - these are fragile and will be removed at some point */
		rpc_result reg_set_cal_src(rpc_regsetcalsrc) = 0xFFFF0225;
		rpc_reggetcalsrc reg_get_cal_src(rpc_linkid) = 0xFFFF0226;
		rpc_result reg_set_cal_out(rpc_regsetcalout) = 0xFFFF0227;
		rpc_reggetcalout reg_get_cal_out(rpc_linkid) = 0xFFFF0228;

		rpc_dspreg dsp_reg_set( rpc_dspreg ) = 0xFFFF022C;
		rpc_dspreg dsp_reg_get( rpc_dspreg ) = 0xFFFF022D;

		/* reset */
		rpc_result reset(rpc_linkid) = 0x100;

		/* Locking Functions */
		rpc_result lock( rpc_linkid ) = 0x200;
		rpc_result unlock( rpc_linkid ) = 0x201;
		rpc_lockstatus check_lock( rpc_linkid ) = 0x202;
		rpc_result break_lock( rpc_linkid ) = 0x203;

		/* System Status Functions */
		rpc_serial_num get_serial_num( rpc_linkid ) = 0x300;
		rpc_getdspversion get_dspversion( rpc_board ) = 0x302;

		rpc_getbackplaneversion get_backplaneversion( rpc_linkid ) = 0x303;
		rpc_getdigitalversion get_digitalversion( rpc_linkid ) = 0x304;

		/* Link ID Functions */
		rpc_link create_clntlink( rpc_void ) = 0x400;
		rpc_result destroy_clntlink( rpc_link ) = 0x401;

		/* DIO functions */
		rpc_result dio_set_bank_0_direction(rpc_direction) = 0x1001;
		rpc_direction dio_get_bank_0_direction(rpc_linkid) = 0x1002;
		rpc_result dio_set_bank_1_direction(rpc_direction) = 0x1003;
		rpc_direction dio_get_bank_1_direction(rpc_linkid) = 0x1004;
		rpc_result dio_set_bank_0_output_type(rpc_outputtype) = 0x1005;
		rpc_outputtype dio_get_bank_0_output_type(rpc_linkid) = 0x1006;
		rpc_result dio_set_bank_1_output_type(rpc_outputtype) = 0x1007;
		rpc_outputtype dio_get_bank_1_output_type(rpc_linkid) = 0x1008;
		rpc_result dio_set_output(rpc_uint32) = 0x1009;
		rpc_uint32 dio_get_output(rpc_linkid) = 0x100a;
		rpc_uint32 dio_get_input(rpc_linkid) = 0x100b;
		rpc_result dio_send_pulse(rpc_uint32) = 0x100c;
		rpc_result dio_set_output_polarity(rpc_uint32) = 0x100d;
		rpc_uint32 dio_get_output_polarity(rpc_linkid) = 0x100e;
		rpc_result dio_set_input_polarity(rpc_uint32) = 0x100f;
		rpc_uint32 dio_get_input_polarity(rpc_linkid) = 0x1010;
		rpc_result dio_set_config_events(rpc_dio_eventconfig) = 0x1011;
		rpc_dio_eventconfig dio_get_config_events(rpc_dio_eventconfig) = 0x1012;
		rpc_result dio_clear_events(rpc_int16) = 0x1013;
		rpc_result dio_clear_events_all(rpc_linkid) = 0x1014;
                rpc_result dio_set_action_control(rpc_int32) = 0x1015;
                rpc_int32 dio_get_action_control (rpc_linkid) = 0x1016;
    	rpc_result dio_set_fifo(rpc_dio_fifo) = 0x1017;
    	rpc_dio_fifo dio_get_fifo(rpc_linkid) = 0x1018;

		/* LXI functions */
		rpc_result set_lxi_config(rpc_lxiconfig) = 0x1101;
		rpc_lxiconfig get_lxi_config(rpc_linkid) = 0x1102;
		rpc_result set_lxi_output(rpc_uint8) = 0x1103;
		rpc_uint8 get_lxi_output(rpc_linkid) = 0x1104;
		rpc_uint8 get_lxi_input(rpc_linkid) = 0x1105;
		rpc_result send_lxi_pulse(rpc_uint8) = 0x1106;
		rpc_result set_lxi_wiredor(rpc_lxiwiredor) = 0x1107;
		rpc_lxiwiredor get_lxi_wiredor(rpc_linkid) = 0x1108;
		rpc_time get_system_time(rpc_linkid) = 0x1109;
		rpc_ptpinfo get_ptp_info(rpc_linkid) = 0x1110;


		/* Scanlist Functions */
		rpc_result set_scanlist(rpc_scanlist) = 0x2000;
		rpc_scanlist get_scanlist(rpc_linkid) = 0x2001;
		rpc_result allow_bad_channels(rpc_linkid) = 0x2002;

		/* Configuration Functions */
		rpc_configdigest store_current_config(rpc_linkid) = 0x3000;
		rpc_configdigest load_stored_config(rpc_linkid) = 0x3001;
		rpc_result clear_stored_config(rpc_linkid) = 0x3002;
		rpc_configdigest get_current_config_digest(rpc_linkid) = 0x3003;
		rpc_configdigest get_stored_config_digest(rpc_linkid) = 0x3004;
		rpc_configfile get_current_config(rpc_linkid) = 0x3005;
		rpc_configfile get_stored_config(rpc_linkid) = 0x3006;
		rpc_result store_config(rpc_configfile) = 0x3007;

		/* Trigger Functions */
		rpc_result trig_abort(rpc_linkid) = 0x4000;
		rpc_result trig_init(rpc_linkid) = 0x4001;
		rpc_result set_trig_param(rpc_trigparam) = 0x4002;
		rpc_trigparam get_trig_param(rpc_linkid) = 0x4003;
		rpc_result set_trig_src(rpc_trigsrc) = 0x4004;
		rpc_trigsrc get_trig_src(rpc_linkid) = 0x4005;
		rpc_result set_arm_src(rpc_armsrc) = 0x4006;
		rpc_armsrc get_arm_src(rpc_linkid) = 0x4007;
		rpc_result set_sync_src(rpc_syncsrc) = 0x4008;
		rpc_syncsrc get_sync_src(rpc_linkid) = 0x4009;
		rpc_result set_samp_clk_src(rpc_sampclksrc) = 0x400A;
		rpc_sampclksrc get_samp_clk_src(rpc_linkid) = 0x400B;
		rpc_result trig_reset(rpc_linkid) = 0x400C;
		rpc_result soft_trig(rpc_linkid) = 0x400D;
		rpc_result soft_arm(rpc_linkid) = 0x400E;
		rpc_result soft_sync(rpc_linkid) = 0x400F;

		/* Gain Functions */
		rpc_result set_gain(rpc_setgain) = 0x5000;
		rpc_getgain get_gain(rpc_channel) = 0x5001;

		/* Filter Functions */
		rpc_result set_filter(rpc_setfilter) = 0x6000;
		rpc_getfilter get_filter(rpc_channel) = 0x6001;
		rpc_result set_samp_freq(rpc_sampfreq) = 0x6002;
		rpc_sampfreq get_samp_freq(rpc_linkid) = 0x6003;
		rpc_getcicdecimation get_cic_decimation(rpc_linkid) = 0x6004;
		rpc_settlingtime get_settling_time(rpc_channel) = 0x6005;

		/* Excitation Functions */
		rpc_result set_excitation_volt(rpc_setexcitationvolt) = 0x7000;
		rpc_result set_excitation_enbl(rpc_setexcitationenbl) = 0x7001;
		rpc_getexcitation get_excitation(rpc_channel) = 0x7002;

		/* Confidence Data Functions */
		rpc_result set_conf_scanlist(rpc_confscanlist) = 0x8000;
		rpc_confscanlist get_conf_scanlist(rpc_linkid) = 0x8001;
                rpc_excitecurrsupported get_excite_curr_supported(rpc_linkid) = 0x8002;

		/* Limit Checking Functions */
		rpc_result set_conf_limit_reporting_mode(rpc_conflimitreportingmode) = 0x8100;
		rpc_conflimitreportingmode get_conf_limit_reporting_mode(rpc_linkid) = 0x8101;
		rpc_result set_conf_limit(rpc_setconflimit) = 0x8102;
		rpc_getconflimitresult get_conf_limit(rpc_getconflimitarg) = 0x8103;
		rpc_result set_bridge_limit_enabled(rpc_bridgelimitenabled) = 0x8104;
		rpc_bridgelimitenabled get_bridge_limit_enabled(rpc_linkid) = 0x8105;
		rpc_result set_bridge_limit(rpc_setbridgelimit) = 0x8106;
		rpc_getbridgelimit get_bridge_limit(rpc_channel) = 0x8107;

		/* lead wire resistance */
		rpc_measureddata measure_lead_wire_resistance(rpc_measureleadwireresistance) = 0x8200;
		rpc_result  set_lead_wire_resistance (rpc_setleadwireresistance) = 0x8201;
		rpc_getleadwireresistance  get_lead_wire_resistance(rpc_channel) = 0x8202;
		rpc_result  set_half_bridge_lead_wire_desensitization(rpc_sethalfbridgeleadwiredesensitization) = 0x8203;
		rpc_gethalfbridgeleadwiredesensitization get_half_bridge_lead_wire_desensitization (rpc_channel)= 0x8204;


		/* EU Conversion Functions */
		rpc_result set_conversion(rpc_setconversion) = 0x9000;
		rpc_getconversion get_conversion(rpc_channel) = 0x9001;
		rpc_result set_unstrained_voltage(rpc_setunstrainedvoltage) = 0x9002;
		rpc_getunstrainedvoltage get_unstrained_voltage(rpc_channel) = 0x9003;
		rpc_result set_gage_factor(rpc_setgagefactor) = 0x9004;
		rpc_getgagefactor get_gage_factor(rpc_channel) = 0x9005;
		rpc_result set_poisson_ratio(rpc_setpoissonratio) = 0x9006;
		rpc_getpoissonratio get_poisson_ratio(rpc_channel) = 0x9007;
		rpc_result set_tare(rpc_settare) = 0x9008;
		rpc_gettare get_tare(rpc_channel) = 0x9009;
		rpc_result set_conv_units(rpc_setconvunits) = 0x900A;
		rpc_getconvunits get_conv_units(rpc_channel) = 0x900B;
		rpc_measureddata measure_unstrained_voltage(rpc_measureunstrainedvoltage) = 0x900C;
		rpc_measureddata measure_excitation_voltage(rpc_measureexcitationvoltage) = 0x900D;
		rpc_geteuconvexcitationvoltage get_euconv_excitationvoltage(rpc_channel) = 0x900E;
		rpc_result set_euconv_excitationvoltage(rpc_seteuconvexcitationvoltage) = 0x900F;
		rpc_geteuconvexcitationvoltsrc get_euconv_excitationvolt_src(rpc_channel) = 0x9010;
		rpc_result set_euconv_excitationvolt_src(rpc_seteuconvexcitationvoltsrc) = 0x9011;
		rpc_measureddata measure_confidence_values(rpc_measureconfidence)	= 0x9012;

		/* Compensation Resistor Functions */
		rpc_result set_compres(rpc_setcompres) = 0xA000;
		rpc_getcompres get_compres(rpc_channel) = 0xA001;

		/* Input Mux Functions */
		rpc_result set_inputmux(rpc_setinputmux) = 0xA100;
		rpc_getinputmux get_inputmux(rpc_channel) = 0xA101;

		/* Shunt Functions */
		rpc_result set_shunt(rpc_setshunt) = 0xA200;
		rpc_getshunt get_shunt(rpc_channel) = 0xA201;
		rpc_result set_shunt_enable(rpc_setshuntenable) = 0xA202;
		rpc_getshuntenable get_shunt_enable(rpc_channel) = 0xA203;

		/* TEDS Functions */
		rpc_result set_teds_data(rpc_tedsdata) = 0xA300;
		rpc_tedsdata get_teds_data(rpc_channel) = 0xA301;
		rpc_result erase_teds_data(rpc_channel) = 0xA302;

		/* New TEDS Functions for version 0.4.0 */
		rpc_mlan_teds_urn get_mlan_teds_urn (rpc_mlan_channel) = 0xA305;
		rpc_result write_mlan_teds(rpc_mlan_data) = 0xA303;
		rpc_mlan_data read_mlan_teds(rpc_mlan_channel) = 0xA304;

		/* timestamp functions */
		rpc_timestamp get_trigger_timestamp(rpc_uint32) = 0xA400;
		rpc_timestamp get_sync_timestamp(rpc_uint32) = 0xA401;
		rpc_result set_sync_timestamp(rpc_timestamp) = 0xA402;

		/* conf filter functions */
		rpc_conf_filter_wt get_conf_filter_wt(rpc_uint32) = 0xA500;
		rpc_result set_conf_filter_wt(rpc_conf_filter_wt) = 0xA501;

		/* Streaming Functions */
		rpc_result streaming_connect(rpc_port) = 0xB000;
		rpc_result streaming_disconnect(rpc_linkid) = 0xB001;
                rpc_result set_net_decimation(rpc_uint32) = 0xB002;
                rpc_uint32 get_net_decimation(rpc_linkid) = 0xB003;

                rpc_result streaming_hd_connect(rpc_linkid) = 0xB010;
                rpc_result streaming_hd_disconnect(rpc_linkid) = 0xB011;
                rpc_result streaming_hd_stop(rpc_linkid) = 0xB012;
                rpc_result streaming_hd_record(rpc_linkid) = 0xB013;
                rpc_result streaming_hd_erase(rpc_linkid) = 0xB014;
                rpc_result streaming_hd_play(rpc_linkid) = 0xB015;
                rpc_result streaming_hd_seek(rpc_time) = 0xB016;
                rpc_hd_statistics streaming_hd_stat(rpc_linkid) = 0xB017;
                rpc_hd_state streaming_hd_get_state(rpc_linkid) = 0xB018;

                /* Fifo Functions */
		rpc_fifoarray read_fifo( rpc_pagecount ) = 0xB100;
		rpc_result reset_fifo( rpc_linkid ) = 0xB101;

		/* Selfcal Functions */
		rpc_calresult self_calibration_init(rpc_calmagic) = 0xC000;
		rpc_result self_calibration_clear(rpc_linkid) = 0xC001;
		rpc_result self_calibration_clear_stored(rpc_linkid) = 0xC002;
		rpc_result self_calibration_load(rpc_linkid) = 0xC003;
		rpc_result self_calibration_store(rpc_linkid) = 0xC004;
		rpc_storedselfcal self_calibration_is_stored(rpc_linkid) = 0xC005;
		rpc_calresult zero_calibration_init(rpc_calmagic) = 0xC00B;
		rpc_selfcal_status get_selfcal_status(rpc_linkid) = 0xC00F;

                /* Selftest Function */
		rpc_calresult self_test_init(rpc_calmagic) = 0xC00D;
		rpc_cal_simple_status get_self_test_simple_status(rpc_linkid) =  0xC00E;

		/* Factorycal Functions */
		rpc_calresult factory_calibration_init(rpc_calmagic) = 0xC010;
		rpc_factorycal_status get_factorycal_status(rpc_linkid) = 0xC006;

		/* Generic Calibration Functions */
		rpc_calibrationrunning get_calibration_running(rpc_linkid) = 0xC007;
		rpc_cal_statuslist get_calibration_progress(rpc_linkid) = 0xC008;
		rpc_cal_simple_status get_calibration_simple_status(rpc_linkid) =  0xC00C;
		rpc_result send_calibration_prompt_response(rpc_cal_prompt_response) = 0xC009;
		rpc_cal_date get_factory_calibration_date(rpc_linkid) = 0xC000A;
		rpc_calfile get_calibration_file(rpc_cal_file_type) = 0xC000C;
		rpc_badchannel_status get_badchannel_status(rpc_linkid) = 0xC011;

		/*Functions for DMM identification*/
		rpc_dmm_list get_dmm_identification(rpc_linkid) = 0xC000B;

		/* Profiling Interfaces */
		rpc_result set_profiling_enabled( rpc_linkid ) = 0xE000;
		rpc_result set_profiling_disabled( rpc_linkid ) = 0xE001;
		rpc_result reset_profiling( rpc_linkid ) = 0xE002;
		rpc_profresult get_profiling( rpc_linkid ) = 0xE003;

		/* Front panel LED control functions */
		rpc_result set_fp_leds (rpc_fp_led_state) = 0xF000;
		rpc_fp_led_state get_fp_leds (rpc_linkid) = 0xF001;

                /* Sensor LED control */
                rpc_result set_sensor_led_status(rpc_sensor_LED) = 0xF002;

		/* Core Voltage Regulator functions */
		rpc_result set_corevoltreg (rpc_corevoltreg) = 0xF100;
		rpc_corevoltreg get_corevoltreg (rpc_linkid) = 0xF101;

		/* LXI Limit Events */
		rpc_result set_lxi_limit_events (rpc_lxilimitevents) = 0xF200;
		rpc_lxilimitevents get_lxi_limit_events (rpc_linkid) = 0xF201;
		rpc_result set_lxi_limit_latches (rpc_lxilimitlatches) = 0xF202;
		rpc_lxilimitlatches get_lxi_limit_latches (rpc_linkid) = 0xF203;

	} = 0x00000201;
} = 100416;
