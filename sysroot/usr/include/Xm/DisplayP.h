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
/*   $RCSfile: DisplayP.h,v $ $Revision: 1.1.15.2 $ $Date: 1999/07/22 17:30:56 $ */
/*
*  (c) Copyright 1989, 1990  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
*  (c) Copyright 1988 MICROSOFT CORPORATION */
#ifndef _XmDisplayP_h
#define _XmDisplayP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/DesktopP.h>
#include <Xm/VendorSEP.h>
#include <Xm/DropSMgr.h>
#include <Xm/Display.h>
#include <Xm/ScreenP.h>

/* A little incest */
#include <Xm/DragCP.h>
#include <Xm/VirtKeysP.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _NO_PROTO
typedef Widget (*XmDisplayGetDisplayProc)();
#else
typedef Widget (*XmDisplayGetDisplayProc)
	(Display *);
#endif


typedef struct {
	XmDisplayGetDisplayProc GetDisplay;
    XtPointer               extension;
} XmDisplayClassPart;

/* 
 * we make it a appShell subclass so it can have it's own instance
 * hierarchy
 */
typedef struct _XmDisplayClassRec{
    CoreClassPart      		core_class;
    CompositeClassPart 		composite_class;
    ShellClassPart  		shell_class;
    WMShellClassPart   		wm_shell_class;
    VendorShellClassPart 	vendor_shell_class;
    TopLevelShellClassPart 	top_level_shell_class;
    ApplicationShellClassPart 	application_shell_class;
    XmDisplayClassPart		display_class;
}XmDisplayClassRec;

typedef struct _XmModalDataRec{
    Widget                      wid;
    XmVendorShellExtObject	ve;
    XmVendorShellExtObject	grabber;
    Boolean			exclusive;
    Boolean			springLoaded;
}XmModalDataRec, *XmModalData;

typedef struct {
    unsigned char		dragInitiatorProtocolStyle;
    unsigned char		dragReceiverProtocolStyle;

    unsigned char		userGrabbed; /* flag for menu vs dnd */

    WidgetClass			dragContextClass;
    WidgetClass			dropTransferClass;
    WidgetClass			dropSiteManagerClass;
    XmDragContext		activeDC;
    XmDropSiteManagerObject	dsm;
    Time			lastDragTime;
    Window			proxyWindow;

    XmModalData			modals;
    Cardinal			numModals;
    Cardinal			maxModals;
    XtPointer			xmim_info;

    String			bindingsString;
    XmKeyBindingRec		*bindings;
    XKeyEvent			*lastKeyEvent;
    unsigned char		keycode_tag[XmKEYCODE_TAG_SIZE];

    int				shellCount;
    XtPointer			displayInfo;	/* extension */
} XmDisplayPart, *XmDisplayPartPtr;

typedef struct _XmDisplayInfo {
	/* so much for information hiding */
	Cursor		SashCursor;		/* Sash.c */
	Widget		destinationWidget;	/* Dest.c */
	Cursor		TearOffCursor;		/* TearOff.c */
	XtPointer	UniqueStamp;		/* UniqueEvnt.c */
#ifdef DEC_MOTIF_BUG_FIX
/*
 * QAR# 73305 - Part 1 of 10
 * We need to store the toggle button check pixmaps on a per display basis.
 * They were previously being stored statically in the "DrawCheck" function.
 * The problem with that approach is that after a display was closed the
 * static variables were not cleared.  If another display was opened within
 * the same application then the static variables contained invalid pixmaps.
 * This lead to invalid pixmap errors from the X Server.
 */
	Pixmap          ToggleBCheckPixmaps[4];  /* ToggleB.c */
#endif
} XmDisplayInfo;

typedef struct _XmDisplayRec{
    CorePart 		core;
    CompositePart 	composite;
    ShellPart 		shell;
    WMShellPart		wm;
    VendorShellPart	vendor;
    TopLevelShellPart 	topLevel;
    ApplicationShellPart application;
    XmDisplayPart	display;
}XmDisplayRec;

externalref XmDisplayClassRec 	xmDisplayClassRec;

externalref String _Xm_MOTIF_DRAG_AND_DROP_MESSAGE ;

/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern XmDropSiteManagerObject _XmGetDropSiteManagerObject() ;
extern unsigned char _XmGetDragProtocolStyle() ;
extern unsigned char _XmGetDragTrackingMode() ;
extern Widget _XmGetDragContextFromHandle() ;
extern WidgetClass _XmGetXmDisplayClass() ;
extern WidgetClass _XmSetXmDisplayClass() ;

#else

extern XmDropSiteManagerObject _XmGetDropSiteManagerObject( 
                        XmDisplay xmDisplay) ;
extern unsigned char _XmGetDragProtocolStyle( 
                        Widget w) ;
extern unsigned char _XmGetDragTrackingMode( 
                        Widget w) ;
extern Widget _XmGetDragContextFromHandle( 
                        Widget w,
                        Atom iccHandle) ;
extern WidgetClass _XmGetXmDisplayClass( void ) ;
extern WidgetClass _XmSetXmDisplayClass( 
                        WidgetClass wc) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmDisplayP_h */
/* DON'T ADD STUFF AFTER THIS #endif */
