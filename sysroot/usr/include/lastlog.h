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
 *	@(#)$RCSfile: lastlog.h,v $ $Revision: 4.2.8.3 $ (DEC) $Date: 1997/05/14 19:22:38 $
 */ 
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	lastlog.h	5.1 (Berkeley) 5/30/85
 */

#ifndef _LASTLOG_H_
#define _LASTLOG_H_

#include <sys/types.h>
#include <utmp_common.h>    /* For common definitions */

/* for lastlog structure */
#define LL_LINELEN      __UT_LINESIZE   /* terminal path length */
#define LL_HOSTLEN      __UT_HOSTSIZE   /* hostname length */

struct lastlog {
	time_t	ll_time;
	char	ll_line[LL_LINELEN];
	char	ll_host[LL_HOSTLEN];		/* same as in utmp */
};

#endif  /* _LASTLOG_H_ */
