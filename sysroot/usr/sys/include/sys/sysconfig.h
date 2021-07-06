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
 *	@(#)$RCSfile: sysconfig.h,v $ $Revision: 4.2.65.3 $ (DEC) $Date: 2002/08/14 22:49:20 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 1.2
 */

#ifndef _SYS_SYSCONFIG_H_
#define _SYS_SYSCONFIG_H_

#include <sys/types.h>
#include <sys/errno.h>
#include <kern/lock.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Type definitions for configuration entrypoints and their operation parameter.
 */
typedef int	cfg_op_t;
typedef int	(* cfg_entrypt_t)(cfg_op_t, caddr_t, ulong, caddr_t, ulong);
/* Type definition kept for backwards compatibility */
typedef int     sysconfig_op_t;

/*
 * Type definitions for subsystem's dependency routine.
 */
typedef int	(* cfg_deprtn_t)(char *subsys, int op, ulong arg);
                                   
/*
 * Range 1 - 99 are subsystem request codes that are framework defined. It is
 * imperative that the numbers used for configure, query, and reconfigure
 * are bitwise mutually exclusive so that subsystem attributes can logically
 * 'or' them to define which operations they support.
 * CFG_HIDDEN_ATTR should also be bitwise mutually exclusive.
 */
#define CFG_OP_CONFIGURE	1	/* configure a subsystem */
#define CFG_OP_QUERY		2	/* query attributes of a subsystem */
#define CFG_OP_UNCONFIGURE	3	/* unconfigure a subsystem */
#define CFG_OP_RECONFIGURE	4	/* modify attributes of a subsystem */
#define CFG_OP_QUERY_DEFAULTS	5	/* query default subsystem attributes */
#define CFG_OP_SUBSYS_STATE	6	/* query subsystem status */
#define CFG_OP_BOOT_OVERRIDE    7       /* override attribute value in bootpath */
#define CFG_HIDDEN_ATTR 	8	/* hidden attributes */
#define SYSCONFIG_CONFIGURE	CFG_OP_CONFIGURE

/*
 * Range 100-999 are subsystem request codes that are subsystem defined.
 */
#define CFG_OP_SUBSYS_MIN	100
#define CFG_OP_SUBSYS_MAX	999

/*
 * Subsystem specific request codes for the 'cm' subsystem.
 */
#define CFG_OP_CM_ADD_REG	100	/* register a subsystem */
#define CFG_OP_CM_DEL_REG	101	/* unregister a subsystem */
#define CFG_OP_CM_GET_REG	102	/* query a subsystem's registration */
#define CFG_OP_CM_GET_ATTRCNT	103	/* query a subsystem's attribute count */
#define CFG_OP_CM_GET_ATTRINFO	104	/* get info about attributes of a subsystem */
#define CFG_OP_CM_GET_ATTRINFO_ALL	105	/* get info about all attributes of a subsystem */

/*
 * Subsystem state bit flags - for setting and checking subsystem states.
 * The most significant bit, bit 31, is reserved and should not be used.
 */
#define CFG_STATE_LOADED	0x01	/* whether subsystem is loaded */
#define CFG_STATE_CONFIGURED	0x02	/* whether subsystem is configured */
#define CFG_STATE_DYNAMIC       0x04    /* whether subsystem is dynamic */
#define CFG_STATE_FOREIGN       0x08    /* was the subsystem loaded from a foreign kit */
#define CFG_STATE_TYPE_OLD      0x10    /* on old-format if_dynamic module */
#define CFG_STATE_INIT_ERROR    0x20    /* subsystem failed to initialize */

/*
 * Mask for clearing a subsystem state bit flag.
 */
#define CFG_STATE_UNCONFIGURED  ~CFG_STATE_CONFIGURED  /* mask for clearing CONFIGURED flag */

/*
 * cfgmgr_get_state() jacket state definitions
 */
#define SUBSYSTEM_DYNAMICALLY_CONFIGURED    0x01
#define SUBSYSTEM_STATICALLY_CONFIGURED     0x02 
#define SUBSYSTEM_KERN_SYSCONFIG_REGISTERED 0x04
extern int cfgmgr_get_state(char *subsys, int *state);
extern int cfgmgr_set_status(char *subsys);

/*
 * Return values from subsystem requests are 32-bit quantities consisting of a
 * 16-bit framework status and a 16-bit subsystem specific status.
 */

typedef int			cfg_status_t;

/*
 * Framework status portion of return values.
 */
#define CFG_FRAME_SUCCESS	0	/* framework succeeded */
#define CFG_FRAME_EEXISTS	1	/* subsystem not loaded */
#define CFG_FRAME_EALREADY	2	/* request already performed */
#define CFG_FRAME_ECONFIGURED	3	/* subsystem not configured */
#define CFG_FRAME_EPRIVS	4	/* insufficient privileges */
#define CFG_FRAME_EMEM		5	/* can't allocate sufficient memory */
#define CFG_FRAME_ECONNECT	6	/* can't connect to cfgmgr daemon */
#define CFG_FRAME_ESIZE		7	/* insufficient buffer size */
#define CFG_FRAME_ESUBSYS	8	/* subsystem failure */
#define CFG_FRAME_ECOPY		9	/* error copying memory */
#define CFG_FRAME_ELOADREQ	10	/* connecting to loader */
#define CFG_FRAME_ELOADER	11	/* loader failed the un/load */
#define CFG_FRAME_ECFG_RTN	12	/* module has no configure routine */
#define CFG_FRAME_EATTR_TBL	13	/* module has no attribute table */
#define CFG_FRAME_EREGISTER	14	/* error un/registering the subsystem */
#define CFG_FRAME_EMODULEID	15	/* unable to get the module id */
#define CFG_FRAME_EMETHOD_PRE	16	/* method failed on preconfiguration */
#define CFG_FRAME_EMETHOD_POST	17	/* method failed on postconfiguration */
#define CFG_FRAME_EATTR_LIST	18	/* bad attribute list */
#define CFG_FRAME_ENOSYM	19	/* unresolved symbol name */
#define CFG_FRAME_EREFCNT	20	/* subsystem's reference count not zero */
#define CFG_FRAME_EEXCEEDENTRY  21      /* dependency table is full, no entry left */
#define CFG_FRAME_EEXCEEDDEPTH  22      /* a dependency table entry is full */
#define CFG_FRAME_ENODEPEND     23      /* the dependency does not exist */
#define CFG_FRAME_ESUBSYSNAME	24	/* subsystem name too long */

/* Hot swapping framework errors. */
#define CFG_FRAME_ENOHOTSWAP    50      /* hot swapping support not available */
#define CFG_FRAME_ETIMEOUT      51      /* timeout occurred on waiting for the server */
 
/*
 * Subsystem status portion of return values should be valid returns
 * as defined in errno.h.
 */
#define CFG_SUBSYS_SUCCESS	ESUCCESS /* subsystem succeeded */
#define CFG_SUBSYS_EINIT        999      /* subsystem initialization failure */
#define CFG_SUBSYS_ERESTART     -1       /* operation needs to be restarted */

/*
 * Macros for constructing and extracting status codes composed of framework
 * and subsystem specific components.
 */
#define CFG_STATUS_MAKE(s_stat, f_stat)	(((s_stat) << 16) | (f_stat))
#define CFG_STATUS_FRAME(stat)	(stat & 0x0000ffff)
#define CFG_STATUS_SUBSYS(stat)	(stat >> 16)

/*
 * Complete success!
 */
#define CFG_SUCCESS CFG_STATUS_MAKE(ESUCCESS, CFG_FRAME_SUCCESS)

/*
 * Maximum name lengths for subsystems and attributes.
 */
#define	CFG_SUBSYS_NAME_SZ	16	/* maximum subsystem name length */
#define	CFG_ATTR_NAME_SZ	30	/* maximum attribute name length */

/*
 * Maximum number of attributes for a subsystem.
 */
#define CFG_SUBSYS_MAXATTR	500

/*
 * Maximum array size.
 */
#define NDIGITS_INT             10      /* max. # of decimal digits in an array index */
#define CFG_MAX_ARRAY_SZ        INT_MAX /* max. # of elements in an array attribute */

/*
 * Attribute type codes.
 */
#define CFG_ATTR_STRTYPE	1	/* string */
#define CFG_ATTR_INTTYPE	2	/* integer */
#define CFG_ATTR_UINTTYPE	3	/* unsigned integer */
#define CFG_ATTR_LONGTYPE	4	/* long */
#define CFG_ATTR_ULONGTYPE	5	/* unsigned long */
#define CFG_ATTR_BINTYPE	6	/* binary data */
#define CFG_ATTR_UCHARTYPE	8	/* byte data */
#define CFG_ATTR_USHORTTYPE	9	/* short data */

#define CFG_ATTR_INTARRAYTYPE   11	/* integer array */
#define CFG_ATTR_UINTARRAYTYPE  12	/* unsigned integer array */
#define CFG_ATTR_LONGARRAYTYPE  13	/* long array */
#define CFG_ATTR_ULONGARRAYTYPE 14	/* unsigned long array */
#define CFG_ATTR_STRARRAYTYPE   15	/* string array */

/*
 * Attribute return status codes.
 */
#define CFG_ATTR_SUCCESS	0	/* successful op */
#define CFG_ATTR_EEXISTS	1	/* attribute doesn`t exist */
#define CFG_ATTR_EOP		2	/* attribute doesn`t support op */
#define CFG_ATTR_ESUBSYS	3	/* subsystem failure */
#define CFG_ATTR_ESMALL		4	/* attribute value/size is too small */
#define CFG_ATTR_ELARGE		5	/* attribute value/size is too large */
#define CFG_ATTR_ETYPE		6	/* invalid attribute type or mismatch */
#define CFG_ATTR_EINDEX		7	/* invalid attribute index */
#define CFG_ATTR_EMEM		8	/* couldn't allocate memory */
#define CFG_ATTR_ENOTNUMBER	9	/* attribute value can't be converted to number */
#define CFG_ATTR_EADDR		10	/* attribute's address not specified */
#define CFG_ATTR_PENDING	11	/* temp internal state during query */

/*
 * Attribute representation for configuring, querying and reconfiguring.
 */
typedef struct {
    char 		name[CFG_ATTR_NAME_SZ];	/* attribute name */
    uchar		type;			/* attribute type */
    uchar		operation;		/* supported operations */
    uint		status;			/* operation result */
    long		index;			/* for indexed attributes */
    union {
	struct {
            caddr_t	val;			/* binary data value */
            ulong	min_size;		/* min binary data size */
            ulong	max_size;		/* min binary data size */
	    void	(*disposal)(void *, int);		/* binary disposal routine */
	    ulong	val_size;		/* binary data size */
	} bin;

	struct {
            caddr_t	val;			/* string value */
            ulong	min_len;		/* min string length */
            ulong	max_len;		/* max string length */
	    void	(*disposal)(void *, int);		/* string disposal routine */
	    ulong	val_size;		/* array size / attribute properties */
	} str;

	struct {
            ulong	val;			/* number value */
            ulong	min_val;		/* min number */
            ulong	max_val;		/* max number */
            ulong	unused;			/* not used */
	    ulong	val_size;		/* array size / attribute properties */
	} num;
    } attr;
} cfg_attr_t;

/*
 * Subsystem attribute table element.
 */
typedef struct {
    char 		name[CFG_ATTR_NAME_SZ];	/* attribute name */
    uchar		type;			/* attribute type */
    uchar		operation;		/* supported operations */
    caddr_t		addr;			/* address of data value */
    ulong		min_val;		/* min size/length/value */
    ulong		max_val;		/* max size/length/value */
                                                /* size of each array element */
    ulong		val_size;		/* a multi-purpose field */
						/* data size (in bytes) for binary data */
						/* # elements in the array for array attributes */
						/* attribute properties for number and string attributes */
} cfg_subsys_attr_t;

/*
 * Subsystem registration table entry.
 */
typedef struct subsys_info {
    ulong		module_id;	/* subsystem module id - 0 if static */
    cfg_entrypt_t	entrypt;	/* config entry point */
    uint		state;		/* loaded/configured/method run */
    char		name[CFG_SUBSYS_NAME_SZ];
    cfg_subsys_attr_t	*attributes;	/* attribute table */
    lock_data_t		subsys_lock;    /* lock subsystem except attributes */
    lock_data_t		attrs_lock;     /* lock subsystem attributes */
    int			refcnt;         /* subsystem's reference count */
    cfg_deprtn_t	deprtn;         /* subsystem's dependency routine */
    struct subsys_info	*next;		/* next registration entry */
} subsys_info_t;

/*
 * The LOCK_ macros ensure that we don't call the locking package until
 * it is available.
 */
extern  int  locking_on;
#define LOCK_READ(l) { if (locking_on) lock_read(l); }
#define LOCK_WRITE(l) { if (locking_on) lock_write(l); }
#define LOCK_DONE(l) { if (locking_on) lock_done(l); }
#define LOCK_SETUP(l, li, f) { if (locking_on) lock_setup(l, li, f); }

/* ====================================================================
 *
 *     BEGINNING OF THE HOT SWAPPING FRAMEWORK SUPPORT AND KERNEL-MODE 
 *     CFG STUFF 
 *
 * ====================================================================
 */

/*
 * CFG kernel APIs.
 */

#ifdef _KERNEL

    cfg_status_t  cfg_configure(char *subsys);
    cfg_status_t  cfg_unconfigure(char *subsys);
    cfg_status_t  cfg_reconfigure(char *subsys, cfg_attr_t *attributes, uint nattributes);
    cfg_status_t  cfg_query(char *subsys, cfg_attr_t *attributes, uint nattributes);
    cfg_status_t  cfg_subsysop(char *subsys, cfg_op_t op, caddr_t indata, size_t insize,
                                             caddr_t outdata, size_t outsize);
#endif  /* _KERNEL */

/*
 * Hot Swapping Framework Support data structures for request and reply messages.
 */
typedef struct hs_req {
    char           subsys[CFG_SUBSYS_NAME_SZ];
    cfg_op_t       op;
    uint           flags;
} hs_req_t;

/*
 * Hot Swapping Control flags - these are bit flags.
 */
#define  HS_DEBUG_ON        0x1       /* decimal   1  */
#define  UCMD_DEBUG_ON      0x2       /* decimal   2  */

typedef struct hs_rply {
    char           subsys[CFG_SUBSYS_NAME_SZ];
    cfg_op_t       op;
    cfg_status_t   status;
    long           magic;
} hs_rply_t;

#define   HS_SRV_TIMEOUT_DEFAULT    120     /* max. # seconds to wait for the hs server,
                                          must be a positive integer >= 1 */

/* ====================================================================
 *
 *     BEGINNING OF  THE CALLBACK RELATED STUFF 
 *
 * ====================================================================
 */

struct callback {
  void              (* func)(int, int, ulong, ulong);  /* name of function to call */
  int               point;       /* call func at this execution/event point */
  int               order;       /* used to order requests for the same point */
                                 /* lowest value gets first execution */
  ulong             arg;         /* pass this argument to func */
};

/*
 * Definitions of dispatch points in the kernel. These include 
 * execution/event points both in the boot path and at run time.
 *
 * !!! Note: The numeric values of the defined dispatch points MUST
 * be in strictly chronological order. The only exception is among
 * the execution/event points at run time themselves, where no 
 * ordering is posssible. However, the following order still needs to be
 * maintained:
 *
 *   multi-user mode point > single user mode point > boot path point
 * i.e.
 *   run time point > CFG_PT_ENTER_SUSER > boot path point
 *
 * To add a new dispatch point, pick up a correct number for the new
 * point, add a #define here, and add the dispatch_callback() at the
 * code path point. For example,
 *
 *   #define  CFG_PT_NEWPOINT    2050  (this goes in this header file)
 *   dispatch_callback(CFG_PT_NEWPOINT);  (this goes to the code path point)
 *
 * If a point is defined simply for checking if the execution has passed
 * that point or not, then the SET_CFGPOINT() macro should be used at the 
 * code path point in place of dispatch_callback(), to avoid unnecessary 
 * overhead. Dispatch_callback() does both SET_CFGPOINT() and the callback. 
 * In addition, the application uses
 *     if (PAST_CFGPOINT(..)) ... or if (BEFORE_CFGPOINT(..)) ...
 * rather than
 *     register_callback(...)
 * The BEFORE_CFGPOINT() and PAST_CFGPOINT() macros can be used for any 
 * defined dispatch point, although it may not make any sense to use them 
 * with a run time point.
 *
 * Whenever you pick the number for a new point, please do it VERY CAREFULLY
 * and make sure that you leave room for growth on BOTH ends and that it is 
 * in chronological order!!! Use numbers in an increment of hundreds or tens.
 * Please consult Jin Chen of the kernel group if you need to add new callback
 * dispatch points.
 *
 * Note that the numeric values of all valid dispatch points must fall 
 * in-between CFG_PT_MIN and CFG_PT_MAX.
 *
 */

#define CFG_PT_DELETED          -1
#define CFG_PT_MIN            1000
#define CFG_PT_MAX           50000

/*
 * Dispatch points during the boot path - before single user mode.
 * These points are in strictly chronological order!
 */
#define CFG_PT_HAL_INIT       2000    /* HAL init point */
#define CFG_PT_UNIXTBL_AVAIL  2200    /* UNIX tables are available */
#define CFG_PT_VM_AVAIL       2500    /* VM is available */
#define CFG_PT_LOCK_AVAIL     2800    /* locking is available */
#define CFG_PT_PRECONFIG      2800    /* Hardware Pre Configuration */
#define CFG_PT_TOPOLOGY_CONF  4500    /* topology configuration point */
#define CFG_PT_PLATFORM_CONF  5000    /* platform configure point */
#define CFG_PT_PRECONSOLE_CONF   5250 /* Before configure_console */
#define CFG_PT_POSTPLATFORM_CONF 5500 /* post platform configure point */
#define CFG_PT_POST_CAM_SCAN  5800    /* All done probing SCSI/Fibre busses */
#define CFG_PT_OLD_CONF_ALL   6000    /* where subsys_conf_all() used to be */
#define CFG_PT_POSTCONFIG     6000    /* Hardware Post Configuration */
#define CFG_PT_CLU_CONF       6800    /* Cluster subsystem configuration */
#define CFG_PT_GLROOTFS_AVAIL 6900    /* global root file system mounted */
#define CFG_PT_ROOTFS_AVAIL   7000    /* root file system mounted */

/* The value of each run time point has to be greater than that of CFG_PT_ENTER_SUSER. */
#define CFG_PT_ENTER_SUSER    8000    /* about to enter single user mode */

/*
 * Run-time dispatch points. These are points after single user mode.
 * There is no order between the run-time points.
 * The run-time point space is further partitioned into kernel and user
 * based on the source that triggers the callback.
 */
/*
 * Kernel-triggered run-time points. The value of each kernel-triggered run-time point
 * should be in-between CFG_PT_RUNTIME_KERN_MIN and CFG_PT_RUNTIME_KERN_MAX.
 */
#define CFG_PT_RUNTIME_KERN_MIN   CFG_PT_ENTER_SUSER+2000         /* 10000 */
#define CFG_PT_RUNTIME_KERN_MAX   CFG_PT_RUNTIME_KERN_MIN+19999   /* 29999 */

/* Kernel-triggered run-time points reserved by the system. */
#define CFG_PT_RUNTIME_KERN_MIN_INT  CFG_PT_RUNTIME_KERN_MIN           /* 10000 */
#define CFG_PT_RUNTIME_KERN_MAX_INT  CFG_PT_RUNTIME_KERN_MIN_INT+9999  /* 19999 */

#define CFG_PT_CPU_SHUTDOWN_1     CFG_PT_RUNTIME_KERN_MIN_INT+0       /* 10000 */
#define CFG_PT_CPU_SHUTDOWN_2     CFG_PT_RUNTIME_KERN_MIN_INT+1       /* 10001 */
#define CFG_PT_CPU_STARTUP_1      CFG_PT_RUNTIME_KERN_MIN_INT+2       /* 10002 */
#define CFG_PT_CPU_STARTUP_2      CFG_PT_RUNTIME_KERN_MIN_INT+3       /* 10003 */


/* Kernel-triggered run-time points for developers to define. */
#define CFG_PT_RUNTIME_KERN_MIN_EXT  CFG_PT_RUNTIME_KERN_MAX_INT+1    /* 20000 */
#define CFG_PT_RUNTIME_KERN_MAX_EXT  CFG_PT_RUNTIME_KERN_MIN_EXT+9999 /* 29999 */

/*
 * User-triggered run-time points. The value of each user-triggered run-time point
 * should be in-between CFG_PT_RUNTIME_USER_MIN and CFG_PT_RUNTIME_USER_MAX.
 */
#define CFG_PT_RUNTIME_USER_MIN   CFG_PT_MAX-20000                /* 30000 */
#define CFG_PT_RUNTIME_USER_MAX   CFG_PT_MAX                      /* 50000 */

/* User-triggered run-time points for developers to define. */
#define CFG_PT_RUNTIME_USER_MIN_EXT  CFG_PT_RUNTIME_USER_MIN          /* 30000 */
#define CFG_PT_RUNTIME_USER_MAX_EXT  CFG_PT_RUNTIME_USER_MIN_EXT+9999 /* 39999 */


/* User-triggered run-time points reserved by the system. */
#define CFG_PT_RUNTIME_USER_MIN_INT  CFG_PT_RUNTIME_USER_MAX_EXT+1     /* 40000 */
#define CFG_PT_RUNTIME_USER_MAX_INT  CFG_PT_RUNTIME_USER_MIN_INT+10000 /* 50000 */

#define CFG_PT_CDB_WR     CFG_PT_RUNTIME_USER_MIN_INT+50   /* cluster databases writeable */
#define CFG_PT_ROOTFS_WR  CFG_PT_RUNTIME_USER_MIN_INT+100  /* root file system writeable */
#define CFG_PT_DBWR_INIT  CFG_PT_ROOTFS_WR+10              /* ok to repair naming database */
#define CFG_PT_MULTIUSER  CFG_PT_RUNTIME_USER_MIN_INT+5000 /* multiuser reached */
/*
 *  NOTE: if the user_cfg_pt's are changed it may affect the following user programs:
 *          dn_setup - boot sequence
 *          install  - full install .profile
 *          bttape   - boot sequence
 */

/* macros for point setting and checking */
#define  SET_CFGPOINT(x)      current_cfgpoint = x
#define  BEFORE_CFGPOINT(x)  (current_cfgpoint < x)
#define  PAST_CFGPOINT(x)    (current_cfgpoint >= x)

/* default value for the order parameter */
#define  CFG_ORD_DONTCARE      0
#define  CFG_ORD_NOMINAL       10000      /* Lowest Priority registration for Device Drivers */ 
#define  CFG_ORD_MAXIMUM       5000       /* Highest Priority registration for Device Drivers */
#define	 CFG_ORD_HAL_EARLY     -5000	  /* Early point for platform code */
#define	 CFG_ORD_HAL_LATE	5000	  /* Late point for HW support code */


#ifdef _KERNEL

#define  MAX_CALLBACKS  (PAGE_SIZE/sizeof(struct callback))
extern struct callback  *callback_list;
extern unsigned int     max_callbacks;
extern int              current_cfgpoint;
extern lock_data_t      callbk_list_lock;
extern struct lockinfo  *callbk_list_lockinfo;
extern subsys_info_t    static_subsys_list[];

int register_callback(void  (* func)(), int point, int order, ulong arg);
int unregister_callback(void  (* func)(), int point, int order, ulong arg);
int dispatch_callback(int  point, ulong  event_arg);

/*
 * Subsystem's callback function - xx_callback():
 *     void xx_callback(
 *            int    point;      (the predefined point of execution where this function is 
 *                                called, from the register_callback() call )
 *            int    order;      (used to order callback requests at the same proint, smaller 
 *                                value gets executed first, from the register_callback() call)
 *            ulong  arg;        (from the register_callback() call)
 *            ulong  event_arg;  (from the dispatcher)
 *          )
 */

#endif  /* _KERNEL */

/* ====================================================================
 *
 *     END OF  THE CALLBACK RELATED STUFF 
 *
 * ====================================================================
 */

/* ====================================================================
 *
 *     SUBSYSTEM DEPENDENCY SUPPORT 
 *
 * ====================================================================
 */

struct cfg_deptab_elem {
    char           name[CFG_SUBSYS_NAME_SZ];
    unsigned int   count;
};

#define  CFG_DEPTAB_ENTRIES  20
#define  CFG_DEPTAB_DEPTH    (PAGE_SIZE/CFG_DEPTAB_ENTRIES/sizeof(struct cfg_deptab_elem))

#define  CFG_SET_DEPEND      1
#define  CFG_REL_DEPEND      2

/*
 * Subsystem's dependency routine. Note: there is no convention on the name of this routine.
 *
 *   int  xx_deprtn(char *subsys, int op, ulong arg);
 *  
 *     subsys - the name of the subsystem claiming its dependency on me.
 *     op     - CFG_SET_DEPEND or CFG_REL_DEPEND.
 *     arg    - an optional value the calling subsystem is passing in.
 */

/* ====================================================================
 *
 *     PROTOTYPES OF MISC. CFG EXPORTED KERNEL FUNCTIONS 
 *
 * ====================================================================
 */

#ifdef _KERNEL

/*
 * Functions for getting/setting a subsystem's state.
 */
cfg_status_t cfg_get_subsys_state(char *subsys, uint *state);
cfg_status_t cfg_set_subsys_state(char *subsys, uint state);

/*
 * Functions for locking/unlocking a subsystem's attributes.
 */
cfg_status_t  lock_subsys_attrs_read(char *subsys);
cfg_status_t  lock_subsys_attrs_write(char *subsys);
cfg_status_t  lock_subsys_attrs_done(char *subsys);

#ifndef __VMS
extern cfg_status_t
	subsys_conf(caddr_t);
#else	/* __VMS */
extern cfg_status_t
	subsys_conf(caddr_t, cfg_attr_t *, ulong);
#endif	/* __VMS */

#endif  /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /*_SYS_SYSCONFIG_H_*/
