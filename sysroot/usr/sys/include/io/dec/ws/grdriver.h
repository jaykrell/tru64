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
 * @(#)$RCSfile: grdriver.h,v $ $Revision: 1.1.8.4 $ (DEC) $Date: 1997/09/30 20:31:56 $
 */

#ifndef _GRDRIVER_H_
#define _GRDRIVER_H_

#ifdef _KERNEL



/*
 *  common graphics drivers include files
 */
#include <io/common/devio.h>
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <machine/hal/console.h>
#include <sys/kernel.h>
#include <machine/cpu.h>
#include <io/common/devdriver.h>
#include <sys/proc.h>
#include <sys/user.h>



/*
 *  ws globals for display drivers
 */

extern ws_cursor_data default_cursor;  /* default cursor data */
extern ws_monitor monitor_type[];      /* default monitor types */
extern int nmon_types;                 /* number of default monitor types */
extern unsigned int cdata[];           /* cusror data */
extern int vt100_emulation;            /* indicates term emulation in-use */

/* 
 * ws-related sizer externs 
 */
extern  int     ws_display_type;       /* sizer -wt */
extern  int     ws_display_units;      /* sizer -wu */


/*
 * macros for cursor maintenance during console
 * terminal emulation,
 *
 *  where:
 *		sp == *ws_screen_descriptor
 */
#define ONE_LINE(sp)		((sp)->max_col)
#define ONE_PAGE(sp)		((sp)->max_col*(sp)->max_row)

#define TOP_LINE(sp)		(0)
#define BOTTOM_LINE(sp)		(((sp)->max_row - 1) * ONE_LINE(sp))

#define BEG_OF_LINE(sp, pos)	((pos) - ((pos) % ONE_LINE((sp))))
#define CURRENT_COLUMN(sp, pos)	((pos) % ONE_LINE((sp)))

#define ROW_POS(sp, row)	(ONE_LINE((sp)) * (row))
#define CHAR_POS(sp, row, col)	(ROW_POS((sp),(row)) + (col))
#define CUR_POS(sp) 		(ROW_POS((sp),(sp)->row) + ((sp)->col))
#define CUR_ROW_POS(sp)		(ONE_LINE((sp)) * ((sp)->row))

#define ROW_FROM_POS(sp, pos)	((pos) / ONE_LINE((sp)))
#define COL_FROM_POS(sp, pos)	((pos) % ONE_LINE((sp)))

/* 
 * 	Defines used in display drivers to indicate memory size
 */
#define QUART_MEG       (256*1024)
#define HALF_MEG        (512*1024)
#define ONE_MEG        (1024*1024)
#define TWO_MEG        (2048*1024)
#define FOUR_MEG       (4096*1024)

/*
 *  Digital-ONLY function prototypes
 */

extern int ws_register_vm_callback( int, int (*func)(), caddr_t);
extern int ws_unregister_vm_callback(int);

#include <io/dec/ws/ws_driver.h>

extern struct controller *ws_get_default_console( struct controller 
						 *ctb_console_ctlr);
extern int install_generic_console(void);

#endif /* _KERNEL */

#endif /*_GRDRIVER_H_*/






