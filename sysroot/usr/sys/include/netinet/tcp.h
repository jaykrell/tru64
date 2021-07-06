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
 *	@(#)$RCSfile: tcp.h,v $ $Revision: 4.3.29.1 $ (DEC) $Date: 2002/01/29 21:19:27 $
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
 *	Base:	tcp.h	7.5 (Berkeley) 6/29/88
 *	Merged:	tcp.h	7.7 (Berkeley) 6/28/90
 */
#ifndef	_NETINET_TCP_H
#define	_NETINET_TCP_H

#include <netinet/ip.h>

#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

typedef	u_int	tcp_seq;
/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
struct tcphdr {
	u_short	th_sport;		/* source port */
	u_short	th_dport;		/* destination port */
	tcp_seq	th_seq;			/* sequence number */
	tcp_seq	th_ack;			/* acknowledgement number */
#if	defined(_KERNEL) || defined(_NO_BITFIELDS) || (__STDC__ == 1)
	u_char	th_xoff;
#else
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	th_x2:4,		/* (unused) */
		th_off:4;		/* data offset */
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	th_off:4,		/* data offset */
		th_x2:4;		/* (unused) */
#endif
#endif
	u_char	th_flags;
#define	TH_FIN	0x01
#define	TH_SYN	0x02
#define	TH_RST	0x04
#define	TH_PUSH	0x08
#define	TH_ACK	0x10
#define	TH_URG	0x20
	u_short	th_win;			/* window */
	u_short	th_sum;			/* checksum */
	u_short	th_urp;			/* urgent pointer */
};
#define TCPOPT_MAX_LEN	40
#define	TCPOPT_EOL	0
#define	TCPOPT_NOP	1
#define	TCPOPT_MAXSEG	2
#define TCPOPT_WINDOW   3       	/* rfc 1323 window scale option */
#define TCPOPT_SACK_REQ	4		/* rfc 2018 Sack option requested SYN only */
#define TCPOPT_SACK	5		/* rfc 2018 SACK option */
#define TCPOPT_TS	8       	/* rfc 1323 timestamp option */

/*
 * sack defines
 */
#define TCP_SACK_ELEMENT_LEN 8		/* Sack element have 2 int fields */
#define TCPOPT_SACK_LEN_OK( len ) ((len>=10) && (((((len-2)/8)*8)+2)==len))

/*
 * timestamp defines
 */
#define TCPOPT_TS_LEN	10		/* tcp timestamp option length */
#define TCPOLEN_TSTAMP_APPA ((TCPOPT_NOP<<24)|(TCPOPT_NOP<<16)|(TCPOPT_TS<<8)|TCPOPT_TS_LEN)

#define TCPOPT_CREATE_TSOPT(opt, optlen, TSVAL, TSECR)		\
{								\
	int *__tmp=(int*)(opt) ;				\
	__tmp[0]=htonl(TCPOLEN_TSTAMP_APPA) ;			\
	__tmp[1]=htonl(TSVAL) ;					\
	__tmp[2]=htonl(TSECR) ;					\
	optlen+=TCPOPT_TS_LEN+2 ;				\
}

#define TCPOPT_EXTRACT_TSOPT(opt, TSVAL, TSECR)			\
{								\
	bcopy((caddr_t)(&(opt)[2]), &(TSVAL), sizeof(TSVAL)) ;	\
	TSVAL=ntohl(TSVAL) ;					\
	bcopy(&(opt)[2+sizeof(TSVAL)], &(TSECR) , sizeof(TSECR)) ; \
	TSECR=ntohl(TSECR) ;					\
}

/*
 * Default maximum segment size for TCP.
 * For RFC1122 MUST conformance, this needs to be 536.
 */
#define	TCP_MSS	536

#define	TCP_MAXWIN	65535		/* largest value for (unscaled) window */

#define TCP_MAX_WINSHIFT      14	/* maximum window shift */

/*
 * User options (used with set/getockopt).
 */
#define	TCP_NODELAY	0x01	/* don't delay send to coalesce packets */
#define	TCP_MAXSEG	0x02	/* maximum segment size */
/* 
 * Number of retransmissions before dropping connection. Larger than  
 * TCP_MAXRXTSHIFT or -1 for infinity 
 */
#define	TCP_RPTR2RXT	0x03	/* set repeat count for R2 RXT timer */ 
#define TCP_KEEPIDLE	0x04	/* seconds before initial keepalive probe */
#define TCP_KEEPINTVL	0x05	/* seconds between keepalive probes */
#define TCP_KEEPCNT	0x06	/* number of keepalive probes before drop */
#define TCP_KEEPINIT	0x07	/* initial connect timeout (seconds) */
#define TCP_PUSH	0x08	/* set push bit in outbound data packets */
#define	TCP_NODELACK	0x09	/* don't delay send to coalesce packets */
#define TCP_TSOPTENA	0x10	/* time stamp option */
#define	TCP_PAWS	0x20	/* PAWS option */
#define TCP_SACKENA	0x40	/* SACK enabled */
#ifdef __VMS
#define TCP_PROBE_IDLE 0x80     /* Probe idle */
#define TCP_DROP_IDLE 0x81      /* Drop idle */
#endif  /* __VMS */

#endif
