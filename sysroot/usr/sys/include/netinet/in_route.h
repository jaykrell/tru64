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
 * @(#)$RCSfile: in_route.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 2000/01/12 16:52:10 $
 */

#ifndef _IN_ROUTE_H_
#define _IN_ROUTE_H_

#include <net/route.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
 * Internet flavor of 'struct route'.  To allow this structure to be
 * cast as a 'struct route', the start of the structure must match
 * 'struct route', i.e. an rtentry followed by a sockaddr.
 */

struct in_route {
	struct rtentry *in_ro_rt;
	union {
		struct sockaddr	    in_ro_dst_un_dst;
		struct sockaddr_in  in_ro_dst_un_dst4;
		struct sockaddr_in6 in_ro_dst_un_dst6;
	} in_ro_dst_un;
	u_long in_ro_timestamp; /* cached route table timestamp */
	caddr_t in_ro_llinfo;
	long in_ro_reserved[1]; /* reserved for future use */
};

#ifdef _KERNEL
#define in_ro_dst  in_ro_dst_un.in_ro_dst_un_dst
#define in_ro_dst4 in_ro_dst_un.in_ro_dst_un_dst4
#define in_ro_dst6 in_ro_dst_un.in_ro_dst_un_dst6

/* Macros to set the route timestamp in an in_route structure */
#define IN_ROUTE_TIMESTAMP(in_ro) ((in_ro)->in_ro_timestamp = route_timestamp)
#define IN_ROUTE6_TIMESTAMP(in_ro) ((in_ro)->in_ro_timestamp = route6_timestamp)
#define IN_ROUTE_TIMESTAMP_AF(in_ro, af) {	\
	if ((af) == AF_INET6)			\
		IN_ROUTE6_TIMESTAMP((in_ro));	\
	else					\
		IN_ROUTE_TIMESTAMP((in_ro));	\
    }

/* Macros to test the route timestamp in an in_route structure */
#define IN_ROUTE_TIMESTAMP_INVALID(in_ro) \
	((in_ro)->in_ro_timestamp != route_timestamp)
#define IN_ROUTE6_TIMESTAMP_INVALID(in_ro) \
	((in_ro)->in_ro_timestamp != route6_timestamp)
#define IN_ROUTE_TIMESTAMP_INVALID_AF(in_ro, af)			\
	(((af) == AF_INET6 && IN_ROUTE6_TIMESTAMP_INVALID((in_ro))) ||	\
	 ((af) != AF_INET6 && IN_ROUTE_TIMESTAMP_INVALID((in_ro))))

#endif

#endif /* _IN_ROUTE_H_ */
