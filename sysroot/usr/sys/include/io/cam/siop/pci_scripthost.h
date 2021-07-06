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
 * @(#)$RCSfile: pci_scripthost.h,v $ $Revision: 1.1.45.13 $ (DEC) $Date: 1999/06/21 20:48:33 $
 */
/* Definitions and declarations for host-SCRIPT interface for the 
 * NCR 53c810 CAM SCSI Driver.
 */

/* ---------------------------------------------------------------------- */

/* This is the main structure that controls host-SCRIPT communications.
 * Both the host and the SCRIPT have access to this and all
 * communication takes place via this structure.  Race conditions
 * between the host and SCRIPT is not a problem since SCRIPTS will
 * only be doing one thing at a time and will suspend while interrupting
 * the host.
 * Even though the chip deals mainly in 8 bit values, most of these
 * fields need to be 32 bits in order to contain pointers into host
 * memory (sigh).
 *
 * WARNING:  The offsets into this structure will be hard coded into
 * the SCRIPTS (do you know a better way?), so avoid changes like the
 * plague.  If you really must change it, remember to change the SCRIPTS.
 *
 * NOTE: Nothing used by the 710 can be 64 bits in length since the 
 * largest data object the 710 can try to deal with is 32 bits.
 * The jobdone and rpcjob fields can be 64 bits since it is not directly 
 * used by the 710 (it is really an opaque value used to identify the job).
 */

#ifndef _INSCRIPTS_

/* SIOP interrupts must be at or below level 4 */
#define splsiop		splbio

/* structure for queue of siopjobs.  */

typedef struct siopq {
	simple_lock_data_t	siopq_lock;
	struct siopjob *siopq_head;
	struct siopjob *siopq_tail;
} SIOP_Q;

struct siop_machdep {
	U32	(*md_init)();
	int	(*md_intr)();
	U32	(*md_csr_read)();
	void	(*md_csr_write)();
	U32	(*md_script_cntl)();
};

/* Macros for calling machine dependent functions */
#define SIOP_MD_INIT(S,C)		(*(S)->sh_machdep.md_init)((C))
#define SIOP_MD_INTR(S,C)		(*(S)->sh_machdep.md_intr)((C))
#define SIOP_MD_SCRIPT_CNTL(S,J,C,V)	(*(S)->sh_machdep.md_script_cntl)((S),(J),(C),(V))

#define SIOP_MD_CSR_READ_LOCKED(S,T,A)	 	\
	psiop_pci_csr_read(S,T,A)

#define SIOP_MD_CSR_READ(S,T,A)			\
	(*(S)->sh_machdep.md_csr_read)((S),(T),(A))

#define SIOP_MD_CSR_WRITE_LOCKED(S,T,A,V)	\
	psiop_pci_csr_write(S,T,A,V)

#define SIOP_MD_CSR_WRITE(S,T,A,V)		\
	(*(S)->sh_machdep.md_csr_write)((S),(T),(A),(V))

/* Definitions for CSR and SRAM read and write to get at a particular
 * byte/word/long through whatever method is used by the machine.
 * The machine dependent routines must interpret these.
 */
#define CSR_BYTE0	0x01
#define CSR_BYTE1	0x02
#define CSR_BYTE2	0x04
#define CSR_BYTE3	0x08

#define CSR_WORD0	0x03
#define CSR_WORD1	0x0C

#define CSR_LONG	0x0f

/* Commands for the machine dependent SCRIPTS manipulation routine. */
#define SIOP_SCRIPTS_LOAD	1
#define SIOP_SCRIPTS_CLEAR_SYNC	2
#define SIOP_SCRIPTS_SET_CACHE	3
#define SIOP_SCRIPTS_READ_RAM	4
#define SIOP_SCRIPTS_SET_DSP	5
#define SIOP_SCRIPTS_CACHE	6
#define SIOP_SCRIPTS_GET_DSP	7
#define SIOP_SCRIPTS_RESET_CHIP	8
#define SIOP_SCRIPTS_MAP_PADDR	9

/* SCRIPTS entry points.  These may be translated by the machine dependent
 * SCRIPTS control routine.
 */
#define SCRIPT_ENTRY_COLD     0               /* cold start address */
#define SCRIPT_ENTRY_WARM     0x8             /* warm start vector address */
#define SCRIPT_ENTRY_ERROR    0x10            /* error entry (for IDE) */
#define SCRIPT_ENTRY_DATA_MA  0x18            /* data M/A recovery */
#define SCRIPT_ENTRY_MSG_MA   0x20            /* msg M/A recovery */
#define SCRIPT_ENTRY_ABORT    0x28            /* general request abort */
#define SCRIPT_ENTRY_CONT     0x30            /* continue with request */

#define SIOP_TYPE_710	      0x0710
#define SIOP_TYPE_810         0x0810
#define SIOP_TYPE_810A        0x810a
#define SIOP_TYPE_825         0x0825
#define SIOP_TYPE_825A        0x825a
#define SIOP_TYPE_860         0x0860
#define SIOP_TYPE_875         0x0875
#define SIOP_TYPE_GENERIC     0x08ff

/*
 * MEMORY ALLOCATION DEFINES
 */
#define SIOP_JOB_PAGES_LOW	10	/* Low level 10 pages (100 jobs)	*/
#define SIOP_JOB_PAGES_MAX	50	/* No more than 50 pages (500 jobs)	*/
#define SIOP_JOB_PAGES_HIGH	20	/* High level 20 pages (200 jobs)	*/
				/* Allocation per job record (quad aligned	*/
#define SJ_MALLOC_CHUNK 	((sizeof(SIOP_JOB) + 7) & (~7))
				/* Number of job records per system RAM page	*/
#define SJ_JOBS_PER_PAGE	(PAGE_SIZE / SJ_MALLOC_CHUNK)

/*
 * Forward declaration
 */
typedef struct siopjob;

/*
 * Queue header of the adapter's free job records
 */
typedef struct siopjob_hdr {
	struct siopjob	*sjh_flink;
	struct siopjob	*sjh_blink;
} SIOP_JOB_HDR;

/*
 * Descriptor of the adapter's job record page
 */
typedef struct malloc_entry {
    struct siopjob  *me_first_job;	/* First record on the page		 */
    U64		     me_inuse_mask;	/* Page allocation mask (bit per record) */
} MALLOC_ENTRY;

typedef struct scripthost {
/*0*/	U32 		sh_intstatus;	/* interrupt status */
/*4*/	U32 		sh_rpcreq;	/* RPC request */
/*8*/	U32 		sh_rpcdata;	/* RPC request data */
/*C*/	U32 		sh_rpcreply;	/* RPC reply data */
/*10*/	volatile U32	sh_jobrequest;	/* new job to start */
/*18*/	struct siopjob *sh_jobdone;	/* newly completed job */
/*20*/	struct siopjob *sh_currentjob;	/* request currently active */
/*28*/  U64		sh_version;	/* Version Number */
/* the following fields are not accessed by the SCRIPTS */
	struct siop_machdep sh_machdep;	/* machine dependent routines */
	simple_lock_data_t sh_lock;	/* lock for this controller */
	struct bus *sh_ctlr;		/* bus adapter reference */
	SIM_SOFTC      *sh_softc;	/* SIM softc struct */
	U32		sh_flags;	/* some state info */
	U32		sh_min_period;	/* minimum transfer period allowed */
	U32		sh_max_period;	/* maximum transfer period allowed */
	U32		sh_max_offset;	/* maximum offset allowed */
	SIOP_Q		sh_outq;	/* output queue pointers */
	SIOP_Q		sh_msgoutq;	/* messages output queue pointers */
	SIOP_Q sh_activeq[NDPS_8][NLPT_8];/* array of queue of active jobs */
	U32		sh_clk_rate;	/* input clock rate (MHz *100) */
	U32		sh_clk_divisor;	/* input clock divisor bits */
	U32		sh_clk_period;	/* clock period for sync calculations */
	U32		sh_siop_type;	/* siop type */
	U32		sh_siop_rev;	/* siop rev */
	U32		sh_sel_tmo;	/* STIME0 bits for selection timeout */
	io_handle_t	sh_pci_config_base;	/* read-after-write address  */
/*
 * Data used for free job records management
 */
	SIOP_JOB_HDR	sh_free_list;	/* Free SIOP_JOB records	*/
	XPT_LOCK_DATA	sh_free_lk;	/* Free list lock structure	*/
	MALLOC_ENTRY	sh_malloc_entry[SIOP_JOB_PAGES_MAX]; /* Job record pages */
	U32		sh_malloc_total; /* Total job records allocated	*/        
	U32		sh_malloc_free; /* Count of free job records	*/         
	U32		sh_malloc_index; /* Current index for the job page */
	U32		sh_tagged;	/* tagged IO still active	*/
	U32		sh_bdr_tid_mask; /* target mas - bdr on		*/
} SCRIPT_HOST;

/* flags definitions */
#define SIOP_SH_ALIVE		0x01		/* it's alive		    */
#define SIOP_SH_RESET_ACTIVE	0x02		/* bus reset state active   */
#define SIOP_SH_ABORTED		0x04		/* SCRIPTS aborted	    */
#define SIOP_SH_FAST		0x08		/* fast SCSI bus	    */
#define SIOP_SH_LOADING		0x10		/* initial script loading   */
#define SIOP_SH_FAST20		0x20		/* Fast 20 capable	    */
#define SIOP_SH_LRGFIFO		0x40		/* chip has 536 byte fifo   */
#define SIOP_SH_BURST_DIS      	0x80		/* disable burst mode xfers */
#define SIOP_SH_DEVRS		0x100		/* BDR on some target	    */
#define SIOP_SH_RESET_SEEN	0x200		/* bus reset detected	    */    
#define SIOP_SH_POST_RESET	0x400		/* post-reset delay on	    */

/* Definition of RPC reply bit fields for the host since it can use 32
 * bit arithmetic to set these.  The SCRIPTS use the 8 bit versions
 * below.
 */
#define RPC_REPLY_ERROR	0x80000000
#define RPC_REPLY_ATN	0x40000000
#define RPC_REPLY_ACK	0x20000000

#else	/* #ifdef _INSCRIPTS_	*/

/* THESE OFFSETS ARE USED BY THE SCRIPTS!! CHANGE WITH EXTREME CAUTION!! */

#define SH_OFFSET_INTSTATUS	0x00
#define SH_OFFSET_RPCREQ	0x04
#define SH_OFFSET_RPCDATA	0x08
#define SH_OFFSET_RPCREPLY	0x0C
#define SH_OFFSET_JOBREQUEST	0x10
#define SH_OFFSET_JOBDONE	0x18
#define SH_OFFSET_CURRENTJOB	0x20
#define SH_OFFSET_VERSION	0x28

/* RPC reply bit definitions */
#define RPC_REPLY_ERROR	0x80
#define RPC_REPLY_ATN	0x40
#define RPC_REPLY_ACK	0x20

#endif	/* _INSCRIPTS_	*/

#define SIOP_SH_VERSION		1

/* ---------------------------------------------------------------------- */

/* SCRIPT Interrupt statuses , they are mutually exclusive.  I didn't
 * use enumerations here to make coding of the SCRIPTS easier.
 */

#define HARD_INTR	0		/* a chip intr causes this */
#define GOING_IDLE	1		/* about to wait for reselect */
#define JOB_DONE	2		/* a job has finished */
#define RPC_REQUEST	3		/* a request for help from host */
#define RESET_BUS	4	/* RESET bus to recover from hard error */

/* RPC Requests:
 * An RPC is really a request from a SCRIPT for host assistance with
 * some operation that is too complicated to be performed by the SCRIPT
 * (the prime example of this is locating a tagged request).  The SCRIPT
 * will set up the scripthost structure and then interrupt the host.
 * The host will perform whatever operation is requested, place the
 * result of this operation in the rpcreply field, and the continue
 * with the SCRIPT.  The SCRIPT will then take the reply value and
 * do withit whatever is necessary.  This works out nicely since
 * the 710 will suspend SCRIPT execution on any interrupt.  It works
 * very much like an RPC without too much complicated code.
 *
 * NOTE: RPC's are restricted to operations that can be performed
 * in the host interrupt routine.
 */

#define RPC_LOOK_TAG		1		/* lookup a tag */
#define RPC_MODIFY_PTR		2		/* modify data pointer */
#define RPC_CAL_SYNC		3		/* calculate sync parameters */
#define RPC_MSG_REJECT		4		/* received REJECT message */
#define RPC_MORE_DATA		5		/* get more data */
#define RPC_REST_PNTR		6		/* restore pointer values */
#define RPC_DEVICE_RESET	7		/* do a device reset */

/* ---------------------------------------------------------------------- */

/* Structure for keeping track of a SCSI request.  This resides in
 * host memory and contains all the information needed by the host
 * and the SCRIPT.
 * 
 * WARNING:  THE SJ_DATAI AND SJ_DOFFSET ARRAYS MUST BE ALIGNED ON A
 *	     256 BYTE BOUNDRY IN SCRIPTS RAM FOR THE SCRIPTS ADDRESSING
 *	     AND ARITHMATIC TO WORK.
 *
 * This structure contains all the information needed by the SCRIPTS to
 * completely process a request (with some not so minor aid from the host).
 * The layout of this structure has been optimized for SCRIPTS performance.
 * There is a bit of extra information here that makes the SCRIPTS
 * simpler to write (or even possible to write).
 *
 * BE VERY CAREFUL WHEN MODIFYING THIS STRUCTURE.  IF CHANGES ARE MADE
 * TO THIS STRUCTURE THEY MUST ALSO ME MADE TO THE SJ_OFFSET_* DEFINES
 * BELOW AND TO scripts/scriptram.h.
 *
 */

#ifndef _INSCRIPTS_

/* struct of each entry in the scatter/gather list.  This entry
 * is directly by the SCRIPTS so it must conform to the BLOCK MOVE
 * command's indirect data format.
 */

struct datai {
	U32	di_count:24;		/* transfer byte count */
	U32	di_mbz:8;		/* must be zero */
	U32	di_datap;		/* physical data pointer */
};


/* The DMA window size is 32 to make most effecient use of SCRIPTS RAM
 * memory and SCRIPTS data addressing.
 */
#define SIOP_DMA_WINDOW_SIZE	32

/* the maximum number of bytes that can be mapped in one scatter/gather
 * entry.
 */
#define SIOP_DMA_MAX_COUNT	0x1000000

/*
 * size of data buffers for command and message out.
 * must be in multiples of 8 (quadwords)
 */
#define SIOP_BUF_SIZE		16

typedef struct siopjob {
	/* the following are read/write by the SCRIPTS */
/*0*/	struct datai    sj_ldatai;	/* last DBC and DNAD */
/*8*/	U64		sj_loffset;	/* byte offset of start of ldatai */
/*10*/	struct datai    sj_sdatai;	/* saved DBC and DNAD */
/*18*/	struct datai	sj_msgoptr;	/* current msgout pointer */
/*20*/	U32		sj_ldatap;	/* last data pointer */
/*24*/	U32		sj_sdatap;	/* save data pointer */
/*28*/	U32		sj_err;		/* error code */
/*2C*/  U32		sj_status;	/* target status */
/*30*/	U64		sj_soffset;	/* saved pointer offset */
	/* The scatter/gather list is read-only (but can be modified
	 * locally) by the SCRIPTS.
	 */
/*38*/	struct datai 	sj_datai[SIOP_DMA_WINDOW_SIZE]; 
				/* actual data scatter/gather list */
	/* the following fields are read-only by the scripts */
/*138*/	U64		sj_doffset[SIOP_DMA_WINDOW_SIZE];
				/* offset for start of scattter/gather entry */
/*238*/	struct datai    sj_cmdptr;	/* pointer to SCB */
/*240*/	struct datai    sj_smsgoptr;	/* saved msgout ptr */
/*248*/	U32             sj_tid;		/* target id */
/*24C*/ U32		sj_lun;		/* logical unit number */
/*250*/	U32		sj_tagged;	/* request is tagged */
/*254*/	U32             sj_tag;		/* request tag */
/*258*/	U32             sj_term;	/* Terminate job if non-0 */
/*25C*/	U32             sj_abort;	/* abort job if non-0 */
/*260*/	struct siopjob  *sj_me;		/* self reference */
/*268*/	U64		sj_version;	/* Version number */
	/* the following fields are the cmd and message buffers for the io */
	/* Note: these need to be quad-word aligned */
	U8		sj_msgobuffer[SIOP_BUF_SIZE];
	U8		sj_cmdbuffer[SIOP_BUF_SIZE];
	/* the following fields are used only by the host */
        U64             sj_offset;	/* offset into data */
	U64             sj_count;	/* number of bytes currently mapped */

	SIOP_JOB_HDR	sj_link;	/* link to host's free job list */
	struct siopjob	*sj_next;	/* host queue links to the ...	*/
	struct siopjob	*sj_prev;	/* ... in progress list		*/

	struct siopq    *sj_myq;	/* pointer to my queue		*/
	struct sim_ws  	*sj_ws;		/* SIM working set for request  */
	SCRIPT_HOST	*sj_shp;	/* script host for this request */
	U8		*sj_msgobuf;	/* message output buffer */
	U8		*sj_cmdbuf;	/* command buffer	 */
	U32		sj_rejptr;	/* last byte rejected	 */
	U32		sj_callback;	/* Trigger callback if set	   */	
	dma_handle_t	sj_dma_data;	/* dma handle (chain) for the data */
/* ================================================ */
/* From this point onwards content must be retained */
/* ================================================ */
	dma_handle_t	sj_dma_job;	/* map job request	 */
	U32		sj_dma_jaddr;	/* physical address of job request */

	U32		sj_malloc_index; /* index to the allocation array */
	U32		sj_page_index;	/* index in the page-sized group  */
					/*  of the job records		  */
} SIOP_JOB;

#else	/* #ifdef _INSCRIPTS_	*/

/* THESE OFFSETS ARE USED BY THE SCRIPTS!!  CHANGE WITH EXTREME CAUTION */

#define SJ_COPYIN_SIZE		0x270
#define SJ_COPYOUT_SIZE		0x38
#define SIZEOF_DATAI		8

#define SJ_OFFSET_DOFFSET	0x138
#define SJ_OFFSET_CMDPTR	0x238
#define SJ_OFFSET_MSGOPTR	0x18
#define SJ_OFFSET_SMSGOPTR	0x240
#define SJ_OFFSET_SDATAI	0x10
#define SJ_OFFSET_LDATAI	0
#define SJ_OFFSET_SDATAP	0x24
#define SJ_OFFSET_LOFFSET	0x8
#define SJ_OFFSET_LDATAP	0x20
#define SJ_OFFSET_SOFFSET	0x30
#define SJ_OFFSET_ERR		0x28
#define SJ_OFFSET_STATUS	0x2C
#define SJ_OFFSET_TID		0x248
#define SJ_OFFSET_LUN		0x24C
#define SJ_OFFSET_TAGGED	0x250
#define SJ_OFFSET_TAG		0x254
#define SJ_OFFSET_TERM		0x258
#define SJ_OFFSET_ABORT		0x25C
#define SJ_OFFSET_ME		0x260
#define SJ_OFFSET_VERSION	0x268

#endif	/* _INSCRIPTS_	*/

#define SIOP_SJ_VERSION	 	1

/* ---------------------------------------------------------------------- */

/* The Address storage structure.  For each Host/PSIOP pair there has to
four common address spaces that the Host has to setup and save for the
PSIOP to run.  These four are: PSIOP Register space, PSIOP SCRIPT space,
HOST/PSIOP communication data space, and the PSIOP local data space.  These
address have to have valus for the Host's point of view and the PSIOP's 
point of view.  At initialization time the CAM PSIOP Machine Dependent
layer is responsible for allocation, setup, and storage of these common
areas and this data structure.

NOTE: At this time, the SCRIPT space and the communication data space are
combined.  There may be a system design that, for performance reasons,
the SCRIPT RAM and communication data space need to be in seperate "areas".
This will not be a trivial change!  The SCRIPT code expects to have the
communication data space referenced off the "START" point of the SCRIPT.
*/

#ifndef _INSCRIPTS_

typedef struct host_siop_addr
{
    /* The storage locations for the Host's side. */

    void * host_reg_addr;		/* where the CSRs etal are */
    void * host_script_addr;		/* where the SCRIPT instructions are */
    U32    host_script_size;		/* from the allocation */
    void * host_comm_addr;		/* where the comm data space is */
    U32    host_comm_size;		/* from the allocation */
    void * host_local_addr;		/* where the local data space is */
    U32    host_local_size;		/* from the allocation */
    dma_handle_t  host_script_handle;	/* dma handle for script space */
    dma_handle_t  host_comm_handle;	/* dma handle for comm space (UNUSED) */
    dma_handle_t  host_local_handle;	/* dma handle for local data space */
    dma_handle_t  host_R_Data_handle;	/* dma handle for R_script_data_Data */
    dma_handle_t  host_SCRIPT_handle;	/* dma handle for SCRIPT array */
    dma_handle_t  host_shp_handle;	/* dma handle for SCRIPT_HOST struct */

    /* The storage locations for the PSIOP's side. */

    void * siop_reg_addr;		/* where the CSRs etal are */
    void * siop_script_addr;		/* where the SCRIPT instructions are */
    void * siop_comm_addr;		/* where the comm data space is */
    void * siop_local_addr;		/* where the local data space is */
} HOST_SIOP_ADDR;

/*
 * SMP Lock Macros:
 */ 
#define SIOP_LOCK_INIT(lock, lockinfo)	\
	usimple_lock_setup ( &(lock), (lockinfo) )

#define SIOP_LOCK_TERMINATE(lock)	\
	usimple_lock_terminate ( &(lock) )

#define SIOP_LOCK(lock, s) {		\
	s = splbio();			\
	usimple_lock ( &lock );		\
}					

#define SIOP_UNLOCK(lock, s) { 		\
	usimple_unlock ( &lock );	\
	splx(s);			\
}
/*
 * Function prototypes - psiop_pci.c
 */
U32 psiop_pci_csr_lock_and_read(SCRIPT_HOST *shp, U64 mask, U64 addr);
void psiop_pci_csr_lock_and_write(SCRIPT_HOST *shp, U64 mask, U64 addr, U64 value);

#else	/* #ifdef _INSCRIPTS_	*/
#endif	/* _INSCRIPTS_		*/
