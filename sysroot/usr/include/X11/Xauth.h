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
 * @(#)$RCSfile: Xauth.h,v $ $Revision: 1.1.3.5 $ (DEC) $Date: 2000/06/21 22:04:24 $
 */
/* $TOG: Xauth.h /main/19 1998/02/06 14:15:45 kaleb $ */

/*

Copyright 1988, 1998  The Open Group

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

*/

#ifndef _Xauth_h
#define _Xauth_h

typedef struct xauth {
    unsigned short   family;
    unsigned short   address_length;
    char    	    *address;
    unsigned short   number_length;
    char    	    *number;
    unsigned short   name_length;
    char    	    *name;
    unsigned short   data_length;
    char   	    *data;
} Xauth;

#ifndef _XAUTH_STRUCT_ONLY

# include   <X11/Xfuncproto.h>
# include   <X11/Xfuncs.h>

# include   <stdio.h>

# define FamilyLocal (256)	/* not part of X standard (i.e. X.h) */
# define FamilyWild  (65535)
# define FamilyNetname    (254)   /* not part of X standard */
# define FamilyKrb5Principal (253) /* Kerberos 5 principal name */
# define FamilyLocalHost (252)	/* for local non-net authentication */


_XFUNCPROTOBEGIN

char *XauFileName();

Xauth *XauReadAuth(
#if NeedFunctionPrototypes
FILE*	/* auth_file */
#endif
);

int XauLockAuth(
#if NeedFunctionPrototypes
_Xconst char*	/* file_name */,
int		/* retries */,
int		/* timeout */,
long		/* dead */
#endif
);

int XauUnlockAuth(
#if NeedFunctionPrototypes
_Xconst char*	/* file_name */
#endif
);

int XauWriteAuth(
#if NeedFunctionPrototypes
FILE*		/* auth_file */,
Xauth*		/* auth */
#endif
);

Xauth *XauGetAuthByName(
#if NeedFunctionPrototypes
_Xconst char*	/* display_name */
#endif
);

Xauth *XauGetAuthByAddr(
#if NeedFunctionPrototypes
#if NeedWidePrototypes
unsigned int	/* family */,
unsigned int	/* address_length */,
#else
unsigned short	/* family */,
unsigned short	/* address_length */,
#endif
_Xconst char*	/* address */,
#if NeedWidePrototypes
unsigned int	/* number_length */,
#else
unsigned short	/* number_length */,
#endif
_Xconst char*	/* number */,
#if NeedWidePrototypes
unsigned int	/* name_length */,
#else
unsigned short	/* name_length */,
#endif
_Xconst char*	/* name */
#endif
);

Xauth *XauGetBestAuthByAddr(
#if NeedFunctionPrototypes
#if NeedWidePrototypes
unsigned int	/* family */,
unsigned int	/* address_length */,
#else
unsigned short	/* family */,
unsigned short	/* address_length */,
#endif
_Xconst char*	/* address */,
#if NeedWidePrototypes
unsigned int	/* number_length */,
#else
unsigned short	/* number_length */,
#endif
_Xconst char*	/* number */,
int		/* types_length */,
char**		/* type_names */,
_Xconst int*	/* type_lengths */
#endif
);

void XauDisposeAuth(
#if NeedFunctionPrototypes
Xauth*		/* auth */
#endif
);

#ifdef K5AUTH
#include <krb5/krb5.h>
/* 9/93: krb5.h leaks some symbols */
#undef BITS32
#ifndef NO_DEC_BUG_FIX
#undef BITS64
#endif
#undef xfree

int XauKrb5Encode(
#if NeedFunctionPrototypes
     krb5_principal	/* princ */,
     krb5_data *	/* outbuf */
#endif
);

int XauKrb5Decode(
#if NeedFunctionPrototypes
     krb5_data		/* inbuf */,
     krb5_principal *	/* princ */
#endif
);
#endif /* K5AUTH */

_XFUNCPROTOEND

/* Return values from XauLockAuth */

# define LOCK_SUCCESS	0	/* lock succeeded */
# define LOCK_ERROR	1	/* lock unexpectely failed, check errno */
# define LOCK_TIMEOUT	2	/* lock failed, timeouts expired */

#endif /* _XAUTH_STRUCT_ONLY */

#endif /* _Xauth_h */
