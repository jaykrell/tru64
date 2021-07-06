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
 * @(#)$RCSfile: if_iptunnel.h,v $ $Revision: 1.1.13.3 $ (DEC) $Date: 2002/03/25 14:28:57 $
 */

#ifndef _IF_IPTUNNEL_H
#define _IF_IPTUNNEL_H

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_llinfo.h>
#include <netinet/iptunnel_cfg.h>

#ifdef _KERNEL

#include "netinet/in_route.h"
#include "netinet/if_ether.h"   /* packetfilter support */
#include "net/ether_driver.h"   /* packetfilter support */

/*
 * Configured IPv4 tunnel definitions
 */

#ifndef __VMS
#define IPT_NAME	"ipt"
#define IP4T_DESCR	"IPv4 Tunnel Interface"
#define IP6T_DESCR	"IPv6 Tunnel Interface"
#else /* __VMS */
#define IPT_NAME	"IT"
#define IP4T_DESCR	""
#define IP6T_DESCR	""
#endif /* __VMS */

/* valid values of ip4t_flags */
#define IPT_SRC_VALID  0x00000001 /* source address is valid */
#define IPT_SRC_STATIC 0x00000002 /* source addr administratively configured */


/* MTU related defines */

#define IP4T_MTU	IPV6_MINIMUM_LINK_MTU 
#define IP6T_MTU  	IPV6_MINIMUM_LINK_MTU

struct ipt_softc {
    struct ifnet	ipt_ifnet;
    char    		pad[sizeof(struct ether_driver)-sizeof(struct ifnet)];
    int                 ipt_flags;
    union {
	struct in_addr  ipt_softc_src_un_src4;
	struct in6_addr ipt_softc_src_un_src6;
    } ipt_softc_src;
    int ipt_scope_id;		             /* Scope id of the interface on which
					      * the tunnel source address is or
					      * will be configured (V6 only) 
					      */
    struct in_route     ipt_ro;
    struct in_ro_llinfo ipt_ro_llinfo;	     /* Cache for ND entry */
#if     NETSYNC_LOCK
    simple_lock_data_t  ipt_lk_softc;        /* "driver/softc" SMP lock */
    lock_data_t		ipt_pmtu_lock;	     /* protects ipt_pmtu */
#endif
    u_short		ipt_pmtu;	     /* most recent estimate of pmtu */
};


#define ip4t_src ipt_softc_src.ipt_softc_src_un_src4
#define ip6t_src ipt_softc_src.ipt_softc_src_un_src6
#define ip4t_dst ipt_ro.in_ro_dst4.sin_addr
#define ip6t_dst ipt_ro.in_ro_dst6.sin6_addr

#if     NETSYNC_LOCK
ndecl_lock_info(extern, ipt_pmtu_li)
#define IPT_PMTU_LOCKINIT(ipt)  ulock_setup(&((ipt)->ipt_pmtu_lock), \
						ipt_pmtu_li, TRUE)
#define IPT_PMTU_READ_LOCK(ipt)        ulock_read(&((ipt)->ipt_pmtu_lock))
#define IPT_PMTU_UNLOCK(ipt)           ulock_done(&((ipt)->ipt_pmtu_lock)) 
#define IPT_PMTU_WRITE_LOCK(ipt)       ulock_write(&((ipt)->ipt_pmtu_lock))
#define IPT_PMTU_WRITETOREAD_LOCK(ipt) ulock_write_to_read(&((ipt->ipt_pmtu_lock))
#else
#define IPT_PMTU_LOCKINIT()
#define IPT_PMTU_LOCK_DECL()
#define IPT_PMTU_READ_LOCK()
#define IPT_PMTU_UNLOCK()
#define IPT_PMTU_WRITE_LOCK()
#define IPT_PMTU_WRITETOREAD_LOCK()
#endif  /* NETSYNC_LOCK */



/* 
 * The tunif_softc structure is a  struct ether_driver, 
 * which is needed for packetfilter stats.
 */
struct tunif_softc {
    struct ether_driver	*tunif_etherdriver;
#if	NETSYNC_LOCK
    simple_lock_data_t  tunif_lk_softc;        /* "driver/softc" SMP lock */
#endif
};
 
/*
 * extern decls for 6-to4 tunnels
 */
extern const struct in6_addr in6addr_tla624;
extern const struct in6_addr in6addr_tla624_pfxmask;

/* 
 * need a  min of 40 bytes to find the ip6_src and ip6_dst of
 * the original tunneled ipv6 packet.
 */
#define ICMP6_MIN_ENCAPS_ERR_LEN 40 

/*
 * need a  min of 20 bytes to find the ip_src and ip_dst of
 * the original tunneled ipv4 packet.
 */
#define ICMP_MIN_ENCAPS_ERR_LEN 20 


#endif /* _KERNEL */


/* cfgmgr constants for tunnel management subsystem */
#define	IPTR_OP_CREATE	0x01			/*   create a new tunnel */
#define	IPTR_OP_DELETE	0x02			/*   delete a virtual tunnel */
#define	IPTR_OP_SHOW	0x03			/*   show a virtual tunnel   */
struct iptunnelreq {
	char	iptr_name[IFNAMSIZ];		/* if name, e.g. "ipt0"	*/
	u_int	iptr_op;			/* operation:		*/
	union {
	    struct {				/* info for create:	*/
		u_int type;			/*   type e.g. IFT_IPV4 */
		union {				/*   source address	*/
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} src;
		union {				/*   destination address */
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} dst;
		int scope_id;			/*   scope id (V6 only) */
	    } create;
	    struct {				/* info for show:	*/
		u_int type;			/*   type e.g. IFT_IPV4 */
	    } show;
	} iptr_un;
};

struct iptunnelres {
	char	iptr_name[IFNAMSIZ];		/* if name, e.g. "ipt0"	*/
	u_int	iptr_status;			/* status of operation: */
	union {
	    struct {				/* info for create:	*/
		u_int type;			/*   type e.g. IFT_IPV4 */
		union {				/*   source address	*/
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} src;
	    } create;
	    struct {				/* info for show:	*/
		u_int type;			/*   type e.g. IFT_IPV4 */
		int scope_id;			/*   scope id (V6 only) */
		union {				/*   source address	*/
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} src;
		union {				/*   destination address */
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} dst;
		union {				/*   next hop            */
		    struct in_addr ina4;
		    struct in6_addr ina6;
		} next_hop;
	    } show;
	} iptr_un;
};



#endif /* _IF_IPTUNNEL_H */
