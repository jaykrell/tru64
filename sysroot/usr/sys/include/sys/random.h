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
 *
 * See additional Linux copyright information below.
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: random.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2001/09/27 20:29:52 $
 */
/*
 * Derived from Linux file include/linux/random.h 2.4.0-test9
 *
 * Version 1.89, last modified 19-Sep-99
 * 
 * Copyright Theodore Ts'o, 1994, 1995, 1996, 1997, 1998, 1999.  All
 * rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 * 
 * ALTERNATIVELY, this product may be distributed under the terms of
 * the GNU Public License, in which case the provisions of the GPL are
 * required INSTEAD OF the above restrictions.  (This clause is
 * necessary due to a potential bad interaction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
/*
 * Include file for /dev/random and kernel get_random_bytes().
 */

#ifndef _SYS_RANDOM_H_
#define _SYS_RANDOM_H_

#include <sys/ioctl.h>

/* Linux types
 */
#ifdef __arch64__
typedef unsigned long  __u64;
#else
#error need a 64bit data type here
#endif
typedef unsigned int   __u32;
typedef          int   __s32;
typedef unsigned short __u16;
typedef unsigned char  __u8;

/* ioctl()'s for the random number generator
 * Superuser only except Get entropy count
 */
#if 0		/* not currently supported -- use sysconfig on random subsystem */
#define RNDGETENTCNT	_IOR( 'R', 0x00, int )     /* Get the entropy count. */
#define RNDADDTOENTCNT	_IOW( 'R', 0x01, int )     /* Add to (or subtract from) the entropy count. */
#define RNDGETPOOL	_IOR( 'R', 0x02, int [2] ) /* Get the contents of the entropy pool. */
#define RNDADDENTROPY	_IOW( 'R', 0x03, int [2] ) /* Write bytes into the entropy pool and add to the entropy count. */
#define RNDZAPENTCNT	_IO( 'R', 0x04 )           /* Clear entropy count to 0. */
#define RNDCLEARPOOL	_IO( 'R', 0x06 )           /* Clear the entropy pool and associated counters. */

struct rand_pool_info {
	int	entropy_count;
	int	buf_size;
	__u32	buf[0];
};
#endif /* 0 */

#ifdef _KERNEL

/* these are the actual hook entrypoints
 * they are called via CALL_RANDOM_HOOK() so that the call
 * and any initialization code can be disabled as necessary
 */
extern void add_keyboard_randomness(__u32 scan_data);
extern void add_mouse_randomness(__u32 mouse_data);
extern void add_net_randomness(__u32 net_data);
extern void add_blkdev_randomness(__u32 blkdev_data);


/* this is the entry for the rest of the kernel to fetch randomness
 * get_random_bytes() will return the requested bytes regardless of how
 * much entropy is in the system.
 * get_random_bytes_wait() will wait until there is sufficient entropy
 * if necessary
 */
extern void get_random_bytes(void *buf, int nbytes);
extern void get_random_bytes_wait(void *buf, int nbytes);

/* structured random data
 */
void generate_random_uuid(unsigned char uuid_out[16]);

#if 0		/* the following are not currently supported */

/* IPV4 random data
 */
extern __u32 secure_ip_id(__u32 daddr);
extern __u32 secure_tcp_sequence_number(__u32 saddr, __u32 daddr,
					__u16 sport, __u16 dport);

/* IPV6 random data
 */
extern __u32 secure_ipv6_id(__u32 *daddr);
extern __u32 secure_tcpv6_sequence_number(__u32 *saddr, __u32 *daddr,
					  __u16 sport, __u16 dport);

/* secure TCP SYN cookie support
 */
extern __u32 secure_tcp_syn_cookie(__u32 saddr, __u32 daddr,
				   __u16 sport, __u16 dport,
				   __u32 sseq, __u32 count,
				   __u32 data);
extern __u32 check_tcp_syn_cookie(__u32 cookie, __u32 saddr,
				  __u32 daddr, __u16 sport,
				  __u16 dport, __u32 sseq,
				  __u32 count, __u32 maxdiff);
#endif /* 0 */

/* History to help estimate amount of randomness;
 * there is one of these per CPU per entropy source.
 */
struct random_timer_state {
#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
  unsigned int last_time;
  int last_delta, last_delta2;
#else
  unsigned int pad[3];
#endif
};

struct random_stats {
  ulong_t cur_keyboard;	/* temporary for timing keyboard hook */
  ulong_t ncalls_keyboard; /* number of calls */
  ulong_t cycles_keyboard; /* cumulative cycle count */
  ulong_t min_keyboard;	/* length of quickest call */
  ulong_t max_keyboard;	/* length of slowest call */
  ulong_t cur_mouse;	/* timings for mouse hook */
  ulong_t ncalls_mouse;
  ulong_t cycles_mouse;
  ulong_t min_mouse;
  ulong_t max_mouse;
  ulong_t cur_net;	/* timings for network hook */
  ulong_t ncalls_net;
  ulong_t cycles_net;
  ulong_t min_net;
  ulong_t max_net;
  ulong_t cur_blkdev;	/* timings for block device hook */
  ulong_t ncalls_blkdev;
  ulong_t cycles_blkdev;
  ulong_t min_blkdev;
  ulong_t max_blkdev;
  ulong_t pad[12];	/* make this a multiple of cache block size */
};

#define DEBUG_RANDOM_TIMINGS

#ifdef _BASE_KERNEL_PRIVATE /* see sys/systm.h - kernel binary compatibility */
#ifdef DEBUG_RANDOM_TIMINGS
/* NB: these timings will be of little use if other interrupts are
 * processed while we are in here -- probably not a problem for timing the
 * "off" case at least.
 */
#define RANDOM_TIME_START(which)			\
         do                                             \
           {						\
	    struct processor *pr = current_processor();	\
	    ++pr->ran_time.ncalls_##which;		\
	    pr->ran_time.cur_##which = -rpcc();		\
	   } while (0)

#define RANDOM_TIME_STOP(which)                                         \
         do                                                             \
           {							        \
	    struct processor *pr = current_processor();		        \
	    pr->ran_time.cur_##which    += rpcc();                      \
	    pr->ran_time.cycles_##which += pr->ran_time.cur_##which;	\
	    if (pr->ran_time.max_##which < pr->ran_time.cur_##which)	\
	      pr->ran_time.max_##which   = pr->ran_time.cur_##which;	\
	    if (pr->ran_time.cur_##which < pr->ran_time.min_##which)	\
	      pr->ran_time.cur_##which   = pr->ran_time.min_##which;	\
	   } while (0)

#else /* DEBUG_RANDOM_TIMINGS */

#define RANDOM_TIME_START(which)
#define RANDOM_TIME_STOP(which)

#endif /* DEBUG_RANDOM_TIMINGS */

/* this macro, and the unusual 3rd arg to CALL_RANDOM_HOOK() is so that CALL_RANDOM_HOOK()
 *  can have local variables/code that is skipped if we are not going to call the hook
 */
#define RANDOM_HOOK_DECL(block_init) block_init /* allow CALL_RANDOM_HOOK() to have local vars */

/* Compute entropy and call the apropriate random driver hook if this hook is
 * enabled
 *
 * The ran_do_net_hook, etc. flags are per-cpu modifiable data so that
 * the hooks can be turned on and off without the overhead of a write_const_data()
 *
 * The 3rd arg is either (;) or (decls; initcode; ... ) e.g.,
 * CALL_RANDOM_HOOK(net, _t1 ^ _t2,
 *                  (int _t1;
 *                   int _t2;
 *                   bcopy(src, &_t1, sizeof(_t1));
 *                   bcopy(dst, &_t2, sizeof(_t2));
 *                   ))
 *
 * Note: the third arg cannot have any , outside () since that would parse
 * as a second arg to RANDOM_HOOK_DECL(), thus the previous example cannot
 * be written: ... _t1 ^ _t2, (int _t2, _t2; bcopy...
 */
#define CALL_RANDOM_HOOK(which, data, block_init)		\
          do {							\
            RANDOM_TIME_START(which);                           \
            if (current_processor()->ran_do_##which##_hook)	\
	      {                                                 \
		RANDOM_HOOK_DECL block_init ;	                \
						                \
		add_##which##_randomness(data);	                \
	      }					                \
	    RANDOM_TIME_STOP(which);                            \
	  } while (0)

#endif /* _BASE_KERNEL_PRIVATE */


#endif /* __KERNEL__ */

#endif /* _SYS_RANDOM_H_ */
