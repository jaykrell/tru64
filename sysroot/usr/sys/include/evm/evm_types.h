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
 * @(#)$RCSfile: evm_types.h,v $ $Revision: 1.1.15.1 $ (DEC) $Date: 2001/09/26 18:57:12 $
 */
#ifndef	__EVM_TYPES_H__
#define	__EVM_TYPES_H__

/******************* System include files */

#include <sys/types.h> /* pid_t */

/* Can only pull in float.h in user space. */
#ifndef _KERNEL
#include <float.h> /* EVM_FLOAT_MIN, _MAX, EVM_DOUBLE_MIN, _MAX */
#endif

/******************* Application specific include files - NONE */

/******************* Global data - NONE */




/******************* Datatypes */
/******************* Constant parameters */
/******************* Macros */

/*
 * Basic types, defined by EVM for ease of portability
 */

#ifdef __arch64__

typedef	short		EvmInt16_t;
typedef	int		EvmInt32_t;
typedef	long		EvmInt64_t;
typedef	unsigned short	EvmUint16_t;
typedef	unsigned int	EvmUint32_t;
typedef	unsigned long	EvmUint64_t;

#else

typedef	short		EvmInt16_t;
typedef	int		EvmInt32_t;
typedef	unsigned short	EvmUint16_t;
typedef	unsigned int	EvmUint32_t;

/* Define 64 bit datatypes as arrays of 32 bit numbers  */
typedef signed long long EvmInt64_t;
typedef unsigned long long EvmUint64_t;

#endif /* __arch64__ */

#ifdef LINUX
#include <evm/evm_linux.h>
#endif /* LINUX */

typedef	char		EvmChar_t;
typedef	unsigned char	EvmUint8_t;
typedef	float		EvmFloat_t;
typedef	double		EvmDouble_t;
typedef pid_t		EvmPid_t;
typedef	void		*EvmOpaque_t;
typedef	void		*EvmPointer_t;

/* Define boolean datatype as an enumerated type */
typedef	enum	EvmBoolean_e
{
	EvmFALSE = 0,
	EvmTRUE = 1
} EvmBoolean_t;

#define EVM_INT8_MIN	SCHAR_MIN
#define EVM_INT8_MAX	SCHAR_MAX
#define EVM_INT16_MIN	SHRT_MIN
#define EVM_INT16_MAX	SHRT_MAX
#define EVM_INT32_MIN	INT_MIN
#define EVM_INT32_MAX	INT_MAX
#define EVM_INT64_MIN	LONG_MIN
#define EVM_INT64_MAX	LONG_MAX
#define EVM_UINT8_MAX	UCHAR_MAX
#define EVM_UINT16_MAX	USHRT_MAX
#define EVM_UINT32_MAX	UINT_MAX
#define EVM_UINT64_MAX	ULONG_MAX
#define EVM_FLOAT_MIN	FLT_MIN
#define EVM_FLOAT_MAX	FLT_MAX
#define EVM_DOUBLE_MIN	DBL_MIN
#define EVM_DOUBLE_MAX	DBL_MAX

#endif	/* __EVM_TYPES_H__ */
