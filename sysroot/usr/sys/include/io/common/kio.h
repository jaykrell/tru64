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
/************************************************************************
  HINT: set tabstops to 4
 ************************************************************************/
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: kio.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1997/07/21 21:08:58 $
 */

/************************************************************************
 *
 *  kio.h
 *
 *  This file contains the defines/structures and routine prototypes for
 *  the routines that do kernel-level file io.
 */

#ifndef _KIO_H_
#define _KIO_H_

typedef void *		kio_handle_t;


/*
 * kernel-level io interface routine prototypes
 *
 * Notes On Usage:
 *
 *    Do not call theses routines with any locks held.
 *
 *    The callee is responsibile for allocating the storage area for the
 *       handle. Thus, the callee should declare a handle as follows,
 *       "kio_handle_t file_handle;" and use "&file_handle" for the
 *       value of handlep in the routines below.
 */
int		kio_open  (caddr_t filename, int fmode, int cmode, kio_handle_t *handlep);
int		kio_close (kio_handle_t *handlep);
int		kio_stat  (kio_handle_t *handlep, struct stat *sb);
int		kio_stat2 (char *filename, struct stat *sb);
int		kio_lock  (kio_handle_t *handlep, int locktype);
int		kio_unlock(kio_handle_t *handlep, int locktype);
int		kio_read  (kio_handle_t *handlep, caddr_t buf, int count, int *resid);
int		kio_write (kio_handle_t *handlep, caddr_t buf, int count, int *resid);
int		kio_lseek (kio_handle_t *handlep, off_t offset, int whence);
int		kio_ftell (kio_handle_t *handlep, long *offset);

#endif /* not _KIO_H_ */


