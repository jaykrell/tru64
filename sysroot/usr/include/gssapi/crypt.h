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
 * @(#)$RCSfile: crypt.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:31 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     crypt.h~4:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This header file is used for development and its purpose is 
        to shorten the GSS-API's compilation command line length. 
        Previously three variables had to be defined on the 
        compilation command line, now there is one. They are:
            CSF_CRYPTO_56bit_DES3
            CSF_CRYPTO_56bit_DES
            CSF_CRYPTO_40bit_DES
            CSF_CRYPTO_NONE

============================================================================*/



#ifndef _GSS_CRYPT_H_
#define _GSS_CRYPT_H_



#if defined(CSF_CRYPTO_56bit_DES3)

/*
 * Definition of CSF_CRYPTO_56bit_DES3 indicates 
 * that the GSS-API will perform message 
 * encryption using 56-bit DES or DES3.
 */

#define CSF_56bit_DES3  1
#define CSF_56bit_DES   1
#define CSF_40bit_DES   0

#elif defined(CSF_CRYPTO_56bit_DES)

/*
 * Definition of CSF_CRYPTO_56bit_DES indicates 
 * that the GSS-API will perform message 
 * encryption using 56-bit DES.
 */

#define CSF_56bit_DES3  0
#define CSF_56bit_DES   1
#define CSF_40bit_DES   0

#elif defined(CSF_CRYPTO_40bit_DES)

/*
 * Definition of CSF_CRYPTO_40bit_DES indicates 
 * that the GSS-API will perform message 
 * encryption using 40-bit DES.
 */

#define CSF_56bit_DES3  0
#define CSF_56bit_DES   0
#define CSF_40bit_DES   1

#else

/*
 * Currently not supported NULL crypto.
 */

#error "Crypto strength specified as neither 56-bit nor 40-bit."

#endif


/* Definition of CSF_CRYPTO_NONE indicates 
    that the GSS-API does not support 
    messages encryption. */
#if defined(CSF_CRYPTO_NONE)

#define CSF_56bit_DES3  0
#define CSF_56bit_DES   0
#define CSF_40bit_DES   0

#endif


/* This decl is an aggregate of the other 
    encryption identifiers and indicates 
    whether the GSS-API supports encryption. */

#define CSF_ANY_SEAL_CRYPTO ( CSF_56bit_DES3 | CSF_56bit_DES | CSF_40bit_DES )


#endif /* _GSS_CRYPT_H_ */ 
