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
 * @(#)$RCSfile: platform.h,v $ $Revision: 1.1.29.3 $ (DEC) $Date: 2002/02/18 20:49:38 $
 */

#ifndef _ARCH_ALPHA_HAL_PLATFORM_H_
#define _ARCH_ALPHA_HAL_PLATFORM_H_

#include	<sys/types.h>
#include	<sys/time.h>
#include	<machine/rpb.h>
#include	<sys/sysconfig.h>
#include	<sys/errno.h>
#include	<mach/machine.h>
#include	<hal/cpuconf.h>
#include	<io/common/devdriver.h>
#include	<sys/idset.h>			/* for #define BITS_PER_LONG */

#if defined(_KERNEL)

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_USE_KERNEL_PROTOS)

extern void dump_dev(struct dump_request *dump_req);

/* from arch/alpha/hal/cpusw.c */
extern u_long no_dma_map_alloc(void);
extern u_long no_dma_map_load(void);
extern int no_dma_map_unload(void);
extern int no_dma_map_dealloc(void);
extern int no_dma_min_bound(void);
extern long no_read_io_port(void);
extern void no_write_io_port(void);
extern u_long no_iohandle_to_phys(io_handle_t io_handle, long flags);
extern int no_io_blockread(void);
extern int no_io_blockwrite(void);
extern int no_io_blockclear(void);
extern int no_io_blockexchange(void);

#else /* !defined(_USE_KERNEL_PROTOS) */

/* from arch/alpha/hal/cpusw.c */
extern u_long		no_dma_map_alloc();
extern u_long		no_dma_map_load();
extern int		no_dma_map_unload();
extern int		no_dma_map_dealloc();
extern int		no_dma_min_bound();
extern long		no_read_io_port();
extern void		no_write_io_port();
extern u_long		no_iohandle_to_phys();
extern int		no_io_blockread();
extern int		no_io_blockwrite();
extern int		no_io_blockclear();
extern int		no_io_blockexchange();

#endif /* defined(_USE_KERNEL_PROTOS) */

/* from arch/alpha/hal/console.c */
extern void hal_pci_cons2dev(struct item_list *request, struct bus *mainbus);
extern void hal_pci_cons2ctl(struct item_list *request, struct bus *mainbus);
extern void hal_pci_dev2cons(struct item_list *request, int bus_probe_alg_type);
extern void hal_pci_dev2user(struct item_list *request);
extern void hal_pci_dump_dev(struct dump_request *dump_req,
		int bus_probe_alg_type);
extern void hal_pci_cons_devstr(int bus_probe_alg_type, char *device_string,
		struct device *device, char *protocol, u_int remoteid,
		u_int unit, caddr_t srm_suffix);

/* from arch/alpha/machdep.c */
extern void mces_mcheck_clear(uint cpuid);

/* from arch/alpha/hal/halswitch.c */
extern boolean_t testpage(long);
extern void get_numa_distances(int, int *, radid_t *);

/* from arch/alpha/hal/platform_switch.c */
extern void machcheck(long, void *, void *, void *, void *);
extern void syscorr_intr(long, void *, void *, void *, void *);
extern void proccorr_intr(long, void *, void *, void *, void *);

/*
 * Registration Tokens
 *
 * These variables are used by the platform support modules in arch/alpha/hal.
 * They are set and/or checked by all configured platform support modules at
 * CFG_PT_HAL_INIT.  Typically, the knxxx.mod file schedules a callback at
 * CFG_PT_HAL_INIT/CFG_ORD_HAL_EARLY to initialize appropriate tokens.  The 
 * common hardware support modules register a callback at 
 * CFG_PT_HAL_INIT/CFG_ORD_DONTCARE to determine whether the knxxx.mod file 
 * has requested them to register their support routines.
 * 
 * For example, on a Rawhide, the following occurs at CFG_PT_HAL_INIT:
 *
 *	1. At CFG_ORD_HAL_EARLY, kn300.mod checks sys_type to see if the 
 *	   machine it is running on is ST_DEC_4100.
 *	2. If it isn't, kn300.mod returns.
 *	3. If it is ST_DEC_4000, kn300.mod registers the hardware support 
 *	   routines provided within its module with the platform switch.
 *	4. kn300.mod sets tokens for other common support modules it needs to
 *	   have registered.  In particular, it sets use_mc146818 and 
 *	   use_pc_bell.
 *	5. At CFG_ORD_DONTCARE, all configured common support routines check
 *	   the token appropriate to them to determine if they should register
 *	   their support.  In this case, pc_bell.mod and mc146818.mod will 
 *	   find the relevant token set and will register their support with
 * 	   the platform switch.
 *
 */

/*
 * Platform_callsw Tokens
 */

extern int    use_pc_bell;		
extern int    use_mc146818;
extern int    use_ds1386;
extern int    use_dc21171;
extern int    use_cbus2_pci;
extern int    use_ruby_common;
extern int    use_lsbmem;

/* 
 * I/O Access, DMA Access callsw Tokens
 */

extern int    use_apecs;
extern int    use_lca;
extern int    use_mcpcia;
extern int    use_pcia;
extern int    use_dc104x;
extern int    use_wfpci;
extern int    use_mvpci;


extern long   sys_type;                 /* system type (family or platform) */
extern char   *platform_name;		/* platform_name for registering 
                                         * platform support with EHM.  This 
                                         * is initialized in init_platform */

#define PLATFORM_USE_HAL_SWITCH		/* use for platform conditional compiles */
#define NUMA_HAL

/*
 * Platform Switch Registration Return Values
 *
 * These values may be returned by register_platform_switch().  The values
 * are in the range 0x0000 to 0x0999.
 *
 */
#define PLATFORM_SW_SUCCESS             0x0000  /* Successful registration   */
#define PLATFORM_SW_FAILURE             0x0001  /* Generic failure return    */
#define PLATFORM_SW_UNK_DESC            0x0002  /* Descriptor passed unknown to
                                                   register_platform_switch()*/
#define PLATFORM_SW_NO_SUP              0x0003  /* Descriptor passed is not
                                                   supported in this rev of
                                                   platform switch           */
                                                                        

/*
 * Platform Switch Routine Descriptors
 *
 * These descriptors are used to indicate to the platform switch registration
 * routine (register_platform_switch()) which routine is being registered.
 *
 * Valid range for descriptor values is 0x1000 to 0x1999.
 *
 */

#define PLATFORM_SW_INIT                0x1000	/* platform_init()           */
#define PLATFORM_SW_CONFIG              0x1001	/* platform_configure()      */
#define	PLATFORM_SW_MACH_ERROR		0x1002	/* mach_error()              */
#define PLATFORM_SW_MACHCHECK		0x1003	/* machcheck()  660/670      */
#define PLATFORM_SW_SYS_CORR_ERR	0x1004	/* harderr_intr() 0x620      */
#define PLATFORM_SW_PROC_CORR_ERR	0x1005	/* softerr_intr() 0x630      */
#define PLATFORM_SW_BADADDR		0x1006	/* badaddr()                 */
#define PLATFORM_SW_DUMP_DEV		0x1007	/* dump_dev()                */
#define PLATFORM_SW_GET_INFO            0x1008	/* get_info()                */
#define PLATFORM_SW_INIT_2NDARY		0x1009	/* init_secondary()          */
#define PLATFORM_SW_CONFIG_2NDARY	0x100a	/* config_secondary()        */
#define PLATFORM_SW_RING_BELL		0x100b	/* ring_bell()               */
#define PLATFORM_SW_TESTPAGE		0x100c	/* testpage()                */
#define PLATFORM_SW_MEMENABLE		0x100d	/* memenable()               */
#define PLATFORM_SW_READTODR		0x100e	/* readtodr()                */
#define PLATFORM_SW_WRITETODR           0x100f	/* writetodr()               */
#define PLATFORM_SW_PAG_NUM		0x1010	/* pag_num()                 */
#define PLATFORM_SW_INTERRUPT_DISTRIB	0x1011	/* interrupt_distribute()    */
#define PLATFORM_SW_POWER_CTL		0x1012	/* power_ctl()               */
#define PLATFORM_SW_CFGTREE_UPDATE	0x1013	/* cfgtree_update_handler()  */
#define PLATFORM_SW_PA_TO_MID		0x1014	/* pa_to_mid()		     */
#define PLATFORM_SW_GET_NUMA_DISTANCES	0x1015	/* get_numa_distances()	     */


/*
 * register_platform_switch() Flag Definitions
 */

/* There are currently no flags defined.  When the need arises to use this
 * field the intent is that it be implemented as a maskable bit field.
 * So, the first flag might look like:
 *
 * #define	PLATFORM_FL_MYFLAG1	0x00000001
 * #define	PLATFORM_FL_MYFLAG2	0x00000002
 * #define	PLATFORM_FL_MYFLAG3	0x00000004
 *
 */

#define		PLATFORM_FL_NOFLAG	0x00000000	/* Null flag         */


struct platform_callsw
{
        void  (*mach_error)();           /* machine check entry point        */
        void  (*machcheck)();            /* hardware trap                    */
        void  (*syscorr_intr)();         /* system correctable (hard error)  */
        void  (*proccorr_intr)();        /* proc correctable (soft error)    */
        int   (*memenable)();            /*                                  */
        int   (*config)();               /* system configuration             */
        int   (*badaddr)();              /* probe addresses                  */
        long  (*readtodr)();             /* read time of day                 */
        void  (*writetodr)();            /* write time of day                */
        int   (*ring_bell)();            /* ring bell                        */
        int   (*testpage)();             /* test a physical frame            */
        void  (*config_secondary)();     /* configure data structures
                                            needed to start secondary;
                                            runs on primary                  */
        void  (*init_secondary)();       /* initialize secondary; runs
                                            on secondary                     */
        void  (*dumpdev)();              /* get system specific device
                                            string for fw                    */
        u_int (*get_info)();             /* get system specific info         */
        void  (*init)();                 /* initialization                   */
        int (*pag_num)();              	 /* processor affinity group number  */
        int (*interrupt_distribute)(); 	 /* send ints to cpu being started   */
        int (*hal_power_ctl)();		 /* power control		     */
	void (*hal_cfgtree_update_handler)(); /* TREE-UPDATE ipintr handler  */
	int (*pa_to_mid)();		 /* convert phys mem addr to MID     */
	void  (*get_numa_distances)();   /* get NUMA distance info           */
};



/*
 * I/O Access Switch Registration Return Values
 *
 * These values may be returned by register_io_switch().  The values
 * are in the range 0x0000 to 0x0999.
 *
 */
#define IO_SW_SUCCESS             0x0000  /* Successful registration   */
#define IO_SW_FAILURE             0x0001  /* Generic failure return    */
#define IO_SW_UNK_DESC            0x0002  /* Descriptor passed unknown to
                                             register_platform_switch()*/
#define IO_SW_NO_SUP              0x0003  /* Descriptor passed is not
                                             supported in this rev of
                                             platform switch           */


/*
 * IO Switch Routine Descriptors
 *
 * These descriptors are used to indicate to the I/O switch registration
 * routine (register_io_switch()) which routine is being registered.
 *
 * Valid range for descriptor values is 0x1000 to 0x1999.
 *
 */

#define IO_SW_READ_IO_PORT              0x1000  /* read_io_port()           */
#define IO_SW_WRITE_IO_PORT             0x1001  /* write_io_port()          */
#define IO_SW_IO_BLOCKREAD              0x1002  /* io_blockread()           */
#define IO_SW_IO_BLOCKWRITE             0x1003  /* io_blockwrite()          */
#define IO_SW_IO_BLOCKEXCHANGE          0x1004  /* io_blockexchange()       */
#define IO_SW_IO_BLOCKCLEAR             0x1005  /* io_blockclear()          */
#define IO_SW_IOHANDLE_TO_PHYS		0x1006  /* iohandle_to_phys()       */

/*
 * register_io_switch() Flag Definitions
 */

/* There are currently no flags defined.  When the need arises to use this
 * field the intent is that it be implemented as a maskable bit field.
 * So, the first flag might look like:
 *
 * #define      IO_FL_MYFLAG1     0x00000001
 * #define      IO_FL_MYFLAG2     0x00000002
 * #define      IO_FL_MYFLAG3     0x00000004
 *
 */

#define         IO_FL_NOFLAG      0x00000000      /* Null flag         */
     

/*
 * DMA Support Switch Registration Return Values
 *
 * These values may be returned by register_dma_switch().  The values
 * are in the range 0x0000 to 0x0999.
 *
 */
#define DMA_SW_SUCCESS             0x0000  /* Successful registration   */
#define DMA_SW_FAILURE             0x0001  /* Generic failure return    */
#define DMA_SW_UNK_DESC            0x0002  /* Descriptor passed unknown to
                                             register_platform_switch()*/
#define DMA_SW_NO_SUP              0x0003  /* Descriptor passed is not
                                             supported in this rev of
                                             platform switch           */


/*
 * DMA Switch Routine Descriptors
 *
 * These descriptors are used to indicate to the DMA switch registration
 * routine (register_dma_switch()) which routine is being registered.
 *
 * Valid range for descriptor values is 0x1000 to 0x1999.
 *
 */

#define DMA_SW_DMA_MAP_ALLOC            0x1000  /* dma_map_alloc()          */
#define	DMA_SW_DMA_MAP_LOAD             0x1001  /* dma_map_load()           */
#define DMA_SW_DMA_MAP_UNLOAD           0x1002  /* dma_map_unload()         */
#define DMA_SW_DMA_MAP_DEALLOC          0x1003  /* dma_map_dealloc()        */
#define DMA_SW_DMA_MIN_BOUNDARY         0x1004  /* dma_min_boundary()       */

/*
 * register_dma_switch() Flag Definitions
 */

/* There are currently no flags defined.  When the need arises to use this
 * field the intent is that it be implemented as a maskable bit field.
 * So, the first flag might look like:
 *
 * #define      DMA_FL_MYFLAG1     0x00000001
 * #define      DMA_FL_MYFLAG2     0x00000002
 * #define      DMA_FL_MYFLAG3     0x00000004
 *
 */

#define         DMA_FL_NOFLAG      0x00000000      /* Null flag         */

                                                                  

extern u_int	register_platform_switch (u_int descriptor,
                                          int (*support_routine)(),
					  int cfg_point,
					  u_int flags);

extern u_int    register_io_switch (u_int descriptor,
                                    int (*support_routine)(),
                                    u_int flags);

extern u_int    register_dma_switch (u_int descriptor,
                                     int (*support_routine)(),
                                     u_int flags);

extern void	failed_registration (char *descriptor, u_int failure_mode);


struct	hal_revision	{
	u_long		maj_rev;
	u_long		min_rev;
	u_long		compat_rev;
	u_long		reserved;
};

struct  request_interface	{
	struct 		hal_revision 	*swoe_revision;
	char		*interface_name;
	int 		(*funcptr)();
	u_int		flags;
};

struct	hal_callsw      {
	void  (*mach_error)();
	int   (*memenable)();
	int   (*configure_platform)();
	long  (*readtodr)();
 	void  (*writetodr)();
	int   (*testpage)();
	void  (*config_secondary)();
	void  (*init_secondary)();
	void  (*dump_dev)();
	u_int (*get_info)();
	void  (*init_platform)();
        int   (*hal_getsysinfo)();
        int   (*hal_setsysinfo)();
        int   (*hal_setsysinfo_nvpair)();
	int   (*pag_num)();
	int   (*interrupt_distribute)();
	int   (*hal_power_ctl)();
	void  (*hal_cfgtree_update_handler)();
	int   (*pa_to_mid)();
	void  (*get_numa_distances)();
};

#define HAL_FL_NOFLAG           0x00000000

#define HAL_SW_SUCCESS		0x0000
#define HAL_SW_UNK_INT		0x0001
#define HAL_SW_BAD_REV		0x0002		/* Platform code doesn't like
						 * SWOE code's rev. 
                                                 */
#define PLATFORM_SW_BAD_REV	0x0004          /* SWOE code doesn't like
                                                 * Platform code's rev.
                                                 */

/*
 * If HAL_SW_BAD_REV is returned, it will be OR'ed with the failure codes
 * for which field of hal_revision was insufficient.  These failure codes
 * follow:
 */

#define HAL_SW_BAD_MAJ_REV	0x00010000
#define HAL_SW_BAD_MIN_REV	0x00020000
#define HAL_SW_BAD_COMPAT_REV	0x00040000
#define HAL_SW_REV_NO_TEST      0x00080000

/*
 * Structure used to describe HAL per-rad/NUMA-centric information.
 * RAD == QBB on Wildfire, but on Marvel a RAD is one CPU/memory/IO
 * or two CPU/memory/IO if memory is striped accross CPUs.
 * Must be cache block size/aligned.
 */

struct hal_rad {
	int	controlling_cpu;	/* controls config, intr assignment   */
	int	rad_type;		/* RAD type see kern/rad.h	      */
	int	rad_id;			/* number of this RAD                 */
	int	ncpus_in_rad;		/* number of CPU's in this RAD        */
	int	rad_is_striped;		/* some/all memory in rad is striped  */
	int	stripe_set_size;	/* # CPUs stripe across for this RAD  */
	int	rad_cpu_base;		/* # of 1st CPU that could be in RAD  */
	u_int	rad_cpu_bitmask;	/* bit/cpu relative to rad_cpu_base   */
};

/*
 * Registration routine in ./kernel/arch/alpha/halswitch.c 
 *
 * This is the interface to initiate halswitch registration
 *
 */

extern	void	register_hal_callsw(int point, int order,
                                    struct hal_revision *platform_revision,
                                    u_long unused);

extern u_int	get_hal_interface (struct request_interface *swoe_request);

#ifdef __cplusplus
}
#endif

#endif /* defined(_KERNEL) */
#endif /* _ARCH_ALPHA_HAL_PLATFORM_H_ */
