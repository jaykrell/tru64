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
 * @(#)$RCSfile: oidsx509.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:48:19 $
 */
/*-----------------------------------------------------------------------
 * File: OIDSX509.H
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

#ifndef _OIDSX509_H
#define _OIDSX509_H

#include "cssm.h"
#include "oidscert.h"
#include "oidscrl.h"

/**************** X509 Certificate, CRL, or Signature OID -> int mapping **************/
typedef enum intel_x509_oid_as_int {
    INT_NoMatch = 0,

    INT_SignedCertificateCStruct,
    INT_SignedCertificate,
    INT_CertificateCStruct,
    INT_Certificate,
    INT_Version,
    INT_SerialNumber,
    INT_IssuerNameCStruct,
    INT_IssuerNameLDAP,
    INT_IssuerName,
    INT_ValidityNotBefore,
    INT_ValidityNotAfter,
    INT_SubjectNameCStruct,
    INT_SubjectNameLDAP,
    INT_SubjectName,
    INT_CSSMKeyStruct,
	INT_SubjectPublicKeyCStruct,
    INT_SubjectPublicKeyAlgorithm,
    INT_SubjectPublicKeyAlgorithmParameters,
    INT_SubjectPublicKey,
    INT_CertificateIssuerUniqueId,
    INT_CertificateSubjectUniqueId,
    INT_CertificateNumberOfExtensions,
    INT_CertificateExtensionsCStruct,
    INT_CertificateExtensionsStruct,
    INT_CertificateExtensionCStruct,
    INT_CertificateExtensionStruct,
    INT_CertificateExtensionId,
    INT_CertificateExtensionCritical,
    INT_CertificateExtensionType,
    INT_CertificateExtensionValue,
	INT_ExtBasicConstraints,
	INT_ExtPrivateUseExemptions,

	INT_SignatureCStruct,
    INT_SignatureStruct,
    INT_SignatureAlgorithm, 
    INT_SignatureAlgorithmParameters, 
    INT_Signature,

    INT_CRLSignedCrlStruct,
    INT_CRLTbsCertListStruct,
    INT_CRLVersion,
    INT_CRLIssuerStruct,
    INT_CRLThisUpdate,
    INT_CRLNextUpdate,
    INT_CRLRevokedCertificatesStruct,
    INT_CRLNumberOfRevokedCertEntries,
    INT_CRLRevokedEntryStruct,
    INT_CRLRevokedEntrySerialNumber,
    INT_CRLRevokedEntryRevocationDate,
    INT_CRLRevokedEntryAllExtensionsStruct,
    INT_CRLRevokedEntryNumberOfExtensions,
    INT_CRLRevokedEntrySingleExtensionStruct,
    INT_CRLRevokedEntryExtensionId,
    INT_CRLRevokedEntryExtensionCritical,
    INT_CRLRevokedEntryExtensionType,
    INT_CRLRevokedEntryExtensionValue,
    INT_CRLAllExtensionsStruct,
    INT_CRLNumberOfExtensions,
    INT_CRLSingleExtensionStruct,
    INT_CRLExtensionId,
    INT_CRLExtensionCritical,
    INT_CRLExtensionType,
    INT_CRLExtensionValue,

    INT_CRLSignatureStruct,
    INT_CRLSignatureAlgorithm,
    INT_CRLSignatureAlgorithmParameters,
    INT_CRLSignature,

	INT_CRLSignedCrlCStruct,
    INT_CRLTbsCertListCStruct,
    INT_CRLRevokedCertificatesCStruct,
    INT_CRLRevokedEntryCStruct,
	INT_CRLIssuerNameCStruct,
	INT_CRLIssuerNameLDAP,
    INT_CRLRevokedEntryAllExtensionsCStruct,
    INT_CRLRevokedEntrySingleExtensionCStruct,
    INT_CRLAllExtensionsCStruct,
    INT_CRLSingleExtensionCStruct,
	INT_CRLSignatureCStruct

} INTEL_X509_OID_AS_INT;


/* Cert OID functions */
int x509_cl_CertOidToInt(CSSM_OID Oid);
CSSM_BOOL IsX509V3CertOid( CSSM_OID Oid );

/* CRL OID functions */
int x509_cl_CrlOidToInt(CSSM_OID Oid);
CSSM_BOOL IsX509V2CrlOid(CSSM_OID Oid);

/* OID functions */
int x509_cl_OidToInt(CSSM_OID Oid);


#endif
