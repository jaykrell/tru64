/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: hyperbrick2.h,v $
 * Revision 1.1.2.2  2004/08/12  18:12:03  Aaron_Biver
 * 	QAR 98088: Add comments to the hb_sensor_t definition.
 *
 * Revision 1.1.2.1  2003/06/20  17:29:03  Mike_Winiarski
 * 	Added more defines for support of the watchdog timer, EVM,
 * 	and envmond.
 * 	[2003/06/18  18:21:05  Mike_Winiarski]
 *
 * 	Redefined the sensor not present indications.
 * 	[2003/05/12  14:57:17  Mike_Winiarski]
 *
 * 	Added bit definitions for the Environmental 680 Error Logout Frame, and
 * 	defined the el_titan_hb_680_logout_frame struct, which is a slight variation
 * 	of the el_titan_680_logout_frame.
 * 	Added plenty of other #define for the DS15/TS15 platform.
 * 	[2003/04/21  20:07:26  Mike_Winiarski]
 *
 * 	Initial support for HyperBrickII (DS15/TS15).
 * 	[2003/03/31  19:40:58  Mike_Winiarski]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: hyperbrick2.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2004/08/12 18:12:03 $
 */
/*
 * External Declarations
 */
extern char **titan_drir_strings;

/*
 * Definitions for debugging
 */
#define HYPERBRICK_MODULE(mod) char *module = mod
#define HYPERBRICK_PRINTF(msg) printf msg
#define HYPERBRICK_DPRINTF(msg) if( _hyperbrick_debug ) dprintf msg

/*
 * Definition for a sensor, as defined
 * in the Dual Ported Ram(DPR).
 */

typedef struct hb_dpr_sensor{
    /* 
     * Note that some of these sensor members are interpreted 
     * in the code as signed types, though they are presented 
     * here as unsigned types.
     */

    uchar  hb_sensor_type;
    uchar  pad1[0x3f];
    uchar  hb_sensor_status;
    uchar  pad2[0x3f];
    uchar  hb_sensor_reading;       /* sensor reading */
    uchar  pad3[0x3f];
    uchar  hb_sensor_lowwarn;       /* low warning threshold */ 
    uchar  pad4[0x3f];
    uchar  hb_sensor_highwarn;      /* high warning threshold */ 
    uchar  pad5[0x3f];
    uchar  hb_sensor_lowfatal;      /* low fatal threshold */
    uchar  pad6[0x3f];
    uchar  hb_sensor_highfatal;     /* high fatal threshold */
    uchar  pad7[0x3f];
    uchar  hb_sensor_mult_low;      /* low bits - multiplier conversion factor */
    uchar  pad8[0x3f];
    uchar  hb_sensor_mult_hi;       /* hi  bits -                              */
    uchar  pad9[0x3f];
    uchar  hb_sensor_off_low;       /* low bits - offset conversion factor     */
    uchar  pad10[0x3f];
    uchar  hb_sensor_off_hi;        /* hi  bits -                              */
    uchar  pad11[0x3f];
    uchar  hb_sensor_oexp;          /* offset exponent conversion factor       */
    uchar  pad12[0x3f];
    uchar  hb_sensor_rexp;          /* result exponent conversion factor       */
    uchar  pad13[0x3f];
    uchar  hb_sensor_resv[19*0x40];      /* reserved */
} hb_sensor_t;

/* Values for 'hb_sensor_type' */
#define HB_SENSOR_THERMAL  0x1
#define HB_SENSOR_VOLTAGE  0x2
#define HB_SENSOR_FAN      0x4

/* Values for 'hb_sensor_status' */
/*
 * From the DS15 DPR Layout Spec. 1.0:
 * 
 * Sensor Status 
 * Bit 0: Lower warning threshold failure 
 * Bit 1: Lower fatal threshold failure 
 * Bit 2: Sensor not present in system 
 * Bit 3: Upper warning threshold failure 
 * Bit 4: Upper fatal threshold failure 
 * Bit 5: Emergency fatal threshold failure 
 *	  (only valid for thermal sensor) 
 * Bit 6: Sensor scanning disabled 
 *	  (Sensor is monitored, but data is 
 *	  not yet stable) 
 * Bit 7: Sensor has failed 
 * 
 * Note 1: For threshold bits 0, 1, 3, 4, and 5, bit will be 
 *         set if corresponding threshold is supported and has been
 *         violated. For example, if the upper fatal threshold has
 *         been crossed on a sensor that supports both an upper fatal
 *         and upper warning threshold, bits 3 and 4 will both be set
 *         (since upper warning threshold must also have been
 *         crossed).
 * 
 * Note 2: If bits 2 or 7 are set, threshold bits 0, 1, 3, 4, and 5
 *         are unpredictable and should be ignored.
 */
#define HB_SENSOR_OK                 0x0
#define HB_SENSOR_LOW_WARN_FAILURE   0x01
#define HB_SENSOR_LOW_FATAL_FAILURE  0x02
#define HB_SENSOR_NOT_PRESENT        0x04
#define HB_SENSOR_HI_WARN_FAILURE    0x08
#define HB_SENSOR_HI_FATAL_FAILURE   0x10
#define HB_SENSOR_EMERGENCY_FAILURE  0x20
#define HB_SENSOR_SCAN_DISABLED      0x40
#define HB_SENSOR_HAS_FAILED         0x80

#define HB_SENSOR_NOT_AVAILABLE_MASK (HB_SENSOR_NOT_PRESENT | HB_SENSOR_HAS_FAILED)
#define HB_SENSOR_FAILURE (HB_SENSOR_LOW_WARN_FAILURE | HB_SENSOR_LOW_FATAL_FAILURE | \
                           HB_SENSOR_HI_WARN_FAILURE | HB_SENSOR_HI_FATAL_FAILURE | \
                           HB_SENSOR_EMERGENCY_FAILURE)

static char *hb_sensor_names[] = {
    "1.65V from VRM", 
    "2.5V from VRM",
    "3.3V from PS", 
    "5V from PS", 
    "12V from PS",
    "-12V from PS", 
    "3.3Vsb from VRM", 
    "5Vsb from PS",
    "2.85V from SCSI A VRM",
    "2.85V from SCSI B VRM", 
    "System Fan", 
    "PCI Fan", 
    "CPU Fan", 
    "Disk Fan", 
    "LM75 Thermal Sensor"
};


/*
 * Length of time it can take hyperbrick to power down
 */
#define HYPERBRICK_OS_POWERDOWN       60;

/* 
 * Defintions for DPR Locations
 */
#define HB_DPR_INDEX                         0x40
#define HB_DPR_SIZE                          0x100
#define HB_DPR_SENSOR_COUNT                  15

/* Base Address of memory config info */
#define HB_DPR_MEM_CONFIG                    (0x80 * HB_DPR_INDEX)

/* Base address of RMC_TIG_MISC Watchdog Timer registers */
#define HB_DPR_WDT_TIMEOUT_DEFAULT           (0xC3 * HB_DPR_INDEX)
#define HB_DPR_WDT_TIMEOUT_CURRENT           (0xC4 * HB_DPR_INDEX)

/* Base address of Event Overrides info */
#define HB_DPR_EVENT_OVERRIDES               (0xC7 * HB_DPR_INDEX)
#define HB_DPR_EVENT_OVERRIDE_TEMP           0x01
#define HB_DPR_EVENT_OVERRIDE_FAN            0x02

/* Addresses for sensor information */
#define HB_DPR_SENSOR_INDEX                  (0xF20 * HB_DPR_INDEX)
#define HB_DPR_SENSOR_SIZE                   0x20
#define HB_DPR_SENSOR_BASE                   0xF20
#define HB_DPR_SENSOR_VOLT_165               0xF20
#define HB_DPR_SENSOR_VOLT_25                0xF40
#define HB_DPR_SENSOR_VOLT_33                0xF60
#define HB_DPR_SENSOR_VOLT_5                 0xF80
#define HB_DPR_SENSOR_VOLT_12                0xFA0
#define HB_DPR_SENSOR_VOLT_M12               0xFC0
#define HB_DPR_SENSOR_VOLT_33VSB             0xFE0
#define HB_DPR_SENSOR_VOLT_5VSB              0x1000
#define HB_DPR_SENSOR_VOLT_SCSIA             0x1020
#define HB_DPR_SENSOR_VOLT_SCSIB             0x1040
#define HB_DPR_SENSOR_FAN_SYS                0x1060
#define HB_DPR_SENSOR_FAN_PCI                0x1080
#define HB_DPR_SENSOR_FAN_CPU                0x10A0
#define HB_DPR_SENSOR_FAN_DISK               0x10C0
#define HB_DPR_SENSOR_THERMAL                0x10E0

/*
 * DIM Register Definitions (assume bits are the same as DRIR)
 */
#define HB_C_ERR_BIT		63	/* bit 63 */
#define HB_P0_HERR_BIT	        62	/* bit 62 */
#define HB_P0_SERR_BIT	        59	/* bit 59 */
#define HB_ISA_INTR_BIT	        55	/* bit 55 */
#define HB_SMI_BIT		54	/* bit 54 */
#define HB_NMI_BIT		53	/* bit 53 */
#define HB_ENV_FATAL_BIT     	50	/* bit 50 */
#define HB_ENV_WARN_BIT	        49	/* bit 49 */

/*
 *      HyperbrickII (DS15/TS15) TIG Registers
 *              The registers are different than privateer/granite.
 */

struct hbrick_tig_regs {
    uchar       trr;            /* offset 0000 */
    char        pad1[0x3f];
    uchar       tir;            /* offset 0040 */
    char        pad2[0x3f];
    uchar       ttcr;           /* offset 0080 */
    char        pad3[0x3f];
    uchar       wdr;            /* offset 00C0 */
    char        pad4[0x3f];
    uchar       m66n;           /* offset 0100 */
    char        pad5[0x3f];
    uchar       RFU1;           /* offset 0140 - Reserved for Future Use */
    char        pad6[0x3f];
    uchar       fwmr0;          /* offset 0180 */
    char        pad7[0x3f];
    uchar       fwmr1;          /* offset 01C0 */
    char        pad8[0x3f];
    uchar       fwmr2;          /* offset 0200 */
    char        pad9[0x3f];
    uchar       fwmr3;          /* offset 0240 */
    char        pad10[0x3f];
    uchar       ipcr0;          /* offset 0280 */
    char        pad11[0x3f];
    uchar       RFU2;           /* offset 02C0 - RFU */
    char        pad12[0xbf];
    uchar       ipcr4;          /* offset 0380 */
    char        pad13[0x3f];
    uchar       RFU3;           /* offset 03C0 - RFU */
    char        pad14[0x3f];
    uchar       cir;            /* offset 0400 */
    char        pad15[0x3f];
    uchar       evir;           /* offset 0440 */
    char        pad16[0x3f];
    uchar       evhr;           /* offset 0480 */
    char        pad17[0x3f];
    uchar       irq5m;          /* offset 04C0 */
    char        pad18[0x3f];
    uchar       eicr;           /* offset 0500 */
    char        pad19[0x3f];
    uchar       RFU4;           /* offset 0540 - RFU */
    char        pad20[0x2bf];
    uchar       srcr;           /* offset 0800 */
    char        pad21[0x3f];
    uchar       frar0;          /* offset 0840 */
    char        pad22[0x3f];
    uchar       frar1;          /* offset 0880 */
    char        pad23[0x3f];
    uchar       RFU5;           /* offset 08C0 - RFU */
    char        pad24[0x33f];
    uchar       plld0;          /* offset 0C00 */
    char        pad25[0x3f];
    uchar       plld1;          /* offset 0C40 */
    char        pad26[0x3f];
    uchar       RFU6;           /* offset 0C80 - RFU */
    char        pad27[0x37f];
    uchar       pctrl;          /* offset 1000 */
    char        pad28[0xff];
    uchar       RFU7;           /* offset 1100 - RFU */
    char        pad29[0x2ff];
    uchar       tpcr;           /* offset 1400 */
    char        pad30[0x3f];
    uchar       RFU8;           /* offset 1440 - RFU */
};

/* hbrick system power control register (PCTRL) */
#define HB_TIG_FAULT_LED        0x80
#define HB_TIG_CPU0_ALIVE       0x40
#define HB_TIG_SOFT_PWR_DOWN    0x20
#define HB_TIG_ACTIVE_CMD       0x10
#define HB_TIG_LOAD_PLL         0x08
#define HB_TIG_PWR_CTL_MASK     0x07

#define HB_TIG_PWR_CTL_IDLE             0x00
#define HB_TIG_PWR_CTL_RESET_TITAN      0x01
#define HB_TIG_PWR_CTL_RESET_SYSTEM     0x02

/* hbrick TIG Watchdog Timer register (WDR) */
#define HB_TIG_WDR_WD_ENA       0x01    /* watchdog enable */
#define HB_TIG_WDR_WD_CLK       0x02    /* watchdog clock pulse */
#define HB_TIG_WDR_WD_PRD       0x04    /* watchdog period update */
#define HB_TIG_WDR_ZIRCON_RDY   0x80    /* Zircon Ready */

/* HyperBrickII DIRx Register Definitions */
#define HB_DIRX_WARN_ENV        (1UL << 50)

/* Masks for envqw_1 -- TIG Information */
#define HB_TIG_INFO_MASK        0x0F
#define HB_TIG_INFO_FATAL_ENV   (1UL << 0)
#define HB_TIG_INFO_WARN_ENV    (1UL << 1)
#define HB_TIG_INFO_HALT        (1UL << 2)
#define HB_TIG_INFO_RMC_NOTRDY  (1UL << 3)

/* Masks for envqw_3 -- RMC Override Status */
#define HB_ENV_OVERRIDE_MASK    0x101
#define HB_ENV_TEMP_OVERRIDE    (1UL << 0)
#define HB_ENV_FAN_OVERRIDE     (1UL << 8)

/* Masks for envqw_4 -- Power/Voltage Warning/Fail */
#define HB_PS_FAIL_MASK         0x03FF03FF03FF03FF
#define HB_PS_FAIL_WARN_MASK    0x0000000003FF03FF
#define HB_PS_FAIL_FATAL_MASK   0x03FF03FF00000000

#define HB_PS_165_LOW_WARN      (1UL << 0)
#define HB_PS_250_LOW_WARN      (1UL << 1)
#define HB_PS_330_LOW_WARN      (1UL << 2)
#define HB_PS_500_LOW_WARN      (1UL << 3)
#define HB_PS_P12_LOW_WARN      (1UL << 4)
#define HB_PS_M12_LOW_WARN      (1UL << 5)
#define HB_PS_33SB_LOW_WARN     (1UL << 6)
#define HB_PS_5SB_LOW_WARN      (1UL << 7)
#define HB_PS_SCSIA_LOW_WARN    (1UL << 8)
#define HB_PS_SCSIB_LOW_WARN    (1UL << 9)

#define HB_PS_165_HI_WARN       (1UL << 16)
#define HB_PS_250_HI_WARN       (1UL << 17)
#define HB_PS_330_HI_WARN       (1UL << 18)
#define HB_PS_500_HI_WARN       (1UL << 19)
#define HB_PS_P12_HI_WARN       (1UL << 20)
#define HB_PS_M12_HI_WARN       (1UL << 21)
#define HB_PS_33SB_HI_WARN      (1UL << 22)
#define HB_PS_5SB_HI_WARN       (1UL << 23)
#define HB_PS_SCSIA_HI_WARN     (1UL << 24)
#define HB_PS_SCSIB_HI_WARN     (1UL << 25)

#define HB_PS_165_LOW_FATAL     (1UL << 32)
#define HB_PS_250_LOW_FATAL     (1UL << 33)
#define HB_PS_330_LOW_FATAL     (1UL << 34)
#define HB_PS_500_LOW_FATAL     (1UL << 35)
#define HB_PS_P12_LOW_FATAL     (1UL << 36)
#define HB_PS_M12_LOW_FATAL     (1UL << 37)
#define HB_PS_33SB_LOW_FATAL    (1UL << 38)
#define HB_PS_5SB_LOW_FATAL     (1UL << 39)
#define HB_PS_SCSIA_LOW_FATAL   (1UL << 40)
#define HB_PS_SCSIB_LOW_FATAL   (1UL << 41)

#define HB_PS_165_HI_FATAL      (1UL << 48)
#define HB_PS_250_HI_FATAL      (1UL << 49)
#define HB_PS_330_HI_FATAL      (1UL << 50)
#define HB_PS_500_HI_FATAL      (1UL << 51)
#define HB_PS_P12_HI_FATAL      (1UL << 52)
#define HB_PS_M12_HI_FATAL      (1UL << 53)
#define HB_PS_33SB_HI_FATAL     (1UL << 54)
#define HB_PS_5SB_HI_FATAL      (1UL << 55)
#define HB_PS_SCSIA_HI_FATAL    (1UL << 56)
#define HB_PS_SCSIB_HI_FATAL    (1UL << 57)

/* Masks for envqw_5 -- Misc RMC Warning/Fail */
#define HB_RMC_MASK             0x0F0103FF0000001F
#define HB_RMC_SENSOR_MASK      0x0F0103FF00000000
#define HB_RMC_BG_TEST_MASK     0x000000000000001F

#define HB_RMC_BG_STACK         (1UL << 0)
#define HB_RMC_BG_POOL          (1UL << 1)
#define HB_RMC_BG_INT_SRAM      (1UL << 2)
#define HB_RMC_BG_EXT_SRAM      (1UL << 3)
#define HB_RMC_BG_DPR_CKSUM     (1UL << 4)

#define HB_RMC_165_FAIL         (1UL << 32)
#define HB_RMC_250_FAIL         (1UL << 33)
#define HB_RMC_330_FAIL         (1UL << 34)
#define HB_RMC_500_FAIL         (1UL << 35)
#define HB_RMC_P12_FAIL         (1UL << 36)
#define HB_RMC_M12_FAIL         (1UL << 37)
#define HB_RMC_33SB_FAIL        (1UL << 38)
#define HB_RMC_5SB_FAIL         (1UL << 39)
#define HB_RMC_SCSIA_FAIL       (1UL << 40)
#define HB_RMC_SCSIB_FAIL       (1UL << 41)

#define HB_RMC_TEMP_FAIL        (1UL << 48)

#define HB_RMC_SYS_FAN_FAIL     (1UL << 56)
#define HB_RMC_PCI_FAN_FAIL     (1UL << 57)
#define HB_RMC_CPU_FAN_FAIL     (1UL << 58)
#define HB_RMC_DISK_FAN_FAIL    (1UL << 59)

/* Masks for envqw_6 -- Temp Warning/Fail */
#define HB_SYS_TEMP_HI_MASK     0x0301
#define HB_SYS_TEMP_HI_WARN     (1UL << 0)
#define HB_SYS_TEMP_HI_FATAL    (1UL << 8)
#define HB_SYS_TEMP_EMERGENCY   (1UL << 9)

/* Masks for envqw_7 -- Fan Warning/Fail */
#define HB_FAN_FAIL_MASK        0x010F0F
#define HB_FAN_FAIL_WARN_MASK   0x00000F
#define HB_FAN_FAIL_FATAL_MASK  0x000F00

#define HB_FAN_SYS_FAN_WARN     (1UL << 0)
#define HB_FAN_PCI_FAN_WARN     (1UL << 1)
#define HB_FAN_CPU_FAN_WARN     (1UL << 2)
#define HB_FAN_DISK_FAN_WARN    (1UL << 3)

#define HB_FAN_SYS_FAN_FATAL    (1UL << 8)
#define HB_FAN_PCI_FAN_FATAL    (1UL << 9)
#define HB_FAN_CPU_FAN_FATAL    (1UL << 10)
#define HB_FAN_DISK_FAN_FATAL   (1UL << 11)

#define HB_FAN_MULTI_FAN_FAIL   (1UL << 16)

/* Masks for envqw_8 -- Fatal Summary */
#define HB_MISC_FAIL_MASK       0x030303033BEF
#define HB_MISC_PS_FAIL_MASK    0x0000000000EF

#define HB_MISC_PS_FAIL         (1UL << 0)
#define HB_MISC_165VRM_FAIL     (1UL << 1)
#define HB_MISC_250VRM_FAIL     (1UL << 2)
#define HB_MISC_330VRM_FAIL     (1UL << 3)
#define HB_MISC_VOLTAGE_FATAL   (1UL << 5)
#define HB_MISC_SCSIA_FAIL      (1UL << 6)
#define HB_MISC_SCSIB_FAIL      (1UL << 7)

#define HB_MISC_PS_OK_DEASSERT  (1UL << 8)
#define HB_MISC_165_DEASSERT    (1UL << 9)
#define HB_MISC_TIGRDY_DEASSERT (1UL << 11)
#define HB_MISC_CPURDY_DEASSERT (1UL << 12)
#define HB_MISC_165_EN_DEASSERT (1UL << 13)

#define HB_MISC_WDT_EXPIRED     (1UL << 16)
#define HB_MISC_WDT_RESET_SYS   (1UL << 17)

#define HB_MISC_RMC_DELAY_SHUT  (1UL << 24)
#define HB_MISC_RMC_IMMED_SHUT  (1UL << 25)

#define HB_MISC_SYSTEMP_FAIL    (1UL << 32)
#define HB_MISC_SYSTEMP_EMERG   (1UL << 33)

#define HB_MISC_FAN_FAIL        (1UL << 40)
#define HB_MISC_MULTI_FAN_FAIL  (1UL << 41)

/* This following structure is a redefinition of el_titan_680_logout_frame */
/*      that is specific to the HyperBrickII platform.                     */

struct  el_titan_hb_680_logout_frame {
    struct el_titan_mcheck_hdr  hdr;
    u_long                      swerr_summary_flags;    /* offset 0x18 */
    u_long                      cchip_dir;              /* offset 0x20 */
    u_long                      tig_info;               /* offset 0x28 */
    u_long                      rsvd0;
    u_long                      rmc_override_status;    /* offset 0x38 */
    u_long                      pwr_warn_fail;          /* offset 0x40 */
    u_long                      misc_rmc_warn_fail;     /* offset 0x48 */
    u_long                      temp_warn_fail;         /* offset 0x50 */
    u_long                      fan_warn_fail;          /* offset 0x58 */
    u_long                      fatal_summary;          /* offset 0x60 */
    u_long                      rsvd1;
};
