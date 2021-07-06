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
/*   $RCSfile: VirtKeysP.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:30:31 $ */
/*
*  (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmVirtKeysP_h
#define _XmVirtKeysP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/XmP.h>
#include <Xm/VirtKeys.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XmKEYCODE_TAG_SIZE 32

typedef struct _XmDefaultBindingStringRec{
    String	vendorName;
    String	defaults;
}XmDefaultBindingStringRec, *XmDefaultBindingString;

typedef	struct _XmKeyBindingRec{
    KeySym		keysym;
    unsigned int	modifiers;
}XmKeyBindingRec, *XmKeyBinding;

typedef	struct _XmVirtualKeysymRec{
    String		name;
    KeySym		keysym;
}XmVirtualKeysymRec, *XmVirtualKeysym;

/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern void _XmVirtKeysInitialize() ;
extern void _XmVirtKeysDestroy() ;
extern void _XmVirtKeysHandler() ;
extern void _XmVirtualToActualKeysym() ;
extern void _XmVirtKeysStoreBindings() ;
extern Boolean _XmVirtKeysLoadFileBindings() ;
extern int _XmVirtKeysLoadFallbackBindings() ;

#else

extern void _XmVirtKeysInitialize( 
                        Widget widget) ;
extern void _XmVirtKeysDestroy( 
                        Widget widget) ;
extern void _XmVirtKeysHandler( 
                        Widget widget,
                        XtPointer client_data,
                        XEvent *event,
                        Boolean *dontSwallow) ;
extern void _XmVirtualToActualKeysym( 
                        Display *dpy,
                        KeySym virtKeysym,
                        KeySym *actualKeysymRtn,
                        Modifiers *modifiersRtn) ;
extern void _XmVirtKeysStoreBindings( 
                        Widget shell,
                        String binding) ;
extern Boolean _XmVirtKeysLoadFileBindings( 
                        char *fileName,
                        String *binding) ;
extern int _XmVirtKeysLoadFallbackBindings(
			Display *display,
			String *binding) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmVirtKeysP_h */
