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
 * (c) Copyright 1989, 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2
*/ 
/*   $RCSfile: DesktopP.h,v $ $Revision: 1.1.8.2 $ $Date: 1994/09/09 21:05:48 $ */
/*
*  (c) Copyright 1989, 1990  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
*  (c) Copyright 1988 MICROSOFT CORPORATION */
#ifndef  _XmDesktopP_h
#define _XmDesktopP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/ExtObjectP.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef XmIsDesktopObject
#define XmIsDesktopObject(w)	XtIsSubclass(w, xmDesktopClass)
#endif /* XmIsDesktopObject */

typedef struct _XmDesktopRec *XmDesktopObject;
typedef struct _XmDesktopClassRec *XmDesktopObjectClass;
externalref WidgetClass xmDesktopClass;


typedef struct _XmDesktopClassPart{
    WidgetClass		child_class;
    XtWidgetProc	insert_child;	  /* physically add child to parent  */
    XtWidgetProc      	delete_child;	  /* physically remove child	     */
    XtPointer		extension;
}XmDesktopClassPart, *XmDesktopClassPartPtr;

typedef struct _XmDesktopClassRec{
    ObjectClassPart		object_class;
    XmExtClassPart		ext_class;
    XmDesktopClassPart 		desktop_class;
}XmDesktopClassRec;

typedef struct {
    Widget		parent;
    Widget		*children;
    Cardinal		num_children;
    Cardinal		num_slots;
} XmDesktopPart, *XmDesktopPartPtr;

externalref XmDesktopClassRec 	xmDesktopClassRec;

typedef struct _XmDesktopRec{
    ObjectPart			object;
    XmExtPart			ext;
    XmDesktopPart		desktop;
}XmDesktopRec;


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern WidgetClass _XmGetActualClass() ;
extern void _XmSetActualClass() ;

#else

extern WidgetClass _XmGetActualClass( 
                        Display *display,
                        WidgetClass w_class) ;
extern void _XmSetActualClass( 
                        Display *display,
                        WidgetClass w_class,
                        WidgetClass actualClass) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif  /* _XmDesktopP_h */
