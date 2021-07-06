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
 *	@(#)$RCSfile: pcm.h,v $ $Revision: 4.3.3.4 $ (DEC) $Date: 1995/01/25 18:51:12 $
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
/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#ifndef _PCM_
#define _PCM_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/inputdevice.h>

/*
 * Peripheral Control Module line discipline.
 */
#ifdef KERNEL
#include "../h/ioctl.h"
#else
#include <sys/ioctl.h>
#endif

#define ACK		0x06
#define NAK		0x15
#define INIT_ALL	0x20
#define DEVICE_PRESENT	0x24
#define THRESHSMOOTH	0x51
#define LEDS		0x75

struct dial_control {
	unsigned char smoothing;
	unsigned char threshold;
};

typedef struct {
	ws_event w;
	short axis_data[8];
} dial_event;

#define PIOSETKNOB _IOW('p', 1, struct dial_control)
#define PIOSETLED _IOW('p', 2, int)

#ifdef __cplusplus
}
#endif
#endif
