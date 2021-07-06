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
 * @(#)$RCSfile: compat.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:29 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     compat.h~11.2:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file contains constants, declarations, environment 
        compilation conditionals, and all sorts of other nasty, ugly 
        stuff so not to clutter the remainder of the GSS-API source.  
        This file is tailored for C compilation environments.

============================================================================*/



#ifndef _GSS_COMPAT_H_
#define _GSS_COMPAT_H_


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
            defined(__ibm_tcpip) && (__COMPILER_VER__ < 0x20000000)
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
            defined(_AIX) || defined(__digital) || defined(__mvs) || defined(__mvscics)) && !defined(_MODERN_COMPILER_)
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



    /* 
        Solaris needs this include
    */
#   if defined(__solaris)
#       include <stdlib.h>
#   endif /* __solaris */ 



    /* 
        Need these types for digitalUNIX too.
    */
#   if defined(__digital)
        typedef unsigned int    u_int;
        typedef unsigned long   u_long;
        typedef unsigned short  u_short;
        typedef unsigned char   u_char;
#   endif


    /* 
         Most platforms don't define socklen_t.
     */
#if defined(__aix43) || defined(__linux) || defined(__tru64)
#define _SOCKLEN_T
#endif

#ifndef _SOCKLEN_T
#define _SOCKLEN_T
typedef int socklen_t;
#endif


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
#   if !defined(_AIX) && !defined(__aix) && \
            !defined(__digital) && \
            !defined(__hpux) && \
            !defined(__irix) && \
            !defined(__linux) && \
            !defined(__mvs) && \
            !defined(__mvscics) && \
            !defined(__sunos) && !defined(__solaris) && \
            !defined(_WINDOWS) && \
            !defined(_WIN32) && \
            !defined(WIN32) 
        error: the system type is undefined
#   endif



    /* 
        This define is for simplifying the code.
    */
#   if defined(_AIX) || defined(__digital) || defined(__hpux) ||\
            defined(__irix) || defined(__linux) || defined(__solaris)
#       define CSFGSS_UNIXBUILD
#   endif



    /* 
        This define is for the code that uses the unix pwd.h file
    */
#   if defined(CSFGSS_UNIXBUILD)
#       define CSFGSS_USESUNIXPWD
#   endif /* CSFGSS_UNIXBUILD */ 



/* These two definitions are often found when passing variables 
    to printf() type functions.  

    If a printf() is to print a character string using its %s 
    format but there is a chance the sting pointer may be NULL 
    because of an error condition, then the string pointer 
    variable is encapsulated in the printf() args using the 
    NULL_NZ() macro.  If the string pointer is NULL the string 
    "(null)" is substituted.  The NULL_Z() macro uses the
    reverse logic. */
#   define NULLC_NZ(cond,val)  (cond ? val : "(null)")
#   define NULLC_Z(cond,val)   (cond ? "(null)" : val)

#   define NULL_NZ(cond)   NULLC_NZ(cond, cond)
#   define NULL_Z(cond)    NULLC_Z(cond, cond)



    /* These prototypes are of functions private to the 
        GSS-API implementation but are made visible because 
        they are used within macros. */
/* 
    prototypes coming, prepare this file for usage with C++ compilers 
*/ 
#   if defined(__cplusplus)
        extern "C" {
#   endif



    void FAR * CSFAPI csfgss_pPtr _GSS_PROTO(( CONST char FAR * ));



    /* These are prototype declarations for functions used 
        in the GSS library but not declared in the header 
        files of various hosts. */
#   if defined(__sunos) || defined(__solaris) || defined(_AIX)
        int     strncasecmp _GSS_PROTO((const char *, const char *, size_t));
        int     strcasecmp _GSS_PROTO((const char *, const char *));
#   endif

    /* Most hosts have gethostname() but few declare it.  The 
        NeXT declares gethostname() in libc.h but libc.h has 
        entries that conflict with other header files such as 
        unistd.h. */

#   if defined(__sunos) || defined(__solaris) || (defined(_AIX) && !defined(__aix43))
        int     gethostname _GSS_PROTO((char *, int));
#   endif


    /* Solaris has definitions for getuid() and unlink() 
        but they are not in the UCB header files. */
#   if defined(__solaris)
        uid_t   getuid(void);
#   endif



/* 
    all done with prototypes, close off the extern
*/ 
#   if defined(__cplusplus)
        }
#   endif



    /* Set endian.
        The default endian order is big endian.  Determine 
        and define the little endian constant if this is a 
        little endian machine. */
#   if defined(i386) || defined(__i386__) || defined(i486) || defined(__i486__)
#       if !defined(__LITTLE_ENDIAN__)
#           define __LITTLE_ENDIAN__
#       endif
#   endif



    /* Need prototypes for malloc(), calloc(), realloc(), and free(). */
#   if defined(__sunos) || defined(__solaris)
#       include    <malloc.h>
#   endif



    /* The GSS-API source uses max() and min().  Some systems 
        define those functions as macros.  Other don't have 
        them at all.  Still others define them but define other 
        macros -- such as remove() -- that interfere with method 
        names.  Hmm... */
#   if !defined(_WINDOWS) && !defined(_WIN32) && !defined(WIN32) &&      \
            !defined(__mvs) && !defined(__mvscics)
#       define min(a,b)              ((a<b) ? (a) : (b))
#       define max(a,b)              ((a>b) ? (a) : (b))
#   endif



#endif /* _GSS_COMPAT_H_ */ 
