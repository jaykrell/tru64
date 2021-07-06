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
/*   $RCSfile: PushBP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:19:49 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
/*
*  (c) Copyright 1988 MASSACHUSETTS INSTITUTE OF TECHNOLOGY  */
/*
*  (c) Copyright 1988 MICROSOFT CORPORATION */
#ifndef _XmPButtonP_h
#define _XmPButtonP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/PushB.h>
#include <Xm/LabelP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PushButton class structure */

typedef struct _XmPushButtonClassPart
{
   XtPointer extension;   /* Pointer to extension record */
} XmPushButtonClassPart;


/* Full class record declaration for PushButton class */

typedef struct _XmPushButtonClassRec {
    CoreClassPart	  core_class;
    XmPrimitiveClassPart  primitive_class;
    XmLabelClassPart      label_class;
    XmPushButtonClassPart pushbutton_class;
} XmPushButtonClassRec;


externalref XmPushButtonClassRec xmPushButtonClassRec;

/* PushButton instance record */

typedef struct _XmPushButtonPart
{
   Boolean 	    fill_on_arm;
   Dimension        show_as_default;
   Pixel	    arm_color;
   Pixmap	    arm_pixmap;
   XtCallbackList   activate_callback;
   XtCallbackList   arm_callback;
   XtCallbackList   disarm_callback;

   Boolean 	    armed;
   Pixmap	    unarm_pixmap;
   GC               fill_gc;
   GC               background_gc;
   XtIntervalId     timer;	
   unsigned char    multiClick;		/* KEEP/DISCARD resource */
   int		    click_count;
   Time		    armTimeStamp;
   Boolean      compatible;   /* if false it is Motif 1.1 else Motif 1.0  */
   Dimension    default_button_shadow_thickness;  
		/* New resource - always add it
                    to widgets dimension. */

} XmPushButtonPart;


/* Full instance record declaration */

typedef struct _XmPushButtonRec {
    CorePart	     core;
    XmPrimitivePart  primitive;
    XmLabelPart      label;
    XmPushButtonPart pushbutton;
} XmPushButtonRec;


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern void _XmClearBCompatibility() ;

#else

extern void _XmClearBCompatibility( 
                        Widget pb) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmPButtonP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
