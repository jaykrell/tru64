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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/stamp.h,v 1.2.27.1 2001/09/11 15:02:55 Randy_Lowell Exp $ */

/* Old definitions, retained for backward compatibility. */
#define	MS_STAMP 3
#define	LS_STAMP 11
#define INCLUDE_STAMP "3.11"
#define BUILD_VERSION 14


/* Object format version */
#define MAJ_OBJ_STAMP 3
#define MIN_OBJ_STAMP 13
#define OBJ_STAMP ((MAJ_OBJ_STAMP << 8) | MIN_OBJ_STAMP)

/* Symbol table format version */
#define MAJ_SYM_STAMP 3
#define MIN_SYM_STAMP 14
#define SYM_STAMP ((MAJ_SYM_STAMP << 8) | MIN_SYM_STAMP)

/* Macros to extract major/minor versions from a version stamp. */
#define MAJ_STAMP(x) (((x) >> 8) & 0xff)
#define MIN_STAMP(x) ((x) & 0xff)

/* Version string for DE tools. */
#define DE_VERSTRING "5.1"

/* Tool version names. */
#define AR_TOOLNAME "ar"
#define ATOM_TOOLNAME "atom"
#define CORD_TOOLNAME "cord"
#define DBX_TOOLNAME "dbx"
#define DIS_TOOLNAME "dis"
#define FIXSO_TOOLNAME "fixso"
#define GPROF_TOOLNAME "gprof"
#define HIPROF_TOOLNAME "hiprof"
#define KDBX_TOOLNAME "kdbx"
#define KLOADSRV_TOOLNAME "kloadsrv"
#define LD_TOOLNAME "ld"
#define LOADER_TOOLNAME "loader"
#define MCS_TOOLNAME "mcs"
#define NM_TOOLNAME "nm"
#define ODUMP_TOOLNAME "odump"
#define OM_TOOLNAME "om"
#define OSTRIP_TOOLNAME "ostrip"
#define PIXIE_TOOLNAME "pixie"
#define PROF_TOOLNAME "prof"
#define STDUMP_TOOLNAME "stdump"
#define STRIP_TOOLNAME "strip"
#define THIRD_TOOLNAME "third"

/* NULL toolversion value */
#define NULL_TOOLVER ((unsigned long)-1)

/* Tool version values. */
#define AR_TOOLVER 0
#define ATOM_TOOLVER 0
#define CORD_TOOLVER 0
#define DBX_TOOLVER 0
#define DIS_TOOLVER 0
#define FIXSO_TOOLVER 0
#define GPROF_TOOLVER 0
#define HIPROF_TOOLVER 0
#define KDBX_TOOLVER 0
#define KLOADSRV_TOOLVER 0
#define LD_TOOLVER 0
#define LOADER_TOOLVER 0
#define MCS_TOOLVER 0
#define NM_TOOLVER 0
#define ODUMP_TOOLVER 0
#define OM_TOOLVER 0
#define OSTRIP_TOOLVER 0
#define PIXIE_TOOLVER 0
#define PROF_TOOLVER 0
#define STDUMP_TOOLVER 0
#define STRIP_TOOLVER 0
#define THIRD_TOOLVER 0
