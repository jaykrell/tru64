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
 *	@(#)$RCSfile: msg.h,v $ $Revision: 4.2.28.1 $ (DEC) $Date: 1999/11/30 12:55:04 $
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




#ifndef _SYS_MSG_H_
#define _SYS_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#ifdef SEC_IPC_ACCESS
#include <sys/sp_attr.h>
#endif
#include <sys/ipc.h>
#if KERNEL
#include <kern/lock.h>
#endif 

#ifdef _XOPEN_SOURCE

/*
 *	Message Operation Flags.
 */

#define	MSG_NOERROR	010000	/* no error if big message */
#define	MSG_TAG		020000	/* tag messages with pid as type */

/*
 *	Structure Definitions
 */

/*
 *	There is one msg structure for each message that may be in the system.
 */

#if defined(_KERNEL) || defined(_OSF_SOURCE)

struct msg {
	struct msg     *msg_next;	/* ptr to next message on q */
	long            msg_type;	/* message type */
	long		msg_ts; 	/* message text size */
	caddr_t         msg_addr;	/* message text address */
};

struct msg_wait {
	struct msg_wait *msg_wait_next; /* ptr to next msg type on wait q */
	long		msg_wait_type;  /* message type waiting on */
	long		msg_wait_cnt;   /* num of msgs waiting on for type */
};

#endif /* _KERNEL || _OSF_SOURCE */


/*
 *	There is one msg queue id data structure for each q in the system.
 */

struct msqid_ds {
	struct ipc_perm	msg_perm;	/* operation permission struct */
	struct msg	*msg_first;	/* ptr to first message on q */
	struct msg	*msg_last;	/* ptr to last message on q */
	msglen_t	msg_cbytes;	/* current # bytes on q */
	msgqnum_t	msg_qnum;	/* # of messages on q */
	msglen_t	msg_qbytes;	/* max # of bytes on q */
	pid_t		msg_lspid;	/* pid of last msgsnd */
	pid_t		msg_lrpid;	/* pid of last msgrcv */
	time_t		msg_stime;	/* last msgsnd time */
	time_t		msg_rtime;	/* last msgrcv time */
	time_t		msg_ctime;	/* last change time */
	struct msg_wait	*msg_wait_list; /* list of message types */
                                        /* waiting on */
};

#if KERNEL
struct msqid_internal {
	struct msqid_ds	m;
	decl_simple_lock_data(,msg_slock)
#ifdef SEC_IPC_ACCESS
	secinfo_t	*msg_secattr;	/* Security Attribute, is expected to
					   be the first field in the kernel
					   defined fields following the user
					   defined data so ipc stat works.
					 */
	long            msg_pag[1];
#else
	long            msg_pag[2];
#endif /* SEC_IPC_ACCESS */
};
#endif

#ifndef _KERNEL
extern int msgget __((key_t, int));
#if _XOPEN_SOURCE>=500
extern ssize_t msgrcv __((int, void *, size_t, long, int));
#else
extern int msgrcv __((int, void *, size_t, long, int));
#endif	/* XSH5 */
extern int msgsnd __((int, const void *, size_t, int));
extern int msgctl __((int, int, struct msqid_ds *));
#endif /* _KERNEL */

#endif /* _XOPEN_SOURCE */

#ifdef	_OSF_SOURCE
/*
 * 	Implementation Constants. 
 */

#define	PMSG	(PZERO + 2)	/* message facility sleep priority */

/*
 * 	Permission Definitions. 
 */
#define	MSG_R		IPC_R	/* read permission */
#define	MSG_W		IPC_W	/* write permission */

/*
 *	ipc_perm Mode Definitions.
 */
#define	MSG_RWAIT	01000	/* a reader is waiting for a message */
#define	MSG_WWAIT	02000	/* a writer is waiting to send */


/*
 *	User message buffer template for msgsnd and msgrcv system calls.
 */

struct msgbuf {
	mtyp_t	mtype;		/* message type */
	char	mtext[1];	/* message text */
};


/*
 *	Message information structure.
 */

struct msginfo {
	int	msgmax,	/* max message size */
		msgmnb,	/* max # bytes on queue */
		msgmni,	/* # of message queue identifiers */
	   	msgtql;	/* # of system message headers */
       	long	msg;	/* # of send and receive messages */
};

#endif	/* _OSF_SOURCE */

#ifdef _KERNEL
extern struct msqid_internal *msgque;
extern struct msginfo msginfo;
#endif  /* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif  /* _SYS_MSG_H_ */

