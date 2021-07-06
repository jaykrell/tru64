/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: processor.h,v $
 * Revision 1.1.28.1  2003/08/28  15:23:07  Anton_Verhulst
 * 	Add struct psr_set_info, psr_set_info() prototypes.
 *
 * Revision 1.1.22.2  2000/10/11  14:10:11  Anton_Verhulst
 * 	Rip out obsolete __SVE__.
 *
 * Revision 1.1.22.1  2000/09/06  19:36:24  David_Gagne
 *  * Add CPU hot swap support:
 *  *
 *  * [2000/04/19  16:46:46  Anton_Verhulst]
 *  * Make P_ONLINE and P_OFFLINE accessible to kernel as well.
 *
 * Revision 1.1.10.4  2000/04/07  19:16:06  Anton_Verhulst
 *  Add prototype assign_cpuset_to_pset().
 *
 * Revision 1.1.10.3  2000/02/25  21:09:14  James_Woodward
 * 	remove PSET_RELEASE_THREADS flag.
 *
 * Revision 1.1.10.2  2000/02/18  19:24:40  Anton_Verhulst
 * 	Change assign_cpu_to_pset() prototype to accept a cpuset.
 *
 * Revision 1.1.10.1  1999/09/30  17:41:49  Anton_Verhulst
 * 	Add define PRIMARY_CPU_NOT_FOUND.
 *
 * Revision 1.1.6.7  1999/05/06  13:51:26  Anton_Verhulst
 * 	Add PSET_RELEASE_THREADS define.
 * 	[1999/05/06  13:32:02  Anton_Verhulst]
 *
 * Revision 1.1.6.6  1999/03/23  19:55:15  Kevin_Harty
 * 	 	** Merge Information **
 * 		** Command used:	bmerge -rSTEELOS **
 * 		** Ancestor revision:	1.1.6.4 **
 * 		** Merge revision:	1.1.6.5 **
 * 	 	** End **
 * 	[1999/03/23  19:54:27  Kevin_Harty]
 * 
 * 	 Put extern "C" around externs for c++
 * 	[1999/03/22  19:01:41  Kevin_Harty]
 * 
 * Revision 1.1.6.5  1999/03/23  18:43:50  Mark_Dewandel
 * 	Add prototype for bind_to_cpu_id().
 * 	[1999/03/17  15:44:16  Mark_Dewandel]
 * 
 * Revision 1.1.6.4  1999/02/09  19:03:53  Ken_Block
 * 	Make header C++ compliant.
 * 	[1998/12/29  22:57:17  Ken_Block]
 * 
 * Revision 1.1.6.3  1998/08/12  17:13:42  Stuart_Hollander
 * 	Add prototypes for bind_to_cpu assign_cpu_to_pset assign_pid_to_pset.
 * 	[1998/08/05  21:12:11  Stuart_Hollander]
 * 
 * Revision 1.1.6.2  1997/08/04  11:47:43  Mark_Dewandel
 * 	Removed definition for NCPUS.
 * 	[1997/07/24  20:01:52  Mark_Dewandel]
 * 
 * Revision 1.1.4.4  1995/06/16  22:55:04  Anton_Verhulst
 * 	Add #define PSR_TEST.
 * 	[1995/06/16  22:53:26  Anton_Verhulst]
 * 
 * Revision 1.1.4.3  1995/05/03  13:37:47  Anton_Verhulst
 * 	Add _DEC define to eliminate build benign build warnings.
 * 	[1995/05/02  17:33:17  Anton_Verhulst]
 * 
 * Revision 1.1.4.2  1995/04/28  22:09:37  Anton_Verhulst
 * 	Add defines and prototypes to support SVE.
 * 	[1995/04/28  21:55:25  Anton_Verhulst]
 * 
 * Revision 1.1.2.3  1994/09/28  20:23:39  Anton_Verhulst
 * 	Add processor set exclusive binding defines.
 * 	[1994/09/27  15:46:22  Anton_Verhulst]
 * 
 * Revision 1.1.2.2  1994/09/10  19:34:57  Anton_Verhulst
 * 	Created/.
 * 	[1994/09/10  19:25:34  Anton_Verhulst]
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: processor.h,v $ $Revision: 1.1.28.1 $ (DEC) $Date: 2003/08/28 15:23:07 $
 */

/* 
 * This file exists to provides SVR4 compatibility.
 */

#ifndef _SYS_PROCESSOR_H
#define	_SYS_PROCESSOR_H
#ifdef __cplusplus
extern "C" {
#endif

/*
 * CPU resource defines.
 */

/* bind_thread_to_cpu() thread defines */
#define ALL_THREADS     0       /* target all threads belonging to task */
/* bind_thread_to_cpu() flag defines */
#define BIND_INHERIT    0
#define BIND_NO_INHERIT	1       /* children will not inherit binding */

/* assign_cpu_to_pset defines */
#define ANY_CPU		1	/* don't care about cpu numbers */

/* processor_set state defines here */
#define PSET_EXCLUSIVE		1 /* Only this process can run on this pset */
#define PSET_NON_EXCLUSIVE 	2 /* Any process can run on this pset */

/*
 * Flags 
 */
#define	P_OFFLINE	1	/* offline cpu or cpu is offline */
#define	P_ONLINE	2	/* online cpu or cpu is online  */

#ifndef _KERNEL

#include <sys/types.h>
#include <cpuset.h>
#include <sys/procset.h>
#include <sys/time.h>
#include <machine/cpuconf.h> 

struct psr_set_info {
	int		pset_id;		/* processor set identifier */
	int		pset_state;		/* see defines above */
	int		pset_pid_count;		/* pids assigned to pset */
	int		pset_thread_count;	/* threads assigned to pset */
	int		pset_processor_count;	/* CPUs assigned to pset */
	int		pset_load_average;	/* scaled X 1000 */
	struct timeval	pset_create_time;
};

extern int pset_get_info(struct psr_set_info **, int *);
extern int pset_get_pids(int, pid_t **, int *);
extern int pset_get_processors(int, cpuset_t);
extern int pset_get_pid_count(int);
extern int pset_get_thread_count(int);
extern int pset_get_processor_count(int);
extern int pset_get_count(void);

extern int bind_to_cpu(pid_t, u_long, u_long);
extern int bind_to_cpu_id(pid_t, long, u_long);
extern int assign_cpu_to_pset(u_long, long, long);
extern int assign_cpuset_to_pset(cpuset_t, long, long);
extern int assign_pid_to_pset(pid_t *, long, long, long);

#define INVALID_PROCESSOR_SET_ID	-500
#define PROCESSOR_SET_ACTIVE		-501
#define	TOO_MANY_PROCESSORS		-502
#define	PROCESSOR_SET_IN_USE		-503
#define	PROCESSOR_SET_EXCLUSIVE_USE	-504
#define	PRIMARY_CPU_NOT_FOUND		-505

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_PROCESSOR_H */



