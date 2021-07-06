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
 *	@(#)$RCSfile: proto_inet.h,v $ $Revision: 4.3.89.7 $ (DEC) $Date: 2002/02/12 19:58:19 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
 */
/*
 *	Revision History:
 *
 * 10-Oct-91	Heather Gray
 *	add ip_dealloc()
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patches.
 *
 */
#ifndef _PROTO_INET_H_
#define _PROTO_INET_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef P
#define	P(s) s
#define __P_IN_PROTO_INET /* P was defined here */
#endif

/* Avoid scoping problems */
typedef union {
	struct arpcom		*p1;
	struct arptab		*p2;
	struct mbuf		*p3;
	struct ifnet		*p4;
	struct route		*p5;
	struct sockaddr		*p6;
	struct sockaddr_in	*p7;
	struct socket		*p8;
	struct in_addr		*p9;
	struct in_ifaddr	*p10;
	struct inpcb		*p11;
	struct ipq		*p12;
	struct ip		*p13;
	struct tcpcb		*p14;
	struct tcpiphdr		*p15;
	struct ipasfrag		*p16;
	struct ipoption		*p17;
	struct in_multi 	*p18;
	struct ip_moptions 	*p19;
	struct trn_header	*p20;
	struct icmp		*p21;
	struct in_afilt		*p22;
	struct __inpcb_hashbucket *p23;
	struct pmtu_rtentry	*p24;
	struct tcphdr		*p25;
	struct in6_addr		*p26;
	struct sockaddr_in6	*p27;
	struct icmpstat		*p28;
	struct mrtstat		*p29;
	struct rtstat		*p30;
	struct rtentry		*p31;
	struct ifqueue		*p32;
	struct uio		*p33;
	struct in_route		*p34;
	struct in6_localaddr	*p35;
	struct ip6_moptions	*p36;
	struct ip6_rxinfo	*p37;
	struct ip6_txinfo	*p38;
	struct iptunnelreq	*p39;
	struct iptunnelres	*p40;
} proto_inet_union_t;

/* The tcp_seq typedef is a problem. Better to cast or rearrange? */
#define proto_tcp_seq	u_int

/* if_ether.c */
#ifndef __VMS
void	arpinit P((void));
void	arpinput P((struct arpcom *, struct mbuf *));
void	in_arpinput P((struct arpcom *, struct mbuf *, struct trn_header *));
#else /* __VMS */
int	arpinit P((void));
void	arpinput P((struct mbuf *));
void	in_arpinput P((struct arpcom *, struct mbuf *));
#endif /* __VMS */
void	arptimer P((void));
void	arpintr P((void));
void	arpoutput P((struct arpcom *, struct mbuf *, u_char *, u_short, caddr_t));
char	*arp_sprintf P((char *, u_char *, int));
int	ifnet_arp_cache_init P((struct ifnet *));
void	ifnet_arp_cache_uninit P((struct ifnet *));
int	ifnet_arp_cache_delete P((struct ifnet *));
void	arp_cache_free P((struct rtentry *));

/* igmp.c */
void	igmp_init P((void));
void	igmp_input P((struct mbuf *, int));
#ifndef __VMS
void    igmp_joingroup P((struct in_multi *));
#else /* __VMS */
int     igmp_joingroup P((struct in_multi *));
#endif /* __VMS */
void    igmp_leavegroup P((struct in_multi *));
void	igmp_fasttimo P((void));
void	igmp_slowtimo P((void));

/* ip_mroute.c */
void	ipip_input P((struct mbuf *, int));
void	mroute_expire_upcalls P((void));
#ifndef MROUTING
int	ip_mrouter_get P((int, struct socket *, struct mbuf *));
#else /* MROUTING */
int	ip_mrouter_get P((int, struct socket *, struct mbuf **));
#endif /* MROUTING */
int	ip_mrouter_set P((int, struct socket *, struct mbuf *));
int	ip_mrouter_done P((void));
int	ip_mforward P((struct ip *, struct ifnet *, struct mbuf *, int));
int	mrt_ioctl P((int, caddr_t));
int	mrtstats P((struct mrtstat*, int, int));
void	mrtaddstats P((void));
int	rtstats P((struct rtstat*, int, int));
int	legal_vif_num P((int));
u_int	ip_mcast_src P((int));
int	ifp_to_vif P((struct ifnet *));

/* ip_rsvp.c */
int     ip_rsvp_start P((struct socket *));
int     ip_rsvp_done  P((void));
int     ip6_rsvp_start P((struct socket *));
int     ip6_rsvp_done P((void));
void	rsvp_init     P((void));
void    rsvp_input    P((struct mbuf *));
int	rsvp_rtioctl  P((struct socket *, unsigned int, caddr_t));

/* in.c */
struct	in_addr in_makeaddr P((u_int, u_int));
u_int	in_netof P((struct in_addr));
void	in_sockmaskof P((struct in_addr, struct sockaddr_in *));
u_int	in_lnaof P((struct in_addr));
int	in_localaddr P((struct in6_addr *, struct rtentry *));
int	in_canforward P((struct in_addr));
int	in_control P((struct socket *, unsigned int, caddr_t, struct ifnet *));
void	in_ifscrub P((struct ifnet *, struct in_ifaddr *, int));
int	in_ifinitia P((struct ifnet *, struct in_ifaddr *, struct sockaddr_in *,
				int));
int	in_ifinitrt P((struct ifnet *, struct in_ifaddr *));
void	in_linkia P((struct ifnet *, struct in_ifaddr *, int));
struct	in_ifaddr *in_iaonnetof P((u_int));
int	in_broadcast P((struct in_addr));
struct	in_multi *in_addmulti P((struct in_addr *, struct ifnet *));
void	in_delmulti P((struct in_multi *));
void	inifaddr_hinit P((void));
struct	in_ifaddrh **inifaddr_halloc P((int));
struct	in_ifaddrh **inifaddr_hrealloc P((int));
void	inifaddr_hdealloc P((struct in_ifaddrh **));
void	inifaddr_hresize P((void));
int	insert_inifaddrh P((struct in_addr, struct ifnet *, u_short));
void	remove_inifaddrh P((struct in_addr));

/* in_cksum.c or machine dependent */
int	in_cksum P((struct mbuf *, int));

/* in_pcb.c */
int	in_pcballoc P((struct socket *, struct inpcb *));
int	in_pcbbind P((struct inpcb *, struct mbuf *));
int	in_pcbconnect P((struct inpcb *, struct mbuf *));
int	in_pcbsnapconnect P((struct inpcb *, struct mbuf *, struct in_route *,
		struct in6_addr *, struct in6_addr *, u_short *, 
		struct ifnet **));
int	in_fastpcbconnect P((struct inpcb *inp, struct sockaddr_in6 *sin));
void	in_pcbdisconnect P((struct inpcb *));
void	in_pcbdetach P((struct inpcb *));
void	in_pcbfree P((struct inpcb *));
void	in_pcbinsque P((struct inpcb *,	struct __inpcb_hashbucket *, struct inpcb *)) ;
void	in_pcbremque P((struct inpcb *)) ;

void	in_setsockaddr P((struct inpcb *, struct mbuf *));
void	in_setpeeraddr P((struct inpcb *, struct mbuf *));
void	in_pcbnotify P((struct inpcb *, const struct in6_addr *, u_short,
			const struct in6_addr *, u_short, int,
			void (*)(struct inpcb *, int)));
void	in_losing P((struct inpcb *));
void	in_rtchange P((struct inpcb *));
void	in_rtconfirm P((struct inpcb *));
struct	inpcb *in_pcblookup P((struct inpcb *, const struct in6_addr *,
				u_short, const struct in6_addr *, u_short, int,
				struct __inpcb_hashbucket *, struct ifnet *));
struct	inpcb *in_pcbmatch P((struct inpcb *, const struct in6_addr *,
				u_short, const struct in6_addr *, u_short,
				struct __inpcb_hashbucket *));
struct	inpcb *in_pcbmatch_ifp P((struct inpcb *, const struct in6_addr *,
				u_short, const struct in6_addr *, u_short,
				struct __inpcb_hashbucket *, struct ifnet *));
struct	__inpcb_hashbucket *in_pcbhashalloc P((int));
void	in_pcbhashdealloc P((struct  __inpcb_hashbucket *));

/* in_proto.c */
int	inet_configure_domain (void);
int	inet6_configure_domain (void);

/* ip_icmp.c */
void	icmp_error P((struct mbuf *, int, int, struct in_addr));
void	icmp_input P((struct mbuf *, int));
void	icmp_reflect P((struct mbuf *));
struct	in_ifaddr *ifptoia P((struct ifnet *));
void	icmp_send P((struct mbuf *, struct mbuf *, int));
void	icmpaddstats P((void));
int	icmpstats P((struct icmpstat *, int, int));

n_time	iptime P((void));

/* ip_input.c */
void 	ip_init_rad P((struct rad *, int, void (*)(void), struct domain *));
void	ip_init_ipqs P((int, struct ifqueue *, void (*)(void), 
        		struct domain *, int *));
void	ip_init P((void));
#ifndef __VMS
void	ipintr P((struct ifqueue *));
#else /* __VMS */
void	ipintr P((struct mbuf *));
#endif	 /* __VMS */
void	ip_reconfig_ipqmaxlen P((int, int *));
struct	mbuf *ip_reass P((struct mbuf *, struct ipq *, int));
void	ip_slowtimo P((void));
void	ip_reastimo P((struct ipq *));
void	ip_drain P((void));
int	ip_dooptions P((struct mbuf *));
struct	in_ifaddr *ip_rtaddr P((struct in_addr));
void	save_rte P((u_char *, struct in_addr));
struct	mbuf *ip_srcroute P((void));
void	ip_stripoptions P((struct mbuf *, struct mbuf *, struct ipoption *));
void	ip_forward P((struct mbuf *, int));
void	ip_forwardscreen P((struct mbuf *, int));
void	ip_outputscreen P((struct mbuf *, int, struct in_route *, int));
int     ip_accessfilter P((struct in_afilt *, struct ip *, struct mbuf *));
void	ip_continue_input P((struct mbuf *));
void	ipsec_continue_input P((struct mbuf *));

/* ip_output.c */
int	ip_output P((struct mbuf *, struct mbuf *, struct in_route *, 
				int, struct ip_moptions *));
struct	mbuf *ip_insertoptions P((struct mbuf *, struct mbuf *, int *));
int	ip_optcopy P((struct ip *, struct ip *));
int	ip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	ip_pcbopts P((struct mbuf **, struct mbuf *));
void	ip_mloopback P((struct ifnet *, struct mbuf *, 
				struct sockaddr_in *, int));
void	ip_freemoptions P((struct ip_moptions *));
int	ip_setmoptions P((int, struct ip_moptions **, struct mbuf *));
int	ip_getmoptions P((int, struct ip_moptions *, struct mbuf **));

/* ip_screen.c */
void	ip_gwbounce P((struct mbuf *, int));
int	ip_cachesize P((void));
int	ip_cacheadd P((struct mbuf *, char *, int *));
int	ip_cachecmp P((char *, char *));

/* pmtu.c */
void	pmtu_init P((void));
void	pmtu_slowtimo P((void));
void	pmtu_dgtb_rcvd P((caddr_t, struct sockaddr *, struct ip6_rxinfo *,
			  u_int));

/* raw_ip.c */
void	rip_input P((struct mbuf *));
int	rip_output P((struct mbuf *, struct socket *));
int	rip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	rip_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));

/* tcp_debug.c */
void	tcp_trace P((short, short, struct tcpcb *, const struct in6_addr *,
		     const struct in6_addr *, const struct tcphdr *, u_int,
		     int));

/* tcp_input.c */
int	tcp_reass P((struct tcpcb *, struct tcphdr *, struct mbuf *,
			caddr_t, struct mbuf *));
void	tcp_input P((struct mbuf *, int));
void    tcp6_input P((struct ip6_rxinfo *, unsigned));
void	tcp_dooptions P((struct tcpcb *, caddr_t, int, struct tcphdr *, int*, unsigned int *));
void	tcp_pulloutofband P((struct socket *, struct tcphdr *,
				struct mbuf *));
void	tcp_xmit_timer P((struct tcpcb *));
int	tcp_mss P((struct tcpcb *, u_short));

/* tcp_output.c */
int	tcp_output P((struct tcpcb *));
void	tcp_setpersist P((struct tcpcb *));
int	tcp_sosend P((struct socket *, struct uio *, int, int));

/* tcp_subr.c */
void	tcp_init P((void));
void	tcb_init P((struct inpcb*));
void	tcp_respond P((struct tcpcb *, struct tcphdr *, struct mbuf *,
				proto_tcp_seq, proto_tcp_seq, int, int,
				struct in6_addr *, struct in6_addr *));
struct	tcpcb *tcp_newtcpcb P((struct inpcb *));
struct	tcpcb *tcp_drop P((struct tcpcb *, int));
struct	tcpcb *tcp_close P((struct tcpcb *));
void	tcp_drain P((void));
void	tcp_notify P((struct inpcb *, int));
void	tcp_ctlinput P((int, struct sockaddr *, caddr_t));
void	tcp6_ctlinput P((int, struct sockaddr *, caddr_t));
void	tcp_quench P((struct inpcb *));
void	tcp_rtupdate P((struct inpcb *));
int	tcp_mss_send P((struct tcpcb *, struct rtentry *));
void	tcp_dgtb_rcvd P((struct inpcb *));
int	tcp_deletetcb P((struct sockaddr *, struct sockaddr *, int *));
int	tcp_abort_if_tcbs P((struct sockaddr *, int *));

/* tcp_timer.c */
void	tcp_fasttimo P((void));
void	tcp_slowtimo P((void));
void	tcp_canceltimers P((struct tcpcb *));
struct	tcpcb *tcp_timers P((struct tcpcb *, int));
void	resize_tcb_hash_list P((void));
void	resize_tcbquickbindtable P((void));

/* tcp_usrreq.c */
int	tcp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	tcp_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	tcp_attach P((struct socket *));
struct	tcpcb *tcp_disconnect P((struct tcpcb *));
struct	tcpcb *tcp_usrclosed P((struct tcpcb *));

/* udp_usrreq.c */
void	udp_init P((void));
void	udp_input P((struct mbuf *, int));
void    udp6_input P((struct ip6_rxinfo *, unsigned));
struct	mbuf *udp_saveopt P((caddr_t, int, int));
void	udp_notify P((struct inpcb *, int));
void	udp_ctlinput P((int, struct sockaddr *, caddr_t));
void	udp6_ctlinput P((int, struct sockaddr *, caddr_t));
int	udp_output P((struct inpcb *, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	udp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
void	udp_slowtimo P((void));

/* ip6_cksum.c */
u_int ip6_mkcksum P((const struct in6_addr *, const struct in6_addr *,
			unsigned, unsigned, u_int));
unsigned ip6_mcksum P((struct mbuf *, unsigned, unsigned));
int	ip6_addcksum P((struct mbuf *, unsigned, unsigned, unsigned));
int	ip6_docksum P((struct mbuf *, const struct in6_addr *,
			const struct in6_addr *, unsigned, unsigned, unsigned));
int	ip6_tstcksum P((struct mbuf *, const struct in6_addr *,
			const struct in6_addr *, unsigned, unsigned, unsigned));

/* inet6_base.c */
const char * inet6_ntoa P((const struct in6_addr *, char *));
int inet6_scope_to_buf P((u_int, char *, size_t, int));
int in6_get_hdrbuf P((struct mbuf *, int, int *));
int in6_get_maxhdrbufsize P((void ));
int pr6_usrreq_stub P((struct socket *, int, struct mbuf *, struct mbuf *,
			struct mbuf *));
int in6_find_hdr P((const struct mbuf *, u_int, u_int, u_int, u_int *));
struct mbuf *in6_saveopt(caddr_t, int, int);
void in6_add_v4mapped_opt(struct ip *, caddr_t *, int *);


#include <netinet/in6_machtypes.h>
typedef union {
        struct ip6_hdr    *p1;
        struct in6_ifaddr *p2;
        struct in6_ifnet  *p3;
	struct ip6ifreq   *p4;
	struct icmp6_hdr  *p5;    
	struct rad        *p6;    
	struct domain     *p7;    
} proto_inet6_union_t;


/* in6_subr.c */
unsigned in6_random(void);


#ifdef __P_IN_PROTO_INET
#undef P
#undef __P_IN_PROTO_INET /* clean up */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif

