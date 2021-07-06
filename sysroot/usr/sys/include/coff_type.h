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
 * @(#)$RCSfile: coff_type.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/12/29 21:23:14 $
 */

/*
 * This file defines the basic types used in structure definitions for the
 * DIGITAL UNIX object file and symbol table formats.
 */

#ifndef _COFF_TYPE_H
#define _COFF_TYPE_H

/* Allow these basic abstract types to be redefined */
#ifndef ALTERNATE_COFF_BASIC_TYPES

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef unsigned long	coff_addr;
typedef unsigned long	coff_off;
typedef unsigned long	coff_ulong;
typedef long		coff_long;
typedef unsigned int	coff_uint;
typedef int		coff_int;
typedef unsigned short	coff_ushort;
typedef short		coff_short;
typedef unsigned char	coff_ubyte;
typedef char            coff_byte;
#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
type
coff_addr   = cardinal64;
coff_off    = cardinal64;
coff_ulong  = cardinal64;	
coff_long   = integer64;
coff_uint   = cardinal;
coff_int    = integer;
coff_ushort = 0..65535;
coff_short  = -32768..32767;
coff_ubyte  = 0..255;
coff_byte   = -128..127;
#endif /* __LANGUAGE_PASCAL__ */
#endif /* ALTERNATE_COFF_BASIC_TYPES */
#endif /* _COFF_TYPE_H */
