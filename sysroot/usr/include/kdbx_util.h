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
 * @(#)$RCSfile: kdbx_util.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/07/09 18:04:27 $
 */

#ifndef __KDBX_UTIL_H_
#define __KDBX_UTIL_H_

/*      util.h (ULTRIX) 12/12/90        */

/************************************************************************
 *                                                                      *
 *                      Copyright (c) 1990 by                           *
 *              Digital Equipment Corporation, Maynard, MA              *
 *                      All rights reserved.                            *
 *                                                                      *
 *   This software is furnished under a license and may be used and     *
 *   copied  only  in accordance with the terms of such license and     *
 *   with the  inclusion  of  the  above  copyright  notice.   This     *
 *   software  or  any  other copies thereof may not be provided or     *
 *   otherwise made available to any other person.  No title to and     *
 *   ownership of the software is hereby transferred.                   *
 *                                                                      *
 *   This software is  derived  from  software  received  from  the     *
 *   University    of   California,   Berkeley,   and   from   Bell     *
 *   Laboratories.  Use, duplication, or disclosure is  subject  to     *
 *   restrictions  under  license  agreements  with  University  of     *
 *   California and with AT&T.                                          *
 *                                                                      *
 *   The information in this software is subject to change  without     *
 *   notice  and should not be construed as a commitment by Digital     *
 *   Equipment Corporation.                                             *
 *                                                                      *
 *   Digital assumes no responsibility for the use  or  reliability     *
 *   of its software on equipment which is not supplied by Digital.     *
 *                                                                      *
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define NEW_TYPE(name, num, type, cast_type, proc)\
  if((name = (cast_type) malloc((size_t) ((num) * sizeof(type)))) == NULL){ \
    fprintf(stderr, "File \"%s\", line %d, procedure \"%s\":\n", __FILE__, \
	    __LINE__, proc); \
    perror(""); \
    exit(1); \
  }

#ifndef True
#ifndef False

typedef enum { False, True } Boolean;

#endif
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#endif
