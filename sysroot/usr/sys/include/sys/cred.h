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
 * @(#)$RCSfile: cred.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1993/08/18 21:29:15 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */
/** Copyright (c) 1990  Mentat Inc.
 ** cred.h 2.1, last change 11/14/90
 **/

#ifndef _SYS_CRED_H
#define _SYS_CRED_H

/*
 * Define "struct cred" for V.4 Streams drivers.
 * The Streams spec calls out only cr_uid and cr_gid.
 */

#include <sys/ucred.h>

typedef struct ucred	cred_t;

/* TEMPORARY (also questionable) */
#define	cr_ruid	cr_uid
#define	cr_rgid	cr_gid
#define	cr_suid	cr_uid
#define	cr_sgid	cr_gid

#endif
