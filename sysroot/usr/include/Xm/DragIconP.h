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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2.3
*/ 
/*   $RCSfile: DragIconP.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:08:45 $ */
/*
*  (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#ifndef _XmDragIconP_h
#define _XmDragIconP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/VendorSEP.h>
#include <Xm/DragIcon.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _NO_PROTO
typedef void 	(*XmCloneVisualProc)();
typedef void 	(*XmMovePixmapProc)();
#else
typedef void (*XmCloneVisualProc)
	(XmDragIconObject, Widget, Widget);
typedef void (*XmMovePixmapProc)
     (XmDragIconObject, XmDragIconObject, XmDragIconObject,
#if NeedWidePrototypes
      int, int);
#else
      Position, Position);
#endif /* NeedWidePrototypes */
#endif /* _NO_PROTO */

typedef struct {
	XtPointer		extension;
} XmDragIconClassPart;

typedef struct _XmDragIconClassRec{
    RectObjClassPart		rectangle_class;
    XmDragIconClassPart		dragIcon_class;
}XmDragIconClassRec;

typedef struct {
    Cardinal	depth;
    Pixmap	pixmap;
    Dimension	width, height;
    Pixmap	mask;
    Position	hot_x, hot_y;
    Position	offset_x, offset_y;
    unsigned char	attachment;
    Boolean	isDirty;
    Region      region;
    Region      restore_region;
    Position	x_offset, y_offset;
} XmDragIconPart, *XmDragIconPartPtr;

externalref XmDragIconClassRec 	xmDragIconClassRec;

typedef struct _XmDragIconRec{
    ObjectPart			object;
    RectObjPart			rectangle;
    XmDragIconPart		drag;
}XmDragIconRec;

/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern void _XmDestroyDefaultDragIcon() ;
extern Boolean _XmDragIconIsDirty() ;
extern void _XmDragIconClean() ;
extern Widget _XmGetTextualDragIcon() ;

#else

extern void _XmDestroyDefaultDragIcon(
			XmDragIconObject icon) ;
extern Boolean _XmDragIconIsDirty(
			XmDragIconObject icon) ;
extern void _XmDragIconClean(
			XmDragIconObject icon1,
			XmDragIconObject icon2,
			XmDragIconObject icon3) ;
extern Widget _XmGetTextualDragIcon(
			Widget w) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmDragIconP_h */
