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
 * @(#)$RCSfile: spl.h,v $ $Revision: 1.1.13.1 $ (DEC) $Date: 2000/09/22 14:27:32 $
 */

#ifndef	_MACHINE_SPL_H_
#define	_MACHINE_SPL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file defines the interrupt priority levels used by
 * machine-dependent code.
 */

/*
 * UNIX PAlcode has 8 levels 0..7
 *
 *	7	machine check
 *	6	realtime device interrupt
 *	5	clock and ip interrupts
 *	4	device level 1 interrupts
 *	3	device level 0 interrupts
 *	2	software level 1 interrupts
 *	1	software level 0 interrupts
 *	0	any interrupt
 */
#define SPLEXTREME	7
#define SPLDEVRT	6
#define SPLCLOCK	5
#define SPLHIGH		4
#define SPLSCHED	4
#define SPLDEVHIGH	4
#define SPLTTY		4
#define SPLIMP	   4 /* because of SLIP interface, splimp must be >= spltty */
#define SPLBIO		4
#define SPLMEMCHN       4
#define SPLDEVLOW	3
#define SPLNET		2		/* software (soft net) */
#define SPLSOFTC	1		/* software (soft clock) */
#define SPL1		1
#define SPLNONE		0		/* no interrupts blocked */

#ifndef ASSEMBLER

typedef int spl_t;

#ifdef _KERNEL

#define splpanic()	swap_ipl_nopatch(SPLEXTREME)

#define splextreme()	swap_ipl(SPLEXTREME)
#define spl7()		swap_ipl(SPLEXTREME)
#define spldevrt()	swap_ipl(SPLDEVRT)
#define spl6()		swap_ipl(SPLHIGH)
#define splhigh()	swap_ipl(SPLHIGH)
#define splsched()	swap_ipl(SPLSCHED)
#define splvm()		swap_ipl(SPLDEVHIGH)
#define splshootdown()	swap_ipl(SPLCLOCK)
#define splclock()	swap_ipl(SPLCLOCK)
#define	splsoftclock()	swap_ipl(SPLSOFTC)

#define spldevhigh()	swap_ipl(SPLDEVHIGH)
#define spl5()		swap_ipl(SPLDEVHIGH)
#define spltty()	swap_ipl(SPLTTY)
#define splimp()	swap_ipl(SPLIMP)
#define splbio()	swap_ipl(SPLBIO)
#define splmemchn()     swap_ipl(SPLMEMCHN)
#define spldevlow()	swap_ipl(SPLDEVLOW)
#define splnet()	swap_ipl(SPLNET)
#define splsoftc()	swap_ipl(SPLSOFTC)
#define spl1()		swap_ipl(SPL1)

#define spl0()		swap_ipl_preempt_check(SPLNONE)
#define splnone()	swap_ipl_preempt_check(SPLNONE)
#define splx(S)		swap_ipl_preempt_check(S)

#define spl0_nopreempt()  swap_ipl(SPLNONE)
#define splx_nopreempt(S) swap_ipl(S)

#ifdef _USE_KERNEL_PROTOS

#include <mach/boolean.h>

extern spl_t	swap_ipl(spl_t);
extern spl_t	swap_ipl_nopatch(spl_t);
extern spl_t	swap_ipl_preempt_check(spl_t);
extern spl_t	getspl(void);
extern boolean_t iplis0(void);
extern boolean_t issplsched(void);

#endif /* _USE_KERNEL_PROTOS */

#endif /* _KERNEL */

#endif /* !ASSEMBLER */

/*
 * Adding the following define will track spl blocking of the clock:
 * #define MISS_TICK_CHECK
 *
 * Adding the follwoign define will track spl changes on a per thread
 * basis:
 * #define SPL_PER_THREAD_TRACING 500
 */

#ifdef __cplusplus
}
#endif

#endif /* _MACHINE_SPL_H_ */
