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
 * @(#)$RCSfile: cssmcspi.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:09 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMCSPI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _CSSMCSPI_H
#define _CSSMCSPI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for CSPI functions */
#define CSSMCSPI CSSMAPI

/* Define a function pointer type for each SPI function. The pointer types 
 * are named _CSSM_CSPSPI_XXX_PTR, where XXX is the value of the SPI.
 */
typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_EventNotify_PTR)(
                        CSSM_MODULE_HANDLE CSPHandle,
                        CSSM_CONTEXT_EVENT Event,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT* Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_QuerySize_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        CSSM_BOOL Encrypt,
                        uint32 QuerySizeCount,
                        CSSM_QUERY_SIZE_DATA_PTR DataBlock );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_SignData_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount,
                        CSSM_ALGORITHMS DigestAlgorithm,
                        CSSM_DATA_PTR Signature );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_SignDataInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_SignDataUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_SignDataFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_DATA_PTR Signature );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyData_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount,
                        CSSM_ALGORITHMS DigestAlgorithm,
                        const CSSM_DATA *Signature );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyDataInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyDataUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyDataFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *Signature );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DigestData_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount,
                        CSSM_DATA_PTR Digest );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DigestDataInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DigestDataUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DigestDataClone_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_CC_HANDLE ClonednewCCHandle );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DigestDataFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_DATA_PTR Digest );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateMac_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount,
                        CSSM_DATA_PTR Mac );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateMacInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateMacUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateMacFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_DATA_PTR Mac );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyMac_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount,
                        const CSSM_DATA *Mac );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyMacInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyMacUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyMacFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *Mac );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_EncryptData_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *ClearBufs,
                        uint32 ClearBufCount,
                        CSSM_DATA_PTR CipherBufs,
                        uint32 CipherBufCount,
                        uint32 *bytesEncrypted,
                        CSSM_DATA_PTR RemData,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_EncryptDataInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_EncryptDataUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *ClearBufs,
                        uint32 ClearBufCount,
                        CSSM_DATA_PTR CipherBufs,
                        uint32 CipherBufCount,
                        uint32 *bytesEncrypted );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_EncryptDataFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_DATA_PTR RemData );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DecryptData_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_DATA *CipherBufs,
                        uint32 CipherBufCount,
                        CSSM_DATA_PTR ClearBufs,
                        uint32 ClearBufCount,
                        uint32 *bytesDecrypted,
                        CSSM_DATA_PTR RemData,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DecryptDataInit_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DecryptDataUpdate_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CipherBufs,
                        uint32 CipherBufCount,
                        CSSM_DATA_PTR ClearBufs,
                        uint32 ClearBufCount,
                        uint32 *bytesDecrypted );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DecryptDataFinal_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        CSSM_DATA_PTR RemData );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_QueryKeySizeInBits_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT * Context,
                        const CSSM_KEY *Key,
                        CSSM_KEY_SIZE_PTR KeySize );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        uint32 KeyUsage,
                        uint32 KeyAttr,
                        const CSSM_DATA *KeyLabel,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                        CSSM_KEY_PTR Key,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateKeyPair_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        uint32 PublicKeyUsage,
                        uint32 PublicKeyAttr,
                        const CSSM_DATA *PublicKeyLabel,
                        CSSM_KEY_PTR PublicKey,
                        uint32 PrivateKeyUsage,
                        uint32 PrivateKeyAttr,
                        const CSSM_DATA *PrivateKeyLabel,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                        CSSM_KEY_PTR PrivateKey,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateRandom_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        CSSM_DATA_PTR RandomNumber );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GenerateAlgorithmParams_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        uint32 ParamBits,
                        CSSM_DATA_PTR Param,
                        uint32* NumberOfUpdatedAttributes,
                        CSSM_CONTEXT_ATTRIBUTE_PTR* UpdatedAttributes );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_WrapKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_ACCESS_CREDENTIALS *Credentials,
                        const CSSM_KEY *Key,
                        const CSSM_DATA *DescriptiveData,
                        CSSM_WRAP_KEY_PTR WrappedKey,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_UnwrapKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        const CSSM_KEY *PublicKey,
                        const CSSM_WRAP_KEY *WrappedKey,
                        uint32 KeyUsage,
                        uint32 KeyAttr,
                        const CSSM_DATA *KeyLabel,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                        CSSM_KEY_PTR UnwrappedKey,
                        CSSM_DATA_PTR DescriptiveData,
                        CSSM_PRIVILEGE Privilege );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_DeriveKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        CSSM_DATA_PTR Param,
                        uint32 KeyUsage,
                        uint32 KeyAttr,
                        const CSSM_DATA *KeyLabel,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                        CSSM_KEY_PTR DerivedKey );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_FreeKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        CSSM_KEY_PTR KeyPtr,
                        CSSM_BOOL Delete );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_PassThrough_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CONTEXT *Context,
                        uint32 PassThroughId,
                        const void *InData,
                        void **OutData );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_Login_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_DATA *LoginName,
                        const void *Reserved );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_Logout_PTR)(
                        CSSM_CSP_HANDLE CSPHandle );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_ChangeLoginAcl_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_ACL_EDIT *AclEdit );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_ObtainPrivateKeyFromPublicKey_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_KEY *PublicKey,
                        CSSM_KEY_PTR PrivateKey );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_RetrieveUniqueId_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_DATA_PTR UniqueID );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_RetrieveCounter_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_DATA_PTR Counter );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_VerifyDevice_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_DATA *DeviceCert );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetTimeValue_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_ALGORITHMS TimeAlgorithm,
                        CSSM_DATA *TimeData );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetOperationalStatistics_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_CSP_OPERATIONAL_STATISTICS *Statistics );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetLoginAcl_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_STRING *SelectionTag,
                        uint32 *NumberOfAclInfos,
                        CSSM_ACL_ENTRY_INFO_PTR *AclInfos );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetKeyAcl_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_KEY *Key,
                        const CSSM_STRING *SelectionTag,
                        uint32 *NumberOfAclInfos,
                        CSSM_ACL_ENTRY_INFO_PTR *AclInfos );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_ChangeKeyAcl_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_ACL_EDIT *AclEdit,
                        const CSSM_KEY *Key );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetKeyOwner_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_KEY *Key,
                        CSSM_ACL_OWNER_PROTOTYPE_PTR Owner );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_ChangeKeyOwner_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_KEY *Key,
                        const CSSM_ACL_OWNER_PROTOTYPE *NewOwner );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_GetLoginOwner_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        CSSM_ACL_OWNER_PROTOTYPE_PTR Owner );

typedef CSSM_RETURN (CSSMCSPI *_CSSM_CSPSPI_ChangeLoginOwner_PTR)(
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ACCESS_CREDENTIALS *AccessCred,
                        const CSSM_ACL_OWNER_PROTOTYPE *NewOwner );


/* Define a function pointer interface table for the SPI.
 */
typedef struct cssm_spi_csp_funcs {
    _CSSM_CSPSPI_EventNotify_PTR                  EventNotify;
    _CSSM_CSPSPI_QuerySize_PTR                    QuerySize;
    _CSSM_CSPSPI_SignData_PTR                     SignData;
    _CSSM_CSPSPI_SignDataInit_PTR                 SignDataInit;
    _CSSM_CSPSPI_SignDataUpdate_PTR               SignDataUpdate;
    _CSSM_CSPSPI_SignDataFinal_PTR                SignDataFinal;
    _CSSM_CSPSPI_VerifyData_PTR                   VerifyData;
    _CSSM_CSPSPI_VerifyDataInit_PTR               VerifyDataInit;
    _CSSM_CSPSPI_VerifyDataUpdate_PTR             VerifyDataUpdate;
    _CSSM_CSPSPI_VerifyDataFinal_PTR              VerifyDataFinal;
    _CSSM_CSPSPI_DigestData_PTR                   DigestData;
    _CSSM_CSPSPI_DigestDataInit_PTR               DigestDataInit;
    _CSSM_CSPSPI_DigestDataUpdate_PTR             DigestDataUpdate;
    _CSSM_CSPSPI_DigestDataClone_PTR              DigestDataClone;
    _CSSM_CSPSPI_DigestDataFinal_PTR              DigestDataFinal;
    _CSSM_CSPSPI_GenerateMac_PTR                  GenerateMac;
    _CSSM_CSPSPI_GenerateMacInit_PTR              GenerateMacInit;
    _CSSM_CSPSPI_GenerateMacUpdate_PTR            GenerateMacUpdate;
    _CSSM_CSPSPI_GenerateMacFinal_PTR             GenerateMacFinal;
    _CSSM_CSPSPI_VerifyMac_PTR                    VerifyMac;
    _CSSM_CSPSPI_VerifyMacInit_PTR                VerifyMacInit;
    _CSSM_CSPSPI_VerifyMacUpdate_PTR              VerifyMacUpdate;
    _CSSM_CSPSPI_VerifyMacFinal_PTR               VerifyMacFinal;
    _CSSM_CSPSPI_EncryptData_PTR                  EncryptData;
    _CSSM_CSPSPI_EncryptDataInit_PTR              EncryptDataInit;
    _CSSM_CSPSPI_EncryptDataUpdate_PTR            EncryptDataUpdate;
    _CSSM_CSPSPI_EncryptDataFinal_PTR             EncryptDataFinal;
    _CSSM_CSPSPI_DecryptData_PTR                  DecryptData;
    _CSSM_CSPSPI_DecryptDataInit_PTR              DecryptDataInit;
    _CSSM_CSPSPI_DecryptDataUpdate_PTR            DecryptDataUpdate;
    _CSSM_CSPSPI_DecryptDataFinal_PTR             DecryptDataFinal;
    _CSSM_CSPSPI_QueryKeySizeInBits_PTR           QueryKeySizeInBits;
    _CSSM_CSPSPI_GenerateKey_PTR                  GenerateKey;
    _CSSM_CSPSPI_GenerateKeyPair_PTR              GenerateKeyPair;
    _CSSM_CSPSPI_GenerateRandom_PTR               GenerateRandom;
    _CSSM_CSPSPI_GenerateAlgorithmParams_PTR      GenerateAlgorithmParams;
    _CSSM_CSPSPI_WrapKey_PTR                      WrapKey;
    _CSSM_CSPSPI_UnwrapKey_PTR                    UnwrapKey;
    _CSSM_CSPSPI_DeriveKey_PTR                    DeriveKey;
    _CSSM_CSPSPI_FreeKey_PTR                      FreeKey;
    _CSSM_CSPSPI_PassThrough_PTR                  PassThrough;
    _CSSM_CSPSPI_Login_PTR                        Login;
    _CSSM_CSPSPI_Logout_PTR                       Logout;
    _CSSM_CSPSPI_ChangeLoginAcl_PTR               ChangeLoginAcl;
    _CSSM_CSPSPI_ObtainPrivateKeyFromPublicKey_PTR    ObtainPrivateKeyFromPublicKey;
    _CSSM_CSPSPI_RetrieveUniqueId_PTR             RetrieveUniqueId;
    _CSSM_CSPSPI_RetrieveCounter_PTR              RetrieveCounter;
    _CSSM_CSPSPI_VerifyDevice_PTR                 VerifyDevice;
    _CSSM_CSPSPI_GetTimeValue_PTR                 GetTimeValue;
    _CSSM_CSPSPI_GetOperationalStatistics_PTR     GetOperationalStatistics;
    _CSSM_CSPSPI_GetLoginAcl_PTR                  GetLoginAcl;
    _CSSM_CSPSPI_GetKeyAcl_PTR                    GetKeyAcl;
    _CSSM_CSPSPI_ChangeKeyAcl_PTR                 ChangeKeyAcl;
    _CSSM_CSPSPI_GetKeyOwner_PTR                  GetKeyOwner;
    _CSSM_CSPSPI_ChangeKeyOwner_PTR               ChangeKeyOwner;
    _CSSM_CSPSPI_GetLoginOwner_PTR                GetLoginOwner;
    _CSSM_CSPSPI_ChangeLoginOwner_PTR             ChangeLoginOwner;
} CSSM_SPI_CSP_FUNCS, *CSSM_SPI_CSP_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CSSMCSPI_H */
