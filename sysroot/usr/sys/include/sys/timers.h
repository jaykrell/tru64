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
 *	@(#)$RCSfile: timers.h,v $ $Revision: 4.2.17.1 $ (DEC) $Date: 2000/01/14 14:34:49 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_TIMERS_H
#define _SYS_TIMERS_H
#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE<500)
#include <sys/signalmisc.h>
#endif /* !defined(_XOPEN_SOURCE) || (_XOPEN_SOURCE<500) */
#include <sys/timemisc.h>

#ifdef POSIX_4D9
#include <sys/types.h>
#define TIMEOFDAY	1		/* time of day clock type */
struct itimerspec {
	struct timespec	it_interval;	/* timer period */
	struct timespec	it_value;	/* timer expiration */
};

struct itimercb {
#ifdef _POSIX_ASYNCHRONOUS_EVENTS
	struct event	itcb_event;	/* timer event definition */
#endif
	int		itcb_count;	/* timer "overrun" count */
};


/*
 * Notification types
 */
#define DELIVERY_SIGNALS	1
#define DELIVERY_EVENTS		2

#ifdef nanosleep
#undef nanosleep
#endif
#define nanosleep(rqtp,rmtp)   nanosleep_d9(rqtp,rmtp)
/*
 * Functions
 */
int getclock(int, struct timespec *);
int setclock(int, struct timespec *);
int resclock(int, struct timespec *, struct timespec *);
timer_t mktimer(int, int, void *);
int rmtimer(timer_t);
int gettimer(timer_t, struct itimerspec *);
int reltimer(timer_t, struct itimerspec *, struct itimerspec *);
int abstimer(timer_t, struct itimerspec *, struct itimerspec *);
int resrel(timer_t, struct timespec *, struct timespec *);
int resabs(timer_t, struct timespec *, struct timespec *);
int nanosleep_d9(struct timespec *, struct timespec *);
int ressleep(struct timespec *, struct timespec *);

#elif defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 

/* 
 * Constants and Macros
 */


#ifndef	_CLOCKID_T
#define	_CLOCKID_T
typedef int             clockid_t;
#endif	/* _CLOCKID_T */

/*
 * Data Structure Definitions
 */

/*
 * The maximum timeout value, in seconds, allowed for an P1003.4
 * interval timers.
 */

struct	itimerspec {
	struct		timespec it_interval; /* timer interval */
	struct		timespec it_value; /* current value */
};

/* 
 * useful macros,  note these are not defined by P1003.4
 */

# if !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE < 500)
/* The following definitions are hidden in XSH5 namespace */
#define TIMEOFDAY	1	/* time of day clock type */
#define	nsec_timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_nsec)
#define	nsec_timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_nsec = 0

/*
 * Compare two nano_second timers.  Not this only works for
 * <, > or = but not for any conbination of the two.
 */

#define	nsec_timercmp(tvp, fvp, cmp)			        	\
	((tvp)->tv_sec cmp (fvp)->tv_sec ||				\
	(tvp)->tv_sec == (fvp)->tv_sec &&				\
	(tvp)->tv_nsec cmp (fvp)->tv_nsec)

#endif /* !_XOPEN_SOURCE || _XOPEN_SOURCE<500 */


/* 
 * routine definitions
 */

int clock_gettime __((clockid_t, struct timespec *));
int clock_settime __((clockid_t, const struct timespec *));
int clock_getdrift __((int, int *));
int clock_setdrift __((int, const int, int *));

#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) )
/*
 * The function sigevent is redefined here as in signalmisc.h
 * Any changes done here should also be reflected in that file
 */
#ifndef _SIGEVENT
#define _SIGEVENT

typedef union sigval {
        int     sival_int;
        void    *sival_ptr;
} sigval_t;

#if defined ( _KERNEL ) || defined (_OSF_SOURCE)
typedef struct sigevent_event {
        union sigval    _sigev_value;   /* application-defined value */
        int             _sigev_signo;   /* signal to raise */
        int             _sigev_notify;  /* raise a signal? */
} sigevent_event_t;
#endif /* _KERNEL || _OSF_SOURCE */

#define SIGEV_MAX_SIZE  (64)
#define SIGEV_PAD_SIZE ((SIGEV_MAX_SIZE/sizeof(int)) - 4)

typedef struct sigev_event {
        union sigval    _sigev_value;   /* application-defined value */
        int             _sigev_signo;   /* signal to raise */
        int             _sigev_notify;  /* raise a signal? */
} sigev_event_t;

typedef struct sigevent {
        sigev_event_t        _sigev_sigevent;
        union {
                int             _sigev[SIGEV_PAD_SIZE];

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
                struct {
                        /*
                         * These fields appear only when compiling
                         * for threaded applications. See SIGEV_THREAD
                         * above.
                         */
                        void (*_sigev_notify_function) __((sigval_t));
                        pthread_attr_t *_sigev_notify_attributes;
                } _sigev_un_s;
#endif /* _POSIX_C_SOURCE >= 199506L */
        } _sigev_un;
} sigevent_t;

#endif /* _SIGEVENT */
#endif /* _OSF_SOURCE || _POSIX_C_SOURCE */

int timer_create __((clockid_t, struct sigevent *, timer_t *));

int timer_delete __((timer_t));
int timer_gettime __((timer_t, struct itimerspec *));
int timer_settime __((timer_t, int, const struct itimerspec *,
		      struct itimerspec *));
int timer_getoverrun __((timer_t));
int nanosleep __((const struct timespec *, struct timespec *));
int clock_getres __((clockid_t, struct timespec *));

#endif  /* _POSIX_C_SOURCE */
#if defined(__cplusplus)
}
#endif
#endif	/* _SYS_TIMERS_H */
