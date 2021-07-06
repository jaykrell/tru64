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
 * @(#)$RCSfile: exec_subr.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/03/21 20:00:28 $
 */

#ifndef _MACHINE_EXEC_SUBR_H_
#define _MACHINE_EXEC_SUBR_H_

#include <sys/ptrace.h>

/*
 * Generic machine dependencies
 */
#define EXEC_SIGTRAP()

/*
 * Machine dependencies for init
 */
/* 
 * SETUP_INIT_ARGS is called just before the first exec of the boot.
 * It is the last place where pmap_scavenge_boot() can be called.  This is
 * desirable because this routine reclaims the address space for the used
 * only once kernel code.
 */
#define SETUP_INIT_ARGS() pmap_scavenge_boot()

#define ALLOW_INITNAME	1
#define GETS(i)		gets(i)

/*
 * Machine dependencies for reading and writing argument pointers
 */

#define WRITE_ARG_PTR(app, ucpp) (suqword(app, ucpp))
#define READ_ARG_PTR(app) (fuqword(app))

#endif /* _MACHINE_EXEC_SUBR_H_ */
