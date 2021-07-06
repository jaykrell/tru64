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
 * @(#)$RCSfile: ip_mroute.h,v $ $Revision: 1.1.11.5 $ (DEC) $Date: 1999/03/25 19:58:46 $
 */
/*
 * Definitions for IP multicast forwarding.
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 * Modified by Ajit Thyagarajan, PARC, August 1993.
 * Modified by Ajit Thyagarajan, PARC, August 1994.
 *
 * MROUTING  3.5
 */

#ifndef _IP_MROUTE_H_
#define _IP_MROUTE_H_

/*
 * Multicast Routing set/getsockopt commands.
 */
#define MRT_INIT		100	/* initialize forwarder */
#define MRT_DONE		101	/* shut down forwarder */
#define MRT_ADD_VIF		102	/* create virtual interface */
#define MRT_DEL_VIF		103	/* delete virtual interface */
#define MRT_ADD_MFC		104	/* insert forwarding cache entry */
#define MRT_DEL_MFC		105	/* delete forwarding cache entry */
#define MRT_VERSION		106	/* get kernel version number */
#define MRT_ASSERT		107	/* enable PIM assert processing */


#if BSD /* >= 199103 */
#define GET_TIME(t)	microtime(&t)
#elif defined(sun)
#define GET_TIME(t)	uniqtime(&t)
#else
#define GET_TIME(t)	((t) = time)
#endif

/*
 * Types and macros for handling bitmaps with one bit per virtual interface.
 */
#define MAXVIFS 32
typedef u_int vifbitmap_t;
typedef u_short vifi_t;		/* type of a vif index */
#define ALL_VIFS (vifi_t)-1
#define MAX_UPCALLS 50

#define	VIFM_SET(n, m)			((m) |=  (1 << (n)))
#define	VIFM_CLR(n, m)			((m) &= ~(1 << (n)))
#define	VIFM_ISSET(n, m)		((m) &   (1 << (n)))
#define VIFM_CLRALL(m)			((m) = 0x00000000)
#define VIFM_COPY(mfrom, mto)		((mto) = (mfrom))
#define VIFM_SAME(m1, m2)		((m1) == (m2))
								  
/*
 * Argument structure for MRT_ADD_VIF.
 * (MRT_DEL_VIF takes a single vifi_t argument.)
 */
struct vifctl {
    vifi_t	    vifc_vifi;	    	/* the index of the vif to be added  */
    u_char	    vifc_flags;     	/* VIFF_ flags defined below         */
    u_char	    vifc_threshold; 	/* min ttl required to forward on vif*/
    u_int	    vifc_rate_limit;    /* max rate           		     */
    struct in_addr  vifc_lcl_addr;  	/* local interface address           */
    struct in_addr  vifc_rmt_addr;  	/* remote address (tunnels only)     */
};

#define VIFF_TUNNEL	  0x1	    	/* vif represents a tunnel end-point */
#define VIFF_SRCRT	  0x2	    	/* tunnel uses IP src routing	     */
#define VIFF_TIMEOUT	  0x4	    	/* vif needing timeout processing    */


/*
 * Argument structure for MRT_ADD_MFC and MRT_DEL_MFC
 * (mfcc_tos to be added at a future point)
 */
struct mfcctl {
    struct in_addr  mfcc_origin;		/* ip origin of mcasts       */
    struct in_addr  mfcc_mcastgrp; 		/* multicast group associated*/
    vifi_t	    mfcc_parent;   		/* incoming vif              */
    u_char	    mfcc_ttls[MAXVIFS]; 	/* forwarding ttls on vifs   */
};

#include <netinet/ip_stat.h>			/* bring in the inet stat structs(mrtstat) */

/*
 * Argument structure used by mrouted to get src-grp pkt counts
 */
struct sioc_sg_req {
    struct in_addr src;
    struct in_addr grp;
    u_int pktcnt;
    u_int bytecnt;
    u_int wrong_if;
};

/*
 * Argument structure used by mrouted to get vif pkt counts
 */
struct sioc_vif_req {
    vifi_t vifi;		/* vif number				*/
    u_int icount;		/* Input packet count on vif		*/
    u_int ocount;		/* Output packet count on vif		*/
    u_int ibytes;		/* Input byte count on vif		*/
    u_int obytes;		/* Output byte count on vif		*/
};
    
/*
 * Data structures for SIOCGVIFCONF ioctl
 */
struct vifinfo {
    struct vifctl       vifctl;
    unsigned int        status;         /* unused, set to zero */
    unsigned int        ifc_index;      /* index of corresp. phys. interface */
};
struct vifconf {
    unsigned int        nr_vifs;        /* number of structs in vif_buf */
    unsigned int        flags;          /* unused, set to zero */
    struct vifinfo     *vif_buf;        /* area to store vif information */
};

/*
 * Definitions used for the bitmaps in ip6_rtgetreq
 */
#define RTGET_BITS_IN_LONG ((int) sizeof (unsigned long) * 8)
#define RTGET_IFC_ISSET(ifc, mask) \
        ((mask)[(ifc)/RTGET_BITS_IN_LONG] & (1 << ((ifc)%RTGET_BITS_IN_LONG)))
#define RTGET_IFC_MAX(nr) ((nr) * RTGET_BITS_IN_LONG)

/*
 * Data structures for the SIOCGROUTE ioctl.
 * Can be used for multicast and unicast. Because vifbitmap_t is
 * needed, it's defined here instead of net/route.h
 */
struct ip4_rtgetreq {
    struct sockaddr_in  dst;
    struct sockaddr_in  src;
    struct sockaddr_in  gateway;
    struct in_addr      forw_ifc_addr;  /* forwarding interface address */
    vifbitmap_t         vif_mask;       /* set of outgoing interfaces (only
                                         * used for multicast)
                                         */
};

struct ip6_rtgetreq {
    struct sockaddr_in6 dst;
    struct sockaddr_in6	src;
    struct sockaddr_in6	gateway;
    struct in6_addr	forw_ifc_addr;	/* forwarding interface address */
    int			unused;		/* 8-byte padding */
    int			nr;		/* Number of used bitmap blocks.
					 * Always 0 for unicast destinations.
					 */
    /*
     * If nr > 1, the following array
     * actually has size "nr".
     */
    unsigned long	ifc_mask[1];
};

struct rtgetreq {
    int         flags;
    int         forw_ifc;       /* index of interface for forwarding */
    int         exp_inc_ifc;    /* expected incoming interface index/vif
                                 * for multicast (only used when sender doesn't
                                 *  use shared tree).
                                 */
    int         prefix;         /* prefix length in bits of matching routing
                                 * entry
                                 */
    union {
        struct sockaddr dst;    /* sa_family field is used to find out
                                 * whether this is actually struct ip4_rtgetreq
                                 * or ip6_rtgetreq
                                 */
        struct ip4_rtgetreq ip4;/* this also starts with a sockaddr */
        struct ip6_rtgetreq ip6;/* this also starts with a sockaddr */
    } rtget_u;
};


#ifdef _KERNEL
#include <netinet/in_route.h>	/* needed for vif */
/*
 * The kernel's virtual-interface structure.
 */
struct vif {
    u_char   		v_flags;     	/* VIFF_ flags defined above         */
    u_char   		v_threshold;	/* min ttl required to forward on vif*/
    u_int      		v_rate_limit; 	/* max rate			     */
    struct tbf 	       *v_tbf;       	/* token bucket structure at intf.   */
    struct in_addr 	v_lcl_addr;   	/* local interface address           */
    struct in_addr 	v_rmt_addr;   	/* remote address (tunnels only)     */
    struct ifnet       *v_ifp;	     	/* pointer to interface              */
    u_int		v_pkt_in;	/* # pkts in on interface            */
    u_int		v_pkt_out;	/* # pkts out on interface           */
    u_int		v_bytes_in;	/* # bytes in on interface	     */
    u_int		v_bytes_out;	/* # bytes out on interface	     */
    struct in_route	v_route;	/* Cached route if this is a tunnel  */
};

/*
 * The kernel's multicast forwarding cache entry structure 
 * (A field for the type of service (mfc_tos) is to be added 
 * at a future point)
 */
struct mfc {
    struct in_addr  mfc_origin;	 		/* ip origin of mcasts       */
    struct in_addr  mfc_mcastgrp;  		/* multicast group associated*/
    vifi_t	    mfc_parent; 		/* incoming vif              */
    u_char	    mfc_ttls[MAXVIFS]; 		/* forwarding ttls on vifs   */
    u_int	    mfc_pkt_cnt;		/* pkt count for src-grp     */
    u_int	    mfc_byte_cnt;		/* byte count for src-grp    */
    u_int	    mfc_wrong_if;		/* wrong if for src-grp	     */
    int		    mfc_expire;			/* time to clean entry up    */
    struct timeval  mfc_last_assert;		/* last time I sent an assert*/
    struct rtdetq  *mfc_stall;                  /* pkts waiting for route */
    struct mfc     *mfc_next;             	/* hash table linkage */
};

/*
 * Struct used to communicate from kernel to multicast router
 * note the convenient similarity to an IP packet
 */
struct igmpmsg {
    u_int	    unused1;
    u_int	    unused2;
    u_char	    im_msgtype;			/* what type of message	    */
#define IGMPMSG_NOCACHE		1
#define IGMPMSG_WRONGVIF	2
    u_char	    im_mbz;			/* must be zero		    */
    u_char	    im_vif;			/* vif rec'd on		    */
    u_char	    unused3;
    struct in_addr  im_src, im_dst;
};

/*
 * Argument structure used for pkt info. while upcall is made
 */
struct rtdetq {
    struct mbuf 	*m;		/* A copy of the packet	    	    */
    struct ifnet	*ifp;		/* Interface pkt came in on 	    */
#ifdef UPCALL_TIMING
    struct timeval	t;		/* Timestamp */
#endif /* UPCALL_TIMING */
    struct rtdetq       *next;
};

#define MFCTBLSIZ	256
#if (MFCTBLSIZ & (MFCTBLSIZ - 1)) == 0	  /* from sys:route.h */
#define MFCHASHMOD(h)	((h) & (MFCTBLSIZ - 1))
#else
#define MFCHASHMOD(h)	((h) % MFCTBLSIZ)
#endif

#define MAX_UPQ	4		/* max. no of pkts in upcall Q */

/*
 * Token Bucket filter code 
 */
#define MAX_BKT_SIZE    10000             /* 10K bytes size 		*/
#define MAXQSIZE        10                /* max # of pkts in queue 	*/

/*
 * queue structure at each vif
 */
struct pkt_queue 
{
    u_int pkt_len;               /* length of packet in queue 	*/
    struct mbuf *pkt_m;           /* pointer to packet mbuf	*/
    struct ip  *pkt_ip;           /* pointer to ip header	*/
};

/*
 * the token bucket filter at each vif
 */
struct tbf
{
    u_int last_pkt_t;	/* arr. time of last pkt 	*/
    u_int n_tok;      	/* no of tokens in bucket 	*/
    u_int q_len;    	/* length of queue at this vif	*/
};

#ifdef RSVP
int	ip_mrouteget (struct in_addr, struct in_addr, int *, int *,
		      vifbitmap_t *);
#endif

#endif /* _KERNEL */

#endif
