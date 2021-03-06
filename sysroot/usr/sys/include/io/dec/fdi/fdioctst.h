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
 * @(#)$RCSfile: fdioctst.h,v $ $Revision: 1.1.13.2 $ (DEC) $Date: 1994/05/24 22:58:31 $
 */

/************************************************************************
 *
 * Modification history:
 *
 * 12-Aug-91	Roger S. Morris
 *	New file for FDI (Floppy Disk Interconnect) driver.
 *
 ************************************************************************/

/* fdioctst.h */

#ifndef _FDIOCTST_H_
#define _FDIOCTST_H_

enum fd_ioctst_cmd
    {
    WREG,                              /* WRITE DATA TO 82077AA REGISTER     */
				       /*  d1 = register no.                 */
                                       /*  d2 = data to write.               */
    RREG,                              /* READ BYTE FROM 82077AA REGISTER    */
				       /*  d1 = register no.                 */
                                       /*  d2 = data read.                   */
    INIT_DIAG_REPORT,                  /* DIAGNOSTIC REPORT INIT.            */
    DIAG_REPORT,                       /* READ NEXT LONG-WORD OF DIAGNOSTIC  */
                                       /*  REPORT.                           */
                                       /*  d1 = next long of report.         */
                                       /*  d2 = non-zero if read past end.   */
    ZOOM_IN,                           /* Seek in command.                   */
    ZOOM_OUT,                          /* Seek out command.                  */
    ZOOM_INIT,                         /* ZOOM_INIT test routine.            */
    REINIT,                            /* RE-initialize device driver        */
    ALL_INIT,                          /* Initialize everything.             */
    RCHAR,                             /* Read char from phys addr.          */
                                       /*  d1 = physical address.            */
                                       /*  d2 = data returned here.          */
    WCHAR,                             /* Write char to phys addr.           */
                                       /*  d1 = physical address.            */
                                       /*  d2 = data to write.               */
    RLONG,                             /* Read long from phys addr.          */
                                       /*  d1 = physical address.            */
                                       /*  d2 = data returned here.          */
    WLONG,                             /* Write long to phys addr.           */
                                       /*  d1 = physical address.            */
                                       /*  d2 = data to write.               */
    RESET_DIAG_LOG,                    /* Delete all entries in log.         */
    SREG,                              /* OR data to 82077aa reg.            */
    CREG,                              /* AND ~data to 82077aa reg.          */
    INT_ON,
    INT_OFF,
    RVLONG,                            /* Read long from virt addr.          */
    WVLONG,                            /* Write long to virt addr.           */
    RVTBADDR,                          /* Read virt addr of test buffer.     */
    RPTBADDR,                          /* Read phys addr of test buffer.     */

    TLDC,                              /* call tl_do_command.                */
                                       /*  INPUT:                            */
                                       /*   d1 = csize                       */
                                       /*   d2 = rsize                       */
                                       /*   d3 = expect_int      0: no intr  */
                                       /*                        1: intr     */
                                       /*                        2: intr+sis */
                                       /*   buf[0..15] = cdata               */
                                       /*  OUTPUT:                           */
                                       /*   d1 = return val.                 */
                                       /*   buf[0..1] = sis_rb               */
                                       /*   buf[2..15] = rdata               */
    TEST1,
				       /*	case TEST1:                  */
				       /*	    fc_0.r[DAT] = data->d1;  */
				       /*	    wbflush();               */
				       /*	    data->d2 = fc_0.r[MSR];  */
				       /*	    break;                   */

    ST1,                               /* Seek-test 1                        */
                                       /*  INPUT:                            */
                                       /*   d1 = cylinder                    */
                                       /*   d2 = whence                      */
                                       /*  OUTPUT:                           */
                                       /*   d1 = resulting status.           */
    ST2,                               /* Read at psn test                   */
                                       /*  INPUT:                            */
                                       /*   d1 = psn                         */
                                       /*  OUTPUT:                           */
                                       /*   d1 = resulting status.           */
    ST3,                               /* write at psn test.                 */
                                       /*  INPUT:                            */
                                       /*   d1 = psn                         */
                                       /*  OUTPUT:                           */
                                       /*   d1 = resulting status.           */
    ST4                                /* SPARE                              */
    };

struct fd_ioctst_struct
    {
    enum fd_ioctst_cmd cmd;
    unsigned long d1;
    unsigned long d2;
    unsigned long d3;
    unsigned char buf[16];
    };


void do_fdioctst( int minor_num, int flag, struct fd_ioctst_struct* data );

#define FDIOCTST     _IOWR( FDIO_X, 13, struct fd_ioctst_struct )


#endif
