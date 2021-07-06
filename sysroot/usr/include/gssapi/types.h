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
 * @(#)$RCSfile: types.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:52 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     types.h~5:H:3 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

============================================================================*/



#ifndef _GSS_TYPES_H_
#   define _GSS_TYPES_H_

    /* 
        The GSS code requires types that define 16 and 32 bit quantities.  
        The next block of stuff creates those types.  They are 
        conditionalized using unsigned integer quantities.  Seems like 
        a good, tricky way of determining those types.
    */ 



    /* The GSS-API preferred preprocessor name for host types 
        are the host type prefixed and suffixed by "__".  Some 
        host preprocessors don't define those types.  Define 
        them here. */



    /* HP's ANSI compiler doesn't define __ANSI__. */
#   if defined(__hpux) && defined(__STDC__) && !defined(__ANSI__)
#       define __ANSI__
#   endif



    /* Make sure the types in sys/types.h 
        get defined under HP/UX ANSI. */
#   if defined(__hpux) && defined(__ANSI__) && !defined(_HPUX_SOURCE)
#       define _HPUX_SOURCE
#   endif



#   include    <limits.h>



#   if (defined(__mvs) || defined(__mvscics)) && !defined(__I370__) &&\
            defined(__ibm_tcpip)
#       ifndef __TYPES_RPC_HEADER__
#           include    <bsdtypes.h>
#           define __TYPES_RPC_HEADER__
#       endif  /* turn off IBM TCP/IP types.h */
#   else
#      include    <sys/types.h>
#   endif



#   if !defined(_WINDOWS) && !defined(_WIN32) && !defined(WIN32)
#       include    <sys/time.h>
#   endif



#   if defined(__STDC__) || defined(__ANSI__) || defined(__cplusplus) || defined(POSIX)
#       define _MODERN_COMPILER_
#   endif



#   if (defined(_WINDOWS) || defined(_WIN32) || defined(WIN32) || \
            defined(__mvs) || defined(__mvscics)) && !defined(_MODERN_COMPILER_)
#       define _MODERN_COMPILER_
#   endif



#   if defined(_MODERN_COMPILER_)
#       include    <stddef.h>
#   endif



    /* The GSS-API uses a common name for various types such as 
        u_char for "unsigned char."  Some operating systems define 
        those types in the system types file.  Other in other 
        files.  Still others not at all.  Make sure they are defined 
        here since they are used here. */

#   if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)
#       include <windows.h>
#       include <stdlib.h>
#       if !defined (_WINSOCKAPI_)
            typedef unsigned int    u_int;
            typedef unsigned long   u_long;
            typedef unsigned short  u_short;
            typedef unsigned char   u_char;
#       endif
#   endif



    /* Figure out whether this compiler 
        understands the unsigned suffix (e.g., 123u). */
#   if defined(_MODERN_COMPILER_)
#       define _UNDERSTANDS_UNSIGNED_
#   endif



    /* The SunOS C compiler does not understand the unsigned 
        suffix but the Solaris compiler does. One will complain 
        if the unsigned suffix is used while the other will 
        complain if the unsigned suffix is not used. The problem 
        is there is no method to distinguish between the two Sun 
        operating systems. On Solaris add -D__solaris to your 
        compile line and all will be well. */
#   if defined(__solaris) && !defined(_UNDERSTANDS_UNSIGNED_)
#       define _UNDERSTANDS_UNSIGNED_
#   endif



    /* Figure out the size of integers and 
        define the GSS 16 and 32 bit types.  */
#   define I32T    2147483647
#   define I16T    32767



    /* Define too either _BIG_INTS_ or _SMALL_INTS_. 
        Those definitions are used to format 
        printf() strings. With _BIG_INTS_ a i_32 
        passed to printf() is assumed to be printable 
        using %d. When _SMALL_INTS_ is defined the 
        printf() format required is %ld. */
#   if ( I32T - INT_MAX ) == 0
#       define u_32    u_int
#       define i_32    int
#       define _BIG_INTS_
#   else
#       if ( I32T - LONG_MAX ) == 0
#           define u_32    u_long
#           define i_32    long
#           define _SMALL_INTS_
#       else
            /* #error: Need a 32 bit integer definition */
#       endif
#   endif



#   if ( I16T - SHRT_MAX ) == 0
#       define u_16    u_short
#       define i_16    short
#   else
#       if ( I16T - INT_MAX ) == 0
#           define u_32    u_int
#           define i_16    int
#       else
            /* #error: Need a 16 bit integer definition */
#       endif
#   endif



    /* Modern compilers support prototypes. */
#   if defined(_MODERN_COMPILER_)
#       define _GSS_PROTO(proto)   proto
#   else
#       define _GSS_PROTO(proto)   ()
#   endif



    /* Some not-modern compilers understand void and 
        volatile but not const.  Special const case. */   
#   if defined(_MODERN_COMPILER_)
#       ifndef CONST
#           define CONST   const
#       endif
#   else
#       define CONST
#   endif



    /* Windows function prototypes 
        require declaration modifiers. */
#   if defined(_WINDOWS) || defined(_WIN32) || defined(WIN32)
#       include <winsock.h>
#       if defined(WIN32) && (_MSC_VER >= 800)
#           define CSFAPI  __stdcall
#           if defined( CSFAPIV )
#               undef CSFAPIV
#           endif
#           define CSFAPIV __stdcall
#       else
#           ifndef FAR
#               define FAR     _far
#           endif
#           define CSFAPI  _pascal
#           define CSFAPIV _cdecl
#       endif
#   endif



#   ifndef FAR
#       define FAR
#   endif
#   ifndef CSFAPI
#       define CSFAPI
#   endif
#   ifndef CSFAPIV
#       define CSFAPIV
#   endif



    /* Generate an error if a system type is not defined. */
#   if !defined(__sunos) && !defined(__solaris) && !defined(__hpux) && \
            !defined(_AIX) && !defined(__irix) && !defined(__linux) && \
            !defined(__mvs) && !defined(__mvscics) && \
            !defined(_WINDOWS) && !defined(_WIN32) && !defined(WIN32)
        error: the system type is undefined
#   endif



#endif /* _GSS_TYPES_H_ */ 
