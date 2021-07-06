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
 * @(#)$RCSfile: proto.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:44 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     proto.h~23:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file contains prototype declarations of functions
        shared throughout the GSS-API implementation.

============================================================================*/



#ifndef _GSS_PROTO_H_
#define _GSS_PROTO_H_

#include    <gssapi/compat.h>
#include    <gssapi/iso/der.h>
#include    <csfc5/header.h>
#include    <gssapi/gssapi.h>
#include    <gssapi/ext.h>


#if defined(__cplusplus)
	extern "C" {
#endif



/*
 * The private versions of the standard GSS-API Version 2 functions
 */

/*
 * CyberSafe Remark:
 * gss_open() and gss_close() are declared for compatibility with older
 * versions of the CyberSafe Application Security Toolkit.
 *
 */
OM_uint32 CSFAPI
    pCSF_gss_open
        _GSS_PROTO(
            (OM_uint32 FAR * CONST          /* minor status         OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_close   
        _GSS_PROTO(
            (OM_uint32 FAR * CONST          /* minor status         OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_acquire_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,         /* minor_status         OUT      */
             CONST gss_name_t,              /* desired_name         IN, OPT  */
             OM_uint32,                     /* time_req             IN, OPT  */
             CONST gss_OID_set,             /* desired_mechs        IN, OPT  */
             gss_cred_usage_t,              /* cred_usage           IN       */
             gss_cred_id_t FAR * CONST,     /* output_cred_handle   OUT      */
             gss_OID_set FAR * CONST,       /* actual_mechs         OUT, OPT */
             OM_uint32 FAR * CONST          /* time_rec             OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_release_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             gss_cred_id_t FAR * CONST     /* cred_handle           IN, OPT  */
            ));

OM_uint32 CSFAPI
    pCSF_gss_init_sec_context
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             CONST gss_cred_id_t,          /* initiator_cred_handle IN, OPT  */
             gss_ctx_id_t FAR * CONST,     /* context_handle        INOUT    */
             CONST gss_name_t,             /* target_name           IN       */
             CONST gss_OID,                /* mech_type             IN, OPT  */
             OM_uint32,                    /* req_flags             IN       */
             OM_uint32,                    /* time_req              IN, OPT  */
             CONST gss_cb_t,               /* input_chan_bindings   IN, OPT  */
             CONST gss_buffer_t,           /* input_token           IN, OPT  */
             gss_OID FAR * CONST,          /* actual_mech_type      OUT, OPT */
             gss_buffer_t,                 /* output_token,         OUT      */
             OM_uint32 FAR * CONST,        /* ret_flags             OUT, OPT */
             OM_uint32 FAR* CONST          /* time_rec              OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_accept_sec_context  
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,         /* minor_status          OUT      */
             gss_ctx_id_t FAR * CONST,     /* context_handle        INOUT    */
             CONST gss_cred_id_t,          /* acceptor_cred_handle  IN, OPT  */
             CONST gss_buffer_t,           /* input_token_buffer    IN       */
             CONST gss_cb_t,               /* input_chan_bindings   IN, OPT  */
             gss_name_t FAR * CONST,       /* src_name              OUT, OPT */
             gss_OID FAR * CONST,          /* mech_type             OUT, OPT */
             gss_buffer_t,                 /* output_token          OUT      */
             OM_uint32 FAR * CONST,        /* ret_flags             OUT, OPT */
             OM_uint32 FAR * CONST,        /* time_rec              OUT, OPT */
             gss_cred_id_t FAR * CONST     /* delegated_cred_handle OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_process_context_token
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             CONST gss_ctx_id_t,           /* context_handle        IN       */
             CONST gss_buffer_t            /* token_buffer          IN       */
            ));

OM_uint32 CSFAPI
    pCSF_gss_delete_sec_context
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             gss_ctx_id_t FAR * CONST,     /* context_handle        IN       */
             gss_buffer_t                  /* output_token          OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_context_time
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             OM_uint32 FAR * CONST        /* time_rec               OUT      */
            ));
            
OM_uint32 CSFAPI
    pCSF_gss_get_mic
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             gss_qop_t,                   /* qop_req                IN, OPT  */
             CONST gss_buffer_t,          /* message_buffer         IN       */
             gss_buffer_t                 /* message_token          OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_verify_mic  
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             CONST gss_buffer_t,          /* message_buffer         IN       */
             CONST gss_buffer_t,          /* token_buffer           IN       */
             gss_qop_t FAR * CONST        /* qop_state              OUT, OPT */
            ));
                
OM_uint32 CSFAPI
    pCSF_gss_wrap    
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             int,                         /* conf_req_flag          IN       */
             gss_qop_t,                   /* qop_req                IN, OPT  */
             CONST gss_buffer_t,          /* input_message_buffer   IN       */
             int FAR * CONST,             /* conf_state             OUT, OPT */
             gss_buffer_t                 /* output_message_buffer  OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_unwrap
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_ctx_id_t,         /* context                 IN       */
             CONST gss_buffer_t,         /* input_message_buffer    IN       */
             gss_buffer_t,               /* output_message_buffer   OUT      */
             int FAR * CONST,            /* conf_state              OUT, OPT */
             gss_qop_t FAR * CONST       /* qop_state               OUT, OPT */
            ));  

OM_uint32 CSFAPI
    pCSF_gss_display_status
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             OM_uint32,                  /* status_value            IN       */
             int,                        /* status_type             IN       */
             CONST gss_OID,              /* mech_type               IN, OPT  */
             OM_uint32 FAR * CONST,      /* message_context         INOUT    */
             gss_buffer_t                /* status_string           OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_indicate_mechs
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_OID_set FAR * CONST     /* mech_set                OUT      */
            ));
            
OM_uint32 CSFAPI
    pCSF_gss_compare_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_name_t,           /* name1                   IN       */
             CONST gss_name_t,           /* name2                   IN       */
             int FAR * CONST             /* name_equal              OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_display_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_name_t,           /* input_name              IN       */
             gss_buffer_t,               /* output_name_buffer      OUT      */
             gss_OID FAR * CONST         /* output_name_type        OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_import_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_buffer_t,         /* input_name_buffer      IN       */
             CONST gss_OID,              /* input_name_type        IN, OPT  */
             gss_name_t FAR * CONST      /* output_name            OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_export_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_name_t,           /* input_name             IN       */
             gss_buffer_t                /* exported_name          OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_release_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_name_t FAR * CONST      /* input_name             IN       */
            ));
            
OM_uint32 CSFAPI
    pCSF_gss_release_buffer
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_buffer_t                /* buffer                 IN       */
            ));

OM_uint32 CSFAPI
    pCSF_gss_release_oid_set
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_OID_set FAR * CONST     /* set                    IN       */
            ));

OM_uint32 CSFAPI
    pCSF_gss_inquire_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_cred_id_t,        /* cred_handle            IN       */
             gss_name_t FAR * CONST,     /* name                   OUT, OPT */
             OM_uint32 FAR * CONST,      /* lifetime               OUT, OPT */
             gss_cred_usage_t FAR * CONST,/* cred_usage            OUT, OPT */
             gss_OID_set FAR * CONST     /* mechanisms             OUT, OPT */
            ));

OM_uint32 CSFAPI
    pCSF_gss_inquire_context
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_ctx_id_t,        /* context_handle        IN       */
               gss_name_t FAR * CONST,    /* src_name              OUT, OPT */
               gss_name_t FAR * CONST,    /* targ_name             OUT, OPT */
               OM_uint32 FAR * CONST,     /* lifetime_rec          OUT, OPT */
               gss_OID FAR * CONST,       /* mech_type             OUT, OPT */
               OM_uint32 FAR * CONST,     /* ctx_flags             OUT, OPT */
               int FAR * CONST,           /* locally_initiated     OUT, OPT */
               int FAR * CONST            /* open                  OUT, OPT */
              ));

OM_uint32 CSFAPI
    pCSF_gss_wrap_size_limit
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_ctx_id_t,        /* context_handle        IN       */
               int,                       /* conf_req_flag         IN       */
               gss_qop_t,                 /* qop_req               IN       */
               OM_uint32,                 /* req_output_size       IN       */
               OM_uint32 FAR * CONST      /* max_input_size        OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_add_cred
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_cred_id_t,       /* input_cred_handle     IN, OPT  */
               CONST gss_name_t,          /* desired_name          IN, OPT  */
               CONST gss_OID,             /* desired_mech          IN       */
               gss_cred_usage_t,          /* cred_usage            IN       */
               OM_uint32,                 /* initiator_time_req    IN, OPT  */
               OM_uint32,                 /* acceptor_time_req     IN, OPT  */
               gss_cred_id_t FAR * CONST, /* output_cred_handle    OUT, OPT */
               gss_OID_set FAR * CONST,   /* actual_mechs          OUT, OPT */
               OM_uint32 FAR * CONST,     /* initiator_time_rec    OUT, OPT */
               OM_uint32 FAR * CONST      /* acceptor_time_rec     OUT, OPT */
              ));

OM_uint32 CSFAPI
    pCSF_gss_inquire_cred_by_mech
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_cred_id_t,       /* cred_handle           IN, OPT  */
               CONST gss_OID,             /* mech_type             IN       */
               gss_name_t FAR * CONST,    /* name                  OUT, OPT */
               OM_uint32 FAR * CONST,     /* initiator_lifetime    OUT, OPT */
               OM_uint32 FAR * CONST,     /* acceptor_lifetime     OUT, OPT */
               gss_cred_usage_t FAR * CONST   /* cred_usage        OUT, OPT */
              ));

OM_uint32 CSFAPI
    pCSF_gss_export_sec_context
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               gss_ctx_id_t FAR * CONST,  /* context_handle        IN       */
               gss_buffer_t               /* interprocess_token    OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_import_sec_context
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_buffer_t,        /* interprocess_token    IN       */
               gss_ctx_id_t FAR * CONST   /* context_handle        OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_create_empty_oid_set
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               gss_OID_set FAR * CONST    /* oid_set               IN       */
              ));

OM_uint32 CSFAPI
    pCSF_gss_add_oid_set_member
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* member_oid            IN       */
               gss_OID_set FAR * CONST    /* oid_set               IN       */
              ));

OM_uint32 CSFAPI
    pCSF_gss_test_oid_set_member
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* member                IN       */
               CONST gss_OID_set,         /* set                   IN       */
               int FAR * CONST            /* present               OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_inquire_names_for_mech
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* mechanism             IN       */
               gss_OID_set FAR * CONST    /* name_types            OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_inquire_mechs_for_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* input_name            IN       */
               gss_OID_set FAR * CONST    /* mech_types            OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_canonicalize_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* input_name            IN       */
               CONST gss_OID,             /* mech_type             IN       */
               gss_name_t FAR * CONST     /* output_name           OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_duplicate_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* src_name              IN       */
               gss_name_t FAR * CONST     /* dest_name             OUT      */
              ));

OM_uint32 CSFAPI
    pCSF_gss_get_context_options
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
               CONST gss_ctx_id_t,        /* context_handle        IN       */
               OM_uint32 FAR * CONST      /* ctx_flags             OUT, OPT */
            )); 

/*
 * CyberSafe Remark:
 * These two API declarations are included for compatibility with a
 * previous draft of Version 2 of the GSS-API.
 */

OM_uint32 CSFAPI
    pCSF_gss_import_internal_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
             void FAR* CONST,             /* input_name            IN       */
             CONST gss_OID,               /* input_name_type       IN       */
             gss_name_t FAR * CONST       /* output_name           OUT      */
            ));

OM_uint32 CSFAPI
    pCSF_gss_export_internal_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
             CONST gss_name_t,            /* input_name            IN       */
             CONST gss_OID,               /* desired_name_type     IN       */
             void FAR * FAR *             /* output_name           OUT      */
            ));



/*
 * The CyberSafe extension functions to the GSS-API Version 2
 */

int pCSF_gss_enc8bitV_i _GSS_PROTO(( u_char**, i_32 ));
int pCSF_gss_dec8bitV_i _GSS_PROTO(( CONST u_char**, int, i_32* CONST ));
int pCSF_gss_enc8bitV_u _GSS_PROTO(( u_char**, u_32 ));
int pCSF_gss_dec8bitV_u _GSS_PROTO(( CONST u_char**, int, u_32* CONST ));
int pCSF_gss_enc7bitV_i _GSS_PROTO(( u_char**, i_32 ));
int pCSF_gss_dec7bitV_i _GSS_PROTO(( CONST u_char**, i_32* CONST ));
int pCSF_gss_enc7bitV_u _GSS_PROTO(( u_char**, u_32 ));
int pCSF_gss_dec7bitV_u _GSS_PROTO(( CONST u_char**, u_32* CONST ));

int pCSF_gss_decTLF _GSS_PROTO(( CONST u_char**, u_32*, u_32 ));
int pCSF_gss_encTLF _GSS_PROTO(( u_char**, u_32 ));

int pCSF_gss_decTF _GSS_PROTO(( CONST u_char**, PElementClass* CONST, 
                                    PElementForm* CONST, PElementID* CONST ));
int pCSF_gss_encTF _GSS_PROTO(( u_char**, PElementClass,
                                    PElementForm, PElementID ));

int pCSF_gss_decO_i_bc _GSS_PROTO(( CONST u_char**, int, int, i_32* CONST ));
int pCSF_gss_decO_u_bc _GSS_PROTO(( CONST u_char**, int, int, u_32* CONST ));


int pCSF_gss_encO_i _GSS_PROTO(( u_char**, int, i_32 ));
int pCSF_gss_decO_i _GSS_PROTO(( CONST u_char**, int, i_32* CONST ));
int pCSF_gss_encO_u _GSS_PROTO(( u_char**, int, u_32 ));
int pCSF_gss_decO_u _GSS_PROTO(( CONST u_char**, int, u_32* CONST ));

int pCSF_gss_lenS_i _GSS_PROTO(( int, i_32 ));
int pCSF_gss_lenS_u _GSS_PROTO(( int, u_32 ));

int pCSF_gss_lenO_i _GSS_PROTO(( int, i_32 ));
int pCSF_gss_lenO_u _GSS_PROTO(( int, u_32 ));



OM_uint32   pCSF_gss_krb5_form_si_bits _GSS_PROTO(( OM_uint32 ));

char*
    pCSF_gss_buf2str
        _GSS_PROTO(( OM_uint32* CONST, CONST gss_buffer_t ));

csf_sts pCSF_gss_str2buf
    _GSS_PROTO((char * CONST, 
                gss_buffer_t));

OM_uint32
    pCSF_gss_Verify_cb 
        _GSS_PROTO(( csfC5_cksBlock* CONST, gss_cb_t, OM_uint32* CONST ));

OM_uint32
    pCSF_gss_Encode_cb 
        _GSS_PROTO((csfC5_creds, CONST gss_name_t, CONST gss_cb_t,
            csfC5_cksBlock* CONST, gss_cb_t, u_32 ));

OM_uint32
    pCSF_gss_krb5_cc_fetch 
        _GSS_PROTO(( csfC5_prnId*, csfC5_creds* CONST ));

char *
     pCSF_gss_getVStr 
         _GSS_PROTO((CONST char *, csf_sts));


void        
    pCSF_gss_Xform_40bit 
        _GSS_PROTO(( csfC5_data* CONST ));

OM_uint32   
    pCSF_gss_GenKey 
        _GSS_PROTO(( CONST csfC5_crsKBlock* CONST, csfC5_crsKBlock* CONST, csfC5_crsKType ));

OM_uint32
    pCSF_gss_krb5_kt_fetch
        _GSS_PROTO(( CONST csfC5_prnId* CONST, csfC5_ktEntry* CONST ));

OM_uint32
    pCSF_gss_DecodeSeqNum
        _GSS_PROTO(( gss_ctx_id_t, void* CONST, u_char*, u_char* ));
OM_uint32
    pCSF_gss_EncodeSeqNum
        _GSS_PROTO(( gss_ctx_id_t, void* CONST, u_char* ));

/*
    for v1-interoperability
*/ 
OM_uint32 CSFAPI
    pCSF_gss_ComputeCksm
        _GSS_PROTO(
            (gss_ctx_id_t,                /* context id            IN       */
             i_32,                        /* which algorithm       IN       */
             csf_size_t,                  /* message length        IN       */
             CONST u_char*,               /* message               IN       */
             csf_size_t,                  /* prefix length         IN       */
             CONST u_char*,               /* prefix                IN       */
             const int,                   /* use key as the seed   IN       */
             u_char* CONST                /* checksum to output    OUT      */
            ));

/* 
    for v1-interoperability -- this function indicates whether 
    the entire library needs to emit V1 gss tokens.
*/ 
int CSFAPI
    pCSF_gss_EmitV1Tokens
        _GSS_PROTO(
            (void
            ));

OM_uint32
    pCSF_gss_CksmPadMsg
        _GSS_PROTO(( csf_size_t, CONST u_char*, u_char* CONST ));
OM_uint32
    pCSF_gss_Prepend_Oid
        _GSS_PROTO(( gss_ctx_id_t, gss_buffer_t ));

u_char      pCSF_gss_PadChr _GSS_PROTO(( csf_size_t ));
csf_size_t  pCSF_gss_CksmPaddedLen _GSS_PROTO(( csf_size_t ));
csf_size_t  pCSF_gss_SealPaddedLen _GSS_PROTO(( csf_size_t ));

OM_uint32
    pCSF_gss_Default_name
        _GSS_PROTO(( i_32, gss_name_t* CONST ));
OM_uint32
    pCSF_gss_DupName
        _GSS_PROTO(( CONST gss_name_t, gss_name_t* CONST ));

int  pCSF_gss_Xlate_param_seal_qop _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop ) );
int  pCSF_gss_Xlate_param_sign_qop _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop ) );
int  pCSF_gss_Xlate_token_qop _GSS_PROTO(( i_32 theQop ));
int  pCSF_gss_Validate_param_seal_QOP _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop ));
int  pCSF_gss_Validate_param_sign_QOP _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop ));
int  pCSF_gss_Validate_token_seal_QOP _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop ));
int  pCSF_gss_Validate_token_sign_QOP _GSS_PROTO(( CONST gss_ctx_id_t, i_32 theQop  ));

csf_sts
    pCSF_gss_OpenRc
        _GSS_PROTO(( csfC5_rc **, CONST char * ));

csf_sts
    pCSF_gss_AddReplay
        _GSS_PROTO(( gss_ctx_id_t, u_32 ));

OM_uint32
    pCSF_gss_krb5_tgs_fetch
        _GSS_PROTO(( csfC5_prnId *, csfC5_prnId *, csfC5_creds* CONST, CONST OM_uint32 ));

OM_uint32
    pCSF_gss_krb5_tgt_fetch
        _GSS_PROTO(( csfC5_prnId *, csfC5_creds* CONST ));

int
    pCSF_gss_Decode_and_verify_token_header 
        _GSS_PROTO(( CONST gss_buffer_t, CONST u_char**, u_32* CONST, OM_uint32 * CONST ));
int
    pCSF_gss_Encode_token_length
        _GSS_PROTO(( u_char**, u_32 ));

int  pCSF_gss_Validate_buffer _GSS_PROTO(( CONST gss_buffer_t ));
int  pCSF_gss_Validate_usage _GSS_PROTO(( i_32 theCredUsage ));
int  pCSF_gss_Validate_princ _GSS_PROTO(( csfC5_prnId* ));
int  pCSF_gss_Validate_name _GSS_PROTO(( gss_name_t ));
int  pCSF_gss_Validate_cred _GSS_PROTO(( gss_cred_id_t ));
int  pCSF_gss_Validate_ctx _GSS_PROTO(( gss_ctx_id_t ));
int  pCSF_gss_Validate_user _GSS_PROTO(( csf_gss_user_t ));
int  pCSF_gss_Validate_key _GSS_PROTO(( CONST csfC5_crsKBlock* CONST ));

OM_uint32
    pCSFgssGetAcqUserOpts _GSS_PROTO(
       (csf_gss_opts_t,
        gss_OID_set,
        csfC5_data FAR * ,
        csfC5_data FAR * ,
        csfC5_tktFlags FAR * ,
        csfC5_tStamp FAR * ,
        csfC5_tStamp FAR * ,
        csfC5_pauthType FAR * ,
        csf_boolean FAR * ,
        csf_boolean FAR *,
        csf_boolean FAR *,
        csfC5_pkCtx **)
    );


OM_uint32
pCSF_gss_store_forwarded_TGT
    _GSS_PROTO(( 
    OM_uint32 FAR* CONST    gMaj,
    csfC5_cksBlock* CONST   theCksm, 
    csfC5_tkt auth_ticket,  /* Authentication ticket from initiator */
    gss_cred_id_t FAR* CONST    theDelegCred  )); /* 3/24/97: delegated cred */


/* grab the name of a per-thread cred cache, or return NULL */
char* pCSF_gss_getthreadcache( void );



/*
 * Clear a newly allocated security context structure.
 */
void
pCSFgssClearCtx
    _GSS_PROTO((
    gss_ctx_id_t ctx));    /* the security context to clear */


OM_uint32 CSFAPI
    csf_gss_get_authz
        _GSS_PROTO(
            (OM_uint32 FAR* CONST,      /* minor_status         OUT          */
             gss_ctx_id_t,              /* context              IN           */
             csf_gss_authz_t FAR* CONST /* authz                OUT          */
            ));

OM_uint32 CSFAPI
    csf_gss_free_authz
        _GSS_PROTO(
            (OM_uint32 FAR * CONST        gMin,     
             csf_gss_authz_t FAR * CONST  theAuthz
            ));



#if defined(__cplusplus)
	}
#endif



#endif /* _GSS_PROTO_H_ */ 
