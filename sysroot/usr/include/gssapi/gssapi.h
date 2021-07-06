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
 * @(#)$RCSfile: gssapi.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:40 $
 */
/*============================================================================

(( Copyright (C) 1994-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     gssapi.h~13:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

		This header file is the C Bindings interface to CyberSafe's 
		GSS-API implementation. The definitions in this file comply 
		with the Generic Security Service API Version 2 : C-bindings
		Internet Draft document.  Corrections have been made and 
		extensions added. 

		One extension is the addition of the keywords CSFAPI, 
		_GSS_PROTO, CONST, and FAR to function prototypes. The keywords 
		CSFAPI and FAR are applicable only in the Windows environment. 
		In that environment CSFAPI is expanded to the compiler 
		'stdcall' and FAR is expanded to 'far'. In other environments 
		the keywords CSFAPI and FAR are empty.

		The keyword _GSS_PROTO is a macro that, depending upon whether 
		the compiler in use supports function prototypes, determines 
		whether function's parameter list are included as part of their 
		prototype declarations. Similarly, if the compiler supports the 
		const keyword then CONST is expanded to 'const'.
============================================================================*/



#ifndef _GSSAPI_H_
#define _GSSAPI_H_

/*
 * First, include stddef.h to get size_t defined.
 * #include <stddef.h>
 *
 * CyberSafe Remark:
 * For purposes of heterogeneous platform support, this is conditionally
 * included from compat.h.
 */

/*
 * If the platform supports the xom.h header file, it should be
 * included here.
 * #include <xom.h>
 *
 * CyberSafe Remark:
 * Few platforms supply this header file, so other alternate provisions are
 * made to define the required symbols.
 */



/*
 * CyberSafe Remark:
 * Define this environment variable to be "0" in order to tell the library when 
 * it needs to emit runtime v2 gss tokens. Note that if you don't define 
 * it at all, the library emits v1 tokens.
 */
#define VERS_ENV_VARIABLE_NAME "CSF_GSS_VERSION"
#define VERS_ENV_VARIABLE_V1   "V1"
#define VERS_ENV_VARIABLE_V2   "V2"
#define VERS_ENV_VARIABLE_DEFAULTSETTING VERS_ENV_VARIABLE_V1 



/*
 * Dependent includes
 */
#include    <gssapi/compat.h>
#include    <gssapi/iso/oid.h>
#include    <gssapi/sts/c5errs.h>



/*
 * Now define the three implementation-dependent types.
 */
typedef struct gss_name_desc { void FAR * theName; } FAR * gss_name_t; 
typedef struct gss_cred_id_desc { void FAR * theCred; } FAR * gss_cred_id_t; 
typedef struct gss_ctx_id_desc { void FAR * theCtx; } FAR * gss_ctx_id_t;

/*
 * The following type must be defined as the smallest natural
 * unsigned integer supported by the platform that has at least
 * 32 bits of precision.
 *
 * CyberSafe Remark:
 * u_32 is defined in a platform-dependent way in compat.h
 */
typedef u_32 gss_uint32;

/*
 * CyberSafe Remark:
 * Since xom.h is not included above, the #else clause of this
 * conditional will always be exercised.
 *
 */


#ifdef OM_STRING
/*
 * We have included the xom.h header file.  Verify that OM_uint32
 * is defined correctly.
 */

#if sizeof(gss_uint32) != sizeof(OM_uint32)
#error Incompatible definition of OM_uint32 from xom.h
#endif

typedef OM_object_identifier gss_OID_desc, *gss_OID;

#else

/*
 * We can't use X/Open definitions, so roll our own.
 */

typedef gss_uint32 OM_uint32;

/*
 * CyberSafe Remark:
 * Equivalent definitions for OID structures are defined below.
 *
 * typedef struct gss_OID_desc_struct {
 *       OM_uint32 length;
 *       void      *elements;
 * } gss_OID_desc, *gss_OID;
 */

#endif


/*
 * CyberSafe Remark:
 * We also use signed 32-bit integers.  i_32 is defined in a
 * platform-dependent way in compat.h
 */
typedef i_32 OM_sint32;


/*
 * Note that a platform supporting the xom.h X/Open header file
 * may make use of that header for the definitions of OM_uint32
 * and the structure to which gss_OID_desc equates.
 */

/*
 * CyberSafe Remark:
 * Equivalent definitions for OID sets are included below.
 *
 * typedef struct gss_OID_set_desc_struct  {
 *       size_t     count;
 *       gss_OID    elements;
 * } gss_OID_set_desc, *gss_OID_set;
 */

/*
 * Type definitions for OIDs and OID sets.  
 * OID and OID set manipulation is in another library.
 */
typedef cs_oid_t            gss_OID;
typedef cs_oid_desc         gss_OID_desc;

typedef cs_oid_set_t        gss_OID_set;
typedef cs_oid_set_desc     gss_OID_set_desc;


typedef struct gss_buffer_desc_struct {

      size_t length;
      void FAR * value;

} gss_buffer_desc, FAR * gss_buffer_t;

/*
 * Channel bindings bind information to a channel.  They bind the checksum
 * of the contents of the gss_channel_bindings_t structure to the channel,
 * not the plaintext contents. 
 */
typedef struct gss_channel_bindings_struct {

      OM_uint32         initiator_addrtype;
      gss_buffer_desc   initiator_address;
      
      OM_uint32         acceptor_addrtype;
      gss_buffer_desc   acceptor_address;

      gss_buffer_desc   application_data;

} gss_channel_bindings_desc, FAR * gss_channel_bindings_t;

/*
 * These types are CyberSafe extensions, defined for typing convenience.
 */
typedef gss_channel_bindings_desc   gss_cb_desc;
typedef gss_channel_bindings_t      gss_cb_t;


/*
 * A QOP-type is an OM_uint32
 */
typedef OM_uint32 gss_qop_t;

typedef int gss_cred_usage_t;


/*
 * Flag bits for context-level services.
 */
#define GSS_C_DELEG_FLAG         1
#define GSS_C_MUTUAL_FLAG        2
#define GSS_C_REPLAY_FLAG        4
#define GSS_C_SEQUENCE_FLAG      8
#define GSS_C_CONF_FLAG          16
#define GSS_C_INTEG_FLAG         32
#define GSS_C_ANON_FLAG          64
#define GSS_C_PROT_READY_FLAG    128
#define GSS_C_TRANS_FLAG         256


/*
 * Credential usage options
 */
#define GSS_C_BOTH                0
#define GSS_C_INITIATE            1
#define GSS_C_ACCEPT              2


/*
 * Status code types for gss_display_status
 */
#define GSS_C_GSS_CODE            1
#define GSS_C_MECH_CODE           2

/*
 * The constant definitions for channel-bindings address families
 */
#define GSS_C_AF_UNSPEC           0
#define GSS_C_AF_LOCAL            1
#define GSS_C_AF_INET             2
#define GSS_C_AF_IMPLINK          3
#define GSS_C_AF_PUP              4
#define GSS_C_AF_CHAOS            5
#define GSS_C_AF_NS               6
#define GSS_C_AF_NBS              7
#define GSS_C_AF_ECMA             8
#define GSS_C_AF_DATAKIT          9
#define GSS_C_AF_CCITT            10
#define GSS_C_AF_SNA              11
#define GSS_C_AF_DECnet           12
#define GSS_C_AF_DLI              13
#define GSS_C_AF_LAT              14
#define GSS_C_AF_HYLINK           15
#define GSS_C_AF_APPLETALK        16
#define GSS_C_AF_BSC              17
#define GSS_C_AF_DSS              18
#define GSS_C_AF_OSI              19
#define GSS_C_AF_X25              21

#define GSS_C_AF_NULLADDR         255

/*
 * Various Null values
 */
#define GSS_C_NO_NAME             ((gss_name_t) 0)
#define GSS_C_NO_BUFFER           ((gss_buffer_t) 0)
#define GSS_C_NO_OID              ((gss_OID) 0)
#define GSS_C_NO_OID_SET          ((gss_OID_set) 0)
#define GSS_C_NO_CONTEXT          ((gss_ctx_id_t) 0)
#define GSS_C_NO_CREDENTIAL       ((gss_cred_id_t) 0)
#define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
#define GSS_C_EMPTY_BUFFER        {0, NULL}

/*
 * Some alternate names for a couple of the above
 * values.  These are defined for V1 compatibility.
 */
#define GSS_C_NULL_OID                GSS_C_NO_OID
#define GSS_C_NULL_OID_SET            GSS_C_NO_OID_SET

/*
 * CyberSafe Remark:
 * Define these for V1 compatibility also.
 */
#define GSS_C_NULL_BUFFER             GSS_C_NO_BUFFER
#define GSS_C_NULL_NAME               GSS_C_NO_NAME
#define GSS_C_NULL_CONTEXT            GSS_C_NO_CONTEXT
#define GSS_C_NULL_CREDENTIAL         GSS_C_NO_CREDENTIAL
#define GSS_C_NULL_CHANNEL_BINDINGS   GSS_C_NO_CHANNEL_BINDINGS

/*
 * Define the default Quality of Protection for per-message
 * services.  Note that an implementation that offers multiple
 * levels of QOP may define GSS_C_QOP_DEFAULT to be either zero
 * (as done here) to mean "default protection", or to a specific
 * explicit QOP value.  However, a value of 0 should always be
 * interpreted by a GSSAPI implementation as a request for the
 * default protection level.
 */
#define GSS_C_QOP_DEFAULT 0

/*
 * Expiration time of 2^32-1 seconds means infinite lifetime for a
 * credential or security context
 */
#define GSS_C_INDEFINITE 0xfffffffful

/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {10, (void *)"\x2a\x86\x48\x86\xf7\x12"
 *              "\x01\x02\x01\x01"},
 * corresponding to an object-identifier value of
 * {iso(1) member-body(2) United States(840) mit(113554)
 *  infosys(1) gssapi(2) generic(1) user_name(1)}.  The constant
 * GSS_C_NT_USER_NAME should be initialized to point
 * to that gss_OID_desc.
extern gss_OID GSS_C_NT_USER_NAME;
 */

/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {10, (void *)"\x2a\x86\x48\x86\xf7\x12"
 *              "\x01\x02\x01\x02"},
 * corresponding to an object-identifier value of
 * {iso(1) member-body(2) United States(840) mit(113554)
 *  infosys(1) gssapi(2) generic(1) machine_uid_name(2)}.
 * The constant GSS_C_NT_MACHINE_UID_NAME should be
 * initialized to point to that gss_OID_desc.
extern gss_OID GSS_C_NT_MACHINE_UID_NAME;
 */

/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {10, (void *)"\x2a\x86\x48\x86\xf7\x12"
 *              "\x01\x02\x01\x03"},
 * corresponding to an object-identifier value of
 * {iso(1) member-body(2) United States(840) mit(113554)
 *  infosys(1) gssapi(2) generic(1) string_uid_name(3)}.
 * The constant GSS_C_NT_STRING_UID_NAME should be
 * initialized to point to that gss_OID_desc.
extern gss_OID GSS_C_NT_STRING_UID_NAME;
 */

/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {6, (void *)"\x2b\x06\x01\x05\x06\x02"},
 * corresponding to an object-identifier value of
 * {1(iso), 3(org), 6(dod), 1(internet), 5(security),
 * 6(nametypes), 2(gss-host-based-services)}.  The constant
 * GSS_C_NT_HOSTBASED_SERVICE should be initialized to point
 * to that gss_OID_desc.
extern gss_OID GSS_C_NT_HOSTBASED_SERVICE;
 */

/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {6, (void *)"\x2b\x06\01\x05\x06\x03"},
 * corresponding to an object identifier value of
 * {1(iso), 3(org), 6(dod), 1(internet), 5(security),
 * 6(nametypes), 3(gss-anonymous-name)}.  The constant
 * and GSS_C_NT_ANONYMOUS should be initialized to point
 * to that gss_OID_desc.
extern gss_OID GSS_C_NT_ANONYMOUS;
 */



/*
 * The implementation must reserve static storage for a
 * gss_OID_desc object containing the value
 * {6, (void *)"\x2b\x06\x01\x05\x06\x04"},
 * corresponding to an object-identifier value of
 * {1(iso), 3(org), 6(dod), 1(internet), 5(security),
 * 6(nametypes), 4(gss-api-exported-name)}.  The constant
 * GSS_C_NT_EXPORT_NAME should be initialized to point
 * to that gss_OID_desc.
extern gss_OID GSS_C_NT_EXPORT_NAME;
 */


/* Major status codes */
#define GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious. 
 */
#define GSS_C_CALLING_ERROR_OFFSET  24
#define GSS_C_ROUTINE_ERROR_OFFSET  16
#define GSS_C_SUPPLEMENTARY_OFFSET  0

#define GSS_C_CALLING_ERROR_MASK    0377ul
#define GSS_C_ROUTINE_ERROR_MASK    0377ul
#define GSS_C_SUPPLEMENTARY_MASK    0177777ul

/*
 * The macros that test status codes for error conditions.
 * Note that the GSS_ERROR() macro has changed slightly from
 * the V1 GSSAPI so that it now evaluates its argument
 * only once.
 */
#define GSS_CALLING_ERROR(x) \
  ((x) & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
#define GSS_ROUTINE_ERROR(x) \
  ((x) & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
#define GSS_SUPPLEMENTARY_INFO(x) \
  ((x) & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
#define GSS_ERROR(x) \
    (((x) & ((GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET) | \
            (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))) != 0)


/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */

#define GSS_S_CALL_INACCESSIBLE_READ \
            (1ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_INACCESSIBLE_WRITE \
            (2ul << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_BAD_STRUCTURE \
            (3ul << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
#define GSS_S_BAD_MECH                (1ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAME                (2ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAMETYPE            (3ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_BINDINGS            (4ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_STATUS              (5ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_SIG                 (6ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CRED                 (7ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CONTEXT              (8ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_TOKEN         (9ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_CREDENTIAL    (10ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CREDENTIALS_EXPIRED     (11ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CONTEXT_EXPIRED         (12ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_FAILURE                 (13ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_QOP                 (14ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAUTHORIZED            (15ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAVAILABLE             (16ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DUPLICATE_ELEMENT       (17ul << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NAME_NOT_MN             (18ul << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Supplementary info bits:
 */
#define GSS_S_CONTINUE_NEEDED         (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#define GSS_S_DUPLICATE_TOKEN         (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#define GSS_S_OLD_TOKEN               (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN             (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
#define GSS_S_GAP_TOKEN               (1ul << (GSS_C_SUPPLEMENTARY_OFFSET + 4))


/*
 * Finally, function prototypes for the GSSAPI routines.
 */



#if defined(__cplusplus)
	extern "C" {
#endif



/*
 * CyberSafe Remark:
 * gss_open() and gss_close() are declared for compatibility with older
 * versions of the CyberSafe Application Security Toolkit.
 *
 */
OM_uint32 CSFAPI
    gss_open    
        _GSS_PROTO(
            (OM_uint32 FAR * CONST          /* minor status         OUT      */
            ));

OM_uint32 CSFAPI
    gss_close   
        _GSS_PROTO(
            (OM_uint32 FAR * CONST          /* minor status         OUT      */
            ));

OM_uint32 CSFAPI
    gss_acquire_cred
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
    gss_release_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             gss_cred_id_t FAR * CONST     /* cred_handle           IN, OPT  */
            ));

OM_uint32 CSFAPI
    gss_init_sec_context
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
    gss_accept_sec_context  
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
    gss_process_context_token
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             CONST gss_ctx_id_t,           /* context_handle        IN       */
             CONST gss_buffer_t            /* token_buffer          IN       */
            ));

OM_uint32 CSFAPI
    gss_delete_sec_context
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,        /* minor_status          OUT      */
             gss_ctx_id_t FAR * CONST,     /* context_handle        IN       */
             gss_buffer_t                  /* output_token          OUT, OPT */
            ));

OM_uint32 CSFAPI
    gss_context_time
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             OM_uint32 FAR * CONST        /* time_rec               OUT      */
            ));
            
OM_uint32 CSFAPI
    gss_get_mic
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             gss_qop_t,                   /* qop_req                IN, OPT  */
             CONST gss_buffer_t,          /* message_buffer         IN       */
             gss_buffer_t                 /* message_token          OUT      */
            ));

OM_uint32 CSFAPI
    gss_verify_mic  
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status           OUT      */
             CONST gss_ctx_id_t,          /* context_handle         IN       */
             CONST gss_buffer_t,          /* message_buffer         IN       */
             CONST gss_buffer_t,          /* token_buffer           IN       */
             gss_qop_t FAR * CONST        /* qop_state              OUT, OPT */
            ));
                
OM_uint32 CSFAPI
    gss_wrap    
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
    gss_unwrap
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_ctx_id_t,         /* context                 IN       */
             CONST gss_buffer_t,         /* input_message_buffer    IN       */
             gss_buffer_t,               /* output_message_buffer   OUT      */
             int FAR * CONST,            /* conf_state              OUT, OPT */
             gss_qop_t FAR * CONST       /* qop_state               OUT, OPT */
            ));  

OM_uint32 CSFAPI
    gss_display_status
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             OM_uint32,                  /* status_value            IN       */
             int,                        /* status_type             IN       */
             CONST gss_OID,              /* mech_type               IN, OPT  */
             OM_uint32 FAR * CONST,      /* message_context         INOUT    */
             gss_buffer_t                /* status_string           OUT      */
            ));

OM_uint32 CSFAPI
    gss_indicate_mechs
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_OID_set FAR * CONST     /* mech_set                OUT      */
            ));
            
OM_uint32 CSFAPI
    gss_compare_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_name_t,           /* name1                   IN       */
             CONST gss_name_t,           /* name2                   IN       */
             int FAR * CONST             /* name_equal              OUT      */
            ));

OM_uint32 CSFAPI
    gss_display_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             CONST gss_name_t,           /* input_name              IN       */
             gss_buffer_t,               /* output_name_buffer      OUT      */
             gss_OID FAR * CONST         /* output_name_type        OUT, OPT */
            ));

OM_uint32 CSFAPI
    gss_import_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_buffer_t,         /* input_name_buffer      IN       */
             CONST gss_OID,              /* input_name_type        IN, OPT  */
             gss_name_t FAR * CONST      /* output_name            OUT      */
            ));

OM_uint32 CSFAPI
    gss_export_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_name_t,           /* input_name             IN       */
             gss_buffer_t                /* exported_name          OUT      */
            ));

OM_uint32 CSFAPI
    gss_release_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_name_t FAR * CONST      /* input_name             IN       */
            ));
            
OM_uint32 CSFAPI
    gss_release_buffer
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_buffer_t                /* buffer                 IN       */
            ));

OM_uint32 CSFAPI
    gss_release_oid_set
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             gss_OID_set FAR * CONST     /* set                    IN       */
            ));

OM_uint32 CSFAPI
    gss_inquire_cred
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status           OUT      */
             CONST gss_cred_id_t,        /* cred_handle            IN, OPT  */
             gss_name_t FAR * CONST,     /* name                   OUT, OPT */
             OM_uint32 FAR * CONST,      /* lifetime               OUT, OPT */
             gss_cred_usage_t FAR * CONST,/* cred_usage            OUT, OPT */
             gss_OID_set FAR * CONST     /* mechanisms             OUT, OPT */
            ));

OM_uint32 CSFAPI
    gss_inquire_context
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
    gss_wrap_size_limit
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_ctx_id_t,        /* context_handle        IN       */
               int,                       /* conf_req_flag         IN       */
               gss_qop_t,                 /* qop_req               IN       */
               OM_uint32,                 /* req_output_size       IN       */
               OM_uint32 FAR * CONST      /* max_input_size        OUT      */
              ));

OM_uint32 CSFAPI
    gss_add_cred
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
    gss_inquire_cred_by_mech
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
    gss_export_sec_context
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               gss_ctx_id_t FAR * CONST,  /* context_handle        IN       */
               gss_buffer_t               /* interprocess_token    OUT      */
              ));

OM_uint32 CSFAPI
    gss_import_sec_context
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_buffer_t,        /* interprocess_token    IN       */
               gss_ctx_id_t FAR * CONST   /* context_handle        OUT      */
              ));

OM_uint32 CSFAPI
    gss_create_empty_oid_set
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               gss_OID_set FAR * CONST    /* oid_set               IN       */
              ));

OM_uint32 CSFAPI
    gss_add_oid_set_member
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* member_oid            IN       */
               gss_OID_set FAR * CONST    /* oid_set               IN       */
              ));

OM_uint32 CSFAPI
    gss_test_oid_set_member
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* member                IN       */
               CONST gss_OID_set,         /* set                   IN       */
               int FAR * CONST            /* present               OUT      */
              ));

OM_uint32 CSFAPI
    gss_inquire_names_for_mech
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_OID,             /* mechanism             IN       */
               gss_OID_set FAR * CONST    /* name_types            OUT      */
              ));

OM_uint32 CSFAPI
    gss_inquire_mechs_for_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* input_name            IN       */
               gss_OID_set FAR * CONST    /* mech_types            OUT      */
              ));

OM_uint32 CSFAPI
    gss_canonicalize_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* input_name            IN       */
               CONST gss_OID,             /* mech_type             IN       */
               gss_name_t FAR * CONST     /* output_name           OUT      */
              ));

OM_uint32 CSFAPI
    gss_duplicate_name
        _GSS_PROTO(
               (OM_uint32 FAR * CONST,    /* minor_status          OUT      */
               CONST gss_name_t,          /* src_name              IN       */
               gss_name_t FAR * CONST     /* dest_name             OUT      */
              ));

/*
 * The following routines are obsolete variants of gss_get_mic,
 * gss_verify_mic, gss_wrap and gss_unwrap.  They should be
 * provided by GSSAPI V2 implementations for backwards
 * compatibility with V1 applications.  Distinct entrypoints
 * (as opposed to #defines) should be provided, both to allow
 * GSSAPI V1 applications to link against GSSAPI V2 implementations,
 * and to retain the slight parameter type differences between the
 * obsolete versions of these routines and their current forms.
 */
OM_uint32 CSFAPI
    gss_sign
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_ctx_id_t,               /* context_handle          IN       */
             i_32,                       /* qop_req                 IN, OPT  */
             CONST gss_buffer_t,         /* message_buffer          IN       */
             gss_buffer_t                /* message_token           OUT      */
            ));

OM_uint32 CSFAPI
    gss_verify
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_ctx_id_t,               /* context_handle          IN       */
             CONST gss_buffer_t,         /* message_buffer          IN       */
             CONST gss_buffer_t,         /* token_buffer            IN       */
             i_32 FAR * CONST            /* qop_state               OUT, OPT */
            ));
                
OM_uint32 CSFAPI
    gss_seal    
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_ctx_id_t,               /* context_handle          IN       */
             i_32,                       /* conf_req_flag           IN       */
             i_32,                       /* qop_req                 IN, OPT  */
             CONST gss_buffer_t,         /* input_message_buffer    IN       */
             i_32 FAR * CONST,           /* conf_state              OUT, OPT */
             gss_buffer_t                /* output_message_buffer   OUT      */
            ));

OM_uint32 CSFAPI
    gss_unseal
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,      /* minor_status            OUT      */
             gss_ctx_id_t,               /* context_handle          IN       */
             CONST gss_buffer_t,         /* input_message_buffer    IN       */
             gss_buffer_t,               /* output_message_buffer   OUT      */
             i_32 FAR * CONST,           /* conf_state              OUT, OPT */
             i_32 FAR * CONST            /* qop_state               OUT, OPT */
            ));  


/*
 * CyberSafe Remark:
 * These two API declarations are included for compatibility with a
 * previous draft of Version 2 of the GSS-API.
 */
OM_uint32 CSFAPI
    gss_import_internal_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
             void FAR* CONST,             /* input_name            IN       */
             CONST gss_OID,               /* input_name_type       IN       */
             gss_name_t FAR * CONST       /* output_name           OUT      */
            ));

OM_uint32 CSFAPI
    gss_export_internal_name
        _GSS_PROTO(
            (OM_uint32 FAR * CONST,       /* minor_status          OUT      */
             CONST gss_name_t,            /* input_name            IN       */
             CONST gss_OID,               /* desired_name_type     IN       */
             void FAR * FAR *             /* output_name           OUT      */
            ));



#if defined(__cplusplus)
}
#endif



/*
 * CyberSafe Remark:
 * CyberSafe extensions to get values of error subfields
 */
#define GSS_CALLING_ERROR_VALUE(x) \
  (((x) >> GSS_C_CALLING_ERROR_OFFSET) & GSS_C_CALLING_ERROR_MASK)
#define GSS_ROUTINE_ERROR_VALUE(x) \
  (((x) >> GSS_C_ROUTINE_ERROR_OFFSET) & GSS_C_ROUTINE_ERROR_MASK)
#define GSS_SUPPLEMENTARY_INFO_VALUE(x) \
  (((x) >> GSS_C_SUPPLEMENTARY_OFFSET) & GSS_C_SUPPLEMENTARY_MASK)



/*
 * CyberSafe Remark:
 * This mechanism set contains a list of all 
 * of the available underlying mechanisms.
 */
#define gss_mech_set    rfc_krb5_c_OID_set



#include    <gssapi/rfckrb5.h>
#include    <gssapi/ext.h>



#endif /* GSSAPI_H_ */
