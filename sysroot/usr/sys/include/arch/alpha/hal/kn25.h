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
 * @(#)$RCSfile: kn25.h,v $ $Revision: 1.1.16.1 $ (DEC) $Date: 2002/01/24 18:53:42 $
 */
#ifndef	_ARCH_ALPHA_HAL_KN25_H
#define	_ARCH_ALPHA_HAL_KN25_H

#ifndef __cplusplus

/* should be in sio.h */

#define	SIO_PIRQ0	0x60
#define	SIO_PIRQ1	0x61
#define	SIO_PIRQ2	0x62
#define	SIO_PIRQ3	0x63
#define	SIO_ROUTE_ENABLE 0x80
#define	SIO_PIRQ_MASK	0xf


#define	KN25_810PCI_SLOT	6
#define	KN25_SIOPCI_SLOT	7
#define	KN25_PCI_SLOT0	11
#define	KN25_PCI_SLOT1	12
#define	KN25_PCI_SLOT2	13
#define	KN25_PCI_SLOT3	14

#define	KN25_SCSI_PCI_SLOT 1
#define KN25_810_IRQ	11

#define PCI_ISA_INDEX_REG	(APECS_IO_SPACE_FLAG | 0x26)
#define PCI_ISA_DATA_REG	(APECS_IO_SPACE_FLAG | 0x27)

#define	PCI_INTR_XLATE_REG	(0x14)
#define	PCI_INTR_LEVEL_REG	(0x15)
#define	PCI_ISA_CNTL_REG	(0x16)

#define	SIO_CNFG_REV	0x8

#define	IS_AN_ISA_DEVICE(a)	(strcmp((a)->bus_name, "isa") == 0)

#define MAX_CENTRAL_INTR	28
#define TABLE_FULL	-1

struct kn25_intr_key
{
    ihandler_id_t	hid_ptr;
    res_handle_t	res_handle;
};

#endif /* __cplusplus */
#endif	/* _ARCH_ALPHA_HAL_KN25_H */
