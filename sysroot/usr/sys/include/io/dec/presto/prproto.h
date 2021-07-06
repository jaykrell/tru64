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
 * @(#)$RCSfile: prproto.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 1999/01/29 17:11:02 $
 */

#ifndef	_PRPROTO_H_
#define	_PRPROTO_H_

#include	<sys/types.h>
#include	<sys/sysconfig.h>
#include	<ksm/ksm.h>
#include	<io/common/hwc_reg.h>

#ifdef	__cplusplus
extern "C" {
#endif

extern caddr_t kmem_fast_alloc(register caddr_t **pool, int size, int count);
extern void kmem_fast_free(register caddr_t *pool, register caddr_t buf);
extern void prdisable(void);
extern void prenable(void);
static void clearstats(void);
extern void bptonvbp(register struct buf *bp);
extern void prinit(u_int size);
extern void prnvinit(u_int size);
extern void prbrelse(register struct buf *bp);
extern void prbwrite(register struct buf *bp, int wflag, int pflag);
extern void prprepareio(register struct buf *bp);
extern int prreap(void);
extern void prbwait(register struct buf *bp);
extern void prbremfree(register struct buf *bp);
extern int prflushdev(dev_t dev, int inval);
extern void prreset(int verify);
extern void prreset_finish(void);
extern void prreboot(struct nvh *nvh);
extern struct buf *prbuflookup(dev_t dev, register daddr_t blkno, int size);
extern struct buf *prbufsearch(dev_t dev, register daddr_t blkno, int size);
extern void prwritedirty(int nwrite);
extern void pr_cluster_wiodone(register struct buf *cbp);
extern void prflush(dev_t dev, off_t off, int len, int flag);
extern struct buf *prbufalloc(dev_t dev, daddr_t blkno, int size);
extern int prprobe(void);
extern int prattach(void);
extern int prverifydev(dev_t dev, void (*xxstrategy)());
extern int prverify_close(dev_t dev);
extern void prbatts(void);
extern void set_battery_mode(enum battery_modes mode);
extern int checkbatteries(void);
extern int propen(dev_t dev, int flag);
extern int PRclose(dev_t dev, int flag, int fmt, int (*xxclose)(), struct prtab *xxprtab, struct ucred *cred, void *priv);
extern int PRclose_ddi(dev_t dev);
extern int prclose(dev_t dev, struct prtab *xxprtab);
extern int PRstrategy(register struct buf *bp, register void (*xxstrategy)());
extern int pr_rw_common(dev_t cdev, struct prtab *xxprtab);
extern int PRread(dev_t dev, struct uio *uio, int (*xxread)(), struct prtab *xxprtab, int ioflag, void *priv);
extern int PRread_ddi(dev_t dev);
extern int PRwrite(dev_t dev, struct uio *uio, int (*xxwrite)(), struct prtab *xxprtab, int ioflag, void *priv);
extern int PRwrite_ddi(dev_t dev);
extern int prdown(void);
extern void presto_reboot(void);
static void mkuprtab(register struct uprtab *uprtab, register struct prtab *prtab, register struct prunit *prunit);
extern int prioctl(dev_t dev, unsigned int cmd, caddr_t data, int flag);
extern int presto_init(caddr_t addr, int size, int mapped, int cached, int machineid);
extern int prprobe_rw(char *s, unsigned int fill);
extern int printnvh(char *str);
extern int pokel(int *lp, int lval);
extern int peekl(int *lp, int *lval);
extern void prnvram_rdwrtest(void);
extern int prdirectio(dev_t dev, int *error);
extern int prenabled(major_t bdev);
extern void presto_smp_init(void);
extern void pr_io_size(dev_t bdev);

extern int presto_configure(cfg_op_t op, caddr_t indata, size_t indata_size, caddr_t outdata, size_t outdata_size);
void pr_callback(int, int, ulong, ulong);
int  pr_reg_diskmajor(HWC_DISK_MAJOR*);
int  presto_close(dev_t, int, int, struct ucred*, void*);
void presto_strategy(struct buf*);
int  presto_read(dev_t, struct uio*, int, void*);
int  presto_write(dev_t, struct uio*, int, void*);

#ifdef	__cplusplus
}
#endif

#endif	/* _PRPROTO_H_ */
