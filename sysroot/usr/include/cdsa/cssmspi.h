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
 * @(#)$RCSfile: cssmspi.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:16 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMSPI.H
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

#ifndef _CSSMSPI_H
#define _CSSMSPI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention definition for the generic SPI functions */
#define CSSMSPI CSSMAPI

/* Basic function table structure found at the start of each function table
 * registered with the CSSM.
 */
typedef struct cssm_module_funcs {
    CSSM_SERVICE_TYPE ServiceType;
    uint32 NumberOfServiceFuncs;
    const CSSM_PROC_ADDR *ServiceFuncs;
} CSSM_MODULE_FUNCS, *CSSM_MODULE_FUNCS_PTR;

/* Used by addins to trigger events of type CSSM_MODULE_EVENT to the
 * application, possibly asynchronously. The callback that the application
 * registered during CSSM_ModuleLoad will be called by the CSSM.
 */
typedef CSSM_RETURN (CSSMAPI *CSSM_SPI_ModuleEventHandler) (
                            const CSSM_GUID *ModuleGuid,
                            void* CssmNotifyCallbackCtx,
                            uint32 SubserviceID,
                            CSSM_SERVICE_TYPE ServiceType,
                            CSSM_MODULE_EVENT EventType );

/* Function pointers to the basic SPI interfaces defined by the CDSA
 * Add-in Module Structure & Administration Specification.
 * *** Not part of the specification ***
 */
typedef CSSM_RETURN (CSSMSPI *_CSSM_SPI_ModuleLoad_PTR)(
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleGuid,
                        CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
                        void* CssmNotifyCallbackCtx );

typedef CSSM_RETURN (CSSMSPI *_CSSM_SPI_ModuleUnload_PTR)(
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleGuid,
                        CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
                        void* CssmNotifyCallbackCtx );

typedef CSSM_RETURN (CSSMSPI *_CSSM_SPI_ModuleAttach_PTR)(
                        const CSSM_GUID *ModuleGuid,
                        const CSSM_VERSION *Version,
                        uint32 SubserviceID,
                        CSSM_SERVICE_TYPE SubServiceType,
                        CSSM_ATTACH_FLAGS AttachFlags,
                        CSSM_MODULE_HANDLE ModuleHandle,
                        CSSM_KEY_HIERARCHY KeyHierarchy,
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleManagerGuid,
                        const CSSM_GUID *CallerGuid,
                        const CSSM_UPCALLS *Upcalls,
                        CSSM_MODULE_FUNCS_PTR *FuncTbl );

typedef CSSM_RETURN (CSSMSPI *_CSSM_SPI_ModuleDetach_PTR)(
                        CSSM_MODULE_HANDLE ModuleHandle );



/* Function prototypes for the basic SPI interfaces defined by the CDSA
 * Add-in Module Structure & Administration Specification.
 */
CSSM_RETURN CSSMSPI CSSM_SPI_ModuleLoad(
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleGuid,
                        CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
                        void* CssmNotifyCallbackCtx );

CSSM_RETURN CSSMSPI CSSM_SPI_ModuleUnload(
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleGuid,
                        CSSM_SPI_ModuleEventHandler CssmNotifyCallback,
                        void* CssmNotifyCallbackCtx );

CSSM_RETURN CSSMSPI CSSM_SPI_ModuleAttach(
                        const CSSM_GUID *ModuleGuid,
                        const CSSM_VERSION *Version,
                        uint32 SubserviceID,
                        CSSM_SERVICE_TYPE SubServiceType,
                        CSSM_ATTACH_FLAGS AttachFlags,
                        CSSM_MODULE_HANDLE ModuleHandle,
                        CSSM_KEY_HIERARCHY KeyHierarchy,
                        const CSSM_GUID *CssmGuid,
                        const CSSM_GUID *ModuleManagerGuid,
                        const CSSM_GUID *CallerGuid,
                        const CSSM_UPCALLS *Upcalls,
                        CSSM_MODULE_FUNCS_PTR *FuncTbl );

CSSM_RETURN CSSMSPI CSSM_SPI_ModuleDetach(
                        CSSM_MODULE_HANDLE ModuleHandle );


#ifdef __cplusplus
}
#endif

#endif
