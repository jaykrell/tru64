/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: numa.h,v $
 * Revision 1.1.11.1  2003/06/05  17:26:44  Anton_Verhulst
 * 	Add prototype for numa_query_pid().
 *
 * Revision 1.1.8.1  2001/03/07  19:52:29  James_Woodward
 * 	We need to conditionalize the definition of the pthread_*()
 * 	on _POSIX_C_SOURCE being greater than 199506L, which is when a
 * 	proper definition of pthread_t will be provided by sys/types.h.
 * 	Submission on behalf of Peter Portante.
 *
 * Revision 1.1.2.9  2000/06/23  14:08:23  Anton_Verhulst
 * 	Add prototypes for memalloc_attr() and pthread_rad_detach().
 *
 * Revision 1.1.2.8  2000/05/10  20:08:54  James_Woodward
 * 	adds flags parameter to rad_fork().
 *
 * Revision 1.1.2.7  2000/03/28  17:14:57  devbld_zko
 * 	DECthreads V3.18-012 submit
 *
 * 	Bring pthread_nsg_detach() in line with man page specification.
 *
 * Revision 1.1.2.6  2000/01/28  20:21:08  David_Long
 * 	Added nacreate.
 *
 * Revision 1.1.2.5  1999/12/17  17:36:49  Stephen_Corbin
 * 	Change nmadvise len parameter from size_t to long
 *
 * Revision 1.1.2.4  1999/11/30  16:07:34  Anton_Verhulst
 * 	Fix nsg_init() prototype. Add new NSG prototypes.
 *
 * Revision 1.1.2.3  1999/10/27  20:54:01  Anton_Verhulst
 * 	* Synch up with the latest API state.
 *
 * Revision 1.1.2.2  1999/06/16  19:59:49  Anton_Verhulst
 * 	Created.
 * 	[1999/06/16  19:56:13  Anton_Verhulst]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: numa.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2003/06/05 17:26:44 $
 */

#ifndef	_NUMA_H
#define _NUMA_H

#include <sys/numa_types.h>
#include <sys/mman.h>
#include <sys/shm.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Topology Query APIs
 */
extern radid_t cpu_get_rad(cpuid_t);

extern radid_t rad_get_current_home(void);
extern int rad_get_num(void); 
extern int rad_get_max(void); 
extern int rad_get_info(radid_t, rad_info_t *); 
extern int rad_get_cpus(radid_t, cpuset_t *); 
extern ssize_t rad_get_physmem(radid_t); 
extern ssize_t rad_get_freemem(radid_t);

extern int nloc(numa_attr_t *, radset_t); 

/*
 * Process/Thread Management APIs:
 */
extern int rad_bind_pid(pid_t, radset_t, long);
extern int rad_attach_pid(pid_t, radset_t, long);
extern int rad_detach_pid(pid_t);

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
extern int pthread_rad_attach(pthread_t, radset_t, ulong_t);
extern int pthread_rad_bind(pthread_t, radset_t, ulong_t);
extern int pthread_rad_detach(pthread_t);
#endif

extern pid_t nfork(numa_attr_t *);
extern pid_t rad_fork(radid_t, ulong_t);

extern int numa_query_pid(pid_t,  numa_pid_info_t *);

/*
 * Memory Management APIs:
 */
extern int memalloc_attr(vm_offset_t, memalloc_attr_t *); 

extern int nmadvise(void *, long, int, memalloc_attr_t *);
extern void *nmmap(void *, size_t, int, int, int, off_t, memalloc_attr_t *); 

extern int nshmget(key_t, size_t, int, memalloc_attr_t *);

/*
 * NUMA Scheduling Groups:
 */
extern int nsg_attach_pid(nsgid_t, pid_t, ulong_t);
extern int nsg_detach_pid(pid_t);
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
extern int pthread_nsg_attach(nsgid_t, pthread_t, long);
extern int pthread_nsg_detach(pthread_t);
extern int pthread_nsg_get(nsgid_t, pthread_t*, long);
#endif
extern int nsg_destroy(nsgid_t);
extern int nsg_get(nsgid_t, nsgid_ds_t *);
extern int nsg_get_nsgs(nsgid_t *, int);
extern int nsg_get_pids(nsgid_t, pid_t *, int);
extern int nsg_set(nsgid_t, nsgid_ds_t *);
extern nsgid_t nsg_init(key_t, ulong_t);

/*
 * NUMA malloc APIs:
 */
void *nacreate(int, memalloc_attr_t *);

#ifdef __cplusplus
}
#endif

#endif	/* _NUMA_H */
