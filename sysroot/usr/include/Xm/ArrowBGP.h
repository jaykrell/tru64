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
/*   $RCSfile: ArrowBGP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:01:40 $ */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmArrowGadgetP_h
#define _XmArrowGadgetP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/ArrowBG.h>
#include <Xm/GadgetP.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  Arrow class structure  */

typedef struct _XmArrowButtonGadgetClassPart
{
   XtPointer extension;
} XmArrowButtonGadgetClassPart;


/*  Full class record declaration for Arrow class  */

typedef struct _XmArrowButtonGadgetClassRec
{
   RectObjClassPart             rect_class;
   XmGadgetClassPart            gadget_class;
   XmArrowButtonGadgetClassPart arrow_button_class;
} XmArrowButtonGadgetClassRec;

externalref XmArrowButtonGadgetClassRec xmArrowButtonGadgetClassRec;

/* "Gadget caching" is currently under investigation for ArrowBG.  It would
 * be very desirable to cache the XRectangles, requiring immediate reference
 * instead of indirectly through pointers.  ArrowBG will be cached by Beta.
 */
/*  The Arrow instance record  */

typedef struct _XmArrowButtonGadgetPart
{
   XtCallbackList activate_callback;
   XtCallbackList arm_callback;
   XtCallbackList disarm_callback;
   unsigned char direction;	  /*  the direction the arrow is pointing  */

   Boolean selected;

   short        top_count;
   short        cent_count;
   short        bot_count;
   XRectangle * top;
   XRectangle * cent;
   XRectangle * bot;

   Position old_x;
   Position old_y;

   GC               arrow_GC;	    /* graphics context for arrow drawing */
   XtIntervalId     timer;	
   unsigned char    multiClick;     /* KEEP/DISCARD resource */
   int              click_count;
   GC       	    insensitive_GC; /* graphics context for insensitive arrow drawing */

} XmArrowButtonGadgetPart;


/*  Full instance record declaration  */

typedef struct _XmArrowButtonGadgetRec
{
   ObjectPart              object;
   RectObjPart             rectangle;
   XmGadgetPart            gadget;
   XmArrowButtonGadgetPart arrowbutton;
} XmArrowButtonGadgetRec;


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
#endif /* _XmArrowGadgetP_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
