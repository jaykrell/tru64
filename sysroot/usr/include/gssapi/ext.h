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
 * @(#)$RCSfile: ext.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:33 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     ext.h~15:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This header file provides declarations and prototypes for 
        the CyberSafe GSS-API extensions.

============================================================================*/



#ifndef _GSS_EXT_H_
#define _GSS_EXT_H_



/*============================================================================
    Dependent includes
============================================================================*/
#include    <gssapi/compat.h>
#include    <gssapi/gssapi.h>



/*============================================================================
    Public types and definitions
============================================================================*/
typedef struct csf_gss_user_desc { void FAR* theUser; } FAR * csf_gss_user_t; 
typedef struct csf_gss_pk_ctx_desc { void FAR* thePkCtx; } FAR * csf_gss_pk_ctx_t;

#define CSF_GSS_C_NO_USER            ((csf_gss_user_t) 0)
#define CSF_GSS_C_NULL_USER          ((csf_gss_user_t) 0)
#define CSF_GSS_C_NO_PK_CTX          ((csf_gss_pk_ctx_t) 0)
#define CSF_GSS_C_NULL_PK_CTX        ((csf_gss_pk_ctx_t) 0)

/*
 * These define the states that 
 * are returned by csf_gss_acq_user().
 */
#define CSF_GSS_C_USER_STATE_NULL                    0
#define CSF_GSS_C_USER_STATE_PASSWORD_NOECHO         1
#define CSF_GSS_C_USER_STATE_CHALLENGE_ECHO          2
#define CSF_GSS_C_USER_STATE_OTP_ECHO                3
#define CSF_GSS_C_USER_STATE_PASSWORD_ECHO           4
#define CSF_GSS_C_USER_STATE_CHALLENGE_NOECHO        5
#define CSF_GSS_C_USER_STATE_OTP_NOECHO              6

/*
 * Value to use for csf_gss_acq_user() options parameter to
 * indicate no options are being specified.
 */
#define CSF_GSS_C_ACQ_USER_OPT_NONE             (csf_gss_opts_t) NULL
#define CSF_GSS_C_ACQ_PK_CONTEXT_OPT_NONE       (csf_gss_opts_t) NULL


/*
 * Values for option identifiers, a bit flag field, in csf_gss_acq_user()
 * Currently, the identifier field indicates only a single option at a time.
 */
#define CSF_GSS_C_ACQ_USER_OPT_LIFETIME                 0x00000001
#define CSF_GSS_C_ACQ_USER_OPT_RENEWABLE                0x00000002
#define CSF_GSS_C_ACQ_USER_OPT_CCNAME                   0x00000004
#define CSF_GSS_C_ACQ_USER_OPT_KTNAME                   0x00000008
#define CSF_GSS_C_ACQ_USER_OPT_SVCKEY                   0x00000010
#define CSF_GSS_C_ACQ_USER_OPT_FORWARDABLE              0x00000020
#define CSF_GSS_C_ACQ_USER_OPT_PROXIABLE                0x00000040
#define CSF_GSS_C_ACQ_USER_OPT_NOPREAUTH                0x00000080
#define CSF_GSS_C_ACQ_USER_OPT_ALWAYS_FETCH             0x00000100
#define CSF_GSS_C_ACQ_USER_OPT_PKINIT                   0x00000200
#define CSF_GSS_C_ACQ_USER_OPT_DES3                     0x00000400

/*
 * This name type represents the X500 principal name format of
 * <name>@<realm>, where each of <name> and <realm> are string
 * format represenations of X500 distinguished names, and this
 * encoding is accomplished via RFC 1779.  This name type is in
 * support of PK-INIT.
 */
#define CSF_GSS_KRB5_NT_X500_PRINCIPAL_NAME (csf_gss_get_OidAddress(10))

/*
 * Definition for the options structure for csf_gss_acq_user
 */
typedef struct csf_gss_mech_opt_desc_struct {
    gss_OID     mechOID;
    OM_uint32   id;
    void        FAR *val;
} csf_gss_mech_opt_desc, FAR *csf_gss_opts_t;

/*
 * Public key information for each user.  This includes the principal name
 * of the subject, key tags for identification of multiple key pairs,
 * the X509 key ID, perhaps the entire PK certificate, and room for
 * extensions for the future.  An array of these structures is returned
 * by csf_gss_acq_pk_ctx(), so as to allow the application to present
 * information to the user and allow that user to choose among multiple
 * public key credentials to use in PK-INIT.
 */
typedef struct _csf_gss_pk_subj_info_desc {
    /*
     * Subject's X500 name in form <name>@<realm>, where each of these
     * components is in the textual form represented by RFC 1779
     */
    gss_buffer_desc X500princName;
    gss_buffer_desc keyTag;    /* label uniquely identifying key pair */
    gss_buffer_desc X500keyID; /* X509 key ID field, part of PK cert */
    gss_buffer_desc pkCert;    /* public key certificate of the subject */
    void * extensions;         /* other info, e.g. altSubjectName */
} csf_gss_pk_subj_info_desc, *csf_gss_pk_subj_info_t;

    /* The following are flag definitions passed 
        to csf_gss_release_user(). 
        
        The purge flag indicates that mechanisms should 
        perform extensive clean up. For example, Kerberos 
        credential caches and replay caches would be 
        deleted from the file store whereas they normally 
        would not. */
#define CSF_GSS_C_PURGE_FLAG    1

    /* The following are flag definitions passed to gss_init_sec_context
       and returned by gss_init_sec_context, gss_accept_sec_context, and
       gss_inquire_context. */
#define CSF_GSS_C_DES_FLAG      0x10000000
#define CSF_GSS_C_DES3_FLAG     0x20000000

    /* The following definition is a QOP that selects DES-40 
        confidentiality, if provided in the version of the 
        toolkit you are using. DES-40 is the default QOP in 
        the international toolkit. */
#define CSF_GSS_KRB5_CONF_C_QOP_DES40       5340

    /* The following are QOP definitions for DES3. */
#define CSF_GSS_KRB5_INTEG_C_QOP_DES3_MD5   5341
#define CSF_GSS_KRB5_CONF_C_QOP_DES3        5342

typedef struct csf_gss_authz_desc { 
    OM_uint32   num_authz;              /* Number of array elements 
                                            returned in authz. */

    struct _authz {
        OM_sint32       type;           /* Authorization data type */
        gss_buffer_desc data;           /* Authorization data. */
    } authz[1];                         /* Array length is 
                                            defined by num_authz */
} csf_gss_authz, FAR * csf_gss_authz_t; 

#define CSF_GSS_C_NULL_AUTHZ    ( (csf_gss_authz_t) NULL )



/*============================================================================
    Public prototypes
============================================================================*/
#   if defined(__cplusplus)
        extern "C" {
#   endif



OM_uint32 CSFAPI
    csf_gss_acq_user
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,  /* minor_status             OUT          */
             CONST gss_name_t,      /* user_name                IN,OPTIONAL  */
             CONST gss_OID_set,     /* desired_mechs            IN,OPTIONAL  */
             CONST csf_gss_opts_t,    /* options                    IN,OPTIONAL     */    
             CONST gss_buffer_t,    /* user_response            IN           */
             csf_gss_user_t FAR* CONST,/* user_id                  IN/OUT    */
             gss_buffer_t,          /* prompt                   OUT          */
             gss_buffer_t,          /* label                    OUT          */
             i_32 FAR* CONST,        /* prompting_state          OUT          */
             gss_OID FAR* CONST,    /* prompting_mech           OUT          */
             time_t FAR * CONST     /* password expiration time OUT          */
            ));

OM_uint32 CSFAPI 
    csf_gss_release_user
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,     /* minor_status          OUT          */
             csf_gss_user_t FAR* CONST,/* user_id               IN           */
             OM_uint32                 /* flags                 IN           */
            ));

OM_uint32 CSFAPI 
    csf_gss_inq_user
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,  /* minor_status             OUT          */
             csf_gss_user_t,        /* user_id                  IN           */
             gss_OID_set FAR* CONST,/* actual_mechs             OUT,OPTIONAL */
             gss_name_t FAR* CONST  /* user_name                OUT,OPTIONAL */
            )); 

OM_uint32 CSFAPI
    csf_gss_krb5_cpw
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,  /* minor_status             OUT          */
             gss_name_t,            /* targ_name                IN           */
             CONST gss_buffer_t,    /* old_pwd                  IN           */
             CONST gss_buffer_t     /* new_pwd                  IN           */
            )); 
    
OM_uint32 CSFAPI
    csf_gss_renew_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,  /* minor_status             OUT          */
             gss_cred_id_t,         /* cred                     IN, OPTIONAL */
             CONST gss_OID,         /* desired_mech             IN, OPTIONAL */
             OM_uint32,             /* time_req                 IN           */
             OM_uint32              /* flags                    IN           */
            )); 

OM_uint32 CSFAPI
    csf_gss_acq_pk_context 
        _GSS_PROTO(
            (OM_uint32 FAR * CONST               minor_status,    /* out */
             CONST char FAR * CONST              password,        /* in */
             CONST char FAR * CONST              pk_policy_file,  /* in */
             CONST csf_gss_opts_t                opts,            /* in, opt */
             csf_gss_pk_ctx_t FAR * CONST        pk_context       /* out */
            )); 

OM_uint32 CSFAPI
    csf_gss_release_pk_context 
        _GSS_PROTO(
            (OM_uint32 FAR * CONST               minor_status,    /* out */
             csf_gss_pk_ctx_t * CONST            pk_context       /* in */
            )); 

OM_uint32 CSFAPI
    csf_gss_detect_smartcard 
        _GSS_PROTO(
            (OM_uint32 FAR * CONST               minor_status,    /* out */
             OM_uint32 FAR * CONST               smartcard_found  /* out */
            )); 

OM_uint32 CSFAPI
    csf_gss_get_X500_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST               minor_status,    /* out */
             csf_gss_pk_ctx_t                    pk_context,      /* in */
             gss_buffer_t FAR * FAR * CONST      X500name         /* out */
            )); 

OM_uint32 CSFAPI
    csf_gss_release_X500_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST               minor_status,    /* out */
             gss_buffer_t FAR * FAR * CONST      X500name         /* inout */
            )); 

OM_uint32 CSFAPI
    csf_gss_get_context_options
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
               CONST gss_ctx_id_t,        /* context_handle        IN       */
               OM_uint32 FAR * CONST      /* ctx_flags             OUT, OPT */
            )); 

gss_OID CSFAPI 
    csf_gss_get_OidAddress
        _GSS_PROTO(
            ( int index 
            ));

gss_OID_set CSFAPI 
    csf_gss_get_RfcOidSet
        _GSS_PROTO( 
            ( void 
            ));



#   if defined(__cplusplus)
        }
#   endif



#endif /* _GSS_EXT_H_ */
