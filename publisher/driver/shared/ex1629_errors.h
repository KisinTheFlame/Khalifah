/*******************************************************************************
 *
 * Module Name: ex1629_errors.h
 *             $Author: jjurack $
 *             $Revision: 1.65 $
 *             $Date: 2010-03-09 21:38:41 $
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 4 October 2004 by Gary Bernhardt
 *
 * Module Description:
 *   This module provides shared error facilities, such as enumerations,
 *   mappings from error codes to strings, and debugging print statements.
 *
 ******************************************************************************/


/*******************************************************************************
 * Protection against circular includes
 ******************************************************************************/
#ifndef __EX1629_ERRORS_H
#define __EX1629_ERRORS_H

#ifndef WINDOWS  //the "WINDOWS" #define is for building calxml on the windows end
                 //since it knows nothing about syslog
#ifdef _WRS_KERNEL
#define EX1629_TEE_ERROR(fmt, args...) \
  { printf(fmt, ##args); }
#else
#include <syslog.h>

#define EX1629_TEE_ERROR(fmt, args...) \
{ fprintf (stderr, fmt, ##args); \
  syslog (LOG_ERR, fmt, ##args); }
#endif
#endif

/*******************************************************************************
 * EX1629 error code enumeration
 ******************************************************************************/
typedef enum {
  EX1629_SUCCESS                                   = 0,

  /* VXI11 errors */
  VXI11_ERROR_NO_ERROR                             = 0,
  VXI11_ERROR_SYNTAX_ERROR                         = 1,
  VXI11_ERROR_DEVICE_NOT_ACCESSIBLE                = 3,
  VXI11_ERROR_INVALID_LINK_IDENTIFIER              = 4,
  VXI11_ERROR_PARAMETER_ERROR                      = 5,
  VXI11_ERROR_CHANNEL_NOT_ESTABLISHED              = 6,
  VXI11_ERROR_OPERATION_NOT_SUPPORTED              = 8,
  VXI11_ERROR_OUT_OF_RESOURCES                     = 9,
  VXI11_ERROR_DEVICE_LOCKED_BY_ANOTHER_LINK        = 11,
  VXI11_ERROR_NO_LOCK_HELD_BY_THIS_LINK            = 12,
  VXI11_ERROR_IO_TIMEOUT                           = 15,
  VXI11_ERROR_IO_ERROR                             = 17,
  VXI11_ERROR_INVALID_ADDRESS                      = 21,
  VXI11_ERROR_ABORT                                = 23,
  VXI11_ERROR_CHANNEL_ALREADY_ESTABLISHED          = 29,

  /* Catch-all used for converting from errno */
  EX1629_ERROR_GENERIC                             = 0x1000,

  /* System errors */
  EX1629_ERROR_SYSTEM_FAILURE                      = 0x1100,
  EX1629_ERROR_OUT_OF_MEMORY                       = 0x1101,
  EX1629_ERROR_SOCKET                              = 0x1102,
  EX1629_ERROR_CONNECT                             = 0x1103,
  EX1629_ERROR_IO_ERROR                            = 0x1104,
  EX1629_ERROR_NO_SERIAL_NUMBER                    = 0x1105,
  EX1629_ERROR_NO_MAC_ADDR                         = 0x1106,
  EX1629_ERROR_PTP_NOT_RUNNING                     = 0x1107,

  /* Device errors */
  EX1629_ERROR_RPC_ERROR                           = 0x1200,
  EX1629_ERROR_TIMEOUT                             = 0x1201,
  EX1629_ERROR_DEVICE_ERROR                        = 0x1202,
  EX1629_ERROR_DEVICE_LOCKED                       = 0x1203,
  EX1629_ERROR_DEVICE_NOT_LOCKED                   = 0x1204,
  EX1629_ERROR_OUT_OF_LINK_IDS                     = 0x1205,
  EX1629_ERROR_INVALID_LID                         = 0x1206,
  EX1629_ERROR_NOT_CONNECTED                       = 0x1207,
  EX1629_ERROR_ALREADY_STREAMING                   = 0x1208,
  EX1629_ERROR_ACQUISITION_IN_PROGRESS             = 0x1209,
  EX1629_ERROR_APP_UNKNOWN_STATUS                  = 0x120A,
  EX1629_ERROR_APP_UNSUPPORTED_PROC                = 0x120B,
  EX1629_ERROR_APP_QUERY_RESPONSE_MISMATCH         = 0x120C,
  EX1629_ERROR_DATA_FIFO_ERROR                     = 0x120D,
  EX1629_ERROR_DATA_READER_THREAD_ERROR            = 0x120E,
  EX1629_ERROR_SAMPLE_COUNT                        = 0x120F,
  EX1629_ERROR_INCORRECT_TEDS_ID                   = 0x1210,
  EX1629_ERROR_INCONSISTENT_CONF_SCANLIST          = 0x1211,
  EX1629_ERROR_PRETRIGGER_NOT_SUPPORTED_YET        = 0x1212,
  EX1629_ERROR_FIFO_STREAMING_ENABLED              = 0x1213,
  EX1629_ERROR_INSUFFICIENT_UPTIME_FOR_CAL         = 0x1214,
  EX1629_ERROR_CONFIG_FILE_NOT_PRESENT             = 0x1215,
  EX1629_ERROR_INCONSISTENT_CONF_WT                = 0x1216,
  EX1629_ERROR_INCONSISTENT_TRIGGER_TIMESTAMP      = 0x1217,
  EX1629_ERROR_INCONSISTENT_SYNC_TIMESTAMP         = 0x1218,
  EX1629_ERROR_MLAN_BUFFER_OVERFLOW                = 0x1219,
  EX1629_ERROR_MLAN_BUFFER_LEN_MISMATCH            = 0x121A,
  EX1629_ERROR_UNSUPPORTED_TEDS_DEVICE             = 0x121B,
  EX1629_ERROR_INCORRECT_TEDS_ID_LEN               = 0x121C,
  EX1629_ERROR_INCORRECT_TEDS_DATA_LEN             = 0x121D,
  EX1629_ERROR_TEDS_DATA_READBACK_FAILURE          = 0x121E,
  EX1629_ERROR_FIFO_OVERFLOW                       = 0x121F,
  EX1629_ERROR_PROFILING_NOT_ENABLED               = 0x1220,
  EX1629_ERROR_INCONSISTENT_SAMP_CLK_SRC           = 0x1221,
  EX1629_ERROR_DYNAMIC_EXCITATION_EU_ENABLED       = 0x1222,
  EX1629_ERROR_HD_INVALID_STATE_TRANSITION         = 0x1223,
  EX1629_ERROR_HD_MOUNT_FAIL                       = 0x1224,
  EX1629_ERROR_HD_UNMOUNT_FAIL                     = 0x1225,
  EX1629_ERROR_HD_FILE_EXISTS                      = 0x1226,
  EX1629_ERROR_HD_NO_DATA_FILE                     = 0x1227,
  EX1629_ERROR_HD_NO_INDEX_FILE                    = 0x1228,
  EX1629_ERROR_HD_FILE_OPEN_FAIL                   = 0x1229,
  EX1629_ERROR_HD_NOT_SUPPORTED                    = 0x122A,
  EX1629_ERROR_HD_HANG                             = 0x122B,
  EX1629_ERROR_NET_HANG                            = 0x122C,
  EX1629_ERROR_INPUT_BRIDGE_NOT_COMPLETE           = 0x122D,
  EX1629_ERROR_INCONSISTENT_LXI_LIMIT_INVERT       = 0x122E,
  EX1629_ERROR_NON_HOMOGENEOUS_ANALOG_BOARDS       = 0x122F,

  /* Argument errors */
  EX1629_ERROR_INVALID_ARG                         = 0x1300,
  EX1629_ERROR_INVALID_CHANNEL                     = 0x1301,
  EX1629_ERROR_INVALID_BOARD                       = 0x1302,
  EX1629_ERROR_INVALID_CHANNEL_LIST_LENGTH         = 0x1303,
  EX1629_ERROR_INVALID_SAMPLING_RATE               = 0x1304,
  EX1629_ERROR_INVALID_GAIN                        = 0x1305,
  EX1629_ERROR_INVALID_CONVERSION_CONFIG           = 0x1306,
  EX1629_ERROR_INVALID_CONF_SCANLIST_LENGTH        = 0x1307,
  EX1629_ERROR_INVALID_CONF_SCANLIST_ENTRY         = 0x1308,
  EX1629_ERROR_INVALID_PARAMETER_LIST_LENGTH       = 0x1309,
  EX1629_ERROR_INVALID_EUCONV_EXCITATION_VOLT_SRC  = 0x130A,
  EX1629_ERROR_ARG_OUT_OF_RANGE                    = 0x130B,
  EX1629_ERROR_INVALID_FS_FOR_THIS_SCANLIST        = 0x130C,
  EX1629_ERROR_INVALID_SCANLIST_FOR_THIS_FS        = 0x130D,
  EX1629_ERROR_DIO_NO_INPUT_BANK_CONFIGURED        = 0x130E,
  EX1629_ERROR_DIO_NO_OUTPUT_BANK_CONFIGURED       = 0x130F,
  EX1629_ERROR_DIO_CONFLICT_OUTPUT_IN_USE          = 0x1310,
  EX1629_ERROR_DIO_CONFLICT_DUPLICATE_ENTRY        = 0x1311,
  EX1629_ERROR_DIO_INVALID_INPUT_LINE              = 0x1312,
  EX1629_ERROR_DIO_INVALID_OUTPUT_LINE             = 0x1313,
  EX1629_ERROR_DIO_INVALID_INPUT_EVENT             = 0x1314,
  EX1629_ERROR_DIO_INVALID_OUTPUT_ACTION           = 0x1315,
  EX1629_ERROR_QTR_BRIDGE_NOT_SELECTED             = 0x1316,
  EX1629_ERROR_INVALID_LEADWIRE_RESISTANCE_VALUE   = 0x1317,
  EX1629_ERROR_INVALID_LEADWIRE_DESENSITIZATION_FACTOR = 0x1318,
  EX1629_ERROR_SCANLIST_CONTAINS_BAD_CHANNEL       = 0x1319,
  EX1629_ERROR_SENSOR_LED_LIT_UP_ON_ANOTHER_CHANNEL = 0x131A,
  EX1629_ERROR_CONF_SRC_NOT_SUPPORTED_ON_THIS_HW    = 0x131B,

  /* Analog board DSP errors (mapped from error_code_t enum in dspcommands.h) */
  EX1629_ERROR_INVALID_EXCITE_POS_VOLT             = 0x1400,
  EX1629_ERROR_INVALID_EXCITE_NEG_VOLT             = 0x1401,
  EX1629_ERROR_INVALID_GAIN_SETTING                = 0x1402,
  EX1629_ERROR_INVALID_BRIDGE_CONFIG               = 0x1403,
  EX1629_ERROR_INVALID_COMPRES_TYPE                = 0x1404,
  EX1629_ERROR_INVALID_SHUNT_SRC                   = 0x1405,
  EX1629_ERROR_INVALID_SHUNT_SRC_FOR_BRIDGE_TYPE   = 0x1406,
  EX1629_ERROR_SHUNT_FP_VAL_UNEQUAL                = 0x1407,
  EX1629_ERROR_INVALID_CONFSRC_TYPE                = 0x1408,
  EX1629_ERROR_INVALID_CONFGAIN_SETTING            = 0x1409,
  EX1629_ERROR_CONF_TOO_MANY_ENTRIES               = 0x140A,
  EX1629_ERROR_INVALID_FILTER_TYPE                 = 0x140B,
  EX1629_ERROR_BESSEL_REQUIRES_ORDER               = 0x140C,
  EX1629_ERROR_IIR_ORDER_OUT_OF_RANGE              = 0x140D,
  EX1629_ERROR_INVALID_TRANSFORM_TYPE              = 0x140E,
  EX1629_ERROR_IIR_PARM_FAILURE                    = 0x140F,
  EX1629_ERROR_INVALID_EU_BRIDGE_TYPE              = 0x1410,
  EX1629_ERROR_FPGA_TRIGINIT_NOT_IN_IDLE_STATE     = 0x1411,
  EX1629_ERROR_FPGA_TRIGINIT_IDLE_TO_ACQ_TIMEOUT   = 0x1412,
  EX1629_ERROR_FPGA_TRIGABORT_ACQ_TO_IDLE_TIMEOUT  = 0x1413,
  EX1629_ERROR_TEDS_DEVICE_NOT_PRESENT             = 0x1414,
  EX1629_ERROR_TEDS_INFO_CRC_FAILURE               = 0x1415,
  EX1629_ERROR_TEDS_ID_CRC_FAILURE                 = 0x1416,
  EX1629_ERROR_TEDS_WRITE_SCRATCHPAD_RDBK          = 0x1417,
  EX1629_ERROR_TEDS_WRITE_INFO_RDBK                = 0x1418,
  EX1629_ERROR_TRIGINIT_NEED_SOFTSYNC              = 0x1419,
  EX1629_ERROR_SHUNT_FPS_ENABLED_ON_MULTIPLE_CHANNELS = 0x141A,
  EX1629_ERROR_EXTERNAL_ADC_MASTER_CLOCK_LOST      = 0x1420,
  EX1629_ERROR_INVALID_CONF_FILTER_WT              = 0x1421,
  EX1629_ERROR_IIR_NOT_SUPPORTED_FOR_CURR_FS       = 0x1422,
  EX1629_ERROR_FS_NOT_SUPPORTED_WHEN_CONF_EN       = 0x1423,
  EX1629_ERROR_CONF_OPS_NOT_SUPPORTED_FOR_CURR_FS  = 0x1424,
	EX1629_ERROR_ILLEGAL_TRIGGER_SAMPLE_COUNT_SPECIFIED = 0x1425,
	EX1629_ERROR_ILLEGAL_PRETRIGGER_SAMPLE_COUNT_SPECIFIED = 0x1426,
	EX1629_ERROR_CALCULATING_SETTLING_TIME           = 0x1427,
  EX1629_ERROR_FS_NOT_SUPPORTED_FOR_DYNAMIC_EXCITATION_EU = 0x1428,
  EX1629_ERROR_DYNAMIC_EXCITATION_EU_NOT_SUPPORTED_AT_CURR_FS = 0x1429,
  EX1629_ERROR_DYNAMIC_EXCITATION_EU_CONF_EXCITEOUT_SRC_NOT_ENABLED = 0x142A,
  EX1629_ERROR_DYNAMIC_EXCITATION_EU_NEEDS_CONF_EXCITEOUT_SRC = 0x142B,
  EX1629_ERROR_CONF_LIMIT_INVALID_REPORTING_TYPE   = 0x142C,
  EX1629_ERROR_BRIDGE_LIMIT_NOT_SUPPORTED_AT_CURR_FS = 0x142D,
  EX1629_ERROR_FS_NOT_SUPPORTED_FOR_BRIDGE_LIMIT_CHECKING = 0x142E,
  EX1629_ERROR_CONF_LIMIT_NOT_SUPPORTED_AT_CURR_FS = 0x142F,
  EX1629_ERROR_FS_NOT_SUPPORTED_FOR_CONF_LIMIT_CHECKING = 0x1430,
  EX1629_ERROR_HW_DOES_NOT_SUPPORT_CONF_EXCITEOUT_BUFF_SRC = 0x1431,
  EX1629_ERROR_TEDS_OPS_NOT_SUPPORTED_DURING_SENSOR_IDENTIFY = 0x1432,
  EX1629_ERROR_FRONT_PANEL_SHUNT_ACTIVE            = 0x1433,
  EX1629_ERROR_TEDS_SHUNT_ACTIVE = 0x1434,
  EX1629_ERROR_INTERNAL_SHUNT_REMOTE_ACTIVE        = 0x1435,
  EX1629_ERROR_SENSOR_LED_ACTIVE                   = 0x1436,
  EX1629_ERROR_TEDS_SHUNT_ENABLED_ON_MULTIPLE_CHANNELS = 0x1437,
  EX1629_ERROR_TEDS_OPS_NOT_SUPPORTED_WHEN_USING_TEDS_SHUNT = 0x1438,

  /*Calibration errors*/
  EX1629_ERROR_XML_SAVE_FILE                       = 0x1500,
  EX1629_ERROR_XML_LOAD_FILE                       = 0x1501,
  EX1629_ERROR_XML_MALFORMED                       = 0x1502,
  EX1629_ERROR_XML_INVALID_PARM                    = 0x1503,
  EX1629_ERROR_XML_REQUIRE_TEDS                    = 0x1504,
  EX1629_ERROR_CAL_UNSET_VALUES                    = 0x1505,
  EX1629_ERROR_CAL_FILENAME_TOO_LONG               = 0x1506,
  EX1629_ERROR_CAL_NOMINAL_CAL_NOT_PRESENT         = 0x1507,
  EX1629_ERROR_CAL_FACTORY_CAL_NOT_PRESENT         = 0x1508,
  EX1629_ERROR_CAL_INCOMPLETE_CAL                  = 0x1509,
  EX1629_ERROR_CAL_SELF_CAL_NOT_PRESENT            = 0x150A,
  EX1629_ERROR_CAL_IN_PROGRESS                     = 0x150B,
  EX1629_ERROR_CAL_BLOCKS_PRESENT                  = 0x150C,
  EX1629_ERROR_CAL_FACTORY_MODE_REQUIRED           = 0x150D,
  EX1629_ERROR_CAL_FILE_NOT_PRESENT                = 0x150E,
  EX1629_ERROR_CAL_FILE_TOO_LARGE                  = 0x150F,

  /* Digital board FPGA errors */
  EX1629_ERROR_LXI_INPUT_CONFIG_CONFLICT           = 0x1600,
  EX1629_ERROR_LXI_OUTPUT_CONFIG_CONFLICT          = 0x1601,
  EX1629_ERROR_LXI_INPUT_MISCONFIGURATION          = 0x1602,
  EX1629_ERROR_LXI_OUTPUT_MISCONFIGURATION         = 0x1603,
  EX1629_ERROR_LXI_OUTPUT_CONFLICT                 = 0x1604,
  EX1629_ERROR_INVALID_MODE_FOR_SOFT_TRIGGER       = 0x1605,
  EX1629_ERROR_INVALID_MODE_FOR_SOFT_ARM           = 0x1606,
} ex1629_result_t;

/*******************************************************************************
 * EX1629 error code to error string mapping struct
 ******************************************************************************/
struct ex1629_error_mappings {
  ex1629_result_t error_code;
  char * error_string;
};


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
const char * ex1629_result_to_string(ex1629_result_t error_code);



/*******************************************************************************
 * Debug printing macros
 ******************************************************************************/
//#define EX1629_DEBUG_ENABLED

#ifdef __GNUC__ /* for visual c */

#ifdef EX1629_DEBUG_ENABLED
#define EX1629_DEBUG_FILE "/var/ex1629_debug.txt"
#define EX1629_DEBUG(fmt, args...) \
  { \
    FILE *fp = fopen(EX1629_DEBUG_FILE, "a"); \
    if (fp) { \
      fprintf(fp, fmt, ## args); \
    } \
    fclose(fp); \
  }

#else
#define EX1629_DEBUG(fmt, args...) do{}while(0)
#endif

#endif  /* for visual c */

#endif
