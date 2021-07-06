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
 * @(#)$RCSfile: dyn_hash.h,v $ $Revision: 1.1.10.1 $ (DEC) $Date: 2001/06/19 21:41:41 $
 */

#ifndef _KERN_DYN_HASH_H_
#define _KERN_DYN_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <kern/e_dyn_hash.h>

/*
 * This is dictates the maximum size of the synamic hash table.
 * Each slot in the index table points to a segment of the dynamic
 * hash table that is twice the size of the segment in the previous
 * slot (except the first two slots). Thus a maximum hash table size
 * of (2**DYN_INDEX_TABLE_SIZE-1) * initial_size.
 */
#define DYN_INDEX_TABLE_SIZE 32

/*
 * This defines the number of message buffers available for sending a
 * message to the dynamic hashtable kernel thread. 
 */
#define DYN_MAX_MSG_Q_ENTRIES 128


#define DYN_THREAD_TIMEOUT 30


/* The bucket must be at 64 bytes in size
 * because the imbedded locks could cause cache line thrashing
 * other wise.
 * Need to add explicit padding because these are
 * immbedded as contiguous memory
 * 
 * The siblingp must be decalred as volitile to insure that
 * the compiler never optimizes (caches) a read of this field inside
 * a loop.
 */

typedef struct dyn_bucket {
    struct dyn_bucket * volatile siblingp;        /* bucket holding chain */
    void              *chainp;          /* first element in bucket */
    uint               split_count;      /* # of splits for this bucket */
    uint               insert_count;     /* incremented on each insertion */
    ulong              element_count;    /* # of elements in bucket */
    ulong              controlling_bkno; /* bucket number of controlling bucket */
    simple_lock_data_t bucket_lock;      /* lock for this bucket */
    ulong              padding[2];       /* keep this 64 bytes in size to
                                            avoid lock pinging in the 
                                            caches
                                            */
} dyn_bucketT;

/*
 * The hashtable header.
 * Contains and index table that points to the actual buckets of
 * the hashtable. This index does put an upper bound on the number of
 * buckets but this is a rather large upper bound (2**32 + initial size).
 * 
 * Note the hash table size (current_buckets) is volitile so that
 * compile does not try to optimize out a read of this field if we
 * are in a loop.
 */

typedef struct dyn_hashtable {
    ulong           initial_buckets;     /* Initial size of table */
    volatile ulong  current_buckets;     /* current number of buckets */
    ulong           max_chain_length;    /* max. elements in a chain */
    ulong           offset_hash_links;           /* offset within element */
    ulong            (*hash_function) (void *);/* pointer to hash function */
    uint            initial_index_shift; /* index calculation optimization */
    int             element_to_bucket_ratio;     /* condition for doubling table */
    ulong           split_interval;      /* minimum time between doubling table */
    ulong           last_split_time;/* time in usec of last time table doubled */
    struct lockinfo *lockinfo_ptr;        /* Lock class to initialize */
    uint            double_pending;       /* don't send message */
    int             pad; 
    dyn_bucketT     *index[DYN_INDEX_TABLE_SIZE];   
    /* array of pointers to bucket segments */
} dyn_hashtableT;



/*
 * The message that is sent to the kernel thread when a chain
 * exceeds its maximum length.
 */


typedef struct dyn_hashthread_msg{
    dyn_hashtableT       *hashtable;
    dyn_bucketT          *dh_bucket;
} dyn_hashthread_msgT;

void dyn_hashthread();
void dyn_split_chain( dyn_hashtableT * hashtable,
                      dyn_bucketT * bucketp);

dyn_bucketT* 
dyn_lock_bucket(dyn_hashtableT* hashtable, 
                ulong key);

#define DYN_GET_HASHLINKS(_hashtable , _element)                         \
((dyn_hashlinksT *) ((char *) (_element) + (_hashtable)->offset_hash_links))
    
#define DYN_UNGET_HASHLINKS(_hashtable , _hashlinks)                         \
    ((void *) ((char *) (_hashlinks) - (_hashtable)->offset_hash_links))
    
#define DYN_HASH_GET_KEY(_hashtable,_hlinks,_element)            \
    ((ulong) ((_hashtable)->hash_function == NULL)?                  \
     (((dyn_hashlinks_w_keyT *)(_hlinks))->dh_key):              \
     ((*((_hashtable)->hash_function))(_element))) 

/* Return a pointer to the bucket                              */
/* h - hashtbable pointer                                      */
/* k - key from hash function  (THIS WILL BE CHANGED AND RETURNED !!!) */
/* s - size of hash table (must be passed not obtained from h) */
/* bp - where pointer to bucket is returned to caller           */

#define  DYN_KEY_TO_BUCKET_PTR(_h,_k,_s,_bp)                                 \
{                                                                            \
long _ti,hb;                                                                  \
_k= (_k) & ((_s)-1);                                                                  \
hb= msb(_k);                                                                  \
_ti = (((long)(hb-(_h)->initial_index_shift) > 0) ? (hb-(_h)->initial_index_shift) : 0);  \
_bp = ((dyn_bucketT*) (((char *) ((_h)->index[(_ti)])) +                                 \
        ( ((_k)&((((_h)->initial_buckets)<<((_ti>0)?(_ti-1):_ti)) - 1))*        \
        (sizeof(dyn_bucketT)))));        \
}

#define DYN_UNLOCK_BUCKET(_bucketp) ((simple_unlock(&(_bucketp)->bucket_lock)))

#ifdef DYN_HASH_DEBUG
        
struct {
    
/* The following are caller statistics */
    
    ulong size_miss;         /* size changed in DYN_LOCK_BUCKET */
    ulong sbptr_miss;        /* sibling pointer changed in DYN_LOCK_BUCKET*/
    ulong longest_chain;      /* longest chain length realized */
    ulong element_inserted;  /* dyn_hash_insert was called*/
    ulong message_sent;      /* message sent to kernel thread */
    ulong unable_to_send_msg;/* Couldn't get a free message */
    ulong element_removed;   /* dyn_hash_remove was called */
    ulong double_no_mem;     /* no memory to double table */
    
/* The following are kernel thread statistics */
    
    ulong message_received;          /* kernel thread received a message */
    ulong chain_already_split;       /*dropped messages because ... */
    ulong chain_dropped_below_thold; /*dropped message because ... */
    ulong split_interval_guard;      /*dropped message because ... */
    ulong max_table_size;            /*dropped message because ... */
    ulong ratio_guard;               /*dropped message because ... */
    ulong chain_split;               /*thread split a chain */
    ulong largest_missed_splits;     /* largest split count difference */
    ulong table_doubled;             /* number of table doubles */
    ulong walked_chains;
    ulong setup_timeout;
    ulong timeout_expired;
}dyn_hash_stats;

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif  /* _KERN_DYN_HASH_H_ */





