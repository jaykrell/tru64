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
 * @(#)$RCSfile: c5errs.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:59 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     c5errs.h~3.1:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

============================================================================*/



#ifndef C5ERRS_H_
#define C5ERRS_H_



#define CSF_CFG_STSBASE         4096
#define CSFC5_CFG_STSBASE       (CSF_CFG_STSBASE + (256*3))
#define CSFASNX_CFG_STSBASE     (CSF_CFG_STSBASE + (256*1))
#define CSF_STS_CFG__base       (CSF_CFG_STSBASE + (256*2))
#define CSFC5c_STS__base        (CSFC5_CFG_STSBASE + (256*0))
#define CSFC5_STS__base         (CSFC5_CFG_STSBASE + (256*1))
#define CSFC5_STS_CC__base      (CSFC5_CFG_STSBASE + (256*2))
#define CSFC5_STS_RC__base      (CSFC5_CFG_STSBASE + (256*3))
#define CSFC5_STS_KT__base      (CSFC5_CFG_STSBASE + (256*4))
#define CSFC5_STS_CRS__base     (CSFC5_CFG_STSBASE + (256*5))
#define CSFC5_STS_CKS__base     (CSFC5_CFG_STSBASE + (256*6))
#define CSFC5_STS_NET__base     (CSFC5_CFG_STSBASE + (256*7))
#define CSFC5_STS_ASN__base     (CSFC5_CFG_STSBASE + (256*8))
#define CSFC5_STS_DB__base      (CSFC5_CFG_STSBASE + (256*9))
#define CSFA5_STS__base         (CSFC5_CFG_STSBASE + (256*10))
#define CSFC5_STS_KADM__base    (CSFC5_CFG_STSBASE + (256*11))
#define CSFC5_STS_KDC__base     (CSFC5_CFG_STSBASE + (256*12))
#define CSFP5_STS__base         (CSFC5_CFG_STSBASE + (256*13))
#define CSFC5_STS_PK__base      (CSFC5_CFG_STSBASE + (256*14))
#define CSFC5_STS_BSF__base     (CSFC5_CFG_STSBASE + (256*15))
#define CSFC5_STS_BCRT__base    (CSFC5_CFG_STSBASE + (256*16))
#define CSFC5_STS_CRL__base     (CSFC5_CFG_STSBASE + (256*19))


#include <csf/sts/asnx_sts.hs>
#include <csf/sts/cfg_sts.hs>
#include <csfc5/sts/asn_sts.hs>
#include <csfc5/sts/bcrt_sts.hs>
#include <csfc5/sts/bsfe_sts.hs>
#include <csfc5/sts/c5_sts.hs>
#include <csfc5/sts/c5c_sts.hs>
#include <csfc5/sts/cc_sts.hs>
#include <csfc5/sts/cks_sts.hs>
#include <csfc5/sts/crl_sts.hs>
#include <csfc5/sts/crs_sts.hs>
#include <csfc5/sts/kt_sts.hs>
#include <csfc5/sts/p5_sts.hs>
#include <csfc5/sts/pkca_sts.hs>
#include <csfc5/sts/rc_sts.hs>

#if defined( _WINDOWS ) || defined(WIN32) || defined(_WIN32)
#include <gssapi/sts/errc.hs>
#include <gssapi/sts/errk5.hs>
#include <gssapi/sts/errs.hs>
#include <gssapi/sts/errdflt.hs>
#include <gssapi/sts/errr.hs>
#else
#include <gssapi/sts/errc_sts.hs>
#include <gssapi/sts/errk5_sts.hs>
#include <gssapi/sts/errs_sts.hs>
#include <gssapi/sts/errdflt_sts.hs>
#include <gssapi/sts/errr_sts.hs>
#endif



#endif
