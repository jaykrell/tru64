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
 * @(#)$RCSfile: fbus_loadable.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2000/09/26 17:56:38 $
 */
#ifndef _FBUS_LOADABLE_H_
#define _FBUS_LOADABLE_H_

#ifndef __cplusplus

#include <sys/types.h>

struct fbus_intr_info {
        caddr_t configuration_st;       /* Pointer to bus/controller struct */
        int (*intr)();                  /* Interrupt handler */
        caddr_t param;                  /* param for interrupt handler */
        unsigned int config_type;       /* Driver type, FBUS_ADPT or FBUS_CTLR */
	unsigned int vector_offset;	/* Fbus interrupt vector for device to use */
	long reserved[6];
};

struct fbus_handler_info {
	vm_offset_t vec_addr;
	int vec_offset;
        int (*intr)();                  /* Interrupt handler */
        caddr_t param;                  /* param for interrupt handler */
	struct fbus_handler_info *self_reference;
};

#endif /* __cplusplus */

#endif /* _FBUS_LOADABLE_H_ */
