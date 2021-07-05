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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/aouthdr.h,v 1.2.10.2 1997/12/29 21:23:11 Randy_Lowell Exp $ */

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef _AOUTHDR_H
#define _AOUTHDR_H

#include <coff_type.h>

/*
 * Values for the magic field in aouthdr
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define	OMAGIC	0407
#define	NMAGIC	0410
#define	ZMAGIC	0413
#define SMAGIC  0411
#define	LIBMAGIC	0443
#define	N_BADMAG(x) \
    (((x).magic)!=OMAGIC && ((x).magic)!=NMAGIC && ((x).magic)!=ZMAGIC && \
     ((x).magic)!=LIBMAGIC && ((x).magic)!=SMAGIC)

#endif /* __LANGUAGE_C__ */
#ifdef __LANGUAGE_PASCAL__
#define	OMAGIC	8#407
#define	NMAGIC	8#410
#define	ZMAGIC	8#413
#define SMAGIC  8#411
#define	LIBMAGIC	8#443
#endif /* __LANGUAGE_PASCAL__ */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef	struct aouthdr {
  coff_ushort	magic;		/* see above				*/
  coff_ushort	vstamp;		/* version stamp			*/
  coff_ushort	bldrev;
  coff_ushort	padcell;
  coff_long	tsize;		/* text size in bytes, padded to DW bdry*/
  coff_long	dsize;		/* initialized data "  "		*/
  coff_long	bsize;		/* uninitialized data "   "		*/
  coff_addr	entry;		/* entry pt.				*/
  coff_addr	text_start;	/* base of text used for this file	*/
  coff_addr	data_start;	/* base of data used for this file	*/
  coff_addr	bss_start;	/* base of bss used for this file	*/
  coff_uint	gprmask;	/* general purpose register mask	*/
  coff_uint	fprmask; 	/* floating point register mask		*/
  coff_long	gp_value;	/* the gp value used for this object    */
} AOUTHDR;
#define AOUTHSZ sizeof(AOUTHDR)
#endif /* __LANGUAGE_C__ */

#ifdef __LANGUAGE_PASCAL__
type
  aouthdr = packed record
      magic : coff_ushort;		/* see magic.h			     */
      vstamp : coff_ushort;		/* version stamp		     */
      bldrev : coff_ushort;
      padcell : coff_ushort;
      tsize : coff_long;		/* text size in bytes, padded to FW  */
					/* bdry 			     */
      dsize : coff_long;		/* initialized data " " 	     */
      bsize : coff_long;		/* uninitialized data " "	     */
      entry : coff_addr;		/* entry pt.			     */
      text_start : coff_addr;		/* base of text used for this file   */
      data_start : coff_addr;		/* base of data used for this file   */
      bss_start : coff_addr;		/* base of bss used for this file    */
      gprmask : coff_uint;		/* general purpose register mask     */
      fprmask : coff_uint;		/* floating point register mask	     */
      gp_value : coff_addr;		/* the gp value used for this object */
    end {record};
#endif /* __LANGUAGE_PASCAL__ */
#endif
