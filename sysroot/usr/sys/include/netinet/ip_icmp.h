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
 *	@(#)$RCSfile: ip_icmp.h,v $ $Revision: 4.2.18.1 $ (DEC) $Date: 2001/12/17 20:55:29 $
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
 *	Base:	ip_icmp.h	7.4 (Berkeley) 6/29/88
 *	Merged:	ip_icmp.h	7.5 (Berkeley) 6/28/90
 */

#ifndef _IP_ICMP_H_
#define _IP_ICMP_H_
/*
 * Interface Control Message Protocol Definitions.
 * Per RFC 792, September 1981, and RFC 1191, November 1990.
 */

/*
 * Structure of an icmp header.
 */
struct icmp {
	u_char	icmp_type;		/* type of message, see below */
	u_char	icmp_code;		/* type sub code */
	u_short	icmp_cksum;		/* ones complement cksum of struct */
	union {
		u_char ih_pptr;			/* ICMP_PARAMPROB */
		struct in_addr ih_gwaddr;	/* ICMP_REDIRECT */
		struct ih_idseq {
			n_short	icd_id;
			n_short	icd_seq;
		} ih_idseq;
		int ih_void;
                struct ih_pmtu {                /* ICMP_UNREACH_NEEDFRAG */
                        n_short ipm_void;
                        n_short ipm_nextmtu;
                } ih_pmtu;
	} icmp_hun;
#define	icmp_pptr	icmp_hun.ih_pptr
#define	icmp_gwaddr	icmp_hun.ih_gwaddr
#define	icmp_id		icmp_hun.ih_idseq.icd_id
#define	icmp_seq	icmp_hun.ih_idseq.icd_seq
#define	icmp_void	icmp_hun.ih_void
#define icmp_pmvoid     icmp_hun.ih_pmtu.ipm_void
#define icmp_nextmtu    icmp_hun.ih_pmtu.ipm_nextmtu
	union {
		struct id_ts {
			n_time its_otime;
			n_time its_rtime;
			n_time its_ttime;
		} id_ts;
		struct id_ip  {
			struct ip idi_ip;
			/* options and then 64 bits of data */
		} id_ip;
		u_int	id_mask;
		char	id_data[1];
	} icmp_dun;
#define	icmp_otime	icmp_dun.id_ts.its_otime
#define	icmp_rtime	icmp_dun.id_ts.its_rtime
#define	icmp_ttime	icmp_dun.id_ts.its_ttime
#define	icmp_ip		icmp_dun.id_ip.idi_ip
#define	icmp_mask	icmp_dun.id_mask
#define	icmp_data	icmp_dun.id_data
};

/*
 * Lower bounds on packet lengths for various types.
 * For the error advice packets must first insure that the
 * packet is large enought to contain the returned ip header.
 * Only then can we do the check to see if 64 bits of packet
 * data have been returned, since we need to check the returned
 * ip header length.
 */
#define	ICMP_MINLEN	8				/* abs minimum */
#define	ICMP_TSLEN	(8 + 3 * sizeof (n_time))	/* timestamp */
#define	ICMP_MASKLEN	12				/* address mask */
#define	ICMP_ADVLENMIN	(8 + sizeof (struct ip) + 8)	/* min */
#define	ICMP_ADVLEN(p)	(8 + (((p)->icmp_ip.ip_vhl & 0x0f) << 2) + 8)
	/* N.B.: must separately check that ip_hl >= 5 */
/*
 * RFC 1812:
 * "4.3.2.3 Original Message Header
 * Historically, every ICMP error message has included the Internet
 * header and at least the first 8 data bytes of the datagram that
 * triggered the error.  This is no longer adequate, due to the use of
 * IP-in-IP tunneling and other technologies.  Therefore, the ICMP
 * datagram SHOULD contain as much of the original datagram as possible
 * without the length of the ICMP datagram exceeding 576 bytes. "
 */
#define	ICMP_ERRLEN	528  /* number of data bytes= 576 - ip_hdr - icmp_hdr */
#define	ICMP_MAXLEN	576			

#ifdef _KERNEL
struct icmp_ctlinput_args {
	unsigned     icmp_len;
	unsigned     icmp_iphlen;
	struct mbuf *icmp_mbuf;
#if 0
	union {
		u_int	     icmp_tun_mtu;
		u_char	     icmp_tun_pptr; /* ICMP_PARAMPROB */
	} icmp_ctldata;
#define icmp_tunnel_mtu icmp_ctldata.icmp_tun_mtu
#define icmp_tunnel_pptr icmp_ctldata.icmp_tun_pptr
#endif
};
#endif /* _KERNEL */

	
/*
 * Definition of type and code field values.
 */
#define	ICMP_ECHOREPLY		0		/* echo reply */
#define	ICMP_UNREACH		3		/* dest unreachable, codes: */
#define		ICMP_UNREACH_NET	0		/* bad net */
#define		ICMP_UNREACH_HOST	1		/* bad host */
#define		ICMP_UNREACH_PROTOCOL	2		/* bad protocol */
#define		ICMP_UNREACH_PORT	3		/* bad port */
#define		ICMP_UNREACH_NEEDFRAG	4		/* IP_DF caused drop */
#define		ICMP_UNREACH_SRCFAIL	5		/* src route failed */
#define		ICMP_UNREACH_NET_UNKNOWN	6	/* unknown net */
#define		ICMP_UNREACH_HOST_UNKNOWN	7	/* unknown host */
#define		ICMP_UNREACH_ISOLATED	8		/* src host isolated */
#define		ICMP_UNREACH_NET_PROHIB	9		/* prohibited access */
#define		ICMP_UNREACH_HOST_PROHIB	10	/* ditto */
#define		ICMP_UNREACH_TOSNET	11		/* bad tos for net */
#define		ICMP_UNREACH_TOSHOST	12		/* bad tos for host */
#define		ICMP_UNREACH_ADM_PROHIB	13		/* prohibited access */
#define		ICMP_UNREACH_PREC_VIOL	14		/* precedence viol. */
#define		ICMP_UNREACH_PREC_CUT	15		/* precedence cutoff */
#define		ICMP_UNREACH_MAXCODE	15		/* unreach max code */
#define	ICMP_SOURCEQUENCH	4		/* packet lost, slow down */
#define	ICMP_REDIRECT		5		/* shorter route, codes: */
#define		ICMP_REDIRECT_NET	0		/* for network */
#define		ICMP_REDIRECT_HOST	1		/* for host */
#define		ICMP_REDIRECT_TOSNET	2		/* for tos and net */
#define		ICMP_REDIRECT_TOSHOST	3		/* for tos and host */
#define		ICMP_REDIRECT_MAXCODE	3		/* redirect max code */
#define	ICMP_ECHO		8		/* echo service */
#define	ICMP_ROUTERADVERT	9		/* router advertisement */
#define	ICMP_ROUTERSOLICIT	10		/* router solicitation */
#define	ICMP_TIMXCEED		11		/* time exceeded, code: */
#define		ICMP_TIMXCEED_INTRANS	0		/* ttl==0 in transit */
#define		ICMP_TIMXCEED_REASS	1		/* ttl==0 in reass */
#define		ICMP_TIMXCEED_MAXCODE	1		/* timxceed max code */
#define	ICMP_PARAMPROB		12		/* ip header bad */
#define		ICMP_PARAMPROB_OPTABSENT 1		/* req. opt. absent */
#define		ICMP_PARAMPROB_MAXCODE	1		/* paramprob max code */
#define	ICMP_TSTAMP		13		/* timestamp request */
#define	ICMP_TSTAMPREPLY	14		/* timestamp reply */
#define	ICMP_IREQ		15		/* information request */
#define	ICMP_IREQREPLY		16		/* information reply */
#define	ICMP_MASKREQ		17		/* address mask request */
#define	ICMP_MASKREPLY		18		/* address mask reply */

#define	ICMP_MAXTYPE		18

#define	ICMP_INFOTYPE(type) \
	((type) == ICMP_ECHOREPLY || (type) == ICMP_ECHO || \
	(type) == ICMP_ROUTERADVERT || (type) == ICMP_ROUTERSOLICIT || \
	(type) == ICMP_TSTAMP || (type) == ICMP_TSTAMPREPLY || \
	(type) == ICMP_IREQ || (type) == ICMP_IREQREPLY || \
	(type) == ICMP_MASKREQ || (type) == ICMP_MASKREPLY)

#endif