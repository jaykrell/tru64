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
 * @(#)$RCSfile: DECWmHints.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1994/10/04 13:18:50 $
 */
/*
*****************************************************************************
**                                                                          *
**                         COPYRIGHT (c) 1988 BY                            *
**             DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.                *
**	MASSACHUSSETTS INSTITUTE OF TECHNOLOGY, CAMBRIDGE, MASS.	    *
**                         ALL RIGHTS RESERVED                              *
**                                                                          *
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED  *
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE  *
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER  *
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY  *
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY  *
**  TRANSFERRED.                                                            *
**                                                                          *
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE  *
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT  *
**  CORPORATION OR MIT.                                                     *
**                                                                          *
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS  *
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.                 *
**                                                                          *
*****************************************************************************
**++
**  FACILITY:
**
**      < to be supplied >
**
**  ABSTRACT:
**
**      < to be supplied >
**
**  ENVIRONMENT:
**
**      < to be supplied >
**
**  MODIFICATION HISTORY:
**
**      < to be supplied >
**
**--
**/
#ifndef _DECWmHints_h_
#define _DECWmHints_h_
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif


extern void WmSetDecorationGeometry();
extern void WmSetDECWmHints();
extern void WmSetIconBoxName();
extern Status WmGetDecorationGeoemtery();
extern Status WmGetDECWmHints();
extern Status WmGetIconBoxName();

typedef struct {
	Font title_font;
	Font icon_font;
	int border_width;
	int title_height;
	int non_title_width;
	int icon_name_width;
	int iconify_width;
	int iconify_height;
} WmDecorationGeometryRec, *WmDecorationGeometry;


#ifndef DECWmIconifyPixmapMask
/* 
 * also defined in Vendor.h
 */
#define DECWmIconifyPixmapMask		(1L<<0)
#define DECWmIconBoxXMask 		(1L<<1)
#define DECWmIconBoxYMask		(1L<<2)
#define DECWmTiledMask			(1L<<3)
#define DECWmStickyMask			(1L<<4)
#define DECWmNoIconifyButtonMask	(1L<<5)
#define DECWmNoLowerButtonMask		(1L<<6)
#define DECWmNoResizeButtonMask		(1L<<7)
#endif

typedef struct {
	unsigned int value_mask;
	Pixmap iconify_pixmap;
	int icon_box_x;
	int icon_box_y;
	Boolean tiled;
	Boolean sticky;
	Boolean no_iconify_button;
	Boolean no_lower_button;
	Boolean no_resize_button;
} DECWmHintsRec, *DECWmHints;

#define WmNormalState 0
#define WmIconicState 1

typedef struct {
	int state; /* normal or iconic (or zoomed?) */
} WmIconStateRec, *WmIconState;

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _DECWmHints_h_ */

