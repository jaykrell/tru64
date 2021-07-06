/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip6_rlimit.h,v $
 * Revision 1.1.9.1  2003/09/23  22:00:35  Brian_Haley
 * 	Mobile IPv6 update.
 * 	This file contains generic rate-limiting structures.
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ip6_rlimit.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2003/09/23 22:00:35 $
 */

#ifndef _NETINET_IP6_RLIMIT_H_
#define _NETINET_IP6_RLMIIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <netinet/in6.h>

/* IPv6 Rate limiting.
 * Send out 1 packet every T ms. Each time an ip6 error  is sent out 
 * We will actually send the error out on the wire only if the 
 * [current time] > [time of lastactual send] + [dt], where dt is
 * computed at each actual send as
 * dt at the i-th send = MIN(ik, T).
 * i.e., dt is incremented at each send attempt by an increment of k ms 
 * for each actual send, and dt is upper-bounded to T ms.
 * In addition, dt is decremented by k ms for each time interval  of 
 * T ms where there has  been no send attempt.
 * 
 * The maximum rate at which errors will be sent is 1/k packets per ms.
 * The minimum rate at which errors are sent is 1/T packets per ms.
 */

/* 
 * use the least-significant  4 bits of the address to find the hash bucket 
 * IP6_TX_ERRLOG_MAX_HASH should be 1 more than the max value returnable
 * by IP6_TX_ERRLOG_HASH()
 */

#define IP6_TX_ERRLOG_HASH(a)  (htonl((a)->s6_laddr[3]) & ((u_int64_t)0x0f))
#define IP6_TX_ERRLOG_MAX_HASH  0x10

#define IP6_RLIMIT_ENABLE 1
#define IP6_RLIMIT_NTOL 10

/* New Generic data structure used for the rate limiting cache */

struct ip6_tx_errlog_cache {
	struct	in6_addr ip6_tx_src;	/* source of packet causing this error */
	int	ip6_npkts;		/* number of packets attempted before
					 * rate limiting was applied
					 */
	long	ip6_lbolt_last_att;	/* lbolt at last attempt send */
	long	ip6_lbolt_last_act;	/* lbolt at last actual send */
	long	ip6_lbolt_dt;		/* number of ticks where no actual send
					 * is to be allowed
					 */

	struct	ip6_tx_errlog_cache *ip6_log_next;
};

/*
 * Rate limiting structure containing important config settings as well as the
 * cache of src addresses currently being rate limited
 */

struct ip6_tx_errlog {
	int	ip6_rlimit_enable;	/* toggle switch for rate limiting */
	int	ip6_rlimit_ntol;	/* start rate limit timers after ntol packets */

	long	ip6_lbolt_T;		/* lbolt value for ip6_rlimit_T and ms */
	long	ip6_lbolt_k;		/* lbolt value for icmp6_rlimit_K and ms */
	long	last_cleanup;		/* last time (in lbolts) of garbage collection */

	struct ip6_tx_errlog_cache *errlog_cache[IP6_TX_ERRLOG_MAX_HASH];
#if NETSYNC_LOCK
	ndecl_lock_data(, ip6_tx_errlog_lock)	/* lock for errlog cache */
#endif

};

/*
 * the IP6_TX_ERRLOG_LOCK protects ip6_tx_errlog[]
 */
#if NETSYNC_LOCK
ndecl_lock_info(extern, ip6_tx_errlog_li)
#define IP6_TX_ERRLOG_LOCKINIT(errlog)    ulock_setup( \
						&(errlog)->ip6_tx_errlog_lock, \
						ip6_tx_errlog_li,\
                                        	TRUE)
#define IP6_TX_ERRLOG_LOCK(errlog)        ulock_write( \
						&(errlog)->ip6_tx_errlog_lock)
#define IP6_TX_ERRLOG_UNLOCK(errlog)      ulock_done( \
						&(errlog)->ip6_tx_errlog_lock)
#define IP6_TX_ERRLOG_ISLOCKED(errlog)    (lockmode==0 || \
                                           simple_lock_holder( \
						&(errlog)->ip6_tx_errlog_lock))
#else
#define IP6_TX_ERRLOG_LOCKINIT(errlog)
#define IP6_TX_ERRLOG_LOCK(errlog)
#define IP6_TX_ERRLOG_UNLOCK(errlog)
#define IP6_TX_ERRLOG_ISLOCKED(errlog)
#endif /* NETSYNC_LOCK */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _NETINET_IP6_RLIMIT_H_ */

 

