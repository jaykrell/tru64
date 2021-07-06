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
#pragma ident "@(#)$RCSfile: wfpci.h,v $ $Revision: 1.1.19.3 $ (DEC) $Date: 2000/11/10 03:40:31 $"



#ifndef __ARCH_ALPHA_HAL_WFPCI_H__
#define __ARCH_ALPHA_HAL_WFPCI_H__

#include <hal/shared_intr.h>

#if defined (__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Entity 12-15, offset F.FFB0.0000
 * PCA0= Entity 12
 *	...
 * PCA3 = Entity 15
 *
 * CSRs on 64-byte boundaries 
 */
/* see wfpci.h for PCA-related structs, defines */

struct wf_pca_csrs {
	u_long	what_am_i;
	u_long	pad0[7];
	u_long	err_sum;
	u_long	pad1[7];
	u_long	diag_force_err;
	u_long	pad2[7];
	u_long	diag_send_err_int;
	u_long	pad3[7];
	u_long	hose_credits;
	u_long	pad4[7];
	u_long	scratch;
	u_long	pad5[7];
	u_long	micro_addr;
	u_long	pad6[7];
	u_long	micro_data;
	u_long	pad7[7];
	u_long	pend_int;
	u_long	pad8[7];
	u_long	sent_int;	/* offset 240 */
	u_long	pad9[15];
	u_long	stdio_edge_level; /* offset 2C0 */
	u_long	pad10[419];
	u_long	int_target_0;	/* offset 1000 */
	u_long	pad11[7];
	u_long	int_enable_0;
	u_long	pad12[7];
	u_long	int_target_1;
	u_long	pad13[7];
	u_long	int_enable_1;
	u_long	pad14[7];
	u_long	int_target_2;
	u_long	pad15[7];
	u_long	int_enable_2;
	u_long	pad16[7];
	u_long	int_target_3;
	u_long	pad17[7];
	u_long	int_enable_3;	
#ifdef not_included
	u_long	pad18[7];	/* offset 0.1200 */
	u_long	alt_sent_int_{0-31}; /* offset 2000->2800 */
				/* skip of 0.EE00 bytes */
#endif
};

struct wf_pca_link_csrs {
	u_long	ne_what_am_i;
	u_long	pad20[7];
	u_long	ne_ctrl;
	u_long	pad21[7];
	u_long	ne_err_sum;
	u_long	pad22[7];
	u_long	ne_diag_force_err;
	u_long	pad23[7];
	u_long	ne_diag_send_err_int;	/* offset 1.0100 */
#ifdef not_included
	u_long	ne_delay_lock_{0-19};	/* offset 1.0300->1.07C00 */
#else
	u_long	pad24[4063];		/* offset 1.8000 */
#endif	/* not included */
	u_long	fe_what_am_i;
	u_long	pad30[7];
	u_long	fe_ctrl;
	u_long	pad31[7];
	u_long	fe_err_sum;
	u_long	pad32[7];
	u_long	fe_diag_force_err;
	u_long	pad33[7];
	u_long	fe_diag_send_err_int;
};

/* Continuation of Entity 12-15 - PCI bridge regs.
 * PCA0,PCI0 = Entity 12, offset F.FFB2.0000
 * PCA0,PCI1 =            offset F.FFB3.0000
 * PCA1,PCI0 = Entity 13, offset F.FFB4.0000
 * PCA1,PCI1 =            offset F.FFB5.0000
 * PCA2,PCI0 = Entity 14, offset F.FFB8.0000
 * PCA2,PCI1 =            offset F.FFB9.0000
 * PCA3,PCI0 = Entity 15, offset F.FFBC.0000
 * PCA3,PCI1 =            offset F.FFBD.0000
 *
 * CSRs on 64-byte boundaries 
 */
struct wf_pci_csrs {
	u_long	io_addr_ext;
	u_long	pad0[7];
	u_long	ctrl;
	u_long	pad1[7];
	u_long	err_sum;
	u_long	pad2[7];
	u_long	err_addr;
	u_long	pad3[7];
	u_long	stall_cnt;
	u_long	pad4[7];
	u_long	iack_special;	/* offset 0140 */
	u_long	pad5[23];
	u_long	pend_int;	/* offset 0200 */
	u_long	pad6[7];
	u_long	sent_int;	/* offset 0240 */
	u_long	pad7[439];
	struct	win_regs {	/* offset 1000 -> 12C0 */
			u_long	wbase;
			u_long	pad8[7];
			u_long	wmask;
			u_long	pad9[7];
			u_long	tbase;
			u_long	pad10[7];
	}	win_regs[4];
	u_long	flush_tlb;
};
	

/*
 * PCA- & PCI-related defines
 */
#define WF_MAX_PCA_PER_IOP	 4
#define WF_MAX_PCI_PER_PCA	 2	
#define WF_MAX_PCI_PER_IOP	 8
#define WF_MAX_PCI_PER_QBB	WF_MAX_PCI_PER_IOP
#define WF_MAX_PCIS		(WF_MAX_PCI_PER_IOP * WF_MAX_IOPS)

#define WF_PCI_SHIFT		33
#define WF_PCI_TO_PCA_NUM_SHIFT 1
#define WF_PCA_TO_QBB_NUM_SHIFT 2
#define WF_PCA_ENTITY		12
#define WF_PCA_WHAT_AM_I	0x00000
/* Bit definitions for WF_PCA_WHAT_AM_I */
#define 	WF_PCA_WHAMI_ASIC_REV_MASK 0x0000000FUL
#define		WF_PCA_WHAMI_BP_REV_SHIFT 4
#define		WF_PCA_WHAMI_BP_REV_MASK 0x00FUL
#define		WF_PCA_WHAMI_BP_NUM_SHIFT 12
#define		WF_PCA_WHAMI_BP_NUM_MASK 0x00FUL
#define		WF_PCA_WHAMI_HOSE_NUM_SHIFT 24
#define		WF_PCA_WHAMI_HOSE_NUM_MASK 0x007UL
#define WF_PCA_ERR_SUM		0x00040
#define WF_PCA_DIAG_FORCE_ERR	0x00080
#define WF_PCA_DIAG_SEND_ERR_INT	0x000C0
#define WF_PCA_HOSE_CREDITS	0x00100
#define WF_PCA_SCRATCH		0x00140
#define WF_PCA_MICRO_ADDR	0x00180
#define WF_PCA_MICRO_DATA	0x001C0
#define WF_PCA_PEND_INT		0x00200
#define WF_PCA_SENT_INT		0x00240
#define WF_PCA_STDIO_EDGE_LEVEL	0x002C0
#define WF_PCA_INT_TARGET	0x01000
#define 	WF_PCA_INT_TARGET_CPU_MASK	0x001F  /* qbb<2:0>,cpu<1:0> */
#define WF_PCA_INT_TARGET_DELTA	0x00080
#define WF_PCA_DEV_INT_TARGET_Valid 0x100
#define WF_PCA_INT_ENABLE	0x01040
#define WF_PCA_INT_ENABLE_DELTA	0x00080
#define WF_PCA_INT_TARGET_0	0x01000
#define WF_PCA_INT_ENABLE_0	0x01040
#define WF_PCA_INT_TARGET_1	0x01080
#define WF_PCA_INT_ENABLE_1	0x010C0
#define WF_PCA_INT_TARGET_2	0x01100
#define WF_PCA_INT_ENABLE_2	0x01140
#define WF_PCA_INT_TARGET_3	0x01180
#define WF_PCA_INT_ENABLE_3	0x011C0
#define WF_PCA_ALT_SENT_INT	0x02000
#define WF_PCA_ALT_SENT_INT_DELTA	0x00040
#define WF_PCA_ALT_SENT_INT_0	0x02000
#define WF_PCA_ALT_SENT_INT_1	0x02040
#define WF_PCA_ALT_SENT_INT_2	0x02080
#define WF_PCA_ALT_SENT_INT_3	0x020C0
#define WF_PCA_ALT_SENT_INT_4	0x02100
#define WF_PCA_ALT_SENT_INT_5	0x02140
#define WF_PCA_ALT_SENT_INT_6	0x02180
#define WF_PCA_ALT_SENT_INT_7	0x021C0
#define WF_PCA_ALT_SENT_INT_8	0x02200
#define WF_PCA_ALT_SENT_INT_9	0x02240
#define WF_PCA_ALT_SENT_INT_10	0x02280
#define WF_PCA_ALT_SENT_INT_11	0x022C0
#define WF_PCA_ALT_SENT_INT_12	0x02300
#define WF_PCA_ALT_SENT_INT_13	0x02340
#define WF_PCA_ALT_SENT_INT_14	0x02380
#define WF_PCA_ALT_SENT_INT_15	0x023C0
#define WF_PCA_ALT_SENT_INT_16	0x02400
#define WF_PCA_ALT_SENT_INT_17	0x02440
#define WF_PCA_ALT_SENT_INT_18	0x02480
#define WF_PCA_ALT_SENT_INT_19	0x024C0
#define WF_PCA_ALT_SENT_INT_20	0x02500
#define WF_PCA_ALT_SENT_INT_21	0x02540
#define WF_PCA_ALT_SENT_INT_22	0x02580
#define WF_PCA_ALT_SENT_INT_23	0x025C0
#define WF_PCA_ALT_SENT_INT_24	0x02600
#define WF_PCA_ALT_SENT_INT_25	0x02640
#define WF_PCA_ALT_SENT_INT_26	0x02680
#define WF_PCA_ALT_SENT_INT_27	0x026C0
#define WF_PCA_ALT_SENT_INT_28	0x02700
#define WF_PCA_ALT_SENT_INT_29	0x02740
#define WF_PCA_ALT_SENT_INT_30	0x02780
#define WF_PCA_ALT_SENT_INT_31	0x027C0
#define WF_PCA_INT_CNT_FIELD    0x30000
#define WF_NE_WHAT_AM_I		0x10000
/* Bit definitions for WF_NE_WHAT_AM_I */
#define 	WF_NE_WHAT_AM_I_REV_MASK 0x0000000FL
#define 	WF_NE_WHAT_AM_I_CABLE_OK 0x00000200L
#define WF_NE_WHAT_AM_I		0x10000
#define WF_NE_CTRL		0x10040
#define WF_NE_ERR_SUM		0x10080
#define WF_NE_DIAG_FORCE_ERR	0x100C0
#define WF_NE_DIAG_SEND_ERR_INT	0x10100
#define WF_NE_PORT_CREDITS	0x10140
#define WF_NE_HOSE_CREDITS	0x10180
#define WF_NE_MAX_PORT_CREDITS	0x101C0
#define WF_NE_MAX_HOSE_CREDITS	0x10200
#define WF_NE_SCRATCH		0x10240
#define WF_NE_DELAY_LOCK	0x10300
#define WF_NE_DELAY_LOCK_DELTA	0x00040
#define WF_NE_DELAY_LOCK_0	0x10300
#define WF_NE_DELAY_LOCK_1	0x10340
#define WF_NE_DELAY_LOCK_2	0x10380
#define WF_NE_DELAY_LOCK_3	0x103C0
#define WF_NE_DELAY_LOCK_4	0x10400
#define WF_NE_DELAY_LOCK_5	0x10440
#define WF_NE_DELAY_LOCK_6	0x10480
#define WF_NE_DELAY_LOCK_7	0x104C0
#define WF_NE_DELAY_LOCK_8	0x10500
#define WF_NE_DELAY_LOCK_9	0x10540
#define WF_NE_DELAY_LOCK_10	0x10580
#define WF_NE_DELAY_LOCK_11	0x105C0
#define WF_NE_DELAY_LOCK_12	0x10600
#define WF_NE_DELAY_LOCK_13	0x10640
#define WF_NE_DELAY_LOCK_14	0x10680
#define WF_NE_DELAY_LOCK_15	0x106C0
#define WF_NE_DELAY_LOCK_16	0x10700
#define WF_NE_DELAY_LOCK_17	0x10740
#define WF_NE_DELAY_LOCK_18	0x10780
#define WF_NE_DELAY_LOCK_19	0x107C0
#define WF_FE_WHAT_AM_I		0x18000
/* Bit definitions for WF_FE_WHAT_AM_I */
#define 	WF_FE_WHAT_AM_I_REV_MASK 0x0000000FL
#define 	WF_FE_WHAT_AM_I_CABLE_OK 0x00000200L
#define WF_FE_CTRL		0x18040
#define WF_FE_ERR_SUM		0x18080
#define WF_FE_DIAG_FORCE_ERR	0x180C0
#define WF_FE_DIAG_SEND_ERR_INT	0x18100
#define WF_FE_PORT_CREDITS	0x18140
#define WF_FE_HOSE_CREDITS	0x18180
#define WF_FE_MAX_PORT_CREDITS	0x181C0
#define WF_FE_MAX_HOSE_CREDITS	0x18200
#define WF_FE_SCRATCH		0x18240
#define WF_FE_DELAY_LOCK	0x18300
#define WF_FE_DELAY_LOCK_DELTA	0x00040
#define WF_FE_DELAY_LOCK_0	0x18300
#define WF_FE_DELAY_LOCK_1	0x18340
#define WF_FE_DELAY_LOCK_2	0x18380
#define WF_FE_DELAY_LOCK_3	0x183C0
#define WF_FE_DELAY_LOCK_4	0x18400
#define WF_FE_DELAY_LOCK_5	0x18440
#define WF_FE_DELAY_LOCK_6	0x18480
#define WF_FE_DELAY_LOCK_7	0x184C0
#define WF_FE_DELAY_LOCK_8	0x18500
#define WF_FE_DELAY_LOCK_9	0x18540
#define WF_FE_DELAY_LOCK_10	0x18580
#define WF_FE_DELAY_LOCK_11	0x185C0
#define WF_FE_DELAY_LOCK_12	0x18600
#define WF_FE_DELAY_LOCK_13	0x18640
#define WF_FE_DELAY_LOCK_14	0x18680
#define WF_FE_DELAY_LOCK_15	0x186C0
#define WF_FE_DELAY_LOCK_16	0x18700
#define WF_FE_DELAY_LOCK_17	0x18740
#define WF_FE_DELAY_LOCK_18	0x18780
#define WF_FE_DELAY_LOCK_19	0x187C0
#define WF_PCI_BUS_DELTA	0x10000
#define WF_PCI_IO_ADDR_EXT	0x20000
#define WF_PCI_CTRL		0x20040
/* Bit definitions for WF_PCI_CTRL	*/
#define 	WF_PCI_CTRL_ENA_TLB	0x2000 /* bit 13 */
#define WF_PCI_ERR_SUM		0x20080
/* Bit definitions for WF_PCI_ERR_SUM	*/
#define 	WF_PCI_ERR_SUM_MASK	0x0000FFFF /* errors = lower 16 bits */
#define 	WF_PCI_BUS_HUNG		0x80008000 /* for both PCI busses */
#define WF_PCI_ERR_ADDR		0x200C0
#define WF_PCI_STALL_CNT	0x20100
#define WF_PCI_IACK_SPECIAL	0x20140
#define WF_PCI_PEND_INT		0x20200
#define WF_PCI_SENT_INT		0x20240
#define WF_PCI_WBASE		0x21000
#define WF_PCI_WBASE_DELTA	0x000C0
#define WF_PCI_WBASE0		0x21000
#define WF_PCI_WMASK		0x21040
#define WF_PCI_WMASK_DELTA	0x000C0
#define WF_PCI_WMASK0		0x21040
#define WF_PCI_TBASE		0x21080
#define WF_PCI_TBASE_DELTA	0x000C0
#define WF_PCI_TBASE0		0x21080
#define WF_PCI_WBASE1		0x210C0
#define WF_PCI_WMASK1		0x21100
#define WF_PCI_TBASE1		0x21140
#define WF_PCI_WBASE2		0x21180
#define WF_PCI_WMASK2		0x211C0
#define WF_PCI_TBASE2		0x21200
#define WF_PCI_WBASE3		0x21240
#define WF_PCI_WMASK3		0x21280
#define WF_PCI_TBASE3		0x212C0
#define WF_PCI0_IO_ADDR_EXT	0x20000
#define WF_PCI0_CTRL		0x20040
#define WF_PCI0_ERR_SUM		0x20080
#define WF_PCI0_ERR_ADDR	0x200C0
#define WF_PCI0_STALL_CNT	0x20100
#define WF_PCI0_IACK_SPECIAL	0x20140
#define WF_PCI0_PEND_INT	0x20200
#define WF_PCI0_SENT_INT	0x20240
#define WF_PCI0_WBASE		0x21000
#define WF_PCI0_WBASE_DELTA	0x000C0
#define WF_PCI0_WBASE0		0x21000
#define WF_PCI0_WMASK		0x21040
#define WF_PCI0_WMASK_DELTA	0x000C0
#define WF_PCI0_WMASK0		0x21040
#define WF_PCI0_TBASE		0x21080
#define WF_PCI0_TBASE_DELTA	0x000C0
#define WF_PCI0_TBASE0		0x21080
#define WF_PCI0_WBASE1		0x210C0
#define WF_PCI0_WMASK1		0x21100
#define WF_PCI0_TBASE1		0x21140
#define WF_PCI0_WBASE2		0x21180
#define WF_PCI0_WMASK2		0x211C0
#define WF_PCI0_TBASE2		0x21200
#define WF_PCI0_WBASE3		0x21240
#define WF_PCI0_WMASK3		0x21280
#define WF_PCI0_TBASE3		0x212C0
#define WF_PCI1_IO_ADDR_EXT	0x30000
#define WF_PCI1_CTRL		0x30040
#define WF_PCI1_ERR_SUM		0x30080
#define WF_PCI1_ERR_ADDR	0x300C0
#define WF_PCI1_STALL_CNT	0x30100
#define WF_PCI1_IACK_SPECIAL	0x30140
#define WF_PCI1_PEND_INT	0x30200
#define WF_PCI1_SENT_INT	0x30240
#define WF_PCI1_WBASE0		0x31000
#define WF_PCI1_WMASK0		0x31040
#define WF_PCI1_TBASE0		0x31080
#define WF_PCI1_WBASE1		0x310C0
#define WF_PCI1_WMASK1		0x31100
#define WF_PCI1_TBASE1		0x31140
#define WF_PCI1_WBASE2		0x31180
#define WF_PCI1_WMASK2		0x311C0
#define WF_PCI1_TBASE2		0x31200
#define WF_PCI1_WBASE3		0x31240
#define WF_PCI1_WMASK3		0x31280
#define WF_PCI1_TBASE3		0x312C0


/* for pa-addr. gen/trans. macros below */
extern	u_long wf_io_space_pa_base;

/*
 * Macros to generate KSEG addresses from QBB numbers
 */
#define WF_PCI_BASE(_Qbb_num_, _Port_Bus_Num_) \
	(WF_QBB_IO_BASE(_Qbb_num_) | ((u_long)(_Port_Bus_Num_) << WF_PCI_SHIFT))

/* 
 * PCI-centric defines for WFCPU-PCI Adapter
 */

/*
 * Extraction of PCI bus number that StdIO that has active console port;
 * bits 22:18 of the hwrpb->sys_var element 
 * note: only 5 bits; need 6 -- console port must be on even-numbered PCI,
 *       so multiply by 2 (shift left by 1) to get actual value.
 */
#define WF_SV_CONS_PCI(Rpb_Sys_Var) ((((Rpb_Sys_Var) >> 18) & 0x01FL) << 1)

/* address generation/translation macros	*/
#define WF_PA_IO_BASE(Offset) (wf_io_space_pa_base | (u_long)(Offset))


/*
 * DMA mapping externs
 */
extern	int wfpci_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long wfpci_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long wfpci_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int wfpci_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int wfpci_dma_min_boundary(struct controller *cntrlrp);


/*
 * PCI Window BASE register defines
 */
#define WINDOW_ENABLE		0x1
#define WINDOW_DISABLE		0x0
#define WINDOW_SCATTER_GATHER	0x2
#define WINDOW_DIRECT_MAPPED 	0x0
#define WINDOW_DAC_ENABLE	0x8L
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
 * WF-PCI Address Space defines & declarations 
 */

/*
 * IOHANDLE-related definitions
 */
#define LOW_23			0x00000000007FFFFFL	/* Low 22 bits   */
#define LOW_24			0x0000000000FFFFFFL	/* Low 24 bits   */
#define LOW_25			0x0000000001FFFFFFL	/* Low 25 bits   */
#define LOW_26			0x0000000003FFFFFFL	/* Low 25 bits   */
#define LOW_27			0x0000000007FFFFFFL	/* Low 27 bits   */
#define LOW_28			0x000000000FFFFFFFL	/* Low 28 bits   */
#define LOW_29			0x000000001FFFFFFFL	/* Low 29 bits   */
#define LOW_30			0x000000003FFFFFFFL	/* Low 30 bits   */
#define LOW_31			0x000000007FFFFFFFL	/* Low 31 bits   */
#define LOW_32			0x00000000FFFFFFFFL	/* Low 32 bits   */
#define HIGH_32			0xFFFFFFFF00000000L	/* Upper 32-bits */
#define WFPCI_BUSMEM_MASK	LOW_32
#define WFPCI_BUSIO_MASK	LOW_24
#define WFPCI_SYSMAP_MASK	0x00000001FF000000L	/* bits 32-24 */
#define WFPCI_HOSE_NUM_SHIFT	33

#define WFPCI_IOBUS_MASK 	0x0000080000000000L
#define WFPCI_MEM_SPACE_MASK	0x0000000100000000L
#define WFPCI_MEM_SPACE	0x0

#define BIT31		0x80000000
#define BIT24		0x01000000


/*
 * The following are offsets from the PCI adapter base address.
 * The adapter base address is a function of the PCI hose number.
 */
#define WFPCI_MEM_BASE		0x000000000UL
#define WFPCI_IO_BASE		0x1FF000000UL
#define WFPCI_CONFIG_BASE	0x1FE000000UL	/* PCI Config Sparse Space */

#define WFPCI_SPARSE_MEM_BASE	WFPCI_MEM_BASE
#define WFPCI_DENSE_MEM_BASE	WFPCI_MEM_BASE
#define WFPCI_SPARSE_IO_BASE	WFPCI_IO_BASE

#define WF_SR_OFFSET            0x100000        /* Offset to Shared RAM */
  
/* 
 * PCI-centric defines for WF-PCI Adapter
 */
#define	WFPCI_PCI_MAX_SLOT		7	
#define WFPCI_PCI_INTR_INFO_SIZE	64 

/* address generation/translation macros	*/
#define WFPCI_PA_IO_BASE(X) (wf_io_space_pa_base | (u_long)(X))

#define WFPCI_8259_INTR_INFO_SIZE	16
#define WFPCI_ISA_BRIDGE_SLOT		0

/* WFPCI INTERRUPT TO SCB INDEX-ing MACROS */
#define WFPCI_SCB_ISA_BASE		0x800
#define WFPCI_SCB_PCI_BASE		0x800
#define WFPCI_SCB_BUS_INDEX		0x200
#define WFPCI_SCB_PCI_SLOT_INDEX	0x40
#define WFPCI_SCB_PER_INTR_INDEX	0x10

#define SET_INTMASK	1
#define CLEAR_INTMASK	2

/* the value used for no PCI IRQ */
#define WFPCI_NO_IRQ -1
#define WFPCI_KEYB_IRQ		1
#define WFPCI_MOUSE_IRQ		12
#define WFPCI_USB_IRQ		10
#define WFPCI_IDE_0_IRQ		14
#define WFPCI_IDE_1_IRQ		15
#define WFPCI_PRIMARY_INTR_REG 	0
#define WFPCI_DIST_INTR_REG	1
#define WFPCI_MIN_PCI_IRQ_NUM	32
#define WFPCI_MAX_PCI_IRQ_NUM	63

#define WFPCI_ISA_INTR_LOW		0xE0
#define WFPCI_ISA_INTR_HIGH		0xEF


#ifdef KERNEL

/*
 * DMA Support
 */

/*
 * DMA Window defines for WF-PCI Bridge
 */

#define WFPCI_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define WFPCI_DIRECT_WIN       1       /* Index to Direct-map DMA Window  */
#define WFPCI_32BIT_SG_WIN     2       /* Index to 32-bit, SAC S/G DMA Window */
#define WFPCI_64BIT_SG_WIN     3       /* Index to 64-bit, DAC S/G DMA Window */
#define WFPCI_DIRECT64         4       /* 64-bit direct DMA is just a 
                                         * register, not a window as such,
                                         * but it needs a dma_map_info_t
                                         * structure allocated...
                                         */
/* PCI base address values of direct-map DMA windows	*/
#define WFPCI_32B_DIRECT_MAP_BASE	(u_long)(1UL << 31)	/* 2GB */
#define WFPCI_64B_DIRECT_MAP_BASE	(u_long)(1UL << 44)  	/* 32TB */

#define WFPCI_64B_SG_MAP_BASE          (u_long)(1UL << 45)     /* 128TB */

/* Can't just AND the lower bits, like other platforms
 * because 1000(10) = 3e8(16), 2000(10) = 7d0(16), which
 * ends up OR-ing bits in the 00->3F(16) range that Wildfire
 * PCI host bridge numbers can be.
 * So, must divide-mod out the 1000's from the PCI bus num
 */
#define WFPCI_BUS_NUM(Busp)	(((Busp)->bus_num) % 1000)
#define _IS_64BIT_CAPABLE_(f)	((f) & DMA_64BIT)

/* Determination of SG DMA Window base address on PCI
 * Now includes 64-bit DMA selection...
 */

/*
 * Use private[] fields attached to PCI bus struct to get
 * high-freq., critical path params.
 */
#define _sg_32b_ctl_     private[1]
#define _sg_64b_ctl_     private[2]
#define _addrlim_sg_ctl_ private[3]
#define _shared_intr_    private[4]
#define _pci_hose_num_   private[5]
#define _soft_qbb_num_   private[6]
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
		WFPCI_64B_DIRECT_MAP_BASE : WFPCI_32B_DIRECT_MAP_BASE)
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
struct wfpci_bus_info {
        struct common_bus_info *common_bus_info;
        volatile struct wf_pci_csrs *wf_pci_csrs;
	io_handle_t	io_base;
	io_handle_t	mem_base;
	io_handle_t	config_base;
	u_int		low_irq;
	u_int		high_irq;
	u_int		hard_pci_bus_num;
	u_int		isa_attached;
	u_int		hw_bugs;
	u_long		soft_qbb_num;
	u_long		hard_qbb_num;
	u_long		present;
	u_long		active;
	u_long		configured;
	struct hal_rad  *hal_radp;
	u_int		rev_pca;
	u_int		rev_backplane;
	u_int		num_backplane;
	u_int		hose_num;
	u_int		rev_ne;
	u_int		rev_fe;
	u_int		num_pci_cfg_hdrs;
	u_int		errors;
};

/* Defines for hw_bugs field in wfpci_bus_info */
#define WFPCI_HWBUGS_NO_BW		0x2
#define WFPCI_HWBUGS_NO_IOTLB		0x4
#define WFPCI_HWBUGS_IOTLB_FLUSH	0x8
#define WFPCI_HWBUGS_XTRA_IOTLB_FLUSH	0x10
#define WFPCI_HWBUGS_SGPTE_EVICT	0x40
#define WFPCI_HWBUGS_ALLOC_BY_8		0x80
#define WFPCI_HWBUGS_NO_PCI_RD_MLT	0x100
#define WFPCI_HWBUGS_NO_WIN3		0x200
#define WFPCI_HWBUGS_PCA4_PCI_HANG	0x400
#define WFPCI_HWBUGS_NO_DAC		0x800

/*
 * WFPCI DMA Window defines
 */

/*
 * Each MCBUS<->PCI adapter had 4 DMA windows.
 * The windows are used as defined below
 *      (console expectations as well).
 *  +--------+--------+--------+--------+-----------------------+
 *  |   PCI  | Window | Offset |  Size  |  Usage                |
 *  | Window |  Type  |        |        |                       |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    0   |  S/G   |   8 MB |   8 MB | ADDR-LIMITED devices  |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    1   | Direct |   3 GB |   1 GB | Map 0-1GB main mem    |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    2   |  S/G   |   2 GB | 128MB  | General Purpose	| 
 *  |        |        |        | - 2GB  | 32-bit SG		|
 *  +--------+--------+--------+--------+-----------------------+
 *  |    3   |  S/G   |   4 GB |  ??    | 64-bit, DAC S/G	|
 *  +--------+--------+--------+--------+-----------------------+
 */

/* win_sel indices */
#define WFPCI_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define WFPCI_DIRECT_WIN       1       /* Index to Direct-map DMA Window  */
#define WFPCI_32BIT_SG_WIN     2       /* Index to 32-bit, SAC S/G DMA Window */
#define WFPCI_64BIT_SG_WIN     3       /* Index to 64-bit, DAC S/G DMA Window */

/* Per-WFPCI info struct used for dma, intrs, etc.	*/
/* Note: order of elements correlates to frequency of use/access in cache */
struct wfpci_info {
	u_long			sg_32b_ctl;
	shared_intr_info_t	*intr;
	u_long			sg_64b_ctl;
	u_long			addrlim_sg_ctl;
	u_long			direct_base;
	dma_map_info_t		dma_maps;
	u_long			present;
	struct bus		*busp;	/* ptr to bus struct for this bus */
	u_long			soft_qbb_num;
	u_long			gp_sg_base;
	u_long			sg_64bit_base;
	u_long			addrlim_sg_base;
};
/* 
 * Macro to extract primary PCI bus number from 
 * (potentially a compound) PCI bus number.
 * Used as index into array of WFPCI_info structs
 */

#define IS_AN_ISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_ISA)
#define IS_A_CONTIG_DEVICE(f)	(f & DMA_CONTIG)
#define IS_A_SG_DEVICE(a,f)	(IS_A_CONTIG_DEVICE(f) || wfpci_always_sg)
#define ADDRESS_LIMITED(Flags)	((Flags) & DMA_ADDR_LIMIT)
#define CONTIG_DESIRED(Flags)	((Flags) & DMA_CONTIG)
#define SG_ALLOCED(f)		((f) & DMA_HW_SG)
#define HAS_SG_ALLOCED(f)	((f) & DMA_HW_SG)

#define SG_NOTNEEDED	0
#define SG_REQUIRED	1
#define SG_DESIRED	2

#define WFPCI_WIN_MAX		0x4	/* 4 DMA mapping windows per PCI */
#define WFPCI_ISA_DMA_PREFETCH	0x0ffL	/* 255 bytes */

/* Various translation macros 	*/
#define CONFIG_BASE_TO_BRIDGE_CSR_BASE	0x02000000L

#define WF_IO_PORT_TO_PCI_CSRS(_Soft_Qbb_Num_, Pca_Port_Num, Pci_Port_Num) \
	( wf_io_space_pa_base | \
	 ((WF_QBB_IO_BASE(_Soft_Qbb_Num_)) | WF_QBB_CSR_BASE | \
	 ((u_long)(WF_PCA_ENTITY | Pca_Port_Num) << WF_ENTITY_SHIFT) | \
	 (u_long)(WF_PCI_IO_ADDR_EXT + (WF_PCI_BUS_DELTA*Pci_Port_Num))))

/* Determination of SG DMA Window base address on PCI	*/
/* TODO: update for 64-bit/DAC window */

/* p2p region includes sparse & dense memory region	*/
#define LOCAL_PEER_TO_PEER_DMA_BASE	(0x0000000000000000L)	/* 0GB->2GB */

#define IS_IN_PCI_SPACE(Pa)		((Pa) & WFPCI_IOBUS_MASK)
#define IS_IN_PCI_MEM(Pa)		(((Pa) & WFPCI_MEM_SPACE_MASK) \
						== WFPCI_MEM_SPACE)
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
#define WFPCI_RESOURCE_MAP_SIZE 200


#ifdef KERNEL
/* for pa-addr. gen/trans. macros below */
extern	u_long wf_io_space_pa_base;

/*
 * Function prototypes for wfpci.c
 */
/*
 * Init, IO-adapt-config
 */
/*
 * IO-Access routine externs
 */
extern	long wfpci_read_io_port(io_handle_t iohandle, int width, int type);
extern	void wfpci_write_io_port(io_handle_t iohandle, int width, int type, 
								long data);
extern	int wfpci_io_copyin(io_handle_t src, vm_offset_t dest, u_long count);
extern	int wfpci_io_copyout(vm_offset_t src, io_handle_t dest, u_long count);
extern	int wfpci_io_zero(io_handle_t dest, u_long count);
extern	int wfpci_io_copyio(io_handle_t src, io_handle_t dest, u_long count);
extern	io_handle_t wfpci_busphys_to_iohandle(u_long bus_addr, 
					int flags, struct controller *ctlrp);
extern	u_long wfpci_iohandle_to_phys(io_handle_t iohandle, long flags);

/*
 * DMA window sizing alg.
 */
extern	void wfpci_choose_dma_windows();

/*
 * DMA mapping externs
 */
extern	int wfpci_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long wfpci_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long wfpci_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int wfpci_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int wfpci_dma_min_boundary(struct controller *cntrlrp);
extern  void    wfpci_sg_tbia(struct sglist *);
/*
 * interrupt related functions
 */
extern u_long wfpci_set_intr_reg(struct bus *busp,
				 int bit_to_change,
				 int operation);

/*
 * Defines for development debug
 */
/* WFPCI_DMA_Debug defines */
#define WFPCI_DMA_Debug_Info		0x1
#define WFPCI_DMA_Debug_SG		0x2
#define WFPCI_DMA_Debug_NO_IOTLB	0x4
#define WFPCI_DMA_Debug_IOTLB_FLUSH	0x8
#define WFPCI_DMA_Debug_XTRA_IOTLB_FLUSH	0x10
#define WFPCI_DMA_Debug_SGPTE_EVICT	0x40
#define WFPCI_DMA_Debug_No_DAC		0x20
#define WFPCI_DMA_Debug_NO_ALLOC_BY_8	0x80
#define WFPCI_DMA_Debug_P2P		0x80000000 /* p2p off for 99.999% of Wildfire's */

/* WFPCI_Developer_Debug defines */
#define WFPCI_Developer_Debug_Info	0x1
#define WFPCI_Developer_Debug_NO_BW	0x2
#define WFPCI_Developer_Debug_NO_PCI_RD_MLT	0x4

/*
 * wfpci.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since wfcpu.h, wfqbb.h, & wfpci.h may be included in
 *	 one .c file, their debug definitions must not collide.
 */

extern	u_int	wfpci_developer_debug;

/* To remove/add all debug printfs */
#define __WFPCIDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * wfpci_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	WFPCID_INOUT	0x00000001	/* routine entry and exit 	*/
#define WFPCID_NUMA	0x00000020	/* NUMA-related info		*/
#define WFPCID_DMAINFO	0x00000100	/* system-level dma settings	*/
#define WFPCID_P2PDMA	0x00000200	/* peer-to-peer dma info	*/
#define WFPCID_PCIINFO	0x00001000	/* PCI config. info		*/
#define WFPCID_ISAINFO	0x00010000	/* ISA config. info		*/
#define WFPCID_CONSOLE	0x00020000	/* console device info		*/
#define WFPCID_INTRINFO	0x00100000	/* Intr. config. info		*/
#define WFPCID_HWINFO	0x01000000	/* HW bugs, workaround info	*/

/* New, testing hw-support debug printfs				*/
#define WFPCID_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */

/*
 * string defines used in WFPCIPRINTF to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision.
 */
extern char * _WFPCIinout;
extern char * _WFPCInuma;
extern char * _WFPCIdmainfo;
extern char * _WFPCIp2pdma;
extern char * _WFPCIpciinfo;
extern char * _WFPCIisainfo;
extern char * _WFPCIconsole;
extern char * _WFPCIintrinfo;
extern char * _WFPCIhwbugs;
extern char * _WFPCInot_yet;


/*
 * printf expansion that WFPCIPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _WFPCIxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __WFPCIDEBUG
#   define _WFPCID_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_INOUT )  {	\
	    /* VARARGS */			\
            printf (_WFPCIinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_NUMA)  {	\
	    /* VARARGS */			\
            printf (_WFPCInuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_DMAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_DMAINFO)  {	\
	    /* VARARGS */			\
            printf (_WFPCIdmainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_P2PDMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_P2PDMA)  {	\
	    /* VARARGS */			\
            printf (_WFPCIp2pdma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_PCIINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_PCIINFO)  {	\
	    /* VARARGS */			\
            printf (_WFPCIpciinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_ISAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_ISAINFO)  {	\
	    /* VARARGS */			\
            printf (_WFPCIisainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_CONSOLE(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_CONSOLE)  {	\
	    /* VARARGS */			\
            printf (_WFPCIconsole); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_INTRINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_INTRINFO)  {	\
	    /* VARARGS */			\
            printf (_WFPCIintrinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_HWINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_HWINFO)  {	\
	    /* VARARGS */			\
            printf (_WFPCIhwbugs); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFPCID_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfpci_developer_debug & WFPCID_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_WFPCInotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * wfpci_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * WFPCID_INOUT | WFPCID_DMAINFO
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define WFPCIPRINTF(F, X)	_##F(X)

#else  /* !__WFPCIDEBUG */
#   define WFPCIPRINTF(F, X)
#endif /* __WFPCIDEBUG */

#endif	/* KERNEL */

#if defined (__cplusplus)
}
#endif /* __cplusplus */

#endif	/* __ARCH_ALPHA_HAL_WFPCI_H__ */

#define     WF_PCA_ASIC_REV_MASK 0x0000000FL
