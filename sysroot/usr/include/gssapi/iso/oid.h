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
 * @(#)$RCSfile: oid.h,v $ $Revision: 1.1.2.1 $ (DEC) $Date: 2000/11/15 04:15:56 $
 */
/*============================================================================

(( Copyright (C) 1995-2000 CyberSafe Corporation. All Rights Reserved.

    %full_filespec:     oid.h~3:H:2 %

    Description:    
        This product is licensed. Use of this product is subject to 
        the CyberSafe Corporation Software License Agreement.

        This file contains structure declarations, constant 
        declarations, and function prototypes for the CyberSafe's 
        OID and OID set C library.
============================================================================*/



#ifndef __OID_H__
#define __OID_H__

#include    <gssapi/compat.h>


    /* These structure declarations represent 
        mutable forms of OID and OID sets. */
    
typedef struct _cs_mutable_oid_desc {

    u_32        nElem; 
    u_32 FAR*   elem;

} cs_mutable_oid_desc, 
    FAR* cs_mutable_oid_t;


typedef struct _cs_mutable_oid_set_desc {

    u_32                        nElem;
    cs_mutable_oid_desc FAR*    elem;

} cs_mutable_oid_set_desc, 
    FAR* cs_mutable_oid_set_t;


        /* These types are used as function 
            parameters -- for now -- are are 
            defined in terms of mutable or 
            immutable structure forms. */
        
    typedef cs_mutable_oid_desc cs_oid_desc;
    typedef cs_mutable_oid_t    cs_oid_t;

    typedef cs_mutable_oid_set_desc cs_oid_set_desc;
    typedef cs_mutable_oid_set_t    cs_oid_set_t;




    /* Compare two OIDs.  
        Return 0 if they are not equal.  NULL may be passed as 
        either or both parameters.  Two NULL pointers are equal. */
int CSFAPI
    cs_oid_cmp
        _GSS_PROTO(( CONST cs_oid_t, CONST cs_oid_t ));

    /* Duplicate an OID.
        If a NULL pointer is passed an empty OID is returned. 
        Returns NULL on memory allocation error. */
cs_oid_t CSFAPI
    cs_oid_dup
        _GSS_PROTO(( CONST cs_oid_t ));

    /* Free the OID.
        A NULL pointer may be passed. */
void CSFAPI
    cs_oid_free
        _GSS_PROTO(( cs_oid_t ));



    /* Compare two OID sets.
        The order of the elements is not important.  Duplicate 
        entries in either set may cause an equality although the 
        two sets are not equal.  However, duplicates should not 
        be present in a set. */
int CSFAPI
    cs_oid_set_cmp
        _GSS_PROTO(( CONST cs_oid_set_t, CONST cs_oid_set_t ));

    /* Test for the presence of an OID in a set.
        Return 0 if the OID is not present. */
int CSFAPI
    cs_oid_in_set
        _GSS_PROTO(( CONST cs_oid_t, CONST cs_oid_set_t ));

    /* Union of two sets.
        Return a new set that is the union of two sets. 
        The returned set may be empty. Returns NULL on memory 
        allocation error. */
cs_oid_set_t CSFAPI
    cs_oid_set_union
        _GSS_PROTO(( CONST cs_oid_set_t, CONST cs_oid_set_t ));

    /* Intersection of two sets.
        Return a new set that is the intersection of two sets.  
        The returned set may be empty. Returns NULL on memory 
        allocation error.*/
cs_oid_set_t CSFAPI
    cs_oid_set_isect
        _GSS_PROTO(( CONST cs_oid_set_t, CONST cs_oid_set_t ));

    /* Insert the OID into the set.
        The OID is inserted IF it is not already in the set.  
        If the set doesn't exist (NULL passed for the set) then 
        one is created. Returns NULL on memory allocation
        error. */
cs_oid_set_t CSFAPI
    cs_oid_set_insert
        _GSS_PROTO(( CONST cs_oid_t, cs_oid_set_t ));

    /* Duplicate the set.
        If NULL is passed for the set then an empty set is 
        allocated and returned. Returns NULL on memory
        allocation error.*/
cs_oid_set_t CSFAPI
    cs_oid_set_dup
        _GSS_PROTO(( CONST cs_oid_set_t ));

    /* Free the set. 
        A NULL pointer may be passed. */
void CSFAPI
    cs_oid_set_free
        _GSS_PROTO(( cs_oid_set_t ));



#endif /* __OID_H__ */ 
