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
/*   $RCSfile: TearOffBP.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:24:38 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
 *  TearOffBP.h - Private definitions for TearOffButton widget 
 *  (Used by RowColumn Tear Off Menupanes)
 *
 */

#ifndef _XmTearOffBP_h
#define _XmTearOffBP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/PushBP.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *
 * TearOffButton Widget Private Data
 *
 *****************************************************************************/

/* New fields for the TearOffButton widget class record */
typedef struct _XmTearOffButtonClassPart
{
    String translations;
} XmTearOffButtonClassPart;

/* Full Class record declaration */
typedef struct _XmTearOffButtonClassRec {
    CoreClassPart         core_class;
    XmPrimitiveClassPart  primitive_class;
    XmLabelClassPart      label_class;
    XmPushButtonClassPart pushbutton_class;
    XmTearOffButtonClassPart    tearoffbutton_class;
} XmTearOffButtonClassRec;

typedef struct _XmTearOffButtonClassRec *XmTearOffButtonWidgetClass;

externalref XmTearOffButtonClassRec xmTearOffButtonClassRec;

/* New fields for the TearOffButton widget record */
typedef struct {
   Dimension      margin;
   unsigned char  orientation;
   unsigned char separator_type;
   GC separator_GC;
} XmTearOffButtonPart;

/*****************************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************************/

typedef struct _XmTearOffButtonRec {
   CorePart         core;
   XmPrimitivePart  primitive;
   XmLabelPart      label;
   XmPushButtonPart pushbutton;
   XmTearOffButtonPart tear_off_button;
} XmTearOffButtonRec;

typedef struct _XmTearOffButtonRec      *XmTearOffButtonWidget;

/* Class Record Constant */

externalref WidgetClass xmTearOffButtonWidgetClass;

#ifndef XmIsTearOffButton
#define XmIsTearOffButton(w)	XtIsSubclass(w, xmTearOffButtonWidgetClass)
#endif /* XmIsTearOffButton */


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO


#else


#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmTearOffButtonP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
