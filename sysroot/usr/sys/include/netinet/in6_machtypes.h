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
 * @(#)$RCSfile: in6_machtypes.h,v $ $Revision: 1.1.7.1 $ (DEC) $Date: 2002/01/29 21:18:54 $
 */

#ifndef _NETINET_IN6_MACHTYPES_H
#define _NETINET_IN6_MACHTYPES_H

/*
 * Machine or architecure specific MACROS and types
 * for IPv6.
 */

#include <machine/endian.h>
#include <sys/bitypes.h>

#ifndef OPENVMS_32BIT
#ifdef __arch64__
#define	IN6_HAS_64BIT_INTTYPE
#endif /* __arch64__ */
#endif /* OPENVMS_32BIT */

#if !defined(BYTE_ORDER) || BYTE_ORDER == LITTLE_ENDIAN
#define	IN6_MSB16_SHIFT			0
#define	IN6_MSB32_SHIFT			0
#define	IN6_MSW32_SHIFT			0
#define	IN6_BIT_ORDER			+1
#ifdef IN6_HAS_64BIT_INTTYPE
#define	IN6_MSB64_SHIFT			0
#define	IN6_MSW64_SHIFT			0
#define	IN6_MSL64_SHIFT			0
#endif

#elif BYTE_ORDER == BIG_ENDIAN
#define	IN6_MSB16_SHIFT			(16 - 8)
#define	IN6_MSB32_SHIFT			(32 - 8)
#define	IN6_MSW32_SHIFT			(32 - 16)
#define	IN6_BIT_ORDER			-1
#ifdef IN6_HAS_64BIT_INTTYPE
#define	IN6_MSB64_SHIFT			(64 - 8)
#define	IN6_MSW64_SHIFT			(64 - 16)
#define	IN6_MSL64_SHIFT			(64 - 32)
#endif
#endif

#ifdef IN6_HAS_64BIT_INTTYPE
#define	IN6_MSB64_OFFSET(n)		(IN6_MSB64_SHIFT + ((n) * IN6_BIT_ORDER * 8))
#define	IN6_MSW64_OFFSET(n)		(IN6_MSB64_SHIFT + ((n) * IN6_BIT_ORDER * 16))
#define	IN6_MSL64_OFFSET(n)		(IN6_MSB64_SHIFT + ((n) * IN6_BIT_ORDER * 32))
#define	IN6_LSB64_SHIFT			IN6_MSB64_OFFSET(7)
#define	IN6_LSW64_SHIFT			IN6_MSW64_OFFSET(3)
#define	IN6_LSL64_SHIFT			IN6_MSL64_OFFSET(1)

#define	IN6__MK0_MSB64_VALUE(a)			( ((u_int64_t) (a)) << IN6_MSB64_OFFSET(0))
#define	IN6__MK1_MSB64_VALUE(a,b)		((((u_int64_t) (b)) << IN6_MSB64_OFFSET(1))|IN6__MK0_MSB64_VALUE(a))
#define	IN6__MK2_MSB64_VALUE(a,b,c)		((((u_int64_t) (c)) << IN6_MSB64_OFFSET(2))|IN6__MK1_MSB64_VALUE(a,b))
#define	IN6__MK3_MSB64_VALUE(a,b,c,d)		((((u_int64_t) (d)) << IN6_MSB64_OFFSET(3))|IN6__MK2_MSB64_VALUE(a,b,c))
#define	IN6__MK4_MSB64_VALUE(a,b,c,d,e)		((((u_int64_t) (e)) << IN6_MSB64_OFFSET(4))|IN6__MK3_MSB64_VALUE(a,b,c,d))
#define	IN6__MK5_MSB64_VALUE(a,b,c,d,e,f)	((((u_int64_t) (f)) << IN6_MSB64_OFFSET(5))|IN6__MK4_MSB64_VALUE(a,b,c,d,e))
#define	IN6__MK6_MSB64_VALUE(a,b,c,d,e,f,g)	((((u_int64_t) (g)) << IN6_MSB64_OFFSET(6))|IN6__MK5_MSB64_VALUE(a,b,c,d,e,f))
#define	IN6__MK7_MSB64_VALUE(a,b,c,d,e,f,g,h)	((((u_int64_t) (h)) << IN6_MSB64_OFFSET(7))|IN6__MK6_MSB64_VALUE(a,b,c,d,e,f,g))

#define	IN6__MK0_MSW64_VALUE(a)		( ((u_int64_t) (a)) << IN6_MSW64_OFFSET(0))
#define	IN6__MK1_MSW64_VALUE(a,b)	((((u_int64_t) (b)) << IN6_MSW64_OFFSET(1))|IN6__MK0_MSW64_VALUE(a))
#define	IN6__MK2_MSW64_VALUE(a,b,c)	((((u_int64_t) (c)) << IN6_MSW64_OFFSET(2))|IN6__MK1_MSW64_VALUE(a,b))
#define	IN6__MK3_MSW64_VALUE(a,b,c,d)	((((u_int64_t) (d)) << IN6_MSW64_OFFSET(3))|IN6__MK2_MSW64_VALUE(a,b,c))

#define	IN6__MK0_MSL64_VALUE(a)		( ((u_int64_t) (a)) << IN6_MSL64_OFFSET(0) )
#define	IN6__MK1_MSL64_VALUE(a,b)	((((u_int64_t) (b)) << IN6_MSL64_OFFSET(1))|IN6__MK0_MSL64_VALUE(a))
#endif

#define	IN6_MSB32_OFFSET(n)		(IN6_MSB32_SHIFT + ((n) * IN6_BIT_ORDER * 8))
#define	IN6_MSW32_OFFSET(n)		(IN6_MSB32_SHIFT + ((n) * IN6_BIT_ORDER * 16))
#define	IN6_LSB32_SHIFT			IN6_MSB32_OFFSET(3)
#define	IN6_LSW32_SHIFT			IN6_MSW32_OFFSET(1)

#define	IN6__MK0_MSB32_VALUE(a)		( ((u_int32_t) (a)) << IN6_MSB32_OFFSET(0) )
#define	IN6__MK1_MSB32_VALUE(a,b)	((((u_int32_t) (b)) << IN6_MSB32_OFFSET(1))|IN6__MK0_MSB32_VALUE(a))
#define	IN6__MK2_MSB32_VALUE(a,b,c)	((((u_int32_t) (c)) << IN6_MSB32_OFFSET(2))|IN6__MK1_MSB32_VALUE(a,b))
#define	IN6__MK3_MSB32_VALUE(a,b,c,d)	((((u_int32_t) (d)) << IN6_MSB32_OFFSET(3))|IN6__MK2_MSB32_VALUE(a,b,c))

#define	IN6__MK0_MSW32_VALUE(a)		(( (u_int32_t) (a)) << IN6_MSW32_OFFSET(0) )
#define	IN6__MK1_MSW32_VALUE(a,b)	((((u_int32_t) (b)) << IN6_MSW32_OFFSET(1))|IN6__MK0_MSW32_VALUE(a))

/*
 * Macros for 16 bit words.
 */

#define	IN6_MSB16_OFFSET(n)		(IN6_MSB16_SHIFT + ((n) * IN6_BIT_ORDER * 8))
#define	IN6_LSB16_SHIFT			IN6_MSB16_OFFSET(1)

#define	IN6__MK0_MSB16_VALUE(a)		( ((u_int16_t) (a)) << IN6_MSB16_OFFSET(0))
#define	IN6__MK1_MSB16_VALUE(a,b)	((((u_int16_t) (b)) << IN6_MSB16_OFFSET(1))|IN6__MK0_MSB16_VALUE(a))

#endif /* _NETINET_IN6_MACHTYPES_H */
