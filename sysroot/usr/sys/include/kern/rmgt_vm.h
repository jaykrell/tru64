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
 * @(#)$RCSfile: rmgt_vm.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/02 17:43:35 $
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
      
#ifndef	__TRU64_RMGT_VM_H
#define	__TRU64_RMGT_VM_H

typedef struct rmgt_vm_ops {
	const int interface_version;
	const char *policy_name;
	struct rmgt_vm_ops *next;

/* vm map ops */
	void (*rmgt_map_register)(vm_map_t, size_t, pid_t);

	void (*rmgt_map_create)(vm_map_t, size_t);

	int (*rmgt_map_attach_vetoed)(vm_map_t, pid_t);
	void (*rmgt_map_attach_cancel)(vm_map_t, pid_t);
	void (*rmgt_map_attach_commit)(vm_map_t, pid_t);

	int (*rmgt_map_use_vetoed)(vm_map_t, size_t);
	void (*rmgt_map_use_cancel)(vm_map_t, size_t);
	void (*rmgt_map_use_commit)(vm_map_t, size_t);

	void (*rmgt_map_release)(vm_map_t, size_t);
	void (*rmgt_map_destroy)(vm_map_t);

/* sv shared memory ops */
	void (*rmgt_svshm_register)(vm_object_t, size_t, pid_t);

	void (*rmgt_svshm_create)(vm_object_t, size_t);

	int (*rmgt_svshm_attach_vetoed)(vm_object_t, pid_t);
	void (*rmgt_svshm_attach_cancel)(vm_object_t, pid_t);
	void (*rmgt_svshm_attach_commit)(vm_object_t, pid_t);

	void (*rmgt_svshm_detach)(vm_object_t, size_t, pid_t);
	void (*rmgt_svshm_destroy)(vm_object_t);

/* stack grow ops */

	int (*rmgt_stk_grow_vetoed)(vm_object_t);
	void (*rmgt_stk_grow_cancel)(vm_object_t);
	void (*rmgt_stk_grow_commit)(vm_object_t);

} rmgt_vm_ops_t;

#define RMGT_VM_INTERFACE_VERSION   1

extern int register_rmgt_vm(struct rmgt_vm_ops *ops);
extern int unregister_rmgt_vm(struct rmgt_vm_ops *ops);
extern int count_rmgt_vm(void);
extern void rmgt_vm_lock_init(void);

#endif	/* __TRU64_RMGT_VM_H */
