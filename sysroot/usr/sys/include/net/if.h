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
 *	@(#)$RCSfile: if.h,v $ $Revision: 4.3.186.4 $ (DEC) $Date: 2002/07/10 18:35:50 $
 */

/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
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
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
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
 *	Base:	if.h	7.6 (Berkeley) 9/20/89
 *	Merged: if.h	7.9 (Berkeley) 6/28/90
 */
/*
 *	Revision History:
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patch
 *
 */

/*
 * Structures defining a network interface, providing a packet
 * transport mechanism (ala level 0 of the PUP protocols).
 *
 * Each interface accepts output datagrams of a specified maximum
 * length, and provides higher level routines with input datagrams
 * received from its medium.
 *
 * Output occurs when the routine if_output is called, with five parameters:
 *	(*ifp->if_output)(ifp, m, dst, ro, lh)
 * Here m is the mbuf chain to be sent and dst is the destination address.
 * The output routine encapsulates the supplied datagram if necessary,
 * and then transmits it on its medium.
 *
 * On input, each interface unwraps the data received by it, and either
 * places it on the input queue of a internetwork datagram routine
 * and posts the associated software interrupt, or passes the datagram to a raw
 * packet input routine.
 *
 * Routines exist for locating interfaces by their addresses
 * or for locating a interface on a certain network, as well as more general
 * routing and gateway routines maintaining information used to locate
 * interfaces.  These routines live in the files if.c and route.c
 */

#ifndef _NET_IF_H_
#define _NET_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/* forward decls for DECC and C++ */
struct mbuf;
struct ifaddr;
struct ifmulti;
struct rtentry;
struct ifafilt;

#include <standards.h>

#if	defined(_KERNEL) && !defined(_NET_GLOBALS_H_)
#include "net/net_globals.h"
#endif

#ifdef	_KERNEL
#include "netinet/if_trnstat.h"
#include "netinet/if_ds1stat.h"
#ifndef	_TIME_
#include "sys/time.h"
#endif
#else
#include <netinet/if_trnstat.h>
#include <netinet/if_ds1stat.h>
#ifndef	_TIME_
#include <sys/time.h>
#endif
#endif

#include <sys/socket.h>

#ifndef REPLICATED
#define REPLICATED
#endif

#ifdef _KERNEL
/*
 * Forward declaration to handle if_tcntl field in ifnet. I wanted
 * to move the include of ip_tcntl.h up top, but it makes reference
 * to at least one thing in this file so it ends up being a catch-22.
 */
struct tcntl;
#endif

/*
 * Structure defining a queue for a network interface.
 */
struct	ifqueue {
		struct	mbuf *ifq_head;
		struct	mbuf *ifq_tail;
		int	ifq_len;
		int	ifq_maxlen;
		int	ifq_drops;
#if	defined(_KERNEL)  && NETSYNC_LOCK
		simple_lock_data_t	ifq_slock;
#endif
}; 

/*
 * Structure defining a network interface.
 */
struct ifnet {
/* 64-byte alignment */
	struct	ifnet *if_next;		/* the next structure in the list */
	char	*if_name;		/* name, e.g. ``en'' or ``lo'' */
	char	*if_version;		/* The version string.		   */
	struct	sockaddr if_addr;	/* address of interface */
	int	if_flags;		/* up/down, broadcast, etc. */
	int	if_pfactive;		/* interface-specific pfactive */
	short	if_unit;		/* sub-unit for lower level driver */
	u_short	if_mtu;			/* maximum IP transmission unit */
	u_short	if_mediamtu;		/* maximum MTU of the media */
	short	if_timer;		/* time 'til if_watchdog called */
	int	if_metric;		/* routing metric (external only) */
	int	pad_a[1];
/* 64-byte alignment */
	struct	ifaddr *if_addrlist;	/* linked list of addresses per if */

	struct	ifmulti *if_multiaddrs; /* list of multicast addrs */
	int	if_multicnt;		/* number of multicast addrs in list */	
	int	if_allmulticnt;		/* number of allmulti requests */	
/* procedure handles */
#ifdef	_KERNEL
	int	(*if_init)(int);
	int	(*if_output)(struct ifnet *, struct mbuf *,
				struct sockaddr *, struct rtentry *, caddr_t);
#ifndef __VMS 
	int	(*if_start)(struct ifnet *);
#else /* __VMS */
	int	(*if_start)(struct ifnet *, struct mbuf *, u_char edst[6], int);
#endif /* __VMS */
	int	(*if_done)(struct ifnet *);
	int	(*if_ioctl)(struct ifnet *, unsigned int, caddr_t);
/* 64-byte alignment */
	int	(*if_reset)(int, int);
	int	(*if_watchdog)(int, struct ifnet *);
#else
	int	(*if_init) __((int));					 /* init routine */
	int	(*if_output) __((struct ifnet *, struct mbuf *,
				struct sockaddr *, struct rtentry *, caddr_t));	 /* output routine (enqueue) */
	int	(*if_start) __((struct ifnet *));			 /* initiate output routine */
	int	(*if_done) __((struct ifnet *));			 /* output complete routine */
	int	(*if_ioctl) __((struct ifnet *, unsigned int, caddr_t)); /* ioctl routine */
/* 64-byte alignment */
	int	(*if_reset) __((int, int));				 /* bus reset routine */
	int	(*if_watchdog) __((int, struct ifnet *));		 /* timer routine */
#endif
	void	*drvr_softc;		/* ptr to driver's softc */
	long	if_reserved[5];		/* reserved for future use */
/* 64-byte alignment */
/* generic interface statistics */
	u_long	if_ipackets;		/* packets received on interface */
	u_long	if_ierrors;		/* input errors on interface */
	u_long	if_opackets;		/* packets sent on interface */
	u_long	if_oerrors;		/* output errors on interface */
	u_long	if_collisions;		/* collisions on csma interfaces */
	u_long	if_sysid_type;		/* MOP SYSID device code */
/* SNMP statistics */
	struct	timeval if_lastchange;	/* last updated */
	u_long	if_ibytes;		/* total number of octets received */
	u_long	if_obytes;		/* total number of octets sent */
	u_long	if_imcasts;		/* packets received via multicast */
	u_long	if_omcasts;		/* packets sent via multicast */
	u_long	if_iqdrops;		/* dropped on input, this interface */
	u_long	if_noproto;		/* destined for unsupported protocol */
	u_long	if_baudrate;		/* linespeed */
	u_long	if_imbytes;		/* multicast octets received */
	u_long	if_ombytes;		/* multicast octets sent */
/* end statistics */
/* 64-byte alignment */
	u_char	if_type;		/* ethernet, tokenring, etc */
	u_char	if_addrlen;		/* media address length */
	u_char	if_hdrlen;		/* media header length */
	u_char	if_initialized;		/* ifnet has been initialized */
	u_int	if_index;		/* numeric abbreviation for this if */
	int	if_trustgrp;		/* Interface trustgrp (see below) for FIREWALL product */
	int 	if_affinity;		/* which CPU to run on (master, all) */
        struct  ifafilt *if_afilt;	/* interface access filter */
        struct  ifnet *if_nrnext;       /* Flink in NetRAIN set - circular list */
        struct  ifnet *if_nrif;         /* Back link to netrain virtual ifp */
	u_short	if_alloc_size;		/* size structure if_alloc() alloc'ed */
	u_short	if_padb[1];		/* unused - padding */
	int	if_rad_id;		/* RAD this interface is in */
	caddr_t	if_arp_cache_head;	/* pointer to this ifnet's ARP cache */
	u_int	if_padc[2];		/* unused - padding */
/* 64-byte alignment */
	struct	ifqueue  if_snd;	/* output queue */
#if	defined(_KERNEL) && NETSYNC_LOCK
	struct ifnetfunhide	*if_funhide;	/* to hide driver routines 
						 * for those drivers who
						 * aren't parallelized */
#ifdef	LOCK_NETSTATS
	simple_lock_data_t	if_slock;	/* statistics lock */
#endif /* LOCK_NETSTATS */
	simple_lock_data_t	*lk_softc;	/* driver's softc lock ptr */
#endif  /*  defined(_KERNEL) && NETSYNC_LOCK */
/* 64-byte alignment */
	int     (*if_uiomove)();	/* DART */
	int     (*if_xmtbufalloc)();	/*  "   */
	int     (*if_pktok)();		/*  "   */
	void    (*if_sockbuf)();	/*  "   */
	int     if_buflen;		/*  "   */
#if	SEC_NET
	struct tnet_if *if_sec;
#	define SEC_IFF_LOADING 0x10000000
#endif	/* SEC_NET */
#ifdef _KERNEL
        struct tcntl *if_tcntl;         /* Traffic Control */
        struct ifnet *if_lagif;		/* lag_softc ifp */
        void *if_vlansc;		/* vlan_softc */
#endif
#ifdef __VMS 
	u_short ovms_if_sts;
	u_short ovms_if_pad;
	u_short	ovms_if_size;
	u_char	ovms_if_type;
	u_char	ovms_if_iftype;
#define IF_LOCAL     0
	u_int	ovms_if_eth_name;
	u_short ovms_if_react_att;
	u_short	ovms_if_succ_react;
	u_int	ovms_if_cluster;
	u_int	ovms_if_clust_tcps;
	u_int	ovms_if_cluster_timer_id;
	u_char	ovms_if_lock[24];

	u_char	*ovms_vcib_ip;
	u_char  *ovms_vcib_arp;		
	u_char	*ovms_vcib_ipv6;
	u_int	if_ovms_outstanding_xmits;
#endif /* __VMS */
};

#if defined(_KERNEL) && defined(INTSERV)
extern struct tcntl **ifnet_tcntl;
#endif

#if defined(_KERNEL) 
/* if_affinity values for which CPU to run on */
#define NETMASTERCPU 0			/* driver not ||ized (must funnel) */
#define NETALLCPU    1			/* driver ||ized */

#if NETSYNC_LOCK

#define DVRFUN             0x1     /* At least one network driver isn't
                                    * ||-ized and needs to be funneled */

#define DVRFUNRESET        0x2     /* At least one network driver with a
                                    * reset routine isn't ||-ized and needs 
                                    * to be funneled */

#define DVRFUNWATCH        0x4     /* At least one network driver with a
                                    * watchdog routine isn't ||-ized and needs 
                                    * to be funneled */
/*
 * Structure used to hide copies of any driver routines that could be
 * called from above the driver.  This is to support
 * non-parallelized network drivers
 */
struct ifnetfunhide {
	int	(*if_init)(int);
	int	(*if_output)(struct ifnet *, struct mbuf *,
				struct sockaddr *, struct rtentry *, caddr_t);
	int	(*if_start)(struct ifnet *);
	int	(*if_done)(struct ifnet *);
	int	(*if_ioctl)(struct ifnet *, unsigned int, caddr_t);
	int	(*if_reset)(int, int);
	int	(*if_watchdog)(int, struct ifnet *);
}; 

/* 
 * RBS: Macros to lock & unlock the net driver's softc struct. This lock is 
 * needed whenever a shared field in the ifnet struct is modified. (if_flags 
 * and if_timer at this time.) Also, splimp() is expected before the lock is 
 * requested.
 */
#define	LOCK_NETDRIVER_SC(ifp)\
	if (ifp->lk_softc)\
		simple_lock(ifp->lk_softc);

#define UNLOCK_NETDRIVER_SC(ifp)\
	if (ifp->lk_softc)\
		simple_unlock(ifp->lk_softc);

#define NETDRIVER_SC_ISLOCKED(ifp)\
	(ifp->lk_softc ? \
	(lockmode == 0 || simple_lock_holder(ifp->lk_softc)) : 0)

extern  simple_lock_data_t  ifnet_spin_lock;
#define IFNET_SPIN_LOCKINIT() simple_lock_setup(&ifnet_spin_lock, ifnet_spin_li)
#define IFNET_SPIN_LOCK()     simple_lock(&ifnet_spin_lock)
#define IFNET_SPIN_UNLOCK()   simple_unlock(&ifnet_spin_lock)
#define IFNET_SPIN_ISLOCKED() (lockmode==0||simple_lock_holder(&ifnet_spin_lock))
#else
#define LOCK_NETDRIVER_SC(ifp)
#define UNLOCK_NETDRIVER_SC(ifp)
#define IFNET_SPIN_LOCKINIT()
#define IFNET_SPIN_LOCK()
#define IFNET_SPIN_UNLOCK()
#define IFNET_SPIN_ISLOCKED()
#endif /* NETSYNC_LOCK */
#endif /* _KERNEL */

#define	IFF_UP		0x1		/* interface is up */
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_LOOPBACK	0x8		/* is a loopback net */
#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
#define	IFF_NOTRAILERS	0x20		/* avoid use of trailers */
#define	IFF_RUNNING	0x40		/* resources allocated */
#define	IFF_NOARP	0x80		/* no address resolution protocol */
#define	IFF_PROMISC	0x100		/* receive all packets */
#define	IFF_ALLMULTI	0x200		/* receive all multicast packets */
#define IFF_MULTICAST	0x400		/* supports multicast */
#define	IFF_SIMPLEX	0x800		/* can't hear own transmissions */
#define	IFF_OACTIVE	0x1000		/* transmission in progress */
#define IFF_PFCOPYALL   0x2000          /* pfilt gets packets to this host */
#define IFF_UIOMOVE     0x10000		/* DART */
#define IFF_PKTOK       0x20000		/* DART */
#define IFF_SOCKBUF     0x40000		/* DART */
#define IFF_VAR_MTU	0x80000		/* interface supports variable MTUs */
#define IFF_NOCHECKSUM	0x100000	/* no checksums need reliable media */
#define IFF_RESERVED	0x4000000       /* interface is reserved for use by LAG, VLAN, etc. */
#define IFF_TAGGING	0x8000000       /* interface is enabled for 802.1Q tagging */
#ifndef __VMS
#define IFF_MULTINET	0x200000	/* Multiple network on interface */
#define IFF_QUORUMLOSS	0x400000  	/* UP interface marked DOWN due to cluster quorum loss */
#define IFF_VMIFNET     0x800000        /* Used to identify a virtual Mac Addr*/
#define IFF_CLUIF	0x1000000       /* interface is cluster interconnect */
#define IFF_DETACHED	0x2000000       /* interface is detached */
#else /* __VMS */
#define IFF_DYNPROTO	0x200000	/* Support dynamic proto dispatching */
#define IFF_MOP		0x400000	/* Device in MOP mode */
#define IFF_SLIP	0x800000	/* Interface is a SLIP IFNET */
#define IFF_DELETE	0x1000000	/* Started DELETE on this interface */
#define IFF_NONAME	0x2000000	/* Interf does not hold cluster name */
#define IFF_CLUSTER	0x4000000	/* Interface is a cluster IFNET */

#define IFF_MULTINET    0x8000000       /* Multiple network on interface */
#define IFF_QUORUMLOSS  0x10000000      /* UP interface marked DOWN due to cluster quorum loss */
#define IFF_VMIFNET     0x20000000      /* Used to identify a virtual Mac Addr*/
#define IFF_CLUIF       0x40000000      /* interface is cluster interconnect */
#define IFF_DETACHED    0x80000000      /* interface is detached */
#endif /* __VMS */

/* Device-specific flags */
#define IFF_D1		0x8000
#define IFF_D2		0x4000
#define IFF_SNAP	IFF_D1		/* Ethernet driver outputs SNAP hdr */

/* flags set internally only: */
#define IFF_CANTCHANGE  \
	(IFF_BROADCAST|IFF_POINTOPOINT|IFF_SIMPLEX|IFF_RUNNING|\
	IFF_OACTIVE|IFF_MULTICAST|IFF_UIOMOVE|IFF_PKTOK|IFF_SOCKBUF|\
	IFF_VAR_MTU|IFF_CLUIF|IFF_RESERVED|IFF_TAGGING)

/* interface types for benefit of parsing media address headers */

#ifdef	_KERNEL
#include "net/if_types.h"
#else
#include <net/if_types.h>
#endif

/* interface trust groups for network security (aka FIREWALL) product */
#define	IFG_ANY		0x0		/* for screend; matches any */
#define	IFG_UNKNOWN	0x1		/* currently unknown */
#define	IFG_INFRARED	0x2		/* Totally untrusted */
#define	IFG_RED		0x3		/*        ^          */
#define	IFG_ORANGE	0x4		/*        :          */
#define	IFG_YELLOW	0x5		/*        v          */
#define	IFG_GREEN	0x6		/* Somewhat trusted  */
#define	IFG_BLUE	0x7		/*        ^          */
#define	IFG_INDIGO	0x8		/*        :          */
#define	IFG_VIOLET	0x9		/*        v          */
#define	IFG_ULTRAVIOLET	0xa		/* Totally trusted   */
#define	IFG_MAX		0xa		/* Current max.; expand as needed */

#if	NETSYNC_LOCK
/*
 * Multiprocessor queue locking.
 *
 * Note that the IF_QFULL and IF_DROP macros become racy in an mp environment.
 * The exact number of ifq_drops probably isn't important; on the other hand,
 * it is possible that an unlocked ifq could grow larger than its declared
 * ifq_maxlen as processors race between IF_QFULL and IF_ENQUEUE.  However,
 * it is still ABSOLUTELY NECESSARY that modification of ifq_len be locked!
 *
 * Note also that any macros which take the IFQ_LOCK must be done at splimp.
 *
 */
#define IFQ_LOCKINIT(ifq)	simple_lock_setup(&((ifq)->ifq_slock), ifqueue_li)
#define IFQ_LOCKTERMINATE(ifq)	simple_lock_terminate(&((ifq)->ifq_slock))
#define IFQ_LOCKINIT_SPLIMP(ifq)	IFQ_LOCKINIT(ifq)
/* same macros as above but with different minimum spl checking */
#define IFQ_LOCKINIT_SPLNET(ifq)	simple_lock_setup(&((ifq)->ifq_slock), ifqueue_splnet_li)
#define IFQ_LOCKINIT_SPLNONE(ifq)	simple_lock_setup(&((ifq)->ifq_slock), ifqueue_splnone_li)
#define IFQ_LOCK(ifq)		simple_lock(&((ifq)->ifq_slock))
#define IFQ_UNLOCK(ifq)		simple_unlock(&((ifq)->ifq_slock))
ndecl_lock_info(extern, ifqueue_li)
ndecl_lock_info(extern, ifqueue_splnet_li)
ndecl_lock_info(extern, ifqueue_splnone_li)
ndecl_lock_info(extern, ifnet_li)
#else
#define IFQ_LOCKINIT(ifq)
#define IFQ_LOCKTERMINATE(ifq)
#define IFQ_LOCKINIT_SPLIMP(ifq)
#define IFQ_LOCKINIT_SPLNET(ifq)
#define IFQ_LOCKINIT_SPLNONE(ifq)
#define IFQ_LOCK(ifq)
#define IFQ_UNLOCK(ifq)
#endif

/*
 * Output queues (ifp->if_snd) and internetwork datagram level (pup level 1)
 * input routines have queues of messages stored on ifqueue structures
 * (defined above).  Entries are added to and deleted from these structures
 * by these macros, which should be called with ipl raised to splimp().
 */
#define	IF_QFULL(ifq)		((ifq)->ifq_len >= (ifq)->ifq_maxlen)
#define	IF_DROP(ifq)		((ifq)->ifq_drops++)
#define	IF_ENQUEUE_NOLOCK(ifq, m) { \
	(m)->m_nextpkt = 0; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_head = m; \
	else \
		(ifq)->ifq_tail->m_nextpkt = m; \
	(ifq)->ifq_tail = m; \
	(ifq)->ifq_len++; \
}
#define	IF_ENQUEUE(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_ENQUEUE_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}
#define	IF_PREPEND_NOLOCK(ifq, m) { \
	(m)->m_nextpkt = (ifq)->ifq_head; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_tail = (m); \
	(ifq)->ifq_head = (m); \
	(ifq)->ifq_len++; \
}
#define	IF_PREPEND(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_PREPEND_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}
#define	IF_DEQUEUE_NOLOCK(ifq, m) { \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		if (((ifq)->ifq_head = (m)->m_nextpkt) == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_nextpkt = 0; \
		(ifq)->ifq_len--; \
	} \
}
#define	IF_DEQUEUE(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_DEQUEUE_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}

#define	IFQ_MAXLEN	1024
#define	IFNET_SLOWHZ	1		/* granularity is 1 second */

/*
 * The ifaddr structure contains information about one address
 * of an interface.  They are maintained by the different address families,
 * are allocated and attached when an address is set, and are linked
 * together so all addresses for an interface can be located.
 */
struct ifaddr {
	struct	sockaddr *ifa_addr;	/* address of interface */
	struct	sockaddr *ifa_dstaddr;	/* other end of p-to-p link */
#define	ifa_broadaddr	ifa_dstaddr	/* broadcast address interface */
	struct	sockaddr *ifa_netmask;	/* used to determine subnet */
	struct	ifnet *ifa_ifp;		/* back-pointer to interface */
	struct	ifaddr *ifa_next;	/* next address for interface */
#ifdef	_KERNEL
	void	(*ifa_rtrequest)(int, struct rtentry *, struct sockaddr *);
#else
	/* check or clean routes (+ or -)'d */
	void	(*ifa_rtrequest) __((int, struct rtentry *, struct sockaddr *));
#endif
	struct	rtentry *ifa_rt;	/* ??? for ROUTETOIF */
	u_short	ifa_flags;		/* mostly rt_flags for cloning */
	u_short ifa_llinfolen;          /* extra to malloc for link info */
	u_int	ifa_refcnt;		/* ref count */
};
#define IFA_ROUTE	RTF_UP		/* route installed */
#define IFA_ARPDISABLED	RTF_REJECT	/* ARP disabled */
/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */
struct	ifreq {
#define	IFNAMSIZ	16
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		int	ifru_flags;
		int	ifru_metric;
		caddr_t	ifru_data;
		int	ifru_value;		/* any generic value */
		u_int	ifru_index;
#if	SEC_NET
		struct  tnet_if *ifru_sec;
#define ifr_sec		ifr_ifru.ifru_sec       /* tnet interface */
#endif	/* SEC_NET */
	} ifr_ifru;
#define	IF_NAMESIZE	IFNAMSIZ
#define	ifr_addr	ifr_ifru.ifru_addr	/* address */
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-to-p link */
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address */
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags */
#define	ifr_metric	ifr_ifru.ifru_metric	/* metric */
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface */
#define	ifr_value	ifr_ifru.ifru_value	/* for use by interface */
#define ifr_index	ifr_ifru.ifru_index	/* interface index */
};

/*
 * structure used to query de and qe for physical addresses
 */
struct ifdevea {
        char    ifr_name[IFNAMSIZ];             /* if name, e.g. "en0" */
        u_char default_pa[6];                   /* default hardware address */
        u_char current_pa[6];                   /* current physical address */
};

struct ifaliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr ifra_addr;
	struct	sockaddr ifra_broadaddr;
	struct	sockaddr ifra_mask;
};

/*
 * Request struct to create interface access filters. Used
 * in SIOCSIFAFILT requests.
 */
struct ifafiltreq {
        char    ifafr_name[IFNAMSIZ];   /* if name, e.g. "en0" */
        u_int   ifafr_cnt;              /* number of entries */
        struct  ifafilt *ifafr_filt;    /* user-defined filter */
};

/*
 * Interface access filter. Filter is variable length as
 * specified by user's ifafiltreq. Filter allocated via
 * NET_MALLOC; one valid filter per interface; new filter
 * outdates existing filter.
 * 
 * Filter entrys contain {addr, mask, action}. {addr, mask}
 * combine to filter packets; {action} gives action for
 * matching packets. "cnt" is reference count for number
 * of hits per filter entry. Filtering is protocol-specific;
 * see netinet/{in,ip_input}.c for IP-style filtering.
 */
struct ifafilt {
	struct	sockaddr ifaf_addr;	/* addr */
	struct	sockaddr ifaf_mask;	/* mask */
	u_int	ifaf_action;		/* action */
	u_int	ifaf_cnt;		/* counter */
};

#define	IFAF_PERMIT	0x1
#define	IFAF_DENY	0x2
#define	IFAF_DENYLOG	0x4

/*
 * IFAF_MAXBUFSIZE = 32Kbytes
 * IFAF_MAXENTRIES = (IFAF_MAXBUFSIZE/sizeof(struct ifafilt)) - 2
 */
#define	IFAF_MAXBUFSIZE	0x8000
#define	IFAF_MAXENTRIES	0x331


/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */
struct	ifconf {
	int	ifc_len;		/* size of associated buffer */
	union {
		caddr_t	ifcu_buf;
		struct	ifreq *ifcu_req;
	} ifc_ifcu;
#define	ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address */
#define	ifc_req	ifc_ifcu.ifcu_req	/* array of structures returned */
};

/*
 * Interface multicast address structure.  There is one of these for each
 * multicast address or range of multicast addresses that we are supposed
 * to listen to on a particular interface.  They are kept in a linked list,
 * rooted in the interfaces's ifnet structure. 
 */
struct ifmulti {
	u_char	ifm_addrlo[6];		/* low  or only address of range */
	u_char	ifm_addrhi[6];		/* high or only address of range */
	struct	ifnet *ifm_ifnet;	/* back pointer to ifnet */
	u_int	ifm_refcount;		/* no. claims to this addr/range */
	struct	ifmulti *ifm_next;	/* ptr to next ifmulti */
};

#ifdef _KERNEL
/*
 * Minimum MTU size for IP: Used by drivers when setting ipmtu.
 */
#define	IP_MINMTU	68

/*
 * Maximum number of loopback (lo) devices allowed
 */
#define LO_DEVS_MAX	255*255*255

/*
 * Loopback (lo) MTU sizes
 */
#define LOMTU   4096	/* default */
#define HIMTU   65535	/* maximum */

/*
 * Maximum number of slip (sl) devices allowed
 */
#define SLIP_DEVS_MAX	64

/*
 * Macro for finding an ifp by name and unit number in the
 * global ifnet list.  Will point to a valid ifp on success,
 * else NULL on failure.  It is assumed callers will be
 * holding the IFNET_SPIN_LOCK.
 */
#define IFP_BYNAMEUNIT(ifp, name, unit) \
	/* struct ifnet *ifp; */ \
	/* char *name; */ \
	/* short unit; */ \
	{ \
	register struct ifnet *_ifp; \
	for (_ifp = ifnet; _ifp; _ifp = _ifp->if_next) \
		if ((strcmp((name), _ifp->if_name) == 0) && \
		    ((unit) == _ifp->if_unit)) { \
			break; \
		    } \
	(ifp) = _ifp; \
	}

/*
 * Structure used by macros below to remember position when stepping through
 * all of the ifmulti records.
  */
struct if_multistep {
	struct ifmulti  *if_ifm;
};

/*
 * Macro for looking up the ifmulti record for a given range of interface
 * multicast addresses connected to a given ifnet structure.  If no matching
 * record is found, "ifm" returns NULL.
 */
#define IF_LOOKUP_MULTI(addrlo, addrhi, ifp, ifm) \
	/* u_char addrlo[6]; */ \
	/* u_char addrhi[6]; */ \
	/* struct ifnet *ifp; */ \
	/* struct ifmulti *ifm; */ \
{ \
	for ((ifm) = (ifp)->if_multiaddrs; \
	    (ifm) != NULL && \
	    (bcmp((ifm)->ifm_addrlo, (addrlo), 6) != 0 || \
	     bcmp((ifm)->ifm_addrhi, (addrhi), 6) != 0); \
		(ifm) = (ifm)->ifm_next); \
}

/*
 * Macro to step through all of the ifmulti records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IF_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "ifm" when there
 * are no remaining records.
 */
#define IF_NEXT_MULTI(step, ifm) \
	/* struct if_multistep step; */  \
	/* struct ifmulti *ifm; */  \
{ \
	if (((ifm) = (step).if_ifm) != NULL) \
		(step).if_ifm = (ifm)->ifm_next; \
}

#define IF_FIRST_MULTI(step, ifp, ifm) \
	/* struct if_multistep step; */ \
	/* struct ifnet *ifp; */ \
	/* struct ifmulti *ifm; */ \
{ \
	(step).if_ifm = (ifp)->if_multiaddrs; \
	IF_NEXT_MULTI((step), (ifm)); \
}
#endif /* _KERNEL */

/*
 * Structure for EEPROM downline upgrades. (Supported by FDDI adapters)
 */
struct ifeeprom {
        char    ife_name[IFNAMSIZ];             /* if name, e.g. "fza0" */
        u_char  ife_data[64];                   /* block of EEPROM data */
        u_int  ife_offset;                     /* byte offset from base */
        u_int  ife_blklen;                     /* len of EEPROM block */
        u_int  ife_lastblk;                    /* True if last block */
};
#define IFE_NOTLAST     0x0     /* Intermediary block of EEPROM image */
#define IFE_LASTBLOCK   0x1     /* Last block of EEPROM image */
#define IFE_SUCCESS     0x0     /* Block of EEPROM successfully written */
#define IFE_RETRY       0x1     /* Retry last block written */
#define IFE_FAIL        0x2     /* Fail entire EEPROM image write sequence */

/*
 * Structure for set adapter's characteristics
 */
struct ifchar {
	char	ifc_name[IFNAMSIZ];
	u_int	ifc_treq;
	u_int	ifc_tvx;
	u_int	ifc_lem;
	u_int  ifc_rtoken;
	u_int  ifc_ring_purger;
	u_int  ifc_cnt_interval;	/* Not applicable to DEFZA */
#define FDX_ENB		1
#define FDX_DIS		2
	int	ifc_full_duplex_mode;	/* Not applicable to DEFZA */
	int	ifc_media_speed;
	int	ifc_media_type;
#define AUTO_ENB        1
#define AUTO_DIS        2
	int     ifc_auto_sense;
};

/*
 * We pass extra options (defined in lan_common.h) by overloading
 * the ifc_media_type field.
 */
#define ifc_extra_options ifc_media_type

/*
 * interface statistics structures
 */
struct estat {				/* Ethernet interface statistics */
	u_short	est_seconds;		/* seconds since last zeroed */
	u_int	est_bytercvd;		/* bytes received */
	u_int	est_bytesent;		/* bytes sent */
	u_int	est_blokrcvd;		/* data blocks received */
	u_int	est_bloksent;		/* data blocks sent */
	u_int	est_mbytercvd;		/* multicast bytes received */
	u_int	est_mblokrcvd;		/* multicast blocks received */
	u_int	est_deferred;		/* blocks sent, initially deferred */
	u_int	est_single;		/* blocks sent, single collision */
	u_int	est_multiple;		/* blocks sent, multiple collisions */
	u_short	est_sendfail_bm;	/*	0 - Excessive collisions */
					/*	1 - Carrier check failed */
					/*	2 - Short circuit */
					/*	3 - Open circuit */
					/*	4 - Frame too long */
					/*	5 - Remote failure to defer */
	u_short	est_sendfail;		/* send failures: (bit map)*/
	u_short	est_collis;		/* Collision detect check failure */
	u_short	est_recvfail_bm;	/*	0 - Block check error */
					/*	1 - Framing error */
					/*	2 - Frame too long */
	u_short	est_recvfail;		/* receive failure: (bit map) */
	u_short	est_unrecog;		/* unrecognized frame destination */
	u_short	est_overrun;		/* data overrun */
	u_short	est_sysbuf;		/* system buffer unavailable */
	u_short	est_userbuf;		/* user buffer unavailable */
	u_int	est_mbytesent;		/* multicast bytes sent */
	u_int	est_mbloksent;		/* multicast blocks sent */
};

struct estat_extended {			/* 64-bit Ethernet interface stats */
        u_long  est_seconds;		/* seconds since last zeroed */

	/* xmit stats: successful */

        u_long  est_bytesent;		/* bytes sent */
        u_long  est_bloksent;		/* blocks (frames) sent */
        u_long  est_mbytesent;		/* multicast bytes sent */
        u_long  est_mbloksent;		/* multicast blocks (frames) sent */
        u_long  est_deferred;		/* initially deferred */
        u_long  est_single;		/* 1 collision */
        u_long  est_multiple;		/* >1 collision */

	/* xmit stats: failed */

        u_long  est_collis;		/* collision detect check failures */
        u_long  est_unrecog;		/* unrecognized frame dest */
        u_long  est_userbuf;		/* user buffer unavailable */
        u_long  est_latecoll;		/* late collisions */
        u_long  est_excesscoll;		/* excessive collisions */
        u_long  est_carrierfail;	/* carrier sense lost */
	u_long	est_shortcirc;		/* short circuit */
	u_long	est_opencirc;		/* open circuit */
	u_long	est_sndlong;		/* frame too long */
        u_long  est_sendfail;		/* total send failures */

	/* recv stats: successful */

        u_long  est_bytercvd;		/* bytes received */
        u_long  est_blokrcvd;		/* blocks (frames) received */
        u_long  est_mbytercvd;		/* multicast bytes received */
        u_long  est_mblokrcvd;		/* multicast blocks (frames) rcvd */

	/* recv stats: failed */

        u_long  est_overrun;		/* data overruns */
        u_long  est_sysbuf;		/* system buffer unavailable */
        u_long  est_unaligned;		/* unaligned frame */
        u_long  est_longframe;		/* frame too long */
        u_long  est_shortframe;		/* frame too short */
        u_long  est_fcsfail;		/* frame check sequence errors */
	u_long	est_badframe;		/* frame error */
        u_long  est_symbolerror;	/* symbol error during carrier */
        u_long  est_recvfail;		/* total receive failures */
	
	/* padding for the future, but must fit in ctrreq
	 *   (512 - 248) / 8 = 33
	 */
	u_long  padding[33];
};

struct dstat {				/* DDCMP pt-to-pt interface statistics */
	u_short	dst_seconds;		/* seconds since last zeroed */
	u_int	dst_bytercvd;		/* bytes received */
	u_int	dst_bytesent;		/* bytes sent */
	u_int	dst_blockrcvd;		/* data blocks received */
	u_int	dst_blocksent;		/* data blocks sent */
	u_short	dst_inbound_bm;		/*	0 - NAKs sent, header crc */
					/*	1 - NAKs sent, data crc */
					/*	2 - NAKs sent, REP response */
	u_char	dst_inbound;		/* data errors inbound: (bit map) */
	u_short	dst_outbound_bm;	/*	0 - NAKs rcvd, header crc */
					/*	1 - NAKs rcvd, data crc */
					/*	2 - NAKs rcvd, REP response */
	u_char	dst_outbound;		/* data errors outbound: (bit map) */
	u_char	dst_remotetmo;		/* remote reply timeouts */
	u_char	dst_localtmo;		/* local reply timeouts */
	u_short	dst_remotebuf_bm;	/*	0 - NAKs rcvd, buffer unavailable */
					/*	1 - NAKs rcvd, buffer too small */
	u_char	dst_remotebuf;		/* remote buffer errors: (bit map) */
	u_short	dst_localbuf_bm;	/*	0 - NAKs sent, buffer unavailable */
					/*	1 - NAKs sent, buffer too small */
	u_char	dst_localbuf;		/* local buffer errors: (bit map) */
	u_char	dst_select;		/* selection intervals elapsed */
	u_short	dst_selecttmo_bm;	/*	0 - No reply to select */
					/*	1 - Incomplete reply to select */
	u_char	dst_selecttmo;		/* selection timeouts: (bit map) */
	u_short	dst_remotesta_bm;	/*	0 - NAKs rcvd, receive overrun */
					/*	1 - NAKs sent, header format */
					/*	2 - Select address errors */
					/*	3 - Streaming tributaries */
	u_char	dst_remotesta;		/* remote station errors: (bit map) */
	u_short	dst_localsta_bm;	/*	0 - NAKs sent, receive overrun */
					/*	1 - Receive overrun, NAK not sent */
					/*	2 - Transmit underruns */
					/*	3 - NAKs rcvd, header format */
	u_char	dst_localsta;		/* local station errors: (bit map) */
};


struct fstat {
        u_short fst_second;             /* seconds since last zeroed */
	u_int	fst_frame;		/* total number of frames seen */ 
	u_int	fst_error;		/* MAC counter frame error */
	u_int 	fst_lost;		/* MAC counter frame count */
        u_int   fst_bytercvd;           /* bytes received */
        u_int   fst_bytesent;           /* bytes sent */
        u_int   fst_pdurcvd;            /* data blocks received */
        u_int   fst_pdusent;            /* data blocks sent */
        u_int   fst_mbytercvd;          /* multicast bytes received */
	u_int   fst_mpdurcvd;           /* multicast blocks received */
        u_int   fst_mbytesent;          /* multicast bytes sent */
        u_int   fst_mpdusent;           /* multicast blocks sent */
	u_short	fst_underrun;		/* transmit underrun error */
        u_short fst_sendfail;           /* sent failures: (bit map)*/
        u_short	fst_fcserror;		/* FCS check failure */
	u_short	fst_fseerror;		/* frame status error */
	u_short	fst_pdualig;		/* frame alignment error */
	u_short	fst_pdulen;		/* frame length error */
	u_short	fst_pduunrecog;		/* frame unrecognized */
	u_short fst_mpduunrecog;	/* multicast frame unrecognized */
        u_short fst_overrun;            /* data overrun */
        u_short fst_sysbuf;             /* system buffer unavailable */
        u_short fst_userbuf;            /* user buffer unavailable */
	u_short fst_ringinit;		/* other station ring reinit. intiated*/
	u_short fst_ringinitrcv;	/* ring reinitialization initiated */
	u_short fst_ringbeacon;		/* ring beacon process initiated */
	u_short fst_ringbeaconrecv;	/* ring beacon process recv */
	u_short fst_duptoken;		/* duplicat token detected */
	u_short fst_dupaddfail;		/* duplicate address test failures */
	u_short	fst_ringpurge;		/* ring purge errors */
	u_short fst_bridgestrip;	/* bridge strip errors */
	u_short fst_traceinit;		/* traces initiated */
	u_short fst_tracerecv;		/* traces received */
	u_short fst_lem_rej;		/* LEM reject count */
	u_short fst_lem_events;		/* LEM events count */
	u_short fst_lct_rej;		/* LCT reject count */
	u_short fst_tne_exp_rej;	/* TNE expired reject count */
	u_short fst_connection;		/* Completed Connection count */
	u_short fst_ebf_error;		/* Elasticity Buffer Errors */
};

/*
 * Same fields as "struct fstat", but all u_long
 */
struct fstat_extended {
	u_long  fst_second;             /* seconds since last zeroed */
	u_long  fst_frame;		/* total number of frames seen */ 
	u_long  fst_error;		/* MAC counter frame error */
	u_long  fst_lost;		/* MAC counter frame count */
	u_long  fst_bytercvd;           /* bytes received */
	u_long  fst_bytesent;           /* bytes sent */
	u_long  fst_pdurcvd;            /* data blocks received */
	u_long  fst_pdusent;            /* data blocks sent */
	u_long  fst_mbytercvd;          /* multicast bytes received */
	u_long  fst_mpdurcvd;           /* multicast blocks received */
	u_long  fst_mbytesent;          /* multicast bytes sent */
	u_long  fst_mpdusent;           /* multicast blocks sent */
	u_long  fst_underrun;		/* transmit underrun error */
	u_long  fst_sendfail;           /* total send failures */
	u_long  fst_fcserror;		/* FCS check failure */
	u_long  fst_fseerror;		/* frame status error */
	u_long  fst_pdualig;		/* frame alignment error */
	u_long  fst_pdulen;		/* frame length error */
	u_long  fst_pduunrecog;		/* frame unrecognized */
	u_long  fst_mpduunrecog;	/* multicast frame unrecognized */
	u_long  fst_overrun;            /* data overrun */
	u_long  fst_sysbuf;             /* system buffer unavailable */
	u_long  fst_userbuf;            /* user buffer unavailable */
	u_long  fst_ringinit;		/* other station ring reinit. intiated*/
	u_long  fst_ringinitrcv;	/* ring reinitialization initiated */
	u_long  fst_ringbeacon;		/* ring beacon process initiated */
	u_long  fst_ringbeaconrecv;	/* ring beacon process recv */
	u_long  fst_duptoken;		/* duplicat token detected */
	u_long  fst_dupaddfail;		/* duplicate address test failures */
	u_long  fst_ringpurge;		/* ring purge errors */
	u_long  fst_bridgestrip;	/* bridge strip errors */
	u_long  fst_traceinit;		/* traces initiated */
	u_long  fst_tracerecv;		/* traces received */
	u_long  fst_lem_rej;		/* LEM reject count */
	u_long  fst_lem_events;		/* LEM events count */
	u_long  fst_lct_rej;		/* LCT reject count */
	u_long  fst_tne_exp_rej;	/* TNE expired reject count */
	u_long  fst_connection;		/* Completed Connection count */
	u_long  fst_ebf_error;		/* Elasticity Buffer Errors */
};

/* 
 * FDDI MIB structures 
 */

/* SMT group */

struct fddismt {
	short   smt_number;             /* SMT number */
	short	smt_index;		/* SMT FDDI SMT index */	
	u_char	smt_stationid[8];	/* FDDI station id */ 
	u_short	smt_opversionid;	/* operation version id */
	u_short	smt_hiversionid;	/* highest version id */
	u_short	smt_loversionid;	/* lowest version id */
	short 	smt_macct;		/* number of MACs */
	short	smt_nonmasterct;	/* number of non master port */
	short	smt_masterct;		/* number of master port */
	short   smt_pathsavail;		/* available path type */
	short	smt_configcap;		/* configuration capabilities */
	short	smt_configpolicy;	/* configuration policy */
	u_short	smt_connectpolicy;	/* connection policy */
	u_short	smt_timenotify;		/* neighbor notification prot. time*/
	short	smt_statusreport;	/* status reporting protocol */
	short	smt_ecmstate;		/* state of ECM state machine */
	short	smt_cfstate;		/* CF_state */
	short	smt_holdstate;		/* current state of Hold function */
	short	smt_remotedisconn;	/* remotely disconnection flag */ 
	u_char	smt_msgtimestamp[8];	/* timestamp for SMT frames */
	u_char	smt_trantimestamp[8];	/* timestamp for last event */
	u_char	smt_setinfo[12];	/* station last parameter change */
	u_char	smt_lastsetid[8];	/* Last station ID change */
	short	smt_action;		/* SMT station action */
}; 

/*--------------------------------------------------------------*/
/*								*/
/* FDDI Station/Link/Physical Port Attributes & Status:		*/
/*								*/
/* defined by the DNA-FDDI Data Link Functional Spec		*/
/* version 1.0.1 chapter 5.					*/
/*								*/
/*--------------------------------------------------------------*/	

struct fddi_dna_attributes {

	/* STATION Attributes */

	u_char	stationid[8];		/* FDDI station id */ 
	short   stationtype;		/* FDDI station type */
	u_short	opversionid;		/* operation version id */
	u_short	hiversionid;		/* highest version id */
	u_short	loversionid;		/* lowest version id */

	/* LINK Attributes */

	u_char  link_addr[6];		/* LINK address */
	u_int	t_req;			/* TRT request */
	u_int  	tvx;			/* Valid Transmission time */
	u_int	rtoken_timeout;		/* restricted token timeout */
	short	ring_purge_enable;	/* ring purger enable */

	/* PHY Attributes */
		
	u_char	phy_type;		/* PHY type */
	u_char	pmd_type;		/* PMD type */
        u_int  	lem_threshold; 		/* lem threshold */
};

struct fddi_dna_status {

	/* STATION Status */

	short   station_state;		/* station state */
	u_char	laststationid[8];	/* Last FDDI station id */ 
	u_char	station_uid[8];		/* station uid */ 

	/* LINK Status */

	short   link_state;		/* LINK state */
	u_char	link_uid[8];		/* link uid */ 
	u_int	neg_trt;		/* Negotiated TRT */
	short   dup_add_flag;		/* duplicate address flag */
	u_char  upstream[6];		/* Upstream Neighbor */
	u_char  oldupstream[6];		/* Old Upstream Neighbor */
	short   upstreamdaf;		/* Upstream Neighbor duplicate address flag */
	u_char  downstream[6];		/* Downstream Neighbor */
	u_char  olddownstream[6];	/* Old Downstream Neighbor */
	short   ring_purge_state;	/* ring purge state */
	u_char 	frame_strip_mode;	/* frame strip mode */
	u_char	ring_error;		/* ring error reasons */
	short	loopback;		/* loopback mode - true/false */
	short 	ring_latency;		/* currently measured ring latency */
	u_char	ring_purge_addr[6];	/* ring purger address */	

	/* PHY Status */

	u_char 	phy_state;		/* Physical state */
	u_char	phy_uid[8];		/* phy uid */ 
	u_char	neighbor_phy_type;	/* Neighborshort */		   
	u_int	phy_link_error;		/* phy link error estimate */
	u_char  broken_reason;		/* phy port broken reason */
	u_char  rej_reason;		/* reject reason */
};

struct fddiDNA_status {
	struct fddi_dna_attributes	attr;
	struct fddi_dna_status		stat;	
};
	
struct fstatus {
	short	led_state;		/* LED State */
	short   rmt_state;		/* RMT state */
	short   link_state;		/* LINK state */
	short   dup_add_test;		/* duplicate address test */
	short   ring_purge_state;	/* ring purge state */
	u_int  neg_trt;		/* Negotiated TRT */
	u_char  upstream[6];		/* Upstream Neighbor */
	u_char  downstream[6];		/* downstream Neighbor */
	u_char	una_timed_out;		/* una timed out flag */
	u_char 	frame_strip_mode;	/* frame strip mode */
	u_char	claim_token_mode;	/* claim token yield mode */
	u_char 	phy_state;		/* Physical state */
	u_char	neighbor_phy_type;	/* Neighborshort */		   
	u_char  rej_reason;		/* reject reason */
	u_int	phy_link_error;		/* phy link error estimate */
	u_char	ring_error;		/* ring error reasons */
	u_int	t_req;			/* TRT request */
	u_int  tvx;			/* TVX value */
	u_int  t_max;			/* TRT maximum */
        u_int  lem_threshold;          /* lem threshold */
	u_int	rtoken_timeout;		/* restricted token timeout */
	u_char  fw_rev[4];		/* firmware revision */
	u_char  phy_rev[4];		/* ROM revision */	
	u_char	pmd_type;		/* PMD type */
	u_char  dir_beacon[6];		/* Last Direct Beacon address */
	short	smt_version;		/* SMT version */
	short   state;			/* Adapter State */
	u_char	dir_beacon_una[6];	/* UNA from last direct beacon addr. */
	short	cnt_interval;		/* Interval to get counter updates */
	short	full_duplex_mode;	/* enabling/disabling duplex mode */
	short	full_duplex_state;	/* state, if enabled */
};	

/* MAC group */

struct fddimac {
	short   mac_number;             /* MAC number */
	short   mac_smt_index;		/* MAC SMT index */
	short   mac_index;		/* MAC index */
	short	mac_fsc;		/* MAC frame status capabilities */
	u_int	mac_gltmax;		/* Greastest lower bound of T_max */
	u_int	mac_gltvx;		/* Greastest lower bound of TVX */
	short	mac_paths;		/* path types available */
	short	mac_current;		/* association of the MAC with path*/
	u_char	mac_upstream[6];	/* upstream neighbor */
	u_char	mac_oldupstream[6];	/* previous upstream neighbor */
	short	mac_dupaddrtest;	/* duplicate address test */
	short   mac_pathsreq;		/* paths requested */
	short	mac_downstreamtype;	/* downstream PC-type */
	u_char	mac_smtaddress[6];	/* MAC address for SMT */
	u_int	mac_treq;		/* TRT time */
	u_int	mac_tneg;		/* Neg. TRT time */
	u_int	mac_tmax;		/* max. TRT time */
	u_int	mac_tvx;		/* TVX value */
	u_int	mac_tmin;		/* min. TRT time */
	short	mac_framestatus;	/* current frame status */
	int	mac_counter;		/* frame counters */
	int	mac_error;		/* frame error counters */
	int	mac_lost;		/* frame lost counter */
	short	mac_rmtstate;		/* Ring Management state */
	short	mac_dupaddr;		/* duplicate address flag */
	short	mac_condition;		/* MAC condition */
	short   mac_action;		/* MAC action */
	short	mac_updupaddr;		/* upstream duplicate address flag */
	short	mac_frame_error_thresh;	/* frame error threshold */
	short 	mac_frame_error_ratio;	/* frame error ratio */
	short	mac_chip_set;		/* the chip set used */
};

/* PATH group */

struct fddipath {
	short	path_configindex;	/* path configuration index */
	short	path_type;		
	short	path_portorder;			
	u_int	path_sba;		/*synchronous bandwidth allocation*/ 
	short	path_sbaoverhead;	/* SBA overhead */
	short	path_status;		/* path status */
};

/* PORT group */

struct fddiport {
	short   port_number;            /* port number */
	short	port_smt_index;		/* port SMT index */
	short	port_index;		/* port index */
	short	port_pctype;		/* value of the port's PC_type */
	short	port_pcneighbor;	/* PC_neighbor of remote port*/
	short   port_connpolicy;	/* connection policies */
	short	port_remoteind;		/* remote MAC indicated */
	short 	port_CEstate;		/* Current Configuration state */
	short   port_pathreq;		/* path request */
	u_short port_placement;		/* upstream MAC */
	short	port_availpaths;	/* available paths */
	u_int	port_looptime;		/* time for MAC loval loop */
	u_int	port_TBmax;		/* TB_max */
	short	port_BSflag;		/* the Break state, BF_flag */
	u_int	port_LCTfail;		/* counter for Link confidence test */
	short	port_LerrEst;		/* Link error estimate */
	u_int	port_Lemreject;		/* Link reject count */
	u_int	port_Lem;		/* Link error monitor count */
	short	port_baseLerEst;	/* value of port Ler Estimate */
	u_int	port_baseLerrej;	/* Ler reject count */
	u_int	port_baseLer;		/* Ler count */
	u_char	port_baseLerTime[8];	/* Ler timestamp */	
	short   port_Lercutoff;		/* error rate cut off limit */
	short	port_alarm;		/* error rate cause alarm generate*/
	short	port_connectstate;	/* connect state */
	short   port_PCMstate;		/* PCM state */
	short	port_PCwithhold;	/* PC_withhold */
	short	port_Lercondition;	/* true if Ler-Est <= Ler_alarm */
	short   port_action;		/* PORT action */
	short	port_chip_set;		/* PORT chip set */
};

/* Attachment group */

struct	fddiatta {
	short	atta_number;            /* attachment number */
	short 	atta_smt_index;		/* attachment SMT index */
	short 	atta_index;		/* attachment index */
	short	atta_class;		/* attachment class */
	short	atta_bypass;		/* attachment optical bypass */	
	short	atta_IMaxExpiration;	/* attachment I_Max Expiration */	
	short	atta_InsertedStatus;	/* Inserted status */	
	short	atta_InsertPolicy;	/* Insert policy */	
};

		/* Information here is conformant to SMT 7.2 */

    /* SMT GROUP */
struct smtmib_smt {

	u_char      smt_station_id[8];
	u_int       smt_op_version_id;
	u_int       smt_hi_version_id;
	u_int       smt_lo_version_id;
	u_char      smt_user_data[32];
	u_int       smt_mib_version_id;
	u_int       smt_mac_ct;
	u_int       smt_non_master_ct;
	u_int       smt_master_ct;
	u_int       smt_available_paths;
	u_int       smt_config_capabilities;
	u_int       smt_config_policy;
	u_int       smt_connection_policy;
	u_int       smt_t_notify;
	u_int       smt_stat_rpt_policy;
	u_int       smt_trace_max_expiration;
	u_int       smt_bypass_present;
	u_int       smt_ecm_state;
	u_int       smt_cf_state;
	u_int       smt_remote_disconnect_flag;
	u_int	    smt_station_status;
	u_int       smt_peer_wrap_flag;
#ifdef __arch64__
	u_long      smt_msg_time_stamp;	/* 64 bit counter */
	u_long      smt_transition_time_stamp; /* 64 bit counter */
#else
	u_int       smt_msg_time_stamp_ms;	/* 64 bit counter */
	u_int       smt_msg_time_stamp_ls;
	u_int       smt_transition_time_stamp_ms; /* 64 bit counter */
	u_int       smt_transition_time_stamp_ls;
#endif /* __arch64__ */
};

	/* MAC GROUP */
struct smtmib_mac {
	u_int       mac_frame_status_functions;
	u_int       mac_t_max_capability;
	u_int       mac_tvx_capability;
	u_int       mac_available_paths;
	u_int       mac_current_path;
	u_char      mac_upstream_nbr[8];
	u_char      mac_downstream_nbr[8];
	u_char      mac_old_upstream_nbr[8];
	u_char      mac_old_downstream_nbr[8];
	u_int       mac_dup_address_test;
        u_int       mac_requested_paths;
      	u_int       mac_downstream_port_type;
	u_char      mac_smt_address[8];
    	u_int       mac_t_req;
	u_int       mac_t_neg;
	u_int       mac_t_max;
	u_int       mac_tvx_value;
	u_int       mac_frame_error_threshold;
	u_int       mac_frame_error_ratio;
	u_int       mac_rmt_state;
	u_int       mac_da_flag;
	u_int       mac_unda_flag;
	u_int       mac_frame_error_flag;
	u_int       mac_ma_unitdata_available;
	u_int       mac_hw_present;
	u_int       mac_ma_unitdata_enable;
};

	/* PATH GROUP */

struct smtmib_path {
	u_char      path_configuration[32];
	u_int       path_tvx_lower_bound;
	u_int       path_t_max_lower_bound;
	u_int       path_max_t_req;
};

	/* PORT GROUP */
struct smtmib_port {
	u_int       port_my_type[2];
	u_int       port_neighbor_type[2];
	u_int       port_connection_policies[2];
	u_int       port_mac_indicated[2];
	u_int       port_current_path[2];
	u_int       port_requested_paths[2];
	u_int       port_mac_placement[2];
	u_int       port_available_paths[2];
	u_int       port_pmd_class[2];
	u_int       port_connection_capabilities[2];
	u_int       port_bs_flag[2];
	u_int       port_ler_estimate[2];
	u_int       port_ler_cutoff[2];
	u_int       port_ler_alarm[2];
	u_int       port_connect_state[2];
	u_int       port_pcm_state[2];
	u_int       port_pc_withhold[2];
	u_int       port_ler_flag[2];
	u_int       port_hardware_present[2];
};

struct decext_mib {
	/* SMT GROUP */
	u_int 	esmt_station_type;

	/* MAC GROUP */
	u_int	emac_link_state;
	u_int	emac_ring_purger_state;
	u_int	emac_ring_purger_enable;
	u_int	emac_frame_strip_mode;
	u_int	emac_ring_error_reason;
	u_int	emac_up_nbr_dup_addr_flag;
	u_int	emac_restricted_token_timeout;

	/* PORT GROUP */
	u_int	eport_pmd_type[2];
	u_int	eport_phy_state[2];
	u_int	eport_reject_reason[2];

	/* FDX (Full-Duplex) GROUP */
	u_int	efdx_enable;        /* Valid only in SMT 7.2 */
	u_int	efdx_op;            /* Valid only in SMT 7.2 */
	u_int	efdx_state;         /* Valid only in SMT 7.2 */
};




#define CTR_ETHER 0			/* Ethernet interface */
#define CTR_DDCMP 1			/* DDCMP pt-to-pt interface */
#define CTR_FDDI 2			/* FDDI interface */
#define FDDIMIB_SMT	3		/* FDDI MIB SMT group */
#define FDDIMIB_MAC	4		/* FDDI MIB MAC group */
#define FDDIMIB_PATH	5		/* FDDI MIB PATH group */
#define FDDIMIB_PORT	6		/* FDDI MIB PORT group */
#define FDDIMIB_ATTA	7		/* FDDI MIB Attatchment Group */
#define FDDI_STATUS	8		/* FDDI status */
#define FDDISMT_MIB_SMT	9		/* FDDI SMT SMT MIB values */
#define FDDISMT_MIB_MAC	10		/* FDDI SMT MAC values */
#define FDDISMT_MIB_PATH	11	/* FDDI SMT PATH values */
#define FDDISMT_MIB_PORT	12	/* FDDI SMT PORT values */
#define FDDIDECEXT_MIB		13	/* FDDI DEC Extended MIB values */
#define CTR_TRN			14	/* Token ring counters */
#define TRN_CHAR		15	/* Token ring characteristics */
#define TRN_MIB_ENTRY		16	/* Token ring mib entry */
#define TRN_MIB_STAT_ENTRY	17	/* Token ring mib status entry */
#define TRN_MIB_TIMER_ENTRY     18	/* Token ring mib timer entry */
#define FDDIMIB_PORT_B		19	/* FDDI MIB PORT group */
#define FDDISMT_MIB_PORT_B	20	/* FDDI MIB PORT group */
#define DS1_CONFIG              21      /* DS1 mib current entry */
#define DS1_CURRENT             22      /* DS1 mib current entry */
#define DS1_INTERVAL            23      /* DS1 mib interval entry */
#define DS1_TOTAL               24      /* DS1 mib total entry */
#define DS1_FAR_END_CURRENT     25      /* DS1 mib far end current entry */
#define DS1_FAR_END_INTERVAL    26      /* DS1 mib far end interval entry */
#define DS1_FAR_END_TOTAL       27      /* DS1 mib far end total entry */
#define DS1_FRAC                28      /* DS1 mib frac entry */
#define CTR_IPSTAT		29	/* ip protocol interface counters since zeroed */
#define CTR_IPSTATBOOT		30	/* ip protocol interface counters since boot */
#define CTR_ICMPSTAT		31	/* icmp protocol interface counters since zeroed */
#define CTR_ICMPSTATBOOT	32	/* icmp protocol interface counters since boot */
#define CTR_TCPSTAT		33	/* tcp protocol interface counters since zeroed */
#define CTR_TCPSTATBOOT		34	/* tcp protocol interface counters since boot */
#define CTR_UDPSTAT		35	/* udp protocol interface counters since zeroed */
#define CTR_UDPSTATBOOT		36	/* udp protocol interface counters since boot */
#define CTR_IGMPSTAT		37	/* igmp protocol interface counters since zeroed  */
#define CTR_IGMPSTATBOOT	38	/* igmp protocol interface counters since boot */
#define CTR_RTSTAT		39	/* ip routing counters since zeroed */
#define CTR_RTSTATBOOT		40	/* ip routing counters since boot */
#define CTR_MRTSTAT		41	/* multicast ip routing counters since zeroed */
#define CTR_MRTSTATBOOT		42	/* multicast ip routing coutners since boot */
#define CTR_ETHER_EXTENDED	43	/* Extended Ethernet interface */       
#define CTR_FDDI_EXTENDED	44	/* Extended FDDI interface */       
#define CTR_IPSECSTAT		45	/* IPsec protocol interface counters since zeroed */
#define CTR_IPSECSTATBOOT	46	/* IPsec protocol interface counters since boot */

#define ctr_ether ctr_ctrs.ctrc_ether
#define ctr_ether_ext ctr_ctrs.ctrc_ether_ext
#define ctr_ddcmp ctr_ctrs.ctrc_ddcmp
#define ctr_fddi  ctr_ctrs.ctrc_fddi
#define ctr_fddi_ext  ctr_ctrs.ctrc_fddi_ext
#define sts_fddi  ctr_ctrs.status_fddi
#define dna_fddi  ctr_ctrs.dna_status_fddi
#define fmib_smt  ctr_ctrs.smt_fddi
#define fmib_mac  ctr_ctrs.mac_fddi
#define fmib_path  ctr_ctrs.path_fddi
#define fmib_port  ctr_ctrs.port_fddi
#define fmib_atta  ctr_ctrs.atta_fddi
#define smib_smt  ctr_ctrs.smt_smt
#define smib_mac  ctr_ctrs.smt_mac
#define smib_port  ctr_ctrs.smt_port
#define smib_path  ctr_ctrs.smt_path
#define decmib_ext ctr_ctrs.dec_ext

#define CTR_HDRCRC	0		/* header crc bit index */
#define CTR_DATCRC	1		/* data crc bit index */
#define CTR_BUFUNAVAIL	0		/* buffer unavailable bit index */

/*
 * Interface counter ioctl request
 */
struct ctrreq {
	char    ctr_name[IFNAMSIZ];     /* if name */
	        char    ctr_type;               /* type of interface */
        union {
                struct estat ctrc_ether;		/* ethernet counters */
                struct estat_extended ctrc_ether_ext;	/* extended ethernet counters */
                struct dstat ctrc_ddcmp;		/* DDCMP pt-to-pt counters */
                struct fstat ctrc_fddi; 		/* FDDI counters */
                struct fstat_extended ctrc_fddi_ext; 	/* extended FDDI counters */
                struct fstatus status_fddi; 		/* FDDI stsatus */
                struct fddiDNA_status dna_status_fddi; 	/* FDDI status per DNA spec */
                struct fddismt smt_fddi;		/* fddi SMT attributes */
                struct fddimac mac_fddi;		/* fddi MAC attributes */
                struct fddipath path_fddi;		/* fddi PATH attributes */
                struct fddiport port_fddi; 		/* fddi PORT attributes */
                struct fddiatta atta_fddi; 		/* fddi attatch attributes */
		struct smtmib_smt	smt_smt;   	/* smt mib attributes */
		struct smtmib_mac	smt_mac;   	/* smt mib attributes */
		struct smtmib_path	smt_path;  	/* smt mib attributes */
		struct smtmib_port	smt_port;  	/* smt mib attributes */
		struct decext_mib	dec_ext;   	/* dec extended mib */
		struct trnchar	trnchar;		/* Token ring characteristics */
		struct trncount	trncount;		/* Token ring counters */
		struct dot5Entry dot5Entry;		/* Token ring MIB counters */
		struct dot5StatsEntry dot5StatsEntry; 	/*Token ring MIB stats */
		struct dot5TimerEntry dot5TimerEntry; 	/*Token ring MIB Timers */
		unsigned char   protos[512];		/* protocol stat structs can't be bigger */
        } ctr_ctrs;
};

union mac_addr {
	u_short	saddr[3];
	u_char	caddr[6];
};

/*
 * NetRAIN interface list structure
 */
typedef struct nrset_t {
    char  name[IFNAMSIZ];
} nrset_t;

struct if_nrset {
    char  nr_name[IFNAMSIZ];
    int   nr_len;
    int   nr_cnt;
    nrset_t *nr_buf;
};

/*
 * Define the event names
 */
#define EVENT_NIFF_UP		_EvmSYSTEM_EVENT_NAME("hw.net.niff.up")
#define EVENT_NIFF_ALERT	_EvmSYSTEM_EVENT_NAME("hw.net.niff.alert")
#define EVENT_NIFF_DOWN		_EvmSYSTEM_EVENT_NAME("hw.net.niff.down")
#define EVENT_NETRAIN_UP	_EvmSYSTEM_EVENT_NAME("hw.net.netrain.up")
#define EVENT_NETRAIN_ALERT	_EvmSYSTEM_EVENT_NAME("hw.net.netrain.alert")
#define EVENT_NETRAIN_DOWN	_EvmSYSTEM_EVENT_NAME("hw.net.netrain.down")

typedef enum niffstate {NIFF_UNKNOWN, NIFF_UP, NIFF_ALERT, NIFF_DOWN} niffstate_t;

typedef enum ifstate {NIFF_INIT, NIFF_GREEN, NIFF_YELLOW, NIFF_ORANGE, NIFF_RED, NIFF_DEAD, NIFF_IF_DOWN} ifstate_t;

typedef struct monitored_interface_prev_state {
    ifstate_t current_state;
    niffstate_t status;
    niffstate_t event;
    int next_time; 
    int current_interval; 
    int time_to_dead;
} mif_prev_state_t;

/*
 *   legal values in flags field of mif_t
 */
#define	MIF_NETRAIN		0x1		/* interface is monitored
						 * on behalf of the NetRAIN.  
						 */
#define	MIF_QUORUMLOSS		0x2		/* hold due to QUORUM loss */
#define	MIF_MILLISECONDS	0x4		/* times are in milliseconds */ 

typedef struct monitored_interface {
    char name[20]; /* e.g. "ln0", "fta0"... */
    ifstate_t current_state;
    niffstate_t status; /* only NIFF_UP or NIFF_DOWN is recorded here.
			 * all NIFF_ALERT is filtered out.
			 * This variable is not sent as part of EVM 
			 * message.
			 */
    niffstate_t event;
    int t1;     /* time to wait before we change state from green to yellow */
    int dt;     /* time interval between yellow through red transitions */
    int t2;     /* total time to go from green to dead state (giving rise
                 * to the relationship: t2 >= t1 + 2dt, but practically
                 * time will elapse between the transition from red to
                 * dead so it's more like t2 > t1 + 2dt)
                 */
    int flags;
    int next_time; /* countdown to when we have to peek at this interface */
    int current_interval; /* how often we actually peek at this interface */
                          /* this number gets smaller if we start to suspect */
                          /* that this interface is dead */
    int time_to_dead; /* countdown to when we declare this interface to be dead */
    u_int pcount; /* the last snapshot of the received packet counter */
    pid_t pid;
    mif_prev_state_t prev_state; /* saved for quorum loss */
    struct monitored_interface *next;
} mif_t;

#ifdef	_KERNEL
#include "net/if_arp.h"
extern struct	ifnet *ifnet, *ifnet_detached, *ifnet_lost, loif;
extern REPLICATED int	lo_devs, lo_devs_cur;
extern REPLICATED int	nslip, nslip_cur;
extern int	ifnet_debug;
extern int	lo_def_ip_mtu;
#else
#include <net/if_arp.h>
#endif

#ifndef _KERNEL
/*
 * following are the prototypes and structure definitions for the
 * interface identification APIs defined in RFC2133
 */

struct if_nameindex {
	unsigned int	 if_index;
	char		*if_name;
};

extern char *			if_indextoname	 __((unsigned int, char *));
extern unsigned int		if_nametoindex	 __((const char *));
extern struct if_nameindex *	if_nameindex	 __((void));
extern void			if_freenameindex __((struct if_nameindex *));
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NET_IF_H_ */
