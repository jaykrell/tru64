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
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/elf_mips.h,v 1.1.16.3 1997/12/29 21:23:17 Randy_Lowell Exp $ */

#ifndef _ELF_MIPS_H_
#define _ELF_MIPS_H_

#include <elf_abi.h>

#if defined(__LANGUAGE_C__) || defined(__LANGUAGE_ASSEMBLY__) || defined(__cplusplus)
                /* no pascal support yet- */

/* Obsolete MIPS-specific definitions */

/* 
 * Special mips section indices
 */
#define SHN_MIPS_ACOMMON    (SHN_LOPROC + 0)
#define SHN_MIPS_TEXT       (SHN_LOPROC + 1)
#define SHN_MIPS_DATA       (SHN_LOPROC + 2)

/*
 * special section names
 */
#define MIPS_SDATA  ".sdata"
#define MIPS_SBSS   ".sbss"
#define MIPS_LIT4   ".lit4"
#define MIPS_LIT8   ".lit8"
#define MIPS_REGINFO    ".reginfo"
#define MIPS_LIBLIST    ".liblist"
#define MIPS_MSYM   ".msym"
#define MIPS_CONFLICT   ".conflict"
#define MIPS_UCODE  ".ucode"

/*
 * r_info
 */
/*
 * relocation types
 */
#define R_MIPS_NONE 0
#define R_MIPS_32   1
#define R_MIPS_64   2
#define R_MIPS_GPREL32  3
#define R_MIPS_LITERAL  4
#define R_MIPS_LITUSE   5
#define R_MIPS_GPDISP   6
#define R_MIPS_BRADDR   7
#define R_MIPS_HINT 8

#define DT_MIPS_RLD_VERSION     0x70000001
#define DT_MIPS_TIME_STAMP      0x70000002
#define DT_MIPS_ICHECKSUM       0x70000003
#define DT_MIPS_IVERSION        0x70000004
#define DT_MIPS_FLAGS           0x70000005
#define DT_MIPS_BASE_ADDRESS    0x70000006
#define DT_MIPS_MSYM            0x70000007
#define DT_MIPS_CONFLICT        0x70000008
#define DT_MIPS_LIBLIST         0x70000009
#define DT_MIPS_LOCAL_GOTNO     0x7000000A
#define DT_MIPS_CONFLICTNO      0x7000000B
#define DT_MIPS_LIBLISTNO       0x70000010
#define DT_MIPS_SYMTABNO        0x70000011
#define DT_MIPS_UNREFEXTNO      0x70000012
#define DT_MIPS_GOTSYM          0x70000013
#define DT_MIPS_HIPAGENO        0x70000014
/* 0x70000015 is skipped */
#define DT_MIPS_RLD_MAP         0x70000016
#define DT_MIPS_SO_SUFFIX	0x70000017


/* Obsolete definitions not used in Digital UNIX */

#define EF_MIPS_NOREORDER   0x00000001
#define EF_MIPS_PIC     0x00000002
#define EF_MIPS_CPIC        0x00000004
#define EF_MIPS_UGEN_ALLOC  0x00000008
#define EF_MIPS_UGEN_RESERVED   0x00000010
#define EF_MIPS_ARCH        0xf0000000u
#define EF_MIPS_ARCH_2          0x10000000
#define EF_MIPS_ARCH_3          0x20000000
#define PT_MIPS_REGINFO (PT_LOPROC + 0)
#define SHT_MIPS_LIBLIST    (SHT_LOPROC + 0)
#define SHT_MIPS_MSYM       (SHT_LOPROC + 1)
#define SHT_MIPS_CONFLICT   (SHT_LOPROC + 2)
#define SHT_MIPS_GPTAB      (SHT_LOPROC + 3)
#define SHT_MIPS_UCODE      (SHT_LOPROC + 4)
#define SHT_MIPS_DEBUG          (SHT_LOPROC + 5)
#define SHT_MIPS_REGINFO        (SHT_LOPROC + 6)
#define SHF_MIPS_GPREL  0x10000000
#define MIPS_REL_SDATA  ".rel.sdata"
#define MIPS_RHEADER    ".rheader"
#define MIPS_GPTAB_SDATA    ".gptab.sdata"
#define MIPS_GPTAB_DATA ".gptab.data"
#define MIPS_GPTAB_BSS  ".gptab.bss"
#define MIPS_GPTAB_SBSS ".gptab.sbss"
#define MIPS_MDEBUG ".mdebug"
#define MS_ALIAS        0x1

/* Obsolete structure for GP histogram info */
typedef union
{
    struct
    {
        Elf32_Word  gt_current_g_value;
        Elf32_Word  gt_unused;
    } gt_header;
    struct
    {
        Elf32_Word  gt_g_value;
        Elf32_Word  gt_bytes;
    } gt_entry;
} Elf32_Gptab;

/* Obsolete reginfo structure */
typedef struct
{
    Elf32_Word  ri_gprmask;
    Elf32_Word  ri_fprmask;
    Elf32_Sword ri_gp_value;
} Elf32_RegInfo;


#endif              /* __LANGUAGE_C__ || __LANGUAGE_ASSEMBLY__ */
#endif              /* _ELF_MIPS_H_ */

