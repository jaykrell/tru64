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
 * @(#)$RCSfile: privateer.h,v $ $Revision: 1.1.8.1 $ (DEC) $Date: 2002/01/28 21:49:01 $
 */

#ifndef __ARCH_ALPHA_HAL_PRIVATEER_H
#define __ARCH_ALPHA_HAL_PRIVATEER_H
#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

/*
 * Definitions for debugging
 */
#define PRIVATEER_MODULE(mod) char *module = mod
#define PRIVATEER_PRINTF(msg) printf msg
#define PRIVATEER_DPRINTF(msg) if( _privateer_debug ) dprintf msg

/******************************************************
 * Server Management Definitions SPECIFIC TO Privateer.
 * See the PFMS spec for details on bit defines.
 ******************************************************/

/*
 * Length of time it can take privateer to power down
 */
#define TITAN_PRIVATEER_OS_POWERDOWN       60;

/* 
 * Define temperature operating threshold for 
 * environmental monitoring on Privateer.
 */
#define PRIVATEER_WARNING_TEMP	48
#define PRIVATEER_FATAL_TEMP	53

/* bit defines for Server Management Information Register (SMIR) */
#define PRIVATEER_SMIR_MASK             0xff
#define PRIVATEER_SMIR_SYS_NOT_RESET	0x80	/* bit 7  */
#define PRIVATEER_SMIR_PCI1_NOT_RESET	0x40	/* bit 6  */
#define PRIVATEER_SMIR_PCI0_NOT_RESET	0x20	/* bit 5  */
#define PRIVATEER_SMIR_TEMP_FAIL	0x10	/* bit 4  */
#define PRIVATEER_SMIR_TEMP_WARN	0x08	/* bit 3  */
#define PRIVATEER_SMIR_SYS_DC_FAIL      0x04	/* bit 2  */
#define PRIVATEER_SMIR_RMC_HALT_OUT	0x02	/* bit 1  */
#define PRIVATEER_SMIR_SYS_PS_FAIL	0x01	/* bit 0  */

/* bit defines for CPU Information Register (CPUIR) */
#define PRIVATEER_CPUIR_MASK            0xff
#define PRIVATEER_CPUIR_CPU_FAIL_MASK   0xf0
#define PRIVATEER_CPUIR_CPU3_REG_FAIL	0x80	/* bit 7  */
#define PRIVATEER_CPUIR_CPU2_REG_FAIL	0x40	/* bit 6  */
#define PRIVATEER_CPUIR_CPU1_REG_FAIL	0x20	/* bit 5  */
#define PRIVATEER_CPUIR_CPU0_REG_FAIL	0x10	/* bit 4  */
#define PRIVATEER_CPUIR_CPU3_REG_ENA    0x08	/* bit 3  */
#define PRIVATEER_CPUIR_CPU2_REG_ENA    0x04	/* bit 2  */
#define PRIVATEER_CPUIR_CPU1_REG_ENA    0x02	/* bit 1  */
#define PRIVATEER_CPUIR_CPU0_REG_ENA    0x01	/* bit 0  */

/* bit defines for Power Supply Information Register (PSIR) */
#define PRIVATEER_PSIR_FAIL_MASK        0x70	/* bits 4-6 */
#define PRIVATEER_PSIR_ENABLE_MASK      0x07	/* bits 0-2 */
#define PRIVATEER_PSIR_PS2_FAIL     	0x40	/* bit 6  */
#define PRIVATEER_PSIR_PS1_FAIL     	0x20	/* bit 5  */
#define PRIVATEER_PSIR_PS0_FAIL     	0x10	/* bit 4  */
#define PRIVATEER_PSIR_PS2_ENA     	0x04	/* bit 2  */
#define PRIVATEER_PSIR_PS1_ENA     	0x02	/* bit 1  */
#define PRIVATEER_PSIR_PS0_ENA          0x01	/* bit 0  */

/* bit defines for System_Power_Supply/Temp/Fan_Fault LM78_ISR */
#define PRIVATEER_LM78_MASK             0xdf00df04ffL
#define PRIVATEER_LM78_FAN_FAIL_MASK    0xc000c000c0L	/*bits 6:7,22:23,38:39*/
#define PRIVATEER_LM78_TEMP_ZONE_FAIL	0x1000100010L   /* bits 4,20,36 */
#define PRIVATEER_LM78_PS_FAIL_MASK     0x0f000f007fL	/* 35-32,19-16,2-0 */

#define PRIVATEER_LM78_AC_HIGH_WARN    	0x800000000000L	/* bits 47 */
#define PRIVATEER_LM78_AC_LOW_WARN    	0x400000000000L	/* bits 46 */
#define PRIVATEER_LM78_PS_TEMP_WARN    	0x200000000000L	/* bits 45 */
#define PRIVATEER_LM78_PS_12V_WARN    	0x100000000000L	/* bits 44 */
#define PRIVATEER_LM78_PS_5V_WARN    	0x80000000000L	/* bits 43 */
#define PRIVATEER_LM78_PS_3_3V_WARN    	0x40000000000L	/* bits 42 */
#define PRIVATEER_LM78_PS	    	0x30000000000L	/* bits 41-40 */
#define PRIVATEER_LM78_SYSFAN_6_FAIL    0x8000000000L   /* bit 39 */
#define PRIVATEER_LM78_SYSFAN_3_FAIL    0x4000000000L   /* bit 38 */
							/* bit 37 unused */
#define PRIVATEER_LM78_TEMP_ZONE_2_FAIL 0x1000000000L   /* bit 36 */
#define PRIVATEER_LM78_CPU3_VIO_1_5     0x0800000000L   /* bit 35 */
#define PRIVATEER_LM78_CPU3_VCORE_2     0x0400000000L   /* bit 34 */
#define PRIVATEER_LM78_CPU2_VIO_1_5     0x0200000000L   /* bit 33 */
#define PRIVATEER_LM78_CPU2_VCORE_2     0x0100000000L   /* bit 32 */
							/* bits 24-31 unused */
#define PRIVATEER_LM78_SYSFAN_5_FAIL    0x0000800000L   /* bit 23 */
#define PRIVATEER_LM78_SYSFAN_4_FAIL    0x0000400000L   /* bit 22 */
							/* bit 21 unused */
#define PRIVATEER_LM78_TEMP_ZONE_1_FAIL 0x0000100000L   /* bit 20 */
#define PRIVATEER_LM78_CPU1_VIO_1_5     0x0000080000L   /* bit 19 */
#define PRIVATEER_LM78_CPU1_VCORE_2     0x0000040000L   /* bit 18 */
#define PRIVATEER_LM78_CPU0_VIO_1_5     0x0000020000L   /* bit 17 */
#define PRIVATEER_LM78_CPU0_VCORE_2     0x0000010000L   /* bit 16 */
							/* bits 11-15 unused */
#define PRIVATEER_LM78_PS_M12V_TOLERANCE 0x0000000400L   /* bit 10 */
#define PRIVATEER_LM78_CTERM_TOLERANCE	0x0000000100L   /* bit 8  */
#define PRIVATEER_LM78_SYSFAN_2_FAIL    0x0000000080L   /* bit 7  */
#define PRIVATEER_LM78_SYSFAN_1_FAIL    0x0000000040L   /* bit 6  */
#define PRIVATEER_LM78_CPU_TEMP_FAIL    0x0000000020L   /* bit 5  */
#define PRIVATEER_LM78_TEMP_ZONE_0_FAIL 0x0000000010L   /* bit 4  */
#define PRIVATEER_LM78_VTERM_TOLERANCE  0x0000000008L   /* bit 3  */
#define PRIVATEER_LM78_PS_12V_TOLERANCE 0x0000000004L   /* bit 2  */
#define PRIVATEER_LM78_PS_5V_TOLERANCE  0x0000000002L	/* bit 1  */
#define PRIVATEER_LM78_PS_3_3V_TOLERANCE 0x0000000001L   /* bit 0  */

/* bit defines for Module Information Register (MIR) */
#define PRIVATEER_MIR_MASK		0xf8
#define PRIVATEER_MIR_CPU3_PRESENT	0x80		/* bit 7 */
#define PRIVATEER_MIR_CPU2_PRESENT	0x40		/* bit 6 */
#define PRIVATEER_MIR_CPU1_PRESENT	0x20		/* bit 5 */
#define PRIVATEER_MIR_CPU0_PRESENT	0x10		/* bit 4 */
							/* bit 3 unused */
#define PRIVATEER_MIR_PS2_PRESENT	0x04		/* bit 2 */
#define PRIVATEER_MIR_PS1_PRESENT	0x02		/* bit 1 */
#define PRIVATEER_MIR_PS0_PRESENT	0x01		/* bit 0 */

/* bit defines for System_Doors */
#define PRIVATEER_SYSDOORS_MASK		0xee		/* bits 1-3, 5-7 */
#define PRIVATEER_SYSDOORS_CLOSED_MASK	0xe0		/* bits 5-7 */
#define PRIVATEER_SYSDOORS_PCI_CL	0x80		/* bit 7 */
#define PRIVATEER_SYSDOORS_FAN_CL	0x40		/* bit 6 */
#define PRIVATEER_SYSDOORS_CPU_CL	0x20		/* bit 5 */
#define PRIVATEER_SYSDOORS_OPEN_MASK	0x0e		/* bits 1-3 */
#define PRIVATEER_SYSDOORS_PCI		0x08		/* bit 3 */
#define PRIVATEER_SYSDOORS_FAN		0x04		/* bit 2 */
#define PRIVATEER_SYSDOORS_CPU		0x02		/* bit 1 */

/* bit defines for System_Temperature_Warning */
#define PRIVATEER_SYSTEMP_MASK		0x77f
#define PRIVATEER_SYSTEMP_PS_2		0x400		/* bit 10 */
#define PRIVATEER_SYSTEMP_PS_1		0x200		/* bit 9 */
#define PRIVATEER_SYSTEMP_PS_0		0x100		/* bit 8 */
							/* bit 7 unused */
#define PRIVATEER_SYSTEMP_ZONE_2        0x040		/* bit 6 */
#define PRIVATEER_SYSTEMP_ZONE_1        0x020		/* bit 5 */
#define PRIVATEER_SYSTEMP_ZONE_0        0x010		/* bit 4 */
#define PRIVATEER_SYSTEMP_CPU3          0x008		/* bit 3 */
#define PRIVATEER_SYSTEMP_CPU2          0x004		/* bit 2 */
#define PRIVATEER_SYSTEMP_CPU1          0x002		/* bit 1 */
#define PRIVATEER_SYSTEMP_CPU0          0x001		/* bit 0 */

/* Fan Status Mask */
#define PRIVATEER_DPR_FAN_OK_MASK                   (0xaa * TITAN_DPR_INDEX)

/* DPR Location 0xaa - Fan Status Mask */
#define PRIVATEER_DPRMASK_FAN_OK                    0x3f
#define PRIVATEER_DPRMASK_FAN1_OK                   0x01
#define PRIVATEER_DPRMASK_FAN2_OK                   0x02
#define PRIVATEER_DPRMASK_FAN3_OK                   0x04
#define PRIVATEER_DPRMASK_FAN4_OK                   0x08
#define PRIVATEER_DPRMASK_FAN5_OK                   0x10
#define PRIVATEER_DPRMASK_FAN6_OK                   0x20

/* bit defines for System_Fan_Control_Fault */
#define PRIVATEER_SYSFAN_MASK           0xf3f
#define PRIVATEER_SYSFAN_CTL_FAULT	0x03f		/* bits 5:0 */
#define PRIVATEER_SYSFAN_PCI_REDUCE     0x800		/* bit 11 */
#define PRIVATEER_SYSFAN_PCI_MAX_SPIN   0x400		/* bit 10 */
#define PRIVATEER_SYSFAN_CPU_REDUCE     0x200		/* bit 9 */
#define PRIVATEER_SYSFAN_CPU_MAX_SPIN   0x100		/* bit 8 */
							/* bits 6-7 unused */
#define PRIVATEER_SYSFAN_6_CTL_FAULT    0x020		/* bit 5 */
#define PRIVATEER_SYSFAN_5_CTL_FAULT    0x010		/* bit 4 */
#define PRIVATEER_SYSFAN_4_CTL_FAULT    0x008		/* bit 3 */
#define PRIVATEER_SYSFAN_3_CTL_FAULT    0x004		/* bit 2 */
#define PRIVATEER_SYSFAN_2_CTL_FAULT    0x002		/* bit 1 */
#define PRIVATEER_SYSFAN_1_CTL_FAULT    0x001		/* bit 0 */

/* bit defines for Fatal_Power_Down_Codes */
#define PRIVATEER_PWR_DOWN_MASK		0xfeff07
#define PRIVATEER_CTERM_FAIL		0x800000	/* bit 23 */
#define PRIVATEER_SYSFAN_5_FAIL		0x400000	/* bit 22 */
#define PRIVATEER_CPU_DOOR_FAIL		0x200000	/* bit 21 */
#define PRIVATEER_TEMP_FAIL		0x100000	/* bit 20 */
#define PRIVATEER_LOAD_INITD_FAIL	0x080000	/* bit 19 */
#define PRIVATEER_INVALID_SROM		0x040000	/* bit 18 */
#define PRIVATEER_NO_CPU_SLOT_0		0x020000	/* bit 17 */
							/* bit 16 unused */
#define PRIVATEER_CPU3_REG_FAIL		0x008000	/* bit 15 */
#define PRIVATEER_CPU2_REG_FAIL		0x004000	/* bit 14 */
#define PRIVATEER_CPU1_REG_FAIL		0x002000	/* bit 13 */
#define PRIVATEER_CPU0_REG_FAIL		0x001000	/* bit 12 */
#define PRIVATEER_VTERM_FAIL		0x000800	/* bit 11 */
#define PRIVATEER_PS_2_DC_FAIL		0x000400	/* bit 10 */
#define PRIVATEER_PS_1_DC_FAIL		0x000200	/* bit 9 */
#define PRIVATEER_PS_0_DC_FAIL		0x000100	/* bit 8 */
							/* bits 3-7 unused */
#define PRIVATEER_PS_2_AC_FAIL		0x000004	/* bit 2 */
#define PRIVATEER_PS_1_AC_FAIL		0x000002	/* bit 1 */
#define PRIVATEER_PS_0_AC_FAIL		0x000001	/* bit 0 */

/* bit defines for Server Management Control Register (SMCR) */
#define PRIVATEER_SMCR_MASK		0xbf
#define PRIVATEER_SMCR_SOFT_PWRDN   	0x80
#define PRIVATEER_SMCR_RESERVED_1	0x40
#define PRIVATEER_SMCR_WATCH_BISC	0x20
#define PRIVATEER_SMCR_WATCH_ENA	0x10
#define PRIVATEER_SMCR_CPU3_PWRDN	0x08
#define PRIVATEER_SMCR_CPU2_PWRDN	0x04
#define PRIVATEER_SMCR_CPU1_PWRDN	0x02
#define PRIVATEER_SMCR_CPU0_PWRDN	0x01

/*
 * AGP defines
 */

/* AGP Rate values */
#define AGP_1X			0
#define AGP_2X			1
#define AGP_4X			2

/* Bit positions */
#define AGP_RATE_SHIFT          52
#define AGP_HP_RD               58
#define AGP_LP_RD               61

/* Bit Masks */
#define AGP_RATE_MASK		0x3
#define TITAN_AGP_PRESENT	0x0200000000000000

#define TITAN_SBA_EN		0x0040000000000000
#define TITAN_AGP_EN		0x0080000000000000

#endif /* __ARCH_ALPHA_HAL_PRIVATEER_H */
