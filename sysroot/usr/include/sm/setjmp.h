/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: setjmp.h,v $
 * Revision 1.1.2.1  2006/07/18  11:16:09  Sunilkumar_Mummigatti
 * 	New for sendmail.v8.13.6
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: setjmp.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2006/07/18 11:16:09 $
 */
/*
 * Copyright (c) 2000-2001 Sendmail, Inc. and its suppliers.
 *	All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *	$Id: setjmp.h,v 1.1.2.1 2006/07/18 11:16:09 Sunilkumar_Mummigatti Exp $
 */

#ifndef SM_SETJMP_H
# define SM_SETJMP_H

# include <sm/config.h>
# include <setjmp.h>

/*
**  sm_setjmp_sig is a setjmp that saves the signal mask.
**  sm_setjmp_nosig is a setjmp that does *not* save the signal mask.
**  SM_JMPBUF_T is used with both of the above macros.
**
**  On most systems, these can be implemented using sigsetjmp.
**  Some old BSD systems do not have sigsetjmp, but they do have
**  setjmp and _setjmp, which are just as good.
*/

# if SM_CONF_SIGSETJMP

typedef sigjmp_buf SM_JMPBUF_T;
#  define sm_setjmp_sig(buf)		sigsetjmp(buf, 1)
#  define sm_setjmp_nosig(buf)		sigsetjmp(buf, 0)
#  define sm_longjmp_sig(buf, val)	siglongjmp(buf, val)
#  define sm_longjmp_nosig(buf, val)	siglongjmp(buf, val)

# else /* SM_CONF_SIGSETJMP */

typedef jmp_buf SM_JMPBUF_T;
#  define sm_setjmp_sig(buf)		setjmp(buf)
#  define sm_longjmp_sig(buf, val)	longjmp(buf, val)
#   define sm_setjmp_nosig(buf)		_setjmp(buf)
#   define sm_longjmp_nosig(buf, val)	_longjmp(buf, val)

# endif /* SM_CONF_SIGSETJMP */

#endif /* ! SM_SETJMP_H */
