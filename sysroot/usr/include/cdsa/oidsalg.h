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
 * @(#)$RCSfile: oidsalg.h,v $ $Revision: 1.1.2.7 $ (DEC) $Date: 2001/11/02 21:48:13 $
 */
/*-----------------------------------------------------------------------
 * File: OIDSALG.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

#ifndef _OIDSALG_H
#define _OIDSALG_H

#include "cssm.h"
#include "oidsbase.h"

extern CSSM_RETURN oidsalg_SetError (uint32 error);

/* From PKCS 1 */
static uint8
OID_MD2[]          = { OID_RSA_HASH, 2 },
OID_MD4[]          = { OID_RSA_HASH, 4 },
OID_MD5[]          = { OID_RSA_HASH, 5 };

static uint8
OID_RSAEncryption[]= { OID_PKCS_1, 1 },
OID_MD2WithRSA[]   = { OID_PKCS_1, 2 },
OID_MD4WithRSA[]   = { OID_PKCS_1, 3 },
OID_MD5WithRSA[]   = { OID_PKCS_1, 4 },
/* From Microsoft CAPI 2.0 API reference */
/* The following two are per Bob Baldwin (baldwin@rsa.com,5.7.96) */
OID_SHA1WithRSA[]  = { OID_PKCS_1, 5 },
OID_SETOAEP_RSA[]  = { OID_PKCS_1, 6 };


/* From PKCS 3 */
static uint8    
OID_DHKeyAgreement[]    = { OID_PKCS_3, 1 };

/* From PKCS 5 */
static uint8    
OID_PBEWithMD2AndDES_CBC[] = { OID_PKCS_5, 1 }, 
OID_PBEWithMD5AndDES_CBC[] = { OID_PKCS_5, 3 }; 

/* From Microsoft CAPI 2.0 API reference */
/* NIST OSE Implementors' Workshop (OIW) */
/* http://nemo.ncsl.nist.gov/oiw/agreements/stable/OSI/12s_9506.w51 */
/* http://nemo.ncsl.nist.gov/oiw/agreements/working/OSI/12w_9503.w51 */

/* NIST OSE Implementors' Workshop (OIW) Security SIG algorithm identifiers */
static uint8
OID_OIW_md4RSA[]  = { OID_OIW_ALGORITHM, 2  },
OID_OIW_md5RSA[]  = { OID_OIW_ALGORITHM, 3  },
OID_OIW_md4RSA2[] = { OID_OIW_ALGORITHM, 4  },
OID_OIW_desECB[]  = { OID_OIW_ALGORITHM, 6  },
OID_OIW_desCBC[]  = { OID_OIW_ALGORITHM, 7  },
OID_OIW_desOFB[]  = { OID_OIW_ALGORITHM, 8  },
OID_OIW_desCFB[]  = { OID_OIW_ALGORITHM, 9  },
OID_OIW_desMAC[]  = { OID_OIW_ALGORITHM, 10  },
OID_OIW_RSASignature[] = { OID_OIW_ALGORITHM, 11  },/* From x9.57 */
OID_OIW_DSA[]     = { OID_OIW_ALGORITHM, 12  },     /* From x9.57 */ 
OID_OIW_DSAWithSHA[]  = { OID_OIW_ALGORITHM, 13  }, /* From x9.57 */
OID_OIW_mdc2RSA[] = { OID_OIW_ALGORITHM, 14  },
OID_OIW_shaRSA[]  = { OID_OIW_ALGORITHM, 15  },
OID_OIW_dhCommMod[]  = { OID_OIW_ALGORITHM, 16  },
OID_OIW_desEDE[]  = { OID_OIW_ALGORITHM, 17  },
OID_OIW_SHA[]     = { OID_OIW_ALGORITHM, 18  },     /* From x9.57 */
OID_OIW_mdc2[]    = { OID_OIW_ALGORITHM, 19  },
OID_OIW_dsaComm[] = { OID_OIW_ALGORITHM, 20  },
OID_OIW_dsaCommSHA[] = { OID_OIW_ALGORITHM, 21  },
OID_OIW_rsaXchg[] = { OID_OIW_ALGORITHM, 22  },
OID_OIW_keyHashSeal[]= { OID_OIW_ALGORITHM, 23  },
OID_OIW_md2RSASign[] = { OID_OIW_ALGORITHM, 24  },
OID_OIW_md5RSASign[] = { OID_OIW_ALGORITHM, 25  },
OID_OIW_SHA1[]    = { OID_OIW_ALGORITHM, 26  },     /* From x9.57 */
OID_OIW_DSAWithSHA1[] = { OID_OIW_ALGORITHM, 27  }, /* From x9.57 */
OID_OIW_dsaCommSHA1[]= { OID_OIW_ALGORITHM, 28  },
OID_OIW_sha1RSASign[]= { OID_OIW_ALGORITHM, 29  }
;

/* NIST OSE Implementors' Workshop (OIW) Directory SIG algorithm identifiers */
static uint8
OID_OIWDIR_md2[]     = { OID_OIWDIR_HASH, 1 },
OID_OIWDIR_md2RSA[]  = { OID_OIWDIR_SIGN, 1 };

static uint8
OID_X9CM_DSA[] = { OID_X9CM_X9ALGORITHM, 1 };

/* ITU-T UsefulDefinitions */
static uint8
OID_DSALG_CRPT[]  = { OID_DSALG, 1  },
OID_DSALG_HASH[]  = { OID_DSALG, 2  },
OID_DSALG_SIGN[]  = { OID_DSALG, 3  },
OID_DSALG_RSA[]   = { OID_DSALG, 1, 1 };

/* From Microsoft CAPI 2.0 API reference */
static uint8 
OID_RC2CBC[]  = { OID_RSA_ENCRYPT, 2  },
OID_RC4[]     = { OID_RSA_ENCRYPT, 4  },
OID_RC5[]     = { OID_RSA_ENCRYPT, 5  };  /* Note: This OID is assumed */

/* From PKIX1 */
static uint8
OID_X9CM_DSAWithSHA1[] = { OID_X9CM_X9ALGORITHM, 3 };

/********************************** ALGORITHMS ************************/
/* These represent the OIDs that the Intel CLM makes available to applications
 * to represent the Algorithm OIDs 
 */
static uint8
#if 0
DH[]        OID_DHKeyAgreement      /*Diffie Hellman key exchange algorithm */
#endif
PH []       = {INTEL_SEC_ALGS, 2},  /*Pohlig Hellman key exchange algorithm */
KEA[]       = {INTEL_SEC_ALGS, 3},  /*Key Exchange Algorithm */
#if 0
MD2[]     OID_MD2
MD4[]     OID_MD4
MD5[]     OID_MD5
SHA1[]    OID_OIW_SHA1  /*Secure Hash Algorithm  (developed by NIST/NSA) */
#endif
NHASH[]     = {INTEL_SEC_ALGS, 8},  /*N-Hash algorithm(developed by Nippon Telephone and Telegraph) */
HAVAL[]     = {INTEL_SEC_ALGS, 9},  /*HAVAL  hash algorithm  (MD5 variant) */
RIPEMD []   = {INTEL_SEC_ALGS, 10}, /*RIPE-MD  hash algorithm  (MD4 variant - developed for the European Community's RIPE project) */
IBCHASH []  = {INTEL_SEC_ALGS, 11}, /*IBC-Hash (keyed hash algorithm or MAC) */
RIPEMAC[]   = {INTEL_SEC_ALGS, 12}, /*RIPE-MAC (invented by Bart Preneel) */
DES []      = {INTEL_SEC_ALGS, 13}, /*Data Encryption Standard block cipher */
DESX []     = {INTEL_SEC_ALGS, 14}, /*DESX block cipher  (DES variant from RSA) */
RDES []     = {INTEL_SEC_ALGS, 15}, /*RDES block cipher  (DES variant) */
ALG_3DES_3KEY[] = {INTEL_SEC_ALGS, 16}, /*Triple-DES block cipher  (with 3 keys) */
ALG_3DES_2KEY[] = {INTEL_SEC_ALGS, 17}, /*Triple-DES block cipher  (with 2 keys) */
ALG_3DES_1KEY[] = {INTEL_SEC_ALGS, 18}, /*Triple-DES block cipher  (with 1 key) */
IDEA []     = {INTEL_SEC_ALGS, 19}, /*IDEA block cipher  (invented by Lai and Massey) */
#if 0
RC2[]     OID_RC2CBC
RC5[]     OID_RC5
RC4[]     OID_RC4
#endif
SEAL[]      = {INTEL_SEC_ALGS, 23}, /*SEAL stream cipher  (invented by Rogaway and Coppersmith) */
CAST[]      = {INTEL_SEC_ALGS, 24}, /*CAST block cipher  (invented by Adams and Tavares) */
BLOWFISH [] = {INTEL_SEC_ALGS, 25}, /*BLOWFISH block cipher  (invented by Schneier) */
SKIPJACK[]  = {INTEL_SEC_ALGS, 26}, /*Skipjack block cipher  (developed by NSA) */
LUCIFER []  = {INTEL_SEC_ALGS, 27}, /*Lucifer block cipher  (developed by IBM) */
MADRYGA []  = {INTEL_SEC_ALGS, 28}, /*Madryga block cipher  (invented by Madryga) */
FEAL []     = {INTEL_SEC_ALGS, 29}, /*FEAL block cipher  (invented by Shimizu and Miyaguchi) */
REDOC []    = {INTEL_SEC_ALGS, 30}, /*REDOC 2 block cipher  (invented by Michael Wood) */
REDOC3[]    = {INTEL_SEC_ALGS, 31}, /*REDOC 3 block cipher  (invented by Michael Wood) */
LOKI[]      = {INTEL_SEC_ALGS, 32}, /*LOKI block cipher */
KHUFU []    = {INTEL_SEC_ALGS, 33}, /*KHUFU block cipher  (invented by Ralph Merkle) */
KHAFRE []   = {INTEL_SEC_ALGS, 34}, /*KHAFRE block cipher  (invented by Ralph Merkle) */
MMB[]       = {INTEL_SEC_ALGS, 35}, /*MMB block cipher  (IDEA variant) */
GOST[]      = {INTEL_SEC_ALGS, 36}, /*GOST block cipher  (developed by the former Soviet Union) */
SAFER[]     = {INTEL_SEC_ALGS, 37}, /*SAFER K-64 block cipher  (invented by Massey) */
CRAB[]      = {INTEL_SEC_ALGS, 38}, /*CRAB block cipher  (invented by Kaliski and Robshaw) */
#if 0
RSA[]         OID_RSAEncryption
DSA[]         OID_OIW_DSA           /*Digital Signature Algorithm */
MD5WithRSA[]  OID_MD5WithRSA
MD2WithRSA[]  OID_MD2WithRSA
#endif
ElGamal[]   = {INTEL_SEC_ALGS, 43}, /* ElGamal signature algorithm */
MD2Random[] = {INTEL_SEC_ALGS, 44}, /*MD2-based random numbers */
MD5Random[] = {INTEL_SEC_ALGS, 45}, /*MD5-based random numbers */
SHARandom[] = {INTEL_SEC_ALGS, 46}, /*SHA-based random numbers */
DESRandom[] = {INTEL_SEC_ALGS, 47}, /*DES-based random numbers */
#if 0
SHA1WithRSA[] OID_SHA1WithRSA       /* SHA1/RSA signature algorithm */
RSA_PKCS[]    OID_RSAEncryption     /* RSA as specified in PKCS #1 */
#endif
RSA_ISO9796[] = {INTEL_SEC_ALGS, 49}, /* RSA as specified in ISO 9796 */
RSA_RAW[]   = {INTEL_SEC_ALGS, 50}, /* Raw RSA as assumed in X.509 */
CDMF[]      = {INTEL_SEC_ALGS, 51}, /* CDMF block cipher */
CAST3[]     = {INTEL_SEC_ALGS, 52}, /* Entrust's CAST3 block cipher */
CAST5[]     = {INTEL_SEC_ALGS, 53}, /* Entrust's CAST5 block cipher */
GenericSecret[]     = {INTEL_SEC_ALGS, 54}, /* Generic secret operations */
ConcatBaseAndKey[]  = {INTEL_SEC_ALGS, 55}, /* Concatenate two keys, base key first */
ConcatKeyAndBase[]  = {INTEL_SEC_ALGS, 56}, /* Concatenate two keys, base key last */
ConcatBaseAndData[] = {INTEL_SEC_ALGS, 57}, /* Concatenate base key and random data, key first */
ConcatDataAndBase[] = {INTEL_SEC_ALGS, 58}, /* Concatenate base key and data, data first */
XORBaseAndData[]    = {INTEL_SEC_ALGS, 59}, /* XOR a byte string with the base key */
ExtractFromKey[]    = {INTEL_SEC_ALGS, 60}, /* Extract a key from base key, starting at arbitrary bit position */
SSL3PreMasterGen[]  = {INTEL_SEC_ALGS, 61}, /* Generate a 48 byte SSL 3 pre-master key */
SSL3MasterDerive[]  = {INTEL_SEC_ALGS, 62}, /* Derive an SSL 3 key from a pre-master key */
SSL3KeyAndMacDerive[] = {INTEL_SEC_ALGS, 63}, /* Derive the keys and MACing keys for the SSL cipher suite */
SSL3MD5_MAC[]       = {INTEL_SEC_ALGS, 64}, /* Performs SSL 3 MD5 MACing */
SSL3SHA1_MAC[]      = {INTEL_SEC_ALGS, 65}, /* Performs SSL 3 SHA-1 MACing */
MD5Derive[]         = {INTEL_SEC_ALGS, 66}, /* Generate key by MD5 hashing a base key */
MD2Derive[]         = {INTEL_SEC_ALGS, 67}, /* Generate key by MD2 hashing a base key */
SHA1Derive[]        = {INTEL_SEC_ALGS, 68}, /* Generate key by SHA-1 hashing a base key */
WrapLynks[]         = {INTEL_SEC_ALGS, 69}, /* Spyrus LYNKS DES based wrapping scheme w/checksum */
#if 0
WrapSET_OAEP[]      OID_SETOAEP_RSA
#endif
BATON[]             = {INTEL_SEC_ALGS, 71}, /* Fortezza BATON cipher */
ECDSA[]             = {INTEL_SEC_ALGS, 72}, /* Elliptic Curve DSA */
MAYFLY[]            = {INTEL_SEC_ALGS, 73}, /* Fortezza MAYFLY cipher */
JUNIPER[]           = {INTEL_SEC_ALGS, 74}, /* Fortezza JUNIPER cipher */
FASTHASH[]          = {INTEL_SEC_ALGS, 75}, /* Fortezza FASTHASH */
ALG_3DES[]	        = {INTEL_SEC_ALGS, 76}, /* Generic 3DES */
SSL3MD5[]	        = {INTEL_SEC_ALGS, 77}, /* SSL3MD5 */
SSL3SHA1[]	        = {INTEL_SEC_ALGS, 78}, /* SSL3SHA1 */
FortezzaTimestamp[] = {INTEL_SEC_ALGS, 79}, /* FortezzaTimestamp */
#if 0
SHA1WithDSA[]       OID_OIW_DSAWithSHA1     /* SHA1WithDSA */
#endif
SHA1WithECDSA[]     = {INTEL_SEC_ALGS, 81}, /* SHA1WithECDSA */
DSA_BSAFE[]         = {INTEL_SEC_ALGS, 82},
ECDH[]              = {INTEL_SEC_ALGS, 83}, /* Elliptic Curve DiffieHellman Key Exchange algorithm*/
ECMQV[]             = {INTEL_SEC_ALGS, 84}, /* Elliptic Curve MQV key exchange algorithm*/
PKCS12_SHA1_PBE[]   = {INTEL_SEC_ALGS, 85}, /* PKCS12 SHA-1 Password key derivation algorithm*/
ECNRA[]             = {INTEL_SEC_ALGS, 86}, /* Elliptic Curve Nyberg-Rueppel*/
SHA1WithECNRA[]     = {INTEL_SEC_ALGS, 87}, /* SHA-1 with Elliptic Curve Nyberg-Rueppel*/
ECES[]              = {INTEL_SEC_ALGS, 88}, /* Elliptic Curve Encryption Scheme*/
ECAES[]             = {INTEL_SEC_ALGS, 89}, /* Elliptic Curve Authenticate Encryption Scheme*/
SHA1HMAC[]          = {INTEL_SEC_ALGS, 90}, /* SHA1-MAC*/
FIPS186Random[]     = {INTEL_SEC_ALGS, 91}, /* FIPs86Random*/
ECC[]               = {INTEL_SEC_ALGS, 92}  /* ECC*/
;


static CSSM_OID
    CSSMOID_DH      = {OID_PKCS_3_LENGTH+1, OID_DHKeyAgreement},
    CSSMOID_PH      = {INTEL_SEC_ALGS_LENGTH+1, PH},
    CSSMOID_KEA     = {INTEL_SEC_ALGS_LENGTH+1, KEA},
    CSSMOID_MD2     = {OID_RSA_HASH_LENGTH+1, OID_MD2},
    CSSMOID_MD4     = {OID_RSA_HASH_LENGTH+1, OID_MD4},
    CSSMOID_MD5     = {OID_RSA_HASH_LENGTH+1, OID_MD5},
    CSSMOID_SHA1    = {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_SHA1},
    CSSMOID_NHASH   = {INTEL_SEC_ALGS_LENGTH+1, NHASH},
    CSSMOID_HAVAL   = {INTEL_SEC_ALGS_LENGTH+1, HAVAL},
    CSSMOID_RIPEMD  = {INTEL_SEC_ALGS_LENGTH+1, RIPEMD},
    CSSMOID_IBCHASH = {INTEL_SEC_ALGS_LENGTH+1, IBCHASH},
    CSSMOID_RIPEMAC = {INTEL_SEC_ALGS_LENGTH+1, RIPEMAC},
    CSSMOID_DES     = {INTEL_SEC_ALGS_LENGTH+1, DES},
    CSSMOID_DESX    = {INTEL_SEC_ALGS_LENGTH+1, DESX},
    CSSMOID_RDES    = {INTEL_SEC_ALGS_LENGTH+1, RDES},
    CSSMOID_ALG_3DES_3KEY = {INTEL_SEC_ALGS_LENGTH+1, ALG_3DES_3KEY},
    CSSMOID_ALG_3DES_2KEY = {INTEL_SEC_ALGS_LENGTH+1, ALG_3DES_2KEY},
    CSSMOID_ALG_3DES_1KEY = {INTEL_SEC_ALGS_LENGTH+1, ALG_3DES_1KEY},
    CSSMOID_IDEA    = {INTEL_SEC_ALGS_LENGTH+1, IDEA}, 
    CSSMOID_RC2     = {OID_RSA_ENCRYPT_LENGTH+1, OID_RC2CBC}, 
    CSSMOID_RC5     = {OID_RSA_ENCRYPT_LENGTH+1, OID_RC5}, 
    CSSMOID_RC4     = {OID_RSA_ENCRYPT_LENGTH+1, OID_RC4}, 
    CSSMOID_SEAL    = {INTEL_SEC_ALGS_LENGTH+1, SEAL},
    CSSMOID_CAST    = {INTEL_SEC_ALGS_LENGTH+1, CAST},
    CSSMOID_BLOWFISH= {INTEL_SEC_ALGS_LENGTH+1, BLOWFISH},
    CSSMOID_SKIPJACK= {INTEL_SEC_ALGS_LENGTH+1, SKIPJACK},
    CSSMOID_LUCIFER = {INTEL_SEC_ALGS_LENGTH+1, LUCIFER}, 
    CSSMOID_MADRYGA = {INTEL_SEC_ALGS_LENGTH+1, MADRYGA}, 
    CSSMOID_FEAL    = {INTEL_SEC_ALGS_LENGTH+1, FEAL}, 
    CSSMOID_REDOC   = {INTEL_SEC_ALGS_LENGTH+1, REDOC},
    CSSMOID_REDOC3  = {INTEL_SEC_ALGS_LENGTH+1, REDOC3},
    CSSMOID_LOKI    = {INTEL_SEC_ALGS_LENGTH+1, LOKI}, 
    CSSMOID_KHUFU   = {INTEL_SEC_ALGS_LENGTH+1, KHUFU},
    CSSMOID_KHAFRE  = {INTEL_SEC_ALGS_LENGTH+1, KHAFRE},
    CSSMOID_MMB     = {INTEL_SEC_ALGS_LENGTH+1, MMB}, 
    CSSMOID_GOST    = {INTEL_SEC_ALGS_LENGTH+1, GOST},
    CSSMOID_SAFER   = {INTEL_SEC_ALGS_LENGTH+1, SAFER},
    CSSMOID_CRAB    = {INTEL_SEC_ALGS_LENGTH+1, CRAB}, 
    CSSMOID_RSA     = {OID_PKCS_1_LENGTH+1, OID_RSAEncryption}, 
    CSSMOID_DSA     = {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_DSA}, 
    CSSMOID_MD5WithRSA    = {OID_PKCS_1_LENGTH+1, OID_MD5WithRSA},
    CSSMOID_MD2WithRSA    = {OID_PKCS_1_LENGTH+1, OID_MD2WithRSA},
    CSSMOID_ElGamal       = {INTEL_SEC_ALGS_LENGTH+1, ElGamal}, 
    CSSMOID_MD2Random     = {INTEL_SEC_ALGS_LENGTH+1, MD2Random},
    CSSMOID_MD5Random     = {INTEL_SEC_ALGS_LENGTH+1, MD5Random}, 
    CSSMOID_SHARandom     = {INTEL_SEC_ALGS_LENGTH+1, SHARandom}, 
    CSSMOID_DESRandom     = {INTEL_SEC_ALGS_LENGTH+1, DESRandom}, 
    CSSMOID_SHA1WithRSA   = {OID_PKCS_1_LENGTH+1, OID_SHA1WithRSA}, 
    CSSMOID_RSA_ISO9796   = {INTEL_SEC_ALGS_LENGTH+1, RSA_ISO9796}, 
    CSSMOID_RSA_RAW = {INTEL_SEC_ALGS_LENGTH+1, RSA_RAW}, 
    CSSMOID_CDMF    = {INTEL_SEC_ALGS_LENGTH+1, CDMF}, 
    CSSMOID_CAST3   = {INTEL_SEC_ALGS_LENGTH+1, CAST3}, 
    CSSMOID_CAST5   = {INTEL_SEC_ALGS_LENGTH+1, CAST5}, 
    CSSMOID_GenericSecret       = {INTEL_SEC_ALGS_LENGTH+1, GenericSecret}, 
    CSSMOID_ConcatBaseAndKey    = {INTEL_SEC_ALGS_LENGTH+1, ConcatBaseAndKey}, 
    CSSMOID_ConcatKeyAndBase    = {INTEL_SEC_ALGS_LENGTH+1, ConcatKeyAndBase}, 
    CSSMOID_ConcatBaseAndData   = {INTEL_SEC_ALGS_LENGTH+1, ConcatBaseAndData}, 
    CSSMOID_ConcatDataAndBase   = {INTEL_SEC_ALGS_LENGTH+1, ConcatDataAndBase}, 
    CSSMOID_XORBaseAndData      = {INTEL_SEC_ALGS_LENGTH+1, XORBaseAndData}, 
    CSSMOID_ExtractFromKey      = {INTEL_SEC_ALGS_LENGTH+1, ExtractFromKey}, 
    CSSMOID_SSL3PreMasterGen    = {INTEL_SEC_ALGS_LENGTH+1, SSL3PreMasterGen}, 
    CSSMOID_SSL3MasterDerive    = {INTEL_SEC_ALGS_LENGTH+1, SSL3MasterDerive}, 
    CSSMOID_SSL3KeyAndMacDerive = {INTEL_SEC_ALGS_LENGTH+1, SSL3KeyAndMacDerive}, 
    CSSMOID_SSL3MD5_MAC   = {INTEL_SEC_ALGS_LENGTH+1, SSL3MD5_MAC}, 
    CSSMOID_SSL3SHA1_MAC  = {INTEL_SEC_ALGS_LENGTH+1, SSL3SHA1_MAC}, 
    CSSMOID_MD5_PBE       = {INTEL_SEC_ALGS_LENGTH+1, MD5Derive}, 
    CSSMOID_MD2_PBE       = {INTEL_SEC_ALGS_LENGTH+1, MD2Derive}, 
    CSSMOID_SHA1_PBE      = {INTEL_SEC_ALGS_LENGTH+1, SHA1Derive}, 
    CSSMOID_WrapLynks     = {INTEL_SEC_ALGS_LENGTH+1, WrapLynks}, 
    CSSMOID_WrapSET_OAEP  = {OID_PKCS_1_LENGTH+1, OID_SETOAEP_RSA}, 
    CSSMOID_BATON         = {INTEL_SEC_ALGS_LENGTH+1, BATON}, 
    CSSMOID_ECDSA         = {INTEL_SEC_ALGS_LENGTH+1, ECDSA}, 
    CSSMOID_MAYFLY        = {INTEL_SEC_ALGS_LENGTH+1, MAYFLY}, 
    CSSMOID_JUNIPER       = {INTEL_SEC_ALGS_LENGTH+1, JUNIPER}, 
    CSSMOID_FASTHASH      = {INTEL_SEC_ALGS_LENGTH+1, FASTHASH},
    CSSMOID_ALG_3DES      = {INTEL_SEC_ALGS_LENGTH+1, ALG_3DES},
    CSSMOID_SSL3MD5       = {INTEL_SEC_ALGS_LENGTH+1, SSL3MD5},
    CSSMOID_SSL3SHA1      = {INTEL_SEC_ALGS_LENGTH+1, SSL3SHA1},
    CSSMOID_FortezzaTimestamp   = {INTEL_SEC_ALGS_LENGTH+1, FortezzaTimestamp},
    CSSMOID_SHA1WithDSA   = {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_DSAWithSHA1}, 
    CSSMOID_SHA1WithECDSA = {INTEL_SEC_ALGS_LENGTH+1, SHA1WithECDSA},
    CSSMOID_DSA_BSAFE     = {INTEL_SEC_ALGS_LENGTH+1, DSA_BSAFE},
    CSSMOID_ECDH          = {INTEL_SEC_ALGS_LENGTH+1, ECDH},
    CSSMOID_ECMQV         = {INTEL_SEC_ALGS_LENGTH+1, ECMQV},
    CSSMOID_PKCS12_SHA1_PBE     = {INTEL_SEC_ALGS_LENGTH+1, PKCS12_SHA1_PBE},
    CSSMOID_ECNRA         = {INTEL_SEC_ALGS_LENGTH+1, ECNRA},
    CSSMOID_SHA1WithECNRA = {INTEL_SEC_ALGS_LENGTH+1, SHA1WithECNRA},
    CSSMOID_ECES          = {INTEL_SEC_ALGS_LENGTH+1, ECES},
    CSSMOID_ECAES         = {INTEL_SEC_ALGS_LENGTH+1, ECAES},
    CSSMOID_SHA1HMAC      = {INTEL_SEC_ALGS_LENGTH+1, SHA1HMAC},
    CSSMOID_FIPS186Random = {INTEL_SEC_ALGS_LENGTH+1, FIPS186Random},
    CSSMOID_ECC           = {INTEL_SEC_ALGS_LENGTH+1, ECC},

	CSSMOID_OIW_md4RSA		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_md4RSA},
	CSSMOID_OIW_md5RSA		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_md5RSA},
	CSSMOID_OIW_md4RSA2		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_md4RSA2},
	CSSMOID_OIW_desECB		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desECB},
	CSSMOID_OIW_desCBC		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desCBC},
	CSSMOID_OIW_desOFB		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desOFB},
	CSSMOID_OIW_desCFB		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desCFB},
	CSSMOID_OIW_desMAC		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desMAC},
	CSSMOID_OIW_RSASignature= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_RSASignature},
	CSSMOID_OIW_DSA			= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_DSA},
	CSSMOID_OIW_DSAWithSHA	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_DSAWithSHA},
	CSSMOID_OIW_mdc2RSA		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_mdc2RSA},
	CSSMOID_OIW_shaRSA		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_shaRSA},
	CSSMOID_OIW_dhCommMod	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_dhCommMod},
	CSSMOID_OIW_desEDE		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_desEDE},
	CSSMOID_OIW_SHA			= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_SHA},
	CSSMOID_OIW_mdc2		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_mdc2},
	CSSMOID_OIW_dsaComm		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_dsaComm},
	CSSMOID_OIW_dsaCommSHA	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_dsaCommSHA},
	CSSMOID_OIW_rsaXchg		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_rsaXchg},
	CSSMOID_OIW_keyHashSeal	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_keyHashSeal},
	CSSMOID_OIW_md2RSASign	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_md2RSASign},
	CSSMOID_OIW_md5RSASign	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_md5RSASign},
	CSSMOID_OIW_SHA1		= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_SHA1},
	CSSMOID_OIW_DSAWithSHA1	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_DSAWithSHA1},
	CSSMOID_OIW_dsaCommSHA1	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_dsaCommSHA1},
	CSSMOID_OIW_sha1RSASign	= {OID_OIW_ALGORITHM_LENGTH+1, OID_OIW_sha1RSASign},

    CSSMOID_X9CM_DSA= {OID_X9CM_X9ALGORITHM_LENGTH+1, OID_X9CM_DSA},
	CSSMOID_X9CM_DSAWithSHA1= {OID_X9CM_X9ALGORITHM_LENGTH+1, OID_X9CM_DSAWithSHA1},
    
	CSSMOID_DSALG_RSA		= {OID_DSALG_LENGTH+2, OID_DSALG_RSA},

	CSSMOID_OIWDIR_md2		= {OID_OIWDIR_HASH_LENGTH+1, OID_OIWDIR_md2},
	CSSMOID_OIWDIR_md2RSA	= {OID_OIWDIR_SIGN_LENGTH+1, OID_OIWDIR_md2RSA}
;

CSSM_BOOL cl_IsEqualOid(CSSM_OID_PTR Oid1, CSSM_OID_PTR Oid2);
CSSM_OID_PTR cl_AlgIdToAlgorithmOid(CSSM_HANDLE CSSMHandle, 
                                  CSSM_UPCALLS_PTR MemoryFunctions, 
                                  uint32 alg_int);
int cl_AlgorithmOidToAlgId(CSSM_OID_PTR Oid);

#endif
