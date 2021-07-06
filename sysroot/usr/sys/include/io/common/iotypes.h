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
 * @(#)$RCSfile: iotypes.h,v $ $Revision: 1.1.7.1 $ (DEC) $Date: 2002/05/30 23:16:42 $
 */
#if !defined(_IOTYPES_INCLUDE_)
#define _IOTYPES_INCLUDE_

/*
 * Defines for 64bit conversions.
 */
#define I8	char
#define U8	unsigned char
#define U8M1	(255)
#define I16	short
#define U16	unsigned short
#define U16M1	(65535)
#define I32	int
#define U32	unsigned int
#define U32M1	(~0U)
#define I64	long
#define U64	unsigned long
#define U64M1	(~0UL)

#define I_WORD	long
#define U_WORD	unsigned long

typedef union pad_u32 {
    U32 reg;
    unsigned long padding;
} PAD_U32;

#endif /* !defined(_IOTYPES_INCLUDE_) */
