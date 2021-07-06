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
 * @(#)$RCSfile: inputdriver.h,v $ $Revision: 1.1.14.1 $ (DEC) $Date: 2002/01/24 18:54:44 $
 */

#ifndef _INPUTDRIVER_H_
#define _INPUTDRIVER_H_

#ifndef __cplusplus

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/buf.h>
#include <kern/queue.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devio.h>
#include <io/common/devdriver.h>
#include <io/dec/ws/slu.h>	
#include <sys/keysyms.h>
#include <sys/sysconfig.h>

extern struct slu	slu;  
extern ws_pointer_report current_rep;
extern u_short		pointer_id;
extern char		*special_keys[];
extern int		special_keys_size;

/* This switch table is defined here for all PC (e.g. gpc driver)
 * keyboard/mouse devices. It is required when gpc is present in
 * system, but ws is not (e.g. Turbolaser). It will be initialized
 * with null values by gpc, and overwritten with actual function
 * pointers when pcxal/pcxas module configure routine is called.
 */

struct input_sw {
  int     (*register_kbd_device)(struct controller *ctlr); /* register kbd
															  with WS */
  int     (*register_pointer_device)(struct controller *ctlr); /* register
												  _pointer with WS*/
  int     (*register_kbd_ehm)(struct controller *ctlr); /* register kbd w/
														   ehm */
  int     (*register_pointer_ehm)(struct controller *ctlr); /* register po
															   inter w/ ehm */
  int     (*input_intr)(int ch);                     /* ws_input_intr */
  int     (*pointer_intr)(int status, int data);     /* mouse interrupt */
  void    (*init_keyboard)(ws_keyboard_state *lp);   /* init_keyboard */
  void    (*disable_keyboard)(void);                 /* disable_keyboard */
  int     (*init_pointer)(caddr_t handle);           /* init_pointer */
  void    (*enable_pointer)(caddr_t handle);         /* enable_pointer */
  int     (*enter_hot_swap_event)(    /* enter_hot_swap_event on Xqueue*/
								  int type, int device_num);
  cfg_status_t (*notify_evm_event)(    /* notify Event Mgr. of event */
								   caddr_t *handle, int event);
  ws_keyboard_state *kbd_softc;           /* keyboard softc structure */
  ws_hardware_type *mouse_softc;          /* mouse softc structure */
  ws_keyboard *kbd_device;                /* ws_keyboard definition */
  ws_pointer  *mouse_device;              /* ws_pointer definition */
  int  (*reserved_func)(void);            /* Reserved */
  caddr_t private1;                       /* Reserved for future use (e.g.
											 USB) */
  caddr_t private2;                       /* Reserved for future use */
};


/* These entry points are used by the keyboard/mouse interface layer 
 * Only used by scc driver - CHS 
 */
extern int 	(*v_consputc)(char c);
extern int 	(*v_consgetc)();
extern int 	(*vs_gdopen)();
extern int 	(*vs_gdclose)();
extern int 	(*vs_gdread)();
extern int 	(*vs_gdwrite)();
extern int 	(*vs_gdselect)();
extern int 	(*vs_gdkint)();		/* keyboard interrupt */
extern int 	(*vs_gdpint)();		/* pointer interrupt */
extern int	(*vs_gdmmap)();
extern int 	(*vs_gdioctl)();
extern int 	(*vs_gdstop)();

extern char *language_names[];
extern xcomp_t comp_seq[];

/*
 *  Common function prototypes for input drivers
 */
#include <io/dec/ws/ws_driver.h>
extern int ws_register_device(int device_type, 
			      ws_input_device *dp, 
			      int event_size);

extern int ws_register_kbd_with_ehm( ws_keyboard *kp, 
				     struct controller *ctlr);

extern int ws_register_pointer_with_ehm( ws_pointer *pp, 
					 struct controller *ctlr);
				
extern void ws_register_kbd_callback( void (*callback)() );

extern int ws_set_cursor_position(caddr_t cursor_handle, ws_screens *wsp, 
				  int x, int y);

extern ws_screen_descriptor * ws_do_edge_work(ws_screen_descriptor *sp, 
					      ws_pointer *p, int edge);

extern int ws_process_mouse_report(ws_screens *wsp, ws_pointer *p, 
				   ws_pointer_report *last_rep, 
				   ws_pointer_report *new_rep, int open);

extern int ws_wakeup_any_pending(void);

extern int ws_enter_keyboard_event(int ch, int type);

extern int ws_input_intr(int ch);

extern int ws_enter_hot_swap_event(int type, int device_num);		

extern cfg_status_t ws_notify_evm_event(caddr_t *handle, int event);		

extern void ws_update_kbd_attrs(int point, 
				int order, 
				ulong args, 
				ulong event_arg);

#endif /* __cplusplus */
#endif /* _INPUTDRIVER_H_ */


