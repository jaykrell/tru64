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
 * @(#)$RCSfile: tty_pty.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1999/03/26 22:47:37 $
 */
#ifndef _SYS_TTY_PTY_H_
#define _SYS_TTY_PTY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/secdefines.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/limits.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/user.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/lock_types.h>
#include <kern/assert.h>
#include <kern/parallel.h>
#if     SEC_BASE
#include <sys/security.h>
#endif  /* SEC_BASE */
#if     SEC_ARCH
#include <sys/secpolicy.h>
#endif  /* SEC_ARCH */

/************************************************************************
 *
 * Define pty structures.
 *
 * pts == /dev/tty[pqrs]?       (Slaves)
 * ptc == /dev/pty[pqrs]?       (Masters)
 *
 ************************************************************************/
struct  pt_ioctl {
        int     pt_flags;
        int     pt_count;
        queue_head_t    pt_selq;
        u_char  pt_send;
        u_char  pt_ucntl;
};
struct pt_data {
        struct pt_data *pt_prev, *pt_next;
        struct tty pt_tty;
        struct pt_ioctl pt_ioctl;
#if     SEC_ARCH
        tag_t  ptctag[SEC_TAG_COUNT];
        tag_t  ptstag[SEC_TAG_COUNT];
#endif  /* SEC_ARCH */
};
#ifdef __cplusplus
}
#endif
#endif  /* _SYS_TTY_PTY_H_ */
