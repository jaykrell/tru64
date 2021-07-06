/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: assert.h,v $
 * Revision 4.2.16.2  2010/03/30  13:41:31  Shekar_M_S
 * 	Fix for QAR 20814. Vikrams fix, I'm just submitting
 * 	auradkar QAR 20814
 * 	Fixes a problem of interleaved NDEBUG
 * 	defines and undefines. The pre-fix
 * 	behavior was deviating from standards.
 *
 * Revision 4.2.16.1  2005/07/20  18:11:56  Brenda_Wulf
 * 	corrects assert macrodefinition
 *
 * Revision 4.2.14.2  1996/03/12  19:00:36  Gerald_Feldman
 * 	 Quiet a lint build warning int the __LINT section.
 * 	[1996/03/11  21:58:11  Gerald_Feldman]
 *
 * Revision 4.2.12.3  1995/08/18  14:22:07  Chris_Gillett
 * 	Change LINT to __LINT.  Has same effect and prevents problems with cfe
 * 	bootstraps.
 * 	[1995/08/18  14:21:19  Chris_Gillett]
 * 
 * Revision 4.2.12.2  1995/08/16  18:55:30  Chris_Gillett
 * 	Changed the ordering of conditional compilation checks for NDEBUG and LINT
 * 	as per Feldman's code review suggestion.
 * 	[1995/08/16  18:53:37  Chris_Gillett]
 * 
 * 	Added an alternate definition of assert(), conditioned on lint
 * 	being run, to keep lint from generating noise during file inclusion.
 * 	[1995/08/10  19:03:54  Chris_Gillett]
 * 
 * Revision 4.2.10.3  1993/06/09  14:04:20  Neil_OBrien
 * 	Cast the condition part of the assert() macro replacement text to an
 * 	int in order to properly truncate the argument to assert().  Fixes
 * 	OSF_QAR #12498.
 * 	[1993/06/09  13:46:38  Neil_OBrien]
 * 
 * Revision 4.2.10.2  1993/06/07  19:41:55  Thomas_Woodburn
 * 	I18N/thread-safe/ANSI-name-space joint submit.
 * 	[1993/06/07  18:30:47  Thomas_Woodburn]
 * 
 * Revision 4.2.8.2  1993/06/03  17:01:31  Robert_Fontaine
 * 	Remove argument names from function prototype for __assert.
 * 	[1993/06/03  13:40:28  Robert_Fontaine]
 * 
 * Revision 4.2.5.2  93/02/07  11:38:15  Neil_OBrien
 * 	Eliminated unneeded ## operator from macro definition of assert(EX).
 * 	Fixes OSF_QAR #09142.
 * 	[93/02/02  12:16:03  Neil_OBrien]
 * 
 * Revision 4.2.3.2  92/04/15  08:14:45  Al_Delorey
 * 	From Silver: AG_BL6
 * 	[92/04/15  08:14:01  Al_Delorey]
 * 
 * 	Merge with AG
 * 	[92/03/27  13:50:02  Craig_Horman]
 * 
 * 	Merge with BL5
 * 	[92/03/09  14:44:28  Craig_Horman]
 * 
 * 	Added C++ Support
 * 	[92/02/26  14:32:07  Craig_Horman]
 * 
 * Revision 4.2.1.2  92/04/13  17:57:27  devbld_gsf
 * 	First AG_BL6 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 4.2  91/09/20  05:13:38  devbld
 * 	Adding ODE Headers
 * 
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: assert.h,v $ $Revision: 4.2.16.2 $ (DEC) $Date: 2010/03/30 13:41:31 $
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
/*
 * assert.h
 *
 *	Modification History:
 *
 * 01-Apr-91	Fred Canter
 *	MIPS C 2.20+, changes for -std
 *
 */

/*
 * COMPONENT_NAME: (SYSDB) Kernel Debugger
 *
 * FUNCTIONS:
 *
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 * 
 * assert.h	1.10  com/inc,3.1,9021 5/11/90 10:03:55 
 */

#ifdef _ASSERT_H_
#undef _ASSERT_H_
#undef assert
#endif

#ifndef _ASSERT_H_
#define _ASSERT_H_
#include <standards.h>

/*
 *
 *      The ANSI standard requires that certain values be in assert.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.  This header includes all ANSI required entries.  
 *
 */
#ifdef _ANSI_C_SOURCE

#if defined(__LINT)
#if defined(__cplusplus)
extern "C" {
#endif
extern void __assert();
#if defined(__cplusplus)
}
#endif
#define assert(EX) __assert(EX,__FILE__,__LINE__)
#elif defined(NDEBUG)
#define assert(ignore) ((void)0)
#else
#if defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C" {
#endif
extern void __assert(char *, char *, int);
#if defined(__cplusplus)
}
#endif
#else  /* __STDC__ */
extern void __assert();
#endif /* _NO_PROTO */

#if defined(__cplusplus)
#  define assert(EX) (( (EX)) ? (void)0 : __assert(#EX, __FILE__, __LINE__))
#elif defined(__STDC__)
#  define assert(EX) (((int) (EX)) ? (void)0 : __assert(#EX, __FILE__, __LINE__))
#else
#  define assert(EX) if ((int) (EX)) ; else __assert("EX", __FILE__, __LINE__)
#endif 

#endif /* NDEBUG */
#endif /* _ANSI_C_SOURCE */
#endif /* _ASSERT_H_ */
