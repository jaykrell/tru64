/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: tcp_var.h,v $
 * Revision 4.2.96.3  2008/01/25  05:11:56  Kuthonuzo_Luruo
 * 	Qar 100369: Corrects multiple issues with RFC1323 TCP timestamps
 *      & PAWS implementation.
 *        - Add t_TSRecent_age to tcpcb.
 *        - Add define for TF2_DUPSEG.
 *
 * Revision 4.2.96.2  2004/12/16  01:12:32  Roger_Spinney
 * 	Added TF2_LOCAL define. CH_G09110 Fix by Tony Bono.
 *
 * Revision 4.2.96.1  2003/06/10  22:03:41  Tony_Bono
 * 	Made changes to support route rate limiting to fix performance
 * 	problem seen at rogers@home (CLD CR2W5100C QAR 94040).
 * 	defined the new TF2_DELAY_SEND flag used by tcp_output and the
 * 	fasttimo routine to limit the outgoing data rate.
 *
 * Revision 4.2.92.4  2002/05/31  16:19:08  Tony_Bono
 * 	Expanded Sack handling code to corrected excessive rexmits
 * 	when handling sack packets.
 *
 * Revision 4.2.92.3  2002/01/31  19:44:38  John_Dustin
 * 	Increased t_flags from u_char to u_short to allow room for
 * 	more flag bits.  Fixed the tcpcb structure padding to
 * 	accurately reflect the cache alignment (no holes).
 *
 * Revision 4.2.92.2  2002/01/29  21:19:38  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 4.2.92.1  2002/01/17  22:23:00  John_Dustin
 * 	Merged Revision 4.2.82.2 from v51asupportos.bl1, SACK fixes
 * 	and RFC1948 random TCP sequence number support.
 *
 * Revision 4.2.82.2  2002/01/07  14:51:03  Renata_Dedek
 * 	Expanded sack processing to handle out of order sack blocks.
 * 	Add support for rfc1948 by adding per hashbucket tcp sequence
 * 	numbers to protect in an attempt to minimize host masquerading.
 * 
 * Revision 4.2.82.1  2001/09/25  21:48:06  Tony_Bono
 * 	Made changes to support the rexmit modification
 * 	for ics interconnect flags
 *
 * Revision 4.2.74.2  2001/03/09  22:14:39  Tony_Bono
 * 	Reduced the temporary structure members needed to
 * 	support the tcp_ics_keepalive_panic_count by adding
 * 	the TF2_KEEP_PANIC flags to t_flags2 also changed the
 * 	logic for determining a panic event.
 *
 * Revision 4.2.74.1  2000/10/24  23:54:20  Ernie_Petrides
 * 	Merge v51supportos-47-bono from Zulu PK2 revision 4.2.72.1.
 *
 * Revision 4.2.72.1  2000/09/22  20:20:39  Tony_Bono
 * 	Added declaration of tcp_free_delay fpr use in tcp_input.
 * 
 * Revision 4.2.68.10  2000/06/23  22:42:51  Tony_Bono
 * 	Change to more efficient enqueue and dequeue of the
 * 	fast and slowtimo lists by usnig the atomic bit operations.
 * 
 * Revision 4.2.68.9  2000/04/26  17:54:53  Tony_Bono
 * 	Change to reduce the length of time an inp is on the
 * 	slowtimo_next list after close.
 * 
 * Revision 4.2.68.8  2000/03/24  23:17:47  Tony_Bono
 * 	Changes to reduce lock contention by delaying dequeue
 * 	of inp from the fast and slow lists.
 * 
 * Revision 4.2.68.7  2000/03/17  15:13:47  Brian_Haley
 * 	NUMA replication work - ipqshiftbits, tcp_skip_local_cwnd,
 * 	tcp_cwnd_segments, tcp_compat_42, tcp_urgent_42, tcbqNum,
 * 	tcbhashmod, tcbhashsize, tcp_keepalive_default
 * 
 * Revision 4.2.68.6  2000/02/22  20:53:32  Brian_Haley
 * 	Increased TCP_SEND/RECVSPACE defaults to 60*1024 (61440) (qar 62659).
 * 
 * Revision 4.2.68.5  2000/01/26  22:29:45  John_Dustin
 * 	Add #if NETSYNC_LOCK, #if NETISR_THREAD for OPENVMS portability
 * 
 * Revision 4.2.68.3  1999/12/17  03:16:58  Tony_Bono
 * 	Added per rad fast and slow timer support.
 * 
 * Revision 4.2.68.2  1999/12/07  23:21:23  Tony_Bono
 * 	Added the SIGNAL_TCPSLOWTIMO macro to support the fasttimo
 * 	changes.
 * 	Addition of per rad tcbinit structs.
 * 
 * Revision 4.2.68.1  1999/11/19  20:31:12  Tony_Bono
 * 	merge from zinc bl2
 * 
 * Revision 4.2.66.1  1999/09/17  22:10:49  Tony_Bono
 * 	Added the SIGNAL_TCPFASTTIMO macro to support the fasttimo
 * 	changes.
 * 
 * Revision 4.2.27.14  1999/04/15  17:43:21  John_Dustin
 * 	add dropped padding before t_startrtt for 64-byte alignment
 * 	[1999/04/14  19:11:57  John_Dustin]
 * 
 * Revision 4.2.27.13  1999/03/30  23:47:16  Tony_Bono
 * 	Cache alignment changes.
 * 	[1999/03/30  23:37:43  Tony_Bono]
 * 
 * Revision 4.2.27.12  1999/02/26  20:09:37  Tony_Bono
 * 	Moved the declaration of the tcpstat struct into ip_stat.h.
 * 	[1999/02/26  20:04:40  Tony_Bono]
 * 
 * Revision 4.2.27.11  1999/01/20  19:08:00  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL8:PTFCOS_BL3 **
 * 		** Ancestor revision:	4.2.48.3 **
 * 		** Merge revision:	4.2.54.3 **
 * 	 	** End **
 * 	[1999/01/20  19:06:00  Tony_Bono]
 * 
 * Revision 4.2.27.10  1998/12/02  23:10:53  Jack_McCann
 * 	IPv6 hooks:
 * 	- replace 'struct ovtcpiphdr' with 'struct ovtcphdr'
 * 	- remove 'struct tcpiphdr t_template' field from tcpcb
 * 	[1998/11/21  02:33:10  Jack_McCann]
 * 
 * Revision 4.2.54.3  1998/11/02  21:24:15  Tony_Bono
 * 	Increased _TCBHASHSIZE from 32 to 512.
 * 	[1998/10/30  16:22:44  Tony_Bono]
 * 
 * Revision 4.2.54.2  1998/10/01  19:27:16  Tony_Bono
 * 	Added addtional stat to track all time hiwat for a
 * 	tcbhashbucket. This is necessary for scalling and
 * 	performance tuning.
 * 	[1998/10/01  19:16:35  Tony_Bono]
 * 
 * Revision 4.2.27.9  1998/07/30  21:48:13  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	4.2.48.2 **
 * 		** Merge revision:	4.2.48.3 **
 * 	 	** End **
 * 	[1998/07/30  21:37:21  Tony_Bono]
 * 
 * Revision 4.2.48.3  1998/06/26  04:11:50  Tony_Bono
 * 	Cleaned up and rearranged some code as a result of
 * 	Jack's review.
 * 	[1998/06/26  02:36:29  Tony_Bono]
 * 
 * Revision 4.2.27.8  1998/05/14  22:39:56  John_Dustin
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 		** Ancestor revision:	4.2.36.5 **
 * 		** Merge revision:	4.2.48.2 **
 * 	 	** End **
 * 	[1998/05/14  22:17:45  John_Dustin]
 * 
 * Revision 4.2.48.2  1998/03/31  21:15:39  Tony_Bono
 * 	Moved stat struct definition to tcp_stat.h. This is
 * 	necessary to support percpu stats.
 * 	Added timestamp option fields and flags.
 * 	[1998/03/31  20:20:52  Tony_Bono]
 * 
 * Revision 4.2.27.7  1997/10/23  21:14:54  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL10:PTCOS_BL11 **
 * 		** Ancestor revision:	4.2.36.4 **
 * 		** Merge revision:	4.2.36.5 **
 * 	 	** End **
 * 	[1997/10/23  20:56:06  Tony_Bono]
 * 
 * Revision 4.2.36.5  1997/08/29  19:31:23  Tony_Bono
 * 	did merge from V40SUPPORTOS_BL6 to PTCOS_NIGHTLY
 * 	[1997/08/29  19:23:34  Tony_Bono]
 * 
 * Revision 4.2.27.6  1997/07/24  14:48:37  Larry_Cohen
 * 	add definitions required for cluster alias tcp sequence number hooks.
 * 	[1997/07/24  14:22:21  Larry_Cohen]
 * 
 * Revision 4.2.42.2  1997/04/25  19:32:27  Benjamin_Dibble
 * 	Changes for MONDO2+
 * 	Added tcp_keepalive_default for systems which need dead
 * 	connections to close on thier own. Spec 1122 says this
 * 	is not allowed so the default is off.
 * 	Fix to allow reliable links to use tcp with no checksum.
 * 	Hint code support.
 * 	[1997/04/24  19:21:20  Benjamin_Dibble]
 * 
 * Revision 4.2.27.5  1997/04/24  18:27:08  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTCOS_BL3:PTCOS_BL6 **
 * 		** Ancestor revision:	4.2.36.2 **
 * 		** Merge revision:	4.2.36.4 **
 * 	 	** End **
 * 	merge
 * 	[1997/04/24  18:08:53  Tony_Bono]
 * 
 * Revision 4.2.36.4  1997/04/07  22:11:32  Tony_Bono
 * 	added tcp_keepalive_default for systems which need dead
 * 	connections to close on thier own. spec 1122 says this
 * 	is not allowed so the default is off
 * 	[1997/04/04  22:45:40  Tony_Bono]
 * 
 * Revision 4.2.27.4  1997/02/06  02:47:06  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTBOS_BL4:PTCOS_BL3 **
 * 		** Ancestor revision:	4.2.10.7 **
 * 		** Merge revision:	4.2.36.2 **
 * 	 	** End **
 * 	merge of PTC BL3 changes
 * 	[1997/02/06  02:31:39  Tony_Bono]
 * 
 * Revision 4.2.36.3  1997/01/24  02:00:23  Tony_Bono
 * 	fix to allow reliable links to use tcp with no checksum
 * 	[1997/01/24  01:48:36  Tony_Bono]
 * 
 * Revision 4.2.36.2  1996/11/22  22:11:16  Tony_Bono
 * 	hint code support
 * 	[1996/11/22  22:02:36  Tony_Bono]
 * 
 * Revision 4.2.27.3  1996/11/19  21:47:54  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	4.2.27.2 **
 * 		** Merge revision:	4.2.27.2 **
 * 	 	** End **
 * 	rework of tcbhashstats
 * 	[1996/11/18  19:49:12  Tony_Bono]
 * 	final pass of web server package including hint,
 * 	 quick bind and tcp syn queue changes
 * 	[1996/11/14  16:44:29  Tony_Bono]
 * 	 	** Merge Information **
 * 		** Command used:	bmerge **
 * 		** Ancestor revision:	4.2.10.7 **
 * 		** Merge revision:	4.2.27.2 **
 * 	 	** End **
 * 	merge into steel
 * 	[1996/08/02  06:02:09  Tony_Bono]
 * 	Added changes suggested in code review
 * 	[1996/07/27  00:56:57  Tony_Bono]
 * 	tcp timer changes for large web servers
 * 	[1996/05/31  20:44:36  Tony_Bono]
 * 
 * Revision 4.2.33.2  1996/10/10  18:14:53  Tony_Bono
 * 	hint patch initial rev 10-10-96
 * 
 * Revision 4.2.27.2  1996/05/03  18:27:31  Tony_Bono
 * 	Bravo to Steel merge
 * 	[1996/05/03  15:51:28  Tony_Bono]
 * 
 * Revision 4.2.15.4  1996/03/10  15:36:50  Ray_Lanza
 * 	merge of Platinum BL8 to BL11 pass 1 changes
 * 	[1996/03/10  15:13:52  Ray_Lanza]
 * 
 * Revision 4.2.10.7  1996/02/08  22:05:47  Tony_Bono
 * 	added a per socket version of tcpnodelack
 * 	[1996/02/07  21:52:58  Tony_Bono]
 * 
 * Revision 4.2.10.6  1995/12/15  18:10:20  Jack_McCann
 * 	Add TCP_SENDSPACE, TCP_RECVSPACE, TCPREXMTTHRESH.
 * 	Move t_persistcntr field to bottom of tcpcb.
 * 	Per-socket keepalive support (add t_keepidle, t_keepintvl, t_keepcnt,
 * 	t_keepinit).
 * 	Add t_flags2 field to support more flags.
 * 	Add TF2_PUSH for NFS.
 * 	[1995/12/12  19:43:01  Jack_McCann]
 * 
 * Revision 4.2.15.3  1995/11/10  23:42:59  Ray_Lanza
 * 	Merge of PTOS BL8
 * 	[1995/11/10  23:24:37  Ray_Lanza]
 * 
 * Revision 4.2.15.2  1995/10/25  19:58:30  Ray_Lanza
 * 	Initial __alpha conditional evaluation and changes
 * 	[1995/10/25  19:28:26  Ray_Lanza]
 * 
 * Revision 4.2.10.5  1995/09/25  19:49:24  Jack_McCann
 * 	pcb hash lookup support (qar 34848):
 * 	- add extern declarations for tcbinit, tcbhashtab, tcbhashmod
 * 	[1995/09/25  16:09:26  Jack_McCann]
 * 
 * Revision 4.2.10.4  1995/08/07  19:10:41  Tony_Bono
 * 	Modified persistence timer to abort connection if no response
 * 	[1995/08/01  17:07:05  Tony_Bono]
 * 
 * Revision 4.2.10.3  1995/04/28  16:45:50  Jack_McCann
 * 	Path MTU Discovery - add t_peermss
 * 	[1995/04/26  22:37:22  Jack_McCann]
 * 
 * Revision 4.2.10.2  1995/04/14  21:23:04  John_Dustin
 * 	added DART hooks (TF_UIOMOVED flag)
 * 	[1995/04/14  19:05:55  John_Dustin]
 * 
 * Revision 4.2.7.6  1994/04/25  18:36:49  Jack_McCann
 * 	Move t_sockoptmss field and change its name to t_msslimit.
 * 	[1994/04/22  20:10:01  Jack_McCann]
 * 	Add t_sockoptmss field to tcpcb.
 * 	[1994/04/21  18:23:55  Jack_McCann]
 * 
 * Revision 4.2.7.5  1994/03/01  23:34:29  Geraldine_Harter
 * 	TCP reassembly changes
 * 	[1994/02/24  13:48:19  Geraldine_Harter]
 * 
 * Revision 4.2.7.4  1993/11/15  23:50:35  John_Dustin
 * 	add lockinfo support for misc_tcp_li
 * 	[1993/10/27  19:17:20  John_Dustin]
 * 
 * Revision 4.2.7.3  1993/10/07  17:54:47  John_Dustin
 * 	sterling to gold merge
 * 	[1993/10/04  18:50:55  John_Dustin]
 * 
 * Revision 4.2.7.2  1993/08/03  16:35:40  Ajay_Kachrani
 * 	Convert n/w locks to new lock stats using LI
 * 	[1993/07/22  19:37:47  Ajay_Kachrani]
 * 
 * Revision 4.2.2.7  1993/01/06  15:19:16  Heather_Gray
 * 	Add extern for new urgent pointer var.
 * 	[92/12/23  14:22:10  Heather_Gray]
 * 
 * Revision 4.2.2.6  92/12/09  17:51:49  Ajay_Kachrani
 * 	Add support for repeting R2 timer in tcbcb
 * 	[92/12/03  15:38:47  Ajay_Kachrani]
 * 
 * Revision 4.2.2.5  92/11/06  16:52:18  Heather_Gray
 * 	Add support for window scale option (RFC 1323). Per skibo@cs.uiuc.edu
 * 
 * Revision 4.2.2.4  92/04/07  12:14:51  Geraldine_Harter
 * 	Common pool merge fixes, so sources will work correctly on MIPS
 * 	[92/04/07  12:12:00  Geraldine_Harter]
 * 
 * Revision 4.2.2.3  92/01/26  20:57:30  Tim_Hoskins
 * 	Alpha support for TCP segment reassembly.
 * 	[92/01/26  20:54:52  Tim_Hoskins]
 * 
 * Revision 4.2.2.2  92/01/20  13:24:09  Tim_Hoskins
 * 	Alpha 64-bit network support.
 * 	[92/01/20  13:02:30  Tim_Hoskins]
 * 
 * Revision 4.2  91/09/19  22:48:33  devbld
 * 	Adding ODE Headers
 * 
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: tcp_var.h,v $ $Revision: 4.2.96.3 $ (DEC) $Date: 2008/01/25 05:11:56 $
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
 *	Base:	tcp_var.h	7.8 (Berkeley) 6/29/88
 *	Merged:	tcp_var.h	7.10 (Berkeley) 6/28/90
 */

#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_
/*
 * Kernel variables for tcp.
 */

/*
 * Tcp control block, one per tcp; fields:
 */

struct tcpcb {
#ifdef __arch64__
	struct	ovtcphdr *seg_next;	/* sequencing queue */
	struct	ovtcphdr *seg_prev;
#else  /* not __arch64__ */
	struct	tcpiphdr *seg_next;	/* sequencing queue */
	struct	tcpiphdr *seg_prev;
#endif /* __arch64__ */
	short	t_dupacks;		/* consecutive dup acks recd */
	short	t_softerror;		/* possible error not yet reported */
	short	t_rxtshift;		/* log(2) of rexmt exp. backoff */
	short	t_rxtcur;		/* current retransmit value */
	u_short	t_flags;
#define	TF_ACKNOW	0x01		/* ack peer immediately */
#define	TF_DELACK	0x02		/* ack, but try to delay it */
#define	TF_NODELAY	0x04		/* don't delay packets to coalesce */
#define	TF_NOOPT	0x08		/* don't use tcp options */
#define	TF_SENTFIN	0x10		/* have sent FIN */
#define TF_REQ_SCALE    0x0020		/* have/will request window scaling */
#define TF_RCVD_SCALE   0x0040		/* other side has requested scaling */
#define TF_UIOMOVED     0x0080		/* UIOMOVE mbufs in use (DART) */
	u_short t_flags2;		/* more flags */
#define TF2_PUSH	0x0001		/* set push for outbound data packets */
#define TF2_NODELACK	0x0002		/* set no delayed ack for incoming packets*/
#define TF2_TSOPTENA	0x0004		/* enable (rfc1323)request of timestamp option */
#define TF2_TSOPT	0x0008		/* connection is running with timestamp enabled */
#define TF2_PAWS	0x0010		/* enable (rfc1323)PAWS option */
#define TF2_CLUA_ALIAS  0x0020		/* this is a cluster alias connection */
#define TF2_CLUA_CNXQ   0x0040		/* a cluster alias connection is queued for registration */
#define TF2_CLUA_CNXR   0x0080		/* a cluster alias connection is registered */
#define TF2_SACKENA	0x0100		/* enable PAWS option(rfc1323) */
#define TF2_SACK	0x0200		/* enable SACK option(rfc2018) */
#define TF2_KEEP_PANIC	0x0400		/* when tcp_keep_panic flag set will
					   panic when keep_cnt exceeded */
#define TF2_DELAY_RXMT	0x0800		/* used to delay rexmit timeout for ics channel */
#define TF2_DELAY_SEND  0x1000		/* delay send till next interval. */
#define TF2_LOCAL	0x2000		/* remote is local host used when tcp_skip_local_cwnd */
#define TF2_DUPSEG      0x4000          /* a duplicate segment entirely to the left of rcv_nxt */

#define TF2_INHERIT	(TF2_PAWS|TF2_TSOPTENA|TF2_SACKENA)
#ifndef  __VMS
	int pad_a[9];
#else /* __VMS */
	int pad_a[11];
#endif /* __VMS */
/* 64-byte alignment */
	struct	inpcb *t_inpcb;		/* back pointer to internet pcb */
	unsigned int t_lastaction;	/* start of inactivity period */
	tcp_seq	snd_wnd;		/* send window */
	tcp_seq	snd_cwnd;		/* congestion-controlled window */
	tcp_seq	snd_max;		/* highest sequence number sent */
	tcp_seq	snd_una;		/* send unacknowledged */
	tcp_seq	snd_nxt;		/* send next */
	tcp_seq	snd_up;			/* send urgent pointer */
	tcp_seq	snd_wl1;		/* window update seg seq number */
	tcp_seq	snd_wl2;		/* window update seg ack number */
	tcp_seq	iss;			/* initial send sequence number */
	tcp_seq	max_sndwnd;		/* largest window peer has offered */
	tcp_seq snd_ssthresh;		/* snd_cwnd size threshhold */
	u_char  snd_scale;		/* window scaling for send window */
	u_char  request_r_scale;	/* pending window scaling */
	u_char  requested_s_scale;
	char pad_b[1];
#ifndef  __VMS
	int pad_c[1];
#else /* __VMS */
	int pad_c[2];
#endif /* __VMS */
/* 64-byte alignment */
	struct tcp_sack_field *t_sack;	/* pointer to last sack field received */
	tcp_seq	rcv_wnd;		/* receive window */
	tcp_seq	rcv_adv;		/* advertised window */
	tcp_seq	rcv_nxt;		/* receive next */
	tcp_seq	rcv_up;			/* receive urgent pointer */
	tcp_seq max_rcvd;		/* most peer has sent into window */
	tcp_seq	irs;			/* initial receive sequence number */
	u_short	t_maxseg;		/* maximum segment size */
	u_char  rcv_scale;		/* window scaling for recv window */
	char pad_i[1];
  	unsigned int t_TSRecent ;	/* timestamp of most recent rcvd packet */
	unsigned int t_TSRecent_age;	/* prevents discard of valid packets when tstamp wraps */
  	unsigned int t_TSEcr ;		/* peers timestamp sent as the TSEcr field of tsopt */
	tcp_seq	 Last_ACK_sent;		/* last ack to determine if the window moves when updating t_TSEcr */
#ifndef  __VMS
	int pad_d[3];
#else /* __VMS */
	int pad_d[4];
#endif /* __VMS */
/* 64-byte alignment */
	tcp_seq	t_rtseq;		/* sequence number being timed */
	short	t_srtt;			/* smoothed round-trip time */
	short	t_rttvar;		/* variance in round-trip time */
	u_short	t_rttmin;		/* minimum rtt allowed */
	u_short	t_msslimit;		/* user-specified max segment size */
	int	t_rptr2rxt;		/* Repeat counter for R2 RXT timer */
	int	t_rptr2cur;		/* Current repeat counter for R2 timer */
	char	t_oobflags;		/* have out-of-band data */
	char	t_iobc;			/* input out-of-band character */
#define	TCPOOB_HAVEDATA	0x01
#define	TCPOOB_HADDATA	0x02
	char	t_force;		/* 1 if forcing out a byte */
	char pad_e[1];
	u_short	t_peermss;		/* max segment size offered by peer */
	short	t_persistcntr;		/* persist timeout for aborting */
	short	t_keepidle;		/* idle time before keepalive probe */
	short	t_keepintvl;		/* interval between keepalive probes */
	short	t_keepcnt;		/* number of keepalive probes */
	short	t_keepinit;		/* initial connect timeout */
	short	t_state;		/* state of this connection */
	short pad_f[1];
#ifndef  __VMS
	long pad_g[3];
#else /* __VMS */
	long pad_g[6];
#endif /* __VMS */
/* 64-byte alignment */
	unsigned int t_startrtt;	/* starting round trip time */
	tcp_seq	t_timestamp;		/* used by slowtimo */
	unsigned int t_timer[TCPT_NTIMERS];	/* tcp timers */
	int	clua_seq_wrap_guard;	/* cluster alias sequence wrap guard */
	int pad_h[1];
};

#define MAX_SACK_ENTRIES 32
/*
 * the tcp_sack_field is used to save a sack update
 * recieved as an option in incoming packet once
 * tcp_outputs the missing packet then the number
 * of entries is set to 0
 */
struct tcp_sack_field {
	short number;		/* the number of entries in this sack update */
	short sack_index;
	struct tcp_sack_entry {
		int ledge ;	/* Left edge of the segment */
		int redge ;	/* right edge of the segment */
	} entries[MAX_SACK_ENTRIES] ;
} ;

#define	intotcpcb(ip)	((struct tcpcb *)(ip)->inp_ppcb)
#define	sototcpcb(so)	(intotcpcb(sotoinpcb(so)))

/*
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define	TCP_RTT_SCALE		8	/* multiplier for srtt; 3 bits frac. */
#define	TCP_RTT_SHIFT		3	/* shift for srtt; 3 bits frac. */
#define	TCP_RTTVAR_SCALE	4	/* multiplier for rttvar; 2 bits */
#define	TCP_RTTVAR_SHIFT	2	/* multiplier for rttvar; 2 bits */

/*
 * The initial retransmission should happen at rtt + 4 * rttvar.
 * Because of the way we do the smoothing, srtt and rttvar
 * will each average +1/2 tick of bias.  When we compute
 * the retransmit timer, we want 1/2 tick of rounding and
 * 1 extra tick because of +-1/2 tick uncertainty in the
 * firing of the timer.  The bias will give us exactly the
 * 1.5 tick we need.  But, because the bias is
 * statistical, we have to test that we don't drop below
 * the minimum feasible timer (which is 2 ticks).
 * This macro assumes that the value of TCP_RTTVAR_SCALE
 * is the same as the multiplier for rttvar.
 */
#define	TCP_REXMTVAL(tp) \
	(((tp)->t_srtt >> TCP_RTT_SHIFT) + (tp)->t_rttvar)

#ifdef __arch64__
#define REASS_MBUF(ov) (*(struct mbuf **)&((struct ovtcphdr *)(ov))->ti_rmb)
#else
#define REASS_MBUF(ti) (*(struct mbuf **)&((ti)->ti_t))
#endif /* __arch64__ */

#include <netinet/ip_stat.h>

#define _TCBHASHSIZE	512		/* default value for tcbhashsize */
#define TCP_SENDSPACE	60*1024		/* default value for tcp_sendspace */
#define TCP_RECVSPACE	60*1024		/* default value for tcp_recvspace */
#define TCPREXMTTHRESH	3		/* default retransmit threshold */

#ifdef _KERNEL

#ifndef REPLICATED
#define REPLICATED
#endif

#if	NETSYNC_LOCK
extern	simple_lock_data_t	misc_tcp_lock;
#define TCPMISC_LOCKINIT()	simple_lock_setup(&misc_tcp_lock, misc_tcp_li)
#define TCPMISC_LOCK()		simple_lock(&misc_tcp_lock)
#define TCPMISC_UNLOCK()	simple_unlock(&misc_tcp_lock)
#else	/* !NETSYNC_LOCK */
#define TCPMISC_LOCKINIT()
#define TCPMISC_LOCK()
#define TCPMISC_UNLOCK()
#endif

#define TCBMAXQUEUES 64
extern	REPLICATED int ipqshiftbits;
#define TCBQINDEX(addr) ((((addr)>>ipqshiftbits)&0xff) % tcbqNum)
extern	REPLICATED int tcp_skip_local_cwnd;
extern	REPLICATED int tcp_cwnd_segments;
extern	REPLICATED int tcp_compat_42;
extern	REPLICATED int tcp_urgent_42;
extern	REPLICATED int tcp_sack_enabled;
extern	REPLICATED int tcp_tsopt_enabled;
extern	REPLICATED int tcp_paws_enabled;

extern	REPLICATED int tcbqNum;
extern	struct	inpcb tcb[];		/* head of queue of active tcpcb's */
extern	struct	tcpstat tcpstat;	/* tcp statistics */
extern	struct	inpcb tcbinit;		/* listeners and some not-yet-connected pcbs */
extern	struct	__inpcb_hashbucket *tcbhashtab; /* connected pcbs */
extern	void * REPLICATED replicated_tcbhbiss;
#define	tcbhbiss ((tcp_seq*)replicated_tcbhbiss)/* modifier for iss on a per hb basis */
extern	REPLICATED int tcbhashmod;	/* buckets in tcbhashtab */
extern	REPLICATED int tcbhashsize;	/* initial value for tcbhashmod */
extern	int tcbquickbindtab[] ;
extern struct tcb_hash_stats_struct {
	int     ChainHiwatCount ;
	int     ChainHiwatThreshold ;
	int     EmptyWarnCount ;
	int     EmptyWarnThreshold ;
	int     FastActive ;
	int     FastIdle ;
	int     SlowActive ;
	int 	AllTimeSlowActive ;
	int     SlowIdle ;
	int     ChainHiwat ;
	int 	AllTimeChainHiwat ;
	int     ChainLowat ;
	int     EmptyBuckets ;
	int     TotalBuckets ;
	int     TotalTcpConns ;
	int     AllTimeMaxTcpConns ;
} tcbhashstats ;

extern struct	__inpcb_hashbucket *HashHiwatBucket ;
extern struct	__inpcb_hashbucket *HashLowatBucket ;

#define FAILSAFEHASHTABLE	32
extern int total_tcp_inpcbs;
extern REPLICATED int tcp_keepalive_default;	/* used to make keep alive the default mod */
extern REPLICATED int tcp_free_delay;		/* delay in slowtimo ticks to free tcp inps */

struct tcpquantumentry {
	int quantum;
	int index;
	struct inpcb *inp;
};
/*
 * contains control information needed for each rad in system.
 */
extern struct tcpradcontrol {
	struct tcpradcontrol	   *trc_next;
	struct   __inpcb_hashbucket trc_tcbinit;
	unsigned int		   *trc_tcbquicklistentab;
	int			    trc_fastserver;
#if	NETSYNC_LOCK
	simple_lock_data_t 	    trc_fastlock;
#endif
	struct inpcb		   *trc_fasttimo_next;
#if	NETISR_THREAD
	thread_t		    trc_fastthread;
#endif
	int			    trc_slowserver;
#if	NETSYNC_LOCK
	simple_lock_data_t 	    trc_slowlock;
#endif
	struct inpcb		   *trc_slowtimo_next;
#if	NETISR_THREAD
	thread_t		    trc_slowthread;
#endif
	struct tcpquantumentry	   *trc_tcpslowquantum;
	int			    trc_maxperiod;
#if	NETISR_THREAD
	wait_queue_data_t	    trc_fast_wait;
	wait_queue_data_t	    trc_slow_wait;
#endif
	struct inpcb		   *trc_fast_active;
	struct inpcb		   *trc_slow_active;
	int			    trc_lperiod;
} *tcpradcontrollist ;

#define TCPRADCONTROL ((struct tcpradcontrol*)current_rad()->tcpradcontrol)
#define RAD2TCPRADCONTROL(__rad) ((struct tcpradcontrol*)((__rad)->tcpradcontrol))
#define RADID2TCPRADCONTROL(__radid) ((struct tcpradcontrol*)(rad_id_to_rad(__radid)->tcpradcontrol))
/* Enqueue the inp onto the fasttimo list.  The atomic test and set
 * allows the timer thread and the signalling thread to coordinate
 * the enqueue and the dequeue of the inp on the worklist.  The
 * simple lock is used to protect the integrity of the list */
#define SIGNAL_TCPFASTTIMO(_tp, _inp) \
(_tp)->t_flags |= TF_DELACK; \
if(test_and_set_l(1,&(_inp)->inp_slowref)) { \
	simple_lock(&RAD2TCPRADCONTROL(_inp->inp_rad)->trc_fastlock); \
	if((_inp)->inp_fasttimo_next == NULL) { \
		(_inp)->inp_fasttimo_next = RAD2TCPRADCONTROL(_inp->inp_rad)->trc_fasttimo_next; \
		INPCBRC_REF((_inp)); \
		RAD2TCPRADCONTROL(_inp->inp_rad)->trc_fasttimo_next = (_inp); \
	} \
	simple_unlock(&RAD2TCPRADCONTROL(_inp->inp_rad)->trc_fastlock); \
}

/* Enqueue the inp onto the slowtimo list.  The atomic test and set
 * allows the timer thread and the signalling thread to coordinate
 * the enqueue and the dequeue of the inp on the worklist.  The
 * simple lock is used to protect the integrity of the list */
#define SIGNAL_TCPSLOWTIMO(_tp, _inp) \
if(test_and_set_l(0,&_inp->inp_slowref)) {\
	simple_lock(&RAD2TCPRADCONTROL(_inp->inp_rad)->trc_slowlock); \
	_inp->inp_slowtimo_next = RAD2TCPRADCONTROL(_inp->inp_rad)->trc_slowtimo_next; \
	RAD2TCPRADCONTROL(_inp->inp_rad)->trc_slowtimo_next = _inp; \
	INPCBRC_REF(_inp); \
	simple_unlock(&RAD2TCPRADCONTROL(_inp->inp_rad)->trc_slowlock); \
}

#endif /* _KERNEL */
#endif /* _TCP_VAR_H_*/
