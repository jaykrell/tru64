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
/*   $RCSfile: TextFSelP.h,v $ $Revision: 1.1.8.2 $ $Date: 1994/09/09 21:26:19 $ */
/*
*  (c) Copyright 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#ifndef _XmTextFSelP_h
#define _XmTextFSelP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/XmP.h>

#ifdef __cplusplus
extern "C" {
#endif

/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern Boolean _XmTextFieldConvert() ;
extern void _XmTextFieldLoseSelection() ;

#else

extern Boolean _XmTextFieldConvert( 
                        Widget w,
                        Atom *selection,
                        Atom *target,
                        Atom *type,
                        XtPointer *value,
                        unsigned long *length,
                        int *format) ;
extern void _XmTextFieldLoseSelection( 
                        Widget w,
                        Atom *selection) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/

#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmTextFSelP_h */
/* DON't ADD STUFF AFTER THIS #endif */
