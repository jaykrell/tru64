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
 * @(#)$RCSfile: io_access.h,v $ $Revision: 1.1.10.1 $ (DEC) $Date: 2000/09/26 17:54:16 $
 */

#include <sys/types.h>

/*
 * Define the alpha standard io alignment information for the copy routines
 */

#define	ASIO_WIDTH_SHIFT	3
#define	ASIO_WIDTH_MASK		0x18
#define	ASIO_IO_SHIFT		5
#define	ASIO_IO_STRIDE		0x80L
#define	ASIO_IO_BYTE_STRIDE	0x20L
#define	ASIO_IO_ALIGN_MASK	0xffffffffffffff9fL

/*
 * IO Space type defines.  Used as part of the common
 * io_blockxxx() routines.
 */

#define	ASIO_DENSE_SPACE		0UL
#define ASIO_SPARSE_MEM_SPACE		1UL
#define ASIO_SPARSE_IO_SPACE		2UL
#define ASIO_CONFIG_SPACE_TYPE_0	3UL
#define ASIO_CONFIG_SPACE_TYPE_1	4UL
#define ASIO_LINEAR_SPACE		5UL


/*
 * Common function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

int
common_swizzle_blockread(u_long, vm_offset_t, u_long, u_long);
int
common_swizzle_blockwrite(vm_offset_t, u_long, u_long, u_long);
int
common_swizzle_blockclear(u_long , u_long, u_long);
int
common_swizzle_blockexchange(u_long, u_long, u_long, u_long, u_long);

int
common_bw_blockread(u_long, vm_offset_t, u_long, u_long);
int
common_bw_blockwrite(vm_offset_t, u_long, u_long, u_long);
int
common_bw_blockclear(u_long, u_long, u_long);
int
common_bw_blockexchange(u_long, u_long, u_long, u_long, u_long);

int
common_pio_swizzle_blockread(u_long, vm_offset_t, u_long, u_long, u_long);
int
common_pio_swizzle_blockwrite(vm_offset_t, u_long, u_long, u_long, u_long);
int
common_pio_swizzle_blockclear(u_long, u_long, u_long, u_long);
int
common_pio_swizzle_blockexchange(u_long, u_long, u_long, u_long, u_long, u_long);

int
common_pio_bw_blockread(u_long, vm_offset_t, u_long, u_long, u_long);
int
common_pio_bw_blockwrite(vm_offset_t, u_long, u_long, u_long, u_long);
int
common_pio_bw_blockclear(u_long, u_long, u_long, u_long);
int
common_pio_bw_blockexchange(u_long, u_long, u_long, u_long, u_long, u_long);

#ifdef __cplusplus
}
#endif

/******************************************************************************
 *                                                                        
 * MACRO NAME:  COMMON_READ_IO_PORT()
 * 
 * SYNOPSIS
 *    COMMON_READ_IO_PORT(crio_trans_addr, crio_width, crio_space_type)
 * 
 *    u_long crio_trans_address;
 *    int crio_width;
 *    int crio_space_type;
 * 
 * PARAMETERS
 *    crio_trans_addr	target address to read
 *    crio_width		The size of read:
 *				1 = byte
 *				2 = word
 *				3 = tri-byte
 *				4 = longword
 *				8 = quadword
 *
 *    crio_space_type	space type:
 *				0 = Dense mem
 *				1 = Sparse mem
 *				2 = Sparse I/O
 *				3 = Type 0 config
 *				4 = Type 1 config
 *
 *    crio_ret_data	The return data
 *
 * FUNCTIONAL DESCRIPTION:  
 *    Perform a read from the target address.
 *    Note:  NO LENGTH CHECKS! This code needs to be fast.
 *
 *
 ****************************************************************************/

#define COMMON_READ_IO_PORT(crio_trans_addr, crio_width, crio_space_type, crio_ret_data) \
{ \
 \
    if (crio_space_type) \
    { \
/* \
 * Sparse type access (either io, mem, or config) \
 */ \
	if ( crio_width <= 4 ) \
	{ \
/* \
 * Byte, Word, Tri-byte, Longword case \
 * (Use pointer typecast of u_int to generate ldl instruction) \
 */ \
	    crio_ret_data = ((u_long) ((*(unsigned int *)PHYS_TO_KSEG( \
			(crio_trans_addr |  \
			((crio_width - 1) << ASIO_WIDTH_SHIFT)) )) >> \
			(((crio_trans_addr >> ASIO_IO_SHIFT) & \
			(4 - crio_width)) << 3)) & \
			((1L << (((u_long)crio_width) * 8)) - 1)); \
	} \
	else \
	{ \
/* \
 * Quadword \
 * (Use pointer typecast of u_long to generate ldq instruction) \
 */ \
	    crio_ret_data = *(unsigned long *)PHYS_TO_KSEG( \
			(crio_trans_addr | \
			(0xf << ASIO_WIDTH_SHIFT)) ); \
	}	     \
    } \
    else \
    { \
/* \
 * Dense type access  \
 */ \
	if (crio_width == 8) \
	    crio_ret_data = *(unsigned long *)PHYS_TO_KSEG( (crio_trans_addr) ); \
	else \
	    crio_ret_data =  (u_long) ((*(unsigned int *)PHYS_TO_KSEG( \
			(crio_trans_addr) )) & 0xffffffff ); \
    } \
}

/******************************************************************************
 *                                                                        
 * MACRO NAME:  COMMON_WRITE_IO_PORT()
 * 
 * SYNOPSIS
 *    COMMON_WRITE_IO_PORT(crio_trans_addr, crio_width, crio_space_type, crio_data)
 * 
 *    crio_trans_address;
 *    crio_width;
 *    crio_space_type;
 *    crio_data;
 * 
 * PARAMETERS
 *    crio_trans_addr	target address to write
 *    crio_width		The size of the write:
 *				1 = byte
 *				2 = word
 *				3 = tri-byte
 *				4 = longword
 *				8 = quadword
 *
 *    crio_space_type	space type:
 *				0 = Dense mem
 *				1 = Sparse mem
 *				2 = Sparse I/O
 *				3 = Type 0 config
 *				4 = Type 1 config
 *
 *    crio_data		The data to write
 * 
 * FUNCTIONAL DESCRIPTION:  
 *    Perform a write to the target address
 *    Note:  NO LENGTH CHECKS! This code needs to be fast.
 *
 *
 ****************************************************************************/

#define COMMON_WRITE_IO_PORT(crio_trans_addr, crio_width, crio_space_type, \
			    crio_data) \
{ \
    if (crio_space_type) \
    { \
	if ( crio_width <= 4 ) \
	{ \
/* \
 * Byte, Word, Tri-byte, Longword case \
 * (Use pointer typecast of u_int to generate ldl instruction) \
 */ \
	    *(unsigned int *)PHYS_TO_KSEG( (crio_trans_addr |  \
			((crio_width - 1) << ASIO_WIDTH_SHIFT)) ) = \
			(crio_data & ((1L << (((u_long)crio_width) * 8)) - 1)) <<  \
			(((crio_trans_addr >> ASIO_IO_SHIFT) & \
			(4 - crio_width)) << 3); \
	} \
	else \
	{ \
/* \
 * Quadword \
 * (Use pointer typecast of u_long to generate ldq instruction) \
 */ \
	    *(unsigned long *)PHYS_TO_KSEG( (crio_trans_addr | \
			(0xf << ASIO_WIDTH_SHIFT)) ) = \
			crio_data; \
	} \
    } \
    else \
    { \
/* \
 * Dense type access  \
 */ \
	if (crio_width == 8) \
	    *(unsigned long *)PHYS_TO_KSEG( (crio_trans_addr) ) = crio_data; \
	else \
	    *(unsigned int *)PHYS_TO_KSEG( (crio_trans_addr) ) =  \
			crio_data & 0xffffffff; \
    } \
}







