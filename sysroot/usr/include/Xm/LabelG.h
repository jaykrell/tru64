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
/*   $RCSfile: LabelG.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:15:29 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmLabelG_h
#define _XmLabelG_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  Widget class and record definitions  */


externalref WidgetClass xmLabelGadgetClass;

typedef struct _XmLabelGadgetClassRec * XmLabelGadgetClass;
typedef struct _XmLabelGadgetRec      * XmLabelGadget;
typedef struct _XmLabelGCacheObjRec   * XmLabelGCacheObject;

/*fast subclass define */
#ifndef XmIsLabelGadget
#define XmIsLabelGadget(w)     XtIsSubclass(w, xmLabelGadgetClass)
#endif /* XmIsLabelGadget */


/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern Widget XmCreateLabelGadget() ;

#else

extern Widget XmCreateLabelGadget( 
                        Widget parent,
                        char *name,
                        Arg *arglist,
                        Cardinal argCount) ;

#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmLabelG_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
