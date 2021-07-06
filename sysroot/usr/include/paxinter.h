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
 * @(#)$RCSfile: paxinter.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1999/01/18 16:46:49 $
 */

#ifndef _PAXINTER_H_
#define _PAXINTER_H_

#include <standards.h>
#include <sys/syslimits.h>

_BEGIN_CPLUSPLUS

/* Values of the link field returned by getHeaderInfo function */

#define DXFILE 0
#define DXDIR  1
#define DXLINK 2


/* Return values from getArchiverFormat function */

#define TAR             1
#define CPIO            2
#define PAX             3
#define XPAX            4    /* extended pax ; Sacalability */
#define CPIOEXTEND      5
#define COMPRESS        6

/* Template of the structure returned by getHeaderInfo function */

typedef struct HeaderInfo{
        char        name[PATH_MAX + 1];  /* Name of the file in the archive */
        int         link;                /* Indicates filetypes of the file
                                          * whether link, directory or reg file
*/
        struct HeaderInfo  *next;
        } Paxinter_HeaderInfo;

/* dxarchiver function prototypes  */

extern int              getArchiverFormat(char *);
extern struct HeaderInfo * getHeaderInfo(char *);

_END_CPLUSPLUS

#endif /* _PAXINTER_H_ */
