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
 *	@(#)$RCSfile: ustat.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/05/12 18:02:14 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 


#ifndef _SYS_USTAT_H_
#define _SYS_USTAT_H_

#include <sys/types.h>

#define FS_NMLN		6

struct  ustat
{
	daddr_t	f_tfree;		/* total free */
	ino_t	f_tinode;		/* total inodes free */
	char	f_fname[FS_NMLN];	/* filsys name */
	char	f_fpack[FS_NMLN];	/* filsys pack name */
};

_BEGIN_CPLUSPLUS
extern int ustat __((dev_t, struct ustat *));
_END_CPLUSPLUS

#endif /* _SYS_USTAT_H_ */

