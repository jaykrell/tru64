/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: if_ether.h,v $
 * Revision 4.2.38.2  2008/03/06  07:22:40  Manish_R_Kulkarni
 * 	Added new ethernet type ETHERTYPE_ICSNODEDETECT
 * 	for ICSTCP heartbeat implementation.
 *
 * Revision 4.2.38.1  2002/10/16  14:42:21  Michael_Daniele
 * 	Redefined ether_tagheader to be the actual 802.1Q tag header per spec.
 * 	Cleaned up other defs and TCI macros.
 *
 * Revision 4.2.34.3  2002/07/10  18:36:04  Paul_Moore
 *  Forward ported changes by Mike Daniele to add 802.1Q VLAN support:
 *   o Added ETHERTYPE_TAG, _ether_xtra and ether_tagheader defs.
 *   o Added TCI formatting macros.
 *
 * Revision 4.2.34.2  2002/01/29  21:18:45  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.2.34.1  2001/12/17  20:54:46  Vladislav_Yasevich
 * 	Added IFNET_ARP_CACHE_LOCKTERMINATE() macro (qar 85357).
 *
 * Revision 4.2.27.2  2000/01/28  21:09:58  Brian_Haley
 * 	Per-interface ARP cache support:
 * 	- added ifnet_arp_cache_head struct
 * 	- added macros to get, lock and unlock each ARP cache, as well as
 * 	get, ref and unref ARP entries
 *
 * Revision 4.2.27.1  1999/10/18  20:20:44  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 4.2.23.4  1999/06/08  18:09:39  Jack_McCann
 * 	IPv6 EAK X6.3 merge to Steel BL23
 * 	- do not merge RTF_ANNOUNCE define, not used in ipv6os pool
 * 	- move RTF_ISGATEWAY and RTF_LLVALID to <net/route.h>
 * 	[1999/06/08  15:51:17  Jack_McCann]
 *
 * Revision 4.2.23.3  1998/10/20  20:26:15  Geraldine_Harter
 * 	Add '#if NETSYNC_LOCK' statement.
 * 	[1998/10/19  20:26:52  Geraldine_Harter]
 * 
 * Revision 4.2.23.2  1998/06/22  20:59:04  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 
 * 	IPv6 V4.0D merge
 * 
 * 	Revision 1.11  1998/02/06  18:17:02  mccann
 * 	IPv4 ARP table restoration
 * 
 * 	Jack McCann		03-Feb-1998
 * 	- remove M_OFFRING, no longer used
 * 	- as part of IPv4 arp table restoration, remove llinfo_arp structure,
 * 	  sockaddr_inarp structure, and arp_rtrequest() prototype
 * 	- remove nd6_cache_rtrequest() and nd6_cache_resolve() prototypes,
 * 	  they don't belong in this header file
 * 
 * 	Revision 1.10  1997/02/18  19:34:28  mccann
 * 	DIGITAL UNIX V4.0B merge
 * 
 * 	Revision 1.9  1996/02/02  23:48:49  thomas
 * 	FDDI support
 * 
 * 	Revision 1.8  1996/01/31  16:48:59  thomas
 * 	Add RTF_ISGATEWAY
 * 
 * 	Revision 1.7  1996/01/19  18:03:02  thomas
 * 	minor cleanup
 * 
 * 	Revision 1.6  1995/09/05  14:45:36  thomas
 * 	add arp_rtrequest
 * 
 * 	Revision 1.5  1995/09/04  21:56:54  thomas
 * 	incorporate new if_ether.c from bsd 4.4
 * 
 * 	Revision 1.4  1995/09/02  19:44:30  thomas
 * 	Add nd6_cache_rtrequest (for in6.c)
 * 
 * 	Revision 1.3  1995/09/02  17:07:41  thomas
 * 	remove stale nd6 function prototypes.
 * 	Add nd6_cache_resolve for if_output
 * 
 * 	Revision 1.2  1995/08/29  21:04:10  thomas
 * 	IPv6 neighbor discovery hooks
 * 
 * 	Revision 1.1  1995/08/24  19:28:27  root
 * 	Initial revision
 * 	[1998/06/16  14:57:56  Jack_McCann]
 * 
 * Revision 4.2.18.4  1997/12/16  18:51:27  Michael_Enright
 * 	revert to v4.2.18.2
 * 	[1997/12/10  15:34:26  Michael_Enright]
 * 
 * Revision 4.2.18.3  1997/09/29  20:43:19  Michael_Enright
 * 	add llinfo_arp, sockaddr_inarp
 * 	remove arptab/ARPTAB stuff, which is obsolete
 * 	[1997/09/26  01:52:00  Michael_Enright]
 * 
 * Revision 4.2.18.2  1996/05/03  18:26:57  Tony_Bono
 * 	Bravo to Steel merge
 * 	[1996/05/03  15:50:48  Tony_Bono]
 * 
 * Revision 4.2.14.3  1996/03/10  15:36:43  Ray_Lanza
 * 	merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:13:38  Ray_Lanza]
 * 
 * Revision 4.2.16.2  1995/12/19  22:04:24  Rajul_Shah
 * 	Add ETHER_BANDWIDTH_100MB #define in support of Fast Ethernet.
 * 	[1995/12/18  14:59:55  Rajul_Shah]
 * 
 * Revision 4.2.14.2  1995/10/25  19:58:07  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:28:06  Ray_Lanza]
 * 
 * Revision 4.2.10.10  1994/05/30  00:01:49  Heather_Gray
 * 	Changed arptab lock from complex to simple.
 * 	[1994/05/26  19:48:11  Heather_Gray]
 * 
 * Revision 4.2.10.9  1994/05/10  21:57:09  Julia_Fey
 * 	Changed ac_ipaddr field of arpcom structure to ac_flag.
 * 	[1994/05/09  20:29:47  Julia_Fey]
 * 
 * Revision 4.2.10.8  1994/03/18  21:53:52  Ernie_Petrides
 * 	Convert locking calls for arptab_lock to use the ulock_*
 * 	versions to allow for call patch-out in lockmode 0.
 * 	[1994/03/17  00:29:50  Ernie_Petrides]
 * 
 * Revision 4.2.10.7  1994/02/11  17:25:36  Geraldine_Harter
 * 	Remove unused global arp lock locks and macros.
 * 	[1994/02/10  21:32:35  Geraldine_Harter]
 * 
 * Revision 4.2.10.6  1993/11/15  23:49:12  John_Dustin
 * 	change lock_init2 to lock_setup using arptab_li
 * 	[1993/10/27  15:43:23  John_Dustin]
 * 
 * Revision 4.2.10.5  1993/10/07  21:59:40  Geraldine_Harter
 * 	Merge with Sterling BL6.  For completeness, all revision logs follow.
 * 	Note that some of the changes have been made prior to this merge:
 * 
 * 	Revision 4.2.5.5  1993/07/27  15:50:54  Uttam_Shikarpur
 * 	Added a pointer to the dli_ifnet structure and removed the unwanted
 * 	fields that are no longer used by DLI.
 * 	[1993/07/26  13:54:21  Uttam_Shikarpur]
 * 
 * 	Revision 4.2.5.4  1993/06/29  17:55:11  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:44:41  SJ_Lee]
 * 
 * Revision 4.2.10.4  1993/09/15  13:52:22  Rajul_Shah
 * 	Merged revision 4.2.5.3 from Sterling. This is needed by
 * 	all ethernet drivers coming over from that pool.
 * 	[1993/09/14  20:18:06  Rajul_Shah]
 * 
 * Revision 4.2.10.3  1993/08/18  23:26:32  Peter_Schulter
 * 	SVR4 Compatable STREAMS infrastructure premerge
 * 	[1993/08/18  18:07:50  Peter_Schulter]
 * 
 * Revision 4.2.10.2  1993/06/25  21:17:55  Geraldine_Harter
 * 	Merged selected OSF1.2 changes (from OSF's net/if_arp.h).
 * 	[1993/06/25  20:29:44  Geraldine_Harter]
 * 
 * Revision 4.2.2.9  1992/12/12  16:04:57  Tim_Hoskins
 * 	Fix typo in comment.
 * 	[92/12/12  16:03:28  Tim_Hoskins]
 * 
 * Revision 4.2.2.8  92/12/11  17:56:04  Tim_Hoskins
 * 	Remove support for ADU variant of ETHERMTU.
 * 	[92/12/11  17:55:24  Tim_Hoskins]
 * 
 * Revision 4.2.2.7  92/11/06  15:36:55  Heather_Gray
 * 	Add struct ether_addr for use by applications.
 * 	[92/11/06  14:55:16  Heather_Gray]
 * 
 * Revision 4.2.2.6  92/08/14  15:10:06  Tim_Hoskins
 * 	Restore ETHERMIN to proper value, as per MIPS version.
 * 	[92/08/07  00:54:50  Tim_Hoskins]
 * 
 * Revision 4.2.2.5  92/02/27  20:12:12  Tim_Hoskins
 * 	Further qualified previous changes to ETHERMTU with ifdef _KERNEL
 * 	[92/02/27  20:11:42  Tim_Hoskins]
 * 
 * Revision 4.2.2.4  92/02/11  15:48:26  Tim_Hoskins
 * 	Bracketed previous changes to ETHERMTU with ifdef __alpha
 * 	[92/02/11  15:47:03  Tim_Hoskins]
 * 
 * Revision 4.2.2.3  92/02/04  20:54:55  Tim_Hoskins
 * 	Because of differences between ADU and everybody else,
 * 	and the need to support ADU's for awhile longer,
 * 	we needed to make ETHERMTU a function of cpu type.
 * 	[92/02/04  20:54:21  Tim_Hoskins]
 * 
 * Revision 4.2.2.2  92/01/20  13:04:38  Tim_Hoskins
 * 	Alpha 64-bit network support.
 * 	[92/01/20  13:00:16  Tim_Hoskins]
 * 
 * Revision 4.2  91/09/19  22:46:34  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: if_ether.h,v $ $Revision: 4.2.38.2 $ (DEC) $Date: 2008/03/06 07:22:40 $
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
 *	Base:	if_ether.h	7.4 (Berkeley) 2/17/89
 *	Merged:	if_ether.h	7.5 (Berkeley) 6/28/90
 */

#ifndef _IF_ETHER_H_
#define _IF_ETHER_H_
/*
 * Modification History:
 *
 *	Matt Thomas	 2/15/90
 *	Add ETHERTYPE_LAT and ETHERTYPE_DECnet for LAT and DLI.
 */

#include <net/route.h>
#include <kern/lock.h>

/*
 * Structure of a 10Mb/s (or for that matter 100Mb/s) Ethernet header.
 */
struct	ether_header {
	u_char	ether_dhost[6];
	u_char	ether_shost[6];
	u_short	ether_type;
};

/*
 * Ethernet 802.1Q tag header, inserted after source address.
 */
struct	ether_tagheader {
	u_short	eth_tpid;	/* Tag Protocol Identifier (0x8100) */
	u_short	eth_tci;	/* Tag Control Information (contains vlan id, user pri) */
};

/*
 * Drivers call ether_input() w/ m->m_data pointing past ether_type.
 * This struct is convenient for referencing what's there (tci then original type).
 */
struct	ether_tagdata {
	u_short	etd_tci;	/* Tag Control Information (contains vlan id, user pri) */
	u_short	etd_origtype;	/* ETHERTYPE_IP, etc. */
};

/*
 * A tagged frame's entire header, including 802.1Q tag header and original type.
 */
struct	ether_taggedframeheader {
	u_char			etfh_dhost[6];
	u_char			etfh_shost[6];
	struct ether_tagheader	etfh_taghdr;
	u_short			etfh_origtype;
};
#define etfh_type etfh_taghdr.eth_tpid
#define etfh_tci  etfh_taghdr.eth_tci

/* 
 * Tag Control Information (TCI) macros.
 *
 * TCI layout is defined on page 67 of 802.1Q-1998:
 *
 *          octets |1              |2                |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                 |user_|c|                         |
 *                 |prio |f|         VID             |
 *                 |rity |i|                         |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *            bits |8   6 5 4     1|8               1|
 *
 *                 user_priority -  3 bit user priority
 *                 cfi           -  1 bit cannonical format indicator
 *                 VID           - 12 bit VLAN ID
 *
 * (Lower numbered bytes are more significant, lower numbered bits
 *  are less significant.)  
 *
 * So our in-memory copy of this is:
 *
 *          octets |1              |2                |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                 |       |c|user_|                 |
 *                 |  VID  |f|prio |       VID       |
 *                 |  MSB  |i|rity |       LSB       |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *            bits |1     4 5 6 7 8|1               8|
 *
 * The formatting macros assume that on input, we first do ntohs 
 * before accessing the data, and on output we format the 2 bytes
 * then do htons.  That way we're operating on 2 (little endian) bytes 
 * with this layout:
 * 
 *          octets |1              |2              |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                 |               |       |c|user_|
 *                 |      VID      |  VID  |f|prio |
 *                 |      LSB      |  MSB  |i|rity |
 *                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *            bits |1             8|1       5 6 7 8|
 *
 * and the macros work for either endianism.
 */
#define TCI_CFI_MASK    0x1000
#define TCI_VID_MASK    0x0FFF
#define TCI_PRI_SHIFT	13

#define TCI_CFI_ON(tci)   ((tci) & TCI_CFI_MASK)
#define TCI_VID(tci)      ((tci) & TCI_VID_MASK)
#define TCI_PRI(tci)      ((u_short)(tci) >> TCI_PRI_SHIFT)

/* CFI bit is 0. */
#define TCI_ENCODE(vid, pri, tci)       \
        (tci) = htons((u_short)((pri) << TCI_PRI_SHIFT) + (vid))
#define TCI_ENCODE_NOPRI(vid, tci)       \
        (tci) = htons((vid) & TCI_VID_MASK)

#ifndef _KERNEL
struct ether_addr {
	u_char  ether_addr_octet[6];
};
#endif

/*
 * Note that PUP is <= 1500 and since falls in the range of valid 802.3
 * frames.  Hence, PUP is not actually usuable.
 */
#define	ETHERTYPE_PUP		0x0200	/* PUP protocol */
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#define ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#define ETHERTYPE_LAT		0x6004	/* Local Area Transport (LAT) */
#define ETHERTYPE_DECnet	0x6003	/* Phase IV DECnet */
#define ETHERTYPE_MOPRC		0x6002	/* MOP CCR protocol type */
#define ETHERTYPE_MOPDL		0x6001	/* MOP Downline Load protocol type */
#define ETHERTYPE_LBACK		0x9000	/* MOP loopback protocol type */
#define ETHERTYPE_IPV6		0x86DD	/* IPV6 protocol */
#define ETHERTYPE_TAG		0x8100	/* 802.1Q tag header */
#define ETHERTYPE_ICSNODEDETECT 0x8042 /* New tag for ICS FAST NODE DOWN DETECTION packets*/

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16

#if 0
/* #if defined(__alpha) && defined(_KERNEL) */
/* This is needed to support networking with ADUs */
#ifndef ALPHA_ADU
#include <hal/cpuconf.h>
#endif
extern int cpu;
#define	ETHERMTU	((cpu == ALPHA_ADU) ? (1500-14) : 1500)
#else
#define	ETHERMTU	1500
#endif	/* __alpha */
#define	ETHERMIN	(60-14)

/*
 * Ethernet Bandwidth.
 */
#define ETHER_BANDWIDTH_10MB	10000000        /* Ethernet - 10Mbs */
#define ETHER_BANDWIDTH_100MB	100000000       /* Fast Ethernet - 100Mbs */

/*
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to 
 * RFC 826.
 */
struct	ether_arp {
	struct	arphdr ea_hdr;	/* fixed-size header */
	u_char	arp_sha[6];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[6];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
};
#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op

/*
 * Structure shared between the ethernet driver modules and
 * the address resolution code.  For example, each ec_softc or il_softc
 * begins with this structure.
 */
#define NISAPS	128
struct	arpcom {
	struct 	ifnet ac_if;		/* network-visible interface */
	u_char	ac_hwaddr[14];		/* hardware address (sizeof sa_data) */
	u_short	ac_arphrd;		/* arp hardware type (net/if_arp.h) */
	u_char	*ac_bcastaddr;		/* pointer to link broadcast or 0 */
	u_int	ac_flag;		/* ip configured or not */
	struct dli_ifnet *ac_dlif;      /* pointer to the DLI data */
#ifdef __VMS
	u_char  ac_phaddr[14];		/* physical address (sizeof sa_data) */
#endif /* __VMS */
};
#define ac_enaddr	ac_hwaddr	/* one size fits many */
#define AC_IPUP		0x01		/* IP addr configured */

/*
 * Internet to ethernet address resolution table.
 */
struct	arptab {
	struct	in_addr at_iaddr;	/* internet address */
	struct	ifnet *at_if;		/* interface pointer */
	u_char	at_hwaddr[14];		/* hardware address (len in at_if) */
	u_short	at_flags;		/* flags (net/if_arp.h) */
	short	at_timer;		/* ticks since last referenced */
	short	at_valid;		/* ticks since last valid */
	short	at_retry;		/* request send count */
	short	at_sent;		/* at_valid at last send */
	struct	mbuf *at_hold;		/* last packet until resolved/timeout */
};
#define at_enaddr	at_hwaddr	/* as for arpcom */

struct ifnet_arp_cache_head {
	struct radix_node_head arp_cache_head;
	long pad_a[3];
	lock_data_t arp_cache_lock;
	long pad_b[2];
};

#ifdef	_KERNEL
#define IFNET_ARP_CACHE(ifp)	&(((struct ifnet_arp_cache_head *) \
				((ifp)->if_arp_cache_head))->arp_cache_head)
#define IFNET_ARP_CACHE_LOCK(ifp)	(((struct ifnet_arp_cache_head *) \
				((ifp)->if_arp_cache_head))->arp_cache_lock)
#define ARP_CACHE_REF(rt)	ROUTE_INC_REFCNT(*(rt))
#define ARP_CACHE_UNREF(rt)	if (ROUTE_DEC_REFCNT(*(rt)) <= 1) \
						arp_cache_free((rt))
/* the "old" arptab entry sits off of the rtentry */
#define ARPTAB_POINTER(rt)	(rt)->rt_llinfo
#define ARPTAB_ENTRY(rt)	(struct arptab *)(rt)->rt_llinfo

#if NETSYNC_LOCK
ndecl_lock_info(extern, ifnet_arp_cache_li)
#define IFNET_ARP_CACHE_LOCKINIT(ifp)	ulock_setup(&IFNET_ARP_CACHE_LOCK(ifp),\
						    ifnet_arp_cache_li, TRUE)
#define IFNET_ARP_CACHE_LOCKTERMINATE(ifp) \
				ulock_terminate(&IFNET_ARP_CACHE_LOCK(ifp))
#define IFNET_ARP_CACHE_READ_LOCK(ifp)	ulock_read(&IFNET_ARP_CACHE_LOCK(ifp))
#define IFNET_ARP_CACHE_WRITE_LOCK(ifp)	ulock_write(&IFNET_ARP_CACHE_LOCK(ifp))
#define IFNET_ARP_CACHE_UNLOCK(ifp)	ulock_done(&IFNET_ARP_CACHE_LOCK(ifp))
#define IFNET_ARP_CACHE_ISLOCKED(ifp)	(lockmode == 0 || \
					lock_holder(&IFNET_ARP_CACHE_LOCK(ifp)))
#else /* NETSYNC_LOCK */
#define IFNET_ARP_CACHE_LOCKINIT(ifp)
#define IFNET_ARP_CACHE_LOCKTERMINATE(ifp)
#define IFNET_ARP_CACHE_READ_LOCK(ifp)
#define IFNET_ARP_CACHE_WRITE_LOCK(ifp)
#define IFNET_ARP_CACHE_UNLOCK(ifp)
#define IFNET_ARP_CACHE_ISLOCKED(ifp)
#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */

#ifdef	_KERNEL
/*
 * Macro to map an IP multicast address to an Ethernet multicast address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address.
 */
#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr) \
	/* struct in_addr *ipaddr; */ \
	/* u_char enaddr[6];	   */ \
{ \
	(enaddr)[0] = 0x01; \
	(enaddr)[1] = 0x00; \
	(enaddr)[2] = 0x5e; \
	(enaddr)[3] = ((u_char *)ipaddr)[1] & 0x7f; \
	(enaddr)[4] = ((u_char *)ipaddr)[2]; \
	(enaddr)[5] = ((u_char *)ipaddr)[3]; \
}

/*
 * Macro to map an IP multicast address to an Ethernet multicast address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address.
 */
#define ETHER_MAP_IP6_MULTICAST(ip6addr, enaddr) \
	/* struct in6_addr *ipaddr; */ \
	/* u_char enaddr[6];	   */ \
do { \
	(enaddr)[0] = 0x33; \
	(enaddr)[1] = 0x33; \
	bcopy(&(ip6addr)->s6_laddr[3], &(enaddr)[2], 4); \
} while(0)

extern CONST u_char etherbroadcastaddr[6];
#endif

#endif
