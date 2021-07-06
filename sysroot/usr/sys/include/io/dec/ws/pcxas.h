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
 * @(#)$RCSfile: pcxas.h,v $ $Revision: 1.1.6.5 $ (DEC) $Date: 1997/09/30 20:32:07 $
 */

#ifndef _PCXAS_H_
#define _PCXAS_H_

#define PCXAS_LEFT_BUTTON	0x01
#define PCXAS_RIGHT_BUTTON	0x02
#define PCXAS_MIDDLE_BUTTON	0x04

#define PCXAS_X_SIGN		0x10
#define PCXAS_Y_SIGN		0x20

#define PCXAS_X_OVER		0x40
#define PCXAS_Y_OVER		0x80

#ifdef _KERNEL

#include <io/dec/ws/ws_driver.h>

extern ws_hardware_type pcxas_softc[];
extern ws_pointer pcxas_mouse;

extern int pcxas_register_device(struct controller *ctlr);
extern int pcxas_intr(int status, int data);
extern int pcxas_init_pointer(caddr_t handle);
extern void pcxas_enable_pointer(caddr_t handle);
extern void pcxas_reset_pointer(caddr_t handle);
extern void pcxas_disable_pointer(caddr_t handle);
extern int pcxas_tablet_event(ws_info *wi, ws_event_queue *queue, 
			      ws_pointer *p, ws_pointer_report *last_rep, 
			      register ws_pointer_report *new_rep, 
			      int screen, int open);
extern int pcxas_mouse_event(ws_screens *wsp, ws_pointer *p, 
			     ws_pointer_report *last_rep, 
			     ws_pointer_report *new_rep, int open);
extern void pcxas_set_tablet_overhang(ws_pointer *p, 
				      ws_screen_descriptor *sp, 
				      unsigned int oh);

#endif /* _KERNEL */

#endif /*_PCXAS_H_*/

