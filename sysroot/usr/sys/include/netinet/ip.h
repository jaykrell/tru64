/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip.h,v $
 * Revision 4.2.26.1  2005/11/30  21:39:52  John_Dustin
 * 	Reduce IPFRAGTTL from 60 down to 18 ticks (1/2 seconds) to reduce
 * 	the chance of frankengrams being accepted over Gigabit Ethernet.
 * 	A cluster dependency requires the value to be evenly divisible by
 * 	both 2 and 3.  Customers can further tune global ipfragttl as needed.
 * 	This fixes QAR 98153.
 *
 * Revision 4.2.24.1  2001/12/17  20:55:07  Vladislav_Yasevich
 * Merge Information:  Non-Visual Merge: User specified tree wildcatos
 *     User Revision:  wcalphaos_bld:4.2.16.3 Local Ancestor: n/a
 *    Merge Revision:  wildcatos_br:4.2.20.1
 *   Common Ancestor:  4.2.16.3
 * 	Merged IPsec changes from wildcat.
 *
 * Revision 4.2.20.1  2001/05/22  15:30:21  Dan_Vuong
 *      Add ipcomp_hdr structure.
 * 
 * Revision 4.2.16.3  1995/11/15  20:26:43  Ajay_Kachrani
 * 	Define MINTTL and DEFTTL for settable ipdefttl.
 * 	[1995/11/13  21:22:10  Ajay_Kachrani]
 * 
 * Revision 4.2.16.2  1995/06/30  22:38:10  Mike_Milicia
 * 	Add MLS secure networking hooks.
 * 	[1995/06/20  22:19:37  Mike_Milicia]
 * 
 * Revision 4.2.13.2  1994/08/24  14:20:20  Heather_Gray
 * 	Include in.h to be self-describing.
 * 	[1994/08/24  13:29:52  Heather_Gray]
 * 
 * Revision 4.2.9.3  1993/10/07  17:54:15  John_Dustin
 * 	sterling to gold merge
 * 	[1993/10/04  18:47:51  John_Dustin]
 * 
 * Revision 4.2.11.3  1993/06/29  18:12:01  SJ_Lee
 * 	add #ifndef
 * 	[1993/06/29  17:46:51  SJ_Lee]
 * 
 * Revision 4.2.11.2  1993/06/23  13:46:05  Heather_Gray
 * 	Change ip_len and uh_ulen fields to unsigned
 * 	for Host Requirements and NFS usage
 * 	[1993/06/22  04:19:13  Heather_Gray]
 * 
 * Revision 4.2.5.2  1993/04/12  14:03:05  Ajay_Kachrani
 * 	Fix ANSI bitfields warning when compiled using -std1
 * 	[1993/04/07  19:46:46  Ajay_Kachrani]
 * 
 * Revision 4.2.3.2  1992/01/29  15:24:35  Geraldine_Harter
 * 	merged in Silver BL3
 * 	Revision 4.2.1.2  92/01/24  18:10:20  devbld_gsf
 * 	First AG_BL3 version. Moved from AG baselevel delivery tree.
 * 	[92/01/29  14:59:53  Geraldine_Harter]
 * 	Merge from ODE/TIN: revision 3.1.9.2
 * 	date: 91/11/14 15:40:37;  author: devrcs;  state: Exp;  lines added/del: 11/1
 * 	sccs rev: 3.2;  orig date: 91/11/04 15:50:46;  orig author: heather
 * 	fix for BYTE_ORDER undefined if _KERNEL not defined
 * 	[91/12/04  10:27:03  William_Burns]
 * 
 * Revision 4.2  91/09/19  22:47:22  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: ip.h,v $ $Revision: 4.2.26.1 $ (DEC) $Date: 2005/11/30 21:39:52 $
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
 *	Base:	ip.h	7.8 (Berkeley) 2/20/89
 *	Merged:	ip.h	7.10 (Berkeley) 6/28/90
 */
/*
 *	Revision History:
 *
 *  4-Nov-91	Heather Gray
 *	Include endian.h if BYTE_ORDER not defined
 */
#ifndef		_NETINET_IP_H
#define	_NETINET_IP_H

#include <netinet/in_systm.h>
#include <netinet/in.h>

#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */
#define	IPVERSION	4

/*
 * Structure of an internet header, naked of options.
 *
 * Beware: We now correctly declare ip_len and ip_off to be u_short.
 *
 */
struct ip {
#if	defined(_KERNEL) || defined(_NO_BITFIELDS) || (__STDC__ == 1)
	u_char	ip_vhl;			/* version and header length */
#else
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ip_hl:4,		/* header length */
		ip_v:4;			/* version */
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ip_v:4,			/* version */
		ip_hl:4;		/* header length */
#endif
#endif
	u_char	ip_tos;			/* type of service */
	u_short	ip_len;			/* total length */
	u_short	ip_id;			/* identification */
	u_short	ip_off;			/* fragment offset field */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
	u_char	ip_ttl;			/* time to live */
	u_char	ip_p;			/* protocol */
	u_short	ip_sum;			/* checksum */
	struct	in_addr ip_src,ip_dst;	/* source and dest address */
};

#define	IP_MAXPACKET	65535		/* maximum packet size */

/*
 * Definitions for IP type of service (ip_tos)
 */
#define	IPTOS_LOWDELAY		0x10
#define	IPTOS_THROUGHPUT	0x08
#define	IPTOS_RELIABILITY	0x04

/*
 * Definitions for IP precedence (also in ip_tos) (hopefully unused)
 */
#define	IPTOS_PREC_NETCONTROL		0xe0
#define	IPTOS_PREC_INTERNETCONTROL	0xc0
#define	IPTOS_PREC_CRITIC_ECP		0xa0
#define	IPTOS_PREC_FLASHOVERRIDE	0x80
#define	IPTOS_PREC_FLASH		0x60
#define	IPTOS_PREC_IMMEDIATE		0x40
#define	IPTOS_PREC_PRIORITY		0x20
#define	IPTOS_PREC_ROUTINE		0x10

/*
 * Definitions for options.
 */
#define	IPOPT_COPIED(o)		((o)&0x80)
#define	IPOPT_CLASS(o)		((o)&0x60)
#define	IPOPT_NUMBER(o)		((o)&0x1f)

#define	IPOPT_CONTROL		0x00
#define	IPOPT_RESERVED1		0x20
#define	IPOPT_DEBMEAS		0x40
#define	IPOPT_RESERVED2		0x60

#define	IPOPT_EOL		0		/* end of option list */
#define	IPOPT_NOP		1		/* no operation */

#define	IPOPT_RR		7		/* record packet route */
#define	IPOPT_TS		68		/* timestamp */
#define	IPOPT_SECURITY		130		/* provide s,c,h,tcc */
#define	IPOPT_LSRR		131		/* loose source route */
#if SEC_NET
#define IPOPT_RIPSO_AUX         133             /* RIPSO extended options. */
#define IPOPT_CIPSO             134             /* CIPSO security options. */
#endif
#define	IPOPT_SATID		136		/* satnet id */
#define	IPOPT_SSRR		137		/* strict source route */

/*
 * Offsets to fields in options other than EOL and NOP.
 */
#define	IPOPT_OPTVAL		0		/* option ID */
#define	IPOPT_OLEN		1		/* option length */
#define IPOPT_OFFSET		2		/* offset within option */
#define	IPOPT_MINOFF		4		/* min value of above */

/*
 * Time stamp option structure.
 */
struct	ip_timestamp {
	u_char	ipt_code;		/* IPOPT_TS */
	u_char	ipt_len;		/* size of structure (variable) */
	u_char	ipt_ptr;		/* index of current entry */
#if	defined(_KERNEL) || defined(_NO_BITFIELDS) || (__STDC__ == 1)
	u_char	ipt_oflg;		/* overflow and flags */
#else
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ipt_flg:4,		/* flags, see below */
		ipt_oflw:4;		/* overflow counter */
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ipt_oflw:4,		/* overflow counter */
		ipt_flg:4;		/* flags, see below */
#endif
#endif
	union ipt_timestamp {
		n_long	ipt_time[1];
		struct	ipt_ta {
			struct in_addr ipt_addr;
			n_long ipt_time;
		} ipt_ta[1];
	} ipt_timestamp;
};

/*
 * IPCOMP header structure
 */
struct ipcomp_hdr {
        uint8_t   ipcomp_nxthdr;      /* next header */
        uint8_t   ipcomp_flags;       /* flags */
        u_int16_t ipcomp_cpi;         /* Compression Paremeter Index */
};


/* flag bits for ipt_flg */
#define	IPOPT_TS_TSONLY		0		/* timestamps only */
#define	IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	IPOPT_TS_PRESPEC	3		/* specified modules only */

/* bits for security (not byte swapped) */
#define	IPOPT_SECUR_UNCLASS	0x0000
#define	IPOPT_SECUR_CONFID	0xf135
#define	IPOPT_SECUR_EFTO	0x789a
#define	IPOPT_SECUR_MMMM	0xbc4d
#define	IPOPT_SECUR_RESTR	0xaf13
#define	IPOPT_SECUR_SECRET	0xd788
#define	IPOPT_SECUR_TOPSECRET	0x6bc5

/*
 * Internet implementation parameters.
 */
#define	MAXTTL		255		/* maximum time to live (seconds) */
#define	MINTTL          1               /* minimum time to live (seconds) */
#define	DEFTTL          64              /* default time to live (rfc1700) */

#define	IPFRAGTTL	18		/* time to live for frags (1/2 seconds) */
#define	IPTTLDEC	1		/* subtracted when forwarding */

#define	IP_MSS		576		/* default maximum segment size */
#endif
