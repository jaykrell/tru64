/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: in6.h,v $
 * Revision 1.1.39.3  2003/10/15  21:11:01  Vladislav_Yasevich
 * 	Update Advanced API to rfc3542:
 * 	- add new options: IPV6_TCLASS, IPV6_RECVTCLASS, IPV6_USE_MIN_MTU
 * 	IPV6_DONTFRAG, IPV6_RECVPATHMTU, IPV6_PATHMTU
 * 	- add ip6_mtuinfo structure definition.
 *
 * Revision 1.1.39.2  2003/09/23  21:52:46  Brian_Haley
 * 	Mobile IPv6 update.
 * 	Add ADMIN multicast scope as per latest addressing architecture
 * 	(Qar 95316).
 * 	Added preferred lifetime to Mobile IPv6 section of ip6ifreq struct
 * 	to support draft 21.
 * 	Mobile IPv6 draft 18 support:
 * 	- added macro to create a mask for the lower 64-bits of an in6_addr so
 *   we can use it in creating link-local proxy addresses for mobility
 * 	- added a macro to create a link-local address from a global address given
 *   a netmask
 * 	- modified ip6ifreq to support SIOCIPV6ADDHOMEPREFIX and
 *   SIOCIPV6REMHOMEPREFIX by adding a prefix/prefixlen/advlifetime/
 *   flags union
 * 	- added Routing Header Type 2
 * 	- added Home Agent Anycast init
 * 	- added proxy and mobile ifr flags
 * 	- added IPV6_RTHDR2 define
 * 	- fixed IN6_ARE_ADDR_SAMEPREFIX() macro to correctly mask both addresses
 *   given when comparing
 *
 * Revision 1.1.39.1  2003/09/10  17:47:42  Vladislav_Yasevich
 * 	Updated the constant for IPV6_MAX_MEMBERSHIPS and added a
 * 	a constant for IPV6_DEFAULT_MEMBERSHIPS to reflect the initial
 * 	number of memberships supported per socket. QAR 97048.
 *
 * Revision 1.1.30.3  2002/01/29  21:18:53  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 1.1.30.2  2002/01/10  19:21:07  Vladislav_Yasevich
 * 	Added the deffinition for the IPV6_RTF_MINMTU [mtu < 1200]. QAR 83232.
 *
 * Revision 1.1.30.1  2001/12/17  20:54:53  Vladislav_Yasevich
 * 	Removed #include of ipv6_swtab.h to fix some header file compile
 * 	problems.
 * 	[2001/10/10  15:35:38  Brian_Haley]
 *
 * 	Changes from wildcatos-85-harter:
 * 	- Sowmini's tunnel changes:
 *   o Added macros to deal with 6-to-4 addresses.
 * 	[2001/10/03  14:51:38  Geraldine_Harter]
 *
 * 	Merge of Anycast Address implementation into wcalpha.
 * 	[2001/10/02  15:31:16  Vladislav_Yasevich]
 * 	Merge of the Advanced API implementations from wildcat.classic
 * 	[2001/09/25  21:08:00  Vladislav_Yasevich]
 * 	[2001/10/02  15:44:40  Vladislav_Yasevich]
 *
 * Revision 1.1.20.4  2001/02/27  15:14:48  Vladislav_Yasevich
 * 	Renamed the v6only socket option according to 2553bis-02.
 *
 * Revision 1.1.20.3  2000/12/11  16:26:35  Vladislav_Yasevich
 * 	Added a deffinition for an IPV6_IPV6ONLY socket option.
 *
 * Revision 1.1.20.2  2000/10/12  16:37:17  Vladislav_Yasevich
 * 	Added macros that identify the address as unspecified (either
 * 	:: or ::ffff:0.0.0.0)
 *
 * Revision 1.1.20.1  2000/07/19  15:34:09  Sowmini_Varadhan
 *    Added SIOCIPV6DELGATE and moved ipv6 ioctls to ioctl.h
 *
 * Revision 1.1.17.2  1999/12/16  20:48:13  Sowmini_Varadhan
 * 	Added radv_flags to ip6ifreq
 *
 * Revision 1.1.17.1  1999/10/18  20:20:59  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 1.1.8.13  1999/07/22  19:01:11  Sowmini_Varadhan
 * 	- include ipv6_swtab.h
 * 	[1999/07/22  14:24:08  Sowmini_Varadhan]
 *
 * Revision 1.1.8.12  1999/06/08  18:09:44  Jack_McCann
 * 	IPv6 EAK X6.3 merge to Steel BL23
 * 	- do not merge unused IP_FLOWLABEL define
 * 	- move all IPv6-related IPPROTO_xxx defines to in.h so they
 * 	  are all in one place
 * 	- merge full set of IPv6 socket options
 * 	- add/rename IP_RXHDR to IPV6_RXHDR to be consistent with other
 * 	  IPPROTO_IPV6 level options
 * 	- for rfc2553 compliance, rename IPV6_ADD_MEMBERSHIP to
 * 	  IPV6_JOIN_GROUP, and IPV6_DROP_MEMBERSHIP to IPV6_LEAVE_GROUP
 * 	- move extern declarations for inet6domain and inet6sw to in6_var.h
 * 	[1999/06/08  15:51:58  Jack_McCann]
 * 
 * Revision 1.1.8.11  1999/03/26  21:41:26  Jack_McCann
 * 	- remove obsolete/unused defines (IPV6_ADDRFORM, IPV6_RECVSRCRT,
 * 	  IPV6_RECVIF, IPV6_SENDIF, IPV6_SR_MAXADDR)
 * 	- add _BEGIN_CPLUSPLUS/_END_CPLUSPLUS around rfc2292 function
 * 	  prototypes (PTR 52-1-74) and use the __() macro
 * 	[1999/03/26  21:08:48  Jack_McCann]
 * 
 * Revision 1.1.4.6  1999/02/04  21:16:37  Vladislav_Yasevich
 * 	Merge left the file checked out.
 * 	[1999/02/04  21:14:20  Vladislav_Yasevich]
 * 
 * 	Moved sockaddr_storage to socket.h
 * 	[1999/02/02  19:01:24  Vladislav_Yasevich]
 * 
 * 	Added sockaddr_storage structure described in section 3.10 ( Prtability
 * 	Additions ) of the draft-ietf-ipngwg-bsd-api-new-04 Internet Draft.
 * 	Also added IPPROTO_IPV6 and other defines needed for IPv6
 * 	set/getsockopt.
 * 	[1998/12/21  19:58:06  Vladislav_Yasevich]
 * 
 * Revision 1.1.8.10  1999/01/26  19:35:35  Vladislav_Yasevich
 * 	Added sin6_scope_id field to sockaddr_in6 as per
 * 	draft-ietf-ipngwg-bsd-api-new-05.txt.  Also fixed up the macros
 * 	that test address compatibilities.
 * 	[1999/01/25  21:33:17  Vladislav_Yasevich]
 * 
 * Revision 1.1.8.9  1998/12/16  14:33:22  Sowmini_Varadhan
 * 	make SIOCIPV6DIFADDR an _IOWR
 * 	[1998/12/15  22:31:22  Sowmini_Varadhan]
 * 
 * Revision 1.1.4.5  1998/12/03  19:58:29  Vladislav_Yasevich
 * 	Added XOPEN_SOURCE_EXTENDED to the sockaddr_in6 for correct deffinition of
 * 	sin_len and sin_family.
 * 	[1998/12/03  19:29:46  Vladislav_Yasevich]
 * 
 * 	Changed the family definition in sockaddr_in6 to the way it was before.
 * 	[1998/12/03  18:59:23  Vladislav_Yasevich]
 * 
 * Revision 1.1.4.4  1998/12/02  17:35:35  Vladislav_Yasevich
 * 	Updated according to the new spec draft-ietf-ipngwg-bsd-api-new-04.
 * 	[1998/11/25  15:31:43  Vladislav_Yasevich]
 * 
 * Revision 1.1.8.8  1998/10/30  16:58:26  Jack_McCann
 * 	- remove definition of 'struct ip6route', replaced by
 * 	  'struct in_route' in in_route.h
 * 	- remove include of <net/route.h>, no longer needed
 * 	- add include of <net/if.h> for IFNAMSIZ
 * 	- remove IFNAMSIZ ifdefs around ip6ifreq and SIOCIPV6xxx ioctls
 * 	[1998/10/29  18:38:45  Jack_McCann]
 * 
 * Revision 1.1.8.7  1998/09/15  18:08:28  Eric_Wong
 * 	RFC2292 Advanced Sockets API for IPv6 changes
 * 	- add new defines for IPv6 socket options
 * 	[1998/09/15  15:02:30  Eric_Wong]
 * 
 * Revision 1.1.8.6  1998/08/11  18:45:11  Geraldine_Harter
 * 	Remove support for IPV6_TOKEN_COMPAT
 * 	[1998/08/06  17:19:39  Geraldine_Harter]
 * 
 * Revision 1.1.8.5  1998/08/05  15:18:22  Jack_McCann
 * 	Spec updates:
 * 	- remove IPV6_PRIORITY_xxx constants
 * 	- remove IPV6_FLOWINFO_SRFLAG, IPV6_SRFLAG_NONE, IPV6_SRFLAG_STRICT,
 * 	  IPV6_SRFLAG_LOOSE, IPV6_FLOWINFO_PRIORITY, IPV6_FLOWINFO_FLOWLABEL
 * 	[1998/08/05  14:30:56  Jack_McCann]
 * 
 * Revision 1.1.8.4  1998/07/24  20:44:26  Sowmini_Varadhan
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -visual **
 * 		** Ancestor revision:	1.1.8.2 **
 * 		** Merge revision:	1.1.8.3 **
 * 	 	** End **
 * 	[1998/07/24  20:28:41  Sowmini_Varadhan]
 * 
 * 	  - remove definition of SIOCIPTUNNEL (ioctl replaced by cfg_subsys_op)
 * 	  - PPP over IPv6 - added support for local and remote id (ifr6_lid and
 * 	    ifr6_rid) in the ip6ifreq used to initialize interfaces.
 * 	  - added SIOCIPV6IFUNINIT
 * 	  - moved iptunnelreq to if_iptunnel.h
 * 	[1998/07/24  17:54:25  Sowmini_Varadhan]
 * 
 * Revision 1.1.8.3  1998/07/16  14:35:58  Ravi_Shankar
 * 	Backport the updates to the basic API from steelos.bl16
 * 	[1998/07/15  11:43:21  Ravi_Shankar]
 * 
 * Revision 1.1.8.2  1998/06/22  20:59:21  Jack_McCann
 * 	IPv6 EAK version X6.2 initial submit to ipv6os pool
 * 
 * 	IPv6 V4.0D merge
 * 	[1998/06/16  16:00:36  Jack_McCann]
 * 
 * Revision 1.1.4.3  1998/04/24  20:45:27  Ravi_Shankar
 * 	Updated api, ipv6 socket interface extensions as per Internet Draft draft-ietf-ipngwg-bsd-api-new-01.txt
 * 	[1998/04/22  19:21:57  Ravi_Shankar]
 * 
 * 	revision 1.28 date: 1998/03/06 14:48:34;  author: varadhan
 * 	added definition for IPTR_OP_SHOW (support for `iptunnel show`)
 * 
 * 	revision 1.27 date: 1998/02/19 19:38:48;  author: varadhan
 * 	added SIOCIPTUNNEL
 * 
 * 	revision 1.26 date: 1998/01/12 19:02:22;  author: varadhan
 * 	Added SIOCIPV6ADDROUT
 * 
 * 	revision 1.25 date: 1997/10/30 19:09:45;  author: gfisher
 * 	name space changes for the advanced socket API
 * 
 * Revision 1.1.4.2  1997/09/30  13:13:50  Jack_McCann
 * 	 * IPv6 hooks:
 * 	 * - incorporate header file from IPv6 pool
 * 	[1997/09/24  13:41:53  Jack_McCann]
 * 
 * 	revision 1.24 date: 1997/08/05 18:55:37;  author: mccann
 * 	add define for IPV6_DEFAULT_UNICAST_HOPLIMIT
 * 
 * 	revision 1.23 date: 1997/08/03 21:16:15;  author: bound
 * 	Multicast for RFC 2133
 * 
 * 	revision 1.22 date: 1997/07/16 16:37:32;  author: mccann
 * 	update IN6_xxx macros to rfc2133, remove obsolete macros
 * 
 * 	revision 1.21 date: 1997/07/11 21:32:09;  author: mccann
 * 	BIND 8.1.1 and rfc2133 (partial) checkin
 * 
 * 	revision 1.20 date: 1997/03/24 18:10:50;  author: root
 * 	remove revision history so it does not appear in kit
 * 
 * 	revision 1.19 date: 1997/02/18 19:34:29;  author: mccann
 * 	DIGITAL UNIX V4.0B merge
 * 
 * 	revision 1.18 date: 1997/02/04 01:57:57;  author: mccann
 * 	RIPng + multilink checkin, sct 19970203-mccann-ripng_multilink.txt
 * 
 * 	revision 1.17 date: 1996/08/02 16:08:00;  author: thomas
 * 	remove u_intXXm_t.
 * 
 * 	revision 1.16 date: 1996/08/01 20:50:46;  author: mccann6
 * 	add IPV6ADDR_LINKLOCAL_ALL_ROUTERS_INIT
 * 
 * 	revision 1.15 date: 1996/07/22 16:27:42;  author: thomas
 * 	Kill _SIT_
 * 
 * 	revision 1.14 date: 1996/05/31 20:46:35;  author: mccann
 * 	bsd-api-05 checkin
 * 
 * 	revision 1.13 date: 1996/01/31 20:19:09;  author: thomas
 * 	Fix macros
 * 
 * 	revision 1.12 date: 1996/01/31 00:12:49;  author: thomas
 * 	Add new ioctls for set ifaddr attributes
 * 
 * 	revision 1.11 date: 1996/01/29 16:52:07;  author: thomas
 * 	fix some more GCC warnings.
 * 
 * 	revision 1.10 date: 1996/01/26 18:34:45;  author: thomas
 * 	Add/change ioctl's to setting interface ioctls
 * 
 * 	revision 1.9 date: 1996/01/25 16:58:09;  author: thomas
 * 	Add support adding global addresses.  Keep track of onlink
 * 	 prefixes.  Add a per-interface structure to store information.
 * 	Do better source address selection.
 * 
 * 	revision 1.8 date: 1996/01/22 21:40:38;  author: thomas
 * 	update to discovery-04
 * 
 * 	revision 1.7 date: 1996/01/19 18:03:02;  author: thomas
 * 	Conforms to BSD API specification
 * 
 * 	revision 1.6 date: 1995/10/04 21:19:57;  author: thomas
 * 	add IN6_IS_ADDR_HOSTMASK
 * 
 * 	revision 1.5 date: 1995/09/07 15:00:43;  author: thomas
 * 	switch to all nodes
 * 
 * 	revision 1.4 date: 1995/09/06 19:49:27;  author: thomas
 * 	define/cleanup many more macros
 * 
 * 	revision 1.3 date: 1995/09/04 22:01:13;  author: thomas
 * 	renable macros
 * 
 * 	revision 1.2 date: 1995/09/02 17:07:41;  author: thomas
 * 	minor cleanup
 * 
 * 	revision 1.1 date: 1995/09/01 23:45:25;  author: thomas
 * 	Initial revision
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: in6.h,v $ $Revision: 1.1.39.3 $ (DEC) $Date: 2003/10/15 21:11:01 $
 */
#ifndef _NETINET_IN6_H_
#define	_NETINET_IN6_H_

#include <netinet/in.h>
#include <netinet/in6_machtypes.h>
#include <net/if.h>

/*
 * IPv6 level socket options
 */

#define IPV6_UNICAST_HOPS       104     /* int; unicast hoplimit (0..255) */
#define IPV6_MULTICAST_HOPS	105	/* int; multicast hoplimit (0..255) */
#define	IPV6_MULTICAST_IF	106	/* u_int; mcast interface */ 
#define	IPV6_MULTICAST_LOOP	107	/* u_int; recv own multicast (0 or 1) */
#define	IPV6_JOIN_GROUP		108	/* struct ipv6_mreq; join group */
#define	IPV6_LEAVE_GROUP	109	/* struct ipv6_mreq; leave group */
#define IPV6_PKTINFO		110	/* set in6_pktinfo */
#define IPV6_HOPLIMIT		111	/* set hop limit */
#define IPV6_HOPOPTS		112	/* set hop-by-hop options */
#define IPV6_DSTOPTS		113	/* set dest. options after rt header */
#define IPV6_RTHDR		114	/* set routing header */
#define IPV6_NEXTHOP		115	/* set next hop address */
#define IPV6_CHECKSUM		116	/* int: checksum offset */
#define IPV6_PKTOPTIONS         117	/* sticky options */
#define	IPV6_RXHDR		118	/* int; include rx info in raw recv */
#define IPV6_V6ONLY             119     /* int; AF_INET6 socket over IPv6 only*/
#define IPV6_RTHDRDSTOPTS	120	/* dest. options before routing header*/
#define IPV6_RECVPKTINFO	121	/* receive the in6_pktinfo */
#define IPV6_RECVHOPLIMIT	122	/* receive hop limit */
#define IPV6_RECVRTHDR		123	/* receive routing header */
#define IPV6_RECVHOPOPTS	124	/* receive hop-by-hop options */
#define IPV6_RECVDSTOPTS	125	/* receive dest opts after rt header */
#define IPV6_RECVRTHDRDSTOPTS	126	/* receive dest opts before rt header */
#define IPV6_RTHDR2		127	/* set rtng hdr t2 (kernel use only) */
#define IPV6_TCLASS		128	/* set traffic class */
#define IPV6_RECVTCLASS		129	/* receive traffic class */
#define IPV6_USE_MIN_MTU	130	/* path mtu discovery policy */
#define IPV6_DONTFRAG		131	/* don't fragment option */
#define IPV6_RECVPATHMTU	132	/* recieve path mtu information */
#define IPV6_PATHMTU		133	/* path mtu data */

#define IPV6_DEFAULT_UNICAST_HOPLIMIT   64 /* default unicast hop limit */
#define IPV6_DEFAULT_MULTICAST_HOPS	 1 /* normally limit mcasts to 1 hop */
#define IPV6_DEFAULT_MULTICAST_LOOP	 1 /* normally hear sends if a member */
#define IPV6_DEFAULT_MEMBERSHIPS	32 /* default per socket */
#define IPV6_MAX_MEMBERSHIPS	     65536 /* max per socket */


/*
 *   Define the IPv6 address.
 */
struct in6_addr {
    union {
	uint8_t sa6_addr[16];
#define	s6_addr		s6_un.sa6_addr
	uint16_t sa6_waddr[8];
#define	s6_waddr	s6_un.sa6_waddr
	uint32_t sa6_laddr[4];
#define	s6_laddr	s6_un.sa6_laddr
#ifdef IN6_HAS_64BIT_INTTYPE
	uint64_t sa6_qaddr[2];
#define	s6_qaddr	s6_un.sa6_qaddr
#endif
    } s6_un;
};

/*
 * Maximum length of IPv6 address as text string
 */

#define INET6_ADDRSTRLEN	46

/*
 * IPv6 protocol specific route flags
 */
#define IPV6_RTF_MINMTU     RTF_PROTO2  /* mtu less then 1280, use frag hdr */

/*
 * Structure for join/leave multicast group
 */

struct ipv6_mreq {
    struct in6_addr ipv6mr_multiaddr; /* IPv6 multicast address */
    unsigned int    ipv6mr_interface; /* interface index */
};

/*
 * IPv6 multicast scope and flags.
 */

#define	IN6_MCSCOPE_NODELOCAL	0x01
#define	IN6_MCSCOPE_LINKLOCAL	0x02
#define	IN6_MCSCOPE_ADMINLOCAL	0x04
#define	IN6_MCSCOPE_SITELOCAL	0x05
#define	IN6_MCSCOPE_ORGLOCAL	0x08
#define	IN6_MCSCOPE_GLOBAL	0x0E

#define	IN6_MCFLAG_PERMANENT	0x00
#define	IN6_MCFLAG_TRANSIENT	0x10

#ifdef IN6_HAS_64BIT_INTTYPE
#define	IN6_SET_MULTICAST_CLASS(addrp, class) \
    ((void) (*(u_int64_t *) (addrp) = IN6__MK1_MSB64_VALUE(0xFF, class)))
#else
#define	IN6_SET_MULTICAST_CLASS(addrp, class) \
    ((void) ((addrp)->s6_laddr[0] = IN6__MK1_MSB32_VALUE(0xFF, class), (addrp)->s6_laddr[1] = 0))
#endif

/*
 * Define the macros to manipulate IPv6 addresses
 */

#ifdef IN6_HAS_64BIT_INTTYPE
#define IN6_ARE_ADDR_EQUAL(a,b)		((a)->s6_qaddr[1] == (b)->s6_qaddr[1] && \
					 (a)->s6_qaddr[0] == (b)->s6_qaddr[0])
#define	IN6_ARE_ADDR_SAMEPREFIX(a,b,m)	\
				(((a)->s6_qaddr[0] & (m)->s6_qaddr[0]) == \
				 ((b)->s6_qaddr[0] & (m)->s6_qaddr[0]) && \
				 ((a)->s6_qaddr[1] & (m)->s6_qaddr[1]) == \
				 ((b)->s6_qaddr[1] & (m)->s6_qaddr[1]))
#define IN6_IS_ADDR_HOSTMASK(a)		(((a)->s6_qaddr[0] & (a)->s6_qaddr[1]) == ~0UL)
#define IN6_IS_ADDR_LOOPBACK(a)		((a)->s6_qaddr[0] == 0UL && \
					 (a)->s6_qaddr[1] == IN6__MK7_MSB64_VALUE(0,0,0,0,0,0,0,1))
#define	IN6_IS_ADDR_UNSPECIFIED(a)	(((a)->s6_qaddr[0] | (a)->s6_qaddr[1]) == 0UL)
#define	IN6_IS_ADDR_V4COMPAT(a)		((a)->s6_qaddr[0] == 0UL && \
					 (a)->s6_laddr[2] == 0 &&   \
					 (a)->s6_laddr[3] != 0 && \
					 (a)->s6_laddr[3] != IN6__MK3_MSB32_VALUE(0,0,0,1))
#define IN6_IS_ADDR_V4MAPPED(a)		((a)->s6_qaddr[0] == 0UL && \
					 (a)->s6_laddr[2] == IN6__MK1_MSW32_VALUE(0, 0xFFFFU))

#if defined(_KERNEL) || defined(KERNEL)
#define IN6_IS_ADDR_V4UNSPECIFIED(a)	((a)->s6_qaddr[0] == 0UL && \
					 (a)->s6_laddr[2] == IN6__MK1_MSW32_VALUE(0, 0xFFFFU) && \
					 (a)->s6_laddr[3] == 0UL)
#endif
			
#define	IN6_SET_ADDR_HOSTMASK(a)	((a)->s6_qaddr[1] = ((a)->s6_qaddr[0] = ~0UL))
#define	IN6_SET_ADDR_LOOPBACK(a)	((a)->s6_qaddr[0] = 0UL, \
					 (a)->s6_qaddr[1] = IN6__MK7_MSB64_VALUE(0,0,0,0,0,0,0,1))
#define	IN6_SET_ADDR_PREFIX(a,b,c)	((a)->s6_qaddr[0] = (b)->s6_qaddr[0] & (c)->s6_qaddr[0], \
					 (a)->s6_qaddr[1] = (b)->s6_qaddr[1] & (c)->s6_qaddr[1])
#define	IN6_SET_ADDR_UNSPECIFIED(a)	((a)->s6_qaddr[1] = ((a)->s6_qaddr[0] = 0UL))
#define IN6_SET_ADDR_V4MAPPED(a,b)	((a)->s6_qaddr[0] = 0, \
					 (a)->s6_laddr[2] = IN6__MK1_MSW32_VALUE(0, 0xFFFFU), \
					 (a)->s6_laddr[3] = (b))
#define IN6_SET_ADDR_V4COMPAT(a,b)	((a)->s6_qaddr[0] = 0, \
					 (a)->s6_laddr[2] = 0, \
					 (a)->s6_laddr[3] = (b))
#define IN6_SET_LINKLOCAL_NETMASK(a)	((a)->s6_qaddr[0] = IN6__MK1_MSB64_VALUE(0xFF, 0xC0), \
					 (a)->s6_qaddr[1] = 0UL)
#define IN6_SET_LINKLOCAL_PREFIX(a)	((a)->s6_qaddr[0] = IN6__MK1_MSB64_VALUE(0xFE, 0x80), \
					 (a)->s6_qaddr[1] = 0UL)
#define IN6_SET_LOWER_64_MASK(a)	((a)->s6_qaddr[0] = 0UL, \
					 (a)->s6_qaddr[1] = ~0UL)
#define IN6_JOIN_PREFIX_TOKEN(a,p,t)	((a)->s6_qaddr[0] = \
					  (p)->s6_qaddr[0] | (t)->s6_qaddr[0], \
					 (a)->s6_qaddr[1] = \
					  (p)->s6_qaddr[1] | (t)->s6_qaddr[1])
#else
#define IN6_ARE_ADDR_EQUAL(a,b)		((a)->s6_laddr[3] == (b)->s6_laddr[3] && \
					 (a)->s6_laddr[0] == (b)->s6_laddr[0] && \
					 (a)->s6_laddr[2] == (b)->s6_laddr[2] && \
					 (a)->s6_laddr[1] == (b)->s6_laddr[1])
#define	IN6_ARE_ADDR_SAMEPREFIX(a,b,m)	\
				(((a)->s6_laddr[0] & (m)->s6_laddr[0]) == \
				 ((b)->s6_laddr[0] & (m)->s6_laddr[0]) && \
				 ((a)->s6_laddr[1] & (m)->s6_laddr[1]) == \
				 ((b)->s6_laddr[1] & (m)->s6_laddr[1]) && \
				 ((a)->s6_laddr[2] & (m)->s6_laddr[2]) == \
				 ((b)->s6_laddr[2] & (m)->s6_laddr[2]) && \
				 ((a)->s6_laddr[3] & (m)->s6_laddr[3]) == \
				 ((b)->s6_laddr[3] & (m)->s6_laddr[3]))
#define IN6_IS_ADDR_HOSTMASK(a)		((a)->s6_laddr[3] == ~0UL && \
					 (a)->s6_laddr[0] == ~0UL && \
					 (a)->s6_laddr[2] == ~0UL && \
					 (a)->s6_laddr[1] == ~0UL)
#define	IN6_IS_ADDR_LOOPBACK(a)		((a)->s6_laddr[0] == 0UL && \
					 (a)->s6_laddr[1] == 0UL && \
					 (a)->s6_laddr[2] == 0UL && \
					 (a)->s6_laddr[3] == IN6__MK3_MSB32_VALUE(0,0,0,1))
#define IN6_IS_ADDR_UNSPECIFIED(a)	((a)->s6_laddr[3] == 0UL && \
					 (a)->s6_laddr[0] == 0UL && \
					 (a)->s6_laddr[2] == 0UL && \
					 (a)->s6_laddr[1] == 0UL)
#define IN6_IS_ADDR_V4COMPAT(a)		((a)->s6_laddr[0] == 0UL && \
					 (a)->s6_laddr[1] == 0UL && \
					 (a)->s6_laddr[2] == 0UL && \
					 (a)->s6_laddr[3] != 0 && \
					 (a)->s6_laddr[3] != IN6__MK3_MSB32_VALUE(0,0,0,1))
#define IN6_IS_ADDR_V4MAPPED(a)		((a)->s6_laddr[0] == 0UL && \
					 (a)->s6_laddr[1] == 0UL && \
					 (a)->s6_laddr[2] == IN6__MK1_MSW32_VALUE(0, 0xFFFFU))

#if defined(_KERNEL) || defined(KERNEL)
#define IN6_IS_ADDR_V4UNSPECIFIED(a)	((a)->s6_laddr[0] == 0UL && \
					 (a)->s6_laddr[1] == 0UL && \
					 (a)->s6_laddr[2] == IN6__MK1_MSW32_VALUE(0, 0xFFFFU) && \
					 (a)->s6_laddr[3] == 0UL)
#endif

#define	IN6_SET_ADDR_HOSTMASK(a)	((a)->s6_laddr[3] = ((a)->s6_laddr[2] = ((a)->s6_laddr[1] = ((a)->s6_laddr[0] = ~0UL))))
#define	IN6_SET_ADDR_LOOPBACK(a)	((a)->s6_laddr[0] = ((a)->s6_laddr[1] = ((a)->s6_laddr[2] = 0UL)), \
					 (a)->s6_laddr[3] = IN6__MK3_MSB32_VALUE(0,0,0,1))
#define	IN6_SET_ADDR_PREFIX(a,b,c)	((a)->s6_laddr[0] = (b)->s6_laddr[0] & (c)->s6_laddr[0], \
					 (a)->s6_laddr[1] = (b)->s6_laddr[1] & (c)->s6_laddr[1], \
					 (a)->s6_laddr[2] = (b)->s6_laddr[2] & (c)->s6_laddr[2], \
					 (a)->s6_laddr[3] = (b)->s6_laddr[3] & (c)->s6_laddr[3])
#define	IN6_SET_ADDR_UNSPECIFIED(a)	((a)->s6_laddr[3] = ((a)->s6_laddr[2] = ((a)->s6_laddr[1] = ((a)->s6_laddr[0] = 0UL))))
#define IN6_SET_ADDR_V4MAPPED(a,b)	((a)->s6_laddr[0] = 0, (a)->s6_laddr[1] = 0, \
					 (a)->s6_laddr[2] = IN6__MK1_MSW32_VALUE(0, 0xFFFFU), \
					 (a)->s6_laddr[3] = (b))
#define IN6_SET_ADDR_V4COMPAT(a,b)	((a)->s6_laddr[0] = 0, (a)->s6_laddr[1] = 0, \
					 (a)->s6_laddr[2] = 0, \
					 (a)->s6_laddr[3] = (b))
#define IN6_SET_LINKLOCAL_NETMASK(a)	((a)->s6_laddr[0] = IN6__MK1_MSB32_VALUE(0xFF, 0xC0), \
					 (a)->s6_laddr[1] = 0, \
					 (a)->s6_laddr[2] = 0, \
					 (a)->s6_laddr[3] = 0)
#define IN6_SET_LINKLOCAL_PREFIX(a)	((a)->s6_laddr[0] = IN6__MK1_MSB32_VALUE(0xFE, 0x80), \
					 (a)->s6_laddr[1] = 0, \
					 (a)->s6_laddr[2] = 0, \
					 (a)->s6_laddr[3] = 0)
#define IN6_SET_LOWER_64_MASK(a)	((a)->s6_laddr[0] = 0, \
					 (a)->s6_laddr[1] = 0, \
					 (a)->s6_laddr[2] = IN6__MK1_MSB32_VALUE(0xFF, 0xFF), \
					 (a)->s6_laddr[3] = IN6__MK1_MSB32_VALUE(0xFF, 0xFF))
#define IN6_JOIN_PREFIX_TOKEN(a,p,t)	((a)->s6_laddr[0] = \
					  (p)->s6_laddr[0] | (t)->s6_laddr[0], \
					 (a)->s6_laddr[1] = \
					  (p)->s6_laddr[1] | (t)->s6_laddr[1], \
					 (a)->s6_laddr[2] = \
					  (p)->s6_laddr[2] | (t)->s6_laddr[2], \
					 (a)->s6_laddr[3] = \
					  (p)->s6_laddr[3] | (t)->s6_laddr[3])
#endif

#define	IN6_EXTRACT_V4ADDR(a)		((a)->s6_laddr[3])
#define	IN6_EXTRACT_V4ADDR_624(a)	(IN6__MK1_MSW32_VALUE((a)->s6_waddr[1],\
							      (a)->s6_waddr[2]))
#define IN6_IS_ADDR_LINKLOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0xC0)) == IN6__MK1_MSB32_VALUE(0xFE, 0x80))
#define IN6_IS_ADDR_SITELOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0xC0)) == IN6__MK1_MSB32_VALUE(0xFE, 0xC0))
#define IN6_IS_ADDR_MULTICAST(a)	(((a)->s6_laddr[0] & IN6__MK0_MSB32_VALUE(0xFF)) == IN6__MK0_MSB32_VALUE(0xFF))
#define IN6_IS_ADDR_MC_NODELOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_NODELOCAL))
#define IN6_IS_ADDR_MC_LINKLOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_LINKLOCAL))
#define IN6_IS_ADDR_MC_SITELOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_SITELOCAL))
#define IN6_IS_ADDR_MC_ADMINLOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_ADMINLOCAL))
#define IN6_IS_ADDR_MC_ORGLOCAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_ORGLOCAL))
#define IN6_IS_ADDR_MC_GLOBAL(a)	(((a)->s6_laddr[0] & IN6__MK1_MSB32_VALUE(0xFF, 0x0F)) == IN6__MK1_MSB32_VALUE(0xFF, IN6_MCSCOPE_GLOBAL))

#if defined(_KERNEL) || defined(KERNEL)
/* 
 * Check if address is unspecified.  Unspecified addresses are:
 *      ::              = in6addr_any or
 *      ::ffff:0.0.0.0  = inaddr_any  mapped to IPv6 (for v4 connections)
 * If the address is in ether one of these formats, return TRUE
 */
#define IS_ADDR_UNSPECIFIED(a)    ( IN6_IS_ADDR_V4UNSPECIFIED(a) || \
                                       IN6_IS_ADDR_UNSPECIFIED(a) )

/*
 * Set address (a) to be of link-local scope based on address (b) joined
 * with mask (m) of a given token length.  Used in Mobile IPv6 code.
 */
#define IN6_SET_ADDR_LINKLOCAL(a, b, m) {			\
	struct in6_addr _in6_ll_prefix;				\
	IN6_SET_ADDR_PREFIX((a), (m), (b));			\
	IN6_SET_LINKLOCAL_PREFIX(&_in6_ll_prefix);		\
	IN6_JOIN_PREFIX_TOKEN((a), &_in6_ll_prefix, (a));	\
}
#endif


#define	IPV6ADDR_LINKLOCAL_ALL_NODES_INIT { \
	0xFF, IN6_MCSCOPE_LINKLOCAL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }

#define	IPV6ADDR_LINKLOCAL_ALL_ROUTERS_INIT { \
	0xFF, IN6_MCSCOPE_LINKLOCAL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }

#if !defined(_KERNEL) && !defined(KERNEL)
extern const struct in6_addr in6addr_any;
#endif

#define	IN6ADDR_ANY_INIT { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

#define	IN6ADDR_TLA624_INIT { 0x20, 0x02, /* IANA defined TLA */ \
			      0, 0, 0, 0, /* NLA == V4ADDR */ \
			      0, 0,       /* SLA ID */ \
			      0, 0, 0, 0, 0, 0, 0, 0 /* interface id */ }

#define IN6ADDR_TLA624_PFXMASK {0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, \
				0, 0, 0, 0, 0, 0 }

#if !defined(_KERNEL) && !defined(KERNEL)
extern const struct in6_addr in6addr_loopback;
#endif

#define	IN6ADDR_LOOPBACK_INIT { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }

#define IN6ADDR_HOMEAGENT_ANYCAST_INIT { 0, 0, 0, 0, 0, 0, 0, 0, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE }


/*
 * Define the socket address for IPv6
 */
struct sockaddr_in6 {
#if defined(_SOCKADDR_LEN) || defined(_KERNEL) || \
			defined(_XOPEN_SOURCE_EXTENDED)
#define SIN6_LEN
    uint8_t	    sin6_len;		/* length of this struct */
    sa_family_t	    sin6_family;	/* AF_INET6 */
#else
    u_short	    sin6_family;	/* AF_INET6 */
#endif
    in_port_t	    sin6_port;		/* Transport layer port # */
    uint32_t	    sin6_flowinfo;	/* IPv6 flow information */
    struct in6_addr sin6_addr;		/* IPv6 address */
    uint32_t        sin6_scope_id;      /* set of interfaces for a scope */
};

/*
 * ioctl handles up to 128 bytes on stack.  The max amount of generic data
 * this structure can hold is carefully chosen so the entire ip6ifreq does 
 * not exceed 128 bytes, thus avoiding a kalloc().  The max size of a link-
 * layer address is smaller to account for a 16 byte IPv6 address, the
 * lladdrlen and the radv_flags.
 */

#define IFR6_MAX_DATA	88	/* max generic data in ip6ifreq */
#define IFR6_MAX_LLADDR	63	/* max link-layer address in un_lladdr */

/*
 * Define the structure used for interface ioctls with IPv6 addresses
 *
 * Caution: some code expects the first portion of the ip6ifreq to
 * be identical to an ifreq (i.e. the union containing the sockaddr
 * structures et al. must immediately follow ifr6_name)
 */

struct ip6ifreq {
    char ifr6_name[IFNAMSIZ];			/* i/f name, e.g. "ln0" */
    union {
        struct sockaddr		un_addr;	/* address */
        struct sockaddr_in	un_addr4;	/* address */
        struct sockaddr_in6	un_addr6;	/* address */
	struct {
	    size_t		un_datalen;		/* generic data len */
	    char		un_data[IFR6_MAX_DATA];	/* generic data */
	} un_1;
	struct {
	    uint                un_value;	/* generic value... */
	    int			un_code;	/* generic ... */
	} un_2;
	struct {
	    struct in6_addr	un_dst;			    /* IPv6 address */
	    size_t		un_lladdrlen;		    /* link addr len */
	    char		un_lladdr[IFR6_MAX_LLADDR]; /* link addr */
	    uint8_t		un_radv_flags;              /* radv flags */
	} un_3;
	struct {
       	    struct in6_addr	un_liid;	/* local intf id   */
       	    struct in6_addr	un_riid;	/* remote intf id for ppp6 */
	} un_4;
	struct {
       	    struct in6_addr	un_prefix;	/* prefix */
	    uint8_t		un_prefixlen;	/* prefix length */
	    uint8_t		un_pad_5_1;	/* padding */
	    uint16_t		un_prefixflags;	/* flags (see ip6_mobile.h) */
	    uint16_t		un_pad_5_2;	/* padding */
	    uint32_t		un_validlife;	/* valid prefix lifetime */
	    uint32_t		un_preferredlife;/* preferred prefix lifetime */
	} un_5;
    } ifr6_un;
#define ifr6_addr	ifr6_un.un_addr
#define ifr6_addr4	ifr6_un.un_addr4
#define ifr6_addr6	ifr6_un.un_addr6
#define ifr6_datalen	ifr6_un.un_1.un_datalen
#define ifr6_data	ifr6_un.un_1.un_data
#define ifr6_value	ifr6_un.un_2.un_value
#define ifr6_code	ifr6_un.un_2.un_code
#define ifr6_dst	ifr6_un.un_3.un_dst
#define ifr6_radv_flags	ifr6_un.un_3.un_radv_flags
#define ifr6_lladdrlen	ifr6_un.un_3.un_lladdrlen
#define ifr6_lladdr	ifr6_un.un_3.un_lladdr
#define ifr6_lid	ifr6_un.un_4.un_liid
#define ifr6_rid	ifr6_un.un_4.un_riid
#define ifr6_prefix	ifr6_un.un_5.un_prefix
#define ifr6_prefixlen	ifr6_un.un_5.un_prefixlen
#define ifr6_prefixflags ifr6_un.un_5.un_prefixflags
#define ifr6_validlife	ifr6_un.un_5.un_validlife
#define ifr6_preferredlife	ifr6_un.un_5.un_preferredlife

    u_int ifr6_flags;				/* flags: */
#define	IFR6_NODAD		0x0001U		/* no dup address detection */
#define	IFR6_ADDTOKEN		0x0002U		/* add token to end of prefix */
#define	IFR6_DADFAILED		0x0004U
#define	IFR6_DADINPROGRESS	0x0008U
#define	IFR6_DEPRECATED		0x0010U
#define IFR6_ANYCAST		0x0020U		/* address is anycast */
#define IFR6_PROXY		0x0040U		/* proxying for address */
#define IFR6_MOBILE		0x0080U		/* mobile node home address */
    u_int ifr6_reserved[3];			/* for future use */
};

/*
 * Define the structure that is added as a control message to
 * incoming raw packets before being handed to the user.
 */
struct rip6_header {
    int   rhdr_ifindex;          /* ifnet index number */
    int   rhdr_pktflags;         /* The mbuf flags (M_MCAST etc) */
    u_short rhdr_offset;         /* data offset in IPv6 packet */
    u_char  rhdr_proto;          /* The protocol type */
    u_char  rhdr_authOK;         /* TRUE if the pkt was authenticated */
};

/*
 * advance API defines (rfc2292)
 */
struct in6_pktinfo {
    struct in6_addr	ipi6_addr;	/* IPv6 address */
    unsigned int	ipi6_ifindex;	/* interface index */
};


struct ip6_mtuinfo {
    struct sockaddr_in6	ip6m_addr;	/* IPv6 destination address */
    uint32_t		ip6m_mtu;	/* path mtu */
};

/*
 * Define constants for the routing header
 */
#define IPV6_RTHDR_LOOSE     0 /* this hop need not be a neighbor */
#define IPV6_RTHDR_STRICT    1 /* this hop must be a neighbor */
#define IPV6_RTHDR_TYPE_0    0 /* IPv6 Routing header type 0 */
#define IPV6_RTHDR_TYPE_2    2 /* IPv6 Routing header type 2 */


#ifndef _KERNEL

/*
 * RFC 3542 function prototypes
 */

_BEGIN_CPLUSPLUS

#if (defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)) || \
    defined(_POSIX_PII_SOCKET) || defined(__VMS)

extern int	inet6_opt_init __((void *, socklen_t));

#ifndef __VMS
extern int	inet6_opt_append __((void *, socklen_t, int,
				     uint8_t, socklen_t, uint_t,
				     void **));
#else  /* __VMS */
/* 2001-10-09 Lee Tibbert
 * Temporary (?) hack to work around compile problems in IPC.
 * IPC is currently built cc/standard=VAXC, so the __() macro
 * below expands to no args empty list (). The uint8_t is not four bytes
 * so the compiler complains (do not ask me).  Basicaly, we are mixing
 * old and new style declarations (not good practice), and gettting hosed.
 * We got away with it before because we did not have uint8_t arguments.
 *
 * Proper fix is to compile IPC /Standard=Relaxed_ANSI but that takes more
 * time than I have now.  When that is done, this hack is no longer needed for
 * the next port. 
 */
extern int	inet6_opt_append (void *, socklen_t, int,
				  uint8_t, socklen_t, uint_t,
				  void **);
#endif /* __VMS */

extern int	inet6_opt_finish __((void *, socklen_t, int));
extern int	inet6_opt_set_val __((void *, int, void *, socklen_t));
extern int	inet6_opt_next __((void *, socklen_t, int,
				   uint8_t *, socklen_t *,
				   void **));
#ifndef __VMS
extern int	inet6_opt_find __((void *, socklen_t, int,
				   uint8_t, socklen_t *,
				   void **));
#else  /* __VMS */
extern int	inet6_opt_find (void *, socklen_t, int,
			        uint8_t, socklen_t *,
				void **);
#endif /* __VMS */

extern int	inet6_opt_get_val __((void *, int, void *, socklen_t));

extern socklen_t	inet6_rth_space __((int, int));
extern void *	inet6_rth_init __((void *, socklen_t, int, int));
extern int	inet6_rth_add __((void *, const struct in6_addr *));
extern int	inet6_rth_reverse __((const void *, void *));
extern int	inet6_rth_segments __((const void *));
extern struct in6_addr *	inet6_rth_getaddr __((void *, int));

#else /* _XOPEN_SOURCE ... */

extern int	inet6_opt_init __((void*, size_t));

extern int	inet6_opt_append __((void *, size_t, int,
				     uint8_t, size_t, uint_t,
				     void **));
extern int	inet6_opt_finish __((void *, size_t, int));
extern int	inet6_opt_set_val __((void *, int, void *, size_t));
extern int	inet6_opt_next __((void *, size_t, int,
				   uint8_t *, size_t *,
				   void **));
extern int	inet6_opt_find __((void *, size_t, int,
				   uint8_t, size_t *,
				   void **));
extern int	inet6_opt_get_val __((void *, int, void *, size_t));

extern size_t	inet6_rth_space __((int, int));
extern void *	inet6_rth_init __((void *, int, int, int));
extern int	inet6_rth_add __((void *, const struct in6_addr *));
extern int	inet6_rth_reverse __((const void *, void *));
extern int	inet6_rth_segments __((const void *));
extern struct in6_addr *	inet6_rth_getaddr __((void *, int));

#endif   /* _XOPEN_SOURCE && _POSIX_PII_SOCKET etc... */

_END_CPLUSPLUS

#endif /* _KERNEL */

#endif /* _NETINET_IN6_H_ */
