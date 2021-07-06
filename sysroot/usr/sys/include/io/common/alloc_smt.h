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
 * @(#)$RCSfile: alloc_smt.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1999/01/28 16:53:13 $
 */

#ifndef _SMT_H_
#define _SMT_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Shared Magentic Tape (SMT) Allocation routine Return Statuses. */

#define SMT_SUCCESS     0      /* Device Allocated/Deallocated */
#define SMT_FAILED      1      /* Requeset unsuccessful, not Allocated */

/* Vector index definitions into jump table */

#define SMT_ALLOCATE 0         /* the allocate vector into the jump table */
#define SMT_DEALLOCATE 1       /* the deallocate vector into the jump table */

typedef struct smt_metadata {
  int flags;         /* global flags variable */
  int ref;           /* reference count variable */
  void (**table)();  /* handle to the jump table */
} SMT_DATA;

/* defines used in the smt_metadata flags member */

#define SMT_EXCLUSIVE 0x1      /* state flags */
#define SMT_LOADING   0x2 

/* Global declarations */

extern int alloc_smt(dev_t devunit);
extern void dealloc_smt(dev_t devunit);

#ifdef __cplusplus
}
#endif
#endif /* _SMT_H_ */






