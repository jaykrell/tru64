/*
* $TOG: TextSrcP.h /main/21 1998/02/06 12:51:38 kaleb $
*/


/***********************************************************

Copyright 1987, 1988, 1994, 1998  The Open Group

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/* 
 * TextSrcP.h - Private definitions for TextSrc object
 * 
 */

#ifndef _XawTextSrcP_h
#define _XawTextSrcP_h

/***********************************************************************
 *
 * TextSrc Object Private Data
 *
 ***********************************************************************/

#include <X11/Xaw/TextSrc.h>
#include <X11/Xaw/TextP.h>	/* This source works with the Text widget. */

/************************************************************
 *
 * New fields for the TextSrc object class record.
 *
 ************************************************************/

typedef struct {
  XtPointer		next_extension;
  XrmQuark		record_type;
  long			version;
  Cardinal		record_size;
  int			(*Input)();
} TextSrcExtRec, *TextSrcExt;

typedef struct _TextSrcClassPart {
  XawTextPosition	(*Read)();
  int			(*Replace)();
  XawTextPosition	(*Scan)();
  XawTextPosition       (*Search)();
  void                  (*SetSelection)();
  Boolean		(*ConvertSelection)();
} TextSrcClassPart;

/* Full class record declaration */
typedef struct _TextSrcClassRec {
    ObjectClassPart     object_class;
    TextSrcClassPart	textSrc_class;
} TextSrcClassRec;

extern TextSrcClassRec textSrcClassRec;

/* New fields for the TextSrc object record */
typedef struct {
    /* resources */
  XawTextEditType	edit_mode;
  XrmQuark		text_format;	/* 2 formats: FMT8BIT for Ascii */
					/*            FMTWIDE for ISO 10646 */
} TextSrcPart;

/****************************************************************
 *
 * Full instance record declaration
 *
 ****************************************************************/

typedef struct _TextSrcRec {
  ObjectPart    object;
  TextSrcPart	textSrc;
} TextSrcRec;

/******************************************************************
 *
 * Semiprivate declarations of functions used in other modules
 *
 ******************************************************************/

char* _XawTextWCToMB(
#if NeedFunctionPrototypes
    Display* /* d */,
    wchar_t* /* wstr */,
    int*     /* len_in_out */
#endif
);

wchar_t* _XawTextMBToWC(
#if NeedFunctionPrototypes
    Display*  /* d */,
    char*     /* str */,
    int*      /* len_in_out */
#endif
);

/************************************************************
 *
 * Private declarations.
 *
 ************************************************************/

typedef Boolean (*_XawBooleanFunc)();
typedef int (*_XawIntFunc)();
typedef XawTextPosition (*_XawTextPositionFunc)();
typedef void (*_XawTextVoidFunc)();

#define XtInheritInput                ((_XawTextPositionFunc) _XtInherit)
#define XtInheritRead                 ((_XawTextPositionFunc) _XtInherit)
#define XtInheritReplace              ((_XawIntFunc) _XtInherit)
#define XtInheritScan                 ((_XawTextPositionFunc) _XtInherit)
#define XtInheritSearch               ((_XawTextPositionFunc) _XtInherit)
#define XtInheritSetSelection         ((_XawTextVoidFunc) _XtInherit)
#define XtInheritConvertSelection     ((_XawBooleanFunc) _XtInherit)
#define XtTextSrcExtVersion	      1
#define XtTextSrcExtTypeString        "XT_TEXTSRC_EXT"

#endif /* _XawTextSrcP_h */
