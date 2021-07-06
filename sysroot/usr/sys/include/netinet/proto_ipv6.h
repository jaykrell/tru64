/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: proto_ipv6.h,v $
 * Revision 1.1.25.3  2003/11/13  22:42:58  Brian_Haley
 * 	Changed mip6_if6_pick() to take and in6_ifnet instead of an ifnet.
 * 	Changed mip6_cache_free() to take an additional arg.
 *
 * Revision 1.1.25.2  2003/10/15  21:21:13  Vladislav_Yasevich
 * Merge Information:  Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Vladislav_Yasevich_v51b_br:1.1.26.1 Local Ancestor:1.1.17.3
 *    Merge Revision:  v51bsupportos_br:1.1.25.1
 *   Common Ancestor:  1.1.17.3
 * 	[2003/10/15  21:21:05  Vladislav_Yasevich]
 *
 * 	IPv6 advanced API update (rfc 3542)
 * 	- add an extra argument to in6_opt_ctloopts.  This argument
 * 	specifies whether we should merge ancillary data with sticky
 * 	options or not.  The merge happens on the option-by-option
 * 	basis for options that are in one data set and not the other.
 * 	[2003/10/06  19:36:16  Vladislav_Yasevich]
 *
 * Revision 1.1.25.1  2003/09/23  22:00:57  Brian_Haley
 * 	Mobile IPv6 update
 * 	- added mip6_nonces_expired() prototype
 * 	- changed mip6_have_binding() prototype
 * 	- MIPv6 Draft 20 Return Routability updates
 * 	Changed in6_rthdrswap() prototype to have 5th 'type' argument.  Added
 * 	other new mobility prototypes.  Changed mip6_add_header() prototype to
 * 	not have ifp argument.
 * 
 * Revision 1.1.17.3  2002/01/29  21:19:23  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 * 
 * Revision 1.1.17.2  2002/01/10  19:21:17  Vladislav_Yasevich
 * 	Fixed definitions of 'P' for prototypes. QAR 82344
 * 
 * Revision 1.1.17.1  2001/12/17  20:55:53  Vladislav_Yasevich
 * 	Mapped API submit:
 * 	- Enabled hanlding of mapped address with Advanced API.
 * 	- Correctly handling mapped address with multicast options.
 * 	[2001/10/19  19:19:45  Vladislav_Yasevich]
 * 	Mobile IPv6 submit:
 * 	- added set_rthdr() and in6_opt_clear() prototypes
 * 	- added many ip6_mobile.c prototypes
 * 	[2001/10/10  15:36:00  Brian_Haley]
 * 	Changes from wildcatos-1165-harter:
 * 	- Add ip6_init_rad() to ipv6_swtab.
 * 	[2001/10/03  14:52:04  Geraldine_Harter]
 * 	Merge of the Advanced API implementations from wildcat.classic
 * 	[2001/10/02  15:44:58  Vladislav_Yasevich]
 * 
 * Revision 1.1.8.1  2000/11/09  17:48:48  Vladislav_Yasevich
 * 	Enabled in6_setsockopts to take an additinal option name
 * 	to support new advanced api options.
 * 
 * Revision 1.1.6.1  2000/09/25  22:42:18  Brian_Haley
 * 	Added rhandle argument to nd6_lloutput() prototype.
 * 
 * Revision 1.1.4.7  2000/04/18  15:57:50  Sowmini_Varadhan
 * 	removed duplicate prototype for nd6_rtconfirm
 * 
 * Revision 1.1.4.6  2000/01/27  19:46:38  Sowmini_Varadhan
 * 	- pass rad_id to nd6_cache_slowtimo.
 * 	- added icmp6_slowtimo_rad, icmp6_fasttimo_rad
 * 
 * Revision 1.1.4.5  2000/01/20  17:42:56  Sowmini_Varadhan
 * 	- renamed nd6_cache_unrefNL to nd6_cache_free
 * 	- removed nd6_llinfo_free
 * 
 * Revision 1.1.4.4  2000/01/12  16:52:21  Sowmini_Varadhan
 * 	- removed nd6_update_default_route, nd6_cache_rtrequest
 * 	in6_prefix* functions
 * 	- added nd6_rtconfirm, nd6_cache_lookup, nd6_llinfo_free
 * 	- changed prototype of nd6_cache_init
 * 
 * Revision 1.1.4.3  1999/12/16  20:48:21  Sowmini_Varadhan
 * 	pass in6_ifnet to nd6_lloutput
 * 
 * Revision 1.1.4.2  1999/11/05  16:31:14  Sowmini_Varadhan
 * 	- added nd6_lloutput
 * 	- made nd6_cache_resolve static to nd6_cache.c
 * 
 * Revision 1.1.4.1  1999/10/18  20:21:58  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 * 
 * Revision 1.1.2.6  1999/09/13  21:28:29  Jack_McCann
 * Merge Information
 *     Merge Revision:  IPV6OS:1.1.2.5
 *     User  Revision:  Jack_McCann_6bugs_br:1.1.3.1
 *    Common Ancestor:  1.1.2.4
 * 	update nd6_process_options() prototype
 * 
 * Revision 1.1.2.5  1999/09/10  16:26:02  Geraldine_Harter
 * 	Remove nd6_input().  Add nd6_process_router_advertisement().
 * 
 * Revision 1.1.2.4  1999/08/13  18:42:21  Sowmini_Varadhan
 * 	moved if_iptunnel.c to iptunnel.mod
 * 	[1999/08/13  17:59:53  Sowmini_Varadhan]
 * 
 * Revision 1.1.2.3  1999/08/12  21:32:18  Jack_McCann
 * 	Update in6_localaddr_pick() prototype for new 'int flags' parameter
 * 	[1999/08/12  21:00:16  Jack_McCann]
 * 
 * Revision 1.1.2.2  1999/07/22  19:01:37  Sowmini_Varadhan
 * 	Initial Revision.
 * 	[1999/07/22  14:24:13  Sowmini_Varadhan]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: proto_ipv6.h,v $ $Revision: 1.1.25.3 $ (DEC) $Date: 2003/11/13 22:42:58 $
 */
#ifndef _PROTO_IPV6_H
#define  _PROTO_IPV6_H

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in6_machtypes.h>
#include <sys/sysconfig.h>
#include <netinet/nd6_cache.h>
#include <netinet/ip6_mobile.h>
#include <netinet/mip6_rrsec.h>

#ifndef P
#define P(s) s
#define __P_IN_PROTO_IPV6	 /* P was defined here */
#endif

typedef union {
        struct ip6_hdr      *p1;
        struct in6_ifaddr   *p2;
        struct in6_ifnet    *p3;
	struct ip6ifreq     *p4;
	struct icmp6_hdr    *p5;    
	struct in6_addr     *p6;    
	struct ip6_rxinfo   *p7;    
	struct ip6_txinfo   *p8;    
	struct ip6_moptions *p9;    
	struct sockaddr_in6 *p10;    
	struct inpcb        *p11;    
	struct ip_moptions  *p12;    
	struct iptunnelreq  *p13;    
	struct iptunnelres  *p14;    
	struct protosw      *p15;    
	struct udphdr       *p16;
	nd6_cache_t         *p17;
	struct tcntl_genflow *p18;
	mip6_cache_t        *p19;
	struct ip6mh_binding_update *p20;
	struct ip6mh_opt_nonce_index *p21;
	struct ip6_tx_errlog	*p22;
} proto_ipv6_union_t;

/* in6.c */
int     in6_control P((struct socket *, unsigned int, caddr_t,
                       struct ifnet *));
int	in6_localaddr P((const struct in6_addr *, const struct rtentry *));
int	in6_ifnet_create P((struct ifnet *, struct ip6ifreq *));
void 	in6_ifnet_free P((struct in6_ifnet *));
struct in6_localaddr *in6_localaddr_pick P((const struct in6_addr *, 
			struct in6_ifnet *, int));
struct in6_localaddr *in6_localaddr_add P((const struct in6_addr *, 
			struct in6_ifnet *, struct in6_localaddr *, 
			struct in6_ifaddr *, unsigned, int *));
void	in6_localaddr_remove P((struct in6_localaddr *));
struct in6_localaddr *in6_localaddr_lookup P((const struct in6_addr *, 
			struct in6_ifnet *));
void 	in6_localaddr_free P((struct in6_localaddr *));
void	in6_localaddr_failure P((struct in6_localaddr *));
void	in6_ifaddr_free P((struct in6_ifaddr *));

/* ip6_input.c */
void    ip6_init P((struct protosw *, struct protosw *));
void    ip6_init_rad P((struct rad *));
void	ip6_slowtimo P((void));
void	ip6_dispatch P((struct ip6_rxinfo *rx));

/* ip6_output.c */
int     ip6_output P((struct ip6_txinfo *));
int	ip6_setmoptions P((int, struct ip6_moptions **, struct mbuf *,
			   struct inpcb *));
int	ip6_getmoptions P((int, struct ip6_moptions *, struct mbuf **));
void	ip6_freemoptions P((struct ip6_moptions *));
int	ip6_mforward P((struct ip6_rxinfo *, int));

/* ip6_forward.c */
void    ip6_forward_init P((void));
void    ip6_forward P((struct ip6_rxinfo *));

/* ip6_frag.c */
int	ip6_frag P((struct mbuf **, u_int));

/* ip6_reass.c */
void    ip6_reass_init P((void));
void	ip6_reass_slowtimo P((void));
#ifdef __VMS
# pragma message save
# pragma message disable UNDEFENUM
#endif  /* __VMS */
enum in6_disposition ip6_process_fragment P((struct ip6_rxinfo * const,
					     unsigned *nxthdr_p));
#ifdef __VMS 
# pragma message restore
#endif	/* __VMS */

/* ip6_rlimit.c */
void ip6_tx_errlog_garbage_collect P((struct ip6_tx_errlog *));
int ip6_rlimit_message P((const struct in6_addr *, struct ip6_tx_errlog *));

/* ip6_icmp.c */
void    icmp6_init P((void));
void    icmp6_input P((struct ip6_rxinfo *, unsigned));
void	icmp6_fasttimo P((void));
void	icmp6_fasttimo_rad P((void *));
void	icmp6_slowtimo P((void));
void	icmp6_slowtimo_rad P((void *));
void	icmp6_mgm_send_message P((struct in6_localaddr *, unsigned));
void	icmp6_send_error P((struct mbuf *, const struct ip6_hdr *,
			    unsigned, unsigned, unsigned));
void 	icmp6_timo_init P((void));

/* nd6_cache.c */
int	nd6_cache_init P((struct in6_ifnet *));
void 	nd6_cache_uninit P((struct in6_ifnet *));
void	nd6_cache_settimer P((struct in6_ifnet *, int));
void	nd6_cache_slowtimo P((int));
nd6_cache_t *nd6_cache_update P((struct in6_ifnet *,
					const struct in6_addr *, unsigned,
					u_int32_t, const char *, size_t));
int	nd6_lloutput P((struct in6_ifnet *, struct mbuf *, struct sockaddr *,
			struct in_route *, int, struct tcntl_genflow *));
struct  nd6_llinfo *nd6_cache_lookup P((struct in6_ifnet *,
					const struct sockaddr_in6 *,
#ifndef __VMS
					enum nd6_cache_state));
#else /* __VMS */
                                        int));
#endif /* __VMS */
int     nd6_cache_head_init P((caddr_t , caddr_t ));
void    nd6_rtconfirm P((nd6_cache_t *));
int     nd6_delete_if6_nd6_cache P((struct in6_ifnet *));
void    nd6_cache_free P((nd6_cache_t *));


/* nd6_discovery.c */
#if defined(__VMS) && defined(__VAX)
/* OPENVMS-VAX can't take symbol names larger than 31 characters */
#define nd6_generate_neighbor_solicitation nd6_generate_neighbor_solicitat
#define nd6_process_neighbor_solicitation  nd6_process_neighbor_solicitati
#define nd6_process_neighbor_advertisement nd6_process_neighbor_advertisem
#define nd6_process_router_advertisement   nd6_process_router_advertisemen
#define nd6_generate_neighbor_advertisement nd6_generate_neighbor_advertis
#endif	/* defined(__VMS) && defined(__VAX) */
struct mbuf * nd6_generate_neighbor_solicitation P((struct in6_ifnet *,
						    const struct in6_addr *,
						    const struct in6_addr *,
						    const struct in6_addr *));
void	nd6_process_neighbor_solicitation P((struct ip6_rxinfo *));
void	nd6_process_neighbor_advertisement P((struct ip6_rxinfo *));
void	nd6_process_router_solicitation P((struct ip6_rxinfo *));
void	nd6_process_router_advertisement P((struct ip6_rxinfo *));
int	nd6_process_options P((struct ip6_rxinfo *, size_t, u_int,
				char *, size_t *));
void	nd6_dad_start P((struct in6_localaddr *));
void	nd6_dad_stop P((struct in6_localaddr *, int));
int	nd6_dad_solicit P((struct in6_localaddr *));
struct mbuf *nd6_generate_neighbor_advertisement P((struct in6_localaddr *,
						    const struct in6_addr *,
						    unsigned,
						    unsigned));


/* nd6_redirect.c */
void	nd6_process_redirect P((struct ip6_rxinfo *));
void	nd6_send_redirect P((struct mbuf *, const struct in6_addr *,
				const struct in6_addr *,
				struct in_route *));

/* raw_ip6.c */
void    rip6_init P((void));
void    rip6_input P((struct ip6_rxinfo *rx, unsigned));
int     rip6_output P((struct mbuf *, struct socket *, struct sockaddr_in6 *,
				struct mbuf *));
int     rip6_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     icmp6_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     rip6_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
                                struct mbuf *));

/* in6_advapi.c */
void in6_rthdrswap P((struct in6_addr *, char *, int, int, int));
struct in6optinfo * in6_opt_init P(( void ));
void in6_opt_free P(( struct in6optinfo *op));
int in6_opt_ctltoopt P((struct inpcb *, struct in6optinfo *, struct mbuf *,
			int));
struct mbuf *in6_opt_passup_options P((struct ip6_rxinfo *rx ,int flags));
void in6_copyip6hdrext P((struct ip6_hdr *ip6, uchar *, struct in6optinfo *op));
int in6_setpktoptions P((struct inpcb *inp, struct mbuf *m, u_char **, int));
int udp_add_v6opt P((struct ip6_txinfo *, struct mbuf *, struct mbuf *,
					struct udphdr *));
int set_rthdr P((struct in6optinfo *, void *, int));
int in6_opt_clear P((struct in6optinfo *, int));

/* ipv6_cfg.c */
cfg_status_t ipv6_configure P(( cfg_op_t, caddr_t, ulong, caddr_t, ulong));
void         ipv6_configure_callback P((int, int, ulong, ulong));


/* in6_proto.c */
int ipv6_domain_configure P((void));
int ipv6_domain_unconfigure P((void));


/* ip6_mobile.c */
void	mip6_init P((void));
void	mip6_cache_rt_delete P((struct rtentry *));
void	mip6_cache_free P((mip6_cache_t *, int));
void	mip6_timer P((void));
int	mip6_have_binding P((struct in6_addr *, const struct in6_addr *));
int	mip6_process_hoti P((struct ip6_rxinfo *, u_int, u_int));
int	mip6_process_coti P((struct ip6_rxinfo *, u_int, u_int));
int	mip6_process_bu P((struct ip6_rxinfo *, u_int, u_int));
struct mbuf *mip6_add_header P((struct ip6_txinfo *, struct rtentry *, int *));
struct mbuf *mip6_check_routeheader P((struct ip6_txinfo *, int *));
void	mip6_dad_stop P((struct in6_localaddr *, int));
enum in6_disposition mip6_ip6_input P((struct ip6_rxinfo *));
int	mip6_control P((unsigned int, struct in6_ifnet *, struct ip6ifreq *));
void	mip6_encap P((struct ip6_rxinfo *, struct mbuf *));
void	mip6_binding_error P((struct ip6_rxinfo *, u_int));
struct in6_ifnet *mip6_if6_pick P((struct in6_addr *, struct in6_ifnet *, int,
		struct rtentry **));
struct rtentry *mip6_update_nh_route P((mip6_cache_t *));


/* mip6_rrsec.c */
void mip6_rrsec_init P((void));
void mip6_rr_nonce_regen_timer P((void));
void mip6_rr_nonce_timeout P((void));
uint16_t mip6_rr_token_create P((uint16_t, const struct in6_addr *,
		uint8_t *));
uint8_t mip6_kbm_create P((const struct in6_addr *, const struct in6_addr *,
		uint16_t, uint16_t, int, mip6_key_t *));
void mip6_key_destroy P((mip6_key_t *));
int mip6_key_valid P((mip6_key_t *));
uint8_t mip6_bu_rrvalidate P((const struct in6_addr *,
		struct ip6mh_opt_nonce_index *, mip6_auth_t *, mip6_key_t *));
int mip6_ba_rrauthenticate P((mip6_key_t *, mip6_auth_t *));
int mip6_nonces_expired P((uint16_t, uint16_t));

#ifdef __P_IN_PROTO_IPV6
#undef P
#undef __P_IN_PROTO_IPV6	/* clean up */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _PROTO_IPV6_H */
