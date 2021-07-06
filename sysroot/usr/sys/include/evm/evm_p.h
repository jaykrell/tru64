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
 * @(#)$RCSfile: evm_p.h,v $ $Revision: 1.1.14.1 $ (DEC) $Date: 2001/09/26 18:57:11 $
 */

/*=====================================================================
 * This header file contains function prototypes and definitions for
 * "private" facilities used internally by EVM, which are not intended
 * for public use.  The interfaces for these facilities are not
 * published, and are not guaranteed to be present in future releases,
 * or to remain unchanged.
 *=====================================================================*/

#ifndef	__EVM_P_H__
#define	__EVM_P_H__

#include <evm/evm.h>

#ifdef __cplusplus
extern "C"
{

#endif /* !defined(__cplusplus) */

/*
 * These macros should be used by system components to define
 * system event names in a vendor-neutral manner:
 */
#define _EvmSYSTEM_VENDOR	     "sys"
#define _EvmSYSTEM_PRODUCT	     "unix"
#define _EvmSYSTEM_VP	             _EvmSYSTEM_VENDOR "." _EvmSYSTEM_PRODUCT
#define _EvmSYSTEM_EVENT_NAME(x)     _EvmSYSTEM_VP "." x

#define _EvmEVM_EVENT_NAME(x)        _EvmSYSTEM_VP ".evm." x


#ifndef _KERNEL


EvmStatus_t
EvmConnProtocolVersionGet(EvmConnection_t a_conn, EvmUint16_t *a_version);

EvmStatus_t
EvmEventDataSizeGet (EvmConstEvent_t a_event, EvmSize_t * a_size);

EvmStatus_t
_EvmItemSetAutoWithContext(EvmEvent_t a_event,
                           EvmItemMask_t a_items,
                           EvmConnection_t a_conn);

EvmConstString_t
EvmItemDescription(EvmItemId_t a_itemid);

EvmStatus_t
EvmItemIdFromName(EvmConstString_t a_itemname, EvmItemId_t *a_itemid);

EvmStatus_t
EvmItemNameFromId(EvmItemId_t a_itemid, EvmConstString_t * a_name);

EvmStatus_t
EvmVarInit (struct EvmVarStruct_s   *a_var_p,
            EvmVarName_t            a_name_p,
            EvmVarType_t            a_type,
            const EvmVarValue_t     a_value,
            EvmI18NMsgId_t          a_msgId,
            EvmSize_t               a_valLen);

EvmStatus_t
EvmConnCreateStep (EvmConnectionType_t          a_type,
                   EvmResponseMode_t            a_responseMode,
                   const EvmTransport_t *       a_transport,
                   const EvmCallback_t          a_callback,
                   const EvmCallbackArg_t       a_callbackArg,
                   EvmConnection_t *            a_conn_p,
                   EvmBoolean_t                 a_stepwise,
		   EvmUint32_t *                a_cookie);

#define EvmItemCompare(e1,e2,item,same) _EvmItemCompare(e1,e2,item,0,same)
EvmStatus_t
_EvmItemCompare (EvmConstEvent_t a_event1,
		 EvmConstEvent_t a_event2,
		 EvmItemId_t a_item,
		 unsigned int a_debug,
		 EvmBoolean_t * a_same);

#define EvmVarCompare(e1,e2,name,same) _EvmItemCompare(e1,e2,name,0,same)
EvmStatus_t
_EvmVarCompare (EvmConstEvent_t a_event1,
		EvmConstEvent_t a_event2,
		EvmVarName_t a_name,
		unsigned int a_debug,
		EvmBoolean_t * a_same);

#define EvmEventCompare(e1,e2,igmsk,same) _EvmEventCompare(e1,e2,igmsk,0,same)
EvmStatus_t
_EvmEventCompare (EvmConstEvent_t a_event1,
		  EvmConstEvent_t a_event2,
		  EvmItemMask_t a_ignoreMask,
		  unsigned int a_debug,
		  EvmBoolean_t * a_same);

EvmStatus_t
_EvmItemSetAuto (EvmEvent_t a_event, EvmItemMask_t a_items);

EvmStatus_t
_EvmQueuePointerGet (EvmEvent_t a_event, EvmEvent_t *a_next);

EvmStatus_t
_EvmQueuePointerSet (EvmEvent_t a_event, EvmEvent_t a_next);

#define EvmEventMergeTemplate(a_event, a_template) \
	_evmMerge(a_event,a_template)

EvmString_t
_EvmFilenameConstruct(EvmString_t a_fileNameBase,
                      EvmInt32_t a_ident,
                      EvmPid_t a_pid);


/*==========================================================
 * Support for Binary Error Log (binlog) interpretation
 *==========================================================*/
#ifdef EVM_INCLUDE_BINLOG_SUPPORT
#include <dec/binlog/binlog.h>

EvmStatus_t
EvmBinlogEventToEvm(char *a_event, EvmEvent_t *a_evm_event);

void
EvmBinlogSCSIReporter(unsigned char * buf);

void
EvmBinlogValidateEvent(char *a_event, EvmBoolean_t *a_valid);

int
EvmBinlogEventSize(char *a_event);

EvmBoolean_t
EvmBinlogEventIsCEH(char *a_event);

#endif /* End of binlog support */


/*==========================================================
 * General constants - these could be moved
 *==========================================================*/
/*
 * Path for the local domain socket.
 * The environment variable overrides the default value.
 */
#define EvmLOCAL_PORT_DEFAULT "/var/evm/sockets/evmd"
#define EvmLOCAL_PORT_ENVVAR "EVM_LOCAL_PORT"

/*
 * Path for the daemon configuration file.
 * The environment variable overrides the default value.
 */
#define EvmDAEMON_CONFIG_DEFAULT "/etc/evmdaemon.conf"
#define EvmDAEMON_CONFIG_ENVVAR "EVM_DAEMON_CONFIGURATION"

#endif /* _KERNEL */

#ifdef _KERNEL
#ifdef _KEVM_ILP_DEBUG

void
KevmIntBufPostTest(void);

/* Trigger is number of executions after which an event is posted. */
#define KEVM_INT_POST_TEST_TRIGGER 5000

#define KEVM_INT_POST_TEST_PERIODIC 					\
{									\
   static _Static_Kevm_Int_Buf_test_count = 0;				\
									\
   if (_Static_Kevm_Int_Buf_test_count++ >= KEVM_INT_POST_TEST_TRIGGER)	\
   {									\
      _Static_Kevm_Int_Buf_test_count = 0;				\
      KevmIntBufPostTest();						\
   }									\
}

#else

#define KEVM_INT_POST_TEST_PERIODIC  

#endif
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* __EVM_P_H__ */
