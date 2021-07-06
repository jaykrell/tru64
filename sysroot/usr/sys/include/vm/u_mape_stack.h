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
 * @(#)$RCSfile: u_mape_stack.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 2002/01/25 22:02:26 $
 */

#ifndef	__VM_U_MAPE_STACK_H__
#define	__VM_U_MAPE_STACK_H__
/*
 * The Stack object.
 */
struct vm_stack_object {
	struct vm_anon_object	stk_aobj;	/* anonymous memory */
	vm_size_t		stk_rsize;	/* red zone */
	vm_size_t		stk_ysize;	/* yellow zone */
	vm_size_t		stk_incr;	/* growth increment */
};

typedef struct vm_stack_object *vm_stack_object_t;

#define	stk_oflags	stk_aobj.ao_oflags
#define	stk_flags	stk_aobj.ao_flags
#define	stk_ranon	stk_aobj.ao_ranon
#define	stk_size	stk_aobj.ao_size
#define	stk_anons	stk_aobj.ao_anons
#define	stk_rbase	stk_aobj.ao_rbase
#define	stk_bigpg	stk_aobj.ao_bigpg

/*
 * Prototypes
 */
struct vm_map;
struct vm_map_entry;
struct vm_stack;

extern kern_return_t
	u_stack_create(struct vm_map *, struct vm_stack *),
	u_stack_grow(struct vm_map_entry *, vm_offset_t),
	u_stack_fault(struct vm_map_entry *, vm_offset_t, vm_size_t,
			vm_prot_t, vm_fault_t, struct vm_page **);
	u_stack_migrate(struct vm_map *, vm_offset_t, int);

extern void
	u_stack_restore_yzone(vm_offset_t);

#endif	/* __VM_U_MAPE_STACK_H__ */
