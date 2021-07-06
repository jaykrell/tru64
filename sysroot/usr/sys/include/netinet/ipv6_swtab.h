/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ipv6_swtab.h,v $
 * Revision 1.1.23.2  2003/11/13  22:42:54  Brian_Haley
 * 	Changed mip6_if6_pick() to take and in6_ifnet instead of an ifnet.
 * 	Changed mip6_cache_free() to take an additional arg.
 *
 * Revision 1.1.23.1  2003/09/23  22:00:39  Brian_Haley
 * 	Mobile IPv6 update.
 * 	Changed in6_rthdrswap() prototype to have 5th 'type' argument.
 * 	Added mip6_if6_pick() to ipv6_swtab.
 *
 * Revision 1.1.15.3  2002/01/29  21:19:20  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 1.1.15.2  2002/01/10  19:21:13  Vladislav_Yasevich
 * 	Fixed definitions of 'P' for prototypes. QAR 82344
 *
 * Revision 1.1.15.1  2001/12/17  20:55:43  Vladislav_Yasevich
 * 	Mapped API submit:
 * 	- Enabled hanlding of mapped address with Advanced API.
 * 	- Correctly handling mapped address with multicast options.
 * 	[2001/10/19  19:19:42  Vladislav_Yasevich]
 *
 * 	Mobile IPv6 submit:
 * 	- added mip6_cache_rt_delete() and mip6_cache_free() to ipv6_swtab
 * 	[2001/10/10  15:35:58  Brian_Haley]
 *
 * 	Changes from wildcatos-1165-harter and QAR 86524:
 * 	- Add ip6_init_rad() to ipv6_swtab.
 * 	- Move extern declaration of ipv6forwarding & ipv6router
 *   from in6_var.h
 * 	[2001/10/03  14:51:58  Geraldine_Harter]
 *
 * 	Merge of the Advanced API implementations from wildcat.classic
 * 	[2001/10/02  15:44:53  Vladislav_Yasevich]
 *
 * Revision 1.1.6.1  2000/11/09  17:48:46  Vladislav_Yasevich
 * 	Enabled the advanced api processing routine to accept option
 * 	type to support the new advanced api options.
 *
 * Revision 1.1.4.5  2000/03/02  23:46:17  Brian_Haley
 * 	NUMA cleanup:
 * 	- made ipv6isconfigured "REPLICATED" data
 *
 * Revision 1.1.4.4  2000/01/20  17:42:54  Sowmini_Varadhan
 * 	- renamed nd6_cache_unrefNL to nd6_cache_free
 * 	- removed nd6_llinfo_free
 *
 * Revision 1.1.4.3  2000/01/12  16:52:16  Sowmini_Varadhan
 * 	- remove nd6_update_default_route, in6_prefix_add, in6_prefix_remove
 * 	- add  nd6_rtconfirm, nd6_cache_lookup, nd6_llinfo_free, nd6_cache_unrefNL
 *
 * Revision 1.1.4.2  1999/11/05  16:31:10  Sowmini_Varadhan
 * 	Removed indirection for nd6_cache_resolve from ether.mod;
 * 	nd6_lloutput is the link-layer output convergence point for IPV6,
 * 	and performs any necessary nd6_cache_resolve calls.
 *
 * Revision 1.1.4.1  1999/10/18  20:21:48  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 1.1.2.4  1999/08/13  18:42:17  Sowmini_Varadhan
 * 	ipv6_swtab cleanup
 * 	- inlined ip6advapi, ip6sockopt etc. into ipv6_swtab
 * 	- name of field in ipv6_swtab matches function name in ipv6_swtab_real
 * 	[1999/08/13  17:59:50  Sowmini_Varadhan]
 *
 * Revision 1.1.2.3  1999/08/12  21:32:17  Jack_McCann
 * 	Update ipv6_laddr_pick prototype for new 'int flags' parameter
 * 	[1999/08/12  21:00:11  Jack_McCann]
 * 
 * Revision 1.1.2.2  1999/07/22  19:01:30  Sowmini_Varadhan
 * 	Initial revision
 * 	[1999/07/07  18:51:37  Sowmini_Varadhan]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ipv6_swtab.h,v $ $Revision: 1.1.23.2 $ (DEC) $Date: 2003/11/13 22:42:54 $
 */

#ifndef _IPV6_SWTAB_H
#define _IPV6_SWTAB_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL

#include <netinet/proto_ipv6.h>
#include <net/proto_net.h>

#ifndef P
#define P(s) s
#define __P_IN_IPV6_SWTAB	/* P was defined here */
#endif



struct _ipv6_swtab {
	/* IPV6 ADVAPI function pointers */
        int (*in6_setpktoptions) P((struct inpcb *, struct mbuf *, u_char **,
				    int));
        struct mbuf *(*in6_opt_passup_options) P((struct ip6_rxinfo *, int));
        void (*in6_rthdrswap) P((struct in6_addr *, char *, int, int, int));
        void (*in6_copyip6hdrext) P((struct ip6_hdr *ip6, uchar *, 
						struct in6optinfo *));
        void (*in6_opt_free) P(( struct in6optinfo *));
        int  (*udp_add_v6opt) P((struct ip6_txinfo *, struct mbuf *,
				struct mbuf *, struct udphdr *));

	/* IPV6 socket options allowed  on IP sockets */
    	int (*ip6_setmoptions)P((int, struct ip6_moptions **, struct mbuf *,
				 struct inpcb *));
    	int (*ip6_getmoptions)P((int, struct ip6_moptions *, struct mbuf **));
    	void (*ip6_freemoptions)P((struct ip6_moptions *));

	/* IPV6 interface information */
    	int (*in6_control) P((struct socket *, unsigned int, caddr_t,
                       struct ifnet *));
    	void (*in6_ifnet_free) P((struct in6_ifnet *));

	/* IPV6 Neighbor discovery */
    	void (*nd6_rtconfirm) P((struct rtentry *));
	struct nd6_llinfo * (*nd6_cache_lookup) P((struct in6_ifnet *,
                                        const struct sockaddr_in6 *,
#ifndef __VMS
                                        enum nd6_cache_state));
#else
                                        int));
#endif /* __VMS */
	void (*nd6_cache_free) P((nd6_cache_t *));
	

	/* IPV6 localaddrs information */
    	int    (*in6_localaddr) P((const struct in6_addr *, 
				const struct rtentry *));
    	struct in6_localaddr *(*in6_localaddr_lookup) P((const struct in6_addr *,
                        		struct in6_ifnet *));
    	struct in6_localaddr *(*in6_localaddr_pick) P((const struct in6_addr *,
                        		struct in6_ifnet *, int));
    	void   (*in6_localaddr_free) P((struct in6_localaddr *));
    	void   (*in6_ifaddr_free) P((struct in6_ifaddr *));

	/* General error reporting functions */
    	void   (*icmp6_send_error) P((struct mbuf *, const struct ip6_hdr *,
				 unsigned, unsigned, unsigned));

	/* IPV6 RAD initialization */
	void    (*ip6_init_rad) P((struct rad *));

	/* Mobile IPv6 functions */
	void   (*mip6_cache_rt_delete) P((struct rtentry *));
	void   (*mip6_cache_free) P((struct mip6_binding_cache *, int));
	struct in6_ifnet *(*mip6_if6_pick) P((struct in6_addr *,
				struct in6_ifnet *,
				int,
				struct rtentry **));
};

extern struct _ipv6_swtab *ipv6_swtab;


extern REPLICATED int ipv6isconfigured;
extern u_int ipv6_minimum_link_mtu;
extern u_int ipv6_default_unicast_hoplimit;
extern int ipv6forwarding;
extern int ipv6router;			    /* act as IPv6 router */

#ifdef __P_IN_IPV6_SWTAB
#undef P
#undef __P_IN_IPV6_SWTAB	/* clean up */
#endif

#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* _IPV6_SWTAB_H */
