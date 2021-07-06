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
 * @(#)$RCSfile: wfqbb.h,v $ $Revision: 1.1.31.1 $ (DEC) $Date: 2002/01/03 14:09:32 $
 */

#ifndef __ARCH_ALPHA_HAL_WFQBB_H__
#define __ARCH_ALPHA_HAL_WFQBB_H__

/*
 * --------------------------------------------
 * WildFire (Programmer's) Physical Address Map:
 * --------------------------------------------
 *
 * System-Level Address Space Layout
 * ---------------------------------
 * +---+-------+----------------------------------------------------+
 * | I |  QBB  | <35:24,23,22:0> = <FFF,1,Offset> = QBB CSR space   | 
 * | O |  ID   | <35:0>          = 0->F.FF7F.FFFF = sub-IOP IO Space| 
 * +---+-------+----------------------------------------------------+
 *  XX  YY   36 35                    23
 *   
 * <XX> - I/O-Memory Select (Always 1 for direct I/O access)
 *	- bit 40 in 43-bit VA mode.
 *	- bit 43 in 48-bit VA mode;
 *
 * <YY> - Max. QBB ID bit
 *	- bit 39 in 43-bit VA mode (up to 16 QBBs)
 *	- bit 41 in 48-bit VA mode (up to architectural max of 64)
 *	NOTE: QBB_ID is inverted for IO accesses
 *
 * Physical Memory Space (64GBytes per QBB) 
 * ----------------------------------------
 *	QBB	QBB_ID			    Range
 *	 0	  0		000.0000.0000 - 00F.FFFF.FFFF
 *	 1	  1		010.0000.0000 - 01F.FFFF.FFFF
 *	 2	  2		020.0000.0000 - 02F.FFFF.FFFF
 *	...	.....		     ...	     ...
 *	16	 16		0F0.0000.0000 - 0FF.FFFF.FFFF
 *			(end of 41-bit Physical, 43-bit VA mode)
 *	...	.....		     ...	     ...
 *	63	 63		3F0.0000.0000 - 3FF.FFFF.FFFF
 *			(end of 44-bit Physical, 48-bit VA mode)
 *
 * Physical IO Space (64GBytes per QBB) 
 * ----------------------------------------
 *	QBB	QBB_ID			    Range
 *	 0	 63		FF0.0000.0000 - FFF.FFFF.FFFF
 *	 1	 62		FE0.0000.0000 - FEF.FFFF.FFFF
 *	 2	 61		FD0.0000.0000 - FDF.FFFF.FFFF
 *	...	.....		     ...	     ...
 *	16	 48		F00.0000.0000 - F0F.FFFF.FFFF
 *			(end of 41-bit Physical, 43-bit VA mode)
 *	...	.....		     ...	     ...
 *	63	  0		C00.0000.0000 - C0F.FFFF.FFFF
 *			(end of 44-bit Physical, 48-bit VA mode)
 */

/*
 * --------------------------------------------
 * WildFire (Programmer's) Physical Address Map:
 * --------------------------------------------
 *
 * QBB CSR Space - 8MB per QBB
 * ---------------------------
 * +---+-------+------------------------+--------+--------------+
 * | I |  QBB  |         FFF,1          | Entity |    Address   |
 * | O |  ID   |                        |   ID   |    Offset    | 
 * +---+-------+------------------------+--------+--------------+
 *  XX  YY   36 35                    23 22    18 17           0
 * 
 * <XX,YY> - <40,39> in 43-bit VA mode.
 *	   - <43,41> in 48-bit VA mode;
 *
 * NOTE: QBB_ID is inverted for QBB CSR Space (QBB=0 -> QBB_ID=63)
 *
 *	Entity_ID	Entity Name
 *	   1		  Fast QSD
 *	   4		  QSA
 *	   5		  QSD
 *	   6		  DIRectory
 *	   8		  IOP
 *	  12		  IOP Port 0 (PCA 0, PCI 0,1)
 *	  13		  IOP Port 1 (PCA 1, PCI 2,3)
 *	  14		  IOP Port 2 (PCA 2, PCI 4,5)
 *	  15		  IOP Port 3 (PCA 3, PCI 6,7)
 *	  16		  GP (Global Port)
 *	  17		  HS (Hierarchical Switch)
 *	  20		  Memory 0
 *	  21		  Memory 1
 *	  22		  Memory 2
 *	  23		  Memory 3
 *	  24		  DTAG 0 (Duplicate TAG)
 *	  25		  DTAG 1 (Duplicate TAG)
 *	  26		  DTAG 2 (Duplicate TAG)
 *	  27		  DTAG 3 (Duplicate TAG)
 *	  28		  DTAG 4 (Duplicate TAG)
 *	  29		  DTAG 5 (Duplicate TAG)
 *	  30		  DTAG 6 (Duplicate TAG)
 *	  31	 	  DTAG 7 (Duplicate TAG)
 * 
 * QBB-0 CSR Address Map (256K per Entity):
 * ---------------------------------------
 * 41-bit PA, 43-bit VA mode
 *	QBB Entity			Address Range
 *	 Fast QSD	1FF.FF84.0000.0000 - 1FF.FF87.FFFF.FFFF
 *	  QSA		1FF.FF90.0000.0000 - 1FF.FF93.FFFF.FFFF
 *	  QSD		1FF.FF94.0000.0000 - 1FF.FF97.FFFF.FFFF
 *	  DIR		1FF.FF98.0000.0000 - 1FF.FF9A.FFFF.FFFF
 *	  IOP		1FF.FFA0.0000.0000 - 1FF.FFA3.FFFF.FFFF
 *	  IOP0/PCA0,1	1FF.FFB0.0000.0000 - 1FF.FFB3.FFFF.FFFF
 *	  IOP1/PCA2,3	1FF.FFB4.0000.0000 - 1FF.FFB7.FFFF.FFFF
 *	  IOP2/PCA4,5	1FF.FFB8.0000.0000 - 1FF.FFBB.FFFF.FFFF
 *	  IOP3/PCA6,7	1FF.FFBC.0000.0000 - 1FF.FFBC.FFFF.FFFF
 *	  GP		1FF.FFC0.0000.0000 - 1FF.FFC3.FFFF.FFFF
 *	  HS		1FF.FFC4.0000.0000 - 1FF.FFC7.FFFF.FFFF
 *	  MEM0		1FF.FFD0.0000.0000 - 1FF.FFD3.FFFF.FFFF
 *	  MEM1		1FF.FFD4.0000.0000 - 1FF.FFD7.FFFF.FFFF
 *	  MEM2		1FF.FFD8.0000.0000 - 1FF.FFDB.FFFF.FFFF
 *	  MEM3		1FF.FFDC.0000.0000 - 1FF.FFDF.FFFF.FFFF
 *	  DTAG0		1FF.FFE0.0000.0000 - 1FF.FFE3.FFFF.FFFF
 *	  DTAG1		1FF.FFE4.0000.0000 - 1FF.FFE7.FFFF.FFFF
 *	  DTAG2		1FF.FFE8.0000.0000 - 1FF.FFEB.FFFF.FFFF
 *	  DTAG3		1FF.FFEC.0000.0000 - 1FF.FFEF.FFFF.FFFF
 *	  DTAG4		1FF.FFF0.0000.0000 - 1FF.FFF3.FFFF.FFFF
 *	  DTAG5		1FF.FFF4.0000.0000 - 1FF.FFF7.FFFF.FFFF
 *	  DTAG6		1FF.FFF8.0000.0000 - 1FF.FFFB.FFFF.FFFF
 *	  DTAG7		1FF.FFFC.0000.0000 - 1FF.FFFF.FFFF.FFFF
 */

/*
 * --------------------------------------------
 * WildFire (Programmer's) Physical Address Map:
 * --------------------------------------------
 *
 * Sub-IOP IO Address Space - 64GB-8MB per IOP 
 * -------------------------------------------
 *
 * PCI Address Space per IOP (per QBB)
 * -----------------------------------
 * +---+-------+-----------------+-------------------------+
 * | I |  QBB  | PCI Hose /      |     Address             | 
 * | O |  ID   | Primary_Bus Num |     Offset              | 
 * +---+-------+-----------------+-------------------------+
 *  XX  YY   36 35             33 32                      0
 * 
 * <XX,YY> - <40,39> in 43-bit VA mode.
 *	   - <43,41> in 48-bit VA mode;
 *
 * NOTE: QBB_ID is inverted for QBB CSR Space (QBB=0 -> QBB_ID=63)
 *
 * QBB Physical PCI Address Map -- 41-bit PA, 43-bit VA mode
 * ---------------------------------------------------------
 * QBB-0, PCI-0		1F0 0000 0000 - 1F1 FF7F FFFF (PCA-0, PCI-0)
 * QBB-0, PCI-1		1F2 0000 0000 - 1F3 FF7F FFFF (PCA-0, PCI-1)
 * QBB-0, PCI-2		1F4 0000 0000 - 1F5 FF7F FFFF (PCA-1, PCI-0)
 * QBB-0, PCI-3		1F6 0000 0000 - 1F7 FF7F FFFF (PCA-1, PCI-1)
 * QBB-0, PCI-4		1F8 0000 0000 - 1F9 FF7F FFFF (PCA-2, PCI-0)
 * QBB-0, PCI-5		1FA 0000 0000 - 1FA FF7F FFFF (PCA-2, PCI-1)
 * QBB-0, PCI-6		1FC 0000 0000 - 1FC FF7F FFFF (PCA-3, PCI-0)
 * QBB-0, PCI-7		1FE 0000 0000 - 1FF FF7F FFFF (PCA-3, PCI-1)
 *
 * QBB-1, PCI-0		1E0 0000 0000 - 1E1 FF7F FFFF (PCA-0, PCI-0)
 *	...			      ...
 * QBB-1, PCI-7		1EE 0000 0000 - 1EF FF7F FFFF (PCA-3, PCI-1)
 *	...			      ...
 * QBB-15,PCI-0		100 0000 0000 - 101 FF7F FFFF (PCA-0, PCI-0)
 *	...			      ...
 * QBB-15,PCI-7		10E 0000 0000 - 10F FF7F FFFF (PCA-3, PCI-1)
 *
 * QBB Physical PCI Address Map -- 44-bit PA, 48-bit VA mode
 * ---------------------------------------------------------
 * QBB-0, PCI-0		8F0 0000 0000 - 8F1 FF7F FFFF (PCA-0, PCI-0)
 *	...			      ...
 * QBB-15,PCI-7		80E 0000 0000 - 80F FF7F FFFF (PCA-3, PCI-1)
 */


/*
 * --------------------------------------------
 * WildFire (Programmer's) Physical Address Map:
 * --------------------------------------------
 *
 * Per-PCI Address Space (8GB per PCI)
 * -----------------------------------
 * +---+-------+-----------------+-------------------------+
 * | I |  QBB  | PCI Hose /      |     Address             | 
 * | O |  ID   | Primary_Bus Num |     Offset              | 
 * +---+-------+-----------------+-------------------------+
 *  XX  YY   36 35             33 32                      0
 * 
 * <XX,YY> - <40,39> in 43-bit VA mode.
 *	   - <43,41> in 48-bit VA mode;
 *
 * <35:33> - PCI Bus Select
 *	
 * <32:23> - PCI Address Space
 *	0.xxxx.xxxx.x = PCI Memory Space	  4GB
 *	1.1111.1110.x = PCI Configuration Space  16MB
 *	1.1111.1111.0 = PCI I/O Space	          8MB
 *
 * -------------------------
 * WFCPU-PCA Address Map: (continued)
 * -------------------------
 *
 * ---------------------------------------------------
 * CPU to PCI Physical Address Mapping for PCIy Bridge 
 * ---------------------------------------------------
 *
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * mQ(n*2).0000.0000		0000.0000 - FFFF.FFFF	QBBq, PCIn Memory Space 
 *  - mQ(n*2).FFFF.FFFF					(4GB, linear)
 *
 * mQ[(n*2)+1].FE00.0000	0000.0000 - 00FF.FFFF	QBBq, PCIn Config. Space 
 *  - mQ[(n*2)+1].FEFF.FFFF				(16MB, linear)
 *
 * mQ[(n*2)+1].FF00.0000	0000.0000 - 01FF.FFFF	QBBq, PCIn IO Space 
 *  - mQ[(n*2)+1].FF7F.FFFF				(8MB, linear)
 *
 * where 
 *	x = 1 when OS in 43-bit VA mode; 8 when OS in 48-bit VA mode.
 * 	q = QBB number
 * 	Q = QBB_ID, which is the inverse the QBB number q for IO space.
 * 	n = PCI primary_bus-hose number, which can be 0,1,2,3,4,5,6,7.
 *
 */
 
/*
 * QBB Physical PCI Address Map -- 41-bit PA, 43-bit VA mode
 * ---------------------------------------------------------
 * QBB-0:
 *        PCI-0, Mem	1F0 0000 0000 - 1F0 FFFF FFFF (PCA-0, PCI-0)
 *               I/O	1F1 FF00 0000 - 1F1 FF7F FFFF (PCA-0, PCI-0)
 *               Config	1F1 FE00 0000 - 1F1 FEFF FFFF (PCA-0, PCI-0)
 *
 *        PCI-1, Mem	1F2 0000 0000 - 1F2 FFFF FFFF (PCA-0, PCI-1)
 *               I/O	1F3 FF00 0000 - 1F3 FF7F FFFF (PCA-0, PCI-1)
 *               Config	1F3 FE00 0000 - 1F3 FEFF FFFF (PCA-0, PCI-1)
 *
 *        PCI-2, Mem	1F4 0000 0000 - 1F4 FFFF FFFF (PCA-1, PCI-0)
 *               I/O	1F5 FF00 0000 - 1F5 FF7F FFFF (PCA-1, PCI-0)
 *               Config	1F5 FE00 0000 - 1F5 FEFF FFFF (PCA-1, PCI-0)
 *
 *        PCI-3, Mem	1F6 0000 0000 - 1F6 FFFF FFFF (PCA-1, PCI-1)
 *               I/O	1F7 FF00 0000 - 1F7 FF7F FFFF (PCA-1, PCI-1)
 *               Config	1F7 FE00 0000 - 1F7 FEFF FFFF (PCA-1, PCI-1)
 *
 *        PCI-4, Mem	1F8 0000 0000 - 1F8 FFFF FFFF (PCA-2, PCI-0)
 *               I/O	1F1 FF00 0000 - 1F1 FF7F FFFF (PCA-2, PCI-0)
 *               Config	1F1 FE00 0000 - 1F1 FEFF FFFF (PCA-2, PCI-0)
 *
 *        PCI-5, Mem	1FA 0000 0000 - 1FA FFFF FFFF (PCA-2, PCI-1)
 *               I/O	1FB FF00 0000 - 1FB FF7F FFFF (PCA-2, PCI-1)
 *               Config	1FB FE00 0000 - 1FB FEFF FFFF (PCA-2, PCI-1)
 *
 *        PCI-6, Mem	1FC 0000 0000 - 1FA FFFF FFFF (PCA-3, PCI-0)
 *               I/O	1FD FF00 0000 - 1FD FF7F FFFF (PCA-3, PCI-0)
 *               Config	1FD FE00 0000 - 1FD FEFF FFFF (PCA-3, PCI-0)
 *
 *        PCI-7, Mem	1FE 0000 0000 - 1FE FFFF FFFF (PCA-3, PCI-1)
 *               I/O	1FF FF00 0000 - 1FF FF7F FFFF (PCA-3, PCI-1)
 *               Config	1FF FE00 0000 - 1FF FEFF FFFF (PCA-3, PCI-1)
 *
 * QBB-1:
 *        PCI-0, Mem	1E0 0000 0000 - 1E0 FFFF FFFF (PCA-0, PCI-0)
 *               I/O	1E1 FF00 0000 - 1E1 FF7F FFFF (PCA-0, PCI-0)
 *               Config	1E1 FE00 0000 - 1E1 FEFF FFFF (PCA-0, PCI-0)
 *
 *        PCI-1, Mem	1E2 0000 0000 - 1E2 FFFF FFFF (PCA-0, PCI-1)
 *               I/O	1E3 FF00 0000 - 1E3 FF7F FFFF (PCA-0, PCI-1)
 *               Config	1E3 FE00 0000 - 1E3 FEFF FFFF (PCA-0, PCI-1)
 *
 *        PCI-2, Mem	1E4 0000 0000 - 1E4 FFFF FFFF (PCA-1, PCI-0)
 *               I/O	1E5 FF00 0000 - 1E5 FF7F FFFF (PCA-1, PCI-0)
 *               Config	1E5 FE00 0000 - 1E5 FEFF FFFF (PCA-1, PCI-0)
 *
 *        PCI-3, Mem	1E6 0000 0000 - 1E6 FFFF FFFF (PCA-1, PCI-1)
 *               I/O	1E7 FF00 0000 - 1E7 FF7F FFFF (PCA-1, PCI-1)
 *               Config	1E7 FE00 0000 - 1E7 FEFF FFFF (PCA-1, PCI-1)
 *
 *        PCI-4, Mem	1E8 0000 0000 - 1E8 FFFF FFFF (PCA-2, PCI-0)
 *               I/O	1E1 FF00 0000 - 1E1 FF7F FFFF (PCA-2, PCI-0)
 *               Config	1E1 FE00 0000 - 1E1 FEFF FFFF (PCA-2, PCI-0)
 *
 *        PCI-5, Mem	1EA 0000 0000 - 1EA FFFF FFFF (PCA-2, PCI-1)
 *               I/O	1EB FF00 0000 - 1EB FF7F FFFF (PCA-2, PCI-1)
 *               Config	1EB FE00 0000 - 1EB FEFF FFFF (PCA-2, PCI-1)
 *
 *        PCI-6, Mem	1EC 0000 0000 - 1EA FFFF FFFF (PCA-3, PCI-0)
 *               I/O	1ED FF00 0000 - 1ED FF7F FFFF (PCA-3, PCI-0)
 *               Config	1ED FE00 0000 - 1ED FEFF FFFF (PCA-3, PCI-0)
 *
 *        PCI-7, Mem	1EE 0000 0000 - 1EE FFFF FFFF (PCA-3, PCI-1)
 *               I/O	1EF FF00 0000 - 1EF FF7F FFFF (PCA-3, PCI-1)
 *               Config	1EF FE00 0000 - 1EF FEFF FFFF (PCA-3, PCI-1)
 *
 * QBB-15:
 *        PCI-0, Mem	100 0000 0000 - 100 FFFF FFFF (PCA-0, PCI-0)
 *               I/O	101 FF00 0000 - 101 FF7F FFFF (PCA-0, PCI-0)
 *               Config	101 FE00 0000 - 101 FEFF FFFF (PCA-0, PCI-0)
 *
 *        PCI-1, Mem	102 0000 0000 - 102 FFFF FFFF (PCA-0, PCI-1)
 *               I/O	103 FF00 0000 - 103 FF7F FFFF (PCA-0, PCI-1)
 *               Config	103 FE00 0000 - 103 FEFF FFFF (PCA-0, PCI-1)
 *
 *        PCI-2, Mem	104 0000 0000 - 104 FFFF FFFF (PCA-1, PCI-0)
 *               I/O	105 FF00 0000 - 105 FF7F FFFF (PCA-1, PCI-0)
 *               Config	105 FE00 0000 - 105 FEFF FFFF (PCA-1, PCI-0)
 *
 *        PCI-3, Mem	106 0000 0000 - 106 FFFF FFFF (PCA-1, PCI-1)
 *               I/O	107 FF00 0000 - 107 FF7F FFFF (PCA-1, PCI-1)
 *               Config	107 FE00 0000 - 107 FEFF FFFF (PCA-1, PCI-1)
 *
 *        PCI-4, Mem	108 0000 0000 - 108 FFFF FFFF (PCA-2, PCI-0)
 *               I/O	101 FF00 0000 - 101 FF7F FFFF (PCA-2, PCI-0)
 *               Config	101 FE00 0000 - 101 FEFF FFFF (PCA-2, PCI-0)
 *
 *        PCI-5, Mem	10A 0000 0000 - 10A FFFF FFFF (PCA-2, PCI-1)
 *               I/O	10B FF00 0000 - 10B FF7F FFFF (PCA-2, PCI-1)
 *               Config	10B FE00 0000 - 10B FEFF FFFF (PCA-2, PCI-1)
 *
 *        PCI-6, Mem	10C 0000 0000 - 10A FFFF FFFF (PCA-3, PCI-0)
 *               I/O	10D FF00 0000 - 10D FF7F FFFF (PCA-3, PCI-0)
 *               Config	10D FE00 0000 - 10D FEFF FFFF (PCA-3, PCI-0)
 *
 *        PCI-7, Mem	10E 0000 0000 - 10E FFFF FFFF (PCA-3, PCI-1)
 *               I/O	10F FF00 0000 - 10F FF7F FFFF (PCA-3, PCI-1)
 *               Config	10F FE00 0000 - 10F FEFF FFFF (PCA-3, PCI-1)
 *
 */


/*
 * Wildfire Quad-switch register structure & bit definitions
 */

/* Entity 1, offset FFF.FF84.0000 */
/*	     Note: no QBB_ID in offset */
struct wf_fast_qsd_csrs {
	u_long	whami;
	u_long	pad0[7];
	u_long	pad1[8];
	u_long	pad2[8];
	u_long	pad3[8];
	u_long	pad4[8];
	u_long	pad5[8];
	u_long	pad6[8];
	u_long	pad7[8];
	struct	cpu_ce {	    /* offset 200 */
		u_long	sum;
		u_long	pad8[7];
	} cpu_ce_sum[4];
	struct	cpu_dev {	    /* offset 300 */
		u_long	intr;
		u_long	pad12[7];
	} cpu_dev_int[4];
	struct	cpu_it {
		u_long	intr; /* offset 400 */
		u_long	pad16[7];
	} cpu_it_int[4];
	struct	cpu_ip_ {
		u_long	intr;	/* offset 500 */
		u_long	pad20[7];
	} cpu_ip_int[4];
	struct	cpu_uce{
		u_long	sum;	/* offset 600 */
		u_long	pad24[7];
	} cpu_uce_sum[4];
	struct	cpu_se {
		u_long	sum;	/* offset 700 */
		u_long	pad28[7];
	} cpu_se_sum[4];
};

/* Entity 4, QBB offset F.FF90.0000 */
/*
 * CSRs on 2048-byte boundaries 
 * -- offset 0, 0x1000, 0x1800, etc. 
 *    unless commented otherwise 
 */
struct wf_qsa_csrs {
	u_long	qbb_id;
	u_long	pad0[511];
	u_long	port_ena;	/* offset 1000 */
	u_long	pad2[255];
	u_long	scratch;	/* offset 1800 */
	u_long	pad3[255];
	u_long	config_0;
	u_long	pad4[255];
	u_long	config_1;
	u_long	pad5[255];
	u_long	config_2;
	u_long	pad6[255];
	u_long	config_3;
	u_long	pad7[255];
	u_long	ref_int;
	u_long	pad8[255];
	u_long	qbb_pop_0;
	u_long	pad9[255];
	u_long	qbb_pop_1;	/* offset 5800 */
	u_long	pad10[1279];
	u_long	diag;		/* offset 8000 */
	u_long	pad11[255];
	u_long	diag_lock_0;
	u_long	pad12[255];
	u_long	diag_lock_1;
	u_long	pad13[255];
	u_long	diag_lock_2;
	u_long	pad14[255];
	u_long	diag_lock_3;	/* offset 0.A000 */
	u_long	pad15[3071];
	u_long	cpu_err_sum;	/* offset 1.0000 */
	u_long	pad16[255];
	u_long	misc_err_sum;
	u_long	pad17[255];
	u_long	tmo_err_sum;
	u_long	pad18[255];
	u_long	err_ena;
	u_long	pad19[255];
	u_long	tmo_config;
	u_long	pad20[255];
	u_long	ill_cmd_err_sum; /* offset 1.2800 */
	u_long	pad21[6911];
	u_long	busy_mask;	/* offset  2.0000 */
	u_long	pad22[255];
	u_long	arr_valid;	/* offset  2.0800 */
	u_long	pad23[767];
	u_long	port_map_0;	/* offset  2.2000 */
	u_long	pad24[255];
	u_long	port_map_1;
	u_long	pad25[255];
	u_long	port_map_2;
	u_long	pad26[255];
	u_long	port_map_3;
	u_long	pad27[255];
	u_long	arr_addr_0;	/* offset  2.4000 */
	u_long	pad28[255];
	u_long	arr_addr_1;
	u_long	pad29[255];
	u_long	arr_addr_2;
	u_long	pad30[255];
	u_long	arr_addr_3;
	u_long	pad31[255];
	u_long	arr_addr_4;
	u_long	pad32[255];
	u_long	arr_addr_5;
	u_long	pad33[255];
	u_long	arr_addr_6;
	u_long	pad34[255];
	u_long	arr_addr_7;
	u_long	pad35[255];
	u_long	arr_mask_0;	/* offset  2.8000 */
	u_long	pad36[255];
	u_long	arr_mask_1;
	u_long	pad37[255];
	u_long	arr_mask_2;
	u_long	pad38[255];
	u_long	arr_mask_3;
	u_long	pad39[255];
	u_long	arr_mask_4;
	u_long	pad40[255];
	u_long	arr_mask_5;
	u_long	pad41[255];
	u_long	arr_mask_6;
	u_long	pad42[255];
	u_long	arr_mask_7;
};

/* Entity 5, QBB offset F.FF94.0000 */
struct wf_qsd_csrs {
	u_long	whami;
	u_long	pad0[7];
	u_long	rev;
	u_long	pad1[7];
	u_long	port_present;
	u_long	pad2[7];
	u_long	port_active;
	u_long	pad3[7];
	u_long	fault_ena;
	u_long	pad4[7];
	u_long	cpu_int_ena;
	u_long	pad5[7];
	u_long	mem_config;
	u_long	pad6[7];
	u_long	err_sum;
	u_long	pad7[7];
	u_long	cpu0_ce_sum;
	u_long	pad8[7];
	u_long	cpu1_ce_sum;
	u_long	pad9[7];
	u_long	cpu2_ce_sum;
	u_long	pad10[7];
	u_long	cpu3_ce_sum;
	u_long	pad11[7];
	u_long	cpu0_dev_int;
	u_long	pad12[7];
	u_long	cpu1_dev_int;
	u_long	pad13[7];
	u_long	cpu2_dev_int;
	u_long	pad14[7];
	u_long	cpu3_dev_int;
	u_long	pad15[7];
	u_long	cpu0_it_int;
	u_long	pad16[7];
	u_long	cpu1_it_int;
	u_long	pad17[7];
	u_long	cpu2_it_int;
	u_long	pad18[7];
	u_long	cpu3_it_int;
	u_long	pad19[7];
	u_long	cpu0_ip_int;
	u_long	pad20[7];
	u_long	cpu1_ip_int;
	u_long	pad21[7];
	u_long	cpu2_ip_int;
	u_long	pad22[7];
	u_long	cpu3_ip_int;
	u_long	pad23[7];
	u_long	cpu0_uce_sum;
	u_long	pad24[7];
	u_long	cpu1_uce_sum;
	u_long	pad25[7];
	u_long	cpu2_uce_sum;
	u_long	pad26[7];
	u_long	cpu3_uce_sum;
	u_long	pad27[7];
	u_long	cpu0_se_sum;
	u_long	pad28[7];
	u_long	cpu1_se_sum;
	u_long	pad29[7];
	u_long	cpu2_se_sum;
	u_long	pad30[7];
	u_long	cpu3_se_sum;
	u_long	pad31[7];
	u_long	cpu0_scratch;
	u_long	pad32[7];
	u_long	cpu1_scratch;
	u_long	pad33[7];
	u_long	cpu2_scratch;
	u_long	pad34[7];
	u_long	cpu3_scratch;
	u_long	pad35[7];
	u_long	timer;
	u_long	pad36[7];
	u_long	diag;
};
/*
 * Map QSD's CPUn_NON_DEV_INT register to CPUn_SE_SUM
 *	
 * CPUn_NON_DEV_INT registers are write-only;
 * CPUn_SE_SUM are read-only
 * -- both are mapped to the same address, thus the 
 *    equivalence define below.
 */
#define cpu0_non_dev_int cpu0_se_sum
#define cpu1_non_dev_int cpu1_se_sum
#define cpu2_non_dev_int cpu2_se_sum
#define cpu3_non_dev_int cpu3_se_sum

/* Entity 6, QBB offset F.FF98.0000 */
struct wf_dir_csrs {
	u_long dir_err_sum;
	u_long	pad16[255];
	u_long dir_ce_trap_0_a;
	u_long	pad0[255];
	u_long dir_ce_trap_0_b;
	u_long	pad1[255];
	u_long dir_ce_trap_0_c;
	u_long	pad2[255];
	u_long dir_ce_trap_1_a;
	u_long	pad3[255];
	u_long dir_ce_trap_1_b;
	u_long	pad4[255];
	u_long dir_ce_trap_1_c;
	u_long	pad5[255];
	u_long dir_ce_trap_2_a;
	u_long	pad6[255];
	u_long dir_ce_trap_2_b;
	u_long	pad7[255];
	u_long dir_ce_trap_2_c;
	u_long	pad8[255];
	u_long dir_ce_trap_3_a;
	u_long	pad9[255];
	u_long dir_ce_trap_3_b;
	u_long	pad10[255];
	u_long dir_ce_trap_3_c;
	u_long	pad11[255];
	u_long dir_uce_trap_a;
	u_long	pad12[255];
	u_long dir_uce_trap_b;
	u_long	pad13[255];
	u_long dir_uce_trap_c;
	u_long	pad14[2560];
	u_long dir_err_detect_a;
	u_long	pad15[255];
	u_long dir_err_detect_b;
};

/* Entity 8, offset F.FFA0.0000
 * IOP0 = Entity 12
 *	...
 * IOP3 = Entity 15
 *
 * CSRs on 64-byte boundaries 
 */
struct wf_iop_csrs {
	u_long	ioa_config;
	u_long	pad0[7];
	u_long	iod_config;
	u_long	pad1[7];
	u_long	iop_switch_credits;
	u_long	pad2[7];
	u_long	iop_hose_credits;
	u_long	pad3[103];
	u_long	hose_0_init;	/* offset 440 */
	u_long	pad4[15];
	u_long	hose_1_init;	/* offset 4C0 */
	u_long	pad5[15];
	u_long	hose_2_init;	/* offset 540 */
	u_long	pad6[15];
	u_long	hose_3_init;	/* offset 5C0 */
	u_long	pad7[7];
	u_long	ioa_hose_0_ctrl; /* offset 600 */
	u_long	pad8[7];
	u_long	iod_hose_0_ctrl;
	u_long	pad9[7];
	u_long	ioa_hose_1_ctrl;
	u_long	pad10[7];
	u_long	iod_hose_1_ctrl;
	u_long	pad11[7];
	u_long	ioa_hose_2_ctrl;
	u_long	pad12[7];
	u_long	iod_hose_2_ctrl;
	u_long	pad13[7];
	u_long	ioa_hose_3_ctrl;
	u_long	pad14[7];
	u_long	iod_hose_3_ctrl;
	u_long	pad15[7];
	u_long	iop_dev_int_target_0; /* offset 800 */
	u_long	pad16[15];
	u_long	iop_dev_int_target_1;
	u_long	pad17[15];
	u_long	iop_dev_int_target_2;
	u_long	pad18[15];
	u_long	iop_dev_int_target_3;
	u_long	pad19[15];
	u_long	iop_err_int_target;
	u_long	pad20[15];
	u_long	iop_qbb_err_sum;
	u_long	pad21[15];
	u_long	iop_qbb_se_sum;
	u_long	pad22[15];
	u_long	ioa_err_sum;	/* offset D00 */
	u_long	pad23[7];
	u_long	iod_err_sum;
	u_long	pad24[39];
	u_long	ioa_diag_force_err; /* offset E80 */
	u_long	pad25[7];
	u_long	iod_diag_force_err; /* offset E80 */
	u_long	pad26[39];
	u_long	iop_dia_send_err_int;	/* offset 1000 */
	u_long	pad27[127];
	u_long	ioa_scratch;	/* offset 1400 */
	u_long	pad28[7];
	u_long	iod_scratch;
};

/* Entity 12-15, offset F.FFB0.0000
 * PCA0= Entity 12
 *	...
 * PCA3 = Entity 15
 *
 * CSRs on 64-byte boundaries 
 */
/* see wfpci.h for PCA-related structs, defines */

/* 
 * PCA0,PCI0 = Entity 12, offset F.FFB2.0000
 * PCA0,PCI1 =            offset F.FFB3.0000
 * PCA1,PCI0 = Entity 13, offset F.FFB4.0000
 * PCA1,PCI1 =            offset F.FFB5.0000
 * PCA2,PCI0 = Entity 14, offset F.FFB8.0000
 * PCA2,PCI1 =            offset F.FFB9.0000
 * PCA3,PCI0 = Entity 15, offset F.FFBC.0000
 * PCA3,PCI1 =            offset F.FFBD.0000
 */
	

/* Entity 16, offset F.FFC0.0000
 *
 * CSRs on 2048-byte boundaries 
 */
struct wf_gp_csrs {
	u_long	qbb_map_0;
	u_long	pad0[255];
	u_long	qbb_map_1;
	u_long	pad1[255];
	u_long 	qbb_map_2;
	u_long	pad2[255];
	u_long	qbb_map_3;
	u_long	pad3[255];
	u_long	mem_pop_map;
	u_long	pad4[255];
	u_long	scratch;
	u_long	pad5[255];
	u_long	diag;
	u_long	pad6[255];
	u_long	config_0;
	u_long	pad7[255];
	u_long	init_id;	/* offset 4800	*/
	u_long	pad8[1791];
	u_long	err_ena;	/* offset 8000 */
	u_long	pad9[255];
	u_long	gpl_err_sum;
	u_long	pad10[255];
	u_long	hsl_err_sum;
	u_long	pad11[255];
	u_long	perf_config;
	u_long	pad12[255];
	struct	gpl_err {
		u_long	addr;
		u_long	pad13[255];
	} gpl_err_addr[7];
	struct	hsl_err {
		u_long	addr;
		u_long	pad14[255];
	} hsl_err_addr[7];
};

/* Entity 20-23, offset F.FFD0.0000
 * CSRs on 2048-byte boundaries 
 *
 * Note: for rev 0 (first pass), use 1st set of regs in unions.
 *	 for rev 1 and beyond, use 2nd set of regs in unions.
 */
struct wf_mem_csrs {
	u_long	err_sum;
	u_long	pad0[255];
	u_long	self_test_poly;
	u_long	pad1[255];
	u_long	mod_config;
	u_long	pad2[255];
	u_long	arr_addr_3;
	u_long	pad4[255];
	u_long	arr_addr_1;
	u_long	pad5[255];
	u_long	shadow_mismatch;
	u_long	pad6[255];
	u_long	diag;
	u_long	pad7[255];
	u_long	ref_ctrl;
	u_long	pad8[255];
	u_long	edc_ctrl;
	u_long	pad9[255];
	u_long	pad10[512];
	u_long	sub_wt_cb;
	u_long	pad11[255];
	u_long	sub_wt_addr;
	u_long	pad12[255];
	u_long	crd_ctrl_0;
	u_long	pad13[255];
	u_long	crd_ctrl_1;
	u_long	pad14[255];
	u_long	dimm_err;
	u_long	pad15[255];
	u_long	dimm0;
	u_long	pad16[255];
	u_long	dimm1;
	u_long	pad17[255];
	u_long	dimm2;
	u_long	pad18[255];
	u_long	dimm3;
	u_long	pad19[255];
	u_long	dimm4;
	u_long	pad20[255];
	u_long	dimm5;
	u_long	pad21[255];
	u_long	dimm6;
	u_long	pad22[255];
	u_long	dimm7;
	u_long	pad23[255];
	union {
		u_long rd_trap0;
		u_long rd_ce_trap_0;
	} urdtrap0;
	u_long	pad24[255];
	union {
		u_long rd_trap1;
		u_long rd_ce_trap_1;
	} urdtrap1;
	u_long	pad25[255];
	union {
		u_long rd_trap2;
		u_long rd_ce_trap_2;
	} urdtrap2;
	u_long	pad26[255];
	union {
		u_long rd_trap3;
		u_long rd_ce_trap_3;
	} urdtrap3;
	u_long	pad27[255];
	union {
		u_long rd_trap4;
		u_long rd_uce_trap;
	} urdtrap4;
	u_long	pad28[255];
	u_long	rd_trap5;
	u_long	pad29[255];
	u_long	rd_trap6;
	u_long	pad30[255];
	u_long	rd_trap7;
	u_long	pad31[255];
	union {
		u_long wt_trap0;
		u_long wt_ce_trap_0;
	} uwtrap0;
	u_long	pad32[255];
	union {
		u_long wt_trap1;
		u_long wt_ce_trap_1;
	} uwtrap1;
	u_long	pad33[255];
	union {
		u_long wt_trap2;
		u_long wt_ce_trap_2;
	} uwtrap2;
	u_long	pad34[255];
	union {
		u_long wt_trap3;
		u_long wt_ce_trap_3;
	} uwtrap3;
	u_long	pad35[255];
	union {
		u_long wt_trap4;
		u_long wt_uce_trap;
	} uwtrap4;
	u_long	pad36[255];
	u_long	wt_trap5;
	u_long	pad37[255];
	u_long	wt_trap6;
	u_long	pad38[255];
	u_long	wt_trap7;
	u_long	pad39[255];
};

/* Entity 24-31, offset F.FFE0.0000
 * CSRs on 2048-byte boundaries 
 */
struct wf_dtag_csrs {
	u_long	control;
	u_long	pad0[255];
	u_long	qbb_id;
	u_long	pad2[255];
	u_long	rev;
	u_long	pad3[255];
	u_long	err_sum;
	u_long	pad4[255];
	u_long	err_cid;
	u_long	pad5[255];
	u_long	err_cmd;
	u_long	pad6[255];
	u_long	err_addr_0;
	u_long	pad12[255];
	u_long	err_addr_1;
	u_long	pad13[255];
	u_long	err_addr_2;
	u_long	pad14[255];
	u_long	err_addr_3;
	u_long	pad15[255];
	u_long	cpu_active;
	u_long	pad16[767];
        u_long  ecc_control;
        u_long  pad17[255];
        u_long  ecc_syndrome;
        u_long  pad18[255];
        u_long	arr_valid;	/* offset 7800 */
	u_long	pad23[255];
	u_long	arr_addr_0;	/* offset  2.4000 */
	u_long	pad28[255];
	u_long	arr_addr_1;
	u_long	pad29[255];
	u_long	arr_addr_2;
	u_long	pad30[255];
	u_long	arr_addr_3;
	u_long	pad31[255];
	u_long	arr_addr_4;
	u_long	pad32[255];
	u_long	arr_addr_5;
	u_long	pad33[255];
	u_long	arr_addr_6;
	u_long	pad34[255];
	u_long	arr_addr_7;
	u_long	pad35[255];
	u_long	arr_mask_0;	/* offset  2.8000 */
	u_long	pad36[255];
	u_long	arr_mask_1;
	u_long	pad37[255];
	u_long	arr_mask_2;
	u_long	pad38[255];
	u_long	arr_mask_3;
	u_long	pad39[255];
	u_long	arr_mask_4;
	u_long	pad40[255];
	u_long	arr_mask_5;
	u_long	pad41[255];
	u_long	arr_mask_6;
	u_long	pad42[255];
	u_long	arr_mask_7;
};



/*
 * A few defines used by the VM memory troller interface code.
 */
#define HI2LO_INT_SHIFT_32	32
#define LO2HI_INT_SHIFT_32	32
#define LOW_30_BITS		0x000000003fffffffUL
#define LOW_32_BITS		0x00000000ffffffffUL

/*
 * Defines for use in read_xxx_csr(), write_xxx_csr()
 */
/*
 * Wildfire's console wildfire.sdl file re-formatted
 * into C h-file.
 *
 * constant == #define
 * equals <deleted>
 */
#define WF_NUM_ENTITY		32
#define WF_NUM_QBB		8
#define WF_NUM_CPU		32
#define WF_NUM_MEM		32
#define WF_NUM_DIR		8
#define WF_NUM_IOP		8
#define WF_NUM_PCA		32
#define WF_NUM_PCI_BUS		64

#define WF_QSD_ENTITY		5
#define WF_QSD_MAX		4	/* Four QSDs per QBB */
#define WF_FAST_QSD_ENTITY	1
#define WF_QSD_SLICE_SHIFT	16
#define WF_QSD_WHAMI		0x00000
/* Bit definitions for QSD_WHAMI */
#	define WF_QSD_WHAMI_HARD_QBB_ID_SHIFT	8
#	define WF_QSD_WHAMI_SOFT_QBB_ID_SHIFT	4
#	define WF_QSD_WHAMI_QBB_ID_MASK		0x7
#	define WF_QSD_WHAMI_CPU_ID_SHIFT	1
#	define WF_QSD_WHAMI_CPU_ID_MASK		0x3
#define WF_QSD_REV		0x00040
/* Bit definitions for WF_QSD_REV	*/
#	define WF_QSD_REV_REV_SHIFT	2
#	define WF_QSD_REV_REV_MASK	0x3F
#define WF_QSD_PORT_PRESENT	0x00080
#define WF_QSD_PORT_ACTIVE	0x000C0
/* Bit definitions for QSD_PORT_ACTIVE */
#	define WF_QSD_PORT_ACTIVE_GP_ACTIVE	0x001	/* bit 0 */
#	define WF_QSD_PORT_ACTIVE_IOP_ACTIVE	0x002	/* bit 1 */
#	define WF_QSD_PORT_ACTIVE_MEM_ACTIVE	0x040	/* bit 6 */
#	define WF_QSD_PORT_ACTIVE_MEM0_ACTIVE	0x040	/* bit 6 */
#	define WF_QSD_PORT_ACTIVE_MEM1_ACTIVE	0x080	/* bit 7 */
#	define WF_QSD_PORT_ACTIVE_MEM2_ACTIVE	0x100	/* bit 8 */
#	define WF_QSD_PORT_ACTIVE_MEM3_ACTIVE	0x200	/* bit 9 */
#define WF_QSD_FAULT_ENA	0x00100
#define WF_QSD_CPU_INT_ENA	0x00140
#define WF_QSD_MEM_CONFIG	0x00180
#define WF_QSD_ERR_SUM		0x001C0
#define WF_CPU_DELTA		0x00040
#define WF_CPU_CE_SUM		0x00200
#define WF_CPU_DEV_INT		0x00300
#define WF_CPU_IT_INT		0x00400
#define WF_CPU_IP_INT		0x00500
#define WF_CPU_UCE_SUM		0x00600
#define WF_CPU_SE_SUM		0x00700
#define WF_CPU_NON_DEV_INT	0x00700
#define WF_CPU_SCRATCH		0x00800
#define WF_CPU0_CE_SUM		0x00200
#define WF_CPU1_CE_SUM		0x00240
#define WF_CPU2_CE_SUM		0x00280
#define WF_CPU3_CE_SUM		0x002C0
#define WF_CPU0_DEV_INT		0x00300
#define WF_CPU1_DEV_INT		0x00340
#define WF_CPU2_DEV_INT		0x00380
#define WF_CPU3_DEV_INT		0x003C0
#define WF_CPU0_IT_INT		0x00400
#define WF_CPU1_IT_INT		0x00440
#define WF_CPU2_IT_INT		0x00480
#define WF_CPU3_IT_INT		0x004C0
#define WF_CPU0_IP_INT		0x00500
#define WF_CPU1_IP_INT		0x00540
#define WF_CPU2_IP_INT		0x00580
#define WF_CPU3_IP_INT		0x005C0
#define WF_CPU0_UCE_SUM		0x00600
#define WF_CPU1_UCE_SUM		0x00640
#define WF_CPU2_UCE_SUM		0x00680
#define WF_CPU3_UCE_SUM		0x006C0
#define WF_CPU0_SE_SUM		0x00700
#define WF_CPU1_SE_SUM		0x00740
#define WF_CPU2_SE_SUM		0x00780
#define WF_CPU3_SE_SUM		0x007C0
#define WF_CPU0_NON_DEV_INT	0x00700
#define WF_CPU1_NON_DEV_INT	0x00740
#define WF_CPU2_NON_DEV_INT	0x00780
#define WF_CPU3_NON_DEV_INT	0x007C0
#define WF_CPU0_SCRATCH		0x00800
#define WF_CPU1_SCRATCH		0x00840
#define WF_CPU2_SCRATCH		0x00880
#define WF_CPU3_SCRATCH		0x008C0
#define WF_QSD_TIMER		0x00900
#define WF_QSD_DIAG		0x00940

#define WF_QSA_ENTITY		4
#define WF_QSA_QBB_ID		0x00000
/* Bit definitions for QSA_QBB_ID	*/
#       define WF_QSA_QBB_ID_DIR_PRES   0x10 /* bit 4 */
#	define WF_QSA_QBB_ID_GP_PRES	0x20 /* bit 5 */
#       define WF_QSA_QBB_ID_HS_PRES    0x40 /* bit 6 */
#define WF_QSA_PORT_ENA		0x01000
#define WF_QSA_SCRATCH		0x01800
#define WF_QSA_CONFIG_0		0x02000
#define WF_QSA_CONFIG_1		0x02800
#define WF_QSA_CONFIG_2		0x03000
#define WF_QSA_CONFIG_3		0x03800
#define WF_QSA_CONFIG_4		0x04000
#define WF_QSA_REF_INT		0x04800
#define WF_QSA_QBB_POP_0	0x05000
#define WF_QSA_QBB_POP_1	0x05800
/* Bit definitions for QSA_QBB_POP_1	*/
#	define WF_QSA_QBB_POP_1_IOR_SHIFT	4	/* bits 4:7 */
#	define WF_QSA_QBB_POP_1_IOR_MASK	0x0FUL
#	define WF_QSA_QBB_POP_1_GP_POP		0x01UL	/* bit 0 */
#	define WF_QSA_QBB_POP_1_DIR_POP		0x02UL	/* bit 1 */
#	define WF_QSA_QBB_POP_1_HS_POP		0x04UL	/* bit 2 */
#	define WF_QSA_QBB_POP_1_HS_READY	0x08UL	/* bit 3 */
#	define WF_QSA_QBB_POP_1_IOR_0_POP	0x010UL /* bit 4 */
#	define WF_QSA_QBB_POP_1_IOR_1_POP	0x020UL /* bit 5 */
#	define WF_QSA_QBB_POP_1_IOR_2_POP	0x040UL /* bit 6 */
#	define WF_QSA_QBB_POP_1_IOR_3_POP	0x080UL /* bit 7 */
#define WF_QSA_DIAG		0x08000
/* Bit definitions for QSA_DIAG	*/
#	define WF_QSA_DIAG_REV_SHIFT	4
#	define WF_QSA_DIAG_REV_MASK	0xF
#define WF_QSA_DIAG_LOCK	0x08800
#define WF_QSA_DIAG_LOCK_DELTA	0x00800
#define WF_QSA_DIAG_LOCK_0	0x08800
#define WF_QSA_DIAG_LOCK_1	0x09000
#define WF_QSA_DIAG_LOCK_2	0x09800
#define WF_QSA_DIAG_LOCK_3	0x0A000
#define WF_QSA_CPU_ERR_SUM	0x10000
#define WF_QSA_MISC_ERR_SUM	0x10800
#define WF_QSA_TMO_ERR_SUM	0x11000
#define WF_QSA_ERR_ENA		0x11800
#define WF_QSA_TMO_CONFIG	0x12000
#define WF_QSA_ILL_CMD_ERR_SUM	0x12800
#define WF_QSA_BUSY_MASK	0x20000
#define WF_QSA_ARR_VALID	0x20800
#define WF_QSA_PORT_MAP_ADDR_MASK 0x3
#define WF_QSA_PORT_MAP_VALID   0x10
#define WF_QSA_PORT_MAP		0x22000
#define WF_QSA_PORT_MAP_DELTA	0x00800
#define WF_QSA_PORT_MAP_0	0x22000
#define WF_QSA_PORT_MAP_1	0x22800
#define WF_QSA_PORT_MAP_2	0x23000
#define WF_QSA_PORT_MAP_3	0x23800
#define WF_QSA_ARR_ADDR		0x24000
#define WF_QSA_ARR_ADDR_DELTA	0x00800
#define WF_QSA_ARR_ADDR_0	0x24000
#define WF_QSA_ARR_ADDR_1	0x24800
#define WF_QSA_ARR_ADDR_2	0x25000
#define WF_QSA_ARR_ADDR_3	0x25800
#define WF_QSA_ARR_ADDR_4	0x26000
#define WF_QSA_ARR_ADDR_5	0x26800
#define WF_QSA_ARR_ADDR_6	0x27000
#define WF_QSA_ARR_ADDR_7	0x27800
#define WF_QSA_ARR_MASK		0x28000
#define WF_QSA_ARR_MASK_DELTA	0x00800
#define WF_QSA_ARR_MASK_0	0x28000
#define WF_QSA_ARR_MASK_1	0x28800
#define WF_QSA_ARR_MASK_2	0x29000
#define WF_QSA_ARR_MASK_3	0x29800
#define WF_QSA_ARR_MASK_4	0x2A000
#define WF_QSA_ARR_MASK_5	0x2A800
#define WF_QSA_ARR_MASK_6	0x2B000
#define WF_QSA_ARR_MASK_7	0x2B800

#define WF_DTAG_ENTITY		24
#define WF_DTAG_MAX		8	/* 8 DTAGs = 8MB cache; 4 DTAGs = 4MB cache */
#define WF_DTAG_CONTROL		0x00000
#define WF_DTAG_QBB_ID		0x00800
/* Bit definitions for DTAG_QBB_ID	*/
#	define WF_DTAG_QBB_ID_8MB_CACHE_MASK	0x80
#define WF_DTAG_REV		0x01000
/* Bit definitions for DTAG_REV	*/
#	define WF_DTAG_REV_REV_SHIFT 3
#	define WF_DTAG_REV_REV_MASK  0x0F
#define WF_DTAG_ERR_SUM		0x01800
#define WF_DTAG_ERR_CID		0x02000
#define WF_DTAG_ERR_CMD		0x02800
#define WF_DTAG_ERR_ADDR_0	0x03000
#define WF_DTAG_ERR_ADDR_1	0x03800
#define WF_DTAG_ERR_ADDR_2	0x04000
#define WF_DTAG_ERR_ADDR_3	0x04800
#define WF_DTAG_CPU_ACTIVE      0x05000
#define WF_DTAG_ECC_CONTROL     0x05800
#define WF_DTAG_ECC_SYNDROME    0x06000
#define WF_DTAG_ARR_VALID	0x07800
#define WF_DTAG_ARR_ADDR	0x08000
#define WF_DTAG_ARR_ADDR_DELTA	0x00800
#define WF_DTAG_ARR_ADDR_0	0x08000
#define WF_DTAG_ARR_ADDR_1	0x08800
#define WF_DTAG_ARR_ADDR_2	0x09000
#define WF_DTAG_ARR_ADDR_3	0x09800
#define WF_DTAG_ARR_ADDR_4	0x0A000
#define WF_DTAG_ARR_ADDR_5	0x0A800
#define WF_DTAG_ARR_ADDR_6	0x0B000
#define WF_DTAG_ARR_ADDR_7	0x0B800
#define WF_DTAG_ARR_MASK	0x0C000
#define WF_DTAG_ARR_MASK_DELTA	0x00800
#define WF_DTAG_ARR_MASK_0	0x0C000
#define WF_DTAG_ARR_MASK_1	0x0C800
#define WF_DTAG_ARR_MASK_2	0x0D000
#define WF_DTAG_ARR_MASK_3	0x0D800
#define WF_DTAG_ARR_MASK_4	0x0E000
#define WF_DTAG_ARR_MASK_5	0x0E800
#define WF_DTAG_ARR_MASK_6	0x0F000
#define WF_DTAG_ARR_MASK_7	0x0F800

#define WF_DIR_ENTITY		6
#define WF_DIR_ERR_SUM		0x00000
#define WF_DIR_ERR_TRAP_A	0x00800
#define WF_DIR_ERR_TRAP_A_DELTA	0x01800
#define WF_DIR_ERR_TRAP_B	0x01000
#define WF_DIR_ERR_TRAP_B_DELTA	0x01800
#define WF_DIR_ERR_TRAP_C	0x01800
#define WF_DIR_ERR_TRAP_C_DELTA	0x01800
#define WF_DIR_CE_TRAP0_A	0x00800
#define WF_DIR_CE_TRAP0_B	0x01000
#define WF_DIR_CE_TRAP0_C	0x01800
#define WF_DIR_CE_TRAP1_A	0x02000
#define WF_DIR_CE_TRAP1_B	0x02800
#define WF_DIR_CE_TRAP1_C	0x03000
#define WF_DIR_CE_TRAP2_A	0x03800
#define WF_DIR_CE_TRAP2_B	0x04000
#define WF_DIR_CE_TRAP2_C	0x04800
#define WF_DIR_CE_TRAP3_A	0x05000
#define WF_DIR_CE_TRAP3_B	0x05800
#define WF_DIR_CE_TRAP3_C	0x06000
#define WF_DIR_UCE_TRAP_A	0x06800
#define WF_DIR_UCE_TRAP_B	0x07000
#define WF_DIR_UCE_TRAP_C	0x07800
#define WF_DIR_ERR_DETECT_A	0x0C800
#define WF_DIR_ERR_DETECT_B	0x0D000
#define WF_DIR_MICRO_REV	0x0D800
#define WF_DIR_DMD_REV		0x0E000
/* Bit definitions for DMD_REV	*/
#	define WF_DIR_DMD_REV_MASK	0x07UL
#define WF_DIR_DMA_REV		0x0E800
/* Bit definitions for DMA_REV	*/
#	define WF_DIR_DMA_REV_MASK	0x07UL
#define WF_DIR_SELF_TEST	0x0F000
#define WF_DIR_PHYS_DIMM_TYPE	0x0F800
#define WF_DIR_FAULT_STATUS	0x14800
#define WF_DIR_REF_CTRL		0x15000
#define WF_DIR_LFSR_A		0x15800
#define WF_DIR_LFSR_A_DELTA	0x02000
#define WF_DIR_LFSR_B		0x16000
#define WF_DIR_LFSR_B_DELTA	0x02000
#define WF_DIR_LFSR_C		0x16800
#define WF_DIR_LFSR_C_DELTA	0x02000
#define WF_DIR_LFSR_D		0x17000
#define WF_DIR_LFSR_D_DELTA	0x02000
#define WF_DIR_LFSR_0_A		0x15800
#define WF_DIR_LFSR_0_B		0x16000
#define WF_DIR_LFSR_0_C		0x16800
#define WF_DIR_LFSR_0_D		0x17000
#define WF_DIR_LFSR_1_A		0x17800
#define WF_DIR_LFSR_1_B		0x18000
#define WF_DIR_LFSR_1_C		0x18800
#define WF_DIR_LFSR_1_D		0x19000
#define WF_DIR_LFSR_2_A		0x19800
#define WF_DIR_LFSR_2_B		0x1A000
#define WF_DIR_LFSR_2_C		0x1A800
#define WF_DIR_LFSR_2_D		0x1B000
#define WF_DIR_LFSR_3_A		0x1B800
#define WF_DIR_LFSR_3_B		0x1C000
#define WF_DIR_LFSR_3_C		0x1C800
#define WF_DIR_LFSR_3_D		0x1D000
#define WF_DIR_LFSR_4_A		0x1D800
#define WF_DIR_LFSR_4_B		0x1E000
#define WF_DIR_LFSR_4_C		0x1E800
#define WF_DIR_LFSR_4_D		0x1F000
#define WF_DIR_LFSR_5_A		0x1F800
#define WF_DIR_LFSR_5_B		0x20000
#define WF_DIR_LFSR_5_C		0x20800
#define WF_DIR_LFSR_5_D		0x21000
#define WF_DIR_LFSR_6_A		0x21800
#define WF_DIR_LFSR_6_B		0x22000
#define WF_DIR_LFSR_6_C		0x22800
#define WF_DIR_LFSR_6_D		0x23000
#define WF_DIR_LFSR_7_A		0x23800
#define WF_DIR_LFSR_7_B		0x24000
#define WF_DIR_LFSR_7_C		0x24800
#define WF_DIR_LFSR_7_D		0x25000
#define WF_DIR_MOD_MAP_A	0x25800
#define WF_DIR_MOD_MAP_B	0x26000
#define WF_DIR_VIRT_DIMM_TYPE	0x26800
#define WF_DIR_VIRT_DIMM_TYPE_DELTA	0x00800
#define WF_DIR_VIRT_DIMM_TYPE_0	0x26800
#define WF_DIR_VIRT_DIMM_TYPE_1	0x27000
#define WF_DIR_VIRT_DIMM_TYPE_2	0x27800
#define WF_DIR_VIRT_DIMM_TYPE_3	0x28000
#define WF_DIR_VIRT_DIMM_TYPE_4	0x28800
#define WF_DIR_VIRT_DIMM_TYPE_5	0x29000
#define WF_DIR_VIRT_DIMM_TYPE_6	0x29800
#define WF_DIR_VIRT_DIMM_TYPE_7	0x2A000
#define WF_DIR_EDC_SUB_ADDR_A	0x2A800
#define WF_DIR_EDC_SUB_ADDR_B	0x2B000
#define WF_DIR_EDC_SUB_ADDR_C	0x2B800
#define WF_DIR_EDC_SUB_ADDR_D	0x2C000
#define WF_DIR_EDC_CTRL		0x2C800
#define WF_DIR_QBB_ID		0x2D000
#define WF_DIR_CRD_CTRL_A	0x2D800
#define WF_DIR_CRD_CTRL_A_DELTA	0x01000
#define WF_DIR_CRD_CTRL_B	0x2E000
#define WF_DIR_CRD_CTRL_B_DELTA	0x01000
#define WF_DIR_CRD_CTRL0_A	0x2D800
#define WF_DIR_CRD_CTRL0_B	0x2E000
#define WF_DIR_CRD_CTRL1_A	0x2E800
#define WF_DIR_CRD_CTRL1_B	0x2F000
#define WF_DIR_CRD_CTRL2_A	0x2F800
#define WF_DIR_CRD_CTRL2_B	0x30000
#define WF_DIR_CRD_CTRL3_A	0x30800
#define WF_DIR_CRD_CTRL3_B	0x31000
#define WF_DIR_SELF_TEST_CTRL	0x31800
#define WF_DIR_MICRO_RESET	0x32000
#define WF_DIR_DIAG		0x32800
#define WF_DIR_DIMM_INT		0x33000
#define WF_DIR_DIMM_INT_DELTA	0x00800
#define WF_DIR_DIMM_INT_0	0x33000
#define WF_DIR_DIMM_INT_1	0x33800
#define WF_DIR_DIMM_INT_2	0x34000
#define WF_DIR_DIMM_INT_3	0x34800
#define WF_DIR_DIMM_INT_4	0x35000
#define WF_DIR_DIMM_INT_5	0x35800
#define WF_DIR_DIMM_INT_6	0x36000
#define WF_DIR_DIMM_INT_7	0x36800
#define WF_DIR_DIMM_ADDR	0x37000
#define WF_DIR_DIMM_ADDR_DELTA	0x00800
#define WF_DIR_DIMM_ADDR_0	0x37000
#define WF_DIR_DIMM_ADDR_1	0x37800
#define WF_DIR_DIMM_ADDR_2	0x38000
#define WF_DIR_DIMM_ADDR_3	0x38800
#define WF_DIR_DIMM_ADDR_4	0x39000
#define WF_DIR_DIMM_ADDR_5	0x39800
#define WF_DIR_DIMM_ADDR_6	0x3A000
#define WF_DIR_DIMM_ADDR_7	0x3A800
#define WF_DIR_DIMM_MASK	0x3B000
#define WF_DIR_DIMM_MASK_DELTA	0x00800
#define WF_DIR_DIMM_MASK_0	0x3B000
#define WF_DIR_DIMM_MASK_1	0x3B800
#define WF_DIR_DIMM_MASK_2	0x3C000
#define WF_DIR_DIMM_MASK_3	0x3C800
#define WF_DIR_DIMM_MASK_4	0x3D000
#define WF_DIR_DIMM_MASK_5	0x3D800
#define WF_DIR_DIMM_MASK_6	0x3E000
#define WF_DIR_DIMM_MASK_7	0x3E800
#define WF_DIR_ADD_ADDR_MASK_A	0x3F000
#define WF_DIR_ADD_ADDR_MASK_B	0x3F800

#define WF_MEM_ENTITY		20
#define WF_MEM_ERR_SUM		0x00000
#define		WF_MEM_ERR_SUM_BIT		0x8000000000000000UL
#define		WF_MEM_ERR_SUM_UCE_BITS		0x8000000000000020UL
#define WF_MEM_SELF_TEST_POLY	0x00800
#define WF_MEM_MOD_CONFIG	0x01000
/* Bit definitions for MEM_MOD_CONFIG	*/
#	define WF_MEM_MOD_CONFIG_MPD0_REV_SHIFT	12
#	define WF_MEM_MOD_CONFIG_MPD1_REV_SHIFT	44
#	define WF_MEM_MOD_CONFIG_MPA_REV_SHIFT	47
#	define WF_MEM_MOD_CONFIG_MPD0_REV_MASK	0x7
#	define WF_MEM_MOD_CONFIG_MPD1_REV_MASK	0x7
#	define WF_MEM_MOD_CONFIG_MPA_REV_MASK	0x7
#define WF_MEM_ARR_ADDR_0	0x01800
#define WF_MEM_ARR_ADDR_1	0x02000
#define WF_MEM_SHADOW_MISMATCH	0x02800
#define WF_MEM_DIAG		0x03000
#define WF_MEM_REF_CTRL		0x03800
#define WF_MEM_EDC_CTRL		0x04000
#define WF_MEM_SUB_WT_CB	0x05800
#define WF_MEM_SUB_WT_ADDR	0x06000
#define WF_MEM_CRD_CTRL_0	0x06800
#define WF_MEM_CRD_CTRL_1	0x07000
#define WF_MEM_DIMM_ERR		0x07800
#define WF_MEM_DIMM		0x08000
#define WF_MEM_DIMM_DELTA	0x00800
#define WF_MEM_DIMM0		0x08000
#define WF_MEM_DIMM1		0x08800
#define WF_MEM_DIMM2		0x09000
#define WF_MEM_DIMM3		0x09800
#define WF_MEM_DIMM4		0x0A000
#define WF_MEM_DIMM5		0x0A800
#define WF_MEM_DIMM6		0x0B000
#define WF_MEM_DIMM7		0x0B800
#define WF_MEM_RD_UCE_TRAP      0x0E000
#define WF_MEM_RD_TRAP		0x0C000
#define WF_MEM_RD_TRAP_DELTA	0x00800
#define WF_MEM_RD_TRAP0		0x0C000
#define WF_MEM_RD_TRAP1		0x0C800
#define WF_MEM_RD_TRAP2		0x0D000
#define WF_MEM_RD_TRAP3		0x0D800
#define WF_MEM_RD_TRAP4		0x0E000
#define WF_MEM_RD_TRAP5		0x0E800
#define WF_MEM_RD_TRAP6		0x0F000
#define WF_MEM_RD_TRAP7		0x0F800
#define WF_MEM_WT_UCE_TRAP      0x12000
#define WF_MEM_WT_TRAP		0x10000
#define WF_MEM_WT_TRAP_DELTA	0x00800
#define WF_MEM_WT_TRAP0		0x10000
#define WF_MEM_WT_TRAP1		0x10800
#define WF_MEM_WT_TRAP2		0x11000
#define WF_MEM_WT_TRAP3		0x11800
#define WF_MEM_WT_TRAP4		0x12000
#define WF_MEM_WT_TRAP5		0x12800
#define WF_MEM_WT_TRAP6		0x13000
#define WF_MEM_WT_TRAP7		0x13800
#define WF_MEM_SELF_TEST	0x14800
#define WF_MEM_SELF_TEST_DELTA	0x00800
#define WF_MEM_SELF_TEST_0	0x14800
#define WF_MEM_SELF_TEST_1	0x15000
#define WF_MEM_SELF_TEST_2	0x15800
#define WF_MEM_SELF_TEST_3	0x16000
#define WF_MEM_SELF_TEST_4	0x16800
#define WF_MEM_SELF_TEST_5	0x17000
#define WF_MEM_SELF_TEST_6	0x17800
#define WF_MEM_SELF_TEST_7	0x18000
#define WF_MEM_SELF_TEST_8	0x18800
#define WF_MEM_SELF_TEST_9	0x19000
#define WF_MEM_SELF_TEST_10	0x19800
#define WF_MEM_SELF_TEST_11	0x1A000
#define WF_MEM_SELF_TEST_12	0x1A800
#define WF_MEM_SELF_TEST_13	0x1B000
#define WF_MEM_SELF_TEST_14	0x1B800
#define WF_MEM_SELF_TEST_15	0x1C000
#define WF_MEM_SELF_TEST_16	0x1C800
#define WF_MEM_SELF_TEST_17	0x1D000
#define WF_MEM_SCRATCH		0x1F800
#define WF_MEM_LMP_SHIFT        6
  
#define WF_IOP_ENTITY		8
#define WF_IOA_CONFIG		0x00000
/* Bit defines for IOA_CONFIG */
#	define WF_IOA_CONFIG_IOA_REV_SHIFT	4
#	define WF_IOA_CONFIG_IOA_REV_MASK  	0x0FUL
#define WF_IOD_CONFIG		0x00040
/* Bit defines for IOD_CONFIG */
#	define WF_IOD_CONFIG_IOD_REV_SHIFT 	12
#	define WF_IOD_CONFIG_IOD_REV_MASK  	0x0FUL
#define WF_IOP_SWITCH_CREDITS	0x00080
#define WF_IOP_HOSE_CREDITS	0x00100
#define WF_IOP_HOSE_INIT	0x00440
#define WF_IOP_HOSE_INIT_DELTA	0x00080
#define WF_IOP_HOSE_0_INIT	0x00440
#define WF_IOP_HOSE_1_INIT	0x004C0
#define WF_IOP_HOSE_2_INIT	0x00540
#define WF_IOP_HOSE_3_INIT	0x005C0
#define WF_IOA_HOSE_CTRL	0x00600
#define WF_IOA_HOSE_CTRL_DELTA	0x00080
#define WF_IOA_HOSE_0_CTRL	0x00600
#define WF_IOD_HOSE_CTRL	0x00640
#define WF_IOD_HOSE_CTRL_DELTA	0x00080
#define WF_IOD_HOSE_0_CTRL	0x00640
#define WF_IOA_HOSE_1_CTRL	0x00680
#define WF_IOD_HOSE_1_CTRL	0x006C0
#define WF_IOA_HOSE_2_CTRL	0x00700
#define WF_IOD_HOSE_2_CTRL	0x00740
#define WF_IOA_HOSE_3_CTRL	0x00780
#define WF_IOD_HOSE_3_CTRL	0x007C0
#define WF_IOP_DEV_INT_TARGET	0x00800
/* Bit definitions common to IOP_DEV_INT_TARGET & ERR_INT_TARGET */
#	define WF_IOP_INT_TARGET_CPU_IN_QBB_MASK	0x003UL
#	define WF_IOP_INT_TARGET_QBB_MASK 		0x01CUL
#	define WF_IOP_INT_TARGET_CPU_MASK \
	(WF_IOP_INT_TARGET_CPU_IN_QBB_MASK | WF_IOP_INT_TARGET_QBB_MASK)
/* Bit definitions common to all IOP_DEV_INT_TARGET regs */
#	define WF_IOP_DEV_INT_TARGET_Valid 0x100
#	define WF_IOP_DEV_INT_TARGET_Valid_SHIFT 8
#define WF_IOP_DEV_INT_TARGET_DELTA	0x00080
#define WF_IOP_DEV_INT_TARGET_0	0x00800
#define WF_IOP_DEV_INT_TARGET_1	0x00880
#define WF_IOP_DEV_INT_TARGET_2	0x00900
#define WF_IOP_DEV_INT_TARGET_3	0x00980
#define WF_IOP_ERR_INT_TARGET	0x00A00
/* Bit definitions for IOP_ERR_INT_TARGET reg */
#	define WF_IOP_ERR_INT_TARGET_ENABLE_SE	(0x01UL << 10)
#	define WF_IOP_ERR_INT_TARGET_ENABLE_UCE	(0x01UL <<  9)
#	define WF_IOP_ERR_INT_TARGET_ENABLE_CE	(0x01UL <<  8)
#define WF_IOP_QBB_ERR_SUM	0x00C00
/* Bit definitions for IOP_QBB_ERR_SUM */
#define WF_IOP_QBB_SE_SUM	0x00C80
/* Bit definitions for IOP_QBB_SE_SUM */
#define WF_IOA_ERR_SUM		0x00D00
/* Bit definitions for WF_IOA_ERR_SUM */
#	define WF_IOA_ERR_PCA_UCE_BITS		0x0101010100000000
#define WF_IOD_ERR_SUM		0x00D40
/* Bit definitions for WF_IOD_ERR_SUM */
#	define WF_IOD_ERR_ECC_SYND		0xff000000ff000000
#define WF_IOA_DIAG_FORCE_ERR	0x00E80
#define WF_IOD_DIAG_FORCE_ERR	0x00EC0
#define WF_IOP_DIAG_SEND_ERR_INT	0x01000
#define WF_IOA_SCRATCH		0x01400
#define WF_IOD_SCRATCH		0x01440

#define WF_PCA_ENTITY		12
#define WF_PCA_ENTITY_MASK	(0xf << WF_PCA_ENTITY)	/* <15:12> all 4 PCAs */

#define WF_GP_ENTITY		16
#define WF_GPA_QBB_MAP		0x00000
#define WF_GPA_QBB_MAP_DELTA	0x00800
#define WF_GPA_QBB_MAP_0	0x00000
#define WF_GPA_QBB_MAP_1	0x00800
#define WF_GPA_QBB_MAP_2	0x01000
#define WF_GPA_QBB_MAP_3	0x01800
/* Bit definitions for GPA_QBB_MAP_x	*/
#	define WF_GPA_QBB_MAP_PORT_QBB_ID_MASK 0x07UL
#	define WF_GPA_QBB_MAP_PORT_POP_MASK 0x08UL
#define WF_GPA_MEM_POP_MAP	0x02000
#define WF_GPA_SCRATCH		0x02800
#define WF_GPA_DIAG		0x03000
/* Bit definitions for GPA_DIAG	*/
#	define WF_GPA_DIAG_GPA_REV_SHIFT 7
#	define WF_GPA_DIAG_GPA_REV_MASK  0x0F
#define WF_GPA_CONFIG_0		0x03800
#define WF_GPA_INIT_ID		0x04800
#define WF_GPA_CONFIG_2         0x05000
#define WF_GPA_EXT_OVFL_ERR_SUM 0x05800
#define WF_GPA_ERR_ENA		0x08000
#define WF_GPA_GPL_ERR_SUM	0x08800
#define		WF_GPA_GPL_ERR_SUM_UCE		0x0000000000000004UL
#define WF_GPA_HSL_ERR_SUM	0x09000
#define		WF_GPA_HSL_ERR_SUM_UCE		0x0000000000000004UL
#define WF_PERF_CONFIG		0x09800
#define WF_GPA_GPL_ERR_ADDR_0	0x10000
#define WF_GPA_GPL_ERR_ADDR_1	0x10800
#define WF_GPA_GPL_ERR_ADDR_2	0x11000
#define WF_GPA_GPL_ERR_ADDR_3	0x11800
#define WF_GPA_GPL_ERR_ADDR_4	0x12000
#define		WF_GPA_GPL_ERR_ADDR_4_CMD_MASK	0x7f
#define		WF_GPA_GPL_CMD32		0x32
#define WF_GPA_GPL_ERR_ADDR_5	0x12800
#define WF_GPA_GPL_ERR_ADDR_6	0x13000
#define WF_GPA_HSL_ERR_ADDR_0	0x18000
#define WF_GPA_HSL_ERR_ADDR_1	0x18800
#define WF_GPA_HSL_ERR_ADDR_2	0x19000
#define WF_GPA_HSL_ERR_ADDR_3	0x19800
#define WF_GPA_HSL_ERR_ADDR_4	0x1A000
#define		WF_GPA_HSL_ERR_ADDR_4_CMD_MASK	0x7f
#define		WF_GPA_HSL_CMD34		0x34
#define WF_GPA_HSL_ERR_ADDR_5	0x1A800
#define WF_GPA_HSL_ERR_ADDR_6	0x1B000
#define WF_GPD_GPL_ERR_SUM	0x20000
#define WF_GPD_HSL_ERR_SUM	0x20800
#define WF_GPD_SCRATCH		0x21000
#define WF_GPD_ERR_ENA		0x21800
/* Bit definitions for GPD_ERR_ENA */
#	define WF_GPD_ERR_ENA_GPD_REV_SHIFT 4
#	define WF_GPD_ERR_ENA_GPD_REV_MASK  0x0F
#define WF_PERF_START_CNT	0x28800
#define WF_PERF_STOP_CNT	0x29000
#define WF_PERF_SWITCH_SILOS	0x29800
#define WF_PERF_READ_FIFO	0x2A000
#define WF_PERF_CONFIG_1	0x2A800
#define WF_PERF_CONFIG_2	0x2B000
#define WF_PERF_CONFIG_3	0x2B800
#define WF_PERF_RESERVED_0	0x30000
#define WF_PERF_RESERVED_1	0x30800
#define WF_PERF_RESERVED_2	0x31000
#define WF_PERF_RESERVED_3	0x31800
#define WF_PERF_RESERVED_4	0x32000
#define WF_PERF_RESERVED_5	0x32800
#define WF_PERF_RESERVED_6	0x33000
#define WF_PERF_RESERVED_7	0x33800
#define WF_PERF_RESERVED_8	0x34000
#define WF_PERF_RESERVED_9	0x34800
#define WF_PERF_RESERVED_10	0x35000
#define WF_PERF_RESERVED_11	0x35800
#define WF_PERF_RESERVED_12	0x36000
#define WF_PERF_RESERVED_13	0x36800
#define WF_PERF_RESERVED_14	0x37000
#define WF_PERF_RESERVED_15	0x37800

#define WF_HS_ENTITY		17
#define WF_HS_CSR0		0x00000
/* Bit definitions for HS_CSR0	*/
#	define WF_HS_CSR0_HSA0_REV_SHIFT 12
#	define WF_HS_CSR0_HSA1_REV_SHIFT 44
#	define WF_HS_CSR0_HSD0_REV_SHIFT 16
#	define WF_HS_CSR0_HSD2_REV_SHIFT 48
#	define WF_HS_CSR0_HSA0_REV_MASK 0x0FUL
#	define WF_HS_CSR0_HSA1_REV_MASK 0x0FUL
#	define WF_HS_CSR0_HSD0_REV_MASK 0x0FUL
#	define WF_HS_CSR0_HSD2_REV_MASK 0x0FUL
#define WF_HS_CSR1		0x00048
#	define WF_HS_CSR1_HSD1_REV_SHIFT 16
#	define WF_HS_CSR1_HSD3_REV_SHIFT 48
#	define WF_HS_CSR1_HSD1_REV_MASK 0x0FUL
#	define WF_HS_CSR1_HSD3_REV_MASK 0x0FUL
#	define WF_HS_CSR1_HS_REV_SHIFT	52
#	define WF_HS_CSR1_HS_REV_MASK	0x0FUL
/* Bit definitions for HS_CSR1	*/


/*
 * Wildfire QBB-related defines
 */
#define WF_CPUS_PER_QBB		 4
#define WF_MEM_PER_QBB_MAX	 4
#define WF_MAX_CPUS		32
#define WF_MAX_QBBS		 8
#define WF_MAX_IOPS		WF_MAX_QBBS
#define WF_MAX_PCA_PER_IOP	 4
#define WF_NUM_TARGETS_PER_IOP	 4
#define WF_MAX_PCI_PER_PCA	 2	
#define WF_MAX_PCI_PER_IOP	 8
#define WF_MAX_PCI_PER_QBB	WF_MAX_PCI_PER_IOP
#define WF_MAX_PCIS		(WF_MAX_PCI_PER_IOP * WF_MAX_IOPS)
#define WF_MAX_HOSE_PER_QBB      4
  
#define WF_QBB_SHIFT		36
#define WF_QBB_MASK		0x0FUL
#define WF_PER_QBB_CPU_MASK	0x00000003
#define WF_PCI_SHIFT		33
#define WF_PORT_ID_SHIFT	WF_PCI_SHIFT
#define WF_ENTITY_SHIFT 18
#define WF_CPU_TO_QBB_NUM_SHIFT 2
#define WF_PCI_TO_PCA_NUM_SHIFT 1
#define WF_PCA_TO_QBB_NUM_SHIFT 2
#define WF_CSR_DATA_WRITE_SHIFT 3	/* 3-bit shift when data
					   included in CSR address */

/*
 * QBB QSD register bit definitions
 */
/* each cpu only 16-bits of QSD data aligned in u_long based on cpu-num */
#define WF_QSD_PER_CPU_DATA_SHIFT	16		
#define WF_QSD_DATA_MASK		0x0000FFFFUL	/* low 16-bits only */


#ifdef KERNEL

/* for pa-addr. gen/trans. macros below */
extern	u_long wf_io_space_pa_base;

/*
 * Macros to generate KSEG addresses from QBB numbers
 */
#define WF_QBB_CSR_BASE		0x0000000FFF800000UL
#define WF_QBB_IO_BASE(_Qbb_num_) \
	(wf_io_space_pa_base | \
	 ((u_long)((~(_Qbb_num_) & WF_QBB_MASK)) << WF_QBB_SHIFT))
#define WF_PCI_BASE(_Qbb_num_, _Port_Bus_Num_) \
	(WF_QBB_IO_BASE(_Qbb_num_) | ((u_long)(_Port_Bus_Num_) << WF_PCI_SHIFT))
#define WF_CSR_BASE(_Soft_Qbb_Num_, _Entity_, _Offset_)	\
	((WF_QBB_IO_BASE(_Soft_Qbb_Num_)) | WF_QBB_CSR_BASE | \
	((u_long)(_Entity_) << WF_ENTITY_SHIFT) | (u_long)(_Offset_))
#define WF_FAST_QSD_BASE(x)	\
	(wf_io_space_pa_base | \
	((u_long)WF_FAST_QSD_ENTITY << WF_ENTITY_SHIFT) | \
	 WF_QBB_CSR_BASE  | (u_long)(x))
/* The Base Physical Address has a 6-bit QBB ID field, so we
 * pad it with F.
 */
#define WF_BASE_PHYS_ADDR(_Soft_Qbb_Num_, _Entity_) \
        WF_CSR_BASE(_Soft_Qbb_Num_, _Entity_, 0) | 0xF0000000000
/* 
 * PCI-centric defines for WFCPU-PCI Adapter
 */

/* address generation/translation macros	*/
#define WF_PA_IO_BASE(Offset) (wf_io_space_pa_base | (u_long)(Offset))

/* Macro for wf_read_and_clear_csr, that's used specifically in the error
 * logging funcion, wfcpu_log_error.
 */
#define WF_READ_AND_CLEAR_CSR(offset) \
         wf_read_and_clear_csr(qbb_loop_num, entity_loop_num, offset)

/* Macro for wf_read_and_clear_by_0_csr, that's used specifically in the error
 * logging funcion, wfcpu_log_error. It clears by writing 0.
 */
#define WF_READ_AND_CLEAR_BY_0_CSR(offset) \
         wf_read_and_clear_by_0_csr(qbb_loop_num, entity_loop_num, offset)

/* Macro for wf_clear_csr, that's used specifically in the clearing
 * error bits funcion, wfcpu_clear_error_bits.
 */
#define WF_CLEAR_CSR(offset) \
         wf_clear_csr(qbb_loop_num, entity_loop_num, offset)

/* Macro for wf_w0tc_csr, that's used specifically in the clearing
 * error bits funcion, wfcpu_clear_error_bits. It clears by writing 0.
 */
#define WF_CLEAR_BY_0_CSR(offset) \
         wf_w0tc_csr(qbb_loop_num, entity_loop_num, offset)


/*
 * Function prototypes for wfqbb.c-sourced functions.
 */
/* CSR access routines */
u_long wf_read_qsd_csr(u_long qbb_id, u_long offset);
u_long wf_read_fast_qsd_csr(u_long offset);
u_long wf_read_csr(u_long qbb, u_long entity, u_long offset);
u_long wf_read_cpu_csr(u_long cpu_id, u_long offset);
u_long wf_read_qsa_csr(u_long qbb_id, u_long offset);
u_long wf_read_dtag_csr(u_long qbb_id, u_int dtag_num, u_long offset);
u_long wf_read_dir_csr(u_long qbb_id, u_long offset);
u_long wf_read_mem_csr(u_long qbb_id, u_int mem_num, u_long offset);
u_long wf_read_iop_csr(u_long qbb_id, u_long offset);
u_long wf_read_gp_csr(u_long qbb_id, u_long offset);
u_long wf_read_hs_csr(u_long offset);
#ifdef notyet
u_long wf_read_pca_csr(u_long hose_id, u_long offset);
u_long wf_read_pci_csr(u_long pci_id, u_long offset);
#endif

void wf_write_csr(u_long qbb, u_long entity, u_long offset, u_long data);
void wf_write_cpu_csr(u_long entity_id, u_long offset, u_long data);
void wf_write_qsd_csr(u_long qbb_id, u_long offset, u_long data);
void wf_write_qsa_csr(u_long qbb_id, u_long offset, u_long data);
void wf_write_dtag_csr(u_long qbb_id, u_int dtag_num, u_long offset, u_long data);
void wf_write_dir_csr(u_long qbb_id, u_long offset, u_long data);
void wf_write_mem_csr(u_long qbb_id, u_int mem_num, u_long offset, u_long data);
void wf_write_iop_csr(u_long qbb_id, u_long offset, u_long data);
void wf_write_gp_csr(u_long qbb_id, u_long offset, u_long data);
void wf_write_hs_csr(u_long offset, u_long data);
#ifdef not_yet
void wf_write_pca_csr(u_long id, ulong offset, ulong data);
void wf_write_pci_bus_csr( ulong id, ulong offset, ulong data);
#endif

void wf_clear_csr(u_long qbb, u_long entity, u_long offset);
void wf_clear_cpu_errors(int cpu_num);
void wf_clear_qsd_csr(u_long qbb_id, u_long offset);
void wf_clear_qsa_csr(u_long qbb_id, u_long offset);
void wf_clear_dtag_csr(u_long qbb_id, u_int dtag_num, u_long offset);
void wf_clear_dir_csr(u_long qbb_id, u_long offset);
void wf_clear_mem_csr(u_long qbb_id, u_int mem_num, u_long offset);
void wf_clear_iop_csr(u_long qbb_id, u_long offset);
void wf_clear_gp_csr(u_long qbb_id, u_long offset);
void wf_clear_hs_csr(u_long offset);
#ifdef not_yet
/* TODO: add offset to PCA_ENTITY field to get to proper PCI */
void wf_clear_pca_csr( ulong id, ulong offset);
/* TODO: add offset to PCA_ENTITY field to get to proper PCI */
void wf_clear_pci_csr( ulong id, ulong offset);
#endif

u_long wf_read_and_clear_csr(u_long qbb, u_long entity, u_long offset);
void   wf_w0tc_csr( u_long qbb, u_long entity, u_long offset);
u_long wf_read_and_clear_by_0_csr( u_long qbb, u_long entity, u_long offset );


/*
 * DMA window sizing alg.
 */
extern	void wfqbb_choose_dma_windows();


/*
 * Wildfire bus configuration related defines & structures
 */
#define CONFIG_SUCCESS 1
#define CONFIG_FAILURE 0

/*
 * WFQBB Bus info structure -- used in busconfl()
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
 *       int            (**intr)();
 *       io_handle_t    sparse_io_base;
 *       io_handle_t    sparse_mem_base;
 *       vm_offset_t    dense_mem_base;
 *      };
 */
struct wfqbb_bus_info {
        struct common_bus_info *common_bus_info;
        struct bus             *wfqbb_bus;
	u_long			soft_qbb_num;
	u_long			hard_qbb_num;
	int			present;
	int			active;
	int			configured;
	struct hal_rad	       *hal_radp;	/* ptr to hal_rad struct */
	long			cpu_present_inited;
	int			cpu_present[WF_CPUS_PER_QBB];
	int			mem_present[WF_MEM_PER_QBB_MAX];
	int			mem_lmp[WF_MEM_PER_QBB_MAX];
        ulong                   cfgtree_id;     /* qbb's config tree node id */
	int			sgpte_cma_node; /* v40g only */
	/* QBB-level rev information */
	int			rev_qsd[WF_QSD_MAX];
	int			rev_qsa;
	int			rev_dtag[WF_DTAG_MAX];
	int			rev_ioa;
	int			rev_iod;
	int			rev_dir_dma;
	int			rev_dir_dmd;
	struct rev_mem {
		int		mpa;
		int		mpd0;
		int		mpd1;
	} rev_mem[WF_MEM_PER_QBB_MAX];
	int			rev_gpa;
	int			rev_gpd; 
	int			rev_hsa0;
	int			rev_hsa1;
	int			rev_hsd0;
	int			rev_hsd2;
	int			rev_hsd1;
	int			rev_hsd3;
	int			rev_hs;
};

/*
 * WF IOP Bus info structure -- used in busconfl()
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
 *       int            (**intr)();
 *       io_handle_t    sparse_io_base;
 *       io_handle_t    sparse_mem_base;
 *       vm_offset_t    dense_mem_base;
 *      };
 */
struct wfiop_bus_info {
        struct common_bus_info *common_bus_info;
	u_long			soft_qbb_num;
	u_long			hard_qbb_num;
	int			present;
	int			active;
	int			configured;
	struct hal_rad	       *hal_radp;	/* ptr to hal_rad struct */
	/* the next group of elements are per-PCI bus specific
	 * and changes on each call to wfpci_adpt_cnfg, confl1.
	 */
	/* can create bridge csr addrs & IO bus addrs from these 2 */
	int			pca_port_num; 
	int			pci_port_num;
	u_long			dev_int_target[WF_MAX_PCA_PER_IOP];
	u_long			pca_primary_mask[WF_MAX_PCA_PER_IOP];
};

/*
 * wfqbb.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since wfcpu.h, wfqbb.h, & wfpci.h may be included in
 *	 one .c file, their debug definitions must not collide.
 */

extern	u_int	wfqbb_developer_debug;

/* To remove/add all debug printfs */
#define __WFQBBDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * wfqbb_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	WFQBBD_INOUT	0x00000001	/* routine entry and exit 	*/
#define WFQBBD_NUMA	0x00000020	/* NUMA-related info		*/
#define WFQBBD_QBBINFO	0x00001000	/* QBB config info		*/
#define WFQBBD_IOPINFO	0x00010000	/* IOP config info		*/
#define WFQBBD_PCIINFO	0x00100000	/* PCI config info		*/
#define WFQBBD_CSR	0x01000000	/* CSR access info		*/

/* New, testing hw-support debug printfs				*/
#define WFQBBD_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _WFQBBinout;
extern char * _WFQBBnuma;
extern char * _WFQBBqbbinfo;
extern char * _WFQBBiopinfo;
extern char * _WFQBBpciinfo;
extern char * _WFQBBcsr;
extern char * _WFQBBnot_yet;


/*
 * printf expansion that WFQBBPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _WFQBBxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __WFQBBDEBUG
#   define _WFQBBD_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_INOUT )  {	\
	    /* VARARGS */			\
            printf (_WFQBBinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_NUMA )  {	\
	    /* VARARGS */			\
            printf (_WFQBBnuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_QBBINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_QBBINFO)  {	\
	    /* VARARGS */			\
            printf (_WFQBBqbbinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_IOPINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_IOPINFO)  {	\
	    /* VARARGS */			\
            printf (_WFQBBiopinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_PCIINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_PCIINFO)  {	\
	    /* VARARGS */			\
            printf (_WFQBBpciinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_CSR(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_CSR)  {	\
	    /* VARARGS */			\
            printf (_WFQBBcsr); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _WFQBBD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( wfqbb_developer_debug & WFQBBD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_WFQBBnotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * wfqbb_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * WFQBBD_INOUT | WFQBBD_CONFIG
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define WFQBBPRINTF(F, X)	_##F(X)

#else  /* !__WFQBBDEBUG */
#   define WFQBBPRINTF(F, X)
#endif /* __WFQBBDEBUG */

#endif	/* KERNEL */

/* 
 * Define high temperature operating threshold for 
 * environmental monitoring 
 */
#define WF_HIGH_TEMP_THRESHOLD 40


#endif	/* __ARCH_ALPHA_HAL_WFQBB_H__ */

