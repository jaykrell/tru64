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
 * 
 */
/*
 * @(#)$RCSfile: guids.h,v $ $Revision: 1.1.2.13 $ (DEC) $Date: 2001/11/02 21:46:59 $
 */

#ifndef _COMPAQ_GUIDS_H_
#define _COMPAQ_GUIDS_H_

#define compaq_cssm_guid_init \
  {0xd6b5e820, 0xf376, 0x11d3, {0x9b, 0xea, 0x0, 0x8, 0xc7, 0x4f, 0xe1, 0x65}}

#define compaq_mds_guid_init \
  {0xd6b5e821, 0xf376, 0x11d3, {0x9b, 0xea, 0x0, 0x8, 0xc7, 0x4f, 0xe1, 0x65}}
#define compaq_mds_guid_string \
   "{d6b5e821-f376-11d3-9bea-0008c74fe165}"

#define compaq_t64csp_guid_init \
  {0xd6b5e822, 0xf376, 0x11d3, {0x9b, 0xea, 0x0, 0x8, 0xc7, 0x4f, 0xe1, 0x65}}

#define COMPAQ_T64CSP_UNSUPPORTED_ALG_TYPE      (CSSM_CSP_PRIVATE_ERROR + 1)
#define COMPAQ_T64CSP_POLICY_FILE_READ_ERROR    (CSSM_CSP_PRIVATE_ERROR + 2)

#define compaq_t64csp_subserviceid 0


/* PassThroughId's for the PassThrough function */

#define COMPAQ_T64CSP_FORCE_LOAD_CAP_TABLE 0 /* Return Capability Table */
#define COMPAQ_T64CSP_GET_CAP_TABLE        1 /*
					      * Cause the Capability Table
					      * in MDS to be updated
					      */
#define COMPAQ_T64CSP_JUST_GEN_CAP_TABLE   2 /*
					      * Just generate the Capability
					      * Table for library lookup
					      */
#endif /* _COMPAQ_GUIDS_H_ */
