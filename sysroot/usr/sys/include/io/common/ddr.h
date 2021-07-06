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
/************************************************************************
  HINT: set tabstops to 4
 ************************************************************************/
/*
 * HISTORY
 */
/*
 * @(#)$RCSfile: ddr.h,v $ $Revision: 1.1.11.7 $ (DEC) $Date: 1998/08/12 16:13:24 $
 */

/************************************************************************
 *
 *  ddr.h
 *
 *  Generic Header for the Dynamic Device Recognition (DDR) subsystem.
 *
 ************************************************************************/

#ifndef _DDR_H_
#define _DDR_H_


/************************************************************************
  General Defines/Macros/Data Structures:
 ************************************************************************/

#define FAILED					TRUE
#define OK						FALSE

#define DDR_VERSION_1			1
#define DDR_VERSION_1_STR		"1"

#define DATABASE_FILE			"/etc/ddr.db"

/************************************************************************
  Locking macros
 ************************************************************************/

/*
 * lock to single-thread through database opens.
 */
#define	INIT_OPEN_LOCK				\
	XPT_INIT_LOCK(&ddr_dbase_open_lk, ddr_dbase_open_lkinfo)

#define	LOCK_OPEN					\
{									\
	XPT_LOCK (&ddr_dbase_open_lk);	\
}

#define	UNLOCK_OPEN						\
{										\
	XPT_UNLOCK (&ddr_dbase_open_lk);	\
}


#define	INIT_DDR_SCSIDEVS_LOCK	\
	XPT_INIT_LOCK(&ddr_scsidevs_lock, ddr_scsidevs_lockinfo)

#ifdef KERNEL

#define	LOCK_DDR_SCSIDEVS			\
{									\
	XPT_LOCK (&ddr_scsidevs_lock);	\
}

#define	UNLOCK_DDR_SCSIDEVS				\
{										\
	XPT_UNLOCK (&ddr_scsidevs_lock);	\
}
		

#define	DEV_DESC_LOCKINIT(ddptr)		\
	XPT_INIT_LOCK(&(ddptr)->dd_desc_lk,cam_ddr_dev_desc_lkinfo)

#define	DEV_DESC_LOCKTERM(ddptr)				\
	XPT_TERMINATE_LOCK(&(ddptr)->dd_desc_lk)	\

#define	DEV_DESC_LOCK(ddptr)			\
{										\
	XPT_LOCK (&(ddptr)->dd_desc_lk);	\
}

#define	DEV_DESC_UNLOCK(ddptr)			\
{										\
	XPT_UNLOCK (&(ddptr)->dd_desc_lk);	\
}

#else

#define LOCK_DDR_SCSIDEVS
#define UNLOCK_DDR_SCSIDEVS

#define DEV_DESC_LOCKINIT(x)
#define DEV_DESC_LOCKTERM(x)
#define	DEV_DESC_LOCK(x)
#define	DEV_DESC_UNLOCK(x)

#endif /* KERNEL */

/*
 * If not compiling as part of the kernel, we must be "utility" code
 */
#ifndef KERNEL
#define DDR_UTILITY
#endif /* KERNEL */


/*
 * generic bit array support
 */

typedef uchar	bitmap_t;
#define BITS_PER_BITMAP_T	(sizeof(bitmap_t) * 8)

#define BITMAPSZ(bitcnt)											\
		(((bitcnt)/BITS_PER_BITMAP_T) + 1)

#define IS_BIT_SET(array,bitno)										\
		((array)[(bitno)/BITS_PER_BITMAP_T] & 						\
				(1 << ((bitno) % BITS_PER_BITMAP_T)))

#define SETBIT(array,bitno)											\
		(array)[(bitno)/BITS_PER_BITMAP_T] |= 						\
				(1 << ((bitno) % BITS_PER_BITMAP_T))

#define CLRBIT(array,bitno)											\
		(array)[(bitno)/BITS_PER_BITMAP_T] &= 						\
				~(1 << ((bitno) % BITS_PER_BITMAP_T))

typedef struct density		density_t;
typedef struct ms_entry		ms_entry_t;


#define MAX_SCSI_DENS_TBLSZ		0x30

typedef struct scsi_dens_tbl_entry {
		char			*dens_name;		/* "name" of the density        */
        U32				dens_bpi;   	/* The density code             */
        U32             dens_blocking;	/* The blocking factor          */
} SCSI_DENS_TBL_ENTRY;

#define NUM_KNOWN_SCSI_DTYPES   (ALL_DTYPE_COMM + 1)


/*
 * Internationalization support
 */
#ifndef DDR_UTILITY			/* KERNEL */
#define MSTR(mid, s)		s
#else /* DDR_UTILITY */
#define MSTR(mid, s)		catgets(catd, 1, mid, s)
#endif /* DDR_UTILITY */


/************************************************************************
  Debug:
 ************************************************************************/

#ifdef DEBUG_ON
/*
   0 = none
   1 = critical
   3 = minimum trace
   4 = logical trace
   5 = full trace
   7 = more info
   9 = almost all
  10 = all
 */

#ifdef DDR_DECLARE_TABLES
int	dbg_lvl = 0;
#else  /* not DDR_DECLARE_TABLES */
extern int dbg_lvl;
#endif  /* not DDR_DECLARE_TABLES */

#define dbg(l,a)		if (dbg_lvl >= l) printf a

#else /* not DEBUG_ON */

#define dbg(l,a)

#endif /* not DEBUG_ON */


#endif /* not _DDR_H_ */


