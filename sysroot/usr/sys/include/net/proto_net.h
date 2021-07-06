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
 *	@(#)$RCSfile: proto_net.h,v $ $Revision: 4.3.91.5 $ (DEC) $Date: 2002/07/10 18:36:01 $
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
 *	add if_isfull()
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patches
 *
 */
#ifndef _PROTO_NET_H_
#define _PROTO_NET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/common_protos.h>

#ifndef P
#define	P(s) s
#define __P_IN_PROTO_NET /* P was defined here */
#endif
/* Avoid scoping problems */
typedef union {
	struct sockaddr		*p1;
	struct socket		*p2;
	struct sockproto	*p3;
	struct mbuf		*p4;
	struct ifnet		*p5;
	struct ifqueue		*p6;
	struct ifaddr		*p7;
	struct ether_header	*p8;
	struct tty		*p9;
	struct slcompress	*p10;
	struct ip		*p11;
	struct in_addr		*p12;
	struct arpcom		*p13;
	struct domain		*p14;
	struct netisr		*p15;
	struct radix_node	*p16;
	struct radix_node_head	*p17;
	struct rawcb		*p18;
	struct route		*p19;
	struct rtentry		*p20;
	struct rt_metrics	*p21;
	struct sl_softc		*p22;
	struct arptab		*p23;
	struct screen_data	*p24;
	struct ifreq       	*p25;
	struct ether_driver   	*p26;
	struct endevp   	*p27;
	struct enOpenDescriptor	*p28;
	struct enState   	*p29;
	struct bpf_insn   	*p30;
	struct Queue		*p31;
	struct enPacket		*p32;
	struct uio		*p33;
	struct rtstat		*p34;
	struct mrtstat		*p35;
	struct in_route		*p36;
	struct vmacreq		*p37;
	struct in6_ifaddr	*p38;
	struct rad_rt_update	*p39;
	struct rad		*p40;
	struct vmac_ifnet	*p41;
} proto_net_union_t;

/* gw_screen.c */
int	screen_control P((struct socket *, int, caddr_t));
void	gw_forwardscreen P((struct mbuf *, int, int, void (*)(), void (*)(), struct in_route *, int));
void	gw_screen_init P((void));
void	screen_bufenter P((struct mbuf *, int, int, void (*)(), void (*)(), struct in_route *, int));
int	screen_getnext P((struct screen_data *));
void	screen_disposition P((u_int, int));
void	screen_purgeold P((void));
void	screen_cacheflush P((void));
void	screen_cacheinit P((void));
void	screen_cacheadd P((struct mbuf *, int, int, int));
int	screen_cachelookup P((struct mbuf *, int, int, int *));

/* if.c */
void	ifinit P((void));
void	ifubareset P((int));
void	ifreset P((int));
#ifndef __VMS
void	if_attach P((struct ifnet *));
#else /* __VMS */
int	if_attach P((struct ifnet *));
#endif /* __VMS */
void	if_proto_attach P((struct ifnet *));
void	if_proto_detach P((struct ifnet *));
int	if_detach P((struct ifnet *));
struct	ether_driver *if_alloc P((char *, int, u_int));
struct	ether_driver *if_alloc_rad P((char *, int, u_int, int));
int	if_dealloc P((struct ether_driver *));
void	if_sphysaddr P((struct ifnet *, struct ifreq *));
struct 	ifaddr *ifa_ifwithaddr P((struct sockaddr *));
struct	ifaddr *ifa_ifwithdstaddr P((struct sockaddr *));
struct  ifaddr *ifa_ifwithdstaddrifp P((struct sockaddr *, 
					struct ifnet *));
struct	ifaddr *ifa_ifwithnet P((struct sockaddr *));
struct	ifaddr *ifa_ifwithaf P((int));
struct	ifaddr *ifaof_ifpforaddr P((struct sockaddr *, struct ifnet *));
void	ifa_addifa P((struct ifnet *, struct ifaddr *, int));
int	ifa_delifa P((struct ifnet *, struct ifaddr *));
void	link_rtrequest P((int, struct rtentry *, struct sockaddr *));
void	if_down P((struct ifnet *));
void	if_qflush P((struct ifqueue *));
int	if_isfull P((struct ifnet *));
void	if_slowtimo P((void));
struct	ifnet *ifunit P((char *));
int	ifprotoioctl P((struct socket *, unsigned int, caddr_t));
int	ifioctl P((struct socket *, unsigned int, caddr_t));
int	ifconf P((unsigned int, caddr_t));
void	if_sphyaddr P((struct ifnet *, struct ifreq *));
void	ifnet_lockinit P((void));
int	vmac_add P((struct ifnet *ifp, struct sockaddr *hwaddr,
			struct sockaddr *paddr));
int	vmac_delete P((struct sockaddr *paddr));
struct  vmac_ifnet *vmac_search P((struct sockaddr *paddr));
struct  vmac_ifnet *vmac_search_in P((struct in_addr *paddr, struct ifnet *ifp));
void	vmac_free P((struct vmac_ifnet *vmifp));
int     vmac_cfg P((struct vmacreq *vmr)); 
	

/* if_ethersubr.c */
int	ether_output P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *, caddr_t));
void	ether_input P((struct ifnet *, struct ether_header *, struct mbuf *));
void	arpwhohas P((struct arpcom *, struct in_addr *));
int	arpioctl P((unsigned int, caddr_t));
int	arpresolve P((struct arpcom *, struct mbuf *, struct sockaddr *,
				u_char *, int *, struct rtentry *));
char	*ether_sprintf P((u_char *));
char 	*inet_ntoa P((struct in_addr, char *));
int	if_addnewaddr P((struct ifnet *, struct ifreq *, int));
int	if_addmulti P((struct ifnet *, struct ifreq *));
int	if_delmulti P((struct ifnet *, struct ifreq *));
int	attachpfilter P((struct ether_driver *));
int	detachpfilter P((struct ether_driver *));
void	arpaliaswhohas P((struct arpcom *, struct in_addr *, caddr_t));
void	rearpwhohas P((struct arpcom *));
int	if_tagging P((struct ifnet *, int (*)(struct ifnet *, unsigned int, caddr_t), int));

/* if_loop.c */
void	loinit P((struct ifnet *));
#ifndef __VMS
void	loattach P((void));
#else /* __VMS */
struct ifnet *loattach P((char *, int));
#endif /* __VMS */
int	loattach2 P((struct ifnet *));
int	looutput P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *, caddr_t));
int	loioctl P((struct ifnet *, unsigned int, caddr_t));
int	looutput2 P((struct ifnet *, struct mbuf *, struct sockaddr *, struct rtentry *));

/* if_sl.c */
#ifndef __VMS
void	slattach P((void));
#else /* __VMS */
struct ifnet *slattach P((char *, int));
#endif /* __VMS */
int	slopen P((dev_t, struct tty *));
void	slclose P((struct tty *));
int	sltioctl P((struct tty *, unsigned int, caddr_t, int));
int	sloutput P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *, caddr_t));
void	slstart P((struct tty *));
void	slinput P((int, struct tty *));
int	slioctl P((struct ifnet *, unsigned int, caddr_t));
static	struct mbuf *sl_btom P((struct sl_softc *, int));
static	int slinit P((struct sl_softc *));

/* slcompress.c */
void	sl_compress_init P((struct slcompress *));
int	sl_compress_tcp P((struct mbuf *, struct ip *,struct slcompress *,int));
int	sl_uncompress_tcp P((u_char **, int, int, struct slcompress *));

/* netisr.c */
int	netinit P((int));
void	netisrinit P((void));
void	netisrinit_rad P((struct rad *));
void	netinit_rad P((struct rad *));
void	net_radctrl P((struct rad *, int));
struct	netisr *netisr_lookup P((int));
struct	netisr *which_netisr P((int));
int	netisr_add P((int, void (*)(void), struct ifqueue *, struct domain *,
			int));
int	netisr_del P((int));
int	netisr_add_rad P((int, void (*)(void), struct ifqueue *,
			struct domain *, int, struct rad *));
int	netisr_del_rad P((int, struct rad *));
int	netisr_input P((int, struct mbuf *, caddr_t, int));
int	netisr_af P((int));
void	netisr_timeout P((caddr_t));
void	Netintr P((void));
void	netisr_thread P((void));
void	schednetisr_nospl P((int));
void	schednetisr_isr P((struct netisr *));
void	schednetisr_netdev P((struct netisr *));

/* netaf_config.c */
void	netinit_domains P((void));

/* radix.c */
struct	radix_node *rn_search P((caddr_t, struct radix_node *));
struct	radix_node *rn_search_m P((caddr_t, struct radix_node *, caddr_t));
#if SEC_NET
struct	radix_node *rn_match P((caddr_t, struct radix_node_head *, 
				struct mbuf *, int *));
#else
struct	radix_node *rn_match P((caddr_t, struct radix_node_head *));
#endif
struct	radix_node *rn_match1 P((caddr_t, struct radix_node_head *, 
				struct ifnet *, caddr_t, u_int));
struct	radix_node *rn_newpair P((caddr_t, int, struct radix_node *));
struct	radix_node *rn_insert P((caddr_t, struct radix_node *, int *,
			struct radix_node *));
struct	radix_node *rn_addmask P((caddr_t, int, int));
struct	radix_node *rn_addmask_rad P((caddr_t, int, int, int));
struct	radix_node *rn_addroute_rad P((caddr_t, caddr_t,
			struct radix_node_head *, struct radix_node *, int));
struct	radix_node *rn_delete_rad P((caddr_t, caddr_t, struct radix_node *,
			struct ifnet *, caddr_t, int));
int	rn_inithead_rad P((struct radix_node_head **, int, int, int));
int	rn_inithead P((struct radix_node_head *, int, int));
int 	rn_walktree P((struct radix_node_head *, 
			int (*f)(struct radix_node *, void *), void *));

/* raw_cb.c */
int	raw_attach P((struct socket *, int));
void	raw_detach P((struct rawcb *));
void	raw_disconnect P((struct rawcb *));
int	raw_bind P((struct socket *, struct mbuf *));

/* raw_usrreq.c */
void	raw_init P((void));
int	raw_input P((struct mbuf *, struct sockproto *,
			struct sockaddr *, struct sockaddr *));
void	raw_ctlinput P((int, struct sockaddr *, caddr_t));
int	raw_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
			struct mbuf *));

/* route.c */
void	rtinithead P((int, int, void (*)(struct sockaddr *,struct sockaddr *)));
void	rtalloc P((struct route *));
struct	rtentry *rtalloc1 P((struct sockaddr *, int));
struct	rtentry *rtalloc2 P((struct sockaddr *, int, struct ifnet *,
			struct sockaddr *));
struct	rtentry *rtalloc_flags P((struct sockaddr *, struct ifnet *,
			struct sockaddr *, u_int));
struct	rtentry *rtalloc_rad P((struct sockaddr *, struct ifnet *,
			struct sockaddr *, int, u_int));
void	rtallocNL P((struct route *));
struct	rtentry *rtallocNL1 P((struct sockaddr *, int));
struct	rtentry *rtallocNL2 P((struct sockaddr *, int, struct ifnet *,
			struct sockaddr *));
struct	rtentry *rtallocNL_flags P((struct sockaddr *, struct ifnet *,
			struct sockaddr *, u_int));
struct	rtentry *rtallocNL_rad P((struct sockaddr *, struct ifnet *,
			struct sockaddr *, int, u_int));
void	rtfree P((struct rtentry *));
void	rtfreeNL P((struct rtentry *));
void	rtredirect P((struct sockaddr *, struct sockaddr *, struct sockaddr *,
			int, struct sockaddr *, struct rtentry **));
int	rtioctl P((struct socket *, unsigned int, caddr_t));
struct	ifaddr *ifa_ifwithrouteifp P((int, struct sockaddr *, struct sockaddr *,
			struct ifnet *));
struct	ifaddr *ifa_ifwithnetifp P((struct sockaddr *, struct ifnet *));
struct  ifaddr *ifa_ifwithaddrifp P(( struct sockaddr *, struct ifnet *));
struct  ifaddr *ifa_ifwithinterfacerouteifp P((const struct sockaddr *,
        					const struct ifnet *));
int	rtrequest P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **));
int	rtrequest1 P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **,
			struct ifnet *));
int	rtrequest_rad P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **,
			struct ifnet *, int, struct radix_node_head *));
void	rt_maskedcopy P((struct sockaddr *, struct sockaddr *,
			struct sockaddr *));
int	rtinit P((struct ifaddr *, int, int));
int	rtinitHL P((struct ifaddr *, int, int));
void	rtscrub P((struct ifnet *, struct ifaddr *, struct ifaddr *));
struct  rtentry *rt_routewithifpgw P((caddr_t, const struct ifnet *ifp,
                                     const struct sockaddr *, u_int));
int 	rt_delete_gw P((struct sockaddr *, struct ifnet *));
int 	rt_delete_ifp P((u_int , struct ifnet *));
struct  radix_node  *rt_match_duplicate P((caddr_t, struct ifnet *, 
					 caddr_t, u_int));
struct	radix_node *rt_add_duplicate P((u_int, caddr_t,  caddr_t));
struct	rtentry *rtalloc_gwroute P((struct rtentry *));
void	rtalloc_gwroute_rad P((struct rtentry *, int));
void	rt_setgate P((struct rtentry *, struct sockaddr *, int));
void	rt_setgate_rad P((struct rtentry *, struct sockaddr *));
void	rt_update_rads P((struct rad_rt_update *));

#if SEC_NET
/* SEC_NET route.c with data accreditation */
int	rtalloc_with_accred P((struct route *, struct mbuf *));
struct	rtentry *rtalloc1_with_accred P((struct sockaddr *, int, struct mbuf *, int*));
#endif

/* rtsock.c */
int	route_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
			struct mbuf *));
int	route_output P((struct mbuf *, struct socket *));
void	rt_setmetrics P((u_long, struct rt_metrics *, struct rtentry *));
void	m_copyback P((struct mbuf *, int, int, caddr_t));
void	rt_missmsg P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, struct sockaddr *, int, int));
int	route_configure P((void));
void	rt_newaddr6msg P((int, struct in6_ifaddr *, struct socket *));
void	rt_if6msg P((struct ifnet *, int, struct socket *));

/* pfilt.c */
struct	mbuf *pfilt_filter P((struct ether_driver *, struct mbuf *,
			struct ether_header *, int, unsigned short, int));
int	pfilt_attach P((struct ifnet *, struct endevp *));
int	pfilt_detach P((struct ifnet *));
void	pfilt_newaddress P((int, u_char *));
struct	mbuf *pf_mcopym P((struct mbuf *, int, int, int));
void	PfiltTrimWaitQueue P((struct enOpenDescriptor *, int));
int	Pfilt_ioctl P((int, int, caddr_t, dev_t));
void	incPromiscCount P((struct enState *, dev_t));

/* pfilt_bpf.c */
int	bpf_rmove P((struct enPacket *, struct uio *, int *, int, int));
void	bpf_reset_counts P((struct enOpenDescriptor *));
int	bpf_ioctl P((int, int, caddr_t, dev_t));

/* bpf_filter.c */
u_int	bpf_filter P((struct bpf_insn *, u_char *, u_int, u_int));
int	bpf_validate P((struct bpf_insn *, int));

#ifdef __P_IN_PROTO_NET
#undef P
#undef __P_IN_PROTO_NET /* clean up */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
