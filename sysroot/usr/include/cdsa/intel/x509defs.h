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
 * @(#)$RCSfile: x509defs.h,v $ $Revision: 1.1.2.7 $ (DEC) $Date: 2001/11/02 21:48:08 $
 */
/*-----------------------------------------------------------------------
 * File: X509DEFS.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */
 
#ifndef _X509DEFS_H
#define _X509DEFS_H
#include "cssm.h"

/*
    CSSM_BER_TAG
    This data type defines CSSM programmatic names for the standard DER tags found 
    in DER-encoded values. These tag values are included in a structure containing
    a certificate field value when the DER type for that field is ambiguous.
*/
typedef uint8 CSSM_BER_TAG;

#define BER_TAG_UNKNOWN 0
#define BER_TAG_BOOLEAN 1
#define BER_TAG_INTEGER 2
#define BER_TAG_BIT_STRING 3
#define BER_TAG_OCTET_STRING 4
#define BER_TAG_NULL 5
#define BER_TAG_OID 6
#define BER_TAG_OBJECT_DESCRIPTOR 7
#define BER_TAG_EXTERNAL 8
#define BER_TAG_REAL 9
#define BER_TAG_ENUMERATED 10
/* 12 to 15 are reserved for future versions of the recommendation */
#define BER_TAG_PKIX_UTF8_STRING 12
#define BER_TAG_SEQUENCE 16
#define BER_TAG_SET 17
#define BER_TAG_NUMERIC_STRING 18
#define BER_TAG_PRINTABLE_STRING 19
#define BER_TAG_T61_STRING 20
#define BER_TAG_TELETEX_STRING BER_TAG_T61_STRING
#define BER_TAG_VIDEOTEX_STRING 21
#define BER_TAG_IA5_STRING 22
#define BER_TAG_UTC_TIME 23
#define BER_TAG_GENERALIZED_TIME 24
#define BER_TAG_GRAPHIC_STRING 25
#define BER_TAG_ISO646_STRING 26
#define BER_TAG_GENERAL_STRING 27
#define BER_TAG_VISIBLE_STRING BER_TAG_ISO646_STRING
/* 28 - are reserved for future versions of the recommendation */
#define BER_TAG_PKIX_UNIVERSAL_STRING 28
#define BER_TAG_PKIX_BMP_STRING 30


/*
    CSSM_X509_ALGORITHM_IDENTIFIER
    This structure holds an object identifier naming a cryptographic algorithm and an optional set of
    parameters to be used as input to that algorithm.
*/
typedef struct cssm_x509_algorithm_identifier 
{
    CSSM_OID algorithm;
    CSSM_DATA parameters;
} CSSM_X509_ALGORITHM_IDENTIFIER, *CSSM_X509_ALGORITHM_IDENTIFIER_PTR;

/*
    CSSM_X509_TYPE_VALUE_PAIR
    This structure contain an type-value pair.
*/
typedef struct cssm_x509_type_value_pair 
{
    CSSM_OID type;
    CSSM_BER_TAG valueType; /* The Tag to be used when this value is BER encoded */
    CSSM_DATA value;
} CSSM_X509_TYPE_VALUE_PAIR, *CSSM_X509_TYPE_VALUE_PAIR_PTR;


/*
    CSSM_X509_RDN
    This structure contains a Relative Distinguished Name composed of an ordered set of type-value
    pairs.
*/
typedef struct cssm_x509_rdn 
{
    uint32 numberOfPairs;
    CSSM_X509_TYPE_VALUE_PAIR_PTR AttributeTypeAndValue;
} CSSM_X509_RDN, *CSSM_X509_RDN_PTR;

/*
    CSSM_X509_NAME
    This structure contains a set of Relative Distinguished Names.
*/
typedef struct cssm_x509_name 
{
    uint32 numberOfRDNs;
    CSSM_X509_RDN_PTR RelativeDistinguishedName;
} CSSM_X509_NAME, *CSSM_X509_NAME_PTR;


/*
    CSSM_X509_SUBJECT_PUBLIC_KEY_INFO
    This structure contains the public key and the description of the verification algorithm
    appropriate for use with this key.
*/
typedef struct cssm_x509_subject_public_key_info 
{
    CSSM_X509_ALGORITHM_IDENTIFIER algorithm;
    CSSM_DATA subjectPublicKey;
} CSSM_X509_SUBJECT_PUBLIC_KEY_INFO, *CSSM_X509_SUBJECT_PUBLIC_KEY_INFO_PTR;


/*
    CSSM_X509_TIME
    Time is represented as a string according to the definitions of GeneralizedTime and UTCTime
    defined in RFC 2459.
*/
typedef struct cssm_x509_time 
{
    CSSM_BER_TAG timeType;
    CSSM_DATA time;
} CSSM_X509_TIME, *CSSM_X509_TIME_PTR;

/*
    CSSM_X509_VALIDITY
*/
typedef struct x509_validity 
{
    CSSM_X509_TIME notBefore;
    CSSM_X509_TIME notAfter;
} CSSM_X509_VALIDITY, *CSSM_X509_VALIDITY_PTR;


/*
    CSSM_X509_OPTION
    This data type is used to indicate the presence or absence of an optional field value.
*/
#define CSSM_X509_OPTION_PRESENT CSSM_TRUE
#define CSSM_X509_OPTION_NOT_PRESENT CSSM_FALSE
typedef CSSM_BOOL CSSM_X509_OPTION;

/*
    CSSM_X509EXT_BASICCONSTRAINTS
*/
typedef struct cssm_x509ext_basicConstraints 
{
    CSSM_BOOL cA;
    CSSM_X509_OPTION pathLenConstraintPresent;
    uint32 pathLenConstraint;
} CSSM_X509EXT_BASICCONSTRAINTS, *CSSM_X509EXT_BASICCONSTRAINTS_PTR;


/*
    CSSM_X509EXT_DATA_FORMAT
    This list defines the valid formats for a certificate extension.
*/
typedef enum extension_data_format 
{
    CSSM_X509_DATAFORMAT_ENCODED = 0,
    CSSM_X509_DATAFORMAT_PARSED,
    CSSM_X509_DATAFORMAT_PAIR
} CSSM_X509EXT_DATA_FORMAT;


/*
    CSSM_X509EXT_TAGandVALUE
    This structure contains a BER/DER encoded extension value and the type of that value.
*/
typedef struct cssm_x509_extensionTagAndValue 
{
    CSSM_BER_TAG type;
    CSSM_DATA value;
} CSSM_X509EXT_TAGandVALUE, *CSSM_X509EXT_TAGandVALUE_PTR;


/*
    CSSM_X509EXT_PAIR
    This structure aggregates two extension representations: a tag and value, and a parsed X509
    extension representation.
*/
typedef struct cssm_x509ext_pair 
{
    CSSM_X509EXT_TAGandVALUE tagAndValue;
    void *parsedValue;
} CSSM_X509EXT_PAIR, *CSSM_X509EXT_PAIR_PTR;


/*
    CSSM_X509_EXTENSION
    This structure contains a complete certificate extension.
*/
typedef struct cssm_x509_extension 
{
    CSSM_OID extnId;
    CSSM_BOOL critical;
    CSSM_X509EXT_DATA_FORMAT format;
    union cssm_x509ext_value 
    {
        CSSM_X509EXT_TAGandVALUE *tagAndValue;
        void *parsedValue;
        CSSM_X509EXT_PAIR *valuePair;
    } value;
    CSSM_DATA BERvalue;
} CSSM_X509_EXTENSION, *CSSM_X509_EXTENSION_PTR;


/*
    CSSM_X509_EXTENSIONS
    This structure contains the set of all certificate extensions contained in a certificate.
*/
typedef struct cssm_x509_extensions 
{
    uint32 numberOfExtensions;
    CSSM_X509_EXTENSION_PTR extensions;
} CSSM_X509_EXTENSIONS, *CSSM_X509_EXTENSIONS_PTR;


/*
    CSSM_X509_TBS_CERTIFICATE
    This structure contains a complete X.509 certificate.
*/
typedef struct cssm_x509_tbs_certificate 
{
    CSSM_DATA version;
    CSSM_DATA serialNumber;
    CSSM_X509_ALGORITHM_IDENTIFIER signature;
    CSSM_X509_NAME issuer;
    CSSM_X509_VALIDITY validity;
    CSSM_X509_NAME subject;
    CSSM_X509_SUBJECT_PUBLIC_KEY_INFO subjectPublicKeyInfo;
    CSSM_DATA issuerUniqueIdentifier;
    CSSM_DATA subjectUniqueIdentifier;
    CSSM_X509_EXTENSIONS extensions;
} CSSM_X509_TBS_CERTIFICATE, *CSSM_X509_TBS_CERTIFICATE_PTR;


/*
    CSSM_X509_SIGNATURE
    This structure contains a cryptographic digital signature.
*/
typedef struct cssm_x509_signature 
{
    CSSM_X509_ALGORITHM_IDENTIFIER algorithmIdentifier;
    CSSM_DATA encrypted;
} CSSM_X509_SIGNATURE, *CSSM_X509_SIGNATURE_PTR;


/*
    CSSM_X509_SIGNED_CERTIFICATE
    This structure associates a set of decoded certificate values with the signature covering those
    values.
*/
typedef struct cssm_x509_signed_certificate 
{
    CSSM_X509_TBS_CERTIFICATE certificate;
    CSSM_X509_SIGNATURE signature;
} CSSM_X509_SIGNED_CERTIFICATE, *CSSM_X509_SIGNED_CERTIFICATE_PTR;


/*
    CSSM_X509EXT_POLICYQUALIFIERINFO
*/
typedef struct cssm_x509ext_policyQualifierInfo 
{
    CSSM_OID policyQualifierId;
    CSSM_DATA value;
} CSSM_X509EXT_POLICYQUALIFIERINFO, *CSSM_X509EXT_POLICYQUALIFIERINFO_PTR;


/*
    CSSM_X509EXT_POLICYQUALIFIERS
*/
typedef struct cssm_x509ext_policyQualifiers 
{
    uint32 numberOfPolicyQualifiers;
    CSSM_X509EXT_POLICYQUALIFIERINFO *policyQualifier;
} CSSM_X509EXT_POLICYQUALIFIERS, *CSSM_X509EXT_POLICYQUALIFIERS_PTR;


/*
    CSSM_X509EXT_POLICYINFO
*/
typedef struct cssm_x509ext_policyInfo 
{
    CSSM_OID policyIdentifier;
    CSSM_X509EXT_POLICYQUALIFIERS policyQualifiers;
} CSSM_X509EXT_POLICYINFO, *CSSM_X509EXT_POLICYINFO_PTR;


/* C Language Data Structures for X.509 CRLs */

/*
    CSSM_X509_REVOKED_CERT_ENTRY
    This structure contains a single entry in a certificate revocation list.
    (x509V2 entry in the CRL revokedCertificates sequence)
*/
typedef struct cssm_x509_revoked_cert_entry {
    CSSM_DATA certificateSerialNumber;
    CSSM_X509_TIME revocationDate;
    CSSM_X509_EXTENSIONS extensions;
} CSSM_X509_REVOKED_CERT_ENTRY, *CSSM_X509_REVOKED_CERT_ENTRY_PTR;

/*
    CSSM_X509_REVOKED_CERT_LIST
    This structure defines an unordered linked list containing certificate revocation nodes. This
    structure aggregates the records describing revoked certificates.
*/
typedef struct cssm_x509_revoked_cert_list 
{
    uint32 numberOfRevokedCertEntries;
    CSSM_X509_REVOKED_CERT_ENTRY_PTR revokedCertEntry;
} CSSM_X509_REVOKED_CERT_LIST, *CSSM_X509_REVOKED_CERT_LIST_PTR;

/*
    CSSM_X509_TBS_CERTLIST
    This structure defines a complete, but unsigned certificate revocation list. This includes the
    header information describing the CRL, and the list of CRL entries identifying the revoked
    certificates and describing the circumstances of the revocation operation.
    (x509v2 Certificate Revocation List (CRL) (unsigned) structure)
*/
typedef struct cssm_x509_tbs_certlist 
{
    CSSM_DATA version;
    CSSM_X509_ALGORITHM_IDENTIFIER signature;
    CSSM_X509_NAME issuer;
    CSSM_X509_TIME thisUpdate;
    CSSM_X509_TIME nextUpdate;
    CSSM_X509_REVOKED_CERT_LIST_PTR revokedCertificates;
    CSSM_X509_EXTENSIONS extensions;
} CSSM_X509_TBS_CERTLIST, *CSSM_X509_TBS_CERTLIST_PTR;


/*
    CSSM_X509_SIGNED_CRL
    This structure aggregates an unsigned CRL and a signature over that CRL.
*/
typedef struct cssm_x509_signed_crl 
{
    CSSM_X509_TBS_CERTLIST tbsCertList;
    CSSM_X509_SIGNATURE signature;
} CSSM_X509_SIGNED_CRL, *CSSM_X509_SIGNED_CRL_PTR;




/* BEGIN Intel specific*/
#define UTC_TIME_STRLEN 13
#define GENERALIZED_TIME_STRLEN 15

#define DER_TAG_UNKNOWN	     0x00
#define DER_TAG_BOOLEAN      0x01
#define DER_TAG_INTEGER      0x02
#define DER_TAG_BIT_STRING   0x03
#define DER_TAG_OCTET_STRING 0x04
#define DER_TAG_NULL         0x05
#define DER_TAG_OID          0x06

#define DER_TAG_SEQUENCE     0x10
#define DER_TAG_SET          0x11

#define DER_TAG_PRINTABLE_STRING 0x13
#define DER_TAG_T61_STRING   0x14

#define DER_TAG_IA5_STRING   0x16
#define DER_TAG_UTC_TIME     0x17
#define DER_TAG_GENERALIZED_TIME 0x18

typedef uint8 CL_DER_TAG_TYPE;

/* x509 private certificate and CRL extension structures */


/* A Node of the CRL revoked cert list */
/* The "revokedCertEntry" field should always be present, but other data fields may be changed
   depending on the type of list being implemented.                                           */
/* Right now an unordered singly-linked list */
typedef struct x509_revoked_list_node {
    CSSM_X509_REVOKED_CERT_ENTRY_PTR     revokedCertEntry;
    struct x509_revoked_list_node   *nextNode;
} X509_REVOKED_LIST_NODE, *X509_REVOKED_LIST_NODE_PTR;


/* The CRL list of revoked certs. */
/* Should always have the name "X509_REVOKED_CERT_LIST", but the underlying type may be
   changed depending on the type of list being implemented.                             */
/* Right now an unordered singly-linked list */
typedef struct x509_revoked_cert_list {
    X509_REVOKED_LIST_NODE   *head;         /* First node in the list */
    X509_REVOKED_LIST_NODE   *tail;         /* Last node in the list */
    uint32                   numNodes;      /* Number of nodes - access via x509_cl_RevokedListNumNodes */
} X509_REVOKED_CERT_LIST, *X509_REVOKED_CERT_LIST_PTR;

typedef struct x509_tbs_certlist 
{
    CSSM_DATA version;
    CSSM_X509_ALGORITHM_IDENTIFIER signature;
    CSSM_X509_NAME issuer;
    CSSM_X509_TIME thisUpdate;
    CSSM_X509_TIME nextUpdate;
    X509_REVOKED_CERT_LIST_PTR revokedCertificates;
    CSSM_X509_EXTENSIONS extensions;
} X509_TBS_CERTLIST, *X509_TBS_CERTLIST_PTR;


/*
    X509_SIGNED_CRL
    This structure aggregates an unsigned CRL and a signature over that CRL.
*/
typedef struct x509_signed_crl 
{
    X509_TBS_CERTLIST tbsCertList;
    CSSM_X509_SIGNATURE signature;
} X509_SIGNED_CRL, *X509_SIGNED_CRL_PTR;


/* UseExemption private extension */
typedef struct x509ext_private_useExemptions {
	char			*builtins;
	uint32			numberOfOtherUSEETags;
	CSSM_OID_PTR	otherUSEETags;
} CSSM_X509EXT_PRIVATE_USEEXEMPTIONS, *X509EXT_PRIVATE_USEEXEMPTIONS_PTR;
/* UseExemption private extension end */



typedef struct x501_any_value {
    CL_DER_TAG_TYPE  valueTag;   /* The Tag to be used when this value is BER encoded */
    CSSM_DATA        value;
} CSSM_X501_ANY_VALUE, *CSSM_X501_ANY_VALUE_PTR;

typedef struct x501_attribute {
    CSSM_OID            type;
    uint32              numberOfValues;
    CSSM_X501_ANY_VALUE_PTR  values;
} CSSM_X501_ATTRIBUTE, *CSSM_X501_ATTRIBUTE_PTR;

typedef struct x501_attributes {
    uint32              numberOfAttributes;
    CSSM_X501_ATTRIBUTE_PTR  attributes;
} CSSM_X501_ATTRIBUTES, *CSSM_X501_ATTRIBUTES_PTR;


typedef CSSM_X509_ALGORITHM_IDENTIFIER_PTR cssm_PKSC7_CONTENT_INFO_PTR;
typedef CSSM_X509_ALGORITHM_IDENTIFIER     cssm_PKSC7_CONTENT_INFO;

typedef struct cssm_pkcs7_issuer_and_serial_number {
    CSSM_X509_NAME issuer;
    CSSM_DATA serialNumber;
} cssm_PKCS7_ISSUER_AND_SERIAL_NUMBER, *cssm_PKCS7_ISSUER_AND_SERIAL_NUMBER_PTR;

typedef struct cssm_pkcs7_signer_info {
    CSSM_DATA                      version;              /* signer info version, default =1, type DER Integer */
    cssm_PKCS7_ISSUER_AND_SERIAL_NUMBER issuerAndSerialNumber;
    CSSM_X509_ALGORITHM_IDENTIFIER      digestAlgId;
    CSSM_X501_ATTRIBUTES                authenticatedAttrs;   /* Set, Implicit, Optional, CtxTag = 0 */
    CSSM_X509_ALGORITHM_IDENTIFIER      digestEncryptionAlgId;
    CSSM_DATA                      encryptedDigest;      /* Octet string */
    CSSM_X501_ATTRIBUTES                unauthenticatedAttrs; /* Set, Implicit, Optional, CtxTag = 0 */
} cssm_PKCS7_SIGNER_INFO, *cssm_PKCS7_SIGNER_INFO_PTR;

typedef struct cssm_pkcs7_signed_data {
    CSSM_DATA                     version;      /* pkcs#7 version, default =1, type DER Integer */
    uint32                        numberOfDigestAlgIds;
    CSSM_X509_ALGORITHM_IDENTIFIER_PTR digestAlgIds; /* Set */
    cssm_PKSC7_CONTENT_INFO            contentInfo;
    CSSM_CERTGROUP                certificates; /* Set, Implicit, Optional, CtxTag = 0 */
    CSSM_CRLGROUP                 crls;         /* Set, Implicit, Optional, CtxTag = 1 */
    uint32                        numberOfSignerInfos;
    cssm_PKCS7_SIGNER_INFO_PTR         signerInfos;  /* Set */
} cssm_PKCS7_SIGNED_DATA, *cssm_PKCS7_SIGNED_DATA_PTR;

/* END Intel specific*/

#endif /* of _X509DEFS_H */
