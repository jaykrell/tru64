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
 * @(#)$RCSfile: der.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:54 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     der.h~5:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file contains declarations used to encode GSS-API tokens
        using ASN.1 encoding. The declarations in this file are taken
        from ISODE, specifically, the header file isode/psap.h.

        I am using these declarations until (if) I recode the DER
        encoding.

============================================================================*/



#ifndef __DER_H__
#define __DER_H__

#include    <gssapi/compat.h>



typedef u_char     PElementClass;
typedef u_char     PElementForm;
typedef u_short    PElementID;

#define PE_CLASS_MASK   0xc0
#define PE_CLASS_SHIFT  6
#define PE_FORM_MASK    0x20
#define PE_FORM_SHIFT   5
#define PE_CODE_MASK    0x1f
#define PE_CODE_SHIFT   0

#define PE_LEN_XTND 0x80
#define PE_LEN_SMAX 127
#define PE_LEN_MASK 0x7f

#define PE_ID_XTND  0x1f
#define PE_ID_MORE  0x80
#define PE_ID_MASK  0x7f
#define PE_ID_SHIFT 7

#define PE_CLASS_UNIV   0x0 /*   Universal */
#define PE_CLASS_APPL   0x1 /*   Application-wide */
#define PE_CLASS_CONT   0x2 /*   Context-specific */
#define PE_CLASS_PRIV   0x3 /*   Private-use */

#define PE_FORM_PRIM    0x0 /*   PRIMitive */
#define PE_FORM_CONS    0x1 /*   CONStructor */


#define PE_ERR_NONE          0
#define PE_ERR_OVER          1      /*   Overflow */
#define PE_ERR_NMEM          2      /*   Out of memory */
#define PE_ERR_BIT           3      /*   No such bit */
#define PE_ERR_UTCT          4      /*   Malformed universal timestring */
#define PE_ERR_GENT          5      /*   Malformed generalized timestring */
#define PE_ERR_MBER          6      /*   No such member */
#define PE_ERR_PRIM          7      /*   Not a primitive form */
#define PE_ERR_CONS          8      /*   Not a constructor form */
#define PE_ERR_TYPE          9      /*   Class/ID mismatch in constructor */
#define PE_ERR_OID          10      /*   Malformed object identifier */
#define PE_ERR_BITS         11      /*   Malformed bitstring */
#define PE_ERR_NOSUPP       12      /*   Type not supported */
#define PE_ERR_SIGNED       13      /*   Signed integer not expected */
#define PE_ERR_DUPLICATE    14      /*   duplicate member */
#define PE_ERR_SYNTAX       15      /*   syntax error */


#endif /* __DER_H__ */ 
