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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/elf_abi.h,v 1.1.12.2 1997/12/29 21:23:16 Randy_Lowell Exp $ */
#ifndef _ELF_ABI_H_
#define _ELF_ABI_H_

/* Note: ELF32 is a misnomer here.  These types and definitions originated
 * from a 32-bit ELF.  The names have been preserved for source-compatibility,
 * but they have been recast to a 64-bit Coff implementation for DIGITAL UNIX.
 * See coff_dyn.h.
 */

#if defined(__LANGUAGE_C__) || defined(__LANGUAGE_ASSEMBLY__) || defined(__cplusplus)
		/* Right now this includes the entire file */
/* Need to deal with _LANGUAGE_PASCAL & _LANGUAGE_ASSEMBLY */

#include <coff_dyn.h>

/*
 * ELF data types
 */
#define Elf32_Addr	coff_addr
#define Elf32_Half	coff_ushort
#define Elf32_Off	coff_off
#define Elf32_Sword	coff_int
#define Elf32_Word	coff_uint

/*
 * ELF header
 */
#define EI_MAG0		0
#define EI_MAG1		1
#define EI_MAG2		2
#define EI_MAG3		3
#define EI_CLASS	4
#define EI_DATA		5
#define EI_VERSION	6
#define EI_PAD		7
#define EI_NIDENT	16

#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'

#define ELFCLASSNONE	0
#define ELFCLASS32	1	
#define ELFCLASS64	2	
#define ELFDATANONE	0	
#define ELFDATA2LSB	1	
#define ELFDATA2MSB	2

/*
 * e_ident
 * e_ident[EI_CLASS] should be ELFCLASS32
 * e_ident[EI_DATA]  should be either ELFDATA2LSB or ELFDATA2MSB
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define IS_ELF(ehdr) ((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
		      (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
		      (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
		      (ehdr).e_ident[EI_MAG3] == ELFMAG3)

typedef struct
{
	unsigned char	e_ident[EI_NIDENT];
	Elf32_Half	e_type;
	Elf32_Half	e_machine;
	Elf32_Word	e_version;
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;
	Elf32_Half	e_ehsize;
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
} Elf32_Ehdr;
#endif

/*
 * e_type
 */
#define ET_NONE		0
#define ET_REL		1
#define ET_EXEC		2
#define ET_DYN		3
#define ET_CORE		4
#define ET_LOPROC	0xff00
#define ET_HIPROC	0xffff

/*
 * e_machine
 */
#define EM_NONE		0
#define EM_M32		1
#define EM_SPARC	2
#define EM_386		3
#define EM_68K		4
#define EM_88K		5
#define EM_486  	6
#define EM_860  	7
#define EM_MIPS 	8
#define EM_NUM  	9

/*
 * e_version
 */
#define EV_NONE		0
#define EV_CURRENT	1

#define ELF32_FSZ_ADDR      8
#define ELF32_FSZ_HALF      2
#define ELF32_FSZ_OFF       8
#define ELF32_FSZ_SWORD     4
#define ELF32_FSZ_WORD      4

#define ELFMAG              "\177ELF"
#define SELFMAG             4

#define ELFDATANUM  	    3

#define ET_NUM              5

#define EV_NUM              2

#define PT_NUM              7

#define SHT_NUM             12

#define STB_NUM             3

#define STT_NUM             5


/*
 * section header
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
} Elf32_Shdr;
#endif
/*
 * sh_type
 */
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL	9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000u
#define SHT_HIUSER	0xffffffffu

/*
 * sh_flags
 */
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000u

/*
 * special section names
 */

#define ELF_BSS		".bss"
#define ELF_DATA	".data"
#define ELF_DEBUG	".debug"
#define ELF_DYNAMIC	".dynamic"
#define ELF_DYNSTR	".dynstr"
#define ELF_DYNSYM	".dynsym"
#define ELF_FINI	".fini"
#define ELF_GOT		".got"
#define ELF_HASH	".hash"
#define ELF_INIT	".init"
#define ELF_REL_DATA	".rel.data"
#define ELF_REL_FINI	".rel.fini"
#define ELF_REL_INIT	".rel.init"
#define ELF_REL_DYN	".rel.dyn"
#define ELF_REL_RODATA	".rel.rodata"
#define ELF_REL_TEXT	".rel.text"
#define ELF_RODATA	".rodata"
#define ELF_SHSTRTAB	".shstrtab"
#define ELF_STRTAB	".strtab"
#define ELF_SYMTAB	".symtab"
#define ELF_TEXT	".text"

/*
 * symbol table entry
 */
#define Elf32_Sym	Coff_Sym

/*
 * st_info
 */
#define ELF32_ST_BIND(i)	COFF_ST_BIND(i)
#define ELF32_ST_TYPE(i)	COFF_ST_TYPE(i)
#define ELF32_ST_INFO(b,t)	COFF_ST_INFO(b,t)

#define Elf32_Dyn	Coff_Dyn

/*
 * relocation entry
 */
#define Elf32_Rel	Coff_Rel

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
/*
 * relocation entry with addend
 */
typedef struct
{
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;
	Elf32_Sword	r_addend;
} Elf32_Rela;
#endif

/*
 * r_info
 */
#define ELF32_R_SYM(i)		COFF_R_SYM(i)
#define ELF32_R_TYPE(i)		COFF_R_TYPE(i)
#define ELF32_R_INFO(s,t)	COFF_R_INFO(s,t)

/*
 * program header
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;
} Elf32_Phdr;
#endif

/*
 * p_type
 */
#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

#define _MAX_NUM_PT     10

/*
 * p_flags
 */
#define PF_X		0x1
#define PF_W		0x2
#define PF_R		0x4
#define PF_MASKPROC	0xf0000000u

/* Archive macros */
#define ELF_AR_SYMTAB_NAME	"/"
#define ELF_AR_SYMTAB_NAME_LEN	1
#define ELF_AR_STRTAB_NAME	"//"
#define ELF_AR_STRTAB_NAME_LEN	2
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define IS_ELF_AR_SYMTAB(s) \
  ((s[0] == '/') && ((s[1] == ' ') || (s[1] == '\0')))

#define IS_ELF_AR_STRTAB(s) \
  (((s[0] == '/') && (s[1] == '/')) && ((s[2] == ' ') || (s[2] == '\0')))
#endif

/*
 * ".liblist" section
 */
#define Elf32_Lib	Coff_Lib

/*
 * ".msym" section
 */
#define Elf32_Msym	Coff_Msym
/*
 * ms_info
 */
#define ELF32_MS_REL_INDEX(i)   COFF_MS_REL_INDEX(i)
#define ELF32_MS_FLAGS(i)   	COFF_MS_FLAGS(i)
#define ELF32_MS_INFO(r,f)  	COFF_MS_INFO(r,f)

/*
 * ".conflict" section
 */
#define Elf32_Conflict	Coff_Conflict

/* 
 * ".got" section
 */
#define Elf32_Got	Coff_Got

#endif /* __LANGUAGE_C__ || __LANGUAGE_ASSEMBLY__ */
#endif /* _ELF_ABI_H_ */
