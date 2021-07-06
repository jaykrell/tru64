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
 * @(#)$RCSfile: comet_driver.h,v $ $Revision: 1.1.36.1 $ (DEC) $Date: 2002/01/24 18:54:41 $
 */

/* /usr/sys/include/io/hw/dec/ws/comet_driver.h */

#ifndef _COMET_DRIVER_H_ 
#define _COMET_DRIVER_H_ 

#ifndef __cplusplus

#include <sys/types.h>
#include <ksm/ksm.h>
#include <io/common/hwc_reg.h>

/* #include <io/dec/ws/comet_hwregs.h> */

#ifndef NDEPTHS
#define NDEPTHS 1                       /* all current hardware just has one */
#define NVISUALS 1
#endif /* NDEPTHS */


#define	COMET_RAISE_SPL()		splhigh();
#define	COMET_LOWER_SPL(_v)		splx(_v);

#define UCHAR unsigned char
#define ULONG unsigned long
#define USHORT unsigned short

typedef struct 
 {
   unsigned int v_clock_ctl;
   unsigned int aperture1;
   unsigned int aperture2;
   unsigned int dmaControl;
   unsigned int fifoDisconnect;
   unsigned int chip_config;
   unsigned int reboot;				
   unsigned int memControl;				
   unsigned int bypassWriteMask;
   unsigned int fbWriteMask;
   unsigned int screen_base;
   unsigned int screen_stride;
   unsigned int horiz_total;
   unsigned int horiz_gate_end;
   unsigned int horiz_blank_end;
   unsigned int horiz_sync_start;
   unsigned int horiz_sync_end;
   unsigned int vert_total;
   unsigned int vert_blank_end;
   unsigned int vert_sync_start;
   unsigned int vert_sync_end;
   unsigned int video_control;
   unsigned int line_count;
   unsigned int fifo_control;
   unsigned int screen_base_right;
   unsigned int vsAControl;
   unsigned short rd_misc_ctl;
   unsigned short rd_mode_ctl;
   unsigned short rd_color_mode;
   unsigned short rd_palette_page;
   unsigned short rd_pclk_ra1;
   unsigned short rd_pclk_ra2;
   unsigned short rd_pclk_ra3;
   unsigned short rd_pclk_rb1;
   unsigned short rd_pclk_rb2;
   unsigned short rd_pclk_rb3;
   unsigned short rd_pclk_rc1;
   unsigned short rd_pclk_rc2;
   unsigned short rd_pclk_rc3;
   
} comet_state_t;

/*
 *  comet driver info (softc) structure
 *
 *  NOTE:
 *  driver info structure was based on an earlier
 *  device driver, and may have several unused fields
 */
typedef struct {
   ws_screen_descriptor screen;
   ws_depth_descriptor  depth[NDEPTHS];
   ws_visual_descriptor visual[NVISUALS];
   ws_screen_functions  sf;
   ws_color_map_functions cmf;
   ws_cursor_functions  cf;
   unsigned int         state;
   short                ctlr_type;
   short                bus_type;
   pid_t                mapped_pid;
   unsigned short       attribute;            /* char mode attribute */
   unsigned short       unit;
   unsigned short       board_id;
   unsigned long        mem_phys;
   io_handle_t          mem_handle;
   ihandler_id_t        *intr_handle;
   io_handle_t          io_handle;
   io_handle_t          p2_fb_1;
   io_handle_t          p2_fb_2;
   io_handle_t          vga_io_handle;
   comet_region0_t	*p2_csr;
   unsigned long        cursor_offset;
   unsigned int         mem_size;
   unsigned short       intr_state;
   unsigned int		ctlr;
   /* interrupt handler id*/
   unsigned int         rev_id;
   unsigned short       mod_rev;
   struct pci_config_hdr *slot_cnfg_p;
   comet_state_t	reg_state;
   struct ws_ehm_screen_info *p_ehm_info;
   char			ehm_mem_size_text[16];
   unsigned int		variant;
   unsigned int		video_control;
   unsigned int		v_clock_ctl;
   unsigned int		dpms_state;
} comet_info_t;


typedef struct {
  short			fb_xoffset;
  short			fb_yoffset;
  short			cmap_min_dirty;
  short			cmap_max_dirty;
  short			wat_min_dirty;
  short			wat_max_dirty;
  short			ovl_wat_dirty;
} ramdac_type_t;

typedef struct {
  unsigned char 	dirty_cell;
  unsigned char 	red;	/* only need 8 bits */
  unsigned char 	green;
  unsigned char 	blue;
} comet_color_cell_t;

typedef struct {
  short			fb_xoffset;
  short			fb_yoffset;
  short			cmap_min_dirty;
  short			cmap_max_dirty;
  short			wat_min_dirty;
  short			wat_max_dirty;
  short			ovl_wat_dirty;
  /***************************************************************
   * fields above this line MUST match struct ramdac_type exactly!
   ***************************************************************/
  u_int			unit;
  char			cur_on;
  unsigned char		color_mode;
  short			x_hot;
  short			x_was_neg;		/* p2v only */
  short			y_hot;
  short			y_was_neg;		/* p2v only */
  ws_color_cell		cursor_fg;
  ws_color_cell		cursor_bg;
  void			(*enable_interrupt)();
  unsigned int		cursor_mode;		/* p2v only */
  u_long		cur_bits[256];
  comet_color_cell_t    color_cells[256]; 
} ramdac_info_t;



/* "state" field defines */
#define COMET_STATE_MAPPED          0x0001          /* has unit been mapped */
#define COMET_STATE_DIRTY_CURSOR    0x0002
#define COMET_STATE_DIRTY_CUR_POS   0x0004
#define COMET_STATE_DIRTY_CUR_COLOR 0x0008
#define COMET_STATE_DIRTY_CMAP      0x0010
#define COMET_STATE_DIRTY_WAT       0x0020
#define COMET_STATE_CURSOR_ON       0x0040
#define COMET_STATE_SCREEN_ON       0x0080
#define COMET_STATE_DAC             0x0100
#define	COMET_STATE_CMAP_RETRY	    0x0200
#define	COMET_STATE_TYPE_MASK	    0x1000
#define	COMET_STATE_TYPE_P2A	    0x0000
#define	COMET_STATE_TYPE_P2V	    0x1000

/* the following macros take a pointer to a comet_type structure */
/* "state" field test macros */
#define IS_COMET_MAPPED(scp)             ((scp)->state & COMET_STATE_MAPPED)
#define IS_COMET_DIRTY_CURSOR(scp)       ((scp)->state & COMET_STATE_DIRTY_CURSOR)
#define IS_COMET_DIRTY_CUR_POS(scp)       ((scp)->state & COMET_STATE_DIRTY_CUR_POS)
#define IS_COMET_DIRTY_CUR_COLOR(scp)       ((scp)->state & COMET_STATE_DIRTY_CUR_COLOR)
#define IS_COMET_DIRTY_CMAP(scp)         ((scp)->state & COMET_STATE_DIRTY_CMAP)
#define IS_COMET_DIRTY_WAT(scp)          ((scp)->state & COMET_STATE_DIRTY_WAT)
#define IS_COMET_CURSOR_ON(scp)          ((scp)->state & COMET_STATE_CURSOR_ON)
#define IS_COMET_SCREEN_ON(scp)          ((scp)->state & COMET_STATE_SCREEN_ON)
#define IS_COMET_DAC(scp)                ((scp)->state & COMET_STATE_DAC)
#define DO_COMET_CMAP_RETRY(scp)         ((scp)->state & COMET_STATE_CMAP_RETRY)
#define	IS_COMET_P2A(scp)	(((scp)->state & COMET_STATE_TYPE_MASK) == \
				 COMET_STATE_TYPE_P2A)
#define	IS_COMET_P2V(scp)	(((scp)->state & COMET_STATE_TYPE_MASK) == \
				 COMET_STATE_TYPE_P2V)

/* "state" field set and clear macros */
#define SET_COMET_MAPPED(scp)            (scp)->state |= COMET_STATE_MAPPED
#define CLR_COMET_MAPPED(scp)            (scp)->state &= ~COMET_STATE_MAPPED
#define SET_COMET_DIRTY_CURSOR(scp)      (scp)->state |= COMET_STATE_DIRTY_CURSOR
#define CLR_COMET_DIRTY_CURSOR(scp)      (scp)->state &= ~COMET_STATE_DIRTY_CURSOR
#define SET_COMET_DIRTY_CUR_POS(scp)     (scp)->state |= COMET_STATE_DIRTY_CUR_POS
#define CLR_COMET_DIRTY_CUR_POS(scp)     (scp)->state &= ~COMET_STATE_DIRTY_CUR_POS
#define SET_COMET_DIRTY_CUR_COLOR(scp)   (scp)->state |= COMET_STATE_DIRTY_CUR_COLOR
#define CLR_COMET_DIRTY_CUR_COLOR(scp)   (scp)->state &= ~COMET_STATE_DIRTY_CUR_COLOR
#define SET_COMET_DIRTY_CMAP(scp)        (scp)->state |= COMET_STATE_DIRTY_CMAP
#define CLR_COMET_DIRTY_CMAP(scp)        (scp)->state &= ~COMET_STATE_DIRTY_CMAP
#define SET_COMET_DIRTY_WAT(scp)         (scp)->state |= COMET_STATE_DIRTY_WAT
#define CLR_COMET_DIRTY_WAT(scp)         (scp)->state &= ~COMET_STATE_DIRTY_WAT
#define SET_COMET_CURSOR_ON(scp)         (scp)->state |= COMET_STATE_CURSOR_ON
#define CLR_COMET_CURSOR_ON(scp)         (scp)->state &= ~COMET_STATE_CURSOR_ON
#define SET_COMET_SCREEN_ON(scp)         (scp)->state |= COMET_STATE_SCREEN_ON
#define CLR_COMET_SCREEN_ON(scp)         (scp)->state &= ~COMET_STATE_SCREEN_ON
#define SET_COMET_DAC(scp)               (scp)->state |= COMET_STATE_DAC
#define CLR_COMET_DAC(scp)               (scp)->state &= ~COMET_STATE_DAC
#define SET_COMET_CMAP_RETRY(scp)        (scp)->state |= COMET_STATE_CMAP_RETRY
#define CLR_COMET_CMAP_RETRY(scp)        (scp)->state &= ~COMET_STATE_CMAP_RETRY
#define	SET_COMET_P2A(scp)	 ((scp)->state = (COMET_STATE_TYPE_P2A | \
				((scp)->state & ~COMET_STATE_TYPE_MASK)))
#define	SET_COMET_P2V(scp)	 ((scp)->state = (COMET_STATE_TYPE_P2V | \
				((scp)->state & ~COMET_STATE_TYPE_MASK)))

typedef struct 
{
  USHORT htot; /* Horizontal total time */
  UCHAR	 hfp;  /* Horizontal front porch */
  UCHAR	 hst; /* Horizontal sync time */
  UCHAR	 hbp; /* Horizontal back porch */
  UCHAR	 hsp; /* Horirontal sync polarity */
  USHORT vtot; /* Vertical total time */
  UCHAR	 vfp; /* Vertical front porch */
  UCHAR	 vst; /* Vertical sync time */
  UCHAR	 vbp; /* Vertical back porch */
  UCHAR	 vsp; /* Vertical sync polarity */
} comet_video_timings_t;

#define TRUECOLOR 1
#define PSEUDOCOLOR 0 

typedef struct
{
  UCHAR  pixel_depth; /* 8, 16, 24 */
  UCHAR  visual; /* TRUECOLOR or PSEUDO COLOR */
  UCHAR  freq; /* hz */
  USHORT x_res;
  USHORT y_res; 
  comet_video_timings_t vid_tim;
  unsigned int fifo16;
  unsigned int fifo24;
} comet_resolution_entry_t; 

#endif /* __cplusplus */
#endif /* _COMET_DRIVER_H_ */
