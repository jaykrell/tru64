/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: useful.h,v $
 * Revision 1.1.2.1  2006/07/18  11:15:35  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * Revision 1.1.2.1  2000/12/01  19:50:59  James_Seagraves
 * 	new for sendmail version 8.11.1
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: useful.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:15:35 $
 */
/*
 * Copyright (c) 1998, 1999 Sendmail, Inc. and its suppliers.
 *	All rights reserved.
 * Copyright (c) 1995-1997 Eric P. Allman.  All rights reserved.
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *
 *	$Id: useful.h,v 1.1.2.1 2006/07/18 11:15:35 Sunilkumar_Mummigatti Exp $
 */

#ifndef _USEFUL_H
# define _USEFUL_H

# include <sys/types.h>

/* support for bool type */
typedef int	bool;
# ifndef TRUE
#  define TRUE	1
#  define FALSE	0
# endif /* ! TRUE */

# ifndef NULL
#  define NULL	0
# endif /* ! NULL */

/* bit hacking */
# define bitset(bit, word)	(((word) & (bit)) != 0)

/* some simple functions */
# ifndef max
#  define max(a, b)	((a) > (b) ? (a) : (b))
#  define min(a, b)	((a) < (b) ? (a) : (b))
# endif /* ! max */

/* assertions */
# ifndef NASSERT
#  define ASSERT(expr, msg, parm)\
	if (!(expr))\
	{\
		fprintf(stderr, "assertion botch: %s:%d: ", __FILE__, __LINE__);\
		fprintf(stderr, msg, parm);\
	}
# else /* ! NASSERT */
#  define ASSERT(expr, msg, parm)
# endif /* ! NASSERT */

/* sccs id's */
# ifndef lint
#  ifdef __STDC__
#   define SCCSID(arg)	static char SccsId[] = #arg;
#  else /* __STDC__ */
#   define SCCSID(arg)	static char SccsId[] = "arg";
#  endif /* __STDC__ */
# else /* ! lint */
#  define SCCSID(arg)
# endif /* ! lint */
#endif /* ! _USEFUL_H */
