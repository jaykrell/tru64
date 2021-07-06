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
**      mangled_name.h
**
**  ABSTRACT:
**
**	This file contains info necessary for demangling a single name.
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


#ifndef _MANGLED_NAME_H_
#define _MANGLED_NAME_H_

/*
*** 
*** Misc.
***
*/

#define	MLD_ERROR	-1
#define MLD_SOMETHING_RECOGNIZED 1
#define MLD_NOTHING_RECOGNIZED 0


/*
*** 
*** Version.
***
*/

enum MLD_version {
	MLD_PRE_VERSION7,
	MLD_VERSION7
};

/*
*** 
*** Predeclarations
***
*/

struct MLD_complex;
struct MLD_pointer;
struct MLD_reference;
struct MLD_array;
struct MLD_pointer_to_member;
struct MLD_function;
struct MLD_qualification;
struct MLD_type_modifiers;
struct MLD_unmodified_type;
struct MLD_type;
struct MLD_mangled_function_name;
struct MLD_mangled_template_name;
struct MLD_mangled_variable_name;
struct MLD_mangled_name;


/*
*** 
*** Definition of the type structure
***
*/

struct MLD_type {

    /* type modifier list:
       This actually isn't a list anymore...it's really a structure
       with a boolean for each of the type modifiers (const, volatile,
       signed, unsigned, __unaligned). */
    struct MLD_type_modifiers* tm_list;
    
    /* unmodified type:
       This is a pointer to an unmodified type.  An unmodified
       type would be a type (pointer, int, char, pointer to member, etc.)
       that doesn't have type modifiers associated with it. */
    struct MLD_unmodified_type* ut;
    
    /* repeat item:
       This is a pointer to a previous one from this list.
       Its purpose is to support ANSI: Tn, which  is used to repeat the 
       type of parameter "n" ("n" can be a multi-digit number; the first 
       parameter is numbered 1). */
    struct MLD_type* repeat_type;
    int repeat_count;
    int shared_ut;

    /* next:
       This is a pointer to the next type.  For instance, let's say that
       you had the mangled name, "foo__Xiii", then there would be 
       three type structures with the first's next field pointing to the
       second and so on. */
    struct MLD_type* next;
};


/*
*** 
*** Definition of the unmodified type structure
***
*/

/* Type of type:
   This is the kind of type that is stored in the unmodified type structure. */
enum MLD_type_type {
  MLD_NO_TYPE,			/* no type defined yet */
  MLD_BASIC_TYPE,		/* int, float, char, double, void, ... */
  MLD_COMPLEX_TYPE,		/* a named type, like "pointer" below */
  MLD_POINTER_TYPE,		/* a pointer */
  MLD_REFERENCE_TYPE,		/* a reference */
  MLD_ARRAY_TYPE,		/* an array */
  MLD_FUNCTION_TYPE,		/* a function */
  MLD_POINTER_TO_MEMBER_TYPE,	/* a pointer to a member */
  MLD_CONSTANT_TYPE,		/* a constant (used only for templates) */
  MLD_ADDRESS_TYPE,		/* an address (used only for templates) */
  MLD_NONTYPE_TYPE		/* a nontype for templates */
};

struct MLD_constant {
  char* name; /* 1 and 0d0Ep000 respectively in CiL_1_1, CdL_8_0d0Ep000 */
  int basic;  /* integer representing a basic type */
};

struct MLD_unmodified_type {
  int type_of_type; /* see the enumeration above for more info */
  union {
    char* type_name; /* used for ADDRESS_TYPE */
    int basic;       /* integer representing a basic type:  see below */
    struct MLD_qualification* complex; /* used for complex */
    struct MLD_constant* constant;     /* used for constant */
    struct MLD_nontype* nontype;       /* used for nontype */
    struct MLD_address* address;       /* used for address */
    struct MLD_pointer* pointer;       /* used for pointer */
    struct MLD_reference* reference;   /* used for reference */
    struct MLD_array* array;           /* used for array */
    struct MLD_function* function;     /* used for function */
    struct MLD_pointer_to_member* ptr_to_member;
				       /* used for pointer to member */
  } the_type; /* storage for the type in question (determined by "type_of_type" */
  char *shared_id;
};

/*
*** 
*** Definitions for the various "types of types"
***
*/

/* Basic types:
   A basic type is represented as an integer.  This enumeration allows you to
   interpret the basic type integer stored in the unmodified type structure.
   Note that ellipses is one of the basic types. */
enum basic_types {
        MLD_VOID_BASIC_TYPE,		/* void */
        MLD_CHAR_BASIC_TYPE,		/* char */
        MLD_SHORT_BASIC_TYPE,		/* short */
        MLD_INT_BASIC_TYPE,		/* int */
        MLD_LONG_BASIC_TYPE,		/* long */
        MLD_FLOAT_BASIC_TYPE,		/* float */
        MLD_DOUBLE_BASIC_TYPE,		/* double */
        MLD_LONG_DOUBLE_BASIC_TYPE,	/* long double */
        MLD_ELLIPSES_BASIC_TYPE		/* ellipses "..." */
};

struct MLD_nontype {
  int				is_address;
  struct MLD_qualification*	qualifications;
  char				*nontype_name;  /* Z1Z */
  struct MLD_mangled_template_name* nested_args; /* temp1<temp2<...>> */
  struct MLD_unmodified_type* ut; /* Only useful if nested_args. */
};

struct MLD_address {
  struct MLD_qualification*	qualifications;
  char				*type_name;
};

/* Pointer type:
   A pointer type has one argument--the type modified.  The type
   modified can be any of the "types of types" including pointer. */
struct MLD_pointer {
  struct MLD_type*	type_modified;
};

/* Reference type:
   A reference type has one argument--the type modified.  The type
   modified can be any of the "types of types" including reference. */
struct MLD_reference {
  struct MLD_type*	type_modified;
};

/* Array type:
   An array type has two arguments--a dimension represented as an integer and
   a type modified which is similar to the type modified part of pointer */
struct MLD_array {
  int 			dimension;
  struct MLD_type*	type_modified;
  struct MLD_type*	nontype_dim;	/* Can have nontype dimension. */
};


/* Pointer to member type:
   A pointer to member type has two arguments--a list of qualifications
   (see the explanation of the qualifications data structure for more info)
   and a type modified portion which is similar to what's been described above. */
struct MLD_pointer_to_member {
  struct MLD_qualification*	qualifications;
  struct MLD_type*		type_modified;
};

/* Qualification type:
   The term qualification is not a good term for this structure.  This
   structure should actually be called something like, "fully qualified
   class or struct name."  Each of the classes or structures that are
   involved with qualifying the final class or struct name is represented
   as a "complex" (see below).  The next field is a pointer to the next
   qualification.  A full qualification consists of a linked list of
   qualification nodes--the last of which is the actual class or struct
   name. */
struct MLD_qualification {
  struct MLD_complex*		q; /* a qualification is a complex type */
  struct MLD_qualification*	next;
};

/* complex:
   a complex is a single class or structure name.  Since a 
   class or structure can be a template, a complex can also be a template */
struct MLD_complex {
  int mangled_template_name; /* boolean:  1 means it's a mangled template name
				0 means that it's just a structure name. */
  union {
    char*    structure_name; /* actual text representing structure name */
    struct MLD_mangled_template_name* template_name; /* a template structure */
  } name; /* either a structure name or a template name */
};

/* function type:
   A function type has two arguments--a series of arguments and a return type. */
struct MLD_function {
	struct MLD_type*	args;
	struct MLD_type*	return_type;
	struct MLD_type_modifiers* tm_list; /* type modifiers */
        struct MLD_function*	ptr_to_function_type;
        int extern_c;           /* boolean:  1 if extern "C" */
};


/*
*** 
*** Definition of type modifier structure
***
*/

/* The type modifiers structure consists of a set of integers 
   each of which is a boolean for one of the types of type modifiers */
struct MLD_type_modifiers {
	int const_tm;		/* boolean:  1 if const, 0 if not */
	int signed_tm;		/* boolean:  1 if signed, 0 if not */
	int unsigned_tm;	/* boolean:  1 if unsigned, 0 if not */
	int volatile_tm;	/* boolean:  1 if volatile, 0 if not */
	int unaligned_tm;	/* boolean:  1 if __unaligned, 0 if not */
	int restrict_tm;	/* boolean:  1 if restrict, 0 if not */
};


/*
*** 
*** Definition of the mangled function name structure (and other associated structures)
***
*/

enum MLD_function_name_types {
	MLD_NO_FUNCTION_NAME,
	MLD_NORMAL_FUNCTION_NAME,
	MLD_OPERATOR_FUNCTION_NAME,
	MLD_CONSTRUCTOR_FUNCTION_NAME,
	MLD_DESTRUCTOR_FUNCTION_NAME,
	MLD_CONVERSION_OPERATOR_FUNCTION_NAME
};

struct MLD_mangled_function_name {
	enum MLD_function_name_types function_name_type; /* the function name type (see above) */
	union {
		char* identifier; /* the identifier text */
		struct MLD_type* conversion_operator_type; /* a type structure--if a conversion op */
	} id;
	struct MLD_type_modifiers* tm_list; /* type modifiers */
	struct MLD_qualification*	qualifications; /* qualifications, if define within a class */
	struct MLD_type* args; /* arguments of the function */
	struct MLD_type* rtn; /* return type of the function */
};


/*
*** 
*** Definition of the mangled template name structure (and other associated structures)
***
*/

struct MLD_mangled_template_name {
	char* identifier; /* the identifier for the template */
	struct MLD_type* args; /* arguments for the template */
};


/*
*** 
*** Definition of the mangled variable name structure (and other associated structures)
***
*/

struct MLD_mangled_variable_name {
	char* identifier; /* identifier for the variable */
	struct MLD_qualification*	qualifications; /* qualifications, if defined within a class */
};


/*
*** 
*** Definition of the mangled name structure (and other associated structures)
***
*/


enum MLD_mangled_name_types {
	MLD_NO_MANGLED_NAME,
	MLD_FUNCTION_MANGLED_NAME,
	MLD_TEMPLATE_MANGLED_NAME,
	MLD_VARIABLE_MANGLED_NAME,
	MLD_VIRTUAL_TABLE_NAME,   /* uses "info" item in name union, below */
	MLD_PROMOTED_ENTITY_NAME, /* uses function_name and as */
	MLD_RUNTIMETYPE_INFO_NAME,/* uses "info" item in name union, below */
	MLD_INIT_INTERNAL_NAME,	  /* uses "info" item in name union, below */
	MLD_FINI_INTERNAL_NAME	  /* uses "info" item in name union, below */
};

struct MLD_mangled_name {
  enum MLD_mangled_name_types mangled_name_type; /* type from above enum */
  union {
    struct MLD_mangled_function_name* funct_name;
    struct MLD_mangled_template_name* templ_name;
    struct MLD_mangled_variable_name* var_name;
    char* info; /* used for VIRTUAL_TABLE_NAME */
  } name;
};


#ifdef __cplusplus
extern "C" {
#endif
/*
*** 
*** Definition of the mangled name function
***
*/

int /* recognition status */
MLD_parse_mangled_name
    (const char* s,		/* IN:  string to be parsed */
     int start,			/* IN:  index of first unparsed character */
     int* end,			/* OUT: index of last parsed character */
     struct MLD_mangled_name** mn,
				/* OUT: structure containing mangled name */
     char* str_before_name,	/* OUT: string before mangled name */
     char* str_replaced_by_name,/* OUT: string replaced by mangled name */
     char* str_after_name,	/* OUT: string after mangled name */
     int size_of_string);	/* IN:	max size of the strings listed above */

void
MLD_delete_mangled_name(struct MLD_mangled_name* mn);

void
MLD_concat_mangled_name(struct MLD_mangled_name* mn,
                     char* s,
                     int max_s,
                     int flags);

void
MLD_concat_mangled_function_name_identifier
                   (struct MLD_mangled_function_name* mfn,
                    char* s,
                    int max_s,
                    int flags);

void
MLD_concat_mangled_template_name
                   (struct MLD_mangled_template_name* mtn,
                    char* s,
                    int max_s,
                    int flags);

void
MLD_map_nontype(
	 struct MLD_qualification* q, /* IN: NULL, or contain template args. */
	 struct MLD_type* post_args,  /* IN: NULL, or template args. */
	 struct MLD_type** type);     /* IN/OUT: nontype to be mapped */

extern struct MLD_type *_mld_nontype_type;
extern enum MLD_version MLD_mangled_version;
extern int _mld_no_template_details;

#ifdef __cplusplus
}
#endif

#endif /* _MANGLED_NAME_H_ */
/* DON'T ADD ANYTHING AFTER THIS #endif */
