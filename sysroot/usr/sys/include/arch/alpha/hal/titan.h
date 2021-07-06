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
 * @(#)$RCSfile: titan.h,v $ $Revision: 1.1.19.3 $ (DEC) $Date: 2002/01/28 21:48:36 $
 */

#ifndef __ARCH_ALPHA_HAL_TITAN_H
#define __ARCH_ALPHA_HAL_TITAN_H
#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

/*
 * Definitions for debugging
 */
#define TITAN_MODULE(mod) char *module = mod
#define TITAN_PRINTF(msg) printf msg
#define TITAN_DPRINTF(msg) if( _titan_developer_debug ) dprintf msg

/*
 * Structures and definitions for machine check/error path debugging
 */
#define TITAN_FORCE_CRD_DATA    0xdc40076543210000L
/* syndrome [63:56] 0xdc
   cmd	    [55:54] 0x4 DMA RMW
   source   [53:52]  "  GPCI (low 2 bits of 0x4, 0 for GPCI)
   resvd    [51:47] 0x0
   addr	    [46:15] 0x07654321
*/
/* definition for crd testing */
struct titan_crd {
    int hosenum;                        /* read-only member */
    int crd_count;                      /* modifiable */
    int iterations;                     /* read-only member */
    int loop_count;                     /* modifiable */
};

/*
 * Known members of the Titan family
 */
#define TITAN_MEMBER_PRIVATEER 1
#define TITAN_MEMBER_FALCON_E  2       /* Ericsson product */
#define TITAN_MEMBER_FALCON_S  3       /* Standard Falcon product */
#define TITAN_MEMBER_GRANITE   4

#define MEMBER_ID_SHIFT 10
#define MEMBER_ID 0xfc00L

#define	NEW_RPB_CACHESIZE	0xffffffff

/* bit defines for Server Management Control Register */
#define TITAN_SMCR_MASK                 0xbf
#define TITAN_SMCR_SOFT_PWRDN   	0x80

/* TBD - determine if these numbers are correct */
#define TITAN_MAX_PCI_SLOTS_PER_BUS 7
#define TITAN_MAX_INTR_PER_SLOT     4

/*
 * Per-cpu data structure for tracking machine check error handing
 */
struct titan_error_counters {	/* this is a copy of elr_error_counters, */
				/* so that errlog.h doesn't need to be   */
				/* included here. */
    char error_counters[96];
};

/*
 * A few defines used by the VM memory troller interface code.
 */
#define HI2LO_INT_SHIFT_32      32
#define LO2HI_INT_SHIFT_32      32
#define LOW_30_BITS             0x000000003fffffffUL
#define LOW_32_BITS             0x00000000ffffffffUL

#ifdef KERNEL
/* A per-cpu data structure for handling, tracking machine checks */
struct titan_mcheck_control {

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

    /* This next set of elements are used to describe the machine 	*/
    /* check frame, built by PAL, and used in error parsing.		*/
    struct titan_mchk_logout *mctl_pmchkf_va;	
				/* VA of PAL's mcheck logout area	*/
    u_long	mctl_pmchkf_pa;	/* PA ... 				*/
    u_long	mctl_pmchkf_len;/* size of logout area 			*/
    u_long	mctl_vector;	/* SCB Vector from PAL.			*/
    u_long	*mctl_regs;	/* ptr to registers saved by _XentInt	*/
				/* before calling machine check routine. */

    /* The next set of elements are used to maintain a running	*/
    /* count of error flags found set in the elr_soft_flags 	*/
    /* structure returned from each error parse. These values 	*/
    /* start at 0 at system boot time. 				*/
    struct titan_error_counters error_670_counters;
    struct titan_error_counters error_660_counters;
    struct titan_error_counters error_630_counters;
    struct titan_error_counters error_620_counters;

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
};
#endif

/*
 * Titan Machine Check Logout Frames
 */

/*
 * Machine Check Error Logout Frame Header
 */
#define TITAN_EL_MCHECK_HDR_RETRY 0x8000000000000000
#define TITAN_EL_MCHECK_HDR_DBL	  0x4000000000000000
struct el_titan_mcheck_hdr {
  u_int  frame_size;
  u_int  err_flags;
  u_int  cpu_area_offset;
  u_int  sys_area_offset;
  u_int  mcheck_code;
  u_int  mcheck_frame_rev;
};

/*
 * Machine Check System Specific Portion
 */
#define TITAN_DIR_CCHIP_ASYNC     0x8000000000000000
#define TITAN_DIR_P0_FATAL        0x4000000000000000
#define TITAN_DIR_P1_FATAL        0x2000000000000000
#define TITAN_MISC_SRC_MASK       0x00000000e0000000
#define TITAN_MISC_CPU0           0x0000000000000000
#define TITAN_MISC_CPU1           0x0000000020000000
#define TITAN_MISC_PCHIP0         0x0000000040000000
#define TITAN_MISC_PCHIP1         0x0000000050000000
#define TITAN_MISC_NXM            0x0000000010000000
#define TITAN_SERR_NXIO           0x8
#define TITAN_SERR_DOUBLE_BIT_ECC 0x2
#define TITAN_SERR_LOST_FATAL     0x1

#define TITAN_PERR_ADDR		  0x00007fffffffc000 	/* bits 46:14 */
#define TITAN_PERR_ADDR_MASK	  0x00000001ffffffff /* shifted down */
#define TITAN_PERR_ADDR_SHIFT	  14
#define TITAN_PERR_CMD_FIELD      0x00f0000000000000
#define TITAN_PERR_WRITE_MEM      0x0070000000000000
#define TITAN_PERR_WRITE_MEM_INV  0x00f0000000000000
#define TITAN_PERR_MWIN		  0x0001000000000000
#define TITAN_PERR_DAC		  0x0000800000000000
#define TITAN_PERR_P2P_WRITE      0x400
#define TITAN_PERR_P2P_READ       0x200
#define TITAN_PERR_NO_DEV_SEL     0x100
#define TITAN_PERR_DPE		  0x80
#define TITAN_PERR_TGT_ABORT      0x40
#define TITAN_PERR_ADDR_PARITY    0x20
#define TITAN_PERR_INVAL_SG_PTE   0x10
#define TITAN_PERR_DCRTO          0x8
#define TITAN_PERR_WRITE_DATA_PARITY 0x4
#define TITAN_PERR_SERR_ADDR      0x2

struct el_titan_mcheck_sys_data {
  u_long swerr_summary_flags;
  u_long cchip_dir;
  u_long cchip_misc;
  u_long p0_serror;
  u_long p0_gperror;
  u_long p0_aperror;
  u_long p0_agperror; /* Reserved on CPBB */
  u_long p1_serror;
  u_long p1_gperror;
  u_long p1_aperror;
  u_long p1_agperror;
};

/*
 * Bit encodings in the swerr_summary_flags
 */
#define TITAN_EL_MCHECK_PCHIP0	0x01
#define TITAN_EL_MCHECK_PCHIP1	0x02
#define TITAN_EL_MCHECK_MEMERR	0x04

/*
 * Correctable Error Logout Frame
 */
#define TITAN_EL_620_630_FRAME_SIZE  0xB0
#define TITAN_EL_620_630_CPU_OFFSET  0X18
#define TITAN_EL_620_630_SYS_OFFSET  0x58
#define TITAN_EL_620_630_MCHECK_REV  1
struct el_titan_620_630_logout_frame {
  struct el_titan_mcheck_hdr hdr;
  struct elf_common_ev6_corr_data procdata;
  struct el_titan_mcheck_sys_data sys_data;
};

/*
 * Uncorrectable Machine Check Error Logout Frame
 */
#define TITAN_EL_660_670_FRAME_SIZE  0xF8
#define TITAN_EL_660_670_CPU_OFFSET  0X18
#define TITAN_EL_660_670_SYS_OFFSET  0xA0
#define TITAN_EL_660_670_MCHECK_REV  1
struct el_titan_660_670_logout_frame {
  struct el_titan_mcheck_hdr hdr;
  struct elf_common_ev6_uncorr_data procdata;
  struct el_titan_mcheck_sys_data sys_data;
};

/*
 * Environmental Error Logout Frame
 */
#define TITAN_EL_680_FRAME_SIZE  0x70
#define TITAN_EL_680_CPU_OFFSET  0X18
#define TITAN_EL_680_SYS_OFFSET  0x18
#define TITAN_EL_680_MCHECK_CODE 0x206
#define TITAN_EL_680_MCHECK_REV  1
#define TITAN_EL_680_SMIR_WDT    0x100
#define TITAN_EL_680_VOLTAGE_SENSOR 0x01
#define TITAN_EL_680_THERMAL_SENSOR 0x02
#define TITAN_EL_680_SENSOR_TIMEOUT 0xde
#define TITAN_EL_680_FATAL_PWR_DN   0x40000
#define TITAN_EL_680_SHUTDOWN    0x1000000000000
struct el_titan_680_logout_frame {
  struct el_titan_mcheck_hdr hdr;
  u_long swerr_summary_flags;
  u_long cchip_dir;
  u_long tig_smir;
  u_long tig_cpuir;
  u_long tig_psir;
  u_long lmxx_isr;               /* power_warning_reg on Falcon */
  u_long sys_doors;              /* env_rsvd0 on Falcon */
  u_long sys_temp_warning;
  u_long sys_fan_control_fault;  /* env_rsvd1 on Falcon */
  u_long fatal_pwr_dn_codes;
  u_long env_rsvd0;              /* misc_sel_env on Falcon */
};

#define TITAN_EL_680_SEL_SENSOR_NUM_OFFSET  0xff0000
#define TITAN_EL_680_VOLTAGE_WARNING        0x0202
#define TITAN_EL_680_VOLTAGE_WARNING_OFFSET 0xff
#define TITAN_EL_680_THERMAL_WARNING        0x0102
#define TITAN_EL_680_THERMAL_WARNING_OFFSET 0xff


/* definitions needed for Termination packet */
#define	TITAN_EL_TERM_LNGTH	8
#define TITAN_EL_TERM_CLASS	0
#define	TITAN_EL_TERM_TYPE	0
#define	TITAN_EL_TERM_REV	1
struct el_titan_packet_hdr {
  short	packet_length;
  short	packet_class;
  short	packet_type;
  short packet_rev;
};

/* definitions needed for Throttle packet */
#define TITAN_EL_THROTTLE_LNGTH 24
#define TITAN_EL_THROTTLE_CLASS 9
#define	TITAN_EL_THROTTLE_TYPE	1
#define	TITAN_EL_THROTTLE_REV	2
#define TITAN_ALL_THROTTLE_OFF  0
#define TITAN_630_THROTTLE_ON   0x108
#define TITAN_620_THROTTLE_ON   0x100000010
struct el_titan_throttle_packet {
  struct el_titan_packet_hdr hdr;
  long cpuid;
  long mces;
};

/*
 * For DPR state capture
 */
#define	TITAN_EL_BLKMEM_LNGTH	0x10
#define TITAN_EL_BLKMEM_CLASS   12
#define	TITAN_EL_BLKMEM_TYPE	4
#define	TITAN_EL_BLKMEM_REV	1
struct el_titan_block_mem_packet {
  struct el_titan_packet_hdr hdr;
  u_char 	dpr80[8];
};

/*
 * Pchip Extended Common Titan System Packet 
 */
#define TITAN_EL_PCHIP_LNGTH   0x110
#define TITAN_EL_PCHIP_CLASS   12
#define TITAN_EL_PCHIP0_TYPE   8
#define TITAN_EL_PCHIP1_TYPE   9
#define TITAN_EL_PCHIP_REV     1
#define TITAN_SCTL_ECC_ENABLED 0x400
struct el_titan_pchip_packet {
  struct el_titan_packet_hdr hdr;
  u_long	sctl;
  u_long	serren;
  /* Aport */
  u_long	apctl;
  u_long	aperren;
  u_long	agperren;
  u_long	asprst;
  u_long	awsba0;
  u_long	awsba1;
  u_long	awsba2;
  u_long	awsba3;
  u_long	awsm0;
  u_long	awsm1;
  u_long	awsm2;
  u_long	awsm3;
  u_long	atba0;
  u_long	atba1;
  u_long	atba2;
  u_long	atba3;
  /* Gport */
  u_long	gpctl;
  u_long	gperren;
  u_long	gsprst;
  u_long	gwsba0;
  u_long	gwsba1;
  u_long	gwsba2;
  u_long	gwsba3;
  u_long	gwsm0;
  u_long	gwsm1;
  u_long	gwsm2;
  u_long	gwsm3;
  u_long	gtba0;
  u_long	gtba1;
  u_long	gtba2;
  u_long	gtba3;
};

/*
 * Extended Common Titan Memory Packet 
 */
#define TITAN_EL_MEM_LNGTH  0x58
#define TITAN_EL_MEM_CLASS  12
#define TITAN_EL_MEM_TYPE   10
#define TITAN_EL_MEM_REV    1
struct el_titan_mem_packet {
  struct el_titan_packet_hdr hdr;
  u_long aar0;
  u_long aar1;
  u_long aar2;
  u_long aar3;
  u_long p0_sctl;
  u_long p0_gpctl;
  u_long p0_apctl;
  u_long p1_sctl;
  u_long p1_gpctl;
  u_long p1_apctl;
};

/*
 * Server Management Definitions specific to Titan platforms using DPR
 *
 *      Dual-Ported RAM Based Server Management
 */
#define TITAN_DPR_INDEX                         0x40
#define TITAN_DPR_SIZE                          0x100

/* Base Address of memory config info */
#define TITAN_DPR_MEM_CONFIG			(0x80 * TITAN_DPR_INDEX)


/* Power Supply Status */
#define	TITAN_DPR_PS_CPU_PRESENT		(0x90 * TITAN_DPR_INDEX)
#define	TITAN_DPR_PS_POK_BITS		        (0x91 * TITAN_DPR_INDEX)
#define	TITAN_DPR_PS_AC_INPUT    		(0x92 * TITAN_DPR_INDEX)

/* Temperature for CPUs */
#define	TITAN_DPR_CPU0_TEMP			(0x93 * TITAN_DPR_INDEX)
#define	TITAN_DPR_CPU1_TEMP			(0x94 * TITAN_DPR_INDEX)
#define	TITAN_DPR_CPU2_TEMP			(0x95 * TITAN_DPR_INDEX)
#define	TITAN_DPR_CPU3_TEMP			(0x96 * TITAN_DPR_INDEX)

/* Temperature for PCI Zones */
#define	TITAN_DPR_PCI_ZONE1_TEMP		(0x97 * TITAN_DPR_INDEX)
#define	TITAN_DPR_PCI_ZONE2_TEMP		(0x98 * TITAN_DPR_INDEX)
#define	TITAN_DPR_PCI_ZONE3_TEMP		(0x99 * TITAN_DPR_INDEX)

/* Raw Fan Speeds */
#define TITAN_DPR_FAN1_SPEED                    (0x9a * TITAN_DPR_INDEX)
#define TITAN_DPR_FAN2_SPEED                    (0x9b * TITAN_DPR_INDEX)
#define TITAN_DPR_FAN3_SPEED                    (0x9c * TITAN_DPR_INDEX)
#define TITAN_DPR_FAN4_SPEED                    (0x9d * TITAN_DPR_INDEX)
#define TITAN_DPR_FAN5_SPEED                    (0x9e * TITAN_DPR_INDEX)
#define TITAN_DPR_FAN6_SPEED                    (0x9f * TITAN_DPR_INDEX)



/* Per-Power Supply Detail */
#define TITAN_DPR_PS0_ID                        (0xdb * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_AC_INPUT                  (0xdc * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_INTERNAL_TEMP             (0xdd * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_INLET_TEMP                (0xde * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_3V_CURRENT                (0xe0 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_5V_CURRENT                (0xe1 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_12V_CURRENT               (0xe2 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS0_FAN_SPEED                 (0xd3 * TITAN_DPR_INDEX)

#define TITAN_DPR_PS1_ID                        (0xe4 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_AC_INPUT                  (0xe5 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_INTERNAL_TEMP             (0xe6 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_INLET_TEMP                (0xe7 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_3V_CURRENT                (0xe9 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_5V_CURRENT                (0xea * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_12V_CURRENT               (0xeb * TITAN_DPR_INDEX)
#define TITAN_DPR_PS1_FAN_SPEED                 (0xec * TITAN_DPR_INDEX)

#define TITAN_DPR_PS2_ID                        (0xed * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_AC_INPUT                  (0xee * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_INTERNAL_TEMP             (0xef * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_INLET_TEMP                (0xf0 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_3V_CURRENT                (0xf2 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_5V_CURRENT                (0xf3 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_12V_CURRENT               (0xf4 * TITAN_DPR_INDEX)
#define TITAN_DPR_PS2_FAN_SPEED                 (0xf5 * TITAN_DPR_INDEX)

#define TITAN_DPR_POWERDOWN			(0xf8 * TITAN_DPR_INDEX)

/*
 * Bit-Level Masks for Dual-Ported RAM Fields
 */

/* DPR Location 0x90 - Power Supply & CPU Present */
#define TITAN_DPRMASK_CPU_PRESENT		0xf0
#define TITAN_DPRMASK_CPU0_PRESENT		0x10
#define TITAN_DPRMASK_CPU1_PRESENT		0x20
#define TITAN_DPRMASK_CPU2_PRESENT		0x40
#define TITAN_DPRMASK_CPU3_PRESENT		0x80
#define TITAN_DPRMASK_PS_PRESENT		0x07
#define TITAN_DPRMASK_PS0_PRESENT		0x01
#define TITAN_DPRMASK_PS1_PRESENT		0x02
#define TITAN_DPRMASK_PS2_PRESENT		0x04

/* DPR Location 0x91 - Power Supply Info */
#define	TITAN_DPRMASK_PS_POK		        0xff
#define	TITAN_DPRMASK_PS0_POK		        0x01
#define	TITAN_DPRMASK_PS1_POK		        0x02
#define	TITAN_DPRMASK_PS2_POK		        0x04
#define	TITAN_DPRMASK_VTERM_POK		        0x08
#define TITAN_DPRMASK_CPU0_POK                  0x10
#define TITAN_DPRMASK_CPU1_POK                  0x20
#define TITAN_DPRMASK_CPU2_POK                  0x40
#define TITAN_DPRMASK_CPU3_POK                  0x80

/* DPR Location 0x92 - Power Supply AC Input */
#define TITAN_DPRMASK_PS_AC_INPUT               0x07
#define TITAN_DPRMASK_PS0_AC_INPUT              0x01
#define TITAN_DPRMASK_PS1_AC_INPUT              0x02
#define TITAN_DPRMASK_PS2_AC_INPUT              0x04

/* DPR Locations db:e3, e4:ec and ed:f5 - Per-Power Supply Detail */
#define TITAN_DPRMASK_PS_ID                     0x03
#define TITAN_DPRMASK_PS_THERMAL_SHUTDOWN       0x08

/*
 * AGP defines
 */
/* 
 * Titan Pchip AGP Rate values 
 */
#define TITAN_AGP_1X	       	0L
#define TITAN_AGP_2X	       	1L
#define TITAN_AGP_4X	       	2L

/* 
 * Titan Pchip Bit positions 
 */
#define TITAN_AGP_RATE_SHIFT    52
#define TITAN_AGP_HP_RD_SHIFT   58
#define TITAN_AGP_LP_RD_SHIFT   61

/*
 * The titan spec. recommends that both AGP_HP_RD and AGP_LP_RD be
 * set to 2.  However, These values are not related to the maximum
 * number of reads that can be outstanding in the PAchip.  These
 * values are also NOT related to the maximum queue depth on the 
 * AGP master/adapter, which should be set to 7 (representing 
 * queue slots 0 through 7) for titan.
 * note: ( AGP_LP_RD + AGP_HP_RD ) must be <= 14.
 */
#define TITAN_REC_AGP_HP_RD     2L
#define TITAN_REC_AGP_LP_RD     2L
#define TITAN_AGP_MASTER_RQ_MAX 7 /* The AGP spec has RQ depth offset
				   * -1 is status registers....
				   * a vaule of 7 = depth of 8 (0...7)
				   */

/* 
 * Titan Pchip Bit Masks 
 */
#define TITAN_AGP_PRESENT	0x0200000000000000
#define TITAN_SBA_EN       	0x0040000000000000
#define TITAN_AGP_EN            0x0080000000000000
#define TITAN_AGP_RATE_MASK	0x0030000000000000

/*
 * Function prototypes shared among Titan family platforms
 */
extern int  titan_init_platform(void);
extern int  titan_configure_platform(void);
extern void titan_init_secondary(void);
extern int  titan_get_info(register struct item_list *);
extern int  titan_memenable(void);
extern u_int titan_system_id(void);
extern int  titan_dump_dev(struct dump_request *);
extern int  titan_badaddr(vm_offset_t, int, struct bus_ctlr_common *);
extern int  titan_testpage(long);
extern int  titan_softerr_intr(long, char *, long *);
extern int  titan_harderr_intr(long, char *, long *);
extern int  titan_machcheck(long, char *, long *);
extern int  titan_log_throttle_event(uint, long);
extern void titan_do_670(volatile int *);
extern void titan_force_crd(struct titan_crd *);
extern int  titan_dpr_get_ps_status(long *);
extern int  titan_dpr_get_sys_temp(long *);
#endif /* __ARCH_ALPHA_HAL_TITAN_H */




