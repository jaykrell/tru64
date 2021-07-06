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
 * @(#)$RCSfile: nd6_cache.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2000/01/20 17:42:55 $
 */

#ifndef _ND6_CACHE_H
#define _ND6_CACHE_H

#include <net/route.h>
#include <net/if.h>
#include <kern/lock.h>

#ifdef _KERNEL

typedef struct rtentry  nd6_cache_t;
#if NETSYNC_LOCK
ndecl_lock_info(extern, if6_nd6_cache_li)
#endif /* NETSYNC_LOCK */

#else
/* !defined(_KERNEL) */
typedef void nd6_cache_t;

#endif /* _KERNEL */

/* 
 * Even though the structures below are exposed outside _KERNEL
 * they are subject to change.
 */

struct nd6_llinfo_qh {
    struct nd6_llinfo *li_head;
    struct nd6_llinfo *li_tail;
};

struct nd6_cache_listhead {
        struct radix_node_head nd6_cache_head;
	long   reserved[3];
	lock_data_t nd6_cache_lock;   /* protects nd6_cache_listhead*/
	struct nd6_llinfo_qh nd6_incomplete;
	struct nd6_llinfo_qh nd6_reachable;
	struct nd6_llinfo_qh nd6_stale;
	struct ifqueue nd6_cache_unreachable_ifq;
	int    nd6_cache_num_stale;
};


#ifdef _KERNEL
#define IF6_ND6_CACHE(if6) &(((struct nd6_cache_listhead *)\
				((if6)->if6_nd6_cache_head))->nd6_cache_head)
#define IF6_ND6_CACHE_LOCK(if6) (((struct nd6_cache_listhead *)\
				 ((if6)->if6_nd6_cache_head))->nd6_cache_lock)
#define IF6_ND6_INCOMPLETE(if6) (((struct nd6_cache_listhead *)\
                                  ((if6)->if6_nd6_cache_head))->nd6_incomplete)
#define IF6_ND6_REACHABLE(if6) (((struct nd6_cache_listhead *)\
                                  ((if6)->if6_nd6_cache_head))->nd6_reachable)
#define IF6_ND6_STALE(if6) (((struct nd6_cache_listhead *)\
                                  ((if6)->if6_nd6_cache_head))->nd6_stale)
#define IF6_ND6_UNREACH_IFQ(if6) (((struct nd6_cache_listhead *)\
                        ((if6)->if6_nd6_cache_head))->nd6_cache_unreachable_ifq)

#define IF6_ND6_CACHE_NUM_STALE(if6) (((struct nd6_cache_listhead *)\
                        ((if6)->if6_nd6_cache_head))->nd6_cache_num_stale)

#define ND6_CACHE_LLINFO(n) ((struct nd6_llinfo *)((struct rtentry *)(n))->rt_llinfo)

#define ND6_TIMER(n) (((struct rtentry *)(n))->rt_expire)
#define ND6_CACHE_REF(x)  ROUTE_INC_REFCNT(*((struct rtentry *)(x)))
#define ND6_CACHE_UNREF(x) if (ROUTE_DEC_REFCNT(*((nd6_cache_t *)(x))) <= 1)\
				(*ipv6_swtab->nd6_cache_free)\
						((struct rtentry *)(x))

/* check sa_family in case  AF_INET usage of rt_llinfo  changes */
#define ND6_PREC(rt) ((rt_key((rt))->sa_family == AF_INET6 &&\
			 rt->rt_flags == RTF_GATEWAY && rt->rt_llinfo)  \
			 ? ((struct rtentry *)(rt->rt_llinfo))->rt_precedence \
			 : rt->rt_precedence);

			
#if NETSYNC_LOCK
#define IF6_ND6_CACHE_LOCKINIT(if6)    ulock_setup(&IF6_ND6_CACHE_LOCK(if6), \
				                     if6_nd6_cache_li, TRUE)
#define IF6_ND6_CACHE_READ_LOCK(if6)   ulock_read(&IF6_ND6_CACHE_LOCK(if6)) 
#define IF6_ND6_CACHE_WRITE_LOCK(if6)  ulock_write(&IF6_ND6_CACHE_LOCK(if6))
#define IF6_ND6_CACHE_UNLOCK(if6)      ulock_done(&IF6_ND6_CACHE_LOCK(if6))
#define IF6_ND6_CACHE_WRITETOREAD_LOCK(if6) \
			               ulock_write_to_read(\
					         &IF6_ND6_CACHE_LOCK(if6))
#define IF6_ND6_CACHE_LOCKTERMINATE(if6) ulock_terminate(\
					         &IF6_ND6_CACHE_LOCK(if6))
#define IF6_ND6_CACHE_ISLOCKED(if6)   (lockmode==0 || \
				      lock_holder(&IF6_ND6_CACHE_LOCK(if6)))
#else /* NETSYNC_LOCK */

#define IF6_ND6_CACHE_INIT(if6) 
#define IF6_ND6_CACHE_READ_LOCK(if6) 
#define IF6_ND6_CACHE_WRITE_LOCK(if6)
#define IF6_ND6_CACHE_UNLOCK(if6) 
#define IF6_ND6_CACHE_WRITETOREAD_LOCK(if6) 
#define IF6_ND6_CACHE_LOCKTERMINATE(if6) 
#define IF6_ND6_CACHE_ISLOCKED(if6)
#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */

#endif /* _ND6_CACHE_H */
