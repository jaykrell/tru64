/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: kintrinsics.h,v $
 * Revision 1.1.18.1  2002/12/12  21:37:42  Renny_Shen
 * 	Added pragma linkage contract on save_context_all
 *
 * Revision 1.1.8.7  2002/07/17  18:30:28  Andrew_Moskal
 *  *	Mark bigpg_cb_enabled no_tail_call.
 *
 * Revision 1.1.8.6  2002/06/26  15:24:49  Julie_Dewandel
 * 	Turn on no_tail_call for _a_lock primitives [QAR 94036]
 *
 * Revision 1.1.8.5  2002/05/18  12:43:09  Frederick_Canter
 * 	Update function prototype for hardclock() for Marvel
 * 	lost timer tick adjust.
 *
 * Revision 1.1.8.4  2002/03/26  16:24:16  Joe_Mario
 * 	Changed the "constnoinit" diag from a warning to an error
 * 	level diag.
 *
 * Revision 1.1.8.3  2002/03/14  17:23:13  Joe_Mario
 * 	Add pragma to enable the constnoinit compiler diagnostic.
 * 	Changed the vlaextension compiler diagnostic from a warning
 * 	to an error level diagnostic
 * 	.
 *
 * Revision 1.1.8.2  2002/02/13  13:22:36  Joe_Mario
 * 	Add pragma to enable the vlaextension compiler diagnostic.
 *
 * Revision 1.1.8.1  2001/09/12  20:25:10  Andrew_Duane
 * 	Turn off no_tail_call for _setjmp to avoid compiler diagnostics. It is not needed.
 *
 * Revision 1.1.4.1  2000/10/19  17:50:33  Ernie_Petrides
 * 	Enable shrink wrap optimizations in kernel builds and add
 * 	definitions for mtpr_ipir(), mtpr_tbi(), and mfpr_ipl().
 *
 * Revision 1.1.2.10  2000/03/25  00:47:02  Ernie_Petrides
 * 	Introduce structure size and alignment assertion macros.
 *
 * Revision 1.1.2.9  2000/02/25  20:01:14  Will_Leslie
 * 	Change parameter type on advfs_sad function prototype.  QAR 74880.
 *
 * Revision 1.1.2.8  1999/12/10  21:36:05  Ernie_Petrides
 * 	Make final preparations in anticipation of tail-call-capable compiler.
 *
 * Revision 1.1.2.7  1999/11/03  22:41:00  Ernie_Petrides
 * 	Introduce a 2nd "extern_model" pragma macro for use of with "const"
 * 	data, move asm() intrinsic declarations here, and add new pragmas
 * 	to avoid tail calls to back-patching functions.
 *
 * Revision 1.1.2.6  1999/10/04  20:11:28  James_Woodward
 * 	Remove pragma linkages for preemption_on/preemption_off
 * 	routines.  The current code patchout code uses more registers
 * 	then allowed by the linkages.  For zulu, the quickest fix is
 * 	to remove the pragma linkages.
 *
 * Revision 1.1.2.5  1999/09/14  16:55:28  Ernie_Petrides
 * 	Introduce macro for use with the "extern_model" pragma.
 *
 * Revision 1.1.2.4  1999/08/16  18:08:45  Anton_Verhulst
 * 	Add hardclock pragma.
 * 	[1999/08/16  18:06:16  Anton_Verhulst]
 *
 * Revision 1.1.2.3  1998/12/08  17:52:12  James_Woodward
 * 	merge of STEELOS_BL20 into zulu.
 * 	[1998/12/08  17:41:20  James_Woodward]
 * 
 * Revision 1.1.2.2  1998/12/02  21:39:53  Ray_Lanza
 * 	Initial version for alpha
 * 	[1998/12/02  19:34:30  Ray_Lanza]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: kintrinsics.h,v $ $Revision: 1.1.18.1 $ (DEC) $Date: 2002/12/12 21:37:42 $
 */

#ifndef _MACHINE_KINTRINSICS_H_
#define _MACHINE_KINTRINSICS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file contains DEC C specific linkages and kernel intrinsics.  Much
 * of this was in common_protos.h, but has been moved here because it is
 * compiler- and architecture-specific.
 */

#ifdef __DECC

#ifdef _KERNEL

extern long asm(const char *, ...);
#pragma intrinsic(asm,bcopy,bzero,strlen,memcpy)

#define _USE_KERNEL_LINKAGES

#if __DECC_VER > 60230249
#define _TAIL_CALLS_POSSIBLE
#define _NO_TAIL_CALLS ,requires_call
#else
#undef _TAIL_CALLS_POSSIBLE
#define _NO_TAIL_CALLS
#endif

#pragma linkage printf_linkage = \
  (preserved(r1,r2,r3,r4,r5,r6,r7,r8,r22,r23,r24,r25))
#pragma use_linkage printf_linkage(printf,aprintf,dprintf,uprintf,log)

#pragma linkage panic_linkage = \
  (preserved(r1,r2,r3,r4,r5,r6,r7,r8,r17,r18,r19,r20,r21,r22,r23,r24,r25) \
   _NO_TAIL_CALLS)
#pragma use_linkage panic_linkage(panic)

void advfs_sad(char *, int, char *, char *, long, long, long);
#pragma linkage advfs_sad_linkage = \
  (preserved(r1,r2,r3,r4,r5,r6,r7,r8,r22,r23,r24,r25) _NO_TAIL_CALLS)
#pragma use_linkage advfs_sad_linkage(advfs_sad)

void hardclock(caddr_t, int, long*, long);
#pragma linkage hardclock_linkage = (nopreserve(r9,r11,r12,r13,r14,r15))
#pragma use_linkage hardclock_linkage(hardclock)

/*
 * This pragma linkage contract on save_context_all() has to be 
 * identical to the contract for switch_context. In boot(), during
 * a panic, a we are restoring a thread through save_context_all()
 * that was saved through switch_context.
 */
extern int save_context_all(void );
#pragma linkage save_ctx_linkage = \
	(nopreserve(r9,r10,r11,r12,r13,r14,r15) _NO_TAIL_CALLS)
#pragma use_linkage save_ctx_linkage(save_context_all)

#pragma linkage swap_ipl_linkage = \
  (preserved(r2,r3,r4,r5,r6,r7,r8,r18,r19,r20,r21) _NO_TAIL_CALLS)
#pragma use_linkage swap_ipl_linkage(swap_ipl,swap_ipl_preempt_check)

#pragma linkage mb_smp_only_linkage = \
  (preserved(r1,r2,r3,r4,r5,r6,r7,r8,r18,r19,r20,r21,r22,r23,r24,r25) \
   _NO_TAIL_CALLS)
#pragma use_linkage mb_smp_only_linkage(mb_smp_only)

/*
 * This paranoid linkage is needed because write_instruction() is called from
 * swap_ipl(), which doesn't save any registers.  Thus, we save them all here.
 */
extern void write_instruction(void *, unsigned int);
#pragma linkage write_instruction_linkage = \
  (preserved(r0,r1,r2,r3,r4,r5,r6,r7,r8,r18,r19,r20,r21,r22,r23,r24,r25))
#pragma use_linkage write_instruction_linkage(write_instruction)

/*
 * The following pragmas inform the compiler that the specified functions
 * will never return to their caller, thus allowing special optimizations.
 */
#if 0 /* no perceived benefit at current time */
#pragma assert func_attrs(panic,boot,halt,stop_secondary_cpu) noreturn
#pragma assert func_attrs(lock_fault,simple_lock_fault,advfs_sad) noreturn
#pragma assert func_attrs(exit,sigexit,load_context,xcpu_panic_ipir) noreturn
#endif

/*
 * The following section lists all functions to which tail calls must be
 * prevented.  The most critical case is where a function might patch out
 * its caller's "bsr" instruction at (RA - 4).  If a tail call were made
 * to one of these, it could patch out the "bsr" in the caller's caller
 * erroneously.
 */
#ifdef _TAIL_CALLS_POSSIBLE

#pragma environment save
#pragma message disable(nofntpdefdecl)

#pragma linkage no_tail_call = (requires_call)

/* back-patching-capable locking primitives in arch/alpha/lockprim.s */
#pragma use_linkage no_tail_call(simple_lock)
#pragma use_linkage no_tail_call(simple_unlock)
#pragma use_linkage no_tail_call(simple_lock_try)
#pragma use_linkage no_tail_call(simple_lock_setup)
#pragma use_linkage no_tail_call(simple_lock_terminate)
#pragma use_linkage no_tail_call(simple_lock_locked)
#pragma use_linkage no_tail_call(simple_lock_holder)
#pragma use_linkage no_tail_call(_a_lock_init)
#pragma use_linkage no_tail_call(_a_lock)
#pragma use_linkage no_tail_call(_a_lock_try)
#pragma use_linkage no_tail_call(_a_unlock)
#pragma use_linkage no_tail_call(rws_read_lock)
#pragma use_linkage no_tail_call(rws_read_unlock)
#pragma use_linkage no_tail_call(rws_read_lock_try)
#pragma use_linkage no_tail_call(rws_write_assert_try)
#pragma use_linkage no_tail_call(rws_write_release)
#pragma use_linkage no_tail_call(preemption_off)
#pragma use_linkage no_tail_call(preemption_on)

/* back-patching-capable locking primitives in kern/lock.c */
#pragma use_linkage no_tail_call(ulock_setup)
#pragma use_linkage no_tail_call(ulock_terminate)
#pragma use_linkage no_tail_call(ulock_write)
#pragma use_linkage no_tail_call(ulock_read)
#pragma use_linkage no_tail_call(ulock_done)
#pragma use_linkage no_tail_call(ulock_try_write)
#pragma use_linkage no_tail_call(ulock_try_write_assert)
#pragma use_linkage no_tail_call(ulock_try_read)
#pragma use_linkage no_tail_call(ulock_write_to_read)
#pragma use_linkage no_tail_call(ulock_set_recursive)
#pragma use_linkage no_tail_call(ulock_clear_recursive)
#pragma use_linkage no_tail_call(rws_alloc)
#pragma use_linkage no_tail_call(rws_free)
#pragma use_linkage no_tail_call(rws_write_lock)
#pragma use_linkage no_tail_call(rws_write_unlock)

/* back-patching-capable socket locking functions in bsd/uipc_socket.c */
#pragma use_linkage no_tail_call(solock)
#pragma use_linkage no_tail_call(solock1)
#pragma use_linkage no_tail_call(solocktry)
#pragma use_linkage no_tail_call(solocktrynoassert)
#pragma use_linkage no_tail_call(sounlock)
#pragma use_linkage no_tail_call(sounlock1)

/* back-patching-capable funneling functions in kern/parallel.c */
#pragma use_linkage no_tail_call(unix_master)
#pragma use_linkage no_tail_call(unix_release)

/* back-patching functions in arch/alpha/pal_lib.s */
#pragma use_linkage no_tail_call(rpcc)
#pragma use_linkage no_tail_call(mb)
#pragma use_linkage no_tail_call(wbflush)
#pragma use_linkage no_tail_call(wmb)
#pragma use_linkage no_tail_call(imb)
#pragma use_linkage no_tail_call(mtpr_ipir)
#pragma use_linkage no_tail_call(mfpr_whami)
#pragma use_linkage no_tail_call(mtpr_tbi)
#pragma use_linkage no_tail_call(amask_bit0)
#pragma use_linkage no_tail_call(amask)
#pragma use_linkage no_tail_call(implver)
#pragma use_linkage no_tail_call(ecb)
#pragma use_linkage no_tail_call(wh64)
#pragma use_linkage no_tail_call(ldbu)
#pragma use_linkage no_tail_call(stb)
#pragma use_linkage no_tail_call(ldwu)
#pragma use_linkage no_tail_call(stw)
#pragma use_linkage no_tail_call(sextb)
#pragma use_linkage no_tail_call(sextw)

/* back-patching functions in bsd/kern_malloc.c */
#pragma use_linkage no_tail_call(malloc_cache_enabled)
#pragma use_linkage no_tail_call(protected_bucket_kbp)
#pragma use_linkage no_tail_call(protected_bucket_index)
#pragma use_linkage no_tail_call(malloc_store_checksum)
#pragma use_linkage no_tail_call(malloc_update_checksum)
#pragma use_linkage no_tail_call(malloc_check_checksum)
#pragma use_linkage no_tail_call(malloc_debug)

/* back-patching functions in kern/sched_prim.c */
#pragma use_linkage no_tail_call(pass_extra_stackspace)
#pragma use_linkage no_tail_call(thread_cont_lite_stack)

/* back-patching functions in vm/vm_resident.c */
#pragma use_linkage no_tail_call(bigpg_cb_enabled)

/* nxm pshared area locking functions in kern/syscall_subr.c */
#pragma use_linkage no_tail_call(mutex_lock)
#pragma use_linkage no_tail_call(mutex_unlock)
#pragma use_linkage no_tail_call(write_lock)
#pragma use_linkage no_tail_call(read_lock)
#pragma use_linkage no_tail_call(rwl_unlock)

/* nofault handler setup functions used by alpha_signal.c and pmap.c */
#pragma use_linkage no_tail_call(nxm_upcall_check_fault)
#pragma use_linkage no_tail_call(sendsig_check_fault)
#pragma use_linkage no_tail_call(sigreturn_check_fault)
#pragma use_linkage no_tail_call(setup_nf_remove_wired_fast)
#pragma use_linkage no_tail_call(setup_nf_ptefetch)
#pragma use_linkage no_tail_call(setup_nf_lw_wire_new)
#pragma use_linkage no_tail_call(setup_nf_lw_unwire_new)

/* other functions whose correct operation depends on true caller address */
/* _setjmp is never tail-called by the compiler, do not need to explicitly disable */
/* #pragma use_linkage no_tail_call(_setjmp) */
#pragma use_linkage no_tail_call(get_caller_ra)
#pragma use_linkage no_tail_call(getpc)
#pragma use_linkage no_tail_call(getra)
#pragma use_linkage no_tail_call(save_context)
/* #pragma use_linkage no_tail_call(switch_context) - moved to sched_prim.c */

/* functions that use caller address solely for informational purposes */
#pragma use_linkage no_tail_call(contig_free)
#pragma use_linkage no_tail_call(contig_malloc)
#pragma use_linkage no_tail_call(event_post)
#pragma use_linkage no_tail_call(event_wait)
#pragma use_linkage no_tail_call(free)
#pragma use_linkage no_tail_call(kalloc)
#pragma use_linkage no_tail_call(lock_adopt)
#pragma use_linkage no_tail_call(lock_clear_recursive)
#pragma use_linkage no_tail_call(lock_disown)
#pragma use_linkage no_tail_call(lock_done)
#pragma use_linkage no_tail_call(lock_done_clear_recursive)
#pragma use_linkage no_tail_call(lock_pc_hist_trace_complex)
#pragma use_linkage no_tail_call(lock_read)
#pragma use_linkage no_tail_call(lock_read_to_write)
#pragma use_linkage no_tail_call(lock_recursive_try)
#pragma use_linkage no_tail_call(lock_set_recursive)
#pragma use_linkage no_tail_call(lock_setup)
#pragma use_linkage no_tail_call(lock_try_read)
#pragma use_linkage no_tail_call(lock_try_read_assert)
#pragma use_linkage no_tail_call(lock_try_read_to_write)
#pragma use_linkage no_tail_call(lock_try_write)
#pragma use_linkage no_tail_call(lock_try_write_assert)
#pragma use_linkage no_tail_call(lock_write)
#pragma use_linkage no_tail_call(lock_write_to_read)
#pragma use_linkage no_tail_call(malloc)
#pragma use_linkage no_tail_call(malloc_ext)
#pragma use_linkage no_tail_call(malloc_percpu_shutdown)
#pragma use_linkage no_tail_call(procfs_trace_event)
#pragma use_linkage no_tail_call(rad_contig_malloc)
#pragma use_linkage no_tail_call(rad_malloc)
#pragma use_linkage no_tail_call(unmap_gh)

/* functions with callers whose stack frame presence is highly desirable */
#pragma use_linkage no_tail_call(biowait)
#pragma use_linkage no_tail_call(badaddr)
#pragma use_linkage no_tail_call(boot)
#pragma use_linkage no_tail_call(copyin)
#pragma use_linkage no_tail_call(copyout)
#pragma use_linkage no_tail_call(halt)
#pragma use_linkage no_tail_call(lock_fault)
#pragma use_linkage no_tail_call(mpsleep)
#pragma use_linkage no_tail_call(rwuio)
#pragma use_linkage no_tail_call(prwuio)
#pragma use_linkage no_tail_call(simple_lock_fault)
#pragma use_linkage no_tail_call(sleep_prim)
#pragma use_linkage no_tail_call(sosleep)
#pragma use_linkage no_tail_call(stop_secondary_cpu)
#pragma use_linkage no_tail_call(swap_ipl_nopatch)
#pragma use_linkage no_tail_call(thread_block)
#pragma use_linkage no_tail_call(thread_preempt)
#pragma use_linkage no_tail_call(waitf)

#pragma environment restore

/*
 * The following pragmas enable tail call and shrink wrap optimizations.
 */
#pragma optimize tail_calls=on
#pragma optimize shrink_wrap=on

#endif /* _TAIL_CALLS_POSSIBLE */

/*
 * The following vlaextension message pragma will detect the use of runtime
 * variables as the dimension for stack array declarations.
 * Their use in the kernel negatively affects the kernel traceback code.
 */
#pragma message enable vlaextension
#pragma message error vlaextension

/*
 * The following constnoinit message pragma will detect const variables
 * being declared but not initialized.  When they are not initialized, 
 * the compiler may put them into the .bss section rather than .rdata.
 * This causes REPLICATED variables to not be replicated.
 */
#pragma message enable constnoinit
#pragma message error constnoinit

/*
 * The following are real built-ins (prototypes are in arch/alpha/builtins.h).
 */
#define mb()		__MB()
#define kdebug_mb()	__MB()		/* Handle kdebug, too */
#define imb()		__PAL_IMB()
#define kdebug_imb()	__PAL_IMB()	/* Handle kdebug, too */
#define rpcc()		__RPCC()

/*
 * The following might be built-ins some day (but asm()'s work just as well).
 */
#define wmb()		asm("wmb")
#define mtpr_ipir(CPU)	asm("call_pal 13", CPU)
#define mtpr_mces(S)	asm("call_pal 17", S)
#define mtpr_fen(S)	asm("call_pal 43", S)
#define mtpr_tbi(X,Y)	asm("call_pal 51", X, Y)
#define mfpr_ipl()	asm("call_pal 54")
#define mtpr_usp(USP)	asm("call_pal 56", USP)
#define mfpr_usp()	asm("call_pal 58")
#define mfpr_whami()	asm("call_pal 60")
#define implver()	asm("implver %v0")
#define ecb(va)		asm("ecb (%a0)", va)
#define wh64(va)	asm("wh64 (%a0)", va)
#define amask(mask)	asm("amask %a0, %v0", mask)

/*
 * The following macros are for use with "assert_m" pragmas, which
 * (by default) generate "assertfail" compilation warnings if the
 * associated size or alignment criteria are not met.  The diagnostic
 * level of "assertfail" can be promoted to generate compilation errors
 * (if desired) as follows:
 *
 *	#pragma message error(assertfail)
 *
 * Use the assertion macros as follows:
 *
 *	struct foo {
 *		long x, y, z, pad[5];
 *		int goo, more_pad[15];
 *	};
 *		...
 *	#pragma assert_m data_size_match(struct foo, 128)
 *	#pragma assert_m data_size_multiple(struct foo, 32)
 *	#pragma assert_m cache_aligned_data_size(struct foo)
 *	#pragma assert_m cache_aligned_field_offset(struct foo, goo)
 */
#define data_size_match(type, value) \
		non_zero (sizeof(type) == (size_t)(value)) \
			"unexpected data size"
#define data_size_multiple(type, value) \
		non_zero ((sizeof(type) % (size_t)(value)) == 0) \
			"unexpected data size"
#define cache_aligned_data_size(type) \
		non_zero ((sizeof(type) & (size_t)63) == 0) \
			"non-cache-aligned data size"
#define cache_aligned_field_offset(type, field) \
		non_zero (((size_t)&((type *)0)->field & (size_t)63) == 0) \
			"non-cache-aligned field offset"

/*
 * The following macro is for use with the "extern_model" pragma.  It
 * instructs the compiler to allocate initialized data in order, with
 * the first item on a 64-byte address boundary (cache line alignment),
 * and with successive globals of type "int" packed on 4-byte boundaries.
 *
 * Use as follows:
 *
 *	#pragma extern_model save
 *	#pragma extern_model cache_aligned_packed_data(foo)
 *		...
 *	void *p = NULL;
 *	int xxx = 42;
 *	int yyy = 0;
 *		...
 *	#pragma extern_model restore
 */
#define cache_aligned_packed_data(name) \
		strict_refdef #name 6, noreorder, natalgn

/*
 * The next macro is an alternate version for use with "const" data.
 */
#define cache_aligned_packed_const_data(name) \
		strict_refdef #name 6, noreorder, natalgn, nowrt

#endif /* _KERNEL */

#endif /* __DECC */

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_KINTRINSICS_H_ */
