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
 * @(#)$RCSfile: kdebug.h,v $ $Revision: 1.1.65.2 $ (DEC) $Date: 2001/03/09 01:19:38 $
 */

#ifndef _SYS_KDEBUG_H_
#define _SYS_KDEBUG_H_

#include <sys/types.h>

/*
 * kdebug states
 */
#define	KDEBUG_DISABLED	0x00
#define	KDEBUG_ENABLED	0x01
#define	KDEBUG_BRK	0x02

#define	KDEBUG_MAGIC	0xfeedface

/*
 * request codes for kdebug subsystem entry point
 */
#define	KDEBUG_REQ_INIT		1
#define	KDEBUG_REQ_BRKPT	2
#define	KDEBUG_REQ_MEM		3

typedef struct _KdebugInfo {
    volatile u_long	state;
    u_long		magic;
    u_long		debug;
    u_long		*exc_frame;
    u_int		lock;
    u_int		nofault;
    int			brkpt_ipl;
    int			cpu_num;
} KdebugInfo;

/*
 * debugging flags
 */
#define DBG_GENERAL     0x0001          /* general */
#define DBG_WARNING     0x0002          /* warnings */
#define DBG_ERROR       0x0004          /* errors */
#define DBG_BRKPT       0x0008          /* breakpoint handling code */
#define DBG_MEM         0x0010          /* memory management */
#define DBG_IO          0x0020          /* character i/o */
#define DBG_RDEBUG      0x0040          /* remote debug requests */
#define DBG_PROTO       0x0080          /* remote debug protocol */

/* forward decl for C++ */
#ifdef __cplusplus
struct device_table;
#endif

/*
 * kdebug's cpu data
 */
struct kdebug_cpusw {
    unsigned long	system_type;		/* value for cpu */
    char		*system_string;		/* description of machine */
    struct device_table *tty_dev;		/* 'tty' device table */
    unsigned long	tty_base;		/* base address of tty device */
    void		(*delay)();		/* microsecond delay */
};

extern struct device_table
	kdebug_gbus_dev,
	kdebug_ace_dev,
	kdebug_iscc_dev;

#define ACE_ISA_ADDR		0x2f8
#define GBUS_TLASER_ADDR	(0xfffffc0000000000 | 0xFFA1000000)
#define ISCC_ISA_ADDR		0x6000

char std_in(unsigned long port);
void std_out(unsigned long port, unsigned char data);
char linear_in(unsigned long port);
void linear_out(unsigned long port, unsigned char data);

/*
 * kdebug ace init stuff 
 */
struct kdebug_ace_conf {
  unsigned long 	system_type;		/* value for cpu */
  long                  apc_base;
  int                   shift;
  void	                (*port_write)(u_long, u_char);
  char	                (*port_read)(u_long);
};

/*
 * system identifiers - we use our own rather than the kernel's
 * since kdebug is often supported before the kernel port
 */

#define ST_ADU                   1       	/* Alpha ADU systype	*/
#define ST_DEC_4000              2       	/* Cobra systype	*/
#define ST_DEC_7000              3       	/* Ruby systype		*/
#define ST_DEC_3000_500          4       	/* Flamingo systype	*/
#define ST_JENSEN         	 6       	/* Jensen systype	*/
#define ST_DEC_3000_300          7       	/* Pelican systype	*/
#define ST_SABLE		 9		/* Sable systype	*/
#define ST_DEC_AXPVME_64	10		/* AXPvme system type	*/
#define ST_DEC_AXPPCI_33	11		/* NoName systype	*/
#define ST_DEC_21000		12		/* Turbolaser systype	*/
#define ST_DEC_2100_A50		13		/* Avanti systype	*/
#define ST_DEC_MUSTANG		14		/* Mustang systype	*/
#define ST_DEC_KN20AA		15		/* Alcor systype	*/
#define ST_DEC_1000		17		/* Mikasa systype	*/
#define ST_EB66			19		/* EB66 systype		*/
#define ST_EB64P		20		/* EB64+ systype	*/
#define ST_ALPHABOOK1		21		/* Tadpole ALPHAbook 1	*/
#define ST_DEC_4100		22              /* RAWHIDE systype      */
#define ST_DEC_EV45_PBP		23		/* LEGO K2 PBP systype	*/
#define ST_LYNX			24		/* Lynx systype		*/
#define ST_EB164		26		/* EB164 systype	*/
#define ST_DEC_1000A		27		/* Noritake systype     */
#define ST_DEC_ALPHAVME_224     28              /* Cortex system type   */
#define ST_DEC_550		30		/* Miata		*/
#define ST_DEC_EV56_PBP		32		/* TAKARA PBP systype	*/
#define ST_DEC_ALPHAVME_320     33              /* Yukon system type    */
#define ST_DEC_6600     	34              /* EV6-Typhoon systype	*/
#define ST_ALPHA_WILDFIRE	35              /* Alpha-Wildfire 	*/
#define ST_DMCC_EV6		37              /* Eiger... */
#define ST_ALPHA_TITAN	        38	        /* EV6-Titan systype	*/

/*
 * device table is interface between debugger and device drivers
 */
#ifndef _KERNEL
struct device_table {
    long (*dt_init) __((unsigned long));		/* init */
    unsigned char (*dt_rx_read) __((void));		/* read character */
    long (*dt_tx_write) __((unsigned char));		/* write character */
    long (*dt_rx_rdy) __((void));			/* ready to read */
    long (*dt_tx_rdy) __((void));			/* ready to write */
};
#else
struct device_table {
    long (*dt_init) (unsigned long);		/* init */
    unsigned char (*dt_rx_read) (void);		/* read character */
    long (*dt_tx_write) (unsigned char);	/* write character */
    long (*dt_rx_rdy) (void);			/* ready to read */
    long (*dt_tx_rdy) (void);			/* ready to write */
};
#endif

/*
 * character device buffer and functions
 */
#define	CBUFSIZE	1024

struct device_buf {
	char *db_in;		/* pts at next free char */
	char *db_out;		/* pts at next filled char */
	char db_buf[CBUFSIZE];	/* circular buffer for input */
};

#define	CIRC_EMPTY(x)	((x)->db_in == (x)->db_out)
#define	CIRC_FLUSH(x)	((x)->db_in = (x)->db_out = (x)->db_buf)

/*
 * these are the dbx register indices
 */
#define	R_R0		0
#define	R_R1		1
#define	R_R2		2
#define	R_R3		3
#define	R_R4		4
#define	R_R5		5
#define	R_R6		6
#define	R_R7		7
#define	R_R8		8
#define	R_R9		9
#define	R_R10		10
#define	R_R11		11
#define	R_R12		12
#define	R_R13		13
#define	R_R14		14
#define	R_R15		15
#define	R_R16		16
#define	R_R17		17
#define	R_R18		18
#define	R_R19		19
#define	R_R20		20
#define	R_R21		21
#define	R_R22		22
#define	R_R23		23
#define	R_R24		24
#define	R_R25		25
#define	R_R26		26
#define	R_R27		27
#define	R_R28		28
#define	R_R29		29
#define	R_R30		30
#define	R_R31		31
#define	R_F0		32
#define	R_F1		33
#define	R_F2		34
#define	R_F3		35
#define	R_F4		36
#define	R_F5		37
#define	R_F6		38
#define	R_F7		39
#define	R_F8		40
#define	R_F9		41
#define	R_F10		42
#define	R_F11		43
#define	R_F12		44
#define	R_F13		45
#define	R_F14		46
#define	R_F15		47
#define	R_F16		48
#define	R_F17		49
#define	R_F18		50
#define	R_F19		51
#define	R_F20		52
#define	R_F21		53
#define	R_F22		54
#define	R_F23		55
#define	R_F24		56
#define	R_F25		57
#define	R_F26		58
#define	R_F27		59
#define	R_F28		60
#define	R_F29		61
#define	R_F30		62
#define	R_F31		63
#define	R_EPC		64
#define	R_PS		65
#define	R_SR		70
#define	NREGS		71

/*
 * max packet size in longwords between dbx and kdebug
 */
#define	MAXPACKET	1024

/*
 * Ascii characters that are special to protocol
 */
#define	SYN		0x16
#define	DLE		0x10

#define	REXMIT_TIME	100000

/*
 * remote debugging packet identifiers
 */
#define P_REG_READ	'r'			/* read registers */
#define P_REG_WRITE	'R'			/* write registers */
#define P_DATA_READ	'd'			/* read data */
#define P_DATA_WRITE	'D'			/* write data */
#define P_THREAD_CNT	't'			/* get the number of threads */
#define P_THREAD_LIST	'T'			/* get the list of threads */
#define P_SET_PID	'p'			/* set the pid */
#define P_CONT		'c'			/* continue the child */
#define P_STEP		's'			/* single step the child */
#define P_EXIT		'x'			/* exit kdebug */
#define P_ACK		'*'			/* ack */
#define P_ERROR		'e'			/* error */
#define P_INIT		'b'			/* init */

#ifdef _KERNEL
/*
 * Function prototypes for functions shared across kdebug's files, and
 * for those which interface with the kernel.
 */
/* From kdebug_brkpt.c */
void install_brkpts(void);
void remove_brkpts(void);
void kdebug_step(void);

/* From kdebug_conf.c */
struct kdebug_cpusw *kdebug_cpuswitch_entry(unsigned long);

/* From kdebug_io.c */
long init_saio(void);
char kdebug_getc(void);
char kdebug_nblock_getc(long *);
void kdebug_putc(char);
void kprintf(unsigned long, char *, ...);

/* From kdebug_kern.c */
u_long *kdebug_serialize(u_long, u_long, u_long, u_long, u_long *);
u_long *kdebug_if_trap(void);
void kdebug_deserialize(void);
void kdebug_mm_trap(u_long, u_long, u_long, u_long, u_long *);
int kdebug_bootstrap(int, char **, int, caddr_t);
unsigned long kdebug_state(void);
void kdebug_wait(void);

/* From kdebug_main.c */
u_long *kdebug_entry(long, int, char **);
void kdebug_quit(void);
unsigned long kdebug_bcopy_fault(void *, void *, long);

/* From kdebug_proto.c */
char getpkt(unsigned long *, unsigned long);
void putpkt(char, unsigned long *, unsigned long);

/* From locore.s */
void kdebug_install_handler(void(*)(u_long, u_long, u_long), int);
void kdebug_halt(void);
void enter_kdebug(void); /* was also known as gimmeabreak() */

/* From fastcopy.s */
unsigned long kdebug_bcopy(void *, void *, long);

/* From nofault.s */
long kdebug_error(void);

/* From pal_lib.s */
long kdebug_cobra_tt(long, long, unsigned char);

/* From spl.s */
int kdebug_ipl(int);

extern unsigned long kdebug_state(void);

#endif /* _KERNEL */

#endif /*_SYS_KDEBUG_H_ */
