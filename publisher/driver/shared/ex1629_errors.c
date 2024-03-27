/*******************************************************************************
 *
 * Module Name: ex1629_errors.h
 *             $Author: jjurack $
 *             $Revision: 1.54 $
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
 * Includes
 ******************************************************************************/
#include <string.h>
#include "ex1629_errors.h"


/*******************************************************************************
 * global error mapping struct
 ******************************************************************************/
const struct ex1629_error_mappings g_ex1629_error_mappings[] = {
  {EX1629_SUCCESS,                                "Success"},
  /* VXI11 errors */
  {VXI11_ERROR_NO_ERROR,                          "Success"},
  {VXI11_ERROR_SYNTAX_ERROR,                      "Syntax error"},
  {VXI11_ERROR_DEVICE_NOT_ACCESSIBLE,             "Device not accessible"},
  {VXI11_ERROR_INVALID_LINK_IDENTIFIER,           "Invalid link identifier"},
  {VXI11_ERROR_PARAMETER_ERROR,                   "Parameter error"},
  {VXI11_ERROR_CHANNEL_NOT_ESTABLISHED,           "Channel not established"},
  {VXI11_ERROR_OPERATION_NOT_SUPPORTED,           "Operation not supported"},
  {VXI11_ERROR_OUT_OF_RESOURCES,                  "Out of resources"},
  {VXI11_ERROR_DEVICE_LOCKED_BY_ANOTHER_LINK,     "Device locked by another link"},
  {VXI11_ERROR_NO_LOCK_HELD_BY_THIS_LINK,         "No lock held by this link"},
  {VXI11_ERROR_IO_TIMEOUT,                        "IO timeout"},
  {VXI11_ERROR_IO_ERROR,                          "IO error"},
  {VXI11_ERROR_INVALID_ADDRESS,                   "Invalid address"},
  {VXI11_ERROR_ABORT,                             "Abort"},
  {VXI11_ERROR_CHANNEL_ALREADY_ESTABLISHED,       "Channel already established"},
  /* Catch-all used for converting from errno */
  {EX1629_ERROR_GENERIC,                          "Undefined/unspecified error"},
  /* System errors */
  {EX1629_ERROR_SYSTEM_FAILURE,                   "System failure"},
  {EX1629_ERROR_OUT_OF_MEMORY,                    "Out of memory"},
  {EX1629_ERROR_SOCKET,                           "Socket error"},
  {EX1629_ERROR_CONNECT,                          "Connection error"},
  {EX1629_ERROR_IO_ERROR,                         "IO error"},
  {EX1629_ERROR_NO_SERIAL_NUMBER,                 "No serial number assigned"},
  {EX1629_ERROR_NO_MAC_ADDR,                      "No MAC address assigned"},
  {EX1629_ERROR_PTP_NOT_RUNNING,                  "PTP is not running"},
  /* Device errors */
  {EX1629_ERROR_RPC_ERROR,                        "RPC error"},
  {EX1629_ERROR_TIMEOUT,                          "Timeout"},
  {EX1629_ERROR_DEVICE_ERROR,                     "Device error"},
  {EX1629_ERROR_DEVICE_LOCKED,                    "Device locked"},
  {EX1629_ERROR_DEVICE_NOT_LOCKED,                "Device not locked"},
  {EX1629_ERROR_OUT_OF_LINK_IDS,                  "Out of link IDs"},
  {EX1629_ERROR_INVALID_LID,                      "Invalid link ID"},
  {EX1629_ERROR_NOT_CONNECTED,                    "Not connected"},
  {EX1629_ERROR_ALREADY_STREAMING,                "Already streaming"},
  {EX1629_ERROR_ACQUISITION_IN_PROGRESS,          "Command not permitted during acquisition"},
  {EX1629_ERROR_APP_UNKNOWN_STATUS,               "Unknown application layer status"},
  {EX1629_ERROR_APP_UNSUPPORTED_PROC,             "Unsupported application layer procedure"},
  {EX1629_ERROR_APP_QUERY_RESPONSE_MISMATCH,      "Application layer response did not match query"},
  {EX1629_ERROR_DATA_FIFO_ERROR,                  "Data FIFO error"},
  {EX1629_ERROR_DATA_READER_THREAD_ERROR,         "Data reader thread error"},
  {EX1629_ERROR_SAMPLE_COUNT,                     "Sample count is not a small positive integer"},
  {EX1629_ERROR_INCORRECT_TEDS_ID,                "TEDS device ID does not match the specified ID"},
  {EX1629_ERROR_INCONSISTENT_CONF_SCANLIST,       "Confidence scanlist is not consistent accross all channels"},
  {EX1629_ERROR_PRETRIGGER_NOT_SUPPORTED_YET,     "Pre-trigger support is not complete"},
  {EX1629_ERROR_FIFO_STREAMING_ENABLED,           "Read_fifo prohibited while streaming data"},
  {EX1629_ERROR_INSUFFICIENT_UPTIME_FOR_CAL,      "Insufficient uptime for calibration"},
  {EX1629_ERROR_CONFIG_FILE_NOT_PRESENT,          "Specified configuration file not present"},
  {EX1629_ERROR_INCONSISTENT_CONF_WT,             "Confidence weight is not consistent across all channels"},
  {EX1629_ERROR_INCONSISTENT_TRIGGER_TIMESTAMP,   "Trigger timestamp is not consistent across all channels"},
  {EX1629_ERROR_INCONSISTENT_SYNC_TIMESTAMP,      "Sync timestamp is not consistent across all channels"},
  {EX1629_ERROR_MLAN_BUFFER_OVERFLOW,             "MicroLAN buffer overflow"},
  {EX1629_ERROR_MLAN_BUFFER_LEN_MISMATCH,         "MicroLAN buffer length mismatch"},
  {EX1629_ERROR_UNSUPPORTED_TEDS_DEVICE,          "Unsupported TEDS device"},
  {EX1629_ERROR_INCORRECT_TEDS_ID_LEN,            "Incorrect TEDS device ID length"},
  {EX1629_ERROR_INCORRECT_TEDS_DATA_LEN,          "Incorrect TEDS data length"},
  {EX1629_ERROR_TEDS_DATA_READBACK_FAILURE,       "TEDS device readback failure"},
  {EX1629_ERROR_FIFO_OVERFLOW,                    "Data FIFO overflowed"},
  {EX1629_ERROR_PROFILING_NOT_ENABLED,            "Profiling is not enabled"},
  {EX1629_ERROR_INCONSISTENT_SAMP_CLK_SRC,        "Clock source is not consistent accross all channels and digital backend"},
  {EX1629_ERROR_DYNAMIC_EXCITATION_EU_ENABLED,    "Cannot perform this operation while dynamic excitation is enabled"},
  {EX1629_ERROR_HD_INVALID_STATE_TRANSITION,      "Improper sequence of hard disk commands"},
  {EX1629_ERROR_HD_MOUNT_FAIL,                    "Failed to mount hard disk"},
  {EX1629_ERROR_HD_UNMOUNT_FAIL,                  "Failed to unmount hard disk"},
  {EX1629_ERROR_HD_FILE_EXISTS,                   "Data file exists"},
  {EX1629_ERROR_HD_NO_DATA_FILE,                  "No data file found"},
  {EX1629_ERROR_HD_NO_INDEX_FILE,                 "No data index file found"},
  {EX1629_ERROR_HD_FILE_OPEN_FAIL,                "Failed to open data file"},
  {EX1629_ERROR_HD_NOT_SUPPORTED,                 "Hard disks are not supported on this hardware"},
  {EX1629_ERROR_HD_HANG,                          "Hard disk hang, cannot proceed"},
  {EX1629_ERROR_NET_HANG,                         "Network hang, cannot proceed"},
  {EX1629_ERROR_INPUT_BRIDGE_NOT_COMPLETE,        "The bridge input may be open"},
  {EX1629_ERROR_INCONSISTENT_LXI_LIMIT_INVERT,    "LXI Limit Invert is not consistent across all channels"},
  {EX1629_ERROR_NON_HOMOGENEOUS_ANALOG_BOARDS,    "All analog boards are not of the same revision, which is a requirement to perform this action."},
 
  /* Argument errors */ 
  {EX1629_ERROR_INVALID_ARG,                      "Invalid argument"},
  {EX1629_ERROR_INVALID_CHANNEL,                  "Invalid channel"},
  {EX1629_ERROR_INVALID_BOARD,                    "Invalid board"},
  {EX1629_ERROR_INVALID_CHANNEL_LIST_LENGTH,      "Invalid channel list length"},
  {EX1629_ERROR_INVALID_SAMPLING_RATE,            "Invalid sampling rate"},
  {EX1629_ERROR_INVALID_GAIN,                     "Invalid gain"},
  {EX1629_ERROR_INVALID_CONVERSION_CONFIG,        "Invalid EU conversion configuration"},
  {EX1629_ERROR_INVALID_CONF_SCANLIST_LENGTH,     "Invalid confidence scanlist length"},
  {EX1629_ERROR_INVALID_CONF_SCANLIST_ENTRY,      "Invalid confidence scanlist entry"},
  {EX1629_ERROR_INVALID_PARAMETER_LIST_LENGTH,    "Invalid parameter list length"},
  {EX1629_ERROR_INVALID_EUCONV_EXCITATION_VOLT_SRC, "Invalid EU conversion excitation volt source"},
  {EX1629_ERROR_ARG_OUT_OF_RANGE,                 "Argument out of range"},
  {EX1629_ERROR_INVALID_FS_FOR_THIS_SCANLIST,    "This sampling frequency is only allowed when one analog board is enabled"},
  {EX1629_ERROR_INVALID_SCANLIST_FOR_THIS_FS,    "This sampling frequency is only allowed when one analog board is enabled"},
  
  {EX1629_ERROR_DIO_NO_INPUT_BANK_CONFIGURED,     "No DIO Input Bank is configured"},
  {EX1629_ERROR_DIO_NO_OUTPUT_BANK_CONFIGURED,    "No DIO Output Bank is configured"},
  {EX1629_ERROR_DIO_CONFLICT_OUTPUT_IN_USE,       "Output Line is already used"},
  {EX1629_ERROR_DIO_CONFLICT_DUPLICATE_ENTRY,     "Duplicate configuration entry"},
  {EX1629_ERROR_DIO_INVALID_INPUT_LINE,           "Invalid Input Line"},
  {EX1629_ERROR_DIO_INVALID_OUTPUT_LINE,          "Invalid Output Line"},
  {EX1629_ERROR_DIO_INVALID_INPUT_EVENT,          "Invalid Input event"},
  {EX1629_ERROR_DIO_INVALID_OUTPUT_ACTION,        "Invalid Output Action"},
  {EX1629_ERROR_QTR_BRIDGE_NOT_SELECTED,          "Quarter bridge configuration is not selected"},
  {EX1629_ERROR_INVALID_LEADWIRE_RESISTANCE_VALUE,"Leadwire resistance value cannot be less than zero"},
  {EX1629_ERROR_INVALID_LEADWIRE_DESENSITIZATION_FACTOR,"Leadwire desensitization factor cannot be less than 1"},
  {EX1629_ERROR_SENSOR_LED_LIT_UP_ON_ANOTHER_CHANNEL,"Sensor LED is already ON on another channel"},
  
  {EX1629_ERROR_CONF_SRC_NOT_SUPPORTED_ON_THIS_HW, "This confidence source requires a certain HW layout which this unit does not have"},
  /* Analog board DSP errors */
  {EX1629_ERROR_INVALID_EXCITE_POS_VOLT,          "Invalid positive excitation voltage"},
  {EX1629_ERROR_INVALID_EXCITE_NEG_VOLT,          "Invalid negative excitation voltage"},
  {EX1629_ERROR_INVALID_GAIN_SETTING,             "Invalid gain setting"},
  {EX1629_ERROR_INVALID_BRIDGE_CONFIG,            "Invalid bridge configuration"},
  {EX1629_ERROR_INVALID_COMPRES_TYPE,             "Invalid compensation resistor type"},
  {EX1629_ERROR_INVALID_SHUNT_SRC,                "Invalid shunt source"},
  {EX1629_ERROR_INVALID_SHUNT_SRC_FOR_BRIDGE_TYPE,"Invalid shunt source for bridge type"},
  {EX1629_ERROR_SHUNT_FP_VAL_UNEQUAL,             "Front panel shunt values are not equal for all 16 channels"},
  {EX1629_ERROR_INVALID_CONFSRC_TYPE,             "Invalid confirmation source type"},
  {EX1629_ERROR_INVALID_CONFGAIN_SETTING,         "Invalid confirmation gain setting"},
  {EX1629_ERROR_CONF_TOO_MANY_ENTRIES,            "Too many confidence list entries"},
  {EX1629_ERROR_INVALID_FILTER_TYPE,              "Invalid filter type"},
  {EX1629_ERROR_BESSEL_REQUIRES_ORDER,            "Bessel filter requires filter order parameter"},
  {EX1629_ERROR_IIR_ORDER_OUT_OF_RANGE,           "IIR filter order out of range"},
  {EX1629_ERROR_INVALID_TRANSFORM_TYPE,           "Invalid filter transform type"},
  {EX1629_ERROR_IIR_PARM_FAILURE,                 "Invalid IIR filter parameters"},
  {EX1629_ERROR_INVALID_EU_BRIDGE_TYPE,           "Invalid EU conversion bridge type"},
  {EX1629_ERROR_FPGA_TRIGINIT_NOT_IN_IDLE_STATE,  "FPGA not in idle state for trigger"},
  {EX1629_ERROR_FPGA_TRIGINIT_IDLE_TO_ACQ_TIMEOUT,"Timeout waiting for the FPGA triggering to begin"},
  {EX1629_ERROR_FPGA_TRIGABORT_ACQ_TO_IDLE_TIMEOUT,"Timeout waiting for the FPGA triggering to end"},
  {EX1629_ERROR_TEDS_DEVICE_NOT_PRESENT,          "TEDS device not present"},
  {EX1629_ERROR_TEDS_INFO_CRC_FAILURE,            "TEDS info CRC failure"},
  {EX1629_ERROR_TEDS_ID_CRC_FAILURE,              "TEDS ID CRC failure"},
  {EX1629_ERROR_TEDS_WRITE_SCRATCHPAD_RDBK,       "TEDS scratchpad write failure"},
  {EX1629_ERROR_TEDS_WRITE_INFO_RDBK,             "TEDS info write failure"},
  {EX1629_ERROR_TRIGINIT_NEED_SOFTSYNC,           "A softsync is required before triginit is valid"},
  {EX1629_ERROR_SHUNT_FPS_ENABLED_ON_MULTIPLE_CHANNELS, "A front panel shunt cannot be enabled on multiple channels"},
  {EX1629_ERROR_EXTERNAL_ADC_MASTER_CLOCK_LOST,   "External ADC master clock was lost"}, 
  {EX1629_ERROR_INVALID_CONF_FILTER_WT,           "Invalid confidence filter weight"},
  {EX1629_ERROR_IIR_NOT_SUPPORTED_FOR_CURR_FS,    "IIR filter is not supported for the current fs"},
  {EX1629_ERROR_FS_NOT_SUPPORTED_WHEN_CONF_EN,    "This sample frequency is not supported when confidence sources are enabled"},
  {EX1629_ERROR_CONF_OPS_NOT_SUPPORTED_FOR_CURR_FS, "Confidence operations are not supported at this sample frequency"},
	{EX1629_ERROR_ILLEGAL_TRIGGER_SAMPLE_COUNT_SPECIFIED, "Illegal trigger sample count"},
	{EX1629_ERROR_ILLEGAL_PRETRIGGER_SAMPLE_COUNT_SPECIFIED, "Illegal pretrigger sample count"},
	{EX1629_ERROR_CALCULATING_SETTLING_TIME,        "Error while calculating settling time"},
  {EX1629_ERROR_FS_NOT_SUPPORTED_FOR_DYNAMIC_EXCITATION_EU, "This sampling frequency is not supported while dynamic excitation EU is enabled."},
  {EX1629_ERROR_DYNAMIC_EXCITATION_EU_NOT_SUPPORTED_AT_CURR_FS, "Dynamic excitation EU is not supported with the current sampling frequncy"},
  {EX1629_ERROR_DYNAMIC_EXCITATION_EU_CONF_EXCITEOUT_SRC_NOT_ENABLED, "Confidence excitation source must be enabled to enable dynamic excitation EU"},
  {EX1629_ERROR_DYNAMIC_EXCITATION_EU_NEEDS_CONF_EXCITEOUT_SRC, "Confidence excitation source cannot be disabled while dynamic excitation EU is enabled"},
  {EX1629_ERROR_CONF_LIMIT_INVALID_REPORTING_TYPE, "Invalid reporting type specified"},
  {EX1629_ERROR_BRIDGE_LIMIT_NOT_SUPPORTED_AT_CURR_FS, "Bridge limit checking is not supported at the current sampling frequency"},
  {EX1629_ERROR_FS_NOT_SUPPORTED_FOR_BRIDGE_LIMIT_CHECKING, "This sampling frequency is not supported while bridge limit checking is enabled"},
  {EX1629_ERROR_CONF_LIMIT_NOT_SUPPORTED_AT_CURR_FS, "Confidence limit checking is not supported at the current sampling frequency"},
  {EX1629_ERROR_FS_NOT_SUPPORTED_FOR_CONF_LIMIT_CHECKING, "This sampling frequency is not supported while confidence limit checking is enabled"},
  {EX1629_ERROR_HW_DOES_NOT_SUPPORT_CONF_EXCITEOUT_BUFF_SRC,     "The Analog Board H/W Version does not support Confidence Source 12"},
  {EX1629_ERROR_TEDS_OPS_NOT_SUPPORTED_DURING_SENSOR_IDENTIFY,     "TEDS operation is not allowed when a Sensor LED is ON on same analog board"},
  {EX1629_ERROR_FRONT_PANEL_SHUNT_ACTIVE,     "Operation not allowed when the Front Panel Shunt is active on same analog board"},
  {EX1629_ERROR_TEDS_SHUNT_ACTIVE,     "Operation not allowed when the TEDS Shunt is active on same analog board"},
  {EX1629_ERROR_INTERNAL_SHUNT_REMOTE_ACTIVE,     "Operation not allowed when the Internal Shunt (Remote) is active on same channel "},
  {EX1629_ERROR_SENSOR_LED_ACTIVE,     "Operation not allowed when the Sensor LED is active"},
  {EX1629_ERROR_TEDS_SHUNT_ENABLED_ON_MULTIPLE_CHANNELS,     "TEDS shunt cannot be enabled on multiple channels on same analog board"},
  {EX1629_ERROR_TEDS_OPS_NOT_SUPPORTED_WHEN_USING_TEDS_SHUNT,     "TEDS Operation not allowed when using TEDS shunt on same analog board "},
  
  /*XML and Calibration errors*/
  {EX1629_ERROR_XML_SAVE_FILE,                    "Error saving XML calibration file"},
  {EX1629_ERROR_XML_LOAD_FILE,                    "Error loading XML calibration file"},
  {EX1629_ERROR_XML_MALFORMED,                    "Invalid XML calibration file format"},
  {EX1629_ERROR_XML_INVALID_PARM,                 "Invalid calibration parameter in XML file"},
  {EX1629_ERROR_XML_REQUIRE_TEDS,                 "Required TEDS ID not available"},
  {EX1629_ERROR_CAL_UNSET_VALUES,                 "Unset values in a calibration"},
  {EX1629_ERROR_CAL_FILENAME_TOO_LONG,            "Cal filename too long (probably factory cal)"},
  {EX1629_ERROR_CAL_NOMINAL_CAL_NOT_PRESENT,      "Nominal calibration not present"},
  {EX1629_ERROR_CAL_FACTORY_CAL_NOT_PRESENT,      "Factory calibration not present"},
  {EX1629_ERROR_CAL_INCOMPLETE_CAL,               "Incomplete calibration"},
  {EX1629_ERROR_CAL_SELF_CAL_NOT_PRESENT,         "Self calibration not present"},
  {EX1629_ERROR_CAL_IN_PROGRESS,                  "Calibration in progress"},
  {EX1629_ERROR_CAL_BLOCKS_PRESENT,               "Calibration blocks detected"},
  {EX1629_ERROR_CAL_FACTORY_MODE_REQUIRED,        "The system must be in factory mode to perform this action"},
  /* Digital board FPGA errors */
  {EX1629_ERROR_LXI_INPUT_CONFIG_CONFLICT,        "LXI input config conflicts with an existing output"},
  {EX1629_ERROR_LXI_OUTPUT_CONFIG_CONFLICT,       "LXI output config conflicts with an existing input"},
  {EX1629_ERROR_LXI_INPUT_MISCONFIGURATION,       "Specified LXI input is not configured as an input"},
  {EX1629_ERROR_LXI_OUTPUT_MISCONFIGURATION,      "Specified LXI output is not configured as an output"},
  {EX1629_ERROR_LXI_OUTPUT_CONFLICT,              "Specified LXI output conflicts with another output"},
  {EX1629_ERROR_INVALID_MODE_FOR_SOFT_TRIGGER,    "Software trigger is only valid in pattern mode"},
  {EX1629_ERROR_INVALID_MODE_FOR_SOFT_ARM,        "Software arm is only valid in pattern mode"},
  {EX1629_ERROR_SCANLIST_CONTAINS_BAD_CHANNEL,    "Scanlist contains a bad channel"},

  {-1, NULL}
};


/*******************************************************************************
 * Function name: ex1629_result_to_string
 *   Returns      Appropriate error string for error code
 *   error_code   Error code to be translated to a string
 * Created by:    Gary Bernhardt
 * Description:   Translate an EX1629 error code to a string.
 * Notes:         N/A
 ******************************************************************************/
const char * ex1629_result_to_string(ex1629_result_t error_code)
{
  int i;
  for (i=0; g_ex1629_error_mappings[i].error_string; i++) {
    if (error_code == g_ex1629_error_mappings[i].error_code) {
      return g_ex1629_error_mappings[i].error_string;
    }
  }
  
  return "Unknown error";
}
