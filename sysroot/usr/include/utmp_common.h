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
 * @(#)$RCSfile: utmp_common.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 1998/12/03 22:27:46 $
 */
#ifndef _UTMP_COMMON_H_
#define _UTMP_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

/* Definitions for ut_type - these are common to utmp.h and utmpx.h */

#define EMPTY           0	/* no valid user accounting information */
#define RUN_LVL         1
#define BOOT_TIME       2	/* time of system boot */
#define OLD_TIME        3	/* time when the system time clock changed */
#define NEW_TIME        4	/* time after system clock changed */
#define INIT_PROCESS    5       /* Process spawned by "init" */
#define LOGIN_PROCESS   6       /* A "getty" process waiting for login */
#define USER_PROCESS    7       /* A user process */
#define DEAD_PROCESS    8	/* a session leader who has exited */

#if defined (_OSF_SOURCE)
#define ACCOUNTING      9
#define	PROCESSOR	10	/* cpu start/stop and pset create/destroy */
#define	UTMAXTYPE	PROCESSOR	/* Largest legal value of ut_type */

#endif

/* The fields in struct lastlog, struct utmp and struct utmpx must correspond */
#define __UT_LINESIZE     32
#define __UT_NAMESIZE     64
#define __UT_HOSTSIZE     256

/* utmp structure always uses 64 bit time. */
struct __ut_timeval {
	long	tv_sec;		/* seconds - always 64 bits */
	int	tv_usec;	/* microseconds - 32 bits */
	int	__reserved;	/* additional 32 bits for future use */
};

#ifdef __cplusplus
}
#endif

#endif  /* _UTMP_COMMON_H_ */
