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
 * @(#)$RCSfile: granite.h,v $ $Revision: 1.1.5.5 $ (DEC) $Date: 2002/03/26 19:13:16 $
 */
#ifndef __ARCH_ALPHA_HAL_GRANITE_H
#define __ARCH_ALPHA_HAL_GRANITE_H
/*
 * Definitions for debugging
 */
#define GRANITE_MODULE(mod) char *module = mod
#define GRANITE_PRINTF(msg) printf msg
#define GRANITE_DPRINTF(msg) if( _granite_debug ) dprintf msg

#define GRANITE_WARNING_TEMP            50
#define GRANITE_FATAL_TEMP              55
#define GRANITE_DOOR_TIME               5

/* bit defines for Server Management Information Register (SMIR) */
#define GRANITE_SMIR_MASK             	0xff
#define GRANITE_SMIR_SYS_NOT_RESET	0x80	/* bit 7  */
#define GRANITE_SMIR_PCI1_NOT_RESET	0x40	/* bit 6  */
#define GRANITE_SMIR_PCI0_NOT_RESET	0x20	/* bit 5  */
#define GRANITE_SMIR_TEMP_FAIL		0x10	/* bit 4  */
#define GRANITE_SMIR_TEMP_WARN		0x08	/* bit 3  */
#define GRANITE_SMIR_SYS_DC_FAIL      	0x04	/* bit 2  */
#define GRANITE_SMIR_RMC_HALT_OUT	0x02	/* bit 1  */
#define GRANITE_SMIR_SYS_PS_FAIL	0x01	/* bit 0  */

/* bit defines for Power Supply Information Register (PSIR) */
#define GRANITE_PSIR_FAIL_MASK        	0x70	/* bits 4-6 */
#define GRANITE_PSIR_ENABLE_MASK      	0x07	/* bits 0-2 */
#define GRANITE_PSIR_PS2_FAIL     	0x40	/* bit 6  */
#define GRANITE_PSIR_PS1_FAIL     	0x20	/* bit 5  */
#define GRANITE_PSIR_PS0_FAIL     	0x10	/* bit 4  */
#define GRANITE_PSIR_PS2_ENA     	0x04	/* bit 2  */
#define GRANITE_PSIR_PS1_ENA     	0x02	/* bit 1  */
#define GRANITE_PSIR_PS0_ENA          	0x01	/* bit 0  */

/* Fan Status Mask */
#define GRANITE_DPR_FAN_STATUS_MASK     (0xAA * TITAN_DPR_INDEX)

/*These Masks are for DPR index 0xAA*/
#define GRANITE_DPRMASK_FANS            0x1F /*bits 0-4 */
#define GRANITE_DPRMASK_SYS0_FAN_FAIL   0x01 /*bit 0*/
#define GRANITE_DPRMASK_SYS1_FAN_FAIL   0x02 /*bit 1*/
#define GRANITE_DPRMASK_CPU0_FAN_FAIL   0x04 /*bit 2*/
#define GRANITE_DPRMASK_CPU1_FAN_FAIL   0x08 /*bit 3*/
#define GRANITE_DPRMASK_PCI_FAN_FAIL    0x10 /*bit 4*/

/*Masks for envqw_4 */
#define GRANITE_PS_FAIL_MASK            0x00000F0407L  /* 19-16,10,2-0 */
#define GRANITE_PS_3_3V_TOLERANCE   	0x0000000001L   /* bit 0  */
#define GRANITE_PS_5V_TOLERANCE      	0x0000000002L   /* bit 1  */
#define GRANITE_PS_12V_TOLERANCE    	0x0000000004L   /* bit 2  */
#define GRANITE_PS_M12V_TOLERANCE       0x0000000400L   /* bit 10 */
#define GRANITE_CPU0_VCORE          	0x0000010000L   /* bit 16 */
#define GRANITE_CPU0_VIO          	0x0000020000L   /* bit 17 */
#define GRANITE_CPU1_VCORE          	0x0000040000L   /* bit 18 */
#define GRANITE_CPU1_VIO           	0x0000080000L   /* bit 19  */

#define GRANITE_PS_TEMP_FAIL            0x200000000000L  /* bit 45 */

#define GRANITE_FAN_FAIL_MASK           0x4000C000C0 /*bits 6-7, 22-23,38 */
#define GRANITE_FAN_FAIL_SYS0        	0x0000000040 /*bit 6*/
#define GRANITE_FAN_FAIL_SYS1        	0x0000000080 /*bit 7*/
#define GRANITE_FAN_FAIL_CPU0        	0x0000400000 /*bit 22*/
#define GRANITE_FAN_FAIL_CPU1        	0x0000800000 /*bit 23*/
#define GRANITE_FAN_FAIL_PCI           	0x4000000000 /*bit 38*/

/*masks for envqw_5 */
#define GRANITE_SYSTEM_DOOR_OPEN                0x0000000002L   /* bit 1  */
#define GRANITE_SYSTEM_DOOR_OPEN_WARNING        0x0000000004L   /* bit 2  */
#define GRANITE_SYSTEM_DOOR_CLOSE               0x0000000020L   /* bit 5  */

/*masks for envqw_6 */
#define GRANITE_SYSTEMP_MASK     	0x000000000000001FL  /*bits 0-4 */
#define GRANITE_SYSTEMP_CPU0   	  	0x0000000000000001L  /* bit 0 */
#define GRANITE_SYSTEMP_CPU1      	0x0000000000000002L  /* bit 1 */
#define GRANITE_SYSTEMP_ZONE_0 		0x0000000000000004L  /* bit 2 */
#define GRANITE_SYSTEMP_ZONE_1 		0x0000000000000008L  /* bit 3 */
#define GRANITE_SYSTEMP_ZONE_2 		0x0000000000000010L  /* bit 4 */

/*masks for envqw_7 */
#define GRANITE_FAN_CTL_FAULT_MASK     	0x03 /*bits 0-1*/

#define GRANITE_SYSFAN_0_CTL_FAULT  	0x01 /*bit 0*/
#define GRANITE_SYSFAN_1_CTL_FAULT 	0x02 /*bit 1*/

/*
 * Length of time it can take granite to power down
 */
#define TITAN_GRANITE_OS_POWERDOWN      60;

#endif
