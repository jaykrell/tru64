/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: marvel_cpu.h,v $
 * Revision 1.1.13.5  2004/02/04  16:51:50  Aaron_Biver
 * 	QAR 97575: Add mchk_pmchkf to mchk control structure for
 * 	holding a pointer to the logout frame.
 * 	Fix typo in debug printf definition
 * 	[2004/01/30  15:28:28  Aaron_Biver]
 *
 * Revision 1.1.13.4  2003/09/02  16:00:32  Martine_Silbermann
 * 	Fix for QAR 96245 - Erroneous PCI errorlog subpackets.
 * 	Some of the field types in the error log packet descriptions were wrong.
 *
 * Revision 1.1.13.1  2002/11/08  20:24:47  Rajesh_R
 * 	Added io7_uph_pid in the mv_mcheck_control structure to keep track of the
 * 	io7 pid.
 *
 * Revision 1.1.4.11  2002/05/29  20:13:04  Martine_Silbermann
 * 	Added the definitions required for the error log subpackets headers
 * 	for PCI and caps.
 *
 * Revision 1.1.4.10  2002/04/09  17:22:38  Rajesh_R
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Rajesh_R_wc_update_br:1.1.9.2 Local Ancestor:1.1.4.8
 *    Merge Revision:  wcalphaos_br:1.1.4.9
 *   Common Ancestor:  1.1.4.8
 * 	[2002/04/09  16:35:13  Rajesh_R]
 *
 * 	Added mv_align_for_mvfi in mv_mcheck_control for allignment. This
 * 	is required as mvfi has a dependency on the order and size of the
 * 	structure.
 * 	[2002/04/09  16:14:03  Rajesh_R]
 *
 * Revision 1.1.4.9  2002/04/09  00:08:55  Rajesh_R
 * 	Added machine check support environmental events.
 * 
 * Revision 1.1.4.8  2002/03/18  16:23:53  Rajesh_R
 * 	Additional Marvel cleanup (fix multiple include extansiation
 * 	of "struct reg_format.....".
 * 	Removed old commented out version of rbox_nsew_err/
 * 
 * Revision 1.1.4.7  2002/02/18  20:49:30  Rajesh_R
 * 	Marvel source file cleanup.
 * 	Add defines for CRD throttle binlog subpacket.
 * 
 * Revision 1.1.4.6  2002/01/29  19:25:06  Martine_Silbermann
 *  *	Added support for PCI-X, MSI and AGP subpkts format
 *  *	(used in mvcpu_consprint() )
 *  *
 * 
 * Revision 1.1.4.5  2002/01/24  23:11:14  Rajesh_R
 * 	Update some Interrupt enable method comments.
 * 
 * Revision 1.1.4.4  2001/12/14  18:16:37  Aaron_Biver
 * 	Move interrupt-enable constants & vars here from
 * 	marvel_cpu.c
 * 
 * Revision 1.1.4.3  2001/11/16  18:30:30  Rajesh_R
 * Merge Information:  Non-Visual Merge: User specified default merge the submit tree wcalphaos
 *     User Revision:  Rajesh_R_wc_buildbreak_br:1.1.6.1 Local Ancestor:1.1.4.1
 *    Merge Revision:  wcalphaos_br:1.1.4.2
 *   Common Ancestor:  1.1.4.1
 * 
 * Revision 1.1.4.2  2001/11/15  14:39:49  Greg_Bellows
 * 	Remove the unused rpb cluster definitions due to imcompatibility
 * 	with the distributed memory cluster support changes.
 * 
 * Revision 1.1.6.1  2001/11/14  21:17:01  Rajesh_R
 * 	Change CSR bit to text strings for RES<14> and RES<19>
 * 	to their actual names (PALSTV and PALIPI).
 * 	Add Marvel Fault Insertion (MVFI) support to machine check
 * 	control structure.
 * 	Minor comment cleanup.
 * 	Bix bug in bit to text definitions for rbox_NSEW_cfg.
 * 
 * Revision 1.1.4.1  2001/10/24  22:18:08  Rajesh_R
 * 	Created this file (cloned from Wildfire) for Marvel support.
 * 
 * 
 * $EndLog$
 */
#pragma ident "@(#)$RCSfile: marvel_cpu.h,v $ $Revision: 1.1.13.5 $ (DEC) $Date: 2004/02/04 16:51:50 $"



#ifndef __ARCH_ALPHA_HAL_MARVEL_CPU_H__
#define __ARCH_ALPHA_HAL_MARVEL_CPU_H__

/* MV_TODO: hack to make marvel_srvmgmt.c compile. */
#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* 
 * Machine check structures, defines 
 */

/*
 * System Specific Machine Check Error Codes
 */
#define MV_MCHK_SYS_UNCORR	0x202
#define MV_MCHK_SYS_CORERR	0x204
#define MV_MCHK_SYS_EVENT	0x206
#define MV_MCHK_SUMM_MEMERR	0x4

/* Bits 31:16 are Marvel's 660,670 machine-check reason mask */
#define MV_MCHECK_REASON_MASK 0x000000000000FF00L

/* 
 * Marvel Machine Check Logout Frames
 */

/* 
 * Marvel uncorrected error log data structures
 */
struct el_mv_ev7_subpkt_hdr {		/* Common header for all subpackets   */
    u_short	elhdr_subpak_length;	/* Subpacket byte count               */
    u_short	elhdr_subpak_class;	/* Subpacket registered class         */
    u_short	elhdr_subpak_type;	/* Subpacket registered type          */
    u_short	elhdr_subpak_rev;	/* Subpacket revision                 */
};

struct el_mv_ev7_logout_header_frame_subpacket {
    u_short	elhfs_subpak_length;	/* subpacket byte count - 0x0018      */
    u_short	elhfs_subpak_class;	/* Class registered as 0x0005         */
    u_short	elhfs_subpak_type;	/* Type registered as 0x0013          */
    u_short	elhfs_subpak_rev;	/* First revision is 0x0001           */
    u_int	elhfs_frame_size;	/* total byte count of PAL built pkt  */
					/* Frame Flags 32-bit wide field      */
    int		elhfs_sbz1:28;		/* should be zero                     */
    int		elhfs_recover:1;	/* 6A0/6B0 machine check successful   */
    int		elhfs_sz2:1;		/* PAL logs this mchk to MBM?         */
					/*            1 = no, 0 = yes         */
					/* Settable by the OS, since this     */
					/* frame lives in memory all the time */
					/* and is pointed to by the rpb.      */
    int		elhfs_2nd_err:1;	/* Second correctable error occurred  */
    int		elhfs_retry:1;		/* ok to dismiss MCHK and resume      */
    u_int	elhfs_cpu_offset;	/* byte offset of CPU specific info   */
    u_int	elhfs_system_offset;	/* byte offset of SYSTEM specific info*/
};

struct el_mv_ev7_pal_specific_subpacket {
    u_short	epss_subpak_length;	/* subpacket byte count - 0x0048      */
    u_short	epss_subpak_class;	/* Class registered as 0x000e         */
    u_short	epss_subpak_type;	/* Type registered as 0x0001          */
    u_short	epss_subpak_rev;	/* First revision is 0x0001           */
    u_int	epss_mchk_code;		/* the usual suspects (e.g., 0x204)   */
    u_int	epss_subpkt_count;	/* number of SYS and CPU subpackets   */
    u_long	epss_cpu_whami;		/* PID of CPU reporting error         */
    u_long	epss_rbox_whami;	/* CPUs position win IP router's mesh */
    u_long	epss_rbox_int;		/* RBOX interrupt status register     */
    u_long	epss_exc_addr;		/* instruction PC of trap or fault    */
    u_long	epss_time_stamp;	/* zero if OS loads time stamp in CEH */
    u_long	epss_halt_code;		/* reason code for why CPU halted     */
    u_long	epss_reserved;		/* reserved for future expansion      */
};

struct el_mv_ev7_processor_subpacket {
    u_short	eps_subpak_length;	/* subpacket byte count - 0x00d8      */
    u_short	eps_subpak_class;	/* Class registered as 0x000e         */
    u_short	eps_subpak_type;	/* Type registered as 0x0004          */
    u_short	eps_subpak_rev;		/* First revision is 0x0001           */
    u_long	eps_i_stat;		/* EV6 core I_STAT register           */
    u_long	eps_dc_stat;		/* EV6 core DC_STAT register          */
    u_long	eps_c_addr;		/* EV6 core C_ADDR register           */
    u_long	eps_c_syndrome_1;	/* EV6 core C_SYNDROME_1 register     */
    u_long	eps_c_syndrome_0;	/* EV6 core C_SYNDROME_0 register     */
    u_long	eps_c_stat;		/* EV6 core C_STAT register           */
    u_long	eps_c_sts;		/* EV6 core C_STS register            */
    u_long	eps_mm_stat;		/* EV6 core MM_STAT register          */
    u_long	eps_exc_addr;		/* EV6 core EXC_ADDR register         */
    u_long	eps_ier_cm;		/* EV6 core IER_CM register           */
    u_long	eps_isum;		/* EV6 core ISUM register             */
    u_long	eps_pal_base;		/* EV6 core PAL_BASE register         */
    u_long	eps_i_ctl;		/* EV6 core I_CTL register            */
    u_long	eps_process_context;	/* EV6 core PROCESS_CONTEXT register  */
    u_long	eps_cbox_ctl;		/* EV7 CBOX_CTL register              */
    u_long	eps_cbox_stp_ctl;	/* EV7 CBOX_STP_CTL register          */
    u_long	eps_cbox_acc_ctl;	/* EV7 CBOX_ACC_CTL register          */
    u_long	eps_cbox_lcl_set;	/* EV7 CBOX_LCL_CTL register          */
    u_long	eps_cbox_gbl_set;	/* EV7 CBOX_GBL_CTL register          */
    u_long	eps_bbox_ctl;		/* EV7 BBOX_CTL register              */
    u_long	eps_bbox_err_sts;	/* EV7 BBOX_ERR_STS register          */
    u_long	eps_bbox_err_idx;	/* EV7 BBOX_ERR_IDX register          */
    u_long	eps_cbox_ddp_err_sts;	/* EV7 CBOX_DDP_ERR_STS register      */
    u_long	eps_bbox_dat_rmp;	/* EV7 BBOX_DAT_RMP register          */
    u_long	eps_reserved1;		/* reserved for future expansion      */
    u_long	eps_reserved2;		/* reserved for future expansion      */
};

struct el_mv_ev7_zbox0_zbox_1_subpacket {
    u_short	ezbs_subpak_length;	/* subpacket byte count - 0x0098      */
    u_short	ezbs_subpak_class;	/* Class registered as 0x000e         */
    u_short	ezbs_subpak_type;	/* Type registered as 0x0005          */
    u_short	ezbs_subpak_rev;	/* First revision is 0x0001           */
    u_int	ezbs_zbox0_dram_err_status_1;
    u_int	ezbs_zbox0_dram_err_status_2;
    u_int	ezbs_zbox0_dram_err_status_3;
    u_int	ezbs_zbox0_dram_error_ctl;
    u_int	ezbs_zbox0_dram_err_adr;
    u_int	ezbs_zbox0_dift_timeout;
    u_int	ezbs_zbox0_dram_mapper_ctl;
    u_int	ezbs_zbox0_frc_err_adr;
    u_int	ezbs_zbox0_dift_err_status;
    u_int	ezbs_reserved0;
    u_int	ezbs_zbox1_dram_err_status_1;
    u_int	ezbs_zbox1_dram_err_status_2;
    u_int	ezbs_zbox1_dram_err_status_3;
    u_int	ezbs_zbox1_dram_error_ctl;
    u_int	ezbs_zbox1_dram_err_adr;
    u_int	ezbs_zbox1_dift_timeout;
    u_int	ezbs_zbox1_dram_mapper_ctl;
    u_int	ezbs_zbox1_frc_err_adr;
    u_int	ezbs_zbox1_dift_err_status;
    u_int	ezbs_reserved1;
    u_long	ezbs_cbox_ctl;
    u_long	ezbs_cbox_stp_ctl;
    u_long	ezbs_zbox0_error_pa;
    u_long	ezbs_zbox1_error_pa;
    u_long	ezbs_zbox0_ored_syndrome;
    u_long	ezbs_zbox1_ored_syndrome;
    u_long	ezbs_reserved2;
    u_long	ezbs_reserved3;
};

struct el_mv_ev7_rbox_subpacket {
    u_short	erbs_subpak_length;	/* subpacket byte count - 0x0098      */
    u_short	erbs_subpak_class;	/* Class registered as 0x000e         */
    u_short	erbs_subpak_type;	/* Type registered as 0x0006          */
    u_short	erbs_subpak_rev;	/* First revision is 0x0001           */
    u_long	erbs_rbox_cfg;
    u_long	erbs_rbox_n_cfg;
    u_long	erbs_rbox_s_cfg;
    u_long	erbs_rbox_e_cfg;
    u_long	erbs_rbox_w_cfg;
    u_long	erbs_rbox_n_err;
    u_long	erbs_rbox_s_err;
    u_long	erbs_rbox_e_err;
    u_long	erbs_rbox_w_err;
    u_long	erbs_rbox_io_cfg;
    u_long	erbs_rbox_io_err;
    u_long	erbs_rbox_l_err;
    u_long	erbs_rbox_whoami;
    u_long	erbs_rbox_imask;
    u_long	erbs_rbox_intq;
    u_long	erbs_rbox_int;
    u_long	erbs_reserved0;
    u_long	erbs_reserved1;
};

struct el_mv_ev7_io_subpacket {
    u_short	eios_subpak_length;	/* subpacket byte count - 0x0158      */
    u_short	eios_subpak_class;	/* Class registered as 0x000e         */
    u_short	eios_subpak_type;	/* Type registered as 0x0007          */
    u_short	eios_subpak_rev;	/* First revision is 0x0001           */
    u_long	eios_io_asic_rev;
    u_long	eios_io_sys_rev;
    u_long	eios_io7_uph;
    u_long	eios_hpi_ctl;
    u_long	eios_crd_ctl;
    u_long	eios_hei_ctl;
    u_long	eios_po7_error_sum;
    u_long	eios_po7_uncrr_sym;
    u_long	eios_po7_crrct_sym;
    u_long	eios_po7_ugbge_sym;
    u_long	eios_po7_err_pkt0;
    u_long	eios_po7_err_pkt1;
    u_long	eios_reserved0;
    u_long	eios_reserved1;
    u_long	eios_po0_err_sum;
    u_long	eios_po0_tlb_err;
    u_long	eios_po0_spl_complt;
    u_long	eios_po0_trans_sum;
    u_long	eios_po0_first_err;
    u_long	eios_po0_mult_err;
    u_long	eios_po0_dm_source;
    u_long	eios_po0_dm_dest;
    u_long	eios_po0_dm_size;
    u_long	eios_po0_dm_ctrl;
    u_long	eios_reserved2;
    u_long	eios_po1_err_sum;
    u_long	eios_po1_tlb_err;
    u_long	eios_po1_spl_complt;
    u_long	eios_po1_trans_sum;
    u_long	eios_po1_first_err;
    u_long	eios_po1_mult_err;
    u_long	eios_po1_dm_source;
    u_long	eios_po1_dm_dest;
    u_long	eios_po1_dm_size;
    u_long	eios_po1_dm_ctrl;
    u_long	eios_reserved3;
    u_long	eios_po2_err_sum;
    u_long	eios_po2_tlb_err;
    u_long	eios_po2_spl_complt;
    u_long	eios_po2_trans_sum;
    u_long	eios_po2_first_err;
    u_long	eios_po2_mult_err;
    u_long	eios_po2_dm_source;
    u_long	eios_po2_dm_dest;
    u_long	eios_po2_dm_size;
    u_long	eios_po2_dm_ctrl;
    u_long	eios_reserved4;
    u_long	eios_po3_err_sum;
    u_long	eios_po3_tlb_err;
    u_long	eios_po3_spl_complt;
    u_long	eios_po3_trans_sum;
    u_long	eios_po3_first_err;
    u_long	eios_po3_mult_err;
    u_long	eios_po3_dm_source;
    u_long	eios_po3_dm_dest;
    u_long	eios_po3_dm_size;
    u_long	eios_po3_dm_ctrl;
    u_long	eios_reserved5;
};

struct el_mv_ev7_type0_dev_bus_snap_subpacket {
    u_short	e0dbs_subpak_length;	/* subpacket byte count - 0x0050      */
    u_short	e0dbs_subpak_class;	/* Class registered as 0x000b         */
    u_short	e0dbs_subpak_type;	/* Type registered as 0x0001          */
    u_short	e0dbs_subpak_rev;	/* First revision is 0x0002           */
    u_long	e0dbs_bpa_cfg_adr_port;
    u_short	e0dbs_vendor_id;
    u_short	e0dbs_device_id;
    u_short	e0dbs_pci_bus_cmd;
    u_short	e0dbs_pci_bus_status;
    u_char	e0dbs_revision_id;
    u_char	e0dbs_program_if;
    u_char	e0dbs_sub_class;
    u_char	e0dbs_base_class;
    u_char	e0dbs_cache_line_size;
    u_char	e0dbs_latency_timer;
    u_char	e0dbs_header_type;
    u_char	e0dbs_bist;
    u_int	e0dbs_base_adr_reg0;
    u_int	e0dbs_base_adr_reg1;
    u_int	e0dbs_base_adr_reg2;
    u_int	e0dbs_base_adr_reg3;
    u_int	e0dbs_base_adr_reg4;
    u_int	e0dbs_base_adr_reg5;
    u_int	e0dbs_cardbus_cis_ptr;
    u_short	e0dbs_subsys_vendor_id;
    u_short	e0dbs_subsys_device_id;
    u_int	e0dbs_expansion_rom_adr;
    u_char	e0dbs_cap_pointer;
    u_char	e0dbs_reserved0;
    u_char	e0dbs_reserved1;
    u_char	e0dbs_reserved2;
    u_int	e0dbs_reserved3;
    u_char	e0dbs_interrupt_line;
    u_char	e0dbs_interrupt_pin;
    u_char	e0dbs_min_grant;
    u_char	e0dbs_max_latency;
};
struct el_mv_ev7_type1_dev_bus_snap_subpacket {
    u_short	e1dbs_subpak_length;	/* subpacket byte count - 0x0050      */
    u_short	e1dbs_subpak_class;	/* Class registered as 0x000b         */
    u_short	e1dbs_subpak_type;	/* Type registered as 0x0002          */
    u_short	e1dbs_subpak_rev;	/* First revision is 0x0002           */
    u_long	e1dbs_bpa_cfg_adr_port;
    u_short	e1dbs_vendor_id;
    u_short	e1dbs_device_id;
    u_short	e1dbs_pci_bus_cmd;
    u_short	e1dbs_pci_bus_status;
    u_char	e1dbs_revision_id;
    u_char	e1dbs_program_if;
    u_char	e1dbs_sub_class;
    u_char	e1dbs_base_class;
    u_char	e1dbs_cache_line_size;
    u_char	e1dbs_latency_timer;
    u_char	e1dbs_header_type;
    u_char	e1dbs_bist;
    u_int	e1dbs_base_adr_reg0;
    u_int	e1dbs_base_adr_reg1;
    u_char	e1dbs_pri_bus_num;
    u_char	e1dbs_sec_bus_num;
    u_char	e1dbs_sub_bus_num;
    u_char	e1dbs_sec_lat_timer;
    u_char	e1dbs_io_base;
    u_char	e1dbs_io_limit;
    u_short	e1dbs_secondary_status;
    u_short	e1dbs_non_pf_mem_base;
    u_short	e1dbs_non_pf_mem_limit;
    u_short	e1dbs_pf_mem_base;
    u_short	e1dbs_pf_mem_limit;
    u_int	e1dbs_pfmem_base_upr32bits;
    u_int	e1dbs_pfmem_limit_upr32bits;
    u_short	e1dbs_io_base_upr16bits;
    u_short	e1dbs_io_limit_upr16bits;
    u_char	e1dbs_cap_pointer;
    u_char	e1dbs_reserved0;
    u_char	e1dbs_reserved1;
    u_char	e1dbs_reserved2;
    u_int	e1dbs_expansion_rom_adr;
    u_char	e1dbs_interrupt_line;
    u_char	e1dbs_interrupt_pin;
    u_short	e1dbs_bridge_control;
};

struct el_mv_ev7_pcix_capability_subpacket {
    u_short	epcs_subpak_length;	/* subpacket byte count - 0x0020      */
    u_short	epcs_subpak_class;	/* Class registered as 0x000b         */
    u_short	epcs_subpak_type;	/* Type registered as 0x0004          */
    u_short	epcs_subpak_rev;	/* First revision is 0x0001           */
    u_long	epcs_bpa_cfg_adr_port;
    u_char	epcs_pcix_cap_id;	/* 0x7 */
    u_char	epcs_next_cap_ptr;
    u_short	epcs_pcix_command_reg;
    u_int	epcs_pcix_status_reg;
    u_long	epcs_reserved0;
};

struct el_mv_ev7_pcix_bridge_capability_subpacket {
    u_short	epbcs_subpak_length;	/* subpacket byte count - 0x0028      */
    u_short	epbcs_subpak_class;	/* Class registered as 0x000b         */
    u_short	epbcs_subpak_type;	/* Type registered as 0x0005          */
    u_short	epbcs_subpak_rev;	/* First revision is 0x0001           */
    u_long	epbcs_bpa_cfg_adr_port;
    u_char	epbcs_pcix_cap_id;	/* 0x7 */
    u_char	epbcs_next_cap_ptr;
    u_short	epbcs_pcix_secndry_sts_reg;
    u_int	epbcs_pcix_bridge_sts_reg;
    u_int	epbcs_upstr_split_trans_ctrl;
    u_int	epbcs_dnstr_split_trans_ctrl;
    u_long	epbcs_reserved0;
};

struct el_mv_ev7_msi_capability_subpacket {
    u_short	emcs_subpak_length;	/* subpacket byte count - 0x0028      */
    u_short	emcs_subpak_class;	/* Class registered as 0x000b         */
    u_short	emcs_subpak_type;	/* Type registered as 0x0006          */
    u_short	emcs_subpak_rev;	/* First revision is 0x0001           */
    u_long	emcs_bpa_cfg_adr_port;
    u_char	emcs_msi_cap_id;	/* 0x5 */
    u_char	emcs_next_cap_ptr;
    u_short	emcs_message_ctrl;
    u_int	emcs_message_adr;
    u_int	emcs_msg_upper_adr;
    u_int	emcs_message_data;
    u_long	emcs_reserved0;
};

struct el_mv_ev7_agp_capability_subpacket {
    u_short	eacs_subpak_length;	/* subpacket byte count - 0x0020      */
    u_short	eacs_subpak_class;	/* Class registered as 0x000b         */
    u_short	eacs_subpak_type;	/* Type registered as 0x0007          */
    u_short	eacs_subpak_rev;	/* First revision is 0x0001           */
    u_long	eacs_bpa_cfg_adr_port;
    u_char	eacs_agp_cap_id;
    u_char	eacs_next_cap_ptr;
    u_char	eacs_maj_min;		/* maj <7:4>  min <3:0> */
    u_char	eacs_reserved0;
    u_int	eacs_agp_status_reg;
    u_int	eacs_command_reg;
    u_int	eacs_reserved1;
};

struct el_mv_ev7_env_monitoring_subpacket {
    u_short	eenv_subpak_length;	/* subpacket byte count - 0x0018      */
    u_short	eenv_subpak_class;	/* Class registered as 0x000e         */
    u_short	eenv_subpak_type;	/* Type registered as 0x00xx          */
    u_short	eenv_subpkt_rev;	/* First revision is 0x0001           */
    u_short	eenv_cab_id;
    u_short	eenv_dra_id;
    u_int	eenv_reserved1;
    u_short	eenv_penum;
    u_short	eenv_index;
    u_short	eenv_reserved2;
    u_short	eenv_sens_cond;

};

/*
 * Data structures for testing error interrupts and machine checks.
 */
struct mvcpu_debug_630_670_logout {
	struct el_mv_ev7_logout_header_frame_subpacket;
	struct el_mv_ev7_pal_specific_subpacket;
	struct el_mv_ev7_processor_subpacket;
};

struct mvcpu_debug_620_660_logout {
	struct el_mv_ev7_logout_header_frame_subpacket;
	struct el_mv_ev7_pal_specific_subpacket;
	struct el_mv_ev7_zbox0_zbox_1_subpacket;
	struct el_mv_ev7_rbox_subpacket;
	struct el_mv_ev7_io_subpacket;
};

struct mvcpu_debug_680_logout {
	struct el_mv_ev7_logout_header_frame_subpacket;
	struct el_mv_ev7_pal_specific_subpacket;
	struct el_mv_ev7_env_monitoring_subpacket;
};
struct mvcpu_debug_6all_logout {
	struct el_mv_ev7_logout_header_frame_subpacket;
	struct el_mv_ev7_pal_specific_subpacket;
	struct el_mv_ev7_processor_subpacket;
	struct el_mv_ev7_zbox0_zbox_1_subpacket;
	struct el_mv_ev7_rbox_subpacket;
	struct el_mv_ev7_io_subpacket; 
	struct el_mv_ev7_env_monitoring_subpacket;
};

/* Entry Terminator Subpacket */
struct entry_terminator {
    short length;   /* Length (0008)   */
    short class;    /* Class (0000)    */
    short type;     /* Type (0000)     */
    short revision; /* Revision (0001) */
};

union el_mv_ev7_subpackets {
    struct el_mv_ev7_subpkt_hdr				elf_hdr;
    struct el_mv_ev7_logout_header_frame_subpacket	elf_lhfs;
    struct el_mv_ev7_pal_specific_subpacket		elf_pss;
    struct el_mv_ev7_processor_subpacket		elf_ps;
    struct el_mv_ev7_zbox0_zbox_1_subpacket		elf_zbs;
    struct el_mv_ev7_rbox_subpacket			elf_rbs;
    struct el_mv_ev7_io_subpacket			elf_ios;
    struct el_mv_ev7_type0_dev_bus_snap_subpacket	elf_t0dbs;
    struct el_mv_ev7_type1_dev_bus_snap_subpacket	elf_t1dbs;
    struct el_mv_ev7_pcix_capability_subpacket		elf_pcs;
    struct el_mv_ev7_pcix_bridge_capability_subpacket	elf_pbcs;
    struct el_mv_ev7_msi_capability_subpacket		elf_mcs;
    struct el_mv_ev7_agp_capability_subpacket		elf_acs;
    struct el_mv_ev7_env_monitoring_subpacket		elf_env; 
    struct entry_terminator				elf_ets;
};

struct el_mv_660_670_6b0_logout_frame {
        struct  el_mv_ev7_logout_header_frame_subpacket		uncorr_common;
	struct el_mv_ev7_pal_specific_subpacket			elfmc_sysdata;
};

/* 
 *  Marvel 630/620 correctable logout frame. This is the PAL's
 * 	logout frame, which becomes a piece of the correctable
 *	errorlog packet.
 */


/* System Error Frame Header Subpacket */
struct sys_err_frame_header {
    struct entry_terminator header;
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* System Event Frame Header Subpacket */
struct sys_evt_frame {
    struct entry_terminator header;
    char   timestamp[8];       /* Timestamp                 */
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* Error Halt Frame Header Subpacket */
struct err_halt_frame_header {
    struct entry_terminator header;
    int    halt_reason_code;   /* Halt Reason Code          */
    int    rsvd;               /* Reserved                  */
    u_long time_stamp;         /* Time Stamp                */
    int    frame_length;       /* Frame Length              */
    int    frame_subpkt_count; /* Frame Subpacket Count (n) */
};

/* Basic System Error Frame Subpacket */
struct basic_sys_err_frame {
    struct entry_terminator header;
    u_long base_phys_addr;     /* Base Physical Address     */
};

/* Kernel Hardware Correctable Error Reporting Status Subpacket */
struct kern_hw_corr_err_status {
    struct entry_terminator header;
    u_long cpu_whami;
    u_long cer_stat;
};

/*
 * Error log subpacket header definitions.
 */

#define MV_EL_HEADER_CLASS	0x5	/* Header Class */
#define MV_EL_PLATFORM_CLASS	0xe	/* Marvel Platform Class */
#define MV_EL_BUS_CLASS		0xb	/* PCI, MSI, AGP Class */
#define MV_EL_SUBPKT_REV1	0x1
#define MV_EL_SUBPKT_REV2	0x2

#define MV_EL_LHFS_TYPE		0x13	/* Logout Header Frame Subpacket */
#define MV_EL_PSS_TYPE		0x1	/* PAL Specific Subpacket */
#define MV_EL_PS_TYPE		0x4	/* Processor Subpacket */
#define MV_EL_ZBS_TYPE		0x5	/* ZBOX Subpacket */
#define MV_EL_RBS_TYPE		0x6	/* RBOX Subpacket */
#define MV_EL_IOS_TYPE		0x7	/* IO Subpacket */
#define MV_EL_OCLAE_TYPE	0x10	/* OCLA EAST Subpacket */
#define MV_EL_OCLAW_TYPE	0x11	/* OCLA WEST Subpacket */
#define MV_EL_CNMC_TYPE		0x14	/* CFG_NODE_MEMORY_CTRL Subpacket */
#define MV_EL_SM_TYPE		0x15	/* Server Management (680) Subpacket */
#define MV_EL_PCI_T0_TYPE	0x1	/* Type 0 PCI Device Subpacket */
#define MV_EL_PCI_T1_TYPE	0x2	/* Type 1 PCI Device Subpacket */
#define MV_EL_PCIX_T0_TYPE	0x4	/* Type 0 PCI-X Capability Subpacket */
#define MV_EL_PCIX_T1_TYPE	0x5	/* Type 1 PCI-X Capability Subpacket */
#define MV_EL_MSI_TYPE		0x6	/* PCI-X MSI Capability Subpacket */
#define MV_EL_AGP_TYPE		0x7	/* AGP Capability Subpacket */
#define MV_EL_TEMP_TYPE		0xa	/* System event - Ambient temp subpkt */
#define MV_EL_AIR_TYPE		0xb	/* System event - Airmover subpacket */
#define MV_EL_VOLT_TYPE		0xc	/* System event - Voltage monitoring subpacket */
#define MV_EL_INTRUS_TYPE	0xd	/* System event - Intrusion subpacket */
#define MV_EL_POS_TYPE		0xe	/* System event - power supply subpacket */
#define MV_EL_PKT_SHIFT		16	/* shift to form combined type/class  */
#define MV_EL_PKT_MASK		0xffff	/* mask for combined type/class       */

#define MV_EL_LHFS_PKT	   ((MV_EL_LHFS_TYPE << 16) | MV_EL_HEADER_CLASS)
#define MV_EL_PSS_PKT	   ((MV_EL_PSS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_PS_PKT	   ((MV_EL_PS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_ZBS_PKT	   ((MV_EL_ZBS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_RBS_PKT	   ((MV_EL_RBS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_IOS_PKT	   ((MV_EL_IOS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_OCLAE_PKT   ((MV_EL_OCLAE_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_OCLAW_PKT   ((MV_EL_OCLAW_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_CNMC_PKT	   ((MV_EL_CNMC_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_SM_PKT	   ((MV_EL_SM_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_PCI_T0_PKT   ((MV_EL_PCI_T0_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_PCI_T1_PKT   ((MV_EL_PCI_T1_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_PCIX_T0_PKT  ((MV_EL_PCIX_T0_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_PCIX_T1_PKT  ((MV_EL_PCIX_T1_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_MSI_PKT	   ((MV_EL_MSI_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_AGP_PKT	   ((MV_EL_AGP_TYPE << 16) | MV_EL_BUS_CLASS)
#define MV_EL_TEMP_PKT	   ((MV_EL_TEMP_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_AIR_PKT	   ((MV_EL_AIR_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_VOLT_PKT	   ((MV_EL_VOLT_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_INTRUS_PKT   ((MV_EL_INTRUS_TYPE << 16) | MV_EL_PLATFORM_CLASS)
#define MV_EL_POS_PKT	   ((MV_EL_POS_TYPE << 16) | MV_EL_PLATFORM_CLASS)

/* definitions needed for Termination packet */
#define  MV_EL_TERM_LENGTH                 sizeof(struct entry_terminator)
#define  MV_EL_TERM_CLASS                  0x0000
#define  MV_EL_TERM_TYPE                   0x0000
#define  MV_EL_TERM_REV                    0x0001

/* definitions needed for system error frame header subpacket */
#define  MV_EL_SYS_ERR_HDR_LNGTH                  sizeof(struct sys_err_frame_header)
#define  MV_EL_SYS_ERR_HDR_CLASS                  0x0005
#define  MV_EL_SYS_ERR_HDR_TYPE                   0x0001
#define  MV_EL_SYS_ERR_HDR_REV                    0x0001

/* definitions needed for system event frame header subpacket */
#define  MV_EL_SYS_EVT_LNGTH                  sizeof(struct sys_evt_frame)
#define  MV_EL_SYS_EVT_CLASS                  0x0005
#define  MV_EL_SYS_EVT_TYPE                   0x0002
#define  MV_EL_SYS_EVT_REV                    0x0001
/* definitons for correctable error throttleon/off subpacket */
#define MV_EL_KERN_HW_CORR_ERR_HDR_REV    0x0002
#define MV_EL_KERN_HW_CORR_ERR_HDR_TYPE   0x0001
#define MV_EL_KERN_HW_CORR_ERR_HDR_CLASS  0x0009
#define MV_EL_KERN_HW_CORR_ERR_HDR_LGTH   sizeof(struct kern_hw_corr_err_status)

/* definitons for correctable error throttling */
#define  MV_620_THROTTLE_ON  0x100000000 /* used for setting CER_STAT<32> */
#define  MV_620_THROTTLE_OFF 0x0 /* used for setting CER_STAT<32> */
#define  MV_630_THROTTLE_ON  0x100 /* used for setting CER_STAT<8> */
#define  MV_630_THROTTLE_OFF 0x0 /* used for setting CER_STAT<8> */
#define  MV_ALL_THROTTLE_OFF 0x0 /* used for initializing CER_STAT to 0 */

/* definitions needed for PCI type 0 subpackets header  */
#define  MV_EL_PCI_T0_LNGTH                  sizeof(struct el_mv_ev7_type0_dev_bus_snap_subpacket)
#define  MV_EL_PCI_T0_CLASS                  0x000b
#define  MV_EL_PCI_T0_REV                    0x0002

/* definitions needed for PCI type 1 subpackets header  */
#define  MV_EL_PCI_T1_LNGTH                  sizeof(struct el_mv_ev7_type1_dev_bus_snap_subpacket)
#define  MV_EL_PCI_T1_CLASS                  0x000b
#define  MV_EL_PCI_T1_REV                    0x0002

/* definitions needed for PCI-X type 0 subpackets header  */
#define  MV_EL_PCIX_T0_LNGTH                  sizeof(struct el_mv_ev7_pcix_capability_subpacket)
#define  MV_EL_PCIX_T0_CLASS                  0x000b
#define  MV_EL_PCIX_T0_REV                    0x0001

/* definitions needed for PCI-X type 1 subpackets header  */
#define  MV_EL_PCIX_T1_LNGTH                  sizeof(struct el_mv_ev7_pcix_bridge_capability_subpacket)
#define  MV_EL_PCIX_T1_CLASS                  0x000b
#define  MV_EL_PCIX_T1_REV                    0x0001

/* definitions needed for MSI subpackets header  */
#define  MV_EL_MSI_LNGTH                  sizeof(struct el_mv_ev7_msi_capability_subpacket)
#define  MV_EL_MSI_CLASS                  0x000b
#define  MV_EL_MSI_REV                    0x0001

/* definitions needed for AGP subpackets header  */
#define  MV_EL_AGP_LNGTH                  sizeof(struct el_mv_ev7_agp_capability_subpacket)
#define  MV_EL_AGP_CLASS                  0x000b
#define  MV_EL_AGP_REV                    0x0001


#ifdef KERNEL
/*
 * A per-cpu data structure for machine check handling
 * and binary error logging.
 * MV_NOTE: Error log buffer sized to always fit within 8kb page.
 */
#define MVCPU_MCHK_ELOG_BUFSIZE		(6 * 1024)
#define MVCPU_MCHK_ELOG_BUFSLOP		(MV_EL_TERM_LENGTH + sizeof(long))
#define MVCPU_MCHK_ELOG_BUFLEN		(MVCPU_MCHK_ELOG_BUFSIZE + \
					 MVCPU_MCHK_ELOG_BUFSLOP)

/* MV_NOTE: current structure size is about 7k bytes
 */
struct mv_mcheck_control {
    /*
     * The following set of structure elements are used for intentional
     * machine checks, such as those caused by BADADDR IO probing,
     * probing memory (testpage code).
     */
    u_int 	mcheck_expected;	/* flag: we're probing.		*/
    u_int 	mcheck_occurred;	/* Number of mchecks during probe.  */
    u_int 	mcheck_action; 		/* Action to take with this mcheck: */
					/* recover, crash, retry	    */
    u_int	mcheck_retry;		/* Logout frames retry bit	*/
    long 	mcheck_return;		/* return to this PC expected mchecks */
    memtest_t 	mcheck_tp_active;	/* flag: testpage in progress	*/
    long  	mcheck_page;		/* page we're testing.		*/
    u_long 	mctl_probe_val;		/* VA being probed.		*/

    long syscorr_period;
    long syscorr_last;           
    long syscorr_first;          
    long syscorr_threshold;      
    long syscorr_count;          
    long proccorr_period;        
    long proccorr_last;          
    long proccorr_first;         
    long proccorr_threshold;     
    long proccorr_count;         
    long disable_620;
    long disable_630;
    long timeout_queued_620;
    long timeout_queued_630;

    char    mv_align_for_mvfi[80]; /* This is required for mvfi */
    struct entry_terminator terminator_packet;  

    /*
     * Keep error info for last error on this processor.
     * Current usage is by MVFI (MarVel Fault Insertion).
     * MV_NOTE: current size is 7112 bytes.
     *
     * WARNING: don't change offset, order, or delete elements (MVFI dependency)
     */
    u_long	num_620_mchk;
    u_long	num_630_mchk;
    u_long	num_660_mchk;
    u_long	num_670_mchk;
    u_long	num_6a0_mchk;
    u_long	num_6b0_mchk;
    u_long	num_680_mchk;
    u_long	last_mchk_type;
    u_long	ev7_i_stat;
    u_long	ev7_dc_stat;
    u_long	ev7_c_addr;
    u_long	ev7_c_syndrome1;
    u_long	ev7_c_syndrome0;
    u_long	ev7_c_stat;
    u_long	ev7_c_sts;
    u_long	ev7_bbox_err_sts;
    u_long	ev7_bbox_err_idx;
    u_long	ev7_cbox_ddp_err_sts;
    u_long	zbox0_dram_err_status_1;
    u_long	zbox0_dram_err_status_2;
    u_long	zbox0_dram_err_status_3;
    u_long	zbox0_dram_err_adr;
    u_long	zbox0_frc_err_adr;
    u_long	zbox1_dram_err_status_1;
    u_long	zbox1_dram_err_status_2;
    u_long	zbox1_dram_err_status_3;
    u_long	zbox1_dram_err_adr;
    u_long	zbox1_frc_err_adr;
    u_long	rbox_n_err;
    u_long	rbox_s_err;
    u_long	rbox_e_err;
    u_long	rbox_w_err;
    u_long	rbox_io_err;
    u_long	rbox_l_err;
    u_long	rbox_imask;
    u_long	rbox_int;
    u_long	io7_po7_error_sum;
    u_long	io7_po7_uncrr_sym;
    u_long	io7_po7_crrct_sym;
    u_long	io7_po7_ugbge_sym;
    u_long	io7_po0_err_sum;
    u_long	io7_po0_tlb_err;
    u_long	io7_po0_spl_complt;
    u_long	io7_po0_trans_sum;
    u_long	io7_po0_first_err;
    u_long	io7_po0_mult_err;
    u_long	io7_po0_dm_ctrl;
    u_long	io7_po1_err_sum;
    u_long	io7_po1_tlb_err;
    u_long	io7_po1_spl_complt;
    u_long	io7_po1_trans_sum;
    u_long	io7_po1_first_err;
    u_long	io7_po1_mult_err;
    u_long	io7_po1_dm_ctrl;
    u_long	io7_po2_err_sum;
    u_long	io7_po2_tlb_err;
    u_long	io7_po2_spl_complt;
    u_long	io7_po2_trans_sum;
    u_long	io7_po2_first_err;
    u_long	io7_po2_mult_err;
    u_long	io7_po2_dm_ctrl;
    u_long	io7_po3_err_sum;
    u_long	io7_po3_tlb_err;
    u_long	io7_po3_spl_complt;
    u_long	io7_po3_trans_sum;
    u_long	io7_po3_first_err;
    u_long	io7_po3_mult_err;
    u_long	io7_po3_dm_ctrl;
    u_long	zbox0_error_pa;			/* was mchk_spare0 */
    u_long	zbox1_error_pa;			/* was mchk_spare1 */
    u_long	io7_uph_pid;
    u_long	mchk_pmchkf;			/* Logout frame (from rpb) */
    u_long	mchk_spare4;
    u_long	mchk_spare5;
    u_long	mchk_spare6;
    u_long	mchk_spare7;
    u_long	mchk_spare8;
    u_long	mchk_spare9;
    u_long	mchk_spare10;
    u_long	mchk_spare11;
    u_long	mchk_spare12;
    u_long	mchk_spare13;
    u_long	mchk_spare14;
    u_long	mchk_spare15;
    u_long	last_mchk_frame_addr;
    u_long	last_mchk_pc;
    u_long	last_mchk_ra;
    u_long	last_mchk_ps;
    u_long	alpha_chip_id;
    u_long	mvcpu_CCsyn_avoided;	/* EV7 P1 CC syndrome MCHK workaround */
    u_long	mvcpu_CCsyn_avoided_count;
    u_long	stop_ocla_on_mchk;	/* stop OCLA on MCHK */
    u_long	stop_ocla_on_mchk_all;	/* stop OCLA on MCHK (all CPUs) */
					/* end of MVFI WARNING */

    /*
     * Error log buffer. So, the binary error log entry will
     * be in the crash dump for the, hopefully rare, case
     * when binlog_alloc() fails [can't malloc kernel buffer].
     * Must hold largest possible error log packet plus fudge factor.
     *
     * MV_NOTE: Size is 6kb, which is big enough and stays in 8kb malloc bucket.
     */
    union {
	u_long	ul[MVCPU_MCHK_ELOG_BUFLEN / sizeof (long)];
	u_char	uc[MVCPU_MCHK_ELOG_BUFLEN];
    } elf_buffer;

    struct kern_hw_corr_err_status	throttle_status_frame;
};
#endif

#define BCOPY_AND_INCREMENT(X, Y)  bcopy(X, errlog_ptr, sizeof(struct Y)); \
			           errlog_ptr += sizeof(struct Y);

/*
 * Data structure, flags, and string arrays used to print
 * register values and, optionally do bit to text expansion.
 */
#define MV_NO_REG	0x1		/* don't print csr type header        */
#define MV_NULL_REG	0x2		/* print "REG" as csr type header     */
#define MV_CHIP_IPR	0x4		/* print "EV7" as csr type header */
#define MV_IO7_CSR	0x8		/* print "IO7" as csr type header     */
#define MV_BIT2TEXT	0x20		/* enable bit to text translation     */
#define MV_P_NULL_REG	0x40		/* print CSR value even if it's zero  */
#define MV_APRINTF	0x80		/* use aprintf vs printf for SBEs */

#define R_NONE		0		/* don't print string or end of array */
#define R_BIN		1		/* Radix binary, print if bit set     */
#define R_DEC		10		/* print field value in decimal       */
#define R_HEX		16		/* print field value in hexadecimal   */
#define R_STR		42		/* print string, but not bit field    */

struct reg_format {
	int	bit_num;		/* starting bit position of field     */
	int	bit_len;		/* number of bits in field            */
	int	pradix;			/* print radix and misc control       */
	char	*bit2text;		/* bit to text string to print        */
};

#ifdef	MV_INCLUDE_MARVEL_CPU
/*
 * So structure defines can remain in this header file,
 * but only be expanded in marvel_cpu.c (also used in
 * marvel_soc.c via extern).
 */
/*
 * IO7 ASIC CSRs
 */
struct reg_format PO7_io_asic_rev[] = {
	0,	4,	R_HEX,	"Revision of the I/O ASIC (IO7 or other )",
	4,	4,	R_HEX,	"Type of the I/O ASIC (1 = IO7)",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io_sys_rev[] = {
	0,	4,	R_HEX,	"Motherboard Revision (HP FPGA & Riser Card)",
	4,	4,	R_HEX,	"Motherboard Type",
	8,	4,	R_DEC,	"Number from Expansion Box Thumb Wheel",
	12,	3,	R_HEX,	"Hose[2:0] (Interesting for Xbox configs only)",
	15,	1,	R_BIN,	"Microprocessor attached to IO7 in Wildfire BP",
	16,	1,	R_HEX,	"Ser_dat_def (0 = Wildfire, 1 = Marvel)",
	17,	47,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};
struct reg_format PO7_io_misc_info[] = {		/* SER_CHAIN3 */
	0,	8,	R_HEX,	"Status Information from Wildfire Backplane",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_rst1[] = {			/* PLL 1 */
	0,	1,	R_BIN,	"Fault Reset (set causes IO7 mimic cold start)",
	1,	2,	R_NONE,	"Reserved",
	3,	3,	R_HEX,	"PLLOUTA frequency divider",
	6,	3,	R_HEX,	"PLLOUTB frequency divider",
	9,	4,	R_HEX,	"PLL1 Feedback Frequency Multiplier",
	13,	10,	R_HEX,	"PLL Tuning Bits",
	23,	7,	R_NONE,	"Reserved",
	30,	1,	R_BIN,	"Programmable Test Point (scope_sync)",
	31,	1,	R_HEX,	"LED (0 = off, 1 = on)",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_rst2[] = {			/* PLL 2 */
	0,	2,	R_NONE,	"Reserved",
	2,	1,	R_BIN,	"PLL2_DIS (clear to release PLL reset)",
	3,	3,	R_HEX,	"PLLOUTA frequency divider",
	6,	3,	R_HEX,	"PLLOUTB frequency divider",
	9,	4,	R_HEX,	"PLL2 Feedback Frequency Multiplier",
	13,	10,	R_HEX,	"PLL Tuning Bits",
	23,	1,	R_NONE,	"Reserved",
	24,	2,	R_HEX,	"TDM_DIV[1:0]",
	26,	1,	R_HEX,	"TDM_DIV[2]",
	27,	1,	R_HEX,	"TDM_DIV[3]",
	28,	36,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_rst3456[] = {		/* PLL 3, 4, 5, & 6 */
	0,	2,	R_NONE,	"Reserved",
	2,	1,	R_BIN,	"Clear to release PLL reset and enable PLL",
	3,	3,	R_HEX,	"PLLOUTA Frequency Divider",
	6,	3,	R_HEX,	"PLLOUTB Frequency Divider",
	9,	4,	R_HEX,	"Feedback Frequency Multiplier",
	13,	10,	R_HEX,	"PLL Tuning Bits",
	23,	3,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"SLOW_NP",
	27,	5,	R_NONE,	"Reserved",
	32,	4,	R_HEX,	"Clock Enables for pins: px_clk_out[3:0]",
	36,	3,	R_HEX,	"Clock Generator Divisor",
	39,	1,	R_HEX,	"CLKDIV[7] 1 = external clock, 0 = PLL2 output",
	40,	4,	R_HEX,	"SP_RATIO",
	44,	1,	R_HEX,	"PCIX_MODE 0 = PCI, 1 = PCIX",
	45,	1,	R_HEX,	"OUTZ 1 = 40 ohm, 0 = 20 ohm",
	46,	1,	R_BIN,	"FWD_EN [must be one]",
	47,	1,	R_HEX,	"RST South Port Reset [0=reset, 1=no reset]",
	48,	1,	R_BIN,	"PCIXCAP Drives px_pcixcap pin for port 0,1,2",
	49,	1,	R_HEX,	"AGP_RG Controls rg pin of AGP IO cells",
	50,	14,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_dwnh[] = {
	0,	2,	R_HEX,	"DNH_EV7ADDR[1:0] EVx Addressing Mode",
	2,	1,	R_BIN,	"SLK_MODE_ENA [must be zero]",
	3,	61,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_maf[] = {
	0,	5,	R_HEX,	"MAF_DIS Available MAFs",
	5,	59,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_maf_to[] = {
	0,	5,	R_HEX,	"MAF Timer",
	5,	59,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_acr0[] = {
	0,	2,	R_HEX,	"ACC_CLUMP",
	2,	62,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_acr1[] = {
	0,	64,	R_HEX,	"PMASK",
	0,	0,	R_NONE,	NULL

};

struct reg_format PO7_io7_acr2[] = {
	0,	64,	R_HEX,	"IOMASK",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_uph[] = {
	0,	11,	R_HEX,	"PID<10:0> -  PID for this I/O ASIC",
	11,	5,	R_HEX,	"UPH_CD_REQ - Up Hose Req Credits",
	16,	5,	R_HEX,	"UPH_CD_RIO - Up Hose RdIO Credits",
	21,	5,	R_HEX,	"UPH_CD_WIO - Up Hose WrIO Credits",
	26,	5,	R_HEX,	"UPH_CD_BLK - Up Hose BlkResp Credits",
	31,	5,	R_HEX,	"UPH_CD_NBK - Up Hose NoBlk Credits",
	36,	1,	R_HEX,	"UPH_FR_CNT - Up Hose Force Errors Count",
	37,	1,	R_HEX,	"UPH_FR_HDR - Up Hose Force Errors Data or Hdr",
	38,	1,	R_BIN,	"UPH_FR_SBE - Up Hose Force Single Bit Error",
	39,	1,	R_BIN,	"UPH_FR_DBE - Up Hose Force Double Bit Error",
	40,	1,	R_BIN,	"UPH_FR_GBG - Up Hose Force Garbage Code",
	41,	2,	R_HEX,	"UPH_ARB_MODE - Up Hose Port ARB Priority",
	43,	21,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_io7_uph_to[] = {
	0,	10,	R_HEX,	"UPH_CD_REQ_TO",
	10,	10,	R_HEX,	"UPH_CD_RIO_TO",
	20,	10,	R_HEX,	"UPH_CD_WIO_TO",
	30,	10,	R_HEX,	"UPH_CD_BLK_TO",
	40,	10,	R_HEX,	"UPH_CD_NBK_TO",
	50,	14,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_rbox_ireq_off[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	18,	R_HEX,	"RBOX_IREQ<21:4> offset in EV7 IPR space",
	22,	16,	R_NONE,	"RA1",
	38,	26,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_rbox_inta_off[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	18,	R_HEX,	"RBOX_INTA<21:4> offset in EV7 IPR space",
	22,	16,	R_NONE,	"RA1",
	38,	26,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_int_rty[] = {
	0,	6,	R_HEX,	"IONACK_CNT",
	6,	6,	R_HEX,	"IONACK_MAX",
	12,	3,	R_HEX,	"BACKOFF_INT",
	15,	1,	R_HEX,	"NXT_INT",
	16,	1,	R_HEX,	"WF_IRQ_SFT",
	17,	47,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_scratch[] = {
	0,	64,	R_HEX,	"IO7 Scratch Register",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_xtra_a[] = {
	0,	1,	R_HEX,	"Drives out the state for pin, p7_xtra",
	2,	63,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_xtra_ts[] = {
	0,	1,	R_HEX,	"Output drive enable pin p7_xtra [0=off, 1=on]",
	1,	63,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_dm_source[] = {
	0,	6,	R_NONE,	"Reserved",
	6,	42,	R_HEX,	"ADDR<47:6> Src PCI [Cache Line] Address",
	48,	2,	R_HEX,	"ADDR<49:48> [00=WIN 0-2, 01=S/G 3, 10=MWIN]",
	50,	14,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_dm_dest[] = {
	0,	6,	R_NONE,	"Reserved",
	6,	1,	R_HEX,	"ADDR<6> DM_SOURCE<6> [src/dest alignment]",
	7,	41,	R_HEX,	"ADDR<47:6> Dest PCI [Cache Line] Address",
	48,	2,	R_HEX,	"ADDR<49:48> [00=WIN 0-2, 01=S/G 3, 10=MWIN]",
	50,	14,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_dm_size[] = {
	0,	6,	R_NONE,	"Reserved",
	6,	27,	R_DEC,	"XFR_SIZE<32:6> Number of Cache Lines to Copy",
	33,	31,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_dm_ctrl[] = {
	0,	1,	R_BIN,	"DM_START [Read as Zero]",
	1,	1,	R_HEX,	"DM_DIS [1 = Data Mover Disabled on this Port]",
	2,	1,	R_HEX,	"DM_STOP [1 = Stop Data Mover]",
	3,	5,	R_NONE,	"Reserved",
	8,	9,	R_HEX,	"DM_MSG [<12:8> Lo MSG, <16:13> MSG_CTL[15:0]",
	17,	38,	R_NONE,	"Reserved",
	56,	1,	R_HEX,	"DM_EN_ERR_INT Error Interrupt Enable",
	57,	1,	R_HEX,	"DM_EN_DN_INT  Done Interrupt Enable",
	58,	1,	R_BIN,	"DM_TLB_ERR Forward hit to PTE during copy",
	59,	1,	R_BIN,	"DM_MAB Src/Dest Addr missed all DMA windows",
	60,	1,	R_BIN,	"DM_FILL_ERR Error signaled on Down Hose side",
	61,	1,	R_BIN,	"DM_2xSTART [running, size = 0, port disabled]",
	62,	1,	R_HEX,	"DM_ERROR Data Mover Error",
	63,	1,	R_HEX,	"DM_DONE Data Mover Done [1 = idle, 0 = busy]",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_monctl[] = {
	0,	8,	R_HEX,	"SELTA",
	8,	8,	R_HEX,	"SELTB",
	16,	8,	R_HEX,	"SELTC",
	24,	1,	R_HEX,	"PULSA",
	25,	1,	R_HEX,	"PULSB",
	26,	38,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_ctra[] = {
	0,	56,	R_DEC,	"POx_perf_ctra",
	56,	8,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_ctrb[] = {
	0,	56,	R_DEC,	"POx_perf_ctrb",
	56,	8,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_ctr56[] = {
	0,	56,	R_DEC,	"POx_perf_ctr56",
	56,	8,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_xtra_z[] = {
	0,	1,	R_HEX,	"State of pin p7_xtra",
	1,	63,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/* The *_PND, *_CLR, *_EIO CSRs not defined. Can be added if needed..... */

struct reg_format PO7_lsi_ctl[] = {
	0,	9,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_msi_ctl[] = {
	0,	9,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	7,	R_NONE,	"Reserved",
	32,	32,	R_HEX,	"Pending Message State Bits (Score Board)",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_hlt_ctl[] = {
	0,	5,	R_HEX,	"HLT_Offset<4:0> - Bit to set in RBOX_IREQ",
	5,	4,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_hpi_ctl[] = {
	0,	5,	R_HEX,	"HP_Offset<4:0> - Bit to set in RBOX_IREQ",
	5,	4,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_crd_ctl[] = {
	0,	5,	R_HEX,	"CRD_Offset<4:0> - Bit to set in RBOX_IREQ",
	5,	4,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_stv_ctl[] = {
	0,	5,	R_HEX,	"OVF_Offset<4:0> - Bit to set in RBOX_IREQ",
	5,	4,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	11,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_hei_ctl[] = {
	0,	5,	R_HEX,	"ERR_Offset<4:0> - Bit to set in RBOX_IREQ",
	5,	4,	R_NONE,	"Reserved",
	9,	4,	R_NONE,	"Reserved",
	13,	1,	R_NONE,	"Reserved",
	14,	9,	R_DEC,	"CPU Target<8:0> - Interrupt Target CPU",
	23,	1,	R_NONE,	"Reserved",
	24,	1,	R_HEX,	"Enables this Interrupt if set",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_error_sum[] = {
	0,	32,	R_NONE,	"Reserved",
	32,	1,	R_BIN,	"Single Bit Error Detected/Corrected",
	33,	1,	R_BIN,	"Multiple Single Bit Errors Detected/Corrected",
	34,	1,	R_BIN,	"Write Byte into IO ASIC CSR",
	35,	1,	R_BIN,	"PIO Transaction Targets a Non-Existent CSR",
	36,	1,	R_BIN,	"Bus Requestor PID (Access Protection Error)",
	37,	1,	R_BIN,	"Received NXM Response Packet from EVx CPU",
	38,	1,	R_BIN,	"Received Error Response Packet",
	39,	1,	R_BIN,	"Clock Error on a Data Flit",
	40,	1,	R_BIN,	"Double Bit Error Data Error Detected",
	41,	1,	R_BIN,	"Garbage Encoding Detected on the Date",
	42,	1,	R_BIN,	"Timeout, all Responses (including inval ack)",
	43,	1,	R_BIN,	"Garbage Encoding Sent in Response Data (UPH)",
	44,	1,	R_BIN,	"Orphan Response (Unexpected Response Packet)",
	45,	1,	R_BIN,	"Down Hose Packet Overflow",
	46,	1,	R_BIN,	"Down hose Credit Overflow",
	47,	1,	R_BIN,	"Unexpected or Bad Dealloc Field",
	48,	3,	R_NONE,	"Reserved",
	51,	1,	R_BIN,	"Credit Timeout Black Hole",
	52,	1,	R_BIN,	"Clock Check on Header",
	53,	1,	R_BIN,	"Double Bit Error (Uncorrectable) on Header",
	54,	1,	R_BIN,	"Garbage on Header",
	55,	1,	R_BIN,	"Bad EVx CPU Command",
	56,	1,	R_BIN,	"Halt Interrupt Pin",
	57,	1,	R_BIN,	"Hot Plug Event",
	58,	1,	R_BIN,	"Correctable Error Interrupt",
	59,	1,	R_BIN,	"Starvation Interrupt",
	60,	1,	R_BIN,	"Hard Error Interrupt",
	61,	1,	R_BIN,	"Black Hole (summary of <55:51>)",
	62,	1,	R_BIN,	"Lost Error",
	63,	1,	R_BIN,	"Error Valid (summary of 62, <55:34>)",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_bhole_msk[] = {
	0,	51,	R_NONE,	"Reserved",
	51,	1,	R_BIN,	"Block Hole Credit Timeout",
	52,	1,	R_BIN,	"Block Hole Clock Check on Header",
	53,	1,	R_BIN,	"Block Hole Double Bit Error (fatal) on Header",
	54,	1,	R_BIN,	"Block Hole Gargage on Header",
	55,	1,	R_BIN,	"Block Hole Bad EVx CPU Command",
	56,	8,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_hei_msk[] = {
	0,	32,	R_NONE,	"Reserved",
	32,	1,	R_BIN,	"Single Bit Error Detected/Corrected",
	33,	1,	R_NONE,	"Reserved",
	34,	1,	R_BIN,	"Write Byte into IO ASIC CSR",
	35,	1,	R_BIN,	"PIO Transaction Targets a Non-Existent CSR",
	36,	1,	R_BIN,	"Bus Requestor PID (Access Protection Error)",
	37,	1,	R_BIN,	"Received NXM Response Packet from EVx CPU",
	38,	1,	R_BIN,	"Received Error Response Packet",
	39,	1,	R_BIN,	"Clock Error on a Data Flit",
	40,	1,	R_BIN,	"Double Bit Error Data Error Detected",
	41,	1,	R_BIN,	"Garbage Encoding Detected on the Date",
	42,	1,	R_BIN,	"Timeout, all Responses (including inval ack)",
	43,	1,	R_BIN,	"Garbage Encoding Sent in Response Data (UPH)",
	44,	1,	R_BIN,	"Orphan Response (Unexpected Response Packet)",
	45,	1,	R_BIN,	"Down Hose Packet Overflow",
	46,	1,	R_BIN,	"Down hose Credit Overflow",
	47,	1,	R_BIN,	"Unexpected or Bad Dealloc Field",
	48,	16,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_crd_msk[] = {
	0,	32,	R_NONE,	"Reserved",
	32,	1,	R_BIN,	"Single Bit Error Detected/Corrected",
	33,	1,	R_NONE,	"Reserved",
	34,	1,	R_BIN,	"Write Byte into IO ASIC CSR",
	35,	1,	R_BIN,	"PIO Transaction Targets a Non-Existent CSR",
	36,	1,	R_BIN,	"Bus Requestor PID (Access Protection Error)",
	37,	1,	R_BIN,	"Received NXM Response Packet from EVx CPU",
	38,	1,	R_BIN,	"Received Error Response Packet",
	39,	1,	R_BIN,	"Clock Error on a Data Flit",
	40,	1,	R_BIN,	"Double Bit Error Data Error Detected",
	41,	1,	R_BIN,	"Garbage Encoding Detected on the Date",
	42,	1,	R_BIN,	"Timeout, all Responses (including inval ack)",
	43,	1,	R_BIN,	"Garbage Encoding Sent in Response Data (UPH)",
	44,	1,	R_BIN,	"Orphan Response (Unexpected Response Packet)",
	45,	1,	R_BIN,	"Down Hose Packet Overflow",
	46,	1,	R_BIN,	"Down hose Credit Overflow",
	47,	1,	R_BIN,	"Unexpected or Bad Dealloc Field",
	48,	16,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_uncrr_sym[] = {
	0,	7,	R_HEX,	"Double Bit Error Syndrome",
	7,	1,	R_BIN,	"Cycle in Error was an Odd Flit",
	8,	1,	R_BIN,	"Cycle in Error was an Even Flit",
	9,	7,	R_HEX,	"Cycle of the Error Event (2 flits/cycle)",
	16,	8,	R_HEX,	"Clock Check Symptoms - 2 bits per clock",
	24,	5,	R_HEX,	"Credit Timeout or Overflow",
	29,	3,	R_HEX,	"Buffer Overflow",
	32,	8,	R_HEX,	"South Port Number Error Response Sent to",
	40,	8,	R_HEX,	"Number of Port that Initiated the Interrupt",
	48,	10,	R_HEX,	"Interrupt Resulting in Starvation Interrupt",
	58,	6,	R_NONE,	"Resvered",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_crrct_sym[] = {
	0,	7,	R_HEX,	"Correctable Error Syndrome",
	7,	1,	R_BIN,	"Correctable Error on Odd flit",
	8,	1,	R_BIN,	"Correctable Error on Even flit",
	9,	7,	R_BIN,	"Cycle of the Error Event (2 flits/cycle)",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_err_pkt0[] = {
	0,	64,	R_STR,	"DNH Cycle 1 of Failing Packet (rising clock)",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_err_pkt1[] = {
	0,	64,	R_STR,	"DNH Cycle 2 of Failing Packet (falling clock)",
	0,	0,	R_NONE,	NULL
};

struct reg_format PO7_ugbge_sym[] = {
	0,	6,	R_NONE,	"Reserved",
	6,	32,	R_HEX,	"Up hose Packet Offset",
	38,	2,	R_NONE,	"Reserved",
	40,	8,	R_HEX,	"Up Hose Packet OPCode",
	48,	4,	R_HEX,	"Up Hose Packet Source Port",
	52,	11,	R_HEX,	"Up Hose Packet Destination ID",
	63,	1,	R_BIN,	"Summary (copy of PO7_ERROR_SUM UGBGE bit)",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_err_sum[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"AGP Request Queue Overflow",
	5,	1,	R_BIN,	"AGP Master Halted SBA bus too few idle cycles",
	6,	1,	R_BIN,	"Master Retry Timeout Exceeded (as PCI master)",
	7,	1,	R_BIN,	"PCI-X Unexpected Split Completion",
	8,	1,	R_BIN,	"PCI-X Split Completion Timeout",
	9,	1,	R_BIN,	"PCI-X Discard Split Completion",
	10,	1,	R_BIN,	"Delayed Read Timeout (delayed read discarded)",
	11,	1,	R_BIN,	"Read to Non-Existent CSR or ACV error",
	12,	1,	R_BIN,	"Write to Non-Existent CSR or ACV error",
	13,	1,	R_BIN,	"Hung Bus During a DMA Write Transaction",
	14,	1,	R_BIN,	"Split Completion Msg - PCI bus master abort",
	15,	1,	R_BIN,	"Master Abort on PCI bus except special cycles",
	16,	1,	R_BIN,	"IO ASIC Target Asserted Target Abort",
	17,	1,	R_BIN,	"IO ASIC Initiator Received a Target Abort",
	18,	1,	R_BIN,	"IO ASIC Asserted SERR#?",
	19,	1,	R_BIN,	"IO ASIC Detected address/attribute Parity Error",
	20,	1,	R_BIN,	"Detected SERR?",
	21,	1,	R_BIN,	"IO ASIC Detected R/W data or address Parity Error",
	22,	1,	R_BIN,	"IO ASIC Accepted Data with Bad Parity up-hose",
	23,	1,	R_BIN,	"Detected PERR (PCI bus Parity Error)",
	24,	1,	R_BIN,	"IO ASIC Asserted or Detected PERR#?",
	25,	1,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"IO ASIC Target of PCI-X Split Completion Error",
	27,	1,	R_NONE,	"Reserved",
	28,	1,	R_BIN,	"Hung Bus",
	29,	23,	R_NONE,	"Reserved",
	52,	7,	R_HEX,	"UPE Error up-hose DMA/PPR/MSI state machines",
	59,	1,	R_BIN,	"TLB_Err (see POx_TLB_ERR)",
	60,	1,	R_NONE,	"Reserved",
	61,	1,	R_BIN,	"Error on a PCI DMA Read Prefetch",
	62,	1,	R_NONE,	"Reserved",
	63,	1,	R_BIN,	"Error Valid",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_first_err[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"AGP Request Queue Overflow",
	5,	1,	R_BIN,	"AGP Master Halted SBA bus too few idle cycles",
	6,	1,	R_BIN,	"Master Retry Timeout Exceeded (as PCI master)",
	7,	1,	R_BIN,	"PCI-X Unexpected Split Completion",
	8,	1,	R_BIN,	"PCI-X Split Completion Timeout",
	9,	1,	R_BIN,	"PCI-X Discard Split Completion",
	10,	1,	R_BIN,	"Delayed Read Timeout (delayed read discarded)",
	11,	1,	R_BIN,	"Read to Non-Existent CSR or ACV error",
	12,	1,	R_BIN,	"Write to Non-Existent CSR or ACV error",
	13,	1,	R_BIN,	"Hung Bus During a DMA Write Transaction",
	14,	1,	R_BIN,	"Split Completion Msg - PCI bus master abort",
	15,	1,	R_BIN,	"Master Abort on PCI bus except special cycles",
	16,	1,	R_BIN,	"IO ASIC Target Asserted Target Abort",
	17,	1,	R_BIN,	"IO ASIC Initiator Received a Target Abort",
	18,	1,	R_BIN,	"IO ASIC Asserted SERR#?",
	19,	1,	R_BIN,	"IO ASIC Detected address/attribute Parity Error",
	20,	1,	R_BIN,	"Detected SERR?",
	21,	1,	R_BIN,	"IO ASIC Detected R/W data or address Parity Error",
	22,	1,	R_BIN,	"IO ASIC Accepted Data with Bad Parity up-hose",
	23,	1,	R_BIN,	"Detected PERR (PCI bus Parity Error)",
	24,	1,	R_BIN,	"IO ASIC Asserted or Detected PERR#?",
	25,	1,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"IO ASIC Target of PCI-X Split Completion Error",
	27,	1,	R_NONE,	"Reserved",
	28,	1,	R_BIN,	"Hung Bus",
	29,	23,	R_NONE,	"Reserved",
	52,	7,	R_HEX,	"UPE Error up-hose DMA/PPR/MSI state machines",
	59,	1,	R_BIN,	"TLB_Err (see POx_TLB_ERR)",
	60,	1,	R_NONE,	"Reserved",
	61,	1,	R_BIN,	"Error on a PCI DMA Read Prefetch",
	62,	1,	R_NONE,	"Reserved",
	63,	1,	R_BIN,	"Error Valid",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_msk_hei[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"AGP Request Queue Overflow",
	5,	1,	R_BIN,	"AGP Master Halted SBA bus too few idle cycles",
	6,	1,	R_BIN,	"Master Retry Timeout Exceeded (as PCI master)",
	7,	1,	R_BIN,	"PCI-X Unexpected Split Completion",
	8,	1,	R_BIN,	"PCI-X Split Completion Timeout",
	9,	1,	R_BIN,	"PCI-X Discard Split Completion",
	10,	1,	R_BIN,	"Delayed Read Timeout (delayed read discarded)",
	11,	1,	R_BIN,	"Read to Non-Existent CSR or ACV error",
	12,	1,	R_BIN,	"Write to Non-Existent CSR or ACV error",
	13,	1,	R_BIN,	"Hung Bus During a DMA Write Transaction",
	14,	1,	R_BIN,	"Split Completion Msg - PCI bus master abort",
	15,	1,	R_BIN,	"Master Abort on PCI bus except special cycles",
	16,	1,	R_BIN,	"IO ASIC Target Asserted Target Abort",
	17,	1,	R_BIN,	"IO ASIC Initiator Received a Target Abort",
	18,	1,	R_BIN,	"IO ASIC Asserted SERR#?",
	19,	1,	R_BIN,	"IO ASIC Detected address/attribute Parity Error",
	20,	1,	R_BIN,	"Detected SERR?",
	21,	1,	R_BIN,	"IO ASIC Detected R/W data or address Parity Error",
	22,	1,	R_BIN,	"IO ASIC Accepted Data with Bad Parity up-hose",
	23,	1,	R_BIN,	"Detected PERR (PCI bus Parity Error)",
	24,	1,	R_BIN,	"IO ASIC Asserted or Detected PERR#?",
	25,	1,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"IO ASIC Target of PCI-X Split Completion Error",
	27,	1,	R_NONE,	"Reserved",
	28,	1,	R_BIN,	"Hung Bus",
	29,	23,	R_NONE,	"Reserved",
	52,	7,	R_HEX,	"UPE Error up-hose DMA/PPR/MSI state machines",
	59,	1,	R_BIN,	"TLB_Err (see POx_TLB_ERR)",
	60,	1,	R_NONE,	"Reserved",
	61,	1,	R_BIN,	"Error on a PCI DMA Read Prefetch",
	62,	2,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_tlb_err[] = {
	0,	2,	R_HEX,	"I/O TLB Error Code",
	2,	1,	R_BIN,	"Not AGP Transaction",
	3,	3,	R_DEC,	"Index of Failing TLB Entry",
	6,	42,	R_HEX,	"Phys Mem Addr of TLB Entry Fetched",
	48,	15,	R_NONE,	"Reserved",
	63,	1,	R_BIN,	"Error Valid",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_spl_complt[] = {
	0,	32,	R_HEX,	"Split Completion Message (see PCI-X spec)",
	32,	12,	R_HEX,	"Split Completion Message Source",
	48,	16,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_trans_sum[] = {
	0,	50,	R_HEX,	"Failing PCI Address",
	50,	1,	R_BIN,	"Failing Address was Dual Address Cycle",
	51,	1,	R_NONE,	"Reserved",
	52,	4,	R_HEX,	"PCI-X Master Device (slot) at Time of Error",
	56,	4,	R_HEX,	"PCI Command at time this Register Locked",
	60,	3,	R_NONE,	"Reserved",
	63,	1,	R_BIN,	"Error Valid (register valid and locked)",
	0,	0,	R_NONE,	NULL
};

struct reg_format POx_mult_err[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"AGP Request Queue Overflow",
	5,	1,	R_BIN,	"AGP Master Halted SBA bus too few idle cycles",
	6,	1,	R_BIN,	"Master Retry Timeout Exceeded (as PCI master)",
	7,	1,	R_BIN,	"PCI-X Unexpected Split Completion",
	8,	1,	R_BIN,	"PCI-X Split Completion Timeout",
	9,	1,	R_BIN,	"PCI-X Discard Split Completion",
	10,	1,	R_BIN,	"Delayed Read Timeout (delayed read discarded)",
	11,	1,	R_BIN,	"Read to Non-Existent CSR or ACV error",
	12,	1,	R_BIN,	"Write to Non-Existent CSR or ACV error",
	13,	1,	R_BIN,	"Hung Bus During a DMA Write Transaction",
	14,	1,	R_BIN,	"Split Completion Msg - PCI bus master abort",
	15,	1,	R_BIN,	"Master Abort on PCI bus except special cycles",
	16,	1,	R_BIN,	"IO ASIC Target Asserted Target Abort",
	17,	1,	R_BIN,	"IO ASIC Initiator Received a Target Abort",
	18,	1,	R_BIN,	"IO ASIC Asserted SERR#?",
	19,	1,	R_BIN,	"IO ASIC Detected address/attribute Parity Error",
	20,	1,	R_BIN,	"Detected SERR?",
	21,	1,	R_BIN,	"IO ASIC Detected R/W data or address Parity Error",
	22,	1,	R_BIN,	"IO ASIC Accepted Data with Bad Parity up-hose",
	23,	1,	R_BIN,	"Detected PERR (PCI bus Parity Error)",
	24,	1,	R_BIN,	"IO ASIC Asserted or Detected PERR#?",
	25,	1,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"IO ASIC Target of PCI-X Split Completion Error",
	27,	1,	R_NONE,	"Reserved",
	28,	1,	R_BIN,	"Hung Bus",
	29,	23,	R_NONE,	"Reserved",
	52,	7,	R_HEX,	"UPE Error up-hose DMA/PPR/MSI state machines",
	59,	1,	R_BIN,	"TLB_Err (see POx_TLB_ERR)",
	60,	1,	R_NONE,	"Reserved",
	61,	1,	R_BIN,	"Error on a PCI DMA Read Prefetch",
	62,	2,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/* Support for PCI and Capabilities subpakts */
struct reg_format bpa_cnfg_adr_port[] = {
	0,	64,	R_HEX,	"BPA Cnfg Address Port",
	0,	0,	R_NONE,	NULL
};

struct reg_format vendor_id[] = {
	0,	16,	R_DEC,	"Vendor ID",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format device_id[] = {
	0,	16,	R_DEC,	"Device ID",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format bus_command[] = {
	0,	1,	R_BIN,	"IO Space Access",
	1,	1,	R_BIN,	"Memory Space Access",
	2,	1,	R_BIN,	"Bus Master",
	3,	1,	R_BIN,	"Special Cycles",
	4,	1,	R_BIN,	"Memory Write and Invalidate Enable",
	5,	1,	R_BIN,	"VGA Palette Snoop Enable",
	6,	1,	R_BIN,	"Parity Error Response",
	7,	1,	R_BIN,	"Stepping Control",
	8,	1,	R_BIN,	"SERR# Enable",
	7,	1,	R_BIN,	"Fast Back-to-Back Enable",
	10,	6,	R_NONE,	"Reserved",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE, NULL
};

struct reg_format bus_status[] = {
	0,	4,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"Capability List Supported",
	5,	1,	R_BIN,	"66Mhz capable",
	6,	1,	R_NONE,	"Reserved",
	7,	1,	R_BIN,	"Fast Back-to-back Capable",
	8,	1,	R_BIN,	"Master Data Parity Error",
	9,	2,	R_DEC,	"DEVSEL Timing",
	11,	1,	R_BIN,	"Signalled Target Abort",
	12,	1,	R_BIN,	"Received Target Abort",
	13,	1,	R_BIN,	"Received Master Abort",
	14,	1,	R_BIN,	"Signalled System Error",
	15,	1,	R_BIN,	"Detected Parity Error",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE, NULL
};

struct reg_format char_fmt[] = {
	0,	8,	R_HEX,	" ",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};


struct reg_format bist[] = {
	0,	4,	R_HEX,	"Completion Code",
	4,	2,	R_NONE,	"Reserved",
	6,	1,	R_BIN,	"Start BIST",
	7,	1,	R_BIN,	"BIST Capable",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};


struct reg_format base_address_reg[] = {
	0,	1,	R_BIN,	"I/O Space Indicator",
	1,	1,	R_NONE,	"Reserved",
	2,	30,	R_HEX,	"Base Address",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format cardbus_cis_ptr[] = {
	0,	32,	R_HEX,	"Cardbus CIS Pointer",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format subsys_vendor_id[] = {
	0,	16,	R_DEC,	"Subsystem Vendor ID",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format subsys_device_id[] = {
	0,	16,	R_DEC,	"Subsystem Device ID",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format expansion_rom_adr[] = {
	0,	1,	R_BIN,	"Address Decode Enable",
	1,	10,	R_NONE,	"Reserved",
	11,	21,	R_HEX,	"Expansion ROM Address",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};


struct reg_format split_trans_ctl[] = {
	0,	16,	R_HEX,	"Split Transaction Capacity Register",
	16,	16,	R_HEX,	"Split Transaction Commitment Limit",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format memory_data[] = {
	0,	16,	R_HEX,	" ",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format memory_data_32bits[] = {
	0,	32,	R_HEX,	" ",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format bridge_control[] = {
	0,	1,	R_BIN,	"Parity Error Response",
	1,	1,	R_BIN,	"SERR# Enable",
	2,	1,	R_BIN,	"ISA Enable",
	3,	1,	R_BIN,	"VGA Enable",
	4,	1,	R_NONE,	"Reserved",
	5,	1,	R_BIN,	"Master Abort Mode",
	6,	1,	R_BIN,	"Secondary Bus Reset",
	7,	1,	R_BIN,	"Fast Back-to-Back Enable",
	8,	1,	R_BIN,	"Primary Discard Timeout",
	9,	1,	R_BIN,	"Secondary Discard Timeout",
	10,	1,	R_BIN,	"Discard Timer Status",
	11,	1,	R_BIN,	"Discard Timer SERR# Enable",
	12,	52,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format pcix_command_reg[] = {
	0,	1,	R_BIN,	"Data Parity Error Recover Enable",
	1,	1,	R_BIN,	"Relaxed Ordering Enable",
	2,	2,	R_HEX,	"Max Memory Read Byte Count",
	4,	3,	R_HEX,	"Max Outstanding Split Transactions",
	6,	58,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format pcix_status_reg[] = {
	0,	3,	R_DEC,	"Function Number",
	3,	5,	R_DEC,	"Device Number",
	8,	8,	R_DEC,	"Bus Number",
	16,	1,	R_BIN,	"64-bit Device",
	17,	1,	R_BIN,	"133MHz Capable",
	18,	1,	R_BIN,	"Split Completion Discarded",
	19,	1,	R_BIN,	"Unexpected Split Completion",
	20,	1,	R_BIN,	"Device Complexity",
	21,	2,	R_HEX,	"Designed Max Memory Read Byte Count",
	23,	3,	R_HEX,	"Designed Max Outstanding Split Transactions",
	26,	3,	R_HEX,	"Designed Max Cumulative Read Size",
	29,	1,	R_BIN,	"Received Split Completion Error Message",
	30,	34,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format pcix_sec_status_reg[] = {
	0,	1,	R_BIN,	"64-bit Device",
	1,	1,	R_BIN,	"133MHz Capable",
	2,	1,	R_BIN,	"Split Completion Discarded",
	3,	1,	R_BIN,	"Unexpected Split Completion",
	4,	1,	R_BIN,	"Split Completion Overrun",
	5,	1,	R_BIN,	"Split Request Delayed",
	6,	3,	R_HEX,	"Secondary Clock Frequency",
	9,	55,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format pcix_bridge_status_reg[] = {
	0,	3,	R_DEC,	"Function Number",
	3,	5,	R_DEC,	"Device Number",
	8,	8,	R_DEC,	"Bus Number",
	16,	1,	R_BIN,	"64-bit Device",
	17,	1,	R_BIN,	"133MHz Capable",
	18,	1,	R_BIN,	"Split Completion Discarded",
	19,	1,	R_BIN,	"Unexpected Split Completion",
	20,	1,	R_BIN,	"Split Completion Overrun",
	21,	1,	R_BIN,	"Split Request Delayed",
	22,	42,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format msi_msg_ctl[] = {
	0,	1,	R_BIN,	"MSI Enable",
	1,	3,	R_HEX,	"Multiple Message Capable",
	4,	3,	R_HEX,	"Multiple Message Enable",
	7,	1,	R_BIN,	"64-bit Address Capable",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format msi_msg_adr[] = {
	0,	32,	R_HEX,	" ",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format msi_msg_data[] = {
	0,	16,	R_HEX,	"Message Data ",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format agp_maj_min[] = {
	0,	4,	R_HEX,	"Minor Rev",
	4,	4,	R_HEX,	"Major Rev",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format agp_status_reg[] = {
	0,	3,	R_HEX,	"Transfer Rate",
	3,	1,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"Fast Write Transactions",
	5,	1,	R_BIN,	"Address Space Greater than 4GB",
	6,	3,	R_NONE,	"Reserved",
	9,	1,	R_BIN,	"Sideband Addressing",
	10,	14,	R_NONE,	"Reserved",
	24,	8,	R_HEX,	"Max Depth of AGP Request",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format agp_command_reg[] = {
	0,	3,	R_HEX,	"Data Rate",
	3,	1,	R_NONE,	"Reserved",
	4,	1,	R_BIN,	"Fast Write Enable",
	5,	1,	R_BIN,	"Address Space Greater than 4GB Enable",
	6,	2,	R_NONE,	"Reserved",
	8,	1,	R_BIN,	"AGP Enable",
	9,	1,	R_BIN,	"Sideband Addressing Enable",
	10,	14,	R_NONE,	"Reserved",
	24,	8,	R_HEX,	"Max Depth of AGP Request of Target",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/*
 * EV7 CBOX/BBOX IPRs
 */
struct reg_format cbox_ctl[] = {
	0,	8,	R_HEX,	"PID<7:0> - This Processor's PID",
	8,	1,	R_BIN,	"Page Migration Sampling Enabled",
	9,	1,	R_HEX,	"Page Migrate Cycles Between Events (0=1,1=16)",
	10,	1,	R_HEX,	"LDs Request RdShr if set, Rd if Clear",
	11,	1,	R_BIN,	"Migratory Data Mode",
	12,	1,	R_BIN,	"Forces STxC Conservative Mode always in CMAF",
	13,	1,	R_BIN,	"Cache I-Stream Fills in Bcache",
	14,	1,	R_BIN,	"Use PA<42> as offset<28> instead of PID<7>",
	15,	1,	R_BIN,	"Enable ECC Checking",
	16,	1,	R_BIN,	"Use Only Z0",
	17,	1,	R_BIN,	"Access Checks are for 4 Processors",
	18,	1,	R_BIN,	"Local CPU can always Access Local Memory",
	19,	1,	R_BIN,	"WMBs wait for STIO's to be Acked",
	20,	1,	R_BIN,	"Tag Bypasses Disabled",
	21,	1,	R_BIN,	"System Address Bypasses Disabled",
	22,	1,	R_BIN,	"Zbox Fill Buffer Bypasses Disabled",
	23,	1,	R_BIN,	"Split Router Fills Disabled",
	24,	1,	R_BIN,	"STxC conservative Mode in CMAF Disabled",
	25,	1,	R_NONE,	"Reserved",
	26,	1,	R_BIN,	"RMAF Speculative Dcache Extracts Disabled",
	27,	1,	R_BIN,	"CMAF Coupled Tag Lookups Disabled",
	28,	1,	R_BIN,	"PRBQ treat StoD_STxC's as StoD's",
	29,	1,	R_BIN,	"PRBQ treat StoD's as StoD_STxC's",
	30,	1,	R_BIN,	"Node has no Memory (Force NXM in range check)",
	31,	1,	R_NONE,	"Reserved",
	32,	16,	R_NONE,	"Reserved",
	48,	11,	R_HEX,	"NXM_MASK<28:18> - NXM Range Check Calc Mask",
	59,	4,	R_NONE,	"Reserved",
	63,	1,	R_BIN,	"Copy of QBOX OCLA Enable Bit",
	0,	0,	R_NONE,	NULL
};
struct reg_format cbox_stp_ctl[] = {
	0,	64,	R_HEX,	"CBOX Memory Stripe Control Mask",
	0,	0,	R_NONE,	NULL
};

struct reg_format cbox_acc_ctl[] = {
	0,	64,	R_HEX,	"CBOX Memory Access Control Mask",
	0,	0,	R_NONE,	NULL
};

struct reg_format cbox_lcl_set[] = {
	0,	64,	R_HEX,	"CBOX Memory Local Set Mask",
	0,	0,	R_NONE,	NULL
};

struct reg_format cbox_gbl_set[] = {
	0,	64,	R_HEX,	"CBOX Memory Gloal Set Mask",
	0,	0,	R_NONE,	NULL
};

struct reg_format bbox_ctl[] = {
	0,	7,	R_HEX,	"SET_ENA<6:0> L2 cache Set Enables",
	7,	1,	R_NONE,	"Reserved",
	8,	3,	R_HEX,	"EVICT_NEXT<2:0> Evict Next Set",
	11,	3,	R_NONE,	"Reserved",
	14,	1,	R_HEX,	"L2 cache sts Parity Check Enable",
	15,	1,	R_HEX,	"L2 cache tag Parity Check Enable",
	16,	1,	R_HEX,	"Ttag Parity Check Enable",
	17,	1,	R_HEX,	"Force Bad L2 cache sts Parity, 1 shot",
	18,	1,	R_HEX,	"Force Bad L2 cache tag Parity, 1 shot",
	19,	1,	R_HEX,	"Force Bad Ttag Parity, 1 shot",
	20,	3,	R_HEX,	"set # to remap to set 0 in L2 cache NW corner",
	23,	3,	R_HEX,	"set # to remap to set 0 in L2 cache NE corner",
	26,	3,	R_HEX,	"set # to remap to set 0 in L2 cache SE corner",
	29,	3,	R_HEX,	"set # to remap to set 0 in L2 cache SW corner",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format bbox_err_sts[] = {
	0,	7,	R_HEX,	"BSTS_PAR<6:0> per set L2 cache sts Parity Error",
	7,	1,	R_NONE,	"Reserved",
	8,	7,	R_HEX,	"BTAG_PAR<6:0> per set L2 cache tag Parity Error",
	15,	1,	R_NONE,	"Reserved",
	16,	8,	R_HEX,	"TTAG_PAR<7:0> per VA/set ttag Parity Error",
	24,	1,	R_BIN,	"Error was Uncorrectable",
	25,	1,	R_BIN,	"Error was Correctable",
	26,	1,	R_BIN,	"Second Correctable Error Occurred",
	27,	37,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format bbox_err_idx[] = {
	0,	6,	R_NONE,	"Reserved",
	6,	12,	R_HEX,	"L2 idx of locked/most recent tag parity error",
	18,	46,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format cbox_ddp_err_sts[] = {
	0,	1,	R_BIN,	"Uncorrectable Error",
	1,	1,	R_BIN,	"Correctable Error",
	2,	1,	R_BIN,	"Second Correctable Error Occurred",
	3,	3,	R_HEX,	"ERR_SET<2:0> Bcache set of Error",
	6,	12,	R_HEX,	"ERR_IDX<17:6> Bcache index of Error",
	18,	2,	R_NONE,	"Reserved",
	20,	9,	R_HEX,	"ERR_SYN<8:0> ECC Error Syndrome",
	29,	1,	R_HEX,	"SIDE, DP0 or DP1",
	30,	34,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format bbox_dat_rmp[] = {
	0,	7,	R_HEX,	"Sets which failed BIST/BISR in SE corner",
	7,	1,	R_NONE,	"Reserved",
	8,	7,	R_HEX,	"Sets which failed BIST/BISR in SW corner",
	15,	1,	R_NONE,	"Reserved",
	16,	7,	R_HEX,	"Sets which failed BIST/BISR in NW corner",
	23,	1,	R_NONE,	"Reserved",
	24,	7,	R_HEX,	"Sets which failed BIST/BISR in NE corner",
	31,	33,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/*
 * EV6 core IPRs (only IPRs captured in MCHK logout frame).
 */
struct reg_format EV6_i_stat[] = {
	0,	29,	R_NONE,	"Reserved",
	29,	1,	R_BIN,	"Parity Error",
	30,	34,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_dc_stat[] = {
	0,	1,	R_BIN,	"Tag Parity Error - Pipe 0",
	1,	1,	R_BIN,	"Tag Parity Error - Pipe 1",
	2,	1,	R_BIN,	"ECC Error on Store",
	3,	1,	R_BIN,	"ECC Error on Load",
	4,	1,	R_BIN,	"Second Error Occurred",
	5,	59,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_addr_v[] = {
	0,	64,	R_HEX,	"Address of last ECC or Parity Error",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_addr_nv[] = {
	0,	64,	R_HEX,	"Contents of C_ADDR not valid",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_syndrome_1[] = {
	0,	8,	R_HEX,	"Syndrome for the upper quadword",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_syndrome_0[] = {
	0,	8,	R_HEX,	"Syndrome for the lower quadword",
	8,	56,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_stat_40[] = {
	0,	1,	R_BIN,	"Bad octaword asserted",
	1,	1,	R_BIN,	"Single-bit error occurred",
	2,	1,	R_BIN,	"Double-bit error occurred",
	3,	1,	R_HEX,	"C_STAT[3]: (1=Istream, 0=Dstream)",
	4,	1,	R_HEX,	"C_STAT[4]: Source of Error",
	5,	59,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_stat_41[] = {
	0,	3,	R_HEX,	"1=CMTO_RSP 2=CMTO_COH 3=IO_TO 4=ER_RSP 5=DS_DC_ERR",
	3,	1,	R_HEX,	"C_STAT[3]: (1=Istream, 0=Dstream)",
	4,	1,	R_HEX,	"C_STAT[4]: Source of Error",
	5,	59,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_c_sts[] = {
	0,	1,	R_BIN,	"Block Status is Shared",
	1,	1,	R_BIN,	"Block Status is Dirty",
	2,	1,	R_BIN,	"Block Status is Valid (if C_STAT[3]=0)",
	3,	1,	R_BIN,	"C_ADDR_BAD (DBE logged, but C_ADDR invalid)",
	4,	60,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_mm_stat[] = {
	0,	1,	R_BIN,	"Error on Write Transaction",
	1,	1,	R_BIN,	"Access Violation durring Transaction",
	2,	1,	R_BIN,	"Fault On Read Error durring Transaction",
	3,	1,	R_BIN,	"Fault On Write Error durring Transaction",
	4,	6,	R_HEX,	"Opcode of Instruction that caused the Error",
	10,	1,	R_BIN,	"Dcache Tag Parity Error [probe of load/store]",
	11,	53,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_exc_addr[] = {
	0,	1,	R_BIN,	"PC in PALcode",
	1,	1,	R_NONE,	"Reserved",
	2,	62,	R_HEX,	"PC[63:2]",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_ier_cm[] = {
	0,	3,	R_NONE,	"Reserved",
	3,	2,	R_HEX,	"Current Mode [00-kern,01-exec,10-Sup,11-User]",
	5,	8,	R_NONE,	"Reserved",
	13,	1,	R_BIN,	"AST Interrupt Enable",
	14,	15,	R_HEX,	"Software Interrupt Enables",
	29,	2,	R_HEX,	"Performance Counter Interrupt Enables",
	31,	1,	R_BIN,	"Corrected Read Error Interrupt Enable",
	32,	1,	R_BIN,	"Serial Line Interrupt Enable",
	33,	6,	R_HEX,	"External Interrupt Enable",
	39,	25,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_isum[] = {
	0,	3,	R_NONE,	"Reserved",
	3,	1,	R_BIN,	"ASTK Interrupt",
	4,	1,	R_BIN,	"ASTE Interrupt",
	5,	4,	R_NONE,	"Reserved",
	9,	1,	R_BIN,	"ASTS Interrupt",
	10,	1,	R_BIN,	"ASTU Interrupt",
	11,	3,	R_NONE,	"Reserved",
	14,	15,	R_HEX,	"Software Interrupts",
	29,	2,	R_HEX,	"Performance Counter Interrupts",
	31,	1,	R_BIN,	"Corrected Read Error Interrupt",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_pal_base[] = {
	0,	44,	R_HEX,	"Base Physical Address for PALcode",
	45,	19,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_i_ctl[] = {
	0,	1,	R_BIN,	"System Performance Counting Enable",
	1,	2,	R_HEX,	"Icache Set Enable",
	3,	1,	R_BIN,	"SPE[0] 32-bit Super Page Mode Enable",
	4,	1,	R_BIN,	"SPE[1] 43-bit Super Page Mode Enable",
	5,	1,	R_BIN,	"SPE[2] 48-bit Super Page Mode Enable",
	6,	2,	R_HEX,	"PALshadow Register Enable",
	8,	2,	R_HEX,	"Stream Buffer Enable",
	10,	2,	R_HEX,	"Branch Prediction Mode Selection",
	12,	1,	R_BIN,	"HWE Allows PALRES instructions in kernel mode",
	13,	1,	R_BIN,	"SL_XMIT",
	14,	1,	R_BIN,	"SL_RCV",
	15,	1,	R_BIN,	"VA_48",
	16,	1,	R_BIN,	"VA_FORM_32",
	17,	1,	R_BIN,	"Single Issue Mode",
	18,	1,	R_BIN,	"Enable Performance Counter 0",
	19,	1,	R_BIN,	"Enable Performance Counter 1",
	20,	1,	R_BIN,	"CALL_PAL_R23",
	21,	1,	R_BIN,	"Machine Check Enable",
	22,	1,	R_BIN,	"TB_MB_EN",
	23,	1,	R_BIN,	"BIST_FAIL",
	24,	6,	R_HEX,	"CHIP_ID",
	30,	18,	R_HEX,	"Virtual Page Table Base[47:30]",
	48,	16,	R_HEX,	"SEXT(VPTB[47])",
	0,	0,	R_NONE,	NULL
};

struct reg_format EV6_process_context[] = {
	0,	1,	R_NONE,	"Reserved",
	1,	1,	R_BIN,	"Process Performance Counting Enable",
	2,	1,	R_BIN,	"Floating Point Enable",
	3,	2,	R_NONE,	"Reserved",
	5,	1,	R_BIN,	"AST Enable Register - Kernel Mode",
	6,	1,	R_BIN,	"AST Enable Register - Exec Mode",
	7,	1,	R_BIN,	"AST Enable Register - Super Mode",
	8,	1,	R_BIN,	"AST Enable Register - User Mode",
	9,	1,	R_BIN,	"ASE Request Register - Kernel Mode",
	10,	1,	R_BIN,	"ASE Request Register - Exec Mode",
	11,	1,	R_BIN,	"ASE Request Register - Super Mode",
	12,	1,	R_BIN,	"ASE Request Register - User Mode",
	13,	26,	R_NONE,	"Reserved",
	39,	8,	R_DEC,	"Address Space Number",
	47,	17,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/*
 * EV7 ZBOX (memory controller) IPRs
 */
struct reg_format zbox01_dram_err_status_1[] = {
	0,	5,	R_NONE,	"Reserved",
	5,	6,	R_HEX,	"Directory Syndrome for Single Bit ECC error",
	11,	3,	R_NONE,	"Reserved",
	14,	9,	R_HEX,	"ECC Syndrome for Octaword 1",
	23,	9,	R_HEX,	"ECC Syndrome for Octaword 0",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dram_err_status_2[] = {
	0,	5,	R_HEX,	"Bitmask of Channels with Bad Temp. Cal. Error",
	5,	5,	R_HEX,	"Which Device had Temp. Cal. Error",
	10,	4,	R_NONE,	"Reserved",
	14,	9,	R_HEX,	"ECC Syndrome for Octaword 3",
	23,	9,	R_HEX,	"ECC Syndrome for Octaword 2",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dram_err_status_3[] = {
	0,	1,	R_BIN,	"PAR - One or more Parity Errors on Read",
	1,	1,	R_BIN,	"SGL - One/Two Single Bit ECC Errors on Read",
	2,	1,	R_BIN,	"RAID - Raid-Remap (remapping was selected)",
	3,	1,	R_BIN,	"MAPF - Raid-Remap (no unique best remapping)",
	4,	1,	R_BIN,	"GE3 - Three/more Single Bit ECC Error on Read",
	5,	1,	R_BIN,	"DBL - Double Bit ECC Error on Read",
	6,	1,	R_BIN,	"D21 - Directory<21> was Read as One",
	7,	1,	R_BIN,	"TCAL - Some Channel had Over Temp. Fault",
	8,	1,	R_BIN,	"TIME - A DIFT Timeout Occurred",
	9,	1,	R_BIN,	"DIFT - A DIFT Error Occurred DIFT_ERR_STS!=0",
	10,	3,	R_NONE,	"Reserved",
	13,	1,	R_BIN,	"MEO - 2nd Correctable Err (no Phys Addr saved)",
	14,	1,	R_BIN,	"SEO - 2nd Uncorrectable Err (no Phys Addr saved)",
	15,	1,	R_BIN,	"SWP - Error Ocurred During Sweep Mode Read",
	16,	16,	R_NONE,	"Reserved",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dram_error_ctl[] = {
	0,	10,	R_HEX,	"ERR_INT_ENAB<9:0> - Interrupt Enables",
	10,	9,	R_NONE,	"Reserved",
	19,	5,	R_HEX,	"RAID_MAP(4,0) - Channel Should be Re-Mapped",
	24,	1,	R_BIN,	"RAID_ON - Byte Writes Disabled",
	25,	1,	R_BIN,	"SET_DIR_21 - Force Spare Dir Bit on adr-match",
	26,	3,	R_HEX,	"FRC_WTERR(2,0) - Force Err if Zbox adr-match",
	29,	1,	R_BIN,	"ECC_COR_ENABLED - ECC Correction Enabled",
	30,	1,	R_BIN,	"FRC_LOCAL - Force Dir. Data to DIFT to RAZ",
	31,	1,	R_BIN,	"FIFTH_CH_ENA - RAID Channel Powered & Enabled",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dram_err_adr[] = {
	0,	29,	R_HEX,	"ERR_ADDR - Mem Adr of 1st (more serious) Err",
	29,	3,	R_NONE,	"Reserved",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dift_timeout[] = {
	0,	31,	R_HEX,	"DIFT_TIMEOUT_VALUE<30:0> - DIFT Timeout Val",
	31,	1,	R_BIN,	"DIFT_TIMEOUT_EN - DIFT Timeout Enabled",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dram_mapper_ctl[] = {
	0,	1,	R_BIN,	"SPLIT_BNK - Split Bank Mode Enabled",
	1,	1,	R_BIN,	"DEP_BNK - Dependent Bank Mode Enabled",
	2,	2,	R_HEX,	"COL_WIDTH_OFF<1:0> - Column Width Offset",
	4,	3,	R_HEX,	"RWL_WIDTH<2:0> - Row Low Width (# of bits)",
	7,	3,	R_HEX,	"ROW_WIDTH_OFF<2:0> - Number of Row Bits",
	10,	3,	R_HEX,	"BNK_WIDTH_OFF<2:0> - BANK Width Offset",
	13,	2,	R_HEX,	"DEV_WIDTH_OFF<1:0> - Device Width Offset",
	15,	3,	R_HEX,	"RWL_START_OFF<2:0> - Row Low Start Offset",
	18,	4,	R_HEX,	"RWH_START_OFF<3:0> - Row High Start Offset",
	22,	4,	R_HEX,	"BNK_START_OFF<3:0> - Bank Start Offset",
	26,	3,	R_HEX,	"DEV_START_OFF<2:0> - Device Start Offset",
	29,	1,	R_HEX,	"NUM_PORT_OFF - # Active Memory Ports (0=1,1=2)",
	30,	1,	R_HEX,	"DEV_WIDTH_OFF<2> - Device Width Offset",
	31,	1,	R_NONE,	"Reserved",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_frc_err_adr[] = {
	0,	7,	R_HEX,	"FRC_COL<6:0> - RAMBUS Column Number",
	7,	13,	R_HEX,	"FRC_ROW<12:0> - RAMBUS Row Number",
	20,	6,	R_HEX,	"FRC_BNK<5:0> - RAMBUS Bank Number",
	26,	5,	R_HEX,	"FRC_DEV<4:0> - RAMBUS Device Number",
	31,	1,	R_NONE,	"Reserved",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format zbox01_dift_err_status[] = {
	0,	32,	R_HEX,	"DIFT_ERR_STATUS<31:0> - DIFT HW Error Bits",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/* MV_NOTE: not a CSR, subpkt entry constructed by PALcode */
struct reg_format zbox01_error_pa[] = {
	0,	44,	R_HEX,	"Zbox Error Physical Address",
	45,	19,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

/* MV_NOTE: not a CSR, subpkt entry constructed by PALcode */
struct reg_format zbox01_ored_syndrome[] = {
	0,	64,	R_HEX,	"Zbox ORED ECC Syndrome",
	0,	0,	R_NONE,	NULL
};

/*
 * EV7 RBOX (router) IPRs
 */
struct reg_format rbox_cfg[] = {
	0,	4,	R_HEX,	"SPD[3:0] - Speed Ratio of the Pins",
	4,	1,	R_HEX,	"PRI - NS or EW Primary Axis",
	5,	1,	R_HEX,	"STR - Assume 'can adapt' Sent on Primary Axis",
	6,	1,	R_HEX,	"ADA - Enable Adaptive Routing",
	7,	1,	R_HEX,	"ADB - Enable Adpative Buffers",
	8,	1,	R_NONE,	"Reserved",
	9,	4,	R_HEX,	"BRO<3:0> - Outputs to Forward Broadcasts to",
	13,	1,	R_HEX,	"SYC - Enable SYNCHs",
	14,	3,	R_HEX,	"SVF<2:0> - SYNCH Frequency",
	17,	1,	R_HEX,	"RSE - Reservation Enable",
	18,	3,	R_HEX,	"STI<2:0> - Starvation Interval",
	21,	1,	R_HEX,	"DRE - Drain Enable",
	22,	3,	R_HEX,	"DRI<2:0> - Drain Interval",
	25,	2,	R_HEX,	"TAS<1:0> - InvalAck Table A Select",
	27,	2,	R_HEX,	"TBS<1:0> - InvalAck Table B Select",
	29,	2,	R_HEX,	"TCS<1:0> - InvalAck Table C Select",
	31,	1,	R_HEX,	"IRW - Writes to Router Table Ignored",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_NSEW_cfg[] = {
	0,	1,	R_BIN,	"OE - Output Enable",
	1,	1,	R_BIN,	"INI - Put the Port in 'init mode'",
	2,	1,	R_BIN,	"IE - Input Enable",
	3,	4,	R_HEX,	"BRO<3:0> - Outputs to Forward Broadcasts to",
	7,	1,	R_HEX,	"BMS - Broadcast Master Select",
	8,	1,	R_HEX,	"BIL - Broadcast Inval Limit (0 = 8, 1 = 16)",
	9,	1,	R_BIN,	"HAE - Enable Receiving HW Alert",
	10,	1,	R_BIN,	"SAE - Enable Receiving SW Alert",
	11,	1,	R_BIN,	"SYC - Enable Receiving SYNCH",
	12,	1,	R_BIN,	"CLC - Enable Fclk Checking",
	13,	1,	R_BIN,	"ECC - Enable ECC Checking/Correction",
	14,	2,	R_HEX,	"UNI<1:0> - Upload Pointer Init Value (CF rst)",
	16,	1,	R_BIN,	"SYE - Run the Port Input in Synchronous Mode",
	17,	1,	R_NONE,	"Reserved",
	18,	2,	R_HEX,	"FEM - Force Error Mode",
	20,	1,	R_BIN,	"IGD - Ignore Incoming Deallocs",
	21,	2,	R_HEX,	"TUN<1:0> - Enable Tuning Mechanism",
	23,	41,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_nsew_err[] = {
	0,	1,	R_BIN,	"SBE - Single Bit Error",
	1,	1,	R_BIN,	"MSE - Multpile Single Bit Errors",
	2,	7,	R_HEX,	"SYN<6:0> - ECC Syndrome",
	9,	1,	R_BIN,	"DBE - Double Bit Error",
	10,	1,	R_BIN,	"FCE - Forward Clock Error",
	11,	1,	R_BIN,	"BPE - Buffer Parity Error",
	12,	1,	R_BIN,	"RSTX - Response Timer Expired",
	13,	1,	R_BIN,	"RETX - Request Timer Expired",
	14,	1,	R_BIN,	"FWTX - Forward Timer Expired",
	15,	1,	R_BIN,	"RITX - RIO Timer Expired",
	16,	1,	R_BIN,	"WITX - WIO Timer Expired",
	17,	1,	R_BIN,	"FOTX - Fanout Timer Expired",
	18,	1,	R_BIN,	"FITX - Fanin Timer Expired",
	19,	45,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_io_cfg[] = {
	0,	1,	R_BIN,	"Enable Output",
	1,	1,	R_NONE,	"Reserved",
	2,	1,	R_BIN,	"Enable Input",
	3,	1,	R_BIN,	"Enable Receiving HW ALERT",
	4,	1,	R_BIN,	"Enable Forward-Clock Checking",
	5,	4,	R_HEX,	"Gclk Cycles per Data Beat",
	9,	1,	R_BIN,	"Synchronous Input Mode Enable (lock-step)",
	10,	2,	R_HEX,	"Upload Pointer Init Value (for lock-step)",
	12,	1,	R_NONE,	"Reserved",
	13,	1,	R_BIN,	"Drive True NOPs",
	14,	1,	R_BIN,	"Enable ECC Checking",
	15,	1,	R_BIN,	"No Disable Output on IO Port Black-Hole",
	16,	2,	R_HEX,	"Force Error Mode",
	18,	1,	R_BIN,	"Ignore Incoming Deallocs",
	19,	2,	R_HEX,	"Read/Write Enable Tuning Mechanism",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_io_err[] = {
	0,	1,	R_BIN,	"SBE - Single Bit Error",
	1,	1,	R_BIN,	"MSE - Multpile Single Bit Errors",
	2,	7,	R_HEX,	"SYN<6:0> - ECC Syndrome",
	9,	1,	R_BIN,	"DBE - Double Bit Error",
	10,	1,	R_BIN,	"FCE - Forward Clock Error",
	11,	1,	R_BIN,	"BPE - Buffer Parity Error",
	12,	1,	R_BIN,	"RSTX - Response Timer Expired",
	13,	1,	R_BIN,	"FWTX - Forward Timer Expired",
	14,	1,	R_BIN,	"RITX - RIO Timer Expired",
	15,	1,	R_BIN,	"WITX - WIO Timer Expired",
	16,	48,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_l_err[] = {
	0,	1,	R_BIN,	"CBP - Cbox Buffer Parity Error",
	1,	1,	R_BIN,	"Z0P - Z0 Buffer Parity Error",
	2,	1,	R_BIN,	"Z1P - Z1 Buffer Parity Error",
	3,	1,	R_BIN,	"RPE - Router Table Parity Error",
	4,	1,	R_BIN,	"Z0FI - Z0 Fanin Timer Expired",
	5,	1,	R_BIN,	"Z1FI - Z1 Fanin Timer Expired",
	6,	1,	R_BIN,	"CBD - CSR Bad Data Received",
	7,	57,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_whoami[] = {
	0,	4,	R_HEX,	"NS WHOAMI Value",
	4,	4,	R_HEX,	"EW WHOAMI Value",
	0,	0,	R_NONE,	NULL
};

struct reg_format rbox_intq[] = {
	0,	24,	R_HEX,	"IQE - Head of Interrupt Queue",
	24,	1,	R_BIN,	"VAL - Queue Entry Valid",
	25,	39,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};
struct reg_format rbox_INTMASK[] = {
	0,	1,	R_BIN,	"CCRDL - CBOX Correctable Lock-Step",
	1,	1,	R_BIN,	"CCRDN - CBOX Correctable No Lock-Step",
	2,	1,	R_BIN,	"Z0CRD - ZBOX0 Correctable",
	3,	1,	R_BIN,	"Z1CRD - ZBOX1 Correctable",
	4,	1,	R_BIN,	"RCRD - RBOX Correctable",
	5,	1,	R_BIN,	"CPERF - CBOX Performance Counter",
	6,	1,	R_BIN,	"Z0PERF - ZBOX0 Performance Counter",
	7,	1,	R_BIN,	"Z1PERF - ZBOX1 Performance Counter",
	8,	1,	R_BIN,	"RPERF - RBOX Performance Counter",
	9,	1,	R_BIN,	"GIOL - GIO Interrupt",
	10,	1,	R_BIN,	"IOACRD - I/O ASIC Correctable/SW",
	11,	1,	R_BIN,	"RES<11> - Reserved for SW",
	12,	1,	R_BIN,	"INTQ - Interrupt Queue",
	13,	1,	R_BIN,	"RES<13> - Reserved for SW",
	14,	1,	R_BIN,	"PALSTV - Interrupt Starvation Avoidance",
	15,	1,	R_BIN,	"INTT - Interval Timer",
	16,	1,	R_BIN,	"INTTO - Interrupt Queue Retry Timeout/SW",
	17,	1,	R_BIN,	"IOHP - Hot-Plug IO Event/SW",
	18,	1,	R_BIN,	"SWAL - Software ALERT",
	19,	1,	R_BIN,	"PALIPI - InterProcessor Interrupt",
	20,	1,	R_BIN,	"RES<20> - Reserved for SW",
	21,	1,	R_BIN,	"GIOH - GIO High Priority Interrupt",
	22,	1,	R_BIN,	"HALT - HALT/SW",
	23,	1,	R_BIN,	"RES<23> - Reserved for SW",
	24,	1,	R_BIN,	"HWAL - Hardware ALERT",
	25,	1,	R_BIN,	"CUCE - CBOX Uncorrectable",
	26,	1,	R_BIN,	"Z0UCE - ZBOX0 Uncorrectable",
	27,	1,	R_BIN,	"Z1UCE - ZBOX1 Uncorrectable",
	28,	1,	R_BIN,	"RUCE - RBOX Uncorrectable",
	29,	1,	R_BIN,	"IOAUCE - I/O ASIC Error/SW",
	30,	1,	R_BIN,	"OCLA0 - On-Chip Logic Analyzer 0",
	31,	1,	R_BIN,	"OCLA1 - On-Chip Logic Analyzer 1",
	32,	32,	R_NONE,	"Reserved",
	0,	0,	R_NONE,	NULL
};
#endif	/* MV_INCLUDE_MARVEL_CPU */

/*
 * If Marvel ever has diff. family members,
 * these macros will be useful.
 */
#define MEMBER_ID_SHIFT 10
#define MEMBER_ID 0xfc00L

/*
 * Marvel specific data structure for organizing processors
 * and their associated memory into RADs/MADs.
 */

#define EV7_PASS1 (((long)EV7_PASS1_MINOR_ID << RPB_PROCTYPE_MINOR_SHIFT) | \
								(long)EV7_CPU)
#define EV7_PASS2 (((long)EV7_PASS2_MINOR_ID << RPB_PROCTYPE_MINOR_SHIFT) | \
								(long)EV7_CPU)
#define EV79_PASS1 (((long)1L << RPB_PROCTYPE_MINOR_SHIFT) | (long)EV79_CPU)

#define MV_ACC_LOCAL		0
#define MV_ACC_REMOTE		1
#define MV_MEM_LINEAR		0
#define MV_MEM_STRIPED		1
#define MV_REGION_256MB		0
#define MV_REGION_16MB		1

struct mvrads_cpu_info {
    int		available:1;		/* set but currently not used */
    int		has_striped_mem:1;	/* some/all of CPU's memory striped */
    int		has_linear_mem:1;	/* some/all of CPU's memory linear */
    int		has_shared_mem:1;	/* CPU has shared global memory */
    int		stripe_default:1;	/* memory: 0 = linear, 1 = striped */
    int		access_default:1;	/* memory: 0 = local, 1 = remote */
    int		region_16mb:1;		/* mem region: 0 = 256mb, 1 = 16mb */
    int		ev7_pass1:1;		/* odd ball stripe/access control */
    int		cpus_per_soc:4;		/* # of CPUs/EV#x (set, but not used)*/
    int		stripe_set_size:4;	/* stripe across this many SOCs */
    int		sbz:16;
    int		pad;
    u_long	cbox_stp_ctl;		/* CPU's CBOX stripe control IPR */
    u_long	cbox_acc_ctl;		/* CPU's CBOX access control IPR */
};

extern struct mvrads_cpu_info mvrads_cpu_info[];

/* RAD related debug code for Marvel.
 */
/*#define MVCPU_RAD_DEBUG		1*/

#ifdef MV_LOCAL_ONLY
#define MVCPU_NUM_MCL		48
#else
#define MVCPU_NUM_MCL		(48 + 8)
#endif


/*
 * Interrupt enable method:
 *
 *  0	Leave rbox_imask as set by PALcode (don't set/clear any IE bits).
 *  1	Use PAL's rbox_imask, but clear RBOX_INT_ERRMASK bits during IO probe.
 *  2	Brute force rbox_imask to initial/final IE bits (see globals below)
 *	(except for IE's owned by the console firmware).
 *  3	Disable only IO7 error interrupts during IO probe.
 *
 */
#define MVCPU_IEM_USEPAL	0
#define MVCPU_IEM_ERRMASK	1
#define MVCPU_IEM_BLAST		2
#define MVCPU_IEM_IO7ERR	3

extern u_long	mvcpu_intr_enable_method;
extern u_long	mvcpu_initial_intr_enables;
extern u_long	mvcpu_final_intr_enables;

/*
 * marvel_cpu.c debugging aid
 *	-- modelled after pci_debug.h
 *
 * NOTE: since marvel_cpu.h, marvel_soc.h, & marvel_pci.h may be included in
 *	 one .c file, their definitions must not collide.
 */

extern	u_int	mvcpu_developer_debug;

/* To remove/add all debug printfs */
#define __MVCPUDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * mvcpu_developer_debug.
 */


/* Bit defines used to turn on debug printfs */

/* The following defines are used for the flag bits in the printf macro. */

#define	MVCPUD_INOUT	0x00000001	/* routine entry and exit 	*/
#define MVCPUD_CPU	0x00000010	/* CPU-related info		*/
#define MVCPUD_NUMA	0x00000020	/* NUMA-related info		*/
#define MVCPUD_SOCCONF	0x00000040	/* SOC config info		*/
#define MVCPUD_DMAINFO	0x00000080	/* system-level dma settings	*/
#define MVCPUD_EV6_B2T	0x00000100	/* enable bit2text for EV6 core regs */
#define MVCPUD_CAPS_B2T	0x00000200	/* enable bit2text for capability regs */
#define MVCPUD_CE_B2T	0x00001000	/* enable bit2text for correctables  */
#define MVCPUD_UCE_B2T	0x00002000	/* enable bit2text for uncorrectable */
#define MVCPUD_CUCE_B2T	0x00004000	/* enable bit2text for 6A0/6B0 MCHK  */
#define MVCPUD_NO_ELOG	0x00008000	/* disable binary error logging      */
#define MVCPUD_CE	0x00010000	/* enable consprint - correctables   */
#define MVCPUD_UCE	0x00020000	/* enable consprint - uncorrectables */
#define MVCPUD_SYSEVT	0x00040000	/* enable consprint - environmental  */
#define MVCPUD_ERRLOG	0x00080000	/* Error-logging info		*/
					/* VM memory troller		    */
#define MVCPUD_VMMT	0x00100000	/* don't supress HSL/GPL parsing    */
#define MVCPUD_VMMT1	0x00200000	/* don't suppress 660 mchk printf's */
#define MVCPUD_INTR	0x00400000	/* print enabled/pending intr/error  */
#define MVCPUD_ERRCLR	0x00800000	/* print error bit clear diag msg's */

/* New, testing hw-support debug printfs (MV_NOTE: Wildfire dregg)	*/
#define MVCPUD_NOTYET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _MVCPUinout;
extern char * _MVCPUnuma;
extern char * _MVCPUcpu;
extern char * _MVCPUdmainfo;
extern char * _MVCPUsocconf;
extern char * _MVCPUerrlog;
extern char * _MVCPUce;
extern char * _MVCPUuce;
extern char * _MVCPUnotyet;


/*
 * printf expansion that MVCPUPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _MVCPUxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef __MVCPUDEBUG
#   define _MVCPUD_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_INOUT )  {	\
	    /* VARARGS */			\
            printf (_MVCPUinout); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_NUMA(X)			\
    {						\
	/* NOSTRICT */				\
         if( mvcpu_developer_debug & MVCPUD_NUMA ) {	\
	    /* VARARGS */			\
            printf (_MVCPUnuma); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_CPU(X)			\
    {						\
	/* NOSTRICT */				\
         if( mvcpu_developer_debug & MVCPUD_CPU ) {	\
	    /* VARARGS */			\
            printf (_MVCPUcpu); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_DMAINFO(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_DMAINFO)  {	\
	    /* VARARGS */			\
            printf (_MVCPUdmainfo); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_SOCCONF(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_SOCCONF)  {	\
	    /* VARARGS */			\
            printf (_MVCPUsocconf); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_ERRLOG(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_ERRLOG)  {	\
	    /* VARARGS */			\
            printf (_MVCPUerrlog); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_CE(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_CE)  {	\
	    /* VARARGS */			\
            printf (_MVCPUce); 		        \
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_UCE(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_UCE)  {	\
	    /* VARARGS */			\
            printf (_MVCPUuce); 		        \
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _MVCPUD_NOTYET(X)			\
    {						\
	/* NOSTRICT */				\
        if( mvcpu_developer_debug & MVCPUD_NOTYET)  {	\
	    /* VARARGS */			\
            printf (_MVCPUnotyet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * mvcpu_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * MVCPUD_INOUT | MVCPUD_CPU
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define MVCPUPRINTF(F, X)	_##F(X)

#else  /* !__MVCPUDEBUG */
#   define MVCPUPRINTF(F, X)
#endif /* __MVCPUDEBUG */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif	/* __ARCH_ALPHA_HAL_MARVEL_CPU_H__ */

