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
 *	@(#)$RCSfile: msg_type.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1993/05/26 22:13:49 $
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
 *    This file defines user msg types that may be ored into
 *    the msg_type field in a msg header. Values 0-5 are reserved
 *    for use by the kernel and are defined in message.h. 
 *
 */

#ifndef	_MACH_MSG_TYPE_H_
#define _MACH_MSG_TYPE_H_

#define MSG_TYPE_CAMELOT	(1 << 6)
#define MSG_TYPE_ENCRYPTED	(1 << 7)
#define MSG_TYPE_RPC		(1 << 8)	/* Reply expected */

#include <mach/message.h>

#endif	/*_MACH_MSG_TYPE_H_*/
