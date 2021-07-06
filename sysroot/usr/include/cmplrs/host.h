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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/host.h,v 1.1.8.2 1998/08/12 17:34:18 Neil_Lewis Exp $ */

#ifndef _HOST_H
#define _HOST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
**  host.h
**
**  Basic type declarations, macros, ... to promote reuse and
**  portability throughout the compiler. 
**
**  Include this file before all others.
*/

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

typedef int boolean;
#ifndef TRUE
#define TRUE	(1)
#endif
#ifndef FALSE
#define FALSE	(0)
#endif

typedef char *string;
typedef char char_t;
typedef unsigned char uchar_t;
typedef short short_t;
typedef unsigned short ushort_t;
typedef int int_t;
typedef unsigned int uint_t;
typedef long long_t;
typedef unsigned long ulong_t;

#if defined(_LONGLONG)
typedef long long longlong_t;
typedef unsigned long long ulonglong_t;
#else
typedef long longlong_t;
typedef unsigned long ulonglong_t;
#endif

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef longlong_t int64;
typedef ulonglong_t uint64;

typedef void *pointer;          /* a generic pointer type */
typedef double double_t;
typedef float float_t;

#endif

/* Pascal types? */
#ifdef __cplusplus
}
#endif

#endif

