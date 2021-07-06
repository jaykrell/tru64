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
 * @(#)$RCSfile: elf.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2000/09/21 11:29:22 $
 */
/*
 * COPYRIGHT NOTICE
 * 
 * 
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (OSF/1).  See /usr/include/COPYRIGHT.OSF1 .
 */

#ifndef _SYS_ELF_H_
#define _SYS_ELF_H_


/* 32-bit types */
typedef unsigned int    Elf32_Addr;
typedef unsigned int    Elf32_Off;
typedef unsigned short  Elf32_Half;
typedef unsigned int    Elf32_Word;
typedef int     	Elf32_Sword;

/* 64-bit types */
typedef unsigned long   Elf64_Addr;
typedef unsigned long   Elf64_Off;
typedef unsigned short  Elf64_Half;
typedef unsigned int    Elf64_Word;
typedef int     	Elf64_Sword;
typedef unsigned long   Elf64_Xword;
typedef long    	Elf64_Sxword;

/* e_ident[] indexes */
#define EI_MAG0         0
#define EI_MAG1         1
#define EI_MAG2         2
#define EI_MAG3         3
#define EI_CLASS        4
#define EI_DATA         5
#define EI_VERSION      6
#define EI_OSABI        7
#define EI_ABIVERSION   8
#define EI_PAD		9
#define EI_NIDENT       16

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

/* e_type */
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOOS   0xfe00
#define ET_HIOS   0xfeff
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* e_machine */
#define EM_NONE  	0
#define EM_M32   	1	/* AT&T WE 32100 */
#define EM_SPARC 	2	/* SPARC */
#define EM_386   	3	/* Intel 80386 */
#define EM_68K   	4	/* Motorola 68000 */
#define EM_88K   	5	/* Motorola 88000 */
#define EM_860   	7	/* Intel 80860 */
#define EM_MIPS  	8	/* MIPS I Architecture */
#define EM_MIPS_RS3_LE	10	/* MIPS RS3000 Little-endian */
#define EM_PARISC	15	/* Hewlett-Packard PA-RISC */
#define EM_VPP500	17	/* Fujitsu VPP500 */
#define EM_SPARC32PLUS	18	/* Enhanced instruction set SPARC */
#define EM_960		19	/* Intel 80960 */
#define EM_PPC		20	/* Power PC */
#define EM_V800		36	/* NEC V800 */
#define EM_FR20		37	/* Fujitsu FR20 */
#define EM_RH32		38	/* TRW RH-32 */
#define EM_RCE		39	/* Motorola RCE */
#define EM_ARM		40	/* Advanced RISC Machines ARM */
#define EM_ALPHA 	41	/* Digital Alpha */
#define EM_SH		42	/* Hitachi SH */
#define EM_SPARCV9	43	/* SPARC Version 9 */
#define EM_TRICOR	44	/* Siemens Tricore embedded processor */
#define EM_ARC		45	/* Argonaut RISC Core */
#define EM_H8_300	46	/* Hitachi H8/300 */
#define EM_H8_300H	47	/* Hitachi H8/300H */
#define EM_H8S		48	/* Hitachi H8S */
#define EM_H8_500	49	/* Hitachi H8/500 */
#define EM_IA_64	50	/* Intel Merced(tm) IA64 */
#define EM_MIPS_X	51	/* Stanford MIPS-X */
#define EM_COLDFIRE	52	/* Motorola Coldfire */
#define EM_68HC12	53	/* Motorola M68HC12 */
#define EM_MMA		54	/* Fujitsu MMA Multimedia Accelerator */
#define EM_PCP		55	/* Siemens PCP */
#define EM_NCPU		56	/* Sony nCPU embedded RISC processor */
#define EM_NDR1		57	/* Denso NDR1 microprocessor */
#define EM_STARCORE	58	/* Motorola Star*Core processor */
#define EM_ME16		59	/* Toyota ME16 processor */
#define EM_ST100	60	/* STMicroelectronics ST100 processor */
#define EM_TINYJ	61	/* Advanced Logic Corp. TinyJ embedded proc */
#define EM_FX66		66	/* Siemens FX66 microcontroller */

/* e_version, EI_VERSION */
#define EV_NONE         0
#define EV_CURRENT      1
#define EV_NUM          2

/* EI_MAG */
#define ELFMAG0         0x7f
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'
#define ELFMAG          "\177ELF"
#define SELFMAG         4

/* EI_CLASS */
#define ELFCLASSNONE    0
#define ELFCLASS32      1
#define ELFCLASS64      2
#define ELFCLASSNUM     3

/* EI_DATA */
#define ELFDATANONE     0
#define ELFDATA2LSB     1
#define ELFDATA2MSB     2

/* st_shndx */
#define SHN_UNDEF       0
#define SHN_LORESERVE   0xff00
#define SHN_LOPROC      0xff00
#define SHN_HIPROC      0xff1f
#define SHN_LOOS        0xff20
#define SHN_HIOS        0xff3f
#define SHN_ABS         0xfff1
#define SHN_COMMON      0xfff2
#define SHN_HIRESERVE   0xffff

typedef struct {
    Elf32_Word    sh_name;
    Elf32_Word    sh_type;
    Elf32_Word    sh_flags;
    Elf32_Addr    sh_addr;
    Elf32_Off     sh_offset;
    Elf32_Word    sh_size;
    Elf32_Word    sh_link;
    Elf32_Word    sh_info;
    Elf32_Word    sh_addralign;
    Elf32_Word    sh_entsize;
} Elf32_Shdr;

typedef struct {
    Elf64_Word    sh_name;
    Elf64_Word    sh_type;
    Elf64_Xword   sh_flags;
    Elf64_Addr    sh_addr;
    Elf64_Off     sh_offset;
    Elf64_Xword   sh_size;
    Elf64_Word    sh_link;
    Elf64_Word    sh_info;
    Elf64_Xword   sh_addralign;
    Elf64_Xword   sh_entsize;
} Elf64_Shdr;

/* sh_type */
#define SHT_NULL        	0
#define SHT_PROGBITS    	1
#define SHT_SYMTAB      	2
#define SHT_STRTAB      	3
#define SHT_RELA        	4
#define SHT_HASH        	5
#define SHT_DYNAMIC     	6
#define SHT_NOTE        	7
#define SHT_NOBITS      	8
#define SHT_REL         	9
#define SHT_SHLIB       	10
#define SHT_DYNSYM      	11
#define SHT_LOOS   		0x60000000
#define SHT_HIOS   		0x6fffffff
#define SHT_LOPROC 		0x70000000
#define SHT_HIPROC 		0x7fffffff
#define SHT_LOUSER 		0x80000000
#define SHT_HIUSER 		0xffffffff

/* sh_flags */
#define SHF_WRITE       0x1
#define SHF_ALLOC       0x2
#define SHF_EXECINSTR   0x4
#define SHF_MASKOS      0x0f000000
#define SHF_MASKPROC    0xf0000000

typedef struct {
    Elf32_Word		st_name;
    Elf32_Addr		st_value;
    Elf32_Word		st_size;
    unsigned char	st_info;
    unsigned char	st_other;
    Elf32_Half		st_shndx;
} Elf32_Sym;

typedef struct {
    Elf64_Word		st_name;
    unsigned char	st_info;
    unsigned char	st_other;
    Elf64_Half		st_shndx;
    Elf64_Addr		st_value;
    Elf64_Xword		st_size;
} Elf64_Sym;

#define ELF32_ST_BIND(x)   ((x)>>4)
#define ELF32_ST_TYPE(x)   ((x) & 0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

#define ELF64_ST_BIND(x)   ELF32_ST_BIND(x)
#define ELF64_ST_TYPE(x)   ELF32_ST_TYPE(x)
#define ELF64_ST_INFO(b,t) ELF32_ST_INFO(b,t)

#define STN_UNDEF      	0	/* Undefined symbol index */

/* st_info bind values */
#define STB_LOCAL   	0
#define STB_GLOBAL  	1
#define STB_WEAK    	2
#define STB_LOOS   	10
#define STB_HIOS   	12
#define STB_LOPROC 	13
#define STB_HIPROC 	15

/* st_info type values */
#define STT_NOTYPE    	0
#define STT_OBJECT    	1
#define STT_FUNC      	2
#define STT_SECTION   	3
#define STT_FILE      	4
#define STT_LOOS     	10
#define STT_HIOS     	12
#define STT_LOPROC   	13
#define STT_HIPROC   	15

typedef struct {
    Elf32_Word      r_offset;
    Elf32_Word      r_info;
} Elf32_Rel;

typedef struct {
    Elf32_Word      r_offset;
    Elf32_Word      r_info;
    Elf32_Sword     r_addend;
} Elf32_Rela;

typedef struct {
    Elf64_Addr      r_offset;
    Elf64_Xword     r_info;
} Elf64_Rel;

typedef struct {
    Elf64_Addr      r_offset;
    Elf64_Xword     r_info;
    Elf64_Sxword    r_addend;
} Elf64_Rela;

#define ELF32_R_SYM(x) ((x) >> 8)
#define ELF32_R_TYPE(x) ((unsigned char)(x))
#define ELF32_R_INFO(s,t) (((s)<<8) + (unsigned char)(t))

#define ELF64_R_SYM(x) ((x) >> 32)
#define ELF64_R_TYPE(x) ((x) & 0xffffffffL)
#define ELF64_R_INFO(s,t) (((s)<<32) + ((t) & 0xffffffffL))

typedef struct {
    Elf32_Word    p_type;
    Elf32_Off     p_offset;
    Elf32_Addr    p_vaddr;
    Elf32_Addr    p_paddr;
    Elf32_Word    p_filesz;
    Elf32_Word    p_memsz;
    Elf32_Word    p_flags;
    Elf32_Word    p_align;
} Elf32_Phdr;

typedef struct {
    Elf64_Word    p_type;
    Elf64_Word    p_flags;
    Elf64_Off     p_offset;
    Elf64_Addr    p_vaddr;
    Elf64_Addr    p_paddr;
    Elf64_Xword   p_filesz;
    Elf64_Xword   p_memsz;
    Elf64_Xword   p_align;
} Elf64_Phdr;

/* p_type */
#define PT_NULL    		0
#define PT_LOAD    		1
#define PT_DYNAMIC 		2
#define PT_INTERP  		3
#define PT_NOTE    		4
#define PT_SHLIB   		5
#define PT_PHDR    		6
#define PT_LOOS    		0x60000000
#define PT_HIOS    		0x6fffffff
#define PT_LOPROC  		0x70000000
#define PT_HIPROC  		0x7fffffff

/* p_flags */
#define PF_X			0x1
#define PF_W            	0x2
#define PF_R            	0x4
#define PF_MASKOS       	0x0ff00000
#define PF_MASKPROC     	0xf0000000

/* Note header in a PT_NOTE section */
typedef struct elf_note {
  Elf64_Word    n_namesz;       /* Name size */
  Elf64_Word    n_descsz;       /* Content size */
  Elf64_Word    n_type;         /* Content type */
} Elf64_Nhdr;

/* n_type */
#define NT_VERSION 1

typedef struct {
  Elf32_Sword 	d_tag;
  union{
    Elf32_Word	d_val;
    Elf32_Addr	d_ptr;
  } d_un;
} Elf32_Dyn;

typedef struct {
  Elf64_Sxword	d_tag;
  union{
    Elf64_Xword	d_val;
    Elf64_Addr	d_ptr;
  } d_un;
} Elf64_Dyn;

/* d_tag */
#define DT_NULL         	0
#define DT_NEEDED       	1
#define DT_PLTRELSZ     	2
#define DT_PLTGOT       	3
#define DT_HASH         	4
#define DT_STRTAB       	5
#define DT_SYMTAB       	6
#define DT_RELA         	7
#define DT_RELASZ       	8
#define DT_RELAENT      	9
#define DT_STRSZ        	10
#define DT_SYMENT       	11
#define DT_INIT         	12
#define DT_FINI         	13
#define DT_SONAME       	14
#define DT_RPATH        	15
#define DT_SYMBOLIC     	16
#define DT_REL          	17
#define DT_RELSZ        	18
#define DT_RELENT       	19
#define DT_PLTREL       	20
#define DT_DEBUG        	21
#define DT_TEXTREL      	22
#define DT_JMPREL       	23
#define DT_BIND_NOW		24
#define DT_INIT_ARRAY		25
#define DT_FINI_ARRAY		26
#define DT_INIT_ARRAYSZ		27
#define DT_FINI_ARRAYSZ		28
#define DT_LOOS		   	0x60000000
#define DT_HIOS		   	0x6fffffff
#define DT_LOPROC	   	0x70000000
#define DT_HIPROC          	0x7fffffff


/* Tru64 Extensions */

/* .msym section */

/* ms_flags */
#define MS_CONFLICT_F 0x01

typedef struct {
  Elf32_Word	ms_hash_value;
  Elf32_Word	ms_flags:8;
  Elf32_Word	ms_rel_index:24;
  Elf32_Half	ms_jmprel_index;
  Elf32_Half	ms_rela_index;
} Elf32_Msym;

typedef struct {
  Elf64_Word	ms_hash_value;
  Elf64_Word	ms_flags:8;
  Elf64_Word	ms_rel_index:24;
  Elf64_Half	ms_jmprel_index;
  Elf64_Half	ms_rela_index;
} Elf64_Msym;

/* .liblist section */

/* l_flags */
#define LL_EXACT_MATCH    0x1
#define LL_IGNORE_INT_VER 0x2
#define LL_USE_SO_SUFFIX  0x4
#define LL_NO_LOAD        0x8

typedef struct {
  Elf32_Word	l_name;
  Elf32_Word	l_time_stamp;
  Elf32_Word	l_checksum;
  Elf32_Word	l_version;
  Elf32_Word	l_flags;
} Elf32_Lib;

typedef struct {
  Elf64_Word	l_name;
  Elf64_Word	l_time_stamp;
  Elf64_Word	l_checksum;
  Elf64_Word	l_version;
  Elf64_Word	l_flags;
} Elf64_Lib;

#ifdef __intel__
/* Processor and OSABI specific definitions */
#include <machine/elf.h>
#endif

#endif /* _SYS_ELF_H_ */
