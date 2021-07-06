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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/syms.h,v 1.2.8.2 1999/02/25 19:10:45 Andrew_Bragg Exp $ */

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _SYMS_H
#define _SYMS_H

/*	Defines for "special" symbols   */


#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define _ETEXT	"_etext"
#define	_EDATA	"_edata"
#define	_END	"_end"
#define _UNWIND "__unwind"
#define _WEAK_ETEXT     "etext"
#define _WEAK_EDATA     "edata"
#define _WEAK_END       "end"
#define _WEAK_UNWIND "unwind"
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define _ETEXT	'_etext\0'
#define	_EDATA	'_edata\0'
#define	_END	'_end\0'
#define _UNWIND '__unwind\0'
#define _WEAK_ETEXT     'etext\0'
#define _WEAK_EDATA     'edata\0'
#define _WEAK_END       'end\0'
#define _WEAK_UNWIND    'unwind\0'
#endif /* __LANGUAGE_PASCAL__ */
/*
 * The displacement of the gp is from the start of the small data section
 * is GP_DISP.  The GP_PAD is the padding of the gp area so small negitive
 * offset from gp relocation values can allways be used.
 */
#define GP_PAD	16
#define GP_DISP	(32768 - GP_PAD)
#define GP_SIZE (GP_DISP+32767)
/* "special" symbols for starts of sections */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define	_FTEXT	"_ftext"
#define	_FDATA	"_fdata"
#define	_FBSS	"_fbss"
#define	_GP	"_gp"
#define	_FPDATA	"_fpdata"
#define	_FPDATA_SIZE	"_fpdata_size"
#define	_PROCEDURE_TABLE	"_procedure_table"
#define	_PROCEDURE_TABLE_SIZE	"_procedure_table_size"
#define	_PROCEDURE_STRING_TABLE	"_procedure_string_table"
#define	_PC_NLC_GOTO   	"__pc_nloc_goto"
#define	_COBOL_MAIN	"_cobol_main"
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define	_FTEXT	'_ftext\0'
#define	_FDATA	'_fdata\0'
#define	_FBSS	'_fbss\0'
#define	_GP	'_gp\0'
#define	_FPDATA	'_fpdata\0'
#define	_FPDATA_SIZE	'_fpdata_size\0'
#define	_PROCEDURE_TABLE	'_procedure_table\0'
#define	_PROCEDURE_TABLE_SIZE	'_procedure_table_size\0'
#define	_PROCEDURE_STRING_TABLE	'_procedure_string_table\0'
#define	_PC_NLC_GOTO   	'__pc_nlc_goto\0'
#define	_COBOL_MAIN	'_cobol_main\0'
#endif /* __LANGUAGE_PASCAL__ */


#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define _START	"__start"
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define _START	'__start\0'
#endif /* __LANGUAGE_PASCAL__ */

#include <symconst.h>
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#include <sym.h>
#include <cmplrs/stsupport.h>
#endif /* __LANGUAGE_C__ || __cplusplus */

#endif	/* _SYMS_H */
