/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_vppage.h,v $
 * Revision 1.1.52.2  2003/10/09  22:07:24  Jeffrey_Cilley
 * Merge Information:  Visual Merge: User specified default merge the submit tree v51bsupportos
 *     User Revision:  Jeffrey_Cilley_newubc_br:1.1.53.1 Local Ancestor:1.1.50.1
 *    Merge Revision:  v51bsupportos_br:1.1.52.1
 *   Common Ancestor:  1.1.50.1
 * 	[2003/10/09  22:05:03  Jeffrey_Cilley]
 *
 * 	Add new flags to pg_reserved field.
 * 	[2003/10/03  20:43:23  Jeffrey_Cilley]
 *
 * Revision 1.1.52.1  2003/09/11  18:34:39  Paul_Park
 * 	QAR 96804: Reorganize the NFS per-page bits to include a checksum,
 * 	and a valid bit.  Shrink written down to one bit too.
 * 
 * Revision 1.1.50.1  2000/10/12  17:14:23  Mike_Milicia
 *  * Add new definitions to accomodate redefinition of CFS file system
 *  * private area.
 * 
 * Revision 1.1.24.7  2000/02/14  20:49:19  Shashi_Mangalat
 * 	Merge from zincos_bl4:
 * 	Revision 1.1.39.2  2000/02/07  16:21:14  Diane_Lebel
 * 	. Make NFS and CFS private structs the same.
 * 
 * Revision 1.1.24.6  1999/12/10  19:33:20  Shashi_Mangalat
 * 	Add VPP_FREE to indicate pages being freed on I/O completion.
 * 
 * Revision 1.1.24.5  1999/05/06  19:35:29  Shashi_Mangalat
 * 	Merge of STEELOS_BL21:STEELOS_BL23
 * 	 Revision 1.1.17.6  1999/03/26  19:34:39  Stephen_Corbin
 * 	 Minor syntax correction. QAR 68847.
 * 	[1999/05/06  19:30:06  Shashi_Mangalat]
 * 
 * Revision 1.1.24.4  1999/03/09  23:49:42  Shashi_Mangalat
 * 	Merge of STEELOS_BL20:STEELOS_BL21
 * 	 Revision 1.1.17.5  1998/11/25  23:35:35  Shashi_Mangalat
 * 	 VM/NUMA scalability enhancements.
 * 	 Revision 1.1.17.4  1998/11/24  21:45:17  Larry_Scott
 * 	 Allow for using the vp_pfs field in the vm_vppage struct as two separate
 * 	 u_integer fields.  UFS previously used this field to store the block
 * 	 address (32-bit daddr_t).  UFS now uses the other 32-bit field as a
 * 	 timestamp (sched_tick based) in support of ufs_smoothsync.
 * 	[1999/03/09  23:44:52  Shashi_Mangalat]
 * 
 * Revision 1.1.24.3  1998/10/02  19:41:37  Shashi_Mangalat
 * 	Merge of STEELOS_BL16:STEELOS_BL18
 * 	 Revision 1.1.17.3  1998/05/11  15:57:31  Jeff_Colburn
 * 	 bmerge -jPTCOS_BL14:PTEV6OS_BL4 **
 * 	  Revision 1.1.19.2  1998/03/31  21:16:33  Tony_Bono
 * 	  Merged in umc support code needed to improve
 * 	  performance for specweb and other web type applications.
 * 	 [1998/05/11  15:45:33  Jeff_Colburn]
 * 	[1998/10/02  19:26:22  Shashi_Mangalat]
 * 
 * Revision 1.1.24.2  1998/08/26  12:44:32  James_Woodward
 * 	Merge of numaproj and zulu
 * 	[1998/07/29  20:19:19  James_Woodward]
 * 
 * Revision 1.1.21.3  1998/07/22  14:31:23  Shashi_Mangalat
 * 	Merge of NUMAPROJ with STEELOS_BL16.
 * 	[1998/07/22  14:17:15  Shashi_Mangalat]
 * 
 * Revision 1.1.21.2  1998/07/08  15:42:13  Shashi_Mangalat
 * 	Add support for UBC replication.
 * 	[1998/07/08  14:11:02  Shashi_Mangalat]
 * 
 * Revision 1.1.17.2  1998/03/10  23:52:12  Diane_Lebel
 * 	Added cfswrinfo and assoc macros for private field use by CFS.
 * 	[1998/03/06  23:59:00  Diane_Lebel]
 * 
 * Revision 1.1.13.2  1997/04/03  18:41:21  Shashi_Mangalat
 * 	Remove VPP_PMAPMOD and VPP_DEAD.
 * 	[1997/03/31  22:33:17  Shashi_Mangalat]
 * 
 * Revision 1.1.10.2  1994/11/07  18:55:40  Diane_Lebel
 * 	Added VPP_PMAPMOD to indicate to PUTPAGE if pmap_was_modified.
 * 	[1994/11/03  00:36:05  Diane_Lebel]
 * 
 * Revision 1.1.8.4  1994/02/23  20:21:12  Diane_Lebel
 * 	Moved nfs3wrinfo here from nfs_clnt.h
 * 	[1994/02/22  22:50:55  Diane_Lebel]
 * 
 * Revision 1.1.8.3  1993/08/26  17:47:14  Timothy_Burke
 * 	Sterling to gold merge.
 * 	[1993/08/26  17:45:12  Timothy_Burke]
 * 
 * Revision 1.1.8.2  1993/08/26  14:32:43  Timothy_Burke
 * 	Merge from sterling to gold.
 * 	[1993/08/20  17:20:16  Timothy_Burke]
 * 
 * Revision 1.1.7.2  1993/08/20  17:20:16  Timothy_Burke
 * 	Merge from sterling to gold.
 * 
 * Revision 1.1.6.2  1993/08/02  14:56:40  Paul_Shaughnessy
 * 	LADDIS performance
 * 	[1993/07/30  19:28:52  Paul_Shaughnessy]
 * 
 * Revision 1.1.3.5  1993/01/15  21:25:33  Robert_Picco
 * 	Added VPP_UBCIO to mark pages setup for I/O by UBC.
 * 	[93/01/14  13:19:39  Robert_Picco]
 * 
 * Revision 1.1.3.4  92/11/13  16:57:02  Ernie_Petrides
 * 	Add VPP_INVALID flag definition.
 * 	[92/11/10  16:56:50  Ernie_Petrides]
 * 
 * Revision 1.1.3.3  92/05/05  13:29:52  Al_Delorey
 * 	From Silver: AG_BL6_4
 * 	[92/05/05  13:29:22  Al_Delorey]
 * 
 * Revision 1.1.4.2  92/05/05  10:07:56  devbld_gsf
 * 	First AG_BL6_4 version.  Moved from Ag baselevel delivery tree.
 * 
 * Revision 1.1.2.3  92/04/24  09:33:13  Robert_Picco
 * 	UBC ref bit changes
 * 	[92/04/16  10:03:51  Robert_Picco]
 * 
 * Revision 1.1.2.2  92/02/26  16:13:22  Charles_Briggs
 * 	UBC merge.
 * 	[92/02/22  14:49:01  Charles_Briggs]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vm_vppage.h,v $ $Revision: 1.1.52.2 $ (DEC) $Date: 2003/10/09 22:07:24 $
 */
#ifndef	__VM_VPPAGE__
#define	__VM_VPPAGE__ 1

/*
 * Vnode specific information for page structure.
 */

struct vm_vppage {
	struct ppg_umc  *_pg_umc;	/* unified mbuf cluster/cache */
	union {
		vm_offset_t 	vp_pfs;		/* File system private data */
		struct {
			unsigned int blk;
			unsigned int stamp;
		} ufs_pfs;
	} _uvpp;
};

/*
 * Reserved flag fields.
 */
#define VPP_NOQUEUE     0x00
#define	VPP_FREE	0x01		/* Page is being freed */
#define	VPP_INVALID	0x02		/* Page is being invalidated */
#define	VPP_UBCIO	0x04		/* Page setup for I/O by UBC */
#define	VPP_MBUF	0x08		/* Page being used as m_cluster */
#define	VPP_REPL	0x10		/* replicated page */
#define VPP_ACTIVE      0x20
#define VPP_INACTIVE    0x40
#define VPP_STATE       0x60
#define vpp_state(PP)   ((PP)->pg_reserved & VPP_STATE)
#define vpp_clearstate(PP)                            \
        ((PP)->pg_reserved &= ~VPP_STATE)
#define vpp_setstate(PP,STATE)                        \
        (PP)->pg_reserved = ((PP)->pg_reserved & ~VPP_STATE) | STATE

/*#define	pg_addr		_upg._vppg.vp_addr*/
#define	pg_umc		_upg._vppg._pg_umc

#define pg_opfs		_upg._vppg._uvpp.vp_pfs
#define	pg_pfs		_upg._vppg._uvpp.ufs_pfs.blk
#define pg_stamp	_upg._vppg._uvpp.ufs_pfs.stamp

/*
 * This struct is used to store NFSv3 async write info in the vm_page
 * using the 64 bits (vm_offset_t) available for NFS private use in the
 * pg_pfs field.
 * NOTE: the definitions of nfs3wrinfo and cfswrinfo MUST be the same (is
 * this still true?)
 */
struct nfs3wrinfo {
	unsigned short nfs_pg_checksum;	/* 16 bits for checksum */
	unsigned nfs_pg_written:1;	/*  1 bit for page written */
	unsigned nfs_pg_sbz1:1;		/*  1 bit unused - PGCOUNTED */
	unsigned nfs_pg_cksumvalid:1;	/*  1 bit for checksum valid */
	unsigned nfs_pg_sbz:13;		/* 13 bits should be zero */
	unsigned int nfs_pg_verfseq;	/* 32 bits for write verifier */
};
#define	pgverfseq(_p) (*(struct nfs3wrinfo *)&(_p)->pg_opfs).nfs_pg_verfseq
#define	pgwritten(_p) (*(struct nfs3wrinfo *)&(_p)->pg_opfs).nfs_pg_written
#define	pgcksumvalid(_p) (*(struct nfs3wrinfo *)&(_p)->pg_opfs).nfs_pg_cksumvalid
#define	pgchecksum(_p)	(*(struct nfs3wrinfo *)&(_p)->pg_opfs).nfs_pg_checksum

struct cfswrinfo {
        short blkresv;
        unsigned short written;  /* Bit flags - see below */
        unsigned int verfseq;
};

#define CFS_PGWRITTEN	0x0001
#define CFS_PGCOUNTED	0x0002

#define BLKRSRV_PAGE(PP) (*(struct cfswrinfo *)&(PP)->pg_opfs).blkresv
#define cfspgwritten(PP) (*(struct cfswrinfo *)&(PP)->pg_opfs).written
#define cfspgverfseq(PP) (*(struct cfswrinfo *)&(PP)->pg_opfs).verfseq

#define	VP_PAGELIST	(12)
#define	VP_PAGELISTSIZE	(ptoa(VP_PAGELIST))

/*
 * returned by vm_ubc_memhigh
 */

#define	VM_UBC_PAGE_ALLOC	0x00			/* Allocate a page */
#define	VM_UBC_PAGE_FREE	0x01			/* Free dirty pages */
#define	VM_UBC_PAGE_LRU		0x02			/* LRU pages */

#endif	/* !__VM_VPPAGE__ */
