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
 * @(#)$RCSfile: wfsrvmgmt.h,v $ $Revision: 1.1.6.6 $ (DEC) $Date: 2000/06/15 14:11:00 $
 */


#ifndef __ARCH_ALPHA_HAL_WFSRVMGMT_H__
#define __ARCH_ALPHA_HAL_WFSRVMGMT_H__

#define WFPCI_READ_SR_AND_INCREMENT(X) wfpci_read_sr(X++)

#define WF_EL_PSM_SYS_EVT_HDR_LNGTH  (sizeof(struct wf_psm_hpm_sysevt) + sizeof(struct entry_terminator))
#define WF_EL_PSM_SYS_EVT_HDR_CLASS  0x000A
#define WF_EL_PSM_SYS_EVT_HDR_TYPE   0x0030
#define WF_EL_PSM_SYS_EVT_HDR_REV    0x0001
  
#define WF_EL_HPM_SYS_EVT_HDR_LNGTH  (sizeof(struct wf_psm_hpm_sysevt) + sizeof(struct entry_terminator))
#define WF_EL_HPM_SYS_EVT_HDR_CLASS  0x000A
#define WF_EL_HPM_SYS_EVT_HDR_TYPE   0x0032
#define WF_EL_HPM_SYS_EVT_HDR_REV    0x0001
  
#define WF_EL_PBM_SYS_EVT_HDR_LNGTH  (sizeof(struct wf_pbm_sysevt) + sizeof(struct entry_terminator))
#define WF_EL_PBM_SYS_EVT_HDR_CLASS  0x000A
#define WF_EL_PBM_SYS_EVT_HDR_TYPE   0x0031
#define WF_EL_PBM_SYS_EVT_HDR_REV    0x0001  

#define WF_SR_TIMESTAMP       0xFCE0 /* Offset in Shared RAM to 8byte Timestamp */
#define WF_SR_VERSION         0xFC00 /* Offset in Shared RAM to 2byte Version field Maj/Min */

/* 
 * Bit defines for Power System Manager Status Register 0 (PSM_SR0)
 */
#define PSM_SR0_PS1_Vaux_OK         0x0001L       /* Power Supply 1 Vaux is okay */
#define PSM_SR0_PS1_48V_OK          0x0002L       /* Power Supply 1 +48V is okay */
#define PSM_SR0_PS2_Vaux_OK         0x0004L       /* Power Supply 2 Vaux is okay */
#define PSM_SR0_PS2_48V_OK          0x0008L       /* Power Supply 2 +48V is okay */
#define PSM_SR0_PS3_Vaux_OK         0x0010L       /* Power Supply 3 Vaux is okay */
#define PSM_SR0_PS3_48V_OK          0x0020L       /* Power Supply 3 +48V is okay */
/* RESERVED                 0x0040L   */
#define PSM_SR0_Service_Sw_Normal   0x0080L       /* Service switch in normal position */
/* RESERVED                 0x0100L   */
#define PSM_SR0_PS1_Temp_OK         0x0200L       /* Power Supply 1 temperature okay */
#define PSM_SR0_PS2_Temp_OK         0x0400L       /* Power Supply 2 temperature okay */
#define PSM_SR0_PS3_Temp_OK         0x0800L       /* Power Supply 3 temperature okay */
/* RESERVED                 0x1000L */
/* RESERVED                 0x2000L */
/* RESERVED                 0x4000L */
/* RESERVED                 0x8000L */

/* 
 * Bit defines for Power System Manager Status Register 1 (PSM_SR1) 
 */
#define GR_Clock_OK         0x0001L      /* GR clock is okay */
#define IO_Clock_OK         0x0002L      /* IO clock is okay */
#define LED_Power_DCOK      0x0004L      /* Yellow LED power (+5V) is okay */
#define PLL_DCOK            0x0008L      /* PLL DC is okay */
#define Main_P_3_3V_DCOK    0x0010L      /* Main +3.3V DC is okay */
#define Aux_P_3_3V_DCOK     0x0020L      /* Auxiliary +3.3V DC is okay */
#define P_1_5V_DCOK         0x0040L      /* +1.5V DC is okay */
#define P_2_5V_DCOK         0X0080L      /* +2.5V DC is okay */
#define CPU0_DCOK           0x0100L      /* CPU 0 DC is okay */
#define CPU1_DCOK           0x0200L      /* CPU 1 DC is okay */
#define CPU2_DCOK           0x0400L      /* CPU 2 DC is okay */
#define CPU3_DCOK           0x0800L      /* CPU 3 DC is okay */
#define IOR0_DCOK           0x1000L      /* IOR 0 DC is okay */
#define IOR1_DCOK           0x2000L      /* IOR 1 DC is okay */
#define IOR2_DCOK           0x4000L      /* IOR 2 DC is okay */
#define IOR3_DCOK           0x8000L      /* IOR 3 DC is okay */

/* 
 * Bit defines for Power System Manager Status Register 2 (PSM_SR2)
 */
#define LM80_1_Int          0x0001L      /* LM80 1 interrupt is asserted */
#define LM80_2_Int          0x0002L      /* LM80 2 interrupt is asserted */
#define LM80_3_Int          0x0004L      /* LM80 3 interrupt is asserted */
/* RESERVED                 0x0008L */
#define IIC_Bus_1_Int       0x0010L      /* I2C Bus 1 interrupt is asserted */
#define IIC_Bus_2_Int       0x0020L      /* I2C Bus 2 interrupt is asserted */
#define IIC_Bus_3_Int       0x0040L      /* I2C Bus 3 interrupt is asserted */
/* RESERVED                 0x0080L */
#define IIC_Bus_1_Reset     0x2000L      /* I2C bus 1 reset */
#define IIC_Bus_2_Reset     0x4000L      /* I2C bus 2 reset */
#define IIC_Bus_3_Reset     0x8000L      /* I2C bus 3 reset */

/* 
 * Bit defines for Power System Manager Status Register 3 (PSM_SR3)
 */
/* RESERVED                 0x0001L */
/* RESERVED                 0x0002L */
#define Dir_Present         0x0004L      /* Directory present */
#define GP_Present          0x0008L      /* Global Port present */
#define MEM0_Present        0x0010L      /* Memory 0 present */
#define MEM1_Present        0x0020L      /* Memory 1 present */
#define MEM2_Present        0x0040L      /* Memory 2 present */
#define MEM3_Present        0x0080L      /* Memory 3 present */
#define CPU0_Present        0x0100L      /* CPU 0 present */
#define CPU1_Present        0x0200L      /* CPU 1 present */
#define CPU2_Present        0x0400L      /* CPU 2 present */
#define CPU3_Present        0x0800L      /* CPU 3 present */
#define IOR0_Present        0x1000L      /* I/O Riser 0 present */
#define IOR1_Present        0x2000L      /* I/O Riser 1 present */
#define IOR2_Present        0x4000L      /* I/O Riser 2 present */
#define IOR3_Present        0x8000L      /* I/O Riser 3 present */

/* 
 * Bit defines for Power System Manager Status Register 4 (PSM_SR4)
 */
#define PSM_SR4_Air_Mover_Present   0x0001L      /* Air Mover Present */
#define PSM_SR4_PS1_Present         0x0002L      /* Power Supply 1 present */
#define PSM_SR4_PS2_Present         0x0004L      /* Power Supply 2 present */
#define PSM_SR4_PSM_SR4_PS3_Present         0x0008L      /* Power Supply 3 present */
#define Main_P_3_3V_Present 0x0010L      /* Main +3.3V converter present */
#define PSM_SR4_Aux_P_3_3V_Present  0x0020L      /* Auxiliary +3.3V converter present */
#define PSM_SR4_P_2_5V_Present      0x0040L      /* +2.5V converter present */
/* RESERVED                 0x0080L */
#define PSM_SR4_QBB_ID              0x0100L      /* bits 10:8 QBB_ID */
#define PSM_SR4_BP_Type             0x0800L      /* bits 14:11 Backplane type */
#define PSM_SR4_CSB_Master_Ena      0x8000L      /* CSB master enable */

/* 
 * Bit defines for Power System Manager Status Register 5 (PSM_SR5)
 */
#define PSM_Initializing    0x0001L      /* PSM initializing */
#define P_3_3V_Present      0x0002L      /* +3.3V present */
#define J7_Jumper_In        0x0004L      /* J7 jumper is in */
/* RESERVED                 0x0008L  */
/* RESERVED                 0x0010L */
/* RESERVED                 0x0020L */
/* RESERVED                 0x0040L */
/* RESERVED                 0x0080L */
#define CPU0_SIO_Sel        0x0100L      /* CPU 0 serial I/O port selected */
#define CPU1_SIO_Sel        0x0200L      /* CPU 1 serial I/O port selected */
#define CPU2_SIO_Sel        0x0400L      /* CPU 2 serial I/O port selected */
#define CPU3_SIO_Sel        0x0800L      /* CPU 3 serial I/O port selected */
#define CPU0_SROM_Ena       0x1000L      /* CPU 0 SROM enable */
#define CPU1_SROM_Ena       0x2000L      /* CPU 1 SROM enable */
#define CPU2_SROM_Ena       0x4000L      /* CPU 2 SROM enable */
#define CPU3_SROM_Ena       0x8000L      /* CPU 3 SROM enable */

/* 
 * Bit defines for Power System Manager Status Register (PSM_SR6)
 */
#define PS_DC_Ena           0x0001L      /* Power SUpply +48V DC enable */
#define PLL_Power_Ena       0x0002L      /* PLL power enable */
#define P_3_3_Power_Ena     0x0004L      /* +3.3V power enable */
#define P_2_5_Power_Ena     0x0008L      /* +2.5V power enable */
/* RESERVED                 0x0010L */
#define Air_Mover_Speed     0x0040L      /* Air Mover speed */
#define CPU0_Power_Ena      0x0080L      /* CPU 0 power enable */
#define CPU1_Power_Ena      0x0100L      /* CPU 1 power enable */
#define CPU2_Power_Ena      0x0200L      /* CPU 2 power enable */
#define CPU3_Power_Ena      0x0400L      /* CPU 3 power enable */
#define IOR0_Power_Ena      0x0800L      /* I/O Riser 0 power enable */
#define IOR1_Power_Ena      0x2000L      /* I/O Riser 1 power enable */
#define IOR2_Power_Ena      0x4000L      /* I/O Riser 2 power enable */
#define IOR3_Power_Ena      0x8000L      /* I/O Riser 3 power enable */

/* 
 * Bit defines for Power System Manager Status Register 7 (PSM_SR7)
 */
#define QBB_Async_Reset     0x2         /* QBB asynchronous reset */
#define Dir_Async_Reset     0x4         /* Directory asynchronous reset */
#define GP_Async_Reset      0x8         /* Global Port asynchronous reset */
#define MEM0_Async_Reset    0x10        /* Memory 0 asynchronous reset */
#define MEM1_Async_Reset    0x20        /* Memory 1 asynchronous reset */
#define MEM2_Async_Reset    0x40        /* Memory 2 asynchronous reset */
#define MEM3_Async_Reset    0x80        /* Memory 3 asynchronous reset */
#define CPU0_Async_Reset    0x100       /* CPU 0 asynchronous reset */
#define CPU1_Async_Reset    0x200       /* CPU 1 asynchronous reset */
#define CPU2_Async_Reset    0x400       /* CPU 2 asynchronous reset */
#define CPU3_Async_Reset    0x800       /* CPU 3 asynchronous reset */
#define IOR0_Async_Reset    0x1000      /* I/O Riser 0 asynchronous reset */
#define IOR1_Async_Reset    0x2000      /* I/O Riser 1 asynchronous reset */
#define IOR2_Async_Reset    0x4000      /* I/O Riser 2 asynchronous reset */
#define IOR3_Async_Reset    0x8000      /* I/O Riser 3 asynchronous reset */

/*
 * Bit defines for PCI Backplane Manager PCI Power Supply 
 * Register (PBM_PCI_POWER_SUPPLY)
 */
#define PBM_PCI_PS1_Present         0x0001L      /* Power Supply 1 present */
#define PBM_PCI_PS2_Present         0x0002L      /* Power Supply 2 present */
#define PBM_PCI_PS1_Power_OK        0x0004L      /* Power Supply 1 power okay */
#define PBM_PCI_PS2_Power_OK        0x0008L      /* Power Supply 2 power okay */
#define PBM_PCI_PS1_Vaux_OK         0x0010L      /* Power Supply 1 Vaux okay */
#define PBM_PCI_PS2_Vaux_OK         0x0020L      /* Power Supply 2 Vaux okay */
#define PBM_PCI_PS1_Over_Temp       0x0040L      /* Power Supply 1 over temperature */
#define PBM_PCI_PS2_Over_Temp       0x0080L      /* Power Supply 2 over temperature */
#define PBM_PCI_PCI_Drawer_CI       0x0100L      /* PCI drawer cover interlock */
#define PBM_PCI_DC_Ena_OJ           0x0200L      /* DC enable override jumper */
/* RESERVED                 0x0400L */
/* RESERVED                 0x0800L */
#define PBM_PCI_PS1_Swap_OK         0x1000L      /* Power Supply 1 swap okay */
#define PBM_PCI_PS2_Swap_OK         0x2000L      /* Power Supply 2 swap okay */
#define PBM_PCI_PS1_DC_Ena          0x4000L      /* Power Supply 1 DC enable */
#define PBM_PCI_PS2_DC_Ena          0x8000L      /* Power Supply 2 DC enable */

/*
 * Bit defines for PCI Backplane Manager Reset Register (PBM_RESET)
 */
#define PCA0_Bus0_Reset     0x0001L      /* PCA 0 Bus 0 PCI reset */
#define PCA0_Bus1_Reset     0x0002L      /* PCA 0 Bus 1 PCI reset */
#define PCA1_Bus0_Reset     0x0004L      /* PCA 1 Bus 0 PCI reset */
#define PCA1_Bus1_Reset     0x0008L      /* PCA 1 Bus 1 PCI reset */
#define Hose0_Reset         0x0010L      /* Hose 0 asynchronous reset */
#define Hose1_Reset         0x0020L      /* Hose 1 asynchronous reset */
#define ML0_Reset           0x0040L      /* Mini-Link 0 reset */
#define ML1_Reset           0x0080L      /* Mini-Link 1 reset */
#define Clear_BIST_LED      0x0100L      /* Clean BIST LED */
#define Force_FSL_Mode      0x0200L      /* Force fail-safe loader mode */
/* RESERVED                 0x0400L */
/* RESERVED                 0x0800L */
#define Hose0_Reset_On      0x1000L      /* Hose 0 asynchronous reset control */
#define Hose1_Reset_On      0x2000L      /* Hose 1 asynchronous reset control */
#define PCD8584_Reset_On    0x4000L      /* PCD8584 reset control */
#define PBM_Reset_On        0x8000L      /* PBM reset control */

/*
 * Bit defines for PCI Backplane Manager PCA System Event Register (PBM_PCA_SE)
 */
#define PCI_HW_0            0x0001L       /* PCI Hardware Group 0 */
#define PCI_HW_1            0x0002L       /* PCI Hardware Group 1 */
#define PCI_HW_2            0x0004L       /* PCI Hardware Group 2 */
#define PCI_HW_3            0x0008L       /* PCI Hardware Group 3 */
#define PCI_HW_4            0x0010L       /* PCI Hardware Group 4 */
#define PCI_Warn            0x0020L       /* PCI Warning */
/* RESERVED                 0x0040L */
/* RESERVED                 0x0080L */
#define PBM_Int             0x0100L       /* PBM interrupt request */
/* RESERVED                 0x0200L */
/* RESERVED                 0x0400L */
/* RESERVED                 0x0800L */
/* RESERVED                 0x1000L */
/* RESERVED                 0x2000L */
/* RESERVED                 0x4000L */
/* RESERVED                 0x8000L */

/*
 * Bit defines for PCI Backplane Manager Interrupt 
 * Clear Register (PBM_INT_CLEAR)
 */
#define PS1_Power_OK_Clear  0x0001L      /* Clear Power Supply 1 
					    power okay failure */
#define PS2_Power_OK_Clear  0x0002L      /* Clear Power Supply 2
					    power okay failure */
#define PS1_Vaux_OK_Clear   0x0004L      /* Clear Power Supply 1 
					    Vaux okay failure */
#define PS2_Vaux_OK_Clear   0x0008L      /* Clear Power Supply 2 
					    Vaux okay failure */
#define PS1_Over_Temp_Clear 0x0010L      /* Clear Power Supply 1 
					    over temperature failure */
#define PS2_Over_Temp_Clear 0x0020L      /* Clear Power Supply 2 
					    over temperature failure */
#define Clock_Clear         0x0040L      /* Clear PCI reference clock failure */
/* RESERVED                 0x0080L */
#define IOR0_DCOK_Clear     0x0100L      /* Clear I/O Riser 0 DC okay failure */
#define IOR1_DCOK_Clear     0x0200L      /* Clear I/O Riser 1 DC okay failure */
/* RESERVED                 0x0400L */
/* RESERVED                 0x0800L */
/* RESERVED                 0x1000L */
/* RESERVED                 0x2000L */
/* RESERVED                 0x4000L */
/* RESERVED                 0x8000L */

/* 
 * Bit defines for PCI Backplane Manager PIO Data 0 Register (PBM_PIO_DATA_0)
 */
#define PBM_IOR0_Present        0x0001L      /* I/O Riser 0 present */
#define PBM_IOR1_Present        0x0002L      /* I/O Riser 1 present */
/* RESERVED                 0x0004L   */
/* RESERVED                 0x0008L   */
/* RESERVED                 0x0010L  */
/* RESERVED                 0x0020L  */
/* RESERVED                 0x0040L  */
/* RESERVED                 0x0080L  */
/* RESERVED                 0x0100L */
/* RESERVED                 0x0200L */
#define Clock_OK            0x0400L      /* PCI reference clock is okay */
#define PBM_IOR0_DCOK           0x0800L      /* I/O Riser 0 DC okay */
#define PBM_IOR1_DCOK           0x1000L      /* I/O Riser 1 DC okay */
/* RESERVED                 0x2000L */
#define CSB_Master_Ena      0x4000L      /* CSB master enable */
#define CSB_Transmit_Ena    0x8000L      /* CSB transmit enable */

/* 
 * Bit defines for PCI Backplane Manager PIO Data 1 Register (PBM_PIO_DATA_1)
 */
/* RESERVED                 0x0001L */
/* RESERVED                 0x0002L */
/* RESERVED                 0x0004L */
/* RESERVED                 0x0008L */
#define Micro_Valid         0x0010L        /* Micro valid */
#define Micro_Ack           0x0020L        /* Micro acknowlege */
/* RESERVED                 0x0040L */
/* RESERVED                 0x0080L */
#define ASIC_Valie          0x0100L       /* ASIC valid */
#define ASIC_Ack            0x0200L       /* ASIC acknowlege */
/* RESERVED                 0x0400L */
/* RESERVED                 0x0800L */
/* RESERVED                 0x1000L */
/* RESERVED                 0x2000L */
/* RESERVED                 0x4000L */
/* RESERVED                 0x8000L */

/* 
 * Misc. Defines for System Management 
 */
#define FireBox_backplane         1
#define Drawer_backplane          2
#define AirMoverSpeed_Low         0
#define AirMoverSpeed_Medium_Low  1
#define AirMoverSpeed_Medium_Med  2
#define AirMoverSpeed_Medium_High 3
#define AirMoverSpeed_High_Low    4 
#define AirMoverSpeed_High_Med1   5
#define AirMoverSpeed_High_Med2   6
#define AirMoverSpeed_High_High   7

/*
 * IOP QBB System Event Summary Registers
 */
#define FAULT                0x0000000000000001L /* Fault */
#define VITAL_POWER_FAIL     0x0000000000000002L /* Vital Power Failure */
#define PS1_VOLT_FAIL        0x0000000000000004L /* Power Supply 1 Voltage Failure */
#define PS2_VOLT_FAIL        0x0000000000000008L /* Power Supply 2 Voltage Failure */
#define PS3_VOLT_FAIL        0x0000000000000010L /* Power Supply 3 Voltage Failure */
#define PS_FAN_FAIL          0x0000000000000020L /* Power Supply Fan Failure */
#define SERVICE_SWITCH       0x0000000000000040L /* Service Switch Set to Service */
#define QBB_OVER_TEMP_FAIL   0x0000000000000080L /* QBB Over-Temperature Failure */
#define AIR_MOVER_FAIL       0x0000000000000100L /* Air Mover Failure */
#define MAIN_3_3V_MOD_FAIL   0x0000000000000200L /* Main +3.3V Module Failure */
#define AUX_3_3V_MOD_FAIL    0x0000000000000400L /* Auxiliary +3.3V Module Failure */
#define CLOCK_SPLIT_MOD_FAIL 0x0000000000000800L /* Clock Splitter Module Failure */
#define PSM_MOD_FAIL         0x0000000000001000L /* PSM Module Failure */
#define CPU_MOD_POWER_FAIL   0x0000000000002000L /* CPU Module Power Failure */
#define IOR_MOD_POWER_FAIL   0x0000000000004000L /* I/O Riser Module Power Failure */
/* #define RESERVED          0x0000000000008000L    Implemented, but reserved for future use */
/* #define RESERVED          0x0000000000010000L    Implemented, but reserved for future use */
#define PS_TEMP_YELLOW       0x0000000000020000L /* Warning-PS Temperature in Yellow Zone */
#define QBB_TEMP_YELLOW      0x0000000000040000L /* Warning-QBB Temperature in Yellow Zone */
#define QBB_POWER_OFF        0x0000000000080000L /* SCM Command-QBB Power Off */
#define QBB_RESET            0x0000000000100000L /* SCM Command-QBB Pulsed Reset */
#define QBB_RESET_ON         0x0000000000200000L /* SCM Command-QBB Static Reset On */
#define QBB_HALT_ON          0x0000000000400000L /* SCM Command-QBB Halt On */
#define QBB_HALT_OFF         0x0000000000800000L /* SCM Command-QBB Halt Off */
#define HS_SYSTEM_EVENT      0x0000000001000000L /* HS System Event */
#define QBB_INIT_CD1         0x0000000002000000L /* QBB Initialization Complete, command delay 1 */
#define QBB_INIT_CD0         0x0000000004000000L /* QBB Initialization Complete, command delay 0 */
#define CPU_INIT             0x0000000008000000L /* CPU Initialization Complete */
#define IOR_SYNC_INIT        0x0000000010000000L /* I/O Riser Synchronous Initialization Complete */
#define CPU_SYNC_INIT        0x0000000020000000L /* CPU Synchronous Initialization Complete */
#define FAULT_RECOVERY       0x0000000040000000L /* Fault Recovery Complete */
#define QBB_FAULT            0x0000000080000000L /* SCM Command-QBB Fault */
#define HOSE_0_PCI_HW_0      0x0000000100000000L /* Hose 0 PCI Hardware Group 0 */
#define HOSE_0_PCI_HW_1      0x0000000200000000L /* Hose 0 PCI Hardware Group 1 */
#define HOSE_0_PCI_HW_2      0x0000000400000000L /* Hose 0 PCI Hardware Group 2 */
#define HOSE_0_PCI_HW_3      0x0000000800000000L /* Hose 0 PCI Hardware Group 3 */
#define HOSE_0_PCI_HW_4      0x0000001000000000L /* Hose 0 PCI Hardware Group 4 */
#define HOSE_0_PCI_WARN      0x0000002000000000L /* Hose 0 PCI Warning */
/* #define RESERVED          0x0000004000000000L    Implemented, but reserved for future use */
#define HOSE_0_CABLE_TRANS   0x0000008000000000L /* Hose 0 Cable Transition */
#define HOSE_1_PCI_HW_0      0x0000010000000000L /* Hose 1 PCI Hardware Group 0 */
#define HOSE_1_PCI_HW_1      0x0000020000000000L /* Hose 1 PCI Hardware Group 1 */
#define HOSE_1_PCI_HW_2      0x0000040000000000L /* Hose 1 PCI Hardware Group 2 */
#define HOSE_1_PCI_HW_3      0x0000080000000000L /* Hose 1 PCI Hardware Group 3 */
#define HOSE_1_PCI_HW_4      0x0000100000000000L /* Hose 1 PCI Hardware Group 4 */
#define HOSE_1_PCI_WARN      0x0000200000000000L /* Hose 1 PCI Warning */
/* #define RESERVED          0x0000400000000000L    Implemented, but reserved for future use */
#define HOSE_1_CABLE_TRANS   0x0000800000000000L /* Hose 1 Cable Transition */
#define HOSE_2_PCI_HW_0      0x0001000000000000L /* Hose 2 PCI Hardware Group 0 */
#define HOSE_2_PCI_HW_1      0x0002000000000000L /* Hose 2 PCI Hardware Group 1 */
#define HOSE_2_PCI_HW_2      0x0004000000000000L /* Hose 2 PCI Hardware Group 2 */
#define HOSE_2_PCI_HW_3      0x0008000000000000L /* Hose 2 PCI Hardware Group 3 */
#define HOSE_2_PCI_HW_4      0x0010000000000000L /* Hose 2 PCI Hardware Group 4 */
#define HOSE_2_PCI_WARN      0x0020000000000000L /* Hose 2 PCI Warning */
/* #define RESERVED          0x0040000000000000L    Implemented, but reserved for future use */
#define HOSE_2_CABLE_TRANS   0x0080000000000000L /* Hose 2 Cable Transition */
#define HOSE_3_PCI_HW_0      0x0100000000000000L /* Hose 3 PCI Hardware Group 0 */
#define HOSE_3_PCI_HW_1      0x0200000000000000L /* Hose 3 PCI Hardware Group 1 */
#define HOSE_3_PCI_HW_2      0x0400000000000000L /* Hose 3 PCI Hardware Group 2 */
#define HOSE_3_PCI_HW_3      0x0800000000000000L /* Hose 3 PCI Hardware Group 3 */
#define HOSE_3_PCI_HW_4      0x1000000000000000L /* Hose 3 PCI Hardware Group 4 */
#define HOSE_3_PCI_WARN      0x2000000000000000L /* Hose 3 PCI Warning */
/* #define RESERVED          0x4000000000000000L    Implemented, but reserved for future use */
#define HOSE_3_CABLE_TRANS   0x8000000000000000L /* Hose 3 Cable Transition */

/* 
 * Bit Masks for Priority level of System Events
 */

/* 
 * Warning-level system events, action by OS
 * should be to simply log the event 
 */
#define SYSEVT_WARNING_PRIORITY \
( PS1_VOLT_FAIL | \
  PS2_VOLT_FAIL | \
  PS3_VOLT_FAIL | \
  PS_FAN_FAIL | \
  PS_TEMP_YELLOW  | \
  QBB_TEMP_YELLOW | \
  HOSE_0_PCI_WARN | \
  HOSE_1_PCI_WARN | \
  HOSE_2_PCI_WARN | \
  HOSE_3_PCI_WARN )

/*
 * Fatal-level system events, action by OS
 * should be to log the event and then shutdown 
 * the system
 */
#define SYSEVT_FATAL_PRIORITY \
     ( VITAL_POWER_FAIL | \
       SERVICE_SWITCH | \
       QBB_OVER_TEMP_FAIL | \
       AIR_MOVER_FAIL | \
       MAIN_3_3V_MOD_FAIL | \
       AUX_3_3V_MOD_FAIL | \
       CLOCK_SPLIT_MOD_FAIL | \
       PSM_MOD_FAIL | \
       QBB_POWER_OFF | \
       QBB_RESET | \
       QBB_RESET_ON )

/*
 * Ignore-level system events, action by OS
 * should be to ignore the event and not log it
 */
#define SYSEVT_IGNORE_PRIORITY \
     ( FAULT | \
       QBB_HALT_ON | \
       QBB_HALT_OFF | \
       QBB_INIT_CD1 | \
       QBB_INIT_CD0 | \
       CPU_INIT | \
       IOR_SYNC_INIT | \
       CPU_SYNC_INIT | \
       FAULT_RECOVERY | \
       QBB_FAULT )

/* 
 * DefensiveShutdown-level system events, action by OS
 * should be to log the event and defensively shutdown
 * the system knowing that it will panic because of a
 * loss of hardware
 */
#define SYSEVT_DEFENSIVESHUTDOWN_PRIORITY \
     ( CPU_MOD_POWER_FAIL | \
       IOR_MOD_POWER_FAIL | \
       HOSE_0_PCI_HW_0 | \
       HOSE_0_PCI_HW_1 | \
       HOSE_0_PCI_HW_2 | \
       HOSE_0_PCI_HW_3 | \
       HOSE_0_PCI_HW_4 | \
       HOSE_0_CABLE_TRANS | \
       HOSE_1_PCI_HW_0 | \
       HOSE_1_PCI_HW_1 | \
       HOSE_1_PCI_HW_2 | \
       HOSE_1_PCI_HW_3 | \
       HOSE_1_PCI_HW_4 | \
       HOSE_1_CABLE_TRANS | \
       HOSE_2_PCI_HW_0 | \
       HOSE_2_PCI_HW_1 | \
       HOSE_2_PCI_HW_2 | \
       HOSE_2_PCI_HW_3 | \
       HOSE_2_PCI_HW_4 | \
       HOSE_2_CABLE_TRANS | \
       HOSE_3_PCI_HW_0 | \
       HOSE_3_PCI_HW_1 | \
       HOSE_3_PCI_HW_2 | \
       HOSE_3_PCI_HW_3 | \
       HOSE_3_PCI_HW_4 | \
       HOSE_3_CABLE_TRANS )

/*
 * Bit masks for PBM, PSM, and HPM system events
 */

/* Lower 32 bits of the QBB Sys Evt Summary indicate a PSM event */
#define WF_PSM_EVENTS \
     ( FAULT | \
       VITAL_POWER_FAIL | \
       PS1_VOLT_FAIL | \
       PS2_VOLT_FAIL | \
       PS3_VOLT_FAIL | \
       PS_FAN_FAIL | \
       SERVICE_SWITCH | \
       QBB_OVER_TEMP_FAIL | \
       AIR_MOVER_FAIL | \
       MAIN_3_3V_MOD_FAIL | \
       AUX_3_3V_MOD_FAIL | \
       CLOCK_SPLIT_MOD_FAIL | \
       PSM_MOD_FAIL | \
       CPU_MOD_POWER_FAIL | \
       IOR_MOD_POWER_FAIL | \
       PS_TEMP_YELLOW | \
       QBB_TEMP_YELLOW | \
       QBB_POWER_OFF | \
       QBB_RESET | \
       QBB_RESET_ON | \
       QBB_HALT_ON | \
       QBB_HALT_OFF | \
       QBB_INIT_CD1 | \
       QBB_INIT_CD0 | \
       CPU_INIT | \
       IOR_SYNC_INIT | \
       CPU_SYNC_INIT | \
       FAULT_RECOVERY | \
       QBB_FAULT )
  
/* Upper 32 bits of the QBB Sys Evt Summary indicate a PBM event */
#define WF_PBM_EVENTS \
     ( HOSE_0_PCI_HW_0 | \
       HOSE_0_PCI_HW_1 | \
       HOSE_0_PCI_HW_2 | \
       HOSE_0_PCI_HW_3 | \
       HOSE_0_PCI_HW_4 | \
       HOSE_0_PCI_WARN | \
       HOSE_0_CABLE_TRANS | \
       HOSE_1_PCI_HW_0 | \
       HOSE_1_PCI_HW_1 | \
       HOSE_1_PCI_HW_2 | \
       HOSE_1_PCI_HW_3 | \
       HOSE_1_PCI_HW_4 | \
       HOSE_1_PCI_WARN | \
       HOSE_1_CABLE_TRANS | \
       HOSE_2_PCI_HW_0 | \
       HOSE_2_PCI_HW_1 | \
       HOSE_2_PCI_HW_2 | \
       HOSE_2_PCI_HW_3 | \
       HOSE_2_PCI_HW_4 | \
       HOSE_2_PCI_WARN | \
       HOSE_2_CABLE_TRANS | \
       HOSE_3_PCI_HW_0 | \
       HOSE_3_PCI_HW_1 | \
       HOSE_3_PCI_HW_2 | \
       HOSE_3_PCI_HW_3 | \
       HOSE_3_PCI_HW_4 | \
       HOSE_3_PCI_WARN | \
       HOSE_3_CABLE_TRANS )

/* Bit 24 is of the QBB Sys Evt Summary indicates an HPM event */
#define WF_HPM_EVENTS         HS_SYSTEM_EVENT
  
/*
 * Bit masks for PBM Hose Events
 */
#define WF_PBM_HOSE_0 ( HOSE_0_PCI_HW_0 | HOSE_0_PCI_HW_1 | HOSE_0_PCI_HW_2 | HOSE_0_PCI_HW_3 | HOSE_0_PCI_HW_4 | HOSE_0_PCI_WARN | HOSE_0_CABLE_TRANS )

#define WF_PBM_HOSE_1 ( HOSE_1_PCI_HW_0 | HOSE_1_PCI_HW_1 | HOSE_1_PCI_HW_2 | HOSE_1_PCI_HW_3 | HOSE_1_PCI_HW_4 | HOSE_1_PCI_WARN | HOSE_1_CABLE_TRANS )
  
#define WF_PBM_HOSE_2 ( HOSE_2_PCI_HW_0 | HOSE_2_PCI_HW_1 | HOSE_2_PCI_HW_2 | HOSE_2_PCI_HW_3 | HOSE_2_PCI_HW_4 | HOSE_2_PCI_WARN | HOSE_2_CABLE_TRANS )
  
#define WF_PBM_HOSE_3 ( HOSE_3_PCI_HW_0 | HOSE_3_PCI_HW_1 | HOSE_3_PCI_HW_2 | HOSE_3_PCI_HW_3 | HOSE_3_PCI_HW_4 | HOSE_3_PCI_WARN | HOSE_3_CABLE_TRANS )
  
/*
 * Envmon-related support
 */
#define WF_FANS_PER_QBB	4		/* Central, 3 n+1 PS 		*/
#define WF_TEMP_PER_QBB	4		/* QBB, 3 n+1 PS		*/
#define WF_PWR_PER_QBB	8		/* 5 for QBB; 3 n+1 PS?		*/

/* 
 * The hose ctft node on wildfire contains PCI-box related information.
 * Thus, two hoses to the same PCI box will have the same values.
 */
#define WF_FANS_PER_HOSE	2	/* 2 PS in PCI box		*/
#define WF_TEMP_PER_HOSE	3	/* 2 PS in PCI box; 3rd ???	*/
#define WF_PWR_PER_HOSE		4	/* 2 PS in PCI box; 3rd & 4th ?	*/

struct wf_fan_status {
	u_char qbb[WF_MAX_QBBS][WF_FANS_PER_QBB];
        u_char hose[WF_MAX_QBBS][WF_MAX_HOSE_PER_QBB][WF_FANS_PER_HOSE];
/*        u_char hs;	*/
};
struct wf_temp_status {
	u_char qbb[WF_MAX_QBBS][WF_TEMP_PER_QBB];
        u_char hose[WF_MAX_QBBS][WF_MAX_HOSE_PER_QBB][WF_TEMP_PER_HOSE];
/*        u_char hs;	*/
};
struct wf_pwr_status {
	u_char qbb[WF_MAX_QBBS][WF_PWR_PER_QBB];
        u_char hose[WF_MAX_QBBS][WF_MAX_HOSE_PER_QBB][WF_PWR_PER_HOSE];
/*        u_char hs;	*/
};
	
struct wf_temp_value {
	u_char qbb[WF_MAX_QBBS][WF_TEMP_PER_QBB];
        u_char hose[WF_MAX_QBBS][WF_MAX_HOSE_PER_QBB][WF_TEMP_PER_HOSE];
/*        u_char hs;	*/
};

/*
 * wfsrvmgmt.c debugging aid
 *
 * NOTE: since wfcpu.h, wfqbb.h, & wfpci.h may be included in
 *	 one .c file, their definitions must not collide.
 */

extern	u_int	wfcpu_developer_debug;

/* To remove/add all debug printfs */
#define __WFSRVMGMTDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * wfcpu_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define WFSRVMGMTD_ENVMON	0x00000080
#define WFSRVMGMTD_SYSEVT	0x00040000

/* New, testing hw-support debug printfs				*/
#define WFSRVMGMTD_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _WFSRVMGMTenvmon;
extern char * _WFSRVMGMTsysevt;
extern char * _WFSRVMGMTnot_yet;


/*
 * printf expansion that WFSRVMGMTPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _WFSRVMGMTxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __WFSRVMGMTDEBUG
#   define _WFSRVMGMTD_SYSEVT(X)			\
    {						\
	/* NOSTRICT */				\
	/* Yes, wfcpu_xxxx since this printout wants to		\
	 * coincide with sysevt in wfcpu			\
	 */							\
        if( wfcpu_developer_debug & WFSRVMGMTD_SYSEVT)  {	\
	    /* VARARGS */			\
            printf (_WFSRVMGMTsysevt); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFSRVMGMTD_ENVMON(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfsrvmgmt_developer_debug & WFSRVMGMTD_ENVMON)  {	\
	    /* VARARGS */			\
            printf (_WFSRVMGMTenvmon); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFSRVMGMTD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfsrvmgmt_developer_debug & WFSRVMGMTD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_WFSRVMGMTnotyet); 		\
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
 * WFSRVMGMTD_INOUT | WFSRVMGMTD_CPU
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define WFSRVMGMTPRINTF(F, X)	_##F(X)

#else  /* !__WFSRVMGMTDEBUG */
#   define WFSRVMGMTPRINTF(F, X)
#endif /* __WFSRVMGMTDEBUG */

#endif /* __ARCH_ALPHA_HAL_WFSRVMGMT_H__ */

