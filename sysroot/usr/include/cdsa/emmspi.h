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
 * @(#)$RCSfile: emmspi.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:20 $
 */
/*-----------------------------------------------------------------------
 * File: EMMSPI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

/* Portions:
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */ 

#ifndef _EMMSPI_H
#define _EMMSPI_H    

/*
 * Structure to define the state table handling functions for use by an EMM.
 */

typedef struct cssm_state_funcs
{
    CSSM_RETURN (CSSMAPI *cssm_GetAttachFunctions)
                                                (CSSM_MODULE_HANDLE hAddIn,
                                                 CSSM_SERVICE_MASK AddinType,
                                                 void **CallBack,
                                                 CSSM_GUID_PTR Guid);

    void (CSSMAPI * cssm_ReleaseAttachFunctions)
                                              (CSSM_MODULE_HANDLE hAddIn);

    CSSM_RETURN (CSSMAPI * cssm_GetAppMemoryFunctions)
                                            (CSSM_MODULE_HANDLE hAddIn,
                                             CSSM_UPCALLS_PTR UpcallTable);

    CSSM_RETURN (CSSMAPI * cssm_IsFuncCallValid)
                                           (CSSM_MODULE_HANDLE hAddin,
                                            CSSM_PROC_ADDR SrcAddress, /* application */
                                            CSSM_PROC_ADDR DestAddress,
                                            CSSM_PRIVILEGE InPriv,
                                            CSSM_PRIVILEGE *OutPriv,
                                            CSSM_BITMASK Hints,
                                            CSSM_BOOL *IsOK);

    CSSM_RETURN (CSSMAPI * cssm_DeregisterManagerServices)
                                                    (const CSSM_GUID *GUID);

    CSSM_RETURN (CSSMAPI * cssm_DeliverModuleManagerEvent)
                    (const CSSM_MANAGER_EVENT_NOTIFICATION *EventDescription);

} CSSM_STATE_FUNCS, *CSSM_STATE_FUNCS_PTR;



/*
 * This structure defines the function prototypes that an elective module manager
 * must implement to be dynamically loaded by CSSM.
 */
typedef struct cssm_manager_registration_info {
    /* loading, unloading, dispatch table, and event notification */ 
    CSSM_RETURN (CSSMAPI *Initialize) (uint32 VerMajor, uint32 VerMinor);
    CSSM_RETURN (CSSMAPI *Terminate) (void);
    CSSM_RETURN (CSSMAPI *RegisterDispatchTable)
                    (CSSM_STATE_FUNCS_PTR CssmStateCallTable);
    CSSM_RETURN (CSSMAPI *DeregisterDispatchTable) (void);
    CSSM_RETURN (CSSMAPI *EventNotifyManager)
                    (const CSSM_MANAGER_EVENT_NOTIFICATION *EventDescription);
    CSSM_RETURN (CSSMAPI *RefreshFunctionTable)
                    (CSSM_FUNC_NAME_ADDR_PTR FuncNameAddrPtr, 
                     uint32 NumOfFuncNameAddr);
} CSSM_MANAGER_REGISTRATION_INFO, *CSSM_MANAGER_REGISTRATION_INFO_PTR; 



#ifdef __cplusplus
extern "C" {
#endif

CSSM_RETURN CSSMAPI
ModuleManagerAuthenticate(CSSM_KEY_HIERARCHY KeyHierarchy,
                          const CSSM_GUID *CssmGuid,
                          const CSSM_GUID *AppGuid,
                          CSSM_MANAGER_REGISTRATION_INFO_PTR FunctionTable);

#ifdef __cplusplus
}
#endif


#endif
