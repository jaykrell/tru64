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
 * Avoid recursive and double includes
 */
#if !defined(__INCLUDE_IP_TCNTL_CL_STRUCT)
#define __INCLUDE_IP_TCNTL_CL_STRUCT


/*
 * Define symbolic names for indices into the cl configuration array.
 */
enum {
    CL_CONF_MAX_NONCONFORM_QUEUE,
    CL_CONF_MAX_TOTAL_r,
    CL_CONF_MAX_TOTAL_b,
    CL_CONF_MAX_NR_FLOWS,

    CL_CONF_LAST
};

#define CL_DEF_MAX_NONCONFORM	24
#define CL_DEF_MAX_TOTAL_b	1000000
#define CL_DEF_MAX_NR_FLOWS	500

/*
 * This structure is a building block used by the
 * controlled load service to return private information
 * about a flow.
 */
typedef struct {
    int			service_type;	/* intserv service number */
    int			unused;

    TB_Tsp_parms_t	tb;		/* token bucket flow parameters */
    u_long		bitrate;	/* link layer data rate in bits/s */

    u_long policed_packets;	/* nr of packets policed */
    u_long policed_bytes;	/* total bytes of policed packets */
    u_long dropped_packets;	/* nr of packets policed + dropped */
    u_long dropped_bytes;	/* total bytes of policed + dropped packets */
    u_long good_packets;	/* nr of conforming packets */
    u_long good_bytes;		/* total bytes of conforming packets */

    union tcntl_sockaddr dst;	/* destination address */
} cl_flowinfo_t;

#if defined(_KERNEL)
/*
 * Traffic control information for network interfaces that use the
 * controlled-load-service-only device-independent packet scheduler.
 *
 * The tcntl lock applies to all of struct cl_tcntl.
 */
struct cl_tcntl {
END_64BYTE_CACHEBLOCK_READ      /* 5 cache blocks (padding not needed) */

    struct tcntl_conf_entry conf[CL_CONF_LAST + 1];

END_64BYTE_CACHEBLOCK_READ

BEGIN_64BYTE_CACHEBLOCK_READ

    /*
     * Information used by admission control.
     */

    /*
     * current values: */
    u_long tx_reserved_r;	   /* data rate in bits/s */
    u_long tx_reserved_b;          /* burst size in bytes */
    /*
     * limits for above values: */
    u_long tx_max_total_r;
    u_long tx_max_total_b;

    u_int tx_max_nr_flows;         /* Maximum permitted flows */
    u_int tx_pad1[7];              /* Pad to even cache block */

END_64BYTE_CACHEBLOCK_READ

BEGIN_64BYTE_CACHEBLOCK_READ

    /*
     * Information used by admission control.
     */

    /*
     * current values: */
    u_long rx_reserved_r;	   /* data rate in bits/s */
    u_long rx_reserved_b;          /* burst size in bytes */
    /*
     * limits for above values: */
    u_long rx_max_total_r;
    u_long rx_max_total_b;

    u_int rx_max_nr_flows;         /* Maximum permitted flows */
    u_int rx_pad2[7];              /* Pad to even cache block */

END_64BYTE_CACHEBLOCK_READ

BEGIN_64BYTE_CACHEBLOCK_WRITE

    /**
     ** The following information augments that in struct ifqueue if_snd.
     ** Thus the lock if_slock also applies here. And splimp() is necessary.
     **/
    u_long ifq_nonconformdrop;	/* nr of non-tspec-conform packets dropped */
    u_long if_oprio;		/* nr of conforming packets sent */
    u_long if_ononconform;	/* nr of non-conforming packets sent */
    struct mbuf *ifq_best_effort;
    struct mbuf *ifq_priority;
    int ifq_prio_len;
    int ifq_best_effort_len;
    int ifq_nonconform_len;
    /**
     ** end of locked if_snd queue data
     **/

    int ifq_max_nonconform_len;

    u_int pad1[2];              /* Bring this to full cache block */

END_64BYTE_CACHEBLOCK_WRITE

};

struct cl_flowentry {
BEGIN_64BYTE_CACHEBLOCK_READ
    union tcntl_sockaddr dst;	/* destination address */
    TB_Tsp_parms_t tb;		/* token bucket tspec */
    u_long bitrate;		/* worst case data rate in bits/s */
END_64BYTE_CACHEBLOCK_READ

BEGIN_64BYTE_CACHEBLOCK_WRITE
    /*
     * Policing information and statistics.
     * Only change it within an IFQ_LOCK on the if_snd queue!
     */
    struct timeval lasttime;	/* the time the previous packet of this flow
				 * has been received
				 */
    u_long policed_packets;	/* nr of packets policed */
    u_long policed_bytes;	/* total bytes of policed packets */
    u_long dropped_packets;	/* nr of packets policed + dropped */
    u_long dropped_bytes;	/* total bytes of policed + dropped packets */
    u_long good_packets;	/* nr of conforming packets */
    u_long good_bytes;		/* total bytes of conforming packets */
    u_int bucket;		/* nr of bytes available for the flow
				 * to send out
				 */
    u_int pad1[1];              /* Padd to full cache block */
END_64BYTE_CACHEBLOCK_WRITE
};

#endif /* defined(_KERNEL) */
#endif /* !defined(__INCLUDE_IP_TCNTL_CL_STRUCT) */
