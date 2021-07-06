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
 * @(#)$RCSfile: gssver.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:14:51 $
 */
#ifndef _CSF_INCLUDE_GSSVER_H_
#define _CSF_INCLUDE_GSSVER_H_
/*
** Copyright (C) 1999-2000 CyberSafe Corporation. All Rights Reserved.
 * All Rights Reserved.
 *
 * This product is licensed. Use of this product is subject to 
 * the CyberSafe Corporation Software License Agreement.
 * 
 */

#define COMPANY_NAME "CyberSafe Corporation\0"
#if defined(CSF_CRYPTO_56bit_DES3)
#define ENC_LEVEL "56-bit(DES3+DES)\0"
#elif defined(CSF_CRYPTO_56bit_DES)
#define ENC_LEVEL "56-bit(DES)\0"
#elif defined(CSF_CRYPTO_40bit_DES)
#define ENC_LEVEL "40-bit(DES)\0"
#else
#define ENC_LEVEL "No encryption\0"
#endif   
#define FILE_DESCRIPTION "CyberSafe GSS-API Runtime Library\0"
#define FILE_VERSION "2.2\0"
#define INTERNAL_NAME "GSSAPI32\0"
#define LEGAL_COPYRIGHT "Copyright © 1999 CyberSafe Corporation\0"
#define ORIGINAL_FILENAME "gssapi32.dll\0"
#define PRODUCT_NAME "CyberSafe Application Security Toolkit\0"
#define PRODUCT_VERSION "ProductVersion", "2.2\0"

#endif	/* _CSF_INCLUDE_GSSVER_H_*/
