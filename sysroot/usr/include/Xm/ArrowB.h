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
/*   $RCSfile: ArrowB.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:01:14 $ */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmArrowButton_h
#define _XmArrowButton_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XmIsArrowButton
#define XmIsArrowButton(w) XtIsSubclass(w, xmArrowButtonWidgetClass)
#endif /* XmIsArrowButton */

externalref WidgetClass xmArrowButtonWidgetClass;

typedef struct _XmArrowButtonClassRec * XmArrowButtonWidgetClass;
typedef struct _XmArrowButtonRec      * XmArrowButtonWidget;


/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern Widget XmCreateArrowButton() ;

#else

extern Widget XmCreateArrowButton( 
                        Widget parent,
                        char *name,
                        ArgList arglist,
                        Cardinal argcount) ;

#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmArrowButton_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
