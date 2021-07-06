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
**++
**  PRODUCT:
***
**	DEC C++ Demangler
**
**  FILE:  
**
**      utilities.h
**
**  ABSTRACT:
**
**	This module contains functions that deallocate storage.
**
**  ENVIRONMENT:
**
**	User Mode
**
**  AUTHORS:
**
**
**  MODIFICATION HISTORY:
**
**
**--
**/


#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#ifdef CXX_NT
#include "mn_nm.h"
#else
#include "mangled_name.h"
#endif

/* 
***
*** General Utility Functions
***
*/
#ifdef __cplusplus
extern "C" {
#endif

void /* substitute string or null, if nothing found */
_basic_operator_substitute(const char* ts,	/* IN:  operator token */
                           char* s,		/* OUT:	operator string */
                           int size_of_s);	/* IN:	max size of s */

int /* recognition status */
_get_class(struct MLD_qualification* q,	/* qualification */
          struct MLD_complex** c); 		/* class */

int /* number of double underscores found */
_num_dbl_uscores(const char* s,	/* IN:  string to be parsed */
		 int start);	/* IN:  index of first unparsed character */

char* /* prepend d to s, put results in s, and return s. */
demangle_string_prepend (char* s, 
			 int max_s, 
			 const char* d);

int /* recognition status */
demangle_unnamed(const char *s, /* IN: string to be parsed */
		 char *string);	/* OUT: of unnamed... */
/* 
***
*** Deletion Utility Functions
***
*/

void
_delete_type_modifier_list(struct MLD_type_modifiers* tml);

struct MLD_type* /* returns the "next" structure */
_delete_type_structure(struct MLD_type* t);

void 
_delete_unmodified_type(struct MLD_unmodified_type* ut);

void
_delete_type_list(struct MLD_type* tl);

void
_delete_mangled_function_name(struct MLD_mangled_function_name* mfn);

void
_delete_mangled_template_name(struct MLD_mangled_template_name* mtn);

void
_delete_mangled_variable_name(struct MLD_mangled_variable_name* mvn);

void
_delete_complex(struct MLD_complex* c);

void
_delete_pointer(struct MLD_pointer* p);

void
_delete_qualifications(struct MLD_qualification* ql);

void
_delete_reference(struct MLD_reference* r);

void
_delete_array(struct MLD_array* a);

void
_delete_pointer_to_member(struct MLD_pointer_to_member* pm);

void
_delete_function(struct MLD_function* f);

void
_delete_address(struct MLD_address* ad);

void
_delete_nontype(struct MLD_nontype* nt);

struct MLD_nontype*
_alloc_nontype();

void
_init_shared_id();

void 
_set_shared_id(struct MLD_unmodified_type *ut);

/* 
***
*** Concatenation Utility Functions
***
*/

char*
_concat(char* s,
 	   int max_s,
  	   const char* d);

void
_concat_type_modifier_list(struct MLD_type_modifiers* tml, 
                          char* s,
                          int max_s, 
                          int flags );
                          
void
_concat_unmodified_type(struct MLD_unmodified_type* ut,
                      char* s,
                      int max_s, 
                      int flags);
                      
struct MLD_type* /* returns the "next" structure */
_concat_type_structure(struct MLD_type* t,
                      char* s,
                      int max_s, 
                      int flags);
                      
void
_concat_type_list(struct MLD_type* tl,
                 char* s,
                 int max_s, 
                 int flags);
                 
void
_concat_mangled_function_name(struct MLD_mangled_function_name* mfn,
                    char* s,
                    int max_s, 
                    int flags);

void
_concat_mangled_variable_name(struct MLD_mangled_variable_name* mvn,
                    char* s,
                    int max_s, 
                    int flags);                    
                    
void
_concat_complex(struct MLD_complex* c,
               char* s,
               int max_s, 
               int flags);

void
_concat_complex_notemplatearg(struct MLD_complex* c,
               char* s,
               int max_s, 
               int flags);

void
_concat_basic(int bt,
               char* s,
               int max_s, 
               int flags);

void
_concat_pointer(struct MLD_pointer* p,
               char* s,
               int max_s, 
               int flags);
               
void
_concat_qualifications(struct MLD_qualification* ql, 
                      char* s,
                      int max_s, 
                      int flags );

void
_concat_reference(struct MLD_reference* r,
                 char* s,
                 int max_s, 
                 int flags);
                 
void
_concat_array(struct MLD_array* a,
             char* s,
             int max_s, 
             int flags);
             
void
_concat_pointer_to_member(struct MLD_pointer_to_member* pm,
                         char* s,
                         int max_s, 
                         int flags);
                         
void
_concat_function(struct MLD_function* f,
                char* s,
                int max_s, 
                int flags);

void
_concat_address(struct MLD_address* ad,
               char* s,
               int max_s, 
               int flags);

int MLD_is_member(struct MLD_mangled_name *mn);

#ifdef __cplusplus
}
#endif

#endif /* _UTILITIES_H_ */
/* DON'T ADD ANYTHING AFTER THIS #endif */
