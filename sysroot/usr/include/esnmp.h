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
 * @(#)$RCSfile: esnmp.h,v $ $Revision: 1.1.25.2 $ (DEC) $Date: 1999/08/26 17:51:16 $
 */
/*********************************************************************
|
|  esnmp.h    Extensible SNMP Subagent -  API definitions
|                                                                  
|  Feb 15, 1995 - Version 0.1                                     
|  David Keeney
|
| This is the public API interface file for the Extensible SNMP Agent.
|
*********************************************************************/

#ifndef _ESNMP_H_
#define _ESNMP_H_

/* for C++ compatability */
#ifdef __cplusplus
extern "C" {     
#endif          

#include <stdarg.h>
#include <time.h>

/*
 ******************************************************************************
 *									      *
 * libsnmp API function return values.					      *
 *									      *
 * These are valid status codes returned by			 	      *
 *									      *
 *	esnmp_init, esnmp_open, esnmp_register, esnmp_poll, esnmp_trap,       *
 *	esnmp_unregister, esnmp_term					      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_LIB_OK               0  /* continue, everything is fine. */
#define ESNMP_LIB_NO_CONNECTION   -1  /* Cannot send OPEN to Master Agent, restart after delay. */
#define ESNMP_LIB_BAD_REG         -2  /* Cannot register the subtree, or not initialized. */
#define ESNMP_LIB_CLOSE           -3  /* Received a CLOSE message. restart after a delay. */
#define ESNMP_LIB_LOST_CONNECTION -4  /* lost connection with Master Agent, restart. */
#define ESNMP_LIB_NOTOK           -5  /* a negative response   */
#define ESNMP_LIB_DUPLICATE       -6  /* Duplicate subagent identifer in OPEN */
#define ESNMP_LIB_BAD_ALLOC       -7  /* Cannot allocate the index(es), or not initialized.   */
#define ESNMP_LIB_BAD_DEALLOC     -8  /* Cannot deallocate the index(es), or not initialized. */



/*
 ******************************************************************************
 *									      *
 * The data types                        				      *
 *									      *
 ******************************************************************************
 */
#define ESNMP_TYPE_Integer32    (128|1) /* 32-bit INTEGER             */
#define ESNMP_TYPE_OctetString       2  /* OCTET STRING (ASN.1)       */
#define ESNMP_TYPE_ObjectId          3  /* OBJECT IDENTIFIER (ASN.1)  */
#define ESNMP_TYPE_NULL              4  /* NULL (ASN.1)               */
#define ESNMP_TYPE_IpAddress         5  /* IMPLICIT OCTET STRING (4)  */
#define ESNMP_TYPE_Counter32    (128|6) /* 32-bit Counter (unsigned)  */
#define ESNMP_TYPE_Gauge32      (128|7) /* 32-bit Gauge   (unsigned)  */
#define ESNMP_TYPE_TimeTicks    (128|8) /* 32-bit TimeTicks (unsigned)*/
                                       /* in hundreths of a second   */
#define ESNMP_TYPE_DisplayString     9  /* DisplayString (Textual Con)*/
#define ESNMP_TYPE_NsapAddress       11 /* Removed in RFC1902, treated as TYPE_OctetString */
#define ESNMP_TYPE_UInteger32   (128|12)/* V2, 32-bit INTEGER (unsigned)  */
#define ESNMP_TYPE_Counter64         13 /* V2, 64-bit Counter (unsigned)  */
#define ESNMP_TYPE_Opaque            14 /* V2, IMPLICIT OCTET STRING      */
#define ESNMP_TYPE_noSuchObject      15 /* IMPLICIT NULL              */
#define ESNMP_TYPE_noSuchInstance    16 /* IMPLICIT NULL              */
#define ESNMP_TYPE_endOfMibView      17 /* IMPLICIT NULL              */



/*
 ******************************************************************************
 *									      *
 * Method routine function return values.				      *
 *									      *
 * These are  a subset of SNMP codes defined in RFC 1448 (SNMPv2).	      *
 * (The libsnmp code can determine the others before calling method routines.)*
 *									      *
 ******************************************************************************
 */

#define ESNMP_MTHD_noError             0
#define ESNMP_MTHD_genErr              5
#define ESNMP_MTHD_noAccess            6
#define ESNMP_MTHD_wrongType	       7
#define ESNMP_MTHD_wrongLength         8
#define ESNMP_MTHD_wrongEncoding       9
#define ESNMP_MTHD_wrongValue          10
#define ESNMP_MTHD_noCreation          11
#define ESNMP_MTHD_inconsistentValue   12
#define ESNMP_MTHD_resourceUnavailable 13
#define ESNMP_MTHD_commitFailed        14
#define ESNMP_MTHD_undoFailed          15
#define ESNMP_MTHD_notWritable         17
#define ESNMP_MTHD_inconsistentName    18
#define ESNMP_MTHD_noSuchInstance      80
#define ESNMP_MTHD_noSuchObject        81


/*
 ******************************************************************************
 *									      *
 *  Action values (for method->action)					      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_ACT_GET            1
#define ESNMP_ACT_GETNEXT        2
#define ESNMP_ACT_SET            3
#define ESNMP_ACT_COMMIT        10
#define ESNMP_ACT_UNDO          11
#define ESNMP_ACT_GETBULK       12
#define ESNMP_ACT_INFORM        14      /* reserved, not implemented  */
#define ESNMP_ACT_ARE_YOU_THERE 15
#define ESNMP_ACT_CLEANUP       16      /* local to subagent only     */


/*
 ******************************************************************************
 *									      *
 *  Bit definitions for ROW_CONTEXT.state				      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_SET_UNKNOWN	0x00	/* test and inter-variable checks not complete*/
#define ESNMP_SET_CREATE	0x01	/* Ready to commit to Create Row */
#define ESNMP_SET_MODIFY	0x02	/* Ready to commit to Modify Row */
#define ESNMP_SET_DELETE	0x04	/* Ready to commit to delete Row */

/*
 ******************************************************************************
 *									      *
 *  Bit definitions for ESNMP_ALLOC.options                                   *
 *									      *
 ******************************************************************************
 */

/* The two options, ESNMP_ALLOC_NEW_INDEX, and ESNMP_ALLOC_ANY_INDEX 
 * are mutually exclusive.  Only one may be set. If neither of these options
 * are set, then the caller must supply a specific value for the requested
 * index allocation.
 *
 * The first option, ESNMP_ALLOC_CLUSTER, may be combined with 
 * either of the other options.
 */
#define ESNMP_ALLOC_CLUSTER          0x01    /* this index (de)allocation request is cluster-wide   */ 
#define ESNMP_ALLOC_NEW_INDEX        0x02    /* this index allocation request is for a new 
                                                index value- the master agent provides a value 
                                                that has never been used (in this epoch) for 
                                                this index, in the response  */
#define ESNMP_ALLOC_ANY_INDEX        0x04    /* this index allocation request is for an unused index 
                                                value, that may have been previously used by this, or
                                                by some other, subagent (in this epoch)  
                                                the master agent provides the value in the response  */

/*
 ******************************************************************************
 *									      *
 *  Bit definitions for ESNMP_ALLOC.state		       			      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_ALLOC_STATE_PENDING     0x01    /* Held locally while waiting for connection  	         */
#define ESNMP_ALLOC_STATE_SENT        0x02    /* Has been sent to master agent              	         */
#define ESNMP_ALLOC_STATE_DONE        0x04    /* Successfully ackowledged by master agent   	         */
#define ESNMP_ALLOC_STATE_ALLOCTYPE   0x08    /* Rejected, wrong index type and/or options               */
#define ESNMP_ALLOC_STATE_ALLOCINUSE  0x10    /* Rejected, supplied index type and options               */
#define ESNMP_ALLOC_STATE_ALLOCAVAIL  0x20    /* Rejected, none available                                */
#define ESNMP_ALLOC_STATE_ALLOCNOCLU  0x40    /* Master agent does not support cluster index allocations */
#define ESNMP_ALLOC_STATE_DEALLOC_REJ 0x80    /* Deallocate rejected, unknown allocation		 */
#define ESNMP_ALLOC_STATE_REJ         0x100   /* Rejected for other reasons                 	         */

/*
 ******************************************************************************
 *									      *
 *  Bit definitions for ESNMP_REG.option	       			      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_REG_OPT_CLUSTER 0x01    /* Instances within this registration are cluster-wide   */ 
                                      /* (name and value are identical on all cluster members) */

/*
 ******************************************************************************
 *									      *
 *  Bit definitions for ESNMP_REG.state		       			      *
 *									      *
 ******************************************************************************
 */

#define ESNMP_REG_STATE_PENDING   0x01    /* Held locally while waiting for connection  	 */
#define ESNMP_REG_STATE_SENT      0x02    /* Has been sent to master agent              	 */
#define ESNMP_REG_STATE_DONE      0x04    /* Successfully ackowledged by master agent   	 */
#define ESNMP_REG_STATE_REGDUP    0x08    /* Rejected as a duplicate registration       	 */
#define ESNMP_REG_STATE_REGNOCLU  0x10    /* Master agent does not support cluster registrations */
#define ESNMP_REG_STATE_UNREG_REJ 0x20    /* Unregister rejected, unknown registration		 */
#define ESNMP_REG_STATE_REJ       0x40    /* Rejected for other reasons                 	 */

/*
 ******************************************************************************
 *									      *
 *  Bit definitions & macros for <foo>_mark byte fields			      *
 *									      *
 ******************************************************************************
 */

#define MARK_FLG_PRESENT	0x01	/* Data value is present */
#define MARK_FLG_CREATE		0x02	/* Data value valid for create */
#define MARK_FLG_MODIFY		0x04	/* Data value valid for modify */
#define MARK_FLG_DELETE		0x08	/* Data value valid for delete */

#define MARK_CREATE(_x_)   *(char *)(_x_) |= (MARK_FLG_CREATE | MARK_FLG_PRESENT)
#define MARK_MODIFY(_x_)   *(char *)(_x_) |= (MARK_FLG_MODIFY | MARK_FLG_PRESENT)
#define MARK_DELETE(_x_)   *(char *)(_x_) |= (MARK_FLG_DELETE | MARK_FLG_PRESENT)

#define REQ_FOR_CREATE(_x_) (*(char *)(_x_) & MARK_FLG_CREATE)
#define REQ_FOR_MODIFY(_x_) (*(char *)(_x_) & MARK_FLG_MODIFY)
#define REQ_FOR_DELETE(_x_) (*(char *)(_x_) & MARK_FLG_DELETE)

#define OPT_FOR_CREATE(_x_) (REQ_FOR_CREATE(_x_) || !(*(char *)(_x_) & MARK_FLG_PRESENT))
#define OPT_FOR_MODIFY(_x_) (REQ_FOR_MODIFY(_x_) || !(*(char *)(_x_) & MARK_FLG_PRESENT))
#define OPT_FOR_DELETE(_x_) (REQ_FOR_DELETE(_x_) || !(*(char *)(_x_) & MARK_FLG_PRESENT))


/*
 ******************************************************************************
 *									      *
 *  Data structures.							      *
 *									      *
 ******************************************************************************
 */

/* Octet String */
typedef struct _oct {
	int len;		        /* length of value in buffer */
	unsigned char *ptr;	        /* pointer to buffer */
} OCT;

/* Object Identifier */
typedef struct _oid {
	int  nelem;                     /* number of elements in oid */
	unsigned int *elements;         /* pointer to array  of elements */
} OID;


typedef struct _method METHOD;

/* MIB Object */
typedef struct _object {
	int object_index;		/* integer identifing this variable in subtree */
	OID oid;			/* OID for this variable */
	int type;			/* Type of variable */
	int (*getfunc)(METHOD *);	/* Function to perform Get/GetNext/GetBulk */
	int (*setfunc)(METHOD *);	/* Function to perform Set/Commit/Undo/Cleanup */
} OBJECT;

/* MIB Subtree */
typedef struct _subtree {
	char   *name;                   /* name of subtree in text form */
        char   *dots;                   /* OID of the subtree base in string dot form */
	OID     oid;			/* OID of the subtree base in binary integer array form*/
        OBJECT *object_tbl;             /* pointer to an array of subtree objects   */
        int     last;                   /* integer id of last item in subtree */
} SUBTREE;


/* A structure to represent a registration, for esnmp_register2() */
typedef struct _esnmp_registration {
      SUBTREE *subtree;		      /* subtree to register				       */
      u_int    priority;              /* Used for tie-breaking of duplicates, default is 128   */
      u_int    timeout;               /* Registration-specific timeout value, default is 0     */
      u_int    range_subid;           /* index into oid->elements of start of range, 0 if none */
      u_int    range_upper_bound;     /* Upper bound of range, 0 if no range                   */
      int      options;               /* Bitmask of registration options                       */
      u_int    state;                 /* Current state of (un)register operation               */
      OID     *instance;              /* instance->elements is NULL, or, contains the row
                                         (or object) instance                                  */
} ESNMP_REG;


/* Variable Binding */
typedef struct _varbind {
	OID name;			/* Identifier for object */
	int type;			/* ESNMP types */
        union _value {
            unsigned int  ul;		/* Value for Counter32, Gauge32, TimeTicks, UInteger32*/
            unsigned long ul64;		/* Value for Counter64 */
            int           sl;		/* Value for Integer32 */
            OID           oid;		/* Value for OID's */
            OCT           oct;		/* Value for everything else */
        } value;
	struct _varbind *next;		/* pointer to next varbind */
} VARBIND;

/* A structure to represent an index allocation, for esnmp_allocate() 
 * and esnmp_deallocate()
 */
typedef struct _esnmp_allocation {
      VARBIND *vb;		      /* varbind list for index (de)allocation request         */
      u_int    options;               /* Bitmask of index (de)allocation options               */
      u_int    status;                /* Current state of (de)allocation request               */
      u_int    error_index;	      /* if state indicates an error, error_index              */
                                      /* indicates which varbind was the cause                 */
} ESNMP_ALLOC;

/* Trap */
typedef struct _trap {     /* not yet used */
    OID            *enterprise;
    int            generic_trap;
    int            specific_trap;
    unsigned int   time_ticks;
    VARBIND        *varbind;
} TRAP_PDU;

/* Row context for SET's only. */
typedef struct _row_context {
	void       *context;		/* commit context (for sets) */
	void       *save;		/* undo data (for sets) */
        unsigned int *instance;         /* pointer to instance array */
        int        instance_len;        /* number of elements in instance */
        int        state;               /* Update state for Set  */
} ROW_CONTEXT;

/* Method, the sole argument passed to method routines */
struct _method {
	int action;                     /* action to perform - the packet type */
	int serial_num;         	/* serial number for packet */
	int flags;           		/* options flag and  ESNMP_FIRST_IN_ROW flag */
	int repeat_cnt;       		/* for GETBULK        */
	int max_repetitions;		/* for GETBULK        */
	VARBIND    *varbind;		/* Requesting VarBind */
	OBJECT     *object;		/* Object structure for current variable */
        void       *security;           /* placeholder for some security thingie */
	ROW_CONTEXT *row;               /* row data for SET   */
	struct _method *prev;    	/* for SET's only, NULL is head of list*/
	struct _method *next;    	/* for SET's only, NULL is end of list*/
}; /* METHOD */

#define ESNMP_FIRST_IN_ROW 0x80  /* used in flags for marking first method in row (SETs only)*/
#define ESNMP_LAST_IN_ROW  0x40  /* used in flags for marking last  method in row (SETs only)*/

/* structure passed to the external log callback routine */
typedef struct _log_callback {
	int log_level;       /* TRACE, WARNING, ERROR */
	char *text;	     /* pointer to buffer containing text of message */
        /* Note: Additional fields may be added in the future */
} LOG_CALLBACK;

typedef void(*LOG_CALLBACK_ROUTINE)(LOG_CALLBACK *);

/* A PDU structure, used only in esnmp_poll_pdu() and esnmp_poll_response(). */
typedef struct _esnmp_pdu {
        int     epdu_id;
        int     epdu_op;
        int     epdu_err_status;
        int     epdu_err_index;
        int     reserved[4];
        VARBIND *epdu_vblist;
} ESNMP_PDU;


/*
 *****************************************************************************
 *                                                                           *
 *  The DEBUG definitions.                                                   *
 *  The ESNMP_LOG macro can be used in the method routines to log messages   *
 *  to the daemon log and to assist in debugging.                            *
 *                                                                           *
 *  Example:   ESNMP_LOG(WARNING,("Cannot open file %s\n", filename));        *
 *                                                                           *
 *****************************************************************************
 */


   /* DPRINTF status codes */
#define ERROR          0x2000   /* Bad things happened, need to restart */
#define WARNING        0x1000   /* Dropping a packet - but continuing */
#define TRACE          0x0080   /* tracing packets */
#define DAEMON_LOG     0x0001   /* if TRUE we are to send log messages to daemon log */
#define EXTERN_LOG     0x0002   /* if TRUE call the callback function to log messages. */

#define ESNMP_LOG(level, x)    {if (is_debug_level(level)) { \
				    esnmp_log(level, esnmp_logs x, __LINE__, __FILE__);}}

/*
 ********************************************************************************
 *										*
 *  Function prototypes for libsnmp routines.					*
 *										*
 ********************************************************************************
 */

int     esnmp_init __((int *ssocket, char *subagent_identifier));
int     esnmp_are_you_there __((void));
int     esnmp_allocate __((ESNMP_ALLOC *alloc_parm));
int     esnmp_deallocate __((ESNMP_ALLOC *alloc_parm));
int     esnmp_register __((SUBTREE *subtree, int timeout, int priority));
int     esnmp_register2 __((ESNMP_REG *reg));
int     esnmp_unregister __((SUBTREE *subtree));
int     esnmp_unregister2 __((ESNMP_REG *reg));
int	esnmp_capabilities __((OID *agent_caps, char *agent_cap_descr));
int	esnmp_uncapabilities __((OID *agent_caps));
int     esnmp_trap __((int generic_trap, int specific_trap, char *enterprise, VARBIND *vb));
int     esnmp_term __((void));
int     esnmp_poll __((void));
int     esnmp_poll_pdu __((ESNMP_PDU **epdu_arg));
int     esnmp_pdu_response __((ESNMP_PDU *epdu));
unsigned int esnmp_sysuptime(struct timeval *timestamp);

int 	o_integer __((VARBIND *vb, OBJECT *obj, unsigned long value));
int 	o_octet __((VARBIND *vb, OBJECT *obj, OCT *oct));
int 	o_oid __((VARBIND *vb, OBJECT *obj, OID *oid));
int 	o_string __((VARBIND *vb, OBJECT *obj, unsigned char *ptr, int len));

OID 	*str2oid  __((OID *oid, char *s));
char   	*sprintoid  __((char *buffer, OID *oid));
OID 	*instance2oid  __((OID *newoid, OBJECT *obj, unsigned int *instance, int len));
int 	oid2instance  __((OID *oid, OBJECT *obj, unsigned int *instance, int max_len));
OID 	*clone_oid  __((OID *newoid, OID *oldoid));
void 	free_oid  __((OID *oid));
int 	cmp_oid  __((OID *q, OID *p));
int 	cmp_oid_prefix  __((OID *q, OID *classoid));
int 	inst2ip __((unsigned int *inst, int instLength, unsigned int *ipAddr, 
		int searchType, int carry));
char 	*clone_buf __((char *str, int len));

OCT     *mem2oct  __((OCT *newoid, char *buffer, int len));
int     cmp_oct __((OCT *oct1, OCT *oct2));
OCT 	*clone_oct  __((OCT *newoid, OCT *old));
void 	free_oct  __((OCT *oct));
void    free_varbind_data(VARBIND *vb);

void 	print_varbind __((VARBIND *vb, int indent));

void    set_debug_level  __((int stat, LOG_CALLBACK_ROUTINE callback));
int     is_debug_level __((int stat));
void    esnmp_log __((int level, char *text, int line, char *file));
char    *esnmp_logs __((char *format, ...));


/* for C++ compatability */
#ifdef __cplusplus 
}                 
#endif           


#endif  /* _ESNMP_H_  Multiple inclusion guard */

