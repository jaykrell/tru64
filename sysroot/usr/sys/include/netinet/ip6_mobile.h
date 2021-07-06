/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip6_mobile.h,v $
 * Revision 1.1.18.5  2007/07/04  02:58:55  Akshay_Nesari
 * 	Added MBC_SEND_NA cache entry flag.
 *
 * Revision 1.1.18.4  2004/02/04  18:59:30  John_Dustin
 * 	Changed MIP6_CACHE_READ_TO_WRITE_LOCK() to not call
 * 	lock_read_to_write() when lockmode=0 to avoid a panic.
 * 	Also, define it to zero if NETSYNC_LOCK is not defined.
 * 	Fix for QAR 97517.
 *
 * Revision 1.1.18.3  2003/11/26  15:17:00  Brian_Haley
 * 	Fixed TAHI conformance problem where we were sending Binding
 * 	Ack responses to the care-of address instead of the original
 * 	IPv6 source address from the incoming packet when an alternate
 * 	care-of address was used.  This required adding an mbc_src
 * 	element to the mip6_binding_cache structure to hold the address.
 *
 * Revision 1.1.18.2  2003/11/13  22:42:51  Brian_Haley
 * 	Corrected a couple of problems from last submit:
 * 	- added an arg to MIP6_CACHE_UNREF() to tell mi6p_cache_free()
 *   that the caller is already holding the route lock
 * 	- added a per-binding cache entry spin lock to aid in lock miss rates
 *   during heavy i/o periods where the binding cache is having a lot of
 *   entries added and deleted
 * 	- added read-to-write locking macros necessary for scalability work,
 *   along with an "invalid" flag bit
 *
 * Revision 1.1.18.1  2003/09/23  22:00:32  Brian_Haley
 * 	Mobile IPv6 update.
 * 	Draft 22 updates:
 * 	- updated to support "ghost" binding cache entries w/MBC_GHOST flag
 *   and statistic
 * 	- added home and care-of nonce index elements to binding cache
 * 	Draft 21 updates:
 * 	- removed mbc_max_lifetime from binding cache structure and replaced
 *   with mbc_ba_status to hold the last Binding Ack status we sent to
 *   the MN
 * 	- removed MBC_DAD_FAILED flag as it is no longer needed with the
 *   above change
 * 	- changed constant names to match draft
 * 	- added mpe_preferred_lifetime to prefix entry structure
 * 	- added mobileipv6_bradvice_interval extern definition
 * 	- added BU status/failure macros
 * 	Changed lifetimes to be 32-bit quantities since USHRT_MAX * 4
 * 	is the maximum value.  Removed infinite lifetime.
 * 	Commented-out 56 bytes of padding in the mip6_prefix_entry struct.
 * 	Updated structures to support draft 18:
 * 	- Added a 'home' and 'cn' entry counter to the binding cache head
 *   structure so the reverse tunneling code would have better performance
 * 	- Created a mip6stat structure and associated lock to hold all the
 *   protocol statistics for Mobile IPv6
 * 	- Changed the binding cache from using two fixed address pointers to be
 *   a linked-list of proxy addresses so we could support S=0, and created
 *   a new structure (mip6_proxy_addr) to hold the info
 * 	- Added a "max lifetime" element to the binding cache to hold the
 *   maximum possible lifetime for a binding (eg. the max of all the proxy
 *   addresses we added)
 * 	- Added a flags field to the prefix entry structure so we could have
 *   some prefixes marked as "home agent capable" and others not
 * 	- Added tunnel encapsulation mbuf entry in binging cache
 * 	- Added prefix list address structures, macros and lock
 * 	ETSI bug fixes:
 * 	- changed lifetimes to be in 64-bit quantities since this is now
 *   allowed by BU (16-bit * 4 seconds)
 * 	- shrunk size of some of the statistics histogram arrays to keep
 *   the size under 8K
 * 	- fixed MIP6_SEQ_GT macro since sequence number is 16 bits again
 * 	- added hash structure definition and macros
 * 	- added max binding cache entries stat
 * 	- added mbc_flags field to binding cache data structure and shrunk
 *   mbc_num_dad_in_progress so that the DAD stop code can signal the
 *   timer thread to send a Binding Ack
 * 	Rate limiting:
 * 	- added rate limiting support
 * 	- added stats for binding error and rate limiting
 * 	RR:
 * 	- added mip6_debug_hexdump macro to dump out a hex string for
 *   debugging purposes.
 * 	Other:
 * 	- added MIP6_ANY_ACTIVE, MIP6_HOMEAGENT_ACTIVE, and
 *   MIP6_CORRESPONDENT_ACTIVE macros
 *
 * Revision 1.1.10.2  2002/01/17  20:41:33  Brian_Haley
 * 	Updated to support Mobile IPv6 draft 15 - prefixlen removed,
 * 	seqno reduced to 8 bits (qar 91336).
 *
 * Revision 1.1.10.1  2001/12/17  20:55:21  Vladislav_Yasevich
 * 	Initial revision
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: ip6_mobile.h,v $ $Revision: 1.1.18.5 $ (DEC) $Date: 2007/07/04 02:58:55 $
 */

/*
 * This file contains data structures, definitions and macros needed for
 * Mobile IPv6 functionality.
 */

#ifndef _NETINET_IP6_MOBILE_H_
#define _NETINET_IP6_MOBILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <net/route.h>
#include <netinet/in6.h>

/*
 * Mobile IPv6 proxy address structure
 */
struct mip6_proxy_addr {
	struct mip6_proxy_addr *mpa_next;	/* next entry */
	struct in6_localaddr *mpa_la6;		/* ptr to in6_localaddr */
};

typedef struct mip6_proxy_addr mip6_proxy_t;


/*
 * Mobile IPv6 binding cache structure
 */
/*
 * alignment:
 *	next (8)
 *	us (8)
 *	home (16)
 *	coa (16)
 *	refcnt (4) | DAD (2) | flags (2)
 *	pad (8)
 *
 *	nh (8)
 *	stamp (8)
 *	rthdr (8)
 *	tunhdr (8)
 *	proxy addrs (8)
 *	flags (2) | seqno (2) | lifetime (4)
 *	last BAck status (1) | padding (3) | hni (2) | cni (2)
 *	spin lock (8)
 *
 *	-------------------------------------
 *	|               next                |
 *	-------------------------------------
 *	|                us                 |
 *	-------------------------------------
 *	|               home                |
 *	|                                   |
 *	-------------------------------------
 *	|                coa                |
 *	|                                   |
 *	-------------------------------------
 *	|     refcnt      |   DAD  | flags  |
 *	-------------------------------------
 *	|                pad                |
 *	-------------------------------------
 *	-------------------------------------
 *	|                nh                 |
 *	-------------------------------------
 *	|               stamp               |
 *	-------------------------------------
 *	|               rthdr               |
 *	-------------------------------------
 *	|               tunhdr              |
 *	-------------------------------------
 *	|            proxy addrs            |
 *	-------------------------------------
 *	| flags  | seqno  |    lifetime     |
 *	-------------------------------------
 *	|back|  padding   |  hni   |  cni   |
 *	-------------------------------------
 *	|             spin lock             |
 *	-------------------------------------
 */
struct mip6_binding_cache {
	struct mip6_binding_cache *mbc_next;	/* next entry */
	struct rtentry *mbc_route;		/* our(selves) route */
	struct in6_addr mbc_home;		/* Home address */
	struct in6_addr mbc_coa;		/* Care-of address */
	u_int mbc_refcnt;			/* # held references */
	u_short mbc_flags;			/* flags, see below */
	u_short mbc_num_dad_in_progress;	/* # of DADs in progress */
	struct in6_addr mbc_src;		/* Source address */

	/* cache line */
	struct rtentry *mbc_nh_route;		/* next-hop route */
	u_long mbc_nh_timestamp;		/* next-hop route timestamp */
	struct mbuf *mbc_rthdr;			/* cached routing header */

	struct mbuf *mbc_tunhdr;		/* cached tunnel header, if HA*/
	struct mip6_proxy_addr *mbc_proxy_addrs;/* cached address(es), if HA */

	/* below are values stored from Binding Update */
	uint16_t mbc_bu_flags;			/* flags from BU */
	uint16_t mbc_bu_seqno;			/* sequence # from BU */
	uint32_t mbc_bu_lifetime;		/* lifetime of BU, in seconds */

	uint8_t mbc_ba_status;			/* status sent in last BAck */

	uint8_t mbc_pad8[3];			/* padding */

	uint16_t mbc_hni;			/* last home nonce index */
	uint16_t mbc_cni;			/* last care-of nonce index */

#if NETSYNC_LOCK
	simple_lock_data_t mbc_spin_lock;
#endif
};

typedef struct mip6_binding_cache mip6_cache_t;

/*
 * Mobile IPv6 cache entry flags
 */
#define MBC_SEND_ACK		0x8000		/* Binding Ack required */
#define MBC_GHOST		0x4000		/* "ghost" entry */
#define MBC_INVALID		0x2000		/* entry is invalid */
#define MBC_SEND_NA		0x1000
/*
 * Mobile IPv6 binding cache head structure
 */
struct mip6_binding_cache_head {
	mip6_cache_t **mbch_hashtable;	/* pointer to hash table */
	u_long mbch_num_entries;	/* number of entries in list */
	u_long mbch_num_maxentries;	/* max number of entries ever in list */
	u_long mbch_num_homeentries;	/* number of home entries in list */
	u_long mbch_num_cnentries;	/* number of correspondent entries */
	u_long mbch_num_ghostentries;	/* number of "ghost" entries */
	u_long mbch_num_adds;		/* number of "add" ops performed */
	u_long mbch_num_deletes;	/* number of "delete" ops performed */
	u_long mbch_num_changes;	/* number of "change" ops performed */
	u_long mbch_num_frees;		/* number of "free" ops performed */
	u_long mbch_num_lookups;	/* number of "lookup" ops performed */
};

#define MIP6_BCACHE_MAXLIFETIME	(USHRT_MAX * 4)	/* max lifetime is 262140 sec */

/*
 * This is the maximum lifetime if using Return Routability (Draft Section 12)
 */
#define MAX_RR_BINDING_LIFETIME		420


/*
 * Mobile IPv6 prefix list structure
 */
/*
 * alignment:
 *	next (8)
 *	prev (8)
 *	prefix (16)
 *	prefix mask (16)
 *	if6 (8)
 *	refcnt (4) | flags (2) | prefix length (2)
 *	valid lifetime (4) | preferred lifetime (4)
 *	pad (56)
 *
 *	-------------------------------------
 *	|               next                |
 *	-------------------------------------
 *	|               prev                |
 *	-------------------------------------
 *	|              prefix               |
 *	|                                   |
 *	-------------------------------------
 *	|           prefix mask             |
 *	|                                   |
 *	-------------------------------------
 *	|               if6                 |
 *	-------------------------------------
 *	|     refcnt      | flags  |plen|pad|
 *	-------------------------------------
 *	-------------------------------------
 *	|      valid      |    preferred    |
 *	-------------------------------------
 *	|                pad                |
 *	|                                   |
 *	|                                   |
 *	|                                   |
 *	|                                   |
 *	|                                   |
 *	|                                   |
 *	-------------------------------------
 */
struct mip6_prefix_entry {
	struct mip6_prefix_entry *mpe_next;	/* next entry */
	struct mip6_prefix_entry *mpe_prev;	/* previous entry */
	struct in6_addr mpe_prefix;		/* Prefix */
	struct in6_addr mpe_prefix_mask;	/* Prefix mask */
	struct in6_ifnet *mpe_if6;		/* interface */
	u_int mpe_refcnt;			/* # held references */
	u_int16_t mpe_flags;			/* flags, see below */
	u_int8_t mpe_prefix_len;		/* Prefix length */
	u_int8_t mpe_pad;			/* padding */

	/* cache line */
	u_int32_t mpe_valid_lifetime;		/* Valid prefix lifetime */
	u_int32_t mpe_preferred_lifetime;	/* Preferred prefix lifetime */
#if 0
	/* 56 bytes of padding is unnecessary, leaving as placeholder */
	u_long mpe_lpad[7];			/* padding */
#endif
};

typedef struct mip6_prefix_entry mip6_prefix_t;

/*
 * Mobile IPv6 prefix entry flags
 */
#define MIP6_PREFIX_HOME	0x8000		/* Home Agent for prefix */

/*
 * Mobile IPv6 prefix list head structure
 */
struct mip6_prefix_list_head {
	mip6_prefix_t *mplh_first;	/* pointer to first entry */
	u_long mplh_num_entries;	/* number of entries in list */
	u_long mplh_num_homeentries;	/* number of home entries in list */
	u_long mplh_num_adds;		/* number of "add" ops performed */
	u_long mplh_num_deletes;	/* number of "delete" ops performed */
	u_long mplh_num_changes;	/* number of "change" ops performed */
	u_long mplh_num_frees;		/* number of "free" ops performed */
	u_long mplh_num_lookups;	/* number of "lookup" ops performed */
};

/*
 * Mobile IPv6 statistics
 */
struct mip6stat {
    u_long	mip6s_rx_total;		/* total # MIPv6 packets received */
    u_long	mip6s_rx_tooshort;	/* packet < MH min */
    u_long	mip6s_rx_unktype;	/* bad MIPv6 MH type */
    u_long	mip6s_rx_proto;		/* bad MIPv6 payload proto */
    u_long	mip6s_rx_checksum;	/* bad MIPv6 checksum */

    u_long	mip6s_hao_toomany;	/* > 1 HAO in packet */
    u_long	mip6s_hao_badaddr;	/* HAO with invalid address */
    u_long	mip6s_hao_unverified;	/* HAO without binding (or IPSec) */

    u_long	mip6s_rx_hist[64];	/* receive count by type */
    u_long	mip6s_tx_hist[64];	/* send count by type */

    u_long	mip6s_tx_rlimit_drops;	/* total dropped by rate limiting */

    u_long	mip6s_bu_errors;	/* total of all BU errors */
    u_long	mip6s_bu_tooshort;	/* BU < BU minimum length */
    u_long	mip6s_bu_nohao;		/* BU without Home Address Option */
    u_long	mip6s_bu_badaddr;	/* BU with invalid CoA or HoA */
    u_long	mip6s_bu_notenabled;	/* BU but Mobile IPv6 not enabled */
    u_long	mip6s_bu_badseqno;	/* BU with bad sequence number */
    u_long	mip6s_bu_noipsec;	/* BU but no IPsec when necessary */
    u_long	mip6s_bu_rrfailed;	/* BU but Return Routability failed */
    u_long	mip6s_bu_badoption;	/* BU with bad mobility option */
    u_long	mip6s_bu_hanotenabled;	/* BU but Home Agent not enabled */
    u_long	mip6s_bu_notha;		/* BU but not Home Agent for MN */
    u_long	mip6s_bu_deletefailed;	/* BU could not be deleted */
    u_long	mip6s_bu_nobinding;	/* BU but no binding for MN */
    u_long	mip6s_bu_addfailed;	/* BU could not be added */
    u_long	mip6s_bu_updatefailed;	/* BU could not be updated */
    u_long	mip6s_bu_cachelimit;	/* BU dropped because cache full */

    u_long	mip6s_ba_hist[256];	/* BAck count by status */

    u_long	mip6s_be_hist[16];	/* BE count by status */

    u_long	mip6s_hoti_errors;	/* total of all HoTI errors */
    u_long	mip6s_hoti_tooshort;	/* HoTI < HoTI minimum length */
    u_long	mip6s_hoti_hao;		/* HAO was present */

    u_long	mip6s_coti_errors;	/* total of all CoTI errors */
    u_long	mip6s_coti_tooshort;	/* CoTI < CoTI minimum length */
    u_long	mip6s_coti_hao;		/* HAO was present */

    u_long	mip6s_encap_success;	/* pkts encapsulated successfully */
    u_long	mip6s_encap_enobufs;	/* pkts dropped, congestion */
    u_long	mip6s_encap_noroute;	/* pkts dropped, dst unreachable */
    u_long	mip6s_encap_other;	/* pkts dropped, other error */

    u_long	mip6s_rtun_success;	/* pkts reverse-tunneled from MN */
    u_long	mip6s_rtun_failed;	/* pkts !reverse-tunneled from MN */

#if defined(_KERNEL) && LOCK_NETSTATS
    simple_lock_data_t	mip6s_lock;		/* statistics lock */
#endif
};


/*
 * Kernel-specific stuff
 */
#ifdef _KERNEL

extern struct mip6stat mip6stat;
#define MIP6STAT(counter)			\
	  NETSTAT_LOCK(&mip6stat.mip6s_lock);	\
	  mip6stat.counter;			\
	  NETSTAT_UNLOCK(&mip6stat.mip6s_lock)

/*
 * Binding cache macros
 */
#define MIP6_INC_REFCNT(mip6) (atomic_incl(&((mip6).mbc_refcnt)))
#define MIP6_DEC_REFCNT(mip6) (atomic_decl(&((mip6).mbc_refcnt)))

#define MIP6_CACHE_REF(mip6)	MIP6_INC_REFCNT(*(mip6))

/*
 * NOTE: atomic_decl() returns the *original* value given to it, so
 *	 the check below is one higher than you think...
 */
#define MIP6_CACHE_UNREF(mip6, lock_held)	\
	if (MIP6_DEC_REFCNT(*(mip6)) <= 1) \
		(*ipv6_swtab->mip6_cache_free)((mip6), (lock_held))

#define MIP6_NH_TIMESTAMP(mip6)	((mip6)->mbc_nh_timestamp = route6_timestamp)
#define MIP6_NH_TIMESTAMP_INVALID(mip6)	\
	((mip6)->mbc_nh_timestamp != route6_timestamp)

/* this is a modulo 2^^16 comparison */
#define MIP6_SEQ_GT(s1, s2)	((short)((s1) - (s2)) > 0)

/* the list entry sits off the rtentry */
#define MIP6_CACHE_P(rt)		(rt)->rt_mip6cache

/*
 * Binding cache hash macros
 */
/*
 * Hash macro given 128-bit in6_addr as a key returns bucket index
 * for table size (1 << mip6bcache_hexp), identical copy of the
 * IN6_LOCALADDR_HASH() macro.  We simply hash over the lower 32 bits
 * since Ethernet MAC addresses are already pretty unique.
 */
#define MIP6_BCACHE_HASH(_dst_, _hb_)				\
    {								\
	int _i_;						\
	(_hb_) = (_dst_)->s6_laddr[3];				\
	for (_i_ = mip6_bcache_hexp; _i_ < 32; _i_ += mip6_bcache_hexp)\
	     (_hb_) += ((_dst_)->s6_laddr[3] >> _i_);		\
	(_hb_) &= mip6_bcache_hmask;				\
    }
#define _MIP6_BCACHE_HASH_ENABLED()	(mip6_bcache_hexp > 0)

/*
 * Prefix list macros
 */
#define MIP6_INC_PE_REFCNT(mpe) (atomic_incl(&((mpe).mpe_refcnt)))
#define MIP6_DEC_PE_REFCNT(mpe) (atomic_decl(&((mpe).mpe_refcnt)))

#define MIP6_PREFIX_REF(mpe)	MIP6_INC_PE_REFCNT(*(mpe))

/*
 * NOTE: atomic_decl() returns the *original* value given to it, so
 *	 the check below is one higher than you think...
 */
#define MIP6_PREFIX_UNREF(mpe)	\
	if (MIP6_DEC_PE_REFCNT(*(mpe)) <= 1) \
		mip6_prefix_free((mpe))


#if NETSYNC_LOCK

ndecl_lock_data(extern, mip6_cache_lock)
#define MIP6_CACHE_LOCKINIT()	ulock_setup(&mip6_cache_lock, mip6_cache_li, TRUE)
#define MIP6_CACHE_READ_LOCK()		ulock_read(&mip6_cache_lock)
#define MIP6_CACHE_WRITE_LOCK()		ulock_write(&mip6_cache_lock)
#define MIP6_CACHE_READ_TO_WRITE_LOCK() (lockmode == 0 || \
				lock_read_to_write(&mip6_cache_lock))
#define MIP6_CACHE_UNLOCK()		ulock_done(&mip6_cache_lock)
#define MIP6_CACHE_ISLOCKED()		(lockmode == 0 || 1)

ndecl_lock_data(extern, mip6_prefix_lock)
#define MIP6_PREFIX_LOCKINIT()	ulock_setup(&mip6_prefix_lock, mip6_prefix_li, TRUE)
#define MIP6_PREFIX_READ_LOCK()		ulock_read(&mip6_prefix_lock)
#define MIP6_PREFIX_WRITE_LOCK()	ulock_write(&mip6_prefix_lock)
#define MIP6_PREFIX_UNLOCK()		ulock_done(&mip6_prefix_lock)
#define MIP6_PREFIX_ISLOCKED()		(lockmode == 0 || 1)

extern simple_lock_data_t mip6_dad_spin_lock;
#define MIP6_DAD_SPIN_LOCKINIT()	simple_lock_setup(&mip6_dad_spin_lock, mip6_dad_spin_li)
#define MIP6_DAD_SPIN_LOCK()		simple_lock(&mip6_dad_spin_lock)
#define MIP6_DAD_SPIN_UNLOCK()		simple_unlock(&mip6_dad_spin_lock)
#define MIP6_DAD_SPIN_ISLOCKED()	(lockmode==0||simple_lock_holder(&mip6_dad_spin_lock)

#define MIP6_MBC_SPIN_LOCKINIT(mbce)	simple_lock_setup(&((mbce)->mbc_spin_lock), mip6_mbc_spin_li)
#define MIP6_MBC_SPIN_LOCKTERMINATE(mbce)	simple_lock_terminate(&((mbce)->mbc_spin_lock))
#define MIP6_MBC_SPIN_LOCK(mbce)	simple_lock(&((mbce)->mbc_spin_lock))
#define MIP6_MBC_SPIN_UNLOCK(mbce)	simple_unlock(&((mbce)->mbc_spin_lock))
#define MIP6_MBC_SPIN_ISLOCKED(mbce)	(lockmode==0||simple_lock_holder(&((mbce)->mbc_spin_lock))

#else /* NETSYNC_LOCK */

#define MIP6_CACHE_LOCKINIT()
#define MIP6_CACHE_READ_LOCK()
#define MIP6_CACHE_WRITE_LOCK()
#define MIP6_CACHE_READ_TO_WRITE_LOCK()	0
#define MIP6_CACHE_UNLOCK()
#define MIP6_CACHE_ISLOCKED()		1

#define MIP6_PREFIX_LOCKINIT()
#define MIP6_PREFIX_READ_LOCK()
#define MIP6_PREFIX_WRITE_LOCK()
#define MIP6_PREFIX_UNLOCK()
#define MIP6_PREFIX_ISLOCKED()		1

#define MIP6_DAD_SPIN_LOCKINIT()
#define MIP6_DAD_SPIN_LOCK()
#define MIP6_DAD_SPIN_UNLOCK()
#define MIP6_DAD_SPIN_ISLOCKED()	1

#define MIP6_MBC_SPIN_LOCKINIT(mbce)
#define MIP6_MBC_SPIN_LOCKTERMINATE(mbce)
#define MIP6_MBC_SPIN_LOCK(mbce)
#define MIP6_MBC_SPIN_UNLOCK(mbce)
#define MIP6_MBC_SPIN_ISLOCKED(mbce)	1

#endif /* NETSYNC_LOCK */

extern int mobileipv6_configured;
extern REPLICATED int mobileipv6_enabled;
extern REPLICATED int mobileipv6_homeaddress;
extern REPLICATED int mobileipv6_homeagent;
extern struct mip6_binding_cache_head mip6_bcache_head;
extern REPLICATED u_int mobileipv6_maxcachelifetime;
extern REPLICATED int mobileipv6_ipsec_allbindings;
extern REPLICATED int mobileipv6_ipsec_homebindings;
extern REPLICATED int mobileipv6_ipsec_allhamn;
extern REPLICATED int mobileipv6_ipsec_rrhamn;
extern REPLICATED int mobileipv6_rr_cnbindings;
extern REPLICATED int mip6isrrconfigured;
extern REPLICATED int mobileipv6_pmtu_enabled;
extern REPLICATED u_long mip6_timestamp;
extern struct mip6_prefix_list_head mip6_plist_head;
extern REPLICATED int mobileipv6_flush_bindings;
extern REPLICATED int mobileipv6_flush_prefixes;
extern REPLICATED u_int mobileipv6_maxbindings;
extern REPLICATED u_int mobileipv6_maxhomebindings;
extern REPLICATED u_int mobileipv6_bradvice_interval;
extern u_int mip6_bcache_hsize;
extern u_int mip6_bcache_hexp;
extern mip6_cache_t **old_mip6_hashtable;

/* Rate Limiting sysconfigurable params */
extern long mip6_rlimit_T;		/* ms */
extern long mip6_rlimit_k;		/* ms */

extern struct ip6_tx_errlog mip6_tx_errlog;

/*
 * Current debugging levels are:
 *
 *	0 = none
 *	1 = "simple" binding added/changed/deleted messages
 *	2 = #1 including IPv6 input (Home Address), binding lookups,
 *		binding update processing and simple routing header messages
 *	3 = #2 including more detailed routing header, mbuf and upper-layer
 *		caching messages
 *	4 = #3 including timer debugging
 *
 * All debugging levels above zero include Mobile IPv6 error messages.
 */
extern REPLICATED int mobileipv6_debug;

/*
 * MOBILEIPV6_DEBUG enables debugging printfs.  This effectively enforces
 * the maximum run-time setting of mobileipv6_debug.
 */
#if defined(_KERNEL) && !defined(__VMS)
#define MOBILEIPV6_DEBUG 3

/* HEX-dump the buffer.*/
#define mip6_debug_hexdump(buf, len) \
	do { \
		int __i; \
		for (__i = 0; __i < (len); __i++) {	\
			if (__i != 0 && __i % 32 == 0) printf("\n"); \
			if (__i % 4 == 0) printf(" "); \
			printf("%02x", (unsigned char)(buf)[__i]); \
		} \
		printf("\n"); \
	} while (0)

#endif /* (_KERNEL) && !defined(__VMS) */

/* Macros to increment, set and test the global mip6 cache timestamp */
#define INC_MIP6_TIMESTAMP() {				\
	u_long _stamp = mip6_timestamp + 1;		\
	write_const_data((void *)&_stamp,		\
			 (void *)&mip6_timestamp,	\
			 sizeof(u_long));		\
	}

#define OPT_MIP6_TIMESTAMP(opt)	((opt)->opt_mip6_timestamp = mip6_timestamp)
#define OPT_MIP6_TIMESTAMP_INVALID(opt) \
	((opt)->opt_mip6_timestamp != mip6_timestamp)

/* Macro to tell if we're "actively" doing any mobility */
#define MIP6_ANY_ACTIVE				\
	(mobileipv6_enabled &&			\
	 mip6_bcache_head.mbch_num_entries)

/* Macro to tell if we're an "active" home agent */
#define MIP6_HOMEAGENT_ACTIVE			\
	(mobileipv6_enabled &&			\
	 mobileipv6_homeagent &&		\
	 mip6_bcache_head.mbch_num_homeentries)

/* Macro to tell if we're an "active" correspondent node */
#define MIP6_CORRESPONDENT_ACTIVE		\
	(mobileipv6_enabled &&			\
	 mip6_bcache_head.mbch_num_cnentries)

/* Macro to tell if a BU status code is a "success" */
#define MIP6_BU_SUCCESS(code) ((code) < 128)

/* Macro to tell if a BU status code is a "failure" */
#define MIP6_BU_FAILURE(code) ((code) > 127)

#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _NETINET_IP6_MOBILE_H_ */
