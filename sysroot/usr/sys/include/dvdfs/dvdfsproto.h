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
 * @(#)$RCSfile: dvdfsproto.h,v $ $Revision: 1.1.4.1 $ (DEC) $Date: 2000/01/21 15:59:31 $
 */
#ifndef _UFS_FS_PROTO_H_
#define _UFS_FS_PROTO_H_

/* forward declarations of structures to avoid warnings about
   structure definitions only within prototype scope */

struct vnode;
struct dvdnode;
struct fileid_d;
struct d_tag;
struct tag;
struct d_extent_ad;
struct extent_ad;
struct d_anchor_vdp;
struct anchor_vdp;
struct d_charspec;
struct charspec;
struct d_entity_id;
struct entity_id;
struct d_timestamp;
struct timestamp;
struct d_primary_vd;
struct primary_vd;
struct d_implementuse_vd;
struct implementuse_vd;
struct d_regid;
struct regid;
struct d_partition_d;
struct partition_d;
struct d_logical_vd;
struct logical_vd;
struct d_unallocsp;
struct unallocsp;
struct d_lb_addr;
struct lb_addr;
struct d_long_ad;
struct long_ad;
struct d_fileset_d;
struct fileset_d;
struct d_icbtag;
struct icbtag;
struct d_file_entry;
struct file_entry;


extern dvdfs_readdir(struct dvdnode *, struct file_entry *);
extern void dfe_to_fe(struct d_file_entry *, struct file_entry *);
extern void dtag_to_tag(struct d_tag *, struct tag *);
extern void dead_to_ead(struct d_extent_ad *, struct extent_ad *);
extern void davd_to_avd(struct d_anchor_vdp *, struct anchor_vdp *);
extern void dcharspec_to_charspec(struct d_charspec *, struct charspec *);
extern void deid_to_eid(struct d_entity_id *, struct entity_id *);
extern void dtimestamp_to_timestamp(struct d_timestamp *, struct timestamp *);
extern void dprimary_to_primary(struct d_primary_vd *, struct primary_vd *);
extern void diu_to_iu(struct d_implementuse_vd *, struct implementuse_vd *);
extern void dregid_to_regid(struct d_regid *, struct regid *);
extern void dpartition_to_partition(struct d_partition_d *, struct partition_d *);
extern void dlogical_to_logical(struct d_logical_vd *, struct logical_vd *);
extern void dunallocsp_to_unallocsp(struct d_unallocsp *, struct unallocsp *);
extern void dlbad_to_lbad(struct d_lb_addr *, struct lb_addr *);
extern void dlad_to_lad(struct d_long_ad *, struct long_ad *);
extern void dfsd_to_fsd(struct d_fileset_d *, struct fileset_d *);
extern void dicbtag_to_icbtag(struct d_icbtag *, struct icbtag *);
extern void dfe_to_fe(struct d_file_entry *, struct file_entry *);
extern void dfid_to_fid(struct d_fileid_d *, struct fileid_d *);
extern cvt_dvdtime_to_sec(struct timestamp *);

/***************
extern int dvdfs_init(void);
extern int dvdnodedrop(register struct dvdnode * );
extern int dvdnodeget(struct mount *  , ino_t  , struct dvdnode * * );
extern int dvdfs_lookup(struct vnode *  , register struct nameidata * );
extern int dvdnodeaccess(register struct dvdnode *  , register int  , struct ucred * );
extern int dvdfs_reclaim(register struct vnode * );
extern int dvdnodeput(register struct dvdnode * );
extern int dvdfs_getnumber(struct vnode *  , struct nameidata *  , ino_t * );
extern int dvdfs_readdir(register struct dvdnode *  , struct file_entry * );
****************/


#endif /* _UFS_FS_PROTO_H_ */

