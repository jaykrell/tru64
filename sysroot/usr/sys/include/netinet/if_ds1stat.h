/*
 * *****************************************************************
 * *                                                               *
 * *   Copyright 2002 Compaq Information Technologies Group, L.P.  *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Compaq    *
 * *   Computer Corporation.  Possession, use,  duplication  or    *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Compaq Computer    *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: if_ds1stat.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1997/11/07 20:04:14 $
 */

#ifndef _IF_DS1STAT_H_
#define _IF_DS1STAT_H_

#include <sys/types.h>

/* 
 * DS1/E1 Counters for MIB (RFC 1406)
 * File defines structures passed across user-kernel boundary
 */

#define CCT_ID_LEN	32

/*
 * The dsx1KernGet* structures are used for
 * getting info from the kernel.
 */

typedef struct _dsx1KernGetConfigEntry {
    int    dsx1LineIndex;
    int    dsx1IfIndex;
    int    dsx1TimeElapsed;
    int    dsx1ValidIntervals;
    int    dsx1LineType;
    int    dsx1LineCoding;
    int    dsx1SendCode;
    u_char dsx1CircuitIdentifier[CCT_ID_LEN];
    int    dsx1LoopbackConfig;
    int    dsx1LineStatus;
    int    dsx1SignalMode;
    int    dsx1TransmitClockSource;
    int    dsx1Fdl;
} dsx1KernGetConfigEntry;

typedef struct _dsx1KernGetCurrentEntry {
    int   dsx1CurrentIndex;
    unsigned int  dsx1CurrentESs;
    unsigned int  dsx1CurrentSESs;
    unsigned int  dsx1CurrentSEFSs;
    unsigned int  dsx1CurrentUASs;
    unsigned int  dsx1CurrentCSSs;
    unsigned int  dsx1CurrentPCVs;
    unsigned int  dsx1CurrentLESs;
    unsigned int  dsx1CurrentBESs;
    unsigned int  dsx1CurrentDMs;
    unsigned int  dsx1CurrentLCVs;
} dsx1KernGetCurrentEntry;

typedef struct _dsx1KernGetIntervalEntry {
    int   dsx1IntervalIndex;
    int   dsx1IntervalNumber;
    unsigned int  dsx1IntervalESs;
    unsigned int  dsx1IntervalSESs;
    unsigned int  dsx1IntervalSEFSs;
    unsigned int  dsx1IntervalUASs;
    unsigned int  dsx1IntervalCSSs;
    unsigned int  dsx1IntervalPCVs;
    unsigned int  dsx1IntervalLESs;
    unsigned int  dsx1IntervalBESs;
    unsigned int  dsx1IntervalDMs;
    unsigned int  dsx1IntervalLCVs;
} dsx1KernGetIntervalEntry;

typedef struct _dsx1KernGetTotalEntry {
    int   dsx1TotalIndex;
    unsigned int  dsx1TotalESs;
    unsigned int  dsx1TotalSESs;
    unsigned int  dsx1TotalSEFSs;
    unsigned int  dsx1TotalUASs;
    unsigned int  dsx1TotalCSSs;
    unsigned int  dsx1TotalPCVs;
    unsigned int  dsx1TotalLESs;
    unsigned int  dsx1TotalBESs;
    unsigned int  dsx1TotalDMs;
    unsigned int  dsx1TotalLCVs;
} dsx1KernGetTotalEntry;

typedef struct _dsx1KernGetFarEndCurrentEntry {
    int   dsx1FarEndCurrentIndex;
    int   dsx1FarEndTimeElapsed;
    int   dsx1FarEndValidIntervals;
    unsigned int  dsx1FarEndCurrentESs;
    unsigned int  dsx1FarEndCurrentSESs;
    unsigned int  dsx1FarEndCurrentSEFSs;
    unsigned int  dsx1FarEndCurrentUASs;
    unsigned int  dsx1FarEndCurrentCSSs;
    unsigned int  dsx1FarEndCurrentLESs;
    unsigned int  dsx1FarEndCurrentPCVs;
    unsigned int  dsx1FarEndCurrentBESs;
    unsigned int  dsx1FarEndCurrentDMs;
} dsx1KernGetFarEndCurrentEntry;

typedef struct _dsx1KernGetFarEndIntervalEntry {
    int   dsx1FarEndIntervalIndex;
    int   dsx1FarEndIntervalNumber;
    unsigned int  dsx1FarEndIntervalESs;
    unsigned int  dsx1FarEndIntervalSESs;
    unsigned int  dsx1FarEndIntervalSEFSs;
    unsigned int  dsx1FarEndIntervalUASs;
    unsigned int  dsx1FarEndIntervalCSSs;
    unsigned int  dsx1FarEndIntervalLESs;
    unsigned int  dsx1FarEndIntervalPCVs;
    unsigned int  dsx1FarEndIntervalBESs;
    unsigned int  dsx1FarEndIntervalDMs;
} dsx1KernGetFarEndIntervalEntry;

typedef struct _dsx1KernGetFarEndTotalEntry {
    int   dsx1FarEndTotalIndex;
    unsigned int  dsx1FarEndTotalESs;
    unsigned int  dsx1FarEndTotalSESs;
    unsigned int  dsx1FarEndTotalSEFSs;
    unsigned int  dsx1FarEndTotalUASs;
    unsigned int  dsx1FarEndTotalCSSs;
    unsigned int  dsx1FarEndTotalLESs;
    unsigned int  dsx1FarEndTotalPCVs;
    unsigned int  dsx1FarEndTotalBESs;
    unsigned int  dsx1FarEndTotalDMs;
} dsx1KernGetFarEndTotalEntry;

typedef struct _dsx1KernGetFracEntry {
    int   dsx1FracIndex;
    int   dsx1FracNumber;
    int   dsx1FracIfIndex;
} dsx1KernGetFracEntry;

typedef union _ds1Entries {
    dsx1KernGetConfigEntry dsx1Config;		/* DS1 config */
    dsx1KernGetCurrentEntry dsx1Current;		/* DS1 current */
    dsx1KernGetIntervalEntry dsx1Interval;	/* DS1 interval */
    dsx1KernGetTotalEntry dsx1Total;		/* DS1 total */
    dsx1KernGetFarEndCurrentEntry dsx1FarEndCurrent; /* DS1 MIB far end current */
    dsx1KernGetFarEndIntervalEntry dsx1FarEndInterval; /* DS1 MIB far end interval */
    dsx1KernGetFarEndTotalEntry dsx1FarEndTotal;	/* DS1 MIB far end total */
    dsx1KernGetFracEntry dsx1Frac;		/* DS1 MIB frac */
} ds1Entries;

/*
 * The dsx1KernSet* structures are used for
 * setting info from the kernel.
 */

typedef struct _dsx1KernSetConfigEntry {
    int    dsx1LineIndex;
    int    dsx1LineType;
    int    dsx1LineCoding;
    int    dsx1SendCode;
    u_char dsx1CircuitIdentifier[CCT_ID_LEN];
    int    dsx1LoopbackConfig;
    int    dsx1SignalMode;
    int    dsx1TransmitClockSource;
    int    dsx1Fdl;

    char dsx1LineIndex_mark;
    char dsx1LineType_mark;
    char dsx1LineCoding_mark;
    char dsx1SendCode_mark;
    char dsx1CircuitIdentifier_mark;
    char dsx1LoopbackConfig_mark;
    char dsx1SignalMode_mark;
    char dsx1TransmitClockSource_mark;
    char dsx1Fdl_mark;
} dsx1KernSetConfigEntry;

typedef struct _dsx1KernSetFracEntry {
    int   dsx1FracIndex;
    int   dsx1FracNumber;
    int   dsx1FracIfIndex;

    char dsx1FracIndex_mark;
    char dsx1FracNumber_mark;
    char dsx1FracIfIndex_mark;
} dsx1KernSetFracEntry;


#define MARK_PRESENT 1
typedef struct ds1_ifdata
{
    int req_type;
    union _data {
	dsx1KernSetConfigEntry configEntry;
	dsx1KernSetFracEntry   fracEntry;
    } data;
} dsx1ManReq_type;

#endif
