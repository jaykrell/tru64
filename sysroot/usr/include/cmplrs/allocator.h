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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/allocator.h,v 4.2.11.2 1998/08/12 17:33:46 Neil_Lewis Exp $ */

#ifndef _CMPLRS_ALLOCATOR_H_
#define _CMPLRS_ALLOCATOR_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LANGUAGE_PASCAL__

function alloc_mark (
       var fheap : pointer)
   : pointer;
  external;

procedure alloc_release (
	var fheap : pointer;
	    fmark : pointer);
  external;

function alloc_new (
	   fsize : integer;
       var fheap : pointer)
   : pointer;
  external;

procedure alloc_dispose (
	    fptr : pointer;
	var fheap : pointer);
  external;

function alloc_resize (
	    fptr : pointer;
	    fsize : cardinal;
	var fheap : pointer)
   : pointer;
  external;

function malloc (
	   fsize : integer)
   : pointer;
  external;

procedure free (
	    fptr : pointer);
  external;

function realloc (
           fptr : pointer;
	   fsize : integer)
   : pointer;
  external;

#endif

#ifdef __cplusplus
}
#endif
#endif  /* _CMPLRS_ALLOCATOR_H_ */
