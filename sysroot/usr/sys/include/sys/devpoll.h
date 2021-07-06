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
 * @(#)$RCSfile: devpoll.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2001/09/21 13:16:40 $
 */

#ifndef _DEVPOLL_H_
#define _DEVPOLL_H_
#include <sys/ioctl.h>
#include <sys/poll.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL
#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/event.h>

struct devpoll_entry {
	struct queue_entry dpe_list;
	int		dpe_hint;	/* interesting entry */
	int		dpe_queued;	/* dpe is queued to the device */
	struct 	pollfd	dpe_pollfd;
	struct devpoll	*dpe_dp;	/* pointer to devpoll */
	struct devpoll_entry *dpe_ndpe; /* used if in 2 poll sets within task */
};

#define dpe_fid 	dpe_pollfd.fd
#define dpe_events	dpe_pollfd.events
#define dpe_revents	dpe_pollfd.revents

typedef struct devpoll_entry *dpe_t;
typedef struct devpoll_entry dpe_data_t;

struct devpoll {
	struct queue_entry dp_entry_list;
	int			dp_count;
	lock_data_t		dp_lock;
	event_t			dp_event;
};

#define DP_EMPTY -1	
struct dvpoll {
	struct user_pollfd * dp_fds;
	int		dp_nfds;
	int		dp_timeout;
};

struct ufile_entry;
struct vnode;
extern int dp_clone(struct ufile_entry *, struct vnode *, struct file *,
			struct ufile_state *);
extern void dp_cleanup(struct file *, struct ufile_entry *);

#else /* _KERNEL */

struct dvpoll {
	struct pollfd * dp_fds;
	int		dp_nfds;
	int		dp_timeout;
};
#endif /* _KERNEL */

#ifdef _KERNEL
#define DP_ISPOLLED	_IOWR('P', 1, struct user_pollfd)
#else
#define DP_ISPOLLED	_IOWR('P', 1, struct pollfd)
#endif

#define DP_POLL		_IOWR('P', 2, struct dvpoll)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*_DEVPOLL_H_ */
