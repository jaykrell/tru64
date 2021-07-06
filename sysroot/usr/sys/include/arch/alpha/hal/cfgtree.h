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
 * @(#)$RCSfile: cfgtree.h,v $ $Revision: 1.1.35.4 $ (DEC) $Date: 2002/04/09 00:08:42 $
 */
#include <kern/lock.h>
#include <kern/queue.h>
#include <dec/binlog/binlog.h>		/* for TLV definition */
#include <io/common/devdriver.h>
#ifndef __ARCH_ALPHA_HAL_CFGTREE_H__
#define __ARCH_ALPHA_HAL_CFGTREE_H__

#ifndef __cplusplus

#define	CFGTREE_VERSION_MAJOR    6  /* revision represented by this header */

#define CFGTREE_VERSION_MAJOR_6

extern unsigned short	gct_version_major;
extern unsigned short	gct_version_minor;
extern unsigned long	cfgtree_root;
extern char *cfgtree_node_transition_strings[];


/*
 * Generic Data Types for Configuration Tree structure members
 */
typedef char            byte;
typedef unsigned char   ubyte;	/* no offence intended */

typedef char            int8;
typedef unsigned char   uint8;
typedef short		int16;
typedef unsigned short	uint16;
typedef int		int32;
typedef unsigned int	uint32;
typedef long		int64;
typedef unsigned long	uint64;

/*
 * Config tree offset
 */
typedef int64 CFGTREE_OFFSET;

/*
 * Configuration Tree Node ID:
 * A 64-bit unsigned integer -- node type specific
 */
typedef uint64 CFGTREE_ID;
#define CFGTREE_NODE_ID_NONE (-1)

/*
 * This is how we will abstract the different nodes' versions.
 */
typedef uint64 cfgtree_node_t;

/*
 * FRU Descriptor ID
 */
typedef union {
	uint64  fru_id;           /* Full FRU ID */
	struct {
		uint32 site_loc : 8;  /* Customer Site Code, if any */
		uint32 cab_id   : 8;  /* Cabinet ID */
		uint32 position : 8;  /* Position in cabinet */
		uint32 chassis  : 8;  /* Chassis ID */
		uint32 assembly : 8;  /* Assembly ID */
		uint32 subassem : 8;  /* Subassembly ID */
		uint32 slot     :16;  /* Slot ID */
	} fru_id_fields;
} FRU_DESC_ID;

/*
 * Configuration Tree Node flags
 *
 * moved to a separate named structure so that they can be embedded in other
 * structures, besides the node itself.
 */
typedef struct _cfgtree_node_flags  {
    unsigned node_hardware       : 1; /* Node represents hardware */
    unsigned node_hotswap        : 1; /* Hardware can be hotswapped */
    unsigned node_unavailable    : 1; /* Node/Hardware is not avail */
    unsigned node_hw_template    : 1; /* Node is a template device */
    unsigned node_initialized    : 1; /* Partition is initialized */
    unsigned node_cpu_primary    : 1; /* Node is a primary CPU */
    unsigned node_in_console     : 1; /* Node is a CPU in console mode */
    unsigned node_pwr_down       : 1; /* Node is Powered Down */
    unsigned node_pwr_ctrl_point : 1; /* Node can be independently powered */
    unsigned node_present        : 1; /* Hardware is physically present */
    unsigned node_reassignable   : 1; /* Hardware is reassignable */
    unsigned node_hard_partition : 1; /* Node = point of hard partitioning */
    unsigned node_disabled       : 1; /* Disabled, regardless of power */
    unsigned node_updating       : 1; /* Node is being updated */
    unsigned node_unhealthy      : 1; /* Node is "unhealthy" */
    unsigned node_attention      : 1; /* Node requires attention */
    unsigned node_ins_ext        : 1; /* CompactPCI Lever Lifted */
    unsigned node_rsrvd_17_31   : 15; /* Unused bits in first longword */
    unsigned node_rsrvd_32_63   : 32; /* Unused bits in second longword */
} CFGTREE_NODE_FLAGS;

/* We need the attention bit in a "maskable" format, as well */
#define CFGTREE_NODE_ATTENTION (1 << 15)



typedef struct gct_node {
    uint8		type;          /* Node type */
    uint8		subtype;       /* Type-specific subtype */
    uint16		size;          /* Size of node including header */
    uint32		hd_extension;  /* Header extension for FRU 
					  subpackets */
    uint64		owner;
    uint64		current_owner;
    CFGTREE_ID		id;            /* Type-specific ID */
    CFGTREE_NODE_FLAGS	flags;

    uint16		rev;                /* Revision of this node */
    uint16		change_counter;     /* Change bit */
    uint32		rsvd1;              /* Reserved */

    uint64		saved_owner;  /* Config binding */
    uint64		affinity;     /* Affinity (performance) binding */
    uint64		parent;       /* Parent node */
    uint64		next_sib;     /* Next sibling node */
    uint64		prev_sib;     /* Previous sibling node */
    uint64		child;        /* Child node */

    uint64		fw_usage;     /* SRM/Firmware usage */
    uint64		os_usage;     /* OS usage */
    FRU_DESC_ID		fru_id;       /* ID of FRU, if any */
    uint32		checksum;     /* Checksum field -- not currently used */
    uint32		magic;        /* Valid bits 'GLXY' */
} GCT6_NODE;


/* 
 * The following node definition was used in the v5.x config tree, and
 * is included here to allow us to walk a v5 config tree.  
 *
 * Note that full functionality is not a requirement.  Hotswap and flags
 * checking are not needed now.  Instead, we are just aiming for
 * accurate tree walking and type//subtype/ID extraction.
 */
typedef struct gct5_node {
    uint8		type;
    uint8		subtype;
    uint16		size;
    uint32		hd_extension;
    uint32		owner;
    uint32		current_owner;
    CFGTREE_ID		id;
    CFGTREE_NODE_FLAGS	flags;

    /* The following are all 32-bit pointers in the v5 cfgtree (sigh) */
    uint32		config;
    uint32		affinity;
    uint32		parent;
    uint32		next_sib;
    uint32		prev_sib;
    uint32		child;

    uint32		depth_use;
    uint32		magic;
} GCT5_NODE;

typedef struct gct_node *gct_node_t;
#define GCT_VALID		'GLXY'       /* magic = 0x59584C47 */
#define GCT_NODE_NULL		((gct_node_t)NULL)

/*
 * The cfgtree header was abolished in V6, but we
 * might still use the structure to pick out the major and minor 
 * version info.
 */
typedef struct _gct5_hdr {
    ulong buffer_cksum;
    int buffer_size;
    union {
	unsigned int rev_full;
	struct {
	    unsigned short rev_major;
	    unsigned short rev_minor;
	} sub;
    } revision;
    unsigned char galaxy_enable;
    unsigned char galaxy_callback;
    unsigned char buffer_reserved[46];
} GCT5_HDR;
    
#define GCT5_HDR_SIZE sizeof(GCT5_HDR)
#define GCT6_HDR_SIZE 0

#define GCT_HDR_SIZE(version)	\
(					\
    (version == 5) ?			\
        (GCT5_HDR_SIZE)		\
    :					\
        (GCT6_HDR_SIZE)		\
)

#define GCT_REV_MAJOR(ROOT) \
	(((GCT5_HDR *)ROOT)->revision.sub.rev_major)
#define GCT_REV_MINOR(ROOT) \
	(((GCT5_HDR *)ROOT)->revision.sub.rev_minor)


/*
 * Root node in v5 tree is offset by the size of the header  
 * In v6, there is no header, and the root node is the fru table
 * plus offset "0"
 */
#define GCT_GET_ROOT_NODE() (cfgtree_root)

/*
 * ===========================================================================
 * All-purpose macro:  Get a config node field from a gct_node_t
 *
 * This macro turns arguments (a,b) into (a->b), with a little
 * casting based on the firmware cfgtree's version.
 */
#define GCT_GET_MEMBER(node, member)		\
(						\
    (gct_version_major==5) ?			\
        (((GCT5_NODE *)node)->member)		\
    :						\
        (((GCT6_NODE *)node)->member)		\
)


/*
 * ===========================================================================
 * All purpose macro:  Set a config node field from a gct_node_t
 *
 * This macro turns arguments (a,b, c) into (a->b = c), with a little
 * casting based on the firmware cfgtree's version.  
 * Note that it cannot know or check the target member's size 
 * (In other words, don't use an 'a', 'b', and 'c' where 'a->b' is a smaller 
 * C-language data size than 'c')
 *
 * TODO: 
 * Consider adding another argument that is a "cast".  e.g. "char" to prevent
 * corruption.
 */
#define GCT_SET_MEMBER(node, member, value)	\
    GCT_GET_MEMBER(node, member) = value


/*
 * ===========================================================================
 * Macro:  validate node magic 
 */
#define GCT_GET_MAGIC(NODE)  (GCT_GET_MEMBER(NODE, magic))

#define GCT_IS_NODE_VALID(NODE) ((NODE != NULL) && (GCT_GET_MAGIC(NODE) == GCT_VALID)) 

/*
 * Macro:  next linear node in tree space:  current node + size ...
 *
 */
#define GCT_NEXT_NODE(NODE)	(GCT_GET_MEMBER(NODE, size) + NODE)
    
/*
 * Macros for testing and following tree links
 */
#define GCT_HANDLE2NODE(offset)	(gct_node_t)(cfgtree_root + offset) 

#define GCT_NODE2HANDLE(NODE)	((int64)(NODE)-(int64)(cfgtree_root))

#define GCT_GET_SIZE(NODE)	(GCT_GET_MEMBER(NODE, size))

#define GCT_GET_REV(NODE)	(GCT_GET_MEMBER(NODE, rev))

#define GCT_GET_OWNER(NODE)				\
(							\
    (GCT_GET_MEMBER(NODE, owner)!= 0) ?			\
        (GCT_HANDLE2NODE(GCT_GET_MEMBER(NODE, owner)))	\
    :							\
	(0)						\
)

#define GCT_GET_CURR_OWNER(NODE) 				\
(								\
    (GCT_GET_MEMBER(NODE, current_owner)!= 0) ?			\
        (GCT_HANDLE2NODE(GCT_GET_MEMBER(NODE, current_owner)))	\
    :								\
	(0)							\
)

#define GCT_GET_SAVED_OWNER(NODE)				\
(								\
    (GCT_GET_MEMBER(NODE, saved_owner)!= 0) ?			\
        (GCT_HANDLE2NODE(GCT_GET_MEMBER(NODE, saved_owner)))	\
    :								\
	(0)							\
)
   
#define GCT_GET_AFFINITY(NODE)					\
(								\
    (GCT_GET_MEMBER(NODE, affinity)!= 0) ?			\
        (GCT_HANDLE2NODE(GCT_GET_MEMBER(NODE, affinity)))	\
    :								\
	(0)							\
)

/*
 * Only V6 nodes have these fields
 */
#define GCT_GET_OS_USAGE(NODE) (((GCT6_NODE *)NODE)->os_usage)


#define GCT_SET_OS_USAGE(NODEIN, value) \
( \
    prom_update_os_usage(GCT_NODE2HANDLE(NODEIN), \
                         (uint64)value, \
                         CONS_NO_TREE_CHANGE, \
                         GCT_GET_CHANGE_COUNTER(NODEIN)))

#define GCT_GET_CHANGE_COUNTER(NODE) (((GCT6_NODE *)NODE)->change_counter)

#define GCT_IS_ROOT(NODE)	\
    (gct_get_type(NODE) == CFGTREE_NODE_ROOT)

#define GCT_IS_HW_ROOT(NODE)	\
    (gct_get_type(NODE) == CFGTREE_NODE_HW_ROOT)

#define GCT_IS_HW(NODE)		\
    ((gct_get_flags(NODE)).node_hardware == 1)

/*
 * ===========================================================================
 * Macros for testing, locating and accessing node header extension
 * and system resource configuration subpackets
 */
#define GCT_GET_HD_EXT(NODE) \
   (CFGTREE_HD_EXT) \
	((uint64)NODE + (uint64)GCT_GET_MEMBER(NODE, hd_extension))

#define GCT_HD_EXT_FIRST_FRU(EXT) (GCT_HANDLE2NODE(GCT_HD_EXT_GET_MEMBER(EXT, fru_handle)))

#define GCT_HD_EXT_NUM_SUBPACKETS(EXT) (GCT_HD_EXT_GET_MEMBER(EXT, subpkt_count))
#define GCT_HD_EXT_NUM_FRU(EXT)        (GCT_HD_EXT_GET_MEMBER(EXT, fru_count))

#define GCT_HD_EXT_FIRST_SUBPACKET(NODE, EXT) \
        (FRU_SRC_SUBPKT_HDR *)((uint64)NODE + (uint64)GCT_HD_EXT_GET_MEMBER(EXT, subpkt_offset))

#define GCT_HD_EXT_NEXT_SUBPACKET(SP) \
	(FRU_SRC_SUBPKT_HDR *)((SP) + (SP)->length)


/*
 * Configuration Tree Root Node:  "Isn't that special!"
 */
typedef struct gct6_root_node {
    GCT6_NODE hd;
    ulong lock;			/* Software lock			*/
    ulong transient_level;	/* Update counter (in prog)		*/
    ulong current_level;	/* Update counter (actual)		*/
    ulong console_req;		/* Memory required for console		*/
    ulong min_alloc;  		/* Minimum memory allocation		*/
    ulong min_align;		/* Memory allocation alignment		*/
    ulong base_alloc;		/* Base memory min allocation		*/
    ulong base_align; 		/* Base memory alloc alignment		*/
    ulong max_phys_address;	/* Largest Physical Address		*/
    ulong mem_size;		/* Total current memory size		*/
    ulong platform_type;	/* Type code of platform		*/
    ulong platform_name;	/* Offset to name string		*/
    ulong primary_instance;	/* Handle of GALAXY Primary Partiion	*/
    ulong first_free;		/* First free byte of tree pool		*/
    ulong high_limit;		/* High address limit for nodes		*/
    ulong lookaside;		/* Lookaside list for node deletion	*/
    int   available;		/* Amount of bytes in pool		*/
    int   max_partition;	/* Max partitions			*/
    ulong partitions;		/* Offset to partition ID map		*/
    ulong communities;		/* Offset to community ID map		*/
    ulong bindings;		/* Offset to array of bindings		*/
    int   max_platform_partition; /* Max part platform supports 	*/
    int   max_desc;       /* Max memory descriptors			*/
    char  galaxy_id [16];	/* Galaxy ID				*/
    char  galaxy_id_pad [4];	/* Pad ID with a longword of bytes	*/
    union {
        uint64 root_flags;
        struct {
            unsigned partitions_capable  : 1; /* console supports partitions */
            unsigned partition_callbacks : 1; /* console supports partitioning 
						 callbacks */
            unsigned rootflag_reserved1  : 30;
            unsigned rootflag_reserved2  : 32;
	} rootflag_bits;
    } rootflag_union;
} GCT6_ROOT_NODE;

typedef struct gct5_root_node {
    GCT5_NODE			hd;
    ulong			lock;
    ulong			transient_level;
    ulong			current_level;
    ulong			console_req;
    ulong			min_alloc;
    ulong			min_align;
    ulong			base_alloc;
    ulong			base_align;
    ulong			max_phys_address;
    ulong			mem_size;
    ulong			platform_type;
    int				platform_name;
    ulong			primary_instance;
    ulong			first_free;
    ulong			high_limit;
    ulong			lookaside;
    ulong			available;
    unsigned int		max_partition;
    int				partitions;
    int				communities;
    unsigned int		max_platform_partition;
    unsigned int		max_fragments;
    unsigned int		max_desc;
    char			galaxy_id[16];
    char			galaxy_id_pad[4];
    int				bindings;
} GCT5_ROOT_NODE;


/*
 * Macros for Root Node access
 */
#define GCT_PLATFORM_TYPE(RN) ((RN)->platform_type & 0x0ffffffff)
#define GCT_PLATFORM_VARN(RN) ((RN)->platform_type >> 32)
#define GCT_PLATFORM_NAME(RN) ((char *)(RN) + (RN)->platform_name)



typedef struct gct_hd_ext {
    uint32	fru_count;
    uint32	reserved;
    uint64	fru_handle;
    uint32	subpkt_count;
    uint32	subpkt_offset;
} GCT6_HD_EXT;

typedef struct gct5_hd_ext {
    uint32	fru_count;
    uint32	fru_handle;
    uint32	subpkt_count;
    uint32	subpkt_offset;
} GCT5_HD_EXT;

typedef unsigned long gct_hd_ext_t;

/*
 * This clever macro takes advantage of the preprocessor's ability
 * to substitute without question.
 *
 * This macro turns arguments (a,b) into (a->b), with a little
 * casting based on the firmware cfgtree's version.
 */
#define GCT_GET_HD_EXT_MEMBER(ext, member)	\
(						\
    (gct_version_major == 5) ?			\
        (((GCT5_HD_EXT *)ext)->member)		\
    :						\
        (((GCT6_HD_EXT *)ext)->member)		\
)
       
/*
 * ===========================================================================
 * Interesting Type specific Structures
 */

/*
 * Memory Subsystem Node
 */
typedef struct _gct_memory_subsystem_node_body {
	uint64		min_pa;	/* lowest physical address for this memory */
	uint64		max_pa;	/* highest physical address for this memory */
} GCT_MEMORY_SUBSYSTEM_NODE_BODY;

/*
 * Memory Configuration Descriptor
 */
typedef struct _gct_mcd {
	uint64 mcd_checksum;		/* MCD structure checksum */
	uint64 mcd_usage_link;		/* Offset to next MCD */
	uint32 mcd_start_pfn;		/* First PFN in range */
	uint32 mcd_pfn_count;		/* Number of PFNs in range */
	uint32 mcd_tested_pfn_count;	/* Number of PFNs tested */
	union {
		uint32 _mcd_usage_flags;/* Memory usage bits (See below) */
		struct {
			unsigned _mcd_usage_console : 1;/* Console memory */
			unsigned _mcd_usage_nvram : 1;	/* Software (NVRAM) */
			unsigned _mcd_usage_shared : 1;	/* Shared memory */
			unsigned _mcd_usage_fixed : 1;	/* "FIXED" memory */
			unsigned _mcd_rsrvd_4_31 : 28;	/* Unused bits */
		} mcd_usage_bits;
	} mcd_usage_union;

	uint64 mcd_bitmap_pa;		/* PA of bitmap for PFN range */
	uint64 mcd_bitmap_checksum;	/* Checksum of tested memory bitmap */

	uint64 mcd_mbz_1;		/* padding */
	uint64 mcd_mbz_2;
	uint64 mcd_mbz_3;
	uint64 mcd_mbz_4;
} GCT_MCD;	
#define mcd_usage_flags   mcd_usage_union._mcd_usage_flags
#define mcd_usage_console mcd_usage_union.mcd_usage_bits._mcd_usage_console
#define mcd_usage_nvram   mcd_usage_union.mcd_usage_bits._mcd_usage_nvram
#define mcd_usage_shared  mcd_usage_union.mcd_usage_bits._mcd_usage_shared
#define mcd_usage_fixed   mcd_usage_union.mcd_usage_bits._mcd_usage_fixed

/*
 * Memory Descriptor Node
 */

typedef struct _gct_mem_desc_node_body {
	GCT_MCD mem_cluster_desc;	/* memory cluster descriptor */
} GCT_MEM_DESC_NODE_BODY;

/*
 * I/O Processor Node
 */
typedef struct _gct_iop_node_body {
	uint64 min_io_pa;		/* min phys addr in i/o space */
	uint64 max_io_pa;		/* max phys addr in i/o space */
} GCT_IOP_NODE_BODY;

/*
 * Hard Partition Node
 */
typedef struct _gct_hard_partition_node_body {
	uint32 hard_flags;		/* Hard Partition flags [see below] */
	uint32 hard_partition_mbz1;	
	uint64 hard_partition_mbz2;	
} GCT_HARD_PARTITION_NODE_BODY;
 
/*
 * Hard Partition Flags:
 */
#define GCT_ACCEPT_HW_UNSOLICITED 0x01	/* can accept new/reassigned hardware */

/*
 * Soft Partition Node
 */
typedef struct _gct_partition_node_body {
	uint64    hwrpb;		/* phys addr of HWRPB */
	uint64    incarnation;		/* boot/restart counter */
	uint64    priority;		/* TBD */
	int32     os_type;		/* Type of OS that is/will be loaded */
	uint32    part_flags;		/* Soft Partition flags [see below] */
	char      instance_name[128];
} GCT_PARTITION_NODE_BODY;

/*
 * Soft Partition Flags:
 */
#define GCT_PART_CAN_ACCEPT_MEM      0x01
#define GCT_PART_CAN_ACCEPT_CPU      0x02
#define GCT_PART_CAN_ACCEPT_IO       0x04
#define GCT_PART_CHANGE_NOTIFY       0x08 /* Notify Instance of Tree change */
#define GCT_PART_HW_CHANGE_NOTIFY    0x10 /* Notify Instance of HW change */
#define GCT_NODE_PART_ERROR_TARGET   0x20 /* */
#define GCT_NODE_PART_ERROR_PENDING  0x40 /* */


/*
 * ===========================================================================
 * FRU Branch of Configuration/FRU Tree:
 */
#if	!defined(_KERNEL)	/* [ defined in binlog.h */
typedef struct _tlv {
	uint16	tlv_tag;	/* data type */
	uint16	tlv_length;	/* length of value in bytes */
	uint8	tlv_val[1];	/* 1st byte of value */
} TLV;
#else  /* ] [ */
/*
 * in binlog.h TLV, tag, length are in embedded TL structure
 */
#define tlv_tag    tl.type
#define tlv_length tl.length

#endif /* ] TLV struct definitions */

enum _tlv_tags {
	TLV_TAG_UNKNOWN=0,
	TLV_TAG_ISO_LATIN1=1,
	TLV_TAG_QUOTED,		/* = 2 */
	TLV_TAG_BINARY,		/* = 3 */
	TLV_TAG_UNICODE16	/* = 4 */
};

#define FRU_TLV(CP) ((TLV *)(CP))	/* (TLV *) from (char *) */
#define TLV_ROUNDUP(TLV) (((uint64)(TLV) + 7) & ~7) /* quadword align */
#define NEXT_TLV(TP) \
	((TLV *)TLV_ROUNDUP(TP->tlv_val + (TP->tlv_length)))

/*
 * GCT_FRU_INFO contains five (5) TLVs ...
 */
typedef struct _gct_fru_info {
	uint32  diag_flag;
	uint32  diag_failure_info;
	TLV     first_tlv;		/* 1st of (5) TLVs */
	        /* 1. Manufacturer */
	        /* 2. Model        */
	        /* 3. Part Number */
	        /* 4. Serial Number */
	        /* 5. Firmware Revision */
} GCT_FRU_INFO;
#define CFGTREE_N_FRU_INFO_TLV 5

struct gct_fru_desc_node{
  GCT6_NODE	hd_fru_desc;
  GCT_FRU_INFO	fru_desc_info;
}; 

struct gct5_fru_desc_node{
  GCT5_NODE	hd_fru_desc;
  GCT_FRU_INFO	fru_desc_info;
}; 

typedef unsigned long gct_fru_desc_node_t;

#define GCT_FRU_DESC_GET_FRU_DESC_PTR(node)				\
(								\
    (gct_version_major == 5) ?					\
        (void *)&(((struct gct5_fru_desc_node *)node)->hd_fru_desc)	\
    :								\
        (void *)&(((struct gct_fru_desc_node *)node)->hd_fru_desc)	\
)

/*
 * ===========================================================================
 * Subpackets
 */


typedef struct sys_res_config_subpkt_hdr {
    uint16 length;
    uint16 class;	/* see enum SUBPKT_CLASS */
    uint16 type;	/* class dependent type */
    uint16 rev;
    int32 diag_flag;
    int32 diag_failure_info;
} FRU_SRC_SUBPKT_HDR;

/*
 * Diagnostic Flag:
 */
#define	DIAG_FLAG_ST_FAILED 0x01
#define	DIAG_FLAG_ST_TDD    0x02
#define	DIAG_FLAG_ST_SDD    0x04

#define DIAG_FLAG_ST_CHK_0_62    0x10
#define DIAG_FLAG_ST_CHK_64_126  0x20
#define DIAG_FLAG_ST_CHK_128_254 0x40
#define DIAG_FLAG_ST_SYS_SN_MISMATCH 0x80

/*
 * Type of sys_res_config_subpkt
 */
#define SUBPKT_POWER		0x8
#define SUBPKT_COOLING		0x9
#define SUBPKT_SENSOR		0x2a
#define SUBPKT_SYSEVT		0x2b

typedef struct pe_pbm_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	int16 reset_configuration;
	int16 present_0_status;
	int16 present_1_status;
	int16 power_control_status;
	int16 rest_control_status;
	int16 interrupt_sys_event;
	int16 hardware_interrupt_ctrl;
	int16 pio_data_0;
} GCT_SUBPKT_PE_PBM;

typedef struct hose_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	int64 pca_what_am_i;
	int64 ne_what_am_i;
	int64 fe_what_am_i;
	int64 pbm_pci_present_0;
	int64 pbm_pci_present_1;
} GCT_SUBPKT_HOSE;

typedef struct sensor_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	int32        fru_count;
	int32        reserved;
	uint64	     fru;
	int64        sr_offset;		/* shared RAM offset */
	int32        sensor_class;	/* temp, power, fan, ... */
	int32        properties;	/* see definitions below */
} GCT6_SENSOR_SUBPKT;

typedef struct _gct5_sensor_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	int	fru_count;
	int	fru;
	uint64	sr_offset;
	int	sensor_class;
	int	properties;
} GCT5_SENSOR_SUBPKT;

typedef unsigned long  cfgtree_sensor_t;
typedef unsigned long  gct_sensor_t;

/*
 * This clever macro takes advantage of the preprocessor's ability
 * to substitute without question.
 *
 * This macro turns arguments (a,b) into (a->b), with a little
 * casting based on the firmware cfgtree's version.
 */
#define GCT_GET_SENSOR_MEMBER(sensor, member)	\
(						\
    (gct_version_major == 5) ?			\
        (((GCT5_SENSOR_SUBPKT *)sensor)->member)\
    :						\
        (((GCT6_SENSOR_SUBPKT *)sensor)->member)\
)

typedef struct sysevt_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	uint64  sysevt_id;
	uint64  sysevt_offset;	/* Shared RAM offset of system event log */
} GCT_SUBPKT_SYSEVT;

/*
 * Configuration tree and FRU table information passed to
 * hardware management for various reasons
 */
typedef struct ctft_info {
    uint8  cfg_type;
    uint8  cfg_subtype;
    uint64 cfg_id;
    uint8  fru_type;
    uint8  fru_subtype;
    uint64 fru_id;
} CTFT_INFO;

/* 
 * Sensor subpacket-specific class field values
 */
typedef enum _cfgtree_sensor_class {
	SENSOR_CLASS_UNDEFINED0 = 0,
	SENSOR_CLASS_FAN =	1,
	SENSOR_CLASS_TEMP =	2,
	SENSOR_CLASS_ACPWR =	3,
	SENSOR_CLASS_DCPWR =	4,
	SENSOR_CLASS_BATTPWR =	5
} CFGTREE_SENSOR_CLASS;

#define SENSOR_PROP_STATUS    0x1
#define SENSOR_PROP_VALUE     0x2
#define SENSOR_PROP_WRITEABLE 0x4
#define SENSOR_PROP_UPPERLONG 0x8
#define SENSOR_PROP_MASK      0xf

#define SENSOR_STATUS_OFFSET(SUBPKT) (SUBPKT->sr_offset & 0x0ffffffff)
#define SENSOR_VALUE_OFFSET(SUBPKT)  (SUBPKT->sr_offset >> 32)

/*
 * Backward compatibility issues:
 * These symbols are already being referenced elsewhere in the
 * OS...though the numeric values are the same.
 * Remove them if compiler-compatibility is not an issue.
 */
#define SENSOR_FAN_CLASS		SENSOR_CLASS_FAN
#define SENSOR_TEMP_CLASS		SENSOR_CLASS_TEMP
#define SENSOR_DCPWR_CLASS		SENSOR_CLASS_DCPWR


/*
 * These are some FRU subpkt types.
 * Not sure how useful they'll be at this point, given the 
 * instability of the FRU table and our unwillingness to use it for 
 * much.
 */ 
typedef struct processor_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	uint32 id;		/* processor id = WHAMI IPR */
	uint32 family;		/* DMI MIF:  0x30 = alpha   */
	uint64 state;		/* HWRPB per cpu slot +128  */
	uint64 ovms_palcode_rev; /* HWRPB per cpu slot +168 */
	uint64 unix_palcode_rev; /* HWRPB per cpu slot +466 */
	uint64 xxx_palcode_rev;	/* unused */
	uint64 alpha_type;	/* HWRPB per cpu slot +176 */
	uint64 variation;	/* HWRPB per cpu slot +184 */
	TLV    first_tlv;	/* 1st or 3 TLVs  */
	       /* 1. Manufacturer */
	       /* 2. Serial number */
	       /* 3. Revision Level */
	
} GCT_SUBPKT_PROCESSOR;
#define GCT_N_CPU_TLV 3

typedef struct cache_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	uint16 cache_level;	/* Secondary cache level (Bcache) */
	uint16 cache_speed;	/* System cache speed in nanoseconds */
	uint16 cache_size;	/* System cache size in kilobytes */
	uint16 size_avail;	/* Size in KB enabled and avail for use */
	uint16 cache_wp;	/* Write Back Cache */
	uint16 cache_ec;	/* error detection/correction scheme */
	uint16 cache_type;	/* Cache type */
	uint16 cache_stat;	/* Operational status */
} GCT_SUBPKT_CACHE; 

typedef struct console_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	uint32 reset_reason;	/* for last reset */
	uint32 ev_count;	/* number of environment variables */
	TLV    first_tlv;	/* first of (4) TLVs */
	       /* 1. SRM console part number */
	       /* 2. SRM console revision */
	       /* 3. Alphabios part number */
	       /* 4. Alphabios revision */
	       /* followed by ev_count environment variable TLVs */
} GCT_SUBPKT_CONSOLE;
#define GCT_N_CONSOLE_TLV 4

typedef struct pci_dev_subpkt {
	FRU_SRC_SUBPKT_HDR hdr;
	uint64	pci_config_addr;
	uint8	pci_config_hdr[64];
} GCT_SUBPKT_PCI_DEV;



/* 
 * Max known subpacket type 
 * This is needed because there are platform-specific subpackets
 * That do not fall in the low ranges listed below in
 * the enumeration type CFGTREE_SPKT_TYPE
 */
#define CFGTREE_MAX_SUBPKT_TYPE 49
#define CFGTREE_SUBPKT_TYPE_STRING(type) \
(					 \
    (type > CFGTREE_MAX_SUBPKT_TYPE) ?   \
        (cfgtree_subpkt_type[0])	 \
    :					 \
        (cfgtree_subpkt_type[type])	 \
)

/*
 * ===========================================================================
 * Symbolic definitions -- node/subpacket types, subtypes, etc.
 */

typedef enum {
    CFGTREE_SUCCESS,
    CFGTREE_INVALID_HANDLE,
    CFGTREE_NOT_SUPPORTED,
    CFGTREE_STATUS_INVALID_ARGS,
    CFGTREE_FAIL,
    CFGTREE_STATUS_LAST
} CFGTREE_STATUS;


typedef enum {
	CFGTREE_NODE_TYPE_ANY=-1,	/* for wildcard searches */
	CFGTREE_NODE_TYPE_NONE=0,
	CFGTREE_NODE_ROOT,		/* valid types start with 1 */
	CFGTREE_NODE_HW_ROOT,
	CFGTREE_NODE_SW_ROOT,
	CFGTREE_NODE_TEMPLATE_ROOT, 
	CFGTREE_NODE_COMMUNITY,
	CFGTREE_NODE_PARTITION,
	CFGTREE_NODE_SBB,
	CFGTREE_NODE_PSEUDO, 
	CFGTREE_NODE_CPU,
	CFGTREE_NODE_MEMORY_SUB,	/* 10 */
	CFGTREE_NODE_MEMORY_DESC,
	CFGTREE_NODE_MEMORY_CTRL, 
	CFGTREE_NODE_IOP,
	CFGTREE_NODE_HOSE,
	CFGTREE_NODE_BUS,		/* 15 */
	CFGTREE_NODE_IO_CTRL,
	CFGTREE_NODE_SLOT, 
	CFGTREE_NODE_CPU_MODULE,
	CFGTREE_NODE_POWER_ENVIR,
	CFGTREE_NODE_FRU_ROOT,		/* 20 */
	CFGTREE_NODE_FRU_DESC, 
	CFGTREE_NODE_SMB,
	CFGTREE_NODE_CAB,
	CFGTREE_NODE_CHASSIS,
	CFGTREE_NODE_EXP_CHASSIS,	/* 25 */
	CFGTREE_NODE_SYS_INTER_SWITCH,
	CFGTREE_NODE_HARD_PARTITION,
	CFGTREE_NODE_RISER,
	CFGTREE_NODE_SOC,		/* 30 */
	/*
	 * Add other node types here 
	 */

	/* Always last */
	CFGTREE_NODE_LAST		
} CFGTREE_NODE_TYPE;

#define CFGTREE_NODE_FIRST CFGTREE_NODE_TYPE_NONE

typedef enum {
	CFGTREE_NODE_SUBTYPE_ANY=-1,	/* for wildcard searches */
	CFGTREE_NODE_SUBTYPE_NONE=0,
	CFGTREE_SUBNODE_CPU_NOPRIMARY,
	CFGTREE_SUBNODE_PCI,
	CFGTREE_SUBNODE_EISA,
	CFGTREE_SUBNODE_ISA,
	CFGTREE_SUBNODE_XMI,			/* 5 */
	CFGTREE_SUBNODE_FBUS,
	CFGTREE_SUBNODE_XBUS,
	CFGTREE_SUBNODE_USB,
	CFGTREE_SUBNODE_SERIAL_PORT,
	CFGTREE_SUBNODE_FLOPPY,			/* 10 */
	CFGTREE_SUBNODE_PARALLEL_PORT,
	CFGTREE_SUBNODE_SCSI,
	CFGTREE_SUBNODE_IDE,
	CFGTREE_SUBNODE_NI,
	CFGTREE_SUBNODE_FDDI,			/* 15 */
	CFGTREE_SUBNODE_TOKEN_RING,
	CFGTREE_SUBNODE_NI_SCSI,
	CFGTREE_SUBNODE_GRAPHICS,
	CFGTREE_SUBNODE_ATM,
	CFGTREE_SUBNODE_MEM_CHAN,		/* 20 */
	CFGTREE_SUBNODE_CI,
	CFGTREE_SUBNODE_1394,
	CFGTREE_SUBNODE_AGP,
	CFGTREE_SUBNODE_SUPER_HIPPI,
	CFGTREE_SUBNODE_FIBERCHANNEL,		/* 25 */
	CFGTREE_SUBNODE_CAB,
	CFGTREE_SUBNODE_CHASSIS,
	CFGTREE_SUBNODE_EXP_CHASSIS,
	CFGTREE_SUBNODE_POWER_SUPPLY,
	CFGTREE_SUBNODE_COOLING,		/* 30 */
	CFGTREE_SUBNODE_SIMM,
	CFGTREE_SUBNODE_DIMM,
	CFGTREE_SUBNODE_RIMM,
	CFGTREE_SUBNODE_CPU_MODULE,
	CFGTREE_SUBNODE_CPU_CACHE_MODULE,	/* 35 */
	CFGTREE_SUBNODE_MEMORY_MODULE,
	CFGTREE_SUBNODE_MEMORY_CARRIER_MODULE,
	CFGTREE_SUBNODE_BACKPLANE_ASSY,
	CFGTREE_SUBNODE_MOTHER_BOARD,
	CFGTREE_SUBNODE_FAN,			/* 40 */
	CFGTREE_SUBNODE_SYS_INTERCONN_PORT,
	CFGTREE_SUBNODE_SYS_INTERCONN_SWITCH,
	CFGTREE_SUBNODE_MEMORY_COHERENCY_MODULE,
	CFGTREE_SUBNODE_IO_PORT_MODULE,
	CFGTREE_SUBNODE_REMOTE_MGNT_MODULE,	/* 45 */
	CFGTREE_SUBNODE_POWER_ENV_CTRL_MODULE,
	CFGTREE_SUBNODE_MULTI_DEVICE,
	CFGTREE_SUBNODE_IO_EXP_CAB,
	CFGTREE_SUBNODE_EXPANSION_CAB,
	CFGTREE_SUBNODE_Reserved50,		/* 50 */
	CFGTREE_SUBNODE_DAUGHTER_CARD,
	CFGTREE_SUBNODE_RISER_CARD,
	CFGTREE_SUBNODE_CPU_FAN,
	CFGTREE_SUBNODE_MASTER_CLOCK,
	CFGTREE_SUBNODE_CLOCK_DIST,		/* 55 */
	CFGTREE_SUBNODE_POWER_SUB_RACK,
	CFGTREE_SUBNODE_POWER_CABINET,
	CFGTREE_SUBNODE_SYSTEM_CABINET,
	CFGTREE_SUBNODE_VOLTAGE_REGULATOR_MODULE,
	CFGTREE_SUBNODE_CPU_CHIP,		/* 60 */
	CFGTREE_SUBNODE_IO_EXPANSION_DRAWER,
	CFGTREE_SUBNODE_SYSTEM_DRAWER,
	CFGTREE_SUBNODE_PCI_X,
	CFGTREE_SUBNODE_IO_EXP_ASSEMBLY,
	/*
	 * Add other node subtypes here 
	 */


	/* Always last */
	CFGTREE_SUBNODE_LAST			/* 65 */
} CFGTREE_NODE_SUBTYPE;


typedef enum {
	CFGTREE_SPKT_CLASS_SYS_RESOURCE=1,
	CFGTREE_SPKT_CLASS_FRU,
	CFGTREE_SPKT_CLASS_3,
	CFGTREE_SPKT_CLASS_4,
	CFGTREE_SPKT_CLASS_5,
	CFGTREE_SPKT_CLASS_6,
	CFGTREE_SPKT_CLASS_7,
	CFGTREE_SPKT_CLASS_8,
	CFGTREE_SPKT_CLASS_9,
	CFGTREE_SPKT_CLASS_WILDFIRE,	/* = 10 */
	/*
	 * Add other platform classes here
	 */


	/* Always last */
	CFGTREE_SPKT_CLASS_LAST
} CFGTREE_SPKT_CLASS;


typedef enum {
	CFGTREE_SPKT_TYPE_0,
	CFGTREE_SPKT_TYPE_PLATFORM, 	/* not used in V5+ */
	CFGTREE_SPKT_TYPE_PROCESSOR,
	CFGTREE_SPKT_TYPE_MEM,
	CFGTREE_SPKT_TYPE_SYS_BUS_BRIDGE,
	CFGTREE_SPKT_TYPE_PCI_DEV,
	CFGTREE_SPKT_TYPE_EISA_DEV,	/* not used in V5+ */
	CFGTREE_SPKT_TYPE_CACHE,
	CFGTREE_SPKT_TYPE_POWER,
	CFGTREE_SPKT_TYPE_COOLING,
	CFGTREE_SPKT_TYPE_SYS_INIT_LOG,
	CFGTREE_SPKT_TYPE_XMI_DEV,	/* not used in V5+ */
	CFGTREE_SPKT_TYPE_FBUS_DEV,	/* not used in V5+ */
	CFGTREE_SPKT_TYPE_VME,
	CFGTREE_SPKT_TYPE_SBB,
	CFGTREE_SPKT_TYPE_IOP,
	CFGTREE_SPKT_TYPE_HOSE,
	CFGTREE_SPKT_TYPE_BUS,
	CFGTREE_SPKT_TYPE_ISA_DEV,
	CFGTREE_SPKT_TYPE_USB_DEV,
	CFGTREE_SPKT_TYPE_CONSOLE,
	CFGTREE_SPKT_TYPE_PWR_ENV_SUMMARY,
	CFGTREE_SPKT_TYPE_22,
	CFGTREE_SPKT_TYPE_23,
	CFGTREE_SPKT_TYPE_24,
	CFGTREE_SPKT_TYPE_25,
	CFGTREE_SPKT_TYPE_26,
	CFGTREE_SPKT_TYPE_27,
	CFGTREE_SPKT_TYPE_28,
	CFGTREE_SPKT_TYPE_29,
	CFGTREE_SPKT_TYPE_PCI_VPD,
	CFGTREE_SPKT_TYPE_SMB,
	CFGTREE_SPKT_TYPE_FC,
	CFGTREE_SPKT_TYPE_AGP,
	CFGTREE_SPKT_TYPE_IDE,
	CFGTREE_SPKT_TYPE_SCSI,
	CFGTREE_SPKT_TYPE_1394,
	CFGTREE_SPKT_TYPE_SHPPI,
	CFGTREE_SPKT_TYPE_MEM_DIR,
	CFGTREE_SPKT_TYPE_NUMA_PORT,
	CFGTREE_SPKT_TYPE_NUMA_SWITCH,
	CFGTREE_SPKT_TYPE_RMC,
	CFGTREE_SPKT_TYPE_SENSOR,
	CFGTREE_SPKT_TYPE_SYSEVENT,
	CFGTREE_SPKT_TYPE_44,
	CFGTREE_SPKT_TYPE_45,
	CFGTREE_SPKT_TYPE_46,
	CFGTREE_SPKT_TYPE_47,
	CFGTREE_SPKT_TYPE_48,
	CFGTREE_SPKT_TYPE_49,
	CFGTREE_SPKT_TYPE_LAST
} CFGTREE_SPKT_TYPE;


typedef struct _gsr {
    int version;	/* = 1		*/
    int flags;		/* unused	*/
    
    uint64 criteria;
/* Define Tree Search-by Types - search modifiers for cfgtree_search_tree() */
#define CFGTREE_FIND_ANY         0x00	/* Find "next" node, no criteria */
#define CFGTREE_FIND_BY_OWNER    0x01	/* Find "next" node with this owner */
#define CFGTREE_FIND_BY_TYPE     0x02	/* Find "next" node with this type */
#define CFGTREE_FIND_BY_SUBTYPE  0x04	/* Find "next" node with this subtype*/
#define CFGTREE_FIND_BY_ID       0x08	/* Find "next" node with this ID */
#define CFGTREE_FIND_UNAVAILABLE 0x10	/* include unavailable nodes */
#define CFGTREE_FIND_MAX         0x10

#define CFGTREE_FIND_BY_TYPE_AND_ID (CFGTREE_FIND_BY_TYPE | CFGTREE_FIND_BY_ID)
    
    CFGTREE_NODE_TYPE		type;
    CFGTREE_NODE_SUBTYPE	subtype;
    CFGTREE_ID			id;
    CFGTREE_ID			id_mask;
   
    gct_node_t			start_node;
    gct_node_t			owner;
    
    int				max_depth;  /* Controls the depth to which 
					       we search.  Any non-zero
					       valued is used. */
    int				index;      /* searching by index */

} GCT_SEARCH_REQ; 


/*
 * Many components' [entity] ids are low byte of node id
 */
#define CFGTREE_ENTITY_ID_MASK 0xff	/* low byte of id */
#define CFGTREE_ENTITY_ID(ID) ((ID) & CFGTREE_ENTITY_ID_MASK)


/* Soft SBB ID starts at bit 48 in the NODE ID */
#define CFGTREE_SOFT_SBB_ID_SHIFT 48
#define CFGTREE_SOFT_SBB_ID_MASK  0x00ff000000000000
#define CFGTREE_SOFT_SBB_TO_ID(ID) \
   (((ID) << CFGTREE_SOFT_SBB_ID_SHIFT) & CFGTREE_SOFT_SBB_ID_MASK)

/* (backward compatibility for symbols) */
#define CFGTREE_QBB_ID_SHIFT CFGTREE_SOFT_SBB_ID_SHIFT
#define CFGTREE_QBB_ID_MASK  CFGTREE_SOFT_SBB_ID_MASK
 
/*
 * Hard SBB ID starts at bit 32 in the NODE ID
 */
#define CFGTREE_HARD_SBB_ID_SHIFT 32
#define CFGTREE_HARD_SBB_ID_MASK  0x000000ff00000000
#define CFGTREE_SBB_ID_TO_HARD_SBB(ID) \
   (((ID) & CFGTREE_HARD_SBB_ID_MASK) >> CFGTREE_HARD_SBB_ID_SHIFT)
    
#define CFGTREE_HARD_SBB_TO_ID(ID) \
    (((ID) << CFGTREE_HARD_SBB_ID_SHIFT) & CFGTREE_HARD_SBB_ID_MASK)


/* 
 * Hose Number starts at bit 0 in the NODE ID
 * SBB/IOP relative Hose # is bits <0:7>
 */
#define CFGTREE_HOSE_ID_SHIFT       0
#define CFGTREE_HOSE_AND_QBB_ID_MASK 0x00ff0000000000ff

#define CFGTREE_HOSE_ID(SOFT_SBB, HOSE) \
  (((uint64)(SOFT_SBB) << CFGTREE_SOFT_SBB_ID_SHIFT) |  \
   ((HOSE) << CFGTREE_HOSE_ID_SHIFT))

/*
 * Memory subsystems
 */
#define CFGTREE_MEM_DESC_ID_SHIFT	0
#define CFGTREE_MEM_DESC_ID_MASK	0x000000000000ffff

#define CFGTREE_MEM_DESC_SUBSYS_SHIFT	16
#define CFGTREE_MEM_DESC_SUBSYS_MASK	0x0000000000ff0000
#define CFGTREE_MEM_SUBSYS_TO_ID(X)	(((X) << CFGTREE_MEM_DESC_SUBSYS_SHIFT)\
                                          & CFGTREE_MEM_DESC_SUBSYS_MASK)

/*
 * IOP
 */
#define CFGTREE_IOP_ID_SHIFT		24
#define CFGTREE_IOP_ID_MASK		0x00000000ff000000
#define CFGTREE_IOP_TO_ID(X)		(((X) << CFGTREE_IOP_ID_SHIFT) \
                                          & CFGTREE_IOP_ID_MASK)

/*
 * IOP
 */
#define CFGTREE_IOP_ID_SHIFT		24
#define CFGTREE_IOP_ID_MASK		0x00000000ff000000
#define CFGTREE_IOP_TO_ID(X)		(((X) << CFGTREE_IOP_ID_SHIFT) \
                                          & CFGTREE_IOP_ID_MASK)

/* CPU ID mask - first 16 bits of cpu id field */
#define CFGTREE_CPU_ID_NUM_MASK 0x000000000000ffff


/*
 * =========================================================================
 * Config Tree Parsing -- platform configuration, etc.
 */

/*
 * Return values from gct_parse_tree()
 */
typedef enum _cfgtree_parse_return {
	CFGTREE_PARSE_DONE = 0,
	CFGTREE_PARSE_CONTINUE,
	CFGTREE_PARSE_CHILD,
	CFGTREE_PARSE_SIBLING,
	CFGTREE_PARSE_FAIL
} CFGTREE_PARSE_RETURN;

typedef CFGTREE_PARSE_RETURN (*CFGTREE_PARSE_FUNC)(gct_node_t);

#define CFGTREE_PARSE_SKIP_UNAVAIL	0x0001	/* skip   unavail siblings */
#define CFGTREE_PARSE_HANDLE_UNAVAIL	0x0002	/* handle unavail nodes */
#define CFGTREE_PARSE_HW_ONLY		0x0004  /* Handle hardware subtree only*/

/*
 * Array of printable strings
 */
extern char *_cfgtree_parse_return_strings[];
extern char *cfgtree_node_type[];
extern char *cfgtree_node_subtype[];

/*
 * =========================================================================
 * Hotswap Data Types and #defines
 */

/* 
 * Config Tree Update Interprocessor Message
 */
#define CFGTREE_UPDTMSG "%TREE_UPDATE% "
#define CFGTREE_UPDTMSG_LEN (strlen(CFGTREE_UPDTMSG))

/*
 * Component Config Tree information:  our context surrounding the nodes
 * we care about.
 */
typedef struct cfgtree_node_info {
    queue_chain_t	q; 
    gct_node_t		fw_node;	/* node ptr, if known */
    CFGTREE_NODE_FLAGS	saved_flags;	/* remembered state */
    uint32		saved_change_ctr;	/* last change counter */
    /* 
     * If set, we have seen the attn flags bit get set.  We are 
     * waiting for either a timer to expire, or another attn 
     * event, both of which should clear this 
     */
    int8		attn_armed;

    CFGTREE_ID		id;
    CTFT_INFO		*ctft_infop;
    void                *hwc_dev_handle;
    HAL_SLOT_INFO	*slot_info;

} CFGTREE_NODE_INFO;	

/*
 * When we see a node's flag bits change, we break it down into one 
 * of these:
 */
typedef enum _cfgtree_node_transition {
        CFGTREE_NODE_UPDT_FAIL = -1,
	CFGTREE_NODE_UPDT_NONE = 0,		/* no change detected */
	CFGTREE_NODE_UPDT_PRESENT,	/* non-present  --> present */
	CFGTREE_NODE_UPDT_NONPRESENT,	/* present      --> non-present */
	CFGTREE_NODE_UPDT_POWERUP,	/* powered down --> powered up */
	CFGTREE_NODE_UPDT_POWERDOWN,	/* powered up   --> powered down */
	CFGTREE_NODE_UPDT_AVAIL,	/* unavailable  --> available */
	CFGTREE_NODE_UPDT_UNAVAIL,	/* available    --> unavailable */
	CFGTREE_NODE_UPDT_ATTN_SET,	/* attn clr	--> attn set */
	CFGTREE_NODE_UPDT_ATTN_CLR,	/* attn set	--> attn clr */
	CFGTREE_NODE_UPDT_UNHEALTHY,	/* healthy	--> unhealthy */
	CFGTREE_NODE_UPDT_HEALTHY,	/* unhealthy	--> healthy */
	CFGTREE_NODE_UPDT_DISABLED,	/* enabled	--> disabled */
	CFGTREE_NODE_UPDT_ENABLED,	/* disabled	--> enabled */

	CFGTREE_NODE_UPDT_LAST
} CFGTREE_NODE_TRANSITION;


/*
 * =========================================================================
 * Function Prototypes
 */
/*
 * Initialization
 */

CFGTREE_PARSE_RETURN gct_parse_tree (gct_node_t start_node, 
				     CFGTREE_PARSE_FUNC *, 
				     int last_entry,
				     uint64 flags);

/*
 * Hotswap-specific 
 */
CFGTREE_NODE_TRANSITION cfgtree_node_compare_flags(gct_node_t);
CFGTREE_PARSE_RETURN    cfgtree_add_node_to_list(gct_node_t);
CFGTREE_PARSE_RETURN	cfgtree_parse_node_ignore(gct_node_t node);
/*
 * Routines that operate on or return the raw config node (internal)
 */
gct_node_t    gct_search_tree(GCT_SEARCH_REQ *); 
gct_node_t    gct_get_child(gct_node_t node);
gct_node_t    gct_get_next_sibling(gct_node_t node);
gct_node_t    gct_get_prev_sibling(gct_node_t node);
gct_node_t    gct_get_parent(gct_node_t node);
gct_node_t    gct_get_owner(gct_node_t node);
unsigned char gct_get_type(gct_node_t node);
unsigned char gct_get_subtype(gct_node_t node);
CFGTREE_ID    gct_get_id(gct_node_t node);
CFGTREE_NODE_FLAGS gct_get_flags(gct_node_t node);

struct sys_res_config_subpkt_hdr *
		 gct_get_subpkt(gct_node_t node, 
				struct sys_res_config_subpkt_hdr *subpkt);
int              gct_sysevt_get_sr_offset(gct_node_t node);
int	         gct_get_ctft_info(gct_node_t node, CTFT_INFO *cfi);
HAL_SLOT_INFO    *gct_get_slot_info(gct_node_t node);

/*
 * Debug routines 
 */
char	*cfgtree_node_type_name(gct_node_t node);
void	gct_print_node(gct_node_t node);
void	cfgtree_dump_node_info();
int	gct_count_children(CFGTREE_NODE_TYPE type, 
			   CFGTREE_NODE_SUBTYPE target_subtype,
			   gct_node_t parent);
gct_node_t gct_get_partition();
gct_node_t gct_get_hard_partition();

#endif /* __cplusplus */

#endif	/* __ARCH_ALPHA_HAL_CFGTREE_H__ */
