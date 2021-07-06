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
 *	@(#)$RCSfile: socket.h,v $ $Revision: 4.2.79.1 $ (DEC) $Date: 2002/01/29 21:19:49 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982,1985,1986,1988 Regents of the University of California.
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
 *	Base:	socket.h	7.6 (Berkeley) 9/4/89
 *	Merged: socket.h	7.10 (Berkeley) 6/28/90
 *	Merged: socket.h	7.13 (Berkeley) 4/20/91
 */

#ifndef	_SYS_SOCKET_H_
#define	_SYS_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/uio.h>

/*
 * Definitions related to sockets: types, address families, options.
 */
/*
 * Types
 */
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */
#define	SOCK_RDM	4		/* reliably-delivered message */
#define	SOCK_SEQPACKET	5		/* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define	SO_DEBUG	0x0001		/* turn on debugging info recording */
#define	SO_ACCEPTCONN	0x0002		/* socket has had listen() */
#define	SO_REUSEADDR	0x0004		/* allow local address reuse */
#define	SO_KEEPALIVE	0x0008		/* keep connections alive */
#define	SO_DONTROUTE	0x0010		/* just use interface addresses */
#define	SO_BROADCAST	0x0020		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	0x0040		/* bypass hardware when possible */
#define	SO_LINGER	0x0080		/* linger on close if data present */
#define	SO_OOBINLINE	0x0100		/* leave received OOB data in line */
#define	SO_REUSEPORT	0x0200		/* allow local addr and port reuse */
#ifdef __VMS
#define SO_OPTIONS_VMS SO_DEBUG+SO_ACCEPTCONN+SO_REUSEADDR+SO_KEEPALIVE+ \
                       SO_DONTROUTE+SO_BROADCAST+SO_USELOOPBACK+ \
                       SO_LINGER+SO_OOBINLINE+SO_REUSEPORT
#define	SO_FULL_DUPLEX_CLOSE 0x2000	/* return error on post-FIN write */
#endif /* __VMS */
#if SEC_BASE
#if SEC_NET
#define SO_EXPANDED_RIGHTS      0x1016  /* return expanded rights on recv */
#define SO_DEFAULT_ATTR         0x1017  /* set def. socket attr. */
#define SO_RCV_ATTR             0x1018  /* set socket rcv mask. */
#define SO_AUTHENTICATION       0x1019  /* set socket authentication data. */
#define SO_ACCESS_ERROR         0x1020  /* record security violation. */
#define SO_SEC_ATTRIBUTES       0x1021  /* get sec. attrs. for last byte read */
#define SO_REMOTE_KEY           0x1022  /* get auth. data for remote process. */
#define SO_NEW_ATTRS_ONLY       0x1023  /* Only return attrs if they change. */
#define SO_SET_TNET_TCB         0x1024  /* Set/reset ALLOWNETACCESS on socket.*/
#define SO_GET_TNET_TCB         0x1025  /* Return ALLOWNETACC. flag on socket.*/
#else
#define	SO_EXPANDED_RIGHTS	0x0400	/* return expanded rights on recv */
#endif /*SEC_NET*/
#endif
#define SO_PAIRABLE	0x0800		/* pairable socket unix domian */
#define SO_UMC		0x01000		/* umc socket */
#define SO_REUSERAD	0x02000		/* allow reuse of addr if not on rad */
#define	SO_CLUA_IN_NOLOCAL     	0x10000	/* must recv packets addressed to a cluster alias */
#define	SO_REUSEALIASPORT 	0x20000	/* may reuse a locked cluster alias port  */
#define	SO_CLUA_IN_NOALIAS     	0x40000	/* must recv packets addressed to a local address */
#define	SO_CLUA_DEFAULT_SRC    	0x80000	/* use default cluster alias as source address */
#define	SO_RESVPORT            0x100000 /* process wants a reserved port */

/*
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF	0x1001		/* send buffer size */
#define SO_RCVBUF	0x1002		/* receive buffer size */
#define SO_SNDLOWAT	0x1003		/* send low-water mark */
#define SO_RCVLOWAT	0x1004		/* receive low-water mark */
#define SO_SNDTIMEO	0x1005		/* send timeout */
#define SO_RCVTIMEO	0x1006		/* receive timeout */
#define	SO_ERROR	0x1007		/* get error status and clear */
#define	SO_TYPE		0x1008		/* get socket type */
#ifndef __VMS
#define SO_STATE	0x1009		/* get socket state bits */
#define SO_FAMILY	0x100a		/* get socket address family*/
#define SO_XSE		0x100b		/* _XOPEN_SOURCE_EXTENDED socket */
#else /* __VMS */
#define SO_SHARE	0x1009		/* ovms Share between processes */
#define SO_CCL		0x100a		/* ovms Carriage Control socket */
#define SO_STATE	0x100b		/* get socket state bits */
#define SO_FAMILY	0x100c		/* get socket address family*/
#define SO_XSE		0x100d		/* _XOPEN_SOURCE_EXTENDED socket */
#endif /* __VMS */

/*
 * Structure used for manipulating linger option.
 */
struct	linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define	SOL_SOCKET	0xffff		/* options for socket level */

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_UNIX		1		/* local to host (pipes, portals) */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_IMPLINK	3		/* arpanet imp addresses */
#define	AF_PUP		4		/* pup protocols: e.g. BSP */
#define	AF_CHAOS	5		/* mit CHAOS protocols */
#define	AF_NS		6		/* XEROX NS protocols */
#define	AF_ISO		7		/* ISO protocols */
#define	AF_OSI		AF_ISO
#define	AF_ECMA		8		/* european computer manufacturers */
#define	AF_DATAKIT	9		/* datakit protocols */
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc */
#define	AF_SNA		11		/* IBM SNA */
#define AF_DECnet	12		/* DECnet */
#define AF_DLI		13		/* DEC Direct data link interface */
#define AF_LAT		14		/* LAT */
#define	AF_HYLINK	15		/* NSC Hyperchannel */
#define	AF_APPLETALK	16		/* Apple Talk */
#define	AF_ROUTE	17		/* Internal Routing Protocol */
#define	AF_LINK		18		/* Link layer interface */

#ifdef _XOPEN_SOURCE_EXTENDED
#define	__pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
#else
#define	pseudo_AF_XTP	19		/* eXpress Transfer Protocol (no AF) */
#endif

#define AF_NETMAN	20		/* DNA Network Management */
#define AF_X25		21		/* X25 protocol */
#define AF_CTF		22		/* Common Trace Facility */
#define AF_WAN		23		/* Wide Area Network protocols */
#define AF_USER		24		/* Wild card (user defined) protocol */
#define AF_LAST		25		/* Local Area System Transport protocol */
#define	AF_INET6	26		/* IPv6: UDP, TCP, etc. */ 
#define AF_AAL		27		/* Native AAL ATM */
#define AF_KEY		28		/* IPSEC key management */
#define	AF_MAX		35		/* leave some space for future growth */

#include <sys/types.h>		/* sa_family_t defined here */

#define SHUT_RD		0	/* Disables further receive operations */
#define SHUT_WR		1	/* Disables further send operations */
#define SHUT_RDWR	2	/* Disables further send and receive operations */

/*
 * This data type is needed for both UNIX98 and POSIX support.
 */
#if (defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)) || \
    defined(_POSIX_PII_SOCKET) || defined(__VMS)
typedef unsigned long	socklen_t;	/* 64-bits */
#endif

/* definitions for sockaddr_storage structure */
#define _SS_MAXSIZE    128  /* Implementation specific max size.  Set to
                             * be large enough to take a sockaddr_un.
                             */

#define _SS_ALIGNSIZE  (sizeof (long))	/* 64 bit alligned */

#if defined(_SOCKADDR_LEN) || \
    defined(_KERNEL) || \
    defined(_XOPEN_SOURCE_EXTENDED) || \
    defined(_POSIX_PII_SOCKET)
/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
	unsigned char	sa_len;		/* total length */
	sa_family_t	sa_family;	/* address family */
	char		sa_data[14];	/* actually longer; address value */
};

#ifdef _OSF_SOURCE
/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct osockaddr {
	unsigned short	sa_family;	/* address family */
	char		sa_data[14];	/* up to 14 bytes of direct address */
};

#define _SS_PAD1SIZE (_SS_ALIGNSIZE - (sizeof (uchar_t) + sizeof(sa_family_t)))
#define _SS_PAD2SIZE   (_SS_MAXSIZE - ( 2 * _SS_ALIGNSIZE))

struct sockaddr_storage {
    unsigned char  ss_len;			/* address length */
    sa_family_t    ss_family;			/* address family */
#define __ss_len	ss_len
#define __ss_family	ss_family
    char           __ss_pad1[_SS_PAD1SIZE];	/* pad to allignment field */
    ulong_t        __ss_align;			/* force structure allignment */
    char           __ss_pad2[_SS_PAD2SIZE];	/* pad to desired size */
};
#endif /* _OSF_SOURCE */

#else	/* BSD4.3 */

struct sockaddr {
	unsigned short	sa_family;	/* address family */
	char		sa_data[14];	/* up to 14 bytes of direct address */
};

#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof (ushort_t))
#define _SS_PAD2SIZE   (_SS_MAXSIZE - ( 2 * _SS_ALIGNSIZE))

struct sockaddr_storage {
    unsigned short  ss_family;		/* address family 4.3 BSD */
#define __ss_family	ss_family
    char            __ss_pad1[_SS_PAD1SIZE];	/* pad to allignment field */
    ulong_t         __ss_align;			/* force structure allignment */
    char            __ss_pad2[_SS_PAD2SIZE];	/* pad to desired size */
};

#endif	/* BSD4.3 */

#ifdef _OSF_SOURCE
/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
	unsigned short	sp_family;	/* address family */
	unsigned short	sp_protocol;	/* protocol */
};
#endif /* _OSF_SOURCE */

/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_UNIX		AF_UNIX
#define	PF_INET		AF_INET
#define	PF_IMPLINK	AF_IMPLINK
#define	PF_PUP		AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS		AF_NS
#define	PF_ISO		AF_ISO
#define	PF_OSI		AF_ISO
#define	PF_ECMA		AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA		AF_SNA
#define PF_DECnet	AF_DECnet
#define PF_DLI		AF_DLI
#define PF_LAT		AF_LAT
#define	PF_HYLINK	AF_HYLINK
#define	PF_APPLETALK	AF_APPLETALK
#define	PF_ROUTE	AF_ROUTE
#define	PF_LINK		AF_LINK

#ifdef _XOPEN_SOURCE_EXTENDED
#define	PF_XTP		__pseudo_AF_XTP	/* really just proto family, no AF */
#else
#define	PF_XTP		pseudo_AF_XTP	/* really just proto family, no AF */
#endif

#define PF_NETMAN	AF_NETMAN
#define PF_X25		AF_X25
#define PF_CTF		AF_CTF
#define PF_WAN		AF_WAN
#define PF_USER		AF_USER
#define PF_LAST		AF_LAST
#define PF_INET6	AF_INET6
#define PF_AAL		AF_AAL
#define PF_KEY		AF_KEY

#define	PF_MAX		AF_MAX

/*
 * Maximum queue length specifiable by listen.
 */
#define	SOMAXCONN	1024


#if defined(_SOCKADDR_LEN) || \
    defined(_KERNEL) || \
    defined(_XOPEN_SOURCE_EXTENDED) || \
    defined(_POSIX_PII_SOCKET)
/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
/*
 * NOTE: The POSIX msghdr structure takes precedence over the XOPEN flavor
 * 	 if both environments are defined.  The two structs differ in the
 *	 size of the msg_iovlen element.
 */
#ifdef _POSIX_PII_SOCKET
struct msghdr {
#else
struct __Pmsghdr {
#endif
	void	       *msg_name;	/* optional address */
#ifdef _POSIX_PII_SOCKET
	socklen_t	msg_namelen;	/* size of address */
#else
	size_t		msg_namelen;	/* size of address */
#endif
	struct iovec   *msg_iov;	/* scatter/gather array */
	size_t		msg_iovlen;	/* # elements in msg_iov */
	void	       *msg_control;	/* ancillary data, see below */
#ifdef _POSIX_PII_SOCKET
	socklen_t	msg_controllen;	/* ancillary data buffer len */
#else
	size_t		msg_controllen;	/* ancillary data buffer len */
#endif
	int		msg_flags;	/* flags on received message */
};

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_POSIX_PII_SOCKET)
struct msghdr {
#else
struct __Xmsghdr {
#endif
	void	       *msg_name;	/* optional address */
#if _XOPEN_SOURCE>=500
	socklen_t	msg_namelen;	/* size of address */
#else
	size_t		msg_namelen;	/* size of address */
#endif
	struct iovec   *msg_iov;	/* scatter/gather array */
	int		msg_iovlen;	/* # elements in msg_iov */
	void	       *msg_control;	/* ancillary data, see below */
#if _XOPEN_SOURCE>=500
	socklen_t	msg_controllen;	/* ancillary data buffer len */
#else
	size_t		msg_controllen;	/* ancillary data buffer len */
#endif
	int		msg_flags;	/* flags on received message */
};

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)
struct __Omsghdr {
#else
/* The msghdr structure the kernel uses */
struct msghdr {
#endif
	caddr_t		msg_name;	/* optional address */
	unsigned int	msg_namelen;	/* size of address */
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)
	struct __Oiovec *msg_iov;	/* scatter/gather array */
#else
	struct iovec   *msg_iov;	/* scatter/gather array */
#endif
	unsigned int	msg_iovlen;	/* # elements in msg_iov */
	caddr_t		msg_control;	/* ancillary data, see below */
	unsigned int	msg_controllen;	/* ancillary data buffer len */
	int		msg_flags;	/* flags on received message */
};

#ifdef _OSF_SOURCE
/*
 * 4.3-compat message header (move to compat file later).
 */
struct omsghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};
#endif /* _OSF_SOURCE */

#else	/* BSD4.3 - !_SOCKADDR_LEN || !_KERNEL || !_XOPEN_SOURCE_EXTENDED || !_POSIX_PII_SOCKET */

struct msghdr {
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;		/* size of address */
	struct	iovec *msg_iov;		/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;		/* access rights sent/received */
	int	msg_accrightslen;
};

#endif	/* BSD4.3 - !_SOCKADDR_LEN || !_KERNEL || !_XOPEN_SOURCE_EXTENDED || !_POSIX_PII_SOCKET */


#define	MSG_MAXIOVLEN	16
#define	MSG_OOB		0x1		/* process out-of-band data */
#define	MSG_PEEK	0x2		/* peek at incoming message */
#define	MSG_DONTROUTE	0x4		/* send without using routing tables */
#define	MSG_EOR		0x8		/* data completes record */
#define	MSG_TRUNC	0x10		/* data discarded before delivery */
#define	MSG_CTRUNC	0x20		/* control data lost before delivery */
#define	MSG_WAITALL	0x40		/* wait for full request or error */
#define	MSG_WIRE	0x80		/* toggle socket wire flag (send only) */

/* MSG_AIO must not be set by the user */
#define MSG_AIO		0x2000		/* Asynchronous IO request */

/* Following used within kernel */
#define	MSG_NONBLOCK	0x4000		/* nonblocking request */
#define MSG_COMPAT	0x8000		/* 4.3-format sockaddr */
#define MSG_SENDFILE	0x10000		/* from sendfile; bypass space checks */

/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)
struct cmsghdr {
#if _XOPEN_SOURCE>=500 || defined(_POSIX_PII_SOCKET)
	socklen_t	cmsg_len;	/* data byte count, including hdr */
#else
	size_t		cmsg_len;	/* data byte count, including hdr */
#endif
	int		cmsg_level;	/* originating protocol */
	int		cmsg_type;	/* protocol-specific type */
/* followed by	u_char  cmsg_data[]; */
};
#endif /* _XOPEN_SOURCE_EXTENDED || _POSIX_PII_SOCKET */

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)
struct __Ocmsghdr {
#else
struct cmsghdr {
#endif
	unsigned int	cmsg_len;	/* data byte count, including hdr */
	int		cmsg_level;	/* originating protocol */
	int		cmsg_type;	/* protocol-specific type */
/* followed by	u_char  cmsg_data[]; */
};

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)

/* Macro for checking and aligning a pointer to the machines native word size.
 */
#define _ALIGN(p) \
	((void *)((caddr_t)(p) + sizeof(void *) - 1UL - \
		 ((unsigned int)((caddr_t)(p) + sizeof(void *) - 1UL) % \
		  sizeof(void *))))

/* given pointer to struct cmsghdr, return pointer to data */
#define	CMSG_DATA(cmsg)		((unsigned char *)(cmsg) + _CMSG_LEN(0))

/* given length of data, return space required for cmsghdr and data,
 * plus any padding needed to satisfy alignment requirements
 */
#define _CMSG_SPACE(length) ((unsigned long)_ALIGN(sizeof(struct cmsghdr)) + \
				(unsigned long)_ALIGN(length))

/* given length of data, return value to store in cmsg_len field, taking
 * into account any padding needed to satisfy alignment requirements.
 */
#define _CMSG_LEN(length) ((unsigned long)_ALIGN(sizeof(struct cmsghdr)) \
				+ length)

/* given pointer to struct cmsghdr, return length of data */
#define _CMSG_DATALEN(cmsg)	((cmsg)->cmsg_len - _CMSG_LEN(0))

#if (_XOPEN_SOURCE >= 500) || defined(_POSIX_PII_SOCKET) || defined(_OSF_SOURCE)
/* for Unix 98, Posix and _OSF_SOURCE, enable all CMSG_ macros */
#define CMSG_SPACE(length)	_CMSG_SPACE(length)
#define CMSG_LEN(length)	_CMSG_LEN(length)
#define CMSG_DATALEN(cmsg)	_CMSG_DATALEN(cmsg)
#endif

/* given pointer to struct msghdr, return pointer to first cmsghdr */
#ifndef __VMS
#define	CMSG_FIRSTHDR(mhdr) \
    ( (mhdr)->msg_controllen >= _CMSG_LEN(0) ? \
      (struct cmsghdr *)(mhdr)->msg_control : \
      (struct cmsghdr *)0L )
#else /* __VMS */
#define	CMSG_FIRSTHDR(mhdr) \
    ( (mhdr)->msg_controllen >= _CMSG_LEN(0) ? \
      (struct cmsghdr *)(mhdr)->msg_control : \
      (struct cmsghdr *)NULL )
#endif /* __VMS */

/* given pointer to struct msghdr and cmsghdr, return pointer to next cmsghdr */
#ifndef __VMS
#define CMSG_NXTHDR(mhdr, cmsg) \
    (  ((cmsg) == 0L) ? CMSG_FIRSTHDR(mhdr) : \
     ( ((caddr_t)(cmsg) + _CMSG_SPACE(_CMSG_DATALEN(cmsg)) + _CMSG_LEN(0)) > \
            ((caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
       (struct cmsghdr *)0L : \
       (struct cmsghdr *)((caddr_t)(cmsg) + _CMSG_SPACE(_CMSG_DATALEN(cmsg)) )))
#else /* __VMS */
#define CMSG_NXTHDR(mhdr, cmsg) \
    (  ((cmsg) == NULL) ? CMSG_FIRSTHDR(mhdr) : \
     ( ((caddr_t)(cmsg) + _CMSG_SPACE(_CMSG_DATALEN(cmsg)) + _CMSG_LEN(0)) > \
            ((caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
       (struct cmsghdr *)NULL : \
       (struct cmsghdr *)((caddr_t)(cmsg) + _CMSG_SPACE(_CMSG_DATALEN(cmsg)) )))
#endif /* __VMS */

#else	/* defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET) */

/* Macro for checking and aligning a pointer to the machines native word size.
 */
#define _CMSG_ALIGN(p) \
	((void *)((caddr_t)(p) + sizeof(void *) - 1UL - \
		 ((unsigned int)((caddr_t)(p) + sizeof(void *) - 1UL) % \
		  sizeof(void *))))

/* given pointer to struct cmsghdr, return pointer to data */
#define	CMSG_DATA(cmsg)		((unsigned char *)(cmsg) + CMSG_LEN(0))

/* given length of data, return space required for cmsghdr and data,
 * plus any padding needed to satisfy alignment requirements
 */
#define CMSG_SPACE(length) ( sizeof(struct cmsghdr) + \
				(unsigned long)_CMSG_ALIGN(length) )

/* given length of data, return value to store in cmsg_len field, taking
 * into account any padding needed to satisfy alignment requirements.
 */
#define CMSG_LEN(length) (sizeof(struct cmsghdr) + length)

/* given pointer to struct cmsghdr, return length of data */
#define CMSG_DATALEN(cmsg)	((cmsg)->cmsg_len - CMSG_LEN(0))

/* given pointer to struct msghdr, return pointer to first cmsghdr */
#define	CMSG_FIRSTHDR(mhdr) \
    ( (mhdr)->msg_controllen >= CMSG_LEN(0) ? \
      (struct cmsghdr *)(mhdr)->msg_control : \
      (struct cmsghdr *)0L )

/* given pointer to struct msghdr and cmsghdr, return pointer to next cmsghdr */
#ifndef __VMS
#define CMSG_NXTHDR(mhdr, cmsg) \
    (  ((cmsg) == 0L) ? CMSG_FIRSTHDR(mhdr) : \
     ( ((caddr_t)(cmsg) + CMSG_SPACE(CMSG_DATALEN(cmsg)) + CMSG_LEN(0)) > \
            ((caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
       (struct cmsghdr *)0L : \
       (struct cmsghdr *)((caddr_t)(cmsg) + CMSG_SPACE(CMSG_DATALEN(cmsg)) )))
#else /* __VMS */
#define CMSG_NXTHDR(mhdr, cmsg) \
    (  ((cmsg) == NULL) ? CMSG_FIRSTHDR(mhdr) : \
     ( ((caddr_t)(cmsg) + CMSG_SPACE(CMSG_DATALEN(cmsg)) + CMSG_LEN(0)) > \
            ((caddr_t)(mhdr)->msg_control + (mhdr)->msg_controllen) ? \
       (struct cmsghdr *)NULL : \
       (struct cmsghdr *)((caddr_t)(cmsg) + CMSG_SPACE(CMSG_DATALEN(cmsg)) )))
#endif /* __VMS */

#endif

/* "Socket"-level control message types: */
#define	SCM_RIGHTS	0x01		/* access rights (array of int) */

#if defined(_SOCKADDR_LEN) && \
    !defined(_KERNEL) && \
    !defined(_XOPEN_SOURCE_EXTENDED) && \
    !defined(_POSIX_PII_SOCKET)

#define recv		_recv_OBSOLETE_ /* use recvfrom */
#define send		_send_OBSOLETE_ /* use sendto   */
#define	accept		naccept
#define	getpeername	ngetpeername
#define	getsockname	ngetsockname
#define	recvfrom	nrecvfrom
#define	recvmsg		nrecvmsg
#define	sendmsg		nsendmsg

#endif /* _SOCKADDR_LEN && !_KERNEL && !_XOPEN_SOURCE_EXTENDED && !_POSIX_PII_SOCKET*/

#ifndef _KERNEL
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII_SOCKET)
#if _XOPEN_SOURCE>=500 || defined(_POSIX_PII_SOCKET)
extern int	bind		__((int, const struct sockaddr *, socklen_t));
extern int	connect		__((int, const struct sockaddr *, socklen_t));
extern int	getsockopt	__((int, int, int, void *, socklen_t *));
extern ssize_t	sendto		__((int, const void *, size_t, int, const struct sockaddr *, socklen_t));
extern int	setsockopt	__((int, int, int, const void *, socklen_t));
#else /* !_XOPEN_SOURCE>=500 || !_POSIX_PII_SOCKET */
extern int	bind		__((int, const struct sockaddr *, size_t));
extern int	connect		__((int, const struct sockaddr *, size_t));
extern int	getsockopt	__((int, int, int, void *, size_t *));
extern ssize_t	sendto		__((int, const void *, size_t, int, const struct sockaddr *, size_t));
extern int	setsockopt	__((int, int, int, const void *, size_t));
#endif /* _XOPEN_SOURCE>=500 || _POSIX_PII_SOCKET */
extern ssize_t	recv		__((int, void *, size_t, int));
extern ssize_t	send		__((int, const void *, size_t, int));
#ifdef _POSIX_PII_SOCKET
extern int	sockatmark	__((int));
#endif
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix "_E"
#else /* !__DECC */
#define accept(__a, __b, __c)			_Eaccept(__a, __b, __c)
#define getpeername(__a, __b, __c)		_Egetpeername(__a, __b, __c)
#define getsockname(__a, __b, __c)		_Egetsockname(__a, __b, __c)
#define recvfrom(__a, __b, __c, __d, __e, __f)	_Erecvfrom(__a, __b, __c, __d, __e, __f)
#ifdef _POSIX_PII_SOCKET
#define recvmsg(__a, __b, __c)			_Precvmsg(__a, __b, __c)
#define sendmsg(__a, __b, __c)			_Psendmsg(__a, __b, __c)
#else /* !_POSIX_PII_SOCKET */
#define recvmsg(__a, __b, __c)			_Erecvmsg(__a, __b, __c)
#define sendmsg(__a, __b, __c)			_Esendmsg(__a, __b, __c)
#endif /* _POSIX_PII_SOCKET */
#endif /* __DECC */
#endif /* !_LIBC_POLLUTION_H_ */
#ifdef _POSIX_PII_SOCKET
extern int	__PIIX(accept)	 __((int, struct sockaddr *, socklen_t *));
extern int	__PIIX(getpeername) __((int, struct sockaddr *, socklen_t *));
extern int	__PIIX(getsockname) __((int, struct sockaddr *, socklen_t *));
extern ssize_t	__PIIX(recvfrom)	 __((int, void *, size_t, int, struct sockaddr *, socklen_t *));
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix "_P"
#endif
#endif /* !_LIBC_POLLUTION_H_ */
/*
 * The POSIX versions of recvmsg() and sendmsg() are different from
 * their _XOPEN_SOURCE_EXTENDED brethren because of the size of the
 * msghdr structure.
 */
extern ssize_t	__PII(recvmsg)	 __((int, struct msghdr *, int));
extern ssize_t	__PII(sendmsg)	 __((int, const struct msghdr *, int));
#else /* !_POSIX_PII_SOCKET */
#if _XOPEN_SOURCE>=500
extern int	__R(accept)	 __((int, struct sockaddr *, socklen_t *));
extern int	__R(getpeername) __((int, struct sockaddr *, socklen_t *));
extern int	__R(getsockname) __((int, struct sockaddr *, socklen_t *));
extern ssize_t	__R(recvfrom)	 __((int, void *, size_t, int, struct sockaddr *, socklen_t *));
#else /* !_XOPEN_SOURCE>=500 */
extern int	__R(accept)	 __((int, struct sockaddr *, size_t *));
extern int	__R(getpeername) __((int, struct sockaddr *, size_t *));
extern int	__R(getsockname) __((int, struct sockaddr *, size_t *));
extern ssize_t	__R(recvfrom)	 __((int, void *, size_t, int, struct sockaddr *, size_t *));
#endif /* _XOPEN_SOURCE>=500 */
extern ssize_t	__R(recvmsg)	 __((int, struct msghdr *, int));
extern ssize_t	__R(sendmsg)	 __((int, const struct msghdr *, int));
#endif /* _POSIX_PII_SOCKET */
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* !_LIBC_POLLUTION_H_ */
#else  /* !_XOPEN_SOURCE_EXTENDED || !_POSIX_PII_SOCKET */
extern int	accept		__((int, struct sockaddr *, int *));
extern int	bind		__((int, const struct sockaddr *, int));
extern int	connect		__((int, const struct sockaddr *, int));
extern int	getpeername	__((int, struct sockaddr *, int *));
extern int	getsockname	__((int, struct sockaddr *, int *));
extern int	getsockopt	__((int, int, int, void *, int *));
extern int	recv		__((int, void *, int, int));
extern int	recvfrom	__((int, void *, int, int, struct sockaddr *, int *));
extern int	recvmsg		__((int, struct msghdr *, int));
extern int	send		__((int, const void *, int, int));
extern int	sendmsg		__((int, struct msghdr *, int));
extern int	sendto		__((int, const void *, int, int, const struct sockaddr *, int));
extern int	setsockopt	__((int, int, int, const void *, int));
#endif /* _XOPEN_SOURCE_EXTENDED || _POSIX_PII_SOCKET */
extern int	listen		__((int, int));
extern int	shutdown	__((int, int));
extern int	socket		__((int, int, int));
extern int	socketpair	__((int, int, int, int [2]));
#ifdef _OSF_SOURCE
extern int 	getdomainname	__((char *, int));
#endif /* _OSF_SOURCE */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_SOCKET_H_ */
