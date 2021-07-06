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
 * @(#)$RCSfile: tvp4020.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/06/26 19:09:46 $
 */

/*
 *
 * Module Name:
 *
 *    TVP4020.h
 *
 * Description:
 *
 *    This module contains the definitions for the TVP4020 internal RAMDAC.
 *
 */

#define COMET_CLOCK_SPEED           ( 80 * (1000*1000)) 
#define COMET_RESET_CLOCK_SPEED           ( 75 * (1000*1000)) 
#define COMET_RESET_VID_SPEED           ( 2864 * (10*1000)) 
/*
 * DIRECT REGISTER - CURSOR POSITION CONTROL
 *
 *  ** TVP4020_CUR_X_LSB 
 *  ** TVP4020_CUR_X_MSB 
 *  ** TVP4020_CUR_Y_LSB 
 *  ** TVP4020_CUR_Y_MSB 
 *		Default - undefined
 * Values written into those registers represent the BOTTOM-RIGHT corner
 * of the cursor. If 0 is in X or Y position - the cursor is off the screen
 * Only 12 bits are used, giving the range from 0 to 4095 ( 0x0000 - 0x0FFF)
 * The size of the cursor is (64,64) (0x40, 0x40)
 */
#define TVP4020_CURSOR_OFFSCREEN 0x00	/* Cursor offscreen */

/*
 * DIRECT REGISTER - CURSOR COLORS 
 */

#define TVP4020_CURSOR_COLOR0           0x01
#define TVP4020_CURSOR_COLOR1           0x02
#define TVP4020_CURSOR_COLOR2           0x03

/*
 * INDIRECT REGISTER - CURSOR CONTROL
 */
#define TVP4020_CURSOR_CONTROL   	0x06	/* Indirect cursor control*/

#define TVP4020_CURSOR_SIZE_32      	(0 << 6)// 32x32 cursor
#define TVP4020_CURSOR_SIZE_64   	(1 << 6)// 64x64 cursor

#define TVP4020_CURSOR_RAM_ADDRESS(x)	(((x) & 0x03) << 2) /* High bits of cursor RAM address */
#define TVP4020_CURSOR_RAM_MASK		((0x03) << 2)  /*Mask for high bits of cursor RAM address */

/*
 * DABO: Added constants for cursor mode
 */
#define TVP4020_CURSOR_OFF	   	0x00	/* Cursor off */
#define TVP4020_CURSOR_COLOR   		0x01	/* 2-bits select color */
#define TVP4020_CURSOR_XGA	   	0x02	/* 2-bits select XOR */
#define TVP4020_CURSOR_XWIN	   	0x03	/* 2-bits select transparency/color */


/*
 * INDIRECT REGISTER - COLOR MODE REGISTER 
 */
#define TVP4020_COLOR_MODE		0x18	/* Color Mode Register */

#define TVP4020_TRUE_COLOR_ENABLE       (1 << 7) /* True Color data accesses LUT */
#define TVP4020_TRUE_COLOR_DISABLE      (0 << 7) /* Non true color accesses LUT */

#define TVP4020_RGB_MODE                (1 << 5) /* RGB mode  DABO: Swapped 0/1 (0=BGR, 1=RGB) */
#define TVP4020_BGR_MODE                (0 << 5) /* BGR mode */

#define TVP4020_VGA_SELECT              (0 << 4) /* select VGA mode */
#define TVP4020_GRAPHICS_SELECT         (1 << 4) /* select graphics modes */

#define TVP4020_PIXEL_MODE_CI8          0 /* pseudo color or VGA mode */
#define TVP4020_PIXEL_MODE_332          1 /* 332 true color */
#define TVP4020_PIXEL_MODE_2320         2
#define TVP4020_PIXEL_MODE_2321         3
#define TVP4020_PIXEL_MODE_5551         4
#define TVP4020_PIXEL_MODE_4444         5
#define TVP4020_PIXEL_MODE_565          6
#define TVP4020_PIXEL_MODE_8888         8 
#define TVP4020_PIXEL_MODE_PACKED       9 /* 24 bit packed */

/*
 * INDIRECT REGISTER - MODE CONTROL REGISTER 
 */
#define TVP4020_MODE_CONTROL		  0x19 /*  Mode control */

#define TVP4020_PRIMARY_INPUT             (0 << 4) /* Primary input throuh palette */
#define TVP4020_SECONDARY_INPUT           (1 << 4) /* Secondary input throuh palette */

#define TVP4020_5551_DBL_BUFFER           (1 << 2) /* Enable 5551 dbl buffer */
#define TVP4020_5551_PACKED               (0 << 2) /* Packed 555 mode */

#define TVP4020_ENABLE_STATIC_DBL_BUFFER  (1 << 1) /* Static dbl buffer enabled */
#define TVP4020_DISABLE_STATIC_DBL_BUFFER (1 << 1) /* Static dbl buffer disabled */

#define TVP4020_SELECT_FRONT_MODE         (0 << 0) /* Front mode */
#define TVP4020_SELECT_BACK_MODE          (1 << 0) /* Back mode */

/*
 * INDIRECT REGISTER - PALETTE PAGE
 */
#define TVP4020_PALETTE_PAGE	        0x1C

/*
 * INDIRECT REGISTER - MISC CONTROL
 */
#define TVP4020_MISC_CONTROL		0x1E

#define TVP4020_SYNC_ENABLE		(1 << 5) /* Output SYNC info onto IOG */
#define TVP4020_SYNC_DISABLE		(0 << 5) /* No SYNC IOG output */

#define TVP4020_PEDESTAL_0		(0 << 4) /* 0 IRE blanking pedestal */
#define TVP4020_PEDESTAL_75		(1 << 4) /* 7.5 IRE blanking pedestal */

#define TVP4020_VSYNC_INVERT		(1 << 3) /* invert VSYNC output polarity */
#define TVP4020_VSYNC_NORMAL		(0 << 3) /* normal VSYNC output polarity */

#define TVP4020_HSYNC_INVERT		(1 << 2) /* invert HSYNC output polarity */
#define TVP4020_HSYNC_NORMAL		(0 << 3) /* normal HSYNC output polarity */

#define TVP4020_DAC_8BIT		(1 << 1) /* DAC is in 8-bit mode */
#define TVP4020_DAC_6BIT		(0 << 1) /* DAC is in 6-bit mode */

#define TVP4020_DAC_POWER_ON		(0 << 0) /* Turn DAC Power on */
#define TVP4020_DAC_POWER_OFF		(1 << 0) /* Turn DAC Power off */

/*
 * INDIRECT REGISTER - COLOR KEY CONTROL
 */
#define TVP4020_CK_CONTROL		0x40   

/*
 * INDIRECT REGISTER - COLOR KEY 
 */
#define TVP4020_CK_OVR_REG 		0x41
#define TVP4020_CK_RED_REG 		0x42
#define TVP4020_CK_GREEN_REG		0x43
#define TVP4020_CK_BLUE_REG		0x44

/*
 * INDIRECT REGISTER - PIXEL CLOCK PLL
 */

#define TVP4020_PIXCLK_REG_A1		0x20
#define TVP4020_PIXCLK_REG_A2		0x21
#define TVP4020_PIXCLK_REG_A3		0x22
#define TVP4020_PIXCLK_REG_B1		0x23
#define TVP4020_PIXCLK_REG_B2		0x24
#define TVP4020_PIXCLK_REG_B3		0x25
#define TVP4020_PIXCLK_REG_C1		0x26
#define TVP4020_PIXCLK_REG_C2		0x27
#define TVP4020_PIXCLK_REG_C3		0x28

#define TVP4020_PIXCLK_STATUS		0x29

/*
 * INDIRECT REGISTER - MEMORY CLOCK PLL
 */

#define TVP4020_MEMCLK_REG_1		0x30
#define TVP4020_MEMCLK_REG_2		0x31
#define TVP4020_MEMCLK_REG_3		0x32

#define TVP4020_MEMCLK_STATUS		0x33





