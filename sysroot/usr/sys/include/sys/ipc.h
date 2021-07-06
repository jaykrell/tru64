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
 *	@(#)$RCSfile: ipc.h,v $ $Revision: 4.3.27.5 $ (DEC) $Date: 2000/03/21 16:41:11 $
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

#ifndef _SYS_IPC_H_
#define _SYS_IPC_H_

#include	<standards.h>

#ifdef _XOPEN_SOURCE

#include <sys/types.h>

typedef long	mtyp_t;		/* ipc message type */

/* Common IPC Structures */
struct ipc_perm {
	uid_t		uid;		/* owner's user id	*/
	gid_t		gid;		/* owner's group id	*/
	uid_t		cuid;		/* creator's user id	*/
	gid_t		cgid;		/* creator's group id	*/
	mode_t		mode;		/* access modes		*/
	ushort_t	seq;		/* slot usage sequence number */
	key_t		key;		/* key			*/
};

/* common IPC operation flag definitions */
#define	IPC_CREAT	0001000		/* create entry if key doesn't exist */
#define	IPC_EXCL	0002000		/* fail if key exists */
#define	IPC_NOWAIT	0004000		/* error if request must wait */

/* Keys. */
#define	IPC_PRIVATE	(key_t)0	/* private key */

/* Control Commands. */
#define	IPC_RMID	0	/* remove identifier */
#define	IPC_SET		1	/* set options */
#ifdef	_KERNEL
#define	IPC_STAT_V40	2	/* for V40 backward compatibility */
#endif
/*	SHM_LOCK	3	see shm.h */
/*	SHM_UNLOCK	4	see shm.h */
/*	GETNCNT		3	see sem.h */
/*	GETPID		4	see sem.h */
/*	GETVAL		5	see sem.h */
/*	GETALL		6	see sem.h */
/*	GETZCNT		7	see sem.h */
/*	SETVAL		8	see sem.h */
/*	SETALL		9	see sem.h */
#ifdef	_KERNEL
#define	IPC_STAT_V50	10	/* for V50 compatibility */
#endif
#define	IPC_STAT	12	/* get options */

#endif /* _XOPEN_SOURCE */

#ifdef _OSF_SOURCE

/* Common ipc_perm mode Definitions. */
#define	IPC_ALLOC	0100000		/* entry currently allocated	*/
#define	IPC_RESERVED	0200000		/* reserved for allocation	*/
#define	IPC_R		0000400		/* read or receive permission	*/
#define	IPC_W		0000200		/* write or send permission	*/

/* type of ipc */
#define IPC_MSG		1
#define IPC_SEM		2
#define IPC_SHM		3

#endif /* _OSF_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#ifndef _KERNEL
#ifdef _NO_PROTO
extern key_t	ftok();
#else
#if defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C"
{
#endif
#ifdef _XOPEN_SOURCE_EXTENDED
extern key_t ftok(const char *, int);
#else	/* _OSF_SOURCE */
extern key_t ftok(char *, char);
#endif

#if defined(__cplusplus)
}
#endif
#endif
#endif /* _NO_PROTO */
#endif /* _KERNEL */

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef KERNEL
/*
 * offsetof gives the offset of the specified member
 * within the designated structure; it is used to determine
 * the size of the structure up to, but not
 * including the named element, which will be the size of the struct
 * up to the previous element inclusive, if there is no padding
 * required for the named element.
 *	t = structure name
 *	e =element name.
 */

#define ipc_offsetof(t,e)	((long) (&((t *) 0)->e))
#endif

#ifdef	_KERNEL
extern int ipcget(key_t, long , int , int *, struct ipc_perm **);
#endif
#endif /* _SYS_IPC_H_ */
