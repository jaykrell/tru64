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
 * 
 * @(#)$RCSfile: evm.h,v $ $Revision: 1.1.24.1 $ (DEC) $Date: 2001/09/26 18:57:10 $
 * 
 * MODULE:	evm.h
 *
 * ABSTRACT:	Public C-language for the EVM API.
 *
 * NOTES:	
*/
#ifndef	__EVM_H__
#define	__EVM_H__


/******************* System include files */
#ifndef _KERNEL
#include <stdio.h>
#endif


/******************* Application specific include files */
#include <evm/evm_types.h>



/******************* Datatypes */
/******************* Constant parameters */
#define EvmMAX_CLUSTER_EVENT_SIZE (128*1024)


/******************* Macros */

/* Simple derived types */
typedef	EvmChar_t		*EvmString_t;
typedef	const EvmChar_t		*EvmConstString_t;

typedef EvmInt32_t		EvmI18NMsgId_t;
#define EvmI18N_MSG_ID_NONE	(EvmI18NMsgId_t)0

typedef EvmInt32_t		EvmI18NSetId_t;
#define EvmI18N_SET_DEFAULT	(EvmI18NSetId_t)1

typedef EvmString_t		EvmI18NCatalog_t;
typedef EvmInt32_t		EvmFd_t;
typedef int       		EvmMemberId_t;
typedef EvmUint32_t		EvmTimestamp_t;
typedef EvmUint32_t		EvmCount_t;
typedef EvmUint32_t		EvmEventId_t;

typedef EvmUint32_t		EvmIpAddress_t;
#define EvmIpAddress_UNDEFINED (~((EvmIpAddress_t)0))

/* Event priority datatype */
typedef EvmUint16_t	EvmPriority_t;

#define EvmPRIO_EMERGENCY	700
#define EvmPRIO_MAX		EvmPRIO_EMERGENCY
#define EvmPRIO_ALERT		600
#define EvmPRIO_CRITICAL	500
#define EvmPRIO_ERROR		400
#define EvmPRIO_WARNING		300
#define EvmPRIO_NOTICE		200
#define EvmPRIO_INFORMATION	100
#define EvmPRIO_DEBUG		0


/******************* Event format flags */
#define EvmFMT_NO_REPEAT_COUNT  1 << 0

 
/*
 * Anonymous structure available for type checking.
 */
struct EvmEventHandle_s;
typedef struct EvmEventHandle_s	*EvmEvent_t;
typedef const struct EvmEventHandle_s * EvmConstEvent_t;

/*
 * Available types for user supplied event variables.
 */
typedef enum	EvmVarType_e
{
	EvmTYPE_NONE = 0,
	EvmTYPE_BOOLEAN,
	EvmTYPE_FIRST = EvmTYPE_BOOLEAN,
	EvmTYPE_CHAR,
	EvmTYPE_INT16,
	EvmTYPE_INT32,
	EvmTYPE_INT64,
	EvmTYPE_UINT8,
	EvmTYPE_UINT16,
	EvmTYPE_UINT32,
	EvmTYPE_UINT64,
	EvmTYPE_FLOAT,
	EvmTYPE_DOUBLE,
	EvmTYPE_STRING,
	EvmTYPE_OPAQUE,
	EvmTYPE_MAX = EvmTYPE_OPAQUE
} EvmVarType_t;

typedef union	EvmVarValue_u
{
	EvmString_t	STRING;
	EvmBoolean_t	BOOLEAN;
	EvmChar_t	CHAR;
	EvmInt16_t	INT16;
	EvmInt32_t	INT32;
	EvmInt64_t	INT64;
	EvmUint8_t	UINT8;
	EvmUint16_t	UINT16;
	EvmUint32_t	UINT32;
	EvmUint64_t	UINT64;
	EvmFloat_t	FLOAT;
	EvmDouble_t	DOUBLE;
	EvmOpaque_t	OPAQUE;
} EvmVarValue_t;

#define EvmNUMBER_OF_VARTYPES (EvmTYPE_MAX - EvmTYPE_FIRST + 1)

typedef	EvmUint32_t	EvmSize_t;

typedef EvmConstString_t	EvmVarName_t;

typedef struct EvmVarStruct_s
{
	EvmVarType_t		type;
	EvmVarName_t		name_p;
	EvmVarValue_t		value;
	EvmSize_t		length;
	EvmI18NMsgId_t		msgId;
} EvmVarStruct_t;

typedef EvmVarName_t	*EvmVarList_t;

#define EvmTYPE_IS_VALID(pbp) \
	(((pbp) <= EvmTYPE_MAX) && ((pbp) > EvmTYPE_NONE))

/*
 * Definition of the EVM event item identifiers.  The existing
 * enumerations should not be changed, except to replace
 * "UNUSED" enumerations and increase the value of "MAX".
 */
typedef enum	EvmItemId_e
{
	EvmITEM_NONE = 0,
	EvmITEM_FIRST = 1,
	EvmITEM_NAME = EvmITEM_FIRST,
	EvmITEM_UNUSED_1,		/* Do not remove; OK to reassign */
	EvmITEM_KERNEL_ONLY,
	EvmITEM_CLUSTER_EVENT,
	EvmITEM_PRIORITY,
	EvmITEM_PID,
	EvmITEM_PPID,
	EvmITEM_EVENT_ID,
	EvmITEM_MEMBER_ID,
	EvmITEM_TIMESTAMP,
	EvmITEM_HOST_IP,
	EvmITEM_REPEAT_COUNT,
	EvmITEM_LAST_TIMESTAMP,
	EvmITEM_I18N_MSG_ID,
	EvmITEM_I18N_SET_ID,
	EvmITEM_I18N_CATALOG,
	EvmITEM_CLUSTER_IP,
	EvmITEM_HOST_NAME,
	EvmITEM_CLUSTER_NAME,
	EvmITEM_USER_NAME,
	EvmITEM_FORMAT,
	EvmITEM_REF,
	EvmITEM_PREDEFINED_MAX = EvmITEM_REF,	/* Last item defined by EVM. */
	EvmITEM_VAR,
	EvmITEM_MAX = EvmITEM_VAR,	 /* Used for item validation. */

	/* This group of items is used for internal EVM operations only. */
	EvmITEM_INTERNAL_USE_FIRST = 512,       /* Table of internal items. */
	EvmITEM_HDR_EXT_SIZE = EvmITEM_INTERNAL_USE_FIRST,
	EvmITEM_FORMATTED,
	EvmITEM_INTERNAL_USE_LAST = EvmITEM_HDR_EXT_SIZE,

	/*
	 * The following enumeration values are used to distinguish
	 * different variable types when setting values in an event using
	 * convenicence wrapper functions.  They do not specify discrete
	 * items, and will never be returned when retrieving information
	 * about the contents of an event.  These values must be greater
	 * than the value of EvmITEM_MAX.
	 */
	EvmITEM_VAR_FIRST = 1024,
	EvmITEM_VAR_BOOLEAN = EvmITEM_VAR_FIRST,
	EvmITEM_VAR_CHAR,
	EvmITEM_VAR_INT16,
	EvmITEM_VAR_INT32,
	EvmITEM_VAR_INT64,
	EvmITEM_VAR_UINT8,
	EvmITEM_VAR_UINT16,
	EvmITEM_VAR_UINT32,
	EvmITEM_VAR_UINT64,
	EvmITEM_VAR_FLOAT,
	EvmITEM_VAR_DOUBLE,
	EvmITEM_VAR_STRING,
	EvmITEM_VAR_STRING_I18N,
	EvmITEM_VAR_OPAQUE,
	EvmITEM_VAR_MAX = EvmITEM_VAR_OPAQUE
} EvmItemId_t;

#define EvmITEM_IS_VALID(pbp) \
	(((pbp) <= EvmITEM_MAX) && ((pbp) > EvmITEM_NONE))

#define EvmNUMBER_OF_ITEMS (EvmITEM_MAX - EvmITEM_FIRST + 1)

typedef union	EvmItemValue_u
{
	EvmString_t		NAME;
	EvmBoolean_t		KERNEL_ONLY;
	EvmBoolean_t		CLUSTER_EVENT;
	EvmPriority_t		PRIORITY;
	EvmMemberId_t		MEMBER_ID;
	EvmPid_t		PID;
	EvmPid_t		PPID;
	EvmEventId_t		EVENT_ID;
	EvmTimestamp_t		TIMESTAMP;
	EvmIpAddress_t		HOST_IP;
	EvmI18NMsgId_t		I18N_MSG_ID;
	EvmI18NSetId_t		I18N_SET_ID;
	EvmI18NCatalog_t	I18N_CATALOG;
	EvmCount_t		REPEAT_COUNT;
	EvmTimestamp_t		LAST_TIMESTAMP;
	EvmIpAddress_t		CLUSTER_IP;
	EvmString_t		HOST_NAME;
	EvmString_t		CLUSTER_NAME;
	EvmString_t		USER_NAME;
	EvmString_t		FORMAT;
	EvmString_t		REF;
	EvmVarStruct_t *	VAR;
} EvmItemValue_t;

typedef	EvmItemId_t	*EvmItemList_t;

/*
 * Definition of item/value list.
 */

typedef	struct EvmItemEntry_s
{
	EvmItemId_t	id;
	EvmItemValue_t	value;
} EvmItemEntry_t;

typedef	EvmItemEntry_t	*EvmItemEntryList_t;

/*
 * Error/Status return codes for all EVM functions
 */
typedef	enum EvmStatus_e
{
	EvmERROR_NONE = 0,
	EvmERROR_NOT_IMPLEMENTED = 1,
	EvmERROR_INVALID_ARGUMENT = 2,
	EvmERROR_NOT_SET = 3,
	EvmERROR_NOT_PRESENT = 4,
	EvmERROR_PROTOCOL_MISMATCH = 5,
	EvmERROR_NO_MEMORY = 6,
	EvmERROR_INVALID_VARARGS_LIST = 7,
	EvmERROR_FILTER_NOT_VALID = 8,
	EvmERROR_INVALID_VALUE = 9,
	EvmERROR_NOT_INITIALIZED = 10,
	EvmERROR_SELECT = 11,
	EvmERROR_SERVICE_TERMINATED = 12,
	EvmERROR_CONNECT = 13,
	EvmERROR_READ = 14,
	EvmERROR_WRITE = 15,
	EvmERROR_OPEN = 16,
	EvmERROR_EVENT_REJECTED = 17,
	EvmERROR_RESOURCE = 18,
	EvmERROR_SEQUENCE = 19,
	EvmERROR_CONNECTION_LOST = 20,
	EvmERROR_INVALID_OPERATION = 21,
	EvmERROR_INVALID_MESSAGE = 22,
	EvmERROR_PARTIAL = 23,
	EvmERROR_WOULDBLOCK = 24,
	EvmERROR_TIMEOUT = 25,
	EvmERROR_QUEUE_FULL = 26,
	EvmERROR_PROTOCOL = 27,
	EvmERROR_INTERRUPT_LEVEL = 28,	/* op prohibited at interrupt level */
	EvmERROR_EOF = 29,
	EvmERROR_SIGNAL = 30,
	EvmERROR_SYNCHRONIZATION_FAILURE = 31,
	EvmERROR_EVENT_NOT_VALID = 32,
	EvmERROR_QUEUED = 33,
	EvmERROR_CONNECTION_REFUSED = 34,
	EvmERROR_TOO_MANY_ITEMS = 35,
	EvmERROR_INVALID_TYPE = 36,
	EvmERROR_EVENT_TOO_BIG = 37,
	EvmERROR_LAST
} EvmStatus_t;


/*
 * Common program exit codes:
 */
#define EvmEXIT_OK 		0
#define EvmEXIT_USAGE 		1
#define EvmEXIT_ARGS 		2
#define EvmEXIT_ENV 		3
#define EvmEXIT_CONFIG 		4
#define EvmEXIT_OPEN_ERR 	5
#define EvmEXIT_IO_ERR	 	6
#define EvmEXIT_TIMEOUT 	7
#define EvmEXIT_CONNECTION 	8
#define EvmEXIT_POST 		9
#define EvmEXIT_SUBSCRIBE 	10
#define EvmEXIT_SERVICE 	11
#define EvmEXIT_CHANNEL_ERR 	12
#define EvmEXIT_FILTER 		13
#define EvmEXIT_MEMORY 		14
#define EvmEXIT_ACCESS 	        15
#define EvmEXIT_UNKNOWN_HOST 	16

#define EvmEXIT_ERROR 		99



/***** DATATYPES FOR THE FILTER EVALUATOR API */

/* if C++
 *    declare C++ classes types correctly
 * else (C)
 *    declare C structs to simulate C++ classes
 */
#ifdef __cplusplus
class EvmFilterEval_c;

#else /* !defined(__cplusplus) */
struct EvmFilterEval_s;
typedef struct EvmFilterEval_s EvmFilterEval_c;

#endif /* !defined(__cplusplus) */

/* Opaque filter evaluator datatype */
typedef EvmFilterEval_c * EvmFilter_t;



/***** CONNECTION HANDLING DATATYPES *****/

/* Opaque datatype for a connection to an event switch/distributor */
typedef struct EvmConnection_s * EvmConnection_t;

typedef EvmOpaque_t EvmCallbackArg_t;

/* Purpose of a connection */
typedef enum EvmConnectionType_e {
	EvmCONNECTION_POST,
	EvmCONNECTION_LISTEN,
	EvmCONNECTION_SERVICE,

	EvmCONNECTION_INTERNAL_USE_FIRST = 512,  /* Table of internal types. */
	EvmCONNECTION_AUTHENT_1 = EvmCONNECTION_INTERNAL_USE_FIRST,
	EvmCONNECTION_AUTHENT_2
} EvmConnectionType_t;

/* Response type for a connection */
typedef enum EvmResponseMode_e {
        EvmRESPONSE_WAIT,
        EvmRESPONSE_CALLBACK,
        EvmRESPONSE_IGNORE
} EvmResponseMode_t;

/* Transport mechanism for a connection: type and supporting data */
typedef enum EvmTransportType_e {
        EvmTRANSPORT_DOMAIN_SOCKET,
        EvmTRANSPORT_TCPIP
} EvmTransportType_t;

/* Connection control request codes */
typedef	enum	EvmConnControlRequest_e
{
		EvmCONN_RCV_SZ_GET,
		EvmCONN_RCV_SZ_SET,
		EvmCONN_SND_SZ_GET,
		EvmCONN_SND_SZ_SET,
		EvmCONN_CHECKSUM_ENABLE,
		EvmCONN_CHECKSUM_DISABLE,
		EvmCONN_CHECKSUM_IS_ENABLED,
		EvmCONN_IS_CLUSTER_ALIAS,
		EvmCONN_REMOTE_IS_ON_CLUSTER,
		EvmCONN_LOCAL_HOST_NAME_GET,
		EvmCONN_LOCAL_IP_GET,
		EvmCONN_REMOTE_HOST_NAME_GET,
		EvmCONN_REMOTE_IP_GET,
		EvmCONN_CLUSTER_LIST_GET,
		EvmCONN_CLUSTER_HOST_IP_GET,
		EvmCONN_POST_ITEM_MASK_SET,
		EvmCONN_POST_ITEM_MASK_RESET,
		EvmCONN_POST_NONBLOCK_SET
} EvmConnControlRequest_t;


struct EvmDomainSocketData_s {
        EvmString_t name; /* if NULL, use default */
};

struct EvmTcpipData_s {
        EvmInt32_t portNumber; /* if -1, use default */
        EvmString_t hostName; /* if NULL, use local host */
};

typedef union EvmTransportData_u {
        struct EvmDomainSocketData_s domainSocket;
        struct EvmTcpipData_s tcpip;
} EvmTransportData_t;

typedef struct EvmTransport_s {
        EvmTransportType_t type;
        EvmTransportData_t data;
} EvmTransport_t;

/* data returned by a callback */
typedef enum EvmCallbackReason_e {
    EvmREASON_POST_COMPLETE, 
    EvmREASON_EVENT_DELIVERED, 
    EvmREASON_SUBSCRIBE_COMPLETE,
    EvmREASON_TEMPLATE_INFO_DELIVERED,
    EvmREASON_REGISTRATION_DELIVERED,
    EvmREASON_EVENTS_MISSED,
    EvmREASON_KBUFF_OVERFLOW 
} EvmCallbackReason_t;

typedef struct EvmCallbackTemplateData_s {
    EvmPointer_t userArg;
    EvmBoolean_t resetToFirst;
    EvmPriority_t squelchLevel;
} EvmCallbackTemplateData_t;

typedef struct EvmCallbackEventMissedData_s {
    EvmInt32_t missedCount;
} EvmCallbackEventMissedData_t;

typedef struct EvmCallbackKBuffOverflowData_s {
    EvmInt32_t			missedCount;
} EvmCallbackKBuffOverflowData_t;

typedef union EvmCallbackExtension_u {
    EvmCallbackTemplateData_t 		templateData;
    EvmCallbackEventMissedData_t 	eventMissedData;
    EvmCallbackKBuffOverflowData_t 	kBuffOverflowData;
} EvmCallbackExtension_t;

typedef struct EvmCallbackData_s {
    EvmCallbackReason_t 	reason;
    EvmEvent_t 			event; 
    EvmStatus_t 		status;
    EvmCallbackExtension_t 	extension;
} EvmCallbackData_t;

/*
 * Callback used by connection to provide asynchronous response. 
 */
typedef void (*EvmCallback_t) (EvmConnection_t a_conn,
			       EvmCallbackArg_t a_callbackArg,
			       EvmCallbackData_t * a_callbackData);



/******************* MACROS FOR NULL VARIABLE TYPES */

/*
 * The following macros define values that are guaranteed to be invalid
 * for their respective datatypes.
 * These values can be used as flags for uninitialized variables.
 */
#define EvmEventNULL		((EvmEvent_t)0)
#define EvmVarListNULL		((EvmVarList_t)0)
#define EvmItemListNULL		((EvmItemList_t)0)
#define EvmFilterNULL		((EvmFilter_t)0)
#define EvmTransportNULL	((EvmTransport_t *)0)
#define EvmCallbackNULL		((EvmCallback_t)0)
#define EvmCallbackArgNULL	((EvmCallbackArg_t)0)
#define EvmCallbackDataNULL	((EvmCallbackData_t)0)
#define EvmConnectionNULL	((EvmConnection_t)0)

/*
 * This macro defines the timeout value if you want no timeout
 * (i.e. wait forever if necessary).
 */
#define EvmTIMEOUT_NONE		((struct timeval *)0)




/******************* GLOBAL FUNCTIONS */

#ifdef __cplusplus
/* tell C++ compiler not to mangle the following function names */
extern "C"
{
#endif /* !defined(__cplusplus) */


/***** EVM STATUS CODE INTERPRETATION *****/

/*
 * Returns up to a_nBytes of descriptive text about an EVM error code in
 * the user-supplied buffer p_text.
 */
EvmStatus_t
EvmStatusTextGet (EvmStatus_t p_status,
		  EvmString_t p_text,
		  EvmSize_t p_nBytes);


/***** GENERAL EVENT MANIPULATION */

#define EvmEventCreate(ev)	EvmEventCreateVa((ev),EvmITEM_NONE)

EvmStatus_t
EvmEventDup (EvmEvent_t * dup_ev, EvmConstEvent_t ev);

EvmStatus_t
EvmEventDestroy (EvmEvent_t a_ev_p);

/*
 * Indicating a single item/value_reference pair (item may be variable):
 *	EvmStatus_t
 *	EvmEventCreateVa (EvmEvent_t	a_ev_p,
 *			  EvmItemId_t itemId, EvmItemValue_t item,
 *			  ...
 *			  EvmITEM_NONE);
 */
EvmStatus_t
EvmEventCreateVa (EvmEvent_t * a_ev_p, ...);

EvmStatus_t
EvmEventCreateFromList (EvmEvent_t *	a_ev_p,
			EvmItemEntryList_t	a_ivlist_p,
			EvmCount_t		a_number);

EvmStatus_t
EvmEventValidate (EvmConstEvent_t a_event);

EvmStatus_t
EvmEventFormat (char * a_buff, size_t a_bufflen, EvmConstEvent_t a_ev);

EvmStatus_t
EvmEventFormatOpt(char *a_buff, size_t a_bufflen, EvmConstEvent_t a_ev,
			    EvmUint32_t a_flags);

EvmStatus_t
EvmEventFormatFromTemplate(char * a_buff, size_t a_bufflen,
			   EvmString_t a_template, EvmConstEvent_t a_ev);

#ifndef _KERNEL

EvmStatus_t
EvmEventDump (EvmConstEvent_t a_event, FILE * a_fd);

#endif

EvmStatus_t
EvmEventWrite (EvmFd_t a_fileDes, EvmConstEvent_t a_ev_p);

EvmStatus_t
EvmItemWriteBinary(EvmFd_t a_fd,EvmEvent_t a_ev,EvmString_t a_itemname);

EvmStatus_t
EvmVarWriteBinary(EvmFd_t a_fd,EvmEvent_t a_ev,EvmString_t a_varname);

EvmStatus_t
EvmEventRead (EvmFd_t a_fileDes, EvmEvent_t * a_ev_p);

EvmStatus_t
EvmEventAutoExtendName (EvmEvent_t a_event, EvmUint32_t *count );

#ifdef _KERNEL

/* Interrupt level kernel event posting routine. */
EvmStatus_t
EvmEventPostImmedVa (void *a_null, ...);

#endif


/***** EVENT ITEM MANIPULATION */

/*
 * Indicating a single item/value_reference pair (item may be variable):
 *	EvmStatus_t
 *	EvmItemSetVa (EvmEvent_t	a_ev_p,
 *		      EvmItemId_t itemId, EvmItemValue_t item,
 *		      ...
 *		      EvmITEM_NONE);
 */
EvmStatus_t
EvmItemSetVa (EvmEvent_t a_ev_p, ...);

#define EvmItemSet(ev,id,val)	EvmItemSetVa((ev),(id),(val),EvmITEM_NONE)

EvmStatus_t
EvmItemEntryListSet (EvmEvent_t		a_ev_p,
		     EvmItemEntryList_t	a_ivlist_p,
		     EvmCount_t		a_number);

EvmStatus_t
EvmItemGet (EvmConstEvent_t	a_ev_p,
	    EvmItemId_t		a_item,
	    EvmItemValue_t *	a_value_p);

EvmStatus_t
EvmItemRelease (EvmItemId_t	a_item,
		EvmItemValue_t	a_value);

EvmStatus_t
EvmItemListGet (EvmConstEvent_t	a_ev_p,
		EvmCount_t 	*a_number_p,
		EvmItemList_t 	*a_list_p);

EvmStatus_t
EvmItemListFree (EvmItemList_t a_list_p);


/***** EVENT VARIABLE MANIPULATION */

EvmStatus_t
EvmVarSet (EvmEvent_t		a_ev_p,
	   EvmVarName_t		a_name_p,
	   EvmVarType_t		a_type,
	   const EvmVarValue_t	a_value,
	   EvmI18NMsgId_t	a_msgId,
	   EvmSize_t		a_valLen);

EvmStatus_t
EvmVarGet (EvmConstEvent_t	a_ev_p,
	   EvmVarName_t		a_name, 
	   EvmVarStruct_t *	a_var_p);

EvmStatus_t
EvmVarRelease (EvmVarStruct_t	*a_var_p);

EvmStatus_t
EvmVarListGet (EvmConstEvent_t	a_ev_p,
	       EvmCount_t 	*a_number_p,
	       EvmVarList_t 	*a_list_p);

EvmStatus_t
EvmVarListFree (EvmVarList_t 	a_list_p);

EvmStatus_t
EvmVarFormat(EvmConstEvent_t a_ev, const char *a_varname, char *a_buff,
		size_t a_buffsz, EvmBoolean_t a_translate);


/***** VARSET WRAPPER FUNCTIONS */

EvmStatus_t EvmVarSetBoolean(EvmEvent_t ev,EvmVarName_t name,
	const EvmBoolean_t value);

EvmStatus_t EvmVarSetChar(EvmEvent_t ev,EvmVarName_t name,
	const EvmChar_t value);

EvmStatus_t EvmVarSetInt16(EvmEvent_t ev,EvmVarName_t name,
	const EvmInt16_t value);

EvmStatus_t EvmVarSetInt32(EvmEvent_t ev,EvmVarName_t name,
	const EvmInt32_t value);

EvmStatus_t EvmVarSetInt64(EvmEvent_t ev,EvmVarName_t name,
	const EvmInt64_t value);

EvmStatus_t EvmVarSetUint8(EvmEvent_t ev,EvmVarName_t name,
	const EvmUint8_t value);

EvmStatus_t EvmVarSetUint16(EvmEvent_t ev,EvmVarName_t name,
	const EvmUint16_t value);

EvmStatus_t EvmVarSetUint32(EvmEvent_t ev,EvmVarName_t name,
	const EvmUint32_t value);

EvmStatus_t EvmVarSetUint64(EvmEvent_t ev,EvmVarName_t name,
	const EvmUint64_t value);

#ifndef _KERNEL
EvmStatus_t EvmVarSetFloat(EvmEvent_t ev,EvmVarName_t name,
	const EvmFloat_t value);
#endif

#ifndef _KERNEL
EvmStatus_t EvmVarSetDouble(EvmEvent_t ev,EvmVarName_t name,
	const EvmDouble_t value);
#endif

EvmStatus_t EvmVarSetString(EvmEvent_t ev,EvmVarName_t name,
	const EvmString_t value);

EvmStatus_t EvmVarSetStringI18n(EvmEvent_t ev,EvmVarName_t name,
	const EvmString_t value,EvmI18NMsgId_t msgid);

EvmStatus_t EvmVarSetOpaque(EvmEvent_t ev,EvmVarName_t name,
	const EvmOpaque_t value,EvmSize_t size);

/***** VARGET WRAPPER FUNCTIONS */

EvmStatus_t
EvmVarGetType(EvmEvent_t ev, EvmVarName_t varname, EvmVarType_t *type);

EvmStatus_t
EvmVarCheckType(EvmEvent_t ev, EvmVarName_t varname, EvmVarType_t type);

EvmStatus_t EvmVarGetBoolean(EvmEvent_t ev,EvmVarName_t name,
	EvmBoolean_t *value);

EvmStatus_t EvmVarGetChar(EvmEvent_t ev,EvmVarName_t name,
	EvmChar_t *value);

EvmStatus_t EvmVarGetInt16(EvmEvent_t ev,EvmVarName_t name,
	EvmInt16_t *value);

EvmStatus_t EvmVarGetInt32(EvmEvent_t ev,EvmVarName_t name,
	EvmInt32_t *value);

EvmStatus_t EvmVarGetInt64(EvmEvent_t ev,EvmVarName_t name,
	EvmInt64_t *value);

EvmStatus_t EvmVarGetUint8(EvmEvent_t ev,EvmVarName_t name,
	EvmUint8_t *value);

EvmStatus_t EvmVarGetUint16(EvmEvent_t ev,EvmVarName_t name,
	EvmUint16_t *value);

EvmStatus_t EvmVarGetUint32(EvmEvent_t ev,EvmVarName_t name,
	EvmUint32_t *value);

EvmStatus_t EvmVarGetUint64(EvmEvent_t ev,EvmVarName_t name,
	EvmUint64_t *value);

#ifndef _KERNEL
EvmStatus_t EvmVarGetFloat(EvmEvent_t ev,EvmVarName_t name,
	EvmFloat_t *value);
#endif

#ifndef _KERNEL
EvmStatus_t EvmVarGetDouble(EvmEvent_t ev,EvmVarName_t name,
	EvmDouble_t *value);
#endif

EvmStatus_t EvmVarGetOpaque(EvmEvent_t ev,EvmVarName_t name,
	EvmOpaque_t *buff,EvmSize_t *size);

EvmStatus_t EvmVarGetString(EvmEvent_t ev,EvmVarName_t name,
	EvmString_t *string,EvmI18NMsgId_t *msgid);

/***** FILTER FUNCTIONS */

EvmStatus_t
EvmFilterCreate (EvmFilter_t	*a_filter_p);

EvmStatus_t
EvmFilterDestroy (EvmFilter_t	a_filter);

EvmStatus_t
EvmFilterSet (EvmFilter_t	a_filter,
	      EvmConstString_t	a_value);
    
EvmStatus_t
EvmFilterDirSet (EvmFilter_t		a_filter,
		 EvmConstString_t	a_directory);
    
EvmStatus_t
EvmFilterTest (EvmFilter_t	a_filter,
	       EvmConstEvent_t	a_event,
	       EvmBoolean_t	*a_matchFlag_p);

EvmStatus_t
EvmFilterIsFile( const char *a_filter, EvmBoolean_t *o_arg);

EvmStatus_t
EvmFilterReadFile( const char *a_filter, char **o_filter);

/***** EVENT NAME MATCHING */

EvmStatus_t
EvmEventNameMatchStr(const char *a_pattern, const char * a_candidate,
        EvmBoolean_t *a_match);

EvmStatus_t
EvmEventNameMatch(const char *a_pattern, EvmEvent_t a_event,
        EvmBoolean_t *a_match);

/***** GENERAL CONNECTION HANDLING *****/

/* Create a connection */
EvmStatus_t
EvmConnCreate (EvmConnectionType_t	a_type,
	       EvmResponseMode_t	a_mode,
	       const EvmTransport_t	*a_transport, /* NULL for default */
	       EvmCallback_t		a_callback,
	       EvmCallbackArg_t		a_callbackArg,
	       EvmConnection_t		*a_conn_p);

#define EvmConnCreatePoster(conn) \
	EvmConnCreate(EvmCONNECTION_POST,EvmRESPONSE_WAIT,NULL,NULL,NULL,(conn))

#define EvmConnCreateSubscriber(callback,arg,conn) \
	EvmConnCreate(EvmCONNECTION_LISTEN,EvmRESPONSE_CALLBACK,NULL, \
				(callback),(arg),(conn))

/* Disconnect and destroy a connection */
EvmStatus_t
EvmConnDestroy (EvmConnection_t	a_conn);

/* Get the Fd for this connection */
EvmStatus_t
EvmConnFdGet (EvmConnection_t	a_conn,
	      EvmFd_t 		*a_fd);

/* Check for unprocessed response information on this connection */
EvmStatus_t
EvmConnCheck (EvmConnection_t	a_conn,
	      EvmBoolean_t	*a_responsePresent_p);

/* Wait for response on this connection. */
#ifndef _SYS_TIME_H_
struct timeval; /* defined in <sys/time.h> */
#endif
EvmStatus_t
EvmConnWait (EvmConnection_t a_conn, const struct timeval *a_timeout);

/*
 * Handle any outstanding i/o for the connection:
 */
EvmStatus_t
EvmConnDispatch (EvmConnection_t a_conn);

/*
 * Connection control function:
 */
EvmStatus_t
EvmConnControl (EvmConnection_t a_conn,
                EvmInt32_t a_request,
                void *a_argument);

/*
 * Flush queued messages:
 */
EvmStatus_t
EvmConnFlush (EvmConnection_t	a_conn,
	      EvmInt32_t	*a_count);


#ifndef _KERNEL
/*
 * Get socket buffer max size
 */
EvmInt32_t
EvmGetSocketBufferLimit( void );

#endif


/***** EVENT POSTING *****/

/* Post an event to a connection */
EvmStatus_t
EvmEventPost (
#ifndef _KERNEL
	      EvmConnection_t a_conn,
#endif /* _KERNEL */
	      EvmEvent_t a_event);
                            

EvmStatus_t EvmEventPostVa(
#ifndef _KERNEL
	      EvmConnection_t a_conn,
#endif /* _KERNEL */
	      EvmEvent_t a_event, ...);

/***** EVENT LISTENING & SUBSCRIPTION *****/

/* Subscribe for events */
EvmStatus_t
EvmConnSubscribe (EvmConnection_t	a_conn,
		  void		 	*a_hostList, /* Not used */
		  EvmConstString_t	a_filter);

#ifndef _KERNEL


EvmStatus_t
EvmConnRegistrationGet (EvmConnection_t         a_conn,
                        EvmConstString_t        a_eventClass,
                        EvmPointer_t            a_userArg);


EvmStatus_t
EvmConnTemplateScan (EvmConnection_t    a_conn,
                     EvmConstString_t   a_filter,
                     EvmPointer_t       a_userArg);


/***** EVM SERVICE FUNCTIONS *****/

EvmStatus_t
EvmSrvStart (char		*a_service_name,
	     char		*a_arg_string,
	     EvmTransport_t	*a_transport,
	     EvmConnection_t	*a_conn);

EvmStatus_t
EvmSrvMessageGet (EvmConnection_t	a_conn,
		  EvmEvent_t		*a_ev,
		  char			**a_msg,
		  char			**a_errmsg,
		  EvmInt32_t		*a_data);


typedef unsigned long EvmItemMask_t;
#define EvmItemMask_(a_item) (0x1L<<((int)(a_item)))
#define EvmItemMaskALL ((EvmItemMask_t)(-1L))

#endif /* End of non-kernel only */

/*
 * evm_p.h depends on definitions above, so must
 * be included at the end.
 */
#include <evm/evm_p.h>

typedef char *EvmHandle_S_t ;
#ifdef _KERNEL
EvmStatus_t EvmKernelEventSubscribe
	(EvmHandle_S_t	*, char *, char *, void (*)(EvmEvent_t, void *), void *);
EvmStatus_t EvmKernelEventUnsubscribe(EvmHandle_S_t);
#endif

#ifdef __cplusplus
/* end of non-mangled-function-name block */
}
#endif /* __cplusplus */

#endif	/* __EVM_H__ */
