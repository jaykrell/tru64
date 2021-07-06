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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/psearch.h,v 4.2.10.1 2000/07/14 19:01:23 Neil_Lewis Exp $ */

#ifndef _CMPLRS_PSEARCH_H_
#define _CMPLRS_PSEARCH_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Sort of like System V's bsearch, but not quite. "key" is a structure,
  "the_array" is an array of such structures, "elem_size" is the size in
  bytes of one element of the array, and "num_elems" is the number of
  elements in the array. Returns pointer to the element which matches
  "key", or pointer to the element which "key" ought to precede.
  Assumes array is already sorted. Both "prof" and "as1" need this. */

#ifndef __cplusplus
char *
psearch(/* char *key; char *the_array; int num_elems; int elem_size;
  procedure cmp */);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _CMPLRS_PSEARCH_H_ */
