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
 * @(#)$RCSfile: uadmin.h,v $ $Revision: 1.1.5.2 $ (DEC) $Date: 1999/02/09 19:03:57 $
 */
#ifndef _SYS_UADMIN_H
#define _SYS_UADMIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define	A_REBOOT	0x01
#define	A_SHUTDOWN	0x02
#define	A_REMOUNT	0x04

#define	AD_HALT		0
#define	AD_BOOT		1
#define	AD_IBOOT	2


#if (defined(__STDC__) || defined(__cplusplus)) && !defined(_KERNEL)
int uadmin(int, int, int);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif	/* _SYS_UADMIN_H */
