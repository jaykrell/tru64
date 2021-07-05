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
 * @(#)$RCSfile: coff_dyn.h,v $ $Revision: 1.1.8.1 $ (DEC) $Date: 2001/09/11 15:02:47 $
 */

/* This file describes the structures, values and access macros required
 * for reading the "dynamic" sections of a shared object file.  This
 * information is used primarily for dynamically loading shared executable 
 * files and shared libraries.
 *
 * The dynamic section definitions are based on a 32-bit ELF implementation
 * of the SVR4 ABI.  Type and definition names have been retained from this
 * original implementation in elf_abi.h and elf_mips.h.
 */

#ifndef _COFF_DYN_H_
#define _COFF_DYN_H_
#if defined(__LANGUAGE_C__) || defined(__LANGUAGE_ASSEMBLY__) || defined(__cplusplus)

#include <coff_type.h>

/*
 * special section indexes
 */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_ACOMMON    (SHN_LOPROC + 0)
#define SHN_TEXT       (SHN_LOPROC + 1)
#define SHN_DATA       (SHN_LOPROC + 2)
#define SHN_HIPROC	0xff1f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

/* 
 * Null dynamic symbol index (used in hash chains)
 */
#define STN_UNDEF   	    0

/*
 * symbol table entry
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
  coff_uint	st_name;
  coff_uint	reserved;
  coff_addr	st_value;
  coff_uint	st_size;
  coff_ubyte	st_info;
  coff_ubyte	st_other;
  coff_ushort	st_shndx;
} Coff_Sym;
#endif



/*
 * st_info
 */
#define COFF_ST_BIND(i)	((i) >> 4)
#define COFF_ST_TYPE(i)	((i) & 0x0f)
#define COFF_ST_INFO(b,t)	(((b) << 4) + ((t) & 0x0f))

/*
 * symbol binding
 */
#define STB_LOCAL	0
#define STB_GLOBAL	1
#define STB_WEAK	2
#define STB_LOPROC	13
#define STB_DUPLICATE	13	/* dup symbol: st_size is link to original */
#define STB_HIPROC	15

/*
 * symbol type
 */
#define STT_NOTYPE	0
#define STT_OBJECT	1
#define STT_FUNC	2
#define STT_SECTION	3
#define STT_FILE	4
#define STT_LOPROC	13
#define STT_HIPROC	15

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct {
    coff_int	d_tag;
    coff_uint	reserved;	
    union {
	coff_uint	d_val;
	coff_addr	d_ptr;
    } d_un;
} Coff_Dyn;
#endif

/*
 * d_tag values 
 */
#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH	15
#define DT_SYMBOLIC	16
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_LOPROC	0x70000000
#define DT_RLD_VERSION  0x70000001
#define DT_TIME_STAMP   0x70000002
#define DT_ICHECKSUM    0x70000003
#define DT_IVERSION     0x70000004
#define DT_FLAGS        0x70000005
#define DT_BASE_ADDRESS 0x70000006
#define DT_MSYM         0x70000007
#define DT_CONFLICT     0x70000008
#define DT_LIBLIST      0x70000009
#define DT_LOCAL_GOTNO  0x7000000A
#define DT_CONFLICTNO   0x7000000B
#define DT_LIBLISTNO    0x70000010
#define DT_SYMTABNO     0x70000011
#define DT_UNREFEXTNO   0x70000012
#define DT_GOTSYM       0x70000013
#define DT_HIPAGENO     0x70000014
/* 0x70000015 is skipped */
#define DT_RLD_MAP      0x70000016
#define DT_SO_SUFFIX	0x70000017
#define DT_HIPROC	0x7fffffff

/* 
 * DT_FLAGS flag values 
 */
#define RHF_NONE                    0x00000000
#define RHF_QUICKSTART              0x00000001
#define RHF_NOTPOT                  0x00000002
#define RHF_NO_LIBRARY_REPLACEMENT  0x00000004
#define RHF_NO_MOVE                 0x00000008
#define RHF_NO_DLOPEN               0x02000000
#define RHF_TLS			    0x04000000
#define RHF_BIND_NOW                0x08000000
#define RHF_RING_SEARCH             0x10000000
#define RHF_DEPTH_FIRST             0x20000000
#define RHF_USE_31BIT_ADDRESSES     0x40000000
#define RHF_RESERVED_SIGN_BIT       0x80000000

/*
 * relocation entry
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
  coff_addr	r_offset;
  coff_uint	r_info;
  coff_uint	reserved;
} Coff_Rel;
#endif

/*
 * r_info
 */
#define COFF_R_SYM(i)		((i) >> 8)
#define COFF_R_TYPE(i)		((unsigned char)(i))
#define COFF_R_INFO(s,t)	(((s) << 8) + (unsigned char)(t))

/*
 * ".liblist" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
  coff_uint  l_name;
  coff_uint  l_time_stamp;
  coff_uint  l_checksum;
  coff_uint  l_version;
  coff_uint  l_flags;
} Coff_Lib;
#endif

/*
 * l_flags
 */
#define LL_NONE         0
#define LL_EXACT_MATCH      0x1
#define LL_IGNORE_INT_VER   0x2
#define LL_USE_SO_SUFFIX    0x4
#define LL_NO_LOAD	    0x8

/*
 * ".msym" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
  coff_uint  ms_hash_value;
  coff_uint  ms_info;
} Coff_Msym;
#endif
/*
 * ms_info
 */
#define COFF_MS_REL_INDEX(i)   ((i) >> 8)
#define COFF_MS_FLAGS(i)   ((i) & 0xff)
#define COFF_MS_INFO(r,f)  (((r) << 8) + ((f) & 0xff))

/*
 * ".conflict" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
    coff_uint  c_index;
} Coff_Conflict;
#endif

#define RLD_VERSION         3   /* Current shared object version 
                                 * produced by LD.  
                                 */
#define RLD_VERSION_2       2   /* LD shared object version prior to
                                 * GOT optimizations.
                                 */
#define RLD_VERSION_ONE_GOT 1   /* LD shared object version prior to
                                 * multi-GOT support.
                                 */

/*
 * ".got" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
    coff_addr  g_index;
} Coff_Got;
#endif

#endif /* __LANGUAGE_C__ || __LANGUAGE_ASSEMBLY__ */
#endif /* _COFF_DYN_H_ */
