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
#pragma ident "@(#)$RCSfile: wfcpu.h,v $ $Revision: 1.1.30.3 $ (DEC) $Date: 2002/06/03 17:08:28 $"



#ifndef __ARCH_ALPHA_HAL_WFCPU_H__
#define __ARCH_ALPHA_HAL_WFCPU_H__

#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * WFCPU-PCI Address Space defines & declarations 
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

#define BIT31		0x80000000
#define BIT24		0x01000000



#ifdef KERNEL
/* for pa-addr. gen/trans. macros below */
extern	u_long wf_io_space_pa_base;

#endif	/* KERNEL */

/* 
 * Define high temperature operating threshold for 
 * environmental monitoring 
 */
#define WF_HIGH_TEMP_THRESHOLD 40



/* 
 * Machine check structures, defines 
 */

/*
 * System Specific Machine Check Error Codes
 */
#define WF_MCHK_SYS_UNCORR	0x202
#define WF_MCHK_SYS_CORERR	0x204
#define WF_MCHK_SYS_EVENT	0x206
#define WF_MCHK_SUMM_MEMERR	0x4

/* MACRO to get ptr to per-cpu mcheck_control struct */
#define WF_MCHECK_CONTROL(cpu_id) wf_mcheck_control[cpu_id]

/*
 * Per-cpu data structure for tracking machine check error handing
 */
struct wf_error_counters {	/* this is a copy of elr_error_counters, */
				/* so that errlog.h doesn't need to be   */
				/* included here. */
    char error_counters[96];
};


/* Bits 31:16 are Wildfire's 660,670 machine-check reason mask */
#define WF_MCHECK_REASON_MASK 0x000000000000FF00L

/* 
 * WildFire Machine Check Logout Frames
 */

/*
 * WildFire-specific portion of the machine check logout 
 * frame. This is used for both correctable and 
 * uncorrectable errors and system events.
 */
struct elf_wf_error_data {
	u_long	cpu_flt_sum;	/* CPU Fault Summary */
        u_long  qbb[8];		/* QBB 0->7 CSRs to be logged summary */
};

/* 
 * WildFire-Specific structure for logout frame on 
 * system events
 */ 
/* TODO: is common ev6 logout header used, or only Alpha-common hdr */
struct el_wf_680_logout_frame {
        struct	elf_common_ev6_logout_header	hdr;
	struct	elf_wf_error_data		sys;
};

/* 
 * Wildfire uncorrected error log data structures
 */
struct el_wf_660_670_logout_frame {
        struct  elf_common_ev6_uncorr_frame	uncorr_common;
	struct	elf_wf_error_data 		elfmc_sysdata;
};

/* 
 *  WildFire 630/620 correctable logout frame. This is the PAL's
 * 	logout frame, which becomes a piece of the correctable
 *	errorlog packet.
 */

struct el_wf_620_630_logout_frame {
        struct  elf_common_ev6_corr_frame	corr_common;
	struct	elf_wf_error_data 		elfcc_sysdata;
};

/* Entry Terminator Subpacket */
struct entry_terminator {
    short length;   /* Length (0008)   */
    short class;    /* Class (0000)    */
    short type;     /* Type (0000)     */
    short revision; /* Revision (0001) */
};

/* System Error Frame Header Subpacket */
struct sys_err_frame_header {
    struct entry_terminator header;
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* System Event Frame Header Subpacket */
struct sys_evt_frame {
    struct entry_terminator header;
    char   timestamp[8];       /* Timestamp                 */
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* Error Halt Frame Header Subpacket */
struct err_halt_frame_header {
    struct entry_terminator header;
    int    halt_reason_code;   /* Halt Reason Code          */
    int    rsvd;               /* Reserved                  */
    u_long time_stamp;         /* Time Stamp                */
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* Basic System Error Frame Subpacket */
struct basic_sys_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;     /* Base Physical Address     */
};

/* Kernel Hardware Correctable Error Reporting Status Subpacket */
struct kern_hw_corr_err_status {
    struct entry_terminator header;
    u_long cpu_whami;
    u_long cer_stat;
};

/* Quad Switch Address (QSA) Error Frame Subpacket */
struct qsa_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this QSA's CSRs */
    u_long qsa_cpu_err_sum;     /* QSA_CPU Error Summary                    */
    u_long qsa_misc_err_sum;    /* QSA_MISC Error Summary                   */
    u_long qsa_tmo_err_sum;     /* QSA_TMO Error Summary                    */
    u_long qsa_ill_cmd_err_sum; /* QSA_ILL_CMD Error Summary                */
};

/* Quad Switch Data (QSD) Error Frame Subpacket */
struct qsd_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this QSD's CSRs */
    u_long qsd_err_sum;         /* QSD Error Summary                        */
};  

/* Directory Error Frame Subpacket */
struct dir_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this Directory's CSRs */
    u_long dir_err_sum;         /* DIR Error Summary */
    u_long dir_ce_trap0_a;     /* DIR_CE_TRAP0_A */
    u_long dir_ce_trap0_b;     /* DIR_CE_TRAP0_B */
    u_long dir_ce_trap0_c;     /* DIR_CE_TRAP0_C */
    u_long dir_ce_trap1_a;     /* DIR_CE_TRAP1_A */
    u_long dir_ce_trap1_b;     /* DIR_CE_TRAP1_B */
    u_long dir_ce_trap1_c;     /* DIR_CE_TRAP1_C */
    u_long dir_ce_trap2_a;     /* DIR_CE_TRAP2_A */
    u_long dir_ce_trap2_b;     /* DIR_CE_TRAP2_B */
    u_long dir_ce_trap2_c;     /* DIR_CE_TRAP2_C */
    u_long dir_ce_trap3_a;     /* DIR_CE_TRAP3_A */
    u_long dir_ce_trap3_b;     /* DIR_CE_TRAP3_B */
    u_long dir_ce_trap3_c;     /* DIR_CE_TRAP3_C */
    u_long dir_uce_trap_a;     /* DIR_UCE_TRAP_A */
    u_long dir_uce_trap_b;     /* DIR_UCE_TRAP_B */
    u_long dir_uce_trap_c;     /* DIR_UCE_TRAP_C */
    u_long dir_err_detect_a;   /* DIR_ERR_DETECT_A */
    u_long dir_err_detect_b;   /* DIR_ERR_DETECT_B */
};

/* IOP Error Frame Subpacket */
struct iop_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this IOP's CSRs */
    u_long ioa_err_sum;         /* IOA Error Summary */
    u_long iod_err_sum;         /* IOD Error Summary */
};

/* PCA Error Frame Subpacket */
struct pca_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this PCA's CSRs */
    u_long pca_whatami;         /* PCA What Am I     */
    u_long pca_err_sum;         /* PCA Error Summary */          
    u_long ne_whatami;          /* NE What Am I      */
    u_long ne_err_sum;          /* NE Error Summary  */
    u_long fe_whatami;          /* FE What Am I      */
    u_long fe_err_sum;          /* FE Error Summary  */
    u_long pci0_err_sum;        /* PCI0 Error Summary */
    u_long pci0_err_addr;       /* PCI0 Error Address */
    u_long pci1_err_sum;        /* PCI1 Error Summary */
    u_long pci1_err_addr;       /* PCI1 Error Address */
};

/* Global Port (GP) Error Frame Subpacket */
struct gp_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this GP's CSRs */
    u_long gpa_gpl_err_sum;     /* GPA_GPL Error Summary */
    u_long gpa_ext_ovfl_err_sum;/* GPA Extended Overflow Error Summary */
    u_long gpa_hsl_err_sum;     /* GPA_HSL Error Summary */
    u_long gpa_gpl_err_addr_0;  /* GPA_GPL Error Address 0 */
    u_long gpa_gpl_err_addr_1;  /* GPA_GPL Error Address 1 */
    u_long gpa_gpl_err_addr_2;  /* GPA_GPL Error Address 2 */
    u_long gpa_gpl_err_addr_3;  /* GPA_GPL Error Address 3 */
    u_long gpa_gpl_err_addr_4;  /* GPA_GPL Error Address 4 */
    u_long gpa_gpl_err_addr_5;  /* GPA_GPL Error Address 5 */
    u_long gpa_gpl_err_addr_6;  /* GPA_GPL Error Address 6 */
    u_long gpa_hsl_err_addr_0;  /* GPA_HSL Error Address 0 */
    u_long gpa_hsl_err_addr_1;  /* GPA_HSL Error Address 1 */
    u_long gpa_hsl_err_addr_2;  /* GPA_HSL Error Address 2 */
    u_long gpa_hsl_err_addr_3;  /* GPA_HSL Error Address 3 */
    u_long gpa_hsl_err_addr_4;  /* GPA_HSL Error Address 4 */
    u_long gpa_hsl_err_addr_5;  /* GPA_HSL Error Address 5 */
    u_long gpa_hsl_err_addr_6;  /* GPA_HSL Error Address 6 */
    u_long gpd_gpl_err_sum;     /* GPD_GPL Error Summary   */
    u_long gpd_hsl_err_sum;     /* GPD_HSL Error Summary   */
};

/* Hierarchical Switch (HS) Error Frame Subpacket */
struct hs_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this HS's CSRs */
    u_long hs_csr0;             /* HS_CSR0 */
    u_long hs_csr1;             /* HS_CSR1 */
};

/* Memory Error Frame Subpacket Rev 2*/
struct mem_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this Memory's CSRs    */
    u_long mem_err_sum;         /* Memory Error Summary */
    u_long mem_rd_ce_trap0;        /* MEM_RD_CE_TRAP0 */
    u_long mem_rd_ce_trap1;        /* MEM_RD_CE_TRAP1 */
    u_long mem_rd_ce_trap2;        /* MEM_RD_CE_TRAP2 */
    u_long mem_rd_ce_trap3;        /* MEM_RD_CE_TRAP3 */
    u_long mem_rd_uce_trap;        /* MEM_RD_UCE_TRAP */
    u_long mem_wt_ce_trap0;        /* MEM_WT_CE_TRAP0 */
    u_long mem_wt_ce_trap1;        /* MEM_WT_CE_TRAP1 */
    u_long mem_wt_ce_trap2;        /* MEM_WT_CE_TRAP2 */
    u_long mem_wt_ce_trap3;        /* MEM_WT_CE_TRAP3 */
    u_long mem_wt_uce_trap;        /* MEM_WT_UCE_TRAP */
};

/* Memory Error Frame Subpacket Rev 1*/
    struct mem_err_frame_rev1 {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this Memory's CSRs    */
    u_long mem_err_sum;         /* Memory Error Summary */
    u_long mem_rd_trap0;        /* MEM_RD_TRAP0 */
    u_long mem_rd_trap1;        /* MEM_RD_TRAP1 */
    u_long mem_rd_trap2;        /* MEM_RD_TRAP2 */
    u_long mem_rd_trap3;        /* MEM_RD_TRAP3 */
    u_long mem_rd_trap4;        /* MEM_RD_TRAP4 */
    u_long mem_rd_trap5;        /* MEM_RD_TRAP5 */
    u_long mem_rd_trap6;        /* MEM_RD_TRAP6 */
    u_long mem_rd_trap7;        /* MEM_RD_TRAP7 */
    u_long mem_wt_trap0;        /* MEM_WT_TRAP0 */
    u_long mem_wt_trap1;        /* MEM_WT_TRAP1 */
    u_long mem_wt_trap2;        /* MEM_WT_TRAP2 */
    u_long mem_wt_trap3;        /* MEM_WT_TRAP3 */
    u_long mem_wt_trap4;        /* MEM_WT_TRAP4 */
    u_long mem_wt_trap5;        /* MEM_WT_TRAP5 */
    u_long mem_wt_trap6;        /* MEM_WT_TRAP6 */
    u_long mem_wt_trap7;        /* MEM_WT_TRAP7 */
};

/* DTag Error Frame Subpacket */
struct dtag_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;      /* Base Physical Address of this DTag's CSRs */
    u_long dtag_control;        /* DTag Control */
    u_long dtag_err_sum;        /* DTag Error Summary */
    u_long dtag_err_cid;        /* DTag Error CID */
    u_long dtag_err_cmd;        /* DTag Error Command */
    u_long dtag_err_addr_0;     /* DTag Error Addres 0 */
    u_long dtag_err_addr_1;     /* DTag Error Addres 1 */
    u_long dtag_err_addr_2;     /* DTag Error Addres 2 */
    u_long dtag_err_addr_3;     /* DTag Error Addres 3 */
    u_long dtag_ecc_control;    /* DTagII ECC Control */
    u_long dtag_ecc_syndrome;   /* DTagII ECC Syndrome */
};

/* Shared RAM structure for PSM and HPM System Events */
struct wf_psm_hpm_sysevt {
    int    timestamp;              /* offset 2(size 4) */
    int    pad0;                   /* align to quadword */
    char   sysevt_code;            /* offset A */
    char   supp_code;              /* offset B */
    short  psm_sr0;                /* offset C(size 2) */
    short  psm_sr1;                /* offset E(size 2) */
    char   csb_addr;                 
    char   pad1;                   /* for alignment */
};

/* Shared RAM structure for PBM System Events */
struct wf_pbm_sysevt {
    int     timestamp;              
    int     pad0;
    short   reset_config;            
    short   pwr_supp;                
    short   pio_data0;               
    short   int_ctrl;                
    char    fail_info_byte2;      
    char    fail_info_byte6;      
    char    fail_info_byte7;      
    char    fail_info_byte8;      
    char    csb_addr;                 
    char    pad1[2];                  /* to align struct */
};

/* definitions needed for subpacket header */
#define WF_EL_HDR_CLASS                    0x000A
#define	WF_EL_HDR_REV	                   0x0001
#define	WF_EL_HDR_REV2	                   0x0002

/* definitions needed for Termination packet */
#define  WF_EL_TERM_LNGTH                  sizeof(struct entry_terminator)
#define  WF_EL_TERM_CLASS                  0x0000
#define  WF_EL_TERM_TYPE                   0x0000
#define  WF_EL_TERM_REV                    0x0001

/* definitions needed for system error frame header subpacket */
#define  WF_EL_SYS_ERR_HDR_LNGTH                  sizeof(struct sys_err_frame_header)
#define  WF_EL_SYS_ERR_HDR_CLASS                  0x0005
#define  WF_EL_SYS_ERR_HDR_TYPE                   0x0001
#define  WF_EL_SYS_ERR_HDR_REV                    0x0001

/* definitions needed for system event frame header subpacket */
#define  WF_EL_SYS_EVT_LNGTH                  sizeof(struct sys_evt_frame)
#define  WF_EL_SYS_EVT_CLASS                  0x0005
#define  WF_EL_SYS_EVT_TYPE                   0x0002
#define  WF_EL_SYS_EVT_REV                    0x0001

/* definitions needed for entity subpacket headers */
#define  WF_EL_QSA_HDR_LGTH                   sizeof(struct qsa_err_frame)
#define  WF_EL_QSD_HDR_LGTH                   sizeof(struct qsd_err_frame)
#define  WF_EL_DIR_HDR_LGTH                   sizeof(struct dir_err_frame)
#define  WF_EL_IOP_HDR_LGTH                   sizeof(struct iop_err_frame)
#define  WF_EL_PCA_HDR_LGTH                   sizeof(struct pca_err_frame)
#define  WF_EL_GP_HDR_LGTH                    sizeof(struct gp_err_frame)
#define  WF_EL_HS_HDR_LGTH                    sizeof(struct hs_err_frame)
#define  WF_EL_MEM_HDR_LGTH                   sizeof(struct mem_err_frame)
#define  WF_EL_DTAG_HDR_LGTH                  sizeof(struct dtag_err_frame)
#define  WF_EL_KERN_HW_CORR_ERR_HDR_REV       0x0002
#define  WF_EL_KERN_HW_CORR_ERR_HDR_TYPE      0x0001
#define  WF_EL_KERN_HW_CORR_ERR_HDR_CLASS     0x0009
#define  WF_EL_KERN_HW_CORR_ERR_HDR_LGTH      sizeof(struct kern_hw_corr_err_status)

/* definitons for correctable error throttling */
#define  WF_620_THROTTLE_ON  0x100000000 /* used for setting CER_STAT<32> */
#define  WF_620_THROTTLE_OFF 0x0 /* used for setting CER_STAT<32> */
#define  WF_630_THROTTLE_ON  0x100 /* used for setting CER_STAT<8> */
#define  WF_630_THROTTLE_OFF 0x0 /* used for setting CER_STAT<8> */
#define  WF_ALL_THROTTLE_OFF 0x0 /* used for initializing CER_STAT to 0 */


#ifdef KERNEL
/* A per-cpu data structure for handling, tracking machine checks */
struct wf_mcheck_control {

    /* The following set of structure elements are used for		*/
    /* intentional machine checks, such as those caused by BADADDR IO	*/
    /* probing, probing memory (testpage code).				*/
    u_int 	mcheck_expected;	/* flag: we're probing.		*/
    u_int 	mcheck_occurred;	/* Number of mchecks during probe.  */
    u_int 	mcheck_action; 		/* Action to take with this mcheck: */
					/* recover, crash, retry	    */
    u_int	mcheck_retry;	/* Logout frames retry bit		*/
    long 	mcheck_return;	/* return to this PC expected mchecks	*/
    memtest_t 	mcheck_tp_active;	/* flag: testpage in progress	*/
    long  	mcheck_page;	/* page we're testing.			*/
    u_long 	mctl_probe_va;	/* VA being probed. 			*/

    /* The next set of elements are used to maintain a running	*/
    /* count of error flags found set in the elr_soft_flags 	*/
    /* structure returned from each error parse. These values 	*/
    /* start at 0 at system boot time. 				*/
    struct wf_error_counters error_670_counters;
    struct wf_error_counters error_660_counters;
    struct wf_error_counters error_630_counters;
    struct wf_error_counters error_620_counters;

    long syscorr_period;
    long syscorr_last;           
    long syscorr_first;          
    long syscorr_threshold;      
    long syscorr_count;          
    long proccorr_period;        
    long proccorr_last;          
    long proccorr_first;         
    long proccorr_threshold;     
    long proccorr_count;         
    long disable_620;
    long disable_630;
    long timeout_queued_620;
    long timeout_queued_630;

    /*
     * error log structures 
     */
    struct sys_err_frame_header     sys_err_sub_hdr;
    struct sys_evt_frame            sysevt_frame;
    struct qsa_err_frame            qsa_logout_frame;
    struct qsd_err_frame            qsd_logout_frame;
    struct iop_err_frame            iop_logout_frame;
    struct mem_err_frame            mem_logout_frame;
    struct dtag_err_frame           dtag_logout_frame;
    struct dir_err_frame            dir_logout_frame;
    struct pca_err_frame            pca_logout_frame;
    struct gp_err_frame             gp_logout_frame;
    struct hs_err_frame             hs_logout_frame;
    struct kern_hw_corr_err_status  throttle_status_frame;
    struct wf_psm_hpm_sysevt        psm_sysevt;
    struct wf_psm_hpm_sysevt        hpm_sysevt;
    struct wf_pbm_sysevt            pbm_sysevt;
    struct entry_terminator         terminator_packet;

};
#endif

#define BCOPY_AND_INCREMENT(X, Y)  bcopy(X, errlog_ptr, sizeof(struct Y)); \
			           errlog_ptr += sizeof(struct Y);

#define WF_PARSE_CSR(X,Y,Z) wfcpu_parse_csr(X,Y,Z, type, vmmt_rv_mask);

/* Strings used for error reporting 
 * NOTE: these must be NULL terminated
 */
/* QSA */
static char *wf_qsa_cpu_err_sum_strings[] = {
    "CPU 0 NXM error",                                         /* Bit 0  */
    "CPU 1 NXM error",                                         /* Bit 1  */
    "CPU 2 NXM error",                                         /* Bit 2  */
    "CPU 3 NXM error",                                         /* Bit 3  */
    "CPU 0 overflow error",                                    /* Bit 4  */
    "CPU 1 overflow error",                                    /* Bit 5  */
    "CPU 2 overflow error",                                    /* Bit 6  */
    "CPU 3 overflow error",                                    /* Bit 7  */
    NULL
};
static char *wf_qsa_misc_err_sum_strings[] = {
    "GPLink/Arbiter overflow error",                           /* Bit 0  */
    "GPLink command inconsistency error",                      /* Bit 1  */
    "GPLink NXM error",                                        /* Bit 2  */
    "IOP overflow error",                                      /* Bit 3  */
    "IOP NXM error",                                           /* Bit 4  */
    "Multiple bank violation",                                 /* Bit 5  */
    "Multiple owner violation",                                /* Bit 6  */
    "IOP probe NXM error",                                     /* Bit 7  */
    NULL
};                             
static char *wf_qsa_tmo_err_sum_strings[] = {
    "Issue pending time-out error",                            /* Bit 0  */
    "Completion pending time-out error",                       /* Bit 1  */
    "Commit pending time-out error",                           /* Bit 2  */
    "CPU idle time-out error",                                 /* Bit 3  */
    "Failing processor",                                       /* Bit 4  */
    "Failing processor",                                       /* Bit 5  */
    "Failing processor",                                       /* Bit 6  */
    NULL
};  

static char *wf_qsa_ill_cmd_err_sum_strings[] = {
    "CPU 0 illegal command error",                             /* Bit 0  */
    "CPU 1 illegal command error",                             /* Bit 1  */
    "CPU 2 illegal command error",                             /* Bit 2  */
    "CPU 3 illegal command error",                             /* Bit 3  */
    "IOP illegal command error",                               /* Bit 4  */
    NULL
};    

/* QSD */
static char *wf_qsd_err_sum_strings[] = { 
    "GPI buffer overflow/underflow error",                     /* Bit 0  */
    "GPO CPU 0 buffer overflow/underflow error",               /* Bit 1  */
    "GPO CPU 1 buffer overflow/underflow error",               /* Bit 2  */
    "GPO CPU 2 buffer overflow/underflow error",               /* Bit 3  */
    "GPO CPU 3 buffer overflow/underflow error",               /* Bit 4  */
    "GPO IOP buffer overflow/underflow error",                 /* Bit 5  */
    "GPO short fill buffer overflow/underflow error",          /* Bit 6  */
    "IOP local fill buffer overflow_underflow error",          /* Bit 7  */
    "IOP local PIO buffer overflow_underflow error",           /* Bit 8  */
    "IOP remote fill buffer overflow_underflow error",         /* Bit 9  */
    "IOP remote PIO buffer overflow_underflow error",          /* Bit 10 */
    "Victim buffer overflow/underflow error",                  /* Bit 11 */
    "CPU 0 local fill buffer overflow/underflow error",        /* Bit 12 */
    "CPU 1 local fill buffer overflow/underflow error",        /* Bit 13 */
    "CPU 2 local fill buffer overflow/underflow error",        /* Bit 14 */
    "CPU 3 local fill buffer overflow/underflow error",        /* Bit 15 */
    "GPI buffer overflow/underflow error",                     /* Bit 16 */
    "GPO CPU 0 buffer overflow/underflow error",               /* Bit 17 */
    "GPO CPU 1 buffer overflow/underflow error",               /* Bit 18 */
    "GPO CPU 2 buffer overflow/underflow error",               /* Bit 19 */
    "GPO CPU 3 buffer overflow/underflow error",               /* Bit 20 */
    "GPO IOP buffer overflow/underflow error",                 /* Bit 21 */
    "GPO short fill buffer overflow/underflow error",          /* Bit 22 */
    "IOP local fill buffer overflow_underflow error",          /* Bit 23 */
    "IOP local PIO buffer overflow_underflow error",           /* Bit 24 */
    "IOP remote fill buffer overflow_underflow error",         /* Bit 25 */
    "IOP remote PIO buffer overflow_underflow error",          /* Bit 26 */
    "Victim buffer overflow/underflow error",                  /* Bit 27 */
    "CPU 0 local fill buffer overflow/underflow error",        /* Bit 28 */
    "CPU 1 local fill buffer overflow/underflow error",        /* Bit 29 */
    "CPU 2 local fill buffer overflow/underflow error",        /* Bit 30 */
    "CPU 3 local fill buffer overflow/underflow error",        /* Bit 31 */
    "GPI buffer overflow/underflow error",                     /* Bit 32 */
    "GPO CPU 0 buffer overflow/underflow error",               /* Bit 33 */
    "GPO CPU 1 buffer overflow/underflow error",               /* Bit 34 */
    "GPO CPU 2 buffer overflow/underflow error",               /* Bit 35 */
    "GPO CPU 3 buffer overflow/underflow error",               /* Bit 36 */
    "GPO IOP buffer overflow/underflow error",                 /* Bit 37 */
    "GPO short fill buffer overflow/underflow error",          /* Bit 38 */
    "IOP local fill buffer overflow_underflow error",          /* Bit 39 */
    "IOP local PIO buffer overflow_underflow error",           /* Bit 40 */
    "IOP remote fill buffer overflow_underflow error",         /* Bit 41 */
    "IOP remote PIO buffer overflow_underflow error",          /* Bit 42 */
    "Victim buffer overflow/underflow error",                  /* Bit 43 */
    "CPU 0 local fill buffer overflow/underflow error",        /* Bit 44 */
    "CPU 1 local fill buffer overflow/underflow error",        /* Bit 45 */
    "CPU 2 local fill buffer overflow/underflow error",        /* Bit 46 */
    "CPU 3 local fill buffer overflow/underflow error",        /* Bit 47 */
    "GPI buffer overflow/underflow error",                     /* Bit 48 */
    "GPO CPU 0 buffer overflow/underflow error",               /* Bit 49 */
    "GPO CPU 1 buffer overflow/underflow error",               /* Bit 50 */
    "GPO CPU 2 buffer overflow/underflow error",               /* Bit 51 */
    "GPO CPU 3 buffer overflow/underflow error",               /* Bit 52 */
    "GPO IOP buffer overflow/underflow error",                 /* Bit 53 */
    "GPO short fill buffer overflow/underflow error",          /* Bit 54 */
    "IOP local fill buffer overflow_underflow error",          /* Bit 55 */
    "IOP local PIO buffer overflow_underflow error",           /* Bit 56 */
    "IOP remote fill buffer overflow_underflow error",         /* Bit 57 */
    "IOP remote PIO buffer overflow_underflow error",          /* Bit 58 */
    "Victim buffer overflow/underflow error",                  /* Bit 59 */
    "CPU 0 local fill buffer overflow/underflow error",        /* Bit 60 */
    "CPU 1 local fill buffer overflow/underflow error",        /* Bit 61 */
    "CPU 2 local fill buffer overflow/underflow error",        /* Bit 62 */
    "CPU 3 local fill buffer overflow/underflow error",        /* Bit 63 */
    NULL
};

/* DIR */
static char *wf_dir_err_sum_strings[] = { 
    "Correctable error pointer",                               /* Bit 0  */
    "Correctable error pointer",                               /* Bit 1  */
    "Reserved",                                                /* Bit 2  */
    "Correctable error count",                                 /* Bit 3  */
    "Correctable error count",                                 /* Bit 4  */
    "Reserved",                                                /* Bit 5  */
    "Correctable error summary",                               /* Bit 6  */
    "Correctable error missed",                                /* Bit 7  */
    "Reserved",                                                /* Bit 8  */
    "Reserved",                                                /* Bit 9  */
    "Reserved",                                                /* Bit 10 */
    "Reserved",                                                /* Bit 11 */
    "Reserved",                                                /* Bit 12 */
    "Reserved",                                                /* Bit 13 */
    "Reserved",                                                /* Bit 14 */
    "Reserved",                                                /* Bit 15 */
    "Error detect valid",                                      /* Bit 16 */
    "Error detect missed",                                     /* Bit 17 */
    "Uncorrectable error valid",                               /* Bit 18 */
    "Uncorrectable error missed",                              /* Bit 19 */
    NULL 
};

/* These return an address, so no text strings associated */
static char *wf_dir_ce_trap0_a_strings[] = { NULL };
static char *wf_dir_ce_trap0_b_strings[] = { NULL }; 
static char *wf_dir_ce_trap0_c_strings[] = { NULL }; 
static char *wf_dir_ce_trap1_a_strings[] = { NULL }; 
static char *wf_dir_ce_trap1_b_strings[] = { NULL }; 
static char *wf_dir_ce_trap1_c_strings[] = { NULL }; 
static char *wf_dir_ce_trap2_a_strings[] = { NULL }; 
static char *wf_dir_ce_trap2_b_strings[] = { NULL }; 
static char *wf_dir_ce_trap2_c_strings[] = { NULL }; 
static char *wf_dir_ce_trap3_a_strings[] = { NULL }; 
static char *wf_dir_ce_trap3_b_strings[] = { NULL }; 
static char *wf_dir_ce_trap3_c_strings[] = { NULL };
static char *wf_dir_uce_trap_a_strings[] = { NULL };
static char *wf_dir_uce_trap_b_strings[] = { NULL };
static char *wf_dir_uce_trap_c_strings[] = { NULL };
static char *wf_dir_err_detect_a_strings[] = { NULL };
static char *wf_dir_err_detect_b_strings[] = { 
    "ArbBus command",                                          /* Bit 0  */
    "ArbBus command",                                          /* Bit 1  */
    "ArbBus command",                                          /* Bit 2  */
    "ArbBus command",                                          /* Bit 3  */
    "ArbBus command",                                          /* Bit 4  */
    "ArbBus command",                                          /* Bit 5  */
    "ArbBus command",                                          /* Bit 6  */
    "Reserved",                                                /* Bit 7  */
    "Reserved",                                                /* Bit 8  */
    "Reserved",                                                /* Bit 9  */
    "Reserved",                                                /* Bit 10 */
    "Reserved",                                                /* Bit 11 */
    "Reserved",                                                /* Bit 12 */
    "Reserved",                                                /* Bit 13 */
    "Reserved",                                                /* Bit 14 */
    "Reserved",                                                /* Bit 15 */
    "Multiple bank violation",                                 /* Bit 16 */
    "Victim access violation",                                 /* Bit 17 */
    "Bank timing violation",                                   /* Bit 18 */
    "Array timing violation",                                  /* Bit 19 */
    "Refresh time-out",                                        /* Bit 20 */
    "Reserved",                                                /* Bit 21 */
    "Reserved",                                                /* Bit 22 */
    "Reserved",                                                /* Bit 23 */
    "Reserved",                                                /* Bit 24 */
    "Reserved",                                                /* Bit 25 */
    "Reserved",                                                /* Bit 26 */
    "Reserved",                                                /* Bit 27 */
    "Reserved",                                                /* Bit 28 */
    "Reserved",                                                /* Bit 29 */
    "Reserved",                                                /* Bit 30 */
    "Reserved",                                                /* Bit 31 */
    "Failing array",                                           /* Bit 32 */
    "Failing array",                                           /* Bit 33 */
    "Failing array",                                           /* Bit 34 */
    "Failing array",                                           /* Bit 35 */
    NULL
};
			    
/* IOP */
static char *wf_ioa_err_sum_strings[] = {
    "Hose 0 address checksum error",                           /* Bit 0  */
    "Hose 1 address checksum error",                           /* Bit 1  */
    "Hose 2 address checksum error",                           /* Bit 2  */
    "Hose 3 address checksum error",                           /* Bit 3  */
    "Hose 0 time-out error",                                   /* Bit 4  */
    "Hose 1 time-out error",                                   /* Bit 5  */
    "Hose 2 time-out error",                                   /* Bit 6  */
    "Hose 3 time-out error",                                   /* Bit 7  */
    "Hose 0 overflow error",                                   /* Bit 8  */
    "Hose 1 overflow error",                                   /* Bit 9  */
    "Hose 2 overflow error",                                   /* Bit 10 */
    "Hose 3 overflow error",                                   /* Bit 11 */
    "Hose 0 credit error",                                     /* Bit 12 */
    "Hose 1 credit error",                                     /* Bit 13 */
    "Hose 2 credit error",                                     /* Bit 14 */
    "Hose 3 credit error",                                     /* Bit 15 */
    "Reserved",                                                /* Bit 16 */
    "Reserved",                                                /* Bit 17 */
    "Reserved",                                                /* Bit 18 */
    "Reserved",                                                /* Bit 19 */
    "Reserved",                                                /* Bit 20 */
    "Reserved",                                                /* Bit 21 */
    "Reserved",                                                /* Bit 22 */
    "Reserved",                                                /* Bit 23 */
    "PIO command overrun",                                     /* Bit 24 */
    "PIO data overrun",                                        /* Bit 25 */
    "Probe overrun",                                           /* Bit 26 */
    "Probe underrun",                                          /* Bit 27 */
    "Reserved",                                                /* Bit 28 */
    "Reserved",                                                /* Bit 29 */
    "Reserved",                                                /* Bit 30 */
    "Reserved",                                                /* Bit 31 */
    "Hose 0 PCA reported an Uncorrectable Error",              /* Bit 32 */
    "Hose 0 Far End Mini-Link reported a UCE",                 /* Bit 33 */
    "Hose 0 Near End Mini-Link reported a UCE",                /* Bit 34 */
    "Reserved",                                                /* Bit 35 */
    "Hose 0 PCA reported a Fault",                             /* Bit 36 */
    "Hose 0 Far End Mini-Link reported a Fault",               /* Bit 37 */
    "Hose 0 Near End Mini-Link reported a Fault",              /* Bit 38 */
    "Reserved",                                                /* Bit 39 */
    "Hose 1 PCA reported an Uncorrectable Error",              /* Bit 40 */
    "Hose 1 Far End Mini-Link reported a UCE",                 /* Bit 41 */
    "Hose 1 Near End Mini-Link reported a UCE",                /* Bit 42 */
    "Reserved",                                                /* Bit 43 */
    "Hose 1 PCA reported a Fault",                             /* Bit 44 */
    "Hose 1 Far End Mini-Link reported a Fault",               /* Bit 45 */
    "Hose 1 Near End Mini-Link reported a Fault",              /* Bit 46 */
    "Reserved",                                                /* Bit 47 */
    "Hose 2 PCA reported an Uncorrectable Error",              /* Bit 48 */
    "Hose 2 Far End Mini-Link reported a UCE",                 /* Bit 49 */
    "Hose 2 Near End Mini-Link reported a UCE",                /* Bit 50 */
    "Reserved",                                                /* Bit 51 */
    "Hose 2 PCA reported a Fault",                             /* Bit 52 */
    "Hose 2 Far End Mini-Link reported a Fault",               /* Bit 53 */
    "Hose 2 Near End Mini-Link reported a Fault",              /* Bit 54 */
    "Reserved",                                                /* Bit 55 */
    "Hose 3 PCA reported an Uncorrectable Error",              /* Bit 56 */
    "Hose 3 Far End Mini-Link reported a UCE",                 /* Bit 57 */
    "Hose 3 Near End Mini-Link reported a UCE",                /* Bit 58 */
    "Reserved",                                                /* Bit 59 */
    "Hose 3 PCA reported a Fault",                             /* Bit 60 */
    "Hose 3 Far End Mini-Link reported a Fault",               /* Bit 61 */
    "Hose 3 Near End Mini-Link reported a Fault",              /* Bit 62 */
    "Reserved",                                                /* Bit 63 */
    NULL
};

static char *wf_iod_err_sum_strings[] = {
    "BIST in progress",
    "Write cache BIST failure",
    "Write cache parity error",
    "Reserved",
    "Reserved",
    "Read cache BIST failure",
    "Read cache parity error",
    "Reserved",
    "Hose 0 address checksum error",
    "Hose 1 address checksum error",
    "Hose 2 address checksum error",
    "Hose 3 address checksum error",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Correctable ECC error from system",
    "Uncorrectable ECC error from system",
    "Reserved",
    "Reserved",
    "Multiple correctable ECC errors from system",
    "Multiple uncorrectable ECC errors from system",
    "Reserved",
    "Reserved",
    "Syndrome for first correctable ECC error",
    "BIST in progress",
    "Write cache BIST failure",
    "Write cache parity error",
    "Reserved",
    "Reserved",
    "Read cache BIST failure",
    "Read cache parity error",
    "Reserved",
    "Hose 0 address checksum error",
    "Hose 1 address checksum error",
    "Hose 2 address checksum error",
    "Hose 3 address checksum error",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Correctable ECC error from system",
    "Uncorrectable ECC error from system",
    "Reserved",
    "Reserved",
    "Multiple correctable ECC errors from system",
    "Multiple uncorrectable ECC errors from system",
    "Reserved",
    "Reserved",
    "Syndrome for first correctable ECC error",
    NULL
};

/* PCA */
static char *wf_pca_whatami_strings[] = {
    "ASIC revision",                                           /* Bit 0  */
    "ASIC revision",                                           /* Bit 1  */
    "ASIC revision",                                           /* Bit 2  */
    "ASIC revision",                                           /* Bit 3  */
    "Backplane revision",                                      /* Bit 4  */
    "Backplane revision",                                      /* Bit 5  */
    "Backplane revision",                                      /* Bit 6  */
    "Backplane revision",                                      /* Bit 7  */
    "Backplane type",                                          /* Bit 8  */
    "Backplane type",                                          /* Bit 9  */
    "Backplane type",                                          /* Bit 10 */
    "Backplane type",                                          /* Bit 11 */
    "Backplane number",                                        /* Bit 12 */
    "Backplane number",                                        /* Bit 13 */
    "Backplane number",                                        /* Bit 14 */
    "Backplane number",                                        /* Bit 15 */
    "Backplane status",                                        /* Bit 16 */
    "Backplane status",                                        /* Bit 17 */
    "Backplane status",                                        /* Bit 18 */
    "Backplane status",                                        /* Bit 19 */
    "Backplane status",                                        /* Bit 20 */
    "Backplane status",                                        /* Bit 21 */
    "Backplane status",                                        /* Bit 22 */
    "Backplane status",                                        /* Bit 23 */
    "Hose number",                                             /* Bit 24 */
    "Hose number",                                             /* Bit 25 */
    "Hose number",                                             /* Bit 26 */
    "Microprocessor present",                                  /* Bit 27 */  
    "Reserved",                                                /* Bit 28 */
    "Reserved",                                                /* Bit 29 */
    "Reserved",                                                /* Bit 30 */
    "Reserved",                                                /* Bit 31 */
    "Reserved",                                                /* Bit 32 */
    "Reserved",                                                /* Bit 33 */
    "Reserved",                                                /* Bit 34 */
    "Reserved",                                                /* Bit 35 */
    "Reserved",                                                /* Bit 36 */
    "Reserved",                                                /* Bit 37 */
    "Reserved",                                                /* Bit 38 */
    "Reserved",                                                /* Bit 39 */
    "Reserved",                                                /* Bit 40 */
    "Reserved",                                                /* Bit 41 */
    "Reserved",                                                /* Bit 42 */
    "Reserved",                                                /* Bit 43 */
    "Reserved",                                                /* Bit 44 */
    "Reserved",                                                /* Bit 45 */
    "Reserved",                                                /* Bit 46 */
    "Reserved",                                                /* Bit 47 */
    "Reserved",                                                /* Bit 48 */
    "Reserved",                                                /* Bit 49 */
    "Reserved",                                                /* Bit 50 */
    "Reserved",                                                /* Bit 51 */
    "Reserved",                                                /* Bit 52 */
    "Reserved",                                                /* Bit 53 */
    "Reserved",                                                /* Bit 54 */
    "Reserved",                                                /* Bit 55 */
    "Reserved",                                                /* Bit 56 */
    "Reserved",                                                /* Bit 57 */
    "Reserved",                                                /* Bit 58 */
    "Reserved",                                                /* Bit 59 */
    "Reserved",                                                /* Bit 60 */
    "Reserved",                                                /* Bit 61 */
    "Reserved",                                                /* Bit 62 */
    "Reserved",                                                /* Bit 63 */
    NULL
};

static char *wf_pca_err_sum_strings[] = { 
    "32-bit write data parity error",                          /* Bit 0  */
    "32-bit address parity error",                             /* Bit 1  */
    "32-bit read data parity error",                           /* Bit 2  */
    "Reserved",                                                /* Bit 3  */
    "64-bit read data parity error",                           /* Bit 4  */
    "64-bit read data parity error",                           /* Bit 5  */
    "64-bit read data parity error",                           /* Bit 6  */
    "Invalid PTE",                                             /* Bit 7  */
    "Master abort was performed",                              /* Bit 8  */
    "Target abort was detected",                               /* Bit 9  */
    "PERR was detected",                                       /* Bit 10 */
    "Reserved",                                                /* Bit 11 */
    "SERR was detected",                                       /* Bit 12 */
    "TLB fill error",                                          /* Bit 13 */
    "Memory fill error",                                       /* Bit 14 */
    "PCI bus hung during Fault",                               /* Bit 15 */
    "32-bit write data parity error",                          /* Bit 16 */
    "32-bit address parity error",                             /* Bit 17 */
    "32-bit read data parity error",                           /* Bit 18 */
    "Reserved",                                                /* Bit 19 */
    "64-bit read data parity error",                           /* Bit 20 */
    "64-bit read data parity error",                           /* Bit 21 */
    "64-bit read data parity error",                           /* Bit 22 */
    "Invalid PTE",                                             /* Bit 23 */
    "Master abort was performed",                              /* Bit 24 */
    "Target abort was detected",                               /* Bit 25 */
    "PERR was detected",                                       /* Bit 26 */
    "Reserved",                                                /* Bit 27 */
    "SERR was detected",                                       /* Bit 28 */
    "TLB fill error",                                          /* Bit 29 */
    "Memory fill error",                                       /* Bit 30 */
    "PCI bus hung during Fault",                               /* Bit 31 */
    "Data checksum error on the port interface",               /* Bit 32 */
    "Address checksum error on the port interface",            /* Bit 33 */
    "Overflow error on the port interface",                    /* Bit 34 */
    "Error on the microprocessor interface",                   /* Bit 35 */
    NULL 
};

/* No strings associated with these */
static char *wf_ne_err_sum_strings[] = { NULL };
static char *wf_ne_whatami_strings[] = { NULL };
static char *wf_fe_err_sum_strings[] = { NULL };
static char *wf_fe_whatami_strings[] = { NULL };

static char *wf_pci_err_sum_strings[] = { 
    "32-bit write data parity error",                          /* Bit 0  */
    "32-bit address parity error",                             /* Bit 1  */
    "32-bit read data parity error",                           /* Bit 2  */
    "Reserved",                                                /* Bit 3  */
    "64-bit read data parity error",                           /* Bit 4  */
    "64-bit read data parity error",                           /* Bit 5  */
    "64-bit read data parity error",                           /* Bit 6  */
    "Invalid PTE",                                             /* Bit 7  */
    "Master abort was performed",                              /* Bit 8  */
    "Target abort was detected",                               /* Bit 9  */
    "PERR was detected",                                       /* Bit 10 */
    "Reserved",                                                /* Bit 11 */
    "SERR was detected",                                       /* Bit 12 */
    "TLB fill error",                                          /* Bit 13 */
    "Memory fill error",                                       /* Bit 14 */
    "PCI bus hung during Fault",                               /* Bit 15 */
    "Failing PCI command",                                     /* Bit 16 */
    "Failing PCI command",                                     /* Bit 17 */
    "Failing PCI command",                                     /* Bit 18 */
    "Failing PCI command",                                     /* Bit 19 */
    "DAC seend during failing command",                        /* Bit 20 */
    "Reserved",                                                /* Bit 21 */
    "Reserved",                                                /* Bit 22 */
    "Reserved",                                                /* Bit 23 */
    "PCI slot that was active during the failure",             /* Bit 24 */
    "PCI slot that was active during the failure",             /* Bit 25 */
    "PCI slot that was active during the failure",             /* Bit 26 */
    "PCA was PCI target when bus was hung",                    /* Bit 27 */
    "PCA was PCI initiator when bus was hung",                 /* Bit 28 */
    NULL 
};

/* These just report address at time of failure, therefore no text strings */
static char *wf_pci0_err_addr_strings[] = { NULL };
static char *wf_pci1_err_addr_strings[] = { NULL };

/* GP */
static char *wf_gpa_ext_ovfl_err_sum_strings[] = { 
    "GPLink Q2 overflow error",
    "GPLink QIO overflow error",
    "Q1 Table overflow error",
    "TTT FIFO overflow error",
    "TTT Blocked FIFO overflow error",
    "TTT Unblocked FIFO overflow error",
    "Q1 data buffer overflow error",
    NULL 
};

static char *wf_gpa_gpl_err_sum_strings[] = { 
    "GPLink failing GPD",
    "GPLink correctable error",
    "GPLink uncorrectable error",
    "GPLink NXM error",
    "GPLink overflow error",
    "GPLink command inconsistency error",
    "Performance monitor interrupt",
    NULL 
};

static char *wf_gpa_hsl_err_sum_strings[] = { 
    "HSLink failing GPD",
    "HSLink correctable error",
    "HSLink uncorrectable error",
    "HSLink command/address parity error",
    "HSLink overflow error",
    "HSLink command inconsistency error",
    NULL 
};

static char *wf_gpa_gpl_err_addr_0_strings[] = { 
    "Partial address 0",                                       /* Bit 0  */
    "Partial address 0",                                       /* Bit 1  */
    "Partial address 0",                                       /* Bit 2  */
    "Partial address 0",                                       /* Bit 3  */
    "Partial address 0",                                       /* Bit 4  */
    "Partial address 0",                                       /* Bit 5  */
    "Partial address 0",                                       /* Bit 6  */
    "Partial address 0",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_1_strings[] = { 
    "Partial address 1",                                       /* Bit 0  */
    "Partial address 1",                                       /* Bit 1  */
    "Partial address 1",                                       /* Bit 2  */
    "Partial address 1",                                       /* Bit 3  */
    "Partial address 1",                                       /* Bit 4  */
    "Partial address 1",                                       /* Bit 5  */
    "Partial address 1",                                       /* Bit 6  */
    "Partial address 1",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_2_strings[] = { 
    "Partial address 2",                                       /* Bit 0  */
    "Partial address 2",                                       /* Bit 1  */
    "Partial address 2",                                       /* Bit 2  */
    "Partial address 2",                                       /* Bit 3  */
    "Partial address 2",                                       /* Bit 4  */
    "Partial address 2",                                       /* Bit 5  */
    "Partial address 2",                                       /* Bit 6  */
    "Partial address 2",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_3_strings[] = { 
    "Partial address 3",                                       /* Bit 0  */
    "Partial address 3",                                       /* Bit 1  */
    "Partial address 3",                                       /* Bit 2  */
    "Partial address 3",                                       /* Bit 3  */
    "Partial address 3",                                       /* Bit 4  */
    "Partial address 3",                                       /* Bit 5  */
    "Partial address 3",                                       /* Bit 6  */
    "Partial address 3",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_4_strings[] = { 
    "Command",                                                 /* Bit 0  */
    "Command",                                                 /* Bit 1  */
    "Command",                                                 /* Bit 2  */
    "Command",                                                 /* Bit 3  */
    "Command",                                                 /* Bit 4  */
    "Command",                                                 /* Bit 5  */
    "Command",                                                 /* Bit 6  */
    "Partial address 0",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_5_strings[] = { 
    "Source CID",                                              /* Bit 0  */
    "Source CID",                                              /* Bit 1  */
    "Source CID",                                              /* Bit 2  */
    "Source CID",                                              /* Bit 3  */
    "Source CID",                                              /* Bit 4  */
    "Source CID",                                              /* Bit 5  */
    NULL 
};

static char *wf_gpa_gpl_err_addr_6_strings[] = { 
    "Dirty CID",                                               /* Bit 0  */
    "Dirty CID",                                               /* Bit 1  */
    "Dirty CID",                                               /* Bit 2  */
    "Dirty CID",                                               /* Bit 3  */
    "Dirty CID",                                               /* Bit 4  */
    "Dirty CID",                                               /* Bit 5  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_0_strings[] = { 
    "Partial address 0",                                       /* Bit 0  */
    "Partial address 0",                                       /* Bit 1  */
    "Partial address 0",                                       /* Bit 2  */
    "Partial address 0",                                       /* Bit 3  */
    "Partial address 0",                                       /* Bit 4  */
    "Partial address 0",                                       /* Bit 5  */
    "Partial address 0",                                       /* Bit 6  */
    "Partial address 0",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_1_strings[] = { 
    "Partial address 1",                                       /* Bit 0  */
    "Partial address 1",                                       /* Bit 1  */
    "Partial address 1",                                       /* Bit 2  */
    "Partial address 1",                                       /* Bit 3  */
    "Partial address 1",                                       /* Bit 4  */
    "Partial address 1",                                       /* Bit 5  */
    "Partial address 1",                                       /* Bit 6  */
    "Partial address 1",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_2_strings[] = { 
    "Partial address 2",                                       /* Bit 0  */
    "Partial address 2",                                       /* Bit 1  */
    "Partial address 2",                                       /* Bit 2  */
    "Partial address 2",                                       /* Bit 3  */
    "Partial address 2",                                       /* Bit 4  */
    "Partial address 2",                                       /* Bit 5  */
    "Partial address 2",                                       /* Bit 6  */
    "Partial address 2",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_3_strings[] = { 
    "Partial address 3",                                       /* Bit 0  */
    "Partial address 3",                                       /* Bit 1  */
    "Partial address 3",                                       /* Bit 2  */
    "Partial address 3",                                       /* Bit 3  */
    "Partial address 3",                                       /* Bit 4  */
    "Partial address 3",                                       /* Bit 5  */
    "Partial address 3",                                       /* Bit 6  */
    "Partial address 3",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_4_strings[] = { 
    "Command",                                                 /* Bit 0  */
    "Command",                                                 /* Bit 1  */
    "Command",                                                 /* Bit 2  */
    "Command",                                                 /* Bit 3  */
    "Command",                                                 /* Bit 4  */
    "Command",                                                 /* Bit 5  */
    "Command",                                                 /* Bit 6  */
    "Partial address 0",                                       /* Bit 7  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_5_strings[] = { 
    "Source CID",                                              /* Bit 0  */
    "Source CID",                                              /* Bit 1  */
    "Source CID",                                              /* Bit 2  */
    "Source CID",                                              /* Bit 3  */
    "Source CID",                                              /* Bit 4  */
    "Source CID",                                              /* Bit 5  */
    NULL 
};

static char *wf_gpa_hsl_err_addr_6_strings[] = { 
    "Dirty CID",                                               /* Bit 0  */
    "Dirty CID",                                               /* Bit 1  */
    "Dirty CID",                                               /* Bit 2  */
    "Dirty CID",                                               /* Bit 3  */
    "Dirty CID",                                               /* Bit 4  */
    "Dirty CID",                                               /* Bit 5  */
    NULL 
};

static char *wf_gpd_gpl_err_sum_strings[] = { 
    "Correctable error",                                       /* Bit 0  */
    "Multiple correctable errors",                             /* Bit 1  */
    "Uncorrectable error",                                     /* Bit 2  */
    "Multiple uncorrectable errors",                           /* Bit 3  */
    "Quadword in error",                                       /* Bit 4  */
    "Quadword in error",                                       /* Bit 5  */
    "Quadword in error",                                       /* Bit 6  */
    "Reserved",                                                /* Bit 7  */
    "Syndrome",                                                /* Bit 8  */
    "Syndrome",                                                /* Bit 9  */
    "Syndrome",                                                /* Bit 10 */
    "Syndrome",                                                /* Bit 11 */
    "Syndrome",                                                /* Bit 12 */
    "Syndrome",                                                /* Bit 13 */
    "Syndrome",                                                /* Bit 14 */
    "Syndrome",                                                /* Bit 15 */
    "Reserved",                                                /* Bit 16 */
    "Reserved",                                                /* Bit 17 */
    "Reserved",                                                /* Bit 18 */
    "Reserved",                                                /* Bit 19 */
    "Reserved",                                                /* Bit 20 */
    "Reserved",                                                /* Bit 21 */
    "Reserved",                                                /* Bit 22 */
    "Reserved",                                                /* Bit 23 */
    "Reserved",                                                /* Bit 24 */
    "Reserved",                                                /* Bit 25 */
    "Reserved",                                                /* Bit 26 */
    "Reserved",                                                /* Bit 27 */
    "Reserved",                                                /* Bit 28 */
    "Reserved",                                                /* Bit 29 */
    "Reserved",                                                /* Bit 30 */
    "Reserved",                                                /* Bit 31 */
    "Correctable error",                                       /* Bit 32 */
    "Multiple correctable errors",                             /* Bit 33 */
    "Uncorrectable error",                                     /* Bit 34 */
    "Multiple uncorrectable errors",                           /* Bit 35 */
    "Quadword in error",                                       /* Bit 36 */
    "Quadword in error",                                       /* Bit 37 */
    "Quadword in error",                                       /* Bit 38 */
    "Reserved",                                                /* Bit 39 */
    "Syndrome",                                                /* Bit 40 */
    "Syndrome",                                                /* Bit 41 */
    "Syndrome",                                                /* Bit 42 */
    "Syndrome",                                                /* Bit 43 */
    "Syndrome",                                                /* Bit 44 */
    "Syndrome",                                                /* Bit 45 */
    "Syndrome",                                                /* Bit 46 */
    "Syndrome",                                                /* Bit 47 */
    "Reserved",                                                /* Bit 48 */
    "Reserved",                                                /* Bit 49 */
    "Reserved",                                                /* Bit 50 */
    "Reserved",                                                /* Bit 51 */
    "Reserved",                                                /* Bit 52 */
    "Reserved",                                                /* Bit 53 */
    "Reserved",                                                /* Bit 54 */
    "Reserved",                                                /* Bit 55 */
    "Reserved",                                                /* Bit 56 */
    "Reserved",                                                /* Bit 57 */
    "Reserved",                                                /* Bit 58 */
    "Reserved",                                                /* Bit 59 */
    "Reserved",                                                /* Bit 60 */
    "Reserved",                                                /* Bit 61 */
    "Reserved",                                                /* Bit 62 */
    "Reserved",                                                /* Bit 63 */
    NULL
};

static char *wf_gpd_hsl_err_sum_strings[] = { 
    "Correctable error",                                       /* Bit 0  */
    "Multiple correctable errors",                             /* Bit 1  */
    "Uncorrectable error",                                     /* Bit 2  */
    "Multiple uncorrectable errors",                           /* Bit 3  */
    "Quadword in error",                                       /* Bit 4  */
    "Quadword in error",                                       /* Bit 5  */
    "Quadword in error",                                       /* Bit 6  */
    "I/O parity error",                                        /* Bit 7  */
    "Syndrome",                                                /* Bit 8  */
    "Syndrome",                                                /* Bit 9  */
    "Syndrome",                                                /* Bit 10 */
    "Syndrome",                                                /* Bit 11 */
    "Syndrome",                                                /* Bit 12 */
    "Syndrome",                                                /* Bit 13 */
    "Syndrome",                                                /* Bit 14 */
    "Syndrome",                                                /* Bit 15 */
    "Interrupt FIFO underflow",                                /* Bit 16 */
    "Interrupt FIFO overflow",                                 /* Bit 17 */
    "Reserved",                                                /* Bit 18 */
    "Reserved",                                                /* Bit 19 */
    "Reserved",                                                /* Bit 20 */
    "Reserved",                                                /* Bit 21 */
    "Reserved",                                                /* Bit 22 */
    "Reserved",                                                /* Bit 23 */
    "Reserved",                                                /* Bit 24 */
    "Reserved",                                                /* Bit 25 */
    "Reserved",                                                /* Bit 26 */
    "Reserved",                                                /* Bit 27 */
    "Reserved",                                                /* Bit 28 */
    "Reserved",                                                /* Bit 29 */
    "Reserved",                                                /* Bit 30 */
    "Reserved",                                                /* Bit 31 */
    "Correctable error",                                       /* Bit 32 */
    "Multiple correctable errors",                             /* Bit 33 */
    "Uncorrectable error",                                     /* Bit 34 */
    "Multiple uncorrectable errors",                           /* Bit 35 */
    "Quadword in error",                                       /* Bit 36 */
    "Quadword in error",                                       /* Bit 37 */
    "Quadword in error",                                       /* Bit 38 */
    "I/O parity error",                                        /* Bit 39 */
    "Syndrome",                                                /* Bit 40 */
    "Syndrome",                                                /* Bit 41 */
    "Syndrome",                                                /* Bit 42 */
    "Syndrome",                                                /* Bit 43 */
    "Syndrome",                                                /* Bit 44 */
    "Syndrome",                                                /* Bit 45 */
    "Syndrome",                                                /* Bit 46 */
    "Syndrome",                                                /* Bit 47 */
    "Interrupt FIFO underflow",                                /* Bit 48 */
    "Interrupt FIFO overflow",                                 /* Bit 49 */
    "Reserved",                                                /* Bit 50 */
    "Reserved",                                                /* Bit 51 */
    "Reserved",                                                /* Bit 52 */
    "Reserved",                                                /* Bit 53 */
    "Reserved",                                                /* Bit 54 */
    "Reserved",                                                /* Bit 55 */
    "Reserved",                                                /* Bit 56 */
    "Reserved",                                                /* Bit 57 */
    "Reserved",                                                /* Bit 58 */
    "Reserved",                                                /* Bit 59 */
    "Reserved",                                                /* Bit 60 */
    "Reserved",                                                /* Bit 61 */
    "Reserved",                                                /* Bit 62 */
    "Reserved",                                                /* Bit 63 */
    NULL 
};

/* HS */
static char *wf_hs_csr0_strings[] = {
    "HSA 0 error summary",                                     /* Bit 0  */
    "HSA 0 error summary",                                     /* Bit 1  */
    "HSA 0 error summary",                                     /* Bit 2  */
    "HSA 0 error summary",                                     /* Bit 3  */
    "HSA 0 error summary",                                     /* Bit 4  */
    "HSA 0 error summary",                                     /* Bit 5  */
    "HSA 0 error summary",                                     /* Bit 6  */
    "HSA 0 error summary",                                     /* Bit 7  */
    "HSA 0 address parity error",                              /* Bit 8  */
    "HSA 0 overflow error",                                    /* Bit 9  */
    "Reserved",                                                /* Bit 10 */
    "Reserved",                                                /* Bit 11 */
    "HSA 0 chip revision",                                     /* Bit 12 */
    "HSA 0 chip revision",                                     /* Bit 13 */
    "HSA 0 chip revision",                                     /* Bit 14 */
    "HSA 0 chip revision",                                     /* Bit 15 */
    "HSD 0 chip revision",                                     /* Bit 16 */
    "HSD 0 chip revision",                                     /* Bit 17 */
    "HSD 0 chip revision",                                     /* Bit 18 */
    "HSD 0 chip revision",                                     /* Bit 19 */
    "QW0 data parity error summary",                           /* Bit 20 */
    "QW0 data parity error summary",                           /* Bit 21 */
    "QW0 data parity error summary",                           /* Bit 22 */
    "QW0 data parity error summary",                           /* Bit 23 */
    "QW0 data parity error summary",                           /* Bit 24 */
    "QW0 data parity error summary",                           /* Bit 25 */
    "QW0 data parity error summary",                           /* Bit 26 */
    "QW0 data parity error summary",                           /* Bit 27 */
    "Force QW0 data parity error",                             /* Bit 28 */
    "Enable QW0 data parity checking",                         /* Bit 29 */
    "Enable HSA 0 error checking",                             /* Bit 30 */
    "Enable HSD 0 to drive fault",                             /* Bit 31 */
    "HSA 1 error summary",                                     /* Bit 32 */
    "HSA 1 error summary",                                     /* Bit 33 */
    "HSA 1 error summary",                                     /* Bit 34 */
    "HSA 1 error summary",                                     /* Bit 35 */
    "HSA 1 error summary",                                     /* Bit 36 */
    "HSA 1 error summary",                                     /* Bit 37 */
    "HSA 1 error summary",                                     /* Bit 38 */
    "HSA 1 error summary",                                     /* Bit 39 */
    "HSA 1 address parity error",                              /* Bit 40 */
    "HSA 1 overflow error",                                    /* Bit 41 */
    "Reserved",                                                /* Bit 42 */
    "Reserved",                                                /* Bit 43 */
    "HSA 1 chip revision",                                     /* Bit 44 */
    "HSA 1 chip revision",                                     /* Bit 45 */
    "HSA 1 chip revision",                                     /* Bit 46 */
    "HSA 1 chip revision",                                     /* Bit 47 */
    "HSD 2 chip revision",                                     /* Bit 48 */
    "HSD 2 chip revision",                                     /* Bit 49 */
    "HSD 2 chip revision",                                     /* Bit 50 */
    "HSD 2 chip revision",                                     /* Bit 51 */
    "Command inconsistency error summary",                     /* Bit 52 */
    "Command inconsistency error summary",                     /* Bit 53 */
    "Command inconsistency error summary",                     /* Bit 54 */
    "Command inconsistency error summary",                     /* Bit 55 */
    "Command inconsistency error summary",                     /* Bit 56 */
    "Command inconsistency error summary",                     /* Bit 57 */
    "Command inconsistency error summary",                     /* Bit 58 */
    "Command inconsistency error summary",                     /* Bit 59 */
    "Reserved",                                                /* Bit 60 */
    "Reserved",                                                /* Bit 61 */
    "Enable HSA 1 error checking",                             /* Bit 62 */
    "Enable HSD 2 to drive fault",                             /* Bit 63 */
    NULL
};


/* MEM */
static char *wf_mem_err_sum_strings[] = {
    "Correctable read error pointer",				/* Bit 0 */
    "Correctable read error pointer",				/* Bit 1 */
    "Reserved",			                                /* Bit 2 */
    "Correctable read error count",		                /* Bit 3 */
    "Correctable read error count",		                /* Bit 4 */
    "Uncorrectable read error",			                /* Bit 5 */
    "Correctable read error",				        /* Bit 6 */
    "Missed correctable read error",			        /* Bit 7 */
    "Correctable write error pointer",			        /* Bit 8 */
    "Correctable write error pointer",			        /* Bit 9 */
    "Reserved",			                                /* Bit 10 */
    "Correctable write error count",				/* Bit 11 */
    "Correctable write error count",				/* Bit 12 */
    "Uncorrectable write error",				/* Bit 13 */
    "Correctable write error",             			/* Bit 14 */
    "Missed correctable write error",             		/* Bit 15 */
    "Missed uncorrectable read error",             		/* Bit 16 */
    "Missed uncorrectable write error",             		/* Bit 17 */
    "DIMM error",             		                        /* Bit 18 */
    "MPDs out of sync error",             		        /* Bit 19 */
    "CSR read error (shadow mismatch)",             		/* Bit 20 */
    "CSR which caused the above error",             		/* Bit 21 */
    "MPD asymmetry error",             		                /* Bit 22 */
    "MPD configuration error", 		                        /* Bit 23 */
    "Not a power of 2 rank configuration error",             	/* Bit 24 */
    "Non-existent rank configuration error",             	/* Bit 25 */
    "RAM access violation error",             		        /* Bit 26 */
    "Refresh missing error",            		        /* Bit 27 */
    NULL
};

/* May not do these... not sure */
static char *wf_mem_rd_ce_trap0_strings[] = {
    NULL };
static char *wf_mem_rd_ce_trap1_strings[] = {
    NULL };
static char *wf_mem_rd_ce_trap2_strings[] = {
    NULL };
static char *wf_mem_rd_ce_trap3_strings[] = {
    NULL };
static char *wf_mem_rd_uce_trap_strings[] = {
    NULL };
static char *wf_mem_wt_ce_trap0_strings[] = {
    NULL };
static char *wf_mem_wt_ce_trap1_strings[] = {
    NULL };
static char *wf_mem_wt_ce_trap2_strings[] = {
    NULL };
static char *wf_mem_wt_ce_trap3_strings[] = {
    NULL };
static char *wf_mem_wt_uce_trap_strings[] = {
    NULL };



/* DTag */
static char *wf_dtag_control_strings[] = {
    "Enable fault",				        /* Bit 0 */
    "Force parity error",				/* Bit 1 */
    "Summary of parity errors in DTag RAM blocks",      /* Bit 2 */
    "Summary of parity errors in DTag RAM blocks",      /* Bit 3 */
    "Summary of parity errors in DTag RAM blocks",      /* Bit 4 */
    "Summary of parity errors in DTag RAM blocks",      /* Bit 5 */
    "Second parity error",                              /* Bit 6 */
    "Start BIST",                                       /* Bit 7 */
    NULL
};

static char *wf_dtag_err_sum_strings[] = {
    "BIST error summary",                               /* Bit 0 */
    "BIST error summary",                               /* Bit 1 */
    "BIST error summary",                               /* Bit 2 */
    "BIST error summary",                               /* Bit 3 */
    "Write FIFO overflow error",                        /* Bit 4 */
    "Command inconsistency error",                      /* Bit 5 */
    "Non-existent memory error",                        /* Bit 6 */
    "BIST done",                                        /* Bit 7 */
    NULL
};

static char *wf_dtag_err_cid_strings[] = {
    "Commander ID",                                     /* Bit 0 */
    "Commander ID",                                     /* Bit 1 */
    "Commander ID",                                     /* Bit 2 */
    "Commander ID",                                     /* Bit 3 */
    "Commander ID",                                     /* Bit 4 */
    "Commander ID",                                     /* Bit 5 */
    NULL
};

static char *wf_dtag_err_cmd_strings[] = {
    "Command",                                          /* Bit 0 */
    "Command",                                          /* Bit 1 */
    "Command",                                          /* Bit 2 */
    "Command",                                          /* Bit 3 */
    "Command",                                          /* Bit 4 */
    "Command",                                          /* Bit 5 */
    "Command",                                          /* Bit 6 */
    NULL
};

static char *wf_dtag_err_addr0_strings[] = {
    "Partial Address 0",                                /* Bit 0 */
    "Partial Address 0",                                /* Bit 1 */
    "Partial Address 0",                                /* Bit 2 */
    "Partial Address 0",                                /* Bit 3 */
    "Partial Address 0",                                /* Bit 4 */
    "Partial Address 0",                                /* Bit 5 */
    "Partial Address 0",                                /* Bit 6 */
    "Partial Address 0",                                /* Bit 7 */
    NULL
};

static char *wf_dtag_err_addr1_strings[] = {
    "Partial Address 1",                                /* Bit 0 */
    "Partial Address 1",                                /* Bit 1 */
    "Partial Address 1",                                /* Bit 2 */
    "Partial Address 1",                                /* Bit 3 */
    "Partial Address 1",                                /* Bit 4 */
    "Partial Address 1",                                /* Bit 5 */
    "Partial Address 1",                                /* Bit 6 */
    "Partial Address 1",                                /* Bit 7 */
    NULL
};

static char *wf_dtag_err_addr2_strings[] = {
    "Partial Address 2",                                /* Bit 0 */
    "Partial Address 2",                                /* Bit 1 */
    "Partial Address 2",                                /* Bit 2 */
    "Partial Address 2",                                /* Bit 3 */
    "Partial Address 2",                                /* Bit 4 */
    "Partial Address 2",                                /* Bit 5 */
    "Partial Address 2",                                /* Bit 6 */
    "Partial Address 2",                                /* Bit 7 */
    NULL
};

static char *wf_dtag_err_addr3_strings[] = {
    "Partial Address 3",                                /* Bit 0 */
    "Partial Address 3",                                /* Bit 1 */
    "Partial Address 3",                                /* Bit 2 */
    "Partial Address 3",                                /* Bit 3 */
    "Partial Address 3",                                /* Bit 4 */
    "Partial Address 3",                                /* Bit 5 */
    "Partial Address 3",                                /* Bit 6 */
    "Partial Address 3",                                /* Bit 7 */
    NULL
};

static char *wf_dtag_ecc_control_strings[] = {
    "SBE detected in DTag RAM sub_block",               /* Bit 0 */
    "SBE detected in DTag RAM sub_block",               /* Bit 1 */
    "SBE detected in DTag RAM sub_block",               /* Bit 2 */
    "SBE detected in DTag RAM sub_block",               /* Bit 3 */
    "A second SBE detected after one logged",           /* Bit 4 */
    "Enable SBE interrupts",                            /* Bit 5 */
    "Enable ECC on DTag RAMs",                          /* Bit 6 */
    "Force an SBE",                                     /* Bit 7 */
    NULL
};

static char *wf_dtag_ecc_syndrome_strings[] = {
    "ECC syndrome value",                               /* Bit 0 */
    "ECC syndrome value",                               /* Bit 1 */
    "ECC syndrome value",                               /* Bit 2 */
    "ECC syndrome value",                               /* Bit 3 */
    "ECC syndrome value",                               /* Bit 4 */
    "ECC syndrome value",                               /* Bit 5 */
    "ECC syndrome value",                               /* Bit 6 */
    NULL
};

/*
 * If WildFire ever has diff. family members,
 * these macros will be useful.
 */
#define MEMBER_ID_SHIFT 10
#define MEMBER_ID 0xfc00L

/*
 * Server Management definitions 
 */

#define	WF_DUAL_PORT_RAM_ADDR			0x0cafebeefL

struct wfcpu_info {
	struct hal_rad	*hal_radp;
	int		present;
	int		assigned_intrs;
	int		cache_size;
	int		rev;
};

/*
 * wfcpu.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since wfcpu.h, wfqbb.h, & wfpci.h may be included in
 *	 one .c file, their definitions must not collide.
 */

extern	u_int	wfcpu_developer_debug;

/* To remove/add all debug printfs */
#define __WFCPUDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * wfcpu_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	WFCPUD_INOUT	0x00000001	/* routine entry and exit 	*/
#define WFCPUD_CPU	0x00000010	/* CPU-related info		*/
#define WFCPUD_NUMA	0x00000020	/* NUMA-related info		*/
#define WFCPUD_DMAINFO	0x00000100	/* system-level dma settings	*/
#define WFCPUD_QBBCONF	0x00001000	/* QBB config info		*/
#define WFCPUD_ERRLOG	0x00080000	/* Error-logging info		*/
#define WFCPUD_CE	0x00010000
#define WFCPUD_UCE	0x00020000
#define WFCPUD_SYSEVT	0x00040000
					/* VM memory troller		    */
#define WFCPUD_VMMT	0x00100000	/* don't supress HSL/GPL parsing    */
#define WFCPUD_VMMT1	0x00200000	/* don't suppress 660 mchk printf's */

/* New, testing hw-support debug printfs				*/
#define WFCPUD_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _WFCPUinout;
extern char * _WFCPUnuma;
extern char * _WFCPUcpu;
extern char * _WFCPUdmainfo;
extern char * _WFCPUqbbconf;
extern char * _WFCPUerrlog;
extern char * _WFCPUce;
extern char * _WFCPUuce;
extern char * _WFCPUnot_yet;


/*
 * printf expansion that WFCPUPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _WFCPUxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __WFCPUDEBUG
#   define _WFCPUD_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_INOUT )  {	\
	    /* VARARGS */			\
            printf (_WFCPUinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
         if( wfcpu_developer_debug & WFCPUD_NUMA ) {	\
	    /* VARARGS */			\
            printf (_WFCPUnuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_CPU(X)			\
    {						\
	/* NOSTRICT */				\
         if( wfcpu_developer_debug & WFCPUD_CPU ) {	\
	    /* VARARGS */			\
            printf (_WFCPUcpu); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_DMAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_DMAINFO)  {	\
	    /* VARARGS */			\
            printf (_WFCPUdmainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_QBBCONF(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_QBBCONF)  {	\
	    /* VARARGS */			\
            printf (_WFCPUqbbconf); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_ERRLOG(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_ERRLOG)  {	\
	    /* VARARGS */			\
            printf (_WFCPUerrlog); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_CE(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_CE)  {	\
	    /* VARARGS */			\
            printf (_WFCPUce); 		        \
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_UCE(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_UCE)  {	\
	    /* VARARGS */			\
            printf (_WFCPUuce); 		        \
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFCPUD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfcpu_developer_debug & WFCPUD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_WFCPUnotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * wfcpu_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * WFCPUD_INOUT | WFCPUD_CPU
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define WFCPUPRINTF(F, X)	_##F(X)

#else  /* !__WFCPUDEBUG */
#   define WFCPUPRINTF(F, X)
#endif /* __WFCPUDEBUG */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif	/* __ARCH_ALPHA_HAL_WFCPU_H__ */

