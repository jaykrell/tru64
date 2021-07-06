/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: rad.h,v $
 * Revision 1.1.24.4  2003/11/13  22:42:38  Brian_Haley
 * 	Added in6_localaddrs_work pointer in network cache block.
 *
 * Revision 1.1.24.3  2003/10/14  18:30:06  Paul_Park
 * 	Add rad_rpcs for RPC server data.
 *
 * Revision 1.1.24.2  2003/06/19  13:27:38  Matthew_McGrath
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Matthew_McGrath_tunebp_br:1.1.23.1 Local Ancestor:1.1.12.7
 *    Merge Revision:  v51bsupportos_br:1.1.24.1
 *   Common Ancestor:  1.1.12.7
 *
 * Revision 1.1.24.1  2003/06/13  18:15:49  Eric_Werme
 *  * Add RPC and NFS client data.
 * 
 * Revision 1.1.23.1  2003/06/13  17:43:22  Matthew_McGrath
 * 	Add nmads, the number of RADs with memory.
 * 
 * Revision 1.1.12.7  2002/02/18  20:50:02  Rajesh_R
 * 	Remove hal_hwnodes_per_rad (Marvel file cleanup).
 * 
 * Revision 1.1.12.6  2002/01/29  21:18:24  Geraldine_Harter
 * 	Add VMS code changes needed to facilitate porting TCP/IP to VMS.
 * 
 * Revision 1.1.12.5  2002/01/29  20:33:19  Mark_Dewandel
 * 	Add RAD set argument to proc_move_to_rad() prototype.
 * 
 * Revision 1.1.12.4  2002/01/28  20:42:07  James_Woodward
 * 	Changes for marvel scheduler.
 * 
 * Revision 1.1.12.3  2001/12/17  20:54:14  Vladislav_Yasevich
 * Merge Information:  Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Vladislav_Yasevich_wcalphaos_ipv6_br:1.1.14.1 Local Ancestor: n/a
 *    Merge Revision:  wcalphaos_br:1.1.12.2
 *   Common Ancestor:  1.1.12.1
 * 	Merge with mainline.
 * 
 * Revision 1.1.12.2  2001/10/24  22:19:38  Rajesh_R
 * 	Define maximum number of RADS for use by platform_numa_init();
 * 
 * Revision 1.1.14.1  2001/10/03  14:51:28  Geraldine_Harter
 * 	Changes from wildcatos-1165-harter:
 * 	- Add IPv6 input queues and netisrs.
 * 
 * Revision 1.1.12.1  2001/09/27  20:29:47  Fran_Fadden
 *  * Add data for /dev/random support.
 * 
 * Revision 1.1.4.1  2000/10/10  14:14:31  James_Woodward
 * 	Add rad_t typedef.
 * 
 * Revision 1.1.2.26  2000/05/22  18:46:31  Anton_Verhulst
 * 	Add proc_move_to_rad() prototype.
 * 
 * Revision 1.1.2.25  2000/01/27  20:24:46  Ernie_Petrides
 * 	Allow for replication of read-mostly global variables.
 * 
 * Revision 1.1.2.24  2000/01/27  19:49:21  Sowmini_Varadhan
 * 	Add pointer to the ipv6 control structure.
 * 	Remove arptab pointer.
 * 
 * Revision 1.1.2.23  2000/01/26  22:29:26  John_Dustin
 * 	Add netisr_table.
 * 
 * Revision 1.1.2.21  2000/01/19  16:35:11  Eric_Werme
 * 	Extend struct rad for NFS data.
 * 
 * Revision 1.1.2.20  2000/01/11  16:10:16  Anton_Verhulst
 * 	Add rad_processor_queue.
 * 
 * Revision 1.1.2.19  1999/12/22  17:40:10  Ernie_Petrides
 * 	Fix cache alignment within 2nd block of rad structure.
 * 
 * Revision 1.1.2.18  1999/12/21  16:41:40  Anton_Verhulst
 * 	Change to fix user space build errors (netstat needs to be fixed).
 * 
 * Revision 1.1.2.17  1999/12/16  21:55:22  Anton_Verhulst
 * 	Add aio hooks.
 * 
 * Revision 1.1.2.16  1999/12/14  21:23:22  John_Dustin
 * 	Allocate 4 cache blocks for networking, local wait queues, etc.
 * 
 * Revision 1.1.2.15  1999/12/07  23:20:51  Tony_Bono
 * 	Added pointer to the tcp control struct.
 * 
 * Revision 1.1.2.14  1999/12/03  22:08:04  John_Dustin
 * 	removed netisr_active_block; added netisr_slock
 * 
 * Revision 1.1.2.13  1999/11/30  21:32:37  Brian_Haley
 * 	Added #include of kern/lock.h and kern/queue.h for compiler warnings.
 * 
 * Revision 1.1.2.12  1999/11/30  20:35:56  James_Woodward
 * 	fix incorrect extern for cpus_per_rad.
 * 	[1999/11/30  20:34:56  James_Woodward]
 * 	add task free list to rad structure to allow delayed freed.  This
 * 	was done to move the proc_lock back into the proc structure, yet
 * 	remove the need to get the pid entry lock when accessing a proc.
 * 	Added rad macros for "execution" context and cpu logical index
 * 	within a rad.
 * 	[1999/11/30  12:47:14  James_Woodward]
 * 
 * Revision 1.1.2.10  1999/11/04  22:27:27  John_Dustin
 * 	Added numnetisrthreads and netisr_active_block to rad struct
 * 
 * Revision 1.1.2.9  1999/09/28  20:14:31  Shashi_Mangalat
 * 	Fix build error: change use of thread_t typedef.
 * 
 * Revision 1.1.2.8  1999/09/27  20:58:08  Brian_Haley
 * 	Added Network cache block to rad struct.
 * 
 * Revision 1.1.2.7  1999/08/05  20:45:40  Shashi_Mangalat
 * 	Move gh_mads to rad.
 * 	[1999/08/04  13:14:03  Shashi_Mangalat]
 * 
 * Revision 1.1.2.6  1999/07/30  19:56:05  Peter_Keilty
 * 	add cam cache block area.
 * 	[1999/07/30  14:03:04  Peter_Keilty]
 * 
 * Revision 1.1.2.5  1999/07/14  19:45:23  James_Woodward
 * 	remove u_mad from thread structure and use u_rad pointer.
 * 	[1999/07/12  18:48:04  James_Woodward]
 * 
 * Revision 1.1.2.4  1999/07/08  19:22:31  James_Woodward
 * 	fix current_rad() macro.
 * 	[1999/07/08  11:13:42  James_Woodward]
 * 
 * Revision 1.1.2.3  1999/06/23  11:50:32  James_Woodward
 * 	change to per-rad allocation of callout structures.
 * 	add per-rad reaper thread.
 * 	[1999/06/22  14:17:23  James_Woodward]
 * 
 * Revision 1.1.2.2  1999/06/21  14:05:04  James_Woodward
 * 	add rad.h and rad structure
 * 	[1999/06/17  12:46:33  James_Woodward]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: rad.h,v $ $Revision: 1.1.24.4 $ (DEC) $Date: 2003/11/13 22:42:38 $
 */

#ifndef _KERN_RAD_H_
#define _KERN_RAD_H_

#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/sched.h>
#ifdef _KERNEL
#include <kern/thread.h>
#include <sys/sysaio.h>
#endif /* _KERNEL */

struct rad {
	/* 64 bytes of read-mostly data */
	int				rad_id;
	int				rad_state;
	struct memory_affinity_domain	*rad_mad;
	struct gh_mad			*rad_gh;
	simple_lock_data_t		rad_processor_queue_lock;
	queue_head_t	 		rad_processor_queue;
	long				rad_num_processors;
	int				rad_type;
	boolean_t			rad_has_io;

	/* 64 bytes callout queue handle */
	simple_lock_data_t rad_callout_free_lock;
	struct callout *rad_callfree;
	long		rad_num_callout_free;
	long		rad_num_callout;
	int		rad_callout_lowater;
	int		rad_callout_hiwater;
	long		pad2[3];

	/* The grim reaper cache block */
	queue_head_t	rad_reaper_queue;
	simple_lock_data_t rad_reaper_lock;
	struct thread	*rad_reaper_thread_ptr;
	long		rad_reaper_th_count;
	long		pad3[3];

	/* Cam cache block */
	void		*cam_xpt_cback_hdr;
	long		cam_pad[7];

	/* Network info, 2 cache blocks (128 bytes) */
	struct radix_node_head	*radix_node_head;
	void			*ipv6control;
	void			*tcpradcontrol;
	struct in6_localaddr	*in6_localaddrs_work;
	long			net_pad_a[4];
	long			net_pad_b[8];

	/* netisr control cache block */
	wait_queue_data_t	netisr_servers;
	simple_lock_data_t	netisr_slock;
	struct netisr_dynamic	*netisr_dynamic;
	long			net_pad_c[2];

	/* ipqs/netisrs read-mostly cache block */
	struct netisr		*netisr_active;
	struct netisr		*netisr_inactive;
	struct ifqueue		**ipintrqs;
	struct netisr		**ip_netisr;
	struct ifqueue		**ip6intrqs;
	struct netisr		**ip6_netisr;
	struct netisr		*netisr_table;
	int			numnetisrthreads;
	int			net_pad_d[1];

	/* next cache block start */
	simple_lock_data_t	rad_task_fl_lock; /* task free list lock */
	queue_head_t		rad_task_fl;	  /* free tasks for rad */
	long			rad_fl_count;
	long			rad_fl_tail_time;
	long			rad_fl_frees;
	long			rad_fl_pad[2];

	/* next cache block start */
#ifdef _KERNEL
	struct thread *		aio_completion_thread_ptr;
	mpqueue_head_t		aio_completion_queue;
	aio_dev_cache_t	*	aio_dev_cache;
	long			aio_pad[3];
#else
	long			aio_pad[8];
#endif /* _KERNEL */

	/* NFS cache block start */
	struct nfs_radinfo *	rad_rfs;	/* NFS server data */
	struct nfsc_radinfo *	rad_nfsc;	/* NFS client data */
	struct rpc_radinfo *	rad_rpc;	/* RPC data */
	void *			rad_rpcs;	/* RPC server data */
	int			nfs_nrads;	/* # rads to check */
	int			nfs_pad[7];

       /* /dev/random cache block start
	* ran_prime, ran_second, and ran_sthread are only set here if they are
	* configured per-RAD; they could each also be configured per-CPU (in
	* struct processor) or PER-System (in global variables).
	*
	* These pointers are used seldom.
	*/
       struct random_entropy_store *ran_prime;   /* primary entropy pool -- data moves from batch_queue to here */
       struct random_entropy_store *ran_second;  /* secondary entropy pool -- data moves from primary to here */
       struct thread               *ran_sthread; /* thread to migrate entropy from primary to secondary */
       struct random_bthread_args *ran_bthread_args; /* arg structure for migrating entropy from batch to primary */
       int random_pad[8];	                 /* pad to 64-byte boundary */
};

#ifdef _KERNEL

#ifndef REPLICATED
#define REPLICATED
#endif

typedef struct rad *rad_t;

extern struct rad ** REPLICATED rad_ptr;/* base of rad structure ptr table */
extern REPLICATED int nrads;		/* number of rads in the system */
extern REPLICATED int cpus_per_rad;	/* max number of cpus in a rad */
extern REPLICATED int nmads;		/* number of rads with memory */

/*
 * Platform HAL NUMA globals and definitions.
 */
#define RAD_EMPTY	0	/* RAD is currently not is use */
#define RAD_CPU_NOMEM	1	/* contains CPUs, but no memory */
#define RAD_CPU_LCLMEM	2	/* CPUs and only local (non-striped) memory */
#define RAD_LCL_MEM	3	/* contains only local (non-striped) memory */
#define RAD_STP_MEM	4	/* contains only striped memory */
#define RAD_SGM_MEM	5	/* contains only shared global memory */

/*
 * Size platform HAL NUMA data structures (const_data.c).
 * Must patch definitions in marvel_soc.h (code checks for mismatch).
 *
 * From marvel_soc.h: MV_MAX_SOCS = 64, MV_MAX_CPUS = 64.
 *
 * RADS allocated in three segments:
 *   RAD_SOC_MEM: MV_MAX_CPUS enough RADs for one CPU per RAD.
 *   RAD_LCL_MEM or RAD_STP_MEM: one RAD/SOC for local/striped memory.
 *   RAD_SGM_MEM: one RAD/SOC for shared global memory.
 *
 * Size is MV_MAX_SOCS + MV_MAX_SOCS + MV_MAX_SOCS.
 *
 */
#define MAX_RADS	64

#define MAX_RADS_X3	(MAX_RADS * 3)
#define RAD_SEGMENTS	3
#define RAD_LCL_BASE	0
#define RAD_STP_BASE	(MAX_RADS_X3 / RAD_SEGMENTS)
#define RAD_SGM_BASE	((MAX_RADS_X3 / RAD_SEGMENTS) + (MAX_RADS_X3 / RAD_SEGMENTS))

						/* CPU number to RAD ID */
extern REPLICATED int cpu_to_rad_id_shift;


extern REPLICATED struct hal_rad platform_hal_rad[];

extern void rad_init(int);
extern int cpu_to_rad_id(int);
extern int get_cpu_pag_logical_index(int);
extern int proc_move_to_rad(struct proc *, int, boolean_t, int, radset_t);
extern radid_t *get_rad_dist(radid_t);

#ifndef __VMS
#define cpu_to_rad(cpu)		(rad_ptr[cpu_to_rad_id(cpu)])
#define processor_to_rad(prc)	(prc->processor_rad)
#define rad_id_to_rad(rid)	(rad_ptr[(rid)])
#define current_rad()	 (AT_INTR_LVL() ? u.processor->processor_rad \
						: u.u_rad)

#define current_rad_id() (AT_INTR_LVL() ? u.processor->processor_rad->rad_id \
						: u.u_rad->rad_id)

#define current_execution_rad()		(u.processor->processor_rad)
#define current_execution_radid()	(u.processor->processor_rad->rad_id)
#define current_cpu_rad_logical_index()	(u.processor->processor_rad_logical_index)
#else	/* __VMS */
#define current_rad()			((struct rad      *) rad_ptr[0])
#define rad_id_to_rad(rid)		(rad_ptr[(rid)])
#define processor_to_rad(prc)	        ((struct rad      *) rad_ptr[0])
#define current_rad_id()		(0)
#define current_execution_radid()	(0)
#define current_execution_rad()		((struct rad      *) rad_ptr[0])
#define current_cpu_rad_logical_index()	(0)
#endif /* __VMS */

#endif /* _KERNEL */
#endif /* _KERN_RAD_H_ */
