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
 * @(#)$RCSfile: rmgt_proc.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/09/27 17:23:05 $
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

#ifndef	__TRU64_RMGT_PROC_H
#define	__TRU64_RMGT_PROC_H

typedef struct rmgt_proc_ops {
	const int interface_version;
	const char *policy_name;
	struct rmgt_proc_ops *next;

	int (*newproc_vetoed)(pid_t, uid_t, gid_t, pid_t);
	void (*newproc_cancel)(pid_t, uid_t, gid_t, pid_t);
	void (*newproc_commit)(pid_t, uid_t, gid_t, pid_t);

	int (*exec_vetoed)(pid_t, dev_t, ino_t, int, void *, int, void *);
	void (*exec_cancel)(pid_t, dev_t, ino_t, int, void *, int, void *);
	void (*exec_commit)(pid_t, dev_t, ino_t, int, void *, int, void *);

	int (*setruid_vetoed)(pid_t, uid_t, uid_t);
	void (*setruid_cancel)(pid_t, uid_t, uid_t);
	void (*setruid_commit)(pid_t, uid_t, uid_t);

	int (*setrgid_vetoed)(pid_t, gid_t, gid_t);
	void (*setrgid_cancel)(pid_t, gid_t, gid_t);
	void (*setrgid_commit)(pid_t, gid_t, gid_t);

	void (*exit)(pid_t);
} rmgt_proc_ops_t;

extern int register_rmgt_proc(struct rmgt_proc_ops *ops);
extern int unregister_rmgt_proc(struct rmgt_proc_ops *ops);
extern int count_rmgt_proc(struct rmgt_proc_ops *ops);

extern void rmgt_proc_lock_init(void);

#endif	/* __TRU64_RMGT_PROC_H */
