/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: cf.h,v $
 * Revision 1.1.2.1  2006/07/18  11:15:40  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: cf.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:15:40 $
 */
/*
 * Copyright (c) 2001 Sendmail, Inc. and its suppliers.
 *      All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *	$Id: cf.h,v 1.1.2.1 2006/07/18 11:15:40 Sunilkumar_Mummigatti Exp $
 */

#ifndef SM_CF_H
# define SM_CF_H

#include <sm/gen.h>

typedef struct
{
	char *opt_name;
	char *opt_val;
} SM_CF_OPT_T;

extern int
sm_cf_getopt __P((
	char *path,
	int optc,
	SM_CF_OPT_T *optv));

#endif /* ! SM_CF_H */
