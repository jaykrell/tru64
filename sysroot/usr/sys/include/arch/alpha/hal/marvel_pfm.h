/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: marvel_pfm.h,v $
 * Revision 1.1.2.2  2002/01/02  18:46:48  Andrew_Duane
 * 	Remove read/write IPR and CSR functions; moved to hal_sysinfo.
 *
 * Revision 1.1.2.1  2001/12/05  20:19:12  Andrew_Duane
 * 	Fix the #pragma around POx_MONCTL, breaks the C++ compiler.
 * 	[2001/11/02  17:41:59  Andrew_Duane]
 *
 * 	Initial version of the MARVEL (EV7) PFM driver defines and structures.
 * 	[2001/10/26  13:52:08  Andrew_Duane]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: marvel_pfm.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2002/01/02 18:46:48 $
 */
#ifndef _MARVEL_PFM_H_
#define _MARVEL_PFM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/cpuset.h>

/*
 * Marvel/EV7/IO7 performace counter defines and structures.
 *
 * There are several sets of performance counters in the EV7:
 *
 * 1) CBOX (Core Chip); related to the OCLA
 * 2) ZBOX (Memory Controller); counts memory request operations
 * 3) RBOX (Router); counts multiples of 256 operations
 * 4) IO7; counts operations on the 5 IO7 ports
 * 5) PCC; not a performance counter, but the SRM-defined cycle counter.
 *    It is not programmable, but is read with an unsigned long.
 */



/*
 * IO7 performance counters: Marvel/EV7 System Programmers Manual, section 4.11
 *
 * There is 1 input quadword: POx_MONCTL, contains all programming
 * There are 3 output quadwords: POx_CTRA, POx_CTRB, POx_CTR56
 * Each of these (1 in, 3 out) are repeated for each port: 0, 1, 2, 3, and 7:
 * a set of 5 POx_MONCTL_t's gets written, a set of 5 POx_CTRS_t's gets read.
 *
 * NOTE: the match, pmode, and cntrl_* fields are pass 2 only
 */
/* Do the pragma pack here to avoid padding POx_MONCTL since the match field straddles */
/* the 32-bit boundary inside the structure. Without it, the size goes to 16 bytes. */
#pragma environment save
#pragma pack 1
typedef struct POx_MONCTL {
	unsigned int	selta:8;	/* Select for CTRA <7:0> RW */
	unsigned int	seltb:8;	/* Select for CTRB <15:8> RW */
	unsigned int	seltc:8;	/* Select for CTRC <23:16> RW */
	unsigned int	pulsea:1;	/* PULSE for CTRA <24> RW */
	unsigned int	pulseb:1;	/* PULSE for CTRB <25> RW */
	unsigned int	match:12;	/* match against UPE when SELTx == 41 */
	unsigned int	pmode:1;	/* enable use of PMASK register */
	unsigned int	reserved1:1;	/* RESERVED: RAZ */
	unsigned int	cntrl_pin:1;	/* enable external input pin for control */
	unsigned int	cntrl_stop_clr:1; /* enable external input pin for stop/clear */
	unsigned int	cntrl_a:1;	/* enable external input pin for POx_CTRa */
	unsigned int	cntrl_b:1;	/* enable external input pin for POx_CTRb */
	unsigned long	reserved2:20;	/* RESERVED: RAZ */
} POx_MONCTL_t;
#pragma environment restore

/*
 * Counters A, B, and 56 can just be read as quadwords; there are only
 * 56 bits of actual data, but the rest are RAZ, so it is safe.
 * This saves a lot of bit-masking operations in reads and writes.
 */
/* OK to use these as outgoing values from mpfmread */
typedef unsigned long POx_CTRA_t;	/* typedef it anyway */
typedef unsigned long POx_CTRB_t;	/* typedef it anyway */
typedef unsigned long POx_CTR56_t;	/* typedef it anyway */
typedef struct POx_CTRS {
	POx_CTRA_t countera;		/* POx_CTRA  <55:0> RW (+reserved <63:56> RAZ) */
	POx_CTRB_t counterb;		/* POx_CTRB  <55:0> RW (+reserved <63:56> RAZ) */
	POx_CTR56_t counter56;		/* POx_CTR56 <55:0> RW (+reserved <63:56> RAZ) */
} POx_CTRS_t;

/* Order of ports */
#define IO7_PORT0	0
#define IO7_PORT1	1
#define IO7_PORT2	2
#define IO7_PORT3	3
#define IO7_PORT7	4
#define IO7_NPORTS	5		/* 5 sets of counters */

typedef POx_CTRS_t IO7_COUNTER_t[IO7_NPORTS];	/* Outgoing counters: 5 sets of 3 unsigned longs */

/*
 * ZBOX performance counters: EV7 System Design Spec sections 17.2.18-20
 * There are two perf counters and one control register for each memory
 * controller (ZBOX0 and ZBOX1) making 4 perf counters and 2 control
 * registers total per EV7. Each register is 32 bits.
 */

/* ZBOX Performance Control registeres: one for each ZBOX */
typedef struct ZBOX_ZPM_CTL {
	unsigned int	ctl0:5;		/* ZPM_CTL0<4:0> RW */
	unsigned int	ctl1:4;		/* ZPM_CTL1<3:0> RW */
	unsigned int	unused1:3;	/* unused<11:9> RW */
	unsigned int	unused2:20;	/* unused<31:12> RO,0 */
} ZBOX_ZPM_CTL_t;


/* ZBOX Performance Counter registers: two for each ZBOX */
/* Outgoing values from mpfmread: unsigned long */
typedef struct ZBOX_ZPM_CTR {
	int		ctr:31;		/* ZBOX_PERF_CTR<30:0> R*W (make this signed) */
	unsigned int	underflow:1;	/* ZBOX_PERF_CTR_UND<31> R*W */
} ZBOX_ZPM_CTR_t;

#define ZBOX0_CTR0	0
#define ZBOX0_CTR1	1
#define ZBOX1_CTR0	2
#define ZBOX1_CTR1	3
#define ZBOX_NPORTS	4

typedef unsigned long ZBOX_COUNTER_t[ZBOX_NPORTS];	/* Outgoing counters: 4 unsigned longs */


/*
 * RBOX performance counters: EV7 System Design Spec sections 17.3.6,11
 * There are two sets of RBOX perf counters: one for each port (N/S/E/W)
 * and one for the I/O port.
 * The values in pcv are actually multiples of 256 (lower 8 bits not visible)
 * NOTE: the programming and counters are in the same registers!
 */

/* RBOX Port Performance Counter: one for each port */
/* Outgoing values from mpfmread: unsigned long */
typedef struct RBOX_x_PERF {
	unsigned int	pcc:2;		/* counter control <1:0> RW */
	unsigned int	unused1:2;	/* unused <3:2> RW */
	unsigned int	pcv:24;		/* counter value <27:4> RW */
	unsigned int	unused2:4;	/* unused <31:28> RW */
} RBOX_x_PERF_t;

/* RBOX IO Port Performance Counter: same as above */
typedef RBOX_x_PERF_t RBOX_IO_PERF_t;

/* Order of NSEW ports */
#define RBOX_N		0
#define RBOX_S		1
#define RBOX_E		2
#define RBOX_W		3
#define RBOX_IO		4
#define RBOX_NPORTS	5

typedef unsigned long RBOX_COUNTER_t[5];	/* Outgoing counters: 5 unsigned longs */


/*
 * CBOX performance counters: EV7 System Design Spec sections 17.1.7-12
 * NOTE: The CBOX performance counters are also tied to the OCLA.
 * There are several registers that control the CBOX performance counters:
 *  CBOX_PERF_CTL  (17.1.7):  trigger selection, masking, mode (general control)
 *  CBOX_PERF_ADR  (17.1.8):  sets opcode and address bits to watch
 *  CBOX_PERF_STS  (17.1.9):  now integrated into CBOX_PERF_ADR
 *  CBOX_PERF_MAT  (17.1.10): match bits for CBOX_PERF_ADR
 *  CBOX_PERF_MATV (17.1.11): REMOVED
 *  CBOX_PERF_CNT  (17.1.12): the performance counter itself
 */

typedef struct CBOX_PRF_CTL {
	unsigned int	prf_mode:2;	/* Performance logic mode <1:0> RW,0 */
	unsigned int	trg_lat_sts:1;	/* Latch bitset 1 when trigger <2> RW,0 */
	unsigned int	trg_lat_adr:1;	/* Latch bitset 2 when trigger <3> RW,0 */
	unsigned int	req_pid_sel:2;	/* Select C_PRF_ADR<REQPID> contents <5:4> RW,0 */
	unsigned int	trg_sel_or:1;	/* Select final trigger (and/or) <6> RW,0 */
	unsigned int	trg_inv:6;	/* Invert which match conditions <12:7> RW,0 */
	unsigned int	trg_or:6;	/* Direct match conditions to and/or plane <18:13> RW,0 */
	unsigned int	vld_sel_or:1;	/* Select final valid condition (and/or) <19> RW,0 */
	unsigned int	vld_inv:6;	/* Invert which match conditions <25:20> RW,0 */
	unsigned int	vld_or:6;	/* Direct match conditions to and/or plane <31:26> RW,0 */
	unsigned int	pad;		/* fill up the other 32 bits */
} CBOX_PRF_CTL_t;

/* Do the pragma pack here to avoid padding CBOX_PRF_ADR_t since the pa1 field straddles */
/* the 32-bit boundary inside the structure. Without it, the size goes to 12 bytes. */
#pragma environment save
#pragma pack 1
typedef struct CBOX_PRF_ADR {
	unsigned int	opcode:8;	/* network opcode or CMAF rdtype <7:0> RW */
	unsigned int	misc:7;		/* misc status bits <14:8> RW */
	unsigned int	reqpid:11;	/* requestor PID <25:15> RW */
	unsigned int	valid_lookup:1;	/* request not aborted (or local) <26> RW */
	unsigned int	pa1:7;		/* PA12:6  (dcache index) <33:27> RW */
	unsigned int	pa2:5;		/* PA17:13 (bcache index) <38:34> RW */
	unsigned int	pa3:25;		/* PA42:18 (bcache tag)   <63:39> RW */
} CBOX_PRF_ADR_t;
#pragma environment restore

typedef CBOX_PRF_ADR_t CBOX_PRF_MAT_t;

typedef struct CBOX_PRF_CNT {
	unsigned int	unused;		/* bits 31:0 are unused RAZ */
	unsigned int	event_cnt;	/* event count <63:32> RW */
} CBOX_PRF_CNT_t;

typedef struct CBOX_PRF_INPUT {
	CBOX_PRF_CTL_t	ctl;
	CBOX_PRF_ADR_t	adr;
	CBOX_PRF_MAT_t	mat;
} CBOX_PRF_INPUT_t;			/* Input to CBOX perf counters */

typedef unsigned long CBOX_COUNTER_t;	/* Outgoing counter: unsigned long */

typedef struct PCC {
	unsigned int pcc_cnt;		/* low 32 bits: counter */
	unsigned int pcc_off;		/* high 32 bits: offset */
} PCC_t;

/* Send the PCC back as the real 64-bit structure */
typedef PCC_t PCC_COUNTER_t;

/* Definitions for IOCTLS and internal state */

/* IOCTL codes for each operation */
#define MPFM_FAMILY	'7'					/* name of MPFM family of ioctl codes */

#define MPFMSETCPUS	 _IOW(MPFM_FAMILY, 0, cpuset_t)		/* set which CPUs to collect; rewrites actual set, returns #cpus */
#define MPFMSETRADS	 _IOW(MPFM_FAMILY, 1, radset_t)		/* set which RADs to collect; rewrites actual set, returns #cpus */
#define MPFMSETCOUNTERS  _IOW(MPFM_FAMILY, 2, unsigned long)	/* select which counters (CBOX, RBOX, etc) to engage */
#define MPFMSETFLAGS	 _IOW(MPFM_FAMILY, 3, unsigned long)	/* set flags (MPFM_AUTOCLEAR, etc) */
#define MPFMDISABLE	 _IO(MPFM_FAMILY, 10)			/* disable the performance counters (Placeholder only) */
#define MPFMENABLE	 _IO(MPFM_FAMILY, 11)			/* enable the performance counters (Placeholder only) */
#define MPFMCLEAR	 _IO(MPFM_FAMILY, 12)			/* clear driver counters */

/* User-visible flags for MPFMSETFLAGS (mpfm_user_flags) */
#define MPFM_COMBINE	0x1		/* combine all CPUs/RADs into a single structure */
#define MPFM_AUTOCLEAR	0x2		/* clear counters on each read */
#define MPFM_FLAG_MASK	0x3

/* Internal-only flags for mpfm_flags (mpfm_flags) */
#define MPFMOPEN	0x1		/* the driver has been opened */


/* MPFMSETCOUNTERS selects which counters to use; OR'd together into mpfm_counters */
/* This controls the size and order of the data structures used for read/write */
#define MPFM_USE_CBOX	0x1
#define MPFM_USE_RBOX 	0x2
#define MPFM_USE_ZBOX	0x4
#define MPFM_USE_IO7	0x8
#define MPFM_USE_PCC	0x10
#define MPFM_USE_MASK	0x1F


/* Sizes required for read and write operations */
/* Write (programming) sizes */
#define MPFM_CBOX_WSIZE	(sizeof(CBOX_PRF_INPUT_t))
#define MPFM_RBOX_WSIZE	(sizeof(RBOX_IO_PERF_t) + 4 * sizeof(RBOX_x_PERF_t))
#define MPFM_ZBOX_WSIZE	(2 * sizeof(ZBOX_ZPM_CTL_t))
#define MPFM_IO7_WSIZE	(5 * sizeof(POx_MONCTL_t))
#define MPGM_PCC_WSIZE	(0)	/* PCC cannot be programmed */

/* Read (retrieving) sizes; usually just a set of ulongs */
#define MPFM_CBOX_RSIZE	(sizeof(CBOX_PRF_CNT_t))
#define MPFM_RBOX_RSIZE	(sizeof(RBOX_COUNTER_t))
#define MPFM_ZBOX_RSIZE	(sizeof(ZBOX_COUNTER_t))
#define MPFM_IO7_RSIZE	(sizeof(IO7_COUNTER_t))
#define MPFM_PCC_RSIZE	(sizeof(PCC_COUNTER_t))

#ifdef KERNEL
/* These are the real sizes needed by the hardware registers */
#define MPFM_CBOX_REG_RSIZE	(sizeof(CBOX_PRF_CNT_t))
#define MPFM_RBOX_REG_RSIZE	(sizeof(RBOX_IO_PERF_t) + 4 * sizeof(RBOX_x_PERF_t))
#define MPFM_ZBOX_REG_RSIZE	(4 * sizeof(ZBOX_ZPM_CTR_t))
#define MPFM_IO7_REG_RSIZE	(5 * sizeof(POx_CTRS_t))
#define MPFM_PCC_REG_RSIZE	(sizeof(PCC_t))
#endif


/* Some useful defines for computing sizes and offsets of the read/write buffers */
/* NOTE: Uses the global "mpfm_counters" to determine which counters to allocate */

/* The buffers are in this order, for each CPU: | IO7 | CBOX | RBOX | ZBOX | PCC | */
/* This allows each CPU to allocate its memory locally, and reduces cache conflicts */

/* Per-CPU read sizes, and offsets into each read buffer for each counter */
#define IRSIZE		((mpfm_counters & MPFM_USE_IO7) ? MPFM_IO7_RSIZE : 0)
#define IROFFSET	0
#define CRSIZE		((mpfm_counters & MPFM_USE_CBOX) ? MPFM_CBOX_RSIZE : 0)
#define CROFFSET	(IRSIZE)
#define RRSIZE		((mpfm_counters & MPFM_USE_RBOX) ? MPFM_RBOX_RSIZE : 0)
#define RROFFSET	(IRSIZE + CRSIZE)
#define ZRSIZE		((mpfm_counters & MPFM_USE_ZBOX) ? MPFM_ZBOX_RSIZE : 0)
#define ZROFFSET	(IRSIZE + CRSIZE + RRSIZE)
#define PRSIZE		((mpfm_counters & MPFM_USE_PCC) ? MPFM_PCC_RSIZE : 0)
#define PROFFSET	(IRSIZE + CRSIZE + RRSIZE + ZRSIZE)
#define RSIZE		(IRSIZE + CRSIZE + RRSIZE + ZRSIZE + PRSIZE)		/* Per CPU/RAD */
#ifdef KERNEL
#define IREGSIZE	((mpfm_counters & MPFM_USE_IO7) ? MPFM_IO7_REG_RSIZE : 0)
#define IREGOFFSET	0
#define CREGSIZE	((mpfm_counters & MPFM_USE_CBOX) ? MPFM_CBOX_REG_RSIZE : 0)
#define CREGOFFSET	(IREGSIZE)
#define RREGSIZE	((mpfm_counters & MPFM_USE_RBOX) ? MPFM_RBOX_REG_RSIZE : 0)
#define RREGOFFSET	(IREGSIZE + CREGSIZE)
#define ZREGSIZE	((mpfm_counters & MPFM_USE_ZBOX) ? MPFM_ZBOX_REG_RSIZE : 0)
#define ZREGOFFSET	(IREGSIZE + CREGSIZE + REGRSIZE)
#define PREGSIZE	((mpfm_counters & MPFM_USE_PCC) ? MPFM_PCC_REG_RSIZE : 0)
#define PREGOFFSET	(IREGSIZE + CREGSIZE + RREGSIZE + ZREGSIZE)
#define REGSIZE		(IREGSIZE + CREGSIZE + RREGSIZE + ZREGSIZE + PREGSIZE)	/* Per CPU/RAD */
#endif

/* For now, we are programming all CPUs the same, so there is only one write buffer */
/* The PCC is not programmable, even though we have defines. PSIZE == 0. */
#define IWSIZE		((mpfm_counters & MPFM_USE_IO7) ? MPFM_IO7_WSIZE : 0)
#define IWOFFSET	0
#define CWSIZE		((mpfm_counters & MPFM_USE_CBOX) ? MPFM_CBOX_WSIZE : 0)
#define CWOFFSET	(IWSIZE)
#define RWSIZE		((mpfm_counters & MPFM_USE_RBOX) ? MPFM_RBOX_WSIZE : 0)
#define RWOFFSET	(IWSIZE + CWSIZE)
#define ZWSIZE		((mpfm_counters & MPFM_USE_ZBOX) ? MPFM_ZBOX_WSIZE : 0)
#define ZWOFFSET	(IWSIZE + CWSIZE + RWSIZE)
#define PWSIZE		(0)
#define PWOFFSET	(IWSIZE + CWSIZE + RWSIZE + ZWSIZE)
#define WSIZE		(IWSIZE + CWSIZE + RWSIZE + ZWSIZE + PWSIZE)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MARVEL_PFM_H_ */
