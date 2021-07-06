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
 * @(#)$RCSfile: e_dyn_hash.h,v $ $Revision: 1.1.5.3 $ (DEC) $Date: 1999/05/06 19:11:02 $
 */

#ifndef _E_KERN_DYN_HASH_H_
#define _E_KERN_DYN_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Define from stddef.h.
 */
#ifdef __arch64__
#define offsetof(s_name, s_member) \
        ((size_t)((char *)&((s_name *)0L)->s_member - (char *)0L))
#endif /* __arch64__ */


typedef struct dyn_hashlinks {
   void    *dh_next;       
   void    *dh_prev;
} dyn_hashlinksT;

typedef struct dyn_hashlinks_w_key{
   dyn_hashlinksT dh_links;
   ulong          dh_key;
} dyn_hashlinks_w_keyT;

extern void *
dyn_hashtable_init(ulong initial_bucket_count,
                   ulong bucket_length_threshold,
                   int   bucket_to_element_ratio,
                   ulong split_interval,
                   ulong offset_to_hashlinks,
                   struct lockinfo *lockinfo_ptr,
                   ulong (*hash_function) ()
                   );

extern void 
dyn_hashtable_destroy( void *hashtable);
 
extern void * 
dyn_hash_obtain_chain( void *hashtable,
                       ulong key,
                       ulong *insert_count);

extern void 
dyn_hash_release_chain( void * hashtable,
                        ulong key);

extern void 
dyn_hash_insert( void *hashtable,
                 void * element,
                 int obtain_lock);

extern void 
dyn_hash_remove( void * hashtable,
                 void * element,
                 int obtain_lock);

extern void 
dyn_kernel_thread_setup();

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif  /* _E_KERN_DYN_HASH_H_ */


