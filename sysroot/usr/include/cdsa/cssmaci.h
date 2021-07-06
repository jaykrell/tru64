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
 * @(#)$RCSfile: cssmaci.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:04 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMACI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _CSSMACI_H
#define _CSSMACI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for AC SPIs */
#define CSSMACI CSSMAPI 

/* Defining a function pointer type for each SPI function. The pointer types 
 * are named _CSSM_ACSPI_XXX_PTR, where XXX is the name of the SPI.
 */
typedef CSSM_RETURN (CSSMACI *_CSSM_ACSPI_AuthCompute_PTR )(
                        CSSM_AC_HANDLE ACHandle,
                        const CSSM_TUPLEGROUP *BaseAuthorizations,
                        const CSSM_TUPLEGROUP *Credentials,
                        uint32 NumberOfRequestors,
                        const CSSM_LIST *Requestors,
                        const CSSM_LIST *RequestedAuthorizationPeriod,
                        const CSSM_LIST *RequestedAuthorization,
                        CSSM_TUPLEGROUP_PTR AuthorizationResult );

typedef CSSM_RETURN (CSSMACI *_CSSM_ACSPI_PassThrough_PTR )(
                        CSSM_AC_HANDLE ACHandle,
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DL_DB_LIST *DBList,
                        uint32 PassThroughId,
                        const void *InputParams,
                        void **OutputParams );


/* Defining a function pointer interface table for the SPI.
 */
typedef struct cssm_spi_ac_funcs {
    _CSSM_ACSPI_AuthCompute_PTR     AuthCompute;
    _CSSM_ACSPI_PassThrough_PTR     PassThrough;
} CSSM_SPI_AC_FUNCS, *CSSM_SPI_AC_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CSSMACI_H */
