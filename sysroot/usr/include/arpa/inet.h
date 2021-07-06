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
 *	@(#)$RCSfile: inet.h,v $ $Revision: 4.2.19.1 $ (DEC) $Date: 1999/12/17 19:32:51 $
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
 * Copyright (c) 1983 Regents of the University of California.
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

/*
 * External definitions for
 * functions in inet(3N)
 */
#include <netinet/in.h>

#if defined (_XOPEN_SOURCE_EXTENDED) && !defined (_OSF_SOURCE)
#include <machine/endian.h>
#endif

_BEGIN_CPLUSPLUS
extern in_addr_t	inet_addr	__((const char *));
extern int		inet_aton	__((const char *, struct in_addr *));
extern in_addr_t        inet_lnaof	__((struct in_addr));
extern struct in_addr	inet_makeaddr	__((in_addr_t, in_addr_t));
extern char *		inet_neta	__((unsigned long, char *, size_t));
extern in_addr_t	inet_netof	__((struct in_addr));
extern in_addr_t	inet_network	__((const char *));
extern char *           inet_net_ntop	__((int, const void *, int, char *, size_t));
extern int		inet_net_pton   __((int, const char *, void *, size_t));
extern char *           inet_cidr_ntop	__((int, const void *, int, char *, size_t));
extern int		inet_cidr_pton   __((int, const char *, void *, int *));
extern char *           inet_ntoa       __((struct in_addr));
extern int	        inet_pton       __((int, const char *, void *));
extern const char *     inet_ntop       __((int, const void *, char *, size_t));
extern unsigned int	inet_nsap_addr	__((const char *,unsigned char *, int));
extern char *		inet_nsap_ntoa	__((int, const unsigned char*, char *));
_END_CPLUSPLUS

#endif	/* _ARPA_INET_H */
