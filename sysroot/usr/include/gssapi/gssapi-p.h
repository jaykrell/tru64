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
 * @(#)$RCSfile: gssapi-p.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:41 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     gssapi-p.h~8:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file contains structure and other definitions private to the 
        CyberSafe Security SDK GSS-API implementation.

============================================================================*/



#ifndef _GSSAPI_P_
#define _GSSAPI_P_

#include <gssapi/compat.h>
#include <gssapi/gssapi.h>
#include <gssapi/proto.h>
#include <gssapi/rfctok.h>
#include <gssapi/extern.h>
#include <csfc5/header.h>

/*
 * This structure is used to house a credential. It is this structure
 * that is returned to callers of gss_acquire_cred().
 */
typedef struct _p_gss_cred {
    gss_name_t      theCredName;     /* the credential's name */
    int             theUsage;        /* The credential's usage. */
    csfC5_ktEntry   *theKTEntry;     /* Key table entry for ACCEPT creds */
} p_gss_cred, *p_gss_cred_t;

typedef enum { GSS_ACC_CTX = 1, GSS_INIT_CTX  } ctx_usage;

/*
 * This structure is used to house a context. It is 
 * this structure that is returned to callers of 
 * gss_init_sec_context() and gss_accept_sec_context().
 */
typedef struct _p_gss_ctx {

/* The following declarations are used by both INITIATE and ACCEPT contexts. */
        
    /* Context usage: accepting or initiating. */
    ctx_usage       theUsage;
        
    /* Is the context constructed and ready to use flag. */
    int             isConstructed;
        
    /* The context's flags. */
    OM_uint32       theFlags;

    /* The encryption/decryption session key. */
    csfC5_crsKBlock theKey;
    
    /* The service ticket key. */
    csfC5_crsKBlock theServiceTicketKey;
    
    /* The sequence number of the local and remote end. */
    csfC5_seqNo     mySeqNo, herSeqNo;

    /* The replay cache. It is used to detect message replays. */
    csfC5_rc *      theRC;

    /* The token format, V1 or V2. */
    OM_uint32       theTokenFormat;


    /* The following declarations are for INITIATE contexts. */

    /* The internal name of the target, or "acceptor", of the context. */
    gss_name_t      theTarget;
    

    /* The following declarations are for ACCEPT contexts. */

    /* The source, or "initiator", of the context. */
    gss_name_t      theSource;

    /* The name of the verifier credential. */
    gss_name_t      theVerifierName;

    csf_gss_authz_t theAuthz; /* Authorization data from the AP-REQ. */

} p_gss_ctx, *p_gss_ctx_t;

/*
 * These macros define the values for theTokenFormat.
 */
#define CSF_GSS_TOKEN_FORMAT_V1  1
#define CSF_GSS_TOKEN_FORMAT_V2  2


/*
 * This structure is used to house a user context. It is 
 * this structure that is returned to callers of csf_gss_acq_user().
 */

typedef struct _p_csf_gss_user {

    /* Is the context constructed and ready to use flag. */
    int         isConstructed;

    /* The user's name. */
    gss_name_t  theUserName;

    /* The One Time Password Authentication context associated with user. */
    csfC5_OTPctx    *OTPctx;

} p_csf_gss_user, *p_csf_gss_user_t;

/*
 * Public key context returned by csf_gss_acq_pk_context(), supports PK-INIT
 */
typedef struct _p_csf_gss_pk_ctx {

    csfC5_pkCtx *pkCtx; /* public key context wrapped for customers' eyes */

} p_csf_gss_pk_ctx, *p_csf_gss_pk_ctx_t;


#endif /* _GSSAPI_P_ */ 
