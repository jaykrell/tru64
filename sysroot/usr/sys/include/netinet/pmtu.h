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
 * @(#)$RCSfile: pmtu.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/03/02 23:46:22 $
 */

#ifndef PMTU_H
#define PMTU_H

#ifdef	_KERNEL

#define PMTU_RT_CHECK_INTVL 10*PR_SLOWHZ	/* 10 seconds */
#define PMTU_DECREASE_INTVL 600*PR_SLOWHZ	/* 10 minutes */
#define PMTU_INCREASE_INTVL 120*PR_SLOWHZ	/* 2 minutes */

#define PMTU_MIN_MTU 68			/* minimum mtu */
#define PMTU_MAX_MTU 65535		/* maximum mtu */

#ifndef REPLICATED
#define REPLICATED
#endif

extern	REPLICATED int	pmtu_enabled;	/* 0 = disabled, !0 = enabled */
extern	u_int	pmtu_rt_check_intvl;	/* route check interval */
extern	u_int	pmtu_rt_check_timer;	/* route check timer */
extern	u_int	pmtu_decrease_intvl;	/* wait after pmtu decrease */
extern	u_int	pmtu_increase_intvl;	/* wait after pmtu increase */

#endif	/* _KERNEL */

#endif	/* PMTU_H */
