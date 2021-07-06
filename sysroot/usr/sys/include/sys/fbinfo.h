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
 *	@(#)$RCSfile: fbinfo.h,v $ $Revision: 4.2.9.1 $ (DEC) $Date: 2000/12/12 21:15:20 $
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
 * Derived from fbinfo.h	4.1	(ULTRIX)	8/10/90
 */

#ifndef fbinfo_DEFINED
#define fbinfo_DEFINED 1

#ifndef __cplusplus

#define NDEPTHS 1			/* all current hardware just has one*/
#define NVISUALS 1

struct fb_info {
	ws_screen_descriptor screen;
	ws_depth_descriptor depth[NDEPTHS];
	ws_visual_descriptor visual[NVISUALS];
	ws_screen_functions sf;
	ws_color_map_functions cmf;
	ws_cursor_functions cf;
	int (*attach)();	/* called at attach time (if defined)	*/
	void (*interrupt)();	/* called at interrupt time (if defined)*/
        void (*bot)();          /* called at beginning of time (console init)*/
};

#ifdef _KERNEL
#include <io/dec/ws/bt459.h>

/*
 * function protos
 */
extern caddr_t fb_init_closure(caddr_t closure, caddr_t address, int unit, 
			       int type);

extern int fb_scroll_screen(caddr_t closure, ws_screen_descriptor *screen);

extern int fb_clear_screen(caddr_t closure, ws_screen_descriptor *screen);

extern int fb_blitc(caddr_t closure, ws_screen_descriptor *screen, int row, 
		    int col, u_char c);

extern int fb_map_unmap_screen(caddr_t closure, ws_depth_descriptor *depths, 
			       ws_screen_descriptor *screen, 
			       ws_map_control *mp);

extern int fbprobe(char *nxv, register struct controller *ctlr);

extern int fbtype(caddr_t address);

extern int fbattach(register struct controller *ctlr);

extern int fb_attach(register caddr_t address, 
		     int unit, 
		     int flags, 
		     struct controller *ctlr);

extern int fbint(int unit);

extern int fb_cons_init(register caddr_t address, int slot);

extern int fb_init_screen(void);

/*
 *  sfb external function protos
 */
extern int sfb_clear_screen(caddr_t closure, ws_screen_descriptor *screen);
extern int sfb_scroll_screen(caddr_t closure, ws_screen_descriptor *screen);
extern int sfb_blitc(caddr_t closure, ws_screen_descriptor *screen, 
		     int row, int col, u_char c);

extern int sfb_map_unmap_screen(caddr_t closure, 
				ws_depth_descriptor *depths, 
				ws_screen_descriptor *screen, 
				ws_map_control *mp);
extern int sfb_ioctl(caddr_t closure, unsigned int cmd, caddr_t data, 
		     int flag);

extern void sfb_bot(register struct fb_info *fbp); 
extern int sfb_attach(register struct controller *ctlr);
extern void sfb_close(caddr_t closure);
extern void sfb_interrupt(register struct controller *ctlr, caddr_t closure);
extern void sfb_enable_interrupt(caddr_t closure);

/*
 *  sfb+ external prototypes
 */
extern caddr_t sfbp_dummy_caddrt(void);
extern int sfbp_dummy_int(void);
extern void sfbp_bot(register struct fb_info *fbp);
extern int sfbp_attach(register struct controller *ctlr);
extern void sfbp_close(caddr_t closure);
extern void sfbp_interrupt(struct controller *ctlr, caddr_t closure);
extern int sfbp_attach(register struct controller *ctlr);
extern void sfbp_close(caddr_t closure);
extern void sfbp_interrupt(struct controller *ctlr, caddr_t closure);
extern int sfbp_init_screen(caddr_t closure, ws_screen_descriptor *screen);
extern int sfbp_clear_screen(caddr_t closure, ws_screen_descriptor *screen);
extern int sfbp_scroll_screen(caddr_t closure, ws_screen_descriptor *screen);
extern int sfbp_blitc(caddr_t closure, ws_screen_descriptor *screen, 
		      int row, int col, u_char c);
extern int sfbp_map_unmap_screen(caddr_t closure, 
				 ws_depth_descriptor *depths, 
				 ws_screen_descriptor *screen, 
				 ws_map_control *mp);
extern int sfbp_ioctl(caddr_t closure, unsigned int cmd, 
		      caddr_t data, int flag);

extern caddr_t sfbp_init_closure(caddr_t closure, 
				 caddr_t address, int unit, int type);
extern int sfbp_load_formatted_cursor(register struct sfbp_curs_info *bti);

extern int sfbp_init_cursor(caddr_t closure);

#endif /*_KERNEL*/

#endif /* __cplusplus */

#endif /* !fbinfo_DEFINED */
