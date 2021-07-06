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
 * @(#)$RCSfile: rfckrb5.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:46 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     rfckrb5.h~15:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file holds external declarations for the OIDs defined in 
        the Draft Kerberos GSS-API Mechanism RFC.

============================================================================*/



#ifndef _GSS_RFC_KRB5_H_
#define _GSS_RFC_KRB5_H_

#include    <gssapi/compat.h>


    /* This is the OID and OID set for the 
        CyberSafe RFC Kerberos V mechanism. */

#if 0
#define rfc_krb5_c_OID \
            ((CONST gss_OID)csfgss_pPtr("rfc_krb5_c_OID"))
#define rfc_krb5_c_OID_set \
            ((CONST gss_OID_set)csfgss_pPtr("rfc_krb5_c_OID_set"))
#endif


    /* From the GSS/K5 Draft RFC:
        This name type represents any valid Kerberos name 
        parseable by the Kerberos V5 routine krb5_parse_name; such 
        names have characteristics as follows: Components of a 
        name are separated by `/`.  The separator `@` may be used 
        instead of `/`, signifying that the remainder of the string 
        following the `@` is to be interpreted as a realm 
        identifier; if no `@` is encountered, the name is 
        interpreted in the context of the local realm.  Once a `@` 
        is encountered, a non-null realm name, with no embedded `/` 
        separators, must follow. The `\` character is used to 
        quote the immediately-following character. */
        
#if 0
#define GSS_KRB5_NT_PRINCIPAL_NAME \
            ((CONST gss_OID)csfgss_pPtr("GSS_KRB5_NT_PRINCIPAL_NAME"))
#endif

    /* This name type is from the Draft K5 RFC type "Service 
        Name Form".  Its representation is "service@host", or 
        ftp@kerby for example.  The Kerberos translation of this
        name type would be service/host@realm. 
    
        Upon the name type's translation to a Kerberos principal is 
        parsed by the Kerberos function krb5_sname_to_principal() 
        using the Kerberos principal type KRB5_NT_SRV_HST.  
        Therefore, "host" is the host's FQDN and "realm" is the 
        default realm.  For example, ftp@kerby would become 
        ftp/kerby.ocsg.com@OCSG.COM. */
        
#define GSS_KRB5_NT_HOSTBASED_SERVICE_NAME GSS_C_NT_HOSTBASED_SERVICE

    /* From the GSS/K5 Draft RFC:
        This name type is used to indicate a named user on a local 
        system.  Its interpretation is OS-specific.  This name form 
        is constructed as:
            username
        Assuming that users' principal names are the same as their 
        local operating system names, an implementation of 
        gss_import_name() based on Kerberos V5 technology can process 
        names of this form by postfixing an "@" sign and the name of 
        the local realm. */
        
#define GSS_KRB5_NT_USER_NAME GSS_C_NT_USER_NAME

    /* From the GSS/K5 Draft RFC:
        This name type is used to indicate a numeric user 
        identifier corresponding to a user on a local system.  
        Its interpretation is OS-specific.  The gss_buffer_desc 
        representing a name of this type should contain a 
        locally-significant uid_t, represented in host byte
        order.  The gss_import_name() operation resolves this 
        uid into a username, which is then treated as the User 
        Name Form.

        The Draft RFC does not define whether the UID is passed 
        as the buffer's value pointer or wether the buffer's 
        value pointer points to a uid_t. CyberSafe's defines the 
        buffer's value pointer points to a uid_t. The Draft RFC 
        doesn't define the buffer's length. CyberSafe defines 
        the buffer's length as sizeof(uid_t). Finally, as in the 
        sting UID name form, CyberSafe defines the name's realm 
        as the default realm. */
        
#define GSS_KRB5_NT_MACHINE_UID_NAME GSS_C_NT_MACHINE_UID_NAME

    /* From the GSS/K5 Draft RFC:
        This name type is used to indicate a string of digits 
        representing the numeric user identifier of a user on a 
        local system.  Its interpretation is OS-specific. This 
        name type is similar to the Machine UID Form, except 
        that the buffer contains a string representing the uid_t.

        The Draft RFC does not define the name type's realm. 
        CyberSafe assigns the name's realm the default realm. */
        
#define GSS_KRB5_NT_STRING_UID_NAME GSS_C_NT_STRING_UID_NAME

    /* From the GSS/K5 Draft RFC:
        This name type represents any valid Kerberos name parseable 
        by the Kerberos V5 routine krb5_parse_name; such names have 
        characteristics as follows: Components of a name are 
        separated by `/`.  The separator `@` may be used instead of 
        `/`, signifying that the remainder of the string following 
        the `@` is to be interpreted as a realm identifier; if no 
       `@` is encountered, the name is interpreted in the context of
        the local realm.  Once a `@` is encountered, a non-null 
        realm name, with no embedded `/` separators, must follow. 
        The `\` character is used to quote the immediately-following 
        character.

        This name type is used in two forms: gss_import_name() and 
        gss_import_internal_name(). When used with gss_import_name() 
        the input name is a string encapsulated in a GSS buffer. 
        When used with gss_import_internal_name() the passed name 
        is a Kerberos principal. */
        
#if 0
#define GSS_KRB5_NT_PRINCIPAL \
            ((CONST gss_OID)csfgss_pPtr("GSS_KRB5_NT_PRINCIPAL"))
#endif



/*
 * Generic OIDs
 */
#define GSS_C_NT_USER_NAME (csf_gss_get_OidAddress( 2 ))
#define GSS_C_NT_MACHINE_UID_NAME (csf_gss_get_OidAddress( 3 ))
#define GSS_C_NT_STRING_UID_NAME (csf_gss_get_OidAddress( 4 ))
#define GSS_C_NT_HOSTBASED_SERVICE (csf_gss_get_OidAddress( 5 ))
#define GSS_C_NT_ANONYMOUS (csf_gss_get_OidAddress( 6 ))
#define GSS_C_NT_EXPORT_NAME (csf_gss_get_OidAddress( 7 ))

/*
 * Kerberos 5 specific OIDs
 */
    /* 
        TEMPORARY!!
        We're going to use the value that SAP is passing in order to get the 
        comparisons everywhere to work.
    */ 
#define rfc_krb5_c_OID (csf_gss_get_OidAddress( 0 ))
#define rfc_krb5_c_OID_old (csf_gss_get_OidAddress( 1 ))
#define GSS_KRB5_NT_PRINCIPAL_NAME (csf_gss_get_OidAddress( 8 ))
#define GSS_KRB5_NT_PRINCIPAL (csf_gss_get_OidAddress( 9 ))


#ifdef __cplusplus
    extern "C" {
#endif
        extern gss_OID_set CSFAPI csf_gss_get_RfcOidSet( void );
#ifdef __cplusplus
    }
#endif

#define rfc_krb5_c_OID_set (csf_gss_get_RfcOidSet())


    /* The following are Quality of Protection (QOP) values used 
        to select among the integrity checking algorithms of the 
        Kerberos mechanism. */
        
#define GSS_KRB5_INTEG_C_QOP_MD5        1
#define GSS_KRB5_INTEG_C_QOP_DES_MD5    2
#define GSS_KRB5_INTEG_C_QOP_DES_MAC    3

    /* The following are Quality of Protection (QOP) values used 
        to select among the confidentiality algorithms of the 
        Kerberos mechanism. */
        
#define GSS_KRB5_CONF_C_QOP_DES         0


#endif /* _GSS_RFC_KRB5_H_ */ 
