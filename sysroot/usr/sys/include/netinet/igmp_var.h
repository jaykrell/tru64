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
 *	@(#)$RCSfile: igmp_var.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1999/02/26 20:09:23 $
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
 * Internet Group Management Protocol (IGMP),
 * implementation-specific definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 1.1
 */

#ifndef _IGMP_VAR_H_
#define _IGMP_VAR_H_

#include <netinet/ip_stat.h>

#ifdef _KERNEL
extern struct igmpstat igmpstat;

/*
 * Macro to compute a random timer value between 1 and (IGMP_MAX_REPORT_DELAY
 * * countdown frequency).  We generate a "random" number by adding
 * the total number of IP packets received, our primary IP address, and the
 * multicast address being timed-out.  The 4.3 random() routine really
 * ought to be available in the kernel!
 */
#define IGMP_RANDOM_DELAY(multiaddr)					\
	/* struct in_addr multiaddr; */					\
	( (u_int)						 	\
	  (ipstat.ips_total +						\
	   ntohl(IA_SIN(in_ifaddr)->sin_addr.s_addr) +			\
	   ntohl((multiaddr).s_addr)					\
	  )								\
	  % (IGMP_MAX_HOST_REPORT_DELAY * PR_FASTHZ) + 1		\
	)

ndecl_lock_data(extern, igmp_lock)
#define IGMP_LOCKINIT() ulock_setup(&igmp_lock, igmp_li, TRUE)
#define IGMP_LOCK_DECL()     NETSPL_DECL(_igs)
#define IGMP_LOCK()     { NETSPL(_igs,net); ulock_write(&igmp_lock); }
#define IGMP_UNLOCK()   { ulock_done(&igmp_lock); NETSPLX(_igs); }

#endif

#endif
