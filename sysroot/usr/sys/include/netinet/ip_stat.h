/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: ip_stat.h,v $
 * Revision 1.1.16.1  2008/01/25  04:47:22  Kuthonuzo_Luruo
 * 	Qar 100369: Add tcps_pawsdrops statistic for RFC1323 PAWS.
 *
 * Revision 1.1.14.1  2002/01/29  21:19:14  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 *
 * Revision 1.1.11.2  2001/02/22  20:03:52  Dan_Vuong
 * 	Redo the ipsec stats structure to match the info really available
 * 	in the kernel.
 *
 * Revision 1.1.11.1  2000/10/30  19:52:07  Gary_Grebus
 * 	Merge missing structure for IPsec from cryptozuluos pool.
 *
 * Revision 1.1.2.1  2000/06/06  15:29:51  Gary_Grebus
 * 	Initial checkin into cryptozuluos.
 * 	Add a structure for global IPsec counters.
 * 
 * Revision 1.1.4.6  1999/03/04  21:08:27  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTFCOS_BL3:PTFCOS_BL5 **
 * 		** Ancestor revision:	1.1.2.3 **
 * 		** Merge revision:	1.1.7.3 **
 * 	 	** End **
 * 	[1999/03/04  20:58:07  Tony_Bono]
 *
 * Revision 1.1.4.5  1999/02/28  18:57:46  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.4.3 **
 * 		** Merge revision:	1.1.4.4 **
 * 	 	** End **
 * 	Fixed compile problem with ogated by moving the stat locks
 * 	into the net_globals.h file.
 * 	[1999/02/28  16:13:43  Tony_Bono]
 * 
 * Revision 1.1.4.4  1999/02/26  20:09:31  Tony_Bono
 * 	Increase size of stat counters from int to u_long
 * 	Added other percpu stats.
 * 	Added RCS variables to the file.
 * 	[1999/02/26  20:04:28  Tony_Bono]
 * 
 * Revision 1.1.7.3  1999/02/16  23:50:06  Tony_Bono
 * 	Fixed Missing ";" on spare declarations
 * 	[1999/02/16  23:48:12  Tony_Bono]
 * 
 * Revision 1.1.7.2  1999/01/08  20:45:34  Tony_Bono
 * 	Added some spare fields to the end of the ipstat structure.
 * 	Moved the per cpu tcpstat structure from tcpstat.h and
 * 	some spare fields.
 * 	Added the per cpu udpstat structure and some spare fields
 * 	incase we need additional counts in the future.
 * 	[1999/01/08  19:44:56  Tony_Bono]
 * 
 * Revision 1.1.4.3  1998/07/30  21:48:02  Tony_Bono
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jPTEV6OS_BL4:PTEV6OS_BL6 **
 * 		** Ancestor revision:	1.1.2.2 **
 * 		** Merge revision:	1.1.2.3 **
 * 	 	** End **
 * 	[1998/07/30  21:36:55  Tony_Bono]
 * 
 * Revision 1.1.2.3  1998/06/26  04:11:03  Tony_Bono
 * 	Added comment to warn anyone who wants to add stats to this file
 * 	to change the code in netaddstats of tcp_timer.c
 * 	[1998/06/26  02:34:22  Tony_Bono]
 * 
 * Revision 1.1.4.2  1998/05/14  22:39:46  John_Dustin
 * 	Add additional ipstat code from Steel to new ip_stat.h header file
 * 	[1998/05/14  22:17:21  John_Dustin]
 * 
 * Revision 1.1.2.2  1998/03/31  21:14:57  Tony_Bono
 * 	Created a seperate stat include file to support percpu stat structures.
 * 	[1998/03/31  20:19:30  Tony_Bono]
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: ip_stat.h,v $ $Revision: 1.1.16.1 $ (DEC) $Date: 2008/01/25 04:47:22 $
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
 * @(#)$RCSfile: ip_stat.h,v $ $Revision: 1.1.16.1 $ (DEC) $Date: 2008/01/25 04:47:22 $
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
 *	Base:	ip_var.h	7.6 (Berkeley) 9/20/89
 *	Merged:	ip_var.h	7.7 (Berkeley) 6/28/90
 */

/*
 * 		--------------Warning------------
 * NOTE: The following restrictions apply to any changes in the
 * following stat structures.
 *	o All stat fields in these structures must be
 *	  u_long.
 * 	o The time sinced zeroed field must be the first
 *	  u_long field.
 */
#ifndef	_NETINET_IP_STAT_H
#define	_NETINET_IP_STAT_H

extern unsigned int netaddstattime;
extern int netaddstatinterval;

struct	ipstat {
	time_t	time;			/* current time or zeroed time */
	u_long	ips_total;		/* total packets received */
	u_long	ips_badsum;		/* checksum bad */
	u_long	ips_tooshort;		/* packet too short */
	u_long	ips_toosmall;		/* not enough data */
	u_long	ips_badhlen;		/* ip header length < data size */
	u_long	ips_badlen;		/* ip length < ip header length */
	u_long	ips_fragments;		/* fragments received */
	u_long	ips_fragdropped;	/* frags dropped (dups, out of space) */
	u_long	ips_fragtimeout;	/* fragments timed out */
	u_long	ips_forward;		/* packets forwarded */
	u_long	ips_cantforward;	/* packets rcvd for unreachable dest */
	u_long	ips_redirectsent;	/* packets forwarded on same net */
	u_long	ips_noproto;		/* unknown or unsupported protocol */
	u_long	ips_delivered;		/* packets consumed here */
	u_long	ips_localout;		/* total ip packets generated here */
	u_long	ips_odropped;		/* lost packets due to nobufs, etc. */
	u_long	ips_reassembled;	/* total packets reassembled ok */
	u_long	ips_fragmented;		/* output packets fragmented ok */
	u_long	ips_ofragments;		/* output fragments created */
	u_long	ips_cantfrag;		/* don't fragment flag was set, etc. */
        u_long     ips_accessdeny;	        /* total access filter denials */
        u_long     ips_linklevelbroadcast;	/* link-level broadcast not forwarded */
	/*
	 * The following are ips_odropped "sub codes" so we can have
	 * a better breakdown of these statistics.
	 */
        u_long     ips_onetdown;		/* output network u_longerface down */
        u_long     ips_onetunreach;	/* output network unreachable */
        u_long     ips_ohostunreach;	/* output host unreachable */
        u_long     ips_onobroadcast;	/* output broadcast not allowed */
        u_long     ips_onomulticast;	/* output multicast not allowed */
        u_long     ips_ocantfrag;	/* output can't fragment */
        u_long     ips_onotsupported;	/* output addrfam, proto, op not supp */
        u_long     ips_oioerror;	/* output IO error */
        u_long     ips_onobufs;		/* output no memory or if queue full */
#ifdef __VMS
        u_long     ips_filter_hosts;    /* access list for hosts */
        u_long	   ips_filter_nets;     /* access list for nets */
#endif
};

/*
 * TCP statistics.
 */
struct	tcpstat {
	time_t	time;
	u_long	tcps_connattempt;	/* connections initiated */
	u_long	tcps_accepts;		/* connections accepted */
	u_long	tcps_connects;		/* connections established */
	u_long	tcps_drops;		/* connections dropped */
	u_long	tcps_conndrops;		/* embryonic connections dropped */
	u_long	tcps_closed;		/* conn. closed (includes drops) */
	u_long	tcps_segstimed;		/* segs where we tried to get rtt */
	u_long	tcps_rttupdated;	/* times we succeeded */
	u_long	tcps_delack;		/* delayed acks sent */
	u_long	tcps_timeoutdrop;	/* conn. dropped in rxmt timeout */
	u_long	tcps_rexmttimeo;	/* retransmit timeouts */
	u_long	tcps_persisttimeo;	/* persist timeouts */
	u_long	tcps_keeptimeo;		/* keepalive timeouts */
	u_long	tcps_keepprobe;		/* keepalive probes sent */
	u_long	tcps_keepdrops;		/* connections dropped in keepalive */

	u_long	tcps_sndtotal;		/* total packets sent */
	u_long	tcps_sndpack;		/* data packets sent */
	u_long	tcps_sndbyte;		/* data bytes sent */
	u_long	tcps_sndrexmitpack;	/* data packets retransmitted */
	u_long	tcps_sndrexmitbyte;	/* data bytes retransmitted */
	u_long	tcps_sndacks;		/* ack-only packets sent */
	u_long	tcps_sndprobe;		/* window probes sent */
	u_long	tcps_sndurg;		/* packets sent with URG only */
	u_long	tcps_sndwinup;		/* window update-only packets sent */
	u_long	tcps_sndctrl;		/* control (SYN|FIN|RST) packets sent */

	u_long	tcps_rcvtotal;		/* total packets received */
	u_long	tcps_rcvpack;		/* packets received in sequence */
	u_long	tcps_rcvbyte;		/* bytes received in sequence */
	u_long	tcps_rcvbadsum;		/* packets received with ccksum errs */
	u_long	tcps_rcvbadoff;		/* packets received with bad offset */
	u_long	tcps_rcvshort;		/* packets received too short */
	u_long	tcps_rcvduppack;	/* duplicate-only packets received */
	u_long	tcps_rcvdupbyte;	/* duplicate-only bytes received */
	u_long	tcps_rcvpartduppack;	/* packets with some duplicate data */
	u_long	tcps_rcvpartdupbyte;	/* dup. bytes in part-dup. packets */
	u_long	tcps_rcvoopack;		/* out-of-order packets received */
	u_long	tcps_rcvoobyte;		/* out-of-order bytes received */
	u_long	tcps_rcvpackafterwin;	/* packets with data after window */
	u_long	tcps_rcvbyteafterwin;	/* bytes rcvd after window */
	u_long	tcps_rcvafterclose;	/* packets rcvd after "close" */
	u_long	tcps_rcvwinprobe;	/* rcvd window probe packets */
	u_long	tcps_rcvdupack;		/* rcvd duplicate acks */
	u_long	tcps_rcvacktoomuch;	/* rcvd acks for unsent data */
	u_long	tcps_rcvackpack;	/* rcvd ack packets */
	u_long	tcps_rcvackbyte;	/* bytes acked by rcvd acks */
	u_long	tcps_rcvwinupd;		/* rcvd window update packets */
	u_long	tcps_nooutputbuffs;	/* mget returned enobuffs and we sent a tcpQuench */
	u_long	tcps_skipchecksum;	/* no checksum generated for packet */
	u_long	tcps_pendingconnectiondropped;	/* temporary listen has gone away*/
	u_long	tcp_ignored_tsopt;	/* number of timestamp options seen for connections with
					   timestamps disabled */
	u_long	tcp_processing_tsopt;	/* number of incoming packets with timestamp option seen */
	u_long  tcps_pawsdrops;		/* number of segments dropped by RFC1323 PAWS */
	u_long	tcps_recycled_tps;	/* recycled inps used while processing syn requests */
};

struct	udpstat {
	time_t	time;			/* current time or zeroed time */ 
				/* input statistics: */
	u_long	udps_ipackets;		/* total input packets */
	u_long	udps_hdrops;		/* packet shorter than header */
	u_long	udps_badsum;		/* checksum error */
	u_long	udps_badlen;		/* data length larger than packet */
	u_long	udps_noport;		/* no socket on port */
	u_long	udps_noportbcast;	/* of above, arrived as broadcast */
	u_long	udps_noportmcast;	/* of above, arrived as multicast */
	u_long	udps_fullsock;		/* not delivered, input socket full */
	u_long	udpps_pcbcachemiss;	/* input packets missing pcb cache */
				/* output statistics: */
	u_long	udps_opackets;		/* total output packets */
};


struct igmpstat {
	time_t	time;			/* current time or zeroed time */ 
	u_long	igps_rcv_total;		/* total IGMP messages received    */
	u_long	igps_rcv_tooshort;	/* received with too few bytes     */
	u_long	igps_rcv_badsum;	/* received with bad checksum      */
	u_long	igps_rcv_queries;	/* received membership queries     */
	u_long	igps_rcv_badqueries;	/* received invalid queries        */
	u_long	igps_rcv_reports;	/* received membership reports     */
	u_long	igps_rcv_badreports;	/* received invalid reports        */
	u_long	igps_rcv_ourreports;	/* received reports for our groups */
	u_long	igps_snd_reports;	/* sent membership reports         */
};

/*
 * Variables related to this implementation
 * of the internet control message protocol.
 */
#define ICMPSTAT_MAXTYPE 18

struct	icmpstat {
	time_t	time;
/* statistics related to icmp packets generated */
	u_long	icps_error;		/* # of calls to icmp_error */
	u_long	icps_oldshort;		/* no error 'cuz old ip too short */
	u_long	icps_oldicmp;		/* no error 'cuz old was icmp */
	u_long	icps_outhist[ICMPSTAT_MAXTYPE + 1];
/* statistics related to input messages processed */
 	u_long	icps_badcode;		/* icmp_code out of range */
	u_long	icps_tooshort;		/* packet < ICMP_MINLEN */
	u_long	icps_checksum;		/* bad checksum */
	u_long	icps_badlen;		/* calculated bound mismatch */
	u_long	icps_reflect;		/* number of responses */
	u_long	icps_inhist[ICMPSTAT_MAXTYPE + 1];
};

/*
 * The kernel's multicast routing statistics.
 */
struct mrtstat {
    time_t	time;			/* last time zeroed		   */
    u_long	mrts_mfc_lookups;	/* # forw. cache hash table hits   */
    u_long	mrts_mfc_misses;	/* # forw. cache hash table misses */
    u_long	mrts_upcalls;		/* # calls to mrouted              */
    u_long	mrts_no_route;		/* no route for packet's origin    */
    u_long	mrts_bad_tunnel;	/* malformed tunnel options        */
    u_long	mrts_cant_tunnel;	/* no room for tunnel options      */
    u_long	mrts_wrong_if;		/* arrived on wrong interface	   */
    u_long	mrts_upq_ovflw;		/* upcall Q overflow		   */
    u_long	mrts_cache_cleanups;	/* # entries with no upcalls 	   */
    u_long  	mrts_drop_sel;     	/* pkts dropped selectively        */
    u_long  	mrts_q_overflow;    	/* pkts dropped - Q overflow       */
    u_long  	mrts_pkt2large;     	/* pkts dropped - size > BKT SIZE  */
    u_long	mrts_upq_sockfull;	/* upcalls dropped - socket full   */
};

/*
 * Routing statistics.
 */
struct	rtstat {
	u_long	time;			/* current time or zeroed time */ 
	u_long	rts_badredirect;	/* bogus redirect calls */
	u_long	rts_dynamic;		/* routes created by redirects */
	u_long	rts_newgateway;		/* routes modified by redirects */
	u_long	rts_unreach;		/* lookups which failed */
	u_long	rts_wildcard;		/* lookups satisfied by a wildcard */
};

/*
 * IPsec statistics.
 * This should track the SshEngineStatistics structure in engine_internal.h
 */
struct ipsecstat {
	time_t	time;			/* Current time or zeroed time */
	u_long ipss_num_not_filtered;	/* Packets passed to IPsec engine but
					   not filtered. */
	u_long ipss_num_packets;	/* Packets filtered by IPsec engine */
	u_long ipss_num_ip;		/* IP pkts seen by IPsec engine */
	u_long ipss_num_ah;		/* AH headers processed */
	u_long ipss_num_esp;		/* ESP headers processed */
	u_long ipss_num_ipcomp;		/* IPCOMP headers processed */
	u_long ipss_num_trigger;	/* Pkts triggering IKE action */
	u_long ipss_num_drop;		/* Pkts dropped by IPsec */
	u_long ipss_num_pass;		/* Pkts passed through by IPsec */
	u_long ipss_num_reass_nonfirst;	/* Non-first frags currently being
					 * reassembled */
	u_long ipss_reass_partial;	/* Pkts currently being reassembled */
	u_long ipss_mem_reass_partial;	/* Bytes currently used by reassembly*/
	u_long ipss_num_icmp_send;	/* Number of ICMP packets generated */
	u_long ipss_spares[20];		/* Leave lots of space for future
					   enhancements. */
};

/*
 * define the per cpu stat struct for the inet proto stack.
 * some fields are not currently used. 
 */
struct inetstats {
	struct ipstat	ipstat;
	u_long	spares_a[10];
	struct tcpstat	tcpstat;
	u_long	spares_b[10];
	struct udpstat	udpstat;
	u_long	spares_c[10];
	struct igmpstat igmpstat;		  /* Not Used */
	u_long	spares_d[10];
	struct icmpstat	icmpstat;
	u_long	spares_e[10];
	struct mrtstat	mrtstat;
	u_long	spares_f[10];
	struct rtstat	rtstat;			  /* Not Used */
	u_long	spares_g[10];
};

#endif
