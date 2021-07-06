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
/* @(#)$RCSfile: core.h,v $ $Revision: 4.3.6.5 $ (DEC) $Date: 1996/02/20 19:21:23 $ */
/*
 *
 * 31-Oct-91	Brian Stevens
 *	Modified core_filehdr to contain the offending thread id.
 */


#ifndef _CORE_H_
#define _CORE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/user.h>
#include <mach/port.h>
#include <machine/coreregs.h>

#define CORE_VERS 2

#define SCNTEXT  1
#define SCNDATA  2
#define SCNRGN   3
#define SCNSTACK 4
#define SCNREGS  5
#define SCNOVFL  6

#ifdef _KERNEL
typedef vm_prot_t core_prot_t;
typedef vm_offset_t core_offset_t;
typedef vm_size_t core_size_t;
#else
typedef uint_t core_prot_t;
typedef void core_offset_t;
typedef ulong_t core_size_t;
#endif /* _KERNEL */

struct core_filehdr {
	char   magic[4];		/* Contains "Core"		*/
	ushort_t version;		/* Version of this core file	*/
	ushort_t nscns;			/* Number of section headers	*/
	port_t   tid;			/* Thread causing fault		*/
	uint_t   nthreads;		/* Number of threads in process */
	int    signo;			/* Signal			*/
	char   name[MAXCOMLEN+1];	/* Name of program		*/
};

struct core_scnhdr {
	ushort_t      scntype;	/* Sect. type: SCNTEXT, SCNDATA, etc.	*/
	union {
	   port_t tid;		/* Thread id in SCNREGS section		*/
	   core_prot_t  prot;	/* Memory protections in text/data/stack*/
	} c_u;
	core_offset_t *vaddr;	/* Starting virtual address		*/
	core_size_t   size;	/* Size of section			*/
	unsigned long scnptr;	/* Offset to raw data from beg. of file */
};

#ifdef __cplusplus
}
#endif
#endif /* _CORE_H_ */
