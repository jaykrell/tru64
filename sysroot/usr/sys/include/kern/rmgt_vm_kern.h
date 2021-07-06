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
 * @(#)$RCSfile: rmgt_vm_kern.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2000/12/07 17:18:28 $
 */

/*
 * Aurema Pty. Limited has provided specific written authorization to
 * Compaq Computer Corporation to include the source material found
 * in this file in the Tru64 UNIX product.  Possession and use of this
 * material is authorized by Compaq Computer Corporation to licensed
 * users of the Tru64 UNIX binary or source product.  No other right
 * to use this source material is implied by possession thereof.
 */

/*
 *  This computer program is a proprietary trade secret of Aurema Pty. Limited.
 *  Possession and use of this program shall be strictly in accordance with a
 *  license agreement between the user and Aurema Pty. Limited.  Receipt and
 *  possession of this program does not convey any rights to divulge, reproduce,
 *  or allow others to use it without specific written authorization of
 *  Aurema Pty. Limited.
 *
 *  Copyright 2000, an unpublished work by Aurema Pty. Limited.
 *  All rights reserved.
 */

#ifndef __TRU64_RMGT_VM_KERN_H
#define __TRU64_RMGT_VM_KERN_H

/**
 **  vm map calls
 **/

/*
 * The address of a newly created empty VM map is passed to the 
 * policy managers via the call_rmgt_map_create() callback function.
 */
extern void call_rmgt_map_create(vm_map_t map);

/*
 * The address of a newly created empty VM map for a forked child 
 * process is passed to the policy managers via the 
 * call_rmgt_map_attach() callback function.
 *
 * This function allows the policy managers to veto this attach 
 * operation. If any of the policy managers vetoes the operation, 
 * it will fail with a non-zero error code returned.
 */
extern int call_rmgt_map_attach(vm_map_t map, pid_t pid);

/*
 * Whenever a user map size increases, the address of the map and
 * its incremental size are passed to the policy managers via the 
 * call_rmgt_map_use() callback function.
 *
 * This function allows the policy managers to veto this size change
 * operation. If any of the policy managers vetoes the operation, 
 * it will fail with a non-zero error code returned.
 */
extern int call_rmgt_map_use(vm_map_t map, size_t vmap_size);

/*
 * Whenever a user map size decreases, the address of the map and
 * its decremental size are passed to the policy managers via the 
 * call_rmgt_map_release() callback function.
 */
extern void call_rmgt_map_release(vm_map_t map, size_t vmap_size);

/*
 * After the last reference of the map has been removed and before 
 * it is deallocated from the system, the policy managers are
 * informed via the call_rmgt_map_destroy() callback function.
 */
extern void call_rmgt_map_destroy(vm_map_t map);

/**
 ** sv shared memory calls 
 **/

/*
 * When a shared memory region is created in "shmget" system call,
 * the address of the newly created object is passed to the
 * policy managers via the call_rmgt_svshm_create() call.
 */
extern void call_rmgt_svshm_create(vm_object_t obj);

/*
 * When a shared memory region is attached to the virtual address 
 * space of the calling process in "shmat" system call,
 * the address of the attached object and the process' pid are passed 
 * to the policy managers via the call_rmgt_svshm_attach() call.
 */
extern int call_rmgt_svshm_attach(vm_object_t obj, pid_t pid);

/*
 * When a shared memory region is detached from the virtual address 
 * space of the calling process in "shmdt" system call,
 * the address of the detached object and the process' pid are passed 
 * to the policy managers via the call_rmgt_svshm_detach() call.
 */
extern void call_rmgt_svshm_detach(vm_object_t obj, pid_t pid);

/*
 * When a shared memory region is removed completely in "shmctl"
 * system call with IPC_RMID command, the address of the shared
 * object is passed via the call_rmgt_svshm_destroy() call.
 */
extern void call_rmgt_svshm_destroy(vm_object_t obj);

/**
 ** "map fault and stack grow" call 
 **/

/*
 * When a user map fault failure occurs and tries to grow the stack,
 * the stack object is passed to the policy managers via the 
 * call_rmgt_stk_grow() call.
 *
 * This function allows the policy managers to veto the stack grow.
 * If any of the policy managers vetoes the operation,
 * it will fail with a non-zero error code returned.
 */
extern int call_rmgt_stk_grow(vm_object_t obj);

#endif  /* __TRU64_RMGT_VM_KERN_H */
