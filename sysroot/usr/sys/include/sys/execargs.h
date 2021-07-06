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
 * @(#)$RCSfile: execargs.h,v $ $Revision: 1.1.17.2 $ (DEC) $Date: 2000/03/21 20:01:04 $
 */

#ifndef _SYS_EXECARGS_H_
#define _SYS_EXECARGS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/auxv.h>
#include <mach/machine/vm_types.h>

struct exec_pagelist {
	vm_offset_t *pl_fill;
	vm_offset_t *pl_current_plpage;
	int pl_count_in_current_plpage;
	vm_offset_t *pl_first_plpage;	/* First page in list of pages */
};

/*
 * Argument block structure
 */
struct execargs {
	vm_offset_t	argsmem;/* pointer to memory allocated for args */
	vm_offset_t	args;	/* pointer to arg/env space */
	int		na;	/* number of args */
	int		ne;	/* number of env variables */
	unsigned	nc;	/* character count (aligned) */
	int		ni;	/* number of interpreter args */
	int		cc;	/* arg space left */
	vm_offset_t	ufile;	/* offset to program name in `args' */
	vm_offset_t	loader; /* offset to loader in `args' */
	char		*interp; /* location of interpreter info in `args' */
	vm_offset_t	interp_offset; /* offset to interpreter info in `args'*/
	kauxv_t		*auxv;	/* auxv structure */
	vm_offset_t	envp;	/* pointer to env space */
	unsigned	nac;	/* char count for args */
	int		align;	/* alignment of args member (EXARG_{NO_}ALIGN)*/

	/* members for exec with unlimited args */
	struct exec_pagelist	argv_pl;
	struct exec_pagelist	strings_pl;
	vm_offset_t	*argv_p;
	vm_offset_t	*argv_current_page_start;
	char		*strings_p;
	vm_offset_t	strings_offset;
	vm_offset_t	*strings_current_page_start;
	vm_offset_t	*argc_p;	/* pointer to the argc */
	int		argv_current_page_remaining;
	int		strings_current_page_remaining;
	vm_offset_t	shell_args_p;
	int		argc;
	int		using_pagelist;
	int		argv_page_count;
	int		strings_page_count;
	char		*ufile_userspace;
	char		*loader_userspace;
	char		*loader_string;	/* contains pointer (not offset) to string */
	int		audit_char_count;
	int		permit_retry;	/* don't have to block on alloc failure; can retry */
};

/*
 * Arg operations
 */
#define EXARG_PREPEND		0x1
#define EXARG_APPEND		0x2
#define EXARG_MOD		0x4

/*
 * Arg pieces to operate on
 */
#define EXARG_ARGS		0x10
#define EXARG_ENV		0x20
#define EXARG_UFILE		0x40
#define EXARG_LOADER		0x80
#define EXARG_SHELL		0x100
#define EXARG_SHARGS		0x200

/*
 * Auxv operations
 */
#define EXARG_AUXADD		0x1000
#define EXARG_AUXDEL		0x2000
#define EXARG_AUXMOD		0x4000

/*
 * Arg alignment directives (boolean) for exec_copy*str()
 * routines
 */
#define EXARG_ALIGN		1
#define EXARG_NO_ALIGN		0

/*
 * Maximum number of auxv elements an exec can use.
 */
#define	MAX_EXEC_AUXV		5


/*
 * Prototypes for execargs manipulation functions.
 */

#ifdef _KERNEL
extern int exec_args_copyin(
	char *,			/* fname */
	char **,		/* uargp */
	char **,		/* uenvp */
	char *,			/* uloader */
	struct execargs *);	/* argbkp */
extern int exec_args_copyout(
	struct execargs *,	/* argbkp */
	char *,			/* loader */
	int,			/* flags */
	vm_offset_t *);		/* usp_loc */
extern vm_offset_t exec_args_allocate(void);
extern void exec_args_free(struct execargs *);
extern kauxv_t *exec_auxv_alloc(void);
extern void exec_auxv_dealloc(kauxv_t *);
extern int exec_auxv_operate(
	struct execargs *,	/* argbkp */
	int,			/* op */
	int,			/* type */
	union auxv_data *);	/* data */
extern int exec_copystr(
	char *,		/* src */
	char **,	/* destp */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *);	/* ncp */
extern int exec_copyinstr(
	caddr_t,	/* user_src */
	char **,	/* kernel_destp */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *,	/* ncp */
	int);		/* align */
extern int exec_copyoutstr(
	char **,	/* kernel_srcp */
	caddr_t,	/* user_dest */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *,	/* ncp */
	int);		/* align */
extern int interp_copyout(
	struct execargs *,	/* argbkp */
	caddr_t *,		/* user argpp */
	caddr_t *,		/* user bufferp */
	int *,			/* maxlengthp */
	unsigned *);		/* lencopiedp */
extern int exec_write_string(
	struct execargs *,	/* argbkp */
	char *,			/* string */
	int,			/* write_argv_entry */
	char **,		/* cpp */
	vm_offset_t *);		/* cpp_offset */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif /* _SYS_EXECARGS_H_ */
