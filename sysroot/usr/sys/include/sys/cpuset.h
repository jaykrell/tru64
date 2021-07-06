/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cpuset.h,v $
 * Revision 1.1.13.1  2003/06/05  17:26:43  Anton_Verhulst
 * 	Add missing prototype for cpu_get_current() and cpu_get_rad().
 *
 * Revision 1.1.3.4  2001/03/07  19:52:27  James_Woodward
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree yankeeos
 *     User Revision:  James_Woodward_yank_br:1.1.9.1 Local Ancestor:1.1.5.2
 *    Merge Revision:  yankeeos_br:1.1.3.3
 *   Common Ancestor:  1.1.3.2
 * 	Added missing prototypes for cpu_get_info() and cpu_get_num().
 * 	We need to conditionalize the definition of pthread_use_only_cpu()
 * 	on _POSIX_C_SOURCE being greater than 199506L, which is when a
 * 	proper definition of pthread_t will be provided by sys/types.h.
 * 	Submission on behalf of Peter Portante.
 *
 * Revision 1.1.3.3  2001/02/14  15:51:04  Mike_Neverisky
 * 	DECthreads V3.18-110 submit
 * 	Back out pthread_use_only_cpu prototype for Yankee BL5.
 * 
 * Revision 1.1.5.1  2001/02/04  00:50:17  Peter_Portante
 * 	Add prototype for pthread_use_only_cpu() and a definition for
 * 	PTHREAD_CPU_INFLEXIBLE.
 * 
 * Revision 1.1.3.1  2000/10/18  14:33:17  devbld_zko
 * 	Add change from old kern module to recognize C++. Define proper
 * 	prototypes for all cpuset interfaces. We no longer reference the
 * 	__ versions the id interface routines. Move user/kernel common
 * 	interfaces to this file. The original kern/cpuset.h now includes
 * 	this one, and it has its edit history intact. This module was
 * 	created from revision 1.1.12.1.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cpuset.h,v $ $Revision: 1.1.13.1 $ (DEC) $Date: 2003/06/05 17:26:43 $
 */

#ifndef	_SYS_CPUSET_H
#define _SYS_CPUSET_H

/*
 *	File:	cpuset.h
 *
 *	operations on CPU sets
 */

#include <sys/types.h>
#include <sys/idset.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *cpuset_t;
typedef id_cursor_t cpuset_cursor_t;
typedef id_cursor_p cpuset_cursor_p;

typedef id_cursor_t cpu_cursor_t;

#define NCPU_INFO_VERSION	1

typedef struct __ncpu_info {
	int	ncpu_version;	/* Revision number */
	int	ncpu_max;	/* Maximum number of CPUs supported by the
				   machine architecture */
	cpuset_t ncpu_present;	/* Cpu set of processors physically plugged
				   into the system. */
	cpuset_t ncpu_running;	/* Cpu set of on-line CPUs in the caller's
				   partition -- i.e., capable of having work
				   scheduled on them by the caller. */
	cpuset_t ncpu_binding;	/* set of CPUs in the partition that have
				   processes bound to them */
	cpuset_t ncpu_ex_binding;/* set of CPUs in the partition whose processor
				   set is marked for exclusive use. */
} ncpu_info_t;

extern int cpusetcreate(cpuset_t *);
extern int cpusetdestroy(cpuset_t *);
extern int cpusetisvalid(cpuset_t);

extern int cpucountset(cpuset_t);
extern int cpuemptyset(cpuset_t);
extern int cpufillset(cpuset_t);
extern int cpuaddset(cpuset_t, int);
extern int cpudelset(cpuset_t, int);

extern int cpuismember(cpuset_t, int);
extern int cpuisemptyset(cpuset_t);

extern int cpuorset(cpuset_t, cpuset_t, cpuset_t);
extern int cpuxorset(cpuset_t, cpuset_t, cpuset_t);
extern int cpuandset(cpuset_t, cpuset_t, cpuset_t);
extern int cpudiffset(cpuset_t, cpuset_t, cpuset_t);
extern int cpucopyset(cpuset_t, cpuset_t);

extern int cpu_foreach(cpuset_t, unsigned int, cpu_cursor_t *);

/* Return TRUE if cpu only member in set. */
#define cpuismember_excl(__set__, __cpuid__)				\
	(cpuismember(__set__, __cpuid__) && (cpucountset(__set__) == 1))

extern int cpu_get_info(ncpu_info_t *);
extern int cpu_get_max(void);
extern int cpu_get_num(void);
extern int cpu_get_current(void);
extern int cpu_get_rad(cpuid_t);

#ifdef CPUSET_DEBUG
extern void debug_set_nmembers(int);
extern void cpuset_print_hex(cpuset_t);
#endif

#if !defined(_KERNEL) && defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
#define PTHREAD_CPU_INFLEXIBLE	1
extern int pthread_use_only_cpu (pthread_t, cpuid_t, long);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#if defined(_KERNEL) && !defined(_GENASSYM)

extern cpuset_t cpu_enable_mask, cpu_disable_mask;
extern cpuset_t master_cpuset, cpus_available_set;

/*
 * The number of valid bits in a cpuset_t
 */
#define CPU_NBITS		cpu_slots

/*
 * The number of longs in a cpuset_t of CPU_NBITS elements
 */
#define CPUSET_LSIZE							\
	((CPU_NBITS + ((BITS_PER_LONG) - 1)) / (BITS_PER_LONG))

#define CPUSET_STRUCT_LSIZE (CPUSET_LSIZE + IDSET_HEADER_LSIZE)

#define CPUSET_STRUCT_NBYTES ((CPUSET_LSIZE+IDSET_HEADER_LSIZE) * sizeof(long))

/*
 * Index into the embedded cpuset_t bits[] array for a given bit i
 */
#define CPUSET_INDEX(__i__)	((__i__) / BITS_PER_LONG)


/*
 * Convenience macros for accessing cpu_{enable,disable}_mask
 */
#define cpu_is_enabled(__cpu__)						\
	cpuismember(cpu_enable_mask, __cpu__)
#define cpu_is_disabled(__cpu__)					\
	cpuismember(cpu_disable_mask, __cpu__)
#define cpu_is_available(__cpu__)					\
	cpuismember(cpus_available_set, __cpu__)

/*
 * Allow backward compatibility with 64-bit masks still required
 * by some user interfaces.
 */
#define CPUSET_LEGACY				1

#if CPUSET_LEGACY

#define CPUSET_LWORDS (4 + IDSET_HEADER_LSIZE)

/*
 * Copy the first 64 bits of __cpuset__ to __mask__.
 */
#define cpuset_to_mask(__cpuset__, __mask__)				\
    idset_to_mask(__cpuset__, __mask__)

/*
 * Assign the first 64 bits from __mask__ to (non-NULL) __cpuset__.
 */
#define mask_to_cpuset(__mask__, __cpuset__)				\
    mask_to_idset(__mask__, __cpuset__)

#endif /* CPUSET_LEGACY */

extern void	cpusetinit(cpuset_t);
extern void	cpuset_clear_extra_bits(cpuset_t, int);
extern void	cpuset_to_array(cpuset_t *, unsigned long *);
extern void	cpusetassign_compl(cpuset_t, cpuset_t);

#endif /* _KERNEL && !_GENASSYM */

#endif /* _SYS_CPUSET_H */
