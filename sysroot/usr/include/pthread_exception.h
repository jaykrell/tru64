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
 */
/*
 * @(#)$RCSfile: pthread_exception.h,v $ $Revision: 1.1.44.2 $ (DEC) $Date: 2002/05/13 20:48:43 $
 */

/*
 *  FACILITY:
 *
 *	DECthreads core
 *
 *  FILENAME:
 *
 *	pthread_exception.h
 *
 *  ABSTRACT:
 *
 *	Header file for exception handling in C
 *
 *  AUTHORS:
 *
 *	Eric Roberts
 *	Bob Conti
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	15 March 1989
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Bob Conti
 *	Paul Curtin
 *	Webb Scales
 *	Peter Portante
 *	Brian Silver
 *	Mark Simons
 *	Richard Love
 *	Tom Dahl
 *
 *  LAST MODIFICATION DATE:
 *
 *	21 October 1999
 */


/*
 * This header file consists of two sections. The first is ANSI/POSIX
 * "clean", with no names disallowed by the standards (all names either begin
 * with "_" and a capital letter, or "__" and a lower case letter, or use the
 * POSIX 1003.1c-1995 "extension" namespace "PTHREAD" prefix with "_NP"
 * suffix or "pthread" prefix with "_np" suffix). The second contains the
 * "namespace-polluting" (non-standard) definitions that we've traditionally
 * documented for client use -- TRY, ENDTRY, and so forth. The two sections
 * each have separate "ifndef" tests, which allows this header file to be
 * included twice by the same module (once for the clean definitions and once
 * for the polluting definitions) and have everything work out nicely. Note
 * that <pthread.h> always includes this header, so a separate include of
 * <pthread_exception.h> after <pthread.h> will automatically activate the
 * "unclean" definitions. (A strictly conforming standard application must not
 * do this, since <pthread_exception.h> is not defined by any standard.)
 *
 * Note that on Tru64 UNIX you cannot, currently, use this header AND
 * <c_excpt.h> (for native compiler try/except/finally handling) unless you
 * compile with _OSF_SOURCE defined. This is because <c_excpt.h> is not
 * "namespace clean" for POSIX or XOPEN, and (because this header requires
 * definitions from <c_excpt.h>) in strict standards mode we need to "fake" a
 * definition that will conflict with the actual definition in
 * <c_excpt.h>. This is OK, since, by default, all programs will be built with
 * _OSF_SOURCE defined (by <standards.h>), and a POSIX/XOPEN conforming
 * program (defining _XOPEN_SOURCE=500 or _POSIX_C_SOURCE=199506L) should not
 * be including non-standard headers like <c_excpt.h>. If you must compile
 * with c89, which automatically defines _XOPEN_SOURCE, but really don't wish
 * to require a strict XOPEN namespace, you can add "-D_OSF_SOURCE" to the c89
 * command to avoid this problem.
 */
#ifndef _PTHREAD_EXCEPTION_CLEAN
# define _PTHREAD_EXCEPTION_CLEAN

# ifdef __cplusplus
    extern "C" {
# endif

/*
 *  INCLUDE FILES
 */

#if defined (__DECCXX)
# define _PTHREAD_EXC_CXX
# define _PTHREAD_EXC_DECCXX
#elif defined (__cplusplus)
# define _PTHREAD_EXC_CXX
# elif defined (__DECC) || defined (__decc)
#  define _PTHREAD_EXC_DECC
#elif defined (__INTEL_COMPILER)
# define _PTHREAD_EXC_INTELC
#else
# endif

# if defined (VMS) || defined (__VMS) || defined (__vms) || defined (vms)
#  define _PTHREAD_EXC_VMS
# elif defined (__unix__) || defined (__unix) || defined (unix)
#  define _PTHREAD_EXC_UNIX
# endif

# if defined (__alpha) || defined (__ALPHA)
#  define _PTHREAD_EXC_ALPHA
# elif defined (__ia64__)
#  define _PTHREAD_EXC_IA64
# endif

# if defined (_PTHREAD_EXC_DECC) && defined (_PTHREAD_EXC_VMS)
#  pragma __extern_model __save
#  pragma __extern_model __strict_refdef
#  define _PTHREAD_EXC_IMPORT_	extern
#  include <builtins.h>
# else
#  define _PTHREAD_EXC_IMPORT_	extern
# endif

/*
 * Include the appropriate header files for the different operating systems.
 */
# if defined (_PTHREAD_EXC_VMS)
#  include <ints.h>
#  include <chfdef.h>
#  include <ssdef.h>
# endif

# include <setjmp.h>
# include <errno.h>

# if defined (_PTHREAD_EXC_UNIX) && defined (_PTHREAD_EXC_DECC)
#  ifdef _OSF_SOURCE
#   include <c_excpt.h>         /* Must be after setjmp.h */
#  else
extern void *__exception_info (void);
#  endif
#  define _PTHREAD_EXC_USE_NATIVE
#  define _PTHREAD_NATIVE_TRY		__builtin_try
#  define _PTHREAD_NATIVE_EXCEPT	__builtin_except
#  define _PTHREAD_NATIVE_FINALLY	__builtin_finally
#  define _PTHREAD_NATIVE_INFO		__exception_info ()
#  define _PTHREAD_NATIVE_HANDLE	EXCEPTION_EXECUTE_HANDLER
# endif

/*
 * This constant helps to identify a context block or exception created with
 * DECthreads BL9 or later; the new structures include a version field to
 * better manage future changes.
 */
# define _PTHREAD_EXC_NEWMAGIC	0x45586732 /* Identify ctx block with version */
# define _PTHREAD_EXC_THDBASE	(_PTHREAD_EXC_NEWMAGIC | 0x01)

/*
 * Define version constants to be put into exception structures.
 *
 * o  V2 is for OpenVMS and non-native Tru64 UNIX exception handling.
 * o  V3 is for native Tru64 UNIX exception handling (as defined before the
 *    __flags field was added to _pthreadExcExt_t).
 * o  V4 is for native Tru64 UNIX exception handling with the __flags field.
 *
 * This code checks the version to see how it should behave.
 */
# define _PTHREAD_EXC_VER_V2	2
# define _PTHREAD_EXC_VER_V3	3
# define _PTHREAD_EXC_VER_V4	4
# if defined (_PTHREAD_EXC_UNIX) && defined (_PTHREAD_EXC_DECC)
#  define _PTHREAD_EXC_VER_CUR	_PTHREAD_EXC_VER_V4
# else
#  define _PTHREAD_EXC_VER_CUR	_PTHREAD_EXC_VER_V2
# endif

/*
 * NOTE: on UNIX systems, these status codes must be kept unique. We do this
 * arbitrarily by setting some high order bits which happen to be the same as
 * we use on VMS.
 */
# if defined (_PTHREAD_EXC_VMS)
#  define _PTHREAD_EXC_FACILITY	00020100000
#  define _PTHREAD_STATUS_(_val_, _sev_) \
    ((__pthreadStatus_t)(_PTHREAD_EXC_FACILITY | ((_val_) << 3) | (_sev_)))
# else
#  define _PTHREAD_EXC_FACILITY	0x177db000
#  define _PTHREAD_STATUS_(_val_, _sev_) \
    ((__pthreadStatus_t)(_PTHREAD_EXC_FACILITY | (_val_)))
# endif

/*
 * Define all of the status codes used by DECthreads.
 *
 * For VMS, these must remain in synch with the CMA_MESSAGE.MSG message file.
 *
 * These values cannot be altered, as they have already been shipped!
 */

/*
 * Messages directly related to exceptions
 */
# define __pthread_exception_s		_PTHREAD_STATUS_ (1, 4)
# define __pthread_exccop_s		_PTHREAD_STATUS_ (2, 4)
# define __pthread_uninitexc_s		_PTHREAD_STATUS_ (3, 4)
# define __pthread_unkstatus_s		_PTHREAD_STATUS_ (128, 4)
# define __pthread_exccoplos_s		_PTHREAD_STATUS_ (129, 4)
# define __pthread_noexcmem_s		_PTHREAD_STATUS_ (131, 4)

/*
 * These should be set to match with underlying system exception codes on
 * platforms where that is appropriate (e.g., ss$_ codes on VMS).
 */
# if defined (_PTHREAD_EXC_VMS)
#  pragma nostandard
/*
 * A few of these codes are somewhat imaginary, since VMS doesn't support
 * condition codes that very closely approximate the sense of some UNIX
 * signals. SIGTRAP, SIGABRT, and SIGEMT have no clear parallels, and the
 * values chosen are fairly arbitrary. For two others, we chose what seemed
 * close equivalents: SIGPIPE becomes "no mailbox", and SIGXFSZ becomes "disk
 * quota exceeded".
 */
#  define __pthread_illaddr_s		SS$_ACCVIO
#  define __pthread_exquota_s		SS$_EXQUOTA
#  define __pthread_insfmem_s		SS$_INSFMEM
#  define __pthread_nopriv_s		SS$_NOPRIV
#  define __pthread_normal_s		SS$_NORMAL
#  define __pthread_illinstr_s		SS$_OPCDEC
#  define __pthread_resaddr_s		SS$_RADRMOD
#  define __pthread_privinst_s		SS$_OPCDEC
#  define __pthread_resoper_s		SS$_ROPRAND
#  define __pthread_SIGTRAP_s		SS$_BREAK
#  define __pthread_SIGABRT_s		SS$_ABORT
#  define __pthread_SIGEMT_s		SS$_COMPAT
#  define __pthread_aritherr_s		SS$_FLTOVF
#  define __pthread_SIGSYS_s		SS$_BADPARAM
#  define __pthread_SIGPIPE_s		SS$_NOMBX
#  define __pthread_excpu_s		SS$_EXCPUTIM
#  define __pthread_exfilsiz_s		SS$_EXDISKQUOTA
#  define __pthread_intovf_s		SS$_INTOVF
#  define __pthread_intdiv_s		SS$_INTDIV
#  define __pthread_fltovf_s		SS$_FLTOVF
#  define __pthread_fltdiv_s		SS$_FLTDIV
#  define __pthread_fltund_s		SS$_FLTUND
#  define __pthread_decovf_s		SS$_DECOVF
#  define __pthread_subrng_s		SS$_SUBRNG
#  define __pthread_stackovf_s		SS$_STKOVF
#  pragma standard
# else
#  define __pthread_illaddr_s		_PTHREAD_STATUS_ (5, 4)
#  define __pthread_exquota_s		_PTHREAD_STATUS_ (6, 4)
#  define __pthread_insfmem_s		_PTHREAD_STATUS_ (7, 4)
#  define __pthread_nopriv_s		_PTHREAD_STATUS_ (8, 4)
#  define __pthread_normal_s		_PTHREAD_STATUS_ (9, 1)
#  define __pthread_illinstr_s		_PTHREAD_STATUS_ (10, 4)
#  define __pthread_resaddr_s		_PTHREAD_STATUS_ (11, 4)
#  define __pthread_privinst_s		_PTHREAD_STATUS_ (12, 4)
#  define __pthread_resoper_s		_PTHREAD_STATUS_ (13, 4)
#  define __pthread_SIGTRAP_s		_PTHREAD_STATUS_ (14, 4)
#  define __pthread_SIGABRT_s		_PTHREAD_STATUS_ (15, 4)
#  define __pthread_SIGEMT_s		_PTHREAD_STATUS_ (16, 4)
#  define __pthread_aritherr_s		_PTHREAD_STATUS_ (17, 4)
#  define __pthread_SIGSYS_s		_PTHREAD_STATUS_ (18, 4)
#  define __pthread_SIGPIPE_s		_PTHREAD_STATUS_ (19, 4)
#  define __pthread_excpu_s		_PTHREAD_STATUS_ (20, 4)
#  define __pthread_exfilsiz_s		_PTHREAD_STATUS_ (21, 4)
#  define __pthread_intovf_s		_PTHREAD_STATUS_ (22, 4)
#  define __pthread_intdiv_s		_PTHREAD_STATUS_ (23, 4)
#  define __pthread_fltovf_s		_PTHREAD_STATUS_ (24, 4)
#  define __pthread_fltdiv_s		_PTHREAD_STATUS_ (25, 4)
#  define __pthread_fltund_s		_PTHREAD_STATUS_ (26, 4)
#  define __pthread_decovf_s		_PTHREAD_STATUS_ (27, 4)
#  define __pthread_subrng_s		_PTHREAD_STATUS_ (28, 4)
#  define __pthread_stackovf_s		_PTHREAD_STATUS_ (57, 4)
# endif

/*
 * Synonyms for signal-based exception statuses.
 */
# define __pthread_SIGIOT_s		__pthread_SIGABRT_s
# define __pthread_SIGSEGV_s		__pthread_illaddr_s
# define __pthread_SIGBUS_s		__pthread_resaddr_s
# define __pthread_SIGFPE_s		__pthread_aritherr_s

/*
 * Internal DECthreads exception statuses.
 */
# define __pthread_cancel_s		_PTHREAD_STATUS_ (48, 4)
# define __pthread_exit_s		_PTHREAD_STATUS_ (52, 4)

/* 
 * The DECthreads "uniplemented" status.
 */
# define _PTHREAD_UNIMP_S		_PTHREAD_STATUS_ (61, 4)

/*
 * TYPEDEFS
 */

# if defined (_PTHREAD_EXC_VMS)
#  ifdef __INITIAL_POINTER_SIZE
#   pragma __required_pointer_size __save
#   pragma __required_pointer_size __short
#  endif
# endif

typedef void		*__pthreadExcAddr_t, **__pthreadExcAddr_p;
typedef long		__pthreadExcLong_t, *__pthreadExcLong_p;
typedef short		__pthreadExcShort_t, *__pthreadExcShort_p;
typedef unsigned long	__pthreadExcUns_t, *__pthreadExcUns_p;
typedef unsigned long	__pthreadStatus_t;

/*
 * Constants for the kind of an exception object.
 *
 * There are *currently* only two kinds.  In the address-kind, the identity
 * of an exception object is its address; in the value-kind, the
 * identity of an exception object is an integer, typically,
 * a system-defined-status-value. These coded kinds also
 * serve as sentinels to help detect uninitialized exceptions.
 */
typedef enum __pthreadExcKind_t {
    _PTHREAD_EXC_KIND_NONE	= 0,
    _PTHREAD_EXC_KIND_ADDR	= 0x02130455,
    _PTHREAD_EXC_KIND_STATUS	= 0x02130456
    } __pthreadExcKind_t;

# if defined (_PTHREAD_EXC_VMS)
  typedef unsigned __int64	__pthreadExcJumpBuf_t[(14+8+3)];
# else
typedef sigjmp_buf		__pthreadExcJumpBuf_t;
# endif

# if defined (_PTHREAD_EXC_VMS)
typedef __int64	__pthreadExcArg_t, *__pthreadExcArg_p;
# else
typedef long	__pthreadExcArg_t, *__pthreadExcArg_p;
# endif

/*
 * Flags which are stored in the __flags field below.
 */
# define _PTHREAD_EXC_FLG_NATEXC  0x1 /* __args pts to native exc */
# define _PTHREAD_EXC_FLG_HEAPARG 0x2 /* __args points to heap mem */

typedef struct __pthreadExcExt {
    __pthreadExcLong_t	__sentinel;
    __pthreadExcShort_t	__version;
    __pthreadExcShort_t	__flags;
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int	__reserved0;	/* Alignment padding */
# endif
    __pthreadExcAddr_t	__extend;
    __pthreadExcArg_p	__args;
    } __pthreadExcExt_t;

typedef struct __pthreadExcKindV1Addr {
    __pthreadExcKind_t	__kind;
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int	__reserved0;	/* Alignment padding */
# endif
    __pthreadExcAddr_t	__address;
    __pthreadExcUns_t	__filler[6];
    } __pthreadExcKindV1Addr_t;

typedef struct __pthreadExcKindV1Status {
    __pthreadExcKind_t	__kind;
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int	__reserved0;	/* Alignment padding */
# endif
    __pthreadExcUns_t	__status;
    __pthreadExcUns_t	__filler[6];
    } __pthreadExcKindV1Status_t;

typedef struct __pthreadExcKindAddr {
    __pthreadExcKind_t	__kind;
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int	__reserved0;	/* Alignment padding */
# endif
    __pthreadExcAddr_t	__address;
    __pthreadExcExt_t	__ext;
    } __pthreadExcKindAddr_t;

typedef struct __pthreadExcKindStatus {
    __pthreadExcKind_t	__kind;
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int	__reserved0;	/* Alignment padding */
# endif
    __pthreadStatus_t	__status;
    __pthreadExcExt_t	__ext;
    } __pthreadExcKindStatus_t;

typedef union __pthreadExceptionObj {
    __pthreadExcKind_t		__kind;
    __pthreadExcKindV1Status_t	__v1status;
    __pthreadExcKindV1Addr_t	__v1address;
    __pthreadExcKindStatus_t	__status;
    __pthreadExcKindAddr_t	__address;
    } __pthreadExceptionObj_t, *__pthreadExceptionObj_p;

/*
 * Constants for the state of handling in the current TRY clause.
 *
 * The implementations of TRY/ENDTRY use the "NONE", "ACTIVE" and "HANDLED"
 * states.  The state variable defined by the TRY macro is set to "NONE" when
 * no exception has been raised, "ACTIVE" when one has been raised but has not
 * been caught by a CATCH clause, and "HANDLED" after the exception has been
 * caught and handled by some CATCH clause.
 */
typedef enum __pthreadExcState_t {
    _PTHREAD_EXC_STATE_ACTIVE	= 0, /* This must be the 0 state, see pop_ctx */
    _PTHREAD_EXC_STATE_NONE	= 1,
    _PTHREAD_EXC_STATE_HANDLED	= 2,
    _PTHREAD_EXC_STATE_POPPED	= 3
    } __pthreadExcState_t;

/*
 * Structure of a context block.
 *
 * A context block is allocated in the current stack frame for each
 * TRY clause.  These context blocks are linked to form a stack of
 * all current TRY blocks in the current thread.  Each context block
 * contains a jump buffer for use by setjmp and longjmp.  Note that
 * for binary compatibility reasonse the jump buffer must be at the
 * beginning.
 */
# if defined (_PTHREAD_EXC_VMS)
#  define _PTHREAD_EXC_ARGS	160 / sizeof (__pthreadExcArg_t)
# endif

# if defined (_PTHREAD_EXC_UNIX)
/*
 * Define the maximum number of parameters we will save in the DECthreads
 * exception block. Also used to define the cut-off between the fast path
 * storing of a native exception and the slow path (exceptions larger than
 * this number of arguments take the slow path).
 */
#  define _PTHREAD_EXC_ARGS	5

/*
 * Definition of a native Tru64 UNIX exception; a copy of system_exrec_type
 * from excpt.h (but that master definition is not included here for
 * namespace reasons).
 */
typedef struct __pthreadExcNative {
    long		__exceptionCode;	/* reason for exception */
    __pthreadExcUns_t	__exceptionFlags;	/* in progress, e.g. unwind */
    void		*__exceptionRecord;	/* rec chain, e.g.nested info */
    void		*__exceptionAddress;	/* where error occurred */
    __pthreadExcUns_t	__numberParameters;	/* # of ExceptionInformation's*/
    __pthreadExcUns_t	__exceptionInformation[_PTHREAD_EXC_ARGS];
    } __pthreadExcNative_t;
# endif

typedef struct __pthreadExcCtx {
    __pthreadExcJumpBuf_t	__jmp;		/* Jump buffer */
    volatile struct __pthreadExcCtx *__link;	/* Link to ctx block stack */
    volatile __pthreadExceptionObj_t __cur_exception; /* Copy of exception */
    volatile __pthreadExcState_t __exc_state;	/* State of handling for TRY */
# if defined (_PTHREAD_EXC_VMS)
    __pthreadExcAddr_t		__current_frame; /* Addr of curr stack frame */
# endif
# if defined (_PTHREAD_EXC_UNIX)
    unsigned int		__reserved0;	/* Alignment padding */
# endif
    __pthreadExcLong_t		__sentinel;	/* Identify ctx block */
    __pthreadExcLong_t		__version;	/* Client context version */
# if defined (_PTHREAD_EXC_UNIX)
    __pthreadExcNative_t	__exrec_copy; /* Copy of small foreign exc */
# endif
# if defined (_PTHREAD_EXC_VMS)
    __pthreadExcArg_t		__exc_args[_PTHREAD_EXC_ARGS];
# endif
    } __pthreadExcCtx_t, *__pthreadExcCtx_p;

# if defined (_PTHREAD_EXC_VMS)
#  ifdef __INITIAL_POINTER_SIZE
#   pragma __required_pointer_size __restore
#  endif
# endif

/*
 * EXTERNAL ROUTINES
 */

# if defined (_PTHREAD_EXC_VMS) && defined (_PTHREAD_CORE_BUILD_)
#  define __pthread_exc_handler_np excCoreHandler
# else
#  define __pthread_exc_handler_np pthread_exc_handler_np
# endif


# if defined (_PTHREAD_EXC_VMS)
extern int pthread_exc_savecontext_np (volatile unsigned __int64 *);
extern unsigned long pthread_exc_restorecontext_np (void);
# else
#  if defined (_PTHREAD_EXC_UNIX)
/*
 * Tru64 UNIX already provides prototypes for setjmp and longjmp in
 * /usr/include/setjmp.h; the prototypes here must be compatible, so we'll
 * just cast the volatile jump buffer inside the macro instead of defining an
 * appropriate prototype as we do elsewhere.
 */
#   define pthread_exc_savecontext_np(__env) sigsetjmp ((__env), 1)
#  else
#   define pthread_exc_savecontext_np(__env) setjmp ((__env))
#  endif
# endif

/*
 * On VMS, use an extern function to get the FP
 */
# if defined (_PTHREAD_EXC_VMS)
extern __pthreadExcAddr_t pthread_exc_fetch_fp_np (void);
# endif
# if defined (_PTHREAD_EXC_USE_NATIVE)
extern int pthread_exc_filter_np (
	__pthreadExcState_t, void *, __pthreadExceptionObj_p);
# endif
extern void pthread_exc_get_message_np (__pthreadExceptionObj_p, int, char *);
extern int pthread_exc_matches_np (
	__pthreadExceptionObj_p, __pthreadExceptionObj_p);
extern void pthread_exc_pop_ctx_np (__pthreadExcCtx_p);
extern void pthread_exc_push_ctx_np (__pthreadExcCtx_p);
extern void pthread_exc_raise_np (__pthreadExceptionObj_p);
extern void pthread_exc_raise_status_np (__pthreadStatus_t);
extern void pthread_exc_report_np (__pthreadExceptionObj_p);

# if defined (_PTHREAD_EXC_VMS) && !defined (_PTHREAD_SUPPRESS_EXTERNALS_)
/*
 * System condition handler
 *
 * The declaration below is conditionalized to allow for compilation on
 * V7.1 systems.  On OpenVMS V7.1, for the __NEW_STARLET case only,
 * chf$mech_array equates to a type (CHFDEF2), whereas for the default
 * (__OLD_STARLET) case, it equates to a structure tag.  As of V7.2,
 * chfdef.h was modified to equate chf$mech_array to the structure tag
 * regardless of the __NEW_STARLET value.
 */
#  pragma nostandard
extern int
#  if (__VMS_VER < 70200000) && defined (__NEW_STARLET)
__pthread_exc_handler_np (unsigned int[], chf$mech_array*);
#  else
__pthread_exc_handler_np (unsigned int[], struct chf$mech_array*);
#  endif
#  pragma standard
# endif

/*
 * CONSTANTS AND MACROS
 */

/*
 * Define exception initializer macro. All exceptions *must* be initialized
 * using this macro.
 */
# if defined (_PTHREAD_EXC_UNIX)
#  define PTHREAD_EXCEPTION_INIT_NP(_e_)   ( \
    (_e_).__address.__address = (__pthreadExcAddr_t)&(_e_), \
    (_e_).__address.__kind = _PTHREAD_EXC_KIND_ADDR, \
    (_e_).__address.__ext.__sentinel = _PTHREAD_EXC_NEWMAGIC, \
    (_e_).__address.__ext.__version = _PTHREAD_EXC_VER_CUR, \
    (_e_).__address.__ext.__flags = 0, \
    (_e_).__address.__ext.__reserved0 = 0, \
    (_e_).__address.__ext.__extend = (__pthreadExcAddr_t)0L, \
    (_e_).__address.__ext.__args = (__pthreadExcArg_p)0L)
# else
#  define PTHREAD_EXCEPTION_INIT_NP(_e_)   ( \
    (_e_).__address.__address = (__pthreadExcAddr_t)&(_e_), \
    (_e_).__address.__kind = _PTHREAD_EXC_KIND_ADDR, \
    (_e_).__address.__ext.__sentinel = _PTHREAD_EXC_NEWMAGIC, \
    (_e_).__address.__ext.__version = _PTHREAD_EXC_VER_CUR, \
    (_e_).__address.__ext.__flags = 0, \
    (_e_).__address.__ext.__extend = (__pthreadExcAddr_t)0L, \
    (_e_).__address.__ext.__args = (__pthreadExcArg_p)0L)
# endif

/*
 * Define a function to convert a portable address exception to a platform
 * specific status exception.
 */
# if defined (_PTHREAD_EXC_VMS)
#  define pthread_exc_set_status_np(_e_,_s_) ( \
    (_e_)->__status.__kind = _PTHREAD_EXC_KIND_STATUS, \
    (_e_)->__status.__status = ((_s_) & ~7) | 4)
# else
#  define pthread_exc_set_status_np(_e_,_s_) ( \
    (_e_)->__status.__kind = _PTHREAD_EXC_KIND_STATUS, \
    (_e_)->__status.__status = (_s_))
# endif

/*
 * Define "routine" to return the status of an exception. Returns 0 if status
 * kind (and value of status in *s), or EINVAL if not status kind.
 */
# define pthread_exc_get_status_np(_e_,_s_) ( \
    (_e_)->__status.__kind == _PTHREAD_EXC_KIND_STATUS ? \
	(*(_s_) = (_e_)->__status.__status, 0) : \
	EINVAL)

/*
 * Define "statement" for clients to use to raise an exception.
 */
# define PTHREAD_RAISE_NP(_e_) pthread_exc_raise_np (&(_e_))

# if defined (_PTHREAD_EXC_VMS)
#   pragma nostandard
#   define pthread_exc_establish_np(_exc_ctx_) \
	(_exc_ctx_)->__current_frame = \
		((__pthreadExcAddr_t)pthread_exc_fetch_fp_np ()); \
	lib$establish (__pthread_exc_handler_np);
#   pragma standard
#   define pthread_exc_unestablish_np(_exc_ctx_)
# else
#  define pthread_exc_establish_np(_exc_ctx_)
#  define pthread_exc_unestablish_np(_exc_ctx_)
# endif

/*
 * Define version constants to be put into exception context structures.
 *
 * o  V2 is for OpenVMS and non-native Digital UNIX exception handling.
 * o  V3 is for native Digital UNIX exception handling.
 * o  V4 was added in Digital UNIX V4.0D (with the __reserved0 field).
 * o  V5 is for support of UNIX foreign exceptions (space added to hold a copy
 *    of a small native exception with arguments).
 *
 * This code checks the version to see how it should behave.
 */
# define _PTHREAD_EXC_CTX_V2	2
# define _PTHREAD_EXC_CTX_V3	3
# define _PTHREAD_EXC_CTX_V4	4
# define _PTHREAD_EXC_CTX_V5	5

# if defined (_PTHREAD_EXC_USE_NATIVE)
#  if defined (_PTHREAD_EXC_UNIX)
#   define _PTHREAD_EXC_CTX_CUR	_PTHREAD_EXC_CTX_V5
#  else
#   define _PTHREAD_EXC_CTX_CUR	_PTHREAD_EXC_CTX_V4
#  endif
# else
#  define _PTHREAD_EXC_CTX_CUR	_PTHREAD_EXC_CTX_V2
# endif

/*
 * Start a new TRY block, which may contain exception handlers.
 *
 * For Tru64 UNIX:
 *
 *   Set up a native C "try {} except() {}" block. Note that previous
 *   implementations of TRY/ENDTRY on Tru64 UNIX used setjmp/longjmp as
 *   described below. We still have to use a context block to make sure
 *   pthread_exc_raise_np() will know how to raise the exception. So we
 *   allocate a context block on the stack to remember the current exception.
 *   Push it on the context block stack. Initialize this context block to
 *   indicate that no exception is active. Then we enter the while loop
 *   surrounding the native try block. The try block guards a block of
 *   statements ended by one of the following macros: CATCH, CATCH_ALL,
 *   FINALLY or ENDTRY.
 *
 * For all other platforms:
 *
 *   Allocate a context block on the stack to remember the current exception.
 *   Push it on the context block stack. Initialize this context block to
 *   indicate that no exception is active. Do a SETJMP to snapshot this
 *   environment (or return to it). Then, start a block of statements to be
 *   guarded by the TRY clause. This block will be ended by one of the
 *   following macros: CATCH, CATCH_ALL, FINALLY or ENDTRY.
 */
# if defined (_PTHREAD_EXC_VMS)
#  define _PTHREAD_INIT_CTX(_ctx_) \
	PTHREAD_EXCEPTION_INIT_NP (_ctx_.__cur_exception); \
	_ctx_.__cur_exception.__kind = _PTHREAD_EXC_KIND_STATUS; \
	_ctx_.__exc_state = _PTHREAD_EXC_STATE_NONE; \
	_ctx_.__sentinel = _PTHREAD_EXC_NEWMAGIC; \
	_ctx_.__version = _PTHREAD_EXC_CTX_CUR; \
	_ctx_.__exc_args[0] = (__pthreadExcArg_t)0
# else
#  define _PTHREAD_INIT_CTX(_ctx_) \
	PTHREAD_EXCEPTION_INIT_NP (_ctx_.__cur_exception); \
	_ctx_.__cur_exception.__kind = _PTHREAD_EXC_KIND_STATUS; \
	_ctx_.__exc_state = _PTHREAD_EXC_STATE_NONE; \
	_ctx_.__sentinel = _PTHREAD_EXC_NEWMAGIC; \
	_ctx_.__version = _PTHREAD_EXC_CTX_CUR
# endif
# if defined (_PTHREAD_EXC_USE_NATIVE)
#  define PTHREAD_TRY_NP \
    { \
    __pthreadExcCtx_t __exc_ctx__; \
    _PTHREAD_INIT_CTX (__exc_ctx__); \
    pthread_exc_push_ctx_np (&__exc_ctx__); \
    while (__exc_ctx__.__exc_state != _PTHREAD_EXC_STATE_HANDLED) { \
	_PTHREAD_NATIVE_TRY { \
	    if (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_NONE) {
	    /* user's block of code goes here */
# else
#  define PTHREAD_TRY_NP \
    { \
    __pthreadExcCtx_t __exc_ctx__; \
    _PTHREAD_INIT_CTX (__exc_ctx__); \
    pthread_exc_push_ctx_np (&__exc_ctx__); \
    pthread_exc_establish_np (&__exc_ctx__); \
    if (!pthread_exc_savecontext_np (__exc_ctx__.__jmp)) {
	/* user's block of code goes here */
# endif

/*
 * Define an PTHREAD_CATCH_NP(_e_) clause (or exception handler).
 *
 * For all platforms:
 *
 *   First, end the prior block. Then, check if the current exception matches
 *   what the user is trying to catch with the CATCH clause. If there is a
 *   match, a variable is declared to support lexical nesting of
 *   PTHREAD_RERAISE_NP statements, and the state of the current exception is
 *   changed to "handled".
 *
 * For Tru64 UNIX:
 *   Note we have to make sure we are in the correct state to deal with with
 *   the exception at all.
 */
# if defined (_PTHREAD_EXC_USE_NATIVE)
#  define PTHREAD_CATCH_NP(_e_) \
    } \
    if ((__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_ACTIVE) \
	    && (pthread_exc_matches_np ( \
		    (__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception, \
		    &(_e_)))) { \
	__pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
	    (__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception; \
	__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED;
	/* user's block of code goes here */
# else
#  define PTHREAD_CATCH_NP(_e_) \
	} \
    else if (pthread_exc_matches_np ( \
	    (__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception, &(_e_))) { \
	__pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
		(__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception; \
	__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED;
	/* user's block of code goes here */
# endif

/*
 * Define an PTHREAD_CATCH_ALL_NP clause (or "catchall" handler).
 *
 * For all other platforms:
 *
 *   First, end the prior block. Then, unconditionally, let execution enter
 *   into the catchall code. As with a normal catch, a variable is declared
 *   to support lexical nesting of PTHREAD_RERAISE_NP statements, and the
 *   state of the current exception is changed to "handled".
 *
 * For Tru64 UNIX:
 *   Note we have to make sure we are in the correct state to deal with with
 *   the exception at all.
 */
# if defined (_PTHREAD_EXC_USE_NATIVE)
#  define PTHREAD_CATCH_ALL_NP \
		} \
	    if (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_ACTIVE) { \
		__pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
			(__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception; \
		__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED;
		/* user's block of code goes here */
# else
#  define PTHREAD_CATCH_ALL_NP \
	} \
    else { \
	__pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
		(__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception; \
	__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED;
	/* user's block of code goes here */
# endif

/*
 * Define a PTHREAD_RERAISE_NP statement.
 *
 * This "statement" is valid only if lexically nested in a CATCH or
 * CATCH_ALL clause.  Reraise the current lexically visible exception.
 */
# define PTHREAD_RERAISE_NP pthread_exc_raise_np (PTHREAD_THIS_CATCH_NP)

/*
 * Define a PTHREAD_FINALLY_NP clause
 *
 * For all platforms:
 *
 *   This "keyword" starts a PTHREAD_FINALLY_NP clause.  It must appear before
 *   an ENDTRY.  A PTHREAD_FINALLY_NP clause will be entered after normal exit
 *   of the TRY block, or if an unhandled exception tries to propagate
 *   out of the TRY block.
 *
 *   Unlike Modula 3's TRY clause, we do not expend overhead trying to
 *   enforce that FINALLY be mutually exclusive with CATCH clauses.  Currently,
 *   if they are used together, then control will drop into a FINALLY clause
 *   under the following conditions:
 *	o normal exit from TRY,
 *	o an exception is raised and no CATCH is present (recommended usage)
 *	o CATCH's are present but none matches the exception.
 *	o CATCH's are present and one matches the exception, but it
 *	  does not raise or reraise any exceptions.
 *   That is, FINALLY is always entered after TRY unless a CATCH clause raises
 *   (or re-raises) an exception.
 *
 *			** WARNING **
 *   You should *avoid* using FINALLY with CATCH clauses, that is, use it
 *   only as TRY {} FINALLY {} ENDTRY.  Source code that combines CATCHes
 *   with FINALLY in the same TRY clause is considered "unsupported"
 *   -- that is, such code may be broken by a future version of this
 *   package.
 *
 *   There are several reasons this restriction is necessary:
 *	o FINALLY may be added to C++ and its combination with CATCH
 *	  clauses may have different semantics than implemented by these macros.
 *	o The restriction is consistant with the same restriction in Modula 3
 *	o It allows the use of the 2-phase or "debugging" implementation
 *	  technique of the SRC exception package for these same macros.
 */
# if defined (_PTHREAD_EXC_USE_NATIVE)
#  define PTHREAD_FINALLY_NP \
		} \
	    if (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_NONE) { \
		pthread_exc_pop_ctx_np (&__exc_ctx__); \
		__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED; \
		} \
	    { \
	    __pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
		    (__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception;
	    /* user's block of code goes here */
# else
#  define PTHREAD_FINALLY_NP \
	} \
    if (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_NONE) \
	pthread_exc_pop_ctx_np (&__exc_ctx__); \
	{ \
	__pthreadExceptionObj_p PTHREAD_THIS_CATCH_NP = \
		(__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception;
	/* user's block of code goes here */
# endif

/*
 * End the whole TRY clause
 *
 * For Tru64 UNIX:
 *   There are two main parts to the operation to this macro. The first thing
 *   we do is close of the previous block. Then we define the except clause
 *   for the native try/except block and then we close out the while loop.
 *   The while loop is used to drive the state machine which the TRY macro
 *   began to setup. If we have reached this point in the loop and the state
 *   of the exception is "ACTIVE" we will raise the exception to allow
 *   another frame to handle it. Note that we don't have to remove the
 *   context block from the stack since the process of raising an exception
 *   already does. If the state is "NONE" when we reach this point, we remove
 *   the context block and change our state to "HANDLED" so that we can exit
 *   TRY block normally.
 *
 *   The except clause is what causes the state to be changed from "NONE" to
 *   "ACTIVE". When a native exception is raised, the except clause calls the
 *   filter routine to decide if the exception should be handled. The filter
 *   is called with the current state of our TRY block, the exception which
 *   is being raised and the __pthreadExceptionObj_t structure to be filled
 *   in should we want to handle the exception. The filter asks if the
 *   exception is a native DECthreads exception being raised. If so, the
 *   exception structure is filled in and then exception facility called the
 *   exception block defined after the except statement. The exception block
 *   simply changes the state of our TRY block from "NONE" to "ACTIVE". We
 *   have now "caught" the exception and we loop back up to beginning of the
 *   TRY block and look for any CATCH blocks or a FINALLY block to execute.
 *
 * For all other platforms:
 *   We close off the block for the previous block and then tear down the
 *   context we established in the opening TRY. If an exception never
 *   occurred or we did not handle the exception, we pop the context block
 *   off the context stack. Note that popping the context block off the stack
 *   will cause an exception to be raised if the context block describes an
 *   unhandled exception.
 */
# if defined (_PTHREAD_EXC_USE_NATIVE)
#  define PTHREAD_ENDTRY_NP \
	    } \
	    if ((__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_NONE) \
		    || (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_ACTIVE)) \
		pthread_exc_pop_ctx_np (&__exc_ctx__); \
		__exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_HANDLED; \
	    } \
	_PTHREAD_NATIVE_EXCEPT (pthread_exc_filter_np ( \
		    __exc_ctx__.__exc_state, \
		    (void *)_PTHREAD_NATIVE_INFO, \
		    (__pthreadExceptionObj_p)&__exc_ctx__.__cur_exception)) { \
	    __exc_ctx__.__exc_state = _PTHREAD_EXC_STATE_ACTIVE; \
	    } \
	} \
    }
# else
#  define PTHREAD_ENDTRY_NP \
	} \
    pthread_exc_unestablish_np (&__exc_ctx__); \
    if ((__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_NONE) \
	    || (__exc_ctx__.__exc_state == _PTHREAD_EXC_STATE_ACTIVE)) \
	pthread_exc_pop_ctx_np (&__exc_ctx__); \
    }
# endif

/*
 * Define the exception variables
 */
# if defined (__STDC__) || defined (_PTHREAD_EXC_DECC) || defined (_PTHREAD_EXC_CXX)
#  define _PTHREAD_EXCNAME(name)	pthread_exc_##name##_e
#  define _PTHREAD_PTDNAME(name)	pthread_##name##_e
# else
#  define _PTHREAD_EXCNAME(name)	pthread_exc_/**/name/**/_e
#  define _PTHREAD_PTDNAME(name)	pthread_/**/name/**/_e
# endif

# if !defined (_EXC_NO_EXCEPTIONS_) && !defined (_PTHREAD_CORE_BUILD_)
_PTHREAD_EXC_IMPORT_ __pthreadExceptionObj_t
    _PTHREAD_EXCNAME (uninitexc),
    _PTHREAD_EXCNAME (illaddr),
    _PTHREAD_EXCNAME (exquota),
    _PTHREAD_EXCNAME (insfmem),
    _PTHREAD_EXCNAME (nopriv),
    _PTHREAD_EXCNAME (illinstr),
    _PTHREAD_EXCNAME (resaddr),
    _PTHREAD_EXCNAME (privinst),
    _PTHREAD_EXCNAME (resoper),
    _PTHREAD_EXCNAME (SIGTRAP),
    _PTHREAD_EXCNAME (SIGABRT),
    _PTHREAD_EXCNAME (SIGEMT),
    _PTHREAD_EXCNAME (aritherr),
    _PTHREAD_EXCNAME (SIGSYS),
    _PTHREAD_EXCNAME (SIGPIPE),
    _PTHREAD_EXCNAME (excpu),
    _PTHREAD_EXCNAME (exfilsiz),
    _PTHREAD_EXCNAME (intovf),
    _PTHREAD_EXCNAME (intdiv),
    _PTHREAD_EXCNAME (fltovf),
    _PTHREAD_EXCNAME (fltdiv),
    _PTHREAD_EXCNAME (fltund),
    _PTHREAD_EXCNAME (decovf),
    _PTHREAD_EXCNAME (subrng),
    _PTHREAD_PTDNAME (cancel),
    _PTHREAD_PTDNAME (exit),
    _PTHREAD_PTDNAME (stackovf),
    _PTHREAD_EXCNAME (noexcmem);

#  define pthread_exc_SIGIOT_e	pthread_exc_SIGABRT_e
#  define pthread_exc_SIGSEGV_e	pthread_exc_illaddr_e
#  define pthread_exc_SIGBUS_e	pthread_exc_resaddr_e
#  define pthread_exc_SIGFPE_e	pthread_exc_aritherr_e
#  define pthread_exc_SIGILL_e	pthread_exc_illinstr_e
# endif

# if defined (_PTHREAD_EXC_DECC) && defined (_PTHREAD_EXC_VMS)
#  pragma __extern_model __restore
# endif

# ifdef __cplusplus
    }
# endif

#endif					/* _PTHREAD_EXCEPTION_CLEAN */


/*
 * The following section of this file contains definitions which are not in
 * the protected part of the namespace.
 */
#if !defined (_PTHREAD_EXCEPTION_POLLUTING) && !defined (_PTHREAD_EXC_INCL_CLEAN)
# define _PTHREAD_EXCEPTION_POLLUTING

# ifdef __cplusplus
    extern "C" {
# endif

/*
 * Define external version of status codes
 */
# define pthread_exception_s		__pthread_exception_s
# define pthread_exccop_s		__pthread_exccop_s
# define pthread_uninitexc_s		__pthread_uninitexc_s
# define pthread_unkstatus_s		__pthread_unkstatus_s
# define pthread_exccoplos_s		__pthread_exccoplos_s
# define pthread_noexcmem_s		__pthread_noexcmem_s

# define pthread_illaddr_s		__pthread_illaddr_s
# define pthread_exquota_s		__pthread_exquota_s
# define pthread_nopriv_s		__pthread_nopriv_s
# define pthread_insfmem_s		__pthread_insfmem_s
# define pthread_normal_s		__pthread_normal_s
# define pthread_illinstr_s		__pthread_illinstr_s
# define pthread_resaddr_s		__pthread_resaddr_s
# define pthread_privinst_s		__pthread_privinst_s
# define pthread_resoper_s		__pthread_resoper_s
# define pthread_SIGTRAP_s		__pthread_SIGTRAP_s
# define pthread_SIGABRT_s		__pthread_SIGABRT_s
# define pthread_SIGEMT_s		__pthread_SIGEMT_s
# define pthread_aritherr_s		__pthread_aritherr_s
# define pthread_SIGSYS_s		__pthread_SIGSYS_s
# define pthread_SIGPIPE_s		__pthread_SIGPIPE_s
# define pthread_excpu_s		__pthread_excpu_s
# define pthread_exfilsiz_s		__pthread_exfilsiz_s
# define pthread_intovf_s		__pthread_intovf_s
# define pthread_intdiv_s		__pthread_intdiv_s
# define pthread_fltovf_s		__pthread_fltovf_s
# define pthread_fltdiv_s		__pthread_fltdiv_s
# define pthread_fltund_s		__pthread_fltund_s
# define pthread_decovf_s		__pthread_decovf_s
# define pthread_subrng_s		__pthread_subrng_s
# define pthread_stackovf_s		__pthread_stackovf_s

# define pthread_SIGIOT_s		__pthread_SIGABRT_s
# define pthread_SIGSEGV_s		__pthread_illaddr_s
# define pthread_SIGBUS_s		__pthread_resaddr_s
# define pthread_SIGFPE_s		__pthread_aritherr_s

# define pthread_cancel_s		__pthread_cancel_s
# define pthread_exit_s			__pthread_exit_s

typedef __pthreadExceptionObj_t	EXCEPTION;

/*
 * Define the documented ("polluted") external names for the exception
 * macros.
 */

# define EXCEPTION_INIT(__e)	PTHREAD_EXCEPTION_INIT_NP (__e)
# define RAISE(__e)		PTHREAD_RAISE_NP (__e)
# define TRY			PTHREAD_TRY_NP
# define ENDTRY			PTHREAD_ENDTRY_NP
# define FINALLY		PTHREAD_FINALLY_NP
# define CATCH_ALL		PTHREAD_CATCH_ALL_NP
# define RERAISE		PTHREAD_RERAISE_NP
# define THIS_CATCH		PTHREAD_THIS_CATCH_NP
# define CATCH(__e)		PTHREAD_CATCH_NP (__e)

# ifdef __cplusplus
    }
# endif

#endif
