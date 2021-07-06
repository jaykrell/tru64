/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: marvel_soc.h,v $
 * Revision 1.1.16.6  2003/10/28  19:51:11  Martine_Silbermann
 * 	Support for CPU offlining. Added a variable MV_MAX_NUM_IO_INTR_PER_CPU
 * 	to indicate how many IO7's interrupts a CPU can support. This value is
 * 	currently set to 2. You CANNOT change this value without making
 * 	changes to the firmware.
 *
 * Revision 1.1.16.5  2003/09/10  14:15:32  Robin_Lewis
 * 	protect the RBOX_INIT_SWAL bit from the os changes so we can detect errors when cpu is offline
 *
 * Revision 1.1.16.4  2003/09/02  16:00:35  Martine_Silbermann
 * 	Support for CPU offlining. Added a variable MV_MAX_NUM_IO_INTR_PER_CPU
 * 	to indicate how many IO7's interrupts a CPU can support. This value is
 * 	currently set to 2. You CANNOT change this value without making
 * 	changes to the firmware. This was submitted by mistake and taken out.
 * 	[2003/06/03  19:20:02;  Martine_Silbermann;]
 *
 * Revision 1.1.16.1  2002/11/08  20:24:51  Rajesh_R
 * 	Added receive_cpuset in mvsoc_bus_info structure this is requried
 * 	for interrupt distribution.
 *
 * Revision 1.1.4.18  2002/07/18  19:36:23  Frederick_Canter
 * 	Make RBOX_INTR_RES23 interrupt enable owned by the console
 * 	firmware (so OS doesn't touch it). Needed for IO7 pass 2
 * 	Memory Channel PALcode workaround.
 * 	[2002/07/18  18:48:40  Frederick_Canter]
 *
 * 	Change RBOX_ROUTE_SIZE from 128 to 256 (so EV79 will work).
 * 	[2002/07/18  13:49:22  Frederick_Canter]
 *
 * Revision 1.1.4.17  2002/07/17  20:35:57  Albert_Shen
 * 	Merge from platformos - Added #defines for error registers
 *
 * Revision 1.1.4.16  2002/07/16  19:42:15  Renny_Shen
 * 	Added Marvel system variant to mvsoc_bus_info
 *
 * Revision 1.1.4.15  2002/06/06  19:42:32  Frederick_Canter
 * 	Workaround a hardware restriction with initial revisions
 * 	of Raptor and the Xshelf (to enable data mover).
 * 	Define POx_MSK_HEI_NOAGP_MSKBITS for empty AGP port.
 * 	[2002/06/05  19:31:17  Frederick_Canter]
 *
 * Revision 1.1.4.14  2002/05/30  17:07:45  Joshua_Smith
 * Merge Information:  Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Joshua_Smith_newwild_br:1.1.14.1 Local Ancestor:1.1.13.1
 *    Merge Revision:  wcalphaos_br:1.1.4.13
 *   Common Ancestor:  1.1.4.12
 *      Added MSI register size define
 *
 * Revision 1.1.4.13  2002/04/23  13:56:05  Andrew_Duane
 * 	Fix typo: EV7_VPTCL -> EV7_VPCTL
 * 
 * Revision 1.1.4.12  2002/04/05  20:53:20  Albert_Shen
 * 	Added #defines for the I/O port, CBOX, BBOX, and ZBOX error registers.
 * 
 * Revision 1.1.4.11  2002/03/28  21:47:54  Aaron_Biver
 * 	Add #define DLY_RD_TO_IRQ_DISABLE for IO7 pass 2.
 * 
 * Revision 1.1.4.10  2002/03/27  21:44:30  Joshua_Smith
 * Merge Information:  Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Joshua_Smith_xpcsubmit_br:1.1.14.2 Local Ancestor:1.1.12.1
 *    Merge Revision:  wcalphaos_br:1.1.4.9
 *   Common Ancestor:  1.1.4.6
 *       Added MSI and data mover definitions
 * 
 * Revision 1.1.4.9  2002/03/27  21:09:34  Gregg_Rivinius
 * 	added bit definitions for POx_RST &
 * 	MV_IOA_POx_CTRL registers.
 * 
 * Revision 1.1.4.8  2002/03/27  15:11:08  Aaron_Biver
 * 	Add defines for RBOX_IO_CFG input/output enable bits.
 * 	Add defines for MV_IOA_POx_RST registers bits.
 * 	Add define for number of EV7 routing table entries.
 * 	Add phys_id to mvsoc_bus_info.
 * 
 * Revision 1.1.14.2  2002/03/20  18:52:57  Joshua_Smith
 *      Added MSI control register definitions
 * 
 * Revision 1.1.4.7  2002/03/18  16:23:58  Rajesh_R
 * 	Add defines for IO7 data mover support.
 * 	Additional Marvel cleanup.
 * 
 * Revision 1.1.4.6  2002/02/18  20:49:35  Rajesh_R
 * 	Marvel source file cleanup.
 * 
 * Revision 1.1.4.5  2002/01/24  23:11:17  Rajesh_R
 * 	Add RBOX_INTR_INTTO and RBOX_INTR_PALSTV interrupt enables
 * 	to mvcpu_initial_intr_enables to prevent interrupt
 * 	starvation whild probing IO.
 * 	Define which interrupts the console controls.
 * 
 * Revision 1.1.4.4  2002/01/02  18:46:48  Andrew_Duane
 * 	Add RBOX_ROUTE_BASE and RBOX_ROUTE_INCR
 * 
 * Revision 1.1.4.3  2001/12/14  18:16:39  Aaron_Biver
 * 	Add mvcpumod_info and mvsbb_info structures.
 * 
 * Revision 1.1.4.2  2001/11/16  18:15:53  Rajesh_R
 * 	Update Marvel RBOX_IMASK_* (interrupt enable bit) definitions.
 * 
 * Revision 1.1.4.1  2001/10/24  22:18:14  Rajesh_R
 * 	Created this file (cloned from Wildfire) for Marvel support.
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: marvel_soc.h,v $ $Revision: 1.1.16.6 $ (DEC) $Date: 2003/10/28 19:51:11 $
 */

#ifndef __ARCH_ALPHA_HAL_MARVEL_SOC_H__
#define __ARCH_ALPHA_HAL_MARVEL_SOC_H__

/*
 * -------------------------------------------------------------------
 * Simplified Marvel System: 4 EV7 Processors each with 16 GB Memory:
 * -------------------------------------------------------------------
 *
 *
 *		  |					      |
 *		  |					      |
 *	    +-----------+				+-----------+
 *	    |     N	|				|     N	    |
 *	    |		|				|	    |
 *	    |   CPU 0   |				|   CPU 1   |
 *	    |		|				|	    |
 *	----| W       E |-------------------------------| W       E |----
 *	    |		|				|	    |
 *	    |		|    +--------+   +--------+    |	    |
 *	    |         Z |----|        |   |        |----| Z         |
 *	    |     S     |    |        |   |        |    |     S     |
 *	    +-----------+    |  MEM 0 |   | MEM 1  |    +-----------+
 *		  |	     |        |   |        |	      |
 *		  |          |  16 GB |   | 16 GB  |          |
 *		  |	     |        |   |        |	      |
 *		  |          +--------+   +--------+	      |
 *		  |					      |
 *		  |          +--------+   +--------+	      |
 *		  |	     |        |   |        |	      |
 *		  |	     |        |   |        |	      |
 *		  |          |  MEM 3 |   | MEM 2  |          |
 *	    +-----------+    |        |   |        |    +-----------+
 *	    |     N     |    |  16 GB |   | 16 GB  |    |     N     |
 *	    |         Z |----|        |   |        |----| Z         |
 *	    |   CPU 3   |    +--------+   +--------+    |   CPU 2   |
 *	    |		|				|	    |
 *	----| W       E |-------------------------------| W       E |----
 *	    |		|				|	    |
 *	    |		|				|	    |
 *	    |		|				|	    |
 *	    |     S     |				|     S     |
 *	    +-----------+				+-----------+
 *		  |					      |
 *		  |					      |
 *
 */

/*
 * --------------------------------------------
 * Marvel (Programmer's) Physical Address Map:
 * --------------------------------------------
 *
 * Bit 43 is the I/O bit (must be 0 for memory space).
 * PE bits are the Processor Identifier.
 * Memory address layouts shown are for EV7 Pass 2. For pass 1
 * addressing, see Marvel System Programmer's Manual Chapter 2.
 *
 *  EV7 16GB Per Processor (up to 256 CPUs) Contiguous Memory Space
 *
 *    4   444333    3     33     3333222222222211111111110000000000
 *    3   210987    6     54     3210987654321098765432109876543210
 *  +---+---------+---+---------+----------------------------------+
 *  | 0 | PE[7:2] | 0 | PE[1:0] |          ADDRESS[33:0]           |
 *  +---+---------+---+---------+----------------------------------+
 *
 *
 *  +--------------------------+-------------------------------+
 *  | Processor ID ( PE[7:0] ) | Physical Memory Address Range |
 *  +--------------------------+-------------------------------+
 *  |            0             | 000.0000.0000 | 003.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            1             | 004.0000.0000 | 007.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            2             | 008.0000.0000 | 00B.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            3             | 00C.0000.0000 | 00F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            4             | 020.0000.0000 | 023.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            5             | 024.0000.0000 | 027.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            6             | 028.0000.0000 | 02B.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            7             | 02C.0000.0000 | 02F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          ...             |      ...      |      ...      |
 *  +--------------------------+-------------------------------+
 *  |          255             | 7EC.0000.0000 | 7EF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 */

/*
 *  EV7 32GB Per Processor (up to 128 CPUs) Contiguous Memory Space
 *
 *   4    4      44333  3   33    3333222222222211111111110000000000
 *   3    2      10987  6   54    3210987654321098765432109876543210
 *  +-+--------+-------+-+-------+----------------------------------+
 *  |0|ADDR[34]|PE[6:2]|0|PE[1:0]|           ADDRESS[33:0]          |
 *  +-+--------+-------+-+-------+----------------------------------+
 *
 *
 *  +--------------------------+-------------------------------+
 *  | Processor ID ( PE[7:0] ) | Physical Memory Address Range |
 *  +--------------------------+-------------------------------+
 *  |            0             | 000.0000.0000 | 003.FFFF.FFFF |
 *  |                          | 400.0000.0000 | 403.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            1             | 004.0000.0000 | 007.FFFF.FFFF |
 *  |                          | 404.0000.0000 | 407.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            2             | 008.0000.0000 | 00B.FFFF.FFFF |
 *  |                          | 408.0000.0000 | 40B.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            3             | 00C.0000.0000 | 00F.FFFF.FFFF |
 *  |                          | 40C.0000.0000 | 40F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            4             | 020.0000.0000 | 023.FFFF.FFFF |
 *  |                          | 420.0000.0000 | 423.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            5             | 024.0000.0000 | 027.FFFF.FFFF |
 *  |                          | 424.0000.0000 | 427.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            6             | 028.0000.0000 | 02B.FFFF.FFFF |
 *  |                          | 428.0000.0000 | 42B.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |            7             | 02C.0000.0000 | 02F.FFFF.FFFF |
 *  |                          | 42C.0000.0000 | 42F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          ...             |      ...      |      ...      |
 *  +--------------------------+-------------------------------+
 *  |          127             | 3EC.0000.0000 | 3EF.FFFF.FFFF |
 *  |                          | 7EC.0000.0000 | 7EF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 */

/*
 *  EV7 16GB Per Processor (up to 256 CPUs) Striped Memory Space
 *
 *   4 444333  3    3    333332222222222111111111100    0      0000000
 *   3 210987  6    5    432109876543210987654321098    7      6543210
 *  +-+-------+-+-------+---------------------------+-------+-----------+
 *  |0|PE[7:2]|1| PE[1] |       ADDRESS[33:7]       | PE[0] | ADDR[6:0] |
 *  +-+-------+-+-------+---------------------------+-------+-----------+
 *
 *
 *  +--------------------------+-------------------------------+
 *  | Processor ID ( PE[7:0] ) | Physical Memory Address Range |
 *  +--------------------------+-------------------------------+
 *  |           0:1            | 010.0000.0000 | 017.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           2:3            | 018.0000.0000 | 01F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           4:5            | 030.0000.0000 | 037.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           6:7            | 038.0000.0000 | 03F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           8:9            | 050.0000.0000 | 057.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          10:11           | 058.0000.0000 | 05F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          12:13           | 070.0000.0000 | 077.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          14:15           | 078.0000.0000 | 07F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           ...            |      ...      |      ...      |
 *  +--------------------------+-------------------------------+
 *  |         252:253          | 7F0.0000.0000 | 7F7.FFFF.FFFF |
 *  |         254:255          | 7F8.0000.0000 | 7FF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 */

/*
 *  EV7 32GB Per Processor (up to 128 CPUs) Striped Memory Space
 *
 *   4    4     44333  3   3   333332222222222111111111100   0   0000000
 *   3    2     10987  6   5   432109876543210987654321098   7   6543210
 *  +-+-------+-------+-+-----+---------------------------+-----+--------+
 *  |0|ADR[34]|PE[6:2]|1|PE[1]|       ADDRESS[33:7]       |PE[0]|ADR[6:0]|
 *  +-+-------+-------+-+-----+---------------------------+-----+--------+
 *
 *
 *  +--------------------------+-------------------------------+
 *  | Processor ID ( PE[7:0] ) | Physical Memory Address Range |
 *  +--------------------------+-------------------------------+
 *  |           0:1            | 010.0000.0000 | 017.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           2:3            | 018.0000.0000 | 01F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           4:5            | 030.0000.0000 | 037.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           6:7            | 03C.0000.0000 | 03F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           8:9            | 050.0000.0000 | 057.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          10:11           | 058.0000.0000 | 05F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          12:13           | 070.0000.0000 | 077.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          14:15           | 078.0000.0000 | 07F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          16:17           | 090.0000.0000 | 097.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          18:19           | 098.0000.0000 | 09F.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          20:21           | 0B0.0000.0000 | 0B7.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          22:23           | 0B8.0000.0000 | 0BF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          24:25           | 0D0.0000.0000 | 0D7.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          26:27           | 0D8.0000.0000 | 0DF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          28:29           | 0F0.0000.0000 | 0F7.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |          30:31           | 0F8.0000.0000 | 0FF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |           ...            |      ...      |      ...      |
 *  +--------------------------+-------------------------------+
 *  |         252:253          | 7F0.0000.0000 | 7F7.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *  |         254:255          | 7F8.0000.0000 | 7FF.FFFF.FFFF |
 *  +--------------------------+-------------------------------+
 *
 */

/*
 * Per-IO7 Physical Address Space (32 GB per IO7)
 *
 * Bit 43 is the I/O bit (must be 1).
 * IPE is the Inverted Processor Identifier.
 * See also, Marvel System Programmer's Manual Chapter 2.
 *
 *    4   44433333   33333222222222211111111110000000000
 *    3   21098765   43210987654321098765432109876543210
 *  +---+----------+-------------------------------------+
 *  | 1 | IPE[7:0] |            ADDRESS<34:0>            |
 *  +---+----------+-------------------------------------+
 *
 * PCI or AGP Address Space Detail
 *
 *    4   44433333    333   3 3 2 2 2 2 2 2 2 2  2211111111110000000000
 *    3   21098765    432   1 0 9 8 7 6 5 4 3 2  1098765432109876543210
 *  +---+----------+-------+-+-+-+-+-+-+-+-+-+-+-----------------------+
 *  | 1 | IPE[7:0] | Iport | | | | | | | | | | |     ADDRESS<21:0>     |
 *  +---+----------+-------+-+-+-+-+-+-+-+-+-+-+-----------------------+
 *			    0 x x x x x x x x x = Memory Space        2Gb
 *			    1 0 x x x x x x x x = reserved            1Gb
 *			    1 1 0 x x x x x x x = reserved          512Mb
 *			    1 1 1 0 x x x x x x = reserved          256Mb
 *			    1 1 1 1 0 x x x x x = reserved          128Mb
 *			    1 1 1 1 1 0 x x x x = reserved           64Mb
 *			    1 1 1 1 1 1 0 x x x = reserved           32Mb
 *			    1 1 1 1 1 1 1 0 x x = PCI Config Space   16Mb
 *			    1 1 1 1 1 1 1 1 0 x = PCI I/O Space       8Mb
 *			    1 1 1 1 1 1 1 1 1 0 = I/O ASIC CSRs       4Mb
 *			    1 1 1 1 1 1 1 1 1 1 = CPU IPRs (port 0)   4Mb
 *
 *  Port/Bus #	Inverted Port #		Usage
 *  ----------	---------------		---------------------------------
 *	0	       7		PCI-X Bus 0 and EV7 IPRs
 *	1	       6		PCI-X Bus 1
 *	2	       5		PCI-X Bus 2
 *	3	       4		4xAGP Bus 3
 *	4	       3		Reserved
 *	5	       2		Reserved
 *	6	       1		Reserved
 *	7	       0		IO7 CSRs and Interrupt Logic
 */

/*
 * A few defines used by the VM memory troller interface code.
 */
#define HI2LO_INT_SHIFT_32	32
#define LO2HI_INT_SHIFT_32	32
#define LOW_30_BITS		0x000000003fffffffUL
#define LOW_32_BITS		0x00000000ffffffffUL


#ifndef ASSEMBLER		/* enables include by locore.s */

#define ERROR_INVALID           -1
#define ERROR_CORR              0x000000
#define ERROR_UNCORR            0x000001

/*
 * EV7 CBOX IPRs
 */
#define CBOX_CTL		0x00e000
/* Bit definitions for CBOX_CTL */
#	define	CBOX_CTL_ENA_32GB		0x000004000
#define CBOX_STP_CTL		0x00e010
/* Bit definitions for CBOX_STP_CTL (EV7 pass 2, EV79, ...) */
#	define	CBOX_STP_CTL_MASK		0x0ffffffff
#	define	CBOX_STP_CTL_DEFAULT		0x100000000
#	define	CBOX_STP_CTL_REGION_16MB	0x200000000
#define CBOX_ACC_CTL		0x00e020
/* Bit definitions for CBOX_ACC_CTL (EV7 pass 2, EV79, ...) */
#	define	CBOX_ACC_CTL_MASK		0x0ffffffff
#	define	CBOX_ACC_CTL_DEFAULT		0x100000000
#define CBOX_LCL_SET		0x00e030
#define CBOX_GBL_SET		0x00e040
#define CBOX_TMR_CTL		0x00e050
#define CBOX_PRF_CTL		0x00e060
#define CBOX_PRF_ADR		0x00e070
#define CBOX_PRF_MAT		0x00e090
#define CBOX_PRF_CNT		0x00e0b0
#define CBOX_DDP_ERR_STS	0x01c030
#define CBOX_DDP_ERR_UNCORR     0x000001
#define CBOX_DDP_ERR_CORR       0x000002
#define CBOX_DDP_ERR_SEO        0x000004
#define CBOX_DDP_ERR_SIDE       0x20000000

/* 
 * EV7 X_STAT IPRs
 */
#define I_STAT_PAR              0x20000000
#define DC_STAT_TPERR_P0        0x000001
#define DC_STAT_TPERR_P1        0x000002
#define DC_STAT_ECC_ERR_ST      0x000004
#define DC_STAT_ECC_ERR_LD      0x000008
#define DC_STAT_SEO             0x000010
#define C_STAT_REG              0x00001F
#define C_STAT_ISTR_BC_ERR      0x00000A
#define C_STAT_ISTR_BC_DBLQ     0x00000C
#define C_STAT_ISTR_BC_DBLO     0x00000E
#define C_STAT_DSTR_BC_ERR      0x000002
#define C_STAT_DSTR_BC_DBLQ     0x000004
#define C_STAT_DSTR_BC_DBLO     0x000006
#define C_STAT_DSTR_DC_ERR      0x000015
#define C_STAT_DSTR_BAD_OW      0x000005
#define C_STAT_ISTR_BAD_OW      0x00000D
#define C_STAT_DERR_RSP         0x000014
#define C_STAT_IERR_RSP         0x00001C
#define C_STAT_DCMAF_TIMEOUT_RSP 0x000011
#define C_STAT_ICMAF_TIMEOUT_RSP 0x000019
#define C_STAT_DCMAF_TIMEOUT_COH 0x000012
#define C_STAT_ICMAF_TIMEOUT_COH 0x00001A
#define C_STAT_WRIO_TIMEOUT     0x000013

/*
 * EV7 BBOX IPRs
 */
#define BBOX_CTL		0x01c000
#define BBOX_ERR_STS		0x01c010
#define BBOX_ERR_IDX		0x01c020
#define BBOX_DAT_RMP		0x01c040
#define BBOX_ERR_STS_UNCORR     0x1000000
#define BBOX_ERR_STS_CORR       0x2000000
#define BBOX_ERR_STS_SEO        0x4000000

/*
 * EV7 ZBOX IPRs
 */
#define ZBOX0_DIFT_CTL		0x010000
#define ZBOX0_DIFT_TIMEOUT	0x010010
#define ZBOX0_DRAM_ERR_ADR	0x010020
#define ZBOX0_DIFT_ERR_STATUS	0x010030
#define ZBOX0_DRAM_TIMING_CTL2	0x012000
#define ZBOX0_DRAM_TIMING_CTL4	0x012010
#define ZBOX0_DRAM_CALIB_CTL1	0x012020
#define ZBOX0_DRAM_REFRESH_ROW	0x012030
#define ZBOX0_DRAM_REFR_CTL	0x012040
#define ZBOX0_FRC_ERR_ADR	0x012100
#define ZBOX0_DRAM_CALIB_CTL2	0x012110
#define ZBOX0_DRAM_TIMING_CTL3	0x012120
#define ZBOX0_DRAM_INIT_CTL	0x012130
#define ZBOX0_ZPM_CTR0		0x012200
#define ZBOX0_ZPM_CTR1		0x012210
#define ZBOX0_ZPM_CTL		0x012220
#define ZBOX0_DRAM_MAPPER_CTL	0x012230
#define ZBOX0_DRAM_ERR_STATUS1	0x014000
#define ZBOX0_DRAM_ERR_STATUS2	0x014010
#define ZBOX0_DRAM_SWEEP_DIR	0x014020
#define ZBOX0_DRAM_ERR_STATUS3	0x014030
#define ZBOX0_DRAM_ERROR_CTL	0x014100
#define ZBOX0_DRAM_TIMING_CTL1	0x014110

#define ZBOX1_DIFT_CTL		0x160000
#define ZBOX1_DIFT_TIMEOUT	0x160010
#define ZBOX1_DRAM_ERR_ADR	0x160020
#define ZBOX1_DIFT_ERR_STATUS	0x160030
#define ZBOX1_DRAM_TIMING_CTL2	0x018000
#define ZBOX1_DRAM_TIMING_CTL4	0x018010
#define ZBOX1_DRAM_CALIB_CTL1	0x018020
#define ZBOX1_DRAM_REFRESH_ROW	0x018030
#define ZBOX1_DRAM_REFR_CTL	0x018040
#define ZBOX1_FRC_ERR_ADR	0x018100
#define ZBOX1_DRAM_CALIB_CTL2	0x018110
#define ZBOX1_DRAM_TIMING_CTL3	0x018120
#define ZBOX1_DRAM_INIT_CTL	0x018130
#define ZBOX1_ZPM_CTR0		0x018200
#define ZBOX1_ZPM_CTR1		0x018210
#define ZBOX1_ZPM_CTL		0x018220
#define ZBOX1_DRAM_MAPPER_CTL	0x018230
#define ZBOX1_DRAM_ERR_STATUS1	0x01a000
#define ZBOX1_DRAM_ERR_STATUS2	0x01a010
#define ZBOX1_DRAM_SWEEP_DIR	0x01a020
#define ZBOX1_DRAM_ERR_STATUS3	0x01a030
#define ZBOX1_DRAM_ERROR_CTL	0x01a100
#define ZBOX1_DRAM_TIMING_CTL1	0x01a110

/*
 * ZBOXn_DRAM_ERR_STATUS3: DRAM Error Status 3 bit definitions.
 */
#define ZBOXn_DRAM_ERR_STATUS3_MASK	0x000e3ff
#define ZBOXn_DRAM_ERR_STATUS3_PAR	0x0000001
#define ZBOXn_DRAM_ERR_STATUS3_SGL	0x0000002
#define ZBOXn_DRAM_ERR_STATUS3_RAID	0x0000004
#define ZBOXn_DRAM_ERR_STATUS3_MAPF	0x0000008
#define ZBOXn_DRAM_ERR_STATUS3_GE3	0x0000010
#define ZBOXn_DRAM_ERR_STATUS3_DBL	0x0000020
#define ZBOXn_DRAM_ERR_STATUS3_D2L	0x0000040
#define ZBOXn_DRAM_ERR_STATUS3_TCAL	0x0000080
#define ZBOXn_DRAM_ERR_STATUS3_TIME	0x00000100
#define ZBOXn_DRAM_ERR_STATUS3_DIFT	0x00000200
#define ZBOXn_DRAM_ERR_STATUS3_MEO	0x00002000
#define ZBOXn_DRAM_ERR_STATUS3_SEO	0x00004000
#define ZBOXn_DRAM_ERR_STATUS3_SWP	0x00008000

#define ZBOXn_DRAM_ERR_STATUS1_MASK     0x000007E0
#define ZBOXn_DRAM_ERR_STATUS3_TYPE     0x00000032

/*
 * ZBOX0_DRAM_ERR_ADR: ZBOX DRAM Error Address bit definitions.
 */
#define ZBOX0_DRAM_ERR_ADR_MASK		0x1fffffff
#define ZBOX0_DRAM_ERR_ADR_SHIFT	6

/*
 * ZBOXn_DIFT_ERR_STATUS: ZBOX DIFT Error Status bit definitions.
 */
#define ZBOXn_DIFT_ERR_STATUS_MASK	0xffff

/*
 * EV7 On-Chip Logic Analyzer IPRs
 */
#define OCLA1_TMATCH		0x024000
#define OCLA1_TMASK		0x024010
#define OCLA1_CTL		0x024020
#define OCLA1_MISC		0x024030
#define OCLA1_SMATCH		0x024100
#define OCLA1_SMASK		0x024110
#define OCLA1_DATA		0x024120
#define OCLA1_PC_TMATCH		0x024200
#define OCLA1_PC_TMASK		0x024210
#define OCLA1_PC_SMATCH		0x024220
#define OCLA1_PC_SMASK		0x024230
#define OCLA1_PC_CTL		0x024240
#define OCLA0_TMATCH		0x026000
#define OCLA0_TMASK		0x026010
#define OCLA0_CTL		0x026020
#define OCLA0_MISC		0x026030
#define OCLA0_SMATCH		0x026100
#define OCLA0_SMASK		0x026110
#define OCLA0_DATA		0x026120
#define DID0			0x028000
#define DID1			0x028010
#define DID2			0x028020
#define EV7_VPCTL		0x028040

/*
 * EV7 RBOX IPRs
 */
#define RBOX_CFG	0x000000
#define RBOX_NSVC	0x000010
#define RBOX_EWVC	0x000020
#define RBOX_WHOAMI	0x000030
#define RBOX_TCTL	0x000040
#define RBOX_INT	0x000050
#define RBOX_IMASK	0x000060
#define RBOX_IREQ	0x000070
#define RBOX_INTQ	0x000080
#define RBOX_INTA	0x000090
#define RBOX_IT		0x0000a0
#define RBOX_SCRATCH1	0x0000b0
#define RBOX_SCRATCH2	0x0000c0			/* not in EV7 pass 1 */
#define RBOX_L_ERR	0x0000d0
#define GIO_CFG		0x000100
#define GIO_DAT		0x000110
#define GIO_CTL		0x000120
/*	RBOX_ROUTE	0x002000 - 0x003ff0 */
#define RBOX_ROUTE_SIZE	     256		/* EV7 = 128, but that's ok */
#define RBOX_ROUTE_BASE	0x002000
#define RBOX_ROUTE_INCR	0x000010
#define RBOX_ROUTE_END	(RBOX_ROUTE_BASE + (RBOX_ROUTE_INCR * RBOX_ROUTE_SIZE))
#define RBOX_N_CFG	0x004000
#define RBOX_N_ERR	0x004010
#define RBOX_N_PERF	0x004020
#define RBOX_N_T1CFG	0x004030
#define RBOX_N_T2CFG	0x004040
#define RBOX_S_CFG	0x006000
#define RBOX_S_ERR	0x006010
#define RBOX_S_PERF	0x006020
#define RBOX_S_T1CFG	0x006030
#define RBOX_S_T2CFG	0x006040
#define RBOX_E_CFG	0x008000
#define RBOX_E_ERR	0x008010
#define RBOX_E_PERF	0x008020
#define RBOX_E_T1CFG	0x008030
#define RBOX_E_T2CFG	0x008040
#define RBOX_W_CFG	0x00a000
#define RBOX_W_ERR	0x00a010
#define RBOX_W_PERF	0x00a020
#define RBOX_W_T1CFG	0x00a030
#define RBOX_W_T2CFG	0x00a040
#define RBOX_IO_CFG	0x00c000
/* Bit definitions for RBOX_IO_CFG */
#	define RBOX_IO_CFG_OE		0x1
#	define RBOX_IO_CFG_IE		0x4
#define RBOX_IO_ERR	0x00c010
#define RBOX_IO_PERF	0x00c020
#define RBOX_IO_T1CFG	0x00c030
#define RBOX_IO_BUF	0x00c040
#define RBOX_FANDI1	0x080000
#define RBOX_FANDI2	0x0c0000
#define RBOX_FANDI3	0x100000			/* not in EV7 pass 1 */
#define RBOX_FANDI4	0x140000			/* not in EV7 pass 1 */
/*
 * RBOX_NSVC: North-South Virtual Selection bit definitions.
 */
#define RBOX_NSVC_VCS_MASK	0x0000ffff
#define RBOX_NSVC_ROT		0x00010000
#define RBOX_NSVC_CPP		0x00020000
#define RBOX_NSVC_CWT		0x00040000
#define RBOX_NSVC_Z1D		0x00080000
#define RBOX_NSVC_DWR		0x00100000	/* disables remote IPR writes */

/*
 * RBOX_EWVC: East-West Virtual Selection bit definitions.
 */
#define RBOX_EWVC_VCS_MASK	0x0000ffff
#define RBOX_EWVC_FITV_MASK	0x003f0000
#define RBOX_EWVC_Z0FITE	0x00400000
#define RBOX_EWVC_Z1FITE	0x00800000

/*
 * RBOX Interrupt Status/Enable bit definitions.
 * Shared by: RBOX_INT, RBOX_IMASK, and RBOX_IREQ.
 */
#define RBOX_INTR_CCRDL   0x00000001  /* CBOX correctable lock-step      IRQ0 */
#define RBOX_INTR_CCRDN   0x00000002  /* CBOX correctable no-lock-step   IRQ0 */
#define RBOX_INTR_Z0CRD   0x00000004  /* ZBOX0 correctable               IRQ0 */
#define RBOX_INTR_Z1CRD   0x00000008  /* ZBOX1 correctable               IRQ0 */
#define RBOX_INTR_RCRD    0x00000010  /* RBOX correctable                IRQ0 */
#define RBOX_INTR_CPERF   0x00000020  /* CBOX performance counter        IRQ0 */
#define RBOX_INTR_Z0PERF  0x00000040  /* ZBOX0 performance counter       IRQ0 */
#define RBOX_INTR_Z1PERF  0x00000080  /* ZBOX1 performance counter       IRQ0 */
#define RBOX_INTR_RPERF   0x00000100  /* RBOX performance counter        IRQ0 */
#define RBOX_INTR_GIOL    0x00000200  /* GIO Interrupt                   IRQ0 */
#define RBOX_INTR_IOACRD  0x00000400  /* I/O ASIC correctable/SW         IRQ0 */
#define RBOX_INTR_RES11   0x00000800  /* reserved for SW                 IRQ0 */
#define RBOX_INTR_INTQ    0x00001000  /* Interrupt Queue                 IRQ1 */
#define RBOX_INTR_RES13   0x00002000  /* reserved for SW                 IRQ1 */
#define RBOX_INTR_PALSTV  0x00004000  /* PAL Intr Starvation (was RES14) IRQ1 */
#define RBOX_INTR_INTT    0x00008000  /* Interval Timer                  IRQ2 */
#define RBOX_INTR_INTTO   0x00010000  /* Interrupt Que retry timeout/SW  IRQ2 */
#define RBOX_INTR_IOHP    0x00020000  /* Hot-Plug IO Event/SW            IRQ2 */
#define RBOX_INTR_SWAL    0x00040000  /* SW ALERT                        IRQ3 */
#define RBOX_INTR_PALIPI  0x00080000  /* PAL IP interrupt (was RES19)    IRQ3 */
#define RBOX_INTR_RES20   0x00100000  /* reserved for SW                 IRQ5 */
#define RBOX_INTR_GIOH    0x00200000  /* GIO high priority interrupt     IRQ4 */
#define RBOX_INTR_HALT    0x00400000  /* HALT/SW                         IRQ4 */
#define RBOX_INTR_RES23   0x00800000  /* reserved for SW                 IRQ4 */
#define RBOX_INTR_HWAL    0x01000000  /* HW ALERT                        IRQ5 */
#define RBOX_INTR_CUCE    0x02000000  /* CBOX uncorrectable              IRQ5 */
#define RBOX_INTR_Z0UCE   0x04000000  /* ZBOX0 uncorrectable             IRQ5 */
#define RBOX_INTR_Z1UCE   0x08000000  /* ZBOX1 uncorrectable             IRQ5 */
#define RBOX_INTR_RUCE    0x10000000  /* RBOX uncorrectable              IRQ5 */
#define RBOX_INTR_IOAUCE  0x20000000  /* I/O ASIC Error/SW               IRQ5 */
#define RBOX_INTR_OCLA0   0x40000000  /* OCLA0                           IRQ5 */
#define RBOX_INTR_OCLA1   0x80000000  /* OCLA1                           IRQ5 */

#define RBOX_INT_UCEMASK  (RBOX_INTR_CUCE | \
			   RBOX_INTR_Z0UCE | RBOX_INTR_Z1UCE | \
			   RBOX_INTR_RUCE | RBOX_INTR_IOAUCE)

#define RBOX_INT_CEMASK   (RBOX_INTR_CCRDL | RBOX_INTR_CCRDN | \
			   RBOX_INTR_Z0CRD | RBOX_INTR_Z1CRD | \
			   RBOX_INTR_RCRD | RBOX_INTR_IOACRD)

#define RBOX_INT_ERRMASK  (RBOX_INT_UCEMASK | RBOX_INT_CEMASK)

#define RBOX_INT_IOAMASK  (RBOX_INTR_IOACRD | RBOX_INTR_IOAUCE)

#define RBOX_INT_CRLMASK  (RBOX_INT_ERRMASK | RBOX_INTR_CPERF | \
			   RBOX_INTR_Z0PERF | RBOX_INTR_Z1PERF | \
			   RBOX_INTR_RPERF)

/*
 * Interrupt enables currently not set by the OS:
 *
 *    RBOX_INTR_IOHP	Controlled by the console.
 *    RBOX_INTR_SWAL	Controlled by the console.
 *    RBOX_INTR_HWAL    Controlled by the console.
 *    RBOX_INTR_OCLA0	Controlled by marvel_pfm driver.
 *    RBOX_INTR_OCLA1	Controlled by marvel_pfm driver.
 *    RBOX_INTR_CPERF	Controlled by marvel_pfm driver.
 *    RBOX_INTR_Z0PERF	Controlled by marvel_pfm driver.
 *    RBOX_INTR_Z1PERF	Controlled by marvel_pfm driver.
 *    RBOX_INTR_RPERF   Controlled by marvel_pfm driver.
 */
#define RBOX_INTR_CONSOLE_OWNS	(RBOX_INTR_IOHP|RBOX_INTR_HWAL|RBOX_INTR_RES23|RBOX_INTR_SWAL) /* Changed for QAR 96582 */

/*
 * Base set of RBOX_IMASK bits which software requires be enabled.
 */
#define RBOX_IMASK_BASE_IE	(RBOX_INTR_GIOH | RBOX_INTR_PALIPI | \
				 RBOX_INTR_INTTO | RBOX_INTR_PALSTV | \
				 RBOX_INTR_INTT | RBOX_INTR_INTQ | \
				 RBOX_INTR_HALT | RBOX_INTR_GIOL)

#define RBOX_IMASK_FINAL_IE	(RBOX_IMASK_BASE_IE | \
				 RBOX_INT_UCEMASK | RBOX_INT_CEMASK)
				 
/*
 * RBOX_L_ERR: RBOX Local Port Error Status bit definitions.
 */
#define RBOX_L_ERR_MASK		0x0000007f
#define RBOX_L_ERR_CBP		0x00000001
#define RBOX_L_ERR_Z0P		0x00000002
#define RBOX_L_ERR_Z1P		0x00000004
#define RBOX_L_ERR_RPE		0x00000008
#define RBOX_L_ERR_Z0FI		0x00000010
#define RBOX_L_ERR_Z1FI		0x00000020
#define RBOX_L_ERR_CBD		0x00000040

/*
 * RBOX_IO_ERR: RBOX I/O Port Error Status bit definitions.
 */
#define RBOX_IO_ERR_MASK	0x0000fe03
#define RBOX_IO_ERR_SBE		0x00000001
#define RBOX_IO_ERR_MSE		0x00000002
#define RBOX_IO_ERR_SYN_MASK	0x000001fc
#define RBOX_IO_ERR_DBE		0x00000200
#define RBOX_IO_ERR_FCE		0x00000400
#define RBOX_IO_ERR_BPE		0x00000800
#define RBOX_IO_ERR_RSTX	0x00001000
#define RBOX_IO_ERR_FWTX	0x00002000
#define RBOX_IO_ERR_RITX	0x00004000
#define RBOX_IO_ERR_WITX	0x00008000

/*
 * RBOX_x_ERR: RBOX (NSEW) Port Error Status bit definitions.
 */
#define RBOX_NSEW_ERR_MASK	0x0007fe03
#define RBOX_NSEW_ERR_SBE	0x00000001
#define RBOX_NSEW_ERR_MSE	0x00000002
#define RBOX_NSEW_ERR_SYN_MASK	0x000001fc
#define RBOX_NSEW_ERR_DBE	0x00000200
#define RBOX_NSEW_ERR_FCE	0x00000400
#define RBOX_NSEW_ERR_BPE	0x00000800
#define RBOX_NSEW_ERR_RSTX	0x00001000
#define RBOX_NSEW_ERR_RETX	0x00002000
#define RBOX_NSEW_ERR_FWTX	0x00004000
#define RBOX_NSEW_ERR_RITX	0x00008000
#define RBOX_NSEW_ERR_WITX	0x00010000
#define RBOX_NSEW_ERR_FOTX	0x00020000
#define RBOX_NSEW_ERR_FITX	0x00040000

#endif	/* #ifndef ASSEMBLER */

/*
 * Due to OLAR requirements, MV_MAX_SOCS must be
 * sized for the largest possible system configuration.
 * The largest Marvel is 64 processors (64 SOCs) with two
 * hard partitions for a total of 128 processors. So,
 * MV_MAX_SOCS for an OS instance is 64.
 */
#define MV_MAX_SBBS		8		/* Max # of drawers	      */
#define MV_MAX_SOCS_PER_CPUMOD	2		/* Max # of SOCs per cpumod   */
#define MV_MAX_CPUMODS_PER_SBB  4		/* Max # cpumods in a drawer  */
#define MV_MAX_SOCS_PER_SBB	(MV_MAX_SOCS_PER_CPUMOD * MV_MAX_CPUMODS_PER_SBB)
#define MV_MAX_CPUMODS		(MV_MAX_SBBS * MV_MAX_CPUMODS_PER_SBB)
#define MV_MAX_SOCS		(MV_MAX_SBBS * MV_MAX_CPUMODS_PER_SBB * MV_MAX_SOCS_PER_CPUMOD)
						/* see also MAX_RADS in rad.h */
#define MV_MAX_NUM_IO_INTR_PER_CPU 2		/* max # of IO7s a CPU can handle intr. from */

#define MV_EV7_P1_STRIPE_SET	4		/* pass1 stripe across 4 CPUs */
#define MV_EV7_P2_STRIPE_SET	2		/* pass2 stripe across 2 CPUs */
#define MV_EV79_STRIPE_SET	2		/* EV79 stripe across 2 CPUs  */
#define MV_EV7_STRIPE_BIT	(1L << 36)	/* EV7/EV79 stripe addr bit */
#define MV_EV7_RT_SIZE		RBOX_ROUTE_SIZE
#define MV_EV7_RT_ENTRY_NULL	0xffffffffffffffff

#define MV_MAX_IOAS		MV_MAX_SOCS
#define MV_MAX_PCI_PER_IOA	4
#define MV_IRQ_IOA_PORT_MASK	0x1f		/* 32 intr per IO7 PCI bus */
#define MV_NUM_TARGETS_PER_IOA	4
#define MV_MAX_PCI_PER_SOC	MV_MAX_PCI_PER_IOA
#define MV_MAX_PCIS		(MV_MAX_PCI_PER_IOA * MV_MAX_IOAS)
#define MV_MAX_HOSE_PER_SOC	4
#define MV_IOA_PID_MASK		0x1ff
  
#define MV_IPE_SHIFT		35
#define MV_IPE_MASK		0xff
#define MV_PORT_MASK		0x7
#define MV_PORT_SHIFT		32
#define MV_PCI_SHIFT		33
#define MV_PORT_ID_SHIFT	MV_PCI_SHIFT

#ifndef ASSEMBLER		/* enables include by locore.s */

/*
 * IO7 - CSR Port Control and Status Registers (port 7)
 */
#define MV_IOA_IO_ASIC_REV		0x300000
/* Bit definitions for IO_ASIC_REV */
#	define MV_IO_ASIC_REV_MASK	0xf
#	define MV_IO_ASIC_REV_PASS1	0
#	define MV_IO_ASIC_REV_PASS2	1
#	define MV_IO_ASIC_TYPE_SHIFT	4
#	define MV_IO_ASIC_TYPE_MASK	0xf
#	define MV_IO_ASIC_TYPE_IO7	0x1
#define MV_IOA_IO_SYS_REV		0x300040	/* SER_CHAIN4 */
/* Bit definitions for IO_SYS_REV */
#	define MV_IO_SYS_REV_BP_Rev_MASK	0xf
#	define MV_IO_SYS_REV_BP_Type_MASK	0xf
#	define MV_IO_SYS_REV_BP_Type_SHIFT	4
#	define BP_Type_Standard_Marvel		0x0
#	define BP_Type_Marvel_2P		0x1
#	define BP_Type_X_shelf			0x2
#	define BP_Type_Standard_Yosemite	0x3
#	define BP_Type_Standard_CSS_Telco	0x4
#	define BP_Type_Raptor			0x5
#	define MV_IO_SYS_REV_BP_Num_MASK	0xf
#	define MV_IO_SYS_REV_BP_Num_SHIFT	8
#	define MV_IO_SYS_REV_Hose_MASK		0x7
#	define MV_IO_SYS_REV_Hose_SHIFT		12
#	define MV_IO_SYS_REV_Micro_Pres		0x8000
#	define MV_IO_SYS_REV_Ser_dat_def	0x10000
#define MV_IOA_IO_MISC_INFO		0x300080	/* SER_CHAIN3 */
/* Bit definitions for IO_MISC_INFO */
#	define IO_MISC_INFO_PBM_SYS_EVENT_MASK	0xff
#define MV_IOA_PO7_RST1			0x3000c0	/* PLL1 */
#define MV_IOA_PO7_RST2			0x300100	/* PLL2 */
#define MV_IOA_PO0_RST			0x300140	/* PLL3 */
#define MV_IOA_PO1_RST			0x300180	/* PLL4 */
#define MV_IOA_PO2_RST			0x3001c0	/* PLL5 */
#define MV_IOA_PO3_RST			0x300200	/* PLL6 */
/* Bit definitions for POx_RST */
#       define POx_RST_PLL_DIS     0x0000000000000004 /* PLL_DIS   */
#       define POx_RST_PLL_RNGA    0x0000000000000038 /* PLL_RNGA  */
#       define POx_RST_PLL_RNGB    0x00000000000001c0 /* PLL_RNGB  */
#       define POx_RST_PLL_MULT    0x0000000000001e00 /* PLL_MULT  */
#       define POx_RST_PLL_TUNE    0x00000000007fe000 /* PLL_TUNE  */
#       define POx_RST_SLOW_NP     0x0000000004000000 /* SLOW_NP   */
#       define POx_RST_CKDIV       0x000000ff00000000 /* CKDIV     */
#       define POx_RST_SP_RATIO    0x00000f0000000000 /* SP_RATIO  */
#       define POx_RST_PCIX_MODE   0x0000100000000000 /* PCIX_MODE */
#       define POx_RST_OUTZ        0x0000200000000000 /* OUTZ      */
#       define POx_RST_FWD_EN      0x0000400000000000 /* FWD_EN    */
#       define POx_RST_RST         0x0000800000000000 /* RST       */
#       define POx_RST_PCIXCAP     0x0001000000000000 /* PCIXCAP   */
#       define POx_RST_AGP_RG      0x0002000000000000 /* AGP_RG    */
/* definition of values of fields within POx_RST */
#define POx_RST_PLL_RNGB_2X    4
#define POx_RST_PLL_RNGB_1X4X  6
#define POx_RST_PLL_RNGB_SHIFT 6

#define MV_IOA_IO7_DWNH			0x300240	/* IO7_DWNH */
#define MV_IOA_IO7_MAF			0x300280	/* MAF_NUM */
#define MV_IOA_IO7_MAF_TO		0x3002c0
#define MV_IOA_IO7_ACR0			0x300300	/* ACC_CLUMP */
#define MV_IOA_IO7_ACR1			0x300340	/* PMASK */
#define MV_IOA_IO7_ACR2			0x300380	/* IOMASK */
#define MV_IOA_IO7_UPH			0x3003c0	/* UPH_CTL */
#define MV_IOA_IO7_UPH_TO		0x300400	/* UPH_TO */
#define MV_IOA_RBX_IREQ_OFF		0x300440	/* NDX_INTA */
#define MV_IOA_RBX_INTA_OFF		0x300480	/* NDX_INTS */
#define MV_IOA_INT_RTY			0x3004c0	/* INT_RTY */
#define MV_IOA_PO7_MONCTL		0x300500
#define MV_IOA_PO7_CTRA			0x300540	/* CTRA */
#define MV_IOA_PO7_CTRB			0x300580	/* CTRB */
#define MV_IOA_PO7_CTR56		0x3005c0
#define MV_IOA_PO7_SCRATCH		0x300600
#define MV_IOA_PO7_XTRA_A		0x300640
#define MV_IOA_PO7_XTRA_TS		0x300680
#define MV_IOA_PO7_XTRA_Z		0x3006c0
							/* 0x300700 rsvd */
							/* 0x301fc0      */
#define MV_IOA_PO7_ERROR_SUM		0x302000
/* Bit definitions for MV_IOA_PO7_ERROR_SUM */
#define		PO7_ERROR_SUM_ALL_ERRBITS	0x7ff8ffff00000000
						/* bits <31:0> reserved */
#define		PO7_ERROR_SUM_CR_SBE		0x0000000100000000
#define		PO7_ERROR_SUM_CR_SBE2		0x0000000200000000
#define		PO7_ERROR_SUM_CR_PIO_WBYTE	0x0000000400000000
#define		PO7_ERROR_SUM_CR_CSR_NXM	0x0000000800000000
#define		PO7_ERROR_SUM_CR_RPID_ACV	0x0000001000000000
#define		PO7_ERROR_SUM_CR_RSP_NXM	0x0000002000000000
#define		PO7_ERROR_SUM_CR_ERR_RESP	0x0000004000000000
#define		PO7_ERROR_SUM_CR_CLK_DERR	0x0000008000000000
#define		PO7_ERROR_SUM_CR_DAT_DBE	0x0000010000000000
#define		PO7_ERROR_SUM_CR_DAT_GRBG	0x0000020000000000
#define		PO7_ERROR_SUM_MAF_TO		0x0000040000000000
#define		PO7_ERROR_SUM_UGBGE		0x0000080000000000
#define		PO7_ERROR_SUM_UN_MAF_LOST	0x0000100000000000
#define		PO7_ERROR_SUM_UN_PKT_OVF	0x0000200000000000
#define		PO7_ERROR_SUM_UN_CDT_OVF	0x0000400000000000
#define		PO7_ERROR_SUM_UN_DEALLOC	0x0000800000000000
						/* bits <50:48> reserved */
#define		PO7_ERROR_SUM_BH_CDT_TO		0x0008000000000000
#define		PO7_ERROR_SUM_BH_CLK_HDR	0x0010000000000000
#define		PO7_ERROR_SUM_BH_DBE_HDR	0x0020000000000000
#define		PO7_ERROR_SUM_BH_GBG_HDR	0x0040000000000000
#define		PO7_ERROR_SUM_BH_BAD_CMD	0x0080000000000000
#define		PO7_ERROR_SUM_HLT_INT		0x0100000000000000
#define		PO7_ERROR_SUM_HP_INT		0x0200000000000000
#define		PO7_ERROR_SUM_CRD_INT		0x0400000000000000
#define		PO7_ERROR_SUM_STV_INT		0x0800000000000000
#define		PO7_ERROR_SUM_HRD_INT		0x1000000000000000
#define		PO7_ERROR_SUM_BH_SUM		0x2000000000000000
#define		PO7_ERROR_SUM_ERR_LST		0x4000000000000000
#define		PO7_ERROR_SUM_ERR_VLD		0x8000000000000000

#define         PO7_ERR_SUM_UNUN_ERR_MASK       0x60F8F00000000000
#define         PO7_ERR_SUM_UNRE_ERR_MASK       0x9F000FFC00000000

#define MV_IOA_PO7_BHOLE_MSK		0x302040
/* Bit definitions for PO7_BHOLE_MSK */
#define		PO7_BHOLE_MSK_ALL_MSKBITS	0x00f8000000000000
#define MV_IOA_PO7_HEI_MSK		0x302080
/* Bit definitions for PO7_HEI_MSK */
#define		PO7_HEI_MSK_ALL_MSKBITS		0x0000fffd00000000
#define MV_IOA_PO7_CRD_MSK		0x3020c0
/* Bit definitions for PO7_CRD_MSK */
#define		PO7_CRD_MSK_ALL_MSKBITS		0x0000fffd00000000
#define MV_IOA_PO7_UNCRR_SYM		0x302100
#define MV_IOA_PO7_CRRCT_SYM		0x302140
#define MV_IOA_PO7_ERR_PKT0		0x302180
#define MV_IOA_PO7_ERR_PKT1		0x3021c0
#define MV_IOA_PO7_UGBGE_SYM		0x302200

/*
 * IO7 - Interrupt Control, Status, and Diagnostic Registers
 */
#define MV_IOA_INTR_ENABLE		0x1000000	/* all IE CSRs bit 24 */
#define MV_IOA_TARGET_CPU_SHIFT		14
#define MV_IOA_TARGET_CPU_MASK		(0x1ff << MV_IOA_TARGET_CPU_SHIFT)
#define MV_IOA_TARGET_TPU_SHIFT		9
#define MV_IOA_TARGET_TPU_MASK		(0xf << MV_IOA_TARGET_TPU_SHIFT)
#define MV_IOA_RBOX_IREQ_MASK		0x1f
#define MV_IOA_NUM_MSI_CTL		16
#define MV_IOA_ICSR_INDEX_SHIFT		6

#define MV_IOA_LSI_CTL_BASE		0x310000	/* LSI_CTL[000] */
#define MV_IOA_LSI_CTL_END		0x311fc0	/* LSI_CTL[127] */
							/* 0x312000 rsvd */
							/* 0x313e80      */
#define MV_IOA_HLT_CTL			0x313ec0
#define MV_IOA_HPI_CTL			0x313f00
#define MV_IOA_CRD_CTL			0x313f40
#define MV_IOA_STV_CTL			0x313f80
#define MV_IOA_HEI_CTL			0x313fc0
#define MV_IOA_MSI_CTL_BASE		0x314000	/* MSI_CTL[0] */
#define MV_IOA_MSI_CTL_END		0x3143c0	/* MSI_CTL[15] */
							/* 0x314400 rsvd */
							/* 0x317fc0      */
#define MV_IOA_INT_PND0			0x318000
#define MV_IOA_INT_CLR0			0x318040
#define MV_IOA_INT_EOI0			0x318080
							/* 0x3180c0 rsvd */
							/* 0x3187c0      */
#define MV_IOA_INT_PND1			0x318800
#define MV_IOA_INT_CLR1			0x318840
#define MV_IOA_INT_EOI1			0x318880
							/* 0x3188c0 rsvd */
							/* 0x318fc0      */
#define MV_IOA_INT_PND2			0x319000
#define MV_IOA_INT_CLR2			0x319040
#define MV_IOA_INT_EOI2			0x319080
							/* 0x3190c0 rsvd */
							/* 0x3197c0      */
#define MV_IOA_INT_PND3			0x319800
#define MV_IOA_INT_CLR3			0x319840
#define MV_IOA_INT_EOI3			0x319880
							/* 0x3198c0 rsvd */
							/* 0x31b7c0      */
#define MV_IOA_MISC_PND			0x31b800
#define MV_IOA_MISC_CLR			0x31b840
							/* 0x31b8c0 rsvd */
							/* 0x31bfc0      */
#define MV_IOA_MSI_PND_BASE		0x31c000	/* MSI_PND[15] */
#define MV_IOA_MSI_PND_END		0x31c3c0	/* MSI_PND[00] */
							/* 0x31c400 rsvd */
							/* 0x31c7c0      */
#define MV_IOA_MSI_CLR_BASE		0x31c800	/* MSI_CLR[15] */
#define MV_IOA_MSI_CLR_END		0x31cbc0	/* MSI_CLR[00] */

/*
 * IO7 - PCI/AGP Port Control and Status Registers (ports 0 - 3)
 */
#define MV_IOA_POx_CTRL			0x0000
/* Bit Definitions for MV_IOA_POx_CTRL */
#       define POx_CTRL_CACHE_LINE_LEN  0x00000000000000ff
#       define POx_CTRL_DIS_64BIT_BUS   0x0000000000000100
#       define POx_CTRL_DIS_ACK64       0x0000000000000200
#       define POx_CTRL_DIS_REQ64       0x0000000000000400
#       define POx_CTRL_EN_IO7_PARK     0x0000000000008000
#       define POx_CTRL_Spl_Cmp_MSG     0x00000000000f0000
#       define POx_CTRL_DIS_MSTR_LT     0x0000000000100000
#       define POx_CTRL_EN_PCHK         0x0000000000200000
#       define POx_CTRL_EN_TLB_CACHE    0x0000000000800000
#       define POx_CTRL_EN_ASSERT_SERR  0x0000000004000000
#       define POx_CTRL_RETRY_CMD_CHK   0x0000000008000000
#       define POx_CTRL_RM_TYPE         0x0000000030000000
#       define POx_CTRL_DIS_FUNC_ALIAS  0x0000000040000000
#       define POx_CTRL_EN_AGP_RD_CACHE 0x0000000080000000
#       define POx_CTRL_EN_PREFETCH     0x0000000100000000
#       define POx_CTRL_EN_DMA_TO       0x0000000200000000
#       define POx_CTRL_DISABLE_UPE     0x0000000400000000
#       define POx_CTRL_PCI_ARB_MODE    0x0000001800000000
#       define POx_CTRL_EN_PCI_RD_CACHE 0x0000002000000000
#       define POx_CTRL_UPE_PCI_22_MODE 0x0000004000000000
#       define POx_CTRL_UPE_ENG_EN_MASK 0x0007ff8000000000
#       define POx_CTRL_ENA_AGP_ORDER   0x0008000000000000
#       define POx_CTRL_UPE_PPRWR_RX    0x0010000000000000
#       define POx_CTRL_HPCE_ENA        0x0020000000000000
#       define POx_CTRL_AGP_MW          0x2000000000000000
#       define POx_CTRL_AGP_RD_CONCAT   0x4000000000000000
#       define POx_CTRL_AGP_WR_CONCAT   0x8000000000000000
#define MV_IOA_POx_CACHE_CTL		0x0040
/* Bit definitions for POx_CACHE_CTL */
#	define	POx_CACHE_CTL_UPE_CACHE_VLD	0x02
#	define	POx_CACHE_CTL_PCI_RESET_L	0x08
#define MV_IOA_POx_TIMER		0x0080
#	define POx_TIMER_DEFAULT		0x3300
#define MV_IOA_POx_IO_ADR_EXT		0x00c0
#define MV_IOA_POx_MEM_ADR_EXT		0x0100
#define MV_IOA_POx_XCAL_CTRL		0x0140
						/* 0x0180 - 0x01c0 rsvd */
#define MV_IOA_POx_DM_SOURCE		0x0200
#define MV_IOA_POx_DM_DEST		0x0240
#define MV_IOA_POx_DM_SIZE		0x0280
#define MV_IOA_POx_DM_CTRL		0x02c0
						/* 0x0300 - 0x03c0 rsvd */
#define MV_IOA_PO3_AGP_CAP_ID		0x0400
#define MV_IOA_PO3_AGP_STAT		0x0440
#define MV_IOA_PO3_AGP_CMD		0x0480
						/* 0x04c0 rsvd */
#define MV_IOA_POx_MONCTL		0x0500
#define MV_IOA_POx_CTRA			0x0540
#define MV_IOA_POx_CTRB			0x0580
#define MV_IOA_POx_CTR56		0x05c0
#define MV_IOA_POx_SCRATCH		0x0600
#define MV_IOA_POx_XTRA_A		0x0640
#define MV_IOA_POx_XTRA_TS		0x0680
#define MV_IOA_POx_XTRA_Z		0x06c0
						/* 0x0700 - 0x0fc0 rsvd */
#define MV_IOA_POx_WBASE0		0x1000
#define MV_IOA_POx_WBASE1		0x1040
#define MV_IOA_POx_WBASE2		0x1080
#define MV_IOA_POx_WBASE3		0x10c0
#define MV_IOA_POx_WMASK0		0x1100
#define MV_IOA_POx_WMASK1		0x1140
#define MV_IOA_POx_WMASK2		0x1180
#define MV_IOA_POx_WMASK3		0x11c0
#define MV_IOA_POx_TBASE0		0x1200
#define MV_IOA_POx_TBASE1		0x1240
#define MV_IOA_POx_TBASE2		0x1280
#define MV_IOA_POx_TBASE3		0x12c0
#define MV_IOA_POx_SG_TBIA		0x1300
#define MV_IOA_POx_MSI_WBASE		0x1340
#	define POx_MSI_WBASE_DEFAULT		0x7ff00001L
#	define POx_MSI_WBASE_ENABLE		0x1
						/* 0x1380 - 0x1fc0 rsvd */
#define MV_IOA_POx_ERR_SUM		0x2000
/* Bit definitions for POx_ERR_SUM */
#define		POx_ERR_SUM_ALL_ERRBITS		0x2ff8000015fffff0
#define POX_ERR_SUM_UNUN_ERR_MASK 0x02C40000000426F0
#define POX_ERR_SUM_UNRE_ERR_MASK 0xFD58000000025900
#define MV_IOA_POx_FIRST_ERR		0x2040
#define MV_IOA_POx_MSK_HEI		0x2080
/* Bit definitions for POx_MSK_HEI */
#define		POx_MSK_HEI_DLY_RD_TO_IRQ_DISABLE	(1L << 62)
#define		POx_MSK_HEI_ALL_MSKBITS			0x2ff0000015fffff0
#define		POx_MSK_HEI_NOAGP_MSKBITS		0x0ff8000000001800
#define MV_IOA_POx_TLB_ERR		0x20c0
/* Bit definitions for POx_TLB_ERR */
#define		POx_TLB_ERR_ALL_ERRBITS		0x8000ffffffffffff
#define MV_IOA_POx_SPL_COMPLT		0x2100
#define MV_IOA_POx_TRANS_SUM		0x2140
#define MV_IOA_POx_FRC_PCI_ERR		0x2180
#define MV_IOA_POx_MULT_ERR		0x21c0
						/* 0x2200 - 0x23c0 rsvd */
#define MV_IOA_POx_EOI_DAT		0x2400
						/* 0x2440 - 0x25c0 rsvd */
#define MV_IOA_POx_IACK_SPECIAL		0x2600
						/* 0x2640 - 0x3fc0 rsvd */
#define MV_IOA_POx_HP_MISC		0x4000
#define MV_IOA_POx_HP_LED		0x4040
#define MV_IOA_POx_HP_INTR_IN		0x4080
#define MV_IOA_POx_HP_DEV_CAP		0x4100
#define MV_IOA_POx_HP_EVNT_ENB_MSK	0x40c0
						/* 0x4140 rsvd */
#define MV_IOA_POx_HP_PWR		0x4180
#define MV_IOA_POx_HP_CNTL		0x41c0
#define MV_IOA_POx_HP_EVNT		0x4200

#ifdef KERNEL

/*
 * Defines for EV7 IPR and IO7 CSR write/read routines.
 */
#define MV_CPU_IPR_PORTID	0x0
#define MV_IOA_PCIX0_PORTID	0x0
#define MV_IOA_PCIX1_PORTID	0x1
#define MV_IOA_PCIX2_PORTID	0x2
#define MV_IOA_PCIX3_PORTID	0x3
#define MV_IOA_AGP3_PORTID	0x3
#define MV_IOA_CSR_PORTID	0x7
#define MV_CPU_IPR_BASE		0x00000000ffc00000
#define MV_IOA_CSR_BASE		0x00000000ff800000

/* Defined here for referrence only. Real defines in mvpci.h.
 */
#if 0
#define MV_IOA_PCI_IO_BASE	0x00000000ff000000
#define MV_IOA_PCI_CONFIG_BASE	0x00000000fe000000
#define MV_IOA_PCI_MEM_BASE	0x0000000000000000
#endif

/*
 * For IO7 on EV7:
 *	bit 43 is the IO vs memory bit (must be set for IO).
 */
#define	EV7_IO_BIT	0x080000000000

/*
 * L2 (Bcache) cache size in K-bytes
 */
#define EV7_L2_CACHE_SIZE       1792            /* 1.75 MB */


/*
 * MSI Control Register Definitions
 */
#define MV_MSI_CTL_15 0x3143c0
#define MV_MSI_CTL_14 0x314380
#define MV_MSI_CTL_13 0x314340
#define MV_MSI_CTL_12 0x314300
#define MV_MSI_CTL_11 0x3142c0


/*
 * MSI Pending Register Definitions
 */
#define MV_MSI_PND_15 0x31c3c0
#define MV_MSI_PND_14 0x31c380
#define MV_MSI_PND_13 0x31c340
#define MV_MSI_PND_12 0x31c300
#define MV_MSI_PND_11 0x31c2c0


/* Difference betwee MSI_CTL_x 
 * and MSI_PND_x
 */
#define MV_MSI_CTL_TO_PND 0x8000

/*
 * Size of an MSI control register
 */
#define MV_MSI_CTL_REG_SIZE 0x40


/*
 * MSI control register defintions
 */
#define MV_MSI_CTL_PEND_MASK       0xffffffff00000000
#define MV_MSI_CTL_CPU_MASK        0x00000000007fc000
#define MV_MSI_CTL_CPU_SHIFT       14
#define MV_MSI_CTL_ENABLED_MASK    0x0000000001000000

/* 
 * PCI_CTL register definitions
 */
#define MV_ENA_AGP_ORDER   0x0008000000000000
#define MV_EN_PCI_RD_CACHE 0x0000002000000000
#define MV_EN_AGP_RD_CACHE 0x0000000080000000


/* 
 * Data Mover definitions 
 */
#define MV_DM_PCI_WIN_MASK         0x0003000000000000
#define MV_DM_PCI_WIN_SHIFT        48

#define MV_DM_PCI_SG_WIN           1UL
#define MV_DM_PCI_MONSTER_WIN      2UL

#define MV_DM_SIZE_MASK            0x00000001ffffffc0
#define MV_DM_SIZE_SHIFT           6 

#define MV_DM_CTL_START_MASK       0x0000000000000001
#define MV_DM_CTL_STOP_MASK        0x0000000000000004
#define MV_DM_CTL_STOP_SHIFT       2

#define MV_DM_CTL_DISABLE_MASK     0x0000000000000002 /* Set if DM is disabled */ 
#define MV_DM_CTL_DM_MSG_NUM_MASK  0x0000000000001f00
#define MV_DM_CTL_DM_MSG_NUM_SHIFT 8
#define MV_DM_CTL_DM_MSG_REG_MASK  0x000000000001e000
#define MV_DM_CTL_DM_MSG_REG_SHIFT 13
#define MV_DM_CTL_INTR_MASK        0x0200000000000000 /* Set if intr enabled on completion */
#define MV_DM_CTL_INTRERR_MASK     0x0100000000000000 /* Set if intr enabled on DM error */
#define MV_DM_CTL_DONE_MASK        0x8000000000000000 /* 1=idle, 0=busy */

#define MV_DM_CTL_ERROR_MASK       0x4000000000000000
#define MV_DM_CTL_TLBERR_MASK      0x0400000000000000 
#define MV_DM_CTL_MABERR_MASK      0x0800000000000000 
#define MV_DM_CTL_FILLERR_MASK     0x1000000000000000 
#define MV_DM_CTL_2XERR_MASK       0x2000000000000000 

/*
 * I/O Error Summary definitions (POx_ERR_SUM register)
 */
/* reserved 3:0                         0x000000000000000f */
#define POx_ERR_SUM_AGP_REQQ_OVFL       0x0000000000000010
#define POx_ERR_SUM_AGP_SYNC_ERR        0x0000000000000020
#define POx_ERR_SUM_MRETRY_TO           0x0000000000000040
#define POx_ERR_SUM_PCIX_UX_SPL         0x0000000000000080
#define POx_ERR_SUM_PCIX_SPLIT_TO       0x0000000000000100
#define POx_ERR_SUM_PCIX_DISCARD_SPL    0x0000000000000200
#define POx_ERR_SUM_DMA_RD_TO           0x0000000000000400
#define POx_ERR_SUM_CSR_NXM_RD          0x0000000000000800
#define POx_ERR_SUM_CSR_NXM_WR          0x0000000000001000
#define POx_ERR_SUM_DMA_TO              0x0000000000002000
#define POx_ERR_SUM_P2cfg_all_maborts   0x0000000000004000
#define POx_ERR_SUM_P2cfg_mabort        0x0000000000008000
#define POx_ERR_SUM_P2cfg_pt_tabort     0x0000000000010000
#define POx_ERR_SUM_P2cfg_pm_tabort     0x0000000000020000
#define POx_ERR_SUM_P2cfg_serr          0x0000000000040000
#define POx_ERR_SUM_P2cfg_addrerr_stb   0x0000000000080000
#define POx_ERR_SUM_DETECTED_SERR       0x0000000000100000
#define POx_ERR_SUM_P2cfg_perr          0x0000000000200000
#define POx_ERR_SUM_P2cfg_dataerr_stb_niow 0x0000000000400000
#define POx_ERR_SUM_DETECTED_PERR       0x0000000000800000
#define POx_ERR_SUM_P2cfg_pm_perr       0x0000000001000000
/* reserved 25                          0x0000000002000000 */
#define POx_ERR_SUM_p2cfg_pt_scerror    0x0000000004000000
/* reserved 27                          0x0000000008000000 */
#define POx_ERR_SUM_HUNG_BUS            0x0000000010000000
/* reserved 50:29                       0x0007ffffe0000000 */
#define POx_ERR_SUM_UPE_MSI_WD          0x0008000000000000
#define POx_ERR_SUM_UPE_MSI_RD          0x0010000000000000
#define POx_ERR_SUM_UPE_TLB_WR          0x0020000000000000
#define POx_ERR_SUM_UPE_TLB_RD          0x0040000000000000
#define POx_ERR_SUM_UPE_DMA_WR          0x0080000000000000
#define POx_ERR_SUM_UPE_DMA_RD          0x0100000000000000
#define POx_ERR_SUM_UPE_PPR_WR          0x0200000000000000
#define POx_ERR_SUM_UPE_PPR_RD          0x0400000000000000
#define POx_ERR_SUM_TLB_Err             0x0800000000000000
/* reserved 60                          0x1000000000000000 */
#define POx_ERR_SUM_Prefetch            0x2000000000000000
#define POx_ERR_SUM_PCI_FILL_VLD_DEL_RD_TO 0x4000000000000000
#define POx_ERR_SUM_ERR_VALID           0x8000000000000000

#define POx_ERR_SUM_SERR_MASK   (POx_ERR_SUM_P2cfg_serr |        \
                                 POx_ERR_SUM_P2cfg_addrerr_stb | \
                                 POx_ERR_SUM_DETECTED_SERR)
#define POx_ERR_SUM_PERR_MASK   (POx_ERR_SUM_P2cfg_perr | \
                                 POx_ERR_SUM_P2cfg_dataerr_stb_niow | \
                                 POx_ERR_SUM_DETECTED_PERR | \
                                 POx_ERR_SUM_P2cfg_pm_perr)
#define POx_ERR_SUM_UPE_MASK    (POx_ERR_SUM_UPE_MSI_WD |       \
                                 POx_ERR_SUM_UPE_MSI_RD |       \
                                 POx_ERR_SUM_UPE_TLB_WR |       \
                                 POx_ERR_SUM_UPE_TLB_RD |       \
                                 POx_ERR_SUM_UPE_DMA_WR |       \
                                 POx_ERR_SUM_UPE_DMA_RD |       \
                                 POx_ERR_SUM_UPE_PPR_WR |       \
                                 POx_ERR_SUM_UPE_PPR_RD)


/*
 * Function prototypes for marvel_soc.c-sourced functions.
 */
/* CSR access routines */
u_long mv_ioa_io_base(u_long soc, u_long port);
u_long mv_read_cpu_ipr(u_long soc, u_long offset);
u_long mv_read_ioa_csr(u_long soc, u_long offset);
u_long mv_read_ioa_port_csr(u_long sco, u_int port, u_long offset);

void mv_write_cpu_ipr(u_long soc, u_long offset, u_long data);
void mv_write_ioa_csr(u_long soc, u_long offset, u_long data);
void mv_write_ioa_port_csr(u_long soc, u_int port, u_long offset, u_long data);


/*
 * DMA window sizing alg.
 */
extern	void mvsoc_choose_dma_windows();


/*
 * Marvel bus configuration related defines & structures
 */
#define CONFIG_SUCCESS 1
#define CONFIG_FAILURE 0

/*
 * MVSOC Bus info structure -- used in busconfl()
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
#define MV_COMP_NAME_MAX 12

struct mvsoc_bus_info {
					/* 1st 64-byte cache block */
    struct common_bus_info *common_bus_info;	/* not used on Marvel */
    struct hal_rad	*hal_radp;		/* ptr to hal_rad struct */
    u_long		cfgtree_id;		/* soc's config tree node id */
    int			soc_present;		/* soc is present */
    int			soc_configured;		/* soc is configured */
    int			cpu_present_inited;	/* cpu found and initialized */
    int			cpu_present;		/* cpu present */
    int			mem_present;		/* set, but not used */
    int			ioa_present;		/* SOC has IO7 ASIC connected */
    int			ioa_pid;		/* PID of connected IO7 */
    char		name[MV_COMP_NAME_MAX];
    					/* 2nd 64-byte cache block */
    struct bus		*mvsoc_bus;		/* for bus registration */
    int			rev_bp;			/* Motherboard revision */
    int			typ_bp;			/* Motherboard type */
    int			num_bp;			/* Expansion box number */
    int			xbox_hose;		/* Hose number, if XBOX */
    int			typ_ioa;		/* IO ASIC type (IO7) */
    int			rev_ioa;		/* IO ASIC revision */
						/* intr's must be on primary */
    u_int		ioa_primary_mask[MV_MAX_PCI_PER_IOA];
						/* assigned intr's bitmask */
    u_int		ioa_lsi_intr_used[MV_MAX_PCI_PER_IOA];
    					/* 2 64-byte cache blocks */
    						/* intr counts per IO7 pid */
    u_short		ioa_intr_targets[MV_MAX_SOCS];
					/* Last (I hope) 64-byte cache block */
    u_short		ioa_msi_intr_used;	/* MSI intr assigned bitmask */
    u_short		inited;
    u_char		ioa_dm_port;		/* data mover in use bitmask */
    u_char		ioa_pci_reset;		/* PCI bus held reset bitmask */
    void		*hwc_handle;
    int			phys_id;
    u_int		mv_sys_var;             /* Marvel system variation */
    u_int		soc_pad4[10];
    cpuset_t		receive_cpuset;		/* set of IO7s this cpu is handling the interrupts for */
};


struct mvsbb_info {
    char	name[MV_COMP_NAME_MAX];
    u_long	cfgtree_id;
    void	*hwc_devhandle;
};


struct mvcpumod_info {
    char	name[MV_COMP_NAME_MAX];
    u_long	cfgtree_id;
    void	*hwc_devhandle;
};

/*
 * MV IOA Bus info structure -- used in busconfl()
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

/*
 * marvel_soc.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since marvel_cpu.h, marvel_soc.h, & marvel_pci.h may be included in
 *	 one .c file, their debug definitions must not collide.
 */

extern	u_int	mvsoc_developer_debug;

/* To remove/add all MVSOCDEBUG debug printfs */
#define __MVSOCDEBUG
/* Enable/disable IO7 CSR and EV7 IPR debug printfs */
/*#define	MVSOC_CSR_PRINT_DEBUG*/
extern u_long mvsoc_print_csr_rw;

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * mvsoc_developer_debug.
 */

#define MARVEL_MODULE(x)  char *fcn_name = "x"

/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	MVSOCD_INOUT	0x00000001	/* routine entry and exit 	*/
#define MVSOCD_NUMA	0x00000020	/* NUMA-related info		*/
#define MVSOCD_ERRCLR	0x00000100	/* print error bit clear diag msg's */
#define MVSOCD_SOCINFO	0x00001000	/* SOC config info		*/
#define MVSOCD_IOAINFO	0x00010000	/* IOA config info		*/
#define MVSOCD_PCIINFO	0x00100000	/* PCI config info		*/
#define MVSOCD_CSR	0x01000000	/* CSR access info		*/

/* MVSOC, MVSBB and MVCPUMOD externs */
extern REPLICATED long mv_routing_table_iprs[];
extern struct mvsoc_bus_info	* REPLICATED mvsoc_bus_info[];
extern struct mvcpumod_info	* REPLICATED mvcpumod_info[];
extern struct mvsbb_info	* REPLICATED mvsbb_info[];
extern int	mvcpumods_per_sbb;				/* 1 or 4 */

/* New, testing hw-support debug printfs				*/
#define MVSOCD_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _MVSOCinout;
extern char * _MVSOCnuma;
extern char * _MVSOCsocinfo;
extern char * _MVSOCioainfo;
extern char * _MVSOCpciinfo;
extern char * _MVSOCcsr;
extern char * _MVSOCnot_yet;


/*
 * printf expansion that MVSOCPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _MVSOCxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __MVSOCDEBUG
#   define _MVSOCD_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_INOUT )  {	\
	    /* VARARGS */			\
            printf (_MVSOCinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_NUMA )  {	\
	    /* VARARGS */			\
            printf (_MVSOCnuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_SOCINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_SOCINFO)  {	\
	    /* VARARGS */			\
            printf (_MVSOCsocinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_IOAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_IOAINFO)  {	\
	    /* VARARGS */			\
            printf (_MVSOCioainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_PCIINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_PCIINFO)  {	\
	    /* VARARGS */			\
            printf (_MVSOCpciinfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_CSR(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_CSR)  {	\
	    /* VARARGS */			\
            printf (_MVSOCcsr); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVSOCD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvsoc_developer_debug & MVSOCD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_MVSOCnotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * mvsoc_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * MVSOCD_INOUT | MVSOCD_CONFIG
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define MVSOCPRINTF(F, X)	_##F(X)

#else  /* !__MVSOCDEBUG */
#   define MVSOCPRINTF(F, X)
#endif /* __MVSOCDEBUG */

#endif	/* KERNEL */

/* 
 * Define high temperature operating threshold for 
 * environmental monitoring 
 */
#define MV_HIGH_TEMP_THRESHOLD 40

#endif	/* #ifndef ASSEMBLER */


#endif	/* __ARCH_ALPHA_HAL_MARVEL_SOC_H__ */

