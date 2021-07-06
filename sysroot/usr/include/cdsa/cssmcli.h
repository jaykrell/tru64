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
 * @(#)$RCSfile: cssmcli.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:08 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMCLI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _CSSMCLI_H
#define _CSSMCLI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for CL SPIs */
#define CSSMCLI CSSMAPI

/* Define a function pointer type for each SPI function. The pointer types 
 * are named _CSSM_CLSPI_XXX_PTR, where XXX is the value of the SPI.
 */
typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertCreateTemplate_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CertFields,
                        CSSM_DATA_PTR CertTemplate );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetAllTemplateFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *CertTemplate,
                        uint32 *NumberOfFields,
                        CSSM_FIELD_PTR *CertFields );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertSign_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CertTemplate,
                        const CSSM_FIELD *SignScope,
                        uint32 ScopeSize,
                        CSSM_DATA_PTR SignedCert );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertVerify_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CertToBeVerified,
                        const CSSM_DATA *SignerCert,
                        const CSSM_FIELD *VerifyScope,
                        uint32 ScopeSize );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertVerifyWithKey_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CertToBeVerified );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetFirstFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        const CSSM_OID *CertField,
                        CSSM_HANDLE_PTR ResultsHandle,
                        uint32 *NumberOfMatchedFields,
                        CSSM_DATA_PTR *Value );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetNextFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle,
                        CSSM_DATA_PTR *Value );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertAbortQuery_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetKeyInfo_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        CSSM_KEY_PTR *Key );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetAllFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        uint32 *NumberOfFields,
                        CSSM_FIELD_PTR *FieldList );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_FreeFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        CSSM_FIELD_PTR FieldArray );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_FreeFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_OID *CertOrCrlOid,
                        CSSM_DATA_PTR Value );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertCache_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        CSSM_HANDLE_PTR CertHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetFirstCachedFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CertHandle,
                        const CSSM_OID *CertField,
                        CSSM_HANDLE_PTR ResultsHandle,
                        uint32 *NumberOfMatchedFields,
                        CSSM_DATA_PTR *FieldValue );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGetNextCachedFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle,
                        CSSM_DATA_PTR *FieldValue );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertAbortCache_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CertHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGroupToSignedBundle_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CERTGROUP *CertGroupToBundle,
                        const CSSM_CERT_BUNDLE_HEADER *BundleInfo,
                        CSSM_DATA_PTR SignedBundle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertGroupFromVerifiedBundle_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_CERT_BUNDLE *CertBundle,
                        const CSSM_DATA *SignerCert,
                        CSSM_CERTGROUP_PTR *CertGroup );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CertDescribeFormat_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 *NumberOfOids,
                        CSSM_OID_PTR *OidList );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlCreateTemplate_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CrlTemplate,
                        CSSM_DATA_PTR NewCrl );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlSetFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CrlTemplate,
                        const CSSM_DATA *OldCrl,
                        CSSM_DATA_PTR ModifiedCrl );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlAddCert_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *Cert,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CrlEntryFields,
                        const CSSM_DATA *OldCrl,
                        CSSM_DATA_PTR NewCrl );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlRemoveCert_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        const CSSM_DATA *OldCrl,
                        CSSM_DATA_PTR NewCrl );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlSign_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *UnsignedCrl,
                        const CSSM_FIELD *SignScope,
                        uint32 ScopeSize,
                        CSSM_DATA_PTR SignedCrl );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlVerify_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CrlToBeVerified,
                        const CSSM_DATA *SignerCert,
                        const CSSM_FIELD *VerifyScope,
                        uint32 ScopeSize );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlVerifyWithKey_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CrlToBeVerified );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_IsCertInCrl_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        const CSSM_DATA *Crl,
                        CSSM_BOOL *CertFound );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetFirstFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Crl,
                        const CSSM_OID *CrlField,
                        CSSM_HANDLE_PTR ResultsHandle,
                        uint32 *NumberOfMatchedFields,
                        CSSM_DATA_PTR *Value );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetNextFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle,
                        CSSM_DATA_PTR *Value );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlAbortQuery_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetAllFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Crl,
                        uint32 *NumberOfCrlFields,
                        CSSM_FIELD_PTR *CrlFields );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlCache_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Crl,
                        CSSM_HANDLE_PTR CrlHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_IsCertInCachedCrl_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        CSSM_HANDLE CrlHandle,
                        CSSM_BOOL *CertFound,
                        CSSM_DATA_PTR CrlRecordIndex );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetFirstCachedFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CrlHandle,
                        const CSSM_DATA *CrlRecordIndex,
                        const CSSM_OID *CrlField,
                        CSSM_HANDLE_PTR ResultsHandle,
                        uint32 *NumberOfMatchedFields,
                        CSSM_DATA_PTR *FieldValue );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetNextCachedFieldValue_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle,
                        CSSM_DATA_PTR *FieldValue );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlGetAllCachedRecordFields_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CrlHandle,
                        const CSSM_DATA *CrlRecordIndex,
                        uint32 *NumberOfFields,
                        CSSM_FIELD_PTR *Fields );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlAbortCache_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CrlHandle );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_CrlDescribeFormat_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        uint32 *NumberOfOids,
                        CSSM_OID_PTR *OidList );

typedef CSSM_RETURN (CSSMCLI *_CSSM_CLSPI_PassThrough_PTR)(
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        uint32 PassThroughId,
                        const void *InputParams,
                        void **OutputParams );


/* Define a function pointer interface table for the SPI.
 */
typedef struct cssm_spi_cl_funcs {
    _CSSM_CLSPI_CertCreateTemplate_PTR            CertCreateTemplate;
    _CSSM_CLSPI_CertGetAllTemplateFields_PTR      CertGetAllTemplateFields;
    _CSSM_CLSPI_CertSign_PTR                      CertSign;
    _CSSM_CLSPI_CertVerify_PTR                    CertVerify;
    _CSSM_CLSPI_CertVerifyWithKey_PTR             CertVerifyWithKey;
    _CSSM_CLSPI_CertGetFirstFieldValue_PTR        CertGetFirstFieldValue;
    _CSSM_CLSPI_CertGetNextFieldValue_PTR         CertGetNextFieldValue;
    _CSSM_CLSPI_CertAbortQuery_PTR                CertAbortQuery;
    _CSSM_CLSPI_CertGetKeyInfo_PTR                CertGetKeyInfo;
    _CSSM_CLSPI_CertGetAllFields_PTR              CertGetAllFields;
    _CSSM_CLSPI_FreeFields_PTR                    FreeFields;
    _CSSM_CLSPI_FreeFieldValue_PTR                FreeFieldValue;
    _CSSM_CLSPI_CertCache_PTR                     CertCache;
    _CSSM_CLSPI_CertGetFirstCachedFieldValue_PTR  CertGetFirstCachedFieldValue;
    _CSSM_CLSPI_CertGetNextCachedFieldValue_PTR   CertGetNextCachedFieldValue;
    _CSSM_CLSPI_CertAbortCache_PTR                CertAbortCache;
    _CSSM_CLSPI_CertGroupToSignedBundle_PTR       CertGroupToSignedBundle;
    _CSSM_CLSPI_CertGroupFromVerifiedBundle_PTR   CertGroupFromVerifiedBundle;
    _CSSM_CLSPI_CertDescribeFormat_PTR            CertDescribeFormat;
    _CSSM_CLSPI_CrlCreateTemplate_PTR             CrlCreateTemplate;
    _CSSM_CLSPI_CrlSetFields_PTR                  CrlSetFields;
    _CSSM_CLSPI_CrlAddCert_PTR                    CrlAddCert;
    _CSSM_CLSPI_CrlRemoveCert_PTR                 CrlRemoveCert;
    _CSSM_CLSPI_CrlSign_PTR                       CrlSign;
    _CSSM_CLSPI_CrlVerify_PTR                     CrlVerify;
    _CSSM_CLSPI_CrlVerifyWithKey_PTR              CrlVerifyWithKey;
    _CSSM_CLSPI_IsCertInCrl_PTR                   IsCertInCrl;
    _CSSM_CLSPI_CrlGetFirstFieldValue_PTR         CrlGetFirstFieldValue;
    _CSSM_CLSPI_CrlGetNextFieldValue_PTR          CrlGetNextFieldValue;
    _CSSM_CLSPI_CrlAbortQuery_PTR                 CrlAbortQuery;
    _CSSM_CLSPI_CrlGetAllFields_PTR               CrlGetAllFields;
    _CSSM_CLSPI_CrlCache_PTR                      CrlCache;
    _CSSM_CLSPI_IsCertInCachedCrl_PTR             IsCertInCachedCrl;
    _CSSM_CLSPI_CrlGetFirstCachedFieldValue_PTR   CrlGetFirstCachedFieldValue;
    _CSSM_CLSPI_CrlGetNextCachedFieldValue_PTR    CrlGetNextCachedFieldValue;
    _CSSM_CLSPI_CrlGetAllCachedRecordFields_PTR   CrlGetAllCachedRecordFields;
    _CSSM_CLSPI_CrlAbortCache_PTR                 CrlAbortCache;
    _CSSM_CLSPI_CrlDescribeFormat_PTR             CrlDescribeFormat;
    _CSSM_CLSPI_PassThrough_PTR                   PassThrough;
} CSSM_SPI_CL_FUNCS, *CSSM_SPI_CL_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CSSMCLI_H */
