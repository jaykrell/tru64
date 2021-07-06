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
 * @(#)$RCSfile: vga_support.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1997/04/08 19:28:50 $
 */


#ifndef _VGA_SUPPORT_H_
#define _VGA_SUPPORT_H_

#ifdef _KERNEL

#include <io/dec/ws/vgareg.h>

/*
 *    Standard VGA common support for graphics drivers
 *
 */


/* 
 *  console register state
 *  can use to verify/modify 
 *  vga console register settings 
 */
extern void *vga_cons_orig_state;
extern void *vga_cons_new_state;




/************************************************************************* 
 * 
 *         vga console support routines 
 *
 *************************************************************************/


/*
 *   install_vga_console(ctlr)
 *
 *
 *   SUMMARY:
 *        Support routine that will register the generic vga driver as the
 *        system console.
 *
 *   ARGUMENTS:
 *        struct controller *ctlr,  valid pointer to calling driver's
 *                                  controller structure
 *
 *   USAGE NOTES:
 *       call from xxx_console_attach routine in place of a call to
 *       to ws_register_console.
 *
 *       Calling driver's console_attach routine must ensure board is
 *       set-up for console mode.
 *
 *       Calling driver's close routine must ensure board is
 *       set-up for console mode for transition from graphics mode (windows)
 *       back to console mode.
 *
 *       Calling driver init_screen function should initialize the
 *       board for graphics mode, it will get called in transition
 *       from console mode to graphics mode (windows open).
 *
 *       When system is in console mode the generic vga driver will assume
 *       it can reference any standard VGA I/O register address.
 *
 *   RETURN VALUES:
 *       Any non-negative value indicates SUCCESS
 */
extern int install_vga_console(struct controller *ctlr);


/********************************************************************
 *
 *           standard VGA common functions
 *
 *           These are common VGA functions that access the
 *           board using legacy I/O addresses (ISA). Before
 *           using, the global vga_cons I/O handles must be 
 *           initialized.  In addition, these assume the board
 *           has I/O access enabled.  They are primarily intended
 *           for use by DEC drivers for the purpose of code-sharing.
 *
 *           NOTE: use caution when using after X server is up
 *    
 ********************************************************************/

/*
 *  I/O handles for register access
 *  If a driver uses vga support routines
 *  prior to console_attach, these must
 *  be initialized.
 */
extern io_handle_t VGA_io_base_handle;
extern io_handle_t VGA_mem_base_handle;

/*
 *  Functions to set/view the standard vga register
 *  set. NOTE: One can view vga console driver's register state
 *  by calling with vga_cons_xxx_state pointers which are 
 *  defined above
 */
extern void VGA_save_registers(vgaHWPtr vga_regs_ptr);
extern void VGA_restore_registers(vgaHWPtr vga_regs_ptr);
extern void VGA_print_registers(vgaHWPtr vga_regs_ptr);

/*
 *  standard vga interrupt routines
 */
extern int VGA_enable_interrupt(void);
extern int VGA_disable_interrupt(void);
extern int VGA_clear_interrupt(void);

/*
 *  standard vga screen on/off routines
 */
extern int VGA_video_on(void);
extern int VGA_video_off(void);

/*
 *  Routine to clear a VGA screen for use on
 *  graphics driver close when using serial console
 */
extern int VGA_clear_screen(struct vga_info * vp);

/*
 *  standard 6/8-bit vga colormap routines, based
 *  on vga_info (softc) struct representation, code uses
 *  and modifies color map flags and CLUT DB in softc pointed to by
 *  colormap_handle 
 */

extern int VGA_load_color_map_entry(caddr_t colormap_handle, 
				    int map, 
				    ws_color_cell *entry);

extern void VGA_clean_color_map(caddr_t colormap_handle);



/********************************************************************
 *
 *           vga common bus functions
 *
 ********************************************************************/

                                  /* c is ctlr struct pointer */
#define VGA_PCI_CONFIG_BASE(c) \
	(((struct pci_slot *)(c)->pcislot)->slot_cnfg_p->config_base)


extern int VGA_get_pci_config_data(struct vga_info *vp, 
				   int offset, 
				   int length,
				   struct controller *ctlr);

extern int VGA_put_pci_config_data(struct vga_info *vp, 
				   int offset, 
				   int length, 
				   int data,
				   struct controller *ctlr);

extern int VGA_reverseByte(int b);  




/*********************************
 *
 *   vga console support defs 
 *
 *********************************/

/* default attribute for VGA adapters which use character attributes */
/* NOTE: attribute byte is 0xBF, where B is bg index, and F is fg index */
#define VGA_ATTR_NORMAL		0x01	/* black bg, white fg */
#define VGA_ATTR_REVERSE	0x10	/* white bg, black fg */

#define VGA_FB_ADDR		0x0a0000
#define VGA_TX_ADDR		0x0b8000

/* default attribute for VGA adapters which use character attributes */
#define DEFAULT_ATTRIBUTE 0x01	/* black bg, white fg */

#endif /* _KERNEL*/

#endif /* _VGA_SUPPORT_H */
