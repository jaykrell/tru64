/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: clnt.h,v $
 * Revision 1.1.39.6  2007/09/05  09:39:23  Vivek_Verma
 * 	Add missing semicolon to the last member of the rpc_const structure
 * 	to fix compilation warning. QAR 100300.
 *
 * Revision 1.1.39.5  2005/09/16  12:25:49  Vivek_Verma
 * 	Add rpcc_default_rad to rpc_const so that we don't default to RAD 0
 * 	QAR 98229.
 *
 * Revision 1.1.39.4  2004/09/30  18:03:32  Paul_Park
 * 	Add cku_refcount to keep track of deferred buffer references.
 * 	[2004/04/29  19:20:39  Paul_Park]
 *
 * 	QAR 97909 [DE_G09145, BCPM402HJ]: RPC/udp client buffer detaching:
 * 	Add cku_program, cku_version for header reserializing.
 * 	Add cku_outmbuf to track down stray packets.
 * 	[2004/04/23  20:40:48  Paul_Park]
 *
 * Revision 1.1.39.3  2003/11/12  18:04:13  Paul_Park
 * 	QAR 90948: Add boolean (privileged port required) argument to
 * 	clntktcp_connect.
 *
 * Revision 1.1.39.2  2003/06/16  20:33:10  Eric_Werme
 * 	Add includes of ip_var.h and ip.h to resolve struct uh_port_reg use.
 *
 * Revision 1.1.39.1  2003/06/13  18:21:04  Eric_Werme
 * 	Add NUMA client NUMA support.
 * 	[2003/06/13  18:18:14  Eric_Werme]
 *
 * Revision 1.1.35.1  2002/07/15  21:21:05  Eric_Werme
 * 	Add definitions for clntktcp_timetest and clntktcp_dotimeout.
 * 	(QAR 94145)
 *
 * Revision 1.1.32.2  1999/08/13  09:47:42  John_Carr
 * 	Use a single port and socket for all KUDP RPC requests.
 * 	[1999/08/13  09:42:24  John_Carr]
 *
 * Revision 1.1.12.8  1999/06/16  14:32:15  John_Carr
 * 	Add optional source address for KUDP RPC.
 * 	[1999/06/16  13:54:07  John_Carr]
 * 
 * Revision 1.1.12.7  1999/03/16  10:00:32  John_Carr
 * 	Add forward declarations of structure tags.
 * 	[1999/03/11  18:58:03  John_Carr]
 * 
 * Revision 1.1.12.6  1999/03/02  19:32:57  Martin_Lund
 * 	Merged in ptfcos.bl5: #define CLGET_BUFBUSY
 * 	[1999/03/02  19:08:51  Martin_Lund]
 * 
 * Revision 1.1.12.5  1998/01/12  19:33:09  Steve_Dickson
 * 	Added timeout argument to clntktcp_connect.
 * 	[1998/01/10  18:40:57  Steve_Dickson]
 * 
 * Revision 1.1.12.4  1997/09/15  20:28:33  Eric_Werme
 * 	Add function prototype for ku_sendto_mbuf().
 * 	[1997/09/15  19:53:42  Eric_Werme]
 * 
 * Revision 1.1.12.3  1996/12/17  19:08:37  Martin_Lund
 * 	Change rpc_timers to u_int to allow for longer timeo.  QAR 45782
 * 	[1996/12/17  18:14:25  Martin_Lund]
 * 
 * Revision 1.1.12.2  1996/12/02  17:30:56  Eric_Werme
 * 	Add support for using small RPC buffers for non-NFS users.  (QAR 49265)
 * 	[1996/11/26  20:56:41  Eric_Werme]
 * 
 * Revision 1.1.9.7  1995/11/05  16:50:24  Eric_Werme
 * 	Add function protoypes for clnt_kudp.c.  Restructure definitions to make
 * 	them usable.
 * 	[1995/11/01  17:56:04  Eric_Werme]
 * 
 * Revision 1.1.9.6  1995/10/24  16:43:42  Eric_Werme
 * 	Add cl_sigmask definition for non-interruptible sleeps.  (QAR 38976)
 * 	[1995/10/24  16:41:54  Eric_Werme]
 * 
 * Revision 1.1.9.5  1995/06/30  20:41:46  Arti_Kumar
 * 	Add CLSET_SERVER_ADDR definition for proplistd
 * 	[1995/06/30  18:09:04  Arti_Kumar]
 * 
 * Revision 1.1.9.4  1995/06/27  21:03:09  Eric_Werme
 * 	Add CLSET_CRED definition for NFS over TCP.  (And maybe UDP someday.)
 * 	[1995/06/27  18:01:57  Eric_Werme]
 * 
 * Revision 1.1.9.3  1995/04/24  21:06:14  Eric_Werme
 * 	Add support for RPC over TCP.
 * 	[1995/04/24  18:26:46  Eric_Werme]
 * 
 * Revision 1.1.9.2  1995/03/18  23:44:58  Arti_Kumar
 * 	bmerge to latest
 * 	[1995/03/18  23:39:43  Arti_Kumar]
 * 
 * 	bci again
 * 	[1995/03/17  22:53:06  Arti_Kumar]
 * 
 * 	Ric: Add cl_next field to client struct
 * 	[1995/03/08  23:33:42  Arti_Kumar]
 * 
 * Revision 1.1.7.3  1993/08/06  14:39:24  Timothy_Burke
 * 	Merge prior to submit.
 * 	[1993/08/06  14:31:56  Timothy_Burke]
 * 
 * 	Added lockinfo structs.
 * 	[1993/08/05  18:25:51  Timothy_Burke]
 * 
 * Revision 1.1.7.2  1993/06/01  20:44:29  Timothy_Burke
 * 	Initial pass at SMP of kernel level RPC.
 * 	[1993/05/26  19:24:00  Timothy_Burke]
 * 
 * Revision 1.1.3.4  1992/08/17  16:20:42  Benoy_Desouza
 * 	Merged in Silver bl9_2
 * 	Fix signal mask corruption problem.
 * 	[92/08/07  13:54:58  Charles_Briggs]
 * 
 * Revision 1.1.3.3  92/03/30  23:04:13  Benoy_Desouza
 * 	64 bit Alpha changes
 * 	[92/03/30  23:03:47  Benoy_Desouza]
 * 
 * Revision 1.1.3.2  92/03/18  17:58:53  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:29:50  Al_Delorey]
 * 
 * 	From ONC reference port
 * 	[92/02/20  15:34:12  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  16:43:45  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: clnt.h,v $ $Revision: 1.1.39.6 $ (DEC) $Date: 2007/09/05 09:39:23 $
 */
/*	@(#)clnt.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *  1.31 88/02/08 SMI  
 */

/*
 * clnt.h - Client side remote procedure call interface.
 */

#ifndef _rpc_clnt_h
#define	_rpc_clnt_h
#include <kern/queue.h>		/* Need for cl_link, etc. */
#include <netinet/in_route.h>
#include <netinet/udp.h>
#include <netinet/ip.h>		/* For IPOPT_OFFSET used in ip_var.h */
#include <netinet/ip_var.h>	/* For struct ipovly used in udp_var.h */
#include <netinet/udp_var.h>	/* For struct uh_port_reg */

#undef RPC_SUCCESS

/*
 * Rpc calls return an enum clnt_stat.  This should be looked at more,
 * since each implementation is required to live with this (implementation
 * independent) list of errors.
 */
enum clnt_stat {
	RPC_SUCCESS=0,			/* call succeeded */
	/*
	 * local errors
	 */
	RPC_CANTENCODEARGS=1,		/* can't encode arguments */
	RPC_CANTDECODERES=2,		/* can't decode results */
	RPC_CANTSEND=3,			/* failure in sending call */
	RPC_CANTRECV=4,			/* failure in receiving result */
	RPC_TIMEDOUT=5,			/* call timed out */
	RPC_INTR=18,                    /* call interrupted */
	/*
	 * remote errors
	 */
	RPC_VERSMISMATCH=6,		/* rpc versions not compatible */
	RPC_AUTHERROR=7,		/* authentication error */
	RPC_PROGUNAVAIL=8,		/* program not available */
	RPC_PROGVERSMISMATCH=9,		/* program version mismatched */
	RPC_PROCUNAVAIL=10,		/* procedure unavailable */
	RPC_CANTDECODEARGS=11,		/* decode arguments error */
	RPC_SYSTEMERROR=12,		/* generic "other problem" */

	/*
	 * callrpc & clnt_create errors
	 */
	RPC_UNKNOWNHOST=13,		/* unknown host name */
	RPC_UNKNOWNPROTO=17,		/* unkown protocol */

	/*
	 * _ create errors
	 */
	RPC_PMAPFAILURE=14,		/* the pmapper failed in its call */
	RPC_PROGNOTREGISTERED=15,	/* remote program is not registered */
	/*
	 * unspecified error
	 */
	RPC_FAILED=16

};

/*
 * Error info.
 */
struct rpc_err {
	enum clnt_stat re_status;
	union {
		int RE_errno;		/* realated system error */
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			u_int low;	/* lowest verion supported */
			u_int high;	/* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			int s1;
			int s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
};

/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */
typedef struct client {
	union {
		queue_head_t cl_u_link;		/* Sometimes we want double */
		struct client *cl_u_next;	/* sometimes single */
	} cl_u;
	struct tcp_sock *cl_tsp; /* NFS dynamically attaches tcp sockets */
	AUTH	*cl_auth;			/* authenticator */
	struct clnt_ops {
		enum clnt_stat	(*cl_call)();	/* call remote procedure */
		void		(*cl_abort)();	/* abort a call */
		void		(*cl_geterr)();	/* get specific error code */
		bool_t		(*cl_freeres)();/* frees results */
		void		(*cl_destroy)();/* destroy this structure */
		bool_t          (*cl_control)();/* the ioctl() of rpc */
	} *cl_ops;
	caddr_t			cl_private;	/* private stuff */
	sigset_t		cl_sigmask;	/* Interruptible or not */
} CLIENT;

#define cl_link cl_u.cl_u_link
#define cl_next cl_u.cl_u_next

/*
 * client side rpc interface ops
 *
 * Parameter types are:
 *
 */

/*
 * enum clnt_stat
 * CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)
 * 	CLIENT *rh;
 *	u_int proc;
 *	xdrproc_t xargs;
 *	caddr_t argsp;
 *	xdrproc_t xres;
 *	caddr_t resp;
 *	struct timeval timeout;
 */
#define	CLNT_CALL(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))
#define	clnt_call(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))

/*
 * void
 * CLNT_ABORT(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_ABORT(rh)	((*(rh)->cl_ops->cl_abort)(rh))
#define	clnt_abort(rh)	((*(rh)->cl_ops->cl_abort)(rh))

/*
 * struct rpc_err
 * CLNT_GETERR(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_GETERR(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))
#define	clnt_geterr(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))


/*
 * bool_t
 * CLNT_FREERES(rh, xres, resp);
 * 	CLIENT *rh;
 *	xdrproc_t xres;
 *	caddr_t resp;
 */
#define	CLNT_FREERES(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))
#define	clnt_freeres(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *      CLIENT *cl;
 *      u_int request;
 *      char *info;
 */
#define	CLNT_CONTROL(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))
#define	clnt_control(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))

/*
 * control operations that apply to both udp and tcp transports
 * (Not all are implemented in the kernel.)
 */
#define CLSET_TIMEOUT       1   /* set timeout (timeval) */
#define CLGET_TIMEOUT       2   /* get timeout (timeval) */
#define CLGET_SERVER_ADDR   3   /* get server's address (sockaddr) */
#define	CLGET_FD	    6   /* get connections file descriptor */
#define	CLSET_FD_CLOSE	    8   /* close fd while clnt_destroy */
#define	CLSET_FD_NCLOSE	    9   /* Do not close fd while clnt_destroy */
#define CLSET_XID	   10	/* Set xid for next request */
#define CLSET_CRED	   11	/* Set credentials for next request */
#define CLSET_SERVER_ADDR  12   /* Set server's address (sockaddr) */
#define CLGET_BUFBUSY      13   /* Return I/O in progress flag */

/*
 * udp only control operations
 */
#define CLSET_RETRY_TIMEOUT 4   /* set retry timeout (timeval) */
#define CLGET_RETRY_TIMEOUT 5   /* get retry timeout (timeval) */

/*
 * void
 * CLNT_DESTROY(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))


/*
 * RPCTEST is a test program which is accessable on every rpc
 * transport/port.  It is used for testing, performance evaluation,
 * and network administration.
 */

#define RPCTEST_PROGRAM		((u_int)1)
#define RPCTEST_VERSION		((u_int)1)
#define RPCTEST_NULL_PROC	((u_int)2)
#define RPCTEST_NULL_BATCH_PROC	((u_int)3)

/*
 * By convention, procedure 0 takes null arguments and returns them
 */

#define NULLPROC ((u_int)0)

/*
 * Timers used for the pseudo-transport protocol when using datagrams
 */
struct rpc_timers {
	u_int		rt_srtt;	/* smoothed round-trip time */
	u_int		rt_deviate;	/* estimated deviation */
	u_int		rt_rtxcur;	/* current (backed-off) rto */
};

/*
 * Feedback values used for possible congestion and rate control
 */
#define	FEEDBACK_REXMIT1	1	/* first retransmit */
#define	FEEDBACK_OK		2	/* no retransmits */

#define	UDPMSGSIZE	8800	/* rpc imposed limit on udp msg size */
#define	RPCSMALLMSGSIZE	600	/* a more reasonable packet size */

/*
 * Below are the client handle creation routines for the various
 * implementations of client side rpc.  They can return NULL if a 
 * creation failure occurs.
 */

/*
 * Copy error message to buffer.
 */
char *clnt_sperrno(/* enum clnt_stat num */);	/* string */


#ifdef KERNEL

struct in_ifaddr;
struct mbuf;

/* UDP based RPC and common code used by TCP */
u_int		alloc_xid(void);
int		bindresvport(struct socket *);
enum clnt_stat	clntkudp_callit_addr(CLIENT *, u_int, xdrproc_t, caddr_t,
				     xdrproc_t, caddr_t, struct timeval,
				     struct sockaddr_in *, int);
/*
 * clntkudp_create arguments are destination address, source address
 * (NULL to use default algorithm), program, version, retries|flags
 * (flag bits are defined below), credentials.
 */
CLIENT		*clntkudp_create(struct sockaddr_in *, struct sockaddr_in *,
				 u_int, u_int, int, struct ucred *);
void		clntkudp_init(CLIENT *, struct sockaddr_in *,int,
			      struct ucred *);

unsigned int	clntkudp_settimers(CLIENT *, struct rpc_timers *,
				   struct rpc_timers *, unsigned int,
				   void (*)(), caddr_t, u_int);

int ku_sendto_mbuf(struct socket *, struct mbuf *, struct sockaddr_in *,
		   struct sockaddr_in *, struct in_ifaddr *, struct in_route *);

void		rpcinit(void);

/* TCP based RPC */
struct tcp_sock   *clntktcp_checksock(CLIENT *, struct tcp_sock **);
enum   clnt_stat   clntktcp_connect(CLIENT *, struct sockaddr_in *, int, bool_t);
CLIENT            *clntktcp_create(u_int, u_int);
int		   clntktcp_dotimeout(struct tcp_sock *, int, struct tcp_sock **);
enum   clnt_stat   clntktcp_freesock(struct tcp_sock *);
int                clntktcp_timeout(struct tcp_sock *, int, struct tcp_sock **);
int		   clntktcp_timetest(struct tcp_sock *, int);

/* Common code */
struct mbuf *mclgetx(void (*)(), caddr_t, caddr_t, int, int);

/*
 * Private data per rpc handle.  This structure is allocated by
 * clntkudp_create, and freed by cku_destroy.
 */
struct cku_private {
	u_int			 cku_flags;	/* see below */
	u_int			 cku_xid;	/* current XID */
	CLIENT			 cku_client;	/* client handle (56 bytes) */
	int			 cku_retrys;	/* request retrys */
	u_int			 cku_refcount;	/* reference count */
	struct sockaddr_in	 cku_addr;	/* remote address */
	struct sockaddr_in	 cku_source;	/* source address */
	struct in_route		 cku_route;	/* route for ku_sendto_mbuf */
	struct rpc_err		 cku_err;	/* error status */
	XDR			 cku_outxdr;	/* xdr routine for output */
	XDR			 cku_inxdr;	/* xdr routine for input */
	u_int			 cku_outpos;	/* position of in output mbuf */
	u_int			 cku_outsize;	/* size of cku_outbuf */
	u_int			 cku_program;	/* For serializing hdr */
	u_int			 cku_version;
	caddr_t			 cku_outbuf;	/* output buffer */
	struct mbuf		*cku_outmbuf;	/* output mbuf */
	struct mbuf		*cku_inmbuf;	/* input mbuf */
	struct sockaddr_in	 cku_inaddr;	/* received packet source */
	struct ucred		*cku_cred;	/* credentials */
	struct rpc_timers	*cku_timers;	/* for estimating RTT */
	struct rpc_timers	*cku_timeall;	/* for estimating RTT */
	void			(*cku_feedback)();
	caddr_t			cku_feedarg;	/* argument for feedback func */
	udecl_simple_lock_data(,cku_lk_outbuf) 	/* SMP lock for mbuf data */
};
udecl_simple_lock_info(extern, cku_lk_outbuf_info) /* SMP stats */
/* MP locking macros associated with the cku_lk_outbuf member of cku_private. */
#define RPC_OUTBUF_LOCKINIT(cku_p)	\
			  usimple_lock_setup(&(cku_p)->cku_lk_outbuf, \
					      cku_lk_outbuf_info)
#define RPC_OUTBUF_LOCK(cku_p)     usimple_lock(&(cku_p)->cku_lk_outbuf)
#define RPC_OUTBUF_UNLOCK(cku_p)   usimple_unlock(&(cku_p)->cku_lk_outbuf)

/* Flags passed to clntkudp_create() in high half of retries argument */
#define KUDP_UNPRIV	0x10000
#define KUDP_SMALLBUF	0x20000
#define KUDP_RETRIES	0x0ffff	/* retries confined to low half */

/* RPC NUMA support. */

/*
 * Structure of rarely changed data that exists in per-RAD memory outside
 * of rpc_radinfo.  This is managed in clnt_kudp.c where a lot of
 * generic RPC data lives, and this is all RPC over UDP data anyway.
 */
struct rpc_const {
    /* These are checked early in UDP input processing */
    /*
     * The fast path UDP code checks a subsystem status flag to decide
     * whether to deliver a packet to the callout function or handle it
     * normally.
     */
    struct uh_port_reg	rpcc_port_reg;	/* 24 Touched on each UDP request */
    struct socket	*rpcc_sock;	/*  8 Socket we're using */
    int			rpcc_one;	/*  4 Enable for uh_port_register */

    /* These are checked early in input and output processing. */
    u_int		rpcc_mask;	/*  4 Mask to isolate radid from xid */
    int			rpcc_shift;	/*  4 Distance to shift radid into xid */

    /* Initialization only at present, could be moved. */
    int			rpcc_nrads;	/*  4 Local copy of rads to check */

    /* J. Random RAD  */
    struct rad		*rpcc_default_rad; /* 8 Local copy of default RAD */
};

/*
 * This per-RAD structure is referenced by struct rad.rad_rpc. It tracks the
 * RPC over UDP list of threads waiting for their XIDs to return and holds
 * the per-RAD XID info, see rpc_const for the system-wide XID info.
 */
/* Per RAD information,  */
struct rpc_radinfo {
    /* SMP lock for waiters and shared counters */
    udecl_simple_lock_data(, rr_lock)	/*  8 */
    queue_head_t rr_waiters;		/* 16 client handles awaiting reply */
    int rr_shared;			/*  4 current queue length */
    int rr_max_shared;			/*  4 maximum queue length */
    int pad1[8];			/* 32 fill out cache line */

    u_int rr_xid;			/*  4 XID, atomically incr'd */
    u_int rr_xidradid;			/*  4 RAD ID shifted to high bits */
    int pad2[14];			/* 56 fill out cache line */
};

#endif

#endif /*!_rpc_clnt_h*/
