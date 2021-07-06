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
 *	@(#)$RCSfile: vfs_proto.h,v $ $Revision: 1.1.78.2 $ (DEC) $Date: 2002/01/29 21:20:02 $
 */ 

#ifndef _SYS_VFS_PROTO_H_
#define _SYS_VFS_PROTO_H_
#include <standards.h>
#include <sys/mount.h>
/* Forward declarations of enum/structure types so
   function prototypes are happy */
/* from files:
   vfs_bio.c
   vfs_cache.c
   vfs_conf.c
   vfs_flock.c
   vfs_subr.c
   vfs_vnops.c
 */
struct  buf;
struct  eflock;
struct  file;
struct  filock;
struct  flino;
struct  blkpids;
struct  nameidata;
struct  proc;
struct  stat;
struct  ucred;
struct  uio;
struct  utask_nd;
struct  vattr;
struct  vfsops;
struct  vnode;
struct  vnodeops;
struct  vfs_ubcops;

#ifdef __cplusplus
/* get or define enums since they can't be forward declared in C++ */
#include <sys/uio.h>     /* to pick up uio_seg enum */
#include <sys/vnode.h>   /* to pick up vtagtype and vnuio_rw enum */
#else
/* forward decls for regular C code */
enum  uio_seg;
enum  vnuio_rw;
enum  vtagtype;
#endif

_BEGIN_CPLUSPLUS
extern void bawrite(struct buf * );
extern void bdwrite(struct buf *  , struct vnode * );
extern int bfree(struct buf * );
extern void bgetvp(struct vnode *  , struct buf * );
extern int biowait(struct buf * );
extern int bread(struct vnode *  , daddr64_t  , int  , struct ucred *  , struct buf * * );
extern int breada(struct vnode *  , daddr64_t  , int  , daddr64_t  , int  , struct ucred *  , struct buf * * );
extern void brelse(struct buf * );
extern void brelvp(struct buf * );
extern int bwrite(struct buf * );
extern int cache_lookup(struct nameidata * );
extern int chk_granted(struct flino *  , struct vnode *  , int );
extern int cleanlocks(struct vnode *, pid_t, int);
extern void clear_vlocks(struct vnode * );
extern int deadflck(struct blkpids *  , pid_t  , pid_t  , u_int );
extern void delflck(struct flino *  , struct filock *  , struct vnode * );
extern int do_grant_locks(struct eflock * );
extern int flckadj(struct flino *  , struct filock *  , struct eflock *  , struct vnode *  , int  , pid_t , int );
extern void flckinit(void);
extern void freefid(struct flino * );
extern int getflck(struct vnode *  , struct eflock *  , off_t  , pid_t  , int );
extern int getnewvnode(enum vtagtype  , struct vnodeops *  , struct vnode * * );
extern int incore(struct vnode *  , daddr64_t );
extern int klm_callbacks(void);
extern int locked(struct vnode *, struct eflock *, pid_t, int );
extern int mntbusybuf(struct mount * );
extern void mntflushbuf(struct mount *  , int );
extern int mntinvalbuf(struct mount * );
extern void nchinit(int);
extern void nchshutdown(void);
extern int nddup(struct nameidata *  , struct nameidata * );
extern int ndinit(struct nameidata *  , struct utask_nd * );
extern int ndrele(struct nameidata * );
extern void print_flino(struct flino * );
extern void print_flock(struct eflock * );
extern int quotactl(struct proc *  , void *  , long * );
extern void reassignbuf(struct buf *  , struct vnode *, int );
extern int regflck(struct eflock *  , struct filock * );
extern int setflck(struct vnode *  , struct eflock *  , int  , off_t  , pid_t  , int );
extern int vflush(struct mount *  , struct vnode *  , int );
extern int vbusycheck(struct mount *, int );
extern int vfs_noop(void);
extern int vfs_nullop(void);
extern int vfsinit(void);
extern int vgetm(struct vnode *  , int );
extern int vgone(struct vnode *  , int  , struct vnodeops * );
extern int vinvalbuf(struct vnode *  , int );
#ifdef _KERNEL
extern int vn_close(struct vnode *, int , struct ucred *);
extern int vn_ioctl(struct file *  , unsigned int  , caddr_t , int *);
extern int vn_select(struct vnode *  , int * , int *  , int , struct ucred * );
#else
extern int vn_close(struct file * );
extern int vn_ioctl(struct file *  , unsigned int  , caddr_t , long *);
extern int vn_select(struct vnode *  , short *  , short *  , int , struct ucred *);
extern int vfs_post_kernel_event(char *  , char *  , char *);
#endif
extern int vn_fhtovp(fhandle_t *  , int  , struct vnode * * );
extern int vn_flock(struct file *  , int );
extern int vn_kopen(struct vnode *  , int  , int * );
extern int vn_open(struct nameidata *  , int  , int );
extern int vn_rdwr(enum vnuio_rw  , struct vnode *  , caddr_t  , int  , off_t  , enum uio_seg  , int  , struct ucred *  , int * );
extern int vn_read(struct file *  , struct uio *  , struct ucred * );
extern int vn_stat(struct vnode *  , struct stat * );
extern int vn_write(struct file *  , struct uio *  , struct ucred * );
extern int vn_writechk(struct vnode * , int );
extern int vprint(char *  , struct vnode * );
extern int wait_for_vxlock(struct vnode *  , int );
extern int wait_for_vxlock2(struct vnode *  , int , int );
extern struct buf * getblk(struct vnode *  , daddr64_t  , int );
extern struct buf * geteblk(int );
extern struct buf * getnewbuf(void);
extern struct filock * blocked(struct filock *  , struct eflock *  , struct filock * *  , int  , pid_t  , struct blkpids * * );
extern struct filock * insflck(struct flino *  , struct eflock *  , struct filock *  , struct vnode *  , int  , pid_t , int );
extern struct flino * allocfid(struct vnode * );
extern struct flino * findfid(struct vnode * );
#ifndef __VMS
extern struct mount * getvfs(fsid_t * );
#else	/* __VMS */
extern struct mount * getvfs(fhandle_t * );
#endif	/* __VMS */
extern void allocbuf(struct buf *  , int );
extern void bio_init(void);
extern void biodone(struct buf * );
extern void bufstats(void);
extern void cache_enter(struct nameidata * );
extern void cache_purge(struct vnode * );
extern void clear_vxlock(struct vnode * );
extern void delsleeplck(pid_t, struct eflock * );
extern void free_blkpids(struct blkpids * );
extern void insmntque(struct vnode *, struct mount *, struct vfs_ubcops *);
extern void kill_proc_locks(struct eflock *, int );
extern void update_sleeper_blkpids(struct vnode *, struct eflock *, pid_t, int);
extern int  vclean(struct vnode *  , long  , struct vnodeops * );
extern void vflushbuf(struct vnode *  , int );
extern void vflushbuf_aged(struct vnode *, int, u_int, u_int);
extern void vfree(struct vnode * );
extern void vfs_mountroot(void);
extern int  vfs_name_hash(char *, char *, u_long *);
extern void vn_funlock(struct file *  , int );
extern void abort_vget(struct vnode *);
extern void vrele(struct vnode * );
extern void smoothsync_thread(void);
/* Not included for the moment (type promotion issues to resolve):
   vfssw_add
   vfssw_del
   vattr_null (declared, without arguments, in <sys/vnode.h>)
*/
_END_CPLUSPLUS

#ifdef  _KERNEL
#if defined(_USE_KERNEL_PROTOS)

extern int vfinddev(dev_t dev, enum vtype type, struct vnode * *vpp);
extern void vrele(struct vnode *vp);

extern void ddi_init_uio(struct vnode *, int, struct uio *, int);
extern int namei(struct nameidata *ndp);
extern void waitforio(struct vnode *vp);
extern int vfssw_del(short fstype);

#endif /* defined(_USE_KERNEL_PROTOS) */
#endif  /* _KERNEL */

#endif /* _SYS_VFS_PROTO_H_ */
