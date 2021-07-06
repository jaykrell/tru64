/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip_var.h,v $
 * Revision 4.4.55.4  2003/09/10  17:47:46  Vladislav_Yasevich
 * 	Updated the ip_moptions structure to support dynamically
 * 	allocated membership array so that it can be grown.  QAR 97048.
 *
 * Revision 4.4.55.3  2003/07/25  20:17:51  Tony_Bono
 * 	Created multiple ip frag reassembley queues to improve marvel scaling.
 *
 * Revision 4.4.55.2  2003/06/10  22:03:38  Tony_Bono
 * 	Made changes to support route rate limiting. to fix performance
 * 	problem seen at rogers@home (CLD CR2W5100C QAR 94040).
 * 	Added definition of IP_LIMIT flag passed to ip_output when
 * 	protocols like tcp expect rate limiting.
 *
 * Revision 4.4.55.1  2003/02/28  17:27:43  Dan_Vuong
 *      Added ipq_nexttime_gatherfrags field to the ipq
 *      structure for triggering the next action of
 *      gathering fragments from other cluster members.
 *      This is for the implementation of new approach of
 *      fragment gathering in cluster environment to address
 *      performance issue described in QAR #95378.
 *
 * Revision 4.4.51.1  2002/01/16  17:50:57  Vladislav_Yasevich
 * 	Added definition to be use for IPv6 reassembly limit. QAR 86544.
 *
 * Revision 4.4.49.1  2000/09/25  22:41:56  Brian_Haley
 * 	Added IP_LLINFO_CANCACHE flag for if_llinfo support.  Callers of
 * 	ip_output() set this flag if they are passing-down an in_ro structure
 * 	that can be used to cache link-layer information.
 *
 * Revision 4.4.23.12  1999/02/11  16:54:27  Larry_Cohen
 * 	Cluster alias support for IP fragment reassembly.
 * 	[1999/02/11  16:28:51  Larry_Cohen]
 *
 * Revision 4.4.23.11  1998/05/14  22:39:46  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.4.33.2 **
 * 		** Merge revision:	4.4.41.2 **
 * 	 	** End **
 * 	[1998/05/14  22:17:23  John_Dustin]
 * 
 * Revision 4.4.41.2  1998/03/31  21:15:00  Tony_Bono
 * 	Moved stat struct definition to ip_stat.h. This is
 * 	necessary to support percpu stats.
 * 	[1998/03/31  20:19:32  Tony_Bono]
 * 
 * Revision 4.4.23.10  1998/02/12  19:47:35  Brian_Haley
 * 	Fixed GET_NEXT_IP_ID to call atomic_incl() correctly.
 * 	[1998/02/06  16:37:25  Brian_Haley]
 * 
 * Revision 4.4.23.9  1998/01/29  23:33:15  Brian_Haley
 * 	Added support for new ip output dropped and can't fragment
 * 	statistics.  Both are now broken down into various sub-codes
 * 	(qar 57961).
 * 	[1998/01/23  16:41:24  Brian_Haley]
 * 
 * Revision 4.4.23.8  1997/07/23  15:41:08  John_Dustin
 * 	For RSVP project, Markus Jork:
 * 	Added multicast_vif field to ip_moptions.
 * 	[1997/07/10  19:44:45  John_Dustin]
 * 
 * 	add IP_HDRCOMPLETE flag for ip_output()
 * 	[1997/06/17  18:31:17  Markus_Jork]
 * 
 * Revision 4.4.23.7  1997/06/04  17:55:30  Jack_McCann
 * 	add IP_PMTUDISC flag for ip_output()
 * 	[1997/05/28  15:37:57  Jack_McCann]
 * 
 * Revision 4.4.23.6  1997/02/06  02:46:47  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 **
 * 		** Ancestor revision:	4.4.28.2 **
 * 		** Merge revision:	4.4.33.2 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/06  02:31:00  Tony_Bono]
 * 
 * Revision 4.4.33.2  1996/11/22  22:10:51  Tony_Bono
 * 	hint code support
 * 	[1996/11/22  22:02:06  Tony_Bono]
 * 
 * Revision 4.4.23.5  1996/11/19  21:47:38  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.4.23.3 **
 * 		** Merge revision:	4.4.23.4 **
 * 	 	** End **
 * 	final pass of web server package including hint,
 * 	 quick bind and tcp syn queue changes
 * 	[1996/11/14  16:44:01  Tony_Bono]
 * 
 * Revision 4.4.23.4  1996/10/28  23:15:11  Ronald_Menner
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTAOS_BL4:PTBOS_BL3 **
 * 		** Ancestor revision:	4.4.16.3 **
 * 		** Merge revision:	4.4.28.2 **
 * 	 	** End **
 * 	[1996/10/28  23:10:04  Ronald_Menner]
 * 
 * Revision 4.4.29.2  1996/10/17  19:12:28  Tony_Bono
 * 	fixed to ip reassembley to handle large > 12M systems
 * 
 * Revision 4.4.28.2  1996/10/15  19:16:59  Tony_Bono
 * 	fix to ipreass struct for QAR 44857
 * 	[1996/10/14  19:18:13  Tony_Bono]
 * 
 * Revision 4.4.23.3  1996/09/25  18:47:23  Brian_Haley
 * 	Added C++ forward declaration
 * 	[1996/09/24  20:09:00  Brian_Haley]
 * 
 * Revision 4.4.23.2  1996/05/03  18:27:20  Tony_Bono
 * 	Bravo to Steel merge
 * 	[1996/05/03  15:51:14  Tony_Bono]
 * 
 * Revision 4.4.21.3  1995/11/10  23:42:53  Ray_Lanza
 * 	Merge of PTOS BL8
 * 	[1995/11/10  23:24:26  Ray_Lanza]
 * 
 * Revision 4.4.21.2  1995/10/25  19:58:18  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:28:16  Ray_Lanza]
 * 
 * Revision 4.4.16.3  1995/08/18  20:51:00  Dirce_Richards
 * 	cleanup
 * 	[1995/08/14  17:56:12  Dirce_Richards]
 * 
 * 	bmerged
 * 	[1995/08/03  20:03:19  Dirce_Richards]
 * 
 * 	Introduce access filter (provided by Fred Templin)
 * 	[1995/08/03  20:01:07  Dirce_Richards]
 * 
 * Revision 4.4.16.2  1995/03/24  19:17:39  Jack_McCann
 * 	Path MTU router support - add IP_NHMTU flag
 * 	[1995/03/22  17:34:55  Jack_McCann]
 * 
 * Revision 4.4.11.7  1994/04/07  13:17:10  Ernie_Petrides
 * 	Add GET_NEXT_IP_ID() macro to allocate ip_id in network byte order,
 * 	convert ip_id to an int for atomic_incl() updates in lockmodes 1-4,
 * 	eliminate ip_misc_lock since it was only used around original ip_id
 * 	updates, and eliminate ipr_lock field of ipreass structure since the
 * 	stats are protected by the ip_frag_lock.
 * 	[1994/04/06  21:29:39  Ernie_Petrides]
 * 
 * Revision 4.4.11.6  1994/03/18  21:54:19  Ernie_Petrides
 * 	Convert locking calls for ip_frag_lock to use the ulock_*
 * 	versions to allow for call patch-out in lockmode 0.
 * 	[1994/03/17  00:30:30  Ernie_Petrides]
 * 
 * Revision 4.4.11.5  1993/11/15  23:50:21  John_Dustin
 * 	change simple_lock_init to simple_lock_setup for ipreass lock
 * 	[1993/11/12  20:37:01  John_Dustin]
 * 
 * 	change to lock_setup for ip_frag_li, ip_misc_li and ipreass_li
 * 	[1993/10/27  16:45:01  John_Dustin]
 * 
 * Revision 4.4.11.4  1993/10/07  17:54:27  John_Dustin
 * 	add missing #endif
 * 	[1993/10/05  15:53:28  John_Dustin]
 * 
 * 	sterling to gold merge
 * 	[1993/10/04  18:48:46  John_Dustin]
 * 
 * Revision 4.4.7.5  1993/07/31  18:49:17  Heather_Gray
 * 	Modify IPR_DEFAULT from 50% of mb_map to 20% of non-wired pages.
 * 	[1993/07/31  18:35:37  Heather_Gray]
 * 
 * Revision 4.4.7.4  1993/06/29  18:12:27  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:47:33  SJ_Lee]
 * 
 * Revision 4.4.7.3  1993/06/23  13:46:23  Heather_Gray
 * 	Change ip_len and uh_ulen fields to unsigned
 * 	for Host Requirements and NFS usage
 * 	[1993/06/22  04:19:47  Heather_Gray]
 * 
 * Revision 4.4.7.2  1993/05/16  21:30:25  Heather_Gray
 * 	Revert to IP_MAX_MEMBERSHIPS.
 * 	[1993/05/16  09:19:54  Heather_Gray]
 * 
 * 	Add extern for ip_max_memberships.
 * 	[1993/05/16  05:27:40  Heather_Gray]
 * 
 * 	Use global for IP_MAX_MEMBERSHIPS. Corrected comments.
 * 	[93/04/30  22:31:06  Heather_Gray]
 * 	Add struct ip_moptions.
 * 	[93/04/12  00:57:10  Heather_Gray]
 * 
 * Revision 4.4.6.2  1993/04/12  14:03:12  Ajay_Kachrani
 * 	Fix ANSI bitfields warning when compiled using -std1
 * 	Revision 4.4.2.6  1992/12/09  15:12:24  Heather_Gray
 * 	Redefine ipf_mff field back to TOS as original TOS needs saving.
 * 	[92/12/07  17:36:42  Heather_Gray]
 * 
 * Revision 4.4.2.6  1992/12/09  15:12:24  Heather_Gray
 * 	Redefine ipf_mff field back to TOS as original TOS needs saving.
 * 	[92/12/07  17:36:42  Heather_Gray]
 * 
 * Revision 4.4.2.5  92/12/03  18:10:59  Chran-Ham_Chang
 * 	add a union ipopt to represent both ipopt_dst and ipopt_len
 * 	[92/11/25  13:22:38  Chran-Ham_Chang]
 * 
 * Revision 4.4.2.4  92/01/29  15:41:06  Geraldine_Harter
 * 	merged in Silver BL3
 * 	Revision 4.4.3.2  92/01/24  18:10:43  devbld_gsf
 * 	First AG_BL3 version. Moved from AG baselevel delivery tree.
 * 
 * 	Revision 4.3.2.2  91/12/18  21:47:11  William_Burns
 * 	Merge from ODE/TIN: revision 3.1.9.3
 * 	date: 91/11/14 15:40:39;  author: devrcs;  state: Exp;  lines added/del: 8/1
 * 	sccs rev: 3.3;  orig date: 91/11/04 15:51:44;  orig author: heather
 * 	fix for BYTE_ORDER undefined if _KERNEL not defined
 * 	[91/12/04  10:27:52  William_Burns]
 * 
 * Revision 4.4.2.3  92/01/26  20:57:04  Tim_Hoskins
 * 	Alpha support for TCP segment reassembly.
 * 	[92/01/26  20:54:30  Tim_Hoskins]
 * 
 * Revision 4.4.2.2  92/01/20  13:18:15  Tim_Hoskins
 * 	Alpha 64-bit network support.
 * 	[92/01/20  13:01:46  Tim_Hoskins]
 * 
 * Revision 4.4  92/01/15  02:03:38  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.3.2.2  91/12/07  16:12:01  Ray_Lanza
 * 	Merged tin-based ALPHA version
 * 	[91/12/07  16:06:45  Ray_Lanza]
 * 
 * Revision 4.3  91/11/26  11:11:44  devbld_zk3
 * 	Baselevel AG_BL0
 * 
 * Revision 4.2.2.2  91/11/05  10:34:46  William_Burns
 * 	Merge from ODE/TIN: revision 3.1.9.2
 * 	date: 91/10/24 16:33:47;  author: devrcs;  state: Exp;  lines added/del: 24/1
 * 	sccs rev: 3.2;  orig date: 91/10/10 15:46:10;  orig author: heather
 * 	add ipreass structure and lock macros to enable quota on reassembly queue
 * 	[91/10/29  10:57:54  William_Burns]
 * 
 * Revision 4.2  91/09/19  22:47:42  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: ip_var.h,v $ $Revision: 4.4.55.4 $ (DEC) $Date: 2003/09/10 17:47:46 $
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
 *	Base:	ip_var.h	7.6 (Berkeley) 9/20/89
 *	Merged:	ip_var.h	7.7 (Berkeley) 6/28/90
 */
#ifndef	_NETINET_IP_VAR_H
#define	_NETINET_IP_VAR_H

#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

#ifdef __cplusplus
extern "C" {
/* forward decls for C++ */
struct ipasfrag;
#endif

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 * For 64-bit pointers, the next and previous fields are stored in the
 * mbuf header instead of in the ipovly.
 */
struct ipovly {
#ifdef __arch64__
	u_int	fill[2];		/* filler */
#else /* __arch64__ */
	caddr_t	ih_next, ih_prev;	/* for protocol sequence q's */
#endif /* __arch64__ */
	u_char	ih_x1;			/* (unused) */
	u_char	ih_pr;			/* protocol */
	u_short	ih_len;			/* protocol length */
	struct	in_addr ih_src;		/* source internet address */
	struct	in_addr ih_dst;		/* destination internet address */
};

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
#ifdef __arch64__

struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	struct	ipasfrag *ipq_next;	/* to ip headers of fragments */
	struct	ipasfrag *ipq_prev;	/*       ""         ""	      */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	in_addr ipq_src,ipq_dst;
	int 	ipq_flags;
        int     ipq_nexttime_gatherfrags;
};

#else

struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	ipasfrag *ipq_next,*ipq_prev;
					/* to ip headers of fragments */
	struct	in_addr ipq_src,ipq_dst;
	int 	ipq_flags;
};

#endif /* __arch64__ */

/*
 * Flags for IP reassembly queue.
 */
#define IPQ_FLAGS_ALIAS	0x01

/*
 * Ip header, when holding a fragment.
 *
 * Note: ipf_next must be at same offset as ipq_next above
 */
#ifdef __arch64__

struct	ipasfrag {
	struct	ip	 *xxx;		/* place holder */
	struct	ip	 *ipf_ip;	/* pointer to the real ip */
	struct	ipasfrag *ipf_next;	/* next fragment */
	struct	ipasfrag *ipf_prev;	/* previous fragment */
};

#else

struct	ipasfrag {
#if	defined(_KERNEL) || defined(_NO_BITFIELDS) || (__STDC__ == 1)
	u_char	ip_vhl;
#else
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ip_hl:4,
		ip_v:4;
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ip_v:4,
		ip_hl:4;
#endif
#endif
	u_char	ip_tos;	
	u_short	ip_len;
	u_short	ip_id;
	short	ip_off;
	u_char	ip_ttl;
	u_char	ip_p;
	u_short	ip_sum;
	struct	ipasfrag *ipf_next;	/* next fragment */
	struct	ipasfrag *ipf_prev;	/* previous fragment */
};

#endif /* __arch64__ */

#define IPFRAG_MFF	0x10

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
#define MAX_IPOPTLEN	40

struct ipoption {
	union {
		struct	in_addr ipopt_dest;	/* first-hop dst if source routed */
		int	ipopt_len;
	} ipopt ;  
#define ipopt_dst	ipopt.ipopt_dest
#define oplen 		ipopt.ipopt_len 
	char	ipopt_list[MAX_IPOPTLEN];	/* options proper */
};

#ifdef _KERNEL
/*
 * Structure attached to inpcb.ip_moptions and
 * passed to ip_output when IP multicast options are in use.
 */
struct ip_moptions {
	struct	ifnet *imo_multicast_ifp; /* ifp for outgoing multicasts */
#ifdef RSVP
	int	imo_multicast_vif;	/* vif for outgoing multicasts */
#endif
	u_char	imo_multicast_ttl;	/* TTL for outgoing multicasts */
	u_char	imo_multicast_loop;	/* 1 => hear sends if a member */
	u_short	imo_num_memberships;	/* no. memberships this socket */
	struct	in_multi **imo_membership;
	u_int	imo_membership_size;	/* size of the current memb array */
};
#endif

/* Source route holding structure (moved here from ip_input.c) */
struct ip_srcrt {
	struct	in_addr dst;			/* final destination */
	char	nop;				/* one NOP to align */
	char	srcopt[IPOPT_OFFSET + 1];	/* OPTVAL, OLEN and OFFSET */
	struct	in_addr route[MAX_IPOPTLEN/sizeof(struct in_addr)];
};

#include <netinet/ip_stat.h>

struct ipreass {
	int		ipr_percent;	/* % buffer space avail for reass */
	unsigned long	ipr_max;	/* max space available for reass */
	unsigned long	ipr_inuse;	/* space currently used for reass */
	unsigned long	ipr_v6inuse;	/* space used by IPv6 */
	int		ipr_drops;	/* # of drops due to buffer unavail */
};
#define IPR_DEFAULT	20		/* use 20% by default */

#ifdef _KERNEL
ndecl_lock_data(extern, * REPLICATED ip_frag_lock)
#define IPFRAG_LOCKINIT(__i)	ulock_setup(&ip_frag_lock[__i], ip_frag_li, TRUE)
#define IPFRAG_LOCK(__i)	ulock_write(&ip_frag_lock[__i])
#define IPFRAG_UNLOCK(__i)	ulock_done(&ip_frag_lock[__i])
#define IP_DEFAULT_FRAG_INDEX	64
#define FRAG_INDEX(__i) 	(__i%ip_max_frag_index)

extern	REPLICATED u_int ip_max_frag_index;
extern	struct ipq	* REPLICATED ipq;			/* ip reass. queue */

/* flags passed to ip_output as fourth parameter */
#define	IP_FORWARDING		0x1		/* most of ip header exists */
#define IP_NHMTU                0x2             /* provide next-hop mtu */
#define IP_PMTUDISC		0x4		/* path mtu discovery enabled */
#define IP_HDRCOMPLETE          0x8		/* complete IP header provided */
#define	IP_ROUTETOIF		SO_DONTROUTE	/* bypass routing tables */
#define	IP_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets */
#define	IP_LLINFO_CANCACHE	0x40		/* cache llinfo data */
#define IP_LIMIT		0x80		/* abide by the configured data rate in the routing table */

extern	CONST u_char inetctlerrmap[];
extern	struct	ipstat	ipstat;
extern	u_int	ip_id;				/* ip packet ctr, for ids */
#if NETSYNC_LOCK
#define GET_NEXT_IP_ID() \
	(htons((u_short)((lockmode == 0) ? ip_id++ : atomic_incl((int *)&ip_id))))
#else
#define GET_NEXT_IP_ID() (htons((u_short)ip_id++))
#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif /* _NETINET_IP_VAR_H */
