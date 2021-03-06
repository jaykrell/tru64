/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: time.h,v $
 * Revision 1.1.2.1  2006/07/18  11:16:14  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: time.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:16:14 $
 */
/*
 * Copyright (c) 2005 Sendmail, Inc. and its suppliers.
 *	All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *	$Id: time.h,v 1.1.2.1 2006/07/18 11:16:14 Sunilkumar_Mummigatti Exp $
 */

#ifndef SM_TIME_H
# define SM_TIME_H 1

# include <sm/config.h>

# include <sys/time.h>

/* should be defined in sys/time.h */
#ifndef timersub
# define timersub(tvp, uvp, vvp)					\
	do								\
	{								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0)					\
		{							\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000;			\
		}							\
	} while (0)
#endif /* !timersub */

#ifndef timeradd
# define timeradd(tvp, uvp, vvp)					\
	do								\
	{								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000)				\
		{							\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000;			\
		}							\
	} while (0)
#endif /* !timeradd */

#ifndef timercmp
# define timercmp(tvp, uvp, cmp)					\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#endif /* !timercmp */


#endif /* ! SM_TIME_H */
