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

/************************************************************************/
/*                                                                      */
/* The following declarations define the CONFIGURATION FILE DEFINITION  */
/* TYPES, the CONFIGURATION FILE TABLE STRUCTURES, an the ALIVE DEVICE  */
/* LIST STRUCTURE.                                                      */
/*                                                                      */
/************************************************************************/

#ifndef __DEVICE_TABLE_H__
#define __DEVICE_TABLE_H__

#ifndef __cplusplus

/* The CONFIGURATION FILE device definition types */
#define UNKNOWN        -1
#define BUS             0
#define CONTROLLER      1
#define MASTER          2
#define DISK            3
#define TAPE            4
#define DEVICE          5

/* The CONFIGURATION FILE node definition types */
#define BINODE  0
#define CINODE          1
#define MSINODE         2
#define XMINODE         3

/* The CONFIGURARTION FILE bus definition types */
#define UNIBUS          0

#define MAXDEVICES              400
#define PATHSIZE                255
#define DEVNAMESIZE             20
#define NODISPLAY               0
#define DISPLAY                 1

/* Structure for configuring the NODE information. */
struct config_node {
    char conn_name[16];          /* The connection point name */
    char nodename[16];           /* The associated node name  */
    int nodetype;                /* The associated node type  */
};

/* Structure for configuring the CPU information. */
struct config_cpu {
    long cputype;               /* The type of the system CPU   */
    char *cpuname;              /* The name of the system CPU   */
    long maxusers;              /* Maximum # of users allowed   */
    char bootdev[32];              /* The name of the boot device  */
};

/* Structure for configuring the DEVICE information. */
struct config_device {
    char devname[16];              /* The name of the I/O device   */
    char devstr[32];               /* Generic name of the device   */
    int makedevflag;            /* Make device special file flag*/
                                /* (1-MAKEDEV)  (0-NO MAKEDEV)  */
    int supportedflag;          /* Supported I/O device flag    */
                                /* (1-SUPPORTED) (0-UNSUPPORTED)*/
    char ivectors[96];             /* The interrupt vectors        */
    int flags;                  /* Flags field of I/O device    */
    int devtype;                /* Generic type of I/O device   */
};

/* Structure for defining the configuration file hardware name. */
struct hardware {
        char    typename[32];      /* The hardware device name */
};

/* Structure for defining the FLOATING ADDRESS DEVICES information. */
struct float_devices {
        char    name[16];          /* Floating address device name */
        int     gap;            /* Floating address device gap  */
};

#endif /* __cplusplus */
#endif /* __DEVICE_TABLE_H__ */
