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
 * @(#)$RCSfile: iptunnel_swtab.h,v $ $Revision: 1.1.12.3 $ (DEC) $Date: 2002/01/29 21:19:18 $
 */
#ifndef  __IPTUNNEL_SWTAB_H
#define __IPTUNNEL_SWTAB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL
#include <netinet/proto_iptunnel.h>
#include <net/net_globals.h>

#ifndef P
#define P(s) s
#define __P_IN_IPTUNNEL_SWTAB	/* P was defined here */
#endif

struct _iptunnel_swtab {
#ifndef __VMS
	void    (*ip6_tunnel_init) P((void));
#else
	int     (*ip6_tunnel_init) P((void));
#endif
	void    (*ipt_intf_enable) P((struct sockaddr *));
	void    (*ipt_intf_disable) P((struct sockaddr *));
	int     (*ip4ip4_input) P((struct mbuf *, int));
	void    (*ipip4_ctlinput) P((int, struct sockaddr *, caddr_t, void *));
	int     (*ipip6_input) P((struct ip6_rxinfo *, int));
};

#ifdef __P_IN_IPTUNNEL_SWTAB
#undef P
#undef __P_IN_IPTUNNEL_SWTAB	/* clean up */
#endif

extern struct _iptunnel_swtab *iptunnel_swtab;

#endif /* _KERNEL */

extern int iptisconfigured;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __IPTUNNEL_SWTAB_H */
