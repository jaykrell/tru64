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
 *	"@(#)cons_sw.h	9.2	(ULTRIX/OSF)	11/5/91"
 */

/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#ifndef _CONS_SW_H_
#define _CONS_SW_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_KERNEL)
#  if defined(_USE_KERNEL_PROTOS)

#include <sys/tty.h>
#include <sys/types.h>
#include <sys/uio.h>

struct	cons_sw {
	int	(*c_open)(		/* console open			*/
			dev_t dev, unsigned int flag);
	int	(*c_close)(dev_t dev);	/* console close		*/
	int	(*c_read)(		/* console read			*/
			dev_t dev, struct uio *uio, unsigned int flag);
	int	(*c_write)(		/* console write		*/
			dev_t dev, struct uio *uio, unsigned int flag);
	int	(*c_ioctl)(		/* console ioctl		*/
			dev_t dev, unsigned int cmd,
			caddr_t addr, unsigned int flag);
	int	(*c_rint)(int c);	/* console receiver int		*/
	int	(*c_xint)(int c);	/* console transmitter int	*/
	int	(*c_start)(		/* console start		*/
			struct tty *tp);
	int	(*c_stop)(		/* console stop			*/
			struct tty *tp, unsigned int flag);
	int	(*c_select)(		/* console select		*/
			dev_t dev, short *events,
			short *revents, int scanning);
	void	(*c_putc)(int c);	/* console putc			*/
	int	(*c_probe)(		/* console probe		*/
			unsigned int c);
	int	(*c_getc)(void);	/* console getc			*/
	int	(*c_init)(void);	/* console init routine		*/
	int	(*c_param)(		/* console parameter routine	*/
			struct tty *tp, struct termios *t);
	int	(*c_mmap)(		/* console mmap routine		*/
			dev_t dev, off_t off, int prot);
	struct tty *ttys;		/* tty structure for select	*/
};

struct vcons_init_sw {
        char	modname[10];		/* module name	*/
	int	(*cons_init)(caddr_t address, int slot);
					/* virtual console init routine */
};

extern int nocons(void);
extern int noconsmmap(dev_t dev, off_t off, int prot);
extern void cons_null(void);
extern void cons_sw_init(int (*cons_open)(dev_t dev, unsigned int flag),
			int (*cons_close)(dev_t dev),
			int (*cons_read)(dev_t dev, struct uio *uio, unsigned int flag),
			int (*cons_write)(dev_t dev, struct uio *uio, unsigned int flag),
			int (*cons_ioctl)(dev_t dev, unsigned int cmd, caddr_t addr, unsigned int flag),
			int (*cons_rint)(int c),
			int (*cons_xint)(int c),
			int (*cons_start)(struct tty *tp),
			int (*cons_stop)(struct tty *tp, unsigned int flag),
			int (*cons_select)(dev_t dev, short *events, short *revents, int scanning),
			void (*cons_putc)(int c),
			int (*cons_probe)(unsigned int c),
			int (*cons_getc)(void),
			int (*cons_init)(void),
			int (*cons_param)(struct tty *tp, struct termios *t),
			int (*cons_mmap)(dev_t dev, off_t off, int prot),
			struct tty *cons_ttys);
extern int cninit(void);
extern int cnopen(dev_t dev, unsigned int flag);
extern int cnclose(dev_t dev);
extern int cnread(dev_t dev, struct uio *uio, unsigned int flag);
extern int cnwrite(dev_t dev, struct uio *uio, unsigned int flag);
extern int cnioctl(dev_t dev, unsigned int cmd, caddr_t addr, unsigned int flag);
extern int cnstop(struct tty *tp, unsigned int flag);
extern int cnstart(struct tty *tp);
extern int cnselect(dev_t dev, short *events, short *revents, int scanning);
extern int cnmmap(dev_t dev, off_t off, int prot);
extern void cnputc(int c);
extern int cngetc(void);
extern int cnprobe(unsigned int c);
extern int cnrint(int c);
extern int cnxint(int c);
extern int cnparam(struct tty *tp, struct termios *t);

#  else /* !defined(_USE_KERNEL_PROTOS) */

/* forward declaration required for C++ */
struct tty;

struct	cons_sw {
	int	(*c_open)();		/* console open			*/
	int	(*c_close)();		/* console close		*/
	int	(*c_read)();		/* console read			*/
	int	(*c_write)();		/* console write		*/
	int	(*c_ioctl)();		/* console ioctl		*/
	int	(*c_rint)();		/* console receiver int		*/
	int	(*c_xint)();		/* console transmitter int	*/
	int	(*c_start)();		/* console start		*/
	int	(*c_stop)();		/* console stop			*/
	int	(*c_select)();		/* console select		*/
	void	(*c_putc)();		/* console putc			*/
	int	(*c_probe)();		/* console probe		*/
	int	(*c_getc)();		/* console getc			*/
	int	(*c_init)();		/* console init routine		*/
	int	(*c_param)();		/* console parameter routine	*/
	int	(*c_mmap)();		/* console mmap routine		*/
	struct tty *ttys;		/* tty structure for select	*/
};

struct vcons_init_sw {
        char	modname[10];		/* module name	*/
	int	(*cons_init)();		/* virtual console init routine */
};

#  endif /* defined(_USE_KERNEL_PROTOS) */
#endif /* defined(_KERNEL) */

#ifdef __cplusplus
}
#endif
#endif /* _CONS_SW_H_ */
