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
/*   $RCSfile: DrawnBP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:10:14 $ */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmDButtonP_h
#define _XmDButtonP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/DrawnB.h>
#include <Xm/LabelP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DrawnButton class structure */

typedef struct _XmDrawnButtonClassPart
{
   XtPointer extension;   /* Pointer to extension record */
} XmDrawnButtonClassPart;


/* Full class record declaration for DrawnButton class */

typedef struct _XmDrawnButtonClassRec {
    CoreClassPart	  core_class;
    XmPrimitiveClassPart  primitive_class;
    XmLabelClassPart      label_class;
    XmDrawnButtonClassPart drawnbutton_class;
} XmDrawnButtonClassRec;


externalref  XmDrawnButtonClassRec xmDrawnButtonClassRec;


/* DrawnButton instance record */

typedef struct _XmDrawnButtonPart
{
   Boolean 	    pushbutton_enabled;
   unsigned char    shadow_type;
   XtCallbackList   activate_callback;
   XtCallbackList   arm_callback;
   XtCallbackList   disarm_callback;
   XtCallbackList   expose_callback;
   XtCallbackList   resize_callback;

   Boolean 	    armed;
   Dimension        old_width;
   Dimension        old_height;
   Dimension        old_shadow_thickness;
   Dimension        old_highlight_thickness;
   XtIntervalId     timer;
   unsigned char    multiClick;         /* KEEP/DISCARD resource */
   int              click_count;
   Time		    armTimeStamp;

} XmDrawnButtonPart;


/* Full instance record declaration */

typedef struct _XmDrawnButtonRec {
    CorePart	     core;
    XmPrimitivePart  primitive;
    XmLabelPart      label;
    XmDrawnButtonPart drawnbutton;
} XmDrawnButtonRec;


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
#endif /* _XmDButtonP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
