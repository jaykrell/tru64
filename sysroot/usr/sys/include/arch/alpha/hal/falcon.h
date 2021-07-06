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
 * @(#)$RCSfile: falcon.h,v $ $Revision: 1.1.14.2 $ (DEC) $Date: 2001/11/01 19:57:19 $
 */

#ifndef __ARCH_ALPHA_HAL_FALCON_H 
#define __ARCH_ALPHA_HAL_FALCON_H 

/*
 * Definitions for debugging
 */
#define FALCON_MODULE(mod) char *module = mod
#define FALCON_PRINTF(msg) printf(msg, module)
#define FALCON_DPRINTF(msg) if( _titan_developer_debug ) printf(msg, module)


/*
 * 680 Machine Check definitions
 */
#define FALCON_MC_SEL_SHIFT       16 
#define FALCON_MC_SEL_MASK        0xff
#define FALCON_MC_THERMAL_MASK    0xffff
#define FALCON_MC_THERMAL_WARNING 0x0102 
#define FALCON_MC_THERMAL_UNCORRECTABLE 0x70000
#define FALCON_MC_POWER_MASK    0xffff
#define FALCON_MC_POWER_WARNING 0x0202

/*
 * Maximum number of CPUs and PCI busses expected on Falcon
 */
#define FALCON_MAX_CPU   2
#define FALCON_E_MAX_PCI 3
#define FALCON_S_MAX_PCI 4

/*
 * Number of PCI interrupts on Falcon
 */
#define FALCON_NUM_PCI_INTR 54

/*
 * IPMI WDT interval
 */
#define FALCON_WDT_INTERVAL 60

/*
 * TIG CSRs
 * Offset 0x3000.0000 from IO base
 */
#define FALCON_BTINT_MASK    0x1
#define FALCON_TIG_IRQ5M_REG 0x801300004c0UL
#define FALCON_TIG_IRQ5S_REG 0x80130000500UL
#define FALCON_TIG_VDDE_REG  0x80130001000UL
#define FALCON_TIG_VDDS_REG  0x80130001040UL
#define FALCON_TIG_CPUS_REG  0x80130001080UL
struct falcon_tig_regs {
  u_char  trr;          /* offset 0x000 */
  char    pad0[0x3f];
  u_char  tir;          /* offset 0x040 */
  char    pad1[0x3f];
  u_char  ttcr;         /* offset 0x080 */
  char    pad2[0x3f];
  u_char  bkpl;         /* offset 0x0C0 */
  char    pad3[0x3f];
  u_char  m66n;         /* offset 0x100 */
  char    pad4[0x3f];
  u_char  bmcr;         /* offset 0x140 */
  char    pad5[0x3f];
  u_char  fwmr0;        /* offset 0x180 */
  char    pad6[0x3f];
  u_char  fwmr1;        /* offset 0x1C0 */
  char    pad7[0x3f];
  u_char  fwmr2;        /* offset 0x200 */
  char    pad8[0x3f];
  u_char  fwmr3;        /* offset 0x240 */
  char    pad9[0x3f];
  u_char  icr0;         /* offset 0x280 */ 
  char    pad10[0x3f];
  u_char  icr1;         /* offset 0x2C0 */
  char    pad11[0x3f];
  u_char  icr2;         /* offset 0x300 */
  char    pad12[0x3f];
  u_char  icr3;         /* offset 0x340 */
  char    pad13[0x3f];
  u_char  icr4;         /* offset 0x380 */
  char    pad14[0x7f];
  u_char  cir;          /* offset 0x400 */
  char    pad16[0x3f];
  u_char  evir;         /* offset 0x440 */
  char    pad17[0x3f];
  u_char  evhr;         /* offset 0x480 */
  char    pad18[0x3f];
  u_char  irq5m;        /* offset 0x4C0 */
  char    pad19[0x3f];
  u_char  irq5s;        /* offset 0x500 */
  char    pad20[0x3f];
  u_char  btint;        /* offset 0x540 */
  char    pad21[0x2bf];
  u_char  srcr;         /* offset 0x800 */
  char    pad23[0x3f];
  u_char  frar0;        /* offset 0x840 */
  char    pad24[0x3f];
  u_char  frar1;        /* offset 0x880 */
  char    pad25[0x37f];
  u_char  plld0;        /* offset 0xc00 */
  char    pad26[0x3f];
  u_char  plld1;        /* offset 0xc40 */
  char    pad27[0x3bf];
  u_char  vdde;         /* offset 0x1000 */
  char    pad29[0x3f];
  u_char  vdds;         /* offset 0x1040 */
  char    pad30[0x3f];
  u_char  cpus;         /* offset 0x1080 */
  char    pad31[0x3f];
  u_char  pctrl;        /* offset 0x10C0 */
  char    pad32[0x3f];
  u_int   espc;         /* offset 0x1100 */
  char    pad33[0x2ff];
  u_char  tpcr;         /* offset 0x1400 */
  char    pad34[0x3ff];
};

/*
 * Falcon Hot Swap Status packet
 */
#define FALCON_HS_LEN   0x60
#define FALCON_HS_CLASS 12
#define FALCON_HS_TYPE  64
#define FALCON_HS_REV   1
struct el_falcon_hs_pkt {
  struct el_titan_packet_hdr hdr;
  long irq5m;
  long irq5s;
  long hsc_command;
  long presence_detect_bus_1;
  long healthy_bus_1;
  long presence_detect_bus_2;
  long healthy_bus_2;
  long presence_detect_bus_3;
  long healthy_bus_3;
  long enum_reg;
  long diagnostic;
};

/*
 * Falcon-specific IPMI command definitions
 */
#define IPMI_FALCON_PWRDN     0x04
#define IPMI_FALCON_PWRDN_LEN 1
#define IPMI_FALCON_FUN_REQ   0x30
#define IPMI_FALCON_PWR_OFF   0
/*
 * IPMI SEL entries
 */
#define IPMISEL0  0
#define IPMI_SEL0 "Undocumented kernel system panic"
#define IPMISEL1  1
#define IPMI_SEL1 "ialloc: dup alloc"
#define IPMISEL10  10
#define IPMI_SEL10 "atmifmp_packet_get"
#define IPMISEL100  100
#define IPMI_SEL100 "sth_uiomove: mode"
#define IPMISEL101  101
#define IPMI_SEL101 "svckudp_dup: can't malloc"
#define IPMISEL102  102
#define IPMI_SEL102 "svckudp_dupdone"
#define IPMISEL103  103
#define IPMI_SEL103 "tcp_init"
#define IPMISEL104  104
#define IPMI_SEL104 "tcp_input: m changed on tcp_reass"
#define IPMISEL105  105
#define IPMI_SEL105 "tcp_respond"
#define IPMISEL106  106
#define IPMI_SEL106 "tcp_output REXMT"
#define IPMISEL107  107
#define IPMI_SEL107 "tcp_pulloutofband"
#define IPMISEL108  108
#define IPMI_SEL108 "tcp_usrreq"
#define IPMISEL109  109
#define IPMI_SEL109 "tcphdr too big"
#define IPMISEL11  11
#define IPMI_SEL11 "atmifmp_process_packet: hdr won't fit in small mbuf"
#define IPMISEL110  110
#define IPMI_SEL110 "udp_usrreq"
#define IPMISEL111  111
#define IPMI_SEL111 "uipc 1"
#define IPMISEL112  112
#define IPMI_SEL112 "uipc 2"
#define IPMISEL113  113
#define IPMI_SEL113 "uipc 3"
#define IPMISEL114  114
#define IPMI_SEL114 "uipc 4"
#define IPMISEL115  115
#define IPMI_SEL115 "umc_checksum_page: not a umc page\n"
#define IPMISEL116  116
#define IPMI_SEL116 "umc_free_page: not a umc page\n"
#define IPMISEL117  117
#define IPMI_SEL117 "unp_connect2"
#define IPMISEL118  118
#define IPMI_SEL118 "unp_disconnect"
#define IPMISEL119  119
#define IPMI_SEL119 "unp_externalize"
#define IPMISEL12  12
#define IPMI_SEL12 "atmifmp_recive: no packet header"
#define IPMISEL120  120
#define IPMI_SEL120 "vnode already free\n"
#define IPMISEL121  121
#define IPMI_SEL121 "wdir: compact1"
#define IPMISEL122  122
#define IPMI_SEL122 "wdir: compact2"
#define IPMISEL13  13
#define IPMI_SEL13 "atmifmp_pfilt: pfilt ate my packet!"
#define IPMISEL14  14
#define IPMI_SEL14 "ATMSIG: atmsig_process_receive no HDR"
#define IPMISEL15  15
#define IPMI_SEL15 "ATMSIG: Unexpected order supplied to SCatMsg\n"
#define IPMISEL16  16
#define IPMI_SEL16 "ATMUNI: Attempting to deref non-existant ILMI instance"
#define IPMISEL17  17
#define IPMI_SEL17 "ATMUNI: Attempting to deref non-existant Sig instance"
#define IPMISEL18  18
#define IPMI_SEL18 "ATMUNI: could not find UNI during delete\n"
#define IPMISEL19  19
#define IPMI_SEL19 "ATMUNI: Simple locks held when allocating mbuf with wait\n"
#define IPMISEL2  2
#define IPMI_SEL2 "arpintr no HDR"
#define IPMISEL20  20
#define IPMI_SEL20 "atm_arp_receive no HDR"
#define IPMISEL21  21
#define IPMI_SEL21 "atm_cmm_connect"
#define IPMISEL22  22
#define IPMI_SEL22 "atm_cmm_driver_commit"
#define IPMISEL23  23
#define IPMI_SEL23 "atm_cmm_driver_res_free: no cvg to notify"
#define IPMISEL24  24
#define IPMI_SEL24 "atm_cmm_driver_vcmaxbw_init: unable to calculate default vcmaxbw"
#define IPMISEL25  25
#define IPMI_SEL25 "atm_cmm_error"
#define IPMISEL26  26
#define IPMI_SEL26 "atm_cmm_free_resvresource"
#define IPMISEL27  27
#define IPMI_SEL27 "atm_cmm_free_resv_listchk"
#define IPMISEL28  28
#define IPMI_SEL28 "atm_cmm_free_resv_listchk: NOTRESV on RESVREQ list"
#define IPMISEL29  29
#define IPMI_SEL29 "atm_cmm_free_resv_listchk: NOTRESV on RESVUNUSED list"
#define IPMISEL3  3
#define IPMI_SEL3 "atimifp_connect1"
#define IPMISEL30  30
#define IPMI_SEL30 "atm_cmm_free_resv_listchk: RESVALLOC on RESVREQ list"
#define IPMISEL31  31
#define IPMI_SEL31 "atm_cmm_free_resv_listchk: RESVALLOC on RESVUNUSED list"
#define IPMISEL32  32
#define IPMI_SEL32 "atm_cmm_free_resv_listchk: RESVREQ not on RESVREQ list"
#define IPMISEL33  33
#define IPMI_SEL33 "atm_cmm_free_resv_listchk: RESVTIMEO not on RESVUNUSED list"
#define IPMISEL34  34
#define IPMI_SEL34 "atm_cmm_free_resv_listchk: RESVTIMEO on RESVREQ list"
#define IPMISEL35  35
#define IPMI_SEL35 "atm_cmm_free_resv_listchk: RESVUNUSED on RESVREQ list"
#define IPMISEL36  36
#define IPMI_SEL36 "atm_cmm_ioctl: no mmip"
#define IPMISEL37  37
#define IPMI_SEL37 "atm_cmm_list__add: list element already on a list\n"
#define IPMISEL38  38
#define IPMI_SEL38 "atm_cmm_list__insert: list element already on a list\n"
#define IPMISEL39  39
#define IPMI_SEL39 "atm_cmm_remove_vc_resources"
#define IPMISEL4  4
#define IPMI_SEL4 "atimifp_connect2"
#define IPMISEL40  40
#define IPMI_SEL40 "atm_cmm_send: negative packet length"
#define IPMISEL41  41
#define IPMI_SEL41 "bad dir"
#define IPMISEL42  42
#define IPMI_SEL42 "blkfree: freeing free block"
#define IPMISEL43  43
#define IPMI_SEL43 "bufcall_init"
#define IPMISEL44  44
#define IPMI_SEL44 "can't create ATM collector thread\n"
#define IPMISEL45  45
#define IPMI_SEL45 "can't create ATM reservation thread\n"
#define IPMISEL46  46
#define IPMI_SEL46 "csq_cleanup"
#define IPMISEL47  47
#define IPMI_SEL47 "do_bio: write count < 0"
#define IPMISEL48  48
#define IPMI_SEL48 "domain_add max_hdr"
#define IPMISEL49  49
#define IPMI_SEL49 "free vnode isn't"
#define IPMISEL5  5
#define IPMI_SEL5 "ATM clone ESI linked to clone"
#define IPMISEL50  50
#define IPMI_SEL50 "freeing free mblk"
#define IPMISEL51  51
#define IPMI_SEL51 "freeing free mbuf"
#define IPMISEL52  52
#define IPMI_SEL52 "ialloc: dup alloc"
#define IPMISEL53  53
#define IPMI_SEL53 "icmp len"
#define IPMISEL54  54
#define IPMI_SEL54 "icmp_error"
#define IPMISEL55  55
#define IPMI_SEL55 "if_delmulti: ifmulti not found"
#define IPMISEL56  56
#define IPMI_SEL56 "ifree: freeing free inode"
#define IPMISEL57  57
#define IPMI_SEL57 "ILMI: atmilmi3x_process_receive -- no mbuf HDR"
#define IPMISEL58  58
#define IPMI_SEL58 "ILMI: Attempt to terminate with non-empty queue\n"
#define IPMISEL59  59
#define IPMI_SEL59 "in_control"
#define IPMISEL6  6
#define IPMI_SEL6 "ATM: no restart threads created"
#define IPMISEL60  60
#define IPMI_SEL60 "in_pcbfree"
#define IPMISEL61  61
#define IPMI_SEL61 "ipintr no HDR"
#define IPMISEL62  62
#define IPMI_SEL62 "ip_output no HDR"
#define IPMISEL63  63
#define IPMI_SEL63 "ku_recvfrom - empty sockbuf"
#define IPMISEL64  64
#define IPMI_SEL64 "ku_recvfrom - not SO_NAME"
#define IPMISEL65  65
#define IPMI_SEL65 "ku_recvfrom - strange packet type"
#define IPMISEL66  66
#define IPMI_SEL66 "looutput no HDR"
#define IPMISEL67  67
#define IPMI_SEL67 "nfs3_bio: write count < 0"
#define IPMISEL68  68
#define IPMI_SEL68 "m_copym length"
#define IPMISEL69  69
#define IPMI_SEL69 "m_copym offset"
#define IPMISEL7  7
#define IPMI_SEL7 "atmifmp_drv_sendup"
#define IPMISEL70  70
#define IPMI_SEL70 "m_copym sanity"
#define IPMISEL71  71
#define IPMI_SEL71 "netinit"
#define IPMISEL72  72
#define IPMI_SEL72 "nfs3_getapage: fs size < PAGE_SIZE"
#define IPMISEL73  73
#define IPMI_SEL73 "nfs3_putpage: zero size"
#define IPMISEL74  74
#define IPMI_SEL74 "nfs_dgreceive 3"
#define IPMISEL75  75
#define IPMI_SEL75 "nfs_getapage: fs size < PAGE_SIZE"
#define IPMISEL76  76
#define IPMI_SEL76 "nnh_setup:unable to malloc nnhtable"
#define IPMISEL77  77
#define IPMI_SEL77 "no stream head on fifo close\n"
#define IPMISEL78  78
#define IPMI_SEL78 "osr_bgcheck: unexpected osr_flags"
#define IPMISEL79  79
#define IPMI_SEL79 "piusrreq"
#define IPMISEL8  8
#define IPMI_SEL8 "atmifmp_exception: ATM_CME_BIND_DEL"
#define IPMISEL80  80
#define IPMI_SEL80 "Problem pruning optmgmt"
#define IPMISEL81  81
#define IPMI_SEL81 "raw_usrreq"
#define IPMISEL82  82
#define IPMI_SEL82 "receive 1a"
#define IPMISEL83  83
#define IPMI_SEL83 "receive 3"
#define IPMISEL84  84
#define IPMI_SEL84 "receive 3a"
#define IPMISEL85  85
#define IPMI_SEL85 "rfs3_read_free: bad count"
#define IPMISEL86  86
#define IPMI_SEL86 "rfs_dispatch"
#define IPMISEL87  87
#define IPMI_SEL87 "rfs_rdfree: bad count"
#define IPMISEL88  88
#define IPMI_SEL88 "rip_attach"
#define IPMISEL89  89
#define IPMI_SEL89 "route_output"
#define IPMISEL9  9
#define IPMI_SEL9 "atmifmp_new_pvcppa"
#define IPMISEL90  90
#define IPMI_SEL90 "rtable_init: unable to allocate rtable"
#define IPMISEL91  91
#define IPMI_SEL91 "rtfree"
#define IPMISEL92  92
#define IPMI_SEL92 "rtinithead"
#define IPMISEL93  93
#define IPMI_SEL93 "runq_init"
#define IPMISEL94  94
#define IPMI_SEL94 "rw3vp: zero size"
#define IPMISEL95  95
#define IPMI_SEL95 "rwvp: zero size"
#define IPMISEL96  96
#define IPMI_SEL96 "soclose: NOFDREF"
#define IPMISEL97  97
#define IPMI_SEL97 "sofree dq"
#define IPMISEL98  98
#define IPMI_SEL98 "soo_select_dequeue"
#define IPMISEL99  99
#define IPMI_SEL99 "sosend 1"

/*
 * Function prototypes
 */
extern void   falcon_callback(int, int, ulong, ulong);
extern void   falcon_cpu_shutdown(long, long, long, long);

/*
 * Maximum temperature for Falcon system.
 */
#define FALCON_HIGH_TEMP_THRESHOLD 48

#endif __ARCH_ALPHA_HAL_FALCON_H 



