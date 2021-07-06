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
 * @(#)$RCSfile: FCClib.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 2000/04/10 00:18:03 $
 */
#ifndef _FCCLIB_H_
#define _FCCLIB_H_

typedef void *FCCInfo;

typedef struct _FCCRec {
    char *pattern;
    char *fromcode;
    char *tocode;
    FCCInfo info;
} FCCRec, *FCC;

extern FCC XfccOpenConverter(
#if NeedFunctionPrototypes
    char*			/* filename */
#endif
);

extern void XfccCloseConverter(
#if NeedFunctionPrototypes
    FCC				/* fcc */
#endif
);

extern char *XfccConvertString(
#if NeedFunctionPrototypes
    FCC				/* fcc */,			
    char *			/* from */
#endif
);

extern char *XfccConvertNString(
#if NeedFunctionPrototypes
    FCC				/* fcc */,			
    char *			/* from */,
    size_t			/* from_len */
#endif
);

extern void XfccFreeString(
#if NeedFunctionPrototypes
    FCC				/* fcc */,
    char*			/* string */
#endif
);

extern size_t XfccConvert(
#if NeedFunctionPrototypes
    FCC				/* fcc */,
    char **			/* inbuf */,
    size_t *			/* inbytesleft */,
    char **			/* outbuf */,
    size_t *			/* outbytesleft */
#endif
);

#endif  /* _FCCLIB_H_ */
