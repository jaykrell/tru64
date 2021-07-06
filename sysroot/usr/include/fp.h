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
 *	@(#)$RCSfile: fp.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1997/12/12 17:13:55 $
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
#ifndef _FP_H_
#define _FP_H_

#include <machine/endian.h>


/****************************************************************************/
/*                      Long Double Precision                               */
/****************************************************************************/

/* The following are provided for backward and 32-bit compatability only. */

#define LVALH(__val) (((unsigned int *)&__val)[3-3*(BYTE_ORDER==BIG_ENDIAN)])
#define LVALL(__val) (((unsigned int *)&__val)[0+3*(BYTE_ORDER==BIG_ENDIAN)])
#define LVALMH(__val) (((unsigned int *)&__val)[2-1*(BYTE_ORDER==BIG_ENDIAN)])
#define LVALML(__val) (((unsigned int *)&__val)[1+1*(BYTE_ORDER==BIG_ENDIAN)])

/* The following are for 64-bit architectures. */

#define	_LVALH(__val)	(((unsigned long *)&__val)[1])
#define	_LVALL(__val)	(((unsigned long *)&__val)[0])

/*
 *      FINITEL(x)
 *
 *      Is true if long double x is finite (Not NaN or INF).
 *
 *      This macro is similar to the finitel(x) function in the IEEE
 *      standard except it is not a function. 
 *	x must be a simple variable and not an expresion.
 */

#define FINITEL(__x)	((_LVALH(__x) & 0x7fff000000000000L) != 0x7fff000000000000L)

/*
 *      IS_INFL(x)
 *
 *      Is true if double x is +INF or -INF.
 *      x must be a simple variable and not an expression.
 */

#define IS_INFL(__x) \
	(((_LVALH(__x) & 0x7fffffffffffffffL) == 0x7fff000000000000L) && \
		(_LVALL(__x) == 0L))

/*
 *      IS_QNANL(x)
 *
 *      Is true if double x is a Quiet NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_QNANL(__x) \
	((_LVALH(__x) & 0x7fff800000000000L) == 0x7fff800000000000L)

/*
 *      IS_SNANL(x)
 *
 *      Is true if double x is a Signaling NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_SNANL(__x) \
	(((_LVALH(__x) & 0x7fff800000000000L) == 0x7fff000000000000L) && \
		((_LVALH(__x) & 0x00007fffffffffffL) || _LVALL(__x)))
  
/*
 *      IS_NANL(x)
 *
 *      Is true if double x is any NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_NANL(__x) \
	(((_LVALH(__x) & 0x7fff000000000000L) == 0x7fff000000000000L) && \
		((_LVALH(__x) & 0x0000ffffffffffffL) || _LVALL(__x)))

#if BYTE_ORDER == BIG_ENDIAN
#	define	INTS2LDBL(w,x,y,z)	(w),(x),(y),(z)
#else
#	define	INTS2LDBL(w,x,y,z)	(z),(y),(x),(w)
#endif /* BYTE_ORDER==BIG_ENDIAN */



/****************************************************************************/
/*                      Double Precision                                    */
/****************************************************************************/

/*
 *      VALH(val)
 *
 *      Return the hipart of the double value of val as an unsigned integer.
 *      val must be a simple variable that can have its address taken.
 */

#define VALH(val) *((unsigned int *)&(val) + (BYTE_ORDER!=BIG_ENDIAN))


/*
 *      VALL(val)
 *
 *      Return the lopart of the double value of val as an unsigned integer.
 *      val must be a simple variable that can have its address taken.
 */

#define VALL(val) *(((unsigned int *)&(val))+(BYTE_ORDER==BIG_ENDIAN))

/*
 *      DBL(val,hi,lo)
 *
 *      The hi word of the double variable val is set to hi and
 *      the lo word of the double variable val is set to lo.
 *
 *      val must be a simple variable.
 */

#define DBL(val,hi,lo)	\
{			\
	VALH(val) = hi;	\
	VALL(val) = lo;	\
}

/*
 *      FINITE(x)
 *
 *      Is true if double x is finite (Not NaN or INF).
 *
 *      This macro is similar to the finite(x) function in the IEEE
 *      standard except it is not a function. 
 *	x must be a simple variable and not an expresion.
 */

#define FINITE(x)	( ( VALH(x) & 0x7ff00000 ) != 0x7ff00000 )

/*
 *      IS_INF(x)
 *
 *      Is true if double x is +INF or -INF.
 *      x must be a simple variable and not an expression.
 */

#define IS_INF(x) \
	( ( ( VALH(x) & 0x7fffffff ) == 0x7ff00000 ) && \
		( VALL(x) == 0 ) )

/*
 *      IS_QNAN(x)
 *
 *      Is true if double x is a Quiet NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_QNAN(x) \
	( ( VALH(x) & 0x7ff80000 ) == 0x7ff80000 )

/*
 *      IS_SNAN(x)
 *
 *      Is true if double x is a Signaling NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_SNAN(x) \
	( IS_NAN(x) && !IS_QNAN(x))
  
/*
 *      IS_NAN(x)
 *
 *      Is true if double x is any NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_NAN(x) \
	( ( ( VALH(x) & 0x7ff00000 ) == 0x7ff00000 ) && \
		( ( VALH(x) & 0x000fffff) | VALL(x) ) )

/*
 *      IS_ZERO(x)
 *
 *      Is true if double x is +0 or -0.
 *      x must be a simple variable and not an expression.
 */

#define IS_ZERO(x) \
	( !( ( VALH(x) & 0x7fffffff ) | VALL(x) ) )


/*
 *      IS_DENORMAL(x)
 *
 *      Is true if double x is a IEEE denormal
 *      x must be a simple variable and not an expression.
 */

#define IS_DENORMAL(x) \
	(  !( VALH(x) & 0x7ff00000 ) && ( (VALH(x) & 0x000fffff) | VALL(x)) )



/*
 *  INTS2DBL(x,y)
 *
 *  Put two unsigned long integers into IEEE double format for the
 *  current machine architecture.
 */
#if BYTE_ORDER == BIG_ENDIAN
#	define	INTS2DBL(x,y)	(x),(y)
#else
#	define	INTS2DBL(x,y)	(y),(x)
#endif /* BYTE_ORDER==BIG_ENDIAN */




/****************************************************************************/
/*                      Single Precision                                    */
/****************************************************************************/


/*
 *      SPVAL(val)
 *
 *      Return the float value of val as an unsigned integer.
 *      val must be a simple variable that can have its address taken.
 */

#define SPVAL(val) *((unsigned int *)&(val))


/*
 *      SNGL(val,hi)
 *
 *      The hi word of the single-precision variable val is set to hi and
 *
 *      val must be a simple variable.
 */
#define SNGL(val,hi) SPVAL(val) = hi


/*
 *      SPFINITE(x)
 *
 *      Is true if float x is finite (Not NaN or INF).
 *
 *      This macro is similar to the finite(x) function in the IEEE
 *      standard except it is not a function. 
 *	x must be a simple variable and not an expresion.
 */

#define SPFINITE(x)	( ( SPVAL(x) & 0x7f800000 ) != 0x7f800000 )

/*
 *      IS_SPINF(x)
 *
 *      Is true if float x is +INF or -INF.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPINF(x) \
	( ( SPVAL(x) & 0x7fffffff ) == 0x7f800000 )
		 

/*
 *      IS_SPQNAN(x)
 *
 *      Is true if float x is a Quiet NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPQNAN(x) \
	( ( SPVAL(x) & 0x7fc00000 ) == 0x7fc00000 )

/*
 *      IS_SPSNAN(x)
 *
 *      Is true if float x is a Signaling NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPSNAN(x) \
	( IS_SPNAN(x) && !IS_SPQNAN(x))
  
/*
 *      IS_SPNAN(x)
 *
 *      Is true if float x is any NaN.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPNAN(x) \
	( ((SPVAL(x) & 0x7f800000 ) == 0x7f800000) &&  (SPVAL(x) & 0x007fffff)  )

/*
 *      IS_SPDENORMAL(x)
 *
 *      Is true if integer x, viewed as a single-precision floating-point number,  is a IEEE denormal;
 *      This is true if the exponent is zero, and the mantissa is not.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPDENORMAL(x) \
	(  !( SPVAL(x) & 0x7f800000) &&  (SPVAL(x) & 0x007fffff)  )

/*
 *      IS_SPZERO(x)
 *
 *      Is true if float x is +0 or -0.
 *      x must be a simple variable and not an expression.
 */

#define IS_SPZERO(x) \
	( ! ( SPVAL(x) & 0x7fffffff )  )


#endif /* _FP_H_ */
