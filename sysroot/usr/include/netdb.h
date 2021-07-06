/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: netdb.h,v $
 * Revision 4.2.59.3  2005/08/26  20:37:03  Roger_Spinney
 * 	QAR 346 - WFM1206833997-122
 * 	Added missing 'defined' operator for fix in Rev 4.2.59.2.
 *
 * Revision 4.2.59.2  2003/11/10  19:50:40  Greg_Colburn
 * 	QAR 96752 - getaddrinfo doesn't compile with POSIX_SOURCE
 * 	Fix definition of n_net in the netent structure.  The variable
 * 	type of in_addr_t is not defined unless either XOPENSOURCE or
 * 	XOPEN_SOURCE_EXTENDED are defined.
 *
 * Revision 4.2.59.1  2003/06/10  18:56:06  Spider_Boardman
 * 	Fix where rpc/netdb.h comes in for mutual dependencies.
 *
 * Revision 4.2.57.1  2001/12/17  20:57:43  Vladislav_Yasevich
 * 	Backport to wcalpha from wildcat.bl5
 *
 * Revision 4.2.54.1  2000/12/01  15:32:23  Bill_Cote
 * 	Added NI_NUMERICSCOPE for getnameinfo().
 *
 * Revision 4.2.52.3  2000/02/24  15:54:15  Vladislav_Yasevich
 * 	Added AI_NUMERICSERV and updated other flags for getaddrinfo().
 *
 * Revision 4.2.52.2  1999/11/23  00:34:20  Ernie_Petrides
 * 	Make conditional declaration of getnameinfo() conform to visibility
 * 	of socklen_t typedef (as conditionalized in src/kernel/sys/socket.h).
 *
 * Revision 4.2.52.1  1999/10/18  20:23:46  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 *
 * Revision 4.2.50.1  1999/09/08  18:49:41  Vladislav_Yasevich
 * 	Added _XOPEN_SOURCE_EXTENDED to the conditional definition of
 * 	getaddrinfo(). PTR 52-1-236.
 * 	Also separated the flags used with getipnodebyname() from others.
 *
 * Revision 4.2.20.12  1998/12/02  17:35:43  Vladislav_Yasevich
 * 	Changed according to the new spec draft-ietf-ipngwg-bsd-api-new-04.
 * 	[1998/11/25  15:40:50  Vladislav_Yasevich]
 *
 * Revision 4.2.20.11  1998/04/27  17:38:43  Ravi_Shankar
 * 	Conditional the inclusion of getnodebyaddr(), getnodebyname() with
 * 	_INET6 because of the conflict with DECnet defintions in
 * 	netdnet/dnetdb.h
 * 	[1998/04/27  17:37:00  Ravi_Shankar]
 * 
 * Revision 4.2.20.10  1998/04/24  20:45:34  Ravi_Shankar
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -visual **
 * 		** Ancestor revision:	4.2.20.8 **
 * 		** Merge revision:	4.2.20.9 **
 * 	 	** End **
 * 	Updated api, ipv6 socket interface extensions as per Internet Draft draft-ietf-ipngwg-bsd-api-new-01.txt
 * 	[1998/04/22  19:22:27  Ravi_Shankar]
 * 
 * 	update bsdapi for IPv6 hooks
 * 	[1998/04/13  19:23:07  Ravi_Shankar]
 * 
 * Revision 4.2.20.9  1998/04/10  19:07:54  David_Long
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.20.7 **
 * 		** Merge revision:	4.2.20.8 **
 * 	 	** End **
 * 	cleanup the get*ent routines and fix 56486.
 * 	[1998/04/08  22:14:38  David_Long]
 * 
 * Revision 4.2.20.8  1998/01/21  21:15:28  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.2.32.2 **
 * 		** Merge revision:	4.2.32.3 **
 * 	 	** End **
 * 	[1998/01/21  20:54:18  Tony_Bono]
 * 
 * Revision 4.2.20.7  1997/10/23  21:15:06  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL10:PTCOS_BL11 **
 * 		** Ancestor revision:	4.2.17.2 **
 * 		** Merge revision:	4.2.32.2 **
 * 	 	** End **
 * 	[1997/10/23  21:01:20  Tony_Bono]
 * 
 * Revision 4.2.20.6  1997/10/08  20:56:23  Ravi_Shankar
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS;PTCOS_BL10;<> **
 * 		** Ancestor revision:	4.2.20.2 **
 * 		** Merge revision:	4.2.20.5 **
 * 	 	** End **
 * 	Added getaddrinfo/getnameinfo for IPV6 hooks
 * 	[1997/10/06  14:06:17  Ravi_Shankar]
 * 
 * 	Merged with BIND 8.1.1
 * 	[1997/10/01  15:16:05  Ravi_Shankar]
 * 
 * Revision 4.2.20.5  1997/09/15  19:52:15  Brian_Haley
 * 	Removed gethostid() prototype, it's supposed to be in
 * 	unistd.h (qars 50254, 51079, 55156).
 * 	[1997/09/05  14:43:43  Brian_Haley]
 * 
 * Revision 4.2.32.3  1997/09/09  14:28:13  Brian_Haley
 * 	Removed gethostid() prototype, it's supposed to be in
 * 	unistd.h (qars 50254, 51079, 55156).
 * 	[1997/09/08  20:43:32  Brian_Haley]
 * 
 * Revision 4.2.32.2  1997/08/28  16:53:32  Tony_Bono
 * 	Merge of BIND-4.9.3-Final
 * 	[1997/08/27  22:05:48  Tony_Bono]
 * 
 * Revision 4.2.20.4  1997/08/14  15:03:12  Brian_Haley
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.20.2 **
 * 		** Merge revision:	4.2.20.3 **
 * 	 	** End **
 * 	Only include inttypes.h if in a UNIX98 namespace.
 * 	[1997/08/14  14:54:43  Brian_Haley]
 * 
 * Revision 4.2.20.3  1997/08/12  21:18:26  Brian_Haley
 * 	Updated for UNIX98, some in_addr_t types changed to uint32_t.
 * 	Also placed whole file in C++ scope instead of little bits
 * 	of it at the request of the DE group.
 * 	[1997/08/08  18:31:10  Brian_Haley]
 * 
 * Revision 4.2.28.3  1997/03/27  14:18:05  Benjamin_Dibble
 * 	Fix for Eugene_Ku's bind fix.
 * 	[1997/03/26  21:16:36  Benjamin_Dibble]
 * 
 * Revision 4.2.28.2  1997/02/21  18:57:32  Eugene_Ku
 * 	     BIND-4.9.3-Final
 * 	[1997/02/03  21:21:00  Eugene_Ku]
 * 
 * Revision 4.2.20.2  1996/07/26  18:53:04  Patsy_Franklin
 * 	Change type of first param to getnetbyaddr_r from long to int.
 * 	[1996/07/16  18:15:48  Patsy_Franklin]
 * 
 * Revision 4.2.17.2  1994/10/05  19:38:08  Deepak_Gupta
 * 	Merged spec1170 name space changes with platinum .BL1
 * 	[1994/10/05  19:05:42  Deepak_Gupta]
 * 
 * Revision 4.2.15.3  1994/08/03  19:33:46  Deepak_Gupta
 * 	included netinet/in.h in _OSF_SOURCE and _XOPEN_SOURCE_EXTENDED name spaces
 * 	[1994/08/03  19:33:29  Deepak_Gupta]
 * 
 * Revision 4.2.15.2  1994/07/29  19:32:34  Andrew_Weakley
 * 	Created name space for Spec 1170 (_XOPEN_SOURCE_EXTENDED).
 * 	[1994/07/29  19:31:50  Andrew_Weakley]
 * 
 * Revision 4.2.12.3  1994/05/12  18:04:12  Thomas_Peterson
 * 	Added extern "C" macros around h_errno decl since this can become a
 * 	function pointer in the threads case.
 * 	[1994/05/10  17:36:50  Thomas_Peterson]
 * 
 * Revision 4.2.12.2  1994/03/29  18:26:36  Thomas_Peterson
 * 	Fixes for ANSI & C++
 * 	[1994/03/04  22:18:43  Thomas_Peterson]
 * 
 * Revision 4.2.7.3  1993/06/14  19:02:41  David_Long
 * 	Put include of rpc/netdb.h back in for compatability with Silver.
 * 	[1993/06/14  18:03:50  David_Long]
 * 
 * Revision 4.2.7.2  1993/06/08  01:07:51  Thomas_Woodburn
 * 	I18N/thread-safe/ANSI-name-space joint submit.
 * 	[1993/06/07  20:55:19  Thomas_Woodburn]
 * 
 * Revision 4.2.4.4  1993/05/24  20:55:57  David_Long
 * 	Extended *ent_data structures to hold stuff for getsvc.
 * 	[1993/05/24  20:53:31  David_Long]
 * 
 * Revision 4.2.4.3  1993/05/23  02:54:52  David_Long
 * 	Changed sethostent to return int.  Added gethostent and
 * 	*host*_r reentrant prototypes.
 * 	[1993/05/23  02:29:57  David_Long]
 * 
 * Revision 4.2.4.2  1993/04/29  23:37:17  David_Long
 * 	Merged the OSF/1 V1.2 source.
 * 	[1993/04/19  18:44:09  David_Long]
 * 
 * Revision 4.2.2.2  1992/04/06  15:51:33  Geraldine_Harter
 * 	Types cleanup; changed n_net type from long to int;
 * 	changed 1st arg proto def'n of getnetbyaddr() from long to int
 * 	[92/04/06  15:50:57  Geraldine_Harter]
 * 
 * Revision 4.2  91/09/20  05:18:11  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* @(#)$RCSfile: netdb.h,v $ $Revision: 4.2.59.3 $ (OSF) $Date: 2005/08/26 20:37:03 $ */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *      netdb.h     5.10 (Berkeley) 6/27/88
 */


#ifndef _NETDB_H_
#define _NETDB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <netinet/in.h>
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
#include <inttypes.h>	/* defines uint32_t for UNIX98 */
#endif

#define _PATH_HEQUIV    "/etc/hosts.equiv"
#define _PATH_HOSTS     "/etc/hosts"
#define _PATH_NETWORKS  "/etc/networks"
#define _PATH_PROTOCOLS "/etc/protocols"
#define _PATH_SERVICES  "/etc/services"

/* Internal constants
 */
#define _MAXALIASES	35
#define _MAXLINELEN	1024
#define _MAXADDRS	35
#define	_HOSTBUFSIZE	(BUFSIZ + 1)

/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
struct  hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
	int	h_addrtype;	/* host address type */
	int	h_length;	/* length of address */
	char	**h_addr_list;	/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};

#ifdef _OSF_SOURCE

#include <rpc/netdb.h>

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

/*
 * After a successful call to gethostbyname_r()/gethostbyaddr_r(), the
 * structure hostent_data will contain the data to which pointers in
 * the hostent structure will reference.
 */
struct  hostent_data {
	struct in_addr	host_addr;
	char		*h_addr_ptrs[_MAXADDRS + 1];
	char		hostaddr[_MAXADDRS];
	char		hostbuf[_HOSTBUFSIZE];
	char		*host_aliases[_MAXALIASES];
	char		*host_addrs[2];
	FILE		*hostf;
#ifdef	_LIBC_POLLUTION_H_
	void		*svc_data;
#else
	int		svc_gethostflag;
	int		svc_gethostbind;
#endif
};
#endif	/* _REENTRANT || _THREAD_SAFE */
#endif	/* _OSF_SOURCE */

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct	netent {
	char		*n_name;	/* official name of net */
	char		**n_aliases;	/* alias list */
	int		n_addrtype;	/* net address type */

#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
	uint32_t	n_net;
#elif defined (_XOPEN_SOURCE) || defined (_XOPEN_SOURCE_EXTENDED)
	in_addr_t	n_net;		/* Replaced unsigned int type to     */
					/* typedef as specified by Spec1170. */
					/* in_addr_t defined as unsigned int */
					/* in netinet/in.h		     */
#else
	unsigned int n_net;
#endif /* _XOPEN_SOURCE && _XOPEN_SOURCE>=500 */
};

#ifdef _OSF_SOURCE
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct  netent_data {		/* should be considered opaque */
	FILE	*net_fp;
	char	line[_MAXLINELEN];
	char	*net_aliases[_MAXALIASES];
#ifdef	_LIBC_POLLUTION_H_
	void	*svc_data;
#else
	int	_net_stayopen;
	int	svc_getnetflag;
#endif
};
#endif	/* _REENTRANT || _THREAD_SAFE */
#endif	/* _OSF_SOURCE */

struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
	int	s_port;		/* port # */
	char	*s_proto;	/* protocol to use */
};

#ifdef _OSF_SOURCE
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct  servent_data {		/* should be considered opaque */
	FILE	*serv_fp;
	char	line[_MAXLINELEN];
	char	*serv_aliases[_MAXALIASES];
#ifdef	_LIBC_POLLUTION_H_
	void	*svc_data;
#else
	int	_serv_stayopen;
	int	svc_getservflag;
#endif
};
#endif	/* _REENTRANT || _THREAD_SAFE */
#endif	/* _OSF_SOURCE */

struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
	int	p_proto;	/* protocol # */
};

#ifdef _OSF_SOURCE
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct  protoent_data {		/* should be considered opaque */
	FILE	*proto_fp;
	char	line[1024];
	char	*proto_aliases[_MAXALIASES];
#ifdef	_LIBC_POLLUTION_H_
	void	*svc_data;
#else
	int	_proto_stayopen;
	int	svc_getprotoflag;
#endif
};
#endif	/* _REENTRANT || _THREAD_SAFE */
#endif	/* _OSF_SOURCE */

#ifdef _OSF_SOURCE
/*
 * addrinfo structure
 */

struct addrinfo {
        int              ai_flags;      /* input flags */
        int              ai_family;     /* protofamily for socket */
        int              ai_socktype;   /* socket type */
        int              ai_protocol;   /* protocol for socket */
        size_t           ai_addrlen;    /* length of socket-address */
        char            *ai_canonname;  /* service location canonical name */
        struct sockaddr *ai_addr;       /* socket-address for socket */
        struct addrinfo *ai_next;       /* pointer to next in list */
};

#if defined (_SOCKADDR_LEN) || defined (_XOPEN_SOURCE_EXTENDED)
#define getaddrinfo ngetaddrinfo
#else
#define getaddrinfo ogetaddrinfo
#endif

/*
 * Flag values for getaddrinfo()
 */

#define AI_PASSIVE      0x00000001      /* socket address intended for bind() */
#define AI_CANONNAME    0x00000002      /* request for canonical name */
#define AI_NUMERICHOST  0x00000004      /* numeric host address string */
#define AI_ALL          0x00000008      /* Both AAAA and A records */
#define AI_V4MAPPED     0x00000010      /* request IPV4 mapped IPV6 address */
#define AI_ADDRCONFIG   0x00000020      /* Address Family must be configured */
#define AI_NUMERICSERV	0x00000040	/* numeric service string */
#define AI_DEFAULT      (AI_V4MAPPED | AI_ADDRCONFIG)   /* Default behavior */

/*
 * Flag values for getnameinfo()
 */

#define NI_DGRAM        0x00000001
#define NI_NAMEREQD     0x00000002
#define NI_NOFQDN       0x00000004
#define NI_NUMERICHOST  0x00000008
#define NI_NUMERICSERV  0x00000010
#define NI_NUMERICSCOPE 0x00000020

#define NI_MAXHOST      1025
#define NI_MAXSERV      32


/*
 * Error values for getaddrinfo()
 */

#define EAI_ADDRFAMILY  1     /* address family for nodename not supported */
#define EAI_AGAIN       2     /* temporary failure in name resolution */
#define EAI_BADFLAGS    3     /* invalid value for ai_flags */
#define EAI_FAIL        4     /* non-recoverable failure in name resolution */
#define EAI_FAMILY      5     /* ai_family not supported */
#define EAI_MEMORY      6     /* memory allocation failure */
#define EAI_NODATA      7     /* no address associated with nodename */
#define EAI_NONAME      8     /* nodename nor servname provided, or not known */
#define EAI_SERVICE     9     /* servname not supported for ai_socktype */
#define EAI_SOCKTYPE    10    /* ai_socktype not supported */
#define EAI_SYSTEM      11    /* system error returned in errno */

#endif /* _OSF_SOURCE */

#ifdef _XOPEN_SOURCE_EXTENDED
extern struct hostent *gethostbyaddr __((const void *, size_t, int));
extern void sethostent __((int));
#if defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)
extern struct netent *getnetbyaddr __((uint32_t, int));
#else
extern struct netent *getnetbyaddr __((in_addr_t, int));
#endif
extern void setnetent __((int));
extern void setservent __((int));
extern void setprotoent __((int));
#else
extern struct hostent *gethostbyaddr __((const char *, int, int));
extern int sethostent __((int));
extern struct netent *getnetbyaddr __((int, int));
extern int setnetent __((int));
extern int setservent __((int));
extern int setprotoent __((int));
#endif

#ifdef _OSF_SOURCE
extern void freeaddrinfo __((struct addrinfo *));
extern int getaddrinfo __((const char *, const char *, const struct addrinfo *, \
			   struct addrinfo **));
#if (defined (_XOPEN_SOURCE) && (_XOPEN_SOURCE>=500)) || \
    defined(_POSIX_PII_SOCKET)
extern int getnameinfo __((const struct sockaddr *, socklen_t, char *, size_t, \
                           char *, size_t, int));
#else
extern int getnameinfo __((const struct sockaddr *, size_t, char *, size_t, \
                           char *, size_t, int));
#endif
extern char *gai_strerror __((int));
extern struct hostent  *getipnodebyname __((const char *, int, int, int*));
extern struct hostent  *getipnodebyaddr __((const void *, size_t, int, int*));
extern void freehostent __((struct hostent *));
#endif /* _OSF_SOURCE */


extern struct hostent *gethostbyname __((const char *));
extern struct hostent *gethostent __((void));
extern void endhostent __((void));

extern struct netent *getnetbyname __((const char *));
extern struct netent *getnetent __((void));
extern void endnetent __((void));

extern struct servent *getservbyname __((const char *, const char *));
extern struct servent *getservbyport __((int, const char *));
extern struct servent *getservent __((void));
extern void endservent __((void));

extern struct protoent *getprotobyname __((const char *));
extern struct protoent *getprotobynumber __((int));
extern struct protoent *getprotoent __((void));
extern void endprotoent __((void));

#ifdef _OSF_SOURCE

#if defined(_REENTRANT) || defined(_THREAD_SAFE)

#include <arpa/nameser.h>
#include <resolv.h>

extern int gethostbyname_r __((const char *, struct hostent *, 
					struct hostent_data *));
extern int gethostbyaddr_r __((const char *, int, int, struct hostent *, \
					struct hostent_data *));
extern int gethostent_r __((struct hostent *, struct hostent_data *));
extern int sethostent_r __((int, struct hostent_data *));
extern void endhostent_r __((struct hostent_data *));

extern int getnetbyaddr_r __((int, int, struct netent *, \
					struct netent_data *));
extern int getnetbyname_r __((const char *, struct netent *, \
					struct netent_data *));
extern int getnetent_r __((struct netent *, struct netent_data *));
extern int setnetent_r __((int, struct netent_data *));
extern void endnetent_r __((struct netent_data *));

extern int getservbyname_r __((const char *, const char *, struct servent *, \
					struct servent_data *));
extern int getservbyport_r __((int, const char *, struct servent *, \
					struct servent_data *));
extern int getservent_r __((struct servent *, struct servent_data *));
extern int setservent_r __((int, struct servent_data *));
extern void endservent_r __((struct servent_data *));

extern int getprotobyname_r __((const char *, struct protoent *, \
					struct protoent_data *));
extern int getprotobynumber_r __((int, struct protoent *, \
					struct protoent_data *));
extern int getprotoent_r __((struct protoent *, struct protoent_data *));
extern int setprotoent_r __((int, struct protoent_data *));
extern void endprotoent_r __((struct protoent_data *));

/*
 * Per thread h_errno.
 */
#define h_errno   (*_h_errno())

#endif	/* _REENTRANT || _THREAD_SAFE */
#endif	/* _OSF_SOURCE */

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */
extern	int h_errno;

#ifdef _OSF_SOURCE
#define NETDB_INTERNAL  -1      /* see errno */
#define NETDB_SUCCESS   0       /* no problem */
#endif	/* _OSF_SOURCE */

#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */

#ifdef __cplusplus
}
#endif

#endif /* _NETDB_H_ */
