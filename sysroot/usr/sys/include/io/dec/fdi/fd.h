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
#pragma ident "@(#)$RCSfile: fd.h,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 2000/12/07 14:40:37 $"

#ifndef _FD_H_
#define _FD_H_

#include <io/dec/fdi/fdi.h>

#define FD_VER 10

#define DO_DISKLABEL 			1


#define OFFSET_MASK (SECTOR_SIZE-1)    /* Sector-size mask.                  */

                                       /* Evaluates to non-zero if specified */
                                       /*  dev is for a 'very raw' device.   */
#define DEV_TO_VERY_RAW(D) ((minor(D)&0xFC)==0x40?1:0)

#define NFDI 1			       /* Number of interfaces supported     */
#define N_LUN 2                        /* Number of drives supported.        */

                                       /* Derives drive number from dev.     */
#define DEV_TO_LUN(D) (DEV_TO_VERY_RAW(D) ? minor(D)&0x03 : (minor(D)>>3&0x03))

#define VERY_RAW_LUN_TO_MINOR(L) (((L)&0x03)<<4)

#define N_PRT 8                        /* Number of partitions supported,    */
                                       /*  not including our internal pseudo */
                                       /*  partition ``VERY_RAW_PRT'', which */
                                       /*  means don't use partitions.       */

#define VERY_RAW_PRT N_PRT             /* Partition number of our internal   */
                                       /*  pseudo partition.                 */

#define N_PRT_TOTAL (N_PRT+1)          /* Number of partitions supported,    */
                                       /*  including the internal pseudo     */
                                       /*  partition ``VERY_RAW_PRT''.       */

                                       /* Derive partition number from dev.  */
#define DEV_TO_PRT(D) (DEV_TO_VERY_RAW(D) ? VERY_RAW_PRT : minor(D)&0x07)


/****  minphys routine uses (63 * 1024) the *****/
/****  fd_minphys routine is used in place  *****/
/****  of the minphys routine in order to   *****/
/****  use 64K size transfers               *****/
#define FD_MAXIO	(64 * 1024)    

/* Opening the following devs will enable/disable debugging cprintf()s.      */
#ifdef DEV_SPECIAL
# undef DEV_SPECIAL
#endif

#if FDCAM_DEBUG
                                       /* Returns non-zero if the specified  */
                                       /*  dev is a special device, the      */
                                       /*  opening of which enables all      */
                                       /*  debugging cprintf()s.             */
# define DEV_SPECIAL_ON(D) (minor(D)==0x44)
                                       /* Returns non-zero if the specified  */
                                       /*  dev is a special device, the      */
                                       /*  opening of which enables selected */
                                       /*  debugging cprintf()s.  Also,      */
                                       /*  reading from this devices will    */
                                       /*  return the entries in the fdcam   */
                                       /*  diag log.                         */
# define DEV_SPECIAL_TRACE(D) (minor(D)==0x45)
                                       /* Returns non-zero if the specified  */
                                       /*  dev is a special device, the      */
                                       /*  opening of which disables all     */
                                       /*  debugging cprintf()s.             */
# define DEV_SPECIAL_OFF(D) (minor(D)==0x46)
                                       /* Returns non-zero if the specified  */
                                       /*  dev is one of the above special   */
                                       /*  devices.                          */
# define DEV_SPECIAL(D) ((minor(D)&0xFC)==0x44)

# define DEV_SPECIAL_RST(D) (minor(D)==0x47)

#else

# define DEV_SPECIAL_ON(D)    (0)
# define DEV_SPECIAL_TRACE(D) (0)
# define DEV_SPECIAL_OFF(D)   (0)
# define DEV_SPECIAL(D)       (0)
# define DEV_SPECIAL_RST(D)   (0)

#endif


#ifndef PROBE_FAILURE
# define PROBE_FAILURE 0
# define PROBE_SUCCESS 1
#endif


#define VALID_CHECK av_forw
#define T_OFFSET(bp) (*(long*)&((bp)->av_back))

#define SINTL_ENA 1                    /* 0 == Disable software interleave.  */
                                       /* 1 == Enable software interleave if */
                                       /*  media is not interleaved.         */

#define RBUF_ENA 0                     /* 0 == Disable read buffering        */
                                       /* 1 == Enable read buffering         */
                                       /* 2 == Disable read buffering if it  */
                                       /*  appears that the media's interl.  */
                                       /*  is greater than 1.                */
#define RBUF_CLOSE 0                   /* 1 == Free buffer space when device */
                                       /*  is closed.  0 == Once acquired,   */
                                       /*  don't free it unless necessary to */
                                       /*  change its size.                  */
#define RBUF_CYL 0                     /* 1 == buffer cylinder, 0 == buffer  */
                                       /*  track.                            */

/* ************************************************************************* */

/* The following structure is used to keep track of the current state of a   */
/*  partition.  One instance exists for each partition.  One instatance also */
/*  exists for each drive for the ``VERY_RAW_PRT''.                          */

struct fdp_class {
    char plock;                        /* Lock access to partition.          */
                                       /*  0 == no lock, 1 = temporary lock, */
                                       /*  (until next I/O operation),       */
                                       /*  2 == lock until closeed or        */
                                       /*  specifically unlocked.            */

    struct fd_seek special_address;    /* special_address.mode has the value */
                                       /*  FD_SEEK_NOT_USED if "normal"      */
                                       /*  addressing is to be used.         */

    int p_nopen[2];                    /* [0] used for raw device, [1] for   */
                                       /*  block.                            */
};


struct fd_strategy_class {
    struct fdi_class* f;
    long st_blkno;                     /* Used by stratgegy, once port has   */
                                       /*  been acquired.                    */
    unsigned char* st_muaddr;
    struct proc* st_process;
    long cur_dev;
    int cur_lun;                       
    int cur_prt;                      
    struct fd_class *cur_fd;         
    struct fdp_class* cur_fdp;      
    int cur_vr;                    
    struct buf* cur_bp;
    int offset;
    struct fd_strategy_class* next;
    long obcount;			/* Original byte count.  Used for    */
					/*  partial transfers due to end of  */
					/*  disk or partition.  In such cases*/
					/*  bp->bcount is reduced to legal   */
					/*  maximum at the beginning         */
					/*  of the transfer.  The requested  */
					/*  count is needed in case the xfer */
					/*  fails.			     */
};

/* ************************************************************************* */


enum open_state {
    OS_DISABLED,
    OS_CLOSED,
    OS_OPENED,                         /* opened, but device never accessed. */
    OS_NO_MEDIA,
    OS_TAMPERED,
    OS_MEDIA,
    OS_PROBED,                         /* Media has been probed, fsb->fms    */
                                       /*  initialized, fdp->n_blocks        */
                                       /*  initialized, and current and      */
                                       /*  default partition tables          */
                                       /*  initialized, and lbl initialized  */
                                       /*  from default partition table.     */
    OS_PTBL_READ
};

#if DO_DISKLABEL
# if MAXPARTITIONS<8 || N_PRT<8
#  if MAXPARTITIONS<N_PRT
#   define N_LABEL_PRT (MAXPARTITIONS)
#  else
#   define N_LABEL_PRT (N_PRT)
#  endif
# else
#  define N_LABEL_PRT (8)
# endif
#else
# define N_LABEL_PRT (0)
#endif

/* The following structure is used to keep track of the current state of a   */
/*  drive.  One instance exists for each drive.                             */
struct fd_class {
    struct fdp_class fdp[N_PRT_TOTAL]; /* One for each partition, including  */
                                       /*  our internal "very raw" partition.*/
                                       /*  Invalid if fndelay                */
#if DO_DISKLABEL
    struct disklabel lbl;              /* The OSF disk label.                */
    int wlabel;                        /* non-zero == disklabel write enable.*/
#endif

    struct pt def_pt;                  /* Invalid if fndelay                 */
    struct pt cur_pt;                  /* Invalid if fndelay                 */
                                       /*  All internal computations are     */
                                       /*  based on contents of ``cur_pt'',  */
                                       /*  not on contents of ``lbl'' or     */
                                       /*  ``def_pt''.  If information is    */
                                       /*  obtained from an OSF disk label,  */
                                       /*  ``cur_pt'' must be updated        */
                                       /*  accordingly.                      */
    long n_blocks;                     /* Invalid if fndelay                 */
    struct fdcam_status_block fsb;     /* FDCAM status block for this device.*/
    char dlock;                        /* Lock access to drive.              */
                                       /*  0 == no lock, 1 = temporary lock  */
                                       /*  (until format complete),          */
                                       /*  2 == lock until closeed or        */
                                       /*  specifically unlocked.            */

    char prev_tamper;                  /*                                    */

    enum open_state os;

    int new_media;                     /* Non-zero if media changed since    */
                                       /*  previous drive-open time.         */
                                       /*  If < 0, information not known.    */

    long change_count;                 /* Number of media changes detected   */

    unsigned char* raw_buffer;         /* If opened, points to tmp buffer.   */

    long raw_buffer_block;             /* If non-negative, indicates that    */
                                       /*  ``raw_buffer'' contains up-to-date*/
                                       /*  copy of this block.               */

#if RBUF_ENA
#define CYL_BUF_DISABLED (-99999)
#define CYL_BUF_INVALID  (-99998)
    long cyl_buf_block;                /* If non-negative, indicates that    */
                                       /*  ''cyl_buf'' contains up-to-date   */
                                       /*  copy of the cylinder starting     */
                                       /*  at this block.                    */
                                       /*  If ==CYL_BUF_DISABLED, then cyl   */
                                       /*  caching is disabled.  If          */
                                       /*  == CYL_BUF_INVALID, then the      */
                                       /*  buffer contents are invalid.      */
    long cyl_buf_start;                /* Valid only if cyl_buf_block is     */
                                       /*  non negative.  This is the psn    */
                                       /*  of the first sector within the    */
                                       /*  buffer that is valid.             */
    long cyl_size;                     /* Cylinder size in number of sectors */
                                       /*  (or track size, if !RBUF_CYL).    */
    unsigned char* cyl_buf;            /* If non-zero, points to cyl buffer. */
                                       /*  This space is alloced at probe    */
                                       /*  time, possibly re-alloced at that */
                                       /*  time if a cylinder size changes.  */
                                       /*  This space is freed at close time */
                                       /*  if all partitions for current     */
                                       /*  drive have been closed.           */
                                       /*  Under OSF, the cylinder buf is    */
                                       /*  not re-allocated as the size      */
                                       /*  changes.  Rather, a buffer is     */
                                       /*  allocated at open time that is    */
                                       /*  large enough to contain any       */
                                       /*  cylinder size.                    */

    FDCAM_CB bio_cb;
    FDCAM_CB_TAG bio_cb_tag;
    long bio_psn;
    long bio_nsec;
    long bio_len;
    struct proc* bio_process;
    unsigned char* bio_buffer;

    long bio_bads;                     /* Cylinder caching disabled for PSN  */
                                       /*  within this range.                */
    long bio_bade;
#endif


    int nopen;                         /* Total number of opens.  Note, since*/
                                       /*  fd_close is only called at the    */
                                       /*  time of the last close, this      */
                                       /*  variable can only contain the     */
                                       /*  upper limit on how many times the */
                                       /*  drive might have been opened.     */

    int vr_nopen;                      /* Number of "very raw" opens.        */


    int tc_new_media_ok;               /* Used by tcheck.  Use synchronized  */
                                       /*  by calls to acquire_port and      */
                                       /*  release_port.                     */
    int tc_update;                     /*  "                                 */
    enum open_state tc_need;           /*  "                                 */
    dev_t tc_dev;                      /*  "                                 */
    FDCAM_CB tc_cb;                    /*  "                                 */
    FDCAM_CB_TAG tc_cb_tag;            /*  "                                 */

    struct fd_strategy_class *sc_list; /* Pointer to a linked-list of free   */
                                       /*  structures.                       */
    int sc_count;                      /* Number in sc_list or in current    */
                                       /*  use.  Just for debugging.         */
    struct device *fd_devp;            /* Pointer to the device structure    */
    char *fd_unique_name;              /* Pointer for ehm unique name        */
    char *fd_model;		       /* Pointer to model name              */
    u_int fd_openpart;		       /* open partition mask                */
    u_int fd_new_part;		       /* new  partition mask                */
    u_int fd_old_part;		       /* old  partition mask                */
    u_int fd_access;                   /* device access                      */
    u_int fd_max_xfer;		       /* max xfer capacity                  */
    void *fd_dev_handle;               /* device handle for hwc              */
};

/* ************************************************************************* */

/* The following structure is used to keep track of the current state of the */
/*  interface.  One instatance exists for each floppy interface.  Currently, */
/*  and probably forever, the MAXine system only supports one floppy         */
/*  interface.                                                               */

struct fdi_class {
    struct fd_class fd[N_LUN];         /* One for each drive.                */

    struct fdcam_class* fcp;           /* Pointer to main FDCAM struct.      */

    caddr_t reg;                       /* As provided by fd_probe call.      */
    struct controller* ctlr;           /*  "                                 */

    long max_cyl_size;                 /* The number of sectors per cylinder */
                                       /*  (or per track, if !RBUF_CYL)      */
                                       /*  in the largest supported media.   */
                                       /*  This value calculated at probe    */
                                       /*  time.                             */

    int did_init;                      /* non-zero if successful init.       */

    char st_last_in_error;             /* Non-zero if last call to strategy  */
                                       /*  resulted in an error.             */
                                       /*  This is only used between calls   */
                                       /*  to fdcam_acquire_port() and       */
                                       /*  fdcam_release_port().             */

    char st_already_acquired;          /* Non-zero if strategy should NOT    */
                                       /*  acquire/release port (i.e., nested*/
                                       /*  strategy call via rsblk()).       */
                                       /*  If >= 10, then allow multiple,    */
                                       /*  consecutive (not sub nested)      */
                                       /*  strategy calls, otherwise only    */
                                       /*  only one nested strategy call.    */

    char st_force_very_raw;            /* Force use of very-raw partition    */
                                       /*  regardless of minor number by     */
                                       /*  strategy routine.                 */
};

/*
 * This is the fdcam queue info struct
 */
typedef struct fdcam_que_info{
    struct fdcam_que_info *next;
    void *fdcam_buf_p;
}FDCAM_QUE_INFO;

typedef struct fdcam_buf
{
    struct buf bp;
    struct buf *orig_bp;
    void (*orig_biodone)(struct buf *);
    caddr_t orig_addr;
    struct proc *orig_proc;
    int orig_bcount;
    int retry;
    int flags;
    struct fdcam_buf *fbp;
    struct fdcam_que_info retry_info;
}FDCAM_BUF;

/*
 * The fifo queue which holds the fdcam_bp's to retry.
 * Added to head by fd_v_biodone function and 
 * removed from tail by the thread handling the retries
 */
typedef struct fdcam_que      {
        FDCAM_QUE_INFO *head;
        FDCAM_QUE_INFO *tail;
} FDCAM_QUE;


/*
 * Called by fd_v_biodone when a retry is needed.
 * This macro must be called with FDI_LOCK held.
 */
#define FDCAM_INSERT_QUE(Q, elem)                               \
MACRO_BEGIN                                                     \
        if(Q.head == NULL)       {       		        \
                Q.head = Q.tail = elem;                         \
        } else  {                                               \
                Q.tail->next = elem;                            \
                Q.tail = elem;                                  \
        }                                                       \
MACRO_END

/*
 * Called by the retry thread to remove a bp
 * from the retry queue.
 * This macro must be called with FDI_LOCK held.
 */
#define FDCAM_REMOVE_QUE(Q, elem)                             \
MACRO_BEGIN                                                     \
        if(Q.head == Q.tail)    {                               \
                elem = Q.head;                                  \
                Q.head = Q.tail = NULL;                         \
        }  else   {                                             \
                elem = Q.head;                                  \
                Q.head = elem->next;                            \
        }                                                       \
MACRO_END


extern int fdi_create_device(int);

extern int     fd_open(dev_t, int, int);
extern int     fd_close(dev_t, int, int);
extern void    fd_bstrategy(struct buf*);
extern int     fd_read(dev_t, struct uio*);
extern int     fd_write(dev_t, struct uio*);
extern int     fd_ioctl(dev_t, unsigned int, caddr_t, int);
extern daddr_t fd_psize(dev_t);

extern int     fd_slave(struct device*, caddr_t);
extern int     fd_attach(struct device*);
extern char   *fdinfo (int, int *);
extern int     fdintr(int);
extern void    fdcam_nothing(void);

#endif /* FD_INCLUDE */
