/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: sgtty.h,v $
 * Revision 4.2.6.1  2002/12/18  20:01:04  Thomas_Peterson
 * 	Added explicit 'int' retyrn type to decls for gtty()
 * 	and stty()  (QAR # 93013).
 *
 * Revision 4.2.4.1  2001/09/11  15:17:05  Thomas_Peterson
 * 	Backport from wildcatos (wildcatos-532-bja).
 * 	Revision 4.2.2.1  2001/02/08  18:45:42  Barry_Andreasen
 * 	Add prototypes for stty and gtty() (QAR 85183)
 *
 * Revision 4.2  1991/09/20  05:18:50  devbld
 * Adding ODE Headers
 *
 * $EndLog$
 */
/*	
 *	@(#)$RCSfile: sgtty.h,v $ $Revision: 4.2.6.1 $ (DEC) $Date: 2002/12/18 20:01:04 $
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
/*	sgtty.h	4.2	85/01/03	*/

#ifndef _SGTTY_H_
#define _SGTTY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/ioctl.h>

extern int gtty __((int, struct sgttyb *));
extern int stty __((int, struct sgttyb *));

#ifdef __cplusplus
}
#endif
#endif /* _SGTTY_H_ */
