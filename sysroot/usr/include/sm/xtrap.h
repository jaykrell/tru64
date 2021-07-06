/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: xtrap.h,v $
 * Revision 1.1.2.1  2006/07/18  11:16:17  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: xtrap.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:16:17 $
 */
/*
 * Copyright (c) 2000-2001 Sendmail, Inc. and its suppliers.
 *	All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *	$Id: xtrap.h,v 1.1.2.1 2006/07/18 11:16:17 Sunilkumar_Mummigatti Exp $
 */

/*
**  scaffolding for testing exception handler code
*/

#ifndef SM_XTRAP_H
# define SM_XTRAP_H

# include <sm/debug.h>
# include <sm/exc.h>

extern SM_ATOMIC_UINT_T SmXtrapCount;
extern SM_DEBUG_T SmXtrapDebug;
extern SM_DEBUG_T SmXtrapReport;

# if SM_DEBUG_CHECK
#  define sm_xtrap_check() (++SmXtrapCount == sm_debug_level(&SmXtrapDebug))
# else /* SM_DEBUG_CHECK */
#  define sm_xtrap_check() (0)
# endif /* SM_DEBUG_CHECK */

# define sm_xtrap_raise_x(exc) \
		if (sm_xtrap_check()) \
		{ \
			sm_exc_raise_x(exc); \
		} else

#endif /* ! SM_XTRAP_H */
