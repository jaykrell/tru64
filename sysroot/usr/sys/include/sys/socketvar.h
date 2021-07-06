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
 * 
 */
/*	
 *	@(#)$RCSfile: socketvar.h,v $ $Revision: 4.2.104.2 $ (DEC) $Date: 2002/01/31 19:44:39 $
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	socketvar.h	7.6 (Berkeley) 9/4/89
 *	Merged: socketvar.h	7.11 (Berkeley) 6/30/90
 */

#ifndef	_SYS_SOCKETVAR_H_
#define	_SYS_SOCKETVAR_H_

#ifdef __cplusplus
extern "C" {
/* forward decls for C++ */
struct socklocks;
#endif

#if	defined(_KERNEL) && !defined(_NET_GLOBALS_H_)
#include "net/net_globals.h"
#define sb_lock_t	lock_t
#else
typedef struct lock *	sb_lock_t;
#endif

#include <sys/secdefines.h>
#if	SEC_ARCH
#include <sys/security.h>
#endif
#include <sys/time.h>

/*
 * Kernel structure per socket.
 * Contains send and receive buffer queues,
 * handle on protocol and pointer to protocol
 * private data and error information.
 */
struct socket {
	int	so_type;		/* generic type, see socket.h */
	int	so_options;		/* from socket call, see socket.h */
	short	so_linger;		/* time to linger while closing */
	short	so_timeo;		/* connection timeout */
	int	so_state;		/* internal state flags SS_*, below */
	caddr_t	so_pcb;			/* protocol control block */
	struct	protosw *so_proto;	/* protocol handle */
	struct	socklocks *so_lock;	/* socket structure lock(s) */
	int	so_atomic_flags;	/* atomic flags set and cleared using 
					 * atomic ops */
	int pad_a[5];
/*
 * Variables for connection queueing.
 * Socket where accepts occur is so_head in all subsidiary sockets.
 * If so_head is 0, socket is not related to an accept.
 * For head socket so_q0 queues partially completed connections,
 * while so_q is a queue of connections ready to be accepted.
 * If a connection is aborted and it has so_head set, then
 * it has to be pulled out of either so_q0 or so_q.
 * We allow connections to queue up based on current queue lengths
 * and limit on number of queued connections for this socket.
 */
/* 64-byte alignment */
	struct	socket *so_head;	/* back pointer to accept socket */
	struct	socket *so_q0;		/* queue of partial connections */
	struct	socket *so_q;		/* queue of incoming connections */
	struct	socket *so_dq;		/* queue of defunct connections */
	unsigned short	so_q0len;	/* partials on so_q0 */
	unsigned short	so_qlen;	/* number of connections on so_q */
	unsigned short	so_qlimit;	/* max number queued connections */
	short	so_dqlen;		/* listener dequeues in progress */
	int	so_error;		/* error affecting connection */
	int	so_special;		/* special state flags SP_*, below */
	pid_t	so_pgid;		/* pgid for signals */
	u_int	so_oobmark;		/* chars to oob mark */
	int pad_b[2];

/* 64-byte alignment */
	struct	sockbuf {
		u_int	sb_cc;		/* actual chars in buffer */
		u_int	sb_hiwat;	/* max actual char count */
		u_int	sb_mbcnt;	/* chars of mbufs used */
		u_int	sb_mbmax;	/* max chars of mbufs to use */
		u_int	sb_dbcnt;	/* DART: chars of dart-style used */
		u_int	sb_dbmax;	/* DART: max chars to use */
		int	sb_lowat;	/* low water mark */
		int     sb_sel;         /* select hint */	
		struct	mbuf *sb_mb;	/* the mbuf chain */
		struct sbselque {	/* process selecting read/write */
			struct sbselque *next, *prev;
		} sb_selq;
		int	sb_flags;	/* flags, see below */
		int pad_c[1];

/* 64-byte alignment */
		struct timeval	sb_timeo;	/* timeout value in seconds and microsec */
#if	__STDC__
		void	(*sb_wakeup)(caddr_t, int);
#else
		void	(*sb_wakeup)();	/* upcall instead of sowakeup */
#endif
		caddr_t	sb_wakearg;	/* (*sb_wakeup)(sb_wakearg, state) */
		sb_lock_t sb_lock;	/* sockbuf lock (in socklocks) */
		struct mbuf *sb_last_mb;/* last mbuf on the current chain 
					 * only valid if sb_mb set */
#ifndef __VMS
		int pad_d[6];
#else /* __VMS */
		int	sb_ovms_flags;	/* OVMS flags */
		int	sb_ovms_wait;	/* OVMS wait flag */
		caddr_t	sb_ovms_krp ;	/* Pending TCPIP_KRP address, if any */
#endif /* __VMS */
	} so_rcv, so_snd;
#define	SB_MAX		(1024*1024)	/* default for max chars in sockbuf */
#define	SB_LOCK		0x01		/* lock on data queue */
#define	SB_WANT		0x02		/* someone is waiting to lock */
#define	SB_WAIT		0x04		/* someone is waiting for data/space */
#define	SB_SEL		0x08		/* someone is selecting */
#define	SB_ASYNC	0x10		/* ASYNC I/O, need signals */
#define	SB_NOTIFY	(SB_WAIT|SB_SEL|SB_ASYNC)
#define	SB_COLL		0x20		/* collision selecting (UNIX) */
#define	SB_NOINTR	0x40		/* operations not interruptible */
#define	SB_WAKEONE	0x80		/* wakeup only one on notify */
#define	SB_WAITING	0x100		/* MSG_WAITALL receive in progress */
#define	SB_SET_LOWAT	0x200		/* user set sb_lowat */
#define	SB_WIRE		0x400		/* Wire don't copy user pages(currently output only) */
#define SB_NEEDSFLUSH	0x800		/* next unlock flush buffer */
#define SB_USELAST	0x1000		/* code expects the use of the sb_last_mb */
#define	SB_INHERIT	(SB_NOINTR|SB_WAKEONE|SB_WIRE|SB_USELAST)
#define	SB_DBMAX_DEF	(1 << 30)	/* DART */

#ifdef  __VMS
/* The following bits are defined in the sb_ovms_flags field */
#define	SB_OVMS_WAKE_IN_PROGRESS 0x01	/* sbwakeup() has executed recently */
#define	SB_OVMS_SND_IN_PROGRESS  0x02	/* INET_SOSEND_xxx is executing  */
#define	SB_OVMS_FIRST_CANTRCV	 0x03	/* first transmit after SS_CANTRCVMORE 
					 * set, has been seen */
#endif /* __VMS */	

/* 64-byte alignment */
#if	SEC_ARCH
	tag_t	so_tag[SEC_TAG_COUNT];	/* security policy tags */
#endif
	struct	socket *so_q0_prev;	/* end of queue of partial connections */
	struct	socket *so_q_prev;	/* end of queue of incoming connections */
#ifndef  __VMS
	int pad_e[4];
#else /*  __VMS */
	caddr_t	so_ovms_ucb;		/* UCB address */
	caddr_t so_ovms_inetkvci;	/* INETVCI$ address */
/* Needs Quadword alignment */
	struct	rcv_ovms_mbufq {	/* reference list */
		struct rcv_ovms_mbufq *forw, *back;
	} so_ovms_rcv_mbufq;
#define ucb      so_ovms_ucb
#define inetkvci so_ovms_inetkvci
#endif /* __VMS */	
};

/*
 * Socket state bits.
 */
#define	SS_NOFDREF		0x001	/* no file table ref any more */
#define	SS_ISCONNECTED		0x002	/* socket connected to a peer */
#define	SS_ISCONNECTING		0x004	/* in process of connecting to peer */
#define	SS_ISDISCONNECTING	0x008	/* in process of disconnecting */
#define	SS_CANTSENDMORE		0x010	/* can't send more data to peer */
#define	SS_CANTRCVMORE		0x020	/* can't receive more data from peer */
#define	SS_RCVATMARK		0x040	/* at mark on input */

#define	SS_PRIV			0x080	/* privileged for broadcast, raw... */
#define	SS_NBIO			0x100	/* non-blocking ops */
#define	SS_ASYNC		0x200	/* async i/o notify */
#define	SS_ISCONFIRMING		0x400	/* deciding to accept connection req */

#ifdef __VMS
#define	SS_RESERVED_DUMMY	0x00000800  /* Place holder */
#define	SS_WAITACCEPT		0x00001000  /* UCX wait for accept */
#define	SS_NOUCB		0x00002000  /* UCX invalid UCB ptr to socket */
#define	SS_FRCD_LINGER		0x00004000  /* UCX forced linger on socket */
#define	SS_REM_CLOSED		0x00008000  /* UCXremote socket closed has been 
					     * reported */
#define	SS_OVMS_KERNEL_INTERFACE 0x00010000 /* UCX Kernel Interface Socket */
#endif	/* __VMS */

/*
 * Socket flags set using atomic ops to set and clear bits
 */
#define SOF_FDREF		0x001	/* atomic flag to indicate File ref set for this connection */
#define SOF_FDREF_BIT		0x000	/* atomic flag bit to indicate File ref set for this connection */
#define SOF_CLEARING		0x002	/* atomic flag to indicate Listener is closing and clearing accepted connections */
#define SOF_CLEARING_BIT	0x001	/* atomic flag bit to indicate Listener is closing and clearing accepted connections */
#define SOF_PRIV		0x004	/* atomic flag to indicate user accout is privilaged */
#define SOF_PRIV_BIT		0x002	/* atomic flag bit to indicate user accout is privilaged */
#define SOF_PROTO_USE		0x800	/* atomic flag for use by protocol */
#define SOF_PROTO_USE_BIT	0x800	/* atomic flag bit for use by protocol */

/*
 * Special socket state bits.
 */
#define SP_PIPE			0x0001	/* socket is unnamed pipe (obsolete) */
#define SP_WATOMIC		0x0002	/* pipe write atomicity (obsolete) */
#define SP_NOUAREA		0x0004	/* no u-area available (XTI - XXX) */
#define SP_LOCKABLE		0x0008	/* locking is active for socket */
#define SP_CLOSING		0x0010	/* closing a listening socket */
#define SP_RWAKEUP		0x0020	/* sorwakeup pending release of lock */
#define SP_WWAKEUP		0x0040	/* sowwakeup pending release of lock */
#define SP_EXTPRIV		0x0080	/* SS_PRIV managed externally */
#define SP_XSE			0x0100	/* _XOPEN_SOURCE_EXTENDED socket */
#define SP_NBIO			0x0200  /* force nbio for any children */
#define SP_UNPCONNECTING        0x4000  /* unp_connect in progress */
#define SP_FREEABLE		0x8000	/* free socket on unlock */

#define SP_INHERIT	(SP_PIPE|SP_WATOMIC|SP_NOUAREA|SP_LOCKABLE|SP_XSE|SP_NBIO)

#ifdef	_KERNEL

#ifndef REPLICATED
#define REPLICATED
#endif

/*
 * Macros for sockets, socket locking and socket buffering.
 */

#if	NETSYNC_LOCK

struct  socklocks {
	lock_data_t	sock_lock;
	lock_data_t	snd_lock;
	lock_data_t	rcv_lock;
	int		refcnt;
	struct socket	*sp_wake;
	struct socket	*socketlist ; 
	struct socklocks *nextlock ;
	int pad[2];
};

#define SOCKET_LOCKINIT(so, lp) { \
	(so)->so_lock = (lp); \
	(so)->so_snd.sb_lock = &((lp)->snd_lock); \
	(so)->so_rcv.sb_lock = &((lp)->rcv_lock); \
	(lp)->nextlock = NULL ; \
	(lp)->socketlist = so ; \
	(lp)->refcnt = 1; \
	(lp)->sp_wake = 0; \
	ulock_setup(&((lp)->sock_lock), sock_li, TRUE); \
	ulock_setup(&((lp)->snd_lock), snd_li, TRUE); \
	ulock_setup(&((lp)->rcv_lock), rcv_li, TRUE); \
}

#define SOCKET_LOCKTERMINATE(lp) { \
	ulock_terminate(&(lp)->sock_lock); \
	ulock_terminate(&(lp)->snd_lock); \
	ulock_terminate(&(lp)->rcv_lock); \
}

#define SOCKLOCK_REF(lp) {  \
	simple_lock(&lp->sock_lock.l_lock) ;  \
        lp->refcnt++ ; \
	simple_unlock(&lp->sock_lock.l_lock) ;  \
}

/*
 * In lockmode 0, calls to solock() and sounlock() are dynamically
 * patched out.  
 */
#define SOCKET_LOCK(so)		solock(so)	/* noop lockmode 0 */
#define SOCKET_UNLOCK(so)	sounlock(so)	/* noop lockmode 0 */

#define SOCKET_READ_LOCK(so)	soreadlock(so)	/* noop lockmode 0 */
#define SOCKET_READ_UNLOCK(so)	soreadunlock(so)	/* noop lockmode 0 */

#define SOCKET_LOCK_READERS(so)	soreaders(so)	/* noop lockmode 0 */

#define SOCKET_TRY_WRITE_LOCK(so) solocktry(so) /* noop lockmode 0 */
#define SOCKET_TRY_WRITE_NOASSERT(so) solocktrynoassert(so) /* noop lockmode 0 */

#define SOCKET_LOCK_ONE(so1) solock1(so1)

#define SOCKET_UNLOCK_ONE(so1) sounlock1(so1)

/*
 * Lock order of unpaired sockets is critical to avoid deadlock.
 */
#define SOCKET_LOCK2(so1, so2) { \
	SOCKET_LOCK_ONE(so1) ; \
	if((!SOCKET_ISLOCKED((so2))) && (!SOCKET_TRY_WRITE_NOASSERT(so2))) {\
		if(so1->so_lock > so2->so_lock)  {\
		      SOCKET_LOCK_ONE(so2); \
		} else {\
			SOCKET_UNLOCK_ONE(so1) ; \
			SOCKET_LOCK_ONE(so2) ; \
			SOCKET_LOCK_ONE(so1) ; \
		} \
	} \
}

#define SOCKET_UNLOCK2(so1, so2) {  \
        sounlock((so1));         \
	if ( SOCKET_ISLOCKED(so2))  \
	       SOCKET_UNLOCK_ONE(so2);  \
}

#define SOCKET_UNLOCK_HALF_OF_2(so1, so2) { \
        if( (so1)->so_lock != (so2)->so_lock ) /* same lock */ \
		   SOCKET_UNLOCK_ONE(so2); \
}
/*
 * Lock order of unpaired sockets is critical to avoid deadlock.
 */
#define SOCKET_LOCK_HALF_OF_2(so1, so2) { \
	if ( (!SOCKET_ISLOCKED((so2))) && (!SOCKET_TRY_WRITE_NOASSERT(so2)) ) { \
		/* quick didn't work now have to maintain order */ \
		if(so1->so_lock > so2->so_lock)  { \
		      SOCKET_LOCK_ONE(so2); \
		} else {\
			SOCKET_UNLOCK_ONE(so1) ; \
			SOCKET_LOCK_ONE(so2) ; \
			SOCKET_LOCK_ONE(so1) ; \
		} \
	} \
}

/* The socket is considered locked for assertions if not lockable */
#define SOCKET_ISLOCKED(so)  (!(so->so_special & SP_LOCKABLE) || \
				lock_holder(&((so)->so_lock->sock_lock)))

/* sockbuf locks are currently disabled */
#define SOCKBUF_LOCKTEST	0
#define SOCKBUF_LOCK(sb)	/*ulock_write((sb)->sb_lock)*/
#define SOCKBUF_UNLOCK(sb)	/*ulock_done((sb)->sb_lock)*/
#define SOCKBUF_ISLOCKED(sb)	1 /*(lockmode==0||lock_holder((sb)->sb_lock))*/

#else	/* !NETSYNC_LOCK */

struct  socklocks { int refcnt; };
#define SOCKET_LOCKINIT(so, lp)
#define SOCKET_LOCKTERMINATE(lp)
#define SOCKET_UNLOCK_HALF_OF_2(so1, so2)
#define SOCKET_LOCK_HALF_OF_2(so1, so2)
#define SOCKET_READ_LOCK(so)
#define SOCKET_LOCK(so)
#define SOCKET_LOCK_ONE(so)
#define SOCKET_TRY_WRITE_LOCK(so)	1
#define SOCKET_TRY_WRITE_NOASSERT(so)  1
#define SOCKET_READ_UNLOCK(so)
#define SOCKET_LOCK_READERS(so)	 1
#define SOCKET_UNLOCK(so)
#define SOCKET_UNLOCK_ONE(so)
#define SOCKET_LOCK2(so1, so2)
#define SOCKET_UNLOCK2(so1, so2)
#define SOCKET_ISLOCKED(so)	1
#define SOCKBUF_LOCKTEST	0
#define SOCKBUF_LOCK(sb)
#define SOCKBUF_UNLOCK(sb)
#define SOCKBUF_ISLOCKED(sb)	1

#endif	/* !NETSYNC_LOCK */

/* Bits for network events to sb_wakeup */
#define SE_ERROR	0x0001	/* so_error non-0 */
#define SE_HAVEDATA	0x0002	/* data in send or recv q */
#define SE_HAVEOOB	0x0004	/* oob data in recv q */
#define SE_DATAFULL	0x0008	/* send or recv q is full */
#define SE_CONNOUT	0x0010	/* outgoing connect complete (connect) */
#define SE_CONNIN	0x0020	/* incoming connect complete (listen)  */
#define SE_SENDCONN	0x0040	/* connected for send */
#define SE_RECVCONN	0x0080	/* connected for recv */
#define SE_POLL		0x4000	/* wakeup is synchronous poll */
#define SE_STATUS	0x8000	/* above status bits valid */

/* does socket have a valid u-area associated? (for stats, security, etc) */
#define SOHASUAREA(so)	(!((so)->so_special & SP_NOUAREA))

/* what is the domain associated with this socket? */
#define sodomain(so)	((so)->so_proto->pr_domain)

/*
 * How much space is there in a socket buffer (so->so_snd or so->so_rcv)?
 * This is problematical if the fields are unsigned, as the space might
 * still be negative (cc > hiwat or mbcnt > mbmax).  Should detect
 * overflow and return 0.  Should use "lmin" but it doesn't exist now.
 */
#define __sbspace_imin(a,b)  ((a) < (b) ? (a) : (b))

#define sbspace(sb) \
    ((int) __sbspace_imin((int)((sb)->sb_hiwat - (sb)->sb_cc), \
	__sbspace_imin((int)((sb)->sb_mbmax - (sb)->sb_mbcnt), \
	(int)((sb)->sb_dbmax - (sb)->sb_dbcnt))))

/* do we have to send all at once on a socket? */
#define	sosendallatonce(so) \
    ((so)->so_proto->pr_flags & PR_ATOMIC)

/* Is write of len bytes to be atomic (for pipes)?  (obsolete) */
#define sowatomic(so, len) (0)

/* can we read something from so? 
 * for certain sequenced packet protocols, zero-length reads are supported 
 */
#define	soreadable(so) \
    ((so)->so_rcv.sb_cc >= (so)->so_rcv.sb_lowat || \
	((so)->so_state & SS_CANTRCVMORE) || \
	(so)->so_qlen || (so)->so_error) || \
	(((so)->so_proto->pr_flags & PR_READZEROLEN ) && \
	 ((so)->so_rcv.sb_mb))

/* can we write something to so? */
#define	sowriteable(so) \
    (sbspace(&(so)->so_snd) >= (so)->so_snd.sb_lowat && \
	(((so)->so_state&SS_ISCONNECTED) || \
	  ((so)->so_proto->pr_flags&PR_CONNREQUIRED)==0) || \
     ((so)->so_state & SS_CANTSENDMORE) || \
     (so)->so_error)

/* adjust counters in sb reflecting allocation of m */
#define sballoc(sb, m) { \
	(sb)->sb_cc += (m)->m_len; \
	(sb)->sb_mbcnt += MSIZE; \
	if ((m)->m_flags & M_EXT) { \
		if ((m)->m_flags & M_UIOMOVE) \
			(sb)->sb_dbcnt += (m)->m_ext.ext_size; \
		else \
			(sb)->sb_mbcnt += (m)->m_ext.ext_size; \
	} \
}

/* adjust counters in sb reflecting freeing of m */
#define sbfree(sb, m) { \
	(sb)->sb_cc -= (m)->m_len; \
	(sb)->sb_mbcnt -= MSIZE; \
	if ((m)->m_flags & M_EXT) { \
		if ((m)->m_flags & M_UIOMOVE) \
			(sb)->sb_dbcnt -= (m)->m_ext.ext_size; \
		else \
			(sb)->sb_mbcnt -= (m)->m_ext.ext_size; \
	} \
}

#define	sorwakeup(so)	sowakeup((so), &(so)->so_rcv)
#define	sowwakeup(so)	sowakeup((so), &(so)->so_snd)

/* to catch callers missing new second argument to sonewconn: */
#define sonewconn(head, connstatus)	sonewsock((head), (connstatus))
extern REPLICATED u_int	sb_max;
#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif
