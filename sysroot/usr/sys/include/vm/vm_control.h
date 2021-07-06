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
 * @(#)$RCSfile: vm_control.h,v $ $Revision: 1.1.10.3 $ (DEC) $Date: 2000/07/20 13:51:07 $
 */
#ifndef __VM_CONTROL__
#define __VM_CONTROL__ 1

/*
 * General level control functions.
 */

typedef enum {
	VMC_INHERITANCE,		/* entry inheritance */
	VMC_KEEP_ON_EXEC,		/* entry keep on exec */
	VMC_MSYNC,			/* msync */
	VMC_SEM_SLEEP,			/* BSD semaphore sleep */
	VMC_SEM_WAKEUP,			/* BSD semaphore wakeup */
	VMC_MADV_DONTNEED		/* madvise MADV_DONTNEED */
}	vm_control_t;	


#endif /* !__VM_CONTROL__ */
