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
 * @(#)$RCSfile: pkcs7oid.h,v $ $Revision: 1.1.2.8 $ (DEC) $Date: 2002/03/20 21:54:41 $
 */
/*-----------------------------------------------------------------------
 * File: PKCS7OID.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _PKCS7OID_H
#define _PKCS7OID_H
    
#include "oidsbase.h"

/*
**  intel cdsa object identifiers for pkcs#7 signature format extensions
*/
#define RSAOID              0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d
#define RSALEN              6

#define PKCSOID             RSAOID, 1
#define PKCSLEN             RSALEN + 1

#define INTELOID            0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x4d
#define INTELLEN            7

#define INTELCDSAOID        INTELOID, 2
#define INTELCDSALEN        INTELLEN + 1

#define INTELCERTFORMATOID  INTELCDSAOID, 1, 1
#define INTELCERTFORMATLEN  INTELCDSALEN + 2

#define INTELAGGSIGOID      INTELCDSAOID, 1, 3, 1
#define INTELAGGSIGLEN      INTELCDSALEN + 3

#define INTELGETDATAALGOID  INTELAGGSIGOID, 1
#define INTELGETDATAALGLEN  INTELAGGSIGLEN + 1

#define INTELGETCERTALGOID  INTELAGGSIGOID, 2
#define INTELGETCERTALGLEN  INTELAGGSIGLEN + 1

#define INTELSIGFORMATOID   INTELAGGSIGOID, 3
#define INTELSIGFORMATLEN   INTELAGGSIGLEN + 1

#define INTELDIGESTALGOID   INTELAGGSIGOID, 4
#define INTELDIGESTALGLEN   INTELAGGSIGLEN + 1

#define INTELSIGALGOID      INTELAGGSIGOID, 5
#define INTELSIGALGLEN      INTELAGGSIGLEN + 1

/* get data algorithms */
#define INTELSIGGETDATAEMBEDOID     INTELGETDATAALGOID, 1
#define INTELSIGGETDATAEMBEDLEN     INTELGETDATAALGLEN + 1

#define INTELSIGGETDATAFILEOID      INTELGETDATAALGOID, 2
#define INTELSIGGETDATAFILELEN      INTELGETDATAALGLEN + 1

#define INTELSIGGETDATAURLOID       INTELGETDATAALGOID, 3
#define INTELSIGGETDATAURLLEN       INTELGETDATAALGLEN + 1

#define INTELSIGGETDATAFILEREFOID   INTELGETDATAALGOID, 4
#define INTELSIGGETDATAFILEREFLEN   INTELGETDATAALGLEN + 1

#define INTELSIGGETDATAURLREFOID    INTELGETDATAALGOID, 5
#define INTELSIGGETDATAURLREFLEN    INTELGETDATAALGLEN + 1

/* From PKCS 7 */
static uint8 
OID_data[]          = { OID_PKCS_7, 1  },
OID_signedData[]    = { OID_PKCS_7, 2  },
OID_envelopedData[] = { OID_PKCS_7, 3  },
OID_signEnvData[]   = { OID_PKCS_7, 4  },
OID_digestedData[]  = { OID_PKCS_7, 5  },
OID_encryptedData[] = { OID_PKCS_7, 6  };

static CSSM_OID
    CSSMOID_Pkcs7Data                    = {OID_PKCS_7_LENGTH+1, OID_data},
    CSSMOID_Pkcs7SignedData              = {OID_PKCS_7_LENGTH+1, OID_signedData},
    CSSMOID_Pkcs7EnvelopedData           = {OID_PKCS_7_LENGTH+1, OID_envelopedData},
    CSSMOID_Pkcs7SignedAndEnvelopedData  = {OID_PKCS_7_LENGTH+1, OID_signEnvData},
    CSSMOID_Pkcs7DigestedData            = {OID_PKCS_7_LENGTH+1, OID_digestedData},
    CSSMOID_Pkcs7EncryptedData           = {OID_PKCS_7_LENGTH+1, OID_encryptedData}
;

#endif /* _PKCS7OID_H */
