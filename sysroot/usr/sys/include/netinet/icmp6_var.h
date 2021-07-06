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
 * @(#)$RCSfile: icmp6_var.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 1999/10/18 20:20:41 $
 */

#ifndef _ICMP6_VAR_H_
#define _ICMP6_VAR_H_

/*
 * Define variables and structures which are related to 
 * the implementation of the IPv6 Internet Control Message Protocol.
 * (ICMP6)
 */

/*
 * ICMPv6 statistics
 */

struct icmp6stat {
    u_long	icmp6s_tx_error;	/* calls to 'icmp6_send_error' */
    u_long	icmp6s_tx_error_drops;	/* error not sent */
    u_long	icmp6s_tx_nobufs;	/* nobufs when sending error */
    u_long	icmp6s_tx_rlimit_drops; /* error not sent due to rate limit */
    u_long	icmp6s_rx_total;	/* total # ICMPv6 packets received */
    u_long	icmp6s_rx_info;		/* total # of informational class */
    u_long	icmp6s_rx_error;	/* total # of error class */
    u_long	icmp6s_rx_tooshort;	/* packet < ICMP6_MINLEN */
    u_long	icmp6s_rx_checksum;	/* bad ICMPv6 checksum */
    u_long	icmp6s_rx_notifications; /* ICMPv6 pr_ctlinput called */
    u_long	icmp6s_rx_torawip6; 	/* msgs delivered to ICMP listeners */
    u_long	icmp6s_rcv_queries;	/* MLD queries received */
    u_long	icmp6s_rcv_badqueries;	/* bad MLD queries received */
    u_long	icmp6s_rcv_reports;	/* MLD reports received */
    u_long	icmp6s_rcv_badreports;	/* bad MLD reports received */
    u_long	icmp6s_rcv_ourreports;	/* MLD reports matching our listeners */
    u_long	icmp6s_rx_hist[256];	/* receive count by type */
    u_long	icmp6s_tx_hist[256];	/* send count by type */
    u_long	icmp6s_nd_badsolicit;	/* bad Neighbor Solicitation */
    u_long	icmp6s_nd_badadvertise;	/* bad Neighbor Advertisement */
    u_long	icmp6s_nd_badoptions;   /* bad ND options */
    u_long	icmp6s_nd_badcachelookup;/* bad ND cache lookup */
    u_long	icmp6s_nd_badcacheupdate;/* bad ND cache update */
    u_long	icmp6s_nd_badredirect;	/* bad Redirect message */
    u_long	icmp6s_rtr_badsolicit;	/* bad Router Solicitation */
    u_long	icmp6s_rtr_badadvertise;/* bad Router Advertisement */
#if defined(_KERNEL) && LOCK_NETSTATS
    simple_lock_data_t	icmp6s_lock;	/* statistics lock */
#endif
};

#ifdef _KERNEL
extern struct icmp6stat icmp6stat;
#define ICMPV6STAT(counter)                     \
          NETSTAT_LOCK(&icmp6stat.icmp6s_lock); \
          icmp6stat.counter;			\
          NETSTAT_UNLOCK(&icmp6stat.icmp6s_lock)

extern int icmp6_mgm_timers_active;

/*
 * Compute random number of fast timer "ticks" between 1 and the number of 
 * ticks in _maxdelay_ milliseconds ((_maxdelay_) * PR_FASTHZ / 1000).
 * Note that things get a little fuzzy for values of _maxdelay_ close
 * to the fast timer granularity.  For values of _maxdelay_ that equate
 * to less than two clock ticks ((1000/PR_FASTHZ)*2)), the delay is set 
 * to one clock tick, which may cause us to exceed _maxdelay_ milliseconds
 * (the next clock tick could be anytime within the next 200 milliseconds).
 */

#define ICMPV6_MGM_RANDOM_DELAY(_maxdelay_) \
	(((_maxdelay_) < ((1000/PR_FASTHZ)*2)) ? 1 : \
	 (1 + (in6_random() % ((_maxdelay_) * PR_FASTHZ / 1000))))

                   
/* data structures associated with rate limiting */
struct  icmp6_tx_errlog_cache {
	struct in6_addr icmp6_tx_src; /* source of packet causing this error */
	int    icmp6_npkts;	      /* number of packets attempted before 
				       * rate limiting was applied
				       */
	long   icmp6_lbolt_last_att;  /* lbolt at last attempted send */
	long   icmp6_lbolt_last_act;  /* lbolt at last actual send */
	long   icmp6_lbolt_dt;        /* number of ticks where no actual send
				       * is to be allowed 
				       */
	struct icmp6_tx_errlog_cache *icmp6_log_next;
};

#endif /* _KERNEL */

#endif /* _ICMP6_VAR_H_ */
