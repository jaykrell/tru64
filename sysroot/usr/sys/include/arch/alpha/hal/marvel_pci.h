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
 * @(#)$RCSfile: marvel_pci.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 2002/07/11 17:42:02 $
 */



#ifndef __ARCH_ALPHA_HAL_MARVEL_PCI_H__
#define __ARCH_ALPHA_HAL_MARVEL_PCI_H__

#include <hal/shared_intr.h>

#if defined (__cplusplus)
extern "C" {
#endif /* __cplusplus */


/*
 * CSRs on 64-byte boundaries 
 * Read/Write granularity is 32 or 64 bits only.
 */
#define MV_NUM_PCI_PER_IOA	4	/* marvel_pci.h: MV_MAX_PCI_PER_IOA! */

struct mv_pci_csrs {
	u_long	ctrl;		/* offset 0x0 */
	u_long	pad0[7];
	u_long	cache_ctrl;
	u_long	pad1[7];
	u_long	timer;
	u_long	pad2[7];
	u_long	io_adr_ext;
	u_long	pad3[7];
	u_long	mem_adr_ext;
	u_long	pad4[7];
	u_long	xcal_ctrl;
	u_long	pad5[7];
	u_long	pad6[80];	/* offset 0x180 */
	u_long	agp_cap_id;	/* offset 0x400 */
	u_long	pad7[7];
	u_long	agp_stat;
	u_long	pad8[7];
	u_long	agp_cmd;
	u_long	pad9[7];
	u_long	rsvd1;
	u_long	pad10[7];
	u_long	monctl;		/* offset 0x500 */
	u_long	pad11[7];
	u_long	ctra;
	u_long	pad12[7];
	u_long	ctrb;
	u_long	pad13[7];
	u_long	ctr56;
	u_long	pad14[7];
	u_long	scratch;
	u_long	pad15[7];
	u_long	xtra_a;
	u_long	pad16[7];
	u_long	xtra_ts;
	u_long	pad17[7];
	u_long	xtra_z;
	u_long	pad18[7];
	u_long	pad19[288];	/* offset 0x700 */
	struct  win_regs {
		struct	{
			u_long	wbase;
			u_long	pad20[7];
		} wb[MV_NUM_PCI_PER_IOA];
		struct {
			u_long	wmask;
			u_long	pad21[7];
		} wm[MV_NUM_PCI_PER_IOA];
		struct {
			u_long	tbase;
			u_long	pad22[7];
		} tb[MV_NUM_PCI_PER_IOA];
	} win_regs;
	u_long	sg_tbia;	/* offset 0x1300 */
	u_long	pad24[7];
	u_long	msi_wbase;
	u_long	pad25[7];
	u_long	rsvd2;
	u_long	pad26[7];
	u_long	rsvd3;
	u_long	pad27[7];
	u_long	pad28[384];	/* offset 0x1400 */
	u_long	err_sum;	/* offset 0x2000 */
	u_long	pad30;
	u_long	first_err;
	u_long	pad31[7];
	u_long	msk_hei;
	u_long	pad32[7];
	u_long	tlb_err;
	u_long	pad33[7];
	u_long	spl_complt;
	u_long	pad34[7];
	u_long	trans_sum;
	u_long	pad35[7];
	u_long	frc_pci_err;
	u_long	pad36[7];
	u_long	mult_err;
	u_long	pad37[7];
	u_long	pad38[32];
	u_long	eoi_dat;	/* offset 0x2400 */
	u_long	pad39[7];
	u_long	pad40[24];
	u_long	iack_special;	/* offset 0x2600 */
	u_long	pad41[7];
	u_long	pad42[824];	/* offset 0x2640 */
	u_long	hp_misc;	/* offset 0x4000 */
	u_long	pad50[7];
	u_long	hp_led;
	u_long	pad51[7];
	u_long	hp_intr_in;
	u_long	pad52[7];
	u_long	hp_evnt_msk;
	u_long	pad53[7];
	u_long	hp_dev_cap;
	u_long	pad54[7];
	u_long	rsvd4;
	u_long	pad55[7];
	u_long	hp_pwr;
	u_long	pad56[7];
	u_long	hp_ctrl;
	u_long	pad57[7];
	u_long	hp_int_evnt;
	u_long	pad58[7];
	u_long	pad59[184];	/* offset 0x4240 */
				/* offset 0x4800 */
};
	

/*
 * DMA mapping externs
 */
extern	int mvpci_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long mvpci_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long mvpci_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int mvpci_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int mvpci_dma_min_boundary(struct controller *cntrlrp);


/*
 * PCI Window BASE register defines
 */
#define WINDOW_ENABLE		0x1
#define WINDOW_DISABLE		0x0
#define WINDOW_SCATTER_GATHER	0x2
#define WINDOW_DIRECT_MAPPED 	0x0
#define WINDOW_DAC_ENABLE	0x4L
#define WINDOW_BASE_MASK	0xfff00000L
#define WINDOW_BASE(Size_index)	 ((1UL << (Size_index - 1)) << 20)

/*
 * PCI WINDOW mask register defines
 */

/* index'es into the base and mask arrays */
#define WIN_NONE        0
#define WIN_1MEG        1
#define WIN_2MEG        2
#define WIN_4MEG        3
#define WIN_8MEG        4
#define WIN_16MEG       5
#define WIN_32MEG       6
#define WIN_64MEG       7
#define WIN_128MEG      8
#define WIN_256MEG      9
#define WIN_512MEG      10
#define WIN_1GIG        11
#define WIN_2GIG        12
#define WIN_4GIG        13
#define WIN_8GIG        14

#define WINDOW_SIZE(Wndw_index)  ((1 << (Wndw_index - 1)) << 20)
#define WINDOW_MASK(Wndw_index) (((1 << (Wndw_index - 1)) - 1) << 20)
#define SG_TABLE_SIZE(Wndw_index) (1 << (Wndw_index + 9))
/* 
 * these defines don't work for window size of WIN_NONE 
 */

#define M_1_MEG                 WINDOW_SIZE(WIN_1MEG)
#define M_2_MEG                 WINDOW_SIZE(WIN_2MEG)
#define M_4_MEG                 WINDOW_SIZE(WIN_4MEG)
#define M_8_MEG                 WINDOW_SIZE(WIN_8MEG)
#define M_16_MEG                WINDOW_SIZE(WIN_16MEG)
#define M_32_MEG                WINDOW_SIZE(WIN_32MEG)
#define M_64_MEG                WINDOW_SIZE(WIN_64MEG)
#define M_128_MEG               WINDOW_SIZE(WIN_128MEG)
#define M_256_MEG               WINDOW_SIZE(WIN_256MEG)
#define M_512_MEG               WINDOW_SIZE(WIN_512MEG)
#define M_1_GIG                 WINDOW_SIZE(WIN_1GIG)
#define M_2_GIG                 WINDOW_SIZE(WIN_2GIG)
#define M_4_GIG                 WINDOW_SIZE(WIN_4GIG)
#define M_8_GIG                 WINDOW_SIZE(WIN_8GIG)



/*
 * MV-PCI Address Space defines & declarations 
 */

/*
 * IOHANDLE-related definitions
 */
#define MVPCI_IOBUS_MASK 	0x0000080000000000L
#define MVPCI_MEM_SPACE_MASK	0x0000000100000000L
#define MVPCI_MEM_SPACE	0x0

/*
 * The following are offsets from the PCI adapter (IO7 port) base address.
 * The adapter base address is a function of the PCI hose (IO7 port) number.
 */
#define MVPCI_MEM_BASE		0x00000000	/* PCI memory space */
#define MVPCI_IO_BASE		0xFF000000	/* PCI I/O space */
#define MVPCI_CONFIG_BASE	0xFE000000	/* PCI Config Space */

#define MV_SR_OFFSET            0x100000        /* Offset to Shared RAM */
  
/* 
 * PCI-centric defines for MV-PCI Adapter
 */
#define MVPCI_PCI_INTR_INFO_SIZE	256


/* MVPCI INTERRUPT TO SCB INDEX-ing MACROS */
#define MVPCI_SCB_PCI_BASE		0x800
#define MVPCI_SCB_BUS_INDEX		0x200
#define MVPCI_SCB_PCI_SLOT_INDEX	0x40
#define MVPCI_SCB_PER_INTR_INDEX	0x10
#define MVPCI_SCB_MSI_BASE		0x1000


#define SET_INTMASK	1
#define CLEAR_INTMASK	2

/*
 * Marvel PCI interrupt related definitions.
 */
#define MVPCI_NO_IRQ			-1	/* pci_common_intr_handler.c, */
						/* irq = PCI_NO_IRQ; */

#define MVPCI_LSI_CPU_TARGET_SHIFT	14
#define MVPCI_MSI_CPU_TARGET_SHIFT	14
#define MVPCI_MSI_INTR_ENABLE_SHIFT	24
#define MVPCI_MSI_CTL_IN_MSG_SHIFT	9
#define MVPCI_PRIMARY_INTR_REG 		0
#define MVPCI_DIST_INTR_REG		1
#define MVPCI_MIN_PCI_IRQ_NUM		0
#define MVPCI_NUM_PCI_LSI_IRQ		128
#define MVPCI_NUM_PCI_MSI_IRQ		512

/*
 * Marvel limitation on the number of slots on PCI primary bus
 */
#define MVPCI_MAX_PCI_SLOTS		16



#ifdef KERNEL

/*
 * DMA Support
 */

/*
 * DMA Window defines for MV-PCI Bridge
 */

#define MVPCI_WIN_MAX          5       /* 5 DMA mapping windows per PCI */
#define MVPCI_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define MVPCI_DIRECT_WIN       1       /* Index to Direct-map DMA Window  */
#define MVPCI_32BIT_SG_WIN     2       /* Index to 32-bit, SAC S/G DMA Window */
#define MVPCI_64BIT_SG_WIN     3       /* Index to 64-bit, DAC S/G DMA Window */
#define MVPCI_DIRECT64         4       /* 64-bit direct DMA is just a 
                                         * register, not a window as such,
                                         * but it needs a dma_map_info_t
                                         * structure allocated...
                                         */
/* PCI base address values of direct-map DMA windows	*/
#define MVPCI_32B_DIRECT_MAP_BASE	(u_long)(1UL << 31)	/* 2GB */
#define MVPCI_64B_DIRECT_MAP_BASE	(u_long)(1UL << 49)  	/* see SPM */

#define MVPCI_64B_SG_MAP_BASE		(u_long)(0x0001ffffUL << 32) /*see SPM*/


/* Can't just AND the lower bits, like other platforms
 * because 1000(10) = 3e8(16), 2000(10) = 7d0(16), which
 * ends up OR-ing bits in the 00->3F(16) range that Marvel
 * PCI host bridge numbers can be.
 * So, must divide-mod out the 1000's from the PCI bus num
 */
#define MVPCI_BUS_NUM(Busp)	(((Busp)->bus_num) % 1000)
#define _IS_64BIT_CAPABLE_(f)	((f) & DMA_64BIT)

/* Determination of SG DMA Window base address on PCI
 * Now includes 64-bit DMA selection...
 */

/*
 * Use private[] fields attached to PCI bus struct to get
 * high-freq., critical path params. Usage:
 *
 *  _sg_32b_ctl_	Address of struct hw_sg_map_control, returned
 *			by hw_sg_map_init() for 32-bit scatter/gather.
 *  _sg_64b_ctl_	Address of struct hw_sg_map_control, returned
 *			by hw_sg_map_init() for 64-bit scatter/gather.
 *  _addrlim_sg_ctl_	Address of struct hw_sg_map_control, returned
 *			by hw_sg_map_init() for address limited device'
 *			scatter/gather (non of these on Marvel).
 *  _shared_intr_	Not used on Marvel.
 *  _pci_hose_num_	Poorly choosen name (cloned from Wildfire). Used
 *			to save the PCI bus number in the bus struct.
 *  _intr_		Saves the shared interrupt info structure in the
 *			bus struct. Used by mvpci_get_shintr_struct() in
 *			marvel_pci.c for example.
 */
#define _sg_32b_ctl_     private[1]
#define _sg_64b_ctl_     private[2]
#define _addrlim_sg_ctl_ private[3]
#define _shared_intr_    private[4]
#define _pci_hose_num_   private[5]
#define _intr_           private[7]

#define SG_MAP_SELECT(Flags,Busp) \
    ( !(_IS_64BIT_CAPABLE_(Flags)) && !(ADDRESS_LIMITED(Flags))) ? \
                Busp->_sg_32b_ctl_ : \
                    (_IS_64BIT_CAPABLE_(Flags) ? \
                            Busp->_sg_64b_ctl_ : \
                            Busp->_addrlim_sg_ctl_ )

/* Determination of direct-map DMA Window base on PCI	*/
#define DIRECT_MAP_SELECT(Flags) \
	(((Flags) & DMA_64BIT) ? \
		MVPCI_64B_DIRECT_MAP_BASE : MVPCI_32B_DIRECT_MAP_BASE)
struct win_sel {
	u_int	type;		/* Direct, SG; En/disable; DAC	*/
	u_long	size;		/* based on WIN_xxxx index 	*/
	u_long	pci_base;	/* PCI base addr. of window 	*/
	u_long	tbase;		/* TBASE for s/g or direct 	*/
};

/*
 *      Definition of bus info structures.
 */
/*----------------------------------------------------------------*/
/* The agreed upon format for bus info structures is              */
/*                                                                */
/*      +----------------------------------------+                */
/*      |  Pointer to common info block          |                */
/*      |  (this is a struct common_bus_info *)  |                */
/*      +----------------------------------------|                */
/*      |  Bus specific data block               |                */
/*      +----------------------------------------+                */
/*                                                                */
/*----------------------------------------------------------------*/
/*
 * note: the common_bus_info looks like:
 * struct  common_bus_info
 *      {
 *       io_handle_t    io_base;
 *       io_handle_t    mem_base;
 *      };
 */
struct mvpci_bus_info {
						/* 1st 64-byte cache block */
        struct common_bus_info *common_bus_info;	/* not used */
        volatile struct mv_pci_csrs *mv_pci_csrs;
	struct hal_rad  *hal_radp;
	io_handle_t	io_base;
	io_handle_t	mem_base;
	io_handle_t	config_base;
	int		ioa_pid;
	u_int		present;
	u_int		hard_pci_bus_num;
	u_int		num_pci_cfg_hdrs;
						/* 2nd 64-byte cache block */
	u_long		sg_32b_ctl;
	shared_intr_info_t	*intr;
	u_long		sg_64b_ctl;
	u_long		addrlim_sg_ctl;
	dma_map_info_t	dma_maps;
	struct bus	*busp;			/* pointer for this PCI bus */
	u_long		rsvd1;
	u_long		rsvd2;
};

extern struct mvpci_bus_info	* REPLICATED mvpci_bus_info[];


/*
 * MVPCI DMA Window defines
 */

/*
 * Each Marvel IO7 has 4 ports, each with 5 DMA windows.
 * The windows are used as defined below. Window 0 is a gentleman's
 * agreement between the OS and console firmware (allows switching
 * between OS and console mode).
 * MV_TODO: under review. why only use 8mb of a 2gb window?
 *
 * See also, Marvel Software Programmer's Manual Chapters 3 and 4.
 *
 * SAC - Single Address Cycle
 * DAC - Dual Address Cycle
 *
 *  +--------+--------+--------+--------+-------------------------------+
 *  |   PCI  | Window | Offset |  Size  |  Usage			|
 *  | Window |  Type  |        |        |				|
 *  +--------+--------+--------+--------+-------------------------------+
 *  |    0   |  S/G   |   8 MB |   8 MB | ADDR-LIMITED devices		|
 *  |        |        |        |        | MV_TODO: why wasted 2gb win?  |
 *  +--------+--------+--------+--------+-------------------------------+
 *  |    1   | Direct |   2 GB |   1 GB | Map 0 - 1GB main memory	|
 *  +--------+--------+--------+--------+-------------------------------+
 *  |    2   |  S/G   |   3 GB |  64MB  | General Purpose		|
 *  |        |        |        | - 1GB  | 32-bit SAC Scatter/Gather	|
 *  +--------+--------+--------+--------+-------------------------------+
 *  |    3   |  S/G   |   (#)  |   1GB  | 64-bit, DAC Scatter/Gather	|
 *  +--------+--------+--------+--------+-------------------------------+
 *  |    4   | Direct |   0    |  2^48  | Direct memory access DAC	|
 *  |        |        |        |  bytes | Monstor Window (Kseg for I/O)	|
 *  +--------+--------+--------+--------+-------------------------------+
 *
 *  # Base = 0x0001ffff00000000 (see Marvel SPM)
 */

/* win_sel indices */
#define MVPCI_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define MVPCI_DIRECT_WIN       1       /* Index to Direct-map DMA Window  */
#define MVPCI_32BIT_SG_WIN     2       /* Index to 32-bit, SAC S/G DMA Window */
#define MVPCI_64BIT_SG_WIN     3       /* Index to 64-bit, DAC S/G DMA Window */

/* 
 * Various bus related macros.
 */
#define IS_AN_ISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_ISA)
#define IS_A_CONTIG_DEVICE(f)	(f & DMA_CONTIG)
#define IS_A_SG_DEVICE(a,f)	(IS_A_CONTIG_DEVICE(f) || mvpci_always_sg)
#define ADDRESS_LIMITED(Flags)	((Flags) & DMA_ADDR_LIMIT)
#define CONTIG_DESIRED(Flags)	((Flags) & DMA_CONTIG)
#define SG_ALLOCED(f)		((f) & DMA_HW_SG)
#define HAS_SG_ALLOCED(f)	((f) & DMA_HW_SG)

#define SG_NOTNEEDED	0
#define SG_REQUIRED	1
#define SG_DESIRED	2


/* MV_NOTE: Required for IO7 split completion error bug and invalid
 *   scatter/gather pte machine check workarounds.
 */
#define MVPCI_DMA_PREFETCH	4096	/* maximum pre-fetch, DO NOT CHANGE */

/* Various translation macros 	*/
#define CONFIG_BASE_TO_BRIDGE_CSR_BASE	0x02000000L

/* Determination of SG DMA Window base address on PCI	*/

/* p2p region includes sparse & dense memory region	*/
#define LOCAL_PEER_TO_PEER_DMA_BASE	(0x0000000000000000L)	/* 0GB->2GB */

#define IS_IN_PCI_SPACE(Pa)		((Pa) & MVPCI_IOBUS_MASK)
#define IS_IN_PCI_MEM(Pa)		(((Pa) & MVPCI_MEM_SPACE_MASK) \
						== MVPCI_MEM_SPACE)
/* 
 * Note:
 *	The and-or check below is designed to:
 *	-- fail if the physical address is not in PCI space 
 *	-- then check for the next most freq. case: dense-mapped mem. region
 *	-- then check for sparse-space mapped mem. region.
 *
 *	The checking is done in this order to minimize the code sequence
 *	executed for the most frequent dma-mapping check (non-peer-to-peer)
 *	and to allow the p-2-p check to be longer if it is p-2-p, since
 *	the performance of p-2-p can afford the slightly greater overhead.
 */
#define IS_PEER_TO_PEER(Pa) (IS_IN_PCI_SPACE(Pa) && IS_IN_PCI_MEM(Pa)) 
/*
#define IS_LOCAL_PEER_TO_PEER(Addr, Busp) \
*/

#endif 

/* size of the I/O resource map for TSUNAMI */
#define MVPCI_RESOURCE_MAP_SIZE 200


#ifdef KERNEL
/* for pa-addr. gen/trans. macros below */

/*
 * Function prototypes for marvel_pci.c
 */
/*
 * Init, IO-adapt-config
 */
/*
 * IO-Access routine externs
 */
extern	long mvpci_read_io_port(io_handle_t iohandle, int width, int type);
extern	void mvpci_write_io_port(io_handle_t iohandle, int width, int type, 
								long data);
extern	int mvpci_io_copyin(io_handle_t src, vm_offset_t dest, u_long count);
extern	int mvpci_io_copyout(vm_offset_t src, io_handle_t dest, u_long count);
extern	int mvpci_io_zero(io_handle_t dest, u_long count);
extern	int mvpci_io_copyio(io_handle_t src, io_handle_t dest, u_long count);
extern	io_handle_t mvpci_busphys_to_iohandle(u_long bus_addr, 
					int flags, struct controller *ctlrp);
extern	u_long mvpci_iohandle_to_phys(io_handle_t iohandle, long flags);

/*
 * DMA window sizing alg.
 */
extern	void mvpci_choose_dma_windows();

/*
 * DMA mapping externs
 */
extern	int mvpci_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long mvpci_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long mvpci_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int mvpci_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int mvpci_dma_min_boundary(struct controller *cntrlrp);
extern  void    mvpci_sg_tbia(struct sglist *);
/*
 * interrupt related functions
 */
extern int mvpci_modify_intmask(struct bus *busp,
				 int bit_to_change,
				 int operation);
extern int mvpci_modify_msi_intmask(struct bus *busp,
				 int msi_data,
				 int operation);

/*
 * Defines for development debug
 */
/* MVPCI_DMA_Debug defines */
#define MVPCI_DMA_Debug_Info		0x1
#define MVPCI_DMA_Debug_SG		0x2
#define MVPCI_DMA_Debug_No_DAC		0x20
/*
 * As per agreement with the Marvel team, peer to peer DMA not supported.
 */
#if 0
#define MVPCI_DMA_Debug_P2P		0x80000000 /* p2p off for 99.999% of Wildfire's */
#endif

/*
 * Marvel IO7 data mover port selection externs.
 */
extern u_int	mvpci_data_mover_port[];

/* MVPCI_Developer_Debug defines */
#define MVPCI_Developer_Debug_NONE_YET	0x0

/*
 * marvel_pci.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since marvel_cpu.h, marvel_soc.h, & marvel_pci.h may be included in
 *	 one .c file, their debug definitions must not collide.
 */

extern	u_int	mvpci_developer_debug;

/* Data Mover polling variable */
extern  u_int   mvpci_data_mover_polling;

/* To remove/add all debug printfs */
#define __MVPCIDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * mvpci_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	MVPCID_INOUT	0x00000001	/* routine entry and exit 	*/
#define MVPCID_NUMA	0x00000020	/* NUMA-related info		*/
#define MVPCID_DMAINFO	0x00000100	/* system-level dma settings	*/
#define MVPCID_P2PDMA	0x00000200	/* peer-to-peer dma info	*/
#define MVPCID_PCIINFO	0x00001000	/* PCI config. info		*/
#define MVPCID_CONSOLE	0x00020000	/* console device info		*/
#define MVPCID_INTRINFO	0x00100000	/* Intr. config. info		*/
#define MVPCID_HWINFO	0x01000000	/* HW bugs, workaround info	*/

/* New, testing hw-support debug printfs				*/
#define MVPCID_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */

/*
 * string defines used in MVPCIPRINTF to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision.
 */
extern char * _MVPCIinout;
extern char * _MVPCInuma;
extern char * _MVPCIdmainfo;
extern char * _MVPCIp2pdma;
extern char * _MVPCIpciinfo;
extern char * _MVPCIisainfo;
extern char * _MVPCIconsole;
extern char * _MVPCIintrinfo;
extern char * _MVPCIhwbugs;
extern char * _MVPCInot_yet;


/*
 * printf expansion that MVPCIPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _MVPCIxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __MVPCIDEBUG
#   define _MVPCID_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_INOUT )  {	\
	    /* VARARGS */			\
            printf (_MVPCIinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_NUMA)  {	\
	    /* VARARGS */			\
            printf (_MVPCInuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_DMAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_DMAINFO)  {	\
	    /* VARARGS */			\
            printf (_MVPCIdmainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_P2PDMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_P2PDMA)  {	\
	    /* VARARGS */			\
            printf (_MVPCIp2pdma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_PCIINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_PCIINFO)  {	\
	    /* VARARGS */			\
            printf (_MVPCIpciinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_CONSOLE(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_CONSOLE)  {	\
	    /* VARARGS */			\
            printf (_MVPCIconsole); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_INTRINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_INTRINFO)  {	\
	    /* VARARGS */			\
            printf (_MVPCIintrinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_HWINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_HWINFO)  {	\
	    /* VARARGS */			\
            printf (_MVPCIhwbugs); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVPCID_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvpci_developer_debug & MVPCID_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_MVPCInotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * mvpci_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * MVPCID_INOUT | MVPCID_DMAINFO
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define MVPCIPRINTF(F, X)	_##F(X)

#else  /* !__MVPCIDEBUG */
#   define MVPCIPRINTF(F, X)
#endif /* __MVPCIDEBUG */

#endif	/* KERNEL */

#if defined (__cplusplus)
}
#endif /* __cplusplus */

#endif	/* __ARCH_ALPHA_HAL_MARVEL_PCI_H__ */

