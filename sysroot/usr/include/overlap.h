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
 * @(#)$RCSfile: overlap.h,v $ $Revision: 1.1.16.1 $ (DEC) $Date: 2001/11/20 20:38:34 $
 */
#ifndef __OVERLAP_H
#define __OVERLAP_H
#include <sys/disklabel.h>



struct dec_partid {
	dev_t lsm_dev;			/* lsm device			*/
	short bus;			/* Bus				*/
	short adpt_num;			/* Adapter number		*/
	short nexus_num;		/* Nexus or node on adapter no.	*/
	short bus_num;			/* Bus number			*/
	short ctlr_num;			/* Controller number		*/
	short rctlr_num;		/* Remote controller number	*/
	short slave_num;		/* Plug or line number		*/
	short unit_num;			/* Ultrix device unit number	*/
	long  category_stat;		/* Category specific mask	*/
	struct partid_pt {
		long part_blkoff;	/* Beginning partition sector	*/
		long part_nblocks;	/* Number of sectors in partition */
		int part_fstype;	/* file system type; see <sys/disklabel.h> */
	} pt_part[MAXPARTITIONS];
};

/* lvm has been retired */
#define lvm_or_lsm_dev lsm_dev

#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

int fsl_swap_part_name(dev_t, char *);


/*
** Replacements for fsl_rawname() and fsl_unrawname().
** Note that these will return NULL if given filename does not
** translate to an existing file of the desired type (and the state
** of 'buf' is undefined).
** These do make stat() calls, thus are subject to unavailable
** filesystem hangs.
** Expects fully qualified pathname.
** samples: fsl_to_raw_name():
**   arg="/dev/rz3c"; if old file present, returns "/dev/rrz3c"
**   arg="/dev/rz3c"; if new name present, xlates eg. "/dev/disk/dsk03c"
**   "/dev/disk/dsk03c" returns "/dev/rdisk/dsk03c"
*/
extern char * fsl_to_raw_name(const char * name, char * buf, int sizeofbuf);
extern char * fsl_to_block_name(const char * name, char * buf, int sizeofbuf);

/*
** Tries to find a raw device name from given arg.  If not already,
** tries again, sticking "/dev/" in front it.  If still no such device,
** tries "/dev/rdisk", then, if still none, returns NULL.
*/
extern char * fsl_find_raw_name(const char * name, char * buf, int sizeofbuf);

#if defined(__cplusplus)
	   }
#endif  /* __cplusplus */


/* New functions defined for overlap checks. */

#if defined(__cplusplus)
extern "C" {
#endif  /* __cplusplus */

int swap_part_name(dev_t, char *);
int check_usage(const char *, int);
int set_usage(const char *, int, int);
int any_fdmns_overlap(char *);

#if defined(__cplusplus)
	   }
#endif  /* __cplusplus */


#define OV_CHECK_ALL    0
#define OV_CHECK_EXACT  1

#define FSL_DEV_NAME_LSM	"LSM"

#define	FSL_LSM_CDEV		"rvol"
#define	FSL_LSM_CDEV_LEN	4
#define	FSL_LSM_BDEV		"vol"
#define	FSL_LSM_BDEV_LEN	3

/*
 * Device naming disk directory names.
 */
#define	FSL_DVNMDSK_CDEV	"rdisk"
#define	FSL_DVNMDSK_CDEV_LEN	5
#define	FSL_DVNMDSK_BDEV	"disk"
#define	FSL_DVNMDSK_BDEV_LEN	4

#define OV_ERR_OPEN_OVERLAP	-1	/* Specified partition or an 
				 	 * overlapping partition is open. 
					 */
#define OV_ERR_INVALID_DEV	-2	/* Specified device is invalid 
				 	 * or does not exist.
					 */
#define OV_ERR_FSTYPE_OVERLAP	256	/* Overlapping partition(s) has fstype 
				 	 * field set. Could be more than one 
					 * partition. 
					 */
#define OV_ERR_MULT_FSTYPE_OVERLAP  257	/* Specified partition and Overlapping 
                        		 * partition(s) has fstype 
				 	 * field set. Could be more than one 
					 * partition. 
					 */
#define OV_ERR_INVALID_DSKLBL	258	/* Disklabel not found or is 
				 	 * corrupted. 	
					 */
#define OV_ERR_ADVFS_CHECK	259	/* Failure when checking overlap 
				 	 * with AdvFS domains. Either 
					 * /etc/fdmns or /etc/fdmns/<dom>
					 * for an active domain does not 
					 * exist. 
					 */
#define OV_ERR_SWAP_CHECK	260	/* Failure when checking overlap 
				 	 * with active swap devices. The 
					 * special device files associated 
					 * with active swap devices are 
					 * invalid. 
					 */

#define OV_ERR_DSKLBL_UPD	261	/* Could not update the disklabel */ 
#define OV_ERR_FDMNS_OVERLAP    262     /* overlaps existing AdvFS /etc/fdmns
                                         * entry
                                         */
#define OV_ERR_MAX            OV_ERR_FDMNS_OVERLAP


#endif /* !__OVERLAP_H */
