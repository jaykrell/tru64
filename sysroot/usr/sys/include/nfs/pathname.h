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
 * @(#)$RCSfile: pathname.h,v $ $Revision: 1.1.9.3 $ (DEC) $Date: 1999/03/16 10:00:31 $
 */
/*	@(#)pathname.h	2.3 89/03/20 NFSSRC4.0 from 2.6 86/07/16 SMI	*/

#ifndef _PATHNAME_H_
#define _PATHNAME_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Pathname structure.
 * System calls which operate on path names gather the
 * pathname from system call into this structure and reduce
 * it by peeling off translated components.  If a symbolic
 * link is encountered the new pathname to be translated
 * is also assembled in this structure.
 */
struct pathname {
	char	*pn_buf;		/* underlying storage */
	char	*pn_path;		/* remaining pathname */
	u_int	pn_pathlen;		/* remaining length */
};

#define PN_STRIP 0x00		/* Strip next component off pn */
#define PN_PEEK	0x01  		/* Only peek at next pn component */

#define	pn_peekchar(PNP)	((PNP)->pn_pathlen!=0?*((PNP)->pn_path):(char)0)
#define pn_pathleft(PNP)	((PNP)->pn_pathlen)
#define pn_getpath(PNP)		((PNP)->pn_path)

extern int	pn_alloc(struct pathname *);	/* allocat buffer for pathname */

extern void	pn_free(struct pathname *);	/* free pathname buffer */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
