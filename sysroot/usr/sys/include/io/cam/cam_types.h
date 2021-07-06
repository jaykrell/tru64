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
 * @(#)$RCSfile: cam_types.h,v $ $Revision: 1.1.4.5 $ (DEC) $Date: 1998/04/15 14:46:54 $
 */

#ifndef _CAM_TYPES_INCL_
#define _CAM_TYPES_INCL_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Define basic types
 */
typedef unsigned char   CAM_U8;            /* Unsigned  8 bit quantity       */
typedef unsigned short  CAM_U16;           /* Unsigned 16 bit quantity       */
typedef unsigned int    CAM_U32;           /* Unsigned 32 bit quantity       */
typedef unsigned long   CAM_U64;           /* Unsigned 64 bit quantity       */
typedef char            CAM_S8;            /* Signed    8 bit quantity       */
typedef short           CAM_S16;           /* Signed   16 bit quantity       */
typedef int             CAM_S32;           /* Signed   32 bit quantity       */
typedef long            CAM_S64;           /* Signed   64 bit quantity       */
typedef void *          CAM_VM_OFFSET;     /* A virtual address pointer      */
                                           /*   within the operating system  */
typedef void *          CAM_PM_OFFSET;     /* A physical address pointer     */
                                           /*   within the host              */
typedef void            CAM_VOID;          /* Generic VOID declaration       */
typedef void *          CAM_VOID_OFFSET;   /* A virtual address pointer      */
                                           /*   within the operating system  */
                                           /*   or a physical address        */
                                           /*   pointer within the host      */
typedef void *          CAM_IO_HANDLE;     /* A virtual address pointer or   */
                                           /*   physical address pointer     */
                                           /*   within an I/O bus's address  */
                                           /*   space                        */
typedef void *          CAM_MAP;           /* Pointer to the O.S. dependent  */
                                           /*   map structure.               */
typedef unsigned char   CAM_BOOLEAN;       /* A boolean value                */



/*
 * Connection definitions
 */
typedef struct connection_id {
    CAM_U32	conn_flags;      /* last known state of connection */
    CAM_U32     port_id;         /* A registered SIM/HA port number          */
    CAM_U32     addr_spec1[2];   /* Array to contain 1st half of a Protocol  */
                                 /*   specific address (ie SCSI-3 target id) */
    CAM_U32     addr_spec2[2];   /* Array to contain 2nd half of a Protocol  */
                                 /*   specific address (ie SCSI-3 LUN id)    */
} CONNECTION_ID;

/*
 * Definitions for CONNECTION_ID.conn_flags
 */
#define CONN_INVALID		0x00000000
#define CONN_VALID		0x00000001
#define CONN_INVAL_PID		0x00000002

typedef struct connections {
    CAM_U32     protocol_type;   /* The protocol number - SCSI, NETWORK, etc */
    CAM_U32     logical_id;      /* The assigned Logical ID of the device.   */
    CAM_U32     num_alloc_c_id;  /* Number of allocated Connect_IDs          */
                                 /*   Specified by the caller.               */
    CAM_U32     num_ret_c_id;    /* Number of valid Connection_IDs           */
                                 /*   Specified (returned) by the callee.    */
    CONNECTION_ID *c_id;         /* Pointer to array of CONNECT_ID structures*/

} CONNECTIONS;

/*
 * Translation structure definition
 */
typedef struct translation {
    CAM_U32     protocol_type;   /* The protocol number - SCSI, NETWORK, etc */
    CAM_U32     logical_id;      /* The assigned Logical ID of the device.   */
    CONNECTION_ID
		connection_id;   /* Protocol-specific addresing info         */
    CAM_U32     num_connect_ids; /* Number of paths to the device            */
    CAM_U32     dev_type;        /* Protocol specific device type	     */
                                 /*   (eg SCSI-3 INQUIRY byte 0, bits 0 - 5) */
    CAM_U32     id_length;       /* The length of the unique identifier      */
    CAM_U32     pd_reg_num;      /* Peripheral drivers registration number   */
    CAM_VOID_OFFSET pd_specific; /* A peripheral drivers vendor unique       */
                                 /*   specific pointer                       */
} TRANSLATION;

/*
 * Definition of the SIM entry point registration structure 
 */

/* size of the name/string buffers (including null-terminator) */
#define ASCIZ_32                32 


typedef struct sim_entry3
{
    CAM_U32       (*sim_init)();      /* Pointer to the SIM init routine      */
    CAM_U32       (*sim_action)();    /* Pointer to the SIM CCB go routine    */
    CAM_VOID_OFFSET  simha_handle;    /* Pointer to a SIM/HA handle (VU)      */
    CAM_U32       max_addr_spec1[2];  /* Maximum value for physical address   */
                                      /*   (target id)                        */
    CAM_U32       max_addr_spec2[2];  /* Maximum value for physical address   */
                                      /*   (LUN id)                           */
    CAM_U32       sim_flags;          /* SIM features supported flags         */
    CAM_U32       sim_ws_size;        /* The size of this SIM's working set   */
    CAM_U32       port_id;            /* Port Identifier (set by XPT)         */
    CAM_U32       protocol_type;      /* Protocol Type/Number (SCSI, NETWORK) */
    CAM_U32       protocol_subtype;   /* Protocol SubType (PARALLEL,IDE,FCP)  */
    CAM_U32       xpt_reg_num;        /* Registration number assigned to      */
                                      /*   the xpt (which performs topology   */
                                      /*   probing).                          */
    CAM_VOID_OFFSET  vu_entry;        /* Pointer to any vendor unique         */
                                      /*   extentions required for            */
                                      /*   registration                       */
    char          sim_name[ASCIZ_32]; /* Unique SIM name (null terminated)    */
    char          vendor_keystring[ASCIZ_32]; /* SIM vendor or OSD key        */
                                              /*   (null terminated)          */
    CAM_U32       vendor_key1;        /* SIM vendor or OSD key */
    CAM_U32       vendor_key2;        /* SIM vendor or OSD key */
    CAM_U32       vendor_key3;        /* SIM vendor or OSD key */
    CAM_U32       vendor_key4;        /* SIM vendor or OSD key */
    CAM_U32       vendor_key5;        /* SIM vendor or OSD key */
    CAM_U32       vendor_key6;        /* SIM vendor or OSD key */

} SIM_ENTRY3;


/*
 * Defines for SIM_ENTRY3.sim_flags
 */
#define SIM_CAM1_CCBS           0x00000001 /* CAM-1 CCB support              */
#define SIM_CAM3_CCBS           0x00000002 /* CAM-3 CCB support              */
#define SIM_AUTO_DEV_PRESENCE   0x40000000 /* Support for Automatically      */
                                           /*   determining Device Presence  */
#define SIM_DYNAMIC_DEV_ADDRS   0x80000000 /* SIM's interconnect supports    */
                                           /*   dynamic (self-configuring)   */
                                           /*   device/target addresses      */

/*
 * Vendor Unique entry for Digital UNIX
 *
 * The SIM_ENTRY3.vu_entry element should point to one of these structures.
 */
typedef struct dec_sim_entry3
{
    struct bus *busp;                 /* Pointer to SIM's bus structure */
    caddr_t     console_proto;        /* console protocol type for format for */
} DEC_SIM_ENTRY3;

#ifdef __cplusplus
}
#endif

#endif /* _CAM_TYPES_INCL_ */


