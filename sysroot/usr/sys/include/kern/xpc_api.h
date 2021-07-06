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
 * @(#)$RCSfile: xpc_api.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 2002/05/30 17:09:03 $
 */
#ifndef _KERN_XPC_API_H_
#define _KERN_XPC_API_H_

#ifndef __cplusplus

#ifdef _KERNEL

#include <sys/types.h>
#include <sys/errno.h>

/****************************************************************************
 * XPC Interface data types                  
 ****************************************************************************/
typedef int         xpc_partn_id_t;     /* XPC Partition Identifier         */
typedef long        xpm_id_t;           /* XPM Identifier                   */
typedef ulong       xpm_handle_t;       /* XPM Handle                       */
typedef ulong       xpm_cursor_t;       /* XPM Enumeration Cursor           */
typedef uint        xpc_client_id_t;    /* XPC Client Identifier            */
typedef ulong       xpi_client_t;       /* XPI Client Handle                */
typedef int         xpi_reason_t;       /* XPI Interrupt Reason             */
typedef ulong       xpdt_map_t;         /* XPDT DMA map                     */
typedef void       (*XPI_HANDLER)(xpi_reason_t, xpc_partn_id_t, void *);
                                        /* XPI Client Interrupt Handler     */
/****************************************************************************
 * XPC API Error return values               
 ****************************************************************************/
#define XPC_ERR_NOTSUP     -ENOTSUP     /* XPC Infrastructure not supported */
					/*   by this platform.              */
#define XPC_ERR_INVAL      -EINVAL      /* One or more arguments invalid.   */
#define XPC_ERR_NOMEM      -ENOMEM      /* Insufficient memory available in */
                                        /*   specified segment.             */
#define XPC_ERR_FAULT      -EFAULT      /* Invalid address argument.        */
#define XPC_ERR_WOULDBLOCK -EWOULDBLOCK /* Resource required not available  */
                                        /*   and caller opted not to wait.  */
#define XPC_ERR_IO         -EIO         /* Error occurred during XPDT tx.   */
#define XPC_ERR_NXIO       -ENXIO       /* Specified partition or the       */
                                        /*   partition exporting the        */
                                        /*   specified segment is shutting  */
                                        /*   down or already gone.          */
#define XPC_ERR_REMOTE     -EREMOTE     /* Attempted operation on a remote  */
                                        /*   XPM segment that is only       */
                                        /*   supported on local XPM         */
                                        /*   segments.                      */
#define XPC_ERR_EXIST      -EEXIST      /* An entry already exists for the  */
                                        /*   specified client in the [XPM,  */
                                        /*   XPI] registry.                 */
#define XPC_PARTN_NONE     -255         /* No valid partition               */
#define XPM_NONE           -256         /* No valid segment                 */

/****************************************************************************
 * XPC API Function Parameters
 ****************************************************************************/
#define XPM_CURSOR_INIT     0x58504d0000000000 /* Hex equiv of "XPM"        */
#define XPM_NO_CLIENT       NULL        /* Used to unregister client_ds     */

/*
 * Maximum number of supported XPC clients
 */
#define XPC_CLIENT_MAX      32          /* This number MUST REMAIN CONSTANT */

/* xpm_enumerate() flags */
#define XPMF_ENUM_LOCAL     0x1         /* Return only local GSM segments.  */
#define XPMF_ENUM_REMOTE    0x2         /* Return only remote GSM segments. */
#define XPMF_ENUM_FIRST     0x4         /* Init cursor to first GSM segment */

/* xpm_malloc() flags */
#define XPMF_PAGE_ALIGN     0x1         /* Request page-aligned allocations.*/

/* xpi_register_client() flags */
#define XPIF_INIT           0x0         /* Initialize the client for XPI    */
#define XPIF_ISR_DIRECT     0x1         /* Call client ISR directly from    */
                                        /*   interrupt state. Default is to */
                                        /*   defer to XPI or client thread. */

/* xpi_post() flags */
#define XPIF_NOWAIT         0x1         /* Do not wait for resources        */

/* Reasons for call to XPI handler */
#define XPI_PEER            0x1         /* Received an XPI for this client  */
                                        /*   from a known partition         */
#define XPI_SHUTDOWN        0x2         /* A remote partition is shutting   */
					/* down                             */

/* xpdt_pull_*() flags */
#define XPDF_NOWAIT        0x1         /* Do not block waiting for rsrc    */
#define XPDF_PUSHLOCAL     0x2         /* Push from a local buffer into GSM */

/****************************************************************************
 *  XPI Client IDs
 ***************************************************************************/

#define XPC_ID_RESERVED_0   0  /* XPI INTERNAL */ 
#define XPC_ID_RESERVED_1   1  /* XPI INTERNAL */
#define XPC_ID_RESERVED_2   2  /* XPI INTERNAL */
#define XPC_ID_RESERVED_3   3  /* XPI INTERNAL */
/*
 * Range of XPI client IDs available for customer/site specific use
 */
#define XPC_ID_AVAIL_MIN    4
#define XPC_ID_AVAIL_MAX    7

/*
 * Range of XPI client IDs allocated by Tru64 UNIX to internal and
 * 3rd party clients
 */
#define XPC_ID_RSVD_MIN     8
#define XPC_ID_RSVD_MAX     XPC_CLIENT_MAX - 1


/****************************************************************************
 * XPI ISR 
 ****************************************************************************/

#define XPI_ISR_PRIORITY (BASEPRI_SYSTEM-3)


/****************************************************************************
 * Function Prototypes
 ****************************************************************************/
int            xpc_supported(void);

xpm_id_t       xpm_enumerate(xpm_cursor_t *, ulong);
xpc_partn_id_t xpm_partition(xpm_id_t);
int            xpm_min_alignment(void);
size_t         xpdt_max_transfer(ulong flags);
int            xpm_register_client(xpm_id_t, xpc_client_id_t, void *, ulong);
int            xpm_lookup_client(xpm_id_t, xpc_client_id_t, 
				 xpm_handle_t *, ulong);
int            xpm_kva_of(void **, xpm_id_t, xpm_handle_t, ulong);
int            xpm_handle_of(xpm_handle_t *, xpm_id_t, void *, ulong);
int            xpm_handle_add(xpm_handle_t *, xpm_id_t, size_t, ulong);
int            xpm_malloc(void **, xpm_id_t, size_t, ulong);
int            xpm_free(void *);

int            xpi_register_client(xpc_client_id_t, XPI_HANDLER, 
                                   xpi_client_t *, ulong);
int            xpi_unregister_client(xpi_client_t, ulong);
int            xpi_post(xpc_partn_id_t, xpi_client_t, ulong);

int            xpdt_pull_buffer(xpm_id_t, xpm_handle_t, size_t, void *, ulong);
int            xpdt_pull_pglist(xpm_id_t, xpm_handle_t, int, int *, ulong);
int            xpdt_map_buffer(void *, size_t, xpdt_map_t *, ulong);
int            xpdt_unmap_buffer(xpdt_map_t, ulong);
int            xpdt_pull_mapped(xpm_id_t, xpm_handle_t, size_t, xpdt_map_t,
				ulong);

#endif     /* #ifndef __cplusplus */

#else      /* #if!def _KERNEL */

#error "The XPC APIs are intended for kernel internal use only".

#endif     /* #ifdef _KERNEL */
#endif     /* #ifndef _KERN_XPC_API_H_ */

