/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: in.h,v $
 * Revision 4.3.57.3  2003/11/13  22:42:42  Brian_Haley
 * 	Updated IPPROTO_MH to be 135 as specified by IANA.
 *
 * Revision 4.3.57.2  2003/09/23  21:52:44  Brian_Haley
 * 	Mobile IPv6 update.
 * 	Added IPPROTO_MH and IPPROTO_MOBILITY for backwards-compatibility.
 * 	Define 'CONST' so we don't get compiler errors.
 *
 * Revision 4.3.57.1  2003/09/10  17:47:41  Vladislav_Yasevich
 * 	Updated the constant for IP_MAX_MEMBERSHIPS, and added a constant
 * 	for IP_DEFAULT_MEMBERSHIPS that provides the initial number of
 * 	memberships supported per socket.  QAR 97048.
 *
 * Revision 4.3.47.2  2002/01/29  21:23:43  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.3.47.1  2001/12/17  20:54:50  Vladislav_Yasevich
 * Merge Information:  Non-Visual Merge: User specified tree wildcatos
 *     User Revision:  wcalphaos_bld:4.3.40.1 Local Ancestor: n/a
 *    Merge Revision:  wildcatos_br:4.3.42.3
 *   Common Ancestor:  4.3.40.1
 * 	Merge IPSec changes from wildcatos.
 *
 * Revision 4.3.42.3  2001/05/22  15:30:20  Dan_Vuong
 *      Add IPPROTO_IPCOMP
 * 
 * Revision 4.3.40.1  1999/10/18  20:20:56  Jack_McCann
 * 	IPv6 submit to Zulu BL6
 * 
 * Revision 4.3.33.5  1999/08/04  15:05:57  Vladislav_Yasevich
 * 	Changed INET_ADDRSTRLEN to have a value of 16 as per rfc.
 * 	[1999/08/02  19:46:51  Vladislav_Yasevich]
 * 
 * Revision 4.3.33.4  1999/06/08  18:09:42  Jack_McCann
 * 	IPv6 EAK X6.3 merge to Steel BL23
 * 	- add IPPROTO_IPV4
 * 	- move all IPv6-related IPPROTO_xxx defines here from in6.h
 * 	  so they are all in one place
 * 	[1999/06/08  15:51:41  Jack_McCann]
 * 
 * Revision 4.3.27.12  1999/03/19  16:41:04  Brian_Haley
 * 	Do not #include endian.h in UNIX95 namespace (qar 69774).
 * 	[1999/03/17  14:50:32  Brian_Haley]
 * 
 * Revision 4.3.27.11  1999/02/04  20:45:16  Brian_Haley
 * 	Always #include endian.h to get ntoh*, hton* prototypes.
 * 	Needed for UNIX98 (qar 66339).
 * 	[1999/02/03  22:50:22  Brian_Haley]
 * 
 * Revision 4.3.27.10  1998/01/21  21:15:04  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL11:PTCOS_BL14 **
 * 		** Ancestor revision:	4.3.26.2 **
 * 		** Merge revision:	4.3.26.3 **
 * 	 	** End **
 * 	[1998/01/21  20:49:00  Tony_Bono]
 * 
 * Revision 4.3.27.9  1997/12/16  18:51:30  Michael_Enright
 * 	remove RTF_LOOPBACK
 * 	[1997/12/10  15:41:01  Michael_Enright]
 * 
 * Revision 4.3.27.8  1997/10/09  21:15:05  Brian_Haley
 * 	Backed out 4.3.27.2 changes, bindresvport() prototype shouldn't
 * 	be here, it's in unistd.h.
 * 	[1997/10/09  21:07:54  Brian_Haley]
 * 
 * Revision 4.3.26.3  1997/10/08  19:01:25  John_Dustin
 * 	Add encapsulated security payload (IPPROTO_ESP) and authentication
 * 	header (IPPROTO_AH) protocol placeholders for tunnels layered prod.
 * 	[1997/09/29  12:16:20  John_Dustin]
 * 
 * Revision 4.3.27.7  1997/09/30  13:13:48  Jack_McCann
 * 	IPv6 hooks:
 * 	- add INET_ADDSTRLEN
 * 	- include <netinet/in6.h>
 * 	- add IPPROTO_IPV6
 * 	[1997/09/30  12:17:09  Jack_McCann]
 * 
 * Revision 4.3.27.6  1997/09/29  20:43:22  Michael_Enright
 * 	add RTF_LOOPBACK
 * 	[1997/09/26  01:57:20  Michael_Enright]
 * 
 * Revision 4.3.27.5  1997/07/25  18:00:15  Ravi_Shankar
 * 	Resolve the problem with arguements for bindresvport
 * 	[1997/07/25  17:59:59  Ravi_Shankar]
 * 
 * Revision 4.3.27.4  1997/06/04  17:55:21  Jack_McCann
 * 	- add IP_RTF_PMTU route flag
 * 	[1997/05/28  15:26:00  Jack_McCann]
 * 
 * Revision 4.3.27.3  1997/02/06  02:46:29  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 **
 * 		** Ancestor revision:	4.3.16.5 **
 * 		** Merge revision:	4.3.26.2 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/06  02:30:24  Tony_Bono]
 * 
 * Revision 4.3.27.2  1996/12/09  22:01:24  Neil_Lewis
 * 	Add conditionals around prototype for bindresvport()
 * 	[1996/11/26  22:53:36  Neil_Lewis]
 * 	Eliminate compiler warnings when compiled with -warnprotos.
 * 	[1996/11/12  16:14:33  Neil_Lewis]
 * 
 * Revision 4.3.26.2  1996/12/09  16:49:52  Geraldine_Harter
 * 	Add IPPROTO_IFMP for Ipsilon protocol
 * 	[1996/12/04  18:25:52  Geraldine_Harter]
 * 
 * Revision 4.3.16.5  1995/11/15  20:33:23  John_Dustin
 * 	add IP_PROXY as hook for IBG Firewall product
 * 	[1995/11/14  23:16:55  John_Dustin]
 * 
 * Revision 4.3.16.4  1995/06/15  20:29:03  Ajay_Kachrani
 * 	bmerged
 * 	[1995/06/13  20:55:25  Ajay_Kachrani]
 * 	Added 3.5 IP Multicast support including new IPPROTO_IPIP and RSVP support.
 * 	[1995/05/18  18:53:38  Ajay_Kachrani]
 * 
 * Revision 4.3.16.3  1994/12/16  22:17:19  Sunil_Bangad
 * 	Made the inclusion of sys/socket.h dependent
 * 	upon the non-definition of _XOPEN_SOURCE_EXTENDED
 * 	to avoid Spec1170 namespace pollution.  Changed
 * 	u_int to unsigned int throughout.  Moved the
 * 	in_port_t and in_addr_t types to sys/types.h
 * 	[1994/12/15  15:34:45  Sunil_Bangad]
 * 
 * Revision 4.3.16.2  1994/10/05  20:49:32  Deepak_Gupta
 * 	Merged spec1170 name space changes with platinum .BL1
 * 	[1994/10/05  19:00:58  Deepak_Gupta]
 * 
 * Revision 4.3.14.3  1994/09/23  19:52:20  Deepak_Gupta
 * 	Changed all the BSD typedefs to their base types.
 * 	[1994/09/23  19:52:05  Deepak_Gupta]
 * 
 * Revision 4.3.14.2  1994/07/29  19:12:20  Andrew_Weakley
 * 	Create name space for Spec 1170.
 * 	[1994/07/29  18:56:59  Andrew_Weakley]
 * 
 * Revision 4.3.10.7  1994/05/12  18:01:23  Thomas_Peterson
 * 	Removed local decls of ntohs(), htons(), ntohl(), htonl() and included
 * 	<machine/endian.h> which has these same decls already.
 * 	[1994/04/25  16:45:13  Thomas_Peterson]
 * 
 * Revision 4.3.10.6  1994/02/23  15:51:20  Gerry_Feldman
 * 	 Added space before the __() macros.
 * 	[1994/02/23  15:49:56  Gerry_Feldman]
 * 
 * Revision 4.3.10.4  1994/02/22  21:22:17  Gerry_Feldman
 * 	Added definitions for ntohs, ntohl, htons, and htonl
 * 	[1994/02/22  21:06:38  Gerry_Feldman]
 * 
 * Revision 4.3.10.3  1993/11/09  19:42:07  Geraldine_Harter
 * 	Merge in Sterling BL7:
 * 	Revision 4.3.6.3  1993/10/04  21:14:07  Heather_Gray
 * 	Revert to old option defs for binary compatibility.
 * 	[1993/10/04  01:36:09  Heather_Gray]
 * 
 * Revision 4.3.10.2  1993/09/28  19:06:17  Geraldine_Harter
 * 	Merge in Sterling BL6.
 * 	 Revision 4.3.6.2  1993/05/16  21:16:45  Heather_Gray
 * 		Changed sockopt values to be consistent with BSD.
 * 		[1993/05/12  17:58:44  Heather_Gray]
 * 		Correct comment re: mbuf.
 * 		[1993/05/02  22:06:28  Heather_Gray]
 * 		Add IGMP protocol and support for class D handling.
 * 		Add IP Multicast group definitions.
 * 		Add IP Multicast socket option definitions and
 * 		struct mreq.
 * 		[1993/04/12  00:46:24  Heather_Gray]
 * 	[1993/09/28  15:50:40  Geraldine_Harter]
 * 
 * Revision 4.3.3.3  1992/04/15  14:08:43  Geraldine_Harter
 * 	Merged in Silver BL6
 * 	Revision 4.3.4.2  92/04/13  18:30:55  devbld_gsf
 * 	First AG_BL6 version.  Moved from Ag baselevel delivery tree.
 * 	Revision 4.2.2.2  92/03/27  15:05:59  Craig_Horman
 * 	Added C++ Support (redefined ip_opts and included sys/types.h)
 * 	[92/03/10  14:30:56  Craig_Horman]
 * 
 * Revision 4.3.3.2  92/04/06  14:28:59  Geraldine_Harter
 * 	Removed 'ifdef __alpha' from code that is not alpha-dependent.  Kept the
 * 	version of the code that correctly declares a net-type to be 'u_int' instead
 * 	of 'u_long'
 * 	[92/04/06  14:25:36  Geraldine_Harter]
 * 
 * Revision 4.3  92/01/15  02:02:59  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 4.2.2.2  91/12/07  16:11:14  Ray_Lanza
 * 	Merged tin-based ALPHA version
 * 	[91/12/07  16:06:07  Ray_Lanza]
 * 
 * Revision 4.2  91/09/19  22:46:53  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*
 *	@(#)$RCSfile: in.h,v $ $Revision: 4.3.57.3 $ (DEC) $Date: 2003/11/13 22:42:42 $
 */
/*
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
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
 *	Base:	in.h	7.8 (Berkeley) 9/13/89
 *	Merged:	in.h	7.10 (Berkeley) 6/28/90
 */

#ifndef	_NETINET_IN_H_
#define	_NETINET_IN_H_

#include <sys/types.h>

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#include <sys/socket.h>		/* Need new sa_family_t typedef for Spec1170 */
#endif

/*
 * Internet address (a structure for historical reasons)
 */
struct in_addr {
#ifdef _XOPEN_SOURCE_EXTENDED
	/* typedef changed for Spec 1170 conformance: 			*/
	/* from u_int to in_addr_t (both are defined as unsigned int)	*/
	in_addr_t  s_addr;
#else
	unsigned int s_addr;
#endif
};

#ifdef _OSF_SOURCE
/*
 * Maximum length of IPv4 address as a text string (RFC2133)
 */
#define INET_ADDRSTRLEN 16
#endif

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981.
 */

/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */
#define IPPROTO_HOPOPTS		0		/* IPv6 Hop-by-Hop options */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define IPPROTO_IGMP		2		/* group mgmt protocol */
#define	IPPROTO_GGP		3		/* gateway^2 (deprecated) */
#define IPPROTO_IPIP            4               /* IPv4 inside IP */
#define IPPROTO_IPV4            IPPROTO_IPIP    /* IPv4 inside IP */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_EGP		8		/* exterior gateway protocol */
#define	IPPROTO_PUP		12		/* pup */
#define	IPPROTO_UDP		17		/* user datagram protocol */
#define	IPPROTO_IDP		22		/* xns idp */
#define	IPPROTO_TP		29 		/* tp-4 w/ class negotiation */
#define IPPROTO_IPV6		41		/* IPv6 header */
#define	IPPROTO_ROUTING		43		/* IPv6 Routing header */
#define	IPPROTO_FRAGMENT	44		/* IPv6 fragmentation header */
#define IPPROTO_RSVP            46              /* resource reservation proto */
#define	IPPROTO_ESP		50		/* encap. security payload */
#define	IPPROTO_AH		51		/* authentication header */
#define	IPPROTO_ICMPV6		58		/* ICMPv6 */
#define	IPPROTO_NONE		59		/* IPv6 no next header */
#define	IPPROTO_DSTOPTS		60		/* IPv6 Destination options */
#define	IPPROTO_EON		80		/* ISO cnlp */
#define	IPPROTO_IFMP		101		/* Ipsilon Flow Mgmt Protocol*/
#define IPPROTO_IPCOMP          108             /* IP Payload Compression */
#define	IPPROTO_MH		135		/* IPv6 Mobility header */
#define	IPPROTO_MOBILITY	IPPROTO_MH	/* IPv6 Mobility header */

#define	IPPROTO_RAW		255		/* raw IP packet */
#define	IPPROTO_MAX		256


/*
 * Local port number conventions:
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */
#define	IPPORT_RESERVED		1024
#define	IPPORT_USERRESERVED	5000

/* From Sun 4.1 sources, needed for SUN rpc */
#define    IPPORT_TIMESERVER       37

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	IN_CLASSA(i)		(((int)(i) & 0x80000000) == 0)
#define	IN_CLASSA_NET		0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		0x00ffffff
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((int)(i) & 0xc0000000) == 0x80000000)
#define	IN_CLASSB_NET		0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		0x0000ffff
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((int)(i) & 0xe0000000) == 0xc0000000)
#define	IN_CLASSC_NET		0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		0x000000ff

#define	IN_CLASSD(i)		(((int)(i) & 0xf0000000) == 0xe0000000)
#define IN_CLASSD_NET		0xf0000000	/* These ones aren't really */
#define IN_CLASSD_NSHIFT	28		/* net and host fields, but */
#define IN_CLASSD_HOST		0x0fffffff	/* routing needn't know.  */
#define	IN_MULTICAST(i)		IN_CLASSD(i)

#define	IN_EXPERIMENTAL(i)	(((int)(i) & 0xe0000000) == 0xe0000000)
#define	IN_BADCLASS(i)		(((int)(i) & 0xf0000000) == 0xf0000000)

#define	INADDR_ANY		(unsigned int)0x00000000
#define	INADDR_BROADCAST	(unsigned int)0xffffffff	/* must be masked */
#define INADDR_LOOPBACK         (unsigned int)0x7F000001

#define INADDR_UNSPEC_GROUP	(unsigned int)0xe0000000	/* 224.0.0.0   */
#define INADDR_ALLHOSTS_GROUP	(unsigned int)0xe0000001	/* 224.0.0.1   */
#define INADDR_MAX_LOCAL_GROUP	(unsigned int)0xe00000ff	/* 224.0.0.255 */

#ifndef _KERNEL
#define	INADDR_NONE		0xffffffff		/* -1 return */
#endif

#define	IN_LOOPBACKNET		127			/* official! */

/*
 * Socket address, internet style.
 */
#if defined(_SOCKADDR_LEN) || defined(_KERNEL) || \
			defined(_XOPEN_SOURCE_EXTENDED)
struct sockaddr_in {
	unsigned char	sin_len;
	sa_family_t	sin_family;	/* New typedef for Spec 1170 */
	in_port_t	sin_port;	/* New typedef for Spec 1170 */
	struct	in_addr sin_addr;
#ifdef _XOPEN_SOURCE_EXTENDED
	unsigned char	sin_zero[8];	/* Changed type from char to	*/
					/* unsigned char for Spec 1170	*/
#else
	char	sin_zero[8];
#endif
};
#else
struct sockaddr_in {
	unsigned short	sin_family;
	unsigned short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};
#endif

/*
 * Structure used to describe IP options.
 * Used to store options internally, to pass them to a process,
 * or to restore options retrieved earlier.
 * The ip_dst is used for the first-hop gateway when using a source route
 * (this gets put into the header proper).
 */
#ifdef _OSF_SOURCE
struct ip_opts {
	struct	in_addr ip_dst;		/* first hop, 0 w/o src rt */
#if defined(__cplusplus)
	char    Ip_opts[40];            /* cannot have same name as class */
#else
	char	ip_opts[40];		/* actually variable in size */
#endif
};
#endif	/* _OSF_SOURCE */

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define	IP_OPTIONS	1	/* buf/ip_opts; set/get IP per-packet options */
#define	IP_HDRINCL	2	/* int; header is included with data (raw) */
#define	IP_TOS		3	/* int; IP type of service and precedence */
#define	IP_TTL		4	/* int; IP time to live */
#define	IP_RECVOPTS	5	/* bool; receive all IP options w/datagram */
#define	IP_RECVRETOPTS	6	/* bool; receive IP options for response */
#define	IP_RECVDSTADDR	7	/* bool; receive IP dst addr w/datagram */
#define	IP_RETOPTS	8	/* ip_opts; set/get IP per-packet options */
#define IP_MULTICAST_IF	   9	/* in_addr; IP multicast interface */
#define IP_MULTICAST_TTL   10	/* u_char; IP multicast timetolive */
#define IP_MULTICAST_LOOP  11	/* u_char; IP multicast loopback */
#define IP_ADD_MEMBERSHIP  12	/* ip_mreq; add  an IP group membership */
#define IP_DROP_MEMBERSHIP 13	/* ip_mreq; drop an IP group membership */
#define IP_MULTICAST_VIF   14   /* set/get IP mcast vir. interface */
#ifdef __VMS
#define OIP_MULTICAST_IF    16	/* in_addr; IP multicast interface */
#define OIP_MULTICAST_TTL   17	/* u_char; IP multicast timetolive */
#define OIP_MULTICAST_LOOP  18	/* u_char; IP multicast loopback */
#define OIP_ADD_MEMBERSHIP  19	/* ip_mreq; add  an IP group membership */
#define OIP_DROP_MEMBERSHIP 20	/* ip_mreq; drop an IP group membership */
#define OIP_MULTICAST_VIF   21  /* set/get IP mcast vir. interface */
#endif /* __VMS */
#ifndef __VMS
#define IP_RSVP_ON         15   /* set rsvp var. in kernel         */
#define IP_RSVP_OFF        16   /* unset rsvp var in kernel        */
#define IP_RSVP_VIF_ON     17   /* set rsvp per-vif socket         */
#define IP_RSVP_VIF_OFF    18   /* unset rsvp per-vif socket       */
#define	IP_PROXY	   19	/* bool; allow proxy packet reception */
#else /* __VMS */
/* 
 * OPENVMS IP Options different than DUNIX for UCX backward capability
 * There is a conflict with UCX defined IP options
 */
#define IP_RSVP_ON         25   /* set rsvp var. in kernel         */
#define IP_RSVP_OFF        26   /* unset rsvp var in kernel        */
#define IP_RSVP_VIF_ON     27   /* set rsvp per-vif socket         */
#define IP_RSVP_VIF_OFF    28   /* unset rsvp per-vif socket       */
#define	IP_PROXY	   29	/* bool; allow proxy packet reception */
#endif /* __VMS */

#define IP_DEFAULT_MULTICAST_TTL   1	/* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP  1	/* normally hear sends if a member  */
#define IP_DEFAULT_MEMBERSHIPS	   20	/* default multicasts per socket */
#define IP_MAX_MEMBERSHIPS	   65535	/* max per socket */

/*
 * IP protocol specific route flags
 */

#define	IP_RTF_PMTU	    RTF_PROTO3	/* rmx_mtu set by pmtu discovery */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
#ifdef _OSF_SOURCE
struct ip_mreq {
	struct in_addr	imr_multiaddr;	/* IP multicast address of group */
	struct in_addr	imr_interface;	/* local IP address of interface */
};
#endif

/*
 * Included to get decls for ntohs, htons, ntohl, htonl.  These can
 * be visible in UNIX98, but not in UNIX95 namespace.
 */
#if (defined (_XOPEN_SOURCE_EXTENDED) && _XOPEN_SOURCE>=500) || defined (_OSF_SOURCE)
#include <machine/endian.h>
#endif

#ifdef _KERNEL

#ifndef CONST
#define CONST const
#define UNDEF_CONST
#endif

extern	struct domain inetdomain;
extern	CONST struct protosw inetsw[];
extern	int inetprintfs;
extern	int ipgateway, ipforwarding;

#ifdef UNDEF_CONST
#undef CONST
#endif
#endif

#ifdef _OSF_SOURCE
#include <netinet/in6.h>
#endif

#endif
