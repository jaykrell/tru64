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
 * @(#)$RCSfile: oidscert.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:48:16 $
 */
/*-----------------------------------------------------------------------
 * File: OIDSCERT.H
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

#ifndef _OIDSCERT_H
#define _OIDSCERT_H

#include "cssm.h"
#include "oidsbase.h"
#include "oidsattr.h"

#define NUMBER_X509_CERT_OIDS  ((32-4) + 5)

#ifdef X509CL_MODULE

#ifdef __cplusplus
extern "C" {
#endif

typedef struct oid_int {
	CSSM_OID_PTR oidval;
	uint32	     intval;
} OID_INT;

extern OID_INT X509_CERT_OIDS[NUMBER_X509_CERT_OIDS];

#ifdef __cplusplus
}
#endif

#endif

#define INTEL_X509V3_CERT_R08           INTEL_SEC_FORMATS, 1, 1
#define INTEL_X509V3_CERT_R08_LENGTH    INTEL_SEC_FORMATS_LENGTH + 2

#define INTEL_X509V3_CERT_PRIVATE_EXTENSIONS           INTEL_X509V3_CERT_R08, 50
#define INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH    INTEL_X509V3_CERT_R08_LENGTH + 1

#define INTEL_X509V3_SIGN_R08           INTEL_SEC_FORMATS, 3, 2
#define INTEL_X509V3_SIGN_R08_LENGTH    INTEL_SEC_FORMATS_LENGTH + 2

/**************** Private Extension OIDS **********************/
static uint8
    SubjectSignatureBitmap[] = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS,1}, 
    SubjectPicture[]         = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS,2}, 
    SubjectEmailAddress[]    = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS,3},

    UseExemptions[]      = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS,4};

static CSSM_OID
    CSSMOID_SubjectSignatureBitmap = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH+1, SubjectSignatureBitmap},
    CSSMOID_SubjectPicture         = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH+1, SubjectPicture},
    CSSMOID_SubjectEmailAddress    = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH+1, SubjectEmailAddress},

    CSSMOID_UseExemptions     = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH+1, UseExemptions};


/************************* CERTIFICATE & SIGNATURE OIDS **********************/
static uint8
    X509V3SignedCertificate[]           = {INTEL_X509V3_CERT_R08, 0},   
    X509V3SignedCertificateCStruct[]    = {INTEL_X509V3_CERT_R08, 0, INTEL_X509_C_DATATYPE}, 

    X509V3Certificate[]                 = {INTEL_X509V3_CERT_R08, 1},
    X509V3CertificateCStruct[]          = {INTEL_X509V3_CERT_R08, 1, INTEL_X509_C_DATATYPE},

    X509V1Version[]                     = {INTEL_X509V3_CERT_R08, 2},
    X509V1SerialNumber[]                = {INTEL_X509V3_CERT_R08, 3},

    X509V1IssuerName[]                  = {INTEL_X509V3_CERT_R08, 5},   
    X509V1IssuerNameCStruct[]           = {INTEL_X509V3_CERT_R08, 5, INTEL_X509_C_DATATYPE},   
    X509V1IssuerNameLDAP[]              = {INTEL_X509V3_CERT_R08, 5, INTEL_X509_LDAPSTRING_DATATYPE},   

    X509V1ValidityNotBefore[]           = {INTEL_X509V3_CERT_R08, 6},   
    X509V1ValidityNotAfter[]            = {INTEL_X509V3_CERT_R08, 7},   

    X509V1SubjectName[]                 = {INTEL_X509V3_CERT_R08, 8},   
    X509V1SubjectNameCStruct[]          = {INTEL_X509V3_CERT_R08, 8, INTEL_X509_C_DATATYPE},   
    X509V1SubjectNameLDAP[]             = {INTEL_X509V3_CERT_R08, 8, INTEL_X509_LDAPSTRING_DATATYPE},

    CSSMKeyStruct[]                     = {INTEL_X509V3_CERT_R08, 20},   
	X509V1SubjectPublicKeyCStruct[]     = {INTEL_X509V3_CERT_R08, 20, INTEL_X509_C_DATATYPE},

    X509V1SubjectPublicKeyAlgorithm[]   = {INTEL_X509V3_CERT_R08, 9},  
    X509V1SubjectPublicKeyAlgorithmParameters[]   = {INTEL_X509V3_CERT_R08, 18},  
    X509V1SubjectPublicKey[]            = {INTEL_X509V3_CERT_R08, 10},   

    X509V1CertificateIssuerUniqueId[]   = {INTEL_X509V3_CERT_R08, 11}, 
    X509V1CertificateSubjectUniqueId[]  = {INTEL_X509V3_CERT_R08, 12}, 

    X509V3CertificateExtensionsStruct[] = {INTEL_X509V3_CERT_R08, 21},
    X509V3CertificateExtensionsCStruct[]= {INTEL_X509V3_CERT_R08, 21, INTEL_X509_C_DATATYPE},

    X509V3CertificateNumberOfExtensions[] = {INTEL_X509V3_CERT_R08, 14},    

    X509V3CertificateExtensionStruct[]    = {INTEL_X509V3_CERT_R08, 13}, 
    X509V3CertificateExtensionCStruct[]   = {INTEL_X509V3_CERT_R08, 13, INTEL_X509_C_DATATYPE}, 

    X509V3CertificateExtensionId[]        = {INTEL_X509V3_CERT_R08, 15},    
    X509V3CertificateExtensionCritical[]  = {INTEL_X509V3_CERT_R08, 16},   
    X509V3CertificateExtensionType[]      = {INTEL_X509V3_CERT_R08, 19},   
    X509V3CertificateExtensionValue[]     = {INTEL_X509V3_CERT_R08, 17}
	;

static uint8
    X509V1SignatureStruct[]				  = {INTEL_X509V3_SIGN_R08, 0},    
	X509V1SignatureCStruct[]              = {INTEL_X509V3_SIGN_R08, 0, INTEL_X509_C_DATATYPE},

    X509V1SignatureAlgorithm[]            = {INTEL_X509V3_SIGN_R08, 1},     
    X509V1SignatureAlgorithmParameters[]  = {INTEL_X509V3_SIGN_R08, 3},
    X509V1Signature[]                     = {INTEL_X509V3_SIGN_R08, 2}
	;   

    /* NOTE: INTEL_X509V3_CERT_R08, 50 is reserved for the Extension Contents OID tree */

static CSSM_OID
    CSSMOID_X509V3SignedCertificate         = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V3SignedCertificate},
    CSSMOID_X509V3SignedCertificateCStruct  = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V3SignedCertificateCStruct},

    CSSMOID_X509V3Certificate               = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V3Certificate},
    CSSMOID_X509V3CertificateCStruct        = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V3CertificateCStruct},

    CSSMOID_X509V1Version                   = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1Version},
    CSSMOID_X509V1SerialNumber              = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1SerialNumber},

    CSSMOID_X509V1IssuerName                = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1IssuerName},
    CSSMOID_X509V1IssuerNameCStruct         = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V1IssuerNameCStruct},
    CSSMOID_X509V1IssuerNameLDAP            = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V1IssuerNameLDAP},

    CSSMOID_X509V1ValidityNotBefore         = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1ValidityNotBefore},
    CSSMOID_X509V1ValidityNotAfter          = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1ValidityNotAfter},

    CSSMOID_X509V1SubjectName               = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1SubjectName},
    CSSMOID_X509V1SubjectNameCStruct        = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V1SubjectNameCStruct},
    CSSMOID_X509V1SubjectNameLDAP           = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V1SubjectNameLDAP},

    CSSMOID_CSSMKeyStruct                   = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												CSSMKeyStruct},
    CSSMOID_X509V1SubjectPublicKeyCStruct   = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
												X509V1SubjectPublicKeyCStruct},

    CSSMOID_X509V1SubjectPublicKeyAlgorithm = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1SubjectPublicKeyAlgorithm},
    CSSMOID_X509V1SubjectPublicKeyAlgorithmParameters = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1SubjectPublicKeyAlgorithmParameters},
    CSSMOID_X509V1SubjectPublicKey          = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1SubjectPublicKey},

    CSSMOID_X509V1CertificateIssuerUniqueId = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1CertificateIssuerUniqueId},
    CSSMOID_X509V1CertificateSubjectUniqueId= {INTEL_X509V3_CERT_R08_LENGTH + 1, 
												X509V1CertificateSubjectUniqueId},

    CSSMOID_X509V3CertificateExtensionsStruct     = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionsStruct},
    CSSMOID_X509V3CertificateExtensionsCStruct    = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
														X509V3CertificateExtensionsCStruct},

    CSSMOID_X509V3CertificateNumberOfExtensions   = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateNumberOfExtensions},

    CSSMOID_X509V3CertificateExtensionStruct      = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionStruct},
    CSSMOID_X509V3CertificateExtensionCStruct     = {INTEL_X509V3_CERT_R08_LENGTH + 1 + 1, 
														X509V3CertificateExtensionCStruct},

    CSSMOID_X509V3CertificateExtensionId          = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionId},
    CSSMOID_X509V3CertificateExtensionCritical    = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionCritical},
    CSSMOID_X509V3CertificateExtensionType        = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionType},
    CSSMOID_X509V3CertificateExtensionValue       = {INTEL_X509V3_CERT_R08_LENGTH + 1, 
														X509V3CertificateExtensionValue},

	/* Add X509 Extension OIDs here.*/
    CSSMOID_X509ExtBasicConstraints               = {OID_EXTENSION_LENGTH + 1, 
														OID_BasicConstraints},
	/* Add X509 Private Extension OIDs here. */
    CSSMOID_X509ExtPrivateUseExemptions           = {INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH + 1, 
														UseExemptions}
	;


static CSSM_OID
    CSSMOID_X509V1SignatureStruct                 = {INTEL_X509V3_SIGN_R08_LENGTH + 1, 
														X509V1SignatureStruct},
	CSSMOID_X509V1SignatureCStruct                = {INTEL_X509V3_SIGN_R08_LENGTH + 1 + 1, 
														X509V1SignatureCStruct},

    CSSMOID_X509V1SignatureAlgorithm              = {INTEL_X509V3_SIGN_R08_LENGTH + 1, 
														X509V1SignatureAlgorithm},
    CSSMOID_X509V1SignatureAlgorithmParameters    = {INTEL_X509V3_SIGN_R08_LENGTH + 1, 
														X509V1SignatureAlgorithmParameters},
    CSSMOID_X509V1Signature                       = {INTEL_X509V3_SIGN_R08_LENGTH + 1, 
														X509V1Signature}
	;

#endif
