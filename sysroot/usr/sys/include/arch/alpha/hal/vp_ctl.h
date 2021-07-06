/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vp_ctl.h,v $
 * Revision 1.1.2.2  2003/06/23  18:22:16  Andrew_Duane
 * 	Add cpu_number to outbound data register packet, and bump VERSION to 3.
 *
 * Revision 1.1.2.1  2003/06/03  18:52:17  Andrew_Duane
 * 	Check in for RCS revision control.
 * 	[2003/05/22  18:57:14  Andrew_Duane]
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vp_ctl.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 2003/06/23 18:22:16 $
 */

/*
 * Header file for VP control server and client (and driver)
 */


#ifdef __cplusplus
extern "C" {
#endif

/* Define the incoming and outgoing data structures */
#ifndef _KERNEL
/* (direction as seen from the chip; in gets written */
/* to the IPRs, out gets read from IPRs and returned) */
/* There is one of these for each CPU. */
#endif

typedef struct vpctl_in {
	u_long	ev7_vpctl;
	u_long	ev7_dir_datamode0;
	u_long	ev7_dir_datamode1;
} vpctl_in_t;

typedef struct vpctl_out {
	u_long	cpu_number;		/* target system's assigned CPU # */
	u_long	zbox0_dram_timing_ctl1;
	u_long	zbox1_dram_timing_ctl1;
	u_long	zbox0_dram_mapper_ctl;
	u_long	zbox1_dram_mapper_ctl;
	u_long	rbox_cfg;
	u_long	rbox_n_cfg;
	u_long	rbox_s_cfg;
	u_long	rbox_e_cfg;
	u_long	rbox_w_cfg;
	u_long	rbox_io_cfg;
	u_long	rbox_whoami;
	u_long	ev7_clockfreq;
	u_long	ev7_vpctl;		/* copy of inbound data */
	u_long	ev7_dir_datamode0;	/* copy of inbound data */
	u_long	ev7_dir_datamode1;	/* copy of inbound data */
} vpctl_out_t;

#ifndef _KERNEL
/* Values for "action" command between server and client */
#define GetRegisters     0  /* read <NCPUs> vpctl_out structures from server */
#define SetRegisters     1  /* send <NCPUs> vpctl_in structures to server */
#define GetConfiguration 2  /* return Configuration Packet */
#define Exit             3  /* tell server to clean up and exit */

#define BROADCAST	-1  /* set/get all CPUs at once */

/* rpc defines for registering with the partmapper */
#define VPCTL_PROGNAME	100100		/* listed in /etc/rpc */
#define VPCTL_VERSION	3		/* current version */
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

