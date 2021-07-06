/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: in_pcb.h,v $
 * Revision 4.2.97.2  2003/10/15  21:11:04  Vladislav_Yasevich
 * 	IPv6 Advanced API update to RFC 3542
 * 	- Added support for per inpcb path mtu discovery
 * 	- Added inpcb flags for the new IPv6 options.
 *
 * Revision 4.2.97.1  2003/03/11  14:30:27  Vladislav_Yasevich
 * Changed placement of inp_uladdr (code review comments).
 * 	[2003/03/07  19:28:24  Vladislav_Yasevich]
 *
 * 	Fix for QAR 91711 "UDP broadcast source is not allowed per RFC 1122,
 * 	compliance failure".
 * 	[2003/02/27  22:51:05  Vladislav_Yasevich]
 *
 * Revision 4.2.84.3  2002/01/31  19:44:37  John_Dustin
 * 	Fixed the inpcb structure padding to accurately reflect the
 * 	cache alignment (no holes).
 *
 * Revision 4.2.84.2  2002/01/29  21:18:59  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.2.84.1  2001/12/17  20:55:05  Vladislav_Yasevich
 * 	Merge of the Advanced API implementations from wildcat.classic
 *
 * Revision 4.2.81.3  2001/06/29  18:48:44  Farrell_Woods
 * 	Add TOS and TTL to the raw_inpcb structure so that these
 * 	can be set on raw sockets via setsockopt().
 *
 * Revision 4.2.81.2  2001/02/27  15:14:53  Vladislav_Yasevich
 * 	Added the definition for INP_IPV6_INHERIT.  These are the inpcb
 * 	flags that should be inherited by child sockets.
 *
 * Revision 4.2.81.1  2000/12/11  16:26:39  Vladislav_Yasevich
 * 	Defined flags used by IPV6_IPV6ONLY socket option (added
 * 	for QARs 83845, 83732).
 *
 * Revision 4.2.77.7  2000/06/23  22:42:45  Tony_Bono
 * 	Change to create multiple udp input queues based on
 * 	the local port number. Unbound udp inps created by
 * 	in_pcballoc will not be enqueued on a head
 * 	until bind at which point the inp will be
 * 	added to the correct udb list based on the
 * 	local port. The present design uses a lock
 * 	within the udb struct. To aquire the lock a process
 * 	determines the correct udb queue without a lock
 * 	preventing the dynamic resizing of the udb list.
 *
 * Revision 4.2.77.6  2000/03/24  23:17:45  Tony_Bono
 * 	Changes to reduce lock contention by delaying dequeue
 * 	of inp from the fast and slow lists.
 *
 * Revision 4.2.77.5  2000/03/17  15:13:16  Brian_Haley
 * 	NUMA replication work - ipport_userreserved, tcbqNum
 *
 * Revision 4.2.77.4  1999/12/17  03:16:54  Tony_Bono
 * 	Added per rad fast and slow timer support.
 *
 * Revision 4.2.77.3  1999/12/07  23:21:01  Tony_Bono
 * 	Improved scaling of tcp_slowtimo
 * 	Added per rad tcbinit support.
 *
 * Revision 4.2.77.2  1999/11/30  21:08:04  Brian_Haley
 * 	Removed inpcb struct long_pad_b[1] to put it into in_route struct.
 *
 * Revision 4.2.77.1  1999/10/18  20:21:09  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 4.2.55.8  1999/09/08  19:13:14  Vladislav_Yasevich
 * 	Changed inp_ttl and inp_tos to be of type u_char.  PTR 52-1-239.
 *
 * Revision 4.2.55.7  1999/06/08  18:09:47  Jack_McCann
 * 	IPv6 EAK X6.3 merge to Steel BL23
 * 	- add inp_moptions6, inp_cksumoff, inp_txif6, inp_txopt, inp_rxopt
 * 	- add INP_HDRINCL, INP_IPV6_PKTINFO, INP_IPV6_HOPLIMIT, INP_IPV6_HOPOPTS
 * 	  INP_RXHDR, INP_IPV6_DSTOPTS, INP_IPV6_RTHDR, INP_IPV6_PASSUP_OPTDATA
 * 	[1999/06/08  15:52:32  Jack_McCann]
 *
 * Revision 4.2.33.18  1999/03/30  23:47:04  Tony_Bono
 * 	Cache block changes.
 * 	[1999/03/30  23:37:26  Tony_Bono]
 *
 * Revision 4.2.33.17  1999/03/25  19:58:39  Brian_Haley
 * 	Changed raw_inpcb to have a struct in_route since we now
 * 	have route timestamps (qar 69411).
 * 	[1999/03/10  23:18:01  Brian_Haley]
 * 
 * Revision 4.2.33.16  1999/03/04  21:08:24  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTFCOS_BL3:PTFCOS_BL5 **
 * 		** Ancestor revision:	4.2.48.4 **
 * 		** Merge revision:	4.2.62.2 **
 * 	 	** End **
 * 	[1999/03/04  20:58:03  Tony_Bono]
 * 
 * Revision 4.2.33.15  1999/02/26  20:09:24  Tony_Bono
 * 	Moved lock to end of inp just incase the struct is
 * 	refed by a usr application that doesn't define _KERNEL
 * 	[1999/02/26  20:04:12  Tony_Bono]
 * 
 * Revision 4.2.62.2  1999/01/08  20:45:33  Tony_Bono
 * 	Added flag for use by tcp_slowtimo.
 * 	Added available flag that can be used to keep inp on active
 * 	list.
 * 	[1999/01/08  19:44:54  Tony_Bono]
 * 
 * Revision 4.2.33.14  1998/12/02  23:10:31  Jack_McCann
 * 	IPv6 hooks:
 * 	- include in_route.h
 * 	- change inp_route from struct route to struct in_route
 * 	- change inp_faddr/inp_laddr from struct in_addr to struct in6_addr
 * 	- add rinp_reserved fields to raw_inpcb
 * 	- remove inpcb inp_ip field
 * 	- add inp_tos, inp_ttl, inp_pcksum, inp_proto, inp_fflow, inp_lflow,
 * 	  inp_netlayer, inp_api, and inpcb reserved fields
 * 	- add declarations for zeroin6_addr, sockaddr_in6_init
 * 	[1998/11/24  21:51:06  Jack_McCann]
 * 
 * Revision 4.2.55.4  1998/09/15  18:08:35  Eric_Wong
 * 	RFC2292 Advanced Sockets API for IPv6 changes
 * 	- add inp_cksumoff, inp_txopt and inp_rxopt
 * 	- add new INP_IPV6_xxx flags for ipv6 options
 * 	[1998/09/15  15:03:02  Eric_Wong]
 * 
 * Revision 4.2.55.3  1998/08/11  18:45:15  Geraldine_Harter
 * 	Add support for rawip6pcb to the IN*_LOCKINIT macros
 * 	[1998/06/25  15:17:46  Geraldine_Harter]
 * 
 * Revision 4.2.33.13  1998/08/06  00:37:47  Tony_Bono
 * 	ptev6 to steel merge cleanup
 * 	[1998/08/05  22:04:13  Tony_Bono]
 * 
 * Revision 4.2.33.12  1998/07/30  21:47:53  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.2.48.2 **
 * 		** Merge revision:	4.2.48.4 **
 * 	 	** End **
 * 	[1998/07/30  21:36:40  Tony_Bono]
 * 
 * Revision 4.2.33.11  1998/05/20  22:29:50  John_Dustin
 * 	replace INP_PORT_CACHING with INP_PORT_CACHED to fix build error
 * 	[1998/05/20  22:25:26  John_Dustin]
 * 
 * Revision 4.2.33.10  1998/05/19  13:47:03  Larry_Cohen
 * 	Two new pcb flags:
 * 		INP_SRC_STATIC - indicates the local address was set in a bind call and should
 * 			be overwritten by subsequent udp connects.
 * 		INP_PORT_NOUNLOCK - it is not safe to unlock the protocol head lock. used by
 * 			cluster alias.
 * 	[1998/05/19  13:45:08  Larry_Cohen]
 * 
 * Revision 4.2.33.9  1998/05/14  22:39:39  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.2.37.3 **
 * 		** Merge revision:	4.2.48.2 **
 * 	 	** End **
 * 	[1998/05/14  22:16:36  John_Dustin]
 * 
 * Revision 4.2.48.4  1998/05/11  22:02:12  Tony_Bono
 * 	Changed the refcnt in the inp to an atomic_incl instead of a lock
 * 	add and unlock.
 * 	[1998/05/11  18:55:51  Tony_Bono]
 * 
 * Revision 4.2.48.3  1998/05/01  22:22:20  Tony_Bono
 * 	Change to support the reuse of inps that are in time_wait when
 * 	a new incoming syn is received.
 * 	[1998/04/30  22:32:36  Tony_Bono]
 * 
 * Revision 4.2.48.2  1998/03/31  21:14:36  Tony_Bono
 * 	Added multiple tcb queues to allow for parallel tcp_input processing.
 * 	This change and the modification to the netisr and ipintr will allow
 * 	for better scaling capabilities for smp systems.
 * 	[1998/03/31  19:58:40  Tony_Bono]
 * 
 * Revision 4.2.33.8  1997/07/24  14:48:27  Larry_Cohen
 * 	remove cluster alias definitions as a result of the TCP sequence number hook.
 * 	[1997/07/24  14:13:23  Larry_Cohen]
 * 
 * Revision 4.2.33.7  1997/07/15  16:18:41  Larry_Cohen
 * 	Cluster alias hooks added.
 * 	[1997/07/14  17:07:35  Larry_Cohen]
 * 
 * Revision 4.2.33.6  1997/06/04  17:55:25  Jack_McCann
 * 	- remove INP_NOPMTUDISC
 * 	[1997/05/28  15:30:28  Jack_McCann]
 * 
 * Revision 4.2.33.5  1997/04/24  18:26:04  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.2.37.2 **
 * 		** Merge revision:	4.2.37.3 **
 * 	 	** End **
 * 	merge
 * 	[1997/04/24  18:06:35  Tony_Bono]
 * 
 * Revision 4.2.37.3  1997/02/25  19:51:27  Ajay_Kachrani
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTAOS_KITBLD:PTCOS_NIGHTLY **
 * 		** Ancestor revision:	4.2.16.5 **
 * 		** Merge revision:	4.2.37.2 **
 * 	 	** End **
 * 	[1997/02/12  18:23:01  Ajay_Kachrani]
 * 
 * 	Added Transparent PROXY hooks
 * 	[1997/02/12  18:17:01  Ajay_Kachrani]
 * 
 * Revision 4.2.33.4  1997/02/06  02:46:35  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 **
 * 		** Ancestor revision:	4.2.16.5 **
 * 		** Merge revision:	4.2.37.2 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/06  02:30:39  Tony_Bono]
 * 
 * Revision 4.2.37.2  1996/11/22  22:10:40  Tony_Bono
 * 	hint code support
 * 	[1996/11/22  22:01:54  Tony_Bono]
 * 
 * Revision 4.2.33.3  1996/11/19  21:47:33  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.16.5 **
 * 		** Merge revision:	4.2.33.2 **
 * 	 	** End **
 * 	final pass of web server package including hint,
 * 	 quick bind and tcp syn queue changes
 * 	[1996/11/14  16:43:48  Tony_Bono]
 * 
 * 	merge into steel
 * 	[1996/08/02  06:01:34  Tony_Bono]
 * 
 * 	Added changes suggested in code review
 * 	[1996/07/27  00:56:26  Tony_Bono]
 * 
 * 	tcp timer changes for large web servers
 * 	[1996/05/31  20:43:39  Tony_Bono]
 * 
 * Revision 4.2.31.2  1996/10/10  18:14:20  Tony_Bono
 * 	hint patch initial rev 10-10-96
 * 
 * Revision 4.2.33.2  1996/09/25  18:47:20  Brian_Haley
 * 	Added C++ forward declaration
 * 	[1996/09/24  20:08:54  Brian_Haley]
 * 
 * Revision 4.2.16.5  1995/11/15  20:33:24  John_Dustin
 * 	add INP_PROXY as hook for IBG Firewall product
 * 	[1995/11/09  16:34:05  John_Dustin]
 * 
 * Revision 4.2.16.4  1995/10/04  21:16:34  Jack_McCann
 * 	Add INPLOOKUP_LOCKHELD flag (qar 38339).
 * 	[1995/10/04  18:40:48  Jack_McCann]
 * 
 * Revision 4.2.16.3  1995/09/25  19:49:19  Jack_McCann
 * 	inpcb hash lookup support (qar 34848):
 * 	- add inp_hb field to inpcb
 * 	- define inpcb hash bucket structure
 * 	[1995/09/22  19:43:40  Jack_McCann]
 * 
 * Revision 4.2.16.2  1995/04/28  16:44:12  Jack_McCann
 * 	PMTU - add INP_NOPMTUDISC flag
 * 	[1995/04/21  20:44:56  Jack_McCann]
 * 
 * Revision 4.2.11.8  1994/03/18  21:53:58  Ernie_Petrides
 * 	Convert locking calls for *.inp_lock and to use the ulock_*
 * 	versions to allow for call patch-out in lockmode 0.
 * 	[1994/03/17  00:30:18  Ernie_Petrides]
 * 
 * Revision 4.2.11.7  1994/01/03  19:16:42  John_Dustin
 * 	use simple_lock_terminate for inp_rc_lock
 * 	[1993/12/10  14:18:02  John_Dustin]
 * 
 * 	add INPCB_LOCKTERMINATE macro definition
 * 	[1993/12/09  23:18:36  John_Dustin]
 * 
 * Revision 4.2.11.6  1993/12/06  22:10:52  John_Dustin
 * 	split inp_head lock into inp_tcphead and inp_udphead
 * 	[1993/12/06  19:19:24  John_Dustin]
 * 
 * 	add ndecl_lock_info's for inpcb split, etc.
 * 	[1993/11/22  21:57:35  John_Dustin]
 * 
 * Revision 4.2.11.5  1993/11/11  18:21:22  Geraldine_Harter
 * 	Fix INPCB_ISLOCKED() macro - test that lock is held by caller
 * 	(instead of testing only that the lock is held).
 * 	[1993/11/03  20:49:42  Geraldine_Harter]
 * 
 * Revision 4.2.11.4  1993/10/07  17:54:04  John_Dustin
 * 	sterling to gold merge
 * 	[1993/10/04  18:47:02  John_Dustin]
 * 
 * Revision 4.2.11.3  1993/08/03  16:35:12  Ajay_Kachrani
 * 	Convert n/w locks to new lock stats using LI
 * 	[1993/07/23  14:34:06  Ajay_Kachrani]
 * 
 * 	Convert n/w locks to new lock stats using LI
 * 	[1993/07/22  19:37:36  Ajay_Kachrani]
 * 
 * Revision 4.2.7.2  1993/05/16  21:19:56  Heather_Gray
 * 	Add member to both inet pcb and raw inet pcb structures which
 * 	points to IP multicast options.
 * 	[1993/05/04  23:01:12  Heather_Gray]
 * 
 * 	Add pointer to IP Multicast options to inpcb.
 * 	[1993/04/12  00:49:00  Heather_Gray]
 * 
 * Revision 4.2.6.2  1993/05/14  19:28:44  John_Dustin
 * 	fix nested comment warnings
 * 	[1993/05/05  18:19:42  John_Dustin]
 * 
 * Revision 4.2  1991/09/19  22:47:04  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: in_pcb.h,v $ $Revision: 4.2.97.2 $ (DEC) $Date: 2003/10/15 21:11:04 $
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
 *	Base:	in_pcb.h	7.4 (Berkeley) 4/22/89
 *	Merged:	in_pcb.h	7.6 (Berkeley) 6/28/90
 */

#ifndef _IN_PCB_H_
#define _IN_PCB_H_

#ifdef __cplusplus
extern "C" {
/* forward decls for C++ */
struct	ip_moptions;	/* just a stub, only defined in kernel */
struct __inpcb_hashbucket;
#endif

#include <netinet/in_route.h>

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
/* 64-byte alignment */
	struct	inpcb *inp_next;	/* pointers to other pcb's */
	struct  inpcb *inp_prev;
	struct	inpcb *inp_head;	/* pointer to head of chain */
	int	inp_api;		/* AF_INET or AF_INET6 socket */
	int pad_b[1];
	struct	socket *inp_socket;	/* back pointer to socket */
	caddr_t	inp_ppcb;		/* pointer to per-protocol pcb */
	int	inp_flags;		/* generic IP/datagram flags */
#ifndef  __VMS
	int pad_a[3];
#else /* __VMS */
	int ovms_pad_a[9];
#endif /* __VMS */
/* 64-byte alignment */
	struct	in_route inp_route;	/* placeholder for routing entry */
#ifdef  __VMS
	int ovms_pad_b[5];
#endif /* __VMS */
/* 64-byte alignment */
	struct	mbuf *inp_options;	/* IP options */
	struct	ip_moptions *inp_moptions; /* IP multicast options */
	struct	__inpcb_hashbucket *inp_hb; /* hash bucket (may be null) */
	/* The following 2 fields can only be used by the timer process */
	struct	inpcb *inp_fasttimo_next ; /* list of inp to process for fast timers */
	struct	inpcb *inp_slowtimo_next ; /* list of inp to process for slow timers */
	struct	inpcb *inp_slowtimo_list ; /* quantum list of inp to process for slow timers */
	struct	inpcb *inp_resize_next;	/* pointer to the next entry on the resize list */
	long 	inp_slowref;		/* ref count to track slowtimer signal events */
#ifdef  __VMS
	int ovms_pad_c[8];
#endif	/* __VMS */
/* 64-byte alignment */
	u_char	inp_tos;		/* type_of_service/class */
	u_char	inp_ttl;		/* time_to_live/hop_limit */
	u_short	inp_pcksum;		/* partial checksum */
	int	inp_proto;		/* protocol type */
        int     inp_fflow;              /* flow to destination */
        int     inp_lflow;              /* from from destination */
	int	inp_netlayer;		/* IPv4 (AF_INET) or IPv6 (AF_INET6) */
	int	inp_refcnt;		/* reference count */
		/* move these next 4 to the end for dbx readability */
	u_short	inp_fport;		/* foreign port */
	u_short	inp_lport;		/* local port */
	int pad_c[1];
	struct	in6_addr inp_faddr;	/* foreign host table entry */
	struct	in6_addr inp_laddr;	/* local host table entry */
#ifdef  __VMS
	int ovms_pad_d[1];
#endif	/* __VMS */
/* 64-byte alignment */
	struct	ip6_moptions *inp_moptions6; /* IPv6 multicast options */
	struct	in6_ifnet *inp_txif6;	/* interface of linkscope laddr/faddr */
	struct	in6optinfo *inp_txopt;	/* sticky options for xmit */
	struct	mbuf *inp_rxopt;	/* sticky option data rcv'ed */
	int	inp_cksumoff;		/* checksum offset, -1 is disable */
	struct in_addr inp_uladdr;	/* laddr when INP_*CAST_LADDR is set */
	struct	rad *inp_rad;		/* rad pcb allocated on */
	void	*inp_quantum_ptr;
	int	inp_pmtud_policy;	/* PMTUD policy: init to pmtu_enabled */
	int	inp_reserved[1];	/* reserved for future use */
/* 64-byte alignment */
#if	defined(_KERNEL) && NETSYNC_LOCK
	lock_data_t inp_lock;		/* structure lock */
	simple_lock_data_t inp_rc_lock;	/* refcnt lock */
#endif
};

/* flags in inp_flags: */
#define	INP_RECVOPTS		0x01	/* receive incoming IP options */
#define	INP_RECVRETOPTS		0x02	/* receive IP options for reply */
#define	INP_RECVDSTADDR		0x04	/* receive IP dst address */
#define INP_PROXY		0x20	/* transparent proxy enabled */
#define INP_SRC_STATIC          0x40    /* laddr set in bind ... dont overwrite */
#define INP_DONTDETACH		0x80	/* Don't detach this from head during in_pcbdetach */
#define	INP_CONTROLOPTS		(INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR|INP_PROXY)

/* cluster alias flags */
#define INP_PORT_LOCKED		0x100	/* port allocated to a cluster alias */
#define INP_PORT_CACHED		0x200	/* port is cached locally but not assigned */
#define INP_PORT_REGISTERED	0x400	/* indicates socket is eligible for cluster data
					   reception */
#define INP_PORT_NOUNLOCK	0x800	/* not safe to unlock proto head lock */
#define INP_CLUA_BITS (INP_PORT_LOCKED|INP_PORT_REGISTERED)

#define INP_AVAILABLE		0x1000	/* inp available for reuse */
#define INP_TIMOREQ		0x2000	/* tcp slowtimo processing required. */
#define	INP_HDRINCL		0x4000	/* header included for raw output */
#define	INP_RXHDR		0x8000	/* prepend hdr info on receive */
#define INP_IPV6_PKTINFO        0x10000	/* receive in6_pktinfo */
#define INP_IPV6_HOPLIMIT       0x20000	/* receive hop limit */
#define INP_IPV6_HOPOPTS        0x40000	/* receive hop options */
#define INP_IPV6_DSTOPTS        0x80000	/* receive destination options */
#define INP_IPV6_RTHDR          0x100000 /* receive routing header */

#define INP_PROTO_TCP		0x200000 /* inp is used by tcp */
#define INP_PROTO_UDP		0x400000 /* inp is used by udp */
#define INP_IPV6_IPV6ONLY	0x800000 /* inp only support IPv6 protocol */
#define INP_IPV6_RTHDRDSTOPTS   0x1000000 /* receive dest opts before
					   * routing header */
#define INP_BCAST_LADDR		0x2000000 /* laddr is bcast */
#define INP_MCAST_LADDR		0x4000000 /* laddr is mcast */
#define INP_IPV6_TCLASS		0x8000000 /* receive traffic class */
#define INP_IPV6_RECVMTU	0x10000000 /* app receives pmtud data */

#define	INP_IPV6_PASSUP_OPTDATA	(INP_IPV6_PKTINFO | INP_IPV6_HOPLIMIT | \
				 INP_IPV6_DSTOPTS | INP_IPV6_HOPOPTS | \
				 INP_IPV6_RTHDR | INP_IPV6_RTHDRDSTOPTS | \
				 INP_IPV6_TCLASS)

#define INP_IPV6_INHERIT	(INP_IPV6_PASSUP_OPTDATA | INP_IPV6_IPV6ONLY)

/* inpcb PMTU Discovery policy - for now policy is only applied to IPv6
 * XXX - do we want to apply the same policy to IPv4
*/
#define INP_PMTUD_POLICY_DEFAULT	-1	/* use system default */
#define INP_PMTUD_POLICY_ENABLE		1	/* enable for all packets */
#define INP_PMTUD_POLICY_DISABLE	0	/* disable for all packets */

struct __inpcb_hashbucket {
	struct inpcb *inphb_first; /* first inpcb in hash bucket */
	struct inpcb *inphb_last;  /* last inpcb in hash bucket */
	int    inphb_delack ;	   /* delack flag indicates something on list might need delack */
	int    inphb_slowtimerchange ;    /* someone has changed one of the slow timers */
	int    inphb_slowtimerlastrunat ; /* the last time the slow timer ran */
	int    inphb_slowtimernextrun ;   /* the next time the slow timer routine should run */
};

#ifdef sotorawcb
/*
 * Common structure pcb for raw internet protocol access.
 * Here are internet specific extensions to the raw control block,
 * and space is allocated to the necessary sockaddrs.
 */
struct raw_inpcb {
	struct	rawcb rinp_rcb;	/* common control block prefix */
	struct	mbuf *rinp_options;	/* IP options */
	int	rinp_flags;		/* flags, e.g. raw sockopts */
#define	RINPF_HDRINCL		0x1	/* user supplies entire IP header */
	struct	sockaddr_in rinp_faddr;	/* foreign address */
	struct	sockaddr_in rinp_laddr;	/* local address */
	struct	in_route rinp_route;	/* placeholder for routing entry */
	struct	ip_moptions *rinp_moptions; /* IP multicast options */
        u_char  rinp_ttl;               /* time to live */
        u_char  rinp_tos;               /* type of service */
        u_char  rinp_reserved4[6];     /* reserved for future use */
	u_long	rinp_reserved3;		/* reserved for future use */
	u_long	rinp_reserved2;		/* reserved for future use */
	u_long	rinp_reserved1;		/* reserved for future use */
};
#endif

#define	INPLOOKUP_WILDCARD	1
#define	INPLOOKUP_SETLOCAL	2
#define	INPLOOKUP_USECACHE	4
#define	INPLOOKUP_LOCKHELD	8
#define	INPLOOKUP_AVAILABLE	0x10
#define	INPLOOKUP_LOCALRAD	0x20
#define INPLOOKUP_V6ONLY	0x40

#define	sotoinpcb(so)		((struct inpcb *)(so)->so_pcb)
#define	sotorawinpcb(so)	((struct raw_inpcb *)(so)->so_pcb)

#ifdef _KERNEL

#ifndef REPLICATED
#define REPLICATED
#endif

extern CONST struct in_addr	zeroin_addr;
extern CONST struct in6_addr	zeroin6_addr;
extern CONST struct sockaddr_in6 sockaddr_in6_init;
extern REPLICATED int ipport_userreserved;

#if	NETSYNC_LOCK
/*
 * The INPCB lock is used to protect each connection on the system.
 *  It implicitly also protects the TCPCB or UDPCB control block
 *  it points to as well.  The socket it points to is protected
 *  separately. Note, however, that in the present code the INPCB
 *  lock is always taken after the socket lock (and never without),
 *  and so is redundant. For this reason the locks are present only
 *  if debugging. Additional parallelism may be achoeved with them
 *  in the future.
 *
 * Taking the INPCB lock is a pain because the structure is linked onto
 *  a global (e.g. UDP or TCP) chain.  Holding the INPCB lock doesn't
 *  mean that someone else can't dequeue themselves from the chain;
 *  i.e. the "next" and "prev" pointers are protected by the global
 *  lock. For this reason the inpcb is reference counted.
 *
 * The lock hierarchy is socket first, inpcb second. A reference on an
 *  inpcb also protects the attached socket. Reference counts are
 *  incremented with the pcb head locked (for read or write). When
 *  the reference count goes to 0, the inpcb is deallocated, and
 *  sofree() is called. However, because sockets may live on from
 *  file table references, the socket unlock is left to the caller.
 *  
 * The chain heads are locked for write recursively to alleviate
 *  the situation in in_pcb.c and unconnected udp sends.
 */
extern struct inpcb tcb[] ;
extern REPLICATED int tcbqNum ;
extern struct inpcb *udb;
extern REPLICATED int udbqNum ;
extern struct inpcb rawip6pcb;
ndecl_lock_info(extern, inp_tcphead_li)
ndecl_lock_info(extern, inp_tcp_rc_li)
ndecl_lock_info(extern, inp_udphead_li)
ndecl_lock_info(extern, inp_udp_rc_li)
ndecl_lock_info(extern, inp_rawip6_li)
ndecl_lock_info(extern, inp_rawip6_rc_li)
#define	INPCB_LOCKINIT(inp) \
	ulock_setup(&((inp)->inp_lock), \
		    ((((inp)->inp_flags) & INP_PROTO_TCP) != 0 ) ? inp_tcphead_li : \
		     ((((inp)->inp_flags) & INP_PROTO_UDP) != 0 ) ? inp_udphead_li : \
		     (((inp)->inp_head) == &rawip6pcb) ? inp_rawip6_li : NULL, \
		    TRUE)
#define INPCB_LOCKTERMINATE(inp) { \
	ulock_terminate(&(inp)->inp_lock); \
}
#if NETSYNC_LOCKTEST
#define	INPCB_LOCK(inp)		ulock_write(&((inp)->inp_lock))
#define	INPCB_UNLOCK(inp)	ulock_done(&((inp)->inp_lock))
#define INPCB_ISLOCKED(inp)	(lockmode == 0 || \
					lock_holder(&((inp)->inp_lock)))
#else
#define	INPCB_LOCK(inp)
#define	INPCB_UNLOCK(inp)
#define INPCB_ISLOCKED(inp)	1
#endif
#define INHEAD_READ_LOCK(head)	ulock_read(&((head)->inp_lock))
#define INHEAD_TRY_READ_LOCK(head) ulock_try_read(&((head)->inp_lock))
#define	INHEAD_READ_UNLOCK(head) ulock_done(&((head)->inp_lock))
#define INHEAD_WRITE_LOCK(head)	{ \
	ulock_write(&((head)->inp_lock)); \
	ulock_set_recursive(&((head)->inp_lock)); \
}
#define	INHEAD_WRITE_UNLOCK(head) { \
	ulock_clear_recursive(&((head)->inp_lock)); \
	ulock_done(&((head)->inp_lock)); \
}
#define INHEAD_LOCKINIT(head) \
	ulock_setup(&((head)->inp_lock), \
		    ((((head)->inp_flags) & INP_PROTO_TCP) != 0 ) ? inp_tcphead_li : \
		    ((((head)->inp_flags) & INP_PROTO_UDP) != 0 ) ? inp_udphead_li : \
		    ((head) == &rawip6pcb) ? inp_rawip6head_li : NULL, \
		    TRUE)

/*
 * Locks and operations on refcounts.
 */
#define	INPCBRC_LOCKINIT(inp)
#define	INPCBRC_LOCK(inp)
#define	INPCBRC_UNLOCK(inp)

#define	INPCBRC_REF(inp) { \
	atomic_incl( &(inp)->inp_refcnt) ; \
}

#define	INPCBRC_UNREF(inp) { \
	if (atomic_decl(&(inp)->inp_refcnt) == 1) { \
		in_pcbfree(inp); \
	} \
}

#else	/* !NETSYNC_LOCK */
#define	INPCB_LOCK(inp)
#define	INPCB_UNLOCK(inp)
#define	INPCB_LOCKINIT(inp)
#define INPCB_LOCKTERMINATE(inp)
#define	INPCB_ISLOCKED(inp)	1
#define INHEAD_READ_LOCK(head)
#define INHEAD_TRY_READ_LOCK(head)  0		/* Head lock was not acquired */
#define INHEAD_WRITE_LOCK(head)
#define	INHEAD_READ_UNLOCK(head)
#define	INHEAD_WRITE_UNLOCK(head)
#define INHEAD_LOCKINIT(head)
#define	INPCBRC_LOCKINIT(inp)
#define	INPCBRC_LOCK(inp)
#define	INPCBRC_UNLOCK(inp)
#define	INPCBRC_REF(inp)	(inp)->inp_refcnt++
#define	INPCBRC_UNREF(inp)	{if (--(inp)->inp_refcnt == 0) in_pcbfree(inp);}
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif
