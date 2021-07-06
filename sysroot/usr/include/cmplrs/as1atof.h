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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/as1atof.h,v 4.2.9.2 1998/08/12 17:33:55 Neil_Lewis Exp $ */

#ifndef _CMPLRS_AS1ATOF_H_
#define _CMPLRS_AS1ATOF_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LANGUAGE_PASCAL__

const
  maxfpstring = 32;

type
  strng = packed array [0..maxfpstring] of char; (* Standard string type.  *)

{ Must call this first to initialize the Hough/Rowen package }
procedure initializefp; external;

{ Hough/Rowen decimal ascii-to-binary conversions: strng is null-terminated,
  function returns mask of exceptions, where all except "inexact" are
  interesting:

  most     least
      ----x		inexact
      ---x-		underflow
      --x--		overflow
      -x---		divide by zero
      x----		invalid operation
}
function atofloat(var { for economy } cstring: strng; var r: integer): integer;
  external;

function atodouble(var { for economy } cstring: strng;
  var rmore, rless: integer): integer;
  external;

function atoextended(var { for economy } cstring: strng;
  var rmost, rmore, rless, rleast:
  integer): integer; external;

#endif

#ifdef __cplusplus
}
#endif
#endif  /* _CMPLRS_AS1ATOF_H_ */
