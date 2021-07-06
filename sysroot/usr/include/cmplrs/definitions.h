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
**      definitions.c
**
**  ABSTRACT:
**
**	Header file containing definitions for tokens used in mangling.
**
**  ENVIRONMENT:
**
**	User Mode
**
**  AUTHORS:
**
**  MODIFICATION HISTORY:
**
**
**--
**/


#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define VERSION7	"__7"
#define VERSION_STRING_LENGTH 3
/* 
***
*** tokens for basic types 
***
*/

/* Total entries in BASIC_TYPE_TOKENS */
#define	NUMBER_OF_BASIC_TYPES 20

/* Index of EXPANDED_TOKEN 'j' */
#define	EXPANDED_BASIC1_TYPE 12

/* Index of SPECIAL_INT_TOKEN 'i' */
#define	EXPANDED_BASIC2_TYPE 16

#define	VOID_TOKEN		'v'
#define	CHAR_TOKEN		'c'
#define	SHORT_TOKEN		's'
#define	INT_TOKEN		'i'
#define	LONG_TOKEN		'l'
#define	FLOAT_TOKEN		'f'
#define	DOUBLE_TOKEN		'd'
#define	LONG_DOUBLE_TOKEN	'r'
#define	ELLIPSES_TOKEN		'e'
#define	LONG_LONG_TOKEN		'L'
#define	UNNAMED_ENUM_TOKEN	'E'
#define EXPANDED_TOKEN		'j'
#define	WCHAR_T_TOKEN		'w'
#define	BOOL_TOKEN		'b'
#define	LONG_DOUBLE128_TOKEN	'r'
#define	SPECIAL_INT_TOKEN	'i'
#define	INT8_TOKEN		'3'
#define	INT16_TOKEN		'4'
#define	INT32_TOKEN		'5'
#define	INT64_TOKEN		'6'

/* Index of string TOKEN, needed for strncmp */
#define EXPANDED_BASIC3_SIZE 3
#define	NUMBER_OF_BASIC3_TYPES 2

#define NONTYPE1_TEMPLATE_TOKEN	"Z1Z"
#define NONTYPE2_TEMPLATE_TOKEN "Z2Z"
#define NONTYPE_TEMPLATE_TOKEN	'Z'

#define BASIC_TYPE_TOKENS \
	{VOID_TOKEN, CHAR_TOKEN, SHORT_TOKEN, INT_TOKEN, LONG_TOKEN,  \
	 FLOAT_TOKEN, DOUBLE_TOKEN, LONG_DOUBLE_TOKEN, ELLIPSES_TOKEN,\
	 LONG_LONG_TOKEN, UNNAMED_ENUM_TOKEN,			      \
	 EXPANDED_TOKEN,					      \
	   WCHAR_T_TOKEN, BOOL_TOKEN, LONG_DOUBLE128_TOKEN,	      \
	 SPECIAL_INT_TOKEN,					      \
	   INT8_TOKEN, INT16_TOKEN, INT32_TOKEN, INT64_TOKEN}

#define BASIC3_TYPE_TOKENS \
	{NONTYPE1_TEMPLATE_TOKEN, NONTYPE2_TEMPLATE_TOKEN}


/* 
***
*** strings for basic types 
***
*/

#define	VOID_STRING		"void"
#define	CHAR_STRING		"char"
#define	SHORT_STRING		"short"
#define	INT_STRING		"int"
#define	LONG_STRING		"long"
#define	FLOAT_STRING		"float"
#define	DOUBLE_STRING		"double"
#define	LONG_DOUBLE_STRING	"long double64"
#define	ELLIPSES_STRING		"..."
#define	WCHAR_T_STRING		"wchar_t"
#define	BOOL_STRING		"bool"
#define	LONG_LONG_STRING	"long long"
#define	UNNAMED_ENUM_STRING	"unnamed enum"
#define SECONDARY_STRING        "error"
#define NEXT_SECONDARY_STRING   "error"
#define INT8_STRING		"__int8"
#define INT16_STRING		"__int16"
#define INT32_STRING		"__int32"
#define INT64_STRING		"__int64"
#define	LONG_DOUBLE128_STRING	"long double128"
#define NONTYPE_TEMPLATE_STRING "nontype"

#define BASIC_TYPE_STRINGS \
	{VOID_STRING, CHAR_STRING, SHORT_STRING, INT_STRING, LONG_STRING, \
	 FLOAT_STRING, DOUBLE_STRING, LONG_DOUBLE_STRING, ELLIPSES_STRING,\
	 LONG_LONG_STRING, UNNAMED_ENUM_STRING,				  \
	 SECONDARY_STRING,						  \
	   WCHAR_T_STRING, BOOL_STRING, LONG_DOUBLE128_STRING,		  \
	 NEXT_SECONDARY_STRING,						  \
	   INT8_STRING, INT16_STRING, INT32_STRING, INT64_STRING,	  \
	 NONTYPE_TEMPLATE_STRING, NONTYPE_TEMPLATE_STRING}


/* 
***
*** Token indicating that something is qualified 
***
*/

#define	QUALIFIED_TOKEN	'Q'


/* 
***
*** Token used to represent template
***
*/

#define	TEMPLATE_TOKEN	'T'

/* 
***
*** Token used to represent special
***
*/

#define	SPECIAL_TOKEN	'S'

/* 
***
*** Token used to represent level
***
*/

#define	LEVEL_TOKEN	'L'

/* 
***
*** Token for type modifiers 
***
*/

#define	NUMBER_OF_TYPE_MODIFIERS 6

#define	CONST_TOKEN	'C'
#define	SIGNED_TOKEN	'S'
#define	UNSIGNED_TOKEN	'U'
#define	VOLATILE_TOKEN	'V'
#define	UNALIGNED_TOKEN	'b'

/* Will follow an EXPANDED TOKEN */
#define RESTRICT_TOKEN  'l'

#define TYPE_MODIFIER_TOKENS \
		{	UNSIGNED_TOKEN, CONST_TOKEN, VOLATILE_TOKEN, \
			SIGNED_TOKEN, UNALIGNED_TOKEN, RESTRICT_TOKEN }


/* 
***
*** Strings for type modifiers 
***
*/

#define	UNSIGNED_STRING	 "unsigned"
#define	CONST_STRING	 "const"
#define	VOLATILE_STRING	 "volatile"
#define	SIGNED_STRING	 "signed"
#define	UNALIGNED_STRING "__unaligned"
#define	RESTRICT_STRING  "restrict"

#define TYPE_MODIFIER_STRINGS \
		{	UNSIGNED_STRING, CONST_STRING, VOLATILE_STRING, \
			SIGNED_STRING, UNALIGNED_STRING, RESTRICT_STRING }


/* 
***
*** Tokens for type declarators 
***
*/

#define	POINTER_TOKEN			'P'
#define	REFERENCE_TOKEN			'R'
#define	ARRAY_TOKEN			'A'
#define	FUNCTION_TOKEN			'X'
#define	ANSI_FUNCTION_TOKEN		'F'
#define	POINTER_TO_MEMBER_TOKEN		'M'
#define UNNAMED_ENUM_TOKEN		'E'

/* 
***
*** Strings for type declarators 
***
*/

#define	POINTER_STRING			"*"
#define	REFERENCE_STRING		"&"
#define	ARRAY_STRING			"[]"
#define	FUNTION_STRING			"()"
#define	POINTER_TO_STRING		"::*"
#define UNNAMED_ENUM_STRING		"unnamed enum"

/* 
***
*** Tokens (in string form as opposed to character form) and strings 
*** for basic operator functions
***
*/
	 
#define NUMBER_OF_BASIC_OPERATORS 43
#define BASIC_OPERATOR_TOKEN 0
#define BASIC_OPERATOR_STRING 1

#define BASIC_OPERATORS {					\
	{/*  1 */ "__ml"	,	"*"		},	\
	{/*  2 */ "__dv"	,	"/"		},	\
	{/*  3 */ "__md"	,	"%"		},	\
	{/*  4 */ "__pl"	,	"+"		},	\
	{/*  5 */ "__mi"	,	"-"		},	\
	{/*  6 */ "__ls"	,	"<<"		},	\
	{/*  7 */ "__rs"	,	">>"		},	\
	{/*  8 */ "__eq"	,	"=="		},	\
	{/*  9 */ "__ne"	,	"!="		},	\
	{/* 10 */ "__lt"	,	"<"		},	\
	{/* 11 */ "__gt"	,	">"		},	\
	{/* 12 */ "__le"	,	"<="		},	\
	{/* 13 */ "__ge"	,	">="		},	\
	{/* 14 */ "__ad"	,	"&"		},	\
	{/* 15 */ "__or"	,	"|"		},	\
	{/* 16 */ "__er"	,	"^"		},	\
	{/* 17 */ "__aa"	,	"&&"		},	\
	{/* 18 */ "__oo"	,	"||"		},	\
	{/* 19 */ "__nt"	,	"!"		},	\
	{/* 20 */ "__co"	,	"~"		},	\
	{/* 21 */ "__pp"	,	"++"		},	\
	{/* 22 */ "__mm"	,	"--"		},	\
	{/* 23 */ "__as"	,	"="		},	\
	{/* 24 */ "__rf"	,	"->"		},	\
	{/* 25 */ "__apl"	,	"+="		},	\
	{/* 26 */ "__ami"	,	"-="		},	\
	{/* 27 */ "__amu"	,	"*="		},	\
	{/* 28 */ "__adv"	,	"/="		},	\
	{/* 29 */ "__amd"	,	"%="		},	\
	{/* 30 */ "__als"	,	"<<="		},	\
	{/* 31 */ "__ars"	,	">>="		},	\
	{/* 32 */ "__aad"	,	"&="		},	\
	{/* 33 */ "__aor"	,	"|="		},	\
	{/* 34 */ "__aer"	,	"^="		},	\
	{/* 35 */ "__cm"	,	","		},	\
	{/* 36 */ "__rm"	,	"->*"		},	\
	{/* 37 */ "__cl"	,	"()"		},	\
	{/* 38 */ "__vc"	,	"[]"		},	\
	{/* 39 */ "__nw"	,	"new"		},	\
	{/* 40 */ "__nwa"	,	"new[]"		},	\
	{/* 41 */ "__dl"	,	"delete"	},	\
	{/* 42 */ "__dla"	,	"delete[]"	},	\
	{/* 43 */ "__stdnw"	,	"new"		}}

/* 
***
*** Tokens for operator functions (in string form)
***
*/

#define	FUNCTION_CALL_TOKEN		"__cl"
#define	SUBSCRIPTING_TOKEN		"__vc"

#define	CONSTRUCTOR_TOKEN		"__ct"
#define	DESTRUCTOR_TOKEN		"__dt"

#define	OPERATOR_NEW_TOKEN		"__nw"
#define	OPERATOR_DELETE_TOKEN		"__dl"

#define	OPERATOR_NEW_ARRAY_TOKEN	"__nwa"
#define	OPERATOR_DELETE_ARRAY_TOKEN	"__dla"

#define	OPERATOR_CONVERSION_TOKEN	"__op"
#define	RUNTIME_TYPE_INFO_TOKEN		"__T_"

/* 
***
*** Strings for operator functions
***
*/

#define	FUNCTION_CALL_STRING		"()"
#define	SUBSCRIPTING_STRING		"[]"
#define	CONSTRUCTOR_STRING		""
#define	DESTRUCTOR_STRING		"~"
#define	OPERATOR_NEW_STRING		""
#define	OPERATOR_DELETE_STRING		""
#define	OPERATOR_CONVERSION_STRING	""
#define	RUNTIME_TYPE_INFO_STRING	""


/* 
***
*** Tokens for shortening the encoding of types
***
*/

#define	NTH_TYPE_TOKEN					'T'
#define	NEXT_N_TYPES_ARE_SAME_AS_NTH_TYPE_TOKEN		'N'

/* 
***
*** Tokens for unnamed ...
***
*/

#define UNNAMED_NAMESPACE_TOKEN		"__N"
#define UNNAMED_CLASS_TOKEN		"__C"
#define UNNAMED_ENUM_TOKEN2		"__E"
#define UNNAMED_MEMBER_VARIABLE_TOKEN	"__V"

#define UNNAMED_NAMESPACE_STRING	"<unnamed namespace>"
#define UNNAMED_CLASS_STRING		"<unnamed class>"
#define UNNAMED_ENUM_STRING2		"unnamed enum"
#define UNNAMED_MEMBER_VARIABLE_STRING	"<unnamed member variable>"

#define UNNAMED_TOKEN_LEN		3
#define NUMBER_OF_UNNAMED_TOKENS	4
#define UNNAMED_TOKENS						\
        { UNNAMED_NAMESPACE_TOKEN, UNNAMED_CLASS_TOKEN,		\
	  UNNAMED_ENUM_TOKEN2, UNNAMED_MEMBER_VARIABLE_TOKEN }
#define UNNAMED_STRINGS						\
	{ UNNAMED_NAMESPACE_STRING, UNNAMED_CLASS_STRING,	\
	  UNNAMED_ENUM_STRING2, UNNAMED_MEMBER_VARIABLE_STRING }

#endif /* _DEFINITIONS_H_ */
/* DON'T ADD ANYTHING AFTER THIS #endif */
