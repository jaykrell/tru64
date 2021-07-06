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
 * @(#)$RCSfile: ksm.h,v $ $Revision: 1.1.2.23 $ (DEC) $Date: 1998/10/30 21:38:59 $
 */

#pragma ident "@(#)$RCSfile: ksm.h,v $ $Revision: 1.1.2.23 $ (DEC) $Date: 1998/10/30 21:38:59 $"

#ifndef _KSM_KSM_H_
#define _KSM_KSM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/sysconfig.h>

/*
 * This header file contains the data structure definitions used within the
 * kernel to maintain the context of the members of sets.  These data
 * structures are not visible to user-mode.  However, this file is shipped
 * on the kit to allow other kernel-mode code to use these data structures.
 *
 * The data structure definitions are broken into three areas:
 *
 * - the data structures that define the member
 * - the data structures that define the relationships
 * - the data structures that define the set
 */

/*****************************************************************************
 *
 * The members of a set represent a manageable entity within the set.  The
 * data structures used to represent a member are defined next.
 *
 *        +----------+
 *        |          |
 *        |          |------>+------------+------------->+------------+--->...
 *        |  member  |       | management |-+            | management |-+
 *        |descriptor|       |  support   |-+            |  support   |-+
 *        |          |       | structure  |-+            | structure  |-+
 *        |          |       +------------+ |            +------------+ |
 *        +----------+                      |                           |
 *                                          |                           |
 *  +---------------------------------------+      +--------------------+
 *  |                                              |
 *  +-->+-----------+                             ...
 *  |   | attribute |
 *  |   |   table   |
 *  |   +-----------+
 *  |
 *  +-->+-----------+
 *  |   |  default  |--->value
 *  |   |  values   |--->value
 *  |   +-----------+
 *  |
 *  +-->+-----------+
 *  |   |  current  |--->value
 *  |   |  values   |--->value
 *  |   +-----------+
 *  |
 *  +-->+-----------+
 *  |   |  saved    |--->value
 *  |   |  values   |--->value
 *  |   +-----------+
 *  |
 *  +-->+-----------+
 *  |   |  command  |
 *  |   |   table   |
 *  |   |  element  |
 *  |   |-----------|
 *  |   |  command  |
 *  |   |   table   |
 *  |   |  element  |
 *  |   |-----------|
 *  |   |  command  |                                 owner1.mod
 *  |   |   table   |                                +-----------------+
 *  |   |  element  |                                |                 |
 *  |   +-----------+                                |                 |
 *  |                                                |                 |
 *  +----------------------------------------------->| support_routine |
 *                                                   |                 |
 *                                                   |                 |
 *                                                   +-----------------+
 *
 ****************************************************************************/

/*
 * Command Table Element
 *
 * The command table element contains the information about a single command
 * that can be requested on a member.  The Management Support Structure
 * points to an array of command table elements.
 */

#define KSM_CMD_NAME_SIZE       32          /* The command name contains up to
                                               this many characters including
                                               the null terminator */

typedef struct cmd_elem {
    char                cmd_name[KSM_CMD_NAME_SIZE];
                                            /* Name of the command */
    int                 prot;               /* Protection on the command */
    int                 unused;
} CMD_ELEM;

/*
 * Management Support Structure
 *
 * The management support structure provides pointers to the data structures
 * provided by a module that supports the member.  These structures contain
 * the information necessary to manage the member.  Remember that each member
 * in the set can have zero to many management support structures.
 */

typedef struct ksm_mem_req_buf KSM_MEM_REQ_BUF;

typedef struct mss {
    struct mss *        next;               /* Pointer to the next management
                                               support structure */
    cfg_subsys_attr_t * attr_table;         /* Pointer to the attribute table */

    char *              owner_name;         /* Pointer to null-terminated string
                                               containing the name of the kernel
                                               code repsonisble for this MSS */
    void *              owner_ds;           /* Pointer to data structure that is
                                               unique to the member */
    void **             default_val;        /* Pointer to the default value
                                               array of pointers */
    void **             current_val;        /* Pointer to the current value
                                               array of pointers */
    void **             saved_val;          /* Pointer to the saved value
                                               array of pointers */
    CMD_ELEM *          commands;           /* Pointer to the command array */

    int                 (*support_rtn) (int op, caddr_t indata, size_t inlen, caddr_t outdata, size_t olen, KSM_MEM_REQ_BUF *memreq, ulong arg, struct mss *mssptr);
					    /* Address of the support routine
                                               for these attributes/commands */
    ulong               flags;              /* Bit flags */
    ulong               arg;                /* Member-supplied argument to support routine */
    long                reserved;
} MSS;

#define  MSS_FLAG_CALL_SUPT_RTN             0x1

/*
 *  The following is a definition for the val_size field in the cfg_subsys_attr_t
 *    structure. KSM uses the field to store other information about the attribute.
 *
 *  The macro is for ease of initialization into the val_size field;
 */
typedef struct attr_info {
    uchar                   type;           /* type of attribute (not value)  */
#define KSM_TYPE_DEFAULT        0             /* default                      */
#define KSM_TYPE_COUNTER        1             /* counter                      */
#define KSM_TYPE_TIME_STAMP     2             /* time-stamp                   */
    uchar                   clu_op;         /* cluster operation on values    */
#define KSM_CLU_OP_UNKNOWN      0             /* not known or undefined       */
#define KSM_CLU_OP_SAME         1             /* must be the same             */
#define KSM_CLU_OP_DIFFERENT    2             /* may be different             */
#define KSM_CLU_OP_ADD          3             /* add (+)                      */
#define KSM_CLU_OP_OR           4             /* bitwise or (|)               */
    uchar                   Rsvd[6];        /* reserved for future            */
}                   attr_info_t;

#define KSM_ATTR_INFO( type, op)    ((op)<<8 | (type))

/*
 * Member Descriptor
 *
 * The member descriptor is the main data structure that represents the
 * member.  It maintains the unique member identifier and provides the
 * pointers to all the information for the member.  The member descriptor
 * is the data structure pointed to by the hierarchy, category, and other
 * relationship data structures.
 *
 * Note that the member descriptor does not point to any other member
 * descriptors.  The relationship data structures are used to connect one
 * member to another member by whatever relationships apply to the member.
 */

typedef struct mem_desc {
    int                 category;           /* Index into the category array
                                               for this member's category */
    char *              unique_name;        /* Unique name for this member */

    long                member_id;          /* Unique member id - used to make
                                               requests to this member */
    lock_data_t         lock;               /* Lock used to lock this member
                                               and everything it points to */
    MSS *               mss_list;           /* Pointer to the first management
                                               support structure */
    int                 last_instance;      /* Last instance number used in the
                                               hierarchy for this member */
    struct mem_desc *   next;              /* Next member is the fast search list */

    int                 flags;              /* member specific bit flags */

    int                 (*cmn_support_rtn)  (KSM_MEM_REQ_BUF *memreq, caddr_t indata, size_t inlen, caddr_t outdata, size_t outlen, ulong arg);
                                            /* Address of the common support routine
                                               for this member */
    ulong               cmn_arg;            /* Member-supplied argument to common support routine */

    int                 cfg[4];             /* cfg-specific storage */

    int                 set_spec1;          /* Reserved for set specific use */
    int                 reserved[3];        /* Reserved for future expansion */

} MEM_DESC;

/****************************************************************************
 *  low order bits reserved for ksm, 
 *  high order bits reserved for set specific use
 ***************************************************************************/
#define KSM_MEM_REGISTERED              0x001
#define KSM_MEM_REGISTERED_CAT_REL      0x002
#define KSM_MEM_REGISTERED_HIER_REL     0x004
#define KSM_MEM_REGISTERED_MIB_REL      0x008
 

/*****************************************************************************
 *
 * The members have relationships between them.  Applications can make
 * requests to find members based upon these relationships.  The data
 * structures used to keep track of the relationships are defined next.
 *
 * There are three standard relationships:
 *
 * - category-based
 * - hierarchical-based
 * - MIB-id-based
 *
 * For these relationships, the configuration module provides routines that
 * can be used to find members based upon these relationships.  Each set can
 * have any number of relationships; including any number of the three
 * standard relationships.  For each relationship in a set, the Find Request
 * structure is used by the configuration module to locate (and call) the
 * find routine.  The configuration module supplies find routines for the
 * three standard relationships.  However, the owner of the set can decide
 * to use their own find routines, if desired.
 *
 * There are data structures specific to each relationship.  The Find
 * Request structure is the only data structure common to all relationships.
 * The Find Request data structures for a set form a list which originates
 * in the set descriptor data structure.
 *
 *        category relationship
 *  ---->+-------------+
 *       |+-----------+|      category table
 *       ||   find    ||  +-->+----------+
 *   +-----   info    ||  |   | category |-->+----------+-->+----------+-->...
 *   |   |+-----------+|  |   |  entry   |   | category |   | category |
 *   |   |             |  |   |----------|   | pointer  |-+ | pointer  |-+
 *   |   |             |--+   | category |   +----------+ | +----------+ |
 *   |   |             |      |  entry   |                V              V
 *   |   |             |      |----------|              member         member
 *   |   +-------------+      |   ...    |
 *   |                        +----------+
 *   |
 *   |
 *   |    hierarchy relationship
 *   +-->+-------------+
 *       |+-----------+|
 *       ||   find    ||  +-->+-----------+
 *   +-----   info    ||  |   | hierarchy |--+
 *   |   |+-----------+|  |   |  pointer  |--+
 *   |   |             |  |   +-----------+  |
 *   |   |             |--+                  |
 *   |   |             |                     +--> parent
 *   |   |             |                     |
 *   |   +-------------+                     +--> peer
 *   |                                       |
 *   |                                       +--> first child
 *   |                                       |
 *   |                                       +--> member
 *   |
 *   |    MIB-id relationship
 *   +-->+-------------+
 *       |+-----------+|
 *       ||   find    ||  +-->+---------+----->+---------+-->...
 *   +-----   info    ||  |   | MIB-id  |      | MIB-id  |
 *   |   |+-----------+|  |   | pointer |--+   | pointer |--+
 *   |   |             |  |   +---------+  |   +---------+  |
 *   |   |             |--+                |                |
 *   |   |             |                   V                V
 *   |   |             |                 member           member
 *   |   +-------------+
 *   |
 *  ...
 *
 ****************************************************************************/

/*
 * Find Request
 *
 * The find info data structure is used to point to the appropriate find
 * routine for a particular find operation.  The set descriptor points to the
 * first find info data structure.  The find operation code is used to
 * determine which find routine is called to perform the find request.
 */

typedef struct ksm_find_buf KSM_FIND_BUF;
typedef struct set_desc SET_DESC;

typedef struct find_info {
    struct find_info *   next;               /* Pointer to the next find
                                               info */
    int                 find_type;          /* Find operation code handled by
                                               this find info */
    int                 (*find_rtn) (SET_DESC *sptr, KSM_FIND_BUF *req, size_t size, struct find_info *ptr, MEM_DESC **m);
                                            /* Address of the find routine that
                                               supports this operation code */
    long                reserved[2];
} FIND_INFO;

/*
 * Category-based data structures ********************************************
 */

/*
 * Category pointer
 *
 * The category pointer data structures are used link all the members of
 * same category.  Each list of members in the same category starts in the
 * Category Array which is made up of Category Entries.
 */

typedef struct cat_ptr {
    struct cat_ptr *    next;               /* Pointer to the next category
                                               pointer */
    MEM_DESC *          member;             /* Pointer to the member that's in
                                               this category */
} CAT_PTR;

/*
 * Category Entry
 *
 * The category entry exists in the category array.  There is one entry in
 * the category array for each category for the set.  Each entry contains
 * various information about the category.
 */

#define KSM_CAT_NAME_SIZE       32          /* The category name contains up to
                                               this many characters including
                                               the null terminator */

typedef struct cat_ent {
    char                cat_name[KSM_CAT_NAME_SIZE];
                                            /* Name of the category */
    CAT_PTR *           next;               /* Pointer to the first category
                                               pointer */

  /* The next three fields are used for the fast lookup feature. */

    simple_lock_data_t  slock;              /* lock for the cache fields */
    long                prev_mem_id;        /* Member id of the previous find
                                               call for this category */
    CAT_PTR *           prev;               /* Category pointer of the previous
                                               find call for this category */
} CAT_ENT;

/*
 * Category Relationship
 *
 * The category relationship data structure contains all the information
 * required to have category-based relationships.  This includes the find
 * info data structure so that requests can be made to find members by
 * category.
 */

typedef struct cat_rel {
    FIND_INFO           find_info;          /* Find info structure for
                                               category-based find info */
    CAT_ENT *           categories;         /* Pointer to the array of category
                                               entries */
    uint                count;              /* size of the array of category entries */

  /* The next three fields are used for the fast lookup feature. */

    simple_lock_data_t  slock;              /* lock for the cache fields */
    long                member_id;          /* member_id of previously found member */
    CAT_PTR *           prev;               /* Category pointer to member found
                                               in previous find-by-category */
} CAT_REL;

/*
 * Hierarchy-based data structures *******************************************
 */

/*
 * Heirarchical pointer
 *
 * The hierarchical pointer data structures are used link the members into
 * a hiearchy.  The hiearchy starts in the hierarchy relationship data
 * structure.
 */

struct hier_ptr;

typedef struct hier_ptr {
    struct hier_ptr *   parent;             /* Pointer to the parent of this
                                               member */
    struct hier_ptr *   peer;               /* Pointer to the next peer of this
                                               member */
    struct hier_ptr *   child;              /* Pointer to the first child of this
                                               member */
    MEM_DESC *          member;             /* Pointer to the member being
                                               represented in the hierarchy */
    int                 instance;           /* The instance of this member in the
                                               hierarchy */
} HIER_PTR;

/*
 * Hierarchy Relationship
 *
 * The hierarchy relationship data structure contains all the information
 * required to have hierarchy-based relationships.  This includes the find
 * info data structure so that requests can be made to find members
 * within the hierarchy.
 */

typedef struct hier_rel {
    FIND_INFO           find_info;          /* Find info structure for
                                               hierarchy-based find info */
    HIER_PTR *          hierarchy;          /* Pointer to the first member in
                                               the hierarchy */

  /* The next four fields are used for the fast lookup feature. */

    simple_lock_data_t  slock;              /* lock for the cache fields */
    long                prev_mem_id;        /* Member id of the previous find call
                                               in the hierarchy */
    int                 prev_inst;          /* Instance of the previous find call
                                               in the hierarchy */
    HIER_PTR *          prev;               /* Hierarchy pointer of the previous
                                               find call in the hierarchy */
} HIER_REL;

/*
 * MIB-id-based data structures **********************************************
 */

/*
 * MIB pointer
 *
 * The MIB pointer data structures are used link the members into numerical
 * order by MIB-id.
 */

typedef struct mib_ptr {
    struct mib_ptr *    next;               /* Pointer to the next MIB pointer
                                               data structure */
    MEM_DESC *          member;             /* Pointer to the member being
                                               represented by this MIB-id */
    long                mib_id;             /* MIB-id for this member */

} MIB_PTR;

/*
 * MIB-id Relationship
 *
 * The MIB-id relationship data structure contains all the information
 * required to have MIB-id-based relationships.  This includes the find
 * info data structure so that requests can be made to find members
 * by MIB-id.
 */

typedef struct mib_rel {
    FIND_INFO           find_info;          /* Find info structure for
                                               MIB-id-based find info */
    MIB_PTR *           first_mib;          /* Pointer to the first member with
                                               a MIB-id */
    long                last_mib_id;        /* Last MIB-id assigned */


  /* The next three fields are used for the fast lookup feature. */

    simple_lock_data_t  slock;              /* lock for the cache fields */
    long                prev_mib_id;        /* MIB id of the previous find call
                                               by MIB-id */
    MIB_PTR *           prev;               /* MIB pointer of the previous find
                                               call by MIB-id */
} MIB_REL;

/*****************************************************************************
 *
 * The members and the relationships between the members are all brought
 * together by the set descriptor.  Each set is registered with the
 * configuration module by passing the set descriptor to the registration
 * routine.
 *
 *   +----------+----------------------------------------->+----------+--->...
 *   |   set    |                                          |   set    |
 *   |descriptor|                                          |descriptor|
 *   |          |                                          +----------+
 *   |          |
 *   |          |---->+---------+---->+---------+---->+---------+--->...
 *   |          | +-->|  find   | +-->|  find   | +-->|  find   |
 *   |          | |   |  info   | |   |  info   | |   |  info   |
 *   |          | |   +---------+ |   +---------+ |   +---------+
 *   | category |-+               |               |
 *   |          |                 |               |
 *   | hierarchy|-----------------+               |
 *   |          |                                 |
 *   |  MIB-id  |---------------------------------+
 *   +----------+
 *
 ****************************************************************************/

/*
 * Set Descriptor
 *
 * The set descriptor data structure is used to represent a set.
 */

#define KSM_SET_NAME_SIZE  CFG_SUBSYS_NAME_SZ  /* The set name contains up to
                                                  this many characters including
                                                  the null terminator */

typedef struct ksm_reqbuf_hdr KSM_REQBUF_HDR;

struct set_desc {
    struct set_desc *   next;               /* Pointer to the next set descriptor
                                               on this system */
    char                setname[KSM_SET_NAME_SIZE];
                                            /* Name of the set */
    lock_data_t         lock;               /* Lock for this entire set */

    FIND_INFO *         find_list;          /* Pointer to the first find
                                               info structure */

  /* For efficiency, we provide a direct pointer to the standard relationship
     descriptors (category, hierarchy, and MIB-id). */

    CAT_REL *           category;           /* Pointer to the category
                                               relationship data structure */
    HIER_REL *          hierarchy;          /* Pointer to the hierarchy
                                               relationship data structure */
    MIB_REL *           mib_rel;            /* Pointer to the MIB-id
                                               relationship data structure */
    simple_lock_data_t  slock;              /* lock for the cache fields */
    MEM_DESC *          member;             /* Pointer to last-found member */
    long                member_id;          /* Member ID of last-found member */
    caddr_t             hash;               /* Pointer to hash table */
    MEM_DESC *          mem_list;           /* Pointer to member list in the set */
    int                 (*set_support_rtn) (KSM_REQBUF_HDR  *reqbuf, caddr_t indata, size_t inlen, caddr_t outdata, size_t outlen);
    int                 version;            /* version of the set */
    int                 reserved[7];

};


/*
 * Request buffers.
 */
/*
 * Request buffer header - common to all KSM operations.
 */
struct ksm_reqbuf_hdr {
    ulong               flags;                  /* bit flags                      */
    int                 opcode;                 /* requested operation (Input required) */
    int                 version;                /* version of the set, provided by application */
    char                setname[KSM_SET_NAME_SIZE];
                                                /* name of kernel set (Input required)  */
    int                 ksm_version;            /* ksm version, set by libcfg */
    int                 reserved[7];
};

/* bit flags in the request buffer header */
#define  KSM_FLAG_ROOT_VERIFIED         0x1
#define  KSM_FLAG_SIZING                0x2
#define  KSM_FLAG_QUERYING              0x4

/* ksm version numbers */
#define  KSM_VERSION_1                    1
#define  KSM_CURRENT_VERSION  KSM_VERSION_1

/* version numbers of the hardware set */
#define  HWSET_VERSION_1                      1
#define  HWSET_CURRENT_VERSION  HWSET_VERSION_1

/*
 * ksm name buffer.
 */
typedef struct ksm_name_buf {
    char                    *names;             /* pointer to the actual data (names)   */
    int                     count;              /* number of data items in the names field */
    uint                    attrs;
    long                    reserved;
} KSM_NAME_BUF;


typedef struct ksm_set_req_buf {
    struct ksm_reqbuf_hdr   hdr;                /* request buffer header */
    int                     set_version;        /* version of set - output */
    int                     unused;
    KSM_NAME_BUF            namebuf;            /* category names - output */
    long                    reserved[4];
} KSM_SET_REQ_BUF;


/* request buffer for find-a-member request */
struct ksm_find_buf {
    struct ksm_reqbuf_hdr   hdr;                /* request buffer header                 */
    int                     find_subtype;       /* sub-type of search                    */
    int                     unused;
    char                    cat_name[KSM_CAT_NAME_SIZE];    /* name of category to find  */
    long                    member_id;          /* member id of last member - 0 if none  */
    long                    parent_id;          /* member id of parent found - 0 if none */
    int                     member_inst;        /* instance of last member - 0 if none   */
    int                     parent_inst;        /* instance of parent found - 0 if none  */
    long                    mib_id;             /* mib id of last member - 0 if none     */
    long                    reserved[4];
};

/* values for find_subtype */
#define KSM_FIND_NEXT      1
#define KSM_FIND_INST      2
#define KSM_FIND_PARENT    3
#define KSM_FIND_CHILD     4
#define KSM_FIND_PEER      5
#define KSM_FIND_THIS      6


/* request buffer for member request */
struct ksm_mem_req_buf {
    struct ksm_reqbuf_hdr   hdr;                /* request buffer header */
    long                    member_id;          /* member id of member   */
    union {
        struct {
            char            cmdname[KSM_CMD_NAME_SIZE]; /* command to execute */
            int             status;             /* status of command execution */
            int             reserved[3];
        } exe;

        struct {
            CMD_ELEM        *cmds;              /* ptr to commands returned */
            int             count;              /* # commands returned */
        } get;

        struct {
            caddr_t         data;               /* pointer to in/out data */
            int             datasize;           /* size of data */
        } user;

    } cmd;
    long                    reserved[4];
};

/* Ksm binary data descriptor */
struct  ksm_bin_data_ds {
    ulong     size;     /* # bytes of the actual binary data */
    caddr_t   addr;     /* starting address of the actual binary data */
};

/*
 * Macros for constructing and extracting KSM-specific error codes.
 */
#define  KSM_FRAMEWK_ERR(x)     (x << 16)
#define  IS_KSM_FRAMEWK_ERR(x)  (x >= (2^16))
#define  KSM_FRAMEWK_ERRVAL(x)  (x >> 16)
#define  KSM_MEMBER_ERRVAL(x)   (x & 0x0000ffff)


/*
 * ksm kernel function prototypes.
 */
extern int ksm_register_set(SET_DESC *s);
extern int ksm_register_member(char setname[], MEM_DESC *m);
extern int ksm_unregister_member(char setname[], MEM_DESC *m);
extern int ksm_find_cat_mem(SET_DESC *sptr, KSM_FIND_BUF *req, size_t size, FIND_INFO *ptr, MEM_DESC **mem);
extern int ksm_find_hier_mem(SET_DESC *sptr, KSM_FIND_BUF *req, size_t size, FIND_INFO *ptr, MEM_DESC **mem);
extern int ksm_find_mib_mem(SET_DESC *sptr, KSM_FIND_BUF *req, size_t size, FIND_INFO *ptr, MEM_DESC **mem);
extern int ksm_find_member(KSM_FIND_BUF  *buf, size_t size);
extern int ksm_get_attributes(KSM_MEM_REQ_BUF *memreq, cfg_attr_t *attrs, uint nattrs);
extern int ksm_set_attributes(KSM_MEM_REQ_BUF *memreq, cfg_attr_t *attrs, uint nattrs);

extern CAT_ENT* ksm_cat_find_category(CAT_REL *cat_rel_ptr, char *name, int *cat_index); 
extern CAT_ENT* ksm_cat_insert_category(CAT_REL *cat_rel_ptr, char *name, int *cat_index, int *cur_tbl_size, int tbl_incr);
extern int ksm_cat_insert_member(CAT_ENT *cat_entry, MEM_DESC *mem);
extern int ksm_cat_remove_member(CAT_ENT *cat_entry, MEM_DESC *mem) ;
extern void ksm_cat_print_cat_rel(CAT_REL *cat_rel_ptr);

extern MIB_PTR* ksm_mib_find_member(MIB_REL *mib_rel_ptr, MEM_DESC *mem);
extern int ksm_mib_insert_member(MIB_REL *mib_rel_ptr, MEM_DESC *mem);
extern int ksm_mib_remove_member(MIB_REL *mib_rel_ptr, MEM_DESC *mem);
extern void ksm_mib_print_mib_rel(MIB_REL *mib_rel_ptr);

extern HIER_PTR* ksm_hier_insert_root(HIER_REL *hier_rel_ptr, MEM_DESC *mem);
extern HIER_PTR* ksm_hier_insert_member(HIER_PTR *hier_ptr, MEM_DESC *mem);
extern int ksm_hier_remove_member(HIER_REL *hier_rel_ptr, HIER_PTR *hier_ptr, MEM_DESC *mem);
extern HIER_PTR* ksm_hier_find_by_instance(HIER_REL *hier_rel_ptr, long id, int instance);
extern HIER_PTR* ksm_hier_find_child(HIER_PTR *hier_ptr, MEM_DESC *mem);
extern HIER_PTR* ksm_hier_find_by_owner_ds(HIER_REL *hier_rel_ptr, void *owner_ds);
extern void ksm_hier_print_hier_rel(HIER_REL *hier_rel_ptr);


/*
 *===========================================================================
 *                  DEFINITIONS OF KSM OPCODES
 *===========================================================================
 */

/*
 * Request/Op codes for the 'ksm'.
 */
#define  CFG_OP_KSM_MIN       CFG_OP_SUBSYS_MAX+2001    /* 3000 */
#define  CFG_OP_KSM_MAX       KSM_OP_PRIV_MEM_MAX       /* 3999 */

#define  CFG_OP_KSM_PRIV_MIN  KSM_OP_PRIV_SYS_MIN
#define  CFG_OP_KSM_PRIV_MAX  KSM_OP_PRIV_MEM_MAX

/*
 *---------------------------------------------------------------------------
 *           KSM OPCODES RESERVED BY SYSTEM IMPLEMENTATION
 * Note: sets, members and applications should NOT use these opcodes.
 *---------------------------------------------------------------------------
 */

    /*- range of values allowed -*/
#define  CFG_OP_KSM_LIB_MIN   CFG_OP_KSM_MIN            /* 3000 */
#define  CFG_OP_KSM_LIB_MAX   CFG_OP_KSM_LIB_MIN+199    /* 3199 */

#define  CFG_OP_KSM_READ_MIN    CFG_OP_KSM_LIB_MIN
#define  CFG_OP_KSM_READ_MAX    CFG_OP_KSM_READ_MIN+99
#define  CFG_OP_KSM_WRITE_MIN   CFG_OP_KSM_READ_MAX+1
#define  CFG_OP_KSM_WRITE_MAX   CFG_OP_KSM_WRITE_MIN+99

    /*- specific values defined and used -*/
    /*- read operations -*/
#define  CFG_OP_KSM_FIND        CFG_OP_KSM_READ_MIN+1
#define  CFG_OP_KSM_GETATTR     CFG_OP_KSM_READ_MIN+2
#define  CFG_OP_KSM_GETALLATTR  CFG_OP_KSM_READ_MIN+3 
#define  CFG_OP_KSM_GETNAMES    CFG_OP_KSM_READ_MIN+4 
#define  CFG_OP_KSM_GETINFO     CFG_OP_KSM_READ_MIN+5 
#define  CFG_OP_KSM_SETOP       CFG_OP_KSM_READ_MIN+6 
#define  CFG_OP_KSM_MEMOP       CFG_OP_KSM_READ_MIN+7 

    /*- write operations -*/
#define  CFG_OP_KSM_SETATTR     CFG_OP_KSM_WRITE_MIN+1

/*
 *---------------------------------------------------------------------------
 *        END OF KSM OPCODES RESERVED BY SYSTEM IMPLEMENTATION
 *---------------------------------------------------------------------------
 */

/*
 *===========================================================================
 *  FOLLOWING ARE KSM OPCODES FOR SETS, MEMBERS, AND APPLICATIONS TO USE
 *===========================================================================
 */

/*
 *---------------------------------------------------------------------------
 * Ksm non-privileged operations - reserved (system-defined).
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_NONPRIV_SYS_MIN    CFG_OP_KSM_LIB_MAX+1         /* 3200 */
#define  KSM_OP_NONPRIV_SYS_MAX    KSM_OP_NONPRIV_SYS_MIN+199   /* 3399 */

    /*- specific values defined and used -*/

/* Non-privileged opcodes for the cfg_ksm_find() */
#define  KSM_OP_FIND_CATEGORY      KSM_OP_NONPRIV_SYS_MIN+1
#define  KSM_OP_FIND_HIERARCHY     KSM_OP_NONPRIV_SYS_MIN+2
#define  KSM_OP_FIND_MIBID         KSM_OP_NONPRIV_SYS_MIN+3

/* Non-privileged opcodes for the cfg_ksm_memreq() */
#define  KSM_OP_MREQ_GETCATTR      KSM_OP_NONPRIV_SYS_MIN+41
#define  KSM_OP_MREQ_GETDATTR      KSM_OP_NONPRIV_SYS_MIN+42
#define  KSM_OP_MREQ_GETSATTR      KSM_OP_NONPRIV_SYS_MIN+43
#define  KSM_OP_MREQ_GETCATTR_ALL  KSM_OP_NONPRIV_SYS_MIN+44
#define  KSM_OP_MREQ_GETDATTR_ALL  KSM_OP_NONPRIV_SYS_MIN+45
#define  KSM_OP_MREQ_GETSATTR_ALL  KSM_OP_NONPRIV_SYS_MIN+46
#define  KSM_OP_MREQ_GETCOMM       KSM_OP_NONPRIV_SYS_MIN+47
#define  KSM_OP_MREQ_OTHER         KSM_OP_NONPRIV_SYS_MIN+48

/* Non-privileged opcodes for the cfg_ksm_setreq() */
#define  KSM_OP_SREQ_GETCAT_NAMES  KSM_OP_NONPRIV_SYS_MIN+91
#define  KSM_OP_SREQ_GETINFO       KSM_OP_NONPRIV_SYS_MIN+92

/*
 *---------------------------------------------------------------------------
 * Ksm non-privileged operations defined by sets (set-specific).
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_NONPRIV_SET_MIN    KSM_OP_NONPRIV_SYS_MAX+1     /* 3400 */
#define  KSM_OP_NONPRIV_SET_MAX    KSM_OP_NONPRIV_SET_MIN+99    /* 3499 */

    /*- specific values defined and used -*/

/*
 *---------------------------------------------------------------------------
 * Ksm non-privileged operations defined by members (member-specific).
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_NONPRIV_MEM_MIN    KSM_OP_NONPRIV_SET_MAX+1     /* 3500 */
#define  KSM_OP_NONPRIV_MEM_MAX    KSM_OP_NONPRIV_MEM_MIN+99    /* 3599 */

    /*- specific values defined and used -*/


/*
 *---------------------------------------------------------------------------
 * Ksm privileged operations - reserved (system-defined).
 * Only the root user is allowed to perform these operations.
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_PRIV_SYS_MIN    KSM_OP_NONPRIV_MEM_MAX+1        /* 3600 */
#define  KSM_OP_PRIV_SYS_MAX    KSM_OP_PRIV_SYS_MIN+199         /* 3799 */

    /*- specific values defined and used -*/

/* Privileged opcodes for the cfg_ksm_memreq() */
#define  KSM_OP_PRIV_MREQ_SETCATTR   KSM_OP_PRIV_SYS_MIN+1
#define  KSM_OP_PRIV_MREQ_SETSATTR   KSM_OP_PRIV_SYS_MIN+2


/*
 *---------------------------------------------------------------------------
 * Ksm privileged operations defined by sets (set-specific).
 * Only the root user is allowed to perform these operations.
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_PRIV_SET_MIN    KSM_OP_PRIV_SYS_MAX+1           /* 3800 */
#define  KSM_OP_PRIV_SET_MAX    KSM_OP_PRIV_SET_MIN+99          /* 3899 */

    /*- specific values defined and used -*/

/*
 *---------------------------------------------------------------------------
 * Ksm privileged operations defined by members (member-specific).
 * Only the root user is allowed to perform these operations.
 *---------------------------------------------------------------------------
 */
    /*- range of values allowed -*/
#define  KSM_OP_PRIV_MEM_MIN    KSM_OP_PRIV_SET_MAX+1           /* 3900 */
#define  KSM_OP_PRIV_MEM_MAX    KSM_OP_PRIV_MEM_MIN+99          /* 3999 */

    /*- specific values defined and used -*/

/*
 *===========================================================================
 *                  END OF DEFINITIONS OF KSM OPCODES
 *===========================================================================
 */

#ifdef __cplusplus
}
#endif

#endif /*_KSM_KSM_H_*/

