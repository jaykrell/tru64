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
 * @(#)$RCSfile: kern_compat.h,v $ $Revision: 1.1.6.1 $ (DEC) $Date: 2000/10/25 21:59:29 $
 */

#ifndef _SYS_KERN_COMPAT_H_
#define _SYS_KERN_COMPAT_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void cm_init(void);
extern int cm_setup(struct compat_mod *mod, char *stanza, int stanzalen,
	char *name, char *rev, int revision, int (*cfg)(int, ...),
	struct compat_mod *(*rec)(struct filehdr *, ...),
	struct sysent *(*syscall)(long), char **call_nam, int *stats,
	char *trace, int hab, int base, int last);
extern int cm_add(struct compat_mod *block);
extern int cm_del(struct compat_mod *block);
extern void cm_newproc(struct compat_mod *block);
extern void cm_terminate(struct compat_mod *block);
#ifdef __alpha
extern void cm_recognizer(struct filehdr *hdr, struct aouthdr *aux,
	struct vnode *vp);
#endif
extern int cm_get_struct(struct compat_mod **ptr, struct compat_mod *buf);
extern int cm_query(struct compat_mod *mod, int *indata, size_t indatalen,
	int *outdata, size_t outdatalen);
extern int cm_operate(struct compat_mod *mod, int *indata, size_t indatalen,
	int *outdata, size_t outdatalen);
static int cm_validate(struct compat_mod *mod);
extern int cm_trace_this(struct compat_mod *mod);
extern void cm_display(struct compat_mod *mod);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _SYS_KERN_COMPAT_H_ */
