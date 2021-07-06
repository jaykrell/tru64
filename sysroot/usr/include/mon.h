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
 *	@(#)$RCSfile: mon.h,v $ $Revision: 4.2.14.4 $ (DEC) $Date: 1997/08/05 20:19:23 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

/*
 * COMPONENT_NAME: (LIBCGEN) Standard C Library General Functions
 *
 * FUNCTIONS: mon.h
 *
 * ORIGINS: 10 26 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1990
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _MON_H_
#define _MON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * mon.h - macros and prototypes for standard and Digital UNIX applications
 *         of the monstartup(2) and monitor(2) profiling utilities.
 */

#include <sys/types.h>
#include <cmplrs/prof_header.h>	/* Defines standard mon.out file format */

#define _PROF_TYPE_IS_P    -1 /* -p  (prof) */
#define _PROF_TYPE_IS_PG    1 /* -pg (gprof) */
#define _PROF_TYPE_IS_NONE  0 /* no profiling active */

/*
 * Macros for standard (unsigned short) histogram counters:
 */

    /*
     *  histogram counters are unsigned shorts (according to the kernel).
     */
#define HISTCOUNTER     unsigned short

    /*
     *  fraction of text space to allocate for histogram counters
     *  here, 1/2
     */
#define HISTFRACTION    2

    /*
     *  Fraction of text space to allocate for from hash buckets.
     *  The value of HASHFRACTION is based on the minimum number of bytes
     *  of separation between two subroutine call points in the object code.
     *  Given MIN_SUBR_SEPARATION bytes of separation the value of
     *  HASHFRACTION is calculated as:
     *
     *          HASHFRACTION = MIN_SUBR_SEPARATION / (2 * sizeof(short) - 1);
     *
     *  For the Alpha architecture, the shortest distance between two
     *  subroutine call instructions is 4 bytes.
     */
#define HASHFRACTION    1

    /*
     *  general rounding functions.
     */
#define ROUNDDOWN(x,y)  (((x)/(y))*(y))
#define ROUNDUP(x,y)    ((((x)+(y)-1)/(y))*(y))

/*
 * Function prototypes for unsigned short and unsigned int histogram counters
 */

extern int moncontrol(  /* Suspend or resume last specified profiling */
	int             /* Mode: 0 = suspend profiling, 1 = resume profiling */
	);              /* Returns previous mode */

extern int monstartup(  /* Start profiling one address range or all initially */
	                /* address ranges */
	caddr_t,        /* Low address of single range to profile, or zero to */
	                /* start profiling all initially loaded text segments */
	caddr_t         /* High address of single range to profile, or zero */
	                /* to profile all initially loaded text segments */
	                /* (High address is upper limit +1 mod min inst size) */
	) ;             /* returns 0 if profiling started, -1 if not - err */

extern int monitor(     /* Stop profiling or start profiling one or more */
	                /* address ranges */
	caddr_t,        /* Low address of single range to profile, or zero */
	                /* to stop profiling and write out data file(s) */
	...             /* See Note: */
	);
/* Note:
 *
 * When the first argument is not zero the second argument definition is:
 *      caddr_t,           High address +1(mod min inst len) of single range
 *
 * When the second argument is not zero, the remaining argument definitions are:
 *      char *,            Address of buffer of unsigned short
 *      size_t,            Buffer size - bytes
 *      size_t             For compatibility, but unused - specify zero
 * Returns 0 if profiling started, -1 if not - err
 *
 * When the second argument is zero, the remaining argument definitions are:
 *      struct monitor_args *,  Array of structs describing multiple address
 *                              ranges to start profiling, and their buffers
 *      size_t,                 Number of elements in array of structs
 *      size_t                  For compatibility, but unused - specify zero
 * Returns number of elements in array of structs if profiling started, or
 * index of element for which an error was detected
 */

struct monitor_args {
	caddr_t         lowpc;          /* Low address of range to profile */
	caddr_t         highpc;         /* High address of range to profile */
	unsigned int    *buffer;        /* Address of buffer of unsigned int */
	size_t          bufsiz;         /* Buffer size - bytes */
};

extern int monitor_signal(int);


#ifdef __cplusplus
}
#endif

#endif /* _MON_H_ */
