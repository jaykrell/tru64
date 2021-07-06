/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: icmp_var.h,v $
 * Revision 4.2.9.1  2003/06/06  18:31:59  Brian_Haley
 * 	Added icmp_rejectcodemask and icmp_redirecttimeout as external
 * 	replicated data.
 *
 * Revision 4.2.5.2  1999/02/26  20:09:21  Tony_Bono
 * 	Added the ability to read/zero the protocol stats
 * 	using the SIOCRD(Z)CTRS ioctls.
 * 	[1999/02/26  20:04:05  Tony_Bono]
 *
 * Revision 4.2.3.2  1993/06/29  17:55:08  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:44:32  SJ_Lee]
 * 
 * Revision 4.2  1991/09/19  22:46:27  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: icmp_var.h,v $ $Revision: 4.2.9.1 $ (DEC) $Date: 2003/06/06 18:31:59 $
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
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
 *	Base:	icmp_var.h	7.4 (Berkeley) 6/29/88
 *	Merged:	icmp_var.h	7.5 (Berkeley) 6/28/90
 */

#ifndef _ICMP_VAR_H_
#define _ICMP_VAR_H_

#include <netinet/ip_stat.h>

#if ( ICMP_MAXTYPE > ICMPSTAT_MAXTYPE )
#error ICMP_MAXTYPE changed and ip_stat not updated
#endif

#ifdef _KERNEL
extern struct	icmpstat icmpstat;
extern REPLICATED int icmp_rejectcodemask;
extern REPLICATED u_int icmp_redirecttimeout;
#endif

#endif
