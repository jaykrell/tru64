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
 * @(#)$RCSfile$ $Revision$ (DEC) $Date$
 */

#ifndef _OTSNUMA_H_
#define _OTSNUMA_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Get base system numa.h */
#include_next <numa.h>

/*
 * Declare additional NUMA-specific API's provided in conjunction with
 * OpenMP support in libots3.  All but the last (_OtsMigrateToOmpThread)
 * can also be useful in an application that does not use OpenMP.
 */


/*
 *      Determine which rad an address is stored in and return
 *	its radid.
 */ 
extern radid_t
_OtsAddrToRad(void *__addr);


/*
 *	Mark a range of pages to be migrated on the next reference
 *	to the page.  The next time a thread references one of these
 *	pages, a page fault occurs and the page is migrated to a
 *	location near the referencing thread.  All pages containing
 *      any addresses in the inclusive range are migrated.
 */
extern void
_OtsMigrateNextTouch(void *__start, void *__end);


/*
 *	Mark a range of pages to be placed on the next reference
 *	to the page.  The next time a thread references one of these
 *	pages, a page fault occurs and the physical memory for the
 *	page will be allocated in a location near the referencing
 *	thread.  The contents of the page is unpredictable.  The
 *      placed pages are only those that lie entirely within the
 *      specified address range.
 */
extern void
_OtsMigrateNextTouchNopreserve(void *__start, void *__end);


/*
 *	This function takes a range of pages identified by start and end,
 *	and a rad id.  It then uses nmadvise to migrate the range of pages 
 *      to that rad.
 */
extern void
_OtsMigrateToRAD(void *__start, void *__end, radid_t __radnum);


/*
 *	This function takes a range of pages identified by start and end,
 *	and an OpenMP thread ID number (the id within the team corresponding
 *      to the parallel scope from which the call occured).  It determines
 *	the home rad of that thread.  It then uses nmadvise to migrate
 *	the range of pages to that rad.
 */
extern void
_OtsMigrateToOmpThread(void *__start, void *__end, int __OmpNumber);


#ifdef __cplusplus
}
#endif

#endif /* _OTSNUMA_H_ */
