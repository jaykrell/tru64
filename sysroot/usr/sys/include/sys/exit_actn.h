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
 * @(#)$RCSfile: exit_actn.h,v $ $Revision: 1.1.20.1 $ (DEC) $Date: 2000/09/22 18:18:44 $
 */

#ifndef	_SYS_EXIT_ACTN_H_
#define _SYS_EXIT_ACTN_H_

#ifdef _KERNEL

#include <kern/task.h>

/*
 *	The exit_actn struct.
 *	These structures are dynamically allocated and chained onto
 *	the u area to indicate kernel functions to be called before
 *	process exit and exec. See ../bsd/kern_exit.c & kern_exec.c.
 */
typedef void (xafunc)(void *, int, task_t);

struct exit_actn {
	struct exit_actn *xa_next;
	xafunc	 	 *xa_func;
	void		 *xa_arg;
	int		 xa_flags;
	int		 xa_priority;
};

/*
 * Kernel Exit/Exec handler flags.
 */
#define XA_EXIT   0x1	/* call on EXIT */
#define XA_EXEC   0x2	/* call on EXEC */
#define XA_KOE	  0x4	/* keep on EXEC */
#define XA_ABORT  0x8	/* abort EXEC call */
#define XA_NOWAIT 0x10 	/* don't sleep on memory allocation */
#define XA_SYSTEM 0x20	/* call for every process exit */
#define XA_FORK	  0x40	/* call on Fork */
#define XA_KOF	  0x80	/* keep on parent chain when forking */
#define XA_IOF	  0x100 /* inherit on fork, add to child's chain */

#define XA_LOCK_WRITE()	lock_write(&sys_exitp_lock)
#define XA_LOCK_READ()	lock_read(&sys_exitp_lock)
#define XA_UNLOCK()	lock_done(&sys_exitp_lock)

#define XA_PRIORITY_REGULAR	100

extern lock_data_t sys_exitp_lock;
extern struct exit_actn *xa_handler_register(xafunc, void *, int, int);
extern struct exit_actn *xa_handler_register_pid(xafunc, void *, int, pid_t, int);
extern int xa_handler_unregister(xafunc, void *, int);
extern int xa_handler_unregister_pid(xafunc, void *, int, pid_t);
extern int xa_handler_callout(int);
extern void *xa_handler_lookup(xafunc *, void *, int, int (*)(void *, void *));
extern void xa_lock_init(void);

#endif /* _KERNEL */
#endif	/* _SYS_EXIT_ACTN_H_ */

