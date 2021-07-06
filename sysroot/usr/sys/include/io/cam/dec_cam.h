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
 * @(#)$RCSfile: dec_cam.h,v $ $Revision: 1.1.53.1 $ (DEC) $Date: 2001/11/01 14:45:22 $
 */
#ifndef	_DEC_CAM_
#define	_DEC_CAM_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_KERNEL)
#include <vm/vm_map.h>
#endif /* defined(_KERNEL) */

/* ---------------------------------------------------------------------- */

/* dec_cam.h		Version	1.03			Dec. 11, 1991 */

/*  This file contains the definitions and data	structures needed by
    the	DEC CAM	source files.
*/

/* ---------------------------------------------------------------------- */

/*
 * Declare the CAM DDI level that this OS rev supports as its base.
 *   CAMDDI_VERSION_MAJOR    : Interface Compatibility Level
 *   CAMDDI_VERSION_MINOR    : Binary Compatibility Level
 *   CAMDDI_VERSION_REV      : Interface Revision Level
 */
#define CAMDDI_VERSION_MAJOR        5
#define CAMDDI_VERSION_MINOR        1
#define CAMDDI_VERSION_REV          1


/* maximum number of SCSI busses supported per system */
#define	MAX_CAM_SCSI_BUSSES	255

#define	OLD_MAX_BUSSES		64 /* Used for the allocation of */
				   /* the pdrv_unit_* arrays.    */

/* set macros for "Number of Devices Per SCSI bus" */
#define	NDPS_8			8
#define	NDPS_16			16
#define	NDPS			8
/* set macros for "Number of Luns Per Target" */
#define	NLPT_8			8
#define	NLPT			8

/* DON'T USE THESE ANY MORE!!! THEY ARE	NO LONGER VALID!!! */
#define	MAX_LUNS		7	/* Maximum LUN value		*/
#define	MAX_TARGETS		7	/* Maximum target id		*/

#define	DEFAULT_SCSIID		7	/* Default system scsi id	*/

#define	DEC_AUTO_SENSE_SIZE	164
#define	PD_SENSE_BUF_LEN	255	/* Driver Auto sense buffer copy reservation */

/*
 * Default command timeout value.
 */
#define	SIM_DEFAULT_TIMEOUT	30	/* Thirty seconds			*/

/*
 * Wait	loop count define for the CDrv during EDT probing.
 * NOTE:  This count is	the number of milliseconds to wait before determining
 * that	an abort or bus	reset is needed	to get the original INQUIRY CCB	back.
 */

#define	CCFG_WAIT_DELAY_LOOP	4000		/* loop	# for 4	seconds	*/

/* ---------------------------------------------------------------------- */

/* Defines for the CAM cam_vu_flags field in the SCSIIO_CCB. */

#define	DEC_CAM_HIGH_PRIOR	0xc000		/* This	CCB will be given
						 * high	priority by the	SIM.
						 */
#define	DEC_CAM_MED_PRIOR	0x8000		/* This	CCB will be given
						 * medium priority by the SIM.
						 */
#define DEC_CAM_LOW_PRIOR_EXP	14		/* This CCB will be given   */
						/* low priority by the SIM. */
#define DEC_CAM_LOW_PRIOR (1 << DEC_CAM_LOW_PRIOR_EXP)	/* = 0x4000	    */ 

#define	DEC_CAM_ZERO_PRIOR	0x0000		/* This	CCB will not be
						 * assigned a priority.
						 */
#define	DEC_CAM_PRIORITY_MASK	0xc000		/* Bits	of cam_vu_flags
						 * which are used by the SIM
						 * to specify a	priority level.
						 */

/*
 * DEC specific	macros
 */
#ifdef __digital__
#define	CAM_IS_KUSEG(addr)	(!IS_SYS_VA((vm_offset_t)(addr)))
#define	CAM_PHYS_TO_KVA(addr)	(PHYS_TO_KSEG((unsigned	long)addr))
#endif /* __digital__ */

#ifdef __mips
#define	CAM_IS_KUSEG(addr)	(IS_KUSEG((addr)))
#define	CAM_PHYS_TO_KVA(addr)	(PHYS_TO_K1(addr))
#endif /* __mips */

#ifdef __intel__
#define	CAM_IS_KUSEG(addr)	(!IS_SYS_VA((vm_offset_t)(addr)))
#define	CAM_PHYS_TO_KVA(addr)	(phystokv(addr))
#endif /* __intel__ */

#if defined(B_HWRELOC)
#define	CAM_IS_HWRELOC_SET(flags) ((flags) & B_HWRELOC)
#else
#define	CAM_IS_HWRELOC_SET(flags) (0)
#endif /* B_HWRELOC */

/*
 * VM memory page lock down for	IO
 */
#define	CAM_VM_USERACC(addr, len, prot )				\
	(vm_map_check_protection( current_task()->map,			\
		trunc_page((addr)), round_page((addr)+(len)),		\
		prot ==	B_READ ? VM_PROT_READ :	VM_PROT_WRITE))		\

#define	CAM_VM_LOCK( addr, len )					\
	vm_map_pageable(current_task()->map, trunc_page((addr)),	\
		  round_page((addr)+(len)), VM_PROT_READ|VM_PROT_WRITE)


#define	CAM_VM_UNLOCK( addr, len, prot )				\
	vm_map_pageable(current_task()->map, trunc_page((addr)),	\
		  round_page((addr)+(len)), VM_PROT_NONE)


/*
 * CAM locking macros.
 */

#define	CAM_SLEEP(chan,	pri, lk) \
    mpsleep(chan, pri, "Zzzzzz", 0, (void *)0, 0) 

#define	CAM_SLEEP_SPINUNLOCK(chan, pri,	lk)  \
    mpsleep(chan, pri, "Zzzzzz", 0, (void *)lk,	(MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE)) 

/* SPIN	LOCKS (SIMPLE) */
#define	CAM_SPINLOCK(lk) usimple_lock(lk)
#define	CAM_SPINUNLOCK(lk) usimple_unlock(lk)

/* PRE SMP LOCK	DEFINITION PLACE HOLDERS */
#define	CAM_LOCK_IT(lk,	flags)
#define	CAM_UNLOCK_IT(lk)
#define	CAM_SLEEP_UNLOCK_IT(chan, pri, lk) \
    mpsleep(chan, pri, "Zzzzzz", 0, (void *)0, 0)

#ifdef __cplusplus
}
#endif
#endif /* _DEC_CAM_ */
