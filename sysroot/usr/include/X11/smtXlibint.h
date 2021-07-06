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
*****************************************************************************
**                                                                          *
**                         COPYRIGHT (c) 1990 BY                            *
**             DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.                *
**			   ALL RIGHTS RESERVED                              *
**                                                                          *
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED  *
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE  *
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER  *
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY  *
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY  *
**  TRANSFERRED.                                                            *
**                                                                          *
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE  *
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT  *
**  CORPORATION.                                                            *
**                                                                          *
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS  *
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.                 *
**                                                                          *
*****************************************************************************
*/
/*
 * smtXlibint.h:
 *	Redefine buffer allocation macros to handle shared memory.
 *	The key thing to note is that allocations are *always* made
 *	for the largest request which the server will accept, and then
 *	are scaled back when the request is complete.  The other thing
 *	to note is that a request is not considered complete until
 *	SyncHandler is invoked.  This allows all the sleazy and broken
 *	things which Xlib does assuming socket transport semantics
 *	to continue to work.  The penalty for this is a certain amount
 *	of waste in the size of the shared memory segment, but this
 *	is a reasonable tradeoff to make for performance.
 *	Also note that _XFlush() is effectively a no-op with a shared-
 *	memory transport.
 */

#include <X11/extensions/smtstr.h>

/* non-ANSI C uses empty comment instead of "##" for token concatenation */
/* be sure to update BOTH sections if making changes ! 			*/

#undef GetReq
#define GetReq(name, req) \
	if (dpy->pSmt) \
	{ \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    int status; \
	    if (dpy->buffer) _XFlush(dpy); \
	    status = \
	     ipAllocateData(&pSmt->chan, dpy->max_request_size, (IPDataPtr*)&dpy->buffer); \
	    if (status != IP_SUCCESS) _SmtIpError(dpy, pSmt, status); \
	    req = (x##name##Req *)(dpy->last_req = dpy->buffer);\
	    req->reqType = X_##name; \
	    req->length = (SIZEOF(x##name##Req))>>2;\
	    dpy->bufptr = dpy->buffer + SIZEOF(x##name##Req);\
	    dpy->bufmax = dpy->buffer + (dpy->max_request_size << 2);\
	    dpy->request++; \
	} \
	else \
	{ \
	    WORD64ALIGN\
	    if ((dpy->bufptr + SIZEOF(x##name##Req)) > dpy->bufmax)\
		    _XFlush(dpy);\
	    req = (x##name##Req *)(dpy->last_req = dpy->bufptr);\
	    req->reqType = X_##name;\
	    req->length = (SIZEOF(x##name##Req))>>2;\
	    dpy->bufptr += SIZEOF(x##name##Req);\
	    dpy->request++;\
	}

#undef GetReqExtra
#define GetReqExtra(name, n1, req) \
	if (dpy->pSmt) \
	{ \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    int status; \
	    if (dpy->buffer) _XFlush(dpy); \
	    status = \
	     ipAllocateData(&pSmt->chan, dpy->max_request_size,(IPDataPtr*) &dpy->buffer); \
	    if (status != IP_SUCCESS) _SmtIpError(dpy, pSmt, status); \
	    req = (x##name##Req *)(dpy->last_req = dpy->buffer);\
	    req->reqType = X_##name; \
	    req->length = (SIZEOF(x##name##Req) + n1)>>2; \
	    dpy->bufptr = dpy->buffer + SIZEOF(x##name##Req) + n1;\
	    dpy->bufmax = dpy->buffer + (dpy->max_request_size << 2);\
	    dpy->request++; \
	} \
	else \
	{ \
	    WORD64ALIGN\
	    if ((dpy->bufptr + SIZEOF(x##name##Req) + n1) > dpy->bufmax)\
		    _XFlush(dpy);\
	    req = (x##name##Req *)(dpy->last_req = dpy->bufptr);\
	    req->reqType = X_##name;\
	    req->length = (SIZEOF(x##name##Req) + n1)>>2;\
	    dpy->bufptr += SIZEOF(x##name##Req) + n1;\
	    dpy->request++;\
	}

#undef GetResReq
#define GetResReq(name, rid, req) \
	if (dpy->pSmt) \
	{ \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    int status; \
	    if (dpy->buffer) _XFlush(dpy); \
	    status = \
	     ipAllocateData(&pSmt->chan, dpy->max_request_size,(IPDataPtr*) &dpy->buffer); \
	    if (status != IP_SUCCESS) _SmtIpError(dpy, pSmt, status); \
	    req = (xResourceReq *) (dpy->last_req = dpy->buffer);\
	    req->reqType = X_##name; \
	    req->length = 2; \
	    req->id = (rid); \
	    dpy->bufptr = dpy->buffer + sizeof(xResourceReq);\
	    dpy->bufmax = dpy->buffer + (dpy->max_request_size << 2);\
	    dpy->request++; \
	} \
	else \
	{ \
	    if ((dpy->bufptr + sizeof(xResourceReq)) > dpy->bufmax)\
	    	_XFlush(dpy);\
	    req = (xResourceReq *) (dpy->last_req = dpy->bufptr);\
	    req->reqType = X_##name;\
	    req->length = 2;\
	    req->id = (rid);\
	    dpy->bufptr += sizeof(xResourceReq);\
	    dpy->request++;\
	}


#undef GetEmptyReq
#define GetEmptyReq(name, req) \
	if (dpy->pSmt) \
	{ \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    int status; \
	    if (dpy->buffer) _XFlush(dpy); \
	    status = \
	     ipAllocateData(&pSmt->chan, dpy->max_request_size,(IPDataPtr*) &dpy->buffer); \
	    if (status != IP_SUCCESS) _SmtIpError(dpy, pSmt, status); \
	    req = (xReq *) (dpy->last_req = dpy->buffer); \
	    req->reqType = X_##name; \
	    req->length = 1; \
	    dpy->bufptr = dpy->buffer + SIZEOF(xReq); \
	    dpy->bufmax = dpy->buffer + (dpy->max_request_size << 2);\
	    dpy->request++; \
	} \
	else \
	{ \
	    WORD64ALIGN\
	    if ((dpy->bufptr + SIZEOF(xReq)) > dpy->bufmax) \
	    	_XFlush(dpy); \
	    req = (xReq *) (dpy->last_req = dpy->bufptr); \
	    req->reqType = X_##name; \
	    req->length = 1; \
	    dpy->bufptr += SIZEOF(xReq); \
	    dpy->request++; \
	}


#undef SyncHandle
#define SyncHandle() \
	if (dpy->pSmt) { \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    if (dpy->buffer) { \
		int status = ipUnallocateAndSendData(&pSmt->chan, \
			    ((dpy->bufmax - dpy->bufptr)>>2) ); \
		if (status != IP_SUCCESS) _SmtIpError(dpy, pSmt, status);\
		dpy->buffer = NULL; \
		dpy->bufptr = (char *) 0x7fffffff; \
	    } \
	} \
	if (dpy->synchandler) (*dpy->synchandler)(dpy)

#define SyncHandleNoSend() \
	if (dpy->synchandler) (*dpy->synchandler)(dpy)

#undef Data
#define Data(dpy, data, len) \
	if (dpy->pSmt) \
	{ \
	    register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
	    if (dpy->bufptr + (len) <= dpy->bufmax) {\
		bcopy(data, dpy->bufptr, (int)len); \
		dpy->bufptr += ((len) + 3) & ~3; \
	    } else { \
		_SmtBufferOverflow(dpy, pSmt); \
	    } \
	} \
	else \
	{ \
	    if (dpy->bufptr + (len) <= dpy->bufmax) {\
		bcopy(data, dpy->bufptr, (int)len);\
		dpy->bufptr += ((len) + 3) & ~3;\
	    } else\
		_XSend(dpy, data, len); \
	}


/* Allocate bytes from the buffer.  No padding is done, so if
 * the length is not a multiple of 4, the caller must be
 * careful to leave the buffer aligned after sending the
 * current request.
 *
 * "type" is the type of the pointer being assigned to.
 * "ptr" is the pointer being assigned to.
 * "n" is the number of bytes to allocate.
 *
 * Example: 
 *    xTextElt *elt;
 *    BufAlloc (xTextElt *, elt, nbytes)
 */
#undef BufAlloc
#define BufAlloc(type, ptr, n) \
    if (dpy->pSmt) \
    { \
	register smtDisplayPtr pSmt = (smtDisplayPtr)dpy->pSmt; \
    	ptr = (type) dpy->bufptr; \
    	dpy->bufptr += (n); \
	if (dpy->bufptr + (n) > dpy->bufmax) {\
	    _SmtBufferOverflow(dpy, pSmt); \
	} \
    } \
    else \
    { \
    	if (dpy->bufptr + (n) > dpy->bufmax) \
            _XFlush (dpy); \
    	ptr = (type) dpy->bufptr; \
    	dpy->bufptr += (n); \
    }
