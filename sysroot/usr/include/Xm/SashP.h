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
/*   $RCSfile: SashP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:21:52 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
 *  SashP.h - Private definitions for Sash widget (Used by VPane Widget)
 *
 */

#ifndef _XmSashP_h
#define _XmSashP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/PrimitiveP.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *
 * Sash Widget Private Data
 *
 *****************************************************************************/

/* New fields for the Sash widget class record */
typedef struct {
   XtPointer extension;   /* Pointer to extension record */
} XmSashClassPart;

/* Full Class record declaration */
typedef struct _XmSashClassRec {
    CoreClassPart         core_class;
    XmPrimitiveClassPart  primitive_class;
    XmSashClassPart    sash_class;
} XmSashClassRec;

typedef struct _XmSashClassRec *XmSashWidgetClass;

externalref XmSashClassRec xmSashClassRec;

/* New fields for the Sash widget record */
typedef struct {
  XtCallbackList sash_action;
  Boolean has_focus;
} XmSashPart;

/*****************************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************************/

typedef struct _XmSashRec {
   CorePart         core;
   XmPrimitivePart  primitive;
   XmSashPart       sash;
} XmSashRec;

typedef struct _XmSashRec      *XmSashWidget;

typedef struct {
  XEvent *event;		/* the event causing the SashAction */
  String *params;		/* the TranslationTable params */
  Cardinal num_params;		/* count of params */
} SashCallDataRec, *SashCallData;

/* Class Record Constant */

externalref WidgetClass xmSashWidgetClass;

#ifndef XmIsSash
#define XmIsSash(w)	XtIsSubclass(w, xmSashWidgetClass)
#endif /* XmIsSash */


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
#endif /* _XmSashP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
