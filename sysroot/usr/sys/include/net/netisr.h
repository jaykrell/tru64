/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: netisr.h,v $
 * Revision 4.2.70.1  2003/09/23  21:52:33  Brian_Haley
 * 	Added a timer entry for Mobile IP nonces generation.
 *
 * Revision 4.2.62.2  2002/01/29  21:18:36  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.2.62.1  2001/12/17  20:54:33  Vladislav_Yasevich
 * 	Added Mobile IPv6 netisr timer entry.
 *
 * Revision 4.2.45.7  2000/03/17  15:13:03  Brian_Haley
 * 	NUMA replication work - netisrwakeupthreshold
 *
 * Revision 4.2.45.6  2000/03/15  18:52:41  John_Dustin
 * Removed obsolete NETISR_LOCK and netisr_slock; use
 * NETISR_LOCK_RAD and rad->netisr_slock instead.
 *
 * Revision 4.2.45.5  2000/01/26  22:29:31  John_Dustin
 * 	{** Forced Submit **}
 * 	Removed netisr_servers, netisr_table; replaced them with
 * 	rad->netisr_servers, rad->netisr_table.
 *
 * Revision 4.2.45.3  1999/12/03  22:08:06  John_Dustin
 * 	Move schednetisr_* macros into netisr.c, and more rad support
 *
 * Revision 4.2.45.2  1999/11/08  22:33:44  John_Dustin
 * 	change netisr_active_block to netisr_active.block
 *
 * Revision 4.2.45.1  1999/11/04  22:27:25  John_Dustin
 * 	Support for netisr threads per RAD (rad->netisr_servers)
 *
 * Revision 4.2.22.10  1999/01/20  19:07:47  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	4.2.34.4 **
 * 		** Merge revision:	4.2.43.3 **
 * 	 	** End **
 * 	[1999/01/20  19:05:33  Tony_Bono]
 *
 * Revision 4.2.43.3  1998/11/02  21:24:13  Tony_Bono
 * 	Fix to netisr->active to prevent race condition when scheduling
 * 	netisr at the same time as unscheduling netisr.
 * 	[1998/10/30  16:22:38  Tony_Bono]
 * 
 * Revision 4.2.43.2  1998/10/01  20:06:53  Tony_Bono
 * 	Removed most netisr locks by changing the meaning of
 * 	several fields in the netisr_active struct.
 * 	[1998/10/01  19:12:39  Tony_Bono]
 * 
 * Revision 4.2.22.9  1998/09/30  19:27:40  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL6:PTEV6OS_BL8 **
 * 		** Ancestor revision:	4.2.34.3 **
 * 		** Merge revision:	4.2.34.4 **
 * 	 	** End **
 * 	[1998/09/30  19:11:28  Tony_Bono]
 * 
 * Revision 4.2.34.4  1998/09/22  23:44:07  John_Dustin
 * 	removed additional fields from netisr struct so DECnet still works
 * 	[1998/09/21  22:30:11  John_Dustin]
 * 
 * Revision 4.2.22.8  1998/08/10  23:29:02  Tony_Bono
 * 	Addtional merge issues.
 * 	[1998/08/10  21:28:28  Tony_Bono]
 * 
 * Revision 4.2.22.7  1998/07/30  21:47:45  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.2.34.2 **
 * 		** Merge revision:	4.2.34.3 **
 * 	 	** End **
 * 	[1998/07/30  21:36:22  Tony_Bono]
 * 
 * Revision 4.2.34.3  1998/06/26  18:57:30  John_Dustin
 * 	Added schednetisr_netdev and schednetisr_isr scheduling macros
 * 	for threaded soft-interrupts and netisr callers with an isr ptr.
 * 	[1998/06/25  14:33:52  John_Dustin]
 * 
 * Revision 4.2.34.2  1998/03/31  22:26:56  Farrell_Woods
 * 	Back-port of NetRAIN
 * 	[1998/02/20  21:05:06  Farrell_Woods]
 * 
 * Revision 4.2.22.6  1998/01/21  21:15:03  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.2.18.3 **
 * 		** Merge revision:	4.2.30.2 **
 * 	 	** End **
 * 	[1998/01/21  20:48:53  Tony_Bono]
 * 
 * Revision 4.2.30.2  1997/10/09  23:22:22  Tony_Bono
 * 	Added netisrwakeupthreshold variable to allow for a second
 * 	netisr to run when the number of pending events exceeds
 * 	netisrwakeupthreshold.
 * 	[1997/10/09  15:39:52  Tony_Bono]
 * 
 * Revision 4.2.22.5  1997/09/30  13:13:46  Jack_McCann
 * 	IPv6 hooks:
 * 	- make NNETISR equal to NETISR_MAX
 * 	[1997/09/24  13:40:57  Jack_McCann]
 * 
 * Revision 4.2.22.4  1997/03/03  15:09:37  Paul_Grist
 * 	Casted queue types in schednetisr_nospl macros for kernel API
 * 	common proto project
 * 	[1997/02/27  19:48:20  Paul_Grist]
 * 
 * Revision 4.2.22.3  1997/02/19  19:52:44  Steve_Hurst
 * 	Added changes for NetRAIN support. This includes a new isr
 * 	routine netrain_isr.
 * 	[1997/02/12  16:12:33  Steve_Hurst]
 * 
 * Revision 4.2.22.2  1996/09/08  14:45:37  Ronald_Menner
 * 	Added NETISR_AAL for Native ATM API and NETISR_IPV6 for
 * 	future IPV6 hook
 * 	[1996/09/06  02:08:03  Ronald_Menner]
 * 
 * Revision 4.2.18.3  1995/04/27  23:07:38  atmproj_Peter_Schulter
 * 	submitted from shared sandbox
 * 	[1995/04/27  21:24:31  atmproj_Peter_Schulter]
 * 
 * Revision 4.2.18.2  1995/02/03  17:46:31  Jack_McCann
 * 	Late in V3.0 the (unused) NETISR_NS slot was taken for use by internal
 * 	routing messages.  Follow up by renaming NETISR_NS to NETISR_RTMSG.
 * 	[1995/02/03  15:44:18  Jack_McCann]
 * 
 * Revision 4.2.14.10  1994/05/16  21:02:06  Geraldine_Harter
 * 	Add NETISR_CTF define for X.25
 * 	[1994/05/13  10:41:40  Geraldine_Harter]
 * 
 * Revision 4.2.14.9  1994/04/25  20:28:37  Geraldine_Harter
 * 	Add NETISR_XXX defines for X.25
 * 	[1994/04/25  13:24:44  Geraldine_Harter]
 * 
 * Revision 4.2.14.8  1994/04/07  13:04:38  Ernie_Petrides
 * 	Implement schednetisr_nospl() to eliminate superfluous spl pairs
 * 	for callers which already have spl raised and change the netisr
 * 	spl level from splhigh() to splimp().  Incorporate Gerri Harter's
 * 	maxactive stat for network thread configuration analysis and the
 * 	definition for max number of netisr id's.
 * 	[1994/04/06  21:56:36  Ernie_Petrides]
 * 
 * Revision 4.2.14.7  1994/02/01  19:15:59  James_Woodward
 * 	convert netisr threads to use standard sleep/wakeup primitives.
 * 	[1994/02/01  18:31:33  James_Woodward]
 * 
 * Revision 4.2.14.6  1993/12/06  21:13:39  Geraldine_Harter
 * 	Shrink size of netisr stats fields.
 * 	[1993/12/06  21:09:55  Geraldine_Harter]
 * 
 * Revision 4.2.14.5  1993/11/15  23:48:41  John_Dustin
 * 	add netisr_li lockinfo support
 * 	[1993/10/27  16:54:49  John_Dustin]
 * 
 * Revision 4.2.14.4  1993/10/07  21:59:08  Geraldine_Harter
 * 	Merge with Sterling BL6.  Turns out to be a NOP except for including
 * 	revision logs of changes made prior to this merge (for completeness).
 * 	Note that some of these changes weren't made since they don't apply to
 * 	Gold.
 * 
 * 	Revision 4.2.10.4  1993/06/29  17:32:46  SJ_Lee
 * 	add #ifndef _NETISR_H_
 * 	[1993/06/29  17:05:59  SJ_Lee]
 * 
 * 	Revision 4.2.10.3  1993/06/28  16:28:49  Mary_Walker
 * 	moved the STREAMS isr defines as a performance improvement
 * 	[1993/06/24  18:46:01  Mary_Walker]
 * 
 * 	Revision 4.2.10.2  1993/05/12  21:09:01  Peter_Schulter
 * 	Check in for minor submit
 * 	[1993/05/12  15:07:45  Peter_Schulter]
 * 
 * 	Revision 4.2.8.3  1993/03/11  17:12:08  Peter_Schulter
 * 	Removed second NETISR_MB definition
 * 	[1993/03/11  17:11:45  Peter_Schulter]
 * 
 * 	Revision 4.2.8.2  1993/03/10  00:25:40  Peter_Schulter
 * 	Added constants needed by R$ STREAMS
 * 	[1993/03/10  00:24:30  Peter_Schulter]
 * 
 * Revision 4.2.14.3  1993/08/26  18:21:43  Julia_Fey
 * 	Token Ring premerge
 * 	[1993/08/25  21:33:39  Julia_Fey]
 * 
 * Revision 4.2.14.2  1993/06/25  21:16:47  Geraldine_Harter
 * 	Merge OSF1.2 changes.
 * 	[1993/06/25  20:27:22  Geraldine_Harter]
 * 
 * Revision 4.2.4.5  1993/01/08  18:01:49  Shashi_Mangalat
 * 	Modified for thread->wait_event data type change.  Wait channel
 * 	argument to assert_wait(), thread_wakeup*() and thread_sleep()
 * 	is a vm_offset_t now.
 * 	[93/01/08  16:38:07  Shashi_Mangalat]
 * 
 * Revision 4.2.4.4  92/06/25  09:34:44  Al_Delorey
 * 	From Silver: AG_BL8_1
 * 	[92/06/25  09:34:17  Al_Delorey]
 * 
 * Revision 4.2.6.2  92/06/23  19:04:34  devbld_gsf
 * 	First AG_BL8_1 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2.3.4  92/06/01  16:14:00  Benjamin_England
 * 	add NETISR_DLO, put it in unused slot so NETISR_MAX doesn't change
 * 	[92/05/15  16:07:27  Benjamin_England]
 * 
 * Revision 4.2.3.3  92/04/21  10:55:23  Ajay_Kachrani
 * 	bmerged
 * 
 * Revision 4.2.5.3  92/04/08  15:53:16  Ajay_Kachrani
 * 	Fix NETISR_MAX to (16) 1 more than the MAX isrs defined-a bug heather
 * 	mentioned..
 * 
 * Revision 4.2.5.2  92/04/06  17:17:45  Ajay_Kachrani
 * 	Define NETISR_OTHER for resolving conflict between dli and dlpi
 * 
 * Revision 4.2.3.2  92/02/28  14:59:08  Heather_Gray
 * 	Add WANDD and X.25 isr's. Reduce NETISR_MAX.
 * 	[92/02/20  22:32:23  Heather_Gray]
 * 
 * Revision 4.2  91/09/19  22:45:27  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: netisr.h,v $ $Revision: 4.2.70.1 $ (DEC) $Date: 2003/09/23 21:52:33 $
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
 * Copyright (c) 1980, 1986, 1989 Regents of the University of California.
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
 *	Base:	netisr.h	7.5 (Berkeley) 4/22/89
 *	Merged:	netisr.h	7.6 (Berkeley) 6/28/90
 */

#ifndef	_NET_NETISR_H
#define	_NET_NETISR_H

#ifndef REPLICATED
#define REPLICATED
#endif

/*
 * The networking code is in separate kernel threads or in software
 * interrupts. When running in threads, all events are delivered in
 * thread context, at splnet() or spl0() depending on lock configuration.
 * When running in software interrupts, events are delivered at splnet()
 * or splsoftclock().
 *
 * Clients of the isr framework use a "netisr" structure to
 * enqueue events and maintain active status. Some default
 * structures are defined globally (especially those used in
 * non-local contexts e.g. packet receive), others may be
 * registered with netisr_add(). See net/netisr.c.
 */

struct netisr {
	/* 64-byte cache alignment, read-mostly data */
	struct	netisr *next, *prev;	/* Link in {in}active isr list */
	void	(*isr)(void);		/* Isr to process input */
	struct	ifqueue *ifq;		/* Queue to receive packets, or NULL */
	struct	domain *dom;		/* Domain isr belongs to, or NULL */
	int	id;			/* Integer id */
	int pad[5];
	/* 64-byte cache alignment, statistics */
	int	active;			/* Softnet active count */
	int	pending;		/* Interrupt pending on queue */
	u_short	flags;			/* Flags */
	u_short use;  			/* use count for this netisr */
#define ISRF_INCHDR	1		/*   Include datalink */
	short	unit;			/* unit number for NETISR_NETDEV */
	short	pad_a;
	u_int	events;			/* Event count */
	u_int	wakeups;		/* Wakeup count */
	u_int	extras;			/* Wakeups with nothing to do */
	u_int	noserver;		/* No servers ready - NETISR_THREAD */
	u_int	block;			/* cnt threads blocked-NETISR_THREAD */
	u_int	maxactive;		/* max # concurrent threads active */
	int pad_b[6];
};

/*
 * Isr's may be used to deliver data to protocols, or simply events.
 */

#define NETISR_WILD	0	/* Copy of all packets */
#define NETISR_OTHER	1	/* Packets otherwise tossed (->dlpi)*/
#define	NETISR_ARP	2	/* ARP packets */
#define	NETISR_IP	3	/* IP packets */
#define	NETISR_RTMSG	4	/* Internal routing messages */
#define	NETISR_ISO	5	/* ISO packets */

#define	NETISR_MB	6	/* Mbuf/mblk event */
#define NETISR_STREAMS	7	/* Streams scheduler */
#define NETISR_ATMRTUPT	8	/* ATM IP route update */
#define NETISR_STRWELD	9	/* Streams "weld" */
#define NETISR_PFFAST	10	/* Sockets fasttimeout */
#define NETISR_PFSLOW	11	/* Sockets slowtimeout */
#define NETISR_IFSLOW	12	/* Sockets interface watchdog */
#define NETISR_ARPTMO	13	/* Sockets ARP timer */

#define NETISR_EVL	14	/* X.25 event logging */
#define NETISR_DLO	15	/* used for node 0 in DECnet */
#define	NETISR_DN	16	/* DECnet packets */
#define	NETISR_DLI	17	/* DLI packets */
#define	NETISR_LAT	18	/* LAT packets */
#define NETISR_WDD	19	/* WAN packets */
#define NETISR_NFSTMO	20	/* NFS timer */

#define NETISR_SRTMO	21	/* Token Ring S.R. timer */
#define NETISR_X25	22	/* X.25 packets */
#define NETISR_HDLC	23	/* HDLC packets */
#define NETISR_CTF	24	/* CTF messages */
#define NETISR_AAL	25	/* "Native" ATM API packets */
#define NETISR_IPV6	26	/* IPV6 packets */
#define NETISR_NETRAIN	27	/* Netrain failure detection code */
#define NETISR_NETDEV	28	/* network driver interrupt threads */
#define NETISR_MIP6TMO	29	/* Mobile IPv6 timer */
#define NETISR_MIP6NRTMO 30	/* Mobile IPv6 nonce regeneration timer */

#define NETISR_MAX	40	/* maximum acticipated number of netisr id's */

/* The number of preallocated isr's is arbitrary, but
 * should be large enough for the above predefines. */
#define NNETISR		NETISR_MAX

#ifdef	_KERNEL

#if	NETISR_THREAD

extern REPLICATED int netisrwakeupthreshold;

#else	/* NETISR_THREAD */

#ifndef __VMS
#if defined(vax) || defined(tahoe)
#include "machine/mtpr.h"
#define setsoftnet()    mtpr(SIRR, 12)
#else
extern void setsoftnet(void);
#endif
#else /* __VMS */
#define setsoftnet() 
#endif /* __VMS */

#endif	/* NETISR_THREAD */

#define schednetisr(num) do {	\
	int _s = splimp();	\
	schednetisr_nospl(num);	\
	splx(_s);		\
} while (0)

extern struct netisr **netisr_active_rad;

#if	NETSYNC_LOCK
/* Next 3 macros use the per-RAD netisr_slock, and protect that RAD only */
#define NETISR_LOCKINIT_RAD(rad) simple_lock_setup(&rad->netisr_slock, netisr_li)
#define NETISR_LOCK_RAD(rad)	simple_lock(&rad->netisr_slock)
#define NETISR_UNLOCK_RAD(rad)	simple_unlock(&rad->netisr_slock)
#else
#define NETISR_LOCKINIT_RAD()
#define NETISR_LOCK_RAD()
#define NETISR_UNLOCK_RAD()
#endif
#endif
#endif
