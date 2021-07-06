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
 *	@(#)$RCSfile: syslimits.h,v $ $Revision: 4.3.12.2 $ (DEC) $Date: 2000/09/28 16:40:11 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef	_SYS_SYSLIMITS_H_
#define _SYS_SYSLIMITS_H_

#define	ARG_MAX		38912	/* max bytes for an exec function */
#if	defined(multimax) || defined(balance)
#define CHILD_MAX	100     /* max processes per user */
#else	/* defined(multimax) || defined(balance) */
#define CHILD_MAX	256	/* max processes per user */
#endif	/* defined(multimax) || defined(balance) */
#define	LINK_MAX	65533	/* max file link count */
#define _LINK_MAX_V3	32767	/* V.3 UFS max hardlink count.  Use pathconf()
				 * to get the correct value;  different file
				 * system use different LINK_MAX's.
				 */
#define	MAX_CANON	255	/* max bytes in terminal canonical input line */
#define	MAX_INPUT	512	/* max bytes in terminal input */
#define	NAME_MAX	255	/* max number of bytes in a file name */
#define	NGROUPS_MAX	32	/* max number of supplemental group id's */
#define SSIZE_MAX       LONG_MAX /* Max value fitting ssize_t (a long) */
#define TZNAME_MAX	255

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) 
#define	OPEN_MAX	64	/* max open files per process - OBSOLETE, sysconf() interface should be used */
#endif

#define	PATH_MAX	1023	/* max number of bytes in pathname */
# if !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE < 500)
#define	PIPE_BUF	4096	/* max number of bytes for atomic pipe writes */
#endif /* !_XOPEN_SOURCE || _XOPEN_SOURCE<500 */
#endif	/* _SYS_SYSLIMITS_H_ */
