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
 * @(#)$RCSfile: mpc.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/07/16 21:39:43 $
 */

#ifndef _MPC_H_
#define _MPC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
** mpc_in_parallel_region
**    This function returns 1 if the current thread is executing
**    in a parallel context, otherwise it returns 0.
*/
extern int  mpc_in_parallel_region(void);

/*
** mpc_numthreads
**    Returns the current number of active threads.
*/
extern int  mpc_numthreads(void);

/*
** mpc_my_threadnum
**    Returns an integer between 0 and the number of threads
**    currently running that uniquely identifies the current 
**    thread within a parallel construct.
*/
extern int  mpc_my_threadnum(void);

/*
** mpc_maxnumthreads
**    Returns the maximum number of threads that can be created
**    to execute a parallel region.
*/
extern int  mpc_maxnumthreads(void);

/*
** mpc_destroy
**    Destroys all threads except the master thread.
*/
extern void mpc_destroy(void);

#ifdef __cplusplus
}
#endif

#endif /* _MPC_H_ */
