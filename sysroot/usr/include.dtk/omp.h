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
 * @(#)$RCSfile: omp.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1999/06/23 20:09:16 $
 */

#ifndef _OMP_H_
#define _OMP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
**  Need pthread.h for _OtsGetOmpThread()
*/
#include <pthread.h>

/*
** Define the omp_lock_t and omp_nest_lock_t types
*/
typedef long int omp_lock_t;
typedef struct {
    long int __first_quad;
    long int __second_quad;
} omp_nest_lock_t;

/*
** If compiling with the directive enabled declare prototypes
*/
#ifdef _OPENMP

/* Sets number of threads for use for subsequent parallel regions */
void	omp_set_num_threads(int __num_threads);

/* Returns the number of threads currently in the team */
int	omp_get_num_threads(void);

/* Returns the maximum value that can be returned by omp_get_num_threads */
int	omp_get_max_threads(void);

/* Returns the thread number, within its team, of the thread */
int	omp_get_thread_num(void);

/* Returns maximum number of processors that coudl be assigned. */
int	omp_get_num_procs(void);

/* Tests if in the dynamic extent of a parallel region */
int	omp_in_parallel(void);

/* Enables/Disables dynamic adjustment of the number of threads */
void	omp_set_dynamic(int __dynamic_threads);

/* Tests if dynamic thread adjustment is enabled */
int	omp_get_dynamic(void);

/* Enables/Disables nested parallelism */
void	omp_set_nested(int __nested);

/* Tests if nested parallelism is enabled */
int	omp_get_nested(void);

/* Initialize locks */
void	omp_init_lock(omp_lock_t *__lock);
void	omp_init_nest_lock(omp_nest_lock_t *__lock);

/* Destroy locks */
void	omp_destroy_lock(omp_lock_t *__lock);
void	omp_destroy_nest_lock(omp_nest_lock_t *__lock);

/* Set locks */
void	omp_set_lock(omp_lock_t *__lock);
void	omp_set_nest_lock(omp_nest_lock_t *__lock);

/* Release locks */
void	omp_unset_lock(omp_lock_t *__lock);
void	omp_unset_nest_lock(omp_nest_lock_t *__lock);

/* Test locks */
int	omp_test_lock(omp_lock_t *__lock);
int	omp_test_nest_lock(omp_nest_lock_t *__lock);

/* pthread_t handle for a specified OpenMP thread ID number */
pthread_t _OtsGetOmpThread(int __OmpNumber);


#else  /* _OPENMP */

/*
** If compiling with directives disabled, define static stubs for
** the routines
*/
#include <stdio.h>
#include <stdlib.h>

static void omp_set_num_threads(int __num_threads)
{
    return;
}


static int omp_get_num_threads(void)
{
    return 1;
}


static int omp_get_max_threads(void)
{
    return 1;
}


static int omp_get_thread_num(void)
{
    return 0;
}


static int omp_get_num_procs(void)
{
    return 1;
}


static int omp_in_parallel(void)
{
    return 0;
}

static void omp_set_dynamic(int __dynamic_threads)
{
    return;
}


static int omp_get_dynamic(void)
{
    return 0;
}


static void omp_set_nested(int __nested)
{
    return;
}


static int omp_get_nested(void)
{
    return 0;
}


enum {_UNLOCKED = -1, _INIT, _LOCKED};

static void omp_init_lock(omp_lock_t *__lock)
{
    *__lock = _UNLOCKED;
}

static void omp_init_nest_lock(omp_nest_lock_t *__lock)
{
    __lock->__first_quad = _UNLOCKED;
}


static void omp_destroy_lock(omp_lock_t *__lock)
{
    *__lock = _INIT;
}

static void omp_destroy_nest_lock(omp_nest_lock_t *__lock)
{
    __lock->__first_quad = _INIT;
}

static void omp_set_lock(omp_lock_t *__lock)
{
    if (*__lock == _UNLOCKED)
    {
	*__lock = _LOCKED;
    }
    else if (*__lock == _LOCKED)
    {
	fprintf(stderr, "error: deadlock in using lock variable\n");
	exit(1);
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n"); exit(1);
    }
}

static void omp_set_nest_lock(omp_nest_lock_t *__lock)
{
    if (__lock->__first_quad == _UNLOCKED)
    {
	__lock->__first_quad = _LOCKED;
    }
    else if (__lock->__first_quad == _LOCKED)
    {
	fprintf(stderr, "error: deadlock in using lock variable\n");
	exit(1);
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n"); exit(1);
    }
}

static void omp_unset_lock(omp_lock_t *__lock)
{
    if (*__lock == _LOCKED)
    {
	*__lock = _UNLOCKED;
    }
    else if (*__lock == _UNLOCKED)
    {
	fprintf(stderr, "error: lock not set\n"); exit(1);
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n");
	exit (1);
    }
}

static void omp_unset_nest_lock(omp_nest_lock_t *__lock)
{
    if (__lock->__first_quad == _LOCKED)
    {
	__lock->__first_quad = _UNLOCKED;
    }
    else if (__lock->__first_quad == _UNLOCKED)
    {
	fprintf(stderr, "error: lock not set\n"); exit(1);
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n");
	exit (1);
    }
}


static int omp_test_lock(omp_lock_t *__lock)
{
    if (*__lock == _UNLOCKED)
    {
	*__lock = _LOCKED;
	return 1;
    }
    else if (*__lock == _LOCKED)
    {
	return 0;
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n");
	exit(1);
    }
}

static int omp_test_nest_lock(omp_nest_lock_t *__lock)
{
    if (__lock->__first_quad == _UNLOCKED)
    {
	__lock->__first_quad = _LOCKED;
	return 1;
    }
    else if (__lock->__first_quad == _LOCKED)
    {
	return 0;
    }
    else
    {
	fprintf(stderr, "error: lock not initialized\n");
	exit(1);
    }
}

static pthread_t _OtsGetOmpThread(int __OmpNumber)
{
    return pthread_self();
}

#endif /* _OPENMP */

#ifdef __cplusplus
}
#endif

#endif /* _OMP_H_ */
