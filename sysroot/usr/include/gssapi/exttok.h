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
 * @(#)$RCSfile: exttok.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:38 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     exttok.h~6:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file holds extensions to the K5 mechanism token.

============================================================================*/



#ifndef _GSS_EXT_TOK_H_
#define _GSS_EXT_TOK_H_



    /* When DES-40 is used to provide message confidentiality 
        then this value is stuffed into the token's SEAL_ALG. */

#define CSF_SEAL_ALG_DES40           3504

    /* The following are algorithm definitions for DES3. */

#define CSF_SIGN_ALG_DES3_MAC_MD5    64221
#define CSF_SEAL_ALG_DES3_CBC        64222



#endif /* _GSS_EXT_TOK_H_ */ 
