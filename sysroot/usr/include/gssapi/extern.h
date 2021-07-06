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
 * @(#)$RCSfile: extern.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:36 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     extern.h~7:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

============================================================================*/



#ifndef _GSS_EXTERN_H_
#define _GSS_EXTERN_H_

/*
 * Set of all nametype OIDs supported by the Kerberos 5 mechanism
 * as implemented by CyberSafe's Security SDK.
 */
extern gss_OID_set pRFCs_2078_1964_NAMETYPE_OID_SET;

/*
 * The Kerberos Mechanism OID ASN.1 encoded and its encoded length.
 */

extern CONST csf_o        pCSF_gss_Encoded_oid[];
extern csf_size_t             pCSF_gss_Encoded_oid_len;

extern CONST csf_o         pCSF_gss_Encoded_oid_old[];
extern csf_size_t             pCSF_gss_Encoded_oid_len_old;

extern CONST csf_o         pCSF_gss_Encoded_oid_sap[];
extern csf_size_t             pCSF_gss_Encoded_oid_len_sap;

/*
 * Zeros fed into encryption routines as an initial vector. 
 */

extern CONST u_char        pCSF_gss_bunchOfZeros[];

#endif /* _GSS_EXTERN_H_ */ 
