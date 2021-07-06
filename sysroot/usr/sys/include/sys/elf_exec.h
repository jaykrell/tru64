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
 * @(#)$RCSfile: elf_exec.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1999/01/22 21:37:42 $
 */

/*
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (OSF/1).  See /usr/include/COPYRIGHT.OSF1 .
 */

#include <sys/elf.h>

#define ELF_DEFAULT_LOADER "/sbin/rtld.so"
#define ELF_HANDLE_MAGIC  0xc0ffee

/* this is a sanity check on the number of program headers */

#define ELF_MAX_PHDRS      128

struct elf_handle {
	long magic;
	Elf64_Ehdr  ehdr;        /* Elf header from file */
	Elf64_Phdr *phdr;        /* Program header from file
				    (var. length array) */
	memory_object_t pager;
	char *interpreter;       /* null terminated path of pgm. interpreter */
#if SEC_BASE
	boolean_t is_priv;       /* are privileges set? */
#endif
};
