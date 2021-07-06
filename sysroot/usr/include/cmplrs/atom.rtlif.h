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
 * @(#)$RCSfile: atom.rtlif.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 2000/11/17 19:24:42 $
 */
/*
 * Routines that implement the Atom/RTL interface.
 */

#ifndef _ATOM_RTLIF_H_
#define _ATOM_RTLIF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <machine/machlimits.h>

#define __PTHREAD_ATOM_NO_STATE LONG_MIN

extern long __pthreadAtomDisable(void);
extern void __pthreadAtomRestore(long state);

extern void __pthreadAtomInit(void);
extern void __pthreadAtomCreate(void);
extern void __pthreadAtomTerminate(void);

extern void __pthreadAtomReset(void);
extern void __pthreadAtomResetAction(void);
extern void __pthreadAtomTisVector(int (***vector)(void),int (***end)(void));
extern void __pthreadAtomThreaded(void);

extern void __pthreadAtomPreFork(void);
extern void __pthreadAtomPostFork(pid_t pid);
extern void __pthreadAtomPreForkAction(void);
extern void __pthreadAtomPostForkAction(int state);

#ifdef __cplusplus
}
#endif

#endif /* _ATOM_RTLIF_H_ */
