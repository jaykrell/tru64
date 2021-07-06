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
 * @(#)$RCSfile: oidscrl.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2001/11/02 21:48:17 $
 */
/*-----------------------------------------------------------------------
 * File: OIDSCRL.H
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

/* This file declares the OIDs and related functions used to identify fields
    of a CRL.
*/

#ifndef _OIDSCRL_H
#define _OIDSCRL_H

#include "cssm.h"
#include "oidsbase.h"

/* number of oids includes oids defined here plus 4 signature field oids common to
certs and crls */
#define NUMBER_X509_CRL_OIDS  ((32-2) + 8 )

#ifdef X509CL_MODULE

#ifdef __cplusplus
extern "C" {
#endif

extern OID_INT X509_CRL_OIDS[NUMBER_X509_CRL_OIDS];

#ifdef __cplusplus
}
#endif

#endif

#define INTEL_X509V2_CRL_R08            INTEL_SEC_FORMATS, 2, 1
#define INTEL_X509V2_CRL_R08_LENGTH     INTEL_SEC_FORMATS_LENGTH + 2

/*** CRL-specific OIDs ***/
static uint8
    X509V2CRLSignedCrlStruct[]                  = { INTEL_X509V2_CRL_R08, 0 },
    X509V2CRLSignedCrlCStruct[]                 = { INTEL_X509V2_CRL_R08, 0, INTEL_X509_C_DATATYPE },

    X509V2CRLTbsCertListStruct[]                = { INTEL_X509V2_CRL_R08, 1 },
    X509V2CRLTbsCertListCStruct[]               = { INTEL_X509V2_CRL_R08, 1, INTEL_X509_C_DATATYPE },
    
    X509V2CRLVersion[]                          = { INTEL_X509V2_CRL_R08, 2 },

    X509V1CRLIssuerStruct[]                     = { INTEL_X509V2_CRL_R08, 3 },
    X509V1CRLIssuerNameCStruct[]                = { INTEL_X509V2_CRL_R08, 3, INTEL_X509_C_DATATYPE },
    X509V1CRLIssuerNameLDAP[]                   = { INTEL_X509V2_CRL_R08, 3, INTEL_X509_LDAPSTRING_DATATYPE },

    X509V1CRLThisUpdate[]                       = { INTEL_X509V2_CRL_R08, 4 },
    X509V1CRLNextUpdate[]                       = { INTEL_X509V2_CRL_R08, 5 },

    X509V1CRLRevokedCertificatesStruct[]        = { INTEL_X509V2_CRL_R08, 7 },
    X509V1CRLRevokedCertificatesCStruct[]       = { INTEL_X509V2_CRL_R08, 7, INTEL_X509_C_DATATYPE },

    X509V1CRLNumberOfRevokedCertEntries[]       = { INTEL_X509V2_CRL_R08, 6 },

    X509V1CRLRevokedEntryStruct[]               = { INTEL_X509V2_CRL_R08, 15 },
    X509V1CRLRevokedEntryCStruct[]              = { INTEL_X509V2_CRL_R08, 15, INTEL_X509_C_DATATYPE },

    X509V1CRLRevokedEntrySerialNumber[]         = { INTEL_X509V2_CRL_R08, 16 },
    X509V1CRLRevokedEntryRevocationDate[]       = { INTEL_X509V2_CRL_R08, 17 },

    X509V2CRLRevokedEntryAllExtensionsStruct[]  = { INTEL_X509V2_CRL_R08, 18 },
    X509V2CRLRevokedEntryAllExtensionsCStruct[] = { INTEL_X509V2_CRL_R08, 18, INTEL_X509_C_DATATYPE },

    X509V2CRLRevokedEntryNumberOfExtensions[]   = { INTEL_X509V2_CRL_R08, 20 },

    X509V2CRLRevokedEntrySingleExtensionStruct[]= { INTEL_X509V2_CRL_R08, 19 },
    X509V2CRLRevokedEntrySingleExtensionCStruct[]= { INTEL_X509V2_CRL_R08, 19, INTEL_X509_C_DATATYPE },

    X509V2CRLRevokedEntryExtensionId[]          = { INTEL_X509V2_CRL_R08, 21 },
    X509V2CRLRevokedEntryExtensionCritical[]    = { INTEL_X509V2_CRL_R08, 22 },
    X509V2CRLRevokedEntryExtensionType[]        = { INTEL_X509V2_CRL_R08, 23 },
    X509V2CRLRevokedEntryExtensionValue[]       = { INTEL_X509V2_CRL_R08, 24 },

    X509V2CRLAllExtensionsStruct[]              = { INTEL_X509V2_CRL_R08, 8 },
    X509V2CRLAllExtensionsCStruct[]             = { INTEL_X509V2_CRL_R08, 8, INTEL_X509_C_DATATYPE },

    X509V2CRLNumberOfExtensions[]               = { INTEL_X509V2_CRL_R08, 10 },

    X509V2CRLSingleExtensionStruct[]            = { INTEL_X509V2_CRL_R08, 9 },
    X509V2CRLSingleExtensionCStruct[]           = { INTEL_X509V2_CRL_R08, 9, INTEL_X509_C_DATATYPE },

    X509V2CRLExtensionId[]                      = { INTEL_X509V2_CRL_R08, 11 },
    X509V2CRLExtensionCritical[]                = { INTEL_X509V2_CRL_R08, 12 },
    X509V2CRLExtensionType[]                    = { INTEL_X509V2_CRL_R08, 13 },
    X509V2CRLExtensionValue[]                   = { INTEL_X509V2_CRL_R08, 14 }
	;

static CSSM_OID
    CSSMOID_X509V2CRLSignedCrlStruct            = { INTEL_X509V2_CRL_R08_LENGTH + 1, 
                                                    X509V2CRLSignedCrlStruct },
    CSSMOID_X509V2CRLSignedCrlCStruct           = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1, 
                                                    X509V2CRLSignedCrlCStruct },

    CSSMOID_X509V2CRLTbsCertListStruct          = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLTbsCertListStruct },
    CSSMOID_X509V2CRLTbsCertListCStruct         = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                    X509V2CRLTbsCertListCStruct },

    CSSMOID_X509V2CRLVersion                    = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLVersion },

	CSSMOID_X509V1CRLIssuerStruct               = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLIssuerStruct },
	CSSMOID_X509V1CRLIssuerNameCStruct			= { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
													X509V1CRLIssuerNameCStruct },
	CSSMOID_X509V1CRLIssuerNameLDAP				= { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
													X509V1CRLIssuerNameLDAP },

    CSSMOID_X509V1CRLThisUpdate                 = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLThisUpdate },
    CSSMOID_X509V1CRLNextUpdate                 = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLNextUpdate },

    CSSMOID_X509V1CRLRevokedCertificatesStruct  = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLRevokedCertificatesStruct },
    CSSMOID_X509V1CRLRevokedCertificatesCStruct = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                    X509V1CRLRevokedCertificatesCStruct },

    CSSMOID_X509V1CRLNumberOfRevokedCertEntries = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLNumberOfRevokedCertEntries },

    CSSMOID_X509V1CRLRevokedEntryStruct         = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLRevokedEntryStruct },
    CSSMOID_X509V1CRLRevokedEntryCStruct        = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                    X509V1CRLRevokedEntryCStruct },

    CSSMOID_X509V1CRLRevokedEntrySerialNumber   = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLRevokedEntrySerialNumber },
    CSSMOID_X509V1CRLRevokedEntryRevocationDate = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V1CRLRevokedEntryRevocationDate },

    CSSMOID_X509V2CRLRevokedEntryAllExtensionsStruct = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                         X509V2CRLRevokedEntryAllExtensionsStruct },
    CSSMOID_X509V2CRLRevokedEntryAllExtensionsCStruct = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                         X509V2CRLRevokedEntryAllExtensionsCStruct },

    CSSMOID_X509V2CRLRevokedEntryNumberOfExtensions = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                        X509V2CRLRevokedEntryNumberOfExtensions },

    CSSMOID_X509V2CRLRevokedEntrySingleExtensionStruct = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                           X509V2CRLRevokedEntrySingleExtensionStruct },
    CSSMOID_X509V2CRLRevokedEntrySingleExtensionCStruct = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                           X509V2CRLRevokedEntrySingleExtensionCStruct },

    CSSMOID_X509V2CRLRevokedEntryExtensionId    = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLRevokedEntryExtensionId },
    CSSMOID_X509V2CRLRevokedEntryExtensionCritical  = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                        X509V2CRLRevokedEntryExtensionCritical },
    CSSMOID_X509V2CRLRevokedEntryExtensionType  = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLRevokedEntryExtensionType },
    CSSMOID_X509V2CRLRevokedEntryExtensionValue = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLRevokedEntryExtensionValue },

    CSSMOID_X509V2CRLAllExtensionsStruct        = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLAllExtensionsStruct },
    CSSMOID_X509V2CRLAllExtensionsCStruct        = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                    X509V2CRLAllExtensionsCStruct },

    CSSMOID_X509V2CRLNumberOfExtensions         = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLNumberOfExtensions },

    CSSMOID_X509V2CRLSingleExtensionStruct      = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLSingleExtensionStruct },
    CSSMOID_X509V2CRLSingleExtensionCStruct      = { INTEL_X509V2_CRL_R08_LENGTH + 1 + 1,
                                                    X509V2CRLSingleExtensionCStruct },

    CSSMOID_X509V2CRLExtensionId                = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLExtensionId },
    CSSMOID_X509V2CRLExtensionCritical          = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLExtensionCritical },
    CSSMOID_X509V2CRLExtensionType              = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLExtensionType },
    CSSMOID_X509V2CRLExtensionValue             = { INTEL_X509V2_CRL_R08_LENGTH + 1,
                                                    X509V2CRLExtensionValue }
	;

#endif
