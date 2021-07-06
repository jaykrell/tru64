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
 * @(#)$RCSfile: sp_attr.h,v $ $Revision: 1.1.30.1 $ (DEC) $Date: 2001/12/11 20:41:39 $
 */

#ifndef	   __SP_ATTR__

#define __SP_ATTR__

#include <sys/types.h>
#include <sys/acl_def.h>
#include <kern/lock.h>
#include <sys/uio.h>
#include <sys/audit.h>


/*
 * Used for telling the operation type for access decisions.  These
 * flags may be or'd togther.
 */

#define ATTR_NOTHING		0	/* Indicates no additional access
					   checks. */
#define ATTR_RETRIEVE		1	/* Indicates additional access checks required 
					   for retrieving the attribute. */
#define ATTR_SET		2	/* Indicates additional access checks required
					   for setting the attribute */
#define ATTR_DELETE		4	/* Indicates additional access checks required
					   for deleting the attribute */


/*
 * The following defines are used in two distinct case.
 *	1) The attr being returned from pacl_fs_get (attirbute_t *)
 *	2) Pointer to the entry in the cache (ir_entry_t *)
 */

#define NO_ATTR         (caddr_t) -1
#define UNKNOWN_ATTR_VAL    (caddr_t) -2
#define MULTIPLE_ATTRS    (caddr_t) -3		/* The attr in the vn will
						 * never be set to this, only
					 	 * functions that may
						 * retrieve more then 1 attr
						 * will use this.
						 */
#define UNFETCHED_ATTR ((void *) -4)
						/* Need another state to
						 * distinguish between attr
						 * doesn't exist and attr
						 * hasn't been fetched from
						 * disk yet.
						 */

/*
 * Check that attr is not one of the above codes or NULL
 */
#define ATTR_VALUE_REAL(x)	\
  ( (void *) (x) && 		\
    ( (void *) (x) < (void *) UNFETCHED_ATTR || \
      (void *) (x) > (void *) NO_ATTR ) )

#define NUMB_IR_CHARS	4		/* This is used to make it very clear
					 * the padding that goes on in the
					 * attribute_t.
					 *
					 * If attribute_t.ir is defined as 1 we still
					 * will allocate the same space as if
					 * attribute_t.ir was defined as 4 because
					 * padding.
					 *
					 * NUMB_IR_CHARS is used in the 
					 * calculation of the size of the
					 * attr with no ir present.
					 */

typedef struct {
        int version;
        int ir_length;            	/* length of internal representation */
        uchar_t  ir[NUMB_IR_CHARS];     /* internal representation pointer, this
					   is expected to be address aligned. */
} attribute_t;

/*
 * note that we subtract the NUMB_IR_CHARS out of the attribute_t, this is because it
 * is already represented in the ir length
 */

#define ATTR_SIZE 	(sizeof(attribute_t) - NUMB_IR_CHARS)

typedef  ulong_t attr_mask_t;

/* Start new types from NUM_ACL_IR_TYPES. */
#define        SP_TYPE_PRIVVEC         (NUM_ACL_IR_TYPES)
#define        SP_TYPE_PRIVVEC_MASK    (1<<SP_TYPE_PRIVVEC)
#define NUMBER_SP_ATTRS                (SP_TYPE_PRIVVEC+1)

/* Defines for proplist names */
#define       PROPL_ACL_ACCESS        "DEC_ACL_ACC"
#define       PROPL_ACL_DEF           "DEC_ACL_DEF"
#define       PROPL_ACL_DEF_DIR       "DEC_ACL_DEF_DIR"
#define       PROPL_PRIVVEC           "DEC_PRIVVEC"
#define       PROPL_AUDIT             AUD_PROPL_FLAG
/* Set the following to hold the longest proplist name plus \0 */
#define	      PROPL_MAX_LENGTH		30


typedef struct {
        caddr_t acl_attr[NUM_ACL_IR_TYPES];
	lock_data_t     secattr_lock;   /* Protects the attribute_t struct */
	int             ref_count;      /* Number of threads ref this  */
	int             flag;           /* Used to indicate the various 
					 * possible states of the attribute_t
					 * data.  Built from ACL_*_MASK and
					 * SP_TYPE_*_MASK bit values.
					 */
} secinfo_t;

#define ATTR_RMBIT(m,b)      m &= ~BIT_IN_WORD(b)


#ifdef	   _KERNEL
struct ipc_perm;

extern struct uio *	alloc_setproplist_data(attr_mask_t mask,
					       attribute_t * attr);
extern attribute_t *	dup_sec_attr(attribute_t *);
extern int		build_attr_name(attr_mask_t, char **);
extern int 		ipcaccess(struct ipc_perm *, secinfo_t *, mode_t);

#define	SECATTR_OK		0	/* v_secattr is ok */
#define	SECATTR_REMOVE		1	/* v_secattr is marked for removal */

extern const char * const SP_ATTR_LIST[NUMBER_SP_ATTRS];

#endif	/* _KERNEL */
#endif	/* __SP_ATTR__ */
