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
 * @(#)$RCSfile: rtpriocntl.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1993/09/23 17:52:18 $
 */


#ifndef _SYS_RTPRIOCNTL_H_
#define _SYS_RTPRIOCNTL_H_

#define	RT_TQINF	(-1)
#define	RT_TQDEF	(-2)
#define	RT_NOCHANGE	(-3)

typedef struct
{
	short	rt_maxpri;		/* Maximum real-time priority. */
} rtinfo_t;

#if defined(_KERNEL)
struct rt_default_quantum
{
	ulong_t		rt_tqsecs;	/* Seconds in time quantum */
	long		rt_tqnsecs;	/* Additional nanoseconds in quantum */
};
#endif

typedef struct
{
	short		rt_pri;		/* Real-Time priority */
	ulong_t		rt_tqsecs;	/* Seconds in time quantum */
	long		rt_tqnsecs;	/* Additional nanoseconds in quantum */
} rtparms_t;

#endif /* ifndef _SYS_RTPRIOCNTL_H_ */
