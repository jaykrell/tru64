/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: svc.h,v $
 * Revision 1.1.26.1  2003/10/14  18:30:13  Paul_Park
 * 	Add per-rad RPCSVC data.
 * 	Add function prototypes.
 *
 * Revision 1.1.17.3  1998/11/18  16:54:31  Steve_Dickson
 * 	Merged in the following deltas from tcr4os pool:
 * 	 Added the SVC_CONTROL() call.
 * 	 [1998/10/01  20:38:33  Steve_Dickson]
 * 	[1998/11/18  16:41:11  Steve_Dickson]
 *
 * Revision 1.1.17.2  1997/04/07  15:49:56  Eric_Werme
 * 	Add IP destination address to SVC_INPUT() macro.  (QAR 48834)
 * 	[1997/04/02  19:26:12  Eric_Werme]
 * 
 * Revision 1.1.11.2  1995/04/24  21:06:26  Eric_Werme
 * 	Add prototype for svctcp_create().
 * 	[1995/04/24  18:26:58  Eric_Werme]
 * 
 * Revision 1.1.9.2  1995/02/15  14:57:53  Timothy_Burke
 * 	Moved DRC return status values from duplicated nfs & rpc modules.
 * 	[1995/02/13  20:19:20  Timothy_Burke]
 * 
 * Revision 1.1.7.3  1994/11/18  19:12:44  Aju_John
 * 	removed a comment within a comment
 * 	[1994/11/18  16:20:09  Aju_John]
 * 
 * Revision 1.1.7.2  1994/08/25  15:26:38  James_Woodward
 * 	replace multisocket code with lightweight requeue. cleanup locks.
 * 	[1994/08/24  15:40:31  James_Woodward]
 * 
 * Revision 1.1.5.2  1993/10/06  13:51:51  Peter_S_Thompson
 * 	Make #endif statements ANSI compliant
 * 	[1993/09/30  17:20:04  Peter_S_Thompson]
 * 
 * Revision 1.1.3.4  1992/12/09  19:34:35  Chet_Juszczak
 * 	remove defunct timing array
 * 	add "type of transport" pointer
 * 	[92/12/09  18:44:21  Chet_Juszczak]
 * 
 * Revision 1.1.3.3  92/03/31  14:59:23  Benoy_Desouza
 * 	64 bit Alpha changes
 * 	[92/03/31  14:58:52  Benoy_Desouza]
 * 
 * Revision 1.1.3.2  92/03/18  18:31:44  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:32:41  Al_Delorey]
 * 
 * 	From ONC reference port.
 * 	[92/02/21  08:51:14  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  15:46:19  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: svc.h,v $ $Revision: 1.1.26.1 $ (DEC) $Date: 2003/10/14 18:30:13 $
 */
/*	@(#)svc.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *      @(#)svc.h 1.20 88/02/08 SMI      *
 */


/*
 * svc.h, Server-side remote procedure call interface.
 */

#ifndef _rpc_svc_h
#define	_rpc_svc_h

/*
 * This interface must manage two items concerning remote procedure calling:
 *
 * 1) An arbitrary number of transport connections upon which rpc requests
 * are received.  The two most notable transports are TCP and UDP;  they are
 * created and registered by routines in svc_tcp.c and svc_udp.c, respectively;
 * they in turn call xprt_register and xprt_unregister.
 *
 * 2) An arbitrary number of locally registered services.  Services are
 * described by the following four data: program number, version number,
 * "service dispatch" function, a transport handle, and a boolean that
 * indicates whether or not the exported program should be registered with a
 * local binder service;  if true the program's number and version and the
 * port number from the transport handle are registered with the binder.
 * These data are registered with the rpc svc system via svc_register.
 *
 * A service's dispatch function is called whenever an rpc request comes in
 * on a transport.  The request's program and version numbers must match
 * those of the registered service.  The dispatch function is passed two
 * parameters, struct svc_req * and SVCXPRT *, defined below.
 */

enum xprt_stat {
	XPRT_DIED,
	XPRT_MOREREQS,
	XPRT_IDLE
};

/*
 * Server side transport handle
 */
struct svcxprt{
	struct svcxprt *xp_next;	/* used for linking in a list */
#ifdef KERNEL
	struct socket	*xp_sock;
#else
	int		xp_sock;
#endif
	u_short		xp_port;	 /* associated port number */
	struct xp_ops {
	    /* get message from socket */
	    bool_t	(*xp_recv)(struct svcxprt *, struct rpc_msg *);
	    /* received message in an mbuf */
	    bool_t	(*xp_input)(struct svcxprt *, struct rpc_msg *,
#ifdef	KERNEL
				    struct mbuf *,
#else
				    void *,
#endif
				    struct sockaddr_in *, struct sockaddr_in *);
	    /* get transport status */
	    enum xprt_stat (*xp_stat)(struct svcxprt *);
	    /* get arguments */
	    bool_t	(*xp_getargs)(struct svcxprt *, xdrproc_t, caddr_t);
	    /* send reply */
	    bool_t	(*xp_reply)(struct svcxprt *, struct rpc_msg *);
	    /* free mem allocated for args */
	    bool_t	(*xp_freeargs)(struct svcxprt *, xdrproc_t, caddr_t);
	    /* destroy this struct */
	    void	(*xp_destroy)(struct svcxprt *);
	    /* the ioctl() of rpc */
	    bool_t	(*xp_control)(struct svcxprt *, int, void *);
	} *xp_ops;
	int		xp_addrlen;	 /* length of remote address */
	struct sockaddr_in xp_raddr;	 /* remote address */
	struct ifaddr	*xp_ifp;	 /* points to the source interface */
	struct opaque_auth xp_verf;	 /* raw response verifier */
	caddr_t		xp_p1;		 /* private: for use by svc ops */
	caddr_t		xp_p2;		 /* private: for use by svc ops */
	caddr_t		xp_p3;		 /* private: for use by rpc app */
	caddr_t		xp_cred_area;	 /* permanent space to cut malloc()s */
};
typedef struct svcxprt SVCXPRT;

/*
 *  Approved way of getting address of caller
 */
#define svc_getcaller(x) (&(x)->xp_raddr)

/*
 * Operations defined on an SVCXPRT handle
 *
 * SVCXPRT		*xprt;
 * struct rpc_msg	*msg;
 * xdrproc_t		 xargs;
 * caddr_t		 argsp;
 */
#define SVC_RECV(xprt, msg)				\
	(*(xprt)->xp_ops->xp_recv)((xprt), (msg))
#define svc_recv(xprt, msg)				\
	(*(xprt)->xp_ops->xp_recv)((xprt), (msg))

#define SVC_INPUT(xprt, msg, m, sin, dst)			\
	(*(xprt)->xp_ops->xp_input)((xprt), (msg), (m), (sin), (dst))
#define svc_input(xprt, msg, m, sin, dst)			\
	(*(xprt)->xp_ops->xp_input)((xprt), (msg), (m), (sin), (dst))

#define SVC_STAT(xprt)					\
	(*(xprt)->xp_ops->xp_stat)(xprt)
#define svc_stat(xprt)					\
	(*(xprt)->xp_ops->xp_stat)(xprt)

#define SVC_GETARGS(xprt, xargs, argsp)			\
	(*(xprt)->xp_ops->xp_getargs)((xprt), (xargs), (argsp))
#define svc_getargs(xprt, xargs, argsp)			\
	(*(xprt)->xp_ops->xp_getargs)((xprt), (xargs), (argsp))

#define SVC_REPLY(xprt, msg)				\
	(*(xprt)->xp_ops->xp_reply) ((xprt), (msg))
#define svc_reply(xprt, msg)				\
	(*(xprt)->xp_ops->xp_reply) ((xprt), (msg))

#define SVC_FREEARGS(xprt, xargs, argsp)		\
	(*(xprt)->xp_ops->xp_freeargs)((xprt), (xargs), (argsp))
#define svc_freeargs(xprt, xargs, argsp)		\
	(*(xprt)->xp_ops->xp_freeargs)((xprt), (xargs), (argsp))

#define SVC_DESTROY(xprt)				\
	(*(xprt)->xp_ops->xp_destroy)(xprt)
#define svc_destroy(xprt)				\
	(*(xprt)->xp_ops->xp_destroy)(xprt)

#define SVC_CONTROL(xprt, request, info)				\
	(*(xprt)->xp_ops->xp_control)((xprt), (request), (info))
#define svc_control(xprt, request, info)				\
	(*(xprt)->xp_ops->xp_control)((xprt), (request), (info))
/*
 * control operations that apply to both udp and tcp transports
 */
#define SVCSET_SRCADDR 1 /* set src addr on udp replies */

/*
 * Service request
 */
struct svc_req {
	u_int		rq_prog;	/* service program number */
	u_int		rq_vers;	/* service protocol version */
	u_int		rq_proc;	/* the desired procedure */
	u_int		rq_xid;		/* transaction ID */
	struct opaque_auth rq_cred;	/* raw creds from the wire */
	caddr_t		rq_clntcred;	/* read only cooked cred */
	SVCXPRT	*rq_xprt;		/* associated transport */
};


/*
 * Service registration
 *
 * svc_register(xprt, prog, vers, dispatch, protocol)
 *	SVCXPRT *xprt;
 *	u_long prog;
 *	u_int vers;
 *	void (*dispatch)();
 *	int protocol;  -- like TCP or UDP, zero means do not register 
 *
 * XXX Why is prog a u_long?!
 * XXX dispatch should have a prototype
 */
extern bool_t	svc_register(SVCXPRT *, u_long, u_int, int (*)(), int);

/*
 * Service un-registration
 *
 * svc_unregister(prog, vers)
 *	u_long prog;
 *	u_int vers;
 */
extern void	svc_unregister(u_long, u_int);

/*
 * Transport registration.
 *
 * xprt_register(xprt)
 *	SVCXPRT *xprt;
 */
extern void	xprt_register(SVCXPRT *);

#ifndef KERNEL
/*
 * Transport un-register
 *
 * xprt_unregister(xprt)
 *	SVCXPRT *xprt;
 */
extern void	xprt_unregister(SVCXPRT *);


#endif /* !KERNEL */


/*
 * When the service routine is called, it must first check to see if it
 * knows about the procedure;  if not, it should call svcerr_noproc
 * and return.  If so, it should deserialize its arguments via 
 * SVC_GETARGS (defined above).  If the deserialization does not work,
 * svcerr_decode should be called followed by a return.  Successful
 * decoding of the arguments should be followed the execution of the
 * procedure's code and a call to svc_sendreply.
 *
 * Also, if the service refuses to execute the procedure due to too-
 * weak authentication parameters, svcerr_weakauth should be called.
 * Note: do not confuse access-control failure with weak authentication!
 *
 * NB: In pure implementations of rpc, the caller always waits for a reply
 * msg.  This message is sent when svc_sendreply is called.  
 * Therefore pure service implementations should always call
 * svc_sendreply even if the function logically returns void;  use
 * xdr.h - xdr_void for the xdr routine.  HOWEVER, tcp based rpc allows
 * for the abuse of pure rpc via batched calling or pipelining.  In the
 * case of a batched call, svc_sendreply should NOT be called since
 * this would send a return message, which is what batching tries to avoid.
 * It is the service/protocol writer's responsibility to know which calls are
 * batched and which are not.  Warning: responding to batch calls may
 * deadlock the caller and server processes!
 */

extern bool_t	svc_sendreply(SVCXPRT *, xdrproc_t, caddr_t);
extern void	svcerr_decode(SVCXPRT *);
extern void	svcerr_weakauth(SVCXPRT *);
extern void	svcerr_noproc(SVCXPRT *);
extern void	svcerr_progvers(SVCXPRT *, u_int, u_int);
extern void	svcerr_auth(SVCXPRT *, enum auth_stat);
extern void	svcerr_noprog(SVCXPRT *);
#ifndef KERNEL
extern void	svcerr_systemerr(SVCXPRT *);
#endif
    
/*
 * Lowest level dispatching -OR- who owns this process anyway.
 * Somebody has to wait for incoming requests and then call the correct
 * service routine.  The routine svc_run does infinite waiting; i.e.,
 * svc_run never returns.
 * Since another (co-existant) package may wish to selectively wait for
 * incoming calls or other events outside of the rpc architecture, the
 * routine svc_getreq is provided.  It must be passed readfds, the
 * "in-place" results of a select system call (see select, section 2).
 */

#ifndef KERNEL
/*
 * Global keeper of rpc service descriptors in use
 * dynamic; must be inspected before each call to select 
 */
extern fd_set svc_fdset;
#define svc_fds svc_fdset.fds_bits[0]	/* compatibility */

/*
 * a small program implemented by the svc_rpc implementation itself;
 * also see clnt.h for protocol numbers.
 */
extern void rpctest_service();
#endif /* !KERNEL */

extern int	svc_getreq(SVCXPRT *);
#ifndef KERNEL
extern void	svc_getreqset(); /* takes fdset instead of int */
extern int	svc_run();
#else
extern int	svc_run(SVCXPRT *);
#endif

/*
 * Socket to use on svcxxx_create call to get default socket
 */
#define	RPC_ANYSOCK	-1

/*
 * These are the existing service side transport implementations
 */

#ifndef KERNEL
/*
 * Memory based rpc for testing and timing.
 */
extern SVCXPRT *svcraw_create();

/*
 * Udp based rpc.
 */
extern SVCXPRT *svcudp_create();
extern SVCXPRT *svcudp_bufcreate();

/*
 * Tcp based rpc.
 */
extern SVCXPRT *svctcp_create();

/*
 * Like svtcp_create(), except the routine takes any *open* UNIX file
 * descriptor as its first input.
 */
SVCXPRT *svcfd_create();
#else

/*
 * Kernel udp based rpc.
 */
extern SVCXPRT *svckudp_create(struct socket *, u_short);
extern void svckudp_destroy(SVCXPRT *);
extern void svckudp_nobusy(SVCXPRT *);

/*
 * Tcp based rpc.
 */
extern SVCXPRT *svcktcp_create(struct socket *);
extern void svcktcp_destroy(SVCXPRT *);

/*
 * kernel-based RPC server duplicate transaction cache flag values
 */
#define DUP_BUSY 0x8000000	/* transaction in progress */
#define DUP_DONE 0x4000000	/* transaction was completed */
#define DUP_FAIL 0x2000000	/* transaction failed */
#define DUP_MASK 0xe000000
/*
 * kernel-based RPC server duplicate transaction cache status return values.
 */
#define	NDUP_NEW		0x0	/* new request */
#define	NDUP_INPROGRESS		0x01	/* request already going */
#define	NDUP_DONE		0x02	/* request done */
#define	NDUP_ERR		0x03	/* DRC error */

/*
 * duplicate transaction cache prototypes.
 */
extern int svckudp_dup(int, u_int, u_int, u_int, u_int, caddr_t, int);
extern void svckudp_dupdone(int, u_int, u_int, u_int, u_int, caddr_t, int, int);
extern void svckudp_drc_init(int, int);
extern void svckudp_drc_done(void);

extern void svckudp_init(void);

/*
 * Per-rad RPCSVC data.
 */
typedef struct svc_per_rad_info {
	void	*rpcs_drc;	/* Used by DRC */
} svc_radinfo_t;
#define	svcrpc_per_rad(_r)	((svc_radinfo_t *)(_r)->rad_rpcs)
#endif /* !KERNEL */

#endif /*!_rpc_svc_h*/
