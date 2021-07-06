/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: tis.template.h,v $
 * Revision 1.1.23.1  2003/09/12  19:02:25  devbld_zko
 * 	DECthreads V3.20-049 submit
 * 	thdbl20-4-miken
 * 	Cleanup ODE revision history log tokens
 * 	[2003/09/03  18:14:48  Mike_Neverisky]
 *
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thdbl20_br:1.1.16.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.12.2
 *   Common Ancestor:  1.1.12.1
 * 	[2002/10/22  19:47:46  Peter_Portante]
 *
 * 	Populate thdbl20
 * 	[2002/08/14  19:34:35  devbld_zko]
 *
 * Revision 1.1.12.2  2002/07/31  18:21:58  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thdbl19_br:1.1.12.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.3
 *   Common Ancestor:  1.1.12.1
 * 
 * Revision 1.1.3.3  2002/06/25  19:32:41  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.3.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.15.1
 *   Common Ancestor:  1.1.3.2
 * 
 * Revision 1.1.15.1  2002/05/17  14:07:07  Peter_Portante
 * 	Add to BL17.
 * 
 * Revision 1.1.6.4  2002/01/28  19:49:59  Mike_Neverisky
 * 	Initiating thdbl20
 * Merge Information:  Non-Visual Merge: User specified tree thdbl19
 *     User Revision:  thddev_br:1.1.6.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl19_br:1.1.12.1
 *   Common Ancestor:  1.1.6.2
 * 	Functional NOP merge of thdbl19 into thddev
 * 
 * Revision 1.1.12.1  2002/01/25  21:32:45  devbld_zko
 * 	Populate thdbl19 from thddev
 * 
 * Revision 1.1.6.2  2001/10/31  16:46:54  Mike_Neverisky
 * 	Fix OldLog tokens
 * Merge Information:  Non-Visual Merge: User specified tree thdbl18
 *     User Revision:  thddev_br:1.1.6.1 Local Ancestor: n/a
 *    Merge Revision:  thdbl18_br:1.1.3.2
 *   Common Ancestor:  1.1.3.1
 * 	[2001/10/31  16:38:39  Mike_Neverisky]
 * 
 * Revision 1.1.3.2  2001/10/26  19:11:58  Mike_Neverisky
 * 	Correct OldLog token to fix comment stripping problem
 * 	Correct OldLog token to fix comment stripping problem
 * 
 * Revision 1.1.6.1  2001/08/06  22:05:05  Peter_Portante
 * 	Add to thddev shared sandbox
 * 
 * Revision 1.1.3.1  2001/01/11  18:10:51  Bill_Blanding
 * 	This file is a template which is used for the generation
 * 	of the include file tis.h during a build.
 * 	It was created from and replaces tis.h.
 * 	All future changes desired for tis.h.
 * 	must be made either to this file or to
 * 	the text substitution files [identified in tis_include.mk]
 * 	which are merged with this template during the build process.
 * 	Text insertion points are identified by the string: __REPLACE_ME_WITH_FILE.
 * 
 * Revision 1.1.9.3  2001/01/05  20:58:12  Peter_Portante
 * Merge Information:  Non-Visual Merge: User specified tree thdbl17
 *     User Revision:  thdbl18_br:1.1.9.2 Local Ancestor: n/a
 *    Merge Revision:  thdbl17_br:1.1.8.2
 *   Common Ancestor:  1.1.8.1
 * 
 * Revision 1.1.8.2  2000/10/24  16:39:29  Mary_Sullivan
 * 	Added #pragma [no]standard to bracket "$" name references
 * 	on VMS.
 * 
 * Revision 1.1.9.2  2000/08/30  18:05:34  Peter_Portante
 * 	Cleanup file a bit.
 * 
 * Revision 1.1.9.1  2000/03/02  21:31:29  devbld_zko
 * 	Move from BL17 to BL18
 * 
 * Revision 1.1.8.1  2000/03/01  15:43:10  Peter_Portante
 * 	Adding BL16 version to BL17
 * 
 * Revision 1.1.4.1  1999/12/05  03:14:35  Peter_Portante
 * 	Pull revision from thdbl15 and update with contents from libc.
 * 
 * Revision 1.1.2.1  1999/11/17  14:48:05  Richard_Love
 * 	Rename new directory structure TIS.
 * 	[1999/11/11  14:09:12  Richard_Love]
 * 	Reorganize directory structure.
 * 	[1999/11/11  00:32:09  Richard_Love]
 * 
 * $EndLog$
 */
/*
 * $OldLog:$
 * Revision 1.1.70.2  1999/11/17  17:49:01  Peter_Portante
 * 	Fix up previous merge history to remove excess.
 * 	[1999/11/11  19:11:17  Peter_Portante]
 *
 * Merge Information
 *     Merge Revision:  thdbl16_br:1.1.70.1
 *     User  Revision:  Peter_Portante_mg_br:1.1.73.2
 *    Common Ancestor:  1.1
 * 	Merge thdadvdev changes into thdbl16
 * 	[1999/11/11  19:09:20  Peter_Portante]
 *
 * Revision 1.1.72.1  1999/11/03  13:09:27  Peter_Portante
 * 	Move to thdadvdev
 *
 * Revision 1.1.68.1  1999/09/20  13:14:43  Peter_Portante
 * Merge Information
 *     Merge Revision:  DECTHREADS_SHARED_THDZULUOS:1.1.66.2
 *     User  Revision:  Peter_Portante_thdzu:1.1.67.2
 *    Common Ancestor:  1.1
 * 	[1999/09/15  21:05:17  Peter_Portante]
 *
 * 	Remove inline versions of mutex lock routines.
 * 	[1999/06/27  12:55:55  Peter_Portante]
 *
 * Revision 1.1.66.2  1999/05/28  14:40:50  Terry_Cassidy
 * 	Initial CMS version
 * 	New-style copyright removed
 * 	Daughter history merged
 * 	History inverted
 * 	[1999/05/28  14:39:37  Terry_Cassidy]
 * 
 * Revision 1.1.25.7  1999/05/06  15:15:09  Andrew_Duane
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jSTEELOS_BL21:STEELOS_BL23 **
 * 		** Ancestor revision:	1.1.13.9 **
 * 		** Merge revision:	1.1.13.11 **
 * 	 	** End **
 * 	[1999/05/06  15:10:34  Andrew_Duane]
 * 
 * Revision 1.1.25.6  1999/04/19  23:40:00  Mike_Neverisky
 * 	Correct merge issues in original BL2 submit
 * 	[1999/04/19  19:16:33  Mike_Neverisky]
 * 
 * Revision 1.1.25.5  1999/04/16  20:36:06  Mike_Neverisky
 * 	 	** Merge Information **
 * 		** Command used:	bsubmit **
 * 		** Ancestor revision:	1.1.61.2 **
 * 		** Merge revision:	1.1.25.4 **
 * 	 	** End **
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rDECTHREADS_SHARED_THDZULUOS **
 * 		** Ancestor revision:	1.1.25.4 **
 * 		** Merge revision:	1.1.61.2 **
 * 	 	** End **
 * 	propagating thdzuluos
 * 	[1999/04/16  19:52:26  Mike_Neverisky]
 * 
 * Revision 1.1.13.11  1999/04/12  15:38:29  Mike_Neverisky
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rDECTHREADS_SHARED_THDSTEELOS **
 * 		** Ancestor revision:	1.1.13.10 **
 * 		** Merge revision:	1.1.54.2 **
 * 	 	** End **
 * 	propagating thdsteelos to BL23
 * 	[1999/04/07  19:22:45  Mike_Neverisky]
 * 
 * Revision 1.1.61.2  1999/04/07  14:36:42  Peter_Portante
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -jSTEELOS:DECTHREADS_SHARED_STEEL -visual **
 * 		** Ancestor revision:	1.1.13.10 **
 * 		** Merge revision:	1.1.51.3 **
 * 	 	** End **
 * 	Use new directory hierarchy for DECthreads code
 * 	[1999/04/06  20:18:34  Peter_Portante]
 * 
 * Revision 1.1.54.2  1999/03/30  18:23:03  Peter_Portante
 * 	Update with latest changes from shared sandbox
 * 	[1999/03/29  19:07:51  Peter_Portante]
 * 
 * Revision 1.1.13.10  1999/02/12  15:41:55  Mike_Neverisky
 * 	DECthreads BL22 Submit
 * 	[1999/02/01  10:59:20  Mike_Neverisky]
 *
 * $EndLog$
 */
/* 
 * $OldLog:$
 * 	034	Peter Portante	 7 January 1999
 * 		Define a macro so that pthread.h can check to see if
 * 		tis.h is including it so that it can avoid defining the
 * 		inline routines.
 * 	033	Dave Butenhof	10 December 1998
 * 		Add new RWLOCK init macro, and tis_mutex_initwithname().
 * 	032	Peter Portante	 7 May 1998
 * 		Use the typedefs for constructor and destructors for uniformity.
 * 	031	Mark Simons	19 March 1998
 * 		Add declaration and flags for tis_allocator_mutex_init().
 * 	030	Steve Johnson	16 July 1997
 * 		NT software and hardware definitions
 * 	029	Webb Scales	23 January 1997
 * 		Added hardware config symbols.
 * 	028	Richard Love	11 December 1996 
 * 		Change type of tis_io_complete and tis_synch.
 * 	027	Richard Love	16 October 1996
 * 		Added parameter names to tis_synch declaration.
 * 		Added copyright macro at header.
 * 	026	Richard Love	 2 October 1996
 * 		Implement tis_cond_timedwait & tis_get_expiration.
 * 	025	Dave Butenhof	24 September 1996
 * 		Implement TLS support -- "constructor keys"
 * 	024	Richard Love	24 September 1996
 * 		Change implementation of Asynchronous I/O interfaces.
 * 	023	Peter Portante	18 September 1996
 * 		Implement Asynchronous I/O interfaces.
 * 	022	Peter Portante	25 June 1996
 * 		Cleanup header file so that is models pthread.h more closely.
 * 		Verify that there are no long/short pointer size issues here
 * 		since all the types are defined by pthread.h which already
 * 		deals with the issue.
 * 	021	Peter Albany	20 June 1996
 * 		Add pragma member_alignment for DECC to ensure that the
 * 		externally visible structures are always aligned.
 * 	020	Dave Butenhof	10 April 1996
 * 		Change the inline mutex unlock for improved performance and
 * 		to allow pthread_mutex_unblock to resolve a race.
 * 	019	Dave Butenhof	 7 February 1996
 * 		Finish namespace cleanups for pthread.h
 * 	018	Peter Portante	 5 December 1995
 * 		Use the _Pfield macro to make sure we get the correct field
 * 		names for the inline locking code.
 * 	017	Dave Butenhof	 1 November 1995
 * 		Reverse 014, because the previously broken behavior is now
 * 		correct. Hee hee.
 * 	016	Peter Portante	24 September 1995
 * 		Remove the thread parameter from the raise call since the
 * 		function which we vector to will determine whether we are
 * 		raising a signal for a process or a thread.
 * 	015	Richard Love	20 September 1995
 * 		Add tis_raise and tis_yield to TIS.
 * 	014	Dave Butenhof	10 August 1995
 * 		Fix tis_mutex_unlock_inline() macros to unref the mutex
 * 		regardless of whether the unblock routine is called. That will
 * 		fix the refcnt overflow problems we've seen. Unfortunately,
 * 		continuing to use "lock/unlock" instead of having tis block
 * 		& unblock routines means each unlock will double-reference
 * 		the mutex (once for tis_mutex_unlock_inline and once for
 * 		pthread_mutex_unlock) -- but that shouldn't be a serious
 * 		problem. It's not worth the trouble of adding new routines to
 * 		the vector at this point.
 * 	013	Dave Butenhof	 2 August 1995
 * 		Add extern "C" { } block for C++
 * 	012	Dave Butenhof	28 July 1995
 * 		Add _TIS_VERSION symbol.
 * 	011	Dave Butenhof	 7 July 1995
 * 		Well, I want to use _PTHREAD_MVF_PRE for the TIS global lock,
 * 		so generalize the name and add a recursive variant... and move
 * 		it all to pthread.h.
 * 	010	Dave Butenhof	 6 July 1995
 * 		Refine 009 by changing the comments -- TIS_INIT_MALLOC_MUTEX
 * 		isn't going to be used by libc, but SHOULD be used by anyone
 * 		else who preempts libc's malloc.
 * 	009	Dave Butenhof	 5 July 1995
 * 		Add TIS_INIT_MALLOC_MUTEX macro to allow libc to cleanly
 * 		initialize _malloc_mutex to take advantage of the preallocated
 * 		DECthreads blocking structure.
 * 	008	Peter Portante	14 June 1995
 * 		Fix the try mutex locking macro to actually try to the lock!
 * 	007	Peter Portante	12 June 1995
 * 		Fix the mutex locking macro to actually lock the mutex!
 * 	006	Dave Butenhof	 7 June 1995
 * 		Fix up some comments.
 * 	005	Paul Clark	 6 June 1995
 * 		A few modules in LEGACY layer need to include TIS.H but
 * 		do not want the side-effect of permanently setting the
 * 		EXC_NO_EXCEPTIONS macro.
 * 	004	Peter Portante	26 May 1995
 * 		Add inline mutex operations and static initialization macros.
 * 	003	Webb Scales	16 May 1995
 * 		Move vector access macros to their own header file.
 * 	002	Peter Portante	15 May 1995
 * 		Move definition of tisVector to tis_jt.h.
 * 	001	Peter Portante	12 May 1995
 * 		Move the definition of the TIS vector table here and add some
 * 		macros for all tis_* routines which reference the vector table
 * 		directly.
 * $EndLog$
 */
/*
 * @(#)$RCSfile: tis.template.h,v $ $Revision: 1.1.23.1 $ (DEC) $Date: 2003/09/12 19:02:25 $
 */
/*
 *  FACILITY:
 *
 *	Thread-Independent Synchronization, a subsidiary of DECthreads
 *
 *  ABSTRACT:
 *
 *	TIS provides synchronization (and other miscellaneous "thread"
 *	services, such as thread-specific data) in a manner that is highly
 *	efficient when DECthreads is not active within the process. When
 *	DECthreads is present these functions are automatically and
 *	transparently remapped into DECthreads, providing multithread
 *	safety.
 *
 *	These interfaces are not intended to be used for threaded code
 *	(i.e., libraries or main programs that create threads). Instead, they
 *	are intended to allow creation of "thread safe" code, which operates
 *	correctly when threads are present, but without the overhead imposed
 *	by thread-safety when run without threads.
 *
 *  AUTHORS:
 *
 *	Webb Scales
 *
 *  CREATION DATE:
 *
 *	29 April 1992
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Peter Portante
 *	Webb Scales
 *	Mark Simons
 *
 *  LAST MODIFIED:
 *
 *	 7 December 1999
 */

#ifndef _TIS_INCLUDE
#define _TIS_INCLUDE

/*
 * <pthread.h> will include <pthread_exception.h> in order to implement some
 * of its required functionality.  The exception header file will cause a few
 * references to be made to the threads library.  If the including module asks
 * for inline routines, <pthread.h> will also cause a few references to be
 * made to the threads library.  We do not want to reference the threads
 * library if the caller is only include tis.h, so we define the
 * _EXC_NO_EXCEPTIONS_ macro to omit the exception handling funcitionality and
 * we define the _TIS_INCLUDE_ENV macro to prevent any other threads library
 * references.
 */
#define _TIS_INCLUDE_ENV
#define _EXC_NO_EXCEPTIONS_
#include <pthread.h>
#undef _EXC_NO_EXCEPTIONS_
#undef _TIS_INCLUDE_ENV

#if defined (_PTHREAD_ENV_DECC)
# if defined (_PTHREAD_ENV_VMS)
#  if __DECC_VER >= 50200000
#   pragma __environment __save
#  else
#   pragma __extern_model __save
#  endif
# else
#  pragma __environment __save
# endif
# pragma member_alignment
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following routines comprise the DECthreads "Thread Independent
 * Synchronization" Services. These routines provide the indicated
 * functionality when used in a program or application in which threads are
 * present. In the absence of threads, these functions impose minimal
 * overhead on their caller.
 *
 * TIS objects created using this (new) interface are fully interchangeable
 * with DECthreads core (POSIX 1003.1c-1995) objects. That means that you can
 * create a mutex using static initialization or tis_mutex_init, lock it
 * before initialization of DECthreads, and then unlock the mutex.
 *
 * Other assorted TIS "state", such as thread-specific data keys and values,
 * and cancelation state, are also propagated into DECthreads at
 * initialization. Thread-Specific data values appear in the default (main)
 * thread, as does the cancelation state.
 */

#define _TIS_VERSION 320004


/*
 * TIS configuration symbols
 */
#define _TIS__OSF	1
#define _TIS__VMS	2

#ifndef _TIS_OS_
# if defined (__OSF__) || defined (__osf__)
#  define _TIS_OS_	_TIS__OSF
# elif defined (vms) || defined (__vms) || defined (__VMS)
#  define _TIS_OS_	_TIS__VMS
# elif defined (_WIN32) || defined (WIN32)
#  define _TIS_OS_	_TIS__WIN32
# else
#  error _TIS_OS_ is undefined
# endif
#endif

#define _TIS__ALPHA	1
#define _TIS__VAX	2
#define _TIS__IA64	3

#ifndef _TIS_HARDWARE_
# if defined (__alpha) || defined (__ALPHA)
#  define _TIS_HARDWARE_ _TIS__ALPHA
# elif defined (vax) || defined (__vax) || defined (__VAX)
#  define _TIS_HARDWARE_ _TIS__VAX
# elif defined (_M_IX86)
#  define _TIS_HARDWARE_ _TIS__X86
# elif defined (__ia64__)
#  define _TIS_HARDWARE_ _TIS__IA64
# else
#  error _TIS_HARDWARE_ is undefined
# endif
#endif


/*
 * TIS structure declarations
 */
typedef struct tis_rwlock {
    int			valid;		/* Validation flag */
    int			readers;	/* Number of readers */
    int			rwaits;		/* Waiting readers */
    int			writer;		/* Writer active */
    int			wwaits;		/* Waiting writers */
    pthread_mutex_t	mutex;		/* The mutex itself */
    pthread_cond_t	Wreaders;	/* Wait for read access */
    pthread_cond_t	Wwriters;	/* Wait for write access */
    } tis_rwlock_t, *tis_rwlock_p;

#define TIS_RWLOCK_VALID	0xbeebeac1

#define TIS_RWLOCK_INITIALIZER {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITIALIZER, \
    PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER}

#define TIS_RWLOCK_INITWITHNAME(_nm_,_am_,_nc1_,_ac1_,_nc2_,_ac2_) \
    {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITWITHNAME_NP(_nm_,_am_), \
    PTHREAD_COND_INITWITHNAME_NP(_nc1_,_ac1_), \
    PTHREAD_COND_INITWITHNAME_NP(_nc2_,_ac2_)}

/*
 * And a simplified form that uses ANSI C string concatination to form the
 * various object names from a single argument:
 */
#define TIS_RWLOCK_INITWITHNAME1(_nm_,_am_) \
    {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITWITHNAME_NP(_nm_,_am_), \
    PTHREAD_COND_INITWITHNAME_NP("read-" _nc1_,_ac1_), \
    PTHREAD_COND_INITWITHNAME_NP("write-" _nc2_,_ac2_)}

/*
 * Flags used for tis_mutex_initwithname
 */
typedef enum tis_mflags_tag {
    TIS_MINIT_RECURSIVE =	0x00000001
    } tis_mflags_t;

/*
 * Flags used for tis_allocator_mutex_init
 */
typedef enum tis_alloc_mflags_tag {
    TIS_ALLOC_MUTEX_PSHARED =	0x00000001,
    TIS_ALLOC_MUTEX_NOALLOC =	0x00000002,
    TIS_ALLOC_MUTEX_RECURSIVE =	0x00000004
    } tis_alloc_mflags_t;


#if _TIS_OS_ == _TIS__VMS
 /*
  * On VMS, these routines must begin with "tis$" not "tis_", so use a
  * macro to translate on those platforms.
  */

# pragma nostandard
 /*
  * TIS ERRNO Routines
  */
# define tis_errno_get_addr		tis$errno_get_addr
# define tis_errno_set_value		tis$errno_set_value
# define tis_vmserrno_get_addr		tis$vmserrno_get_addr
# define tis_vmserrno_set_value		tis$vmserrno_set_value

 /*
  * TIS Pthread Routines
  */
# define tis_cond_broadcast		tis$cond_broadcast
# define tis_cond_destroy		tis$cond_destroy
# define tis_cond_init			tis$cond_init
# define tis_cond_signal		tis$cond_signal
# define tis_cond_timedwait		tis$cond_timedwait
# define tis_cond_wait			tis$cond_wait
# define tis_get_expiration		tis$get_expiration
# define tis_getspecific		tis$getspecific
# define tis_key_create			tis$key_create
# define tis_key_create_new		tis$key_create_new
# define tis_key_delete			tis$key_delete
# define tis_lock_global		tis$lock_global
# define tis_mutex_destroy		tis$mutex_destroy
# define tis_mutex_init			tis$mutex_init
# define tis_mutex_initwithname		tis$mutex_initwithname
# define tis_mutex_lock			tis$mutex_lock
# define tis_mutex_trylock		tis$mutex_trylock
# define tis_mutex_unlock		tis$mutex_unlock
# define tis_mutex_unblock		tis$mutex_unblock
# define tis_once			tis$once
# define tis_raise			tis$raise
# define tis_self			tis$self
# define tis_setcancelstate		tis$setcancelstate
# define tis_setspecific		tis$setspecific
# define tis_testcancel			tis$testcancel
# define tis_unlock_global		tis$unlock_global
# define tis_yield			tis$yield

 /*
  * TIS Readers/Writer Locks Routines
  */
# define tis_read_lock			tis$read_lock
# define tis_read_trylock		tis$read_trylock
# define tis_read_unlock		tis$read_unlock
# define tis_rwlock_destroy		tis$rwlock_destroy
# define tis_rwlock_init		tis$rwlock_init
# define tis_write_lock			tis$write_lock
# define tis_write_trylock		tis$write_trylock
# define tis_write_unlock		tis$write_unlock

 /*
  * TIS Asynchronous I/O Routines
  */
# define tis_io_complete		tis$io_complete
# define tis_synch			tis$synch
# pragma standard
#endif


/*
 * TIS functions.
 */

/*
 * Get the address of errno
 */
extern int *tis_errno_get_addr (void);

/*
 * Set all known errno cells to a particular value
 */
extern void tis_errno_set_value (int);

#if _TIS_OS_ == _TIS__VMS
/*
 * Get the address of the VMS-specific errno
 */
extern int *tis_vmserrno_get_addr (void);

/*
 * Set all known VMS-specific errno cells to a particular value
 */
extern void tis_vmserrno_set_value (int);
#endif

#if _TIS_OS_ == _TIS__OSF
/*
 * Allocate and/or initialize a TIS mutex, and allocate a blocking structure.
 * This function can be used by a malloc-replacement so that it can safely be
 * used by libpthread to allocate blocking structures. (Otherwise, a deadlock
 * may occur when contention occurs on the allocator mutex.)
 *
 * handle	Pointer to a pthread_mutex_t*, in which address of a new mutex
 *		is returned; or, if TIS_ALLOC_MUTEX_NOALLOC is specified, a
 *		pointer to a pthread_mutex_t, which is initialized.
 * allocator	An allocation routine that will be used to allocate the mutex
 *		and blocking structure.
 * arg		A value passed to the allocator. This is not interpreted by
 *		TIS.
 * name		A character string representing the name of the mutex. For
 *		example, "myMalloc". This will show up in Visual Threads and
 *		debugger output when mutexes are displayed (e.g., ladebug's
 *		"show mutex").
 * name_arg	An undocumented and unsupported name argument, which you
 *		should specify as 0.
 * flags	One or more of the values in the tis_alloc_mflags_t enum.
 *		(Yes, they're really flags.) TIS_ALLOC_MUTEX_NOALLOC means
 *		that you have already allocated a pthread_mutex_t before
 *		making the call, and "handle" is a pointer to that structure.
 */
extern int
tis_allocator_mutex_init (
	void *,				/* handle */
	void *(*)(size_t, void *),	/* callback */
	void *,				/* allocator argument */
	const char *,			/* (mutex name) */
	unsigned int,			/* (mutex name argument) */
	unsigned long);			/* (tis_alloc_mflags_t) */
#endif

/*
 * Broadcast on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to broadcast.
 */
extern int tis_cond_broadcast (pthread_cond_t *);

/*
 * Destroys a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference,
 * which is to be destroyed or "uninitialized".
 */
extern int tis_cond_destroy (pthread_cond_t *);

/*
 * Initialize a TIS condition variable.
 *
 * "cond" is a pointer to an condition variable, passed by reference, which
 * is initialized.
 */
extern int tis_cond_init (pthread_cond_t *);

/*
 * Signal a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, on which to signal.
 */
extern int tis_cond_signal (pthread_cond_t *);

/*
 * Wait on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to wait. "mutex" is the address of the mutex, passed by reference,
 * which is associated with "cond".
 */
extern int tis_cond_wait (pthread_cond_t *, pthread_mutex_t *);

/*
 * Timed Wait on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to wait. "mutex" is the address of the mutex, passed by reference,
 * which is associated with "cond".  "abstime" is the address of the timespec
 * containing the absolute time in which the wait expires.
 */
extern int tis_cond_timedwait (
	pthread_cond_t *,
	pthread_mutex_t *,
	const struct timespec *);

/*
 * Get an expiration time, in preparation for calling tis_cond_timedwait()
 *
 * "delta" is the address of the timespec structure that is the number of
 * seconds and nanoseconds to add to the current system time.
 * "abstime" is the address of the timespec structure of the result 
 * representing the absolute expiration time computed from the current system
 * time plus the given "delta".
 */
extern int tis_get_expiration (const struct timespec *, struct timespec *);

/*
 * Lock the TIS global lock
 */
extern int tis_lock_global (void);

/*
 * Create a thread specific data (tsd) key.
 *
 * "key" is the address of a variable which will receive the key value; this
 * value is used in calls to tis_setspecific() and tis_getspecific() to get
 * and set the value associated with this key. The same key value is used in
 * each thread to access that thread's context, when and if DECthreads is
 * initialized in the process.
 *
 * "Destructor" is the address of a routine which is called to destroy (e.g.,
 * deallocate) the thread-specific data value when a thread terminates with a
 * non-NULL value for the key. If DECthreads is initialized after a TIS tsd
 * key is created, the key (and destructor) is taken over by DECthreads
 * transparently.
 */
extern int tis_key_create (pthread_key_t *, __pthreadDestructor_t);

/*
 * Create a thread specific data (tsd) "constructor" key.
 *
 * "key" is the address of a variable which will receive the key
 * value; this value is used in calls to tis_setspecific() and
 * tis_getspecific() to get and set the value associated with this
 * key. The same key value is used in each thread to access that
 * thread's context, when and if DECthreads is initialized in the
 * process.
 *
 * "Constructor" is the address of a routine which is called to create
 * a value when a new thread is created. Constructor will also be
 * called with appropriate arguments for each CURRENTLY EXISTING
 * THREAD when the key is created, if the PTHREAD_KEY_ALLTHREAD_NP
 * flag is specified. The call, in this case, it made in the context
 * of the thread that creates the key, and thus cannot call anything
 * else that relies upon thread context.
 *
 * "Destructor" is the address of a routine which is called to destroy
 * (e.g., deallocate) the thread-specific data value when a thread
 * terminates with a non-NULL value for the key. Note that the
 * prototype for constructor key destructor routines is different than
 * that of the destructor for normal keys. When a constructor key
 * created with the PTHREAD_KEY_ALLTHREAD_NP flag is deleted by
 * calling tis_key_delete or pthread_key_delete, the destructor is
 * called for all currently existing threads -- again, in the context
 * of the thread deleting the key.
 *
 * If DECthreads is initialized after a TIS tsd key is created, the
 * key (and destructor) is taken over by DECthreads transparently.
 */
extern int tis_key_create_new (
	pthread_key_t *,
	__pthreadConstructor_t,
	__pthreadExtDestructor_t,
	int);

/*
 * Delete a thread specific data (tsd) key.
 *
 * Deletes a thread specific data key previously returned by
 * tis_key_create(). The application must free any storage or do any cleanup
 * on the data structures associated with the key. The cleanup may be done
 * before or after tis_key_delete is called.
 */
extern int tis_key_delete (pthread_key_t);

/*
 * Get the thread specific data (tsd) value associated with a particular key.
 *
 * "Key" is a key value returned by a call to tis_key_create(). The thread
 * specific data value associated with this key is returned by the call to
 * the tis_getspecific().
 */
extern void *tis_getspecific (pthread_key_t);

/*
 * Initialize a TIS mutex
 *
 * "mutex" is a pointer to a mutex, which will be initialized.
 */
extern int tis_mutex_init (pthread_mutex_t *);

/*
 * Initialize a TIS mutex with additional parameters
 *
 * "mutex" is a pointer to a mutex, which will be initialized. You may specify
 * a name for the mutex, and you may set the mutex "recursive". The "arg"
 * parameter is officially undefined, and you should specify 0. Also, the name
 * string should be a string literal, or other storage that will remain for
 * the life of the mutex -- the library will not copy the string.
 */
extern int tis_mutex_initwithname (pthread_mutex_t *, const char *, int, int);

/*
 * Destroy a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be destroyed. The mutex
 * object becomes "uninitialized".
 */
extern int tis_mutex_destroy (pthread_mutex_t *);

/*
 * Lock a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be locked.
 */
extern int tis_mutex_lock (pthread_mutex_t *);

/*
 * Non-blocking TIS mutex lock
 *
 * "mutex" is the address of the mutex which is to be locked.
 *
 * The function returns a boolean value indicating if the mutex was
 * successfully locked.
 */
extern int tis_mutex_trylock (pthread_mutex_t *);

/*
 * Unlock a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be unlocked.
 */
extern int tis_mutex_unlock (pthread_mutex_t *);

/*
 * Unblock from a TIS mutex
 *
 * "mutex" is the address of the mutex from which threads may be unblocked.
 */
extern int tis_mutex_unblock (pthread_mutex_t *);

/*
 * Execute a one-time initialization routine.
 *
 * The specified routine is called exactly once during a program's execution,
 * even if multiple threads call tis_once() simultaneously. This is useful
 * for performing one-time initialization tasks (e.g., for a facility API),
 * such as creating mutexes and thread specific data keys. (Although note
 * that with statically initialized mutexes, it's rarely necessary to call
 * tis_once.)
 *
 * "once_control" is the address of a one-time initialization control block.
 * This should be in static storage and unique to the initialization routine.
 * "init_routine" is the address of the initialization routine to call.
 */
extern int tis_once (pthread_once_t *, void (*) (void));

/*
 *  Raise (send) the signal to the current thread or process.
 */
extern int tis_raise (int);

/*
 * Get current thread "ID". NOTE: without DECthreads, this returns a
 * "prototype" TEB which is not used by DECthreads. The value returned by
 * tis_self within the main thread will change when DECthreads initializes!
 */
extern pthread_t tis_self (void);

/*
 * Set the caller's cancelability to state, and return the previous
 * cancelability state to the location referenced by oldstate.
 */
extern int tis_setcancelstate (int state, int *);

/*
 * Set the thread specific data (tsd) value associated with a particular key.
 *
 * "Key" is a key value returned by a call to tis_key_create(). "Value" is
 * value to be associated with this key. Once set, this value can be
 * retrieved in this thread using the same key in a call to
 * tis_getspecific().
 */
extern int tis_setspecific (pthread_key_t, const void *);

/*
 * Creates a cancellation point in the calling thread. Has no effect if
 * cancelability is disabled or DECthreads is not initialized.
 */
extern void tis_testcancel (void);

/*
 * Unlock the TIS global lock
 */
extern int tis_unlock_global (void);

/*
 *  Yield this thread to another.
 */
extern void tis_yield (void);

/*
 * Locks a readers/writer lock for read.
 */
extern int tis_read_lock (tis_rwlock_t *);

/*
 * Locks a readers/writer lock for write.
 */
extern int tis_write_lock (tis_rwlock_t *);

/*
 * Tries to lock a readers/writer lock for read. Does not wait if lock is
 * unavailable.
 */
extern int tis_read_trylock (tis_rwlock_t *);

/*
 * Destroy a readers/writer lock.
 */
extern int tis_rwlock_destroy (tis_rwlock_t *);

/*
 * Initialize a readers/writer lock.
 */
extern int tis_rwlock_init (tis_rwlock_t *);

/*
 * Tries to lock a readers/writer lock for write. Does not wait if lock is
 * unavailable.
 */
extern int tis_write_trylock (tis_rwlock_t *);

/*
 * Unlocks the readers/writer lock from read access.
 */
extern int tis_read_unlock (tis_rwlock_t *);

/*
 * Unlocks the readers/writer lock from write access.
 */
extern int tis_write_unlock (tis_rwlock_t *);

#if _TIS_OS_ == _TIS__VMS
/*
 * Declare completion of Asynchronous I/O operation.
 *
 * Note: this routine can be called from AST level.
 */
extern void tis_io_complete (void);

/*
 * Wait for Asynchronous I/O to complete.
 */
extern unsigned long tis_synch (unsigned long, void *);
#endif

#if defined (_PTHREAD_ENV_DECC)
# if defined (_PTHREAD_ENV_VMS)
#  if __DECC_VER >= 50200000
#   pragma __environment __restore
#  else
#   pragma __extern_model __restore
#  endif
# else
#  pragma __environment __restore
# endif
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _TIS_INCLUDE */
