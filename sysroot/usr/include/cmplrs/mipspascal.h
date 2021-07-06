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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/mipspascal.h,v 4.2.8.2 1998/08/12 17:34:20 Neil_Lewis Exp $ */
#ifndef _CMPLRS_MIPSPASCAL_H_
#define _CMPLRS_MIPSPASCAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _PASTEL
/* Define all these in uppercase as well?? */
#define lbound lowerbound
#define hbound upperbound
/* use "And" instead of "and" to prevent further expansion into "andif". */
#define bitand(_a,_b) ((_a) And (_b))
#define bitxor(_a,_b) ((_a) Xor (_b))
#define bitor(_a,_b) ((_a) Or (_b))
#define bitnot(_a) (Not (_a))
#define sizeof size
#define otherwise others
#define and andif
#define or orif
type
    double = longreal;
    /* These are not part of the MIPS Pascal standard.
        long = integer;
        ushort = 0..65535;
        short = -32768..32767;
    */
#define err ttyoutput
#include "/usr/local/include/pastel/pc-compatibility.h"
#endif
#ifdef _PP
/* Define all these in uppercase as well?? */
/* use "And" instead of "and" to prevent further expansion into "andif". */
#define bitand(_a,_b) ((_a) And (_b))
#define bitxor(_a,_b) ((_a) Xor (_b))
#define bitor(_a,_b) ((_a) Or (_b))
#define bitnot(_a) (Not (_a))
#define otherwise others
#define and andif
#define or orif
#define assert(_b) begin if not (_b) then assertion_error end
#define argv(_i,_s) _s := argv_string(_i)
var
  argc: external cardinal;

function argv_string (
    in i: cardinal
    ): string;
  external;
function clock (): cardinal;
  external;
function sysclock (): cardinal;
  external;
function wallclock (): cardinal;
  external;
procedure remove (
    in filename: string );
  external;
procedure assertion_error;
  external;
procedure halt;
  external;
#endif

#ifdef __cplusplus
}
#endif
#endif  /* _CMPLRS_MIPSPASCAL_H_ */
