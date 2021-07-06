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
 * @(#)$RCSfile: sad.h,v $ $Revision: 1.1.9.5 $ (DEC) $Date: 1995/01/26 18:52:47 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/** Copyright (c) 1990  Mentat Inc.
 ** sad.h 2.1, last change 11/14/90
 **/

#ifndef _SYS_SAD_H
#define _SYS_SAD_H
#ifdef __cplusplus
extern "C" {
#endif

#define	MAXAPUSH	8

#include <sys/ioctl.h>
#ifdef _KERNEL
#include <sys/stropts.h>
#else
#include <stropts.h>
#endif

/* Ioctl commands for sad driver */
#define	SAD_SAP		_IO('A', 0x1)	/* Set autopush information */
#define	SAD_GAP		_IO('A', 0x2)	/* Get autopush information */
#define	SAD_VML		_IO('A', 0x3)	/* Validate a list of modules (uses str_list structure) */

/* Ioctl structure used for SAD_SAP and SAD_GAP commands */
struct strapush {
	uint	sap_cmd;
	long	sap_major;
	long	sap_minor;
	long	sap_lastminor;
	long	sap_npush;
	char	sap_list[MAXAPUSH][FMNAMESZ+1];
};

/* Command values for sap_cmd */
#define	SAP_ONE		1	/* Configure a single minor device */
#define	SAP_RANGE	2	/* Configure a range of minor devices */
#define	SAP_ALL		3	/* Configure all minor devices */
#define	SAP_CLEAR	4	/* Clear autopush information */

#ifdef _KERNEL
extern int sad_get_autopush(int, int, struct strapush *);
#endif

#ifdef __cplusplus
}
#endif
#endif
