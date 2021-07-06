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
 * *****************************************************************
 * *                                                               *
 * *    Copyright Compaq Computer Corporation, 2000                *
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
 * Copyright (c) 1998 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 *
 *		RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *		VERITAS SOFTWARE
 * 1600 PLYMOUTH STREET, MOUNTAIN VIEW, CA 94043
 */

#ifndef _DMAPI_H
#define _DMAPI_H

typedef unsigned char dm_u8_t;
typedef signed char dm_s8_t;
typedef unsigned short dm_u16_t;
typedef signed short dm_s16_t;
typedef unsigned int dm_u32_t;
typedef signed int dm_s32_t;
typedef unsigned long dm_u64_t;
typedef signed long dm_s64_t;

#ifndef _KERNEL
#ifdef __cplusplus
extern "C" {
#endif
#endif

#define DM_FALSE 0
#define DM_TRUE 1
typedef dm_u64_t dm_boolean_t;
typedef dm_s64_t dm_off_t;
typedef dm_u64_t dm_size_t;
typedef dm_s64_t dm_ssize_t;
typedef dm_u32_t dm_ino_t;
typedef dm_s32_t dm_sessid_t;
typedef dm_s32_t dm_token_t;
typedef dm_ino_t dm_attrloc_t;
typedef dm_s32_t dm_ftype_t;
typedef dm_s32_t dm_updtimes_t;
typedef dm_u8_t dm_event_type_t;
typedef dm_s32_t dm_event_disp_t;
typedef dm_s32_t dm_eventset_t;
typedef dm_u64_t dm_sequence_t;
typedef dm_s64_t dm_igen_t;
typedef dm_u64_t dm_fsid_t;
typedef dm_u64_t dm_fset_index_t;

#define DM_VER_STR_CONTENTS	"DMAPI Tru64 V5.1A"

/*
	maximum hsm name string
*/
#define DM_MAXNAME 256

/*
 * Definitions from DMAPI specification 2/1997 (X/Open Document C429)
 */

typedef enum
{
	DM_EVENT_INVALID,
	DM_EVENT_MOUNT,
	DM_EVENT_PREUNMOUNT,
	DM_EVENT_UNMOUNT,
	DM_EVENT_NOSPACE,
	DM_EVENT_CREATE,
	DM_EVENT_POSTCREATE,
	DM_EVENT_REMOVE,
	DM_EVENT_POSTREMOVE,
	DM_EVENT_RENAME,
	DM_EVENT_POSTRENAME,
	DM_EVENT_SYMLINK,
	DM_EVENT_POSTSYMLINK,
	DM_EVENT_LINK,
	DM_EVENT_POSTLINK,
	DM_EVENT_READ,
	DM_EVENT_WRITE,
	DM_EVENT_TRUNCATE,
	DM_EVENT_ATTRIBUTE,
	DM_EVENT_DESTROY,
	DM_EVENT_USER,
	DM_EVENT_MAX,   /* beyond MAX are unsupported */
	DM_EVENT_CLOSE,	/* not supported--return EINVAL */
	DM_EVENT_DEBUT, /* not supported--return EINVAL */
	DM_EVENT_CANCEL /* not supported--return EINVAL */
} dm_eventtype_t;

typedef enum
{
	DM_EXTENT_INVALID,
	DM_EXTENT_RES,
	DM_EXTENT_HOLE
} dm_extenttype_t;

typedef enum
{
	DM_MSGTYPE_INVALID,
	DM_MSGTYPE_SYNC,
	DM_MSGTYPE_ASYNC
} dm_msgtype_t;

typedef enum
{
	DM_RETFLAG_INVALID,
	DM_RETFLAG_NOFLAG,
	DM_RETFLAG_FORCE
} dm_namesp_retflag_t;

typedef enum
{
	DM_RESP_INVALID,
	DM_RESP_CONTINUE,
	DM_RESP_ABORT,
	DM_RESP_DONTCARE
} dm_response_t;

typedef enum
{
	DM_RIGHT_NULL,
	DM_RIGHT_SHARED,
	DM_RIGHT_EXCL
} dm_right_t;

typedef enum
{
	DM_CONFIG_INVALID,
	DM_CONFIG_BULKALL,
	DM_CONFIG_CREATE_BY_HANDLE,
	DM_CONFIG_DTIME_OVERLOAD,
	DM_CONFIG_LEGACY,
	DM_CONFIG_LOCK_UPGRADE,
	DM_CONFIG_MAX_ATTR_ON_DESTROY,
	DM_CONFIG_MAX_ATTRIBUTE_SIZE,
	DM_CONFIG_MAX_HANDLE_SIZE,
	DM_CONFIG_MAX_MANAGED_REGIONS,
	DM_CONFIG_MAX_MESSAGE_DATA,
	DM_CONFIG_OBJ_REF,
	DM_CONFIG_PENDING,
	DM_CONFIG_PERS_ATTRIBUTES,
	DM_CONFIG_PERS_EVENTS,
	DM_CONFIG_PERS_INHERIT_ATTRIBS,
	DM_CONFIG_PERS_MANAGED_REGIONS,
	DM_CONFIG_PUNCH_HOLE,
	DM_CONFIG_TOTAL_ATTRIBUTE_SPACE,
	DM_CONFIG_WILL_RETRY,
	DM_CONFIG_MAX
} dm_config_t;

typedef struct dm_fileattr
{
	mode_t fa_mode;
	uid_t fa_uid;
	gid_t fa_gid;
	time_t fa_atime;
	time_t fa_mtime;
	time_t fa_ctime;
	time_t fa_dtime;
	dm_off_t	fa_size;
} dm_fileattr_t;

/*
	variable data length structure
*/
typedef struct dm_vardata
{
	dm_off_t	vd_offset;
	dm_size_t	vd_length;
} dm_vardata_t;

#define	DM_GET_VALUE(p, field, type) ((type)((dm_off_t)(p) + (p)->field.vd_offset))

#define DM_GET_LEN(p, field) ((p)->field.vd_length)

#define	DM_STEP_TO_NEXT(p, type) ((type)((p)->_link ? (char *)(p) + (p)->_link : NULL))

/*
	DM global handle, invalid handle
*/

typedef struct kdm_handle dm_dummy_handle_t;

extern dm_dummy_handle_t hsmfs_global_handle;
#define DM_GLOBAL_HANP (void *) &hsmfs_global_handle
#define DM_GLOBAL_HLEN sizeof(dm_dummy_handle_t)

extern dm_dummy_handle_t hsmfs_invalid_handle;
#define DM_INVALID_HANP (void *) &hsmfs_invalid_handle
#define DM_INVALID_HLEN sizeof(dm_dummy_handle_t)

#define DM_ATTR_NAME_SIZE 8 /* for dm_attrname_t */

typedef struct dm_attrname
{
	char an_chars[DM_ATTR_NAME_SIZE];
} dm_attrname_t;

typedef struct dm_attrlist
{
	dm_attrname_t al_name;
	dm_vardata_t al_data;
} dm_attrlist_t;

typedef struct dm_data_event
{
	dm_vardata_t	de_handle;
	dm_off_t	de_offset;
	dm_size_t	de_length;
} dm_data_event_t;

typedef struct dm_namesp_event
{
	mode_t ne_mode;
	dm_vardata_t ne_handle1;
	dm_vardata_t ne_handle2;
	dm_vardata_t ne_name1;
	dm_vardata_t ne_name2;
	dm_s32_t ne_retcode;
} dm_namesp_event_t;

typedef struct dm_mount_event
{
	mode_t me_mode;
	dm_vardata_t me_handle1;
	dm_vardata_t me_handle2;
	dm_vardata_t me_name1;
	dm_vardata_t me_name2;
	dm_vardata_t me_roothandle;
	dm_s32_t me_retcode;
} dm_mount_event_t;

typedef struct dm_destroy_event
{
	dm_vardata_t ds_handle;
	dm_attrname_t ds_attrname;
	dm_vardata_t ds_attrcopy;
} dm_destroy_event_t;

typedef struct dm_inherit
{
	dm_attrname_t ih_name;
	mode_t ih_filetype;
} dm_inherit_t;

typedef struct dm_dispinfo
{
	dm_ssize_t _link;
	dm_vardata_t di_fshandle;
	dm_eventset_t di_eventset;
} dm_dispinfo_t;

/*
	Note:
		The ev_body members presence is defined by its length
		ev_data.vd_length. So, the sizeof this struct is less
		sizeof ev_data.
*/
typedef struct dm_eventmsg
{
	dm_ssize_t _link;
	dm_eventtype_t ev_type;
	dm_token_t ev_token;
	dm_sequence_t ev_sequence;
	dm_vardata_t ev_data;
	char ev_body[1];
} dm_eventmsg_t;

typedef struct dm_cancel_event
{
	dm_sequence_t ce_sequence;
	dm_token_t ce_token;
} dm_cancel_event_t;

typedef struct dm_region
{
	dm_off_t rg_offset;	/* start offset in file */
	dm_size_t rg_size;	/* region length */
	dm_u32_t rg_flags;	/* flags - read/write/trunc */
        u_int rg_opaque;        /* requested by Unitree */
} dm_region_t;

typedef struct dm_extent
{
	dm_extenttype_t ex_type;
	dm_off_t ex_offset;
	dm_size_t ex_length;
} dm_extent_t;
#define DM_REGION_NOEVENT 0x00
#define DM_REGION_READ 0x01
#define DM_REGION_WRITE 0x02
#define DM_REGION_TRUNCATE 0x04
#define DM_REGION_VALIDFLAG 0x07

/*
	Misc defines
*/
#define DM_SESSION_INFO_LEN 256
#define DM_NO_SESSION -1
#define DM_INVALID_TOKEN -1
#define DM_NO_TOKEN 0

/*
	Wait flags
*/
#define DM_EV_WAIT 0x01
#define DM_RR_WAIT 0x01

/*
	mount option flags -- delivered with mount event in the
	me_mode field
*/
#define DM_MOUNT_RDONLY 0x01

/*
	unmount flag
*/
#define DM_UNMOUNT_FORCE 0x001

/*
	dm_invis_write() option
*/
#define DM_WRITE_SYNC 0x01

/*
	Attribute mask flags
*/
#define DM_AT_ATIME 0x0001
#define DM_AT_CFLAG 0x0002
#define DM_AT_CTIME 0x0004
#define DM_AT_DTIME 0x0008
#define DM_AT_EMASK 0x0010
#define DM_AT_GID   0x0020
#define DM_AT_HANDLE 0x0040
#define DM_AT_MODE 0x0080
#define DM_AT_MTIME 0x0100
#define DM_AT_PATTR 0x0200
#define DM_AT_PMANR 0x0400
#define DM_AT_SIZE 0x0800
#define DM_AT_STAT 0x1000
#define DM_AT_UID  0x2000

typedef struct dm_stat
{
	dm_ssize_t _link;
	dm_vardata_t dt_handle;
	dm_vardata_t dt_compname;
	dm_eventset_t dt_emask;
	dm_s32_t dt_nevents;
	dm_s32_t dt_pers;
	dm_s32_t dt_pmanreg;
	time_t dt_dtime;
	dm_u32_t dt_change;
	/*  1170 fields */
	dev_t dt_dev;
	dm_ino_t dt_ino;
	mode_t dt_mode;
	nlink_t dt_nlink;
	uid_t dt_uid;
	gid_t dt_gid;
	dev_t dt_rdev;
	dm_off_t dt_size;
	time_t dt_atime;
	time_t dt_mtime;
	time_t dt_ctime;
	dm_u32_t dt_blksize;
	dm_size_t dt_blocks;
} dm_stat_t;

/*
	dm_xstat -- same as dm_stat but includes data for one named DM attribute
*/
typedef struct dm_xstat
{
	dm_ssize_t _link;
	dm_stat_t dx_statinfo;
	dm_vardata_t dx_attrdata;
} dm_xstat_t;

typedef struct dm_timestruct
{
	time_t dm_tv_sec;
	dm_s32_t dm_tv_nsec;
} dm_timestruct_t;

/*
	Macros for setting/resetting event set list.
*/
#define DMEV_SET(ev, evlist) ((evlist) |= (1 << (ev)))
#define DMEV_CLR(ev, evlist) ((evlist) &= ~(1 << (ev)))
#define DMEV_ISSET(ev, evlist) ((evlist) & (1 << (ev)))
#define DMEV_ZERO(evlist) (evlist) = 0

#ifndef _KERNEL

/*
 * For Unitree, only requested functionality will be supported
 */

#ifdef  __STDC__

extern int      dm_create_session(dm_sessid_t, char *, dm_sessid_t *);
extern int      dm_create_userevent(dm_sessid_t, size_t, void *, dm_token_t *);
extern int      dm_destroy_session(dm_sessid_t);
extern int      dm_find_eventmsg(dm_sessid_t, dm_token_t, size_t,
                                 void *, size_t *);
extern int      dm_get_allocinfo(dm_sessid_t, void *, size_t, dm_token_t,
                                 dm_off_t *, u_int, dm_extent_t *, u_int *);
extern int      dm_get_bulkattr(dm_sessid_t, void *, size_t, dm_token_t,
                                u_int, dm_attrloc_t *, size_t,
                                void *, size_t *);
extern int      dm_get_dirattrs(dm_sessid_t, void *, size_t, dm_token_t,
                                u_int, dm_attrloc_t *, size_t, void *,
                                size_t *);
extern int      dm_init_attrloc(dm_sessid_t, void *, size_t, dm_token_t,
                                dm_attrloc_t *);
extern int      dm_get_config(void *, size_t, dm_config_t, dm_size_t *);
extern int      dm_get_config_events(void *, size_t, u_int, dm_eventset_t *,
                                     u_int *);
extern int      dm_get_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
                              dm_attrname_t *, size_t, void *, size_t *);
extern int      dm_get_eventlist(dm_sessid_t, void *, size_t, dm_token_t,
                                 u_int, dm_eventset_t *, u_int  *);
extern int      dm_get_events(dm_sessid_t, u_int, u_int, size_t, void *,
                              size_t *);
extern int      dm_get_fileattr(dm_sessid_t, void *, size_t, dm_token_t,
                                u_int, dm_stat_t *);
extern int      dm_get_mountinfo(dm_sessid_t, void *, size_t, dm_token_t,
                                 size_t, void *, size_t *);
extern int      dm_get_region(dm_sessid_t, void *, size_t, dm_token_t,
                              u_int, dm_region_t *, u_int *);
extern int      dm_getall_disp(dm_sessid_t, size_t, void *, size_t *);
extern int      dm_getall_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
                                 size_t, void *, size_t *);
extern int      dm_getall_sessions(u_int, dm_sessid_t *, u_int *);
extern int      dm_getall_tokens(dm_sessid_t, u_int, dm_token_t *, u_int *);
extern int      dm_handle_cmp(void *, size_t, void *, size_t);
extern dm_boolean_t dm_handle_is_valid(void *, size_t);
extern u_int    dm_handle_hash(void *, size_t);
extern int      dm_handle_to_fshandle(void *, size_t, void **, size_t *);
extern int      dm_handle_to_path(void *, size_t, void *, size_t,
                                  size_t, char *, size_t *);
extern int      dm_init_service(char **);
extern int      dm_move_event(dm_sessid_t, dm_token_t, dm_sessid_t,
                              dm_token_t *);
extern int      dm_path_to_fshandle(char *, void **, size_t *);
extern int      dm_path_to_handle(char *, void **, size_t *);
extern void     dm_handle_free(void *, size_t);
extern int      dm_punch_hole(dm_sessid_t, void *, size_t, dm_token_t,
                              dm_off_t, dm_size_t);
extern int      dm_probe_hole(dm_sessid_t, void *, size_t, dm_token_t,
                              dm_off_t, dm_size_t, dm_off_t *, dm_size_t *);
extern int      dm_query_right(dm_sessid_t, void *, size_t, dm_token_t,
                               dm_right_t *);
extern int      dm_query_session(dm_sessid_t, size_t, void *, size_t *);
extern dm_ssize_t dm_read_invis(dm_sessid_t, void *, size_t, dm_token_t,
                                dm_off_t, dm_size_t, void *);
extern dm_ssize_t dm_write_invis(dm_sessid_t, void *, size_t, dm_token_t,
                                 int, dm_off_t, dm_size_t, void *);
extern int      dm_release_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int      dm_remove_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
                                 int, dm_attrname_t *);
extern int      dm_request_right(dm_sessid_t, void *, size_t, dm_token_t,
                                 u_int, dm_right_t);
extern int      dm_respond_event(dm_sessid_t, dm_token_t, dm_response_t,
                                 int, size_t, void *);
extern int      dm_send_msg(dm_sessid_t, dm_msgtype_t, size_t, void *);
extern int      dm_set_disp(dm_sessid_t, void *, size_t, dm_token_t,
                            dm_eventset_t *, u_int);
extern int      dm_set_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
                              dm_attrname_t *, int, size_t, void *);
extern int      dm_set_eventlist(dm_sessid_t, void *, size_t, dm_token_t,
                                 dm_eventset_t *, u_int);
extern int      dm_set_fileattr(dm_sessid_t, void *, size_t, dm_token_t,
                                u_int, dm_fileattr_t *);
extern int      dm_set_region(dm_sessid_t, void *, size_t, dm_token_t,
                              u_int, dm_region_t *, dm_boolean_t *);
extern int      dm_set_return_on_destroy(dm_sessid_t, void *, size_t,
                                         dm_token_t,  dm_attrname_t *,
                                         dm_boolean_t);
extern int      dm_sync_by_handle(dm_sessid_t, void *, size_t, dm_token_t);
extern int      dm_handle_to_fsid(void *, size_t, dm_fsid_t *);
extern int      dm_handle_to_igen(void *, size_t, dm_igen_t *);
extern int      dm_handle_to_ino(void *, size_t, dm_ino_t *);

/*
 * Stubs for CAE "optional" interfaces that are unsupported
 */

extern int      dm_fd_to_handle(int, void **, size_t *);

extern int      dm_get_bulkall(dm_sessid_t, void *, size_t, dm_token_t,
                               u_int, dm_attrname_t *, dm_attrloc_t *, size_t,
                               void *, size_t *);
extern int      dm_clear_inherit(dm_sessid_t, void *, size_t,
                                 dm_token_t, dm_attrname_t *);
extern int      dm_getall_inherit(dm_sessid_t, void *, size_t, dm_token_t,
                                  u_int, dm_inherit_t *, u_int *);
extern int      dm_set_inherit(dm_sessid_t, void *, size_t, dm_token_t,
                               dm_attrname_t *, mode_t);
extern int      dm_create_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
                                    void *, size_t, char *);
extern int      dm_mkdir_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
                                   void *, size_t, char *);
extern int      dm_symlink_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
                                     void *, size_t, char *, char *);
extern int      dm_make_handle(dm_fsid_t *, dm_ino_t, dm_igen_t, void **,
                               size_t *);
extern int      dm_make_fshandle(dm_fsid_t *, void **, size_t *);
extern int      dm_upgrade_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int      dm_downgrade_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int      dm_pending(dm_sessid_t, dm_token_t, dm_timestruct_t *);
extern int      dm_obj_ref_hold(dm_sessid_t, dm_token_t, void *, size_t);
extern int      dm_obj_ref_rele(dm_sessid_t, dm_token_t, void *, size_t);
extern int      dm_obj_ref_query(dm_sessid_t, dm_token_t, void *, size_t);
#else   /* __STDC__ */

extern int      dm_create_session();
extern int      dm_create_userevent();
extern int      dm_destroy_session();
extern int      dm_find_eventmsg();
extern int      dm_get_allocinfo();
extern int      dm_get_bulkattr();
extern int      dm_get_dirattrs();
extern int      dm_init_attrloc();
extern int      dm_get_config();
extern int      dm_get_config_events();
extern int      dm_get_dmattr();
extern int      dm_get_eventlist();
extern int      dm_get_events();
extern int      dm_get_fileattr();
extern int      dm_get_mountinfo();
extern int      dm_get_region();
extern int      dm_getall_disp();
extern int      dm_getall_dmattr();
extern int      dm_getall_sessions();
extern int      dm_getall_tokens();
extern int      dm_handle_cmp();
extern dm_boolean_t dm_handle_is_valid();
extern u_int    dm_handle_hash();
extern int      dm_handle_to_fshandle();
extern int      dm_handle_to_path();
extern int      dm_init_service();
extern int      dm_move_event();
extern int      dm_fd_to_handle();
extern int      dm_path_to_fshandle();
extern int      dm_path_to_handle();
extern void     dm_handle_free();
extern int      dm_punch_hole();
extern int      dm_probe_hole();
extern int      dm_query_right();
extern int      dm_query_session();
extern dm_ssize_t dm_read_invis();
extern dm_ssize_t dm_write_invis();
extern int      dm_release_right();
extern int      dm_remove_dmattr();
extern int      dm_request_right();
extern int      dm_respond_event();
extern int      dm_send_msg();
extern int      dm_set_disp();
extern int      dm_set_dmattr();
extern int      dm_set_eventlist();
extern int      dm_set_fileattr();
extern int      dm_set_region();
extern int      dm_set_return_on_destroy();
extern int      dm_sync_by_handle();
extern int      dm_handle_to_fsid();
extern int      dm_handle_to_igen();
extern int      dm_handle_to_ino();

/*
 * Stubs for non-supported optional interfaces
 */

extern int      dm_get_bulkall();
extern int      dm_clear_inherit();
extern int      dm_getall_inherit();
extern int      dm_set_inherit();
extern int      dm_create_by_handle();
extern int      dm_mkdir_by_handle();
extern int      dm_symlink_by_handle();
extern int      dm_make_handle();
extern int      dm_make_fshandle();
extern int      dm_upgrade_right();
extern int      dm_downgrade_right();
extern int      dm_pending();
extern int      dm_obj_ref_hold();
extern int      dm_obj_ref_rele();
extern int      dm_obj_ref_query();

#endif  /* __STDC__ */

#endif /* ifndef KERNEL */

#ifndef _KERNEL
#ifdef __cplusplus
}
#endif
#endif

#endif	/* _DMAPI_H */
