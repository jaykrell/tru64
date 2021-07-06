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
 * Avoid recursive and double includes
 */
#if !defined(__INCLUDE_IP_TCNTL_STRUCT)
#define __INCLUDE_IP_TCNTL_STRUCT

/*
 * This parameter controls the number of FILTER IDs that are allocated
 * in one block. A block represents one slot id in the flow hash table.
 */
#define TCNTL_FILT_IDBLOCK (300)

/*
 * This macro computes the hash index for a IPv6 flow filter into
 * a filter table. The outcome is sensitive to the byte ordering
 * of the host machine.
 */
#ifndef BYTE_ORDER
#error
#elif BYTE_ORDER == BIG_ENDIAN
#define _TCNTL_HASH_IPV6_FLOW_FILTER(ft, fi)                   \
           (((fi->filter.ip6_fl.src.s6_qaddr[1] << 20) |       \
	     (u_int64_t)fi->filter.ip6_fl.flowlabel) %         \
	    ft->size)
#elif BYTE_ORDER == LITTLE_ENDIAN
#define _TCNTL_HASH_IPV6_FLOW_FILTER(ft, fi)                   \
           (((fi->filter.ip6_fl.src.s6_qaddr[1] & ~0xfffffL) | \
	     (u_int64_t)ntohl(fi->filter.ip6_fl.flowlabel)) %  \
	    ft->size)
#endif

/*
 * This macro computes the hash index for an IPv4 Wildcard filter into
 * a filter table.
 */
#define _TCNTL_HASH_IPV4_WF_FILTER(ft, fi)                     \
           (fi->filter.ip4_wf.k %                              \
	    ft->size)

/*
 * This macro computes the hash index for an IPv4 Port filter into
 * a filter table.
 */
#define _TCNTL_HASH_IPV4_PORT_FILTER(ft, fi)                   \
           ((fi->filter.ip4_port.k.key1 +                      \
	     fi->filter.ip4_port.k.key2) %                     \
	    ft->size)

/*
 * This private definition ensures that we can control if
 * is enabled or not in a more restricted scope.
 */
#if defined(TCNTL_DEBUG)
#include <kern/macro_help.h>
#define TCNTL_ASSERT(ex)						\
MACRO_BEGIN								\
	if (!(ex)) {							\
		extern char *strrchr( char *, char );			\
		extern char tcntl_panic_msg[512];			\
		char *_fn;						\
		_fn = strrchr(__FILE__, '/');				\
		if (_fn == NULL)					\
		    _fn = __FILE__;					\
		else _fn++;						\
		sprintf(tcntl_panic_msg,				\
			"tcntl assertion failed: %s, file: %s, line: %d\n",\
			#ex, _fn, __LINE__);				\
		panic(tcntl_panic_msg);					\
	}								\
MACRO_END
#else	/* TCNTL_DEBUG */
#define TCNTL_ASSERT(ex)
#endif	/* TCNTL_DEBUG */

/*
 * Debug levels (in tcntl_debug_flags)
 */
#define TCNTL_M_XDEBUG (1<<0)   /* Inline informational */
#define TCNTL_M_YDEBUG (1<<1)   /* Warning */
#define TCNTL_M_ZDEBUG (1<<2)   /* Recoverable error */

/*
 * Debug execution macros
 */
#define TCNTL_YDEBUG_ENABLED (tcntl_debug_flags & TCNTL_M_YDEBUG)
#define TCNTL_ZDEBUG_ENABLED (tcntl_debug_flags & TCNTL_M_ZDEBUG)
#if defined(TCNTL_DEBUG)
#define TCNTL_XDEBUG_ENABLED (tcntl_debug_flags & TCNTL_M_XDEBUG)
#else
#define TCNTL_XDEBUG_ENABLED (0)
#endif

/*
 * Debug print macros
 */
#define TCNTL_YDEBUG(args) \
   if (TCNTL_YDEBUG_ENABLED) printf args;
#define TCNTL_ZDEBUG(args) \
   if (TCNTL_ZDEBUG_ENABLED) printf args;
#if defined(TCNTL_DEBUG)
#define TCNTL_XDEBUG(args) \
   if (TCNTL_XDEBUG_ENABLED) printf args;
#else
#define TCNTL_XDEBUG(args)
#endif


#include "netinet/in.h"
#include <netinet/rsvp_intserv.h>

/*
 * Define macros that flag boundaries between blocks of data
 * hand carved to fit certain cache block boundaries for better
 * speed. These macros do not do anything -- they attempt to make
 * any future maintainer aware of that pain has gone into placing
 * fields where they currently are.
 *
 * DO NOTE!! A number of ASSERTs are placed in the routine
 * tcntl_setup() to verify that various cache alignments thata
 * have been crafted into structures are met. If you change
 * anything in the structures that are sensitive to cache
 * blocks, be sure to tweak the associated ASSERTs in the
 * tcntl_setup().
 */
#define BEGIN_64BYTE_CACHEBLOCK_READ
#define END_64BYTE_CACHEBLOCK_READ
#define BEGIN_64BYTE_CACHEBLOCK_WRITE
#define END_64BYTE_CACHEBLOCK_WRITE

/*
 * This compiletime is used to flag the version number of the
 * ioctl() interface. Bump this by one when you make changes
 * that require kernel and user mode code to stay in synch.
 */
#define TCNTL_INFO_VERSION	(2)

/*
 * This type defines the opaque flow handle.
 */
typedef u_int64_t tcntl_rhandle_t;

/*
 * This defines the filter handle, which in user mode
 * is an opaque identifier while in kernel mode it has a
 * distinct number of fields.
 */
#ifdef _KERNEL
typedef struct {
#ifndef __VMS
    u_int64_t table : 5,
              pos  : 12,
              id : 47;
#else /* __VMS */
    u_int32_t table : 5,
	      pos   : 12,
	      id_low : 32,
	      id_high : 15;
#endif /* __VMS */
} tcntl_fhandle_t;
#else
typedef u_int64_t tcntl_fhandle_t;
#endif

/*
 * The socket address is used in a few sructures
 */
union tcntl_sockaddr {
    struct sockaddr	sa;
    struct sockaddr_in  sin;
    struct sockaddr_in6 sin6;
};

/*
 * This is a user structure part of the ioctl() interface.
 * Is is used to describe information about a filter.
 */
typedef struct {
    u_int length;	/* total length of this struct */
    u_int type;		/* TCNTL_FILT_TABLE_xxx */
    tcntl_fhandle_t fhandle; /* Filter handle */

    union {
	struct {
	    struct in_addr src;
	    struct in_addr dest;
	    u_short src_port;
	    u_short dest_port;
	    u_char proto;
	} ip4;
	struct {
	    struct in6_addr src;
	    struct in6_addr dest;
	    u_int flowlabel;
	    u_short src_port;
	    u_short dest_port;
	    u_char proto;
	    u_char unused[7];
	} ip6;
    } filt_u;
} tcntl_filtspec_t;

/*
 * Definitions for cmd parameter in struct flowreq, struct filtreq
 * or struct tcntllistreq.
 */
enum {
    TCNTL_CMD_ADDFLOWSPEC = 1,
    TCNTL_CMD_MODFLOWSPEC,
    TCNTL_CMD_DELFLOWSPEC,
    TCNTL_CMD_ADDFILTER,
    TCNTL_CMD_DELFILTER,
    TCNTL_CMD_LISTFLOW_HANDLES,
    TCNTL_CMD_LISTFLOW_HTH,
    TCNTL_CMD_LISTFLOW_SLOT,
    TCNTL_CMD_LISTFILT_HTH,
    TCNTL_CMD_LISTFILT_SLOT

};

/*
 * Definitions for flags parameter in struct flowreq
 */
enum {
    TCNTL_E_POLICE_FLAG = 1,
    TCNTL_M_POLICE_FLAG = 2,
    TCNTL_B_POLICE_FLAG = 4
};

/*
 * Definitions for flags parameter in struct adspecreq
 */
enum {
    TCNTL_ADSPEC_NON_RSVP_HOP = 1
};

/*
 * Error codes in our package
 */
typedef enum
{
    TCNTL_ERR_OK = 0,                   /* It worked */
    TCNTL_ERR_NSCONFP,                  /* No such configuration parameter */
    TCNTL_ERR_NOMEM,                    /* Not enough kernel memory */
    TCNTL_ERR_ADSPEC,                   /* Unsupported or malformed ADSPEC */
    TCNTL_ERR_COPYOUTF,                 /* Failed to copyout() to user buffer */
    TCNTL_ERR_NO_NET_RESOURCES,         /* Insufficient network resources for req */
    TCNTL_ERR_FLOWSPEC,                 /* Unsupported or malformed FLOWSPEC */
    TCNTL_ERR_INVARG,                   /* Invalid argument */
    TCNTL_ERR_TCNE,                     /* Traffic control not enabled on device */
    TCNTL_ERR_BADTABLEI,                /* Bad table index */
    TCNTL_ERR_NSFLT,                    /* No such flow table */
    TCNTL_ERR_TABTOOSMALL,              /* New table size is too small */
    TCNTL_ERR_NSFIT,                    /* No such filter table */
    TCNTL_ERR_RESINP,                   /* Table resize in progress */
    TCNTL_ERR_FLNFND,                   /* Flow not found */
    TCNTL_ERR_FLMFDEL,                  /* Flow is marked for delete */
    TCNTL_ERR_TRESIZED,                 /* Table resized in between calls */
    TCNTL_ERR_INVSLOT,                  /* Invalid table slot specified */
    TCNTL_ERR_NSLASTFI,                 /* No such last filter */
    TCNTL_ERR_FLTOVERF,                 /* Flow table overflow */
    TCNTL_ERR_TOUTDATED,                /* Table is outdated */
    TCNTL_ERR_FITOVERF,                 /* Filter table overflow */
    TCNTL_ERR_DUPFILT,                  /* Duplicate filter detected */
    TCNTL_ERR_FINFND,                   /* Filter not found */
    TCNTL_ERR_ATCNTL,                   /* Traffic control already enabled on dev */
    TCNTL_ERR_BUFTOOSMALL,              /* Buffer is too small */
    TCNTL_ERR_POLICY_REJECT,            /* Rejected due to policy problems */
    TCNTL_ERR_BADFTAG                   /* Bad rhandle flow tag scope */

} tcntl_error_code_t;

/*
 * Structures used for ioctl. They are all interface ioctl's and thus
 * need to start with the ifr_name entry (just like struct ifreq).
 */
/* SIOCFLOWSPEC */
struct flowreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    int cmd;                    /* I: Flowreq subcommand */
    tcntl_error_code_t error;   /* O: Internal completion code from operation */
    tcntl_rhandle_t rhandle;    /* IO: Handle of flow (new or old) */
    u_int tag_scope;            /* I: Used for modify and delete ops */
    u_int flow_table;           /* I: Flow table this request applies to. See
				      explanation of flow_buckets[] field in
				      tcntl */
    u_int nhop_len;		/* I: length of all the next-hop addresses */
    u_int IS_objects_len;	/* I: length of all the INTSERV objects */
    struct sockaddr dst;	/* I: network layer destination of the flow,
				 *    variable length struct sockaddr,
				 *    BSD4.4 style with sa_len field
				 */
    /*
     * Any number of next hop addresses go here (with total length nhop_len).
     * Type and size is defined by dst->sa_family.
     * For AF_INET: struct in_addr
     * For AF_INET6: struct in6_addr
     */
    /*
     * all of the following entries of variable length may follow here
     * (their total length is IS_objects_len):
     *
     * IS_specbody_t flowspec;
     * IS_tspbody_t  tspec;
     * IS_adsbody_t  adspec;
     * per-service adspec pieces
     */
};

/* SIOCFILTSPEC */
struct filtreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    int cmd;                    /* I: Subcommand for filreq */
    tcntl_error_code_t error;   /* O: Internal completion code for request */
    tcntl_rhandle_t rhandle;    /* I: Handle to flow for which this applies */
    u_int tag_scope;            /* I: Sanity check on handle ID */
    tcntl_fhandle_t fhandle;    /* O: Filter handle */
    u_int flow_table;           /* I: Flow table this request applies to. See
				      explanation of flow_buckets[] field in
				      tcntl */
    u_int nr_filters;		/* I: nr of filtspecs */

    /*
     * Any number of varible length
     * tcntl_filt_t filtspec;
     *
     * ADDFILTER currently expects exactly one, DELFILTER none.
     */
};

/* SIOCGHASHINFO */
struct hashreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    int cmd;                    /* I: Subcommand for filreq */
    tcntl_error_code_t error;   /* O: Internal completion code for request */
    unsigned int varlen;        /* I: Length of variable area in bytes */
    void *lookup_ctx;           /* I/O: Lookup context */
    union 
    {
      struct
	{
	  unsigned int tag_scope;       /* I: Tag scope for flows we want */
	  unsigned int flow_bucket;     /* I: Flow bucket for request */
	  unsigned int actual_handles;  /* O: Actual count of handles we got */
	  tcntl_rhandle_t last_handle;  /* I: Last handle we looked at */
	} list_flows;                    
      struct
	{
	  unsigned int flow_bucket;     /* I: Flow bucket for request */
	  unsigned int table_slots;     /* O: Slots in this table */
	  unsigned int max_entries;     /* O: Max entries we allow in table */
	  unsigned int curr_entries;    /* O: Current entries in table */
	  unsigned int flags;           /* O: Table flags */
	} list_flow_hth;
      struct
	{
	  unsigned int flow_bucket;     /* I: Flow bucket for request */
	  unsigned int flow_slot;       /* I: Slot in hash table to examine */
	  unsigned int flow_count;      /* O: Count of flows at this slot */
	  unsigned int bucket_flags;    /* O: Bucket slot flags */
	  unsigned long hit_count;      /* O: Times we've matched this slot */
	  unsigned long miss_count;     /* O: Times we've missed this slot */
	  unsigned long colission_count;/* O: Number of colissions on this slot */
	} e_flow_slot;
      struct
	{
	  unsigned int filter_bucket;   /* I: Filter bucket for request */
	  unsigned int table_slots;     /* O: Slots in this table */
	  unsigned int max_entries;     /* O: Max entries we allow in table */
	  unsigned int curr_entries;    /* O: Current entries in table */
	  unsigned int flags;           /* O: Table flags */
	} list_filt_hth;
      struct
	{
	  unsigned int filter_bucket;   /* I: Filter bucket for request */
	  unsigned int filter_slot;     /* I: Filter slot in hash table */
	  unsigned int filter_count;    /* O: Count of filters at this slot */
	  unsigned int bucket_flags;    /* O: Bucket slot flags */
	  unsigned long hit_count;      /* O: Times we've matched this slot */
	  unsigned long miss_count;     /* O: Times we've missed this slot */
	  unsigned long colission_count;/* O: Number of colissions on this slot */
	} e_filt_slot;
    } spec;
};

/* SIOCGADSPEC */
struct adspecreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    tcntl_error_code_t error;   /* O: Internal completion code for request */
    u_int adspec_len;		/* O: length of the following entry */
    /*
     * IS_adsbody_t goes here.
     * Per-service adspec pieces may follow.
     */
};

/*
 * This structure is used to extract information about a specific
 * flow.
 */
/* SIOCGLISTSPECFLOW */
struct listflowreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    tcntl_rhandle_t rhandle;    /* I: Handle of flow we'd like to examine */
    unsigned int flow_bucket;   /* I: Index of flow bucket for this flow */
    unsigned char *device_data; /* I: Pointer to user buffer for private data */
    unsigned int max_output;    /* I: Size of user's output buffer (bytes) */
    unsigned int actual_olen;   /* O: Actual bytes copied to output buffer */
    tcntl_error_code_t error;   /* O: Internal completion code for request */
    unsigned int tag_scope;     /* O: Tag scope of requested flow */
    void *tag;                  /* O: Tag of requested flow */
    unsigned int flow_class;    /* O: Flow class of requested flow */
    unsigned long refc;         /* O: Flow reference count */
};

/*
 * This structure is used to request information about a specific filter.
 */
/* SIOCGLISTSPECFILT */
struct listfiltreq
{
    char ifr_name[IFNAMSIZ];    /* I: if name, e.g. "en0" */
    u_long version;             /* I: Version of code issuing this call.
				      Should be filled in with the compiletime
				      TCNTL_INFO_VERSION */
    tcntl_rhandle_t rhandle;    /* I: Handle of flow for filter */
    unsigned int flow_bucket;   /* I: Index of flow bucket for this flow */
    tcntl_fhandle_t last_filter;/* I: ID of last filter examined */
    unsigned int max_output;    /* I: Size of user's output buffer (bytes) */
    tcntl_filtspec_t *fv;       /* I: Pointer to user buffer for filter data */
    unsigned int actual_olen;   /* O: Actual bytes copied to output buffer */
    tcntl_error_code_t error;   /* O: Internal completion code for request */
};

/*
 * Definitions for struct tcntlconfreq
 */
#define TCNTL_CONF_PARAM_SIZE  30
#define TCNTL_CONF_UNSIGNED	0
#define TCNTL_CONF_SIGNED	1

enum {
    TCNTL_CONF_OP_GET		= 1,
    TCNTL_CONF_OP_GETNEXT	= 2,
    TCNTL_CONF_OP_SET		= 3
};

/*
 * Convenience structure to deal with signed versus unsigned
 * configuration parameters.
 */
typedef union {
    u_long u_;
    long   s_;
} tcntl_conf_value_t;

/*
 * This structure is used to pass configuration information in and out
 * from the kernel
 */
/* SIOCTCNTLCONF */
struct tcntlconfreq {
    char ifr_name[IFNAMSIZ];	 /* if name, e.g. "en0" */
    u_int version;               /* Version of code issuing this call.
				    Should be filled in with the compiletime
				    TCNTL_INFO_VERSION */
    char parameter[TCNTL_CONF_PARAM_SIZE]; /* '\0' terminated string */
    tcntl_error_code_t error;   /* O: Internal completion code from operation */

    char operation;		 /* TCNTL_CONF_OPT_GET, ... */
    char sign;			 /* boolean, indicates whether
				    values are signed or
				    unsigned */
    tcntl_conf_value_t cur;	 /* current value */
    tcntl_conf_value_t min;	 /* minimum */
    tcntl_conf_value_t max;	 /* maximum */
    tcntl_conf_value_t def;	 /* default */
};


/*
 * List of different types of filters. We use this field to index
 * into the array of filter buckets off the tcntl structure
 */
enum {
    TCNTL_FILT_TABLE_IP4_WF=0,
    TCNTL_FILT_TABLE_IP4_PORT=1,
    TCNTL_FILT_TABLE_IP6_FLOW=2,
    TCNTL_FILT_TABLE_IP4_WF_RX=3,
    TCNTL_FILT_TABLE_IP4_PORT_RX=4,
    TCNTL_FILT_TABLE_IP6_FLOW_RX=5,
    TCNTL_FILT_TABLE_LAST
};

#if defined(_KERNEL)

/*
 * Define symbolic constants for indices into the tcntl_filt_conf table
 */
enum
{
    TCNTL_CONF_FLOW_TX_HASHTSIZE,
    TCNTL_CONF_FLOW_TX_MAXENTRIES,
    TCNTL_CONF_FILT_IP4_WF_HASHTSIZE,
    TCNTL_CONF_FILT_IP4_WF_MAXENTRIES,
    TCNTL_CONF_FILT_IP4_PORT_HASHTSIZE,
    TCNTL_CONF_FILT_IP4_PORT_MAXENTRIES,
    TCNTL_CONF_FILT_IP6_FLOW_HASHTSIZE,
    TCNTL_CONF_FILT_IP6_FLOW_MAXENTRIES,
    TCNTL_CONF_PARM_LAST
};

/*
 * This structure is used in the kernel to define one
 * traffic control configuration parameter
 */
struct tcntl_conf_entry {
    char parameter[TCNTL_CONF_PARAM_SIZE];	/* '\0' terminated string */
    char is_signed;				/* boolean, indicates whether
						 * values are signed or
						 * unsigned */
    tcntl_conf_value_t cur;			/* current value */
    tcntl_conf_value_t min;			/* minumum */
    tcntl_conf_value_t max;			/* maximum */
    tcntl_conf_value_t def;			/* default */
};

/*
 * This structure describes a hash bucket entry used to describe the
 * queue head of a list of filters. This structure appears in the
 * hash bucket vector (defined below).
 */
struct tcntl_filt_bucket_entry
{
BEGIN_64BYTE_CACHEBLOCK_WRITE
    simple_lock_data_t slock;          /* Access lock */
    struct tcntl_filter_entry *first;  /* First filter entry */
    u_long hit_count;                  /* Times we hit this slot */
    u_long miss_count;                 /* Times we were empty handed */
    u_long collision_count;            /* Filters skipped before match/eol */
    u_int32_t bucket_flags;            /* Flags for this bucket entry
					  see below for definitions */
    unsigned short slot_idx;           /* Index of this slot in vector */
    unsigned short pad1;               /* Pad. Free for use. MBZ. */
    u_long fid_counter;                /* Counter for unqiue IDs */
    u_long fid_limit;                  /* Limit how far we can go */
END_64BYTE_CACHEBLOCK_WRITE
};
#define TCNTL_M_FIB_OUTDATED (1<<0)    /* This slot is outdated */
#define TCNTL_M_FIB_LAPSED_COUNT (1<<1) /* Counter has lapsed */

/*
 * This structure defines a bucket header used to manage all filters
 * for a particular class on a particular network adapter (for example
 * all IPv4 port based filters). This structure is referenced by the
 * tcntl structure.
 *
 * This structure only includes one single bucket_entry. Caller is
 * expected to allocate the rest. That is, you need to allocate
 * sizeof(tcntl_filt_bucket) + ((size-1) * sizeof(tcntl_filt_bucket_entry))
 * to hold a hash vector of 'size' entries.
 */
struct tcntl_filt_bucket
{
BEGIN_64BYTE_CACHEBLOCK_READ
    u_int size;                        /* Number of tnctl_filt_bucket_entry
                                          slots in bucket vector below */
    u_int max_entries;                 /* Total entries permitted in this
					  entire bucket. This is an
					  artificial limit */
    u_int curr_entries;                /* Entries currently in all
					  tables. This is a fuzzy counter */
    u_int flags;                       /* Flags for block (see below) */
    struct tcntl_filt_bucket *oldb;    /* Pointer to old bucket else 0 */
    u_int filt_style;                  /* Style of filters used in this
					  table; TCNTL_FILT_TABLE_xxx */
    u_int pad2[9];                     /* Make 64 byte aligned */
END_64BYTE_CACHEBLOCK_READ
BEGIN_64BYTE_CACHEBLOCK_WRITE
    struct tcntl_filt_bucket_entry     /* This is the hash bucket vector. */
            bucket_vec[1];             /* It has 'size' entries in the vector;
	                                  See comments above */
END_64BYTE_CACHEBLOCK_WRITE
};
#define TCNTL_M_FIB_RESINP (1<<0)      /* Resize in progress */
#endif /* defined(_KERNEL) */

/*
 * The traffic control structure below can have device class specific
 * extensions. Each extension should have its own structure type. And
 * each extension type should have its own constant defined.
 */
enum
{
    TCNTL_DEXT_ETHER_STD,              /* Ethernet class devices */
    TCNTL_DEXT_USER_WRITTEN            /* User written and unknown type */
};

/*
 * This is a list of types of tags that we may associate with the
 * generic flow. This helps identify the scope of the tag rather
 * than just making it a 64 bit void.
 */
enum
{
    TCNTL_TAGS_ANY=0,                  /* Wildcard type match */
    TCNTL_TAGS_RSVP_SOCKET,            /* Socket handle for rsvpd */
    TCNTL_TAGS_SOCKET_PTR,             /* Generic socket (could be anyone) */
    TCNTL_TAGS_RSVP_BASEFLOW           /* RSVP baseflow */
};

/*
 * List of different types of flows. We use this field to index
 * into the array of flow buckets off the tcntl structure
 */
enum {
    TCNTL_FLOW_TABLE_TX=0,
    TCNTL_FLOW_TABLE_RX=1,
    TCNTL_FLOW_TABLE_LAST
};

/*
 * This structure defines a generic flow. This structure is managed
 * by the generic traffic control logic. A device specific extension
 * to this structure accomodates Ethernet class support.
 */
#if defined(_KERNEL)
struct tcntl_genflow_bucket_entry;      /* Forward declaration */
struct tcntl_genflow
{
BEGIN_64BYTE_CACHEBLOCK_READ
    struct tcntl_genflow *next_flow;    /* Next flow in bucket */
    struct tcntl_filter_entry *first_filter; /* First filter in flow */
    tcntl_rhandle_t extern_id;          /* Flow ID passed to user mode */
    void *tag;                          /* Opaque tag used with flow */
    void *flow_ext;                     /* Device specific extension */
    u_int32_t flags;                    /* Flags for this flow (see below) */
    u_char flow_class;                  /* Type of flow (see above) */
    u_char tag_scope;                   /* Type of tag (see above) */
    struct tcntl_genflow_bucket_entry *flow_bucket; /* Backlink to bucket */
    u_long refc;                        /* Ref count on this flow */
END_64BYTE_CACHEBLOCK_READ
};
#define TCNTL_M_FLOW_MDEL (1<<0)        /* Flow marked for delete */
#define TCNTL_M_FLOW_ORPHANED (1<<1)    /* Flow is on orphan list */
#define TCNTL_M_FLOW_NO_TRANSPORT (1<<2)/* Flow has no transport data */

/*
 * This structure describes a hash bucket entry used to describe the
 * queue head of a list of flows. It is almost identical to the structure
 * used for filters.
 */
struct tcntl_genflow_bucket_entry
{
BEGIN_64BYTE_CACHEBLOCK_WRITE
    simple_lock_data_t slock;          /* Access lock */
    struct tcntl_genflow *first;       /* First flow entry */
    u_long hit_count;                  /* Times we hit this slot */
    u_long miss_count;                 /* Times we were empty handed */
    u_long collision_count;            /* Filters skipped before match/eol */
    u_int32_t bucket_flags;            /* Flags for this bucket entry
					  see definition below */
    unsigned short flow_table_idx;     /* Index within flow_bucket[] of
					  tcntl to hosting
					  tcntl_flow_bucket. */
    unsigned char pad1[2+16];          /* Pad to 64 bits */
END_64BYTE_CACHEBLOCK_WRITE
};
#define TCNTL_M_FLB_OUTDATED (1<<0)    /* This slot is outdated */

/*
 * This structure defines a bucket header used to manage all flows
 * for a particular class on a particular network adapter. There are
 * currently only two classes of flows: incoming and outgoing. This
 * structure is referenced by the tcntl structure.
 *
 * This structure only includes one single bucket_entry. Caller is
 * expected to allocate the rest. That is, you need to allocate
 * sizeof(tcntl_flow_bucket) + ((size-1) * sizeof(tcntl_genflow_bucket_entry))
 * to hold a hash vector of 'size' entries.
 */
struct tcntl_flow_bucket
{
BEGIN_64BYTE_CACHEBLOCK_READ
    u_int size;                        /* Number of tnctl_genflow_bucket_entry
                                          slots in bucket vector below */
    u_int max_entries;                 /* Total entries permitted in this
					  entire bucket. This is an
					  artificial limit */
    u_int curr_entries;                /* Entries currently in all
					  tables. This is a fuzzy counter */
    u_int flags;                       /* Flags -- see below */
    struct tcntl_flow_bucket *oldb;    /* Pointer to old bucket else 0 */
    u_int pad1[5*2];                   /* Make 64 byte aligned */
END_64BYTE_CACHEBLOCK_READ
BEGIN_64BYTE_CACHEBLOCK_WRITE
    struct tcntl_genflow_bucket_entry  /* This is the hash bucket vector. */
            bucket_vec[1];             /* It has 'size' entries in the vector;
	                                  See comments above */
END_64BYTE_CACHEBLOCK_WRITE
};
#define TCNTL_M_FLB_RESINP (1<<0)      /* Table resize in progress */

/*
 * Types that define the routines used in the interface between
 * the generic traffic control code and the device specific support.
 */
struct tcntl; /* Forward declaration */
typedef tcntl_error_code_t (*tcntl_admit_flow_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				struct flowreq *flowreq,
				unsigned int flowreq_len,
				unsigned int flow_table,
			        void *nhops,
				IS_specbody_t *i_spec,
				IS_tspbody_t *i_tsp,
			        IS_adsbody_t *i_ads,
				struct tcntl_genflow *gflow);

typedef tcntl_error_code_t (*tcntl_modify_flow_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				struct flowreq *flowreq,
				unsigned int flowreq_len,
				unsigned int flow_table,
			        void *nhops,
				IS_specbody_t *i_spec,
				IS_tspbody_t *i_tsp,
			        IS_adsbody_t *i_ads,
				struct tcntl_genflow *gflow);

typedef tcntl_error_code_t (*tcntl_remove_flow_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				unsigned int flow_table,
				struct tcntl_genflow *gflow);

typedef tcntl_error_code_t (*tcntl_examine_flow_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				unsigned int flow_table,
				struct tcntl_genflow *gflow,
				unsigned int flow_params_maxsize,
				void *flow_params,
				unsigned int *actual_flow_params);

typedef tcntl_error_code_t (*tcntl_get_adspec_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				unsigned int flow_table,
				struct adspecreq *adspec,
				unsigned int adspec_input_len);

typedef tcntl_error_code_t (*tcntl_device_initialize_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl);

typedef tcntl_error_code_t (*tcntl_device_rundown_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl);

typedef tcntl_error_code_t (*tcntl_config_req_rtn_t)(
				struct ifnet *ifp,
				struct tcntl *tcntl,
				struct tcntlconfreq *confreq,
			        int index,
				tcntl_conf_value_t);

/*
 * This is the generic traffic control structure. It is referenced from
 * the if_tcntl field of the ifnet structure. Device class specific
 * information can be added to this structure through an extension
 * pointer.
 *
 * As it stands right now, the tcntl structure maintains information
 * to handle packet classification.
 */
struct tcntl
{
BEGIN_64BYTE_CACHEBLOCK_READ /* These are two read blocks */
    tcntl_config_req_rtn_t rtn_config;         /* Set parameter value */
    tcntl_device_rundown_rtn_t rtn_rundown;    /* Rundown device */
    tcntl_get_adspec_rtn_t rtn_get_adspec;     /* Get ADSPEC */
    tcntl_examine_flow_rtn_t rtn_examine_flow; /* Examine flow */
    tcntl_remove_flow_rtn_t rtn_remove_flow;   /* Remove flow */
    tcntl_modify_flow_rtn_t rtn_modify_flow;   /* Modify flow params */
    tcntl_admit_flow_rtn_t rtn_admit_flow;     /* Admit new flow */
    struct tcntl_conf_entry *conf_table;/* array for interface-specific
					 * configuration values,
					 * ends with all-zero entry */
    struct tcntl_genflow *rsvp_rhandle; /* reservation for
					 * RSVP messages */
    struct tcntl_filt_bucket *filt_buckets[TCNTL_FILT_TABLE_LAST];
                                        /* Filter hash tables */
    struct tcntl_flow_bucket *flow_buckets[TCNTL_FLOW_TABLE_LAST];
                                        /* Flow hash tables */
    void *dev_ext;                      /* Device specific extension */
    u_int dev_ext_type;                 /* Type of extension */
    u_int pad1[11];                     /* Free for use. Round to next */

END_64BYTE_CACHEBLOCK_READ

BEGIN_64BYTE_CACHEBLOCK_WRITE
    simple_lock_data_t tcntl_lock;      /* Simple lock protecting bucket
					   links and possibly more */
    u_long filt_id;                     /* Next available filter ID. 
					   These are allocated in block */
    u_long flow_id;                     /* Next available flow ID.
					   These are allocated in block */
    u_int pad2[2*5];                    /* Free for use. Round to next
					   cache block */
END_64BYTE_CACHEBLOCK_WRITE
};

/*
 * Parts to IPv4 Wildcard filter
 */
union ip4_wf_filter_entry {
    struct {
	struct in_addr dest;
	unsigned short dest_port;
	unsigned char proto;
	unsigned char unused;
    } s;
    unsigned long k;
};

/*
 * Parts to IPv4 port based filter
 */
union ip4_port_filter_entry {
    struct {
	struct in_addr src;
	struct in_addr dest;
	unsigned short src_port;
	unsigned short dest_port;
	unsigned char proto;
	unsigned char unused[3];
    } s;
    struct {
	unsigned long key1;
	unsigned long key2;
    } k;
};

/*
 * Parts to IPv6 flow based filter
 */
struct ip6_flow_filter_entry {
    struct in6_addr src;
    unsigned int flowlabel;
};

/*
 * The filter entry structure describes information about one single
 * filter. Filters are maintained in filter buckets, each with one
 * filter class (although this structure is capable of expressing them
 * all).
*/
struct tcntl_genflow; /* Forward declaration */
struct tcntl_filt_bucket_entry; /* Forward declaration */
struct tcntl_filter_entry
{
    struct tcntl_filter_entry *filt_next;   /* Next filter in bucket */
    tcntl_fhandle_t handle;                 /* This filter's ID/handle */
    struct tcntl_filt_bucket_entry *filt_bucket; /* Filter bucket we're in */
    struct tcntl_genflow *flow;             /* Flow this filter belongs to */
    struct tcntl_filter_entry *flow_next;   /* Next filter with flow */
    union {
        union ip4_wf_filter_entry   ip4_wf;
        union ip4_port_filter_entry ip4_port;
        struct ip6_flow_filter_entry ip6_fl;
    } filter;
    u_int32_t pad1[1];                      /* Make us full cache block */
};

#endif /* defined(_KERNEL) */

#endif /* !defined(__INCLUDE_IP_TCNTL_STRUCT) */
