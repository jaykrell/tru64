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
 * @(#)$RCSfile: guids.h,v $ $Revision: 1.1.2.9 $ (DEC) $Date: 2001/11/02 21:47:45 $
 */
/*-----------------------------------------------------------------------
 * File: GUIDS.H
 *
 * Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
 *-----------------------------------------------------------------------
 */

/*--------------------------------------*
 * GUIDS.h                              *
 *   guids for Intel Addins to CSSM	    *
 * Generated: 10/1/96, Apr 7 1997	    *
 * updates for 2.0 on 3 Feb 1998        *
 * updates for 3.0 on 28 July 1999      *
 * updates for 3.1 on 12 June 2000      *
 *--------------------------------------*/

#ifndef _GUIDS_H
#define _GUIDS_H

#ifdef __digital__
#include <cdsa/compaq/guids.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
 * All GUID values are defined as follows. The sample name used in the
 * examples is "my_module_guid".
 *
 * 1) A variable initializer string for type CSSM_GUID is defined with the
 *    target name with "_init" appended. (i.e. my_module_guid_init). It is
 *    used to initialize individual instances of a variable. For instance,
 *    to declare a CSSM_GUID variable with the my_module_guid value you
 *    would use the following code:
 *
 *       CSSM_GUID TempGuid = my_module_guid_init;
 *
 * 2) The macro _CSSM_DEFINE_GUID (defined below) is used to declare a
 *    variable instance with the value of the corresponding initializer.
 *
 *       _CSSM_DEFINE_GUID( my_module_guid, my_module_guid_init );
 *
 *    If the value CSSM_INITGUID is defined, then the macro will expand to
 *    produce a global constant variable with the appropriate value. If
 *    CSSM_INITGUID is not defined, then the macro expands to an external
 *    declaration of a global constant.
 *
 *    For instance, if a source file needs the  global constants to be
 *    defined, the following code is used:
 *
 *       #define CSSM_INITGUID
 *       #include "intel/guids.h"
 *
 *    If only external references are required, just include the header
 *    normally.
 *
 *    NOTE: ALL STATIC LIBRARIES SHOULD AVOID DECLARING CSSM_INITGUID. THIS
 *    WILL CAUSE A LINKER COLLISION IF ANOTHER STATIC LIBRARY OR THE
 *    EXECUTABLE ITSELF DEFINES CSSM_INITGUID.
 *
 *    NOTE: ONLY ONE SOURCE FILE IN AN EXECUTABLE SHOULD DEFINE
 *    CSSM_INITGUID.
 *
 * NOTE: The preferred method of using the GUID values in this file is to
 * use the initializer values described in (1) above. It allows the finest
 * control over the set of constants instantiated in your executable.
 **************************************************************************
 */
#ifndef CSSM_INITGUID
#define _CSSM_DEFINE_GUID(name, value) \
	extern CSSM_GUID name
#else
#define _CSSM_DEFINE_GUID(name, value) \
	CSSM_GUID name = value
#endif /* CSSM_INITGUID */

/****************************************************************************/
/*************************   CURRENT GUIDS    *******************************/
/****************************************************************************/
/* Version independant references to global CSSM_GUID constants */
#define intel_cssm_guid                 intel_cssm_guid_3_0_0
#define intel_csm_guid                  intel_csm_guid_3_0_0
#define intel_rsa_csm_guid              intel_csm_guid_3_0_0_r
#define intel_x509v3_clm_guid           intel_x509v3_clm_guid_3_0_0
#define intel_clm_guid_current          intel_x509v3_clm_guid_3_0_0
#define intel_odbc_dsm_guid             intel_odbc_dsm_guid_3_0_0
#define intel_ldap_dsm_guid             intel_ldap_dsm_guid_3_0_0
#define intel_ff_dsm_guid               intel_ff_dsm_guid_3_0_0
#define intel_tpm_guid                  intel_tpm_guid_3_0_0
#define intel_dummy_guid                intel_dummy_guid_3_0_0
#define intel_dummy_multi_guid          intel_dummy_multi_guid_3_0_0
#define intel_mds_guid                  intel_module_directory_service_3_0_0
#define intel_stub_csp_guid             intel_stub_csp_guid_3_0_0
#define intel_bsafecsp_guid				intel_bsafecsp_guid_3_0_0
#define intel_bsafeexp_guid				intel_bsafeexp_guid_3_0_0
#define intel_spki_clm_guid				intel_spki_clm_guid_3_0_0
#define intel_dummy_emm_guid            intel_dummy_emm_guid_3_0_0
#define intel_dummy_emmaddin_guid       intel_dummy_emm_addin_guid_3_0_0
#define intel_hrs_emm_guid              intel_hrs_emm_guid_1_0_0
#define intel_dummy_hrs_addin_guid      intel_dummy_hrs_addin_guid_1_0_0
#define intel_dummy_test_emm_guid       intel_dummy_test_emm_guid_3_0_0
#define intel_dummy_test_emmaddin_guid  intel_dummy_test_emm_addin_guid_3_0_0
#define intel_acm_guid                  intel_acm_guid_3_0_0
#define intel_eaycsp_guid               intel_eaycsp_guid_3_0_0
#define intel_hrs_pwbsp_guid            intel_hrs_pwbsp_guid_1_0_0

/* Version independant references to CSSM_GUID initializer values */
#define intel_cssm_guid_init            intel_cssm_guid_3_0_0_init
#define intel_csm_guid_init             intel_csm_guid_3_0_0_init
#define intel_rsa_csm_guid_init         intel_csm_guid_3_0_0_r_init
#define intel_x509v3_clm_guid_init      intel_x509v3_clm_guid_3_0_0_init
#define intel_clm_guid_current_init     intel_x509v3_clm_guid_3_0_0_init
#define intel_odbc_dsm_guid_init        intel_odbc_dsm_guid_3_0_0_init
#define intel_ldap_dsm_guid_init        intel_ldap_dsm_guid_3_0_0_init
#define intel_ff_dsm_guid_init          intel_ff_dsm_guid_3_0_0_init
#define intel_tpm_guid_init             intel_tpm_guid_3_0_0_init
#define intel_dummy_guid_init           intel_dummy_guid_3_0_0_init
#define intel_dummy_multi_guid_init     intel_dummy_multi_guid_3_0_0_init
#define intel_mds_guid_init             intel_module_directory_service_3_0_0_init
#define intel_stub_csp_guid_init        intel_stub_csp_guid_3_0_0_init
#define intel_bsafecsp_guid_init		intel_bsafecsp_guid_3_0_0_init
#define intel_bsafeexp_guid_init		intel_bsafeexp_guid_3_0_0_init
#define intel_spki_clm_guid_init		intel_spki_clm_guid_3_0_0_init
#define intel_dummy_emm_guid_init       intel_dummy_emm_guid_3_0_0_init
#define intel_dummy_emm_addin_guid_init intel_dummy_emm_addin_guid_3_0_0_init
#define intel_hrs_emm_guid_init         intel_hrs_emm_guid_1_0_0_init
#define intel_dummy_hrs_addin_guid_init intel_dummy_hrs_addin_guid_1_0_0_init
#define intel_dummy_test_emm_guid_init  intel_dummy_test_emm_guid_3_0_0_init
#define intel_dummy_test_emm_addin_guid_init intel_dummy_test_emm_addin_guid_3_0_0_init
#define intel_acm_guid_init             intel_acm_guid_3_0_0_init
#define intel_eaycsp_guid_init          intel_eaycsp_guid_3_0_0_init
#define intel_hrs_pwbsp_guid_init       intel_hrs_pwbsp_guid_1_0_0_init

/* ----- Core CSSM ----- */
#ifdef __digital__
#define intel_cssm_guid_3_0_0_init compaq_cssm_guid_init
#else
/* release 3.0 Intel CSSM: */
/* {A94AE240-4538-11d3-A8F3-0090271D266F} */
#define intel_cssm_guid_3_0_0_init \
	{ 0xa94ae240, 0x4538, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
#endif
_CSSM_DEFINE_GUID( intel_cssm_guid_3_0_0, intel_cssm_guid_3_0_0_init );
/* CSSM major/minor version is defined in file cssm.h, not here. */

/* ----- CSP ----- */
/* release 3.0 Web CSP */
/* {27BEEA70-4537-11d3-A8F3-0090271D266F} */
#define intel_csm_guid_3_0_0_init \
	{ 0x27beea70, 0x4537, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_csm_guid_3_0_0, intel_csm_guid_3_0_0_init );
#define INTEL_CSM_MAJOR_VER	(3)
#define INTEL_CSM_MINOR_VER	(0)


/* release 3.0 CSP with RSA algids */
/* {328BFDA0-453D-11d3-A8F3-0090271D266F} */
#define intel_csm_guid_3_0_0_r_init \
	{ 0x328bfda0, 0x453d, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_csm_guid_3_0_0_r, intel_csm_guid_3_0_0_r_init );
#define INCSM_R_MAJOR_VER (3)
#define INCSM_R_MINOR_VER (0)


#ifdef __digital__
#define intel_bsafecsp_guid_3_0_0_init compaq_t64csp_guid_init
#else
/* {A79E2610-453D-11d3-A8F3-0090271D266F} */
#define intel_bsafecsp_guid_3_0_0_init \
	{ 0xa79e2610, 0x453d, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
#endif
_CSSM_DEFINE_GUID( intel_bsafecsp_guid_3_0_0, intel_bsafecsp_guid_3_0_0_init );
#define BSCSP_VERMAJOR (3)
#define BSCSP_VERMINOR (0)


/* {16EDB690-453E-11d3-A8F3-0090271D266F} */
#define intel_bsafeexp_guid_3_0_0_init \
	{ 0x16edb690, 0x453e, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_bsafeexp_guid_3_0_0, intel_bsafeexp_guid_3_0_0_init );


/* ----- Intel X509v3 CL ----- */
/* release 3.0 x509CL */
/* {5CF39320-453E-11d3-A8F3-0090271D266F} */
#define intel_x509v3_clm_guid_3_0_0_init \
	{ 0x5cf39320, 0x453e, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_x509v3_clm_guid_3_0_0, intel_x509v3_clm_guid_3_0_0_init );
#define INTEL_X509V3_CLM_MAJOR_VER	(3)
#define INTEL_X509V3_CLM_MINOR_VER	(1)


/* ----- Intel ACM ----- */
/* release 3.0 AC */
/* {C519F4A7-2526-11d4-BA93-0004AC2E8890}*/
#define intel_acm_guid_3_0_0_init \
{ 0xc519f4a7, 0x2526, 0x11d4, { 0xba, 0x93, 0x0, 0x4, 0xac, 0x2e, 0x88, 0x90 } }
_CSSM_DEFINE_GUID( intel_acm_guid_3_0_0, intel_acm_guid_3_0_0_init );
#define INTEL_ACM_MAJOR_VER	(3)
#define INTEL_ACM_MINOR_VER	(1)


/* ----- Intel SPKI CLM ----- */
/* release 3.0 SPKI CL TP */
/* {B7B65D90-4541-11d3-A8F3-0090271D266F} */
#define intel_spki_clm_guid_3_0_0_init \
	{ 0xb7b65d90, 0x4541, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_spki_clm_guid_3_0_0, intel_spki_clm_guid_3_0_0_init );
#define INTEL_SPKI_CLM_MAJOR_VER	(3)
#define INTEL_SPKI_CLM_MINOR_VER	(1)


/* ----- ODBC DL ----- */
/* release 3.0 ODBC_DL */
/* {8FE73BA0-453E-11d3-A8F3-0090271D266F} */
#define intel_odbc_dsm_guid_3_0_0_init \
	{ 0x8fe73ba0, 0x453e, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_odbc_dsm_guid_3_0_0, intel_odbc_dsm_guid_3_0_0_init );
#define INTEL_ODBC_DSM_MAJOR_VER	(3)
#define INTEL_ODBC_DSM_MINOR_VER	(0)


/* -- LDAP DL-- */
/* release 3.0 LDAP_DL */
/* {B7807D80-453E-11d3-A8F3-0090271D266F} */
#define intel_ldap_dsm_guid_3_0_0_init \
	{ 0xb7807d80, 0x453e, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_ldap_dsm_guid_3_0_0, intel_ldap_dsm_guid_3_0_0_init );
#define INTEL_LDAP_DSM_MAJOR_VER	(3)
#define INTEL_LDAP_DSM_MINOR_VER	(0)


/* -- Flat File DL -- */
/* release 3.0 FF_DL */
/* {E5B6DB20-453E-11d3-A8F3-0090271D266F} */
#define intel_ff_dsm_guid_3_0_0_init \
	{ 0xe5b6db20, 0x453e, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_ff_dsm_guid_3_0_0, intel_ff_dsm_guid_3_0_0_init );
#define INTEL_FF_DSM_MAJOR_VER	(3)
#define INTEL_FF_DSM_MINOR_VER	(1)


/* -- Module Directory Service -- */
#ifdef __digital__
#define intel_module_directory_service_3_0_0_init compaq_mds_guid_init
#else
/* {692BCEF0-4540-11d3-A8F3-0090271D266F} */
#define intel_module_directory_service_3_0_0_init \
	{ 0x692bcef0, 0x4540, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
#endif
_CSSM_DEFINE_GUID( intel_module_directory_service_3_0_0, intel_module_directory_service_3_0_0_init );


/* ----- TP ----- */
/* release 3.0 TP */
/* {B24192B0-4540-11d3-A8F3-0090271D266F} */
#define intel_tpm_guid_3_0_0_init \
	{ 0xb24192b0, 0x4540, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_tpm_guid_3_0_0, intel_tpm_guid_3_0_0_init );
#define INTEL_TPM_MAJOR_VER	(3)
#define INTEL_TPM_MINOR_VER	(1)


/* ----- dummy ----- */
/* release 3.0 dummy module */
/* {D73D8870-4540-11d3-A8F3-0090271D266F} */
#define intel_dummy_guid_3_0_0_init \
	{ 0xd73d8870, 0x4540, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_dummy_guid_3_0_0, intel_dummy_guid_3_0_0_init );
#define INTEL_DUMMY_MAJOR_VER	(3)
#define INTEL_DUMMY_MINOR_VER	(0)

/* ----- dummymulti ----- */
/* release 3.0 dummy multi-service module */
/* {14764042-3E44-11D3-8E86-00A0C91F000C} */
#define intel_dummy_multi_guid_3_0_0_init \
    { 0x14764042, 0x3e44, 0x11d3, { 0x8e, 0x86, 0x0, 0xa0, 0xc9, 0x1f, 0x0, 0xc } }
_CSSM_DEFINE_GUID( intel_dummy_multi_guid_3_0_0, intel_dummy_multi_guid_3_0_0_init );
#define INTEL_DUMMY_MULTI_MAJOR_VER    (3)
#define INTEL_DUMMY_MULTI_MINOR_VER    (1)

/* ----- emmdummyaddin ----- */
/* release 3.0 dummy emm addin module */
/* {09D581B0-4541-11d3-A8F3-0090271D266F} */
#define intel_dummy_emm_addin_guid_3_0_0_init \
	{ 0x9d581b0, 0x4541, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_dummy_emm_addin_guid_3_0_0, intel_dummy_emm_addin_guid_3_0_0_init );
#define INTEL_DUMMY_EMM_ADDIN_MAJOR_VER	(3)
#define INTEL_DUMMY_EMM_ADDIN_MINOR_VER	(1)


/* ----- inteldummyemm ----- */
/* release 3.0 intel dummy emm module */
/* {53319010-4541-11d3-A8F3-0090271D266F} */
#define intel_dummy_emm_guid_3_0_0_init \
	{ 0x53319010, 0x4541, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_dummy_emm_guid_3_0_0, intel_dummy_emm_guid_3_0_0_init );
#define INTEL_DUMMY_EMM_MAJOR_VER	(3)
#define INTEL_DUMMY_EMM_MINOR_VER	(1)


/* ----- dummyhrsaddin ----- */
/* release 1.0 dummy hrs addin module */
/* {2D3B4730-9D4E-11d3-9984-0004AC6EBABE} */
#define intel_dummy_hrs_addin_guid_1_0_0_init \
	{ 0x2d3b4730, 0x9d4e, 0x11d3, { 0x99, 0x84, 0x0, 0x4, 0xac, 0x6e, 0xba, 0xbe } }
_CSSM_DEFINE_GUID( intel_dummy_hrs_addin_guid_1_0_0, intel_dummy_hrs_addin_guid_1_0_0_init );
#define INTEL_DUMMY_HRS_ADDIN_MAJOR_VER	(1)
#define INTEL_DUMMY_HRS_ADDIN_MINOR_VER	(0)


/* ----- intelhrsemm ----- */
/* release 1.0 intel hrs emm module */
/* {4F7852B0-9D4E-11d3-9984-0004AC6EBABE} */
#define intel_hrs_emm_guid_1_0_0_init \
	{ 0x4f7852b0, 0x9d4e, 0x11d3, { 0x99, 0x84, 0x0, 0x4, 0xac, 0x6e, 0xba, 0xbe } }
_CSSM_DEFINE_GUID( intel_hrs_emm_guid_1_0_0, intel_hrs_emm_guid_1_0_0_init );
#define INTEL_HRS_EMM_MAJOR_VER	(1)
#define INTEL_HRS_EMM_MINOR_VER	(0)

/* ----- inteldummytestemm ----- */
/* release 3.0 intel dummy test emm module */
/* {E2CCA4F0-10D1-11d4-9AC9-0004AC373B41} */
#define intel_dummy_test_emm_guid_3_0_0_init \
	{ 0xe2cca4f0, 0x10d1, 0x11d4, { 0x9a, 0xc9, 0x0, 0x4, 0xac, 0x37, 0x3b, 0x41 } }
_CSSM_DEFINE_GUID( intel_dummy_test_emm_guid_3_0_0, intel_dummy_test_emm_guid_3_0_0_init );
#define INTEL_DUMMY_TEST_EMM_MAJOR_VER	(3)
#define INTEL_DUMMY_TEST_EMM_MINOR_VER	(1)

/* ----- dummytestemmaddin ----- */
/* release 3.0 dummy test emm addin module */
/* {5773D640-10D2-11d4-9AC9-0004AC373B41} */
#define intel_dummy_test_emm_addin_guid_3_0_0_init \
	{ 0x5773d640, 0x10d2, 0x11d4, { 0x9a, 0xc9, 0x0, 0x4, 0xac, 0x37, 0x3b, 0x41 } }
_CSSM_DEFINE_GUID( intel_dummy_test_emm_addin_guid_3_0_0, intel_dummy_test_emm_addin_guid_3_0_0_init );
#define INTEL_DUMMY_TEST_EMM_ADDIN_MAJOR_VER	(3)
#define INTEL_DUMMY__TEST_EMM_ADDIN_MINOR_VER	(1)

/* ----- stub_csp ----- */
/* release 3.0 stub_csp module */
/* {79BDE0F0-4541-11d3-A8F3-0090271D266F} */
#define intel_stub_csp_guid_3_0_0_init \
	{ 0x79bde0f0, 0x4541, 0x11d3, { 0xa8, 0xf3, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_stub_csp_guid_3_0_0, intel_stub_csp_guid_3_0_0_init );
#define INTEL_STUB_CSP_MAJOR_VER	(3)
#define INTEL_STUB_CSP_MINOR_VER	(1)

/* ----- eaycsp ----- */
/* release 3.0 Intel EAY CSP */
/* {67EF50D0-FE74-11d2-A8E6-0090271D266F} */
#define intel_eaycsp_guid_3_0_0_init \
	{ 0x67ef50d0, 0xfe74, 0x11d2, { 0xa8, 0xe6, 0x0, 0x90, 0x27, 0x1d, 0x26, 0x6f } }
_CSSM_DEFINE_GUID( intel_eaycsp_guid_3_0_0, intel_eaycsp_guid_3_0_0_init );
#define INTEL_EAYCSP_MAJOR_VER	(3)
#define INTEL_EAYCSP_MINOR_VER	(1)

/* ----- hrspwbsp ----- */
/* release 1.0 Intel HRS Password BSP */
/* {4B302E32-4D50-11D4-BA80-000629E26171} */
#define intel_hrs_pwbsp_guid_1_0_0_init \
	{ 0x4b302e32, 0x4d50, 0x11d4, { 0xba, 0x80, 0x0, 0x6, 0x29, 0xe2, 0x61, 0x71 } }
_CSSM_DEFINE_GUID( intel_hrs_pwbsp_guid_1_0_0, intel_hrs_pwbsp_guid_1_0_0_init );
#define INTEL_HRS_PWBSP_MAJOR_VER	(1)
#define INTEL_HRS_PWBSP_MINOR_VER	(0)

#ifndef NO_MODULE_STRING_NAMES
#ifdef UNIX
static const char intel_csm_fullname_string[] = "Intel Cryptographic Services Module";
static const char intel_csm_filename_string[] = "libincsm.so";
static const char intel_csm_credname_string[] = "libincsm.esw";

static const char intel_csm_r_fullname_string[] = 
	"Intel Cryptographic Services Module with RSA";
static const char intel_csm_r_filename_string[] = "libincsmr.so";
static const char intel_csm_r_credname_string[] = "libincsmr.esw";

static const char bsafe_csm_fullname_string[] = "CDSA Adaptation Layer CSP for the BSafe Toolkit from RSA DSI";
static const char bsafe_csm_filename_string[] = "libbsafecsm.so";

static const char intel_x509v3_clm_fullname_string[] = "Intel X509 v3 Certificate Library Module";
static const char intel_x509v3_clm_filename_string[] = "libin509cl.so";
static const char intel_x509v3_clm_credname_string[] = "libin509cl.esw";

static const char intel_spki_clm_fullname_string[] = "Intel SPKI CL/TP Module";
static const char intel_spki_clm_filename_string[] = "libinspkicltp.so";
static const char intel_spki_clm_credname_string[] = "libinspkicltp.esw";

static const char intel_odbc_dsm_fullname_string[] = "Intel Data Storage Module";
static const char intel_odbc_dsm_filename_string[] = "libinodbcdl.so";
static const char intel_odbc_dsm_credname_string[] = "libinodbcdl.esw";

static const char intel_ldap_dsm_fullname_string[] = "Intel LDAP Data Storage Module";
static const char intel_ldap_dsm_filename_string[] = "libinldapdl.so";
static const char intel_ldap_dsm_credname_string[] = "libinldapdl.esw";

static const char intel_ff_dsm_fullname_string[] = "Intel Flat File Data Storage Module";
static const char intel_ff_dsm_filename_string[] = "libinffdl.so";
static const char intel_ff_dsm_credname_string[] = "libinffdl.esw";

static const char intel_mds_fullname_string[] = "Module Directory Service";
static const char intel_mds_filename_string[] = "libmds.so";

static const char intel_tpm_fullname_string[] = "Intel Trust Policy Module";
static const char intel_tpm_filename_string[] = "libin509tp.so";
static const char intel_tpm_credname_string[] = "libin509tp.esw";

static const char intel_dummy_fullname_string[] = "Intel Dummy Module";
static const char intel_dummy_filename_string[] = "libinteldm.so";
static const char intel_dummy_credname_string[] = "libinteldm.esw";

static const char intel_dummy_multi_fullname_string[] = "Intel Dummy Multi-Service Module";
static const char intel_dummy_multi_filename_string[] = "libdummymulti.so";
static const char intel_dummy_multi_credname_string[] = "libdummymulti.esw";

static const char intel_dummy_emm_addin_fullname_string[] = "Intel Dummy Emm Addin Module";
static const char intel_dummy_emm_addin_filename_string[] = "libemmdyad.so";
static const char intel_dummy_emm_addin_credname_string[] = "libemmdyad.esw";

static const char intel_dummy_emm_fullname_string[] = "Intel Dummy Emm Module";
static const char intel_dummy_emm_filename_string[] = "libindyemm.so";
static const char intel_dummy_emm_credname_string[] = "libindyemm.esw"; 

static const char intel_dummy_test_emm_addin_fullname_string[] = "Intel Dummy Test Emm Addin Module";
static const char intel_dummy_test_emm_addin_filename_string[] = "libemmdytstad.so";
static const char intel_dummy_test_emm_addin_credname_string[] = "emmdytstad.esw";

static const char intel_dummy_test_emm_fullname_string[] = "Intel Dummy Test Emm Module";
static const char intel_dummy_test_emm_filename_string[] = "libindytstemm.so";
static const char intel_dummy_test_emm_credname_string[] = "libindytstemm.esw"; 

static const char intel_dummy_hrs_addin_fullname_string[] = "Intel Dummy HRS Addin Module";
static const char intel_dummy_hrs_addin_filename_string[] = "libinhrsdummy.so";
static const char intel_dummy_hrs_addin_credname_string[] = "libinhrsdummy.esw";

static const char intel_hrs_emm_fullname_string[] = "Intel HRS EMM Module";
static const char intel_hrs_emm_filename_string[] = "libinhrsemm.so";
static const char intel_hrs_emm_credname_string[] = "libinhrsemm.esw"; 

static const char intel_stub_csp_fullname_string[] = "Intel Stub CSP Module";
static const char intel_stub_csp_filename_string[] = "libstubcsp.so";
static const char intel_stub_csp_credname_string[] = "libstubcsp.esw";

static const char intel_eaycsp_fullname_string[] = "SSLeay Crypto Based CSP";
static const char intel_eaycsp_filename_string[] = "libeaycsp.so";
static const char intel_eaycsp_credname_string[] = "libeaycsp.esw";

static const char intel_hrs_pwbsp_fullname_string[] = "HRS Password BSP";
static const char intel_hrs_pwbsp_filename_string[] = "libinhrspwbsp.so";
static const char intel_hrs_pwbsp_credname_string[] = "libinhrspwbsp.esw";
#else
static const char intel_csm_fullname_string[] = "Intel Cryptographic Services Module";
static const char intel_csm_filename_string[] = "incsm300.dll";
static const char intel_csm_credname_string[] = "incsm300.esw";

static const char intel_csm_r_fullname_string[] = 
	"Intel Cryptographic Services Module with RSA";
static const char intel_csm_r_filename_string[] = "incsm300r.dll";
static const char intel_csm_r_credname_string[] = "incsm300r.esw";

static const char bsafe_csm_fullname_string[] = "CDSA Adaptation Layer CSP for the BSafe Toolkit from RSA DSI";
static const char bsafe_csm_filename_string[] = "bsafecsm300.dll";

static const char intel_acm_fullname_string[] = "Intel AuthCompute Module";
static const char intel_acm_filename_string[] = "intelac.dll";
static const char intel_acm_credname_string[] = "intelac.esw";

static const char intel_x509v3_clm_fullname_string[] = "Intel X509 v3 Certificate Library Module";
static const char intel_x509v3_clm_filename_string[] = "in509cl300.dll";
static const char intel_x509v3_clm_credname_string[] = "in509cl300.esw";

static const char intel_spki_clm_fullname_string[] = "Intel SPKI CL/TP Module";
static const char intel_spki_clm_filename_string[] = "inspkicltp300.dll";
static const char intel_spki_clm_credname_string[] = "inspkicltp300.esw";

static const char intel_odbc_dsm_fullname_string[] = "Intel Data Storage Module";
static const char intel_odbc_dsm_filename_string[] = "inodbcdl300.dll";
static const char intel_odbc_dsm_credname_string[] = "inodbcdl300.esw";

static const char intel_ldap_dsm_fullname_string[] = "Intel LDAP Data Storage Module";
static const char intel_ldap_dsm_filename_string[] = "inldapdl.dll";
static const char intel_ldap_dsm_credname_string[] = "inldapdl.esw";

static const char intel_ff_dsm_fullname_string[] = "Intel Flat File Data Storage Module";
static const char intel_ff_dsm_filename_string[] = "inffdl300.dll";
static const char intel_ff_dsm_credname_string[] = "inffdl300.esw";

static const char intel_mds_fullname_string[] = "Module Directory Service";
static const char intel_mds_filename_string[] = "mds300.dll";

static const char intel_tpm_fullname_string[] = "Intel Trust Policy Module";
static const char intel_tpm_filename_string[] = "in509tp300.dll";
static const char intel_tpm_credname_string[] = "in509tp300.esw";

static const char intel_dummy_fullname_string[] = "Intel Dummy Module";
static const char intel_dummy_filename_string[] = "inteldm300.dll";
static const char intel_dummy_credname_string[] = "inteldm300.esw";

static const char intel_dummy_multi_fullname_string[] = "Intel Dummy Multi-Service Module";
static const char intel_dummy_multi_filename_string[] = "dummymulti300.dll";
static const char intel_dummy_multi_credname_string[] = "dummymulti300.esw";

static const char intel_dummy_emm_addin_fullname_string[] = "Intel Dummy Emm Addin Module";
static const char intel_dummy_emm_addin_filename_string[] = "emmdyad300.dll";
static const char intel_dummy_emm_addin_credname_string[] = "emmdyad300.esw";

static const char intel_dummy_emm_fullname_string[] = "Intel Dummy Emm Module";
static const char intel_dummy_emm_filename_string[] = "indyemm300.dll";
static const char intel_dummy_emm_credname_string[] = "indyemm300.esw"; 

static const char intel_dummy_test_emm_addin_fullname_string[] = "Intel Dummy Test Emm Addin Module";
static const char intel_dummy_test_emm_addin_filename_string[] = "emmdytstad300.dll";
static const char intel_dummy_test_emm_addin_credname_string[] = "emmdytstad300.esw";

static const char intel_dummy_test_emm_fullname_string[] = "Intel Dummy Test Emm Module";
static const char intel_dummy_test_emm_filename_string[] = "indytstemm300.dll";
static const char intel_dummy_test_emm_credname_string[] = "indytstemm300.esw"; 

static const char intel_dummy_hrs_addin_fullname_string[] = "Intel Dummy HRS Addin Module";
static const char intel_dummy_hrs_addin_filename_string[] = "inhrsdummy100.dll";
static const char intel_dummy_hrs_addin_credname_string[] = "inhrsdummy100.esw";

static const char intel_hrs_emm_fullname_string[] = "Intel HRS EMM Module";
static const char intel_hrs_emm_filename_string[] = "inhrsemm100.dll";
static const char intel_hrs_emm_credname_string[] = "inhrsemm100.esw"; 

static const char intel_stub_csp_fullname_string[] = "Intel Stub_csp Module";
static const char intel_stub_csp_filename_string[] = "stb_csp300.dll";
static const char intel_stub_csp_credname_string[] = "stb_csp300.esw";

static const char intel_eaycsp_fullname_string[] = "SSLeay Crypto Based CSP";
static const char intel_eaycsp_filename_string[] = "eaycsp300.dll";
static const char intel_eaycsp_credname_string[] = "eaycsp300.esw";

static const char intel_hrs_pwbsp_fullname_string[] = "HRS Password BSP";
static const char intel_hrs_pwbsp_filename_string[] = "inhrspwbsp100.dll";
static const char intel_hrs_pwbsp_credname_string[] = "inhrspwbsp100.esw";
#endif

#endif  /* NO_MODULE_STRING_NAMES */



#ifdef __cplusplus
}
#endif

#endif
