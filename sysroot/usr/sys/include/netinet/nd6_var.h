/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: nd6_var.h,v $
 * Revision 1.1.20.2  2003/11/13  22:42:57  Brian_Haley
 * 	Removed obsolete nd6_dad_refcnt and nd6_adverts declarations.
 *
 * Revision 1.1.20.1  2003/09/23  22:00:56  Brian_Haley
 * 	Changed nd6_anycast_adv to nd6_adverts.
 *
 * Revision 1.1.10.1  2001/12/17  20:55:48  Vladislav_Yasevich
 * 	Merge of Anycast Address implementation into wcalpha.
 *
 * Revision 1.1.7.1  2001/03/14  17:06:41  Vladislav_Yasevich
 * 	Added nd6_anycast_adv to keep track of any anycast timers.
 *
 * Revision 1.1.4.3  2000/01/12  16:52:20  Sowmini_Varadhan
 * 	- moved nd6_llinfo_qh to nd6_cache.h
 * 	- added li_slowtimo_next
 *
 * Revision 1.1.4.2  1999/12/16  20:48:20  Sowmini_Varadhan
 * 	added  ND6_LINK_HAS_LLADDR, ND6_IF_FLAGS
 *
 * Revision 1.1.4.1  1999/10/18  20:21:53  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 1.1.2.8  1999/09/13  21:28:28  Jack_McCann
 * 	add ND6_MAX_LINKADDR_OPTION_SIZE
 *
 * Revision 1.1.2.7  1999/01/07  22:49:11  Jack_McCann
 * 	add ND6_RT_PREC_INCOMPLETE and ND6_RT_PREC_OTHER
 * 	[1999/01/07  21:58:25  Jack_McCann]
 *
 * Revision 1.1.2.6  1998/12/07  21:44:09  Geraldine_Harter
 * 	- Added comment describing li_ifq locking assumptions
 * 	[1998/12/07  20:15:18  Geraldine_Harter]
 * 
 * Revision 1.1.2.5  1998/10/30  16:58:44  Jack_McCann
 * 	- add include of <netinet/in6_var.h> for struct in6_ifnet li_if6
 * 	- add include of <net/if.h> for struct ifqueue li_ifq
 * 	- add include of <net/route.h> for struct rtentry li_rt
 * 	[1998/10/29  19:39:14  Jack_McCann]
 * 
 * Revision 1.1.2.4  1998/10/15  21:01:24  Jack_McCann
 * 	add extern declaration for nd6_dad_refcnt
 * 	[1998/10/09  18:52:35  Jack_McCann]
 * 
 * Revision 1.1.2.3  1998/09/02  14:24:39  Sowmini_Varadhan
 * 	removed dead code (IF6_IF_TYPE)
 * 	[1998/09/01  14:39:49  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.2  1998/06/22  21:00:36  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 
 * 	move prototypes to proto_inet.h
 * 
 * 	revision 1.21
 * 	date: 1998/03/06 14:57:50;  author: varadhan;  state: Exp;  lines: +5 -1
 * 	to enable ifconfig to detect ipt intfs, added support for the
 * 	IF6_IF_TYPE option in the SIOCGIFATTR ioctl.
 * 	----------------------------
 * 	revision 1.20
 * 	date: 1997/10/30 21:27:27;  author: gfisher;  state: Exp;  lines: +5 -2
 * 	name space changes for the advanced socket API
 * 	----------------------------
 * 	revision 1.19
 * 	date: 1997/09/22 09:26:29;  author: jork;  state: Exp;  lines: +5 -2
 * 	fixed bug due to wrong const usage
 * 	----------------------------
 * 	revision 1.18
 * 	date: 1997/02/18 19:34:32;  author: mccann;  state: Exp;  lines: +68 -0
 * 	DIGITAL UNIX V4.0B merge
 * 	----------------------------
 * 	revision 1.17
 * 	date: 1997/02/04 01:57:58;  author: mccann;  state: Exp;  lines: +18 -0
 * 	RIPng + multilink checkin, sct 19970203-mccann-ripng_multilink.txt
 * 	----------------------------
 * 	revision 1.16
 * 	date: 1996/08/01 20:52:51;  author: mccann6;  state: Exp;  lines: +1 -0
 * 	dded prototype for nd6_process_router_solicitation()
 * 	----------------------------
 * 	revision 1.15
 * 	date: 1996/04/05 20:26:26;  author: root;  state: Exp;  lines: +2 -0
 * 	(matt) bug fixes from Feb96 UNH.
 * 	----------------------------
 * 	revision 1.14
 * 	date: 1996/01/31 00:18:11;  author: thomas;  state: Exp;  lines: +2 -1
 * 	Add redirect support
 * 	----------------------------
 * 	revision 1.13
 * 	date: 1996/01/26 18:34:45;  author: thomas;  state: Exp;  lines: +2 -0
 * 	Add/change ioctl's to setting interface ioctls
 * 	----------------------------
 * 	revision 1.12
 * 	date: 1996/01/26 00:11:55;  author: thomas;  state: Exp;  lines: +10 -6
 * 	Add more stuff for DAD
 * 	----------------------------
 * 	revision 1.11
 * 	date: 1996/01/25 16:58:09;  author: thomas;  state: Exp;  lines: +5 -1
 * 	remove rejecting state; Add defines to setting the per-interface
 * 	timers
 * 	----------------------------
 * 	revision 1.10
 * 	date: 1996/01/24 01:44:10;  author: thomas;  state: Exp;  lines: +1 -1
 * 	add nd6_cache_confirm
 * 	----------------------------
 * 	revision 1.9
 * 	date: 1996/01/22 21:31:36;  author: thomas;  state: Exp;  lines: +1 -0
 * 	include icmp6_var.h to get ICMPV6STAT macro
 * 	----------------------------
 * 	revision 1.8
 * 	date: 1996/01/19 18:03:02;  author: thomas;  state: Exp;  lines: +7 -23
 * 	update to new discovery-03
 * 	improve multicast support
 * 	----------------------------
 * 	revision 1.7
 * 	date: 1995/10/04 21:19:57;  author: thomas;  state: Exp;  lines: +6 -4
 * 	fix solicitation generation problem (target and ip6dst reversed).
 * 	----------------------------
 * 	revision 1.6
 * 	date: 1995/09/11 18:27:59;  author: thomas;  state: Exp;  lines: +0 -2
 * 	move ND6_HZ to nd6_cache.c
 * 	----------------------------
 * 	revision 1.5
 * 	date: 1995/09/07 15:06:30;  author: thomas;  state: Exp;  lines: +12 -3
 * 	add rx_payload_offset
 * 	----------------------------
 * 	revision 1.4
 * 	date: 1995/09/06 19:49:27;  author: thomas;  state: Exp;  lines: +7 -20
 * 	add more prototypes
 * 	----------------------------
 * 	revision 1.3
 * 	date: 1995/09/02 17:07:41;  author: thomas;  state: Exp;  lines: +16 -4
 * 	remove static functions that are solely private to nd6_cache.c
 * 	----------------------------
 * 	revision 1.2
 * 	date: 1995/09/01 23:45:25;  author: thomas;  state: Exp;  lines: +60 -1
 * 	add prototypes for kernel
 * 	make sure it compiles clean
 * 	----------------------------
 * 	revision 1.1
 * 	date: 1995/09/01 15:53:44;  author: thomas;  state: Exp;
 * 	Initial revision
 * 	[1998/06/16  14:59:28  Jack_McCann]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: nd6_var.h,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 2003/11/13 22:42:57 $
 */

#ifndef _ND6_VAR_H_
#define _ND6_VAR_H_

#include <netinet/in6.h>
#include <netinet/ip6.h>
#include <netinet/icmp6_var.h>
#include <netinet/icmp6.h>
#include <netinet/in6_var.h>
#include <net/if.h>
#include <net/route.h>

/*
 *	Define various structures and constants used in
 *	Neighbor Discovery.
 */

/*
 * The following enums are used to control/update neighbor discovery cache
 * (ie. the IPv6 version of ARP).
 */

enum nd6_cache_action {
    ND6_CACHE_UPDATE,
    ND6_CACHE_CREATE
};

/* 
 * Note: ND6_CACHE_UNREACHABLE is not a valid state in RFC 2461.
 * It is defined here as an nd6_cache_state purely for the purpose of 
 * providing an interface to nd6_cache_newstate-  marking an li_state 
 * to "ND6_CACHE_UNREACHABLE" via  nd6_cache_newstate will cause that 
 * nd6_llinfo to be freed, so an existing li can never have the state
 * ND6_CACHE_UNREACHABLE.
 */
			    
enum nd6_cache_state {
    ND6_CACHE_INCOMPLETE, ND6_CACHE_UNREACHABLE, 
    ND6_CACHE_REACHABLE, ND6_CACHE_STALE, ND6_CACHE_PROBE,
    ND6_CACHE_MAX
};

#define	ND6_FIRST_PROBE_DELAY		1001
#define	ND6_RETRANSMIT_DELAY		1002
#define	ND6_REACHABLE_TIME		1003
#define	ND6_MAX_RTR_SOLICITATION_DELAY	1004
#define	ND6_DAD_TRIES			1005
#define	ND6_LINK_MTU			1006
#define	ND6_UNICAST_HOPS		1007
#define ND6_TOKEN_LENGTH		1008
#define ND6_IF6_FLAGS			1009

/*
 * Access to the following structure is protected by the ROUTE_LOCK.
 * The IF_ENQUEUE_NOLOCK, IF_DEQUEUE_NOLOCK, etc. macros are used
 * to manage the li_ifq queue.  These macros assume that the caller 
 * holds the lock protecting the queue, which in this case is the ROUTE_LOCK.
 */
struct nd6_llinfo {
    struct nd6_llinfo *li_next;
    struct nd6_llinfo *li_prev;
    struct rtentry *li_rt;
    struct in6_ifnet *li_if6;
    struct sockaddr_in6 li_dst;
    unsigned li_retries;		/* queries left for this addr */
    enum nd6_cache_state li_state;
    struct ifqueue li_ifq;		/* packets until resolved/timeout */
    struct nd6_llinfo *li_slowtimo_next;/* list of li's to be processed in
					 * nd6_cache_slowtimo
					 */
};


/*
 * default route precedence for router reachability states (lower is better)
 */
#define ND6_RT_PREC_INCOMPLETE	10	/* for incomplete state */
#define ND6_RT_PREC_OTHER	 0	/* for states other than incomplete */

/*
 * max supported source/target link-layer address option size (bytes)
 */
#define ND6_MAX_LINKADDR_OPTION_SIZE	32

#ifdef _KERNEL

#define ND6_LINK_HAS_LLADDR(if6)      (((if6)->if6_flags & IFF6_NOLLADDR) == 0)

#endif /* _KERNEL */

#endif /* _ND6_VAR_H_ */
