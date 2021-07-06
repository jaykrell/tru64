/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright 2001 Compaq Computer Corporation                 *
 * *                                                               *
 * *    Compaq and the Compaq logo Registered in U.S. Patent       *
 * *    and Trademark Office.                                      *
 * *                                                               *
 * *    Confidential computer software. Valid license from Compaq  *
 * *    required for possession, use or copying. Consistent with   *
 * *    FAR 12.211 and 12.212, Commercial Computer Software,       *
 * *    Computer Software Documentation, and Technical Data for    *
 * *    Commercial Items are licensed to the U.S. Government       *
 * *    under vendors standard commercial license.                 *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: mpc.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1999/06/23 20:09:15 $
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
**    Returns the current number of active threads.  Inside a parallel
**    region that has used a numthreads clause to limit the number
**    of threads, this function returns that number.  Otherwise
**    it returns the same value as mpc_maxnumthreads.
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
**    to execute a parallel region.  This is generally the number
**    of processors, or the value of the MP_THREAD_COUNT environment
**    variable if it is set.
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
