/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mip6_rrsec.h,v $
 * Revision 1.1.9.2  2003/11/13  22:42:56  Brian_Haley
 * 	Added missing NETSYNC_LOCK around the mip6_rr_nonce struct lock.
 *
 * Revision 1.1.9.1  2003/09/23  22:00:48  Brian_Haley
 * 	Initial submission - Mobile IPv6.
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: mip6_rrsec.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 2003/11/13 22:42:56 $
 */

#ifndef _NETINET_MIP6_RRSEC_H_
#define _NETINET_MIP6_RRSEC_H_

#include <sys/types.h>
#include <kern/lock.h>
#include <netinet/in.h>

/*
 * Mobile IPv6 Keys
 */
struct mip6_rr_key {
	uint8_t  *mip6k_key;    /* Pointer to the key buffer */
       	uint8_t  mip6k_size;    /* size of the key buffer */
};
typedef struct mip6_rr_key mip6_key_t;

#define MIP6_RR_KCN_SIZE	20	/* Kcn is 20 bytes [Section 5.2.1] */
#define MIP6_RR_AUTHDATA_LEN	12	/* RR Authenticator is 96 bits */


/*
 * Mobile IPv6 Nonces (and Cookies)
 */

#define MIP6_RR_NONCE_SIZE	8      /* nonces are 64 bits */
#define MIP6_RR_NONCE_REGEN	30     /* seconds between nonce regeneration */
#define MIP6_RR_MAX_NONCE_LIFE	240	/* max seconds a nonce is valid */
#define MIP6_RR_MAX_NONCE_LIST	((MIP6_RR_MAX_NONCE_LIFE / MIP6_RR_NONCE_REGEN) \
				  + 1)  /* (240 / 8) + 1 = 9, (+1) for time skew */ 
#define MIP6_RR_TOKEN_SIZE	sizeof(uint64_t)	/* RR token size */
#define MIP6_RR_MAX_TOKEN_LIFE	210	/* max seconds a token is valid */

#define MIP6_RR_HOME_COOKIE_TAG		0	/* constant used to calculate home token */
#define MIP6_RR_CAREOF_COOKIE_TAG	1	/* constant used to calculate careof token */

/* nonce structure */
struct mip6_rr_nonce {
	uint8_t       mip6rrn_home_nonce[MIP6_RR_NONCE_SIZE];  /* 64bit nonce */
	uint8_t       mip6rrn_careof_nonce[MIP6_RR_NONCE_SIZE];  /* 64bit nonce */
	uint16_t      mip6rrn_index;     /* this nonces index */
	uint16_t      mip6rrn_state;     /* nonces state */
	uint32_t      mip6rrn_timeout;   /* when this nonce times out */
#if NETSYNC_LOCK
	lock_data_t   mip6rrn_lock;      /* a nonce lock */
#endif
};
typedef struct mip6_rr_nonce mip6_rr_nonce_t;

#define MIP6_RR_NONCE_EXPIRED      0	/* Nonce is expired, can replace */
#define MIP6_RR_NONCE_VALID        1	/* Nonce is valid */

#if _KERNEL
#if NETSYNC_LOCK

/* NONCE LIST LOCK */
ndecl_lock_data(extern, mip6_nonce_list_lock); 	    /* lock for nonce list */
ndecl_lock_info(extern, mip6_nonce_list_li)

#define MIP6_NONCE_LIST_LOCK_INIT()     ulock_setup(&mip6_nonce_list_lock, \
                                                    mip6_nonce_list_li, \
                                                    TRUE)
#define MIP6_NONCE_LIST_READ_LOCK()     ulock_read(&mip6_nonce_list_lock)
#define MIP6_NONCE_LIST_WRITE_LOCK()    ulock_write(&mip6_nonce_list_lock)
#define MIP6_NONCE_LIST_UNLOCK()        ulock_done(&mip6_nonce_list_lock)
#define MIP6_NONCE_LIST_LOCKTERM()      ulock_terminate(&mip6_nonce_list_lock)
#define MIP6_NONCE_LIST_ISLOCKED()      (lockmode==0 || \
                                         lock_holder(&mip6_nonce_list_lock))

/* NONCE LOCK */
ndecl_lock_info(extern, mip6_nonce_li)

#define MIP6_NONCE_LOCK_INIT(nonce)     ulock_setup(&(nonce)->mip6rrn_lock, \
                                                    mip6_nonce_li, \
                                                    TRUE)
#define MIP6_NONCE_READ_LOCK(nonce)     ulock_read(&(nonce)->mip6rrn_lock)
#define MIP6_NONCE_WRITE_LOCK(nonce)    ulock_write(&(nonce)->mip6rrn_lock)
#define MIP6_NONCE_UNLOCK(nonce)        ulock_done(&(nonce)->mip6rrn_lock)
#define MIP6_NONCE_LOCKTERM(nonce)	ulock_terminate(&(nonce)->mip6rrn_lock)
#define MIP6_NONCE_ISLOCKED(nonce)   	(lockmode==0 || \
                                         lock_holder(&(nonce)->mip6rrn_lock))

#else  /* NETSYNC_LOCK */

/* NONCE LIST LOCK MACROS */
#define MIP6_NONCE_LIST_LOCK_INIT()
#define MIP6_NONCE_LIST_READ_LOCK()
#define MIP6_NONCE_LIST_WRITE_LOCK()
#define MIP6_NONCE_LIST_UNLOCK()
#define MIP6_NONCE_LIST_LOCKTERM()
#define MIP6_NONCE_LIST_ISLOCKED()

/* NONCE LOCK MACROS */
#define MIP6_NONCE_LOCK_INIT(nonce)
#define MIP6_NONCE_READ_LOCK(nonce)
#define MIP6_NONCE_WRITE_LOCK(nonce)
#define MIP6_NONCE_UNLOCK(nonce)
#define MIP6_NONCE_LOCKTERM(nonce)
#define MIP6_NONCE_ISLOCKED(nonce)

#endif /* NETSYNC_LOCK */
#endif /* _KERNEL */

/*
 * PRIVATE DATA
 */

/* structure used to create the RR authenticator */
struct mip6_auth {
	const struct in6_addr	*mip6auth_coa;		/* Care-of address */
	const struct in6_addr	*mip6auth_cna;		/* CN address */
	struct mbuf	*mip6auth_msghdr;	/* mbuf containing the message*/
	u_int		mip6auth_hdroffset;	/* offset of message header */
	u_int		mip6auth_msglen;	/* total length of message */
	u_int		mip6auth_authoffset;	/* offset of Auth Data opt*/
	u_int		mip6auth_authlen;	/* length of authenticator */
	int		mip6auth_bindingdelete;	/* binding deletion flag */
};
typedef struct mip6_auth mip6_auth_t;

#endif /* _NETINET_MIP6_RRSEC_H_ */
