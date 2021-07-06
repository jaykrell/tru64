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
 * @(#)$RCSfile: ev7_ocla.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2002/03/28 20:34:42 $
 */
#ifndef _EV7_OCLA_H_
#define _EV7_OCLA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * EV7 OCLA defines and structures.
 */


#ifdef _KERNEL
/* Do the pragma pack here to avoid padding since the reserved */
/* field straddles the 32-bit boundary inside the structure. */
#pragma environment save
#pragma pack 1
typedef struct ocla_ctl {
	unsigned int	aaddr:14;
	unsigned int	amatch:14;
	unsigned int	reserved:11;
	unsigned int	srel:1;
	unsigned int	wrap:1;
	unsigned int	eio:1;
	unsigned int	ts_force:1;
	unsigned int	ext_src:3;
	unsigned int	tag_src:3;
	unsigned int	tihang:1;
	unsigned int	irqt:1;
	unsigned int	irqf:1;
	unsigned int	tmode:2;
	unsigned int	sfilt:2;
	unsigned int	pdat_en:1;
	unsigned int	ts_en:1;
	unsigned int	tag_en:1;
	unsigned int	ifull:1;
	unsigned int	itrig:1;
	unsigned int	rdrst:1;
	unsigned int	run:1;
	unsigned int	enable:1;
} ocla_ctl_t;
#pragma environment restore
#endif

#define OCLA_ALL_CPUS	99999			/* Minor number for "all cpus" */

/* Definitions for IOCTLS and internal state */

/* IOCTL codes for each operation */
#define OCLA_FAMILY	'7'			/* name of OCLA family of ioctl codes */

#define OCLASTOP	_IO(OCLA_FAMILY, 1)	/* stop the OCLAs (if enabled and running ) */
#define OCLASTART	_IO(OCLA_FAMILY, 2)	/* start the OCLAs (if enabled and stopped) */
#define OCLARESET	_IO(OCLA_FAMILY, 3)	/* reset the OCLAs to entry 0 */
#define OCLADUMP	_IO(OCLA_FAMILY, 4)	/* stop/dump (really IP state transition only) */


/* Saved OCLA state structure; copies of control registers and saved scandump. */
/* As each CPU is brought online, space for one of these is allocated */

#define OCLA_NREGISTERS	16		/* max # of registers to save */
#define OCLA_NENTRIES	16384		/* max # of entries in a scandump */

typedef struct ocla_saved_register {
	unsigned long	address;	/* -1 if unused */
	unsigned long	value;		/* -1 if unused */
} ocla_saved_register;

typedef struct ocla_state {
	ocla_saved_register	registers[OCLA_NREGISTERS];	/* saved control register tuples */
	unsigned long		dump_storage[2][OCLA_NENTRIES];	/* saved scandump */
	unsigned long		panic_stop_count;		/* is_panic calls to ocla_stop */
	unsigned long		ipr_base;			/* base address for IPRs */
} ocla_state, *ocla_state_t;


#ifdef _KERNEL

/* If linked in, call the OCLA "stop" routine */
#define OCLA_STOP() \
	do { \
		if (ev7_oclastop) \
			(*ev7_oclastop)(FALSE); \
	} while (0)

/* If linked in, call the OCLA "stop" routine in is_panicing mode */
#define OCLA_PANIC_STOP() \
	do { \
		if (ev7_oclastop) \
			(*ev7_oclastop)(TRUE); \
	} while (0)

/* If linked in, call the OCLA "dump" routine */
#define OCLA_DUMP() \
	do { \
		if (ev7_ocladump) \
			(*ev7_ocladump)(); \
	} while (0)

/* If linked in, call the OCLA "xcpu" routine */
#define OCLA_XCPU() \
	do { \
		if (ev7_oclaxcpu) \
			(*ev7_oclaxcpu)(); \
	} while (0)

/* If EV7s are present and handling OCLA requests, these will get assigned */
/* pointers to the real OCLA management routines. Check for NULL before using */
/* (e.g. with above macros). */
/* These routines are to be called on the CPU that must be controlled (except dump). */
extern void (*ev7_oclastop)(int);
extern void (*ev7_ocladump)(void);
extern void (*ev7_oclaxcpu)(void);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _EV7_OCLA_H_ */
