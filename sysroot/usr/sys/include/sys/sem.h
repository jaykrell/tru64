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
 *	@(#)$RCSfile: sem.h,v $ $Revision: 4.2.44.1 $ (DEC) $Date: 2001/10/09 18:10:51 $
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


#ifndef _SYS_SEM_H_
#define _SYS_SEM_H_

#include <standards.h>
#ifdef SEC_IPC_ACCESS
#include <sys/sp_attr.h>
#endif
#include <sys/ipc.h>

#ifdef _XOPEN_SOURCE

#if defined (__cplusplus)
struct undo_entry;
#endif

#ifdef _KERNEL
#include <kern/lock.h>
#include <kern/sched.h>
#endif 

/*
 *	Semaphore Operation Flags.
 */

#define	SEM_UNDO	010000	/* set up adjust on exit entry */

/*
 *	Semctl Command Definitions.
 */

#define	GETNCNT	3	/* get semncnt */
#define	GETPID	4	/* get sempid */
#define	GETVAL	5	/* get semval */
#define	GETALL	6	/* get all semval's */
#define	GETZCNT	7	/* get semzcnt */
#define	SETVAL	8	/* set semval */
#define	SETALL	9	/* set all semval's */

/*
 *	There is one semaphore structure for each semaphore in the system.
 */

struct sem {
	ushort_t	semval;		/* semaphore text map address	*/
	pid_t		sempid;		/* pid of last operation	*/
	ushort_t	semncnt;	/* # awaiting semval > cval	*/
	ushort_t	semzcnt;	/* # awaiting semval = 0	*/
#ifdef _KERNEL 
	struct		wait_queue semncnt_wq; /* channel for waiters */
	struct		wait_queue semzcnt_wq; /* channel for waiters */
	ushort_t	sem_op_outstanding; /* sem operations in progress */
#endif /* _KERNEL */
};

/*
 *	There is one semaphore id data structure for each set of semaphores
 *		in the system.
 */

struct semid_ds {
	struct ipc_perm	sem_perm;	/* operation permission struct	*/
	struct sem	*sem_base;	/* ptr to first semaphore in set*/
	ushort_t	sem_nsems;	/* # of semaphores in set	*/
	time_t		sem_otime;	/* last semop time		*/
	time_t		sem_ctime;	/* last change time		*/
};

#ifdef _KERNEL
struct semid_internal {
	struct semid_ds s;
	decl_simple_lock_data(,sem_slock) /* lock for accessing semaphore */
#ifdef SEC_IPC_ACCESS
	secinfo_t    	*sem_secattr;   /* Security Attribute, is expected to
                                           be the first field in the kernel
					   defined fields following the user
					   defined data so ipc stat works.
					 */
#endif /* SEC_IPC_ACCESS */
};
#endif /* _KERNEL */

/*
 *	User semaphore template for semop system calls.
 */

struct sembuf {
	ushort_t	sem_num;	/* semaphore #			*/
	short		sem_op;		/* semaphore operation		*/
	short		sem_flg;	/* operation flags		*/
};

#ifndef _KERNEL
#ifdef _NO_PROTO
extern int semctl();
extern int semget();
extern int semop();
#else
#if defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C"
{
#endif
extern int semget(key_t, int, int);
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_XOPEN_SOURCE)
extern int semop(int, struct sembuf *, size_t); 	/* move to base in pass 2 */
#else
extern int semop(int, struct sembuf *, uint_t);
#endif   /* _XOPEN_SOURCE_EXTENDED || _XOPEN_SOURCE */
extern int semctl(int, int, int, ...);
#if defined(__cplusplus)
}
#endif
#endif
#endif /* _NO_PROTO */
#else

struct proc;
 
extern int semctl(struct proc *p, void *args, long *retval);
extern int semget(struct proc *p, void *args, long *retval);
extern int semop(struct proc *p, void *args, long *retval);
#endif /* _KERNEL   */

#endif /* _XOPEN_SOURCE */

#ifdef _OSF_SOURCE
/*
 * 	Implementation Constants. 
 */

#define	PSEMN	(PZERO + 3)	/* sleep priority waiting for greater value */
#define	PSEMZ	(PZERO + 2)	/* sleep priority waiting for zero */

/*
 * 	Permission Definitions. 
 */
#define	SEM_A	IPC_W	/* alter permission */
#define	SEM_R	IPC_R	/* read permission */

/*
 * 	There is one undo structure per process in the system. 
 *      each sem_undo struct has: 
 *       - a pointer to the next active undo struct,       
 * 	 - the number of active entries, 
 *       - and an array of undo struct entries. 
 */

struct sem_undo {
	struct sem_undo 	*un_nextp;	/* ptr to next active undo structure */
	short           	un_cnt;		/* # of active entries */
	struct undo_entry 	*un_entp;	/* ptr to list of undo entries */
};

struct undo_entry {
	struct undo_entry	*uent_nextp;	/* pointer to next undo structure */
	short           	uent_aoe;	/* adjust on exit values */
	short           	uent_num;	/* semaphore # */
	int             	uent_id;	/* semid */
};

/*
 *	Semaphore information structure. 
 */
struct seminfo {
	int	semmni,		/* # of semaphore identifiers */
		semmsl,		/* max # of semaphores per id */
		semopm,		/* max # of operations per semop call */
		semume,		/* max # of undo entries per process */
		semvmx,		/* semaphore maximum value */
		semaem;		/* adjust on exit max value */
        long	sema;		/* # of semaphore operations */
};

#ifdef _KERNEL
#ifndef REPLICATED
#define REPLICATED
#endif
extern struct semid_internal *sema;
extern REPLICATED struct seminfo seminfo;
#endif /* _KERNEL */

#endif /* _OSF_SOURCE */

#endif /* _SYS_SEM_H_ */
