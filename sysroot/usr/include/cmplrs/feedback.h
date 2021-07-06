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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/cmplrs/feedback.h,v 4.2.11.4 1998/08/12 17:34:03 Neil_Lewis Exp $ */
/* Definition of the "mprof" feedback file format */

#ifndef _CMPLRS_FEEDBACK_H_
#define _CMPLRS_FEEDBACK_H_
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
# define FEEDBACK_MAGIC 0x64656566
# define PROC_FEEDBACK 0x636f7270
# define CALL_FEEDBACK 0x6c6c6163
# define BB_FEEDBACK 0x6c6d5e2c
#endif
#ifdef __LANGUAGE_PASCAL__
# define FEEDBACK_MAGIC 16#64656566
# define PROC_FEEDBACK 16#636f7270
# define CALL_FEEDBACK 16#6c6c6163
# define BB_FEEDBACK 16#6c6d5e2c
#endif

#define NO_LINE -1
#define NO_INVOCATIONS -1
#define H_EXPANSION 7
#define PP_EXPANSION 3
#define STAMPLEN 28

/* Major and minor versions of the feedback file format */
#define MS_FEEDBACK 3	/* structural changes: none in this release */
#define LS_FEEDBACK 12	/* non-structural changes: [ug]id now 32 bit */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#include <sys/types.h>	/* to get uid_t and gid_t */
struct f_header {
  int magic; /* = FEEDBACK_MAGIC */
  int callee_count; /* number of callees in this file */
  int proc_count; /* number of procedure names (union of callers, callees) */
  uid_t uid;  /* Unix user id */
  gid_t gid;  /* group id */
  uid_t euid; /* effective user id */
  gid_t egid; /* effective group id */
  int argc; /* Number of command-line arguments */
  int ms_stamp, ls_stamp; /* Format version: MS_FEEDBACK, LS_FEEDBACK */
  int for_expansion[H_EXPANSION];
  char stamp[STAMPLEN]; /* Like Unix "asctime", null-padded up to *4 chars */
  };
#endif
#ifdef __LANGUAGE_PASCAL__
type
  f_header =
    record
      magic: integer;
      callee_count: integer;
      proc_count: integer;
      uid:  cardinal;
      gid:  cardinal;
      euid: cardinal;
      egid: cardinal;
      argc: integer;
      ms_stamp, ls_stamp: integer;
      for_expansion: array[1 .. H_EXPANSION] of integer;
      stamp: packed array[1 .. STAMPLEN] of char;
    end {record};
  f_header_ptr = ^f_header;
#endif

/* Describes one callee */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct f_per_proc {
  /* callee's id (zero-origin index into list of procedure ids) */
  unsigned n_id;
  unsigned start_line; /* = NO_LINE if we don't know it */
  unsigned long cycles; /* based on bb counts */
  unsigned invocations; /* based on own invocation counts */
  /* size, excluding profiling code inserted by assembler */
  unsigned instructions;
  unsigned caller_count; /* number of points-of-call for this callee */
  unsigned bb_count; /* number of basic blocks for this callee */
  unsigned regmask, fregmask; /* sets of gp and fp registers used in callee */
  int for_expansion[PP_EXPANSION];
  };
#endif
#ifdef __LANGUAGE_PASCAL__
type
  f_per_proc =
    record
      magic: integer;		{ note: not in C struct }
      n_id: cardinal;
      start_line: cardinal;
      cycles: array [0 .. 1] of cardinal;
      invocations: cardinal;
      instructions: cardinal;
      caller_count: cardinal;
      bb_count: cardinal; 
      regmask, fregmask: cardinal;
      for_expansion: array[1 .. PP_EXPANSION] of integer;
    end {record};
  f_per_proc_ptr = ^f_per_proc;
#endif

/* Describes one point-of-call */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct f_per_call {
  unsigned n_id; /* Caller's id */
  int relative_line; /* = NO_LINE if we don't know it */
  unsigned invocations; /* = NO_INVOCATIONS if we don't know how many */
  };
#endif
#ifdef __LANGUAGE_PASCAL__
type
  f_per_call =
    record
      magic: integer;		{ note: not in C struct }
      n_id: cardinal;
      relative_line: integer;
      invocations: cardinal;
    end {record};
  f_per_call_ptr = ^f_per_call;
#endif

/* Describes one basic block */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct f_per_bb {
  int relative_line; /* = NO_LINE if we don't know it */
  unsigned bb_freq; /* = NO_INVOCATIONS if we don't know how many */
  };
#endif
#ifdef __LANGUAGE_PASCAL__
type
  f_per_bb = 
    record
      magic: integer;		{ note: not in C struct }
      relative_line: integer;
      bb_freq: cardinal;
    end {record};
  f_per_bb_ptr = ^f_per_bb;
#endif

/*

To describe the file format, we introduce a mythical parameterized type,
which consists of a string padded with at least one null (and enough to
align the end with an integer boundary):

  struct padded_string(name) {
    int length = strlen(name);
    char padded_name[((strlen(name) + sizeof(int)) / sizeof(int)) *
      sizeof(int)];
    };

Then the file itself consists of:

  struct f_header fh;

  struct padded_string(<argument>) argv[fh.argc];
  struct padded_string(<procedure name>) idstring[fh.proc_count];

  struct {

    int magic = PROC_FEEDBACK;
    struct f_per_proc callee_info;

       struct {
	 int magic = CALL_FEEDBACK;
	 struct f_per_call caller_info;
	 } callers[callee_info.caller_count];

       struct {
	 int magic = BB_FEEDBACK;
	 struct f_per_bb bb_info;
	 } bbs[callee_info.bb_count];

    } callees[fh.callee_count];

The idstring for an unnested procedure is the name of its source file,
followed by a null, followed by the procedure's name.  The idstring for
a nested procedure is the concatenation of its parent's idstring, a
dot, and its own name (apply this definition recursively).

If we don't know a procedure's name (because, for example, we saw an
invocation for it but no symbol information for it), its idstring will
be the empty string.

*/
#ifdef __LANGUAGE_PASCAL__
type
  f_name =
    record
      length: cardinal;
    end {record};
  f_name_ptr = ^f_name;
#endif


#ifdef __cplusplus
}
#endif
#endif  /* _CMPLRS_FEEDBACK_H_ */
