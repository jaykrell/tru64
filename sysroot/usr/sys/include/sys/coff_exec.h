/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: coff_exec.h,v $
 * Revision 1.1.7.1  2003/06/19  13:26:37  Matthew_McGrath
 * 	Add struct CMHDR and related values for per-binary bigpage tunables.
 *
 * Revision 1.1.4.2  1999/02/09  19:03:47  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  20:21:34  Ken_Block]
 *
 * Revision 1.1.2.2  1993/09/23  14:54:10  Anton_Verhulst
 * 	Created from OSF1.2 source and ported to alpha.
 * 	[1993/09/20  16:52:24  Anton_Verhulst]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: coff_exec.h,v $ $Revision: 1.1.7.1 $ (DEC) $Date: 2003/06/19 13:26:37 $
 */

#ifndef __COFF_EXEC_H__
#define __COFF_EXEC_H__

/*
 *      Fileheaders for coff files.
 */
#include <sysV/scnhdr.h>
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>

#include <machine/coff_subr.h>

/*
 *      Corresponding definitions are in coff_getxfile because the
 *      section size (SECTALIGN, corresponds to LOADER_PAGE_SIZE)
 *      must be obtained from the file header for some architectures.
 */

#ifdef  LOADER_PAGE_SIZE
#define SECTALIGN               LOADER_PAGE_SIZE
#else
#define LOADER_PAGE_SIZE        SECTALIGN
#endif

/*
 * This is the coff header.
 */
struct coff_hdr {
	struct filehdr fhdr;
	struct aouthdr ohdr;
};

union coff_exec {
	struct coff_hdr coff;
	struct {
		short magic;
	} coff_magic;
};

struct coff_handle {
	struct coff_hdr	hdr;
	memory_object_t	pager;
#if	SEC_BASE
	boolean_t	is_priv;
#endif
};

#define hdr_magic	coff_magic.magic

/*
 * This structure contains a set of machine-dependent data that is set
 * up when exec'ing a COFF file.
 */
struct coff_machine {
	off_t		nopagi_text;
	off_t		nopagi_data;
	vm_offset_t	pagi_text;
	vm_offset_t	pagi_data;
	int		vm_flags;
	size_t		data_size;
};

/* from scncomment.h, MUST remain sync'd up */
typedef struct {
	unsigned int	cm_tag;
	unsigned int	cm_len;
	unsigned long	cm_val;
} CMHDR;

#define CMHDRSZ sizeof(CMHDR)

#define CM_END		0
#define CM_BP_ENABLED	16
#define CM_BP_ANON	17
#define CM_BP_SEG	18
#define CM_BP_SHM	19
#define CM_BP_SSM	20
#define CM_BP_STACK	21
#define CM_BP_FACTOR	22
#define CM_L3_ANON	23
#define CM_L3_SHM	24
#define CM_L3_SSM	25

#endif /* __COFF_EXEC_H */
