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
 *	@(#)$RCSfile: un.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1999/03/19 16:41:05 $
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	un.h	7.4 (Berkeley) 9/4/89
 *	Merged: un.h	7.7 (Berkeley) 6/28/90
 */

#ifndef	_SYS_UN_H_
#define	_SYS_UN_H_

#include <standards.h>

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#include <sys/socket.h>
#else
#include <sys/types.h>
#endif

/*
 * Definitions for UNIX IPC domain.
 */
#if	defined(_SOCKADDR_LEN) || defined(_KERNEL) || defined(_XOPEN_SOURCE_EXTENDED)
struct	sockaddr_un {
	unsigned char	sun_len;		/* sockaddr len including null */
	sa_family_t	sun_family;	/* AF_UNIX, sa_family is introduced by spec1170 */
	char	sun_path[104];		/* path name */
};
#else
struct	sockaddr_un {
	unsigned short	sun_family;		/* AF_UNIX */
	char	sun_path[104];		/* path name */
};
#endif

#ifdef _OSF_SOURCE
/* actual length of an initialized sockaddr_un */
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

#endif
