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
#pragma ident "@(#)$RCSfile: ti1130_reg.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2002/01/24 18:54:37 $"

#ifndef _TI1130_REG_H_
#define _TI1130_REG_H_

#ifndef __cplusplus

#include <io/common/devdriver.h>

/****************************************************************/
/*								*/
/* MODULE NAME: ti1130_reg.h					*/
/*								*/
/* LOCATION:  /src/kernel/io/dec/pcmcia				*/
/*								*/
/* DESCRIPTION:							*/
/* 	Contains definitions for TI1130 PCI-PCMCIA bus adapter.	*/
/*								*/
/****************************************************************/

#include <sys/types.h>

/*
 * Local resource structure for ti1130_request and release resource
 */
struct ti1130_resource_key {
    struct pci_sw *parent_sw;	/* Pointer to parent bus */
    res_handle_t bus_res_id;	/* Bus specific resource handle */
    struct pcmcia_bus_adapt *adap_ptr;	/* Pointer to the TI1130 adapter */
    u_int flags;
};

/* 
 * Operation Registers offset definition 
 *
 * These are accessed as index off the index register pointed
 * to by the PCI Base Address 0 register for this chip.
 *
 * To access these registers for the socket 1, add 40h to them.
 */

/*
 * TI Extention registers located in PCI config space for the adapter
 */
#define BRIDGE_CONTROL_REG	0x3e
#define SYSTEM_CONTROL_REG	0x80
#define RETRY_STATUS_REG	0x90
#define CARD_CONTROL_REG	0x91
#define DEVICE_CONTROL_REG	0x92
#define BUFFER_CONTROL_REG	0x93

/*
 * Bit definitions in the BRIDGE_CONTROL_REG
 */
#define BCR_WPE		0x0400		/* Write posting enable */
#define BCR_MW1T	0x0200		/* Memory window 1 type */
#define BCR_MW0T	0x0100		/* Memory window 0 type */
#define BCR_PCI_INT	0x0080		/* PCI interrupt routing */
#define BCR_CB_RESET	0x0040		/* CardBus Reset */
#define BCR_MAM		0x0020		/* Master abort mode */
#define BCR_VGA		0x0008		/* VGA enable */
#define BCR_ISA		0x0004		/* ISA enable */
#define BCR_SERR	0x0002		/* SERR enable */
#define BCR_PERE	0x0001		/* Parity error response enable */

/*
 * Bit definitions in the SYSTEM_CONTROL_REG
 */
#define SCR_SMI_IRS	0x04000000	/* SMI interrupt routing selected */
#define SCR_SMI_ISB	0x02000000	/* SMI interrupt status bit */
#define SCR_SMI_IME	0x01000000	/* SMI interrupt mode enable */
#define SCR_VPE		0x00200000	/* Vcc protection enable */
#define SCR_RZVE	0x00100000	/* Reduced zoom video enable*/
#define SCR_DCE		0x00080000	/* PC/PCI DMA Card Enable*/
#define SCR_SASB	0x00002000	/* Socket activity status bit*/
#define SCR_PSIP	0x00000800	/* Power stream in progress */
#define SCR_PDDIP	0x00000400	/* Power down delay in progress */
#define SCR_PUDIP	0x00000200	/* Power up delay in progress */
#define SCR_IIP		0x00000100	/* Interrogation in progress */
#define SCR_ROE		0x00000020	/* ExCA rev read only enable */
#define SCR_SSEB	0x00000010	/* Data parity SERR signal enable */
#define SCR_PDE		0x00000008	/* PC/PCI DMA enable bit */
#define SCR_AME		0x00000004	/* Asynchronous mode enable bit */
#define SCR_KCR		0x00000002	/* Keep PCI clock running */
#define SCR_CRE		0x00000001	/* PCI clock run enable */

/*
 * Bit definitions in the RETRY_STATUS_REGISTER
 */
#define RSR_PRTCE	0x80	/* PCI retry timeout counter enable */
#define RSR_CRTCE	0x40	/* CardBus retry timeout counter enable */
#define RSR_CBRES	0x20	/* CardBus B retry expired status */
#define RSR_CBMRES	0x10	/* CardBus B master retry expired status */
#define RSR_CARES	0x08	/* CardBus A retry expired status */
#define RSR_CAMRES	0x04	/* CardBus A master retry expired status */
#define RSR_PRES	0x02	/* PCI retry expired status */
#define RSR_PMRES	0x01	/* PCI master retry expired status */

/*
 * Bit defitions in the CARD_CONTROL_REGISTER
 */
#define CCR_RIOE	0x80	/* Ring indicate output enable */
#define CCR_ZVME	0x40	/* Zoom video mode enable */
#define CCR_PIE		0x20	/* PCI interrupt enable */
#define CCR_FIRE	0x10	/* Function interrupt routing enable */
#define CCR_CSCIRE	0x08	/* Card status change int routine enable */
#define CCR_SOSE	0x02	/* SpeakerOut/Suspend enable */
#define CCR_IFG		0x01	/* Interrupt flag */

/*
 * Bit defitions in the DEVICE_CONTROL_REGISTER
 */
#define DCR_5VFB	0x40	/* 5V socket capable force bit */
#define DCR_3VFB	0x20	/* 3V socket capable force bit */
#define DCR_RSVD1	0x10	/* Always set this be when writing the reg */
#define DCR_IIM		0x02	/* ISA interrupt mode */
#define DCR_CIM		0x04	/* Compaq interrupt mode */

/*
 * Bit defitions in the BUFFER_CONTROL_REGISTER
 */
#define BFCR_CRBD	0x08	/* CardBus read buffer depth */
#define BFCR_CWBD	0x04	/* CardBus write buffer depth */
#define BFCR_PRBD	0x02	/* PCI read buffer depth */
#define BFCR_PWBD	0x01	/* PCI write buffer depth */


/*
 * CardBus Socket registers
 */
#define SOCKET_EVENT_REG		0x00
#define SOCKET_MASK_REG			0x04
#define SOCKET_PRESENT_STATE_REG	0x08
#define SOCKET_FORCE_EVENT_REG		0x0C
#define SOCKET_CONTROL_REG		0x10
#define SOCKET_POWER_MANAGEMENT_REG	0x20

/*
 * Bit defitions in the	SOCKET_EVENT_REG
 */
#define SER_PC		0x00000008	/* Power cycle bit changed */
#define SER_CCD2	0x00000004	/* CCD2 bit changed */
#define SER_CCD1	0x00000002	/* CCD2 bit changed */
#define SER_CSTSCHG	0x00000001	/* CSTSSCHG bit changed */

/*
 * Bit defitions in the	SOCKET_MASK_REG
 */
#define SMR_PWRCYCLE	0x00000008	/* Enable power cycle interrupts */
#define SMR_CCD_MASK	0x00000006	/* Enable Card Detect interrupts*/
#define SMR_CSTSCHG	0x00000001	/* Enable CSTSSCHG interrupts*/

/*
 * Bit defitions in the	SOCKET_PRESENT_STATE_REG
 */
#define SPSR_YV_SOCKET	0x80000000	/* Socket can supply Vcc=Y.YV */
#define SPSR_XV_SOCKET	0x40000000	/* Socket can supply Vcc=X.XV */
#define SPSR_3V_SOCKET	0x20000000	/* Socket can supply Vcc=3V */
#define SPSR_5V_SOCKET	0x10000000	/* Socket can supply Vcc=5V */
#define SPSR_YV_CARD	0x00002000	/* Card inserted supports Vcc=Y.YV */
#define SPSR_XV_CARD	0x00001000	/* Card inserted supports Vcc=X.XV */
#define SPSR_3V_CARD	0x00000800	/* Card inserted supports Vcc=3V */
#define SPSR_5V_CARD	0x00000400	/* Card inserted supports Vcc=5V */
#define SPSR_BADVCCREQ	0x00000200	/* Host software requested a bad Vcc */
#define SPSR_DATALOST	0x00000100	/* Card eject caused data to be lost */
#define SPSR_NOTACARD	0x00000080	/* Invalid Card inserted */
#define SPSR_READY	0x00000040	/* Card ready or IRQ asserted */
#define SPSR_CBCARD	0x00000020	/* Card is a CardBus card */
#define SPSR_16BITCARD	0x00000010	/* Card is a 16 bit PC card */
#define SPSR_POWERCYCLE	0x00000008	/* Card has been power cycled */
#define SPSR_CD2	0x00000004	/* Card detect 2 */
#define SPSR_CD1	0x00000002	/* Card detect 1 */
#define SPSR_CDMASK	0x00000006	/* Bitmask of both CD1 and CD2 */
#define SPSR_CSTSCHG	0x00000001	/* Card status changed signal */

/*
 * Bit defitions in the	SOCKET_FORCE_EVENT_REG
 */
#define SFER_CVSTEST	0x00004000	/* Re-interrogate the Card */
#define SFER_YVCARD	0x00002000	/* Force the YV Card bit set */
#define SFER_XVCARD	0x00001000	/* Force the XV Card bit set */
#define SFER_3VCARD	0x00000800	/* Force the 3V Card bit set */
#define SFER_5VCARD	0x00000400	/* Force the 5V Card bit set */
#define SFER_BADVCCREQ	0x00000200	/* Force the bad VCC bit set */
#define SFER_DATALOST	0x00000100	/* Force the data lost bit set */
#define SFER_NOTACARD	0x00000080	/* Force the not-a-card bot set */
#define SFER_CBCARD	0x00000020	/* Force the CardBus card type */
#define SFER_16BITCARD	0x00000010	/* Force the 16 Bit card type */
#define SFER_POWERCYCLE	0x00000008	/* Force the power cycle bit set */
#define SFER_CCD2	0x00000004	/* Force the CCD2 bit to be set */
#define SFER_CCD1	0x00000002	/* Force the CCD1 bit to be set */
#define SFER_CSTSCHG	0x00000001	/* Force the status change bit set */

/*
 * Bit defitions in the	SOCKET_CONTROL_REG
 */
#define SKCR_STOPCLK	0x00000080	/* Placeholder.  Not functional */
#define SKCR_VCC5V	0x00000020	/* Drive Vcc=5V to the socket */
#define SKCR_VCC3V	0x00000030	/* Drive Vcc=3V to the socket */
#define SKCR_VCCXXV	0x00000040	/* Drive Vcc=X.XV to the socket */
#define SKCR_VCCYYV	0x00000050	/* Drive Vcc=Y.YV to the socket */
#define SKCR_VPP12V	0x00000001	/* Drive Vpp=12V to the socket */
#define SKCR_VPP5V	0x00000002	/* Drive Vcc=5V to the socket */
#define SKCR_VPP3V	0x00000003	/* Drive Vcc=3V to the socket */
#define SKCR_VPPXXV	0x00000004	/* Drive Vcc=X.XV to the socket */
#define SKCR_VPPYYV	0x00000005	/* Drive Vcc=Y.YV to the socket */

/*
 * ExCR registers
 */
#define ID_AND_REV_REG			0x800
#define	INTERFACE_STATUS_REG		0x801
#define POWER_CONTROL_REG		0x802
#define INTERRUPT_AND_CONTROL_REG	0x803
#define CARD_STATUS_CHANGE_REG		0x804
#define CARD_STATUS_CHANGE_INT_REG	0x805
#define ADDRESS_WINDOW_ENABLE_REG	0x806
#define IO_WINDOW_CONTROL_REG		0x807
#define CARD_DETECT_AND_GEN_CTL_REG	0x816
#define GLOBAL_CONTROL_REG		0x81e

/*
 * Bit defitions in the	INTERFACE_STATUS_REG
 */
#define	ISR_CP		0x40	/* Current state of card power to the socket */
#define ISR_READY	0x20	/* Card ready is asserted */
#define ISR_CWP		0x10	/* Card write protect */
#define ISR_CD_MASK	0x0C	/* Card Detect Mask */
#define ISR_BATT_MASK	0x03	/* Card Battery mask */
#define ISR_BG		0x03	/* Battery is good */
#define ISR_BL		0x02	/* Battery is going low */
#define ISR_BVD2	0x01	/* State of BV2 pin */
#define ISR_BVD1	0x02	/* State of BV1 pin */

/*
 * Bit defitions in the	POWER_CONTROL_REG
 */
#define PCR_COE 	0x80	/* Card outputs enable */
#define PCR_VCC_0V	0x00	/* Request Vcc = 0V */
#define PCR_VCC_3V	0x18	/* Request Vcc = 3V */
#define PCR_VCC_5V	0x10	/* Request Vcc = 5V */
#define PCR_VPP_0V	0x00	/* Set Vpp level of socket equal to 0V */
#define PCR_VPP_VCC	0x01	/* Set Vpp level of socket equal to Vcc */
#define PCR_VPP_12V	0x02	/* Set Vpp level of socket equal to 12v */

/*
 * Bit defitions in the	INTERRUPT_AND_CONTROL_REG
 */
#define ICR_CRIE	0x80	/* Card ring indicate enable */
#define ICR_NOTRESET	0x40	/* Card reset */
#define ICR_TYPE_IO	0x20	/* Card I/O type*/
#define ICR_PCRE	0x10	/* Route CSC interrupts through PCI */

/*
 * Bit defitions in the	CARD_STATUS_CHANGE_REG
 */
#define CSC_CDC		0x08	/* Card detect change*/
#define CSC_READY	0x04	/* Ready change */
#define CSC_BAT_LOW	0x02	/* Battery warning change */
#define CSC_BAT_DEAD	0x01	/* Battery dead or status change */

/*
 * Bit defitions in the	CARD_STATUS_CHANGE_INT_REG
 */
#define CSCI_CDCE	0x08	/* Card detect enable */
#define CSCI_RE		0x04	/* Ready enable */
#define CSCI_BLE	0x02	/* Battery warning enable */
#define CSCI_BDE	0x01	/* Battery dead enable */

/*
 * Bit defitions in the ADDRESS_WINDOW_ENABLE_REG
 */
#define AWE_IOW1E	0x80	/* I/O window 1 enable */
#define AWE_IOW0E	0x40	/* I/O window 0 enable */
#define AWE_MW4E	0x10	/* Memory window 4 enable */
#define AWE_MW3E	0x08	/* Memory window 3 enable */
#define AWE_MW2E	0x04	/* Memory window 2 enable */
#define AWE_MW1E	0x02	/* Memory window 1 enable */
#define AWE_MW0E	0x01	/* Memory window 0 enable */

/*
 * Bit defitions in the IO_WINDOW_CONTROL_REG
 */
#define IWC_IOW1WS	0x80	/* I/O window 1 wait state */
#define IWC_IOW1ZWS	0x40	/* I/O window 1 zero wait state */
#define IWC_IOW1S16S	0x20	/* I/O window 1 !IOIS16 source */
#define IWC_IOW1DS	0x10	/* I/O window 1 data size */
#define IWC_IOW0WS	0x08	/* I/O window 0 wait state */
#define IWC_IOW0ZWS	0x04	/* I/O window 0 zero wait state */
#define IWC_IOW0S16S	0x02	/* I/O window 0 !IOIS16 source */
#define IWC_IOW0DS	0x01	/* I/O window 0 data size */

/*
 * Bit defitions in the CARD_DETECT_AND_GEN_CTL_REG
 */
#define CDGC_VS2	0x80	/* State of the VS2 pin */
#define CDGC_VS1	0x40	/* State of the VS1 pin */
#define CDGC_SCDI	0x20	/* Software card detect enable */
#define CDGC_CDRE	0x10	/* Card detect resume enable */
#define CDGC_RCUCR	0x02	/* Register configuration upon card removal */

/*
 * Bit defitions in the GLOBAL_CONTROL_REG
 */
#define GCR_LEIMSB	0x10	/* Level/edge interrupt mode select card B*/
#define GCR_LEIMSA	0x08	/* Level/edge interrupt mode select card A */
#define GCR_IFCMS	0x04	/* Interrupt flag clear mode select */
#define GCR_CSCLEMS	0x02	/* Card status change level/edge mode select */
#define GCR_PMS		0x01	/* Powerdown mode select */

/*
 * I/O Registers 
 */
#define IO_WINDOW_CTRL			0x807
#define IO_START_LOW_0			0x808
#define IO_START_HIGH_0			0x809
#define IO_END_LOW_0			0x80a
#define IO_END_HIGH_0			0x80b

#define IO_START_LOW_1			0x80c
#define IO_START_HIGH_1			0x80d
#define IO_END_LOW_1			0x80e
#define IO_END_HIGH_1			0x80f

/*
 * Memory Registers
 */
#define MEM_START_LOW_0			0x810
#define MEM_START_HIGH_0		0x811
#define MEM_END_LOW_0			0x812
#define MEM_END_HIGH_0			0x813
#define MEM_OFFSET_LOW_0		0x814
#define MEM_OFFSET_HIGH_0		0x815

#define MEM_START_LOW_1			0x818
#define MEM_START_HIGH_1		0x819
#define MEM_END_LOW_1			0x81a
#define MEM_END_HIGH_1			0x81b
#define MEM_OFFSET_LOW_1		0x81c
#define MEM_OFFSET_HIGH_1		0x81d

#define MEM_START_LOW_2			0x820
#define MEM_START_HIGH_2		0x821
#define MEM_END_LOW_2			0x822
#define MEM_END_HIGH_2			0x823
#define MEM_OFFSET_LOW_2		0x824
#define MEM_OFFSET_HIGH_2		0x825

#define MEM_START_LOW_3			0x828
#define MEM_START_HIGH_3		0x829
#define MEM_END_LOW_3			0x82a
#define MEM_END_HIGH_3			0x82b
#define MEM_OFFSET_LOW_3		0x82c
#define MEM_OFFSET_HIGH_3		0x82d

#define MEM_START_LOW_4			0x830
#define MEM_START_HIGH_4		0x831
#define MEM_END_LOW_4			0x832
#define MEM_END_HIGH_4			0x833
#define MEM_OFFSET_LOW_4		0x834
#define MEM_OFFSET_HIGH_4		0x835

#define MEMORY_WINDOW_0_PAGE_REG	0x840
#define MEMORY_WINDOW_1_PAGE_REG	0x841
#define MEMORY_WINDOW_2_PAGE_REG	0x842
#define MEMORY_WINDOW_3_PAGE_REG	0x843
#define MEMORY_WINDOW_4_PAGE_REG	0x844
/*
 * Defines for setting up memory address register contents
 */
#define LOW_SHIFT	12
#define HIGH_SHIFT	20
#define UPPER_SHIFT     24
#define LOW_MASK	0xff
#define HIGH_MASK	0xf
#define UPPER_MASK	0xff
#define OFFSET_ORMASK	0x30	/* bit 4 and 5 must be 1's for offset reg. */ 

/*
 * Defines for memory window start address high reg
 */
#define MWSAH_DS	0x80	/* Data Size */
#define MWSAH_ZWS	0x40	/* Zero wait state */

/*
 * Defines for memory window send address high reg
 */
#define WAIT_STATE_1	  0x40		/* 1 additional wait state */
#define WAIT_STATE_2	  0x80		/* 2 additional wait states */
#define WAIT_STATE_3	  0xc0		/* 3 additional wait states */

/*
 * Defines for memory window offset address high reg
 */
#define MWOAH_WP	0x80	/* Write protect */
#define MWOAH_AME	0x40	/* REG - Set to indicate attribute memory */

/*
 * ISA Memory Space starting address to set up for memory window mapping
 *
 * (TBD) This address probably should be determined by the platform-specific
 *	 code, as each platform can have different set up/layout of the
 *	 memory space.
 */

#define ISA_MEM_START_ADDR 	0xd0000 	/* 832 K bytes */
#define ISA_MEM_END_ADDR	0x100000

#endif /* __cplusplus */
#endif  /* _TI1130_REG_H_ */
