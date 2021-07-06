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
 * @(#)$RCSfile: cssmdli.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:10 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMDLI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _CSSMDLI_H
#define _CSSMDLI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for the DL SPI functions */
#define CSSMDLI CSSMAPI

/* Define a function pointer type for each SPI function. The pointer types 
 * are named _CSSM_DLSPI_XXX_PTR, where XXX is the value of the SPI.
 */
typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DbOpen_PTR)(
                        CSSM_DL_HANDLE DLHandle,
                        const char *DbName,
                        const CSSM_NET_ADDRESS *DbLocation,
                        CSSM_DB_ACCESS_TYPE AccessRequest,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const void *OpenParameters,
                        CSSM_DB_HANDLE *DbHandle );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DbClose_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DbCreate_PTR)(
                        CSSM_DL_HANDLE DLHandle,
                        const char *DbName,
                        const CSSM_NET_ADDRESS *DbLocation,
                        const CSSM_DBINFO *DBInfo,
                        CSSM_DB_ACCESS_TYPE AccessRequest,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                        const void *OpenParameters,
                        CSSM_DB_HANDLE *DbHandle );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DbDelete_PTR)(
                        CSSM_DL_HANDLE DLHandle,
                        const char *DbName,
                        const CSSM_NET_ADDRESS *DbLocation,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_Authenticate_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_ACCESS_TYPE AccessRequest,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_GetDbAcl_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        const CSSM_STRING *SelectionTag,
                        uint32 *NumberOfAclInfos,
                        CSSM_ACL_ENTRY_INFO_PTR *AclInfos );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_ChangeDbAcl_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_ACL_EDIT *AclEdit );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_GetDbOwner_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_ACL_OWNER_PROTOTYPE_PTR Owner );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_ChangeDbOwner_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_ACL_OWNER_PROTOTYPE *NewOwner );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_GetDbNames_PTR)(
                        CSSM_DL_HANDLE DLHandle,
                        CSSM_NAME_LIST_PTR *NameList );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_GetDbNameFromHandle_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        char ** DbName );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_FreeNameList_PTR)(
                        CSSM_DL_HANDLE DLHandle,
                        CSSM_NAME_LIST_PTR NameList );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataInsert_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_RECORDTYPE RecordType,
                        const CSSM_DB_RECORD_ATTRIBUTE_DATA *Attributes,
                        const CSSM_DATA *Data,
                        CSSM_DB_UNIQUE_RECORD_PTR *UniqueId );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataDelete_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        const CSSM_DB_UNIQUE_RECORD *UniqueRecordIdentifier );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataModify_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_RECORDTYPE RecordType,
                        CSSM_DB_UNIQUE_RECORD_PTR UniqueRecordIdentifier,
                        const CSSM_DB_RECORD_ATTRIBUTE_DATA *AttributesToBeModified,
                        const CSSM_DATA *DataToBeModified,
                        CSSM_DB_MODIFY_MODE ModifyMode );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataGetFirst_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        const CSSM_QUERY *Query,
                        CSSM_HANDLE_PTR ResultsHandle,
                        CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                        CSSM_DATA_PTR Data,
                        CSSM_DB_UNIQUE_RECORD_PTR *UniqueId );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataGetNext_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_HANDLE ResultsHandle,
                        CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                        CSSM_DATA_PTR Data,
                        CSSM_DB_UNIQUE_RECORD_PTR *UniqueId );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataAbortQuery_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_HANDLE ResultsHandle );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DataGetFromUniqueRecordId_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord,
                        CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                        CSSM_DATA_PTR Data );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_FreeUniqueRecord_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_CreateRelation_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_RECORDTYPE RelationID,
                        const char *RelationName,
                        uint32 NumberOfAttributes,
                        const CSSM_DB_SCHEMA_ATTRIBUTE_INFO *pAttributeInfo,
                        uint32 NumberOfIndexes,
                        const CSSM_DB_SCHEMA_INDEX_INFO *pIndexInfo );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_DestroyRelation_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_RECORDTYPE RelationID );

typedef CSSM_RETURN (CSSMDLI *_CSSM_DLSPI_PassThrough_PTR)(
                        CSSM_DL_DB_HANDLE DLDBHandle,
                        uint32 PassThroughId,
                        const void *InputParams,
                        void **OutputParams );


/* Define a function pointer interface table for the SPI.
 */
typedef struct cssm_spi_dl_funcs {
    _CSSM_DLSPI_DbOpen_PTR                        DbOpen;
    _CSSM_DLSPI_DbClose_PTR                       DbClose;
    _CSSM_DLSPI_DbCreate_PTR                      DbCreate;
    _CSSM_DLSPI_DbDelete_PTR                      DbDelete;
    _CSSM_DLSPI_Authenticate_PTR                  Authenticate;
    _CSSM_DLSPI_GetDbAcl_PTR                      GetDbAcl;
    _CSSM_DLSPI_ChangeDbAcl_PTR                   ChangeDbAcl;
    _CSSM_DLSPI_GetDbOwner_PTR                    GetDbOwner;
    _CSSM_DLSPI_ChangeDbOwner_PTR                 ChangeDbOwner;
    _CSSM_DLSPI_GetDbNames_PTR                    GetDbNames;
    _CSSM_DLSPI_GetDbNameFromHandle_PTR           GetDbNameFromHandle;
    _CSSM_DLSPI_FreeNameList_PTR                  FreeNameList;
    _CSSM_DLSPI_DataInsert_PTR                    DataInsert;
    _CSSM_DLSPI_DataDelete_PTR                    DataDelete;
    _CSSM_DLSPI_DataModify_PTR                    DataModify;
    _CSSM_DLSPI_DataGetFirst_PTR                  DataGetFirst;
    _CSSM_DLSPI_DataGetNext_PTR                   DataGetNext;
    _CSSM_DLSPI_DataAbortQuery_PTR                DataAbortQuery;
    _CSSM_DLSPI_DataGetFromUniqueRecordId_PTR     DataGetFromUniqueRecordId;
    _CSSM_DLSPI_FreeUniqueRecord_PTR              FreeUniqueRecord;
    _CSSM_DLSPI_CreateRelation_PTR                CreateRelation;
    _CSSM_DLSPI_DestroyRelation_PTR               DestroyRelation;
    _CSSM_DLSPI_PassThrough_PTR                   PassThrough;
} CSSM_SPI_DL_FUNCS, *CSSM_SPI_DL_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CSSMDLI_H */
