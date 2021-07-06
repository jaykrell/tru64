/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mip6_random.h,v $
 * Revision 1.1.9.1  2003/09/23  22:00:46  Brian_Haley
 * 	Initial submission - Mobile IPv6.
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: mip6_random.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2003/09/23 22:00:46 $
 */

#ifndef _NETINET_MIP6_RANDOM_H_
#define _NETINET_MIP6_RANDOM_H_

#include <sys/types.h>
#include <netinet/mip6_rrsec.h>

#ifdef __cplusplus
extern "C" {
#endif

/* define constants for MT11213A */
#define C		29943829
#define N		351
#define M		175
#define R		19
#define MATRIX_A	0xEABD75F5U
#define TEMU		11
#define TEMS		7
#define TEMT		15
#define TEML		17
#define TEMB		0x655E5280U
#define TEMC		0xFFD58000U

void		mip6_random_init();
uint64_t        mip6_random_64();             /* get 64 random bits */
void		mip6_random_key(mip6_key_t *);   /* random key */

#ifdef __cplusplus
};
#endif

#endif /* _NETINET_MIP6_RANDOM_H_ */
