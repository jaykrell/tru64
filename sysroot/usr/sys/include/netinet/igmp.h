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
 *	@(#)$RCSfile: igmp.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1995/06/15 20:29:01 $
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
 * Internet Group Management Protocol (IGMP) definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 3.5
 */

#ifndef _IGMP_H_
#define _IGMP_H_
/*
 * IGMP packet format.
 */
struct igmp {
	u_char		igmp_type;	/* version & type of IGMP message  */
	u_char		igmp_code;	/* code for routing sub-msgs       */
	u_short		igmp_cksum;	/* IP-style checksum               */
	struct in_addr	igmp_group;	/* group address being reported    */
};					/*  (zero for queries)             */

#define IGMP_MINLEN		     8

/*
 * Message types, including version number.
 */
#define IGMP_HOST_MEMBERSHIP_QUERY   0x11      /* Host membership query    */
#define IGMP_HOST_MEMBERSHIP_REPORT  0x12      /* Old membership report    */
#define IGMP_DVMRP                   0x13      /* DVMRP routing message    */
#define IGMP_PIM                     0x14      /* PIM routing message      */

#define IGMP_HOST_NEW_MEMBERSHIP_REPORT 0x16   /* New membership report    */

#define IGMP_HOST_LEAVE_MESSAGE      0x17      /* Leave-group message      */

#define IGMP_MTRACE_RESP             0x1e /* traceroute resp. (to sender)  */
#define IGMP_MTRACE                  0x1f /* mcast traceroute messages     */

#define IGMP_MAX_HOST_REPORT_DELAY   10   /* max delay for response to     */
                                          /*  query (in seconds)           */


#define IGMP_TIMER_SCALE     10    /* denotes that the igmp->timer filed */
                                   /* specifies time in 10th of seconds  */

/*
 * States for the IGMPv2 state table
 */
#define IGMP_DELAYING_MEMBER                     1
#define IGMP_IDLE_MEMBER                         2
#define IGMP_LAZY_MEMBER                         3
#define IGMP_SLEEPING_MEMBER                     4
#define IGMP_AWAKENING_MEMBER                    5

/*
 * We must remember whether the querier is an old or a new router.
 */
#define IGMP_OLD_ROUTER                          0
#define IGMP_NEW_ROUTER                          1

/*
 * Revert to new router if we haven't heard from an old router in
 * this amount of time.
 */
#define IGMP_AGE_THRESHOLD                       540

#endif
