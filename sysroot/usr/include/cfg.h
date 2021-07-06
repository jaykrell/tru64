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
 * @(#)$RCSfile: cfg.h,v $ $Revision: 1.1.22.1 $ (DEC) $Date: 2001/09/21 17:50:24 $
 */

#ifndef _CFG_H_
#define _CFG_H_

#include <stdio.h>
#include <sys/sysconfig.h>
#include <sys/param.h>
#include <nlist.h>
#include <ksm/ksm.h>

#define  CFG_USER_NAMELEN_V2  32
#define  CFG_USER_NAMELEN     L_cuserid

/*
 * Connection initialization packet.
 */
typedef struct {
    int			proto_version;
    unsigned int        flags;
    char		username[CFG_USER_NAMELEN];
    char		reserved[296-CFG_USER_NAMELEN];
} cfg_init_pack_t;

/*
 * Request header packet.
 */
typedef struct {
    char		subsys[CFG_SUBSYS_NAME_SZ];
    int			operation;
    cfg_status_t	result;
    long		data_size;
} cfg_pack_t;

/*
 * Connection handle.
 */
typedef struct {
    char		host[MAXHOSTNAMELEN + 1];
    int			in_fd;
    int			out_fd;
    int                 pid;
    char		reserved[40];
} cfg_handle_t;

/*
 * Protocol versions.
 */
#define CFG_PROTO_V1		1
#define CFG_PROTO_V2		2     /* add security check and debug option */
#define CFG_PROTO_V3		3     /* long login name */
#define CFG_PROTO_VERSION	CFG_PROTO_V3

/*
 * Bit flags for the flags argument in cfg_connect().
 */
#define    CFG_FLAG_NOFLAGS        0x0
#define    CFG_FLAG_VERBOSE        0x1

/*
 * Functions in libcfg.a.
 */

#ifdef __cplusplus
extern "C" {
#endif

cfg_status_t cfg_connect( caddr_t  host, cfg_handle_t  *handle, uint  flags );

cfg_status_t cfg_disconnect( cfg_handle_t  *handle );

cfg_status_t cfg_subsys_config( cfg_handle_t  *handle, caddr_t  subsys );

cfg_status_t cfg_subsys_unconfig( cfg_handle_t  *handle, caddr_t  subsys );

cfg_status_t cfg_subsys_reconfig( cfg_handle_t  *handle, caddr_t  subsys,
                                  cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_query( cfg_handle_t  *handle, caddr_t  subsys,
                               cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_query_all( cfg_handle_t  *handle, caddr_t  subsys,
                                   cfg_attr_t  **attributes, int  *nattributes );

cfg_status_t cfg_subsys_op( cfg_handle_t  *handle, caddr_t  subsys, cfg_op_t  op,
                            caddr_t  indata,  ulong  indata_size, 
                            caddr_t  outdata, ulong  outdata_size );

cfg_status_t cfg_subsys_state( cfg_handle_t  *handle, caddr_t  subsys, uint  *state );

cfg_status_t cfg_subsys_list( cfg_handle_t  *handle, caddr_t  **subsys,
                              uint  **state, int  *nsubsys );

cfg_status_t cfg_subsys_defaults( cfg_handle_t  *handle, caddr_t  subsys,
                                  cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_defaults_all( cfg_handle_t  *handle, caddr_t  subsys,
                                      cfg_attr_t  **attributes, int  *nattributes );

/*
 * KSM functions.
 */
cfg_status_t cfg_ksm_find(cfg_handle_t *handle, KSM_FIND_BUF *reqbuf, int bufsiz);
cfg_status_t cfg_ksm_memreq(cfg_handle_t *handle, KSM_MEM_REQ_BUF *reqbuf,
    int bufsiz, cfg_attr_t **attributes, int *nattributes);
cfg_status_t cfg_ksm_setreq(cfg_handle_t *handle, KSM_SET_REQ_BUF *reqbuf, int bufsiz);
cfg_status_t cfg_ksm_setop(cfg_handle_t *handle, struct ksm_reqbuf_hdr *reqbuf, caddr_t inbuf, size_t inbuf_size, caddr_t outbuf, size_t outbuf_size);
cfg_status_t cfg_ksm_memop(cfg_handle_t *handle, struct ksm_mem_req_buf *reqbuf, caddr_t inbuf, size_t inbuf_size, caddr_t outbuf, size_t outbuf_size);


#ifdef __cplusplus
}
#endif

/*
** BEGIN Process Set Manager declarations
*/

#include <ksm/psm/psm.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	_PSM_MYNODE	((const char *)NULL)
#define	_PSM_MYPID	((pid_t)0)
#define	_PSM_ALLNODE	""
#define	_PSM_ALLCAT	((const char *)NULL)
#define	_PSM_ALLPID	((pid_t)0)

/*
 * The following well-known-categories are generally registered
 * with the PSM at configuration time.  When these applications
 * start running, they should register their instances with:
 *
 *	_PSM_REGSELF(_PSM_CAT_MOUNTD);
 *
 * The above example registers the caller as a mountd instance.
 * If the index is out of range, _PSM_REGSELF() registers the
 * application in the "_unknown_" category.
 */
extern const char *_psm_categories[];
extern const int _psm_ncategories;

#define	_PSM_CAT_AUTOMOUNTD	0
#define	_PSM_CAT_BINLOGD	1
#define	_PSM_CAT_CLULOCKD	2
#define	_PSM_CAT_CLUSTATD	3
#define	_PSM_CAT_EVMCHMGR	4
#define	_PSM_CAT_EVMD		5
#define	_PSM_CAT_EVMLOGGER	6
#define	_PSM_CAT_GATED		7
#define	_PSM_CAT_JOIND		8
#define	_PSM_CAT_LOCKD		9
#define	_PSM_CAT_MOUNTD		10
#define	_PSM_CAT_NAMED		11
#define	_PSM_CAT_NFSD		12
#define	_PSM_CAT_NFSIOD		13
#define	_PSM_CAT_PCNFSD		14
#define	_PSM_CAT_PORTMAP	15
#define	_PSM_CAT_PROPLISTD	16
#define	_PSM_CAT_ROUTED		17
#define	_PSM_CAT_RWHOD		18
#define	_PSM_CAT_STATD		19
#define	_PSM_CAT_SYSLOGD	20
#define	_PSM_CAT_XNTPD		21
#define	_PSM_CAT_YPBIND		22
#define	_PSM_CAT_INETD		23
#define	_PSM_CAT_SMSD		24
#define	_PSM_CAT_SMAUTH		25
#define	_PSM_CAT_AUTOFSD	26
#define	_PSM_CAT_SENDMAILD	27

#define	_PSM_REGSELF(idx)		\
	cfg_psm_memadd(_PSM_MYNODE,	\
		(idx < _psm_ncategories)? _psm_categories[idx]:	"_unknown_", \
		_PSM_MYPID)

/*
 * Prototypes.
 */
cfg_status_t	cfg_psm_catadd	__((const char *, const char *));
cfg_status_t	cfg_psm_catrem	__((const char *, const char *));
cfg_status_t	cfg_psm_catget	__((const char *, const char *,
					psm_catrsp_t **));
void		cfg_psm_catfree	__((psm_catrsp_t *));

cfg_status_t	cfg_psm_memadd	__((const char *, const char *, pid_t));
cfg_status_t	cfg_psm_memrem	__((const char *, const char *, pid_t));
cfg_status_t	cfg_psm_memget	__((const char *, const char *, pid_t,
					psm_memrsp_t **));
void		cfg_psm_memfree	__((psm_memrsp_t *));

#ifdef __cplusplus
}
#endif

/*
** END Process Set Manager declarations
*/

#endif /* _CFG_H_ */
