/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright 2001 Compaq Computer Corporation                 *
 * *                                                               *
 * *    Compaq and the Compaq logo Registered in U.S. Patent       *
 * *    and Trademark Office.                                      *
 * *                                                               *
 * *    Confidential computer software. Valid license from Compaq  *
 * *    required for possession, use or copying. Consistent with   *
 * *    FAR 12.211 and 12.212, Commercial Computer Software,       *
 * *    Computer Software Documentation, and Technical Data for    *
 * *    Commercial Items are licensed to the U.S. Government       *
 * *    under vendors standard commercial license.                 *
 * *                                                               *
 * *****************************************************************
 */

#ifndef _C99STDIO_H
#define _C99STDIO_H 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#include_next <stdio.h>

/*
** The following functions have formats and arguments that should be
** checked even when they are not recognized as intrinsics.
**
**   printf, scanf, fprintf, sprintf, fscanf, sscanf, and snprintf
** 
** The following functions are not intrinsics but have formats that
** should be checked. 
** 
**   vprintf, vscanf, vfprintf, vsprintf, vfscanf, vsscanf, and vsnprintf
*/
#if defined(__DECC) && !defined(__KERNEL)
#  pragma assert func_attrs(printf) format(printf,1,2)
#  pragma assert func_attrs(scanf) format(scanf,1,2)
#  pragma assert func_attrs(fprintf,sprintf) format(printf,2,3)
#  pragma assert func_attrs(fscanf,sscanf) format(scanf,2,3)
#  pragma assert func_attrs(vprintf) format(printf,1,0)
#  pragma assert func_attrs(vfprintf,vsprintf) format(printf,2,0)
#endif

#if (defined(_OSF_SOURCE) && defined(__STDC_VERSION__)          \
                          && __STDC_VERSION__ >= 199901L)  ||   \
    (defined(_ISO_C_SOURCE) && _ISO_C_SOURCE  >= 199901L)

extern int snprintf(char * /*restrict*/ __s, size_t __n,
		    const char * /*restrict*/ __format, ...);

/*  Set __VA_LIST__ to the appropriate struct type for va_list if it is not
 *  already set.
 *
 *  Since the system stdio.h has been included at least one va_list struct
 *  type has been defined.  There are 3 possibilities:
 *
 *  1) if varargs.h/stdarg.h has not been included then only the "hidden" 
 *     struct type (__va_list) is defined.  The HIDDEN_VA_LIST macro is 
 *     defined. 
 *  2) if varargs.h/stdarg.h was included before stdio.h then only the "real"
 *     struct type (va_list) is defined.  The _HIDDEN_VA_LIST macro is not 
 *     defined. 
 *  3) if stdio.h was included before varargs.h/stdarg.h then both the
 *     "hidden" and the "real" struct types are defined and there is a typedef
 *     that makes them interchangeable.  The _HIDDEN_VA_LIST macro is not
 *     defined.
 *
 *  Here, we set __VA_LIST__ to the "real" struct type (va_list) if it
 *  is defined and the "hidden" struct type (__va_list) otherwise.  The
 *  _HIDDEN_VA_LIST macro distinguishes these cases. 
 *
 *  Note that if we use the "hidden" struct type and varargs.h/stdarg.h is
 *  later included and causes the "real" struct type to be defined, va_list.h
 *  will create a typedef so that va_list and __va_list are interchangeable.
 */

#ifndef __VA_LIST__  /* UNIX V5.1A or later */
#ifdef _HIDDEN_VA_LIST
#  define __VA_LIST__   __va_list
#else
#  define __VA_LIST__   va_list
#endif /* _HIDDEN_VA_LIST */
#endif /* __VA_LIST__ */

extern int vfscanf(FILE * /*restrict*/ __stream,
		   const char * /*restrict*/ __format, __VA_LIST__ __arg);

extern int vscanf(const char * /*restrict*/ __format, __VA_LIST__ __arg);

extern int vsnprintf(char * /*restrict*/ __s, size_t __n,
		     const char * /*restrict*/ __format, __VA_LIST__ __arg);

extern int vsscanf(const char * /*restrict*/ __s,
		   const char * /*restrict*/ __format, __VA_LIST__ __arg);

#if defined(__DECC) && !defined(__KERNEL)
#  pragma assert func_attrs(snprintf) format(printf,3,4)
#  pragma assert func_attrs(vscanf) format(scanf,1,0)
#  pragma assert func_attrs(vfscanf,vsscanf) format(scanf,2,0)
#  pragma assert func_attrs(vsnprintf) format(printf,3,0)
#endif

#endif /* _OSF_SOURCE && __STDC_VERSION__ || _ISO_C_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _C99STDIO_H */
