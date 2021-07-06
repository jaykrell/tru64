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
 *	@(#)$RCSfile: notify.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/05/26 22:13:55 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 *	Kernel notification message definitions.
 *
 */

#ifndef	_MACH_NOTIFY_H_
#define _MACH_NOTIFY_H_

#include <mach/message.h>

/*
 *	Notifications sent upon interesting system events.
 */

#define NOTIFY_FIRST			0100
#define NOTIFY_PORT_DELETED		( NOTIFY_FIRST + 001 )
#define NOTIFY_MSG_ACCEPTED		( NOTIFY_FIRST + 002 )
#if	!defined(KERNEL)
#define NOTIFY_OWNERSHIP_RIGHTS		( NOTIFY_FIRST + 003 )
#define NOTIFY_RECEIVE_RIGHTS		( NOTIFY_FIRST + 004 )
#endif	/*!defined(KERNEL)*/
#define NOTIFY_PORT_DESTROYED		( NOTIFY_FIRST + 005 )
#define NOTIFY_LAST			( NOTIFY_FIRST + 015 )

typedef struct {
	msg_header_t	notify_header;
	msg_type_t	notify_type;
	port_t		notify_port;
} notification_t;

#endif	/* _MACH_NOTIFY_H_ */
