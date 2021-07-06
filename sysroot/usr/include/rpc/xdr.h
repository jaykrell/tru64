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
 *	@(#)$RCSfile: xdr.h,v $ $Revision: 4.2.13.6 $ (DEC) $Date: 1998/11/02 16:29:36 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */


/*
 * xdr.h, External Data Representation Serialization Routines.
 */

#ifndef _rpc_xdr_h
#define	_rpc_xdr_h

#include <standards.h>
#ifdef	KERNEL
#include "../rpc/types.h"
#else
#include <rpc/types.h>
#include <stdio.h>
#endif
/*
 * XDR provides a conventional way for converting between C data
 * types and an external bit-string representation.  Library supplied
 * routines provide for the conversion on built-in C data types.  These
 * routines and utility routines defined here are used to help implement
 * a type encode/decode routine for each user-defined type.
 *
 * Each data type provides a single procedure which takes two arguments:
 *
 *	bool_t
 *	xdrproc(xdrs, argresp)
 *		XDR *xdrs;
 *		<type> *argresp;
 *
 * xdrs is an instance of a XDR handle, to which or from which the data
 * type is to be converted.  argresp is a pointer to the structure to be
 * converted.  The XDR handle contains an operation field which indicates
 * which of the operations (ENCODE, DECODE * or FREE) is to be performed.
 *
 * XDR_DECODE may allocate space if the pointer argresp is null.  This
 * data can be freed with the XDR_FREE operation.
 *
 * We write only one procedure per data type to make it easy
 * to keep the encode and decode procedures for a data type consistent.
 * In many cases the same code performs all operations on a user defined type,
 * because all the hard work is done in the component type routines.
 * decode as a series of calls on the nested data types.
 */

/*
 * Xdr operations.  XDR_ENCODE causes the type to be encoded into the
 * stream.  XDR_DECODE causes the type to be extracted from the stream.
 * XDR_FREE can be used to release the space allocated by an XDR_DECODE
 * request.
 */
enum xdr_op {
	XDR_ENCODE=0,
	XDR_DECODE=1,
	XDR_FREE=2
};

/*
 * This is the number of bytes per unit of external data.
 */
#define BYTES_PER_XDR_UNIT	(4)
#define RNDUP(x)  ((((x) + BYTES_PER_XDR_UNIT - 1) / BYTES_PER_XDR_UNIT) \
		    * BYTES_PER_XDR_UNIT)

/*
 * The XDR handle.
 * Contains operation which is being applied to the stream,
 * an operations vector for the paticular implementation (e.g. see xdr_mem.c),
 * and two private fields for the use of the particular impelementation.
 */
typedef struct XDR {
	enum xdr_op	x_op;		/* operation; fast additional param */
	struct xdr_ops {
		bool_t	(*x_getlong) __((struct XDR *,  int *));	/* get an int from underlying stream */
		bool_t	(*x_putlong) __((struct XDR *,  int *));	/* put an int to " */
		bool_t	(*x_getbytes) __((struct XDR *, caddr_t, int));	/* get some bytes from " */
		bool_t	(*x_putbytes) __((struct XDR *, caddr_t, int));	/* put some bytes to " */
		u_int	(*x_getpostn) __((struct XDR *));		/* returns bytes off from beginning */
		bool_t  (*x_setpostn) __((struct XDR *, u_int));	/* lets you reposition the stream */
		int *	(*x_inline) __((struct XDR *, int));		/* buf quick ptr to buffered data */
		void	(*x_destroy) __((struct XDR *));		/* free privates of this xdr_stream */
	} *x_ops;
	caddr_t 	x_public;	/* users' data */
	caddr_t		x_private;	/* pointer to private data */
	caddr_t 	x_base;		/* private used for position info */
	int		x_handy;	/* extra private word */
} XDR;

/*
 * A xdrproc_t exists for each data type which is to be encoded or decoded.
 *
 * The second argument to the xdrproc_t is a pointer to an opaque pointer.
 * The opaque pointer generally points to a structure of the data type
 * to be decoded.  If this pointer is 0, then the type routines should
 * allocate dynamic storage of the appropriate size and return it.
 * bool_t	(*xdrproc_t)(XDR *, caddr_t *);
 */

#ifdef __cplusplus
#ifdef __V40_OBJ_COMPAT
typedef bool_t (*xdrproc_t) (XDR *, caddr_t *, ...);
#else
typedef bool_t (*xdrproc_t) (XDR *, void *);
#endif
#else
/* No prototype. */
typedef bool_t (*xdrproc_t) ();
#endif


/*
 * Operations defined on a XDR handle
 *
 * XDR		*xdrs;
 * int		*longp;
 * caddr_t	 addr;
 * u_int	 len;
 * u_int	 pos;
 */
#define XDR_GETLONG(xdrs, intp)				\
	(*(xdrs)->x_ops->x_getlong)(xdrs, intp)
#define xdr_getlong(xdrs, intp)				\
	(*(xdrs)->x_ops->x_getlong)(xdrs, intp)

#define XDR_PUTLONG(xdrs, intp)				\
	(*(xdrs)->x_ops->x_putlong)(xdrs, intp)
#define xdr_putlong(xdrs, intp)				\
	(*(xdrs)->x_ops->x_putlong)(xdrs, intp)

#define XDR_GETBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)
#define xdr_getbytes(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_getbytes)(xdrs, addr, len)

#define XDR_PUTBYTES(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)
#define xdr_putbytes(xdrs, addr, len)			\
	(*(xdrs)->x_ops->x_putbytes)(xdrs, addr, len)

#define XDR_GETPOS(xdrs)				\
	(*(xdrs)->x_ops->x_getpostn)(xdrs)
#define xdr_getpos(xdrs)				\
	(*(xdrs)->x_ops->x_getpostn)(xdrs)

#define XDR_SETPOS(xdrs, pos)				\
	(*(xdrs)->x_ops->x_setpostn)(xdrs, pos)
#define xdr_setpos(xdrs, pos)				\
	(*(xdrs)->x_ops->x_setpostn)(xdrs, pos)

#define	XDR_INLINE(xdrs, len)				\
	(*(xdrs)->x_ops->x_inline)(xdrs, len)
#define	xdr_inline(xdrs, len)				\
	(*(xdrs)->x_ops->x_inline)(xdrs, len)

/* 
 * nsd did this 
#define	XDR_DESTROY(xdrs)				\
	(*(xdrs)->x_ops->x_destroy)(xdrs)
*/
#define	XDR_DESTROY(xdrs)				\
	( * (void (*) (XDR *)) ((xdrs)->x_ops->x_destroy))(xdrs)
#define	xdr_destroy(xdrs) XDR_DESTROY(xdrs)

/*
 * Support struct for discriminated unions.
 * You create an array of xdrdiscrim structures, terminated with
 * a entry with a null procedure pointer.  The xdr_union routine gets
 * the discriminant value and then searches the array of structures
 * for a matching value.  If a match is found the associated xdr routine
 * is called to handle that part of the union.  If there is
 * no match, then a default routine may be called.
 * If there is no match and no default routine it is an error.
 */
#define NULL_xdrproc_t ((xdrproc_t)0)
struct xdr_discrim {
	int	value;
	xdrproc_t proc;
};

/*
 * In-line routines for fast encode/decode of primitve data types.
 * Caveat emptor: these use single memory cycles to get the
 * data from the underlying buffer, and will fail to operate
 * properly if the data is not aligned.  The standard way to use these
 * is to say:
 *	if ((buf = XDR_INLINE(xdrs, count)) == NULL)
 *		return (FALSE);
 *	<<< macro calls >>>
 * where ``count'' is the number of bytes of data occupied
 * by the primitive data types.
 *
 * N.B. and frozen for all time: each data type here uses 4 bytes
 * of external representation.
 */
#define IXDR_GET_LONG(buf)		((int)ntohl((u_int)*(buf)++))
#define IXDR_PUT_LONG(buf, v)		(*(buf)++ = (int)htonl((u_int)v))

#define IXDR_GET_BOOL(buf)		((bool_t)IXDR_GET_LONG(buf))
#define IXDR_GET_ENUM(buf, t)		((t)IXDR_GET_LONG(buf))
#define IXDR_GET_U_LONG(buf)		((u_int)IXDR_GET_LONG(buf))
#define IXDR_GET_SHORT(buf)		((short)IXDR_GET_LONG(buf))
#define IXDR_GET_U_SHORT(buf)		((u_short)IXDR_GET_LONG(buf))

#define IXDR_PUT_BOOL(buf, v)		IXDR_PUT_LONG((buf), ((int)(v)))
#define IXDR_PUT_ENUM(buf, v)		IXDR_PUT_LONG((buf), ((int)(v)))
#define IXDR_PUT_U_LONG(buf, v)		IXDR_PUT_LONG((buf), ((int)(v)))
#define IXDR_PUT_SHORT(buf, v)		IXDR_PUT_LONG((buf), ((int)(v)))
#define IXDR_PUT_U_SHORT(buf, v)	IXDR_PUT_LONG((buf), ((int)(v)))

/*
 * These are the "generic" xdr routines.
 */
_BEGIN_CPLUSPLUS
extern bool_t	xdr_void ();
extern bool_t	xdr_int __((XDR *, int *));
extern bool_t	xdr_u_int __((XDR *, unsigned int *));
extern bool_t	xdr_long __((XDR *, long *));
extern bool_t	xdr_u_long __((XDR *, unsigned long *));
extern bool_t	xdr_short __((XDR *, short *));
extern bool_t	xdr_u_short __((XDR *, unsigned short *));
extern bool_t	xdr_bool __((XDR *, bool_t *));
extern bool_t	xdr_enum __((XDR *, enum_t *));
extern bool_t	xdr_array __((XDR *, char **, u_int *, u_int, u_int, xdrproc_t));
extern bool_t	xdr_bytes __((XDR *, char **, u_int *, u_int));
extern bool_t	xdr_opaque __((XDR *, caddr_t, u_int));
	/* Forward reference; full structure definition is in auth.h */
struct opaque_auth;
extern bool_t	xdr_opaque_auth __((XDR *, struct opaque_auth *));
extern bool_t	xdr_string __((XDR *, char **, u_int));
extern bool_t	xdr_union __((XDR *, int *, char *, struct xdr_discrim *, bool_t (*) ()));
extern bool_t	xdr_longlong_t __((XDR *, longlong_t *));
extern bool_t	xdr_u_longlong_t __((XDR *,u_longlong_t * ));
extern bool_t	xdr_hyper __((XDR *, longlong_t *));
extern bool_t	xdr_u_hyper __((XDR *, u_longlong_t *));
#ifndef KERNEL
extern void	xdr_free __((xdrproc_t, char *));
extern bool_t	xdr_char __((XDR *, char * ));
extern bool_t	xdr_u_char __((XDR *, unsigned char *));
extern bool_t	xdr_vector __((XDR *, char *, u_int, u_int, xdrproc_t));
extern bool_t	xdr_float __((XDR *, float *));
extern bool_t	xdr_double __((XDR *, double *));
extern bool_t	xdr_reference __((XDR *, char **, u_int, xdrproc_t));
extern bool_t	xdr_pointer __((XDR *, char **, u_int, xdrproc_t));
extern bool_t	xdr_wrapstring __((XDR *, char * * ));
#endif /* !KERNEL */
_END_CPLUSPLUS

/*
 * Common opaque bytes objects used by many rpc protocols;
 * declared here due to commonality.
 */
#define MAX_NETOBJ_SZ 1024 
struct netobj {
	u_int	n_len;
	char	*n_bytes;
};
typedef struct netobj netobj;

_BEGIN_CPLUSPLUS
extern bool_t   xdr_netobj __((XDR *, struct netobj *));

/*
 * These are the public routines for the various implementations of
 * xdr streams.
 */
extern void   xdrmem_create __((XDR*, char*, u_int, enum xdr_op));	/* XDR using memory buffers */
#ifndef KERNEL
extern void   xdrstdio_create __((XDR*, FILE*, enum xdr_op));	/* XDR using stdio library */
extern void   xdrrec_create __((XDR *, u_int, u_int, char *, int (*) (),int (*) () ));		/* XDR pseudo records for tcp */
extern bool_t xdrrec_endofrecord __((XDR *,int));	/* make end of xdr record */
extern bool_t xdrrec_skiprecord __((XDR *));	/* move to beginning of next record */
extern bool_t xdrrec_eof __((XDR *));		/* true if no more input */
#else
extern void xdrmbuf_init __((XDR *, struct mbuf *, enum xdr_op));		/* XDR using kernel mbufs */
#endif /* !KERNEL */
_END_CPLUSPLUS

#endif /*!_rpc_xdr_h*/
