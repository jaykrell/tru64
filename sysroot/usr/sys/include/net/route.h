/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: route.h,v $
 * Revision 4.2.61.4  2003/06/23  18:21:56  Tony_Bono
 * 	Corrected problem with conflicts between version 2 and
 * 	version 3 rt_msghdr structs. QAR 96586
 *
 * Revision 4.2.61.3  2003/06/10  22:51:43  Tony_Bono
 * 	Made changes to support route rate limiting to fix performance
 * 	problem seen at rogers@home (CLD CR2W5100C QAR 94040).
 * 	Route entries contain a rate limit field for data exchanges
 * 	between the local host and a remote host or a remote network.
 *
 * Revision 4.2.61.1  2003/06/06  18:31:58  Brian_Haley
 * 	Added RTF_PERMANENT support for "permanent" route table entries - those
 * 	that can't be modified by a redirect.
 *
 * Revision 4.2.51.2  2001/12/17  20:54:39  Vladislav_Yasevich
 * 	Mobile IPv6 submit:
 * 	- added binding cache entry pointer to rtentry struct
 * 	- added RTF_MOBILE definition
 * 	- added new RTALLOC_* flags
 * 	- changed routedebug comment
 * 	- Moved rt_precedence location in the rtentry to occupy some unused
 *   padding instead of creating some of its own.  Increased the size
 *   to account for this space reclaim and a little more to fill the
 *   cache line - it is now 256 bytes.
 *
 * Revision 4.2.51.1  2001/09/13  13:35:28  Chris_Houser
 * 	Added EVENT_ROUTE_IP_ADD, EVENT_ROUTE_IP_DELETE,
 * 	EVENT_ROUTE_IP_CHANGE event name macros.
 *
 * Revision 4.2.42.2  2000/10/24  22:47:59  Brian_Haley
 * 	Moved ROUTE_LOCK_HOLDER_AF() macro under NETSYNC_LOCK and created
 * 	dummy version for !NETSYNC_LOCK (qar 82943).
 *
 * Revision 4.2.42.1  2000/09/25  22:41:00  Brian_Haley
 * 	Fixed ROUTE_LOCK_HOLDER_AF() macro to call lock_holder() directly and
 * 	not using the LOCK_HOLDER() macro when determining if we are currently
 * 	the lock holder.  The macro is not normally defined (qar 81956).
 *
 * Revision 4.2.34.8  2000/03/02  23:46:01  Brian_Haley
 * 	NUMA cleanup:
 * 	- made route timestamps and some of the other routing flags
 * 	"REPLICATED" data.  Updated timestamp macros appropriately
 * 	- added rru_inc_timestamp to rad_rt_update struct to fix a
 * 	double-increment of the route timestamp
 * 	- removed unneeded RTHASHSIZ, RTHASHMOD, rthost and rtnet arrays
 *
 * Revision 4.2.34.7  2000/01/26  22:29:33  John_Dustin
 * 	{** Forced Submit **}
 * 	Add #if NETSYNC_LOCK for OPENVMS portability
 *
 * Revision 4.2.34.5  1999/11/30  21:07:45  Brian_Haley
 * 	NUMA route table support:
 * 	- added route6_timestamp and macros to increment it for AF_INET6
 * 	address family.  Added generic _AF ones too.
 * 	- added rad_rt_update structure and some flags for rt_update_rads().
 * 	- added route6_lock declaration and macros, as well as generic AF ones.
 *
 * Revision 4.2.34.4  1999/10/18  20:20:37  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 4.2.26.6  1999/10/08  18:55:01  Sowmini_Varadhan
 * 	IPv6 EAK X7.0 merge to Zulu BL6
 *
 * Revision 4.2.37.2  1999/08/25  19:25:48  Larry_Cohen
 * 	Cluster alias support to avoid sending packets to the loopback driver
 * 	when outbound packets are destined for a cluster alias.
 * 	Added rt_aliasid field to the rtentry structure.
 * 	[1999/08/25  18:55:02  Larry_Cohen]
 *
 * Revision 4.2.26.5  1999/09/08  19:10:49  Sowmini_Varadhan
 * 	obsolete RTF_BOGUSGW
 *
 * Revision 4.2.34.2  1999/08/18  20:02:21  Brian_Haley
 * 	Moved mr_ifp struct definition here from route.c (qar 73794).
 * 	[1999/08/11  20:56:56  Brian_Haley]
 *
 * Revision 4.2.26.4  1999/06/08  18:09:36  Jack_McCann
 * 	IPV6 EAK X6.3 merge to Steel BL23
 * 	- add RTF_ISGATEWAY and RTF_LLVALID
 * 	- add ip6_msghdr, IP6M_xxx, and RTM_IPV6INFO
 * 	- add rnheads[] extern declaration
 * 	[1999/06/08  16:13:38  Jack_McCann]
 * 
 * Revision 4.2.14.16  1999/03/25  19:58:24  Brian_Haley
 * 	Added route_timestamp global and increment macro (qar 69411).
 * 	[1999/03/23  17:15:10  Brian_Haley]
 * 
 * Revision 4.2.14.15  1999/02/26  20:09:19  Tony_Bono
 * 	Added the ability to read/zero the inet protocol stats
 * 	using the SIOCRD(Z)CTRS ioctls.
 * 	[1999/02/26  20:04:02  Tony_Bono]
 * 
 * Revision 4.2.14.14  1999/02/25  23:07:03  Brian_Haley
 * 	Added RTF_LOOPBACK flag (qar 68374).
 * 	[1999/02/08  18:57:44  Brian_Haley]
 * 
 * Revision 4.2.14.13  1999/02/05  21:46:01  Brian_Haley
 * 	Added new RTF_ #defines, put all kernel routing variables
 * 	inside #ifdef _KERNEL (qar 67487).
 * 	[1999/02/04  23:19:14  Brian_Haley]
 * 
 * Revision 4.2.14.12  1999/01/20  19:07:52  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	4.2.24.2 **
 * 		** Merge revision:	4.2.29.2 **
 * 	 	** End **
 * 	[1999/01/20  19:05:42  Tony_Bono]
 * 
 * Revision 4.2.14.11  1998/12/02  23:10:23  Jack_McCann
 * 	- struct rtentry changes:
 * 	  - change rt_flags from short to int
 * 	  - change rt_refcnt from short to int
 * 	  - change rt_use from u_int to u_long
 * 	  - add rt_gwroute, rt_precedence (IPv6 hooks)
 * 	  - add rt_reserved field
 * 	- change struct rtstat counters from short to u_long
 * 	- ROUTE_INC_REFCNT use atomic_incl now that rt_refcnt is an int
 * 	- ROUTE_DEC_REFCNT use atomic_decl now that rt_refcnt is an int
 * 	- RTFREE, RTFREENL (!NETSYNC_LOCK versions) use atomic_decl now that
 * 	  rt_refcnt is an int
 * 	- remove RT_REFCNT_INC and RT_REFCNT_DEC (no longer needed)
 * 	[1998/11/18  20:01:04  Jack_McCann]
 * 
 * Revision 4.2.29.2  1998/10/02  17:41:21  Brian_Haley
 * 	Added extern declarations for routemode, routefailover and
 * 	routedebug, as well as bitmasks to support sending more
 * 	message types on the kernel routing socket.
 * 	[1998/10/01  22:12:37  Brian_Haley]
 * 
 * Revision 4.2.26.3  1998/07/24  20:44:18  Sowmini_Varadhan
 * 	     - Support for RTM_IPV6INFO- the kernel sends an ip6_msghdr message
 * 	       to all routing socket listeners on succesful execution of
 * 	       IPV6IFINIT, IPV6IFUNINIT, IPV6AIFADDR and IPV6DIFADDR ioctls
 * 	     [1998/07/24  17:54:10  Sowmini_Varadhan]
 * 
 * Revision 4.2.14.10  1998/05/14  22:39:31  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.2.20.2 **
 * 		** Merge revision:	4.2.24.2 **
 * 	 	** End **
 * 	[1998/05/14  22:16:23  John_Dustin]
 * 
 * Revision 4.2.24.2  1998/03/31  21:14:02  Tony_Bono
 * 	Added support for incrementing and decrementing refcnt
 * 	with only a read lock. The read lock is necessary to
 * 	protect the flag field.
 * 	[1998/03/31  19:58:20  Tony_Bono]
 * 
 * Revision 4.2.14.9  1997/12/16  18:51:24  Michael_Enright
 * 	revert to v4.2.14.6 structures
 * 	[1997/12/10  15:33:37  Michael_Enright]
 * 
 * Revision 4.2.14.8  1997/10/01  20:16:44  Michael_Enright
 * 	remove #include of <kern/queue.h>
 * 	add rt_queue_entry which mirror queue_entry struct
 * 	from kern/queue.h
 * 	[1997/10/01  20:13:14  Michael_Enright]
 * 
 * 	split rtentry into rtentryhead+rtentry to support multiple routes to a given
 * 	destination. added RTF_WASCLONED. removed obsolete stuff
 * 	(RTHASH*, rthost[], rtnet[]).
 * 	[1997/09/29  14:50:54  Michael_Enright]
 * 
 * Revision 4.2.14.6  1997/09/11  20:01:45  John_Dustin
 * 	Fix merge botch, use RTF_PROTO3 instead of RTF_PMTU.
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	4.2.9.3 **
 * 		** Merge revision:	4.2.20.2 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/11  15:01:28  John_Dustin]
 * 
 * Revision 4.2.14.5  1997/09/10  23:31:28  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	4.2.9.3 **
 * 		** Merge revision:	4.2.20.2 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/10  23:04:20  John_Dustin]
 * 
 * Revision 4.2.14.4  1997/07/23  15:40:48  John_Dustin
 * 	For RSVP project, Markus Jork:
 * 	A couple of changes to support RSVP and in preparation for IPv6.
 * 	Added new RTM_xxx definitions taken from BSD4.4 and some new
 * 	inventions to support multicast.
 * 	Added three more RTA_xxx definitions in support of the new RTM_xxx stuff.
 * 	Added three more RTF_xxx definitions for the SIOCGROUTE ioctl.
 * 	Data structures for the SIOCGROUTE ioctl are in netinet/ip_mroute.h.
 * 	[1997/07/10  19:43:18  John_Dustin]
 * 
 * Revision 4.2.14.3  1997/06/04  17:55:20  Jack_McCann
 * 	- change RTF_PMTU back to RTF_PROTO3 (RTF_PMTU is now defined as
 * 	  IP_RTF_PMTU in netinet/in.h)
 * 	- while I'm here, add RTF_STATIC and RTF_BLACKHOLE as in ptcos-560-ajay
 * 	[1997/05/15  20:58:56  Jack_McCann]
 * 
 * Revision 4.2.20.2  1997/05/02  18:21:32  Ajay_Kachrani
 * 	Add RTF_BLACKHOLE/RTF_STATIC flags.
 * 	[1997/04/11  20:53:09  Ajay_Kachrani]
 * 
 * Revision 4.2.14.2  1996/05/01  14:51:21  Fred_Knight
 * 	Merge from bravos.bl2
 * 	[1996/05/01  14:33:36  Fred_Knight]
 * 
 * Revision 4.2.12.2  1995/10/25  19:57:56  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:27:55  Ray_Lanza]
 * 
 * Revision 4.2.9.3  1995/06/30  22:37:46  Mike_Milicia
 * 	Add MLS secure networking hooks.
 * 	[1995/06/20  22:19:32  Mike_Milicia]
 * 
 * Revision 4.2.9.2  1995/04/28  16:43:47  Jack_McCann
 * 	Path MTU Discovery - add RTF_PMTU
 * 	[1995/04/26  21:03:11  Jack_McCann]
 * 
 * Revision 4.2.6.8  1994/05/24  23:17:34  John_Dustin
 * 	change ROUTE_READ_UNLOCK, ROUTE_WRITE_UNLOCK to just ROUTE_UNLOCK
 * 	[1994/05/20  13:51:49  John_Dustin]
 * 
 * Revision 4.2.6.7  1994/05/11  22:32:33  John_Dustin
 * 	removed recursion from route lock macros
 * 	[1994/05/11  15:27:53  John_Dustin]
 * 
 * Revision 4.2.6.6  1994/03/18  21:53:45  Ernie_Petrides
 * 	Convert locking calls for route_lock to use the ulock_*
 * 	versions to allow for call patch-out in lockmode 0.
 * 	[1994/03/17  00:29:35  Ernie_Petrides]
 * 
 * Revision 4.2.6.5  1994/02/03  22:09:04  John_Dustin
 * 	merge of Sterling BL9 changes
 * 	[1994/02/03  20:41:13  John_Dustin]
 * 
 * Revision 4.2.6.4  1993/11/15  23:49:03  John_Dustin
 * 	change lock_init2 to lock_setup using route_li
 * 	[1993/10/27  15:22:54  John_Dustin]
 * 
 * Revision 4.2.6.3  1993/10/07  21:59:29  Geraldine_Harter
 * 	Merge with Sterling BL6:
 * 
 * 	Revision 4.2.7.2  1993/06/29  17:34:06  SJ_Lee
 * 	Revision 4.2.7.3  1993/12/17  00:00:09  Heather_Gray
 * 	Replace roundup macro for performance, courtesy Ken Lesniak.
 * 	[1993/12/16  20:04:33  Heather_Gray]
 * 
 * Revision 4.2.7.2  1993/06/29  17:34:06  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:08:29  SJ_Lee]
 * 
 * Revision 4.2.6.2  1993/06/25  21:17:39  Geraldine_Harter
 * 	Merge selected OSF1.2 changes.
 * 	[1993/06/25  20:28:37  Geraldine_Harter]
 * 
 * Revision 4.2.2.4  1992/12/11  17:47:42  Tim_Hoskins
 * 	Cast RT_ROUNDUP to 'int' to prevent arithmetic overflow.
 * 	[92/12/11  03:09:57  Tim_Hoskins]
 * 
 * Revision 4.2.2.3  92/05/04  16:35:54  Geraldine_Harter
 * 	Change RT_ROUNDUP to use a 'long' instead of an 'int'
 * 	for structure alignment
 * 	[92/05/04  16:20:10  Geraldine_Harter]
 * 
 * Revision 4.2.2.2  92/01/20  11:26:50  Tim_Hoskins
 * 	Alpha 64-bit network support.
 * 	[92/01/20  11:22:31  Tim_Hoskins]
 * 
 * Revision 4.2  91/09/19  22:46:05  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: route.h,v $ $Revision: 4.2.61.4 $ (DEC) $Date: 2003/06/23 18:21:56 $
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
 * Copyright (c) 1980, 1986 Regents of the University of California.
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
 *	Base:	route.h	7.4 (Berkeley) 6/27/88
 *	Merged:	route.h	7.11 (Berkeley) 6/28/90
 */

#ifndef _ROUTE_H_
#define _ROUTE_H_

/* forward decls for DECC and C++ */
struct mip6_binding_cache;

/*
 * Kernel resident routing tables.
 *
 * The routing tables are initialized when interface addresses
 * are set by making entries for all directly connected interfaces.
 */

/*
 * A route consists of a destination address and a reference
 * to a routing entry.  These are often held by protocols
 * in their control blocks, e.g. inpcb.
 */
struct route {
	struct	rtentry *ro_rt;
	struct	sockaddr ro_dst;
};

/*
 * These numbers are used by reliable protocols for determining
 * retransmission behavior and are included in the routing structure.
 */
struct rt_metrics {
	u_int	rmx_locks;	/* Kernel must leave these values alone */
	u_int	rmx_mtu;	/* MTU for this path */
	u_int	rmx_hopcount;	/* max hops expected */
	u_int	rmx_expire;	/* lifetime for route, e.g. redirect */
	u_int	rmx_recvpipe;	/* inbound delay-bandwith product */
	u_int	rmx_sendpipe;	/* outbound delay-bandwith product */
	u_int	rmx_ssthresh;	/* outbound gateway buffer limit */
	u_int	rmx_rtt;	/* estimated round trip time */
	u_int	rmx_rttvar;	/* estimated rtt variance */
};

/*
 * rmx_rtt and rmx_rttvar are stored as microseconds;
 * RTTTOPRHZ(rtt) converts to a value suitable for use
 * by a protocol slowtimo counter.
 */
#define	RTM_RTTUNIT	1000000	/* units for rtt, rttvar, as units per sec */
#define	RTTTOPRHZ(r)	((r) / (RTM_RTTUNIT / PR_SLOWHZ))

/*
 * We distinguish between routes to hosts and routes to networks,
 * preferring the former if available.  For each route we infer
 * the interface to use from the gateway address supplied when
 * the route was entered.  Routes that forward packets through
 * gateways are marked so that the output routines know to address the
 * gateway rather than the ultimate destination.
 */
#ifndef	RNF_NORMAL
#include "net/radix.h"
#endif
struct rtentry {
	struct	radix_node rt_nodes[2];	/* tree glue, and other values */
#define	rt_key(r)	((struct sockaddr *)((r)->rt_nodes->rn_key))
#define	rt_mask(r)	((struct sockaddr *)((r)->rt_nodes->rn_mask))
	struct	sockaddr *rt_gateway;	/* value */
	int	rt_flags;		/* up/down?, host/net */
	int	rt_refcnt;		/* # held references */
	u_long	rt_use;			/* raw # packets forwarded */
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
	struct	ifaddr *rt_ifa;		/* the answer: interface to use */
	struct	sockaddr *rt_genmask;	/* for generation of cloned routes */
	caddr_t	rt_llinfo;		/* pointer to link level info cache */
	struct	rt_metrics rt_rmx;	/* metrics used by rx'ing protocols */
	short	rt_idle;		/* easy to tell llayer still live */
	short   rt_aliasid;		/* cluster aliasid id of dst */
	u_int	rt_precedence;		/* precedence */
#if SEC_NET
        struct tnrh_rem_host *rt_host;  /* Remote host structure. */
#endif
	struct	rtentry *rt_gwroute;	/* entry for gateway route */
	struct mip6_binding_cache *rt_mip6cache;/* ptr to Mobile IPv6 binding */
	u_int	rt_limit;		/* limit for this route */
	u_int	rt_current;		/* limit remaining for interval */
	u_int	rt_limit_time;		/* last time reset */
	u_int	rt_reserved[7];		/* reserved for future use */
};

/*
 * Following structure necessary for 4.3 compatibility;
 * We should eventually move it to a compat file.
 */
struct ortentry {
	u_int	rt_hash;		/* to speed lookups */
	struct	sockaddr rt_dst;	/* key */
	struct	sockaddr rt_gateway;	/* value */
	short	rt_flags;		/* up/down?, host/net */
	short	rt_refcnt;		/* # held references */
	u_int	rt_use;			/* raw # packets forwarded */
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
};

#define	RTF_UP		0x00000001	/* route useable */
#define	RTF_GATEWAY	0x00000002	/* destination is through a gateway */
#define	RTF_HOST	0x00000004	/* host entry (net otherwise) */
#define RTF_REJECT	0x00000008	/* host or net unreachable */
#define	RTF_DYNAMIC	0x00000010	/* created dynamically (by redirect) */
#define	RTF_MODIFIED	0x00000020	/* modified dynamically (by redirect) */
#define RTF_DONE	0x00000040	/* message confirmed */
#define RTF_MASK	0x00000080	/* subnet mask present */
#define RTF_CLONING	0x00000100	/* generate new routes on use */
#define RTF_XRESOLVE	0x00000200	/* external daemon resolves name */
#define RTF_LLINFO	0x00000400	/* generated by ARP or ESIS */
#define RTF_STATIC      0x00000800	/* manually added */
#define RTF_BLACKHOLE   0x00001000	/* just discard pkts (during updates) */
#define RTF_PROTO3	0x00002000	/* protocol specific routing flag */
#define RTF_PROTO2	0x00004000	/* protocol specific routing flag */
#define RTF_PROTO1	0x00008000	/* protocol specific routing flag */
#define RTF_WASCLONED	0x00010000	/* route entry was cloned */
#define RTF_ALLROUTES	0x00040000	/* add/delete all possible routes */
#define RTF_LOOPBACK	0x00080000	/* send packets over loopback device */
#define	RTF_CLUALIAS	0x00100000	/* route to a cluster alias */
#define	RTF_ISGATEWAY	0x00200000	/* destination is a gateway */
#define	RTF_LLVALID	0x00400000	/* link layer address is valid */
#define	RTF_MOBILE	0x00800000	/* route to a mobile node */
#define	RTF_PERMANENT	0x01000000	/* should not be modified by redirect */
/*
 * used in struct rtgetreq:
 */
#define RTF_NOT_MROUTING	 0x10000000	/* vif_mask/ifc_mask invalid */
#define RTF_SND_USES_SHARED_TREE 0x20000000
#define RTF_ALL_USE_SHARED_TREE	 0x40000000

#include <netinet/ip_stat.h>

/*
 * Define the event names
 */
#define EVENT_ROUTE_IP_ADD 	_EvmSYSTEM_EVENT_NAME("net.route.ip.add")
#define EVENT_ROUTE_IP_DELETE 	_EvmSYSTEM_EVENT_NAME("net.route.ip.delete")
#define EVENT_ROUTE_IP_CHANGE 	_EvmSYSTEM_EVENT_NAME("net.route.ip.change")

/*
 * Structures for routing messages.
 */
struct rt_msghdr_v3 {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatability */
	u_char	rtm_type;	/* message type */
	u_short	rtm_index;	/* index for associated ifp */
#ifdef __digital__
	int	rtm_pid;	/* identify sender */
#else
	pid_t	rtm_pid;	/* identify sender */
#endif
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_use;	/* from rtentry */
	u_int	rtm_inits;	/* which metrics we are initializing */
	struct	rt_metrics rtm_rmx; /* metrics themselves */
	u_int	rtm_limit;	/* data limit for 200msec interval */
};

/*
 * Structures for routing messages.
 */
struct rt_msghdr {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatability */
	u_char	rtm_type;	/* message type */
	u_short	rtm_index;	/* index for associated ifp */
#ifdef __digital__
	int	rtm_pid;	/* identify sender */
#else
	pid_t	rtm_pid;	/* identify sender */
#endif
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_use;	/* from rtentry */
	u_int	rtm_inits;	/* which metrics we are initializing */
	struct	rt_metrics rtm_rmx; /* metrics themselves */
};

struct ip6_msghdr {
	u_short ip6m_msglen;         /* to skip over non-understood messages */
	u_char ip6m_version;         /* PF_ROUTE msg version for 
			              * future binary compatibility */
	u_char ip6m_type;            /* message type  */
	int ip6m_addrs;	             /* bitmask indentifying sockaddrs in msg */
	int ip6m_op;	             /* sub-type indicating operation 
			              * (INIT, AIFADDR etc.) */
	int ip6m_ifindex;            /* index of associated ifnet */
	union {			     /* IPV6 specific info */
	   int ip6m_addrflags;       /* address flags for AIFADDR/DIFADDR */
	   int ip6m_ifnetflags;      /* value of if_flags for INIT/UNINIT*/
	}ip6m_msghdr_un;
};

#define ip6m_aflags ip6m_msghdr_un.ip6m_addrflags
#define ip6m_ifflags ip6m_msghdr_un.ip6m_ifnetflags

#define IP6M_INIT	0x1 /* SIOCIPV6IFINIT */
#define IP6M_UNINIT	0x2 /* SIOCIPV6IFUNINIT */
#define IP6M_AIFADDR	0x3 /* SIOCIPV6AIFADDR */
#define IP6M_DIFADDR	0x4 /* SIOCIPV6DIFADDR */

struct route_cb {
	int	count[AF_MAX];
};
#define	ip_count	count[AF_INET]
#define	ns_count	count[AF_NS]
#define	iso_count	count[AF_ISO]
#define	any_count	count[AF_UNSPEC]

#ifdef _KERNEL

#ifndef REPLICATED
#define REPLICATED
#endif

/*
 * Global route timestamps, updated on route table changes
 * Initialized to: 1
 */
extern REPLICATED u_long route_timestamp;
extern REPLICATED u_long route6_timestamp;

/*
 * Routing modes for >1 interface on the same subnet
 *
 * Current modes are:
 *	0 = multiple routes behavior based on rt->rt_refcnt and rt->rt_use
 * Default: 0
 *
 * NOTE: Currently unused
 */
extern int routemode;

/*
 * When set to 1, this triggers the routing code to automatically add all
 * possible routes to a destination through all relevant interfaces.
 * Similar to using 'route add -net net gw -all'
 * Default: 0
 */
extern REPLICATED int routeallroutes;


/*
 * When set to 1, this triggers the routing code to automatically scrub,
 * or flush, all routes through an interface when the last address
 * associated with the interface is deleted (e.g. ifconfig tu0 down delete).
 * Default: 1
 */
extern int routescrub;

/*
 * When set to 1, this allows the routing code to fail-over a route from
 * one interface to another in the same subnet when the last address
 * associated with the interface is deleted (e.g. ifconfig tu0 down delete).
 * 'routescrub' must be set to 1 for this to have any effect.
 * Default: 0
 */
extern int routefailover;

/*
 * When set to 1, this turns-on printf debugging in the routing code for
 * add/delete/change cases.  When set to 2, this also turns-on printf
 * debugging in the routing code for lookup cases.  When set to 3, you get
 * the radix code as well.  NOTE: Most printfs at levels >1 require a
 * recompile of the kernel with ROUTEDEBUG defined.
 * Default: 0
 */
extern REPLICATED int routedebug;
/* default rate limit for all routes created without a specific rate */
extern u_int route_rate_limit;

/* Structure for multiple routes support */
struct mr_ifp {
	struct ifaddr *ifa;
	struct ifnet *ifp;
	struct mr_ifp *next;
};

/* Structure for RAD support */
struct rad_rt_update {
	struct rtentry *rru_cur_rt;	/* current rtentry pointer */
	struct rtentry rru_rt;		/* holds new rtentry values */
	int rru_flags;			/* see RRU_*_FLAGS below */
	u_int rru_rtm_inits;		/* which metrics we are initializing */
	int rru_ifa_req;		/* request to issue to rt_ifa->ifa_rt_request */
	int rru_inc_timestamp;		/* increment route*_timestamp? */
	u_int rru_limit;		/* route limit for this network. */
};

#define RRU_IGNORE_FLAGS	0	/* ignore rt->rt_flags (default) */
#define RRU_OR_FLAGS		1	/* OR-in rt->rt_flags */
#define RRU_AND_FLAGS		2	/* AND-in rt->rt_flags */
#define RRU_SET_FLAGS		3	/* set rt->rt_flags */

/* Flags for kernel internal rtalloc*()/rn_match*() calls */
#define	RTALLOC_REPORT		0x00000001	/* report desired */
#define	RTALLOC_GLOBAL		0x00000002	/* route from any RAD is OK */
#define	RTALLOC_LOADBALANCE	0x00000004	/* find "best" if duplicates */
#define	RTALLOC_NOMOBILE	0x00000008	/* RTF_MOBILE not desired */

#endif /* _KERNEL */


#define RTM_VERSION_V2	2	/* Up the ante and ignore older versions */
#define RTM_VERSION_V3	3	/* highest recognized version */
#define RTM_VERSION	2	/* until a new major release version is 2 */

#define RTM_ADD		0x1	/* Add Route */
#define RTM_DELETE	0x2	/* Delete Route */
#define RTM_CHANGE	0x3	/* Change Metrics or flags */
#define RTM_GET		0x4	/* Report Metrics */
#define RTM_LOSING	0x5	/* Kernel Suspects Partitioning */
#define RTM_REDIRECT	0x6	/* Told to use different route */
#define RTM_MISS	0x7	/* Lookup failed on this address */
#define RTM_LOCK	0x8	/* fix specified metrics */
#define RTM_OLDADD	0x9	/* caused by SIOCADDRT */
#define RTM_OLDDEL	0xa	/* caused by SIOCDELRT */
#define RTM_RESOLVE	0xb	/* req to resolve dst to LL addr */
#define RTM_NEWADDR     0xc     /* address being added to iface */
#define RTM_DELADDR     0xd     /* address being removed from iface */
#define RTM_IFINFO      0xe     /* iface going up/down etc. */
#define RTM_VIFINFO     0xf	/* vif going up/down etc. */
/*
 * sockaddr usage in RTM_MC_xxx messages:
 *   RTA_DST:           multicast group
 *   RTA_SRC:           origin
 *   RTA_BITMAP:        vif_mask/ifc_mask put into a struct sockaddr:
 *                      sa_family is AF_UNSPEC, sa_len is length in bytes
 *                      sa_data contains some padding for 4/8 byte alignment
 *                      followed by the bitmask
 *
 * usage of struct rt_msghdr elements in RTM_MC_xxx messages:
 *   rtm_index:         expected incoming vif/interface
 */
#define RTM_MC_ADD      0x10	/* multicast route added notification */
#define RTM_MC_DELETE   0x11	/* multicast route deleted notification */
#define RTM_MC_CHANGE   0x12	/* multicast route changed notification */
#define RTM_IPV6INFO	0x13	/* ipv6 related routing messages */
#define RTM_CONFIRM     0x100   /* llinfo is still good */

#define RTV_MTU		0x1	/* init or lock _mtu */
#define RTV_HOPCOUNT	0x2	/* init or lock _hopcount */
#define RTV_EXPIRE	0x4	/* init or lock _expire */
#define RTV_RPIPE	0x8	/* init or lock _recvpipe */
#define RTV_SPIPE	0x10	/* init or lock _sendpipe */
#define RTV_SSTHRESH	0x20	/* init or lock _ssthresh */
#define RTV_RTT		0x40	/* init or lock _rtt */
#define RTV_RTTVAR	0x80	/* init or lock _rttvar */

/*
 * Bitmask values for rtm_addr.
 */
#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define RTA_BRD         0x80    /* for NEWADDR, broadcast or p-p dest addr */
#define RTA_SRC         0x100	/* for RTM_MC_xxx */
#define RTA_BITMAP      0x200	/* for RTM_MC_xxx */
#define RTA_PRECEDENCE  0x400   /* precedence present */
#define RTA_OLDGATEWAY  0x800   /* old gateway sockaddr present */
#define RTA_OLDIFINDEX  0x1000  /* old interface name sockaddr present */

#define	RT_ROUNDUP(sa)	\
	((int)(((sa)->sa_len + (sizeof(long) - 1)) & ~(sizeof(long) - 1)))


#ifdef _KERNEL
/* AF_INET family route lock macros */
#if	NETSYNC_LOCK
ndecl_lock_data(extern, route_lock)
#define ROUTE_LOCKINIT()	ulock_setup(&route_lock, route_li, TRUE)
#define	ROUTE_LOCK_DECL()	NETSPL_DECL(_rs)
#define ROUTE_READ_LOCK()	{ NETSPL(_rs,net); ulock_read(&route_lock); }
#define ROUTE_UNLOCK()		{ ulock_done(&route_lock); NETSPLX(_rs); }
#define ROUTE_WRITE_LOCK() 	{ NETSPL(_rs,net); ulock_write(&route_lock); }
#define ROUTE_WRITETOREAD_LOCK() { ulock_write_to_read(&route_lock); }
#else
#define ROUTE_LOCKINIT()
#define ROUTE_LOCK_DECL()
#define ROUTE_READ_LOCK()
#define ROUTE_UNLOCK()
#define ROUTE_WRITE_LOCK()
#define ROUTE_WRITETOREAD_LOCK()
#endif	/* NETSYNC_LOCK */

/* AF_INET6 family route lock macros */
#if	NETSYNC_LOCK
ndecl_lock_data(extern, route6_lock)
#define ROUTE6_LOCKINIT()	ulock_setup(&route6_lock, route6_li, TRUE)
#define	ROUTE6_LOCK_DECL()	NETSPL_DECL(_rs6)
#define ROUTE6_READ_LOCK()	{ NETSPL(_rs6,net); ulock_read(&route6_lock); }
#define ROUTE6_UNLOCK()		{ ulock_done(&route6_lock); NETSPLX(_rs6); }
#define ROUTE6_WRITE_LOCK() 	{ NETSPL(_rs6,net); ulock_write(&route6_lock); }
#define ROUTE6_WRITETOREAD_LOCK() { ulock_write_to_read(&route6_lock); }
#else
#define ROUTE6_LOCKINIT()
#define ROUTE6_LOCK_DECL()
#define ROUTE6_READ_LOCK()
#define ROUTE6_UNLOCK()
#define ROUTE6_WRITE_LOCK()
#define ROUTE6_WRITETOREAD_LOCK()
#endif	/* NETSYNC_LOCK */

/*
 * Generic macros to lock the correct family's route lock.
 * AF_INET6 uses the route6_lock, all others use the route_lock.
 */
#if	NETSYNC_LOCK
#define	ROUTE_LOCK_DECL_AF()	NETSPL_DECL2(_rs, _rs6)
#define ROUTE_READ_LOCK_AF(af) {	\
	if ((af) == AF_INET6)		\
		ROUTE6_READ_LOCK()	\
	else				\
		ROUTE_READ_LOCK()	\
    }
#define ROUTE_UNLOCK_AF(af) {		\
	if ((af) == AF_INET6)		\
		ROUTE6_UNLOCK()		\
	else				\
		ROUTE_UNLOCK()		\
    }
#define ROUTE_WRITE_LOCK_AF(af) {	\
	if ((af) == AF_INET6)		\
		ROUTE6_WRITE_LOCK()	\
	else				\
		ROUTE_WRITE_LOCK()	\
    }
#define ROUTE_WRITETOREAD_LOCK_AF(af) {		\
	if ((af) == AF_INET6)			\
		ROUTE6_WRITETOREAD_LOCK()	\
	else					\
		ROUTE_WRITETOREAD_LOCK()	\
    }

/*
 * Generic macro to check if we're holding a family's route lock.
 */
#define ROUTE_LOCK_HOLDER_AF(af)				\
	((lockmode == 0) ||					\
	 ((af) == AF_INET6 && lock_holder(&route6_lock)) ||	\
	 ((af) != AF_INET6 && lock_holder(&route_lock)))
#else
#define ROUTE_LOCK_DECL_AF()
#define ROUTE_READ_LOCK_AF(af)
#define ROUTE_UNLOCK_AF(af)
#define ROUTE_WRITE_LOCK_AF(af)
#define ROUTE_WRITETOREAD_LOCK_AF(af)
#define ROUTE_LOCK_HOLDER_AF(af)	1
#endif	/* NETSYNC_LOCK */

#define ROUTE_INC_REFCNT(rt) (atomic_incl(&((rt).rt_refcnt)))
#define ROUTE_DEC_REFCNT(rt) (atomic_decl(&((rt).rt_refcnt)))

/*
 * Macros to increment the global route timestamps - this will tell
 * everyone the route table just changed.  We don't want a zero
 * timestamp since we always want bzero'd structures to rtalloc().
 * AF_INET6 uses the route6_timestamp, all others use the route_timestamp.
 */
#define INC_ROUTE_TIMESTAMP() {				\
	u_long _stamp = route_timestamp + 1;		\
	write_const_data((void *)&_stamp,		\
			 (void *)&route_timestamp,	\
			 sizeof(u_long));		\
    }
#define INC_ROUTE6_TIMESTAMP() {			\
	u_long _stamp = route6_timestamp + 1;		\
	write_const_data((void *)&_stamp,		\
			 (void *)&route6_timestamp,	\
			 sizeof(u_long));		\
    }
#define INC_ROUTE_TIMESTAMP_AF(af) {	\
	if ((af) == AF_INET6)		\
		INC_ROUTE6_TIMESTAMP() 	\
	else				\
		INC_ROUTE_TIMESTAMP() 	\
    }

#if	NETSYNC_LOCK
#define RTFREE(rt)		rtfree(rt)
#define RTFREENL(rt)		rtfreeNL(rt)
#else	/* !NETSYNC_LOCK */
#define	RTFREE(rt) 						\
	if ((rt)->rt_refcnt <= 1) 				\
		rtfree(rt); 					\
	else							\
		atomic_decl(&rt->rt_refcnt);

#define	RTFREENL(rt) 						\
	if ((rt)->rt_refcnt <= 1) 				\
		rtfreeNL(rt); 					\
	else							\
		atomic_decl(&rt->rt_refcnt);
#endif

extern	struct	route_cb route_cb;
extern	struct	rtstat	rtstat;
extern  struct  radix_node_head *rnheads[AF_MAX+1];
#endif

#endif
