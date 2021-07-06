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
 * @(#)$RCSfile: XKBlibint.h,v $ $Revision: 1.1.3.17 $ (DEC) $Date: 2000/06/21 22:03:38 $
 */
/* $TOG: XKBlibint.h /main/15 1997/06/10 06:53:27 kaleb $ */
/************************************************************
Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of Silicon Graphics not be 
used in advertising or publicity pertaining to distribution 
of the software without specific prior written permission.
Silicon Graphics makes no representation about the suitability 
of this software for any purpose. It is provided "as is"
without any express or implied warranty.

SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

#ifndef _XKBLIBINT_H_
#define	_XKBLIBINT_H_

#include <X11/Xutil.h>
#include <X11/XKBlib.h>

#define	XkbMapPending		(1<<0)
#define	XkbXlibNewKeyboard	(1<<1)

typedef int	(*XkbKSToMBFunc)(
#if NeedFunctionPrototypes
	XPointer	/* priv */,
	KeySym		/* sym */,
	char *		/* buf */,
	int		/* len */,
	int *		/* extra_rtrn */
#endif
);

typedef KeySym	(*XkbMBToKSFunc)(
#if NeedFunctionPrototypes
	XPointer	/* priv */,
	char *		/* buf */,
	int		/* len */,
	Status *	/* status */
#endif
);

typedef KeySym	(*XkbToUpperFunc)(
#if NeedFunctionPrototypes
	KeySym		/* sym */
#endif
);

typedef struct _XkbConverters {
	XkbKSToMBFunc	 KSToMB;
	XPointer	 KSToMBPriv;
	XkbMBToKSFunc	 MBToKS;
	XPointer	 MBToKSPriv;
	XkbToUpperFunc	 KSToUpper;
} XkbConverters;

extern	XkbInternAtomFunc	_XkbInternAtomFunc;
extern	XkbGetAtomNameFunc	_XkbGetAtomNameFunc;

typedef struct _XkbInfoRec {
	unsigned	 flags;
	unsigned	 xlib_ctrls;
	XExtCodes	 *codes;
	int		 srv_major;
	int		 srv_minor;
	unsigned	 selected_events;
	unsigned short	 selected_nkn_details;
	unsigned short	 selected_map_details;
	XkbDescRec	*desc;
	XkbMapChangesRec changes;
	Atom		 composeLED;
	XkbConverters	 cvt;
	XkbConverters	 latin1cvt;
} XkbInfoRec, *XkbInfoPtr;


#define	_XkbUnavailable(d) \
	(((d)->flags&XlibDisplayNoXkb) ||\
	 ((!(d)->xkb_info || (!(d)->xkb_info->desc)) && !_XkbLoadDpy(d)))

#define	_XkbCheckPendingRefresh(d,xi) {\
    if ((xi)->flags&XkbXlibNewKeyboard)\
	_XkbReloadDpy((d));\
    else if ((xi)->flags&XkbMapPending) {\
	if (XkbGetMapChanges((d),(xi)->desc, &(xi)->changes)==Success) {\
	    LockDisplay((d));\
	    (xi)->changes.changed= 0;\
	    UnlockDisplay((d));\
	}\
    }\
}

#define	_XkbNeedModmap(i)    ((!(i)->desc->map)||(!(i)->desc->map->modmap))

	/*
	 * mask of the events that the "invisible" XKB support in Xlib needs
	 */
#define XKB_XLIB_MAP_MASK (XkbAllClientInfoMask)

	/*
	 * Handy helper macros 
	 */
#define	XKB_INSURE_SIZE(f,t,nNum,oNum)	{\
	if ((f)==NULL)	\
	     (f)=(t *)Xmalloc(sizeof(t)*(nNum));\
	else if ((nNum)<(oNum))\
	     (f)=(t *)Xrealloc((f),sizeof(t)*(nNum));\
	}

typedef struct _XkbReadBuffer {
	int	 error;
	int	 size;
	char	*start;
	char	*data;
} XkbReadBufferRec,*XkbReadBufferPtr;

#define	_XkbAlloc(s)		Xmalloc((s))
#define	_XkbCalloc(n,s)		Xcalloc((n),(s))
#define	_XkbRealloc(o,s)	Xrealloc((o),(s))
#define	_XkbTypedAlloc(t)	((t *)Xmalloc(sizeof(t)))
#define	_XkbTypedCalloc(n,t)	((t *)Xcalloc((n),sizeof(t)))
#define	_XkbTypedRealloc(o,n,t) \
	((o)?(t *)Xrealloc((o),(n)*sizeof(t)):_XkbTypedCalloc(n,t))
#define	_XkbClearElems(a,f,l,t)	bzero(&(a)[f],((l)-(f)+1)*sizeof(t))
#define	_XkbFree(p)		Xfree(p)

_XFUNCPROTOBEGIN

extern	void _XkbReloadDpy(
#if NeedFunctionPrototypes
    Display *		/* dpy */
#endif
);

extern KeySym _XKeycodeToKeysym(
#if NeedFunctionPrototypes
    Display*		/* display */,
    KeyCode		/* keycode */,
    int			/* index */
#endif
);

extern KeyCode _XKeysymToKeycode(
#if NeedFunctionPrototypes
    Display*		/* display */,
    KeySym		/* keysym */
#endif
);

extern KeySym _XLookupKeysym(
#if NeedFunctionPrototypes
    XKeyEvent*		/* key_event */,
    int			/* index */
#endif
);

extern int _XRefreshKeyboardMapping(
#if NeedFunctionPrototypes
    XMappingEvent*	/* event_map */    
#endif
);

extern unsigned	_XKeysymToModifiers(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    KeySym 		/* ks */
#endif
);

extern int _XTranslateKey(	
#if NeedFunctionPrototypes
    register Display *	/* dpy */,
    KeyCode 		/* keycode */,
    register unsigned int /* modifiers */,
    unsigned int *	/* modifiers_return */,
    KeySym *		/* keysym_return */
#ifndef NO_DEC_COMPOSE_SUPPORT
    ,KeySym *, KeySym *
#endif
#endif
);

extern int	_XTranslateKeySym(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    register KeySym 	/* symbol */,
#ifndef NO_DEC_COMPOSE_SUPPORT
    KeySym, KeySym, 
#endif
    unsigned int 	/* modifiers */,
    char *		/* buffer */,
    int 		/* nbytes */
#endif
);

extern	int _XLookupString(
#if NeedFunctionPrototypes
    register XKeyEvent *	/* event */,
    char *			/* buffer */,
    int 			/* nbytes */,
    KeySym *			/* keysym */,
    XComposeStatus *		/* status */
#endif
);

extern void _XkbNoteCoreMapChanges(
#if NeedFunctionPrototypes
    XkbMapChangesRec * 		/* old */,
    XMappingEvent * 		/* new */,
    unsigned int 		/* wanted */
#endif
);

extern	int _XkbInitReadBuffer(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    XkbReadBufferPtr	/* buf */,
    int			/* size */
#endif
);

extern int _XkbSkipReadBufferData(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
    int			/* size */
#endif
);

extern int _XkbCopyFromReadBuffer(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
    char *		/* to */,
    int			/* size */
#endif
);


#if defined(WORD64) || defined(LONG64)
extern	int _XkbReadCopyData32(
#if NeedFunctionPrototypes
    int *		/* from */,
    long *		/* to */,
    int			/* num_words */
#endif
);

extern	int _XkbWriteCopyData32(
#if NeedFunctionPrototypes
    unsigned long *	/* from */,
    CARD32 *		/* to */,
    int			/* num_words */
#endif
);

extern int _XkbReadBufferCopy32(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
    long *		/* to */,
    int			/* size */
#endif
);
#else
#define	_XkbReadCopyData32(f,t,s)    memcpy((char *)(t),(char *)(f),(s)*4)
#define	_XkbWriteCopyData32(f,t,s)   memcpy((char *)(t),(char *)(f),(s)*4)
#define	_XkbReadBufferCopy32(f,t,s) _XkbCopyFromReadBuffer(f,(char *)t,(s)*4)
#endif

#ifndef NO_DEC_BINARY_COMPATIBILITY
#define XKB_FORCE_INT_KEYSYM 1
#endif

#ifdef XKB_FORCE_INT_KEYSYM
extern int _XkbReadCopyKeySyms(
#if NeedFunctionPrototypes
    int *		/* from */,
    KeySym *		/* to */,
    int			/* num_words */
#endif
);

extern	int _XkbWriteCopyKeySyms(
#if NeedFunctionPrototypes
    KeySym *		/* from */,
    CARD32 *		/* to */,
    int			/* num_words */
#endif
);

extern int _XkbReadBufferCopyKeySyms(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
#ifndef NO_DEC_BUG_FIX
    KeySym *		/* to */,
#else
    long *		/* to */,
#endif
    int			/* size */
#endif
);
#else
#define	_XkbReadCopyKeySyms(f,t,n)		_XkbReadCopyData32(f,t,n)
#define	_XkbWriteCopyKeySyms(f,t,n)		_XkbWriteCopyData32(f,t,n)
#define	_XkbReadBufferCopyKeySyms(f,t,s)	_XkbReadBufferCopy32(f,t,s)
#endif

extern char *_XkbPeekAtReadBuffer(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
    int			/*  size */
#endif
);

extern char *_XkbGetReadBufferPtr(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* from */,
    int			/* size */
#endif
);
#define	_XkbGetTypedRdBufPtr(b,n,t) ((t *)_XkbGetReadBufferPtr(b,(n)*SIZEOF(t)))

extern int _XkbFreeReadBuffer(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* buf */
#endif
);

extern Bool
_XkbGetReadBufferCountedString(
#if NeedFunctionPrototypes
    XkbReadBufferPtr	/* buf */,
    char **		/* rtrn */
#endif
);

extern char	*_XkbGetCharset(
#if NeedFunctionPrototypes
    void
#endif
);

extern int	 _XkbGetConverters(
#if NeedFunctionPrototypes
    char *		/* encoding_name */,
    XkbConverters *	/* cvt_rtrn */
#endif
);

#ifdef	NEED_MAP_READERS

extern	Status	_XkbReadGetMapReply(
#if NeedFunctionPrototypes
    Display *		/* dpy */,
    xkbGetMapReply * 	/* rep */,
    XkbDescRec *	/* xkb */,
    int *		/* nread_rtrn */
#endif
);

extern	Status	_XkbReadGetCompatMapReply(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    xkbGetCompatMapReply *	/* rep */,
    XkbDescPtr			/* xkb */,
    int	*			/* nread_rtrn */
#endif
);

extern	Status	_XkbReadGetIndicatorMapReply(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    xkbGetIndicatorMapReply *	/* rep */,
    XkbDescPtr			/* xkb */,
    int	*			/* nread_rtrn */
#endif
);

extern	Status	_XkbReadGetNamesReply(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    xkbGetNamesReply *		/* rep */,
    XkbDescPtr 			/* xkb */,
    int *			/* nread_rtrn */
#endif
);

extern	Status	_XkbReadGetGeometryReply(
#if NeedFunctionPrototypes
    Display *			/* dpy */,
    xkbGetGeometryReply *	/* rep */,
    XkbDescPtr 			/* xkb */,
    int *			/* nread_rtrn */
#endif
);

#endif

_XFUNCPROTOEND

#endif /* _XKBLIBINT_H_ */
