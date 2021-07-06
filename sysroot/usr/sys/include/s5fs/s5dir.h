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
 *	@(#)$RCSfile: s5dir.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1995/02/10 21:11:30 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * 20-aug-1991: vipul patel
 *	OSF/1 Release 1.0.1; lock for dir() of libc.
 */

#ifndef _S5_DIR_H_
#define _S5_DIR_H_

#include <s5fs/s5param.h>
/*
 * NOTE: s5ino_t is defined as ushort while ino_t is defined as ulong in UFS
 *
 */

struct	s5direct
{
	s5ino_t	d_ino;
	char	d_name[s5DIRSIZ];
};

/*
 * Used by s5fs_readdir to create file system independent directory entries.
 * This format is required by directory routines in libc.
 */
#define s5DIRECTSIZE sizeof(struct s5direct)

struct  gpdirect
{
        u_long  d_ino;
	u_short d_reclen;
	u_short d_namlen;
	char    d_name[s5DIRSIZ];
        u_short d_padding;
};
#define gpDIRECTSIZE (sizeof(struct gpdirect))


struct  s5dirtemp
{
	s5ino_t	dot_ino;
	char	dot_name[s5DIRSIZ];
	s5ino_t	dotdot_ino;
	char	dotdot_name[s5DIRSIZ];
};

#endif /*  _S5_DIR_H_ */
