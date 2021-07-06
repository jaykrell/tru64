/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: in6_var.h,v $
 * Revision 1.1.38.4  2003/11/13  22:42:44  Brian_Haley
 * 	Added la6_work_next pointer to in6_localaddr structure to support
 * 	linking together any addresses that have pending "work" (timers, etc),
 * 	each RAD keeps a list of such addresses.  Also added macros to insert
 * 	and remove addresses from each list.  Added rx_mobhdr to ip6_rxinfo
 * 	struct to support future Mobile IPv6 API work.
 *
 * Revision 1.1.38.3  2003/10/15  21:21:08  Vladislav_Yasevich
 * Merge Information:  Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Vladislav_Yasevich_v51b_br:1.1.39.1 Local Ancestor:1.1.38.1
 *    Merge Revision:  v51bsupportos_br:1.1.38.2
 *   Common Ancestor:  1.1.38.1
 * 	[2003/10/15  21:21:02  Vladislav_Yasevich]
 *
 * 	IPv6 Advanced API update to RFC 3542
 * 	- Added option bits for IPV6_TCLASS and IPV6_DONTFRAG options
 * 	- changed the in6optinfo structure layout to get rid of the holes
 *   and to better allign the new data.
 * 	[2003/10/06  19:36:11  Vladislav_Yasevich]
 *
 * Revision 1.1.38.2  2003/09/23  21:52:50  Brian_Haley
 * 	Mobile IPv6 update.
 * 	Separate the scope element from the flags in in6_localaddr
 * 	(Qar 95316).  Also, update the structure and align it at
 * 	the cache and memory bucket boundries.
 * 	Added tx_nomobile bit to ip6_txinfo structure to support callers
 * 	of ip6_output() that want to avoid a binding cache (route) lookup.
 * 	Added _IN6_LOCALADDR_HASH_ENABLED() macro.
 * 	Fixed ips_rx_errors comment.
 * 	Mobile IPv6 draft 18 support:
 * 	- changed the anycast advert queue names to be more generic
 * 	- added padding definitions to the ip6_rxinfo struct so I could tell
 *   how much space was still available
 * 	- changed the in6optinfo struct to have a type 2 routing header pointer
 *   since Mobile IPv6 doesn't use type 0 any more
 * 	- created two bits in the ip6_rxinfo struct - one to designate if we've
 *   seen a home address option, and the other to say we've swapped it with
 *   the IPv6 source address
 * 	- added Proxy and Mobile statistics support
 * 
 * Revision 1.1.38.1  2003/09/10  17:47:43  Vladislav_Yasevich
 * 	Updated the ip6_moptions structure to provide for a dynamically
 * 	allocated membership array.  QAR 97048.
 * 
 * Revision 1.1.27.3  2002/01/29  21:18:56  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 * 
 * Revision 1.1.27.2  2002/01/16  17:50:53  Vladislav_Yasevich
 * 	Added ip6_reass_quota counter to IPv6 statistics. QAR 86544
 * 
 * Revision 1.1.27.1  2001/12/17  20:55:00  Vladislav_Yasevich
 * 	Mapped API submit:
 * 	- Enabled hanlding of mapped address with Advanced API.
 * 	- Correctly handling mapped address with multicast options.
 * 	[2001/10/19  19:19:37  Vladislav_Yasevich]
 * 	Mobile IPv6 submit:
 * 	- added OPT_MIP6_RTHDR definition for in6optinto
 * 	- added opt_mip6_timestamp element to in6optinto
 * 	- added rx_homeaddr element to ip6_rxinfo
 * 	- added tx_cancacheopt and tx_rawmobile elements to ip6_txinfo
 * 	- added some extern declarations to fix some compile problems
 * 	[2001/10/10  15:35:41  Brian_Haley]
 * 	Fix for QAR QAR fix 86524:
 * 	- Move extern declaration of ipv6forwarding and ipv6router
 *   to ipv6_swtab.h
 * 	[2001/10/03  14:51:40  Geraldine_Harter]
 * 	Merge of Anycast Address implementation into wcalpha.
 * 	[2001/10/02  15:31:16  Vladislav_Yasevich]
 * 	Merge of the Advanced API implementations from wildcat.classic
 * 	[2001/09/25  21:08:01  Vladislav_Yasevich]
 * 	[2001/10/02  15:44:42  Vladislav_Yasevich]
 * 
 * Revision 1.1.18.1  2001/07/10  15:01:53  Paul_Moore
 * 	add tx_partial_orig_packet to the ip6_txinfo structure for ipsec use, this
 * 	is a backport from wildcat
 * 
 * Revision 1.1.14.10  2000/02/22  20:44:53  Sowmini_Varadhan
 * 	- Added missing ;
 * 
 * Revision 1.1.14.9  2000/01/28  16:05:26  Sowmini_Varadhan
 * 	move include of thread.h to be conditionally compiled for _KERNEL
 * 
 * Revision 1.1.14.8  2000/01/27  19:46:34  Sowmini_Varadhan
 * 	- added ipv6control and RAD2IP6CTL
 * 
 * Revision 1.1.14.7  2000/01/20  17:42:53  Sowmini_Varadhan
 * 	- rearrange in6_ifnet to keep (mostly) const fields in
 * 	the same cache line; pad to an integer mult of 64 bytes
 * 
 * Revision 1.1.14.6  2000/01/12  16:52:07  Sowmini_Varadhan
 * 	- added if6_nd6_cache, if6_nd6_cache_lock
 * 	- renamed IN6_LADDR_ADD_DEL_LOCK to IN6_LADDR_ADD_DEL_WRITE_LOCK
 * 	and added IN6_LADDR_ADD_DEL_READ_LOCK
 * 	- removed in6_ifprefix definition.
 * 
 * Revision 1.1.14.5  1999/12/16  20:48:13  Sowmini_Varadhan
 * 	Defined IFF6_NONUD, IFF6_NOLLADDR, IFF6_CANTCHANGE
 * 
 * Revision 1.1.14.4  1999/11/29  16:27:18  Sowmini_Varadhan
 * 	PTR 52-1-253- remove ips_rx_tcptotal
 * 
 * Revision 1.1.14.3  1999/11/05  16:31:06  Sowmini_Varadhan
 * 	PTR 52-1-256: removed M_NOPROBE.
 * 
 * Revision 1.1.14.2  1999/11/03  19:53:15  Geraldine_Harter
 * 	Convert IN6_LOCALADDR_READ_LOCK and IN6_LOCALADDR_WRITE_LOCK
 * 	to Reader/Writer spin locks.
 * 
 * Revision 1.1.14.1  1999/10/18  20:21:05  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 * 
 * Revision 1.1.2.20  1999/09/10  16:25:37  Geraldine_Harter
 * 	Set _IN6_DEBUG to zero
 * 
 * Revision 1.1.2.19  1999/08/13  18:42:03  Sowmini_Varadhan
 * 	ipv6_swtab cleanup
 * 	- inline ip6laddr, ip6ifnet into ipv6_swtab.
 * 	- field name in ipv6_swtab matches func name in ipv6_swtab_real
 * 	[1999/08/13  15:16:31  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.18  1999/08/12  21:32:13  Jack_McCann
 * 	- add flag for in6_localaddr_pick()
 * 	- remove M_TUNNELED flag (not used)
 * 	- remove M_TRANSIT (no longer needed)
 * 	[1999/08/12  21:00:04  Jack_McCann]
 * 
 * Revision 1.1.2.17  1999/07/22  19:01:14  Sowmini_Varadhan
 * 	- changed definition of IN6_LOCALADDR_DEREF to use ipv6_swtab
 * 	  indirection (assumes non-null ipv6_swtab)
 * 	- ipv6_minimum_link_mtu and ipv6_default_unicast_hoplimit are now
 * 	  in ipv6_swtab
 * 	- inet6sw is a pointer to inet6sw_stub[] that changes to  point to
 * 	  inet6sw_ipv6 when ipv6 is loaded.
 * 	[1999/07/07  18:54:25  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.16  1999/06/08  18:09:45  Jack_McCann
 * 	IPv6 EAK X6.3 merge to Steel
 * 	- move xxx_TOKEN_LENGTH macros here from in6.h and change the
 * 	  name to xxx_IID_LENGTH (Interface IDentifier length)
 * 	- rename IN6_SET_ETHER_TOKEN to IN6_IEEE802_TO_IID
 * 	- remove unused IPV6_FORWARDING, IPV6_RAWOUTPUT, IPV6_DONTFRAGMENT,
 * 	  IPV6_DONTROUTE defines
 * 	- remove IP6_ADD_AUTHENTICATION macro; it's currently a no-op,
 * 	  and authentication will be handled by the IPSEC project
 * 	- remove unused struct ip6mgmt
 * 	- remove tx_dontfragment and tx_fragtopmtu
 * 	[1999/06/08  15:52:14  Jack_McCann]
 * 
 * Revision 1.1.2.15  1999/03/04  16:05:18  Geraldine_Harter
 * 	- Replace if6->if6_addrlist with if6->if6_lladdr, since the
 * 	  if6_addrlist used to be used only for accessing the interface's
 * 	  link local address.
 * 	- Add LA6_GLOBAL define
 * 	[1999/03/01  21:39:57  Geraldine_Harter]
 * 
 * Revision 1.1.2.14  1999/02/19  22:32:17  Jack_McCann
 * 	Add IN6_IFNET_OF_IFINDEX
 * 	[1999/02/19  21:44:00  Jack_McCann]
 * 
 * Revision 1.1.2.13  1999/01/27  21:17:18  Geraldine_Harter
 * 	Add support for in6_ifaddr refcnts & locking
 * 	[1999/01/26  21:33:52  Geraldine_Harter]
 * 
 * Revision 1.1.2.12  1999/01/07  22:49:09  Jack_McCann
 * 	- add LA6_ANYCAST and LA6_PROXY flags; although neither has been
 * 	  implemented, we can start adding code (or stubs) in places where
 * 	  anycast and/or proxy require special treatment
 * 	[1999/01/04  22:20:12  Jack_McCann]
 * 
 * Revision 1.1.2.11  1998/12/07  21:44:02  Geraldine_Harter
 * 	Misc fixes:
 * 	- Consolidate _IN6_DEBUG & IN6_DEBUG
 * 	- Add comments describing in6_ifnet fields locking
 * 	- Move function prototypes to proto_inet.h
 * 	- Add la6_dadsendfail to struct in6_localaddr
 * 	[1998/12/07  20:14:51  Geraldine_Harter]
 * 
 * Revision 1.1.2.10  1998/10/30  16:58:28  Jack_McCann
 * 	- replace ip6route with in_route and include in_route.h
 * 	- add rx_forwarding flag to ip6_rxinfo structure
 * 	[1998/10/29  18:40:46  Jack_McCann]
 * 
 * Revision 1.1.2.9  1998/10/20  20:26:25  Geraldine_Harter
 * 	Misc locking changes:
 * 	o Rename in6_laddr_mutex_* to in6_laddr_add_del_*
 * 	o Split IN6_LOCALADDR_LOCK into read/write versions,
 * 	  so that we can use spin read/write locks when we
 * 	  merge with Steel.
 * 	o Change IN6_LOCALADDR_REF/DEREF to use atomic operations
 * 	o Add new args to in6_localaddr_add()
 * 	 	o Add '#if NETSYNC_LOCK' statement
 * 	o Use 'u' versions of the locking primitives.
 * 	o Remove in6_stupid_neighbors (unused)
 * 	o Support in6_whine only if IN6_DEBUG is set.
 * 	[1998/10/20  16:08:54  Geraldine_Harter]
 * 
 * Revision 1.1.2.8  1998/10/06  19:16:43  Sowmini_Varadhan
 * 	Re-defined IN6_IFNET_REF and IN6_IFNET_DEREF to be atomic operations,
 * 	releasing the requirement that these must be called with the
 * 	IN6_IFNET_LOCK held
 * 	[1998/10/06  14:31:35  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.7  1998/09/24  19:38:26  Sowmini_Varadhan
 * 	added if6_refcnt, IN6_IFNET_REF, IN6_IFNET_DEREF, _IN6_DEBUG
 * 	[1998/09/24  17:04:15  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.6  1998/09/15  18:08:32  Eric_Wong
 * 	RFC2292 Advanced Sockets API for IPv6 changes
 * 	- add ips_rip_tooshort and ips_rip_badcksum
 * 	- add new data structures for ipv6 options processing
 * 	- add new member to txinfo and rxinfo
 * 	[1998/09/15  15:02:16  Eric_Wong]
 * 
 * Revision 1.1.2.5  1998/09/03  19:38:52  Geraldine_Harter
 * 	Cleanup incorrect locking comments.
 * 	[1998/09/03  16:59:07  Geraldine_Harter]
 * 
 * Revision 1.1.2.4  1998/08/11  18:45:12  Geraldine_Harter
 * 	Add new locks & IN6_LOCALADDR_REF macro, and modify IN6_LOCALADDR_DEREF;
 * 	Remove support for IPV6_SOLMCAST_COMPAT & IPV6_TOKEN_COMPAT;
 * 	Remove unused rx_ia6 field;
 * 	Add mcu_members field to the in6_localaddr struct.
 * 	[1998/08/11  15:58:05  Geraldine_Harter]
 * 
 * Revision 1.1.2.3  1998/07/24  20:44:27  Sowmini_Varadhan
 * 	-  PPP over IPv6 - added extern definiton of ip6intrq in in6_var.h,
 * 	   analagous to definition of ipintrq in in_var.h.
 * 	-  la6_refcnt cleanup- added IN6_LOCALADDR_REF
 * 	-  defined IN6_IS_MCAST_INTF
 * 	[1998/07/24  17:54:28  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.2  1998/06/22  20:59:26  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 	revision 1.18
 * 	date: 1997/08/05 18:55:44;  author: mccann;  state: Exp;  lines: +42 -6
 * 	64-bit token and solicited node multicast changes
 * 	dd extern for ipv6_default_unicast_hoplimit
 * 	----------------------------
 * 	revision 1.17
 * 	date: 1997/04/11 04:27:41;  author: mccann;  state: Exp;  lines: +32 -1
 * 	add M_FINDBYTE (moved from ip6_frag.c)
 * 	----------------------------
 * 	revision 1.16
 * 	date: 1997/02/18 19:34:29;  author: mccann;  state: Exp;  lines: +63 -10
 * 	DIGITAL UNIX V4.0B merge
 * 	----------------------------
 * 	revision 1.15
 * 	date: 1997/02/04 01:57:57;  author: mccann;  state: Exp;  lines: +7 -5
 * 	RIPng + multilink checkin, sct 19970203-mccann-ripng_multilink.txt
 * 	----------------------------
 * 	revision 1.14
 * 	date: 1996/06/12 17:46:57;  author: mccann6;  state: Exp;  lines: +4 -2
 * 	add ips_rx_forwarded and rx_should_be_jumbo
 * 	----------------------------
 * 	revision 1.13
 * 	date: 1996/05/10 21:31:19;  author: mccann;  state: Exp;  lines: +28 -1
 * 	PMTU Discovery and IPv6 Forwarding checkin
 * 	----------------------------
 * 	revision 1.12
 * 	date: 1996/04/05 20:42:56;  author: root;  state: Exp;  lines: +31 -4
 * 	add frag/reas support and IPV6_DONTFRAGMENT flag
 * 	----------------------------
 * 	revision 1.11
 * 	date: 1996/01/31 00:18:44;  author: thomas;  state: Exp;  lines: +13 -7
 * 	Add router structure.
 * 	switch to using in6_ifnet instead of ifnet
 * 	----------------------------
 * 	revision 1.10
 * 	date: 1996/01/29 18:19:59;  author: thomas;  state: Exp;  lines: +2 -1
 * 	Add alignment bit
 * 	----------------------------
 * 	revision 1.9
 * 	date: 1996/01/26 22:49:24;  author: thomas;  state: Exp;  lines: +5 -2
 * 	add support for new ioctls
 * 	----------------------------
 * 	revision 1.8
 * 	date: 1996/01/26 00:11:55;  author: thomas;  state: Exp;  lines: +17 -8
 * 	Add various things for doing DAD.
 * 	----------------------------
 * 	revision 1.7
 * 	date: 1996/01/25 16:58:09;  author: thomas;  state: Exp;  lines: +48 -19
 * 	Add support adding global addresses.  Keep track of onlink
 * 	 prefixes.  Add a per-interface structure to store information.
 * 	Do better source address selection.
 * 	----------------------------
 * 	revision 1.6
 * 	date: 1996/01/24 01:44:10;  author: thomas;  state: Exp;  lines: +2 -1
 * 	Add M_NOPROBE for ND.
 * 	----------------------------
 * 	revision 1.5
 * 	date: 1996/01/22 21:39:43;  author: thomas;  state: Exp;  lines: +7 -3
 * 	update to discovery-04
 * 	----------------------------
 * 	revision 1.4
 * 	date: 1996/01/19 18:03:02;  author: thomas;  state: Exp;  lines: +183 -149
 * 	Major reorganization and rewrite
 * 	----------------------------
 * 	revision 1.3
 * 	date: 1995/09/06 19:49:27;  author: thomas;  state: Exp;  lines: +4 -1
 * 	add authentication stub macro and extern for all_nodes
 * 	----------------------------
 * 	revision 1.2
 * 	date: 1995/09/02 19:41:04;  author: thomas;  state: Exp;  lines: +2 -2
 * 	starting using Matt's ND code
 * 	ANSI C cleanup
 * 	----------------------------
 * 	revision 1.1
 * 	date: 1995/09/01 23:45:25;  author: thomas;  state: Exp;
 * 	Initial revision
 * 	[1998/06/16  14:58:16  Jack_McCann]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: in6_var.h,v $ $Revision: 1.1.38.4 $ (DEC) $Date: 2003/11/13 22:42:44 $
 */

#ifndef _IN6_VAR_H_
#define	_IN6_VAR_H_

#include <netinet/nd6_cache.h>
#include <netinet/ipv6_swtab.h>
#include <netinet/in_route.h>

/* 
 * _IN6_DEBUG enables debugging printfs 
 */
#ifdef _KERNEL
#include <kern/thread.h>
#define _IN6_DEBUG 0	
#endif /* _KERNEL */

#if _IN6_DEBUG
extern int in6_whine;			/* complain about bad packets */
#define IN6_WHINE(level,x) if (in6_whine > level) printf##x
#else 
#define IN6_WHINE(level,x)
#endif

/* 
 * The following fields of the in6_ifnet structure are protected by 
 * the IN6_IFNET_LOCK:
 *	if6_hlim
 *	if6_rxmt_interval
 *	if6_first_probe_delay
 *	if6_reachable_time
 *	if6_real_first_probe_delay
 *	if6_real_rtr_solicit_delay
 *	if6_real_rxmt_interval
 *	if6_real_reachable_time
 *	if6_dadtries
 *	if6_link_mtu
 * 
 * The if6_refcnt field is protected by the IN6_IFNET_REF/IN6_IFNET_DEREF macros
 *
 * The remaining fields are not protected by any locks, since these fields
 * are set when the structure is allocated and are never updated:
 * 	if6_lladdr
 *	if6_ifp
 *	if6_settimer
 *	if6_max_link_mtu
 *	if6_flags
 *	if6_token
 *	if6_tokenlen
 */
struct in6_ifnet {
    struct in6_ifaddr *if6_lladdr;	/* Pointer to the link local address */
    struct ifnet *if6_ifp;
    void (*if6_settimer)(struct in6_ifnet *, int);
    unsigned if6_real_first_probe_delay;/* # of milliseconds before first probe delay */
    unsigned if6_real_rtr_solicit_delay;/* # of milliseconds before first RS */
    unsigned if6_max_link_mtu;		/* */
    u_int8_t if6_tokenlen;		/* interface token length (bits) */
    u_char   pad[3];
    struct in6_addr if6_token;		/* interface token */
    caddr_t if6_nd6_cache_head;		/* Neighbor cache entry list */

    unsigned if6_hlim;			/* unicast hop limit */
    unsigned if6_rxmt_interval;		/* # of "ticks" between solicitations */
    unsigned if6_first_probe_delay;	/* # of "ticks" until first probe */
    unsigned if6_reachable_time;	/* # of "ticks" a cache entry stay good */
    unsigned if6_real_rxmt_interval;	/* # of milliseconds between solicitations */
    unsigned if6_real_reachable_time;	/* # of milliseconds a cache entry is
					   reachable without confirmation */
    unsigned if6_dadtries;		/* # of times to do dupl. addr. detection */
    unsigned if6_link_mtu;		/* */
    unsigned if6_flags;			/* */
#define	IFF6_NOND6		0x0001U /* No  Neighbor Discovery needed */
#define	IFF6_NONUD		0x0002U /* NUD is not required */
#define	IFF6_NOLLADDR		0x0004U /* link has no link-layer addr for ND */
    unsigned if6_refcnt;		/* */
    long     reserved[3];		/* future use */
};


/* Flags in IFF6_CANTCHANGE can be set by kernel only */
#define IFF6_CANTCHANGE		(IFF6_NOND6|IFF6_NOLLADDR) 

/*
 * Define the structure used for IPv6 interface addresses
 * Fields of the structure are protected by the IN6_IFADDR_LOCK
 * The ia6_flags field, which is in the ifaddr part of the in6_ifaddr,
 * is protected by the INIFADDR_SPIN_LOCK.
 */

struct in6_ifaddr {
    struct ifaddr	ia6_ifa;	/* protocol-independent info */
#define ia6_ifp         ia6_ifa.ifa_ifp
#define ia6_flags       ia6_ifa.ifa_flags
    struct in6_localaddr *ia6_la6;
    struct in6_ifaddr    *ia6_next;	/* for linking multiple link local
					 * addresses (currently unused 
					 */
    struct sockaddr_in6 ia6_addr;	/* reserve space for unicast address */
    struct sockaddr_in6 ia6_dstaddr;	/* destination address */
    struct sockaddr_in6 ia6_netmask;	/* netmask for this address */
    unsigned		ia6_refcnt;	/* reference count */
};

#ifndef __VMS
#define IN6_IFADDR_REF(ia6) { \
	atomic_incl( &(ia6)->ia6_refcnt) ; \
}
#else /* __VMS */
#define IN6_IFADDR_REF(ia6) { \
	atomic_incl( (int *) &(ia6)->ia6_refcnt) ; \
}
#endif /* __VMS */

#ifndef __VMS
#define IN6_IFADDR_DEREF(ia6) { \
        if (atomic_decl(&(ia6)->ia6_refcnt) == 1) { \
		(void)(*ipv6_swtab->in6_ifaddr_free)(ia6);\
	} \
}
#else /* __VMS */
#define IN6_IFADDR_DEREF(ia6) { \
        if (atomic_decl((int *) &(ia6)->ia6_refcnt) == 1) { \
		(void)(*ipv6_swtab->in6_ifaddr_free)(ia6);\
	} \
}
#endif /* __VMS */


struct in6_localaddr {
    struct in6_localaddr *la6_next;	/* next local address.  
					 * MUST BE THE FIRST FIELD */
    struct rtentry *la6_rt;		/* associated route for this address */
    struct in6_ifnet *la6_if6;		/* owning interface for this address */
    struct in6_addr la6_addr;
    u_int  la6_scope;			/* identifies the scope of the address*/
#define	LA6_SCOPE_NODELOCAL	0x1	/* Node local entry */
#define LA6_SCOPE_IFLOCAL	LA6_SCOPE_NODELOCAL
#define	LA6_SCOPE_LINKLOCAL	0x2	/* Link local entry */
#define LA6_SCOPE_ADMINLOCAL	0x4	/* admin-local scope */
#define	LA6_SCOPE_SITELOCAL	0x5	/* Site local entry */
#define	LA6_SCOPE_ORGLOCAL	0x8	/* Org-local scope */
#define	LA6_SCOPE_GLOBAL	0xE	/* Global */
    u_int  la6_flags;
#define LA6_LOOPBACK		0x0001U	/* this is a loopback entry */
#define	LA6_MULTICAST		0x0002U	/* This refers to a multicast entry */
#define LA6_ANYCAST		0x0004U /* Anycast address entry */
#define	LA6_V4COMPAT		0x0008U	/* IPv4 compatible entry */
#define LA6_PROXY		0x0010U /* providing proxy for this address */
#define	LA6_TENTATIVE		0x0020U	/* This address is not yet valid */
#define	LA6_DEPRECATED		0x0040U	/* This address is going away */
#define	LA6_INVALID		0x0080U	/* Address is no longer valid */
#define	LA6_DADFAILED		0x0100U	/* Duplicate address check failed */
#define	LA6_NOREPORT		0x0200U	/* Don't send reports for this mcast */
#define LA6_MOBILE		0x0400U /* Mobile Node entry */
    u_int la6_refcnt;
    u_int pad_i[1];
    struct in6_localaddr *la6_work_next; /* next local address the timer thread
					  * has to do some work on */
    /* 64 byte cache boundry */
    union {
	struct {
	    struct in6_ifaddr *uni_ia6;	/* For link local */
	    struct in6_localaddr *uni_solmcast; /* solicited node multicast 
						 * (for ND) */
	    struct ifqueue *uni_advert_queue; /* queue to hold adverts */
	    unsigned uni_dadtimer;	/* duplicate address timer */
	    u_short uni_dadtries;	/* duplicate address tries */
	    u_short uni_dadsendfail;	/* unable to send dad solicitation */
#define	la6_ia6		  la6_un.un_uni.uni_ia6
#define	la6_solmcast	  la6_un.un_uni.uni_solmcast
#define	la6_dadtimer	  la6_un.un_uni.uni_dadtimer
#define	la6_dadtries	  la6_un.un_uni.uni_dadtries
#define	la6_dadsendfail	  la6_un.un_uni.uni_dadsendfail
#define la6_advert_queue  la6_un.un_uni.uni_advert_queue
#define la6_adverttimer	  la6_dadtimer	/* reuse dad timer for advertisements */
	} un_uni;
	struct {
	    unsigned mcu_timer;		/* ICMP MGM membership report timer */
    	    unsigned mcu_members;	/* # of times mcast addr was added */
#define	la6_timer	la6_un.un_mc.mcu_timer
#define	la6_members	la6_un.un_mc.mcu_members
	} un_mc;
    } la6_un;
};

/*
 * Define the structure used for recording network layer statistics
 */
struct ip6stat {
	u_long ips_rx_total;		/* total packets received */
	u_long ips_rx_idle_discards;	/* rcvd over inactive interface */
	u_long ips_rx_toosmall;		/* packet is too small */
	u_long ips_rx_tooshort;		/* mbuf is smaller then pload len */
	u_long ips_rx_badvers;		/* Version number not = 6 */
	u_long ips_rx_errors;		/* packet caused ICMPv6 error 2b sent */
	u_long ips_rx_local;		/* packet is for us */
	u_long ips_rx_nonlocal;		/* packet is not for us */
	u_long ips_rx_multicast;	/* multicast packet is for us */
	u_long ips_rx_badaligns;	/* packet is not quad-aligned */
	u_long ips_rx_noproto;		/* unknown or unsupported protocol */
	u_long ips_rx_delivered;	/* packets consumed here */
	u_long ips_rx_discarded;	/* packets not consumed here */
	u_long ips_rx_forwarded;	/* source routed packets forwarded */
	u_long ips_rx_tentative;	/* packets to tentative addresses */
	u_long ips_rx_proxy;		/* packets to proxy addresses */
	u_long ips_rx_mobile;		/* packets to mobile addresses */
	u_long ips_rx_mobile_encap;	/* mobile packets encapsulated */

	u_long ips_tx_local;		/* packets sourced locally */
        u_long ips_tx_fragmented;	/* fragment output datagram */
        u_long ips_tx_quota_exceeded;	/* long output queue full */
        u_long ips_tx_multicast;	/* multicast output packets */
        u_long ips_tx_forward;		/* forwarded datagrams */
        u_long ips_tx_attempts;		/* total # of output attempts */
        u_long ips_tx_failures;		/* total # of output failures */
        u_long ips_tx_looped_multicasts; /* total # of looped back multicasts */
/**/
	u_long ips_trl_trfailure;	/* IPv4 translation failure */
	u_long ips_enc_allocfailed;	/* encaps input - alloc failed */
/**/
	u_long ips_rip_noproto;		/* raw input - no matching pcb */
	u_long ips_rip_nospace;		/* raw input - no space in socket */
	u_long ips_rip_delivered;	/* raw input - success */
	u_long ips_rip_allocfailed;	/* raw input - alloc failed */
	u_long ips_rip_tooshort;	/* raw input - too short */
	u_long ips_rip_badcksum;	/* raw input - bad checksum */

	u_long ips_frag_packets;	/* packets fragmented */
	u_long ips_frag_fragments;	/* fragments built */
	u_long ips_frag_nofragpart;	/* frag part not found */
	u_long ips_frag_badhopbyhop;	/* hop-by-hop hdr not after IPv6 hdr */
	u_long ips_frag_ufpbadalign;	/* unfrag part end not quad-aligned */
	u_long ips_frag_ufptoobig;	/* unfrag part too big */
	u_long ips_frag_hdrtoobig;	/* fragment pkt hdr exceeds MCLBYTES */
	u_long ips_frag_jumbo;		/* pkt contains jumbo payload option */
	u_long ips_frag_allocfailed;	/* fragmentation - alloc failed */

	u_long ips_reas_fragsrcvd;	/* fragments received */
	u_long ips_reas_pktsreass;	/* packets reassembled */
	u_long ips_reas_timeout;	/* packet reassembly timeout */
	u_long ips_reas_copy;		/* unfrag part copied for reassembly */
	u_long ips_reas_ufptoobig;	/* unfrag part exceeds MCLBYTES */
	u_long ips_reas_badfraglen;	/* M set, frag len not multiple of 8 */
	u_long ips_reas_payloadtoobig;	/* reassembled payload too big */
	u_long ips_reas_overlap;	/* partial fragment overlap detected */
	u_long ips_reas_dupfrag;	/* duplicate fragment, discarded */
	u_long ips_reas_jumbo;		/* fragment has jumbo payload option */
	u_long ips_reas_allocfailed;	/* reassembly - alloc failed */
	u_long ips_reas_quota;		/* fragment would exceed reass limit */

	u_long ips_fwd_success;		/* pkts forwarded successfully */
	u_long ips_fwd_baddst;		/* pkts dropped, dst not forwardable */
	u_long ips_fwd_badsrc;		/* pkts dropped, src not forwardable */
	u_long ips_fwd_enobufs;		/* pkts dropped, congestion */
	u_long ips_fwd_emsgsize;	/* pkts dropped, packet too big */
	u_long ips_fwd_eother;		/* pkts dropped, other error */

#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t ips_lock;	/* statistics lock */
#endif
};

#include <netinet/ip6.h>

/*
 * Define a structure, used during IPv6 output processing, which will
 * point to where, within the mbuf chain, various options are found
 *
 */
struct in6optinfo {
    unsigned int        opt_flags;
#define OPT_NXTHOP		0x00000001	/* IPV6_NEXTHOP */
#define OPT_PKTINFO		0x00000002	/* IPV6_PKTINFO */
#define OPT_HOPLIMIT		0x00000004	/* IPV6_HOPLIMIT ancillary*/
#define OPT_HOPOPTS		0x00000008	/* IPV6_HOPOPTS */
#define OPT_DSTOPTS1		0x00000010	/* IPV6_RTHDRDSTOPTS */
#define OPT_RTHDR		0x00000020	/* IPV6_RTHDR */
#define OPT_DSTOPTS2		0x00000040	/* IPV6_DSTOPTS */
#define OPT_RIP6_HEADER		0x00000080	
#define OPT_RTHDR2		0x00000100	/* rthdr2 added by mip6 code */
#define OPT_TCLASS		0x00000200	/* IPV6_TCLASS */
#define OPT_DONTFRAG		0x00000400	/* IPV6_DONTFRAG */
    int	                opt_total_len;	/*space for hopopts, dstopts & rthdr */
    int	   		opt_hoplimit;
    int			opt_tclass;     /* this used to be undefined padding */
    struct rip6_header	opt_riphdr;
    int			opt_dont_frag;
    struct sockaddr_in6	opt_nxthop;
    struct in6_pktinfo	opt_pktinfo;
    struct in6_ifnet *	opt_if6;
    struct mbuf *	opt_hopopts;
    struct mbuf *	opt_dstopts1;
    struct mbuf *	opt_rthdr;
    struct mbuf *	opt_rthdr2;
    struct mbuf *	opt_dstopts2;
    u_long		opt_mip6_timestamp;  /* valid if OPT_RTHDR2 set */
};

struct ip6option {
    unsigned offset;			/* offset of currect header */
    unsigned length;			/* length in bytes of current header */
    unsigned next_hdr;			/* next header in packet */
    struct ip6option *ip6o_next;	/* next header of same type */
};

struct ip6opthdr {
    unsigned long found;		/* enough for future flags */
    struct ip6option *ip6h_first;	/* points to first opt header */
    struct ip6option *ip6h_last;	/* points to last opt header in list */
};

struct ip6_rxinfo {
    struct mbuf *rx_mbuf;		/* IPv6 Packet in toto */
    const struct ip6_hdr *rx_ip6hdr;	/* IPv6 Header */
    const struct icmp6_hdr *rx_icmp6hdr;/* ICMPv6 Header */
    struct in6_ifnet *rx_if6;		/* Received interface */
    struct in6_localaddr *rx_la6;	/* Received address */
    unsigned rx_packet_length;		/* Length in host order */
    unsigned rx_header_offset;		/* offset from start of IPv6 packet */
					/*  to start of current header */
    unsigned rx_prevhdr_offset;		/* offset from start of IPv6 packet */
					/*  to start of previous header */
    unsigned rx_icmp_type;		/* ICMP error type */
    unsigned rx_icmp_code;		/* ICMP error code */
    unsigned rx_icmp_data;		/* ICMP error data (offset, mtu, etc) */
    unsigned rx_is_multicast:1;		/* Multicast address */
    unsigned rx_is_aligned:1;		/* mbuf is aligned */
    unsigned rx_should_be_jumbo:1;	/* jumbo payload option expected */
    unsigned rx_is_jumbo:1;		/* jumbo payload option present */
    unsigned rx_srcrt:1;		/* source routed */
    unsigned rx_forwarding:1;		/* packet is being forwarded */
    unsigned rx_is_proxy:1;		/* proxy address */
    unsigned rx_is_mobile:1;		/* mobile address */
    unsigned rx_is_homeaddr:1;		/* home address option present */
    unsigned rx_swapped_homeaddr:1;	/* home address was swapped with src */
    unsigned rx_pad_bit3:1;		/* padding */
    unsigned rx_pad_bit4:1;		/* padding */
    unsigned rx_pad_bit5:1;		/* padding */
    unsigned rx_pad_bit6:1;		/* padding */
    unsigned rx_pad_bit7:1;		/* padding */
    unsigned rx_pad_bit8:1;		/* padding */
    unsigned short rx_pad_short:1;	/* padding */
    unsigned int rx_pad_int:1;		/* padding */
    struct ip6_hdr rx_ip6hdr_buf;	/* Space for copy of IPV6 header */
    struct ip6opthdr rx_hopopts;	/* where in chain hopbyhop was found */
    struct ip6opthdr rx_dstopts;	/* where in chain dstopt was found */
    struct ip6opthdr rx_rthopts;	/* where in chain routing was found */
    struct ip6opthdr rx_dstopts2;	/* where in chain 2nd dstopts found */
    struct in6_addr rx_homeaddr;	/* saved home address option */
    struct ip6opthdr rx_mobhdr;		/* where in chain mob header found */
};

struct ip6_txinfo {
    struct mbuf *tx_mbuf;		/* IPv6 packet */
    struct ip6_hdr *tx_ip6;		/* IPv6 header */
    struct in_route *tx_ro;		/* route */
    struct in6_ifnet *tx_if6;		/* interface */
    struct sockaddr_in6 *tx_nexthop;	/* next hop destination */
    struct ip6_moptions *tx_imo6;	/* multicast options */
    unsigned tx_pmtudisc:1;		/* sender wants pmtu discovery */
    unsigned tx_dontroute:1;		/* don't route */
    unsigned tx_rawoutput:1;		/* raw output packet */
    unsigned tx_cancacheopt:1;		/* can cache tx_opt if passed-back */
    unsigned tx_rawmobile:1;		/* raw mip6 making call */
    unsigned tx_nomobile:1;		/* no mip6 on route lookup */
    unsigned tx_ipsecneeded:1;		/* IPsec protection needed for packet */
    u_int32_t tx_mtu;			/* max packet size (returned) */
    struct in6optinfo *tx_opt;		/* optional data for xmit */
    struct mbuf *tx_partial_orig_packet; /* partial original packet for IPsec use */
};

/* The fields of the ip6_moptions struct are protected by 
 * the SOCKET_LOCK and INPCB_LOCK
 */
struct ip6_moptions {
    struct in6_ifnet *imo6_multicast_if6; /* ifp for outgoing multicasts */
    u_char imo6_multicast_hlim;		/* hop limit for outgoing multicasts */
    u_char imo6_multicast_loop;		/* 1 => hear sends if a member */
    u_char imo6_v4mapped_memb;		/* no. of v4mapped members */
    u_int  imo6_num_memberships;	/* no. memberships this socket */
    struct in6_localaddr **imo6_membership;
    u_int  imo6_membership_size;	/* current size of membership list */
};

/*
 * Given a pointer to an ifaddr (in6_ifaddr),
 * return a pointer to the address as a sockaddr_in6.
 */
#define IA_SIN6(ia) (&(((struct in6_ifaddr *)(ia))->ia6_addr))

#ifdef _KERNEL

#if NETSYNC_LOCK


/* 
 * The IN6_LADDR_ADD_DEL_LOCK prevents multiple threads from 
 * simultaneously initializing and uninitializing interfaces (and therefore
 * prevents in6_ifnets[] and in6_max_ifindex from changing), and
 * from simultaneously adding and deleting in6_localaddr addresses
 * to/from the in6_localaddrs[] list.  It also protects the
 * la6_members field of an in6_localaddr struct.
 */
ndecl_lock_data(extern, in6_laddr_add_del_lock)
#define IN6_LADDR_ADD_DEL_LOCKINIT()     ulock_setup(&in6_laddr_add_del_lock, in6_laddr_add_del_li, TRUE)
#define IN6_LADDR_ADD_DEL_WRITE_LOCK()   ulock_write(&in6_laddr_add_del_lock)
#define IN6_LADDR_ADD_DEL_READ_LOCK()    ulock_read(&in6_laddr_add_del_lock)
#define IN6_LADDR_ADD_DEL_UNLOCK()       ulock_done(&in6_laddr_add_del_lock)
#define IN6_LADDR_ADD_DEL_ISLOCKED()     (lockmode==0||lock_holder(&in6_laddr_add_del_lock))

/* 
 * The IN6_LOCALADDR_READ_LOCK and IN6_LOCALADDR_WRITE_LOCK protect
 * these data structures:
 * 	- in6_localaddrs[]
 * 	- in6_defaultaddr
 * 	- la6_refcnt, la6_flags, la6_timer, la6_dadtimer & la6_dadtries
 *	  fields of an in6_localaddr struct.
 * 	- la6_adverttimer (advertisement timer)
 *	- la6_advert_queue
 * 	- icmp6_mgm_timers_active
 * 	- nd6_dad_refcnt
 * 	- nd6_dad_tries
 * 	- nd6_dad_skipped
 */
ndecl_rws_lock_data(extern, in6_localaddr_lock)
#define IN6_LOCALADDR_LOCKINIT() 	in6_localaddr_lock=rws_alloc(in6_localaddr_li, 0)
#define IN6_LOCALADDR_READ_LOCK()	rws_read_lock(in6_localaddr_lock)
#define IN6_LOCALADDR_READ_UNLOCK()	rws_read_unlock(in6_localaddr_lock)
#define IN6_LOCALADDR_WRITE_LOCK()	rws_write_lock(in6_localaddr_lock)
#define IN6_LOCALADDR_WRITE_UNLOCK()	rws_write_unlock(in6_localaddr_lock)
#ifdef NOTYET	/* No way to do this yet with R/W spin locks */
#define IN6_LOCALADDR_ISLOCKED() (lockmode==0||simple_lock_holder(&in6_localaddr_lock))
#else
#define IN6_LOCALADDR_ISLOCKED() (1)
#endif /* NOTYET */

/*
 * The IN6_IFNET_LOCK protects these data structures:
 *	- in6_ifnets[]
 *	- in6_max_ifindex
 *	- fields of the in6_ifnet struct
 */
udecl_simple_lock_data(extern, in6_ifnet_lock)
#define IN6_IFNET_LOCKINIT()     usimple_lock_setup(&in6_ifnet_lock, in6_ifnet_li)
#define IN6_IFNET_LOCK()         usimple_lock(&in6_ifnet_lock)
#define IN6_IFNET_UNLOCK()       usimple_unlock(&in6_ifnet_lock)
#define IN6_IFNET_ISLOCKED()     (lockmode==0||simple_lock_holder(&in6_ifnet_lock))

/*
 * The IN6_IFADDR_LOCK protects these data structures:
 *	- fields of the in6_ifaddr struct, except for ia6_flags
 */
udecl_simple_lock_data(extern, in6_ifaddr_lock)
#define IN6_IFADDR_LOCKINIT()	usimple_lock_setup(&in6_ifaddr_lock, in6_ifaddr_li)
#define IN6_IFADDR_LOCK()	usimple_lock(&in6_ifaddr_lock)
#define IN6_IFADDR_UNLOCK()	usimple_unlock(&in6_ifaddr_lock)
#define IN6_IFADDR_ISLOCKED()	(lockmode==0||simple_lock_holder(&in6_ifaddr_lock))

/*
 * The IN6_RANDOMSEED_LOCK protects these data structures:
 *	- in6_randomseed
 */
udecl_simple_lock_data(extern, in6_randomseed_lock)
#define IN6_RANDOMSEED_LOCKINIT()	usimple_lock_setup(&in6_randomseed_lock, in6_randomseed_li)
#define IN6_RANDOMSEED_LOCK()	usimple_lock(&in6_randomseed_lock)
#define IN6_RANDOMSEED_UNLOCK()	usimple_unlock(&in6_randomseed_lock)
#define IN6_RANDOMSEED_ISLOCKED()	(lockmode==0||simple_lock_holder(&in6_randomseed_lock))

#else /* NETSYNC_LOCK */
#define IN6_LADDR_ADD_DEL_LOCKINIT()
#define IN6_LADDR_ADD_DEL_LOCK()
#define IN6_LADDR_ADD_DEL_UNLOCK()
#define IN6_LADDR_ADD_DEL_ISLOCKED()
#define IN6_LOCALADDR_LOCKINIT()
#define IN6_LOCALADDR_READ_LOCK()
#define IN6_LOCALADDR_READ_UNLOCK()
#define IN6_LOCALADDR_WRITE_LOCK()
#define IN6_LOCALADDR_WRITE_UNLOCK()
#define IN6_LOCALADDR_ISLOCKED()
#define IN6_IFNET_LOCKINIT()
#define IN6_IFNET_LOCK()
#define IN6_IFNET_UNLOCK()
#define IN6_IFNET_ISLOCKED()
#define IN6_IFADDR_LOCKINIT()
#define IN6_IFADDR_LOCK()
#define IN6_IFADDR_UNLOCK()
#define IN6_IFADDR_ISLOCKED()
#define IN6_RANDOMSEED_LOCKINIT()
#define IN6_RANDOMSEED_LOCK()
#define IN6_RANDOMSEED_UNLOCK()
#define IN6_RANDOMSEED_ISLOCKED()
#endif /* NETSYNC_LOCK */

extern int in6_max_ifindex;
extern struct in6_ifnet **in6_ifnets;

#ifndef __VMS
#define IN6_IFNET_REF(if6)  {\
	    atomic_incl(&(if6)->if6_refcnt); \
} 
#else /* __VMS */
#define IN6_IFNET_REF(if6)  {\
	    atomic_incl((int *) &(if6)->if6_refcnt); \
} 
#endif /* __VMS */

#ifndef __VMS
#define	IN6_IFNET_DEREF(if6)  {\
	    if (atomic_decl(&(if6)->if6_refcnt)  == 1) \
		(*ipv6_swtab->in6_ifnet_free)(if6);\
} 
#else /* __VMS */
#define	IN6_IFNET_DEREF(if6)  {\
	    if (atomic_decl((int *) &(if6)->if6_refcnt)  == 1) \
		(*ipv6_swtab->in6_ifnet_free)(if6);\
} 
#endif /* __VMS */

#define IN6_IFNET_OF_IFINDEX(if6, ifindex) { \
	struct in6_ifnet  *_if6_; \
	u_int _index_ = ifindex; \
	IN6_IFNET_LOCK(); \
        if ((_index_ < in6_max_ifindex) && \
	    ((_if6_ = in6_ifnets[_index_]) != NULL)) { \
		IN6_IFNET_REF(_if6_); \
	} else { \
		_if6_ = NULL; \
	} \
	IN6_IFNET_UNLOCK(); \
        (if6) = _if6_; \
}

/*
 * Hash macro given 128-bit in6_addr as a key returns bucket index
 * for table size (1 << in6ifaddr_hexp), modified version of the
 * _INIFADDR_HASH macro.  We simply hash over the lower 32 bits.
 */
#define IN6_LOCALADDR_HASH(_dst_, _hb_)				\
    {								\
       int _i_;							\
       (_hb_) = (_dst_)->s6_laddr[3];				\
       for (_i_ = in6ifaddr_hexp; _i_ < 32; _i_ += in6ifaddr_hexp)\
	    (_hb_) += ((_dst_)->s6_laddr[3] >> _i_);		\
       (_hb_) &= in6ifaddr_hmask;				\
     }
#define _IN6_LOCALADDR_HASH_ENABLED()		(in6ifaddr_hexp > 0)

#define _IN6IFADDR_MAX_HEXP  13   /* max size (2^max_hexp) of in6_localaddrs */
#define _IN6IFADDR_MIN_HEXP  4    /* min size (2^min_hexp) of in6_localaddrs */
#define _IN6IFADDR_DEF_HEXP  5    /* default size (2^hexp) of in6_localaddrs */

extern unsigned int in6ifaddr_hexp, in6ifaddr_hsize;
extern unsigned int in6ifaddr_hmask;
extern struct in6_localaddr *in6_defaultaddr;
extern struct in6_localaddr **in6_localaddrs;
extern struct in6_localaddr **oldin6_localaddrs;

#ifndef __VMS
#define IN6_LOCALADDR_REF(la6) { \
	atomic_incl( &(la6)->la6_refcnt) ; \
} 
#else /* __VMS */
#define IN6_LOCALADDR_REF(la6) { \
	atomic_incl( (int *) &(la6)->la6_refcnt) ; \
} 
#endif /* __VMS */

#ifndef __VMS
#define	IN6_LOCALADDR_DEREF(la6) { \
	if (atomic_decl(&(la6)->la6_refcnt) == 1) { \
		(*ipv6_swtab->in6_localaddr_free)(la6); \
	} \
}
#else /* __VMS */
#define	IN6_LOCALADDR_DEREF(la6) { \
	if (atomic_decl((int *) &(la6)->la6_refcnt) == 1) { \
		(*ipv6_swtab->in6_localaddr_free)(la6); \
	} \
}
#endif /* __VMS */

/*
 * Instead of looking at icmp6_mgm_timers_active, nd6_dad_refcnt, and
 * nd6_adverts in icmp6_fasttimo_rad(), then possibly searching the whole
 * in6_localaddrs[] array looking for the addresses that have a pending
 * timer event, we instead create a linked-list of these addresses on each
 * RAD (since there are per-RAD timers on NUMA machines).  Each RAD's list
 * contains only addresses associated with interfaces on that RAD via
 * la6->la6_if6->if6_ifp->if_rad_id, and each such address is linked
 * together using the la6->la6_work_next pointer.
 *
 * This was determined necessary when stress testing the Mobile IPv6
 * Home Agent code, having large numbers of addresses being added to
 * the system, some small subset of those having DAD performed on them.
 * This led to huge stall times and lock miss rates even on the fastest
 * of systems since the icmp6_fasttimo_rad() timer runs 5 times a second.
 * These changes reduced time spent in the timer routine to noise.
 *
 * Macros to insert/remove an address from the "work queue".
 * The IN6_LOCALADDR_WRITE_LOCK() must be held when calling these.
 *
 */
#define RAD2IN6LWORK(_rad_) (_rad_)->in6_localaddrs_work

#define	IN6_LOCALADDR_WORK_INSERT(la6) { \
	struct rad  *_rad_ = rad_id_to_rad(la6->la6_if6->if6_ifp->if_rad_id); \
	(la6)->la6_work_next = RAD2IN6LWORK(_rad_); \
	RAD2IN6LWORK(_rad_) = (la6); \
	IN6_LOCALADDR_REF((la6)); \
}

#define	IN6_LOCALADDR_WORK_REMOVE(la6) { \
	struct rad  *_rad_ = rad_id_to_rad((la6)->la6_if6->if6_ifp->if_rad_id);\
	struct in6_localaddr **_la6_p_ = &RAD2IN6LWORK(_rad_); \
	for (; (*_la6_p_) != NULL; _la6_p_ = &(*_la6_p_)->la6_work_next) { \
		if ((la6) == (*_la6_p_)) { \
			(*_la6_p_) = (la6)->la6_work_next; \
			(la6)->la6_work_next = NULL; \
			IN6_LOCALADDR_DEREF((la6)); \
			break; \
		} \
	} \
}

extern const struct in6_addr in6_linklocal_all_nodes;

#define IPV6STAT(field)                       \
	  NETSTAT_LOCK(&ip6stat.ips_lock);   \
          ip6stat.field;                     \
	  NETSTAT_UNLOCK(&ip6stat.ips_lock)

extern struct ip6stat ip6stat;

/*
 * Macro used to make sure output headers are 64-bit aligned
 */
#define align8(x)  (((u_long)(x) + 7) & ((u_long) ~7))

extern struct domain inet6domain;
extern struct protosw *inet6sw;
extern CONST struct protosw inet6sw_stub[];
extern u_char ip6_protox[];

#define	IN6_ADDRSTRLEN 50
extern const char *inet6_ntoa(const struct in6_addr *, char [IN6_ADDRSTRLEN]);


#ifndef offsetof
#define offsetof(s_name, s_member) \
        ((size_t)((char *)&((s_name *)0L)->s_member - (char *)0L))
#endif

/*
 * Find the address of a byte with the given offset into an mbuf.
 */

#define M_FINDBYTE(m, off, ptr, cast)					\
        do {								\
                register u_int _len;					\
                register u_int _off = (off);				\
                register const struct mbuf *_m = (m);			\
									\
		while (_m != NULL) {					\
			if ((_len = _m->m_len) != 0) {			\
				if (_off < _len)			\
					break;				\
	                       	_off -= _len;				\
			}						\
			_m = _m->m_next;				\
                }							\
                if (_m == NULL) {					\
                        (ptr) = (cast) NULL;				\
                } else {						\
                        (ptr) = (cast) (_m->m_data + _off);		\
                }							\
        } while (0)

enum in6_disposition {
    IN6_RX_PROCESS_NEXT_HEADER,
    IN6_RX_SILENTLY_DROP,
    IN6_RX_DELIVERED,
    IN6_RX_FORWARD,
    IN6_RX_SEND_ICMP_ERROR
};

/*
 * Interface identifier (IID) lengths (bits)
 */

#define IPV6_LOOPBACK_IID_LENGTH       0
#define IPV6_ETHERNET_IID_LENGTH      64	/* rfc 2464 */
#define IPV6_FDDI_IID_LENGTH          64	/* rfc 2467 */
#define IPV6_IPV4_IID_LENGTH          64	/* rfc TBD (IPv6 Trans Mech) */
#define IPV6_PPP_IID_LENGTH           64	/* rfc 2472 */

/*
 * Macro to map an IEEE 802 MAC address to an IPv6 interface
 * identifier (IID) as defined in RFC 2373.
 */

#define IN6_IEEE802_TO_IID(in6, enaddr) {	\
	/* struct in6_addr *in6; */		\
	/* u_char enaddr[6]; */			\
	(in6)->s6_addr[8] = 			\
	    ((enaddr)[0] & 0x02) ?		\
		((enaddr)[0] & ~0x02) :		\
		((enaddr)[0] | 0x02);		\
	(in6)->s6_addr[9] = (enaddr)[1];	\
	(in6)->s6_addr[10] = (enaddr)[2];	\
	(in6)->s6_addr[11] = 0xff;		\
	(in6)->s6_addr[12] = 0xfe;		\
	(in6)->s6_addr[13] = (enaddr)[3];	\
	(in6)->s6_addr[14] = (enaddr)[4];	\
	(in6)->s6_addr[15] = (enaddr)[5];	\
}

/*
 * Interfaces that have  IFF_MULTICAST (hardware mcast) set support 
 * IP multicasting.  For interfaces like PPP, multicasting reduces to
 * unicast, even though IFF_MULTICAST is not set.
 * IN6_IS_MCAST_INTF must be called with the IN6_IFNET_LOCK held
 * and must minimally check that the in6_ifnets[idx] is non-null.
 */
#define IN6_IS_MCAST_INTF(idx) \
	/* int idx */ \
	( in6_ifnets[idx] &&  \
	 ((in6_ifnets[idx]->if6_ifp->if_flags & IFF_MULTICAST) || \
	  (in6_ifnets[idx]->if6_ifp->if_type == IFT_PPP)))


extern int ipv6forwarding;		    /* forward IPv6 packets */
extern int ipv6router;			    /* act as IPv6 router */
extern struct ifqueue ip6intrq; 		    /* IPv6 packet input queue */

/*
 * Flags for in6_localaddr_pick()
 */

#define IN6_MUST_MATCH_IF	0x01	/* must match interface */

struct ipv6control {
	thread_t icmp6_slowtimo;
	wait_queue_data_t icmp6_slowtimo_waitq;
	thread_t icmp6_fasttimo;
	wait_queue_data_t icmp6_fasttimo_waitq;
};

#define RAD2IPV6CTL(__rad) ((struct ipv6control *)((__rad)->ipv6control))

#endif /* _KERNEL */

#endif /* _IN6_VAR_H_ */
