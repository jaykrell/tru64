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
 * @(#)$RCSfile: proto_iptunnel.h,v $ $Revision: 1.1.12.3 $ (DEC) $Date: 2002/01/29 21:19:22 $
 */

#ifndef __PROTO_IPTUNNEL_H
#define __PROTO_IPTUNNEL_H
#ifdef __cplusplus
extern "C" {
#endif

typedef union {
	struct sockaddr     *p1;    
	struct mbuf         *p2;
	struct rtentry 	    *p3;
	struct iptunnelreq  *p4;
	struct iptunnelres  *p5;
	struct ip6_rxinfo   *p6;
} proto_iptunnel_union_t;

#ifndef P
#define P(s) s
#define __P_IN_PROTO_IPTUNNEL	/* P was defined here */
#endif

/* if_iptunnel.c */
#ifndef	__VMS 
void    ip6_tunnel_init P((void));
#else /* __VMS */
int    ip6_tunnel_init P((void));
#endif /* __VMS */
void    ip6ip4_input P((struct mbuf *, int));
void    ipip4_ctlinput P((int, struct sockaddr *, caddr_t, void *));
int 	ipt_tunnel_op P((struct iptunnelreq *, struct iptunnelres *));
void    ipt_intf_enable P((struct sockaddr *));
void    ipt_intf_disable P((struct sockaddr *));
int     ip4ip4_input P((struct mbuf *, int));
int     ipip6_input P((struct ip6_rxinfo *, int));

#ifdef __P_IN_PROTO_IPTUNNEL
#undef P
#undef __P_IN_PROTO_IPTUNNEL	/* clean up */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __PROTO_IPTUNNEL_H */
