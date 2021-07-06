/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: xdr.h,v $
 * Revision 1.1.28.1  2003/09/11  18:34:37  Paul_Park
 * 	QAR 96804: Add xdrmbuf_putbuf_cksum and xdrmbuf_putopaque_checksum
 * 	to support page checksums.
 *
 * Revision 1.1.24.1  2002/06/06  14:23:09  Eric_Werme
 * 	Add new field to xdrrecmbuf_send() call needed by client.  (QAR 81879)
 *
 * Revision 1.1.18.2  2000/06/26  15:01:03  Eric_Werme
 * 	Add prototype for xdrmbuf_discard().
 *
 * Revision 1.1.18.1  2000/05/09  21:07:55  Eric_Werme
 * 	Add prototype for xdrmbuf_finish().
 *
 * Revision 1.1.12.4  1999/03/16  10:00:32  John_Carr
 * 	Add prototypes.
 * 	[1999/03/11  18:58:18  John_Carr]
 *
 * Revision 1.1.12.3  1999/01/19  19:39:46  Eric_Werme
 * 	Merge PtFC BL3: Rev 1.1.15.2
 * 	[1999/01/16  20:38:35  Eric_Werme]
 * 
 * Revision 1.1.15.2  1998/09/25  14:48:08  Eric_Werme
 * 	Add prototype for xdrmbuf_putopaque(). (QAR 62581)
 * 	[1998/09/21  21:16:53  Eric_Werme]
 * 
 * Revision 1.1.12.2  1997/01/15  21:34:47  Carolyn_Hurley
 * 	Changed arguments to xdrmbuf_putbuf(). Support
 * 	for 32K read/write server enhancements.  (QAR 49053)
 * 	[1997/01/14  16:30:36  Carolyn_Hurley]
 * 
 * Revision 1.1.10.3  1995/10/30  19:54:10  Eric_Werme
 * 	Optimize replies with a single record.  (QAR 38501)
 * 	[1995/10/30  17:33:16  Eric_Werme]
 * 
 * Revision 1.1.10.2  1995/04/24  21:06:30  Eric_Werme
 * 	Add prototypes for xdr_mbuf.c routines.
 * 	[1995/04/24  18:27:02  Eric_Werme]
 * 
 * Revision 1.1.8.4  1993/11/04  21:15:52  Timothy_Burke
 * 	Sterling BL7 to gold merge.
 * 	[1993/11/04  20:00:49  Timothy_Burke]
 * 
 * Revision 1.1.5.3  1993/10/06  13:51:53  Peter_S_Thompson
 * 	Make #endif statements ANSI compliant
 * 	[1993/09/30  17:20:14  Peter_S_Thompson]
 * 
 * Revision 1.1.8.3  1993/08/26  18:02:30  Timothy_Burke
 * 	Sterling to gold merge.
 * 	[1993/08/26  17:34:15  Timothy_Burke]
 * 
 * Revision 1.1.8.2  1993/08/26  14:31:24  Timothy_Burke
 * 	Sterling to gold merge. (agosminor-53-tim)
 * 	[1993/08/19  14:17:00  Timothy_Burke]
 * 
 * Revision 1.1.7.2  1993/08/19  14:17:00  Timothy_Burke
 * 	Sterling to gold merge. (agosminor-53-tim)
 * 
 * Revision 1.1.5.2  1993/05/18  21:07:38  Timothy_Burke
 * 	Added extern declarations for xdr_hyper and xdr_longlong routines.
 * 	[1993/05/05  14:43:16  Timothy_Burke]
 * 
 * Revision 1.1.3.3  1992/03/31  15:05:30  Benoy_Desouza
 * 	64 bit Alpha changes
 * 	[92/03/31  15:04:47  Benoy_Desouza]
 * 
 * Revision 1.1.3.2  92/03/18  18:33:56  Al_Delorey
 * 	From Silver: AG_BL5
 * 	[92/03/18  16:39:03  Al_Delorey]
 * 
 * 	From ONC reference port.
 * 	[92/02/21  09:00:45  Charles_Briggs]
 * 
 * Revision 1.1.1.2  92/03/17  15:49:22  devbld_gsf
 * 	First AG_BL5 version.  Moved from Ag baselevel delivery tree.
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: xdr.h,v $ $Revision: 1.1.28.1 $ (DEC) $Date: 2003/09/11 18:34:37 $
 */
/*	@(#)xdr.h	1.2 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *      @(#)xdr.h 1.22 88/02/08 SMI 
 */


/*
 * xdr.h, External Data Representation Serialization Routines.
 */

#ifndef _rpc_xdr_h
#define	_rpc_xdr_h

#include <rpc/types.h>
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
 * A xdrproc_t exists for each data type which is to be encoded or decoded.
 *
 * The second argument to the xdrproc_t is a pointer to an opaque pointer.
 * The opaque pointer generally points to a structure of the data type
 * to be decoded.  If this pointer is 0, then the type routines should
 * allocate dynamic storage of the appropriate size and return it.
 * bool_t	(*xdrproc_t)(XDR *, caddr_t *);
 */
typedef	bool_t (*xdrproc_t)();

/*
 * The XDR handle.
 * Contains operation which is being applied to the stream,
 * an operations vector for the paticular implementation (e.g. see xdr_mem.c),
 * and two private fields for the use of the particular impelementation.
 */
typedef struct {
	enum xdr_op	x_op;		/* operation; fast additional param */
	struct xdr_ops {
		bool_t	(*x_getlong)();	/* get a long from underlying stream */
		bool_t	(*x_putlong)();	/* put a long to " */
		bool_t	(*x_getbytes)();/* get some bytes from " */
		bool_t	(*x_putbytes)();/* put some bytes to " */
		u_int	(*x_getpostn)();/* returns bytes off from beginning */
		bool_t  (*x_setpostn)();/* lets you reposition the stream */
		int *	(*x_inline)();	/* buf quick ptr to buffered data */
		void	(*x_destroy)();	/* free privates of this xdr_stream */
	} *x_ops;
	caddr_t 	x_public;	/* users' data */
	caddr_t		x_private;	/* pointer to private data */
	caddr_t 	x_base;		/* private used for position info */
	int		x_handy;	/* extra private word */
} XDR;

/*
 * Operations defined on a XDR handle
 *
 * XDR		*xdrs;
 * int		*longp;
 * caddr_t	 addr;
 * u_int	 len;
 * u_int	 pos;
 */
#define XDR_GETLONG(xdrs, int)			\
	(*(xdrs)->x_ops->x_getlong)(xdrs, int)
#define xdr_getlong(xdrs, int)			\
	(*(xdrs)->x_ops->x_getlong)(xdrs, int)

#define XDR_PUTLONG(xdrs, int)			\
	(*(xdrs)->x_ops->x_putlong)(xdrs, int)
#define xdr_putlong(xdrs, int)			\
	(*(xdrs)->x_ops->x_putlong)(xdrs, int)

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

#define	XDR_DESTROY(xdrs)				\
	(*(xdrs)->x_ops->x_destroy)(xdrs)
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
extern bool_t	xdr_void();
extern bool_t	xdr_int(XDR *, int *);
extern bool_t	xdr_u_int(XDR *, u_int *);
extern bool_t	xdr_long(XDR *, long *);
extern bool_t	xdr_u_long(XDR *, u_long *);
extern bool_t	xdr_short(XDR *, short *);
extern bool_t	xdr_u_short(XDR *, u_short *);
extern bool_t	xdr_bool(XDR *, bool_t *);
extern bool_t	xdr_enum();
extern bool_t	xdr_array(XDR *xdrs, caddr_t *addrp, u_int *sizep,
			  u_int maxsize, u_int elsize, xdrproc_t elproc);
extern bool_t	xdr_bytes(XDR *xdrs, char **cpp, u_int *sizep, u_int maxsize);
extern bool_t	xdr_opaque(XDR *xdrs, caddr_t cp, u_int cnt);
extern bool_t	xdr_string(XDR *xdrs, char **cpp, u_int maxsize);
extern bool_t	xdr_union();
extern bool_t	xdr_longlong_t(XDR *, longlong_t *);
extern bool_t	xdr_u_longlong_t(XDR *, u_longlong_t *);
extern bool_t	xdr_hyper();
extern bool_t	xdr_u_hyper();
#ifndef KERNEL
extern void	xdr_free();
extern bool_t	xdr_char();
extern bool_t	xdr_u_char();
extern bool_t	xdr_vector();
extern bool_t	xdr_float();
extern bool_t	xdr_double();
extern bool_t	xdr_reference();
extern bool_t	xdr_pointer();
extern bool_t	xdr_wrapstring();
#endif /* !KERNEL */

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
extern bool_t   xdr_netobj();

/*
 * These are the public routines for the various implementations of
 * xdr streams.
 */
extern void   xdrmem_create();		/* XDR using memory buffers */
#ifndef KERNEL
extern void   xdrstdio_create();	/* XDR using stdio library */
extern void   xdrrec_create();		/* XDR pseudo records for tcp */
extern bool_t xdrrec_endofrecord();	/* make end of xdr record */
extern bool_t xdrrec_skiprecord();	/* move to beginning of next record */
extern bool_t xdrrec_eof();		/* true if no more input */
extern bool_t	xdrrec_eof();		/* true if no more input */
#else
/* XDR using kernel mbufs */
struct mbuf;
typedef int (* xdr_cksum_fn_t)(struct mbuf *, int);
extern void         xdrmbuf_init(XDR *, struct mbuf *, enum xdr_op);
extern void	    xdrrecmbuf_discard(struct socket *);
extern void	    xdrmbuf_finish(XDR *);
extern bool_t       xdrmbuf_getmbuf(XDR *, struct mbuf **, u_int *);
extern bool_t       xdrmbuf_putbuf(XDR *, struct iovec *, u_int, u_int, 
				   void (*)(), caddr_t);
extern bool_t	    xdrmbuf_putbuf_cksum(XDR *, struct iovec *, u_int, u_int, 
					 void (*)(), xdr_cksum_fn_t, caddr_t);
extern bool_t       xdrmbuf_putopaque(XDR *, struct iovec *, u_int, u_int,
				      void (*)(), caddr_t);
extern bool_t       xdrmbuf_putopaque_cksum(XDR *, struct iovec *, u_int,
					    u_int, void (*)(),
					    xdr_cksum_fn_t, caddr_t);
extern struct mbuf *xdrrecmbuf_recv(XDR *, struct socket *, u_int, u_int *);
extern bool_t       xdrrecmbuf_avail(struct socket *, u_int *, u_int *);
extern int          xdrrecmbuf_send(XDR *, struct socket *, struct mbuf *, int);
#endif /* !KERNEL */

#endif /*!_rpc_xdr_h*/
