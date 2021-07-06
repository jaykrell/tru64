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
 *	"@(#)endian.h	9.1	(ULTRIX/OSF)	10/21/91"
 */ 
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
/************************************************************************
 *			Modification History: alpha/endian.h
 *
 *  28-May-91	afd
 *	Created this file for Alpha/OSF support
 *
 ************************************************************************/

#ifndef	_MACHINE_ENDIAN_H_
#define _MACHINE_ENDIAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

/* MIPS may use either endian, compiler tells us which. */
#define	BYTE_ORDER	LITTLE_ENDIAN


#endif /* !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE) */

/*
 * Macros for network/external number representation conversion.
 */
#ifdef _KERNEL
extern unsigned short	nuxi_16(unsigned short);
extern unsigned int	nuxi_32(unsigned int);
#define	ntohl(x)	nuxi_32(x)
#define	ntohs(x)	nuxi_16(x)
#define	htonl(x)	nuxi_32(x)
#define	htons(x)	nuxi_16(x)
#define NTOHL(x)	(x) = ntohl((u_int)x)
#define NTOHS(x)	(x) = ntohs((u_short)x)

#if defined(_USE_KERNEL_INTRINSICS)
#pragma linkage nuxi_linkage = \
  (preserved(r2,r3,r4,r5,r6,r7,r8,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25))
#pragma use_linkage nuxi_linkage(nuxi_16)
#pragma use_linkage nuxi_linkage(nuxi_32)
#endif

#else /* !_KERNEL */

#ifdef _XOPEN_SOURCE_EXTENDED
#if _XOPEN_SOURCE>=500
#include <inttypes.h>
extern uint16_t	ntohs(uint16_t), htons(uint16_t);
extern uint32_t	ntohl(uint32_t), htonl(uint32_t);
#else /* !_XOPEN_SOURCE>= 500 */
#include <sys/types.h>
extern in_port_t	ntohs(in_port_t), htons(in_port_t);
extern in_addr_t	ntohl(in_addr_t), htonl(in_addr_t);
#endif /* _XOPEN_SOURCE>= 500 */
#else /* !_XOPEN_SOURCE_EXTENDED */
extern unsigned short	ntohs(unsigned short), htons(unsigned short);
extern unsigned int	ntohl(unsigned int), htonl(unsigned int);
#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* !_KERNEL */

#ifdef __cplusplus
}
#endif
#endif
