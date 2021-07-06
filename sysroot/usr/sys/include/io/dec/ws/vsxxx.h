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
 *	@(#)$RCSfile: vsxxx.h,v $ $Revision: 1.2.11.6 $ (DEC) $Date: 1997/12/02 20:14:34 $
 */ 

#ifndef _VSXXX_H_
#define _VSXXX_H_

#define EVENT_LEFT_BUTTON	0x01
#define EVENT_MIDDLE_BUTTON	0x02
#define EVENT_RIGHT_BUTTON	0x03

#define EVENT_T_LEFT_BUTTON	0x01
#define EVENT_T_FRONT_BUTTON	0x02
#define EVENT_T_RIGHT_BUTTON	0x03
#define EVENT_T_BACK_BUTTON	0x04

/* puck buttons */

#define T_LEFT_BUTTON		0x02
#define T_FRONT_BUTTON		0x04
#define T_RIGHT_BUTTON		0x08
#define T_BACK_BUTTON		0x10

/* Mouse definitions */
#define MOTION_BUFFER_SIZE 100
#define SELF_TEST	'T'
#define INCREMENTAL	'R'
#define PROMPT		'D'

#define TABLET_NOPTR    0x13
#define TABLET_STYLUS   0x11
#define TABLET_PUCK     0x00


/* NOTE: these are the same as WSPR_XXX_BUTTON in sys/wsdevice.h */
#define VSXXX_RIGHT_BUTTON	0x01
#define VSXXX_MIDDLE_BUTTON	0x02
#define VSXXX_LEFT_BUTTON	0x04

#define VSXXX_X_SIGN	0x10		/* sign bit for X		*/
#define VSXXX_Y_SIGN	0x08		/* sign bit for Y		*/

#define START_FRAME	0x80		/* start of report frame bit	*/

#define UPDATE_POS	0x01

#ifdef FIXME
/* FIXME FIXME should be able to remove this 'cuz of ws_pointer_report?? */
/* Mouse report structure definition */
struct mouse_report {
	char state;			/* buttons and sign bits	*/
	short dx;			/* delta X since last change	*/
	short dy;			/* delta Y since last change	*/
	char bytcnt;			/* mouse report byte count	*/
};
#endif /* FIXME */

#ifdef _KERNEL
#include <io/dec/ws/ws_driver.h>

extern ws_hardware_type vsxxx_softc[];
extern ws_pointer	vsxxx_mouse;

extern void scc_enable_pointer(void);
extern int scc_stub(void);

extern int vsxxx_register_device(struct controller *ctlr);
extern int vsxxx_register_pointer_ehm(struct controller *ctlr);
extern int vsxxx_mouse_init(void);

extern int vsxxx_tablet_event(ws_info *wi, ws_event_queue *queue, 
			      ws_pointer *p,  ws_pointer_report *last_rep, 
			      ws_pointer_report *new_rep, int screen, 
			      int open);

extern int vsxxx_mouse_event(ws_screens *wsp, ws_pointer *p, 
			     ws_pointer_report *last_rep, 
			     ws_pointer_report *new_rep, int open);

extern void vsxxx_set_tablet_overhang(ws_pointer *p, ws_screen_descriptor *sp, 
			       unsigned int oh);

#endif /* _KERNEL */
#endif /*_VSXXX_H_*/
