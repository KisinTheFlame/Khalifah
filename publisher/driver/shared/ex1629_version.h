/*******************************************************************************
 *
 * Module Name: ex1629_version.h
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
 *   Provides version constants and data structures to the server.
 *
 ******************************************************************************/


/*******************************************************************************
 * Protect Against Multiple Inclusion
 ******************************************************************************/
#ifndef EX1629_VERSION_H
#define EX1629_VERSION_H 


/*******************************************************************************
 * Various Device and Version Constants
 ******************************************************************************/
/* manufacturer string */
#define EX1629_MANUF_STR "VTI Instruments Corporation"
/* model string */
#define EX1629_MODEL_STR "EX1629"
/* the prefix is for special builds, like alpha or beta releases */
#define EX1629_VERSION_PREFIX "DEV"

/* Important:
 * for the following 3 #defines, only one space should appear between the 
 * symbol being defined and its value.  This is because a script uses cut
 * to strip out the version numbers using the space character as the delimiter
 * and it will interpret the wrong number of fields if there is an extra space
 */

/* version major number */
#define EX1629_VERSION_MAJOR 1
/* version minor number */
#define EX1629_VERSION_MINOR 11
/* version build number */
#define EX1629_VERSION_BUILD 2
/* build date */
#define EX1629_VERSION_DATE  __DATE__
/* build time */
#define EX1629_VERSION_TIME __TIME__


#endif
