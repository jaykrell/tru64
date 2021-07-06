/*
 
  Copyright 2004 Hewlett-Packard Development Company, L.P.

  Confidential computer software. Valid license from HP required for
  possession, use or copying. Consistent with FAR 12.211 and 12.212,
  Commercial Computer Software, Computer Software Documentation, and
  Technical Data for Commercial Items are licensed to the U.S. Government
  under vendor's standard commercial license.

*/
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: builtins.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1999/06/23 20:09:14 $
 */
/****************************************************************************
**
**  <builtins.h> - Prototypes for Compaq C platform specific builtins
**
*****************************************************************************
*/

#ifndef __BUILTINS_LOADED
#define __BUILTINS_LOADED 1

#if defined(__DECC) || defined(__DECCXX)

#ifdef __cplusplus
extern "C" {
#endif


#pragma __nostandard

/***************************************************************
**  Part 1: Compaq C builtins for atomic/interlocked operations.
****************************************************************
**
**  These functions are not easily/efficiently implemented using
**  inline assembly code, and so the compiler has builtin knowledge
**  of their names and signatures in order to generate fast and
**  reliable code (e.g. it may generate loops with tests arranged
**  for branch prediction using out-of-line branch targets for
**  failure paths).
**
**  The _RETRY variants store a non-zero status if the operation
**  completes successfully within the specified number of retries.
**  The variants without _RETRY do not return until they succeed.
**
**  Note that by convention the names _LONG and _QUAD designate
**  32-bit longword and 64-bit quadword operations (as defined by
**  the Alpha architecture), and should not be confused with the
**  C language type "long", which is 64-bits on Digital UNIX.
**
**  The following operations do not in themselves generate Memory
**  Barriers.  The user is expected to code explicitly any Memory
**  Barriers where needed using inline assembly code, e.g. asm("mb"),
**  or asm("wmb").  See /usr/include/c_asm.h for more information
**  on inline assembly code.
*/

/*
**  Atomic update of location with integer operation, returning
**  previous contents.
*/
int  __ATOMIC_ADD_LONG(volatile void *__address, int __expression);
int  __ATOMIC_ADD_LONG_RETRY(volatile void *__address,
			     int __expression,
			     int __retry,
			     int *__status);
long  __ATOMIC_ADD_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_ADD_QUAD_RETRY(volatile void *__address,
			      long __expression,
			      int __retry,
			      int *__status);

int  __ATOMIC_AND_LONG(volatile void *__address, int __expression);
int  __ATOMIC_AND_LONG_RETRY(volatile void *__address,
			     int __expression,
			     int __retry,
			     int *__status);
long  __ATOMIC_AND_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_AND_QUAD_RETRY(volatile void *__address,
			      long __expression,
			      int __retry,
			      int *__status);

int  __ATOMIC_OR_LONG(volatile void *__address, int __expression);
int  __ATOMIC_OR_LONG_RETRY(volatile void *__address,
			    int __expression,
			    int __retry,
			    int *__status);
long  __ATOMIC_OR_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_OR_QUAD_RETRY(volatile void *__address,
			     long __expression,
			     int __retry,
			     int *__status);

/*
**  Slightly faster than __ATOMIC_ADD using explicit +1 or -1.
*/
int  __ATOMIC_INCREMENT_LONG(volatile void *__address);
long  __ATOMIC_INCREMENT_QUAD(volatile void *__address);

int  __ATOMIC_DECREMENT_LONG(volatile void *__address);
long  __ATOMIC_DECREMENT_QUAD(volatile void *__address);

/*
**  Atomic replacement of location's contents, returning previous
**  contents.
*/
int  __ATOMIC_EXCH_LONG(volatile void *__address, int __expression);
int  __ATOMIC_EXCH_LONG_RETRY(volatile void *__address,
			      int __expression,
			      int __retry,
			      int *__status);
long  __ATOMIC_EXCH_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_EXCH_QUAD_RETRY(volatile void *__address,
			       long __expression,
			       int __retry,
			       int *__status);

/*
**  Interlocked "test for bit clear and then clear".  Returns non-zero
**  if bit was already clear.
*/
int __INTERLOCKED_TESTBITCC_QUAD(volatile void *__address, int __bit_position);
int __INTERLOCKED_TESTBITCC_QUAD_RETRY(volatile void *__address,
				       int __bit_position,
				       int __retry,
				       int *__status);
/*
**  Interlocked "test for bit set and then set".  Returns non-zero
**  if bit was already set.
*/
int __INTERLOCKED_TESTBITSS_QUAD(volatile void *__address, int __bit_position);
int __INTERLOCKED_TESTBITSS_QUAD_RETRY(volatile void *__address,
				       int __bit_position,
				       int __retry,
				       int *__status);

/*
**  Acquire/release binary spinlock based on low-order bit of a longword.
**  NOTE: Memory barrier generated after lock, before unlock.
**  _RETRY variant returns non-zero on success within retry attempts.
*/
void __LOCK_LONG(volatile void *__address);
int  __LOCK_LONG_RETRY(volatile void *__address, int __retry);
void __UNLOCK_LONG(volatile void *__address);

/*
**  Acquire/release counted semaphore based on positive value of
**  longword indicating number of resources available.
**  NOTE: Memory barrier generated after acquisition, before release.
**  _RETRY variant returns non-zero on success within retry attempts.
*/
void __ACQUIRE_SEM_LONG(volatile void *__address);
int  __ACQUIRE_SEM_LONG_RETRY(volatile void *__address, int __retry);
void __RELEASE_SEM_LONG(volatile void *__address);

/*
**  Compare, Store Longword/Quadword
**      If *source matches old_value, store new_value in *dest, returning
**      0 if no match or if compare and store were not interlocked.
**
**	NOTE: Memory Barrier is generated only within the LDx_L/STx_C
**	sequence, but may be suppressed when the source and
**	destination addresses can be recognized at compile-time as
**	being identical. 
*/
int __CMP_STORE_LONG(volatile void *__source,
		     int __old_value,
		     int __new_value,
		     volatile void *__dest);
int __CMP_STORE_QUAD(volatile void *__source,
		     signed long __old_value,
		     signed long __new_value,
		     volatile void  *__dest);

/*
**  Add Aligned Word Interlocked (emulates the VAX instruction).
**      As on VAX, returns NZVC (0:3) of a VAX PSL.
**      Memory Barrier before and after update.
*/
int __ADAWI(short __src, volatile short *__dest);

#if !defined(__cplusplus) || \
    (defined(__DECCXX_VER) && __DECCXX_VER >= 60000000)

/*********************************************************************
**  Part 1a: Compaq C/C++ builtins for bit counting
**********************************************************************
**
**  These functions are not trivially implementable as asms
**  and need to be be highly optimized for certain kinds
**  of applications.  The names are compatible with some other
**  compiler implementations.
**
**  _popcnt, _poppar, _leadz, _trailz, _int_mult_upper
*/

long _popcnt(unsigned long);
long _poppar(unsigned long);
long _leadz(unsigned long);
long _trailz(unsigned long);
#pragma intrinsic(_popcnt, _poppar, _leadz, _trailz)
#define _int_mult_upper __UMULH
#endif  /* __cplusplus */


/*********************************************************************
**  Part 2: "old" Compaq C builtins for atomic/interlocked operations.
**********************************************************************
**
**  The following atomic/interlocked builtins have some usability issues,
**  but are retained as-is for compatibility with previous versions
**  of Compaq C.  In particular, these _ATOMIC_ builtins always return
**  status (even when the retry count is omitted), but they have no
**  way to provide the old value, which is often useful.  The TESTBIT
**  routines return a value that indicates the previous state of
**  the bit, but they provide no way to determine success of the
**  operation if a retry count is specified.  They also generate
**  Memory Barrier instructions both before and after the atomic
**  update code, which tends to make them slower than necessary in
**  some cases.
*/

/*
**  op_ATOMIC_size Builtins
**
**  Note: There is one optional retry count parameter
*/
int __ADD_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __ADD_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

int __AND_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __AND_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

int __OR_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __OR_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

/*
**  TESTBITxxI
**
**  Note: There is one optional retry count parameter
*/
int __TESTBITCCI(volatile void *__address, int __position, ...);
int __TESTBITSSI(volatile void *__address, int __position, ...);


/******************************************************************
**  Part 3: OpenVMS compatibility
*******************************************************************
**
**  These builtins are provided here largely to improve portability
**  of "older" source code from OpenVMS to Digital UNIX.  The more
**  usual UNIX convention for most of these builtins is to use inline
**  assembly code, which is now also available on OpenVMS Alpha (with
**  Compaq C V5.0 or later).
*/

/*
**  Memory Barrier
*/
void	__MB(void);

/*
**  Instruction Memory Barrier
*/
void	__PAL_IMB(void);

/*
**  Trap Barrier Instruction
*/
void __TRAPB(void);

/*
**  Read Process Cycle Counter
*/
unsigned long __RPCC(void);

/*
**  Generate Trap
*/
void __PAL_GENTRAP(unsigned long __encoded_software_trap);

/*
**  Breakpoint
*/
void __PAL_BPT(void);

/*
**  Bugcheck
*/
void __PAL_BUGCHK(unsigned long __bugchk_code);

/*
**  Swap Privileged Context (Privileged)
*/
void __PAL_SWPCTX(void *__address);

/*
**  Halt the Processor. (Privileged)
*/
void __PAL_HALT(void);

/*
**  UMULH Builtin - Unsigned Quadword Multiply High
*/
unsigned long __UMULH(unsigned long __oper1,
			 unsigned long __oper2);


/*
**  The following floating point operations map to single
**  Alpha instructions (some with qualifiers), and can
**  also be specified by inline assembly code.
*/

/*
**  Copy Sign
*/
float	    __CPYSF(float __operand1, float __operand2);
double	    __CPYS(double __operand1, double __operand2);

/*
**  Copy Sign Negate
*/
float	    __CPYSNF(float __operand1, float __operand2);
double	    __CPYSN(double __operand1, double __operand2);

/*
**  Copy Sign Exponent
*/
float	    __CPYSEF(float __operand1, float __operand2);
double	    __CPYSE(double __operand1, double __operand2);

/*
**  Convert from T-Floating to Quadword
*/
signed long __CVTTQ(double __operand1);

/*
**  Convert from T-Floating to S-Floating Chopped
*/
float __CVTTS_C(double __operand1);

/*
**  Add Floating Point Chopped
*/
float __ADDS_C(float __operand1, float __operand2);
double __ADDT_C(double __operand1, double __operand2);

/*
**  Subtract Floating Point Chopped
*/
float __SUBS_C(float __operand1, float __operand2);
double __SUBT_C(double __operand1, double __operand2);

/*
**  Multiply Floating Point Chopped
*/
float __MULS_C(float __operand1, float __operand2);
double __MULT_C(double __operand1, double __operand2);

/*
**  Divide Floating Point Chopped
*/
float __DIVS_C(float __operand1, float __operand2);
double __DIVT_C(double __operand1, double __operand2);

/*
**  __ALLOCA builtin - allocate n-bytes from the stack
**
**  This cannot be implemented using inline assembly code.  But
**  on Digital UNIX, code would typically #include <alloca.h>
**  and then use alloca() rather than including this header
**  file and using __ALLOCA().  The Compaq C compiler treats both
**  styles equivalently, however.
*/
void *__ALLOCA(unsigned int __x);


#if defined(__DECC) && \
    ((__DECC_VER / 100000) * 10000 + (__DECC_VER % 10000)) >= 6050200
    /* >= 6.5-200, ignoring T6.5 vs V6.5 vs X6.5 distinction */
/******************************************************************
**  Part 4: __CMP_STORE_[LONG|QUAD] replacements
*******************************************************************
**
**  These built-in functions are provided to replace the
**  __CMP_STORE_[LONG|QUAD] built-ins, which are deprecated.
*/

/*
**  Compare and Swap Longword/Quadword (unordered):
**	If *__addr matches __old_value, store __new_value in *__addr.
**	Return 0 if no match or if compare and store were not
**	interlocked, 1 if the atomic read-compare-write of *__addr
**	succeeded. 
**	NOTE: No memory barrier is generated, no ordering guaranteed.
*/
int __CMP_SWAP_LONG(volatile void *__addr,
		    int __old_value,
		    int __new_value);
int __CMP_SWAP_QUAD(volatile void *__addr,
		    __int64 __old_value,
		    __int64 __new_value);

/*
**  Compare and Swap Longword/Quadword ("acquire" ordering):
**      A memory barrier is generated after the store, guaranteeing that
**      all pending stores from other processors are visible, and that
**      this store becomes visible on other processors, before
**      proceding.
*/
int __CMP_SWAP_LONG_ACQ(volatile void *__addr,
			int __old_value,
			int __new_value);
int __CMP_SWAP_QUAD_ACQ(volatile void *__addr,
			__int64 __old_value,
			__int64 __new_value);

/*
**  Compare and Swap Longword/Quadword ("release" ordering):
**      A memory barrier is generated before the store, guaranteeing that
**      all pending stores from other processors become visible, and
**      that all previous stores on this processor become visible
**      to other processors, before performing the exchange.
*/
int __CMP_SWAP_LONG_REL(volatile void *__addr,
			int __old_value,
			int __new_value);
int __CMP_SWAP_QUAD_REL(volatile void *__addr,
			__int64 __old_value,
			__int64 __new_value);

/*
**  IA64-compatible _InterlockedCompareExchange (Compare and Swap) for Alpha
**
**      The following prototypes match those provided by Intel-based
**      compilers for IPF.  They differ from the __CMP_SWAP builtins
**      in that they spin in a LDx_L/STx_C loop so that they never
**	fail for lack of atomic update.  Instead of status, they
**	return the old value of *__Destination.  If the returned
**	value matches __Comparand, the update happened atomically.
**
**	Note the difference in the order of parameters and the types
**	compared to the __CMP_SWAP* builtins.
**
**	The _acq and _rel suffixes specify "acquire" versus "release"
**	ordering, implemented with memory barriers as described for
**	the __CMP_SWAP builtins, above.
**	
*/
unsigned __int64 _InterlockedCompareExchange_acq(
			 unsigned int *__Destination,
			 unsigned __int64 __Newval,
			 unsigned __int64 __Comparand);
unsigned __int64 _InterlockedCompareExchange64_acq(
			 unsigned __int64 *__Destination,
			 unsigned __int64 __Newval,
			 unsigned __int64 __Comparand);

unsigned __int64 _InterlockedCompareExchange_rel(
                         unsigned int *__Destination,
			 unsigned __int64 __Newval,
			 unsigned __int64 __Comparand);
unsigned __int64 _InterlockedCompareExchange64_rel(
                         unsigned __int64 *__Destination,
			 unsigned __int64 __Newval,
			 unsigned __int64 __Comparand);

#endif	/* __DECC */

#pragma __standard

#ifdef __cplusplus
}
#endif

#endif	/* __DECC || __DECCXX */
#endif  /* __BUILTINS_LOADED */
