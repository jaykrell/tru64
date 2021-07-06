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
 *	@(#)$RCSfile: signal.h,v $ $Revision: 1.1.12.4 $ (DEC) $Date: 1998/10/12 22:05:00 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

/*
 * COMPONENT_NAME: SYSPROC - signal.h
 *                                                                    
 * ORIGIN: 27
 *
 * Copyright International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 */                                                                   

#ifndef _ALPHA_SIGNAL_H_
#define _ALPHA_SIGNAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_KERNEL) && (defined(__LANGUAGE_C__) || defined(__cplusplus))
typedef int sig_atomic_t;
#endif

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#if	defined(_KERNEL) || defined (_SIGSET_OPS_MACROS)

/*
 * Macros to manipulate a sigset_t:
 *	sigemptyset, sigfillset, sigaddset, sigdelset,
 *	sigismember, sigsetdiff, sigsetsum, sigsetand,
 *	sigfirstset, siganyset, sigset32, sigcompl, sigseteq
 */

/* sigemptyset: clear a signal set */
#define _SIGEMPTYSET(setp)						\
	*(setp) = (sigset_t)0

/* sigfillset: fill a signal set */
#define _SIGFILLSET(setp)						\
	*(setp) = (sigset_t)~0

/* sigaddset: add signal S to set */
#define _SIGADDSET(setp, S)						\
	*(setp) |= (1L << ((S) - 1))

/* sigdelset: remove signal S from set */
#define _SIGDELSET(setp, S)						\
	*(setp) &= ~(1L << ((S) - 1))

/* sigismember: say whether S is a member of set */
#define _SIGISMEMBER(setp, S)						\
        ((*(setp) & (1L << ((S) - 1))) != (sigset_t)0)

/* sigsetdiff: create set of signals in setp not in set */
#define _SIGSETDIFF(setp, set)						\
	*(setp) &= ~(set)

/* sigsetsum: create set of signals in either (or both) sets */
#define _SIGSETSUM(setp, set)						\
	*(setp) |= (set)

/* sigsetand: create set of signal in only in both sets */
#define _SIGSETAND(setp, set)						\
	*(setp) &= (set)

/* sigfirstset: return signal number of first signal in set */
#ifdef _KERNEL
#define _SIGFIRSTSET(setp)						\
	(lsb(*(setp)) + 1)
#else
#define _SIGFIRSTSET(setp)						\
	ffs(*(setp))
#endif

/* siganyset: say whether setp has any signals set */
#define _SIGANYSET(setp)						\
	(*(setp) != 0)

/* sigset32: assign 32 bit mask to a sigset_t */
#define _SIGSET32(setp, S)						\
	*(setp) = (S);

/* sigsettomask: assign 64 bit mask to a 32-bit sigmask */
#define _SIGSETTOMASK(S, setp)						\
	(S) = *(setp);


/* sigsetcompl: complement a signal set */
#define _SIGSETCOMPL(setp, set)						\
	*(setp) = ~(set);

/* sigseteq: say whether two sets are equal */
#define _SIGSETEQ(setp, set)						     \
	*(setp) == (set)

#endif /*  defined(_KERNEL) || defined(_SIGSET_OPS_MACROS) */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
/*
 * These definition are also used in machdep.c.
 */
#define R_V0	0
#define R_A0	16
#define R_A1	17
#define R_A2	18
#define R_A3	19
#define R_A4	20
#define R_A5	21
#define R_SP	30
#endif

/* defines the machine dependent sigcontext structure */
#include <machine/context.h>

#define     ILL_RESAD_FAULT     0x0     /* reserved addressing fault */
#define     ILL_PRIVIN_FAULT    0x1     /* privileged instruction fault */
#define     ILL_RESOP_FAULT     0x2     /* reserved operand fault */
#define     ILL_INST_FAULT      0x3     /* Illegal instruction */
#define     ILL_MODE_FAULT      0x4     /* Illegal mode - VMSPAL only */


/* FPE signal code usage note:  In some previous releases, FAULT codes
were incorrectly used when TRAP codes should have been.  But, both then
and now, true TRAPs and FAULTs could be distinguished by comparing the
sc_pc and the sc_trap_pc fields of the signal context block.  With a true
FAULT, the sc_pc field contains the trigger PC of the faulting
instruction.  With a true TRAP, sc_pc contains the trap PC where the
exception was realized (and so it will be the same as sc_fp_trap_pc).
See the ieee(3) man page for details.

To continue from a FAULT (with the default IEEE result for the
exceptional operation), a signal handler might look something like:

    void fpe_handler(int sig, int code, struct sigcontext *scp)
    {
	. . . .
	if (scp->sc_pc != scp->sc_fp_trap_pc)
	    scp->sc_pc += 4;
	. . . .
    }

If it is a true FAULT, incrementing sc_pc by 4 is necessary to advance
the PC beyond the exceptional instruction.  (Or, the handler could
correct the exceptional condition and allow the faulting instruction to
re-execute).

For existing executables which cannot handle correct TRAP codes, the old,
incorrect behavior of always using FAULT codes can be restored by setting
a configurable system parameter:

    #  sysconfig -r generic use_faulty_fpe_traps=1

which will cause the system to continue to incorrectly use FAULT codes
when TRAP codes should be produced.  */

#define     FPE_INTOVF_TRAP     0x1     /* integer overflow */
#define     FPE_INTDIV_TRAP     0x2     /* integer divide by zero */
#define     FPE_FLTOVF_TRAP     0x3     /* floating overflow */
#define     FPE_FLTDIV_TRAP     0x4     /* floating/decimal divide by zero */
#define     FPE_FLTUND_TRAP     0x5     /* floating underflow */
#define     FPE_DECOVF_TRAP     0x6     /* decimal overflow */
#define     FPE_SUBRNG_TRAP     0x7     /* subscript out of range */
#define     FPE_FLTOVF_FAULT    0x8     /* floating overflow fault */
#define     FPE_FLTDIV_FAULT    0x9     /* divide by zero floating fault */
#define     FPE_FLTUND_FAULT    0xa     /* floating underflow fault */
#define     FPE_UNIMP_FAULT     0xb     /* Unimplemented FPU instruction */
#define     FPE_INVALID_FAULT   0xc     /* Invalid operation */
#define     FPE_INEXACT_FAULT   0xd     /* Inexact result */
#define	    FPE_HPARITH_TRAP	0xe	/* High performance trap */
#define     FPE_INTOVF_FAULT    0xf     /* Integer Overflow fault */
#define	    FPE_ILLEGAL_SHADOW_TRAP 0x10 /* Illegal Trap Shadow Trap */
#define	    FPE_GENTRAP		0x11	/* */

#ifndef _XOPEN_SOURCE_EXTENDED
#define BRK_USERBP        0       /* user bp (used by debuggers) */
#define BRK_KERNELBP      1       /* kernel bp (used by prom) */
#define BRK_ABORT         2       /* no longer used */
#define BRK_BD_TAKEN      3       /* for taken bd emulation */
#define BRK_BD_NOTTAKEN   4       /* for not taken bd emulation */
#define BRK_SSTEPBP       5       /* user bp (used by debuggers) */
#define BRK_OVERFLOW      6       /* overflow check */
#define BRK_DIVZERO       7       /* divide by zero check */
#define BRK_RANGE         8       /* range error check */
#define BRK_STACKOVERFLOW 9	  /* used by ada */
#endif

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#if defined(_KERNEL)
#define sigemptyset 	_SIGEMPTYSET
#define sigfillset 	_SIGFILLSET
#define sigaddset	_SIGADDSET
#define sigdelset	_SIGDELSET
#define sigismember	_SIGISMEMBER
#define sigsetdiff	_SIGSETDIFF
#define sigsetsum	_SIGSETSUM
#define sigsetand	_SIGSETAND
#define sigfirstset	_SIGFIRSTSET
#define siganyset	_SIGANYSET
#define sigset32	_SIGSET32
#define sigsetcompl	_SIGSETCOMPL
#define sigseteq	_SIGSETEQ
#define sigsettomask	_SIGSETTOMASK
#endif /*  defined(_KERNEL)  */

#ifdef __cplusplus
}
#endif
#endif /* _ALPHA_SIGNAL_H_ */
