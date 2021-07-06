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
 *	@(#)$RCSfile: rusers.h,v $ $Revision: 4.2.4.3 $ (DEC) $Date: 1994/03/29 18:47:23 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * @(#) from SUN 1.6
 */

#ifndef _rpcsvc_rusers_h
#define _rpcsvc_rusers_h

#include <standards.h>
#include <rpc/xdr.h>

#define RUSERSPROC_NUM 1
#define RUSERSPROC_NAMES 2
#define RUSERSPROC_ALLNAMES 3
#define RUSERSPROG 100002
#define RUSERSVERS_ORIG 1
#define RUSERSVERS_IDLE 2
#define RUSERSVERS 2

#define MAXUSERS 100

/*
 * to maintain compatibility with Sun, we cannot use
 * the utmp structure from our local utmp.h files.
 * Instead, we are using the utmp structure from SunOS
 */
#define SUN_UT_LINE 8
#define SUN_UT_NAME 8
#define SUN_UT_HOST 16
struct utmp {
        char    ut_line[SUN_UT_LINE];             /* tty name */
        char    ut_name[SUN_UT_NAME];             /* user id */
        char    ut_host[SUN_UT_HOST];            /* host name, if remote */
        int     ut_time;                         /* time on */
};


struct utmparr {
	struct utmp **uta_arr;
	int uta_cnt;
};

struct utmpidle {
	struct utmp ui_utmp;
	unsigned ui_idle;
};

struct utmpidlearr {
	struct utmpidle **uia_arr;
	int uia_cnt;
};

_BEGIN_CPLUSPLUS
int xdr_utmparr __((XDR *, struct utmparr *));
int xdr_utmpidlearr __((XDR *, struct utmpidlearr *));
_END_CPLUSPLUS

#endif /*!_rpcsvc_rusers_h*/
