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
 * Motif Release 1.2.2
*/ 
/*   $RCSfile: MainW.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:16:52 $ */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmMainWindow_h
#define _XmMainWindow_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XmIsMainWindow
#define XmIsMainWindow(w)	XtIsSubclass(w, xmMainWindowWidgetClass)
#endif /* XmIsMainWindow */

externalref WidgetClass xmMainWindowWidgetClass;

typedef struct _XmMainWindowClassRec * XmMainWindowWidgetClass;
typedef struct _XmMainWindowRec      * XmMainWindowWidget;


/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern void XmMainWindowSetAreas() ;
extern Widget XmMainWindowSep1() ;
extern Widget XmMainWindowSep2() ;
extern Widget XmMainWindowSep3() ;
extern Widget XmCreateMainWindow() ;

#else

extern void XmMainWindowSetAreas( 
                        Widget w,
                        Widget menu,
                        Widget command,
                        Widget hscroll,
                        Widget vscroll,
                        Widget wregion) ;
extern Widget XmMainWindowSep1( 
                        Widget w) ;
extern Widget XmMainWindowSep2( 
                        Widget w) ;
extern Widget XmMainWindowSep3( 
                        Widget w) ;
extern Widget XmCreateMainWindow( 
                        Widget parent,
                        char *name,
                        ArgList args,
                        Cardinal argCount) ;

#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmMainWindow_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
