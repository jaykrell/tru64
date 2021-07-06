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
 * @(#)$RCSfile: rfctok.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:48 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     rfctok.h~5:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file holds definitions that describe the token format and 
        encoding of the Draft Kerberos GSS-API Mechanism RFC tokens.
============================================================================*/



#ifndef _GSS_RFC_TOK_H_
#define _GSS_RFC_TOK_H_



    /* These are token identifiers.
        They are used in all tokens and identify the token type.  
        They immediately follow a token's OID. Token identifiers
        are 16 bit integers and are encoded in little endian
        form (e.g., 0x01 proceeds 0x00). */
        
#define TOK_ID_KRB5_AP_REQ          0x0001
#define TOK_ID_KRB5_AP_REP          0x0002
#define TOK_ID_KRB5_ERR             0x0003
#define TOK_ID_KRB5_SIGN            0x0101
#define TOK_ID_KRB5_SEAL            0x0102
#define TOK_ID_KRB5_DELE            0x0201

/* This token ID is for the exported name token in Version 2 of GSS. */
#define TOK_ID_GSS_EXPORTED_NAME    0x0104 /* 1st byte = 04, 2d byte  = 01 */


    /* These are token identifiers too but use 
        the GSS-API V2 naming conventions. */
    
#define TOK_ID_KRB5_MIC         TOK_ID_KRB5_SIGN
#define TOK_ID_KRB5_WRAP        TOK_ID_KRB5_SEAL



    /* These definitions identify the authenticator checksum 
        length and type used in context establishment. */
        
#define KRB5_CHKSUM_TYPE        0x8003
#define KRB5_CHKSUM_LENGTH      8


    /* The GSS authenticator includes "bindings."  These bindings 
        are created by calculating the MD5 hash value of GSS
        channel bindings (passed as a parameter to the GSS 
        initiate and accept context functions). 
        
        The value of this definition must equal 
        RSA_MD5_CKSUM_LENGTH. */
        
#define KRB5_BINDINGS_LENGTH    16


    /* Type definition of token identifiers (TOK ID). */
    
typedef u_16    gss_krb5_tok_id, *gss_krb5_tok_id_t;



    /* The minimum length of the GSS authenticator passed in 
        the authentication tokens' authenticator. */
    
#define AUTH_CKSM_LENGTH    \
    ( sizeof( u_32 ) + KRB5_BINDINGS_LENGTH + sizeof( u_32 ))


    /* This is the number of bytes allocated for sequence 
        numbers in SIGN and SEAL message headers. Sequence 
        numbers are really unsigned thirty two bit integers. 
        The first four bytes are the sequence number in 
        little endian form. The remaining four bytes are a 
        direction indicator. The whole field is encrypted 
        using DES-CBC. Therefore, the length of this field 
        must be a multiple of 8. */
    
#define SEQ_LEN             8


    /* These definitions are used in SIGN, or MIC, headers. 
        There are two bytes of unused filler data that are 
        set to 0xff each. */

#define SEAL_FILLER_LEN     2
#define SIGN_FILLER_LEN     4
#define FILLER_CHAR         (u_char)0xff


    /* This definition is used in SIGN headers and 
        is the length of the checksum field. */
    
#define CKSM_LEN            8


    /* These definitions are offsets from the beginning of a
        character buffer to the components of a signed message. 
        Note there is no data in the buffer however the location 
        is used within the code. */

#define SIGN_TOK_ID_OFFSET      0
#define SIGN_SIGN_ALG_OFFSET    SIGN_TOK_ID_OFFSET + sizeof( u_16 )
#define SIGN_FILLER_OFFSET      SIGN_SIGN_ALG_OFFSET + sizeof( u_16 )
#define SIGN_SEQNUM_OFFSET      SIGN_FILLER_OFFSET + SIGN_FILLER_LEN
#define SIGN_CHKSM_OFFSET       SIGN_SEQNUM_OFFSET + SEQ_LEN
#define SIGN_DATA_OFFSET        SIGN_CHKSM_OFFSET + CKSM_LEN

    /* This definition is the length of SIGN headers. A SIGN 
        header is composed of a token identifier, signature 
        algorithm indicator, filler data, a sequence number, 
        and the signature itself respectively. */
    
#define SIGN_HDR_LEN        ( SIGN_DATA_OFFSET - SIGN_TOK_ID_OFFSET )


    /* These definitions are offsets from the beginning of a
        character buffer to the components of a sealed message. */

#define SEAL_TOK_ID_OFFSET      0
#define SEAL_SIGN_ALG_OFFSET    SEAL_TOK_ID_OFFSET + sizeof( u_16 )
#define SEAL_SEAL_ALG_OFFSET    SEAL_SIGN_ALG_OFFSET + sizeof( u_16 )
#define SEAL_FILLER_OFFSET      SEAL_SEAL_ALG_OFFSET + sizeof( u_16 )
#define SEAL_SEQNUM_OFFSET      SEAL_FILLER_OFFSET + SEAL_FILLER_LEN
#define SEAL_CHKSM_OFFSET       SEAL_SEQNUM_OFFSET + SEQ_LEN
#define SEAL_DATA_OFFSET        SEAL_CHKSM_OFFSET + CKSM_LEN

    /* This definition is the length of SEAL headers. A SEAL 
        header is composed of a token identifier, signature 
        algorithm indicator, seal algorithm indicator, filler 
        data, sequence number, and message checksum respectively. */

#define SEAL_HDR_LEN        ( SEAL_DATA_OFFSET - SEAL_TOK_ID_OFFSET )


    /* These two character definitions are used as the 
        sequence number direction indicators. The first 
        definition indicates the sender is the context 
        initiator whereas the second indicates the context 
        acceptor is the sender. */
    
#define INITIATOR_DIR_CHAR  '\0'
#define ACCEPTOR_DIR_CHAR   '\377'


    /* These definitions are encoded in sealed and signed 
        packet headers and indicate the signature algorithm. 
        Signature indicators are two byte values and are 
        encoded in little endian form. */
    
#define SIGN_ALG_DES_MAC_MD5    0x0000
#define SIGN_ALG_MD2_5          0x0001
#define SIGN_ALG_DES_MAC        0x0002


    /* These definitions are encoded in sealed packet headers
        and indicate the seal algorithm. Seal indicators are 
        two byte values and are encoded in little endian form. */

#define SEAL_ALG_NONE           0xffff
#define SEAL_ALG_DES_CBC        0x0000


    /* Messages sealed using DES-CBC are padded so they are
        a multiple of eight bytes. Eight is the DES block size. */

#define DES_BLK_SIZE            8


    /* When message checksums are calculated the message is 
        logically prefixed with part of the token header. This 
        definition is the amount of data from the header. */
    
#define MSG_CKSM_PREFIX_LEN     8


    /* This definition is the number of confounder bytes 
        prefixed to plain text messages before their checksum 
        is calculated or they are encrypted. */
    
#define CONFOUNDER_LEN          8



#endif /* _GSS_RFC_TOK_H_ */ 
