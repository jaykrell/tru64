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
 * @(#)$RCSfile: oidsbase.h,v $ $Revision: 1.1.2.7 $ (DEC) $Date: 2001/11/02 21:48:15 $
 */
/*-----------------------------------------------------------------------
 * File: OIDSBASE.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _OIDSBASE_H
#define _OIDSBASE_H

#include "cssm.h"

/* From X.680 */

#define OID_ITU_RECOMMENDATION 0
#define OID_ITU_QUESTION       1
#define OID_ITU_ADMIN          2
#define OID_ITU_NETWORK_OP     3
#define OID_ITU_IDENTIFIED_ORG 4

#define OID_ISO_STANDARD       40
#define OID_ISO_MEMBER         42                      /* Also in PKCS */
#define OID_US                 OID_ISO_MEMBER, 134, 72 /* Also in PKCS */
#define OID_CA                 OID_ISO_MEMBER, 124

#define OID_ISO_IDENTIFIED_ORG 43
#define OID_OSINET             OID_ISO_IDENTIFIED_ORG, 4
#define OID_GOSIP              OID_ISO_IDENTIFIED_ORG, 5
#define OID_DOD                OID_ISO_IDENTIFIED_ORG, 6
#define OID_OIW                OID_ISO_IDENTIFIED_ORG, 14 /* Also in x9.57 */

#define OID_ISO_CCITT_DIR_SERVICE 85
#define OID_ISO_CCITT_COUNTRY     96
#define OID_COUNTRY_US            OID_ISO_CCITT_COUNTRY, 134, 72
#define OID_COUNTRY_CA            OID_ISO_CCITT_COUNTRY, 124
#define OID_COUNTRY_US_ORG        OID_COUNTRY_US, 1
#define OID_COUNTRY_US_MHS_MD     OID_COUNTRY_US, 2
#define OID_COUNTRY_US_STATE      OID_COUNTRY_US, 3

/* From the PKCS Standards */
#define OID_ISO_MEMBER_LENGTH 1
#define OID_US_LENGTH         (OID_ISO_MEMBER_LENGTH + 2)

#define OID_RSA               OID_US, 134, 247, 13
#define OID_RSA_LENGTH        (OID_US_LENGTH + 3)

#define OID_RSA_HASH          OID_RSA, 2
#define OID_RSA_HASH_LENGTH   (OID_RSA_LENGTH + 1)

#define OID_RSA_ENCRYPT       OID_RSA, 3
#define OID_RSA_ENCRYPT_LENGTH (OID_RSA_LENGTH + 1)

#define OID_PKCS              OID_RSA, 1
#define OID_PKCS_LENGTH       (OID_RSA_LENGTH + 1)

#define OID_PKCS_1            OID_PKCS, 1 
#define OID_PKCS_1_LENGTH     (OID_PKCS_LENGTH + 1)

#define OID_PKCS_2            OID_PKCS, 2 
#define OID_PKCS_3            OID_PKCS, 3 
#define OID_PKCS_3_LENGTH     (OID_PKCS_LENGTH + 1)

#define OID_PKCS_4            OID_PKCS, 4 
#define OID_PKCS_5            OID_PKCS, 5 
#define OID_PKCS_5_LENGTH     (OID_PKCS_LENGTH + 1)
#define OID_PKCS_6            OID_PKCS, 6 
#define OID_PKCS_7            OID_PKCS, 7 
#define OID_PKCS_7_LENGTH     (OID_PKCS_LENGTH + 1)

#define OID_PKCS_8            OID_PKCS, 8 
#define OID_PKCS_9            OID_PKCS, 9
#define OID_PKCS_9_LENGTH     (OID_PKCS_LENGTH + 1)
#define OID_PKCS_10           OID_PKCS, 10


#define OID_DS                OID_ISO_CCITT_DIR_SERVICE /* Also in X.501 */
#define OID_DS_LENGTH         1

#define OID_ATTR_TYPE         OID_DS, 4                /* Also in X.501 */
#define OID_ATTR_TYPE_LENGTH  (OID_DS_LENGTH + 1)

#define OID_DSALG             OID_DS, 8                /* Also in X.501 */
#define OID_DSALG_LENGTH      (OID_DS_LENGTH + 1)

#define OID_EXTENSION         OID_DS, 29               /* Also in X.501 */
#define OID_EXTENSION_LENGTH  (OID_DS_LENGTH + 1)

/* From PKIX part1 */
/* { iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7) } */
#define OID_PKIX             43, 6, 1, 5, 5, 7
#define OID_PKIX_LENGTH      6

/* private certificate extensions, { id-pkix 1 } */
#define OID_PKIX_PE          OID_PKIX, 1
#define OID_PKIX_PE_LENGTH   (OID_PKIX_LENGTH + 1)

/* policy qualifier types {id-pkix 2 } */
#define OID_PKIX_QT          OID_PKIX, 2
#define OID_PKIX_QT_LENGTH   (OID_PKIX_LENGTH + 1)

  /*  policyQualifierIds */
    /* CPS qualifier, { id-qt 1 } */
#define OID_PKIX_QT_CPS      OID_PKIX_QT, 1
#define OID_PKIX_QT_CPS_LENGTH (OID_PKIX_QT_LENGTH + 1)
    /* user notice qualifier, { id-qt 2 } */
#define OID_PKIX_QT_UNOTICE  OID_PKIX_QT, 2
#define OID_PKIX_QT_UNOTICE_LENGTH (OID_PKIX_QT_LENGTH + 1)

/* extended key purpose OIDs {id-pkix 3 } */
#define OID_PKIX_KP          OID_PKIX, 3
#define OID_PKIX_KP_LENGTH   (OID_PKIX_LENGTH + 1)

/* access descriptors {id-pkix 4 } */
#define OID_PKIX_AD          OID_PKIX, 48
#define OID_PKIX_AD_LENGTH   (OID_PKIX_LENGTH + 1)

  /* access descriptors */
    /* OCSP */
#define OID_PKIX_AD_OCSP     OID_PKIX_AD, 1
#define OID_PKIX_AD_OCSP_LENGTH (OID_PKIX_AD_LENGTH + 1)
    /* cAIssuers */
#define OID_PKIX_AD_CAISSUERS OID_PKIX_AD, 2
#define OID_PKIX_AD_CAISSUERS_LENGTH (OID_PKIX_AD_LENGTH + 1)
/* end PKIX part1 */

#define OID_APPL_TCP_PROTO   43, 6, 1, 2, 1, 27, 4
#define OID_APPL_TCP_PROTO_LENGTH   8

#define OID_DAP              OID_DS, 3, 1
#define OID_DAP_LENGTH       (OID_DS_LENGTH + 2)

/* From x9.57 */
#define OID_OIW_LENGTH        2

#define OID_OIW_SECSIG        OID_OIW, 3
#define OID_OIW_SECSIG_LENGTH (OID_OIW_LENGTH + 1)

#define OID_OIW_ALGORITHM     OID_OIW_SECSIG, 2
#define OID_OIW_ALGORITHM_LENGTH (OID_OIW_SECSIG_LENGTH + 1)

#define OID_OIWDIR           OID_OIW, 7, 2
#define OID_OIWDIR_LENGTH    (OID_OIW_LENGTH + 2)

#define OID_OIWDIR_CRPT      OID_OIWDIR, 1

#define OID_OIWDIR_HASH      OID_OIWDIR, 2
#define OID_OIWDIR_HASH_LENGTH (OID_OIWDIR_LENGTH + 1)

#define OID_OIWDIR_SIGN      OID_OIWDIR, 3
#define OID_OIWDIR_SIGN_LENGTH (OID_OIWDIR_LENGTH + 1)

#if 0
define  OID_X9CM             OID_US, 10040 
This DER encoding for 10040 should be re-verified
#endif

#define OID_X9CM             OID_US, 206, 56
#define OID_X9CM_MODULE      OID_X9CM, 1
#define OID_X9CM_INSTRUCTION OID_X9CM, 2
#define OID_X9CM_ATTR        OID_X9CM, 3
#define OID_X9CM_X9ALGORITHM OID_X9CM, 4
#define OID_X9CM_X9ALGORITHM_LENGTH ((OID_US_LENGTH) + 2 + 1)

/* Intel CSSM */
#define INTEL        96, 134, 72, 1, 134, 248, 77 
#define INTEL_LENGTH 7

#define INTEL_CDSASECURITY              INTEL, 2
#define INTEL_CDSASECURITY_LENGTH       (INTEL_LENGTH + 1)

#define INTEL_SEC_FORMATS               INTEL_CDSASECURITY, 1
#define INTEL_SEC_FORMATS_LENGTH        (INTEL_CDSASECURITY_LENGTH + 1)

#define INTEL_SEC_ALGS                  INTEL_CDSASECURITY, 2, 5  
#define INTEL_SEC_ALGS_LENGTH           (INTEL_CDSASECURITY_LENGTH + 2)

#define INTEL_SEC_OBJECT_BUNDLE         INTEL_SEC_FORMATS, 4
#define INTEL_SEC_OBJECT_BUNDLE_LENGTH  (INTEL_SEC_FORMATS_LENGTH + 1)

#define INTEL_CERT_AND_PRIVATE_KEY_2_0  INTEL_SEC_OBJECT_BUNDLE, 1
#define INTEL_CERT_AND_PRIVATE_KEY_2_0_LENGTH  (INTEL_SEC_OBJECT_BUNDLE_LENGTH + 1)

#define INTEL_X509_C_DATATYPE          1
#define INTEL_X509_LDAPSTRING_DATATYPE 2

#endif
