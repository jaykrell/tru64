/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mip6_hmac.h,v $
 * Revision 1.1.9.1  2003/09/23  22:00:42  Brian_Haley
 * 	Initial submission - Mobile IPv6.
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: mip6_hmac.h,v $ $Revision: 1.1.9.1 $ (DEC) $Date: 2003/09/23 22:00:42 $
 */

/*
 * Copyright (C) 2002 WIDE Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETINET_MIP6_HMAC_H_
#define _NETINET_MIP6_HMAC_H_

#include <netinet/in6_machtypes.h>

struct hmac_ctx;
struct hmac_hash {
	int ctx_size;
	int hash_resultlen;
	void (*init) (struct hmac_ctx *);
	void (*loop) (struct hmac_ctx *, u_int8_t *, u_int);
	void (*result) (struct hmac_ctx *, u_int8_t *);
};

struct hmac_ctx {
	u_int8_t	*key;
	int		keylen;
	void		*foo;	/* per algorithm data - maybe */
	void		*hash_ctx;
	struct hmac_hash	*hash;
};
typedef struct hmac_ctx	HMAC_CTX;


#if defined(KERNEL) || defined(_KERNEL)
extern struct hmac_hash hmac_hash[];
#define HMAC_SHA1	&hmac_hash[0]
#define HMAC_SHA1_SIZE	16

int hmac_init(HMAC_CTX *, u_int8_t *, int, struct hmac_hash *);
int hmac_loop(HMAC_CTX *, u_int8_t *, int);
int hmac_result(HMAC_CTX *, u_int8_t *addr);
void hmac_uninit(HMAC_CTX *);
#endif /* defined(KERNEL) || defined(_KERNEL) */

#endif /* _NETINET_MIP6_HMAC_H_ */
