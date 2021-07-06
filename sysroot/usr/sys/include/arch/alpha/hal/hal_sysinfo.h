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
 *	@(#)$RCSfile: hal_sysinfo.h,v $ $Revision: 1.1.60.1 $ (DEC) $Date: 2002/01/02 18:46:44 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *	This file contains constants used with the hal_getsysinfo() and
 *	hal_setsysinfo() system calls.
 *
 *	Both of these calls are operation driven; particular
 *	flavors of operation may use arguments, identifiers, flags, etc.
 *	to define the actual result.
 *
 */

/***************************************************************************
 ***************************************************************************
 **  WARNING, HAZARD, WATCH OUT, NOTICE!!!!!!!!!!!!!!
 **
 ** Whenever adding a new GSI or SSI number look in both <hal/hal_sysinfo.h>
 ** and <sys/sysinfo.h> to make sure that the function numbers remain unique!
 ** The defines for GSI/SSI appear in these two header files and can not
 ** overlap, otherwise the hal variant would never be called!
 **
 ***************************************************************************
 **
 ** The GSI range <1:68> is randomly assigned to either <sys/sysinfo.h> or
 ** <arch/alpha/hal/hal_sysinfo.h>.  This random assignment is maintained
 ** to provide backward compatibility, however in the future assignments
 ** for GSI in this file (<arch/alpha/hal/hal_sysinfo.h>) should be in the 
 ** range <101:300>.
 ** Assignments for <sys/sysinfo.h> will be in the range <69:100, 301:500>
 **
 ** The SSI range <1:24> is randomly assigned to either <sys/sysinfo.h> or
 ** <arch/alpha/hal/hal_sysinfo.h>.  This random assignment is maintained
 ** to provide backward compatibility, however in the future assignments
 ** for SSI in this file (<arch/alpha/hal/hal_sysinfo.h>) should be in the
 ** range <101:300>.
 ** Assignments for <sys/sysinfo.h> will be in the range <25:100, 301:500>
 **
 ** The SSIN range <1:99> is assigned to <sys/sysinfo.h>.  Assignments
 ** for SSIN in this file (<arch/alpha/hal/hal_sysinfo.h>) must be in 
 ** the range <100:199>.
 **
 ** If these ranges are ever exhausted, new ranges should be
 ** reserved via a comment similar to this in both files.
 **
 ***************************************************************************
 ***************************************************************************/

#ifndef _HAL_SYSINFO_H_
#define _HAL_SYSINFO_H_

#include <sys/types.h>
#include <sys/cpuset.h>

/*
 * struct cpu_info
 *	current_cpu		Is the CPU number that the caller was
 *				running on when the call was made.
 *
 *	cpus_in_box		Is the number of CPUs that are capable of
 *				running during the current boot sesion.
 *
 *	cpu_type		Number corresponding to machine type - see
 *				/usr/include/machine/hal/cpuconf.h.
 *
 *	ncpus			The highest available CPU number plus one.
 *				(e.g., ncpus = 5 for a 3 CPU system with
 *				CPUs numbered 0, 2, and 4.)
 *
 *	cpus_present		Bit mask of processors physically plugged into 
 *				the box (e.g., cpus_present = 0x15 means that
 *				the system has CPUs numbered 0, 2, and 4).
 *
 *	cpus_running		Bit mask of processors currently capable of
 *				having work scheduled on them.
 *
 *	cpu_binding		is a bit mask of processors that have actual
 *				processes bound to it.
 *
 *	cpu_ex_binding		is a bit mask of processors whose processor set
 *				is marked for exclusive use by a task.  Note
 *				that the processor itself may be idle. 
 *
 *	mhz			processor speed in megahertz.
 */
struct cpu_info {
	int     current_cpu;
	int     cpus_in_box;
	int     cpu_type;
	int     ncpus;
	ulong_t cpus_present;	
	ulong_t cpus_running;
	ulong_t cpu_binding;
	ulong_t cpu_ex_binding;
	int	mhz;
	int	unused[3];	/* future expansion */
};

/*
 * The cpusets must be created by cpusetcreate() prior to the call.
 *
 * There are major differences in focus between cpu_info and cpu_state.
 * GSI_CPU_INFO returns data on a partition basis - so if you are on an 
 * 8 cpu turbolaser (for instance) but your partition consists of CPUs 3 and 4,
 * GSI_CPU_INFO will only show you data for CPUs 3 and 4. GSI_CPU_STATE, on
 * the other hand, will show data for the entire machine architecture.
 *
 * cs_present and cs_available refer to the state bits in the percpu 
 * restart parameter block (see arch/alpha/rpb.h).
 */
struct cpu_state {
	int	 cs_cpu_slots;	/* max # CPUs supported by this acrchitecture */
	int	 cs_primary;	/* Current primary processor */
	cpuset_t cs_primary_eligible; /* CPU can be primary */
	cpuset_t cs_configured;	/* CPUs with kernel structs allocated */
	cpuset_t cs_powered;	/* CPU slots currently powered up */
	cpuset_t cs_present;	/* CPUs marked as "present" by firmware */
	cpuset_t cs_available;	/* CPUs marked as "available" by firmware */
	cpuset_t cs_running;	/* CPUs currently running (online) */
	cpuset_t cs_binding;	/* CPUs that have threads bound to them */
	cpuset_t cs_ex_binding;	/* CPUs that have threads exclusively bound */
	cpuset_t cs_hwc_registered; /* CPU is registered with HWC */
	cpuset_t cs_interrupt_enabled; /* CPU is able to take interrupts */
	long	 cs_future[5];	/* Future expansion  - sizeof(cpu_state)=128 */
};
	
/*
 * Tuples for reading IPRs (currently supported only on EV7 platforms).
 * Fill in the CPU and the ADDR fields, the DATA field will be filled
 * in and returned from the system call.
 */
typedef struct ipr {
	u_long	cpu;
	u_long	addr;
	u_long	data;
} ipr_t;

/*
 *	hal_getsysinfo() operation types
 */

/*                      1       RESERVED for sys: GSI_PROG_ENV */
/*                      2       RESERVED for sys: GSI_MAX_UPROCS */
/*                      3       RESERVED for sys: GSI_TTYP */

#define GSI_NETBLK	4	/* Return the entire netblk structure */
				/* which is used for network install */

/*                      5       RESERVED for sys: GSI_BOOTDEV */
/*                      6       RESERVED for sys: GSI_UACSYS */
/*                      7       RESERVED for sys: GSI_UACPARNT */
/*                      8       RESERVED for sys: GSI_UACPROC */
/*                      9       RESERVED for sys: GSI_LMF */

#define GSI_WSD_TYPE    10      /* Workstation Display Type Info */

#define GSI_WSD_UNITS   11      /* Workstation Display Units Info */

/*                      12      RESERVED for sys: GSI_MMAPALIGN */
/*                      13      RESERVED for sys: GSI_BOOTTYPE */
/*                      14      RESERVED for sys: GSI_VPTOTAL */
/*                      15      RESERVED for sys: GSI_SCS */
/*                      16      RESERVED for sys: GSI_IECSYS */
/*                      17      RESERVED for sys: GSI_IECPARNT */
/*                      18      RESERVED for sys: GSI_IECPROC */
/*                      19      RESERVED for sys: GSI_PHYSMEM */
/*                      20      RESERVED for sys: GSI_DNAUID */


#define	GSI_BOOTCTLR	21	/* Logical Controller # for TURBOchannel slot */

#define	GSI_CONSTYPE	22	/* MIPS console type identifier */


/* All values from 1 - 22 are reserved. This is for compatibility */
/* with ULTRIX							  */

#define GSI_BUS_STRUCT  23     /* get bus structure */
#define GSI_BUS_NAME    24     /* get name of bus */

#define GSI_CTLR_STRUCT 25     /* get controller structure */
#define GSI_CTLR_NAME   26     /* get name of controller */

#define GSI_DEV_STRUCT  27     /* get device structure */
#define GSI_DEV_NAME    28     /* get name of device */

#define	GSI_CPU		29     /* cpu type (from cpu global variable) */
#define GSI_MAX_CPU     30     /* max # cpu's on this machine */

/*                      31      RESERVED for sys: GSI_ROOTDEV */
/*                      32      RESERVED for sys: GSI_DUMPDEV */
/*                      33      RESERVED for sys: GSI_SWAPDEV */

#define GSI_PRESTO      34     /* size of non-volatile ram if installed */

/*                      35      RESERVED for sys: GSI_COMPAT_MOD */

#define GSI_GRAPHICTYPE 36     /* Graphics module names */

/*			37     AVAILABLE FOR USE: GSI_TBD */

#define GSI_SCS_SYSID   38     /* scs_sysid for ci */
#define GSI_BUS_PNAME   39     /* get port name of bus */
#define GSI_CTLR_PNAME  40     /* get port name of controller */

/*                      41      RESERVED for sys: GSI_STATIC_DEF */
/*                      42      RESERVED for sys: GSI_CLK_TCK */

#define GSI_WSD_CONS	43     /* get console device type (0=gfx,1=alt) */
#define GSI_BOOTEDFILE	44     /* get booted kernel filename */
#define GSI_IEEE_FP_CONTROL 45 /* gateway to ieee_get_fp_control */
#define GSI_IEEE_STATE_AT_SIGNAL 46 /* gateway to ieee_get_state_st_signal */
#define GSI_PROM_ENV	47

/*                      48      RESERVED for sys: GSI_IPRSETUP */
/*                      49      RESERVED for sys: GSI_DUMPINFO */

#define GSI_GRAPHIC_RES	50     /* get graphics card resolution */

#define GSI_LURT	51     /* get LURT table entry for licensing use */

#define GSI_KEYBOARD	52     /* get keyboard name */
#define GSI_POINTER	53     /* get mouse/tablet name */

/*                      54      RESERVED for sys: GSI_CURRENT_CPU */
/*                      55      RESERVED for sys: GSI_CPUS_IN_BOX*/

#define GSI_CONS_BOOTPATH 56	/* get the booted_dev string for the console */
#define GSI_CONS_BOOTDEV 57	/* get the user device name string ie dka100 */

/*                       58     RESERVED for sys: GSI_SIGQ_MAX */

#define GSI_CPU_INFO	59	/* CPU information */

#define GSI_PROC_TYPE   60      /* get proc_type (eg, EV4 P2, per SRM app. D) */
#define GSI_MODULE_LIST	61	/* get module list (up to 1 page or so) */

/*                      62      RESERVED for sys: GSI_VERSIONSTRING */
/*                      63      RESERVED for sys: GSI_DBASE */
/*                      64      RESERVED for sys: GSI_IPDEFTTL */

#define GSI_LITE_SYSTEM 65      /* determine if this is a lite box */
#define	GSI_BYTEWORD_IO	66	/* Is byte/word IO supported & enabled? */

/*                      67      RESERVED for sys: GSI_TIMER_MAX */
/*                      68      RESERVED for sys: GSI_FD_NEWMAX */

/*****************************************************************************
 **
 ** THE RANGE <69:100, 301:500> IS RESERVED FOR USE IN <sys/sysinfo.h>  DO NOT
 ** USE THESE VALUES FOR GSI IN THIS FILE!
 **
 ** THE VALID RANGE FOR GSI IN THIS FILE IS <101:300>.
 **
 ****************************************************************************/

#define GSI_GET_HWRPB	101	/* get the HWRPB */

#define GSI_DEV_TYPE	102     /* get dev type of device (disk, tape, etc.) */
#define GSI_PLATFORM_NAME 103	/* get platform name as string (e.g.	*/
                                /* "AlphaStation 2100 4/200" */

#define GSI_NO_BINLOGD_FRU 109  /* if true binlogd should NOT log FRU table */
#define GSI_FRU_TABLE_SIZE 110	/* get size of Field Replaceable Unit table */
#define GSI_FRU_TABLE      111	/* get Field Replaceable Unit table */
#define GSI_FIRMWARE_REV   112	/* get console firmware revision information */
#define GSI_PALCODE_REV    113	/* get palcode revision information  */
#define GSI_FAM_CPU_SMM    114  /* get the platform ids used by firmware */
#define GSI_PROM_VAR       115  /* get the table of console EV info */
#define GSI_CONSDEV_TO_DEVT 116	/* Convert console device string to dev_t */
#define GSI_READ_FRU_EEROM 117  /* read eerom data from a FRU */
#define GSI_SIZER          118  /* Sizer(8) hardware info via this interface */
#define GSI_READ_IPRS	   119  /* read IPRs (through platform get_info) */
#define GSI_CPU_STATE	   120	/* CPU configured, slote powered, etc */
#define SIZER_NODETBL      1    /* sizer arg: get the nodetbl data */
#define SIZER_NODETBL_SZ   2    /* sizer arg: get the size of the nodetbl entries */
#define SIZER_NODETBL_B    3    /* sizer arg: get the size of the nodetbl bytes */
#define SIZER_CPUTBL       4    /* sizer arg: get the cputbl data */
#define SIZER_CPUTBL_SZ    5    /* sizer arg: get the size of the devtbl entries */
#define SIZER_CPUTBL_B     6    /* sizer arg: get the size of the devtbl bytes */
#define SIZER_DEVTBL       7    /* sizer arg: get the devtbl data */
#define SIZER_DEVTBL_SZ    8    /* sizer arg: get the size of the devtbl entries */
#define SIZER_DEVTBL_B     9    /* sizer arg: get the size of the devtbl bytes */
#define SIZER_HARDTBL      10   /* sizer arg: get the hardtbl data */
#define SIZER_HARDTBL_SZ   11   /* sizer arg: get the size of the hardtbl entries */
#define SIZER_HARDTBL_B    12   /* sizer arg: get the size of the hardtbl bytes */
#define SIZER_DRVTBL       13   /* sizer arg: get the drvtbl data */
#define SIZER_DRVTBL_SZ    14   /* sizer arg: get the size of the drvtbl entries */
#define SIZER_DRVTBL_B     15   /* sizer arg: get the size of the drvtbl bytes */

/*
 * 	setsysinfo() variable names
 */

/*                           1    RESERVED for sys: SSI_NVPAIRS */
/*                           2    RESERVED for sys: SSI_ZERO_STRUCT */
/*                           3    RESERVED for sys: SSI_SET_STRUCT */
/*                           4    RESERVED for sys: SSI_TBD */
/*                           5    RESERVED for sys: SSI_TBD */
/*                           6    RESERVED for sys: SSI_TBD */
/*                           7    RESERVED for sys: SSI_LMF */
/*                           8    RESERVED for sys: SSI_LOGIN */
/*                           9    RESERVED for sys: SSI_SLIMIT */
/*                          10    RESERVED for sys: SSI_ULIMIT */
/*                          11    RESERVED for sys: SSI_DUMPDEV */
/*                          12    RESERVED for sys: SSI_TBD */
/*                          13    RESERVED for sys: SSI_IPRSETUP */

#define SSI_IEEE_FP_CONTROL 14 /* gateway to ieee_set_fp_control */
#define SSI_IEEE_STATE_AT_SIGNAL 15 /* gateway to ieee_eet_state_st_signal */
#define SSI_IEEE_IGNORE_STATE_AT_SIGNAL 16 /* to ieee_ignore_state_st_signal */
#define SSI_PROM_ENV	17

/*                          18    RESERVED for sys: SSI_DBASE*/
/*                          19    RESERVED for sys: SSI_IPDEFTTL */

#define SSI_PROM_SAVE_ENV 20		/* allow user to save console Env Vars */

/*                          21    RESERVED for sys: SSI_TBD */
/*                          22    RESERVED for sys: SSI_TBD */
/*                          23    RESERVED for sys: SSI_TBD */
/*                          24    RESERVED for sys: SSI_FD_NEWMAX */

/*****************************************************************************
 **
 ** THE RANGE <25:100, 301:500> IS RESERVED FOR USE IN <sys/sysinfo.h>  DO NOT
 ** USE THESE VALUES FOR SSI IN THIS FILE!
 **
 ** THE VALID RANGE FOR SSI IN THIS FILE IS <101:300>.
 **
 ****************************************************************************/

#define SSI_WRITE_FRU_EEROM 101 /* write data into a FRU eerom */

/*
 *      setsysinfo() SSI_NVPAIRS variable names
 */

/* All values from 1 - 8 are reserved for compatibility with ULTRIX */

/*                           1    RESERVED for sys: SSIN_NFSPORTMON */
/*                           2    RESERVED for sys: SSIN_NFSSETCLOCK */
/*                           3    RESERVED for sys: SSIN_PROG_ENV */
/*                           4    RESERVED for sys: SSIN_UACSYS */
/*                           5    RESERVED for sys: SSIN_UACPARNT */
/*                           6    RESERVED for sys: SSIN_UACPROC */
/*                           7    RESERVED for sys: SSIN_IECSYS */
/*                           8    RESERVED for sys: SSIN_IECPARNT */
/*                           9    RESERVED for sys: SSIN_IECPROC */

/*****************************************************************************
 **
 ** THE RANGE <1:99> IS RESERVED FOR USE IN <sys/sysinfo.h>  DO NOT
 ** USE THESE VALUES FOR SSIN IN THIS FILE!
 **
 ** THE VALID RANGE FOR SSIN IN THIS FILE IS <100:199>.
 **
 ****************************************************************************/

#define SSIN_LOAD_CONFIG 100	/* Add a new loadable driver config struct */
#define SSIN_DEL_CONFIG 101	/* Delete all driver config structs        */

#endif /* _HAL_SYSINFO_H_ */



