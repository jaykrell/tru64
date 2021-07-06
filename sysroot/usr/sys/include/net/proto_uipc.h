/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: proto_uipc.h,v $
 * Revision 4.2.68.2  2010/03/30  05:49:35  Nune_Venkata_Chalapathi
 * 	QAR99390:
 * 	Fix for compiler warning in uipc_socket2.c
 *
 * Revision 4.2.68.1  2003/06/05  13:31:58  Dan_Vuong
 *      Add m_copym2() and pf_mcopym().
 *      This is part of the effort to fix CLD FR_G06708, QAR 96108.
 *
 * Revision 4.2.51.4  2002/06/05  22:40:25  Tony_Bono
 * 	Merge up to v51asupport.bl2
 *
 * Revision 4.2.60.1  2002/02/21  15:33:07  Olif_Chapman
 * 	Added definition of soqremquesafe used to correct
 * 	accept inconsistencies seen by vms et al.
 * 	Fixed Hang while closing of an active listening socket
 * 	seen in Mexico when running the newer version of
 * 	sendmail QAR/CLD <MXOM80005>
 *
 * Revision 4.2.51.3  2002/01/29  21:18:40  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.2.51.2  2002/01/04  22:19:22  John_Dustin
 * 	Fixed definitions of 'P' for prototypes. QAR 91237 and 82344.
 *
 * Revision 4.2.51.1  2001/09/21  13:16:39  James_Woodward
 * 	Add prototyupes for soo_select_dequeue and soo_select_enqueue.
 *
 * Revision 4.2.47.4  2000/06/23  22:42:42  Tony_Bono
 * 	removed queue identity parameter and added socket
 * 	parameter for soqrem1stquenl
 *
 * Revision 4.2.47.3  1999/12/17  00:13:08  Tony_Bono
 * 	Fix corruption of socket receive mbuf chain
 * 	that cause panic in sbdrop.
 *
 * Revision 4.2.47.2  1999/10/28  19:41:26  Ernie_Petrides
 * 	Remove obsolete prototypes for unp_abort(), unp_drain(), and unp_gc().
 *
 * Revision 4.2.47.1  1999/10/14  21:29:24  Brian_Haley
 * 	Added pftimeout_init() prototype.
 *
 * Revision 4.2.45.2  1999/08/26  20:37:22  Kris_Corwin
 * 	Add protos for so_sendfile and sendfile.
 * 	[1999/08/24  22:57:38  Kris_Corwin]
 *
 * Revision 4.2.23.12  1999/04/15  21:09:55  Tony_Bono
 * 	Added protos for socket read lock routines.
 * 	[1999/04/15  20:38:19  Tony_Bono]
 * 
 * Revision 4.2.23.11  1999/03/25  19:58:22  Brian_Haley
 * 	Added struct sockaddr forward declaration to avoid warnings.
 * 	[1999/03/10  23:14:29  Brian_Haley]
 * 
 * Revision 4.2.23.10  1999/02/09  19:03:37  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:19:58  Ken_Block]
 * 
 * Revision 4.2.23.9  1998/08/13  13:01:34  Joseph_Vlcek
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit -visual **
 * 		** Ancestor revision:	4.2.23.6 **
 * 		** Merge revision:	4.2.23.8 **
 * 	 	** End **
 * 	Rename uipc_configure() to uipc_configure_domain() to avoid
 * 	conflict with uipc subsystem configuration routine in uipc_cfg.c.
 * 	uipc_configure_domain() is called from netinit(), while
 * 	uipc_configure() is called by the configuration subsystem.
 * 	[1998/07/31  17:59:54  Joseph_Vlcek]
 * 
 * Revision 4.2.23.8  1998/08/03  18:48:36  Anton_Verhulst
 * 	Fix merge problem.
 * 	[1998/08/03  18:30:01  Anton_Verhulst]
 * 
 * Revision 4.2.23.7  1998/07/30  21:47:47  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.2.36.2 **
 * 		** Merge revision:	4.2.36.3 **
 * 	 	** End **
 * 	[1998/07/30  21:36:27  Tony_Bono]
 * 
 * Revision 4.2.36.3  1998/06/26  04:10:09  Tony_Bono
 * 	Added prototype for sonewsocknolock used by tcp_input().
 * 	[1998/06/26  02:33:23  Tony_Bono]
 * 
 * Revision 4.2.23.6  1998/05/14  22:39:28  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.2.30.2 **
 * 		** Merge revision:	4.2.36.2 **
 * 	 	** End **
 * 	[1998/05/14  22:16:17  John_Dustin]
 * 
 * Revision 4.2.36.2  1998/03/31  21:13:47  Tony_Bono
 * 	Added soqmvque to eliminate the need for locking the head while
 * 	processing close of pending connections.
 * 	[1998/03/31  19:58:11  Tony_Bono]
 * 
 * Revision 4.2.23.5  1998/02/12  19:47:30  Brian_Haley
 * 	Added tssmap_timeo() and soqrem1stquenl() prototypes.
 * 	[1998/02/06  16:23:26  Brian_Haley]
 * 
 * Revision 4.2.23.4  1997/09/10  23:31:27  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL6:PTCOS_BL10 **
 * 		** Ancestor revision:	4.2.16.4 **
 * 		** Merge revision:	4.2.30.2 **
 * 	 	** End **
 * 	merge of PTmin BL10 changes
 * 	[1997/09/10  23:04:17  John_Dustin]
 * 
 * Revision 4.2.30.2  1997/05/30  22:35:30  Tony_Bono
 * 	HPXQB6189/QAR 49847, An enhanced fix to solockpair() routine
 * 	was needed because the routine was freeing a solock structure
 * 	that was concurrently spun upon in lock_write().
 * 	[1997/05/30  14:33:42  Tony_Bono]
 * 
 * Revision 4.2.23.3  1997/04/24  18:25:35  Tony_Bono
 * 	merge
 * 	[1997/04/24  18:05:31  Tony_Bono]
 * 
 * Revision 4.2.23.2  1996/05/01  14:51:19  Fred_Knight
 * 	Merge from bravos.bl2
 * 	[1996/05/01  14:33:33  Fred_Knight]
 * 
 * Revision 4.2.18.3  1996/03/12  20:04:08  Al_Delorey
 * 	merge of Platinum BL11 pass 1 to BL11 pass 2 changes
 * 	[1996/03/12  20:02:42  Al_Delorey]
 * 
 * Revision 4.2.16.4  1996/02/29  15:06:07  Ajay_Kachrani
 * 	Add solocktry() proto-types...
 * 	[1996/02/20  19:52:35  Ajay_Kachrani]
 * 
 * Revision 4.2.18.2  1995/10/25  19:57:54  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:27:52  Ray_Lanza]
 * 
 * Revision 4.2.16.3  1995/04/26  16:49:54  James_Woodward
 * 	convert select arguments event/revent from short to integer for alpha.
 * 	[1995/04/24  12:40:04  James_Woodward]
 * 
 * Revision 4.2.16.2  1995/02/03  15:28:19  Jack_McCann
 * 	Add prototypes for pffindtype1() and pffindproto1()
 * 	[1995/02/01  20:57:28  Jack_McCann]
 * 
 * Revision 4.2.11.8  1994/04/06  19:09:47  Ernie_Petrides
 * 	Add function prototype for solock() and change that for sounlock().
 * 	[1994/04/05  20:41:43  Ernie_Petrides]
 * 
 * Revision 4.2.11.7  1994/03/02  00:00:21  Geraldine_Harter
 * 	Changes needed to reduce size of socket fields (long to int).
 * 	[1994/02/28  19:04:29  Geraldine_Harter]
 * 
 * Revision 4.2.11.6  1993/11/09  19:41:31  Geraldine_Harter
 * 	Merge with Sterling BL7:
 * 	Revision 4.2.8.6  1993/10/13  20:04:38  Heather_Gray
 * 	Add 8K cluster alloc function proto. Remove obsolete prototypes.
 * 	[1993/10/11  21:11:44  Heather_Gray]
 * 
 * 	Add 2K cluster mbuf alloc function proto.
 * 	[1993/10/04  20:46:54  Heather_Gray]
 * 
 * 	Revision 4.2.8.5  1993/09/30  19:26:24  John_Dustin
 * 	added m_length() prototype
 * 	[1993/09/27  17:57:55  John_Dustin]
 * 
 * Revision 4.2.11.5  1993/10/07  21:59:17  Geraldine_Harter
 * 	Merge with Sterling BL6.  Turns out to be a NOP except for including
 * 	revision logs of changes made prior to this merge (for completeness):
 * 
 * 	Revision 4.2.8.4  1993/07/31  18:49:11  Heather_Gray
 * 	Change m_clalloc() return from int to caddr_t for use with new
 * 	allocator.
 * 	[1993/07/28  03:39:44  Heather_Gray]
 * 
 * 	Revision 4.2.8.3  1993/06/29  17:33:33  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:07:08  SJ_Lee]
 * 
 * 	Revision 4.2.8.2  1993/05/12  21:09:15  Peter_Schulter
 * 	Check in for minor submit
 * 	[1993/05/12  15:08:06  Peter_Schulter]
 * 
 * 	Revision 4.2.6.2  1993/03/17  16:24:50  Mary_Walker
 * 	added mbuf_to_mblk and mblk_to_mbuf protos
 * 	[1993/03/17  16:24:07  Mary_Walker]
 * 
 * Revision 4.2.11.4  1993/09/10  18:26:43  Geraldine_Harter
 * 	Sterling mbuf alloc premerge (based on Sterling BL5):
 * 	[1993/09/09  20:48:17  Geraldine_Harter]
 * 
 * Revision 4.2.11.3  1993/08/09  18:40:08  Geraldine_Harter
 * 	Remove protos for obsolete functions sbselqueue(), sbseldequeue()
 * 	[1993/08/09  16:32:20  Geraldine_Harter]
 * 
 * Revision 4.2.11.2  1993/06/25  21:17:02  Geraldine_Harter
 * 	Merge selected OSF1.2 changes (all but mbuf allocation routines).
 * 	[1993/06/25  20:27:55  Geraldine_Harter]
 * 
 * Revision 4.2.4.2  1992/03/18  17:50:34  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:15:49  Al_Delorey]
 * 
 * Revision 4.2.2.2  92/03/17  16:35:34  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2  91/09/19  22:45:42  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: proto_uipc.h,v $ $Revision: 4.2.68.2 $ (DEC) $Date: 2010/03/30 05:49:35 $
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

#ifndef _PROTO_UIPC_H_
#define _PROTO_UIPC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef P
#define	P(s) s
#define __P_IN_PROTO_UIPC /* P was defined here */
#endif

/* Avoid scoping problems */
typedef union {
	struct file	*p1;
	struct uio	*p2;
	struct ucred	*p3;
	struct stat	*p4;
	struct proc	*p5;
	struct socket	*p6;
	struct sockbuf	*p7;
	struct mbuf	*p8;
	struct msghdr	*p9;
	struct unpcb	*p10;
	struct domain	*p11;
	struct msgb	*p12;
	struct sockaddr	*p13;
	struct socket_sel_queue *p14;
	struct ufile_entry *p15;
} proto_uipc_union_t;

#ifdef __VMS
# include "sys/socket.h"
# ifdef __ALPHA
#  ifndef __PCBDEF_LOADED
#  include <pcbdef.h>
#  endif    /* __PCBDEF_LOADED */
#  ifndef __UCBDEF_LOADED
#  include <ucbdef.h>
#  endif    /* __UCBDEF_LOADED */
# elif defined __VAX
#  ifndef __PCBDEF_LOADED
#  include <pcbdef.h>
#  endif    /* __PCBDEF_LOADED */
#  ifndef __UCBDEF_LOADED
#  include <ucbdef.h>
#  endif    /* __UCBDEF_LOADED */
   typedef struct PCBDEF PCB;
   typedef struct ucbdef UCB;
# else
#  error "proto_uipc.h: Unknown hardware architecture, neither Alpha nor VAX"
# endif
#endif	/* __VMS */

/* sys_socket.c */
int	soo_read P((struct file *, struct uio *, struct ucred *));
int	soo_write P((struct file *, struct uio *, struct ucred *));
#ifndef __VMS
int	soo_ioctl P((struct file *, unsigned int, caddr_t));
#else
int	ovms_check_priv P((PCB *));
int	soo_ioctl P((struct socket *, unsigned int, caddr_t));
#endif
#ifdef __digital__
int	soo_select P((struct file *, int *, int *, int));
#else
int	soo_select P((struct file *, short *, short *, int));
#endif /* __digital__ */
void	soo_select_dequeue P((struct file *, struct socket_sel_queue *));
boolean_t soo_select_enqueue P((struct file *, int,  struct ufile_entry *));
int	soo_stat P((struct socket *, struct stat *));
int	soo_close P((struct file *));

/* uipc_domain.c */
void	domaininit P((void));
int	domain_add P((struct domain *));
int	domain_del P((struct domain *));
struct	protosw *pffindtype P((int, int));
struct	protosw *pffindtype1 P((int, int, int *));
struct	protosw *pffindproto P((int, int, int));
struct	protosw *pffindproto1 P((int, int, int, int *));
void	pfctlinput P((int, struct sockaddr *));
void	pfreclaim P((void));
void	pfslowtimo P((void));
void	pffasttimo P((void));
void	pftimeout_init P((void));

/* uipc_mbuf.c */
void	mbinit P((void));
caddr_t	m_clalloc P((int, int));
caddr_t	m_clalloc2 P((struct mbuf *, int));
caddr_t	m_clalloc8 P((struct mbuf *, int));
void	mbufintr P((void));
struct	mbuf *m_retry P((int, int));
struct	mbuf *m_retryhdr P((int, int));
struct	mbuf *m_get P((int, int));
struct	mbuf *m_gethdr P((int, int));
struct	mbuf *m_getclr P((int, int));
struct	mbuf *m_free P((struct mbuf *));
void	m_freem P((struct mbuf *));
int	m_leadingspace P((struct mbuf *));
int	m_trailingspace P((struct mbuf *));
int	m_length P((struct mbuf *));
struct	mbuf *m_prepend P((struct mbuf *, int, int));
struct	mbuf *m_copym P((struct mbuf *, int, int, int));
struct	mbuf *m_copym2 P((struct mbuf *, int, int, int));
struct	mbuf *pf_mcopym P((struct mbuf *, int, int, int));
void	m_copydata P((struct mbuf *, int, int, caddr_t));
void	m_cat P((struct mbuf *, struct mbuf *));
void	m_adj P((struct mbuf *, int));
struct	mbuf *m_pullup P((struct mbuf *, int));
struct	mbuf *m_pullup_exact P((struct mbuf *, int));
struct	msgb *mbuf_to_mblk P((struct mbuf *, int));
struct	mbuf *mblk_to_mbuf P((struct msgb *, int));

/* uipc_proto.c */
int	uipc_configure_domain P((void));

/* uipc_socket.c */
#ifndef __VMS 
int	socreate P((int, struct socket **, int, int));
int	sobind P((struct socket *, struct mbuf *));
#else /* __VMS */
int	socreate P((int, struct socket **, int, int, PCB *));
int	sobind P((struct socket *, struct mbuf *, PCB *));
#endif  /* __VMS */
int	solisten P((struct socket *, int));
void	sofree P((struct socket *));
void	solockpair P((struct socket *, struct socket *));
void	soreadlock P((struct socket *));
void	solock P((struct socket *));
void	solock1 P((struct socket *));
int	solocktry P((struct socket *));
int	solocktrynoassert P((struct socket *));
int	soreaders P((struct socket *));
void	soreadunlock P((struct socket *));
void	sounlock P((struct socket *));
void	sounlock1 P((struct socket *));
int	soclose P((struct socket *));
int	soabort P((struct socket *));
int	soaccept P((struct socket *, struct mbuf *));
int	soconnect P((struct socket *, struct mbuf *));
int	soconnect2 P((struct socket *, struct socket *));
int	sodisconnect P((struct socket *));
int	so_sendfile P((struct socket *, int, off_t, size_t, struct uio *,
			struct uio *, int, long *));
int	sosend P((struct socket *, struct mbuf *, struct uio *,
				struct mbuf *, struct mbuf *, int));
int	soreceive P((struct socket *, struct mbuf **, struct uio *,
				struct mbuf **, struct mbuf **, int *));
int	soshutdown P((struct socket *, int));
void	sorflush P((struct socket *));
#ifndef __VMS 
void	sopriv P((struct socket *));
#else /* __VMS */
void	sopriv P((struct socket *, PCB *));
#endif	 /* __VMS */
#ifndef __VMS 
int	sosetopt P((struct socket *, int, int, struct mbuf *));
int	sogetopt P((struct socket *, int, int, struct mbuf **));
#else /* __VMS */
int	sosetopt P((struct socket *, int, int, struct mbuf *, PCB *, UCB *));
int	sogetopt P((struct socket *, int, int, struct mbuf **, UCB *));
#endif /* __VMS */
void	sohasoutofband P((struct socket *));
int	sodequeue P((struct socket *, struct socket **, struct mbuf **, int));
int	sogetaddr P((struct socket *, struct mbuf **, int, int));
void	tssmap_timeo P((void));

/* uipc_socket2.c */
void	soisconnecting P((struct socket *));
void	soisconnected P((struct socket *));
void	soisdisconnecting P((struct socket *));
void	soisdisconnected P((struct socket *));
struct	socket *sonewsock P((struct socket *, int));
struct	socket *sonewsocknolock P((struct socket *, int, caddr_t*));
int	soqmvque P((struct socket *, int, int));
void	soqinsque P((struct socket *, struct socket *, int));
void    soqinsquenl P((struct socket *, struct socket *, int));
int	soqremquesafe P((struct socket *));
int	soqremque P((struct socket *, int));
void	socantsendmore P((struct socket *));
void	socantrcvmore P((struct socket *));
int	sosblock P((struct sockbuf *, struct socket *));
void	sbunlock P((struct sockbuf *));
int	sosbwait P((struct sockbuf *, struct socket *));
int	sosleep P((struct socket *, caddr_t, int, int));
void	sowakeup P((struct socket *, struct sockbuf *));
int	sbwakeup P((struct socket *, struct sockbuf *, int));
int	sbpoll P((struct socket *, struct sockbuf *));
int	soreserve P((struct socket *, u_int, u_int));
int	sbreserve P((struct sockbuf *, u_int));
void	sbrelease P((struct sockbuf *));
void	sbappend P((struct sockbuf *, struct mbuf *));
void	sbappendrecord P((struct sockbuf *, struct mbuf *));
void	sbinsertoob P((struct sockbuf *, struct mbuf *));
int	sbappendaddr P((struct sockbuf *, struct sockaddr *,
				struct mbuf *, struct mbuf *));
int	sbappendcontrol P((struct sockbuf *, struct mbuf *, struct mbuf *));
struct mbuf*	sbcompress P((struct sockbuf *, struct mbuf *, struct mbuf *));
void	sbflush P((struct sockbuf *));
void	sbdrop P((struct sockbuf *, int));
void	sbdroprecord P((struct sockbuf *));
int	lock_socheck P((struct socket *));
int	unlock_socheck P((struct socket *));
int	lock_sbcheck P((struct sockbuf *));
int	unlock_sbcheck P((struct sockbuf *));
struct	socket *soqrem1stquenl P((struct socket *, struct socket *));
#ifdef __VMS
struct	socket *ovms_soqrem1stquenl P((struct socket *, int));
#endif /* __VMS */

/* uipc_syscalls.c */
int	socket P((struct proc *, void *, long *));
int	bind P((struct proc *, void *, long *));
int	listen P((struct proc *, void *, long *));
int	accept P((struct proc *, void *, long *));
int	oaccept P((struct proc *, void *, long *));
int	connect P((struct proc *, void *, long *));
int	socketpair P((struct proc *, void *, long *));
int	sendto P((struct proc *, void *, long *));
int	osend P((struct proc *, void *, long *));
int	osendmsg P((struct proc *, void *, long *));
int	sendmsg P((struct proc *, void *, long *));
int	sendfile P((struct proc *, void *, long *));
int	recvfrom P((struct proc *, void *, long *));
int	orecvfrom P((struct proc *, void *, long *));
int	orecv P((struct proc *, void *, long *));
int	orecvmsg P((struct proc *, void *, long *));
int	recvmsg P((struct proc *, void *, long *));
int	shutdown P((struct proc *, void *, long *));
int	setsockopt P((struct proc *, void *, long *));
int	getsockopt P((struct proc *, void *, long *));
int	pipe P((struct proc *, void *, long *));
int	getsockname P((struct proc *, void *, long *));
int	ogetsockname P((struct proc *, void *, long *));
int	getpeername P((struct proc *, void *, long *));
int	ogetpeername P((struct proc *, void *, long *));
int	sendit P((int, struct msghdr *, int, long *));
int	recvit P((int, struct msghdr *, caddr_t, long *));
#ifdef	COMPAT_43
int	accept1 P((struct proc *, void *, long *, int));
int	recvfrom1 P((int));
int	getsockname1 P((struct proc *, void *, long *, int));
int	getpeername1 P((struct proc *, void *, long *, int));
#endif
void	sockaddr_new P((struct mbuf *));
void	sockaddr_old P((struct mbuf *));
int	sockargs P((struct mbuf **, caddr_t, int, int));
struct	file *getsock P((int, int *));

/* uipc_usrreq.c */
void	uipc_init P((void));
int	uipc_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	unp_attach P((struct socket *));
void	unp_detach P((struct unpcb *));
int	unp_bind P((struct unpcb *, struct mbuf *));
int	unp_connect P((struct socket *, struct mbuf *));
int	unp_connect2 P((struct socket *, struct socket *));
void	unp_disconnect P((struct unpcb *));
void	unp_shutdown P((struct unpcb *));
void	unp_drop P((struct unpcb *, int));
int	unp_externalize P((struct mbuf *));
int	unp_internalize P((struct mbuf *));
void	unp_dispose P((struct mbuf *));
void	unp_scan P((struct mbuf *, void (*)(struct file *)));
void	unp_mark P((struct file *));
void	unp_discard P((struct file *));

#ifdef __P_IN_PROTO_UIPC
#undef P
#undef __P_IN_PROTO_UIPC /* clean up */
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
