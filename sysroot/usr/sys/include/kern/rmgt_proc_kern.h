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
 * @(#)$RCSfile: rmgt_proc_kern.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/09/27 17:23:06 $
 */
/*
 * Aurema Pty. Limited has provided specific written authorization to
 * Compaq Computer Corporation to include the source material found
 * in this file in the Tru64 UNIX product.  Possession and use of this
 * material is authorized by Compaq Computer Corporation to licensed
 * users of the Tru64 UNIX binary or source product.  No other right
 * to use this source material is implied by possession thereof.
 */

/*
 *  This computer program is a proprietary trade secret of Aurema Pty. Limited.
 *  Possession and use of this program shall be strictly in accordance with a
 *  license agreement between the user and Aurema Pty. Limited.  Receipt and
 *  possession of this program does not convey any rights to divulge, reproduce,
 *  or allow others to use it without specific written authorization of
 *  Aurema Pty. Limited.
 *
 *  Copyright 2000, an unpublished work by Aurema Pty. Limited.
 *  All rights reserved.
 */

#ifndef __TRU64_RMGT_PROC_KERN_H
#define __TRU64_RMGT_PROC_KERN_H

extern int call_rmgt_proc_newproc(struct proc *, struct proc *);

extern int call_rmgt_proc_exec(struct proc *, dev_t, ino_t, int, void *, int, void *);

extern int call_rmgt_proc_setruid(struct proc *, uid_t, uid_t);

extern int call_rmgt_proc_setrgid(struct proc *, gid_t, gid_t);

extern void call_rmgt_proc_exit(struct proc *);

#endif  /* __TRU64_RMGT_PROC_KERN_H */
