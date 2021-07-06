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
 * @(#)$RCSfile: ws_driver.h,v $ $Revision: 1.1.15.1 $ (DEC) $Date: 2002/01/24 18:54:45 $
 */

#ifndef _WS_DRIVER_H_
#define _WS_DRIVER_H_

#ifndef __cplusplus

#include <sys/wsdevice.h>

extern ws_devices 	devices[];
extern ws_screens 	screens[];
extern ws_screens 	console_screen[];


#ifdef KERNEL
typedef struct {
  ws_descriptor ws;
  struct queue_entry rsel;	/* process waiting for select */
  ws_event_queue *queue;		/* where to find shared queue */
  ws_event *events;		/* where the driver puts the events*/
  ws_event_queue *user_queue_address;
  ws_motion_buffer *mb;
  ws_motion_history *motion;
  short open_flag;
  short dev_in_use;
  short mouse_on;
  short keybd_reset;
  short max_event_size;
  short max_axis_count;
  ws_pointer_report last_rep;
  char new_switch, old_switch;
  struct proc *p_server_proc;
  int server_proc_ref_count;
  unsigned int server_proc_screens;
  ws_emulation_functions *emul_funcs;
  int mouse_screen;		/* which screen the HW mouse is on */
  unsigned int cbuf[128], mbuf[128];
  int (*(server_vm_callback[NUMSCREENS]))();
  caddr_t server_proc_data[NUMSCREENS];
  u_long ws_lock;   /* Reserved for future use */
  u_long ws_reserved;  /* Reserved for future use */
} ws_info;
#endif /* KERNEL */

#endif /* __cplusplus */
#endif /* WS_DRIVER_H*/
