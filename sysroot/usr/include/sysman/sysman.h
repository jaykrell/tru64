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
 * @(#)$RCSfile: sysman.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/01/21 14:36:03 $
 */


#ifndef __SYSMAN_H__
#define __SYSMAN_H__

#include <io/common/hwc_reg.h>

int
get_message (nl_catd, const char *, const char *, const char *, \
   const char **, char *);

indictStatus_t
indictObject (indictInfo_t *);

#endif /* __SYSMAN_H__ */
