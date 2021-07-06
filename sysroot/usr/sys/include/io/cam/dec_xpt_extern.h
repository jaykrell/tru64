/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: dec_xpt_extern.h,v $
 * Revision 1.1.31.3  2006/03/14  22:55:57  Gokhan_Sozmen
 * 	FAST BOOT PROJECT
 * 	Add cam_c_scan_li for ccfg_scans.ccfg_scan_lock.
 *
 * Revision 1.1.31.2  2003/12/11  17:42:44  Charlotte_Richardson
 * 	Add definitions for xpt calls that register
 * 	scsi buses and controllers with hwmgr.
 * 	QAR #95999
 *
 * Revision 1.1.31.1  2002/10/04  12:03:18  Mike_Zaharee
 * 	Merge of v51asupportos-725-zaharee, 1.1.19.3 -> 1.1.19.4 delta.
 * 	Add locked_did parameter to camdb_devreg.  QAR 91730
 *
 * Revision 1.1.21.4  2002/05/30  23:16:02  Ashoke_Rampuria
 * 	Changes for compiler switch project
 *
 * Revision 1.1.21.3  2002/02/01  18:13:36  Mike_Zaharee
 * 	Add hsz_logic parameter to camdb_compare_wwids.
 *
 * Revision 1.1.21.2  2001/10/30  21:54:51  Robin_Miller
 * Merge Information:  Non-Visual Merge: User specified tree v51asupportos
 *     User Revision:  Robin_Miller_wcalphaos_br:1.1.22.1 Local Ancestor:1.1.19.1
 *    Merge Revision:  v51asupportos_br:1.1.19.2
 *   Common Ancestor:  1.1.19.1
 * 	[2001/10/23  16:40:21  Robin_Miller]
 *
 * Merge Information:  Non-Visual Merge: User specified revision 1.1.19.1
 *     User Revision:  wcalphaos_nightly:1.1.21.1 Local Ancestor: n/a
 *    Merge Revision:  1.1.19.1
 *   Common Ancestor:  1.1.10.4
 * 	[2001/10/19  16:19:33  Robin_Miller]
 *
 * Revision 1.1.21.1  2001/10/03  20:18:46  Jim_Goddard
 * 	parallel probe backport
 * 
 * Revision 1.1.19.2  2001/09/26  22:09:43  Robin_Miller
 * 	Additional update for QAR 86800:
 * 	Update function prototype for camdb_did_from_HSZ_wwid().
 * 
 * Revision 1.1.19.1  2001/09/25  17:01:07  Robin_Miller
 * 	Add external declarations for camdb_hsz_debug, camdb_hsz_panic,
 * 	and camdb_hsz_print variables.  Settable via sysconfig.
 * 
 * Revision 1.1.14.1  2001/08/09  17:26:58  Robin_Miller
 *  * Feature Tag: mo.upk_plat.002.starlight
 *  * Declare external ccfg flag to control single bit selection,
 *  * in support of the Proliant Starlight/Starbright storage shelf.
 * 
 * Revision 1.1.10.4  2000/01/13  19:30:36  William_Dallas
 * 	Remove cam_x_qhead lock extern. Nolonger needed.
 * 
 * Revision 1.1.10.3  1999/08/02  18:31:28  Peter_Keilty
 * 	Add function prototype xpt_initialize_cam3 back in, needed for
 * 	xpt_generic_lock initialization.
 * 	[1999/08/02  18:03:31  Peter_Keilty]
 * 
 * Revision 1.1.10.2  1999/07/30  19:27:09  Peter_Keilty
 * 	Remove lockinfo no longer needed cam_alloc_li and cam_gbl_alloc_li.
 * 	Remove function prototypes xpt_pool_alloc_thread,
 * 	xpt_alloc_qcam3, xpt_initialize_cam3, and xpt_pool_alloc3.
 * 	Changed xpt_callback_thread(void *).
 * 	[1999/07/30  14:12:52  Peter_Keilty]
 * 
 * Revision 1.1.2.15  1999/04/20  18:46:30  Fred_Knight
 * 	Add add_cam_dme_entry and add_cam_hba_entry function prototype.
 * 	[1999/04/19  22:27:54  Fred_Knight]
 * 
 * Revision 1.1.2.14  1999/02/04  22:17:47  Carolyn_Briglia
 * 	Added prototype for camdb_refresh_bus_paths,
 * 	camdb_refresh_paths, camdb_new_user_wwid
 * 	[1999/02/03  22:54:34  Carolyn_Briglia]
 * 
 * Revision 1.1.2.13  1998/12/04  15:58:01  Jamey_Poirier
 * 	Added a prototype for scsi_mgmt_locate.
 * 	[1998/12/04  15:56:39  Jamey_Poirier]
 * 
 * Revision 1.1.2.12  1998/11/18  19:15:30  Carolyn_Briglia
 * 	Added function prototypes for camdb functions
 * 	Changed camdb_hack_wwid camdb_wwid2hwname
 * 	[1998/11/17  14:05:17  Carolyn_Briglia]
 * 
 * Revision 1.1.2.11  1998/10/19  18:10:22  Carolyn_Briglia
 * 	added function prototype for scsi_mgmt_init, camdb_hack_wwid
 * 	modified prototype for camdb_common_support_cb
 * 	[1998/10/14  21:36:57  Carolyn_Briglia]
 * 
 * Revision 1.1.2.10  1998/04/27  20:51:42  Fred_Knight
 * 	Update prototype with new parameter.
 * 	[1998/04/27  19:31:37  Fred_Knight]
 * 	Add function prototype for camdb_did_from_HSZ_wwid().
 * 	[1998/04/24  19:23:20  Fred_Knight]
 * 
 * Revision 1.1.2.9  1998/04/22  20:06:20  James_Smart
 * 	Change syntax for camdb_wwid_bin2str() to accept a SCSI_WWID ptr
 * 	  rather than a SCSI_DID pointer.
 * 	[1998/04/17  21:25:45  James_Smart]
 * 
 * Revision 1.1.2.8  1998/04/14  18:52:24  Jamey_Poirier
 * 	Added prototype for camdb_common_support routine.
 * 	[1998/04/08  22:05:42  Jamey_Poirier]
 * 
 * Revision 1.1.2.7  1998/03/24  20:58:48  James_Smart
 * 	Add extern declaration for panicstr
 * 	[1998/03/24  15:30:36  James_Smart]
 * 
 * Revision 1.1.2.6  1997/10/07  17:00:39  James_Smart
 * 	CAM3 : Rework for CAM3
 * 	[1997/10/03  18:04:22  James_Smart]
 * 
 * Revision 1.1.2.5  1997/08/15  17:52:07  Fred_Knight
 * 	Add new camdb function prototypes
 * 	[1997/08/14  15:55:02  Fred_Knight]
 * 
 * Revision 1.1.2.4  1997/08/05  20:05:49  James_Smart
 * 	Remove reference to camminfo
 * 	Add exported routines moved from cam_config to ccfg
 * 	[1997/08/05  16:34:34  James_Smart]
 * 
 * Revision 1.1.2.3  1997/07/21  20:35:07  James_Smart
 * 	Remove edt_dir - no longer implemented
 * 	[1997/07/17  19:08:29  James_Smart]
 * 
 * Revision 1.1.2.2  1997/07/09  20:40:08  James_Smart
 * 	Creation
 * 	[1997/07/03  19:38:27  James_Smart]
 * 
 * 
 * $EndLog$
 */
/*
 * @(#)$RCSfile: dec_xpt_extern.h,v $ $Revision: 1.1.31.3 $ (DEC) $Date: 2006/03/14 22:55:57 $
 */
/*
 * This file contains the external data references and function prototypes
 * that are exported by cam modules.
 */

#ifndef _DEC_XPT_EXTERN_INCL_
#define _DEC_XPT_EXTERN_INCL_
#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************
 *
 * Available tagged sections:
 *
 ************************************************************************/

/************************************************************************
 * :tag::	module xpt.c
 ************************************************************************/

/* data */

extern U32			cam_subsystem_ready;

extern int			cam_compatmode;
extern int			cam_bootmsgs;

extern XPT_SIM_ENTRY		***cam_xse_tbl;
extern U32			cam_xse_tblsz;

extern SIM_ENTRY3		xpt_sim_entry;

extern XPT_CTRL			cam_conf_ctrl;
extern struct lockinfo		*cam_x_ctrl_li;
extern struct lockinfo		*cam_cplt_li;


/* routines  (note: also in xpt.h) */

int		cam_configure(cfg_op_t op, cfg_attr_t *indata,
			size_t indatalen, cfg_attr_t *outdata,
			size_t outdatalen);

I32		xpt_initialize(void);

void		xpt_callback_thread(void *);
void		scsiisr_init(void);
void		xpt_path_async(SCSI_PATH *path, I32 opcode,
			char *buffer_ptr, I32 buffer_len);
void		xpt_post_xpt_events(ASYNC_INFO *ap, U32 new_events);

#if XPT_DEBUG
void		xpt_insque(void *ws, void *header);
void		xpt_remque(void *ws);
#endif

/* CAM1 interface (API) routines given in cam1.h */

/* DEC specific utilities routines given in dec_common.h */

/************************************************************************
 * :tag::	module xpt3.c
 ************************************************************************/

CAM_U32                 xpt_initialize_cam3(void);

void 
xpt_ehm_register_scsi_bus(struct bus *, CAM_SCSI_BUS *);

void
xpt_ehm_register_scsi_bus_attributes(struct bus *, struct controller *);

void
xpt_ehm_register_scsi_ctlr(struct controller *, CAM_SCSI_BUS *);

int
xpt_hwm_scsi_ctlr_support_rtn(KSM_MEM_REQ_BUF *, caddr_t, size_t, caddr_t, size_t, ulong);

/* CAM3 interface (API) routines given in cam3.h */


/************************************************************************
 * :tag::	module ccfg.c
 ************************************************************************/

/* data */

extern struct lockinfo		*cam_c_ctrl_li;
extern struct lockinfo		*cam_c_qhead_li;
extern struct lockinfo		*cam_c_edt_li;
extern struct lockinfo		*cam_c_scan_li;
extern caddr_t			camstd[];
extern struct driver		camdriver;

extern int			cam_ccfg_debug;
extern int			cam_ccfg_singlebit;

extern CAM_EDT_ENTRY		xpt_async_list;
extern CAM_SCSI_BUS		xpt_cbus;

/* routines */

U32			ccfg_simattach(XPT_SIM_ENTRY *xse,
				struct controller *ctlr);
int			ccfg_slave(struct device *attach, caddr_t csr);
int			ccfg_attach(struct device *attach);
U32			ccfg_action(CCB_HEADER *ch);
U32			ccfg_initialize(void);
U32			ccfg_gettype(CCB_GETDEV *cg);
U32			ccfg_setasync(CCB_SETASYNC_VU *ca);
U32			ccfg_settype(CCB_SETDEV *cs);
U32			ccfg_edtscan(int scan_type, int bus, int target,
				int lun, U32 *topology_chg);
U32                     ccfg_xpt_action(CCB_HEADER *ch);
int			ccfg_ctlr_attach(struct controller *ctlr);
I32			ccfg_findluns(U32 bus, U32 sim_id);
CAM_SCSI_BUS *		ccfg_get_cbus(U64 bus);
int			cam_probe(caddr_t csr, struct controller *prb);
int			cam_detach_dev(struct controller *ctlr,
				struct device *device);
int			cam_detach_ctlr(struct bus *busp,
				struct controller *ctlr);

/************************************************************************
 * :tag::	module camdb.c
 ************************************************************************/

extern int		camdb_pr;
extern int		camdb_hsz_debug, camdb_hsz_panic, camdb_hsz_print;

void			camdb_init(void);
void			camdb_callback(int point, int order, ulong arg,
				ulong event_arg);
void			camdb_reinit(void);
void			camdb_write(void);
int			camdb_devreg(TRANSLATION *trans, U32 dev_subtype,
				SCSI_WWID *wwid, uint req_did, uint valid_addr,
				SCSI_DID * *locked_did );
SCSI_DID *		camdb_did_from_wwid(SCSI_WWID *wwid,
				SCSI_DID **avail_did, U32 req_did);
void			camdb_mark_path_stale(SCSI_PATH *path);
SCSI_WWID*		camdb_did_from_HSZ_wwid( wwid_hsz_this_other_t *wwid,
				TRANSLATION *trans, int changeit );
SCSI_DID *		camdb_did_from_lid(U32 lid);
SCSI_DID *		camdb_did_from_btl(U32 port_id, U64 target, U64 lun);
SCSI_PATH *		camdb_path_from_btl(U32 port_id, U64 target, U64 lun);

U32			camdb_wwid_bin2str(SCSI_WWID *wwid, caddr_t buffer,
				U32 buffer_len);
U32			camdb_wwid_str2bin(caddr_t str, SCSI_WWID *wwid);
int			camdb_compare_wwids(SCSI_WWID *wwid1, SCSI_WWID *wwid2, int hsz_logic);
int			camdb_common_support_cb(KSM_MEM_REQ_BUF*, caddr_t, 
                        	size_t, caddr_t, size_t, ulong);
char * 			camdb_wwid2hwname(SCSI_DID* did);
char *			camdb_hwname2strwwid(char *hwname);
int			camdb_hwname2did(char *hwname, SCSI_DID **pdid);
int			camdb_lid2hwid( U32 lid, long *hwid);
int			camdb_new_wwid(char *newname, SCSI_WWID **pnewwwid);
int			camdb_new_user_wwid(char *newname, SCSI_WWID **pnewwwid);
int			camdb_delete_did(SCSI_DID *);
int			camdb_mark_for_delete(SCSI_DID *did, int cam_del_flags);
int			camdb_refresh_paths(SCSI_DID *did);
int			camdb_refresh_bus_paths(U64 bus);

/************************************************************************
 * :tag::	module cam_config.c
 ************************************************************************/

extern struct driver		camdriver;


/************************************************************************
 * :tag::	module sim_config.c
 ************************************************************************/

extern void		init_sim_components(void);
extern int add_cam_hba_entry( char *, int(*)(char *, struct bus *), int(*)(SIM_SOFTC *),
                  		int(*)(SIM_SOFTC *), int(*)(struct bus *));

extern int add_cam_dme_entry( char *, int(*)(SIM_SOFTC *sc), int(*)(struct bus *));


/************************************************************************
 * :tag::	module cam_data.c
 ************************************************************************/

extern char			cam_ctlr_string[];

extern U32			ccfg_inquiry_retry_limit;
extern U32			ccfg_use_sdtr_inquiry;
extern U32			ccfg_wait_delay_loop;


/************************************************************************
 * :tag::	module cam_config.c
 ************************************************************************/

extern int				cam_pdrv_entries;
extern struct cam_peripheral_driver	cam_peripheral_drivers[];

extern void		init_cam_components(void);

/************************************************************************
 * :tag::	module scsi_mgmt.c
 ************************************************************************/

extern void		scsi_mgmt_init(void);
extern void		scsi_mgmt_locate(void *locate_data);

/************************************************************************
 * :tag::	module sim_xpt.c
 ************************************************************************/

/* COMMON sim interface definitions */

extern SIM_ENTRY3		dec_sim_entry;

extern CAM_U32		sim_init(SIM_ENTRY3 *sim_entry);
extern CAM_U32		sim_action(CCB_HEADER *ccb_hdr,
				CAM_VOID_OFFSET simha_handle);

/************************************************************************
 * :tag::	module arch/alpha/machdep.c
 ************************************************************************/

extern int			shutting_down;


/***********************************************************************n
 * :tag::	module bsd/kern_utctime.c
 ************************************************************************/

extern int			hz;


/***********************************************************************n
 * :tag::	module bsd/subr_prf.c
 ************************************************************************/

extern char			*panicstr;


/***********************************************************************n
 * :tag::	module arch/alpha/cpu.c
 ************************************************************************/

extern int			cpu_slots;



#ifdef __cplusplus
}
#endif
#endif /* _DEC_XPT_EXTERN_INCL_ */

