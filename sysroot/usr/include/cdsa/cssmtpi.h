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
 * @(#)$RCSfile: cssmtpi.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:47:18 $
 */
/*-----------------------------------------------------------------------
 * File: CSSMTPI.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _CSSMTPI_H
#define _CSSMTPI_H    

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for TPI functions */
#define CSSMTPI CSSMAPI

/* Define a function pointer type for each SPI function. The pointer types 
 * are named _CSSM_TPSPI_XXX_PTR, where XXX is the value of the SPI.
 */
typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_SubmitCredRequest_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_TP_AUTHORITY_ID *PreferredAuthority,
                        CSSM_TP_AUTHORITY_REQUEST_TYPE RequestType,
                        const CSSM_TP_REQUEST_SET *RequestInput,
                        const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthContext,
                        sint32 *EstimatedTime,
                        CSSM_DATA_PTR ReferenceIdentifier );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_RetrieveCredResult_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_DATA *ReferenceIdentifier,
                        const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthCredentials,
                        sint32 *EstimatedTime,
                        CSSM_BOOL *ConfirmationRequired,
                        CSSM_TP_RESULT_SET_PTR *RetrieveOutput );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_ConfirmCredResult_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_DATA *ReferenceIdentifier,
                        const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthCredentials,
                        const CSSM_TP_CONFIRM_RESPONSE *Responses,
                        const CSSM_TP_AUTHORITY_ID *PreferredAuthority );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_ReceiveConfirmation_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_DATA *ReferenceIdentifier,
                        CSSM_TP_CONFIRM_RESPONSE_PTR *Responses,
                        sint32 *ElapsedTime );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertReclaimKey_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_CERTGROUP *CertGroup,
                        uint32 CertIndex,
                        CSSM_LONG_HANDLE KeyCacheHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertReclaimAbort_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_LONG_HANDLE KeyCacheHandle );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_FormRequest_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        const CSSM_TP_AUTHORITY_ID *PreferredAuthority,
                        CSSM_TP_FORM_TYPE FormType,
                        CSSM_DATA_PTR BlankForm );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_FormSubmit_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_TP_FORM_TYPE FormType,
                        const CSSM_DATA *Form,
                        const CSSM_TP_AUTHORITY_ID *ClearanceAuthority,
                        const CSSM_TP_AUTHORITY_ID *RepresentedAuthority,
                        CSSM_ACCESS_CREDENTIALS_PTR Credentials );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertGroupVerify_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_CERTGROUP *CertGroupToBeVerified,
                        const CSSM_TP_VERIFY_CONTEXT *VerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR VerifyContextResult );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertCreateTemplate_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CertFields,
                        CSSM_DATA_PTR CertTemplate );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertGetAllTemplateFields_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *CertTemplate,
                        uint32 *NumberOfFields,
                        CSSM_FIELD_PTR *CertFields );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertSign_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CertTemplateToBeSigned,
                        const CSSM_CERTGROUP *SignerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *SignerVerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR SignerVerifyResult,
                        CSSM_DATA_PTR SignedCert );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CrlVerify_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ENCODED_CRL *CrlToBeVerified,
                        const CSSM_CERTGROUP *SignerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *VerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CrlCreateTemplate_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        uint32 NumberOfFields,
                        const CSSM_FIELD *CrlFields,
                        CSSM_DATA_PTR NewCrlTemplate );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertRevoke_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_DATA *OldCrlTemplate,
                        const CSSM_CERTGROUP *CertGroupToBeRevoked,
                        const CSSM_CERTGROUP *RevokerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *RevokerVerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult,
                        CSSM_TP_CERTCHANGE_REASON Reason,
                        CSSM_DATA_PTR NewCrlTemplate );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertRemoveFromCrlTemplate_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_DATA *OldCrlTemplate,
                        const CSSM_CERTGROUP *CertGroupToBeRemoved,
                        const CSSM_CERTGROUP *RevokerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *RevokerVerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult,
                        CSSM_DATA_PTR NewCrlTemplate );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CrlSign_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_ENCODED_CRL *CrlToBeSigned,
                        const CSSM_CERTGROUP *SignerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *SignerVerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR SignerVerifyResult,
                        CSSM_DATA_PTR SignedCrl );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_ApplyCrlToDb_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_ENCODED_CRL *CrlToBeApplied,
                        const CSSM_CERTGROUP *SignerCertGroup,
                        const CSSM_TP_VERIFY_CONTEXT *ApplyCrlVerifyContext,
                        CSSM_TP_VERIFY_CONTEXT_RESULT_PTR ApplyCrlVerifyResult );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertGroupConstruct_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_DL_DB_LIST *DBList,
                        const void *ConstructParams,
                        const CSSM_CERTGROUP *CertGroupFrag,
                        CSSM_CERTGROUP_PTR *CertGroup );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertGroupPrune_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DL_DB_LIST *DBList,
                        const CSSM_CERTGROUP *OrderedCertGroup,
                        CSSM_CERTGROUP_PTR *PrunedCertGroup );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_CertGroupToTupleGroup_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_CERTGROUP *CertGroup,
                        CSSM_TUPLEGROUP_PTR *TupleGroup );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_TupleGroupToCertGroup_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_TUPLEGROUP *TupleGroup,
                        CSSM_CERTGROUP_PTR *CertTemplates );

typedef CSSM_RETURN (CSSMTPI *_CSSM_TPSPI_PassThrough_PTR)(
                        CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        CSSM_CC_HANDLE CCHandle,
                        const CSSM_DL_DB_LIST *DBList,
                        uint32 PassThroughId,
                        const void *InputParams,
                        void **OutputParams );


/* Define a function pointer interface table for the SPI.
 */
typedef struct cssm_spi_tp_funcs {
    _CSSM_TPSPI_SubmitCredRequest_PTR       SubmitCredRequest;
    _CSSM_TPSPI_RetrieveCredResult_PTR      RetrieveCredResult;
    _CSSM_TPSPI_ConfirmCredResult_PTR       ConfirmCredResult;
    _CSSM_TPSPI_ReceiveConfirmation_PTR     ReceiveConfirmation;
    _CSSM_TPSPI_CertReclaimKey_PTR          CertReclaimKey;
    _CSSM_TPSPI_CertReclaimAbort_PTR        CertReclaimAbort;
    _CSSM_TPSPI_FormRequest_PTR             FormRequest;
    _CSSM_TPSPI_FormSubmit_PTR              FormSubmit;
    _CSSM_TPSPI_CertGroupVerify_PTR         CertGroupVerify;
    _CSSM_TPSPI_CertCreateTemplate_PTR      CertCreateTemplate;
    _CSSM_TPSPI_CertGetAllTemplateFields_PTR    CertGetAllTemplateFields;
    _CSSM_TPSPI_CertSign_PTR                CertSign;
    _CSSM_TPSPI_CrlVerify_PTR               CrlVerify;
    _CSSM_TPSPI_CrlCreateTemplate_PTR       CrlCreateTemplate;
    _CSSM_TPSPI_CertRevoke_PTR              CertRevoke;
    _CSSM_TPSPI_CertRemoveFromCrlTemplate_PTR    CertRemoveFromCrlTemplate;
    _CSSM_TPSPI_CrlSign_PTR                 CrlSign;
    _CSSM_TPSPI_ApplyCrlToDb_PTR            ApplyCrlToDb;
    _CSSM_TPSPI_CertGroupConstruct_PTR      CertGroupConstruct;
    _CSSM_TPSPI_CertGroupPrune_PTR          CertGroupPrune;
    _CSSM_TPSPI_CertGroupToTupleGroup_PTR   CertGroupToTupleGroup;
    _CSSM_TPSPI_TupleGroupToCertGroup_PTR   TupleGroupToCertGroup;
    _CSSM_TPSPI_PassThrough_PTR             PassThrough;
} CSSM_SPI_TP_FUNCS, *CSSM_SPI_TP_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CSSMTPI_H */
