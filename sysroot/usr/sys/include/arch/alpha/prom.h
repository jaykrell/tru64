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
/* @(#)prom.h	9.2  (ULTRIX)        10/28/91    */

/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/*
 * Modification History: /sys/sas/alpha/prom.h
 *
 * 21-Oct-91 -- Andrew L. Duane
 *	Major fixes to upgrade to the Console rev. 3.2 specification
 *	New calling sequences, arguments, function codes, and register usage.
 *	NOTE: some of these are not yet implemented: see prom.c
 *
 * 13-Nov-90 -- Tim Burke
 *	Created this file for Alpha console support.
 */

#ifndef __PROM_INCLUDE__
#define __PROM_INCLUDE__

#ifndef __cplusplus

#include <sys/types.h>

/*
 * The console routines are dispatched through the DISPATCH routine by
 * passing function codes and an argument list.  The various routines and
 * their function code assignments are defined in this module.
 */

#define DISPATCH prom_dispatcher	/* tim fix - no doubt will change   */

/*
 * UPDATE_FLASH_TIME is the number of seconds that we will
 * wait (overall) before we decide whether one of the callbacks
 * that writes nonvolatile storage (PROM_SAVEENV, PROM_WRITE_EEROM)
 * has failed due to timeout expiration.
 */
#define UPDATE_FLASH_TIME 30

/*
 * Console routine function codes.
 */
#define CONS_GETC		1	/* Get char from console terminal   */
#define CONS_PUTS		2	/* Put string to console terminal   */
#define CONS_RESET_TERM		3	/* Reset console term to defaults   */
#define CONS_SET_TERM_INTR	4	/* Set console terminal interrupts  */
#define CONS_SET_TERM_CTRL	5	/* Set console terminal controls    */
#define CONS_PROCESS_KEYCODE	6	/* Process/translate keycode	    */
#define CONS_CONSOLE_OPEN	7	/* Open console terminal for use    */
#define CONS_CONSOLE_CLOSE	8	/* Close console terminal           */
#define CONS_RESERVED_9		9	/* reserved */
#define CONS_RESERVED_10	10	/* reserved */
#define CONS_RESERVED_11	11	/* reserved */
#define CONS_RESERVED_12	12	/* reserved */
#define CONS_RESERVED_13	13	/* reserved */
#define CONS_RESERVED_14	14	/* reserved */
#define CONS_RESERVED_15	15	/* reserved */
#define CONS_OPEN		16	/* Open IO device for access        */
#define CONS_CLOSE		17	/* Close IO device for access       */
#define CONS_IOCTL		18	/* Device specific IO operations    */
#define CONS_READ		19	/* Read IO device		    */
#define CONS_WRITE		20	/* Write IO device		    */
#define CONS_RESERVED_21	21	/* reserved */
#define CONS_RESERVED_22	22	/* reserved */
#define CONS_RESERVED_23	23	/* reserved */
#define CONS_RESERVED_24	24	/* reserved */
#define CONS_RESERVED_25	25	/* reserved */
#define CONS_RESERVED_26	26	/* reserved */
#define CONS_RESERVED_27	27	/* reserved */
#define CONS_RESERVED_28	28	/* reserved */
#define CONS_RESERVED_29	29	/* reserved */
#define CONS_RESERVED_30	30	/* reserved */
#define CONS_RESERVED_31	31	/* reserved */
#define CONS_SETENV		32	/* Set an environment variable	    */
#define CONS_CLEARENV		33	/* Delete an evnoronment variable   */
#define CONS_GETENV		34	/* Get an environment variable	    */
#define CONS_SAVEENV		35	/* Save environment variables	    */
#define CONS_PARTITION          40      /* Configure Partition Info         */
#define	CONS_PSWITCH		48	/* Switch primary processor (MP)    */
#define CONS_SAVE_ERROR_LOG     49      /* Write errorlog data to non-volatile
                                            storage                         */
#define CONS_BIOS	        50	/* BIOS emmulation callback */
#define CONS_WRITE_EEROM        51      /* 0x33 - write FRU data to eerom   */
#define CONS_READ_EEROM         52      /* 0x34 - read FRU data from eerom  */
#define CONS_LOG_IPMI_SEL       53      /* 0x35 - log IPMI SEL entry */

#if 0
#define CONS_FIXUP		16	/* Does virtual address fixup       */
#endif 

/*
 * CONS_PARTITION Dispatch Subcodes -- per V6 Config Tree Spec Section 10.1
 */
#define CONS_READ_LOCK		 1
#define CONS_READ_UNLOCK	 2
#define CONS_SET_NODE_FLAGS	 3
#define CONS_CLEAR_NODE_FLAGS	 4
#define CONS_UPDATE_TREE	 6
#define CONS_ASSIGN_HW		11
#define CONS_UPDATE_OS_USAGE	12
#define CONS_FIND_PARTITION	13
#define CONS_POWER_HW		26
#define CONS_UPDATE_TESTED_PFNS	27
#define CONS_UPDATE_PARTIAL_TREE 31

/* Flags for DISPATCH routines */
#define CONS_POWER_DOWN		0
#define CONS_POWER_UP		1

/* Flags for Assign_HW dispatch routine */
#define CONS_ASSIGN_ALL_DESCENDANTS	0x0001
#define CONS_ASSIGN_POWER_UP		0x0002
#define CONS_ASSIGN_POWER_DOWN		0x0004
#define CONS_ASSIGN_IGNORE_COUNTER	0x0008


/* Flag types for SET_NODE_FLAGS callback */
#define CONS_NODE_FLAGS	0x0000 /* Node flags */
#define CONS_PART_FLAGS	0x0001 /* partition node flags */
#define CONS_COMM_FLAGS	0x0002 /* Community node flags */
#define CONS_HARD_FLAGS	0x0003 /* hard partition node flags */
#define CONS_ROOT_FLAGS	0x0004 /* root node */

/* Valid flags for flag type CONS_NODE_FLAGS */
#define CONS_NODE_DISABLED	0x1000
#define CONS_NODE_UPDATING	0x2000
#define CONS_NODE_UNHEALTHY	0x4000

/* Flags for SET_OS_USAGE */
#define CONS_NO_TREE_CHANGE 0x0001  /* Do not notify instances after setting 
				       the OS usage in this node */

/*
 * Flags Type definitions for CONS_SET_NODE_FLAGS/CONS_CLEAR_NODE_FLAGS:
 * per V6 Config Tree Spec Section 10.4
 */
#define CONS_CTFT_NODE_FLAGS 0
#define CONS_CTFT_PART_FLAGS 1
#define CONS_CTFT_COMM_FLAGS 2
#define CONS_CTFT_HARD_FLAGS 3
#define CONS_CTFT_ROOT_FLAGS 4
    
/*
 * The DISPATCH routine is used to call the console routine.  
 *
 * Notes: The dispatch routine is a generic interface to the console
 * routines.  The first argument is always one of the function codes.
 * Following the function code is 0 to 5 parameters.
 *
 * tim fix -
 * I'm not sure if it is necessary to pass null parameters in the case
 * where all 5 parameters are needed.  I suppose this will  depend on how
 * the dispatch routine is implemented and register conventions/usage.
 * For now I'll assume that a full list of 5 parameters must always be
 * provided.
 *
 * ald -
 * The last two arguments are reserved for IOCTL only. Propagate them
 * for all routines, even if unused. Comment above is right: pass them all.
 *
 * Dispatch() calling sequence:
 *	arg0 is function code: e.g. CONS_GETC; goes into r16 (s0)
 *	arg1->5 are arg0->4 of caller; go into r17-r21 (s1-s5)
 *	r26 (k0) is used for the return address back to DISPATCH.
 *	r25 (t9) isn't used, even though the spec says it is.
 */

/* char = getc(unit) */
#define PROM_GETC(P_UNIT) \
	DISPATCH(CONS_GETC, P_UNIT, 0, 0, 0, 0)

/* wcount = puts(unit, string, length) */
#define PROM_PUTS(P_UNIT, P_ADDRESS, P_LENGTH) \
	DISPATCH((u_long)CONS_PUTS, (u_long)P_UNIT, (u_long)P_ADDRESS, (u_long)P_LENGTH, (u_long)0, (u_long)0)

/* status = reset_term(unit) */
#define PROM_RESET_TERM(P_UNIT)	\
	DISPATCH((u_long)CONS_RESET_TERM, (u_long)P_UNIT, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* status = set_term_intr(unit, mask) */
#define PROM_SET_TERM_INTR(P_UNIT, P_MASK) \
	DISPATCH((u_long)CONS_SET_TERM_INTR, (u_long)P_UNIT, (u_long)P_MASK, (u_long)0, (u_long)0, (u_long)0)

/* status = set_term_ctrl(unit, crb) */
#define PROM_SET_TERM_CTRL(P_CRB) \
	DISPATCH((u_long)CONS_SET_TERM_CTRL, (u_long)P_UNIT, (u_long)P_CRB, (u_long)0, (u_long)0, (u_long)0)

/* char = process_keycode(unit, keycode, again) */
#define PROM_PROCESS_KEYCODE(P_UNIT, P_KEYCODE, P_AGAIN) \
	DISPATCH((u_long)CONS_PROCESS_KEYCODE, (u_long)P_UNIT, (u_long)P_KEYCODE, (u_long)P_AGAIN, (u_long)0, (u_long)0)

/* console_open() */
#define PROM_CONSOLE_OPEN() \
	DISPATCH((u_long)CONS_CONSOLE_OPEN, (u_long)0, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* console_close() */
#define PROM_CONSOLE_CLOSE() \
	DISPATCH((u_long)CONS_CONSOLE_CLOSE, (u_long)0, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* channel = open(devstr, length) */
#define PROM_OPEN(P_DEVSTR, P_LENGTH) \
	DISPATCH((u_long)CONS_OPEN, (u_long)P_DEVSTR, (u_long)P_LENGTH, (u_long)0, (u_long)0, (u_long)0)

/* status = close(channel) */
#define PROM_CLOSE(P_CHANNEL) \
	DISPATCH((u_long)CONS_CLOSE, (u_long)P_CHANNEL, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* count = ioctl(channel, param2, param3, param4, param5) */
#define PROM_IOCTL(P_CHANNEL, P_PARAM2, P_PARAM3, P_PARAM4, P_PARAM5) \
	DISPATCH((u_long)CONS_IOCTL, (u_long)P_CHANNEL, (u_long)P_PARAM2, (u_long)P_PARAM3, (u_long)P_PARAM4, (u_long)P_PARAM5)

/* rcount = read(channel, count, address, block) */
#define PROM_READ(P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK) \
	DISPATCH((u_long)CONS_READ, (u_long)P_CHANNEL, (u_long)P_COUNT, (u_long)P_ADDRESS, (u_long)P_BLOCK, (u_long)0)

/* wcount = write(channel, count, address, block) */
#define PROM_WRITE(P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK) \
	DISPATCH((u_long)CONS_WRITE, (u_long)P_CHANNEL, (u_long)P_COUNT, (u_long)P_ADDRESS, (u_long)P_BLOCK, (u_long)0)

/* status = setenv(id, value, length) */
#define PROM_SETENV(P_ID, P_VALUE, P_LENGTH) \
	DISPATCH((u_long)CONS_SETENV, (u_long)P_ID, (u_long)P_VALUE, (u_long)P_LENGTH, (u_long)0, (u_long)0)

/* status = clearenv(id, value, length) */
#define PROM_CLEARENV(P_ID, P_BUFFER, P_BUFLEN) \
	DISPATCH((u_long)CONS_CLEARENV, (u_long)P_ID, (u_long)P_BUFFER, (u_long)P_BUFLEN, (u_long)0, (u_long)0)

/* status = getenv(id, buffer, length) */
#define PROM_GETENV(P_ID, P_BUFFER, P_BUFLEN) \
	DISPATCH((u_long)CONS_GETENV, (u_long)P_ID, (u_long)P_BUFFER, (u_long)P_BUFLEN, (u_long)0, (u_long)0)

/* status = save_env() */
#define PROM_SAVEENV() \
	DISPATCH((u_long)CONS_SAVEENV, (u_long)0, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* status = prom_pswtch(action) */
#define PROM_PSWTCH(P_ACTION, P_CPUID) \
	DISPATCH((u_long)CONS_PSWITCH, (u_long)P_ACTION, (u_long)P_CPUID, (u_long)0, (u_long)0, (u_long)0)

/* status = save_error_log(device, size, buffer, classtype, flag) */
#define SAVE_ERROR_LOG(P_ID, P_BUFLEN, P_BUFFER, CLASSTYPE, FLAG) \
        DISPATCH((u_long)CONS_SAVE_ERROR_LOG, (u_long)P_ID, (u_long)P_BUFLEN, (u_long)P_BUFFER, (u_long)CLASSTYPE, (u_long)FLAG)

/* status = prom_bios(int86, x86_reg_mask, x86_regs, data1, data2) */
#define PROM_BIOS(INT86, MASK, REGS, DATA1, DATA2) \
        DISPATCH((u_long)CONS_BIOS, (u_long)INT86, (u_long)MASK, (u_long)REGS, (u_long)DATA1, (u_long)DATA2 )

/* status = prom_write_eerom(buffer, length, dpr_offset, eerom_offset) */
#define PROM_WRITE_EEROM(P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE) \
        DISPATCH((u_long)CONS_WRITE_EEROM, (u_long)P_BUFFER, (u_long)P_LENGTH, (u_long)P_FRU_ID, (u_long)P_OPCODE, (u_long)0)

/* status = prom_read_eerom(buffer, length, dpr_offset, eerom_offset) */
#define PROM_READ_EEROM(P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE) \
        DISPATCH((u_long)CONS_READ_EEROM, (u_long)P_BUFFER, (u_long)P_LENGTH, (u_long)P_FRU_ID, (u_long)P_OPCODE, (u_long)0)

/* status = prom_log_ipmi_sel(action, value) */
#define PROM_LOG_IPMI_SEL(P_ACTION, P_VALUE) \
        DISPATCH((u_long)CONS_LOG_IPMI_SEL, (u_long)P_ACTION, (u_long)P_VALUE, (u_long)0, (u_long)0, (u_long)0)

#if 0
/* This is BROKEN! FIXUP uses a separate entry point from DISPATCH !!! */
#define PROM_FIXUP() \
 	DISPATCH((u_long)CONS_FIXUP, (u_long)0, (u_long)0, (u_long)0, (u_long)0, (u_long)0)
#endif

/*
 * CONS_PARTITION call backs
 */
/* status = prom_power(fru_id, flag, change_counter) */
#define PROM_POWER(P_FRU_ID, P_FLAG, P_CHNG_CTR) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_POWER_HW, (u_long)P_FRU_ID, (u_long)P_CHNG_CTR, (u_long)P_FLAG, (u_long)0)

/* status = prom_read_lock(fru_id, retry_cnt) */
#define PROM_READ_LOCK(P_PART_ID, P_RETRY_CNT) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_READ_LOCK, (u_long)P_PART_ID, (u_long)P_RETRY_CNT, (u_long)0, (u_long)0)

/* status = prom_read_unlock(fru_id) */
#define PROM_READ_UNLOCK(P_PART_ID) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_READ_UNLOCK, (u_long)P_PART_ID, (u_long)0, (u_long)0, (u_long)0)

/* status = prom_set_node_flags(fru_id, type, mask, node_change_ctr) */
#define PROM_SET_NODE_FLAGS(P_FRU_ID, P_TYPE, P_MASK, P_CTR) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_SET_NODE_FLAGS, (u_long)P_FRU_ID, (u_long)P_TYPE, (u_long)P_MASK, (u_long)P_CTR)

/* status = prom_clear_node_flags(fru_id, type, mask, node_change_ctr) */
#define PROM_CLEAR_NODE_FLAGS(P_FRU_ID, P_TYPE, P_MASK, P_CTR) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_CLEAR_NODE_FLAGS, (u_long)P_FRU_ID, (int)P_TYPE, (u_long)P_MASK, (int)P_CTR)

/* status = prom_update_tree(void) */
#define PROM_UPDATE_TREE() \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_UPDATE_TREE, (u_long)0, (u_long)0, (u_long)0, (u_long)0)

/* status = prom_assign_hw(fru_id, new_owner, new_current_owner, node_change_ctr, flags) */
#define PROM_ASSIGN_HW(P_FRU_ID,  P_NEW_OWNER, P_NEW_CURR_OWNER, P_FLAGS, P_CTR)\
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_ASSIGN_HW, (u_long)P_FRU_ID, (u_long)P_NEW_OWNER, (u_long)P_NEW_CURR_OWNER, (int)P_CTR, (u_int)P_FLAGS);

/* status = prom_update_os_usage(fru_id, data, flags, node_change_ctr) */
#define PROM_UPDATE_OS_USAGE(P_FRU_ID, P_DATA, P_FLAGS, P_CTR)\
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_UPDATE_OS_USAGE, (u_long)P_FRU_ID, (u_long)P_DATA, (u_long)P_FLAGS, (u_long)P_CTR, (u_long)0)

/* status = prom_find_partition(hwrpb, &part_hdl, &part_id, &comm_hdl, &comm_id) */
#define PROM_FIND_PARTITION(P_HWRPB, P_PART_HDL, P_PART_ID, P_COMM_HDL, P_COMM_ID) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_FIND_PARTITION, (u_long)P_HWRPB, (u_long)P_PART_HDL, (u_long)P_PART_ID, (u_long)P_COMM_HDL, (u_long)P_COMM_ID)
/* status = prom_update_partial_tree(fru_id) */
#define PROM_UPDATE_PARTIAL_TREE(P_FRU_ID) \
	DISPATCH((u_long)CONS_PARTITION, (u_long)CONS_UPDATE_PARTIAL_TREE, (u_long)P_FRU_ID, (u_long)0, (u_long)0, (u_long)0)

/*
 * TODO:  more CONS_PARTITION callbacks as we need them.
 */


/*
 * The following constants are used to examine the status of prom calls.
 */
#define CONS_WRITE_ERROR	0x8000000000000000
#define CONS_WRITE_EOT		0x4000000000000000
#define CONS_WRITE_ILI		0x2000000000000000
#define CONS_WRITE_EOM		0x1000000000000000
#define CONS_READ_ERROR		0x8000000000000000
#define CONS_READ_EOF		0x4000000000000000
#define CONS_READ_ILI		0x2000000000000000
#define CONS_READ_EOM		0x1000000000000000
#define GETC_RCV_OK	0	/* Success, character received 		*/
#define GETC_NOT_READY	2	/* Not ready for reception		*/
#define GETC_RCV_ERR	3	/* Character received with error	*/

/* 
 * Defines for return status of PROM_PUTS and PROM_GETC. PROM_GETC has the 
 * same status bit values as PROM_PUTC, except that the 32 LSB holds either 
 * (PUTS) the number of bytes written or (GETC) the character retrieved.
 *
 * CONS_PUTS_STATUS_MASK is 0xc0... to cover both success and partial success.
 */
#define CONS_PUTS_STATUS_MASK   0xc000000000000000
#define CONS_PUTS_VALUE_MASK    0x00000000ffffffff
#define CONS_PUTS_SUCCESS       0x0000000000000000      

/* defines for return status of PROM_SAVEENV */
#define CONS_SAVEENV_SUCCESS	0x0000000000000000
#define CONS_SAVEENV_PARTIAL	0x2000000000000000	/* some vars stored in nvr, 
							 * additional vars to be
							 * stored in nvr
							 */
#define	CONS_SAVEENV_UNSUP	0xc000000000000000	/* saveenv unsupported */
#define CONS_SAVEENV_FAIL	0xe000000000000000	/* saveenv failed */

/* defines for return status of PROM_GETENV */
#define CONS_GETENV_SUCCESS	0x0000000000000000
#define CONS_GETENV_FAILURE	0xc000000000000000	/* variable not recognized */
#define CONS_GETENV_TRUNC	0x2000000000000000	/* value truncated */
#define CONS_GETENV_STATUS_MASK 0xffffffff00000000	/* lower 32 bits are num chars copied */

/* defines for return status of WRITE/READ_EEROM */
#define CONS_EEROM_STATUS_MASK  0xf000000000000000      /* for masking off byte count    */
#define CONS_EEROM_SUCCESS      0x0000000000000000
#define CONS_EEROM_ILL_BUFSIZE  0x1000000000000000      /* buffer size exceeds 256 bytes */
#define CONS_EEROM_FRU_ID_INVAL 0x2000000000000000      /* invalid fru_id specified      */
#define CONS_EEROM_ACCESS_FAIL  0x3000000000000000      /* FRU EEROM cannot be accessed  */
#define CONS_EEROM_MEM_FAIL     0x4000000000000000      /* cannot access virtual address */
#define CONS_EEROM_SDD_BUFSIZE  0x5000000000000000      /* buffer size != 88 bytes for SDD logs */
#define CONS_EEROM_IN_PROG      0x6000000000000000      /* Command in progress           */
#define CONS_EEROM_ILL_OPCODE   0x8000000000000000      /* unsupported operation code    */
#define CONS_EEROM_BUSY         0x9000000000000000      /* busy, retry later             */
 
/* defines for return status of PROM_LOG_IPMI_SEL */
#define CONS_LOG_SEL_SUCCESS    0x0000000000000000      /* SEL logging success */
#define CONS_LOG_SEL_FAIL_SUPP  0x8000000000000000      /* SEL logging failure, not supported */
#define CONS_LOG_SEL_FAIL_WRITE 0xA000000000000000      /* SEL logging failure, write failed */
#define CONS_LOG_SEL_FAIL_BUSY  0xC000000000000000      /* SEL logging failure, SEL busy */
#define CONS_LOG_SEL_FAIL_PRIM  0xE000000000000000      /* SEL logging failure, not on primary */
#define CONS_LOG_SEL_FULL_MASK  0x1000000000000000      /* Mask for SEL full bit */

/*
 * Status returns for CONS_PARTITION callbacks
 * See Alpha Systems Configuration Tree Spec, V6+, Section 10.2
 */
#define CONS_CTFT_NOSTATUS	0x00L	/* no status returned */
#define CONS_CTFT_SUCCESS	0x01L	/* success */
#define CONS_CTFT_BADPARAM	 -2UL	/* Bad parameter value */
#define CONS_CTFT_ILLEGAL	 -4UL	/* Illegal parameter value */
#define CONS_CTFT_NOTFOUND	 -6UL	/* Requested item not found */
#define CONS_CTFT_BADALIGN	 -8UL	/* Bad alignment */
#define CONS_CTFT_BADALLOC	-10UL	/* Bad allocation parameter */
#define CONS_CTFT_OVERLAP	-12UL	/* Descriptor overlaps existing descriptors */
#define CONS_CTFT_NOTINITIALIZED -14UL	/* The soft partition was not initialized */
#define CONS_CTFT_BADHANDLE	-16UL	/* handle not a valid HW node */
#define CONS_CTFT_NOTDELETED	-18UL	/* Not deleted */
#define CONS_CTFT_MAXEXCEEDED	-20UL	/* Max exceeded */
#define CONS_CTFT_NOTALLOWED	-22UL	/* Operation not allowed */
#define CONS_CTFT_BADOWNER	-24UL	/* A comp. had an owner that is incompatible with the request */
#define CONS_CTFT_NOTDONE	-26UL	/* callback processing not completed in allotted time */
#define CONS_CTFT_NOTPARTITION	-28UL	/* node is not a soft partition */
#define CONS_CTFT_NOTCOMMUNITY	-30UL	/* Not a community node */
#define CONS_CTFT_ILLEGALTREE	-32UL	/* Illegal tree detected */
#define CONS_CTFT_NOTHARDWARE	-34UL	/* Not hardware */
#define CONS_CTFT_NOMEMORY	-36UL	/* Config tree memory exhausted */
#define CONS_CTFT_BADPFN	-38UL	/* The PFN is invalid or out of range */
#define CONS_CTFT_BADCOUNT	-40UL	/* The PFN count is invalid or out of range */
#define CONS_CTFT_TREELOCKED	-42UL	/* The tree is locked by another soft partition */
#define CONS_CTFT_BADUPDATELEVEL -44UL	/* The update level is not the same as the input to the call */
#define CONS_CTFT_NOTMEMORYDESC	-46UL	/* not a memory descriptor */
#define CONS_CTFT_NOTLOCKED	-48UL	/* Attempted to unlock a cfgtree that wasn't locked */
#define CONS_CTFT_UNAVILABLE	-50UL	/* node flagged as unavailable */
#define CONS_CTFT_STILLACTIVE	-52UL	/* The HW comp. is still active */
#define CONS_CTFT_CHILDSTILLACTIVE	-54UL  /* A component part of the HW is still active */
#define CONS_CTFT_CHILDALREADYOWNED	-56UL  /* A child is owned.  This is an internal error */
#define CONS_CTFT_NOTSHARED		-58UL  /* The device cannot be assigned because an ancestor is not shared */
#define CONS_CTFT_TREEBEINGUPDATED	-60UL  /* Tree is being updated */
#define CONS_CTFT_BADTREEINTEGRITY	-62UL  /* Tree corruption detected */
#define CONS_CTFT_NOTHARDPARTITION	-64UL  /* Not a hard partition node */
#define CONS_CTFT_NOTIMPLEMENTED	-66UL  /* Callback not implemented */
#define CONS_CTFT_ALREADYOWNED		-68UL  /* Node already has an owner */
#define CONS_CTFT_CHANGECOLLISION	-70UL  /* Node change counter mismatch */
#define CONS_CTFT_NOTSOFTWARE		-72UL  /* Node is not a software node */
#define CONS_CTFT_NO_TREE_CHANGE	-74UL  /* No change was made to the configuration tree */
#define CONS_CTFT_WRONG_SPEED		-75UL  /* Incompatible operating speed */
#define CONS_CTFT_WRONG_MODE		-76UL  /* Incompatible operating mode */
#define CONS_CTFT_POWER_BUDGET_EXCEEDED	-77UL  /* Power budget exceeded */
#define CONS_CTFT_MEMORY_SPACE_EXCEEDED	-78UL  /* PCI memory exceeded */
#define CONS_CTFT_IO_SPACE_EXCEEDED	-79UL  /* PCI I/O space exceeded */
#define CONS_CTFT_CONSOLE_REJECTED_CHANGE -80UL  /* Console rejected hot-plug operation */
#define CONS_CTFT_POWER_FAULT		-81UL  /* Device power fault */
#define CONS_CTFT_PHPC_FAULT		-82UL  /* Hot-Plug controller fault */

/*
 * Assume that there is a maximum sized output string to protect from the
 * case where cprintf is called with an improperly terminated string.
 */
#define MAX_CONSOLE_STRING	1023	/* Maximum size of output string */

/*
 * This is an internal buffer used to pass back null terminated environment
 * variable values with getenv.
 */
#define MAX_ENVIRON_LENGTH	255

/* Status returned from prom_saveenv */
#define SAVE_ENV_PARTIAL	(int)1
#define SAVE_ENV_SUCCESS	(int)0
#define SAVE_ENV_FAIL		(int)-1
#define SAVE_ENV_DISABLED       (int)-2

/* Status returned from prom_setenv */
#define SET_ENV_SUCCESS		(int)0
#define SET_ENV_FAILURE		(int)-1
#define SET_ENV_DISABLED        (int)-2

/* Status returned from prom_getenv */
#define GET_ENV_SUCCESS         (int)0
#define GET_ENV_TRUNC   	(int)1
#define GET_ENV_FAILURE 	(int)-1
#define GET_ENV_DISABLED        (int)-2

/* Status returned from prom_write_eerom/prom_read_eerom */
#define EEROM_IN_PROG   	(int)1
#define EEROM_SUCCESS   	(int)0
#define EEROM_FAIL      	(int)-1

/* Status returned from prom_log_ipmi_sel */
#define LOG_SEL_SUCCESS         (int)0
#define LOG_SEL_FAIL_SUPP       (int)-1
#define LOG_SEL_FAIL_WRITE      (int)-2
#define LOG_SEL_FAIL_BUSY       (int)-3
#define LOG_SEL_FAIL_PRIM       (int)-4
#define LOG_SEL_FAIL_FULL       (int)-5

/*
 * Status returned from PROM_CONSOLE_OPEN() and PROM_CONSOLE_CLOSE()
 */
#define PROM_CONSOLE_STATUS_FAIL	0x8000000000000000
#define PROM_CONSOLE_STATUS_MASK	0xC000000000000000
#define PROM_CONSOLE_FAIL_DATA		0x1FFFFF0000000000


/*
 * Three functions which set, save, and get console environment
 * variables.
 */

/*
 * int prom_setenv(char *varname, char *value, int flags)
 *
 * synopsis: sets the in memory environment variable specified by 
 *	varname to the value specified by the value parameter.
 *	The environment	variable type is validated as one 
 *	that Digital UNIX recognizes. Then an attempt is made 
 *	to set the in memory copy of the console environment 
 *	variable via SRM console callback.  According to the
 *	SRM, the environment variable is not saved in NVR after 
 *	this call.
 *
 *	The flags field will be used to determine if this
 *	functionality should be verified by the hal.  This
 *	is needed because new UNIX 4.0b EV functionality
 *	is not backward compatable with existing firmware,
 *	which doesn't compley with the SRM.
 *
 * parameters:
 *
 *	char *varname 
 *		is the type of environment variable that is 
 *		being set.
 *
 *		Alpha SRM defined varnames are:
 *		===============================
 * 		auto_action,	boot_dev,	bootdef_dev,
 *		booted_dev, 	boot_file, 	booted_file,
 *		boot_osflags, 	booted_osflags,	boot_reset,
 *		dump_dev, 	enable_audit, 	license,
 *		char_set, 	language, 	tty_dev,
 *
 *		Serial Modem Console Support varnames
 *		which are system specific:
 *		==========================
 *	 	com1_baud,	com1_modem, 	com1_flow,
 *	 	com1_misc,	com2_baud, 	com2_modem,
 *	 	com2_flow,	com2_misc
 *
 *		Bird only? system specific scsi varnames
 *		========================================
 *		scsiid, 	scsifast
 *
 *	char *value
 *		the value that the console environment variable
 *		is being set to.
 *
 *	int flags 
 *		This interface should be called with the PROM_VERIFY
 *		flag when:
 *
 *			an environment variable is defined as 
 *			being stored in NVR or flash ROM and
 *			it is expected to be saved there with
 *			a subsequent call to prom_saveenv
 *
 *			an environment variable is being used
 *			for the first time.
 *
 *			an environment variable is already being
 *			used with the PROM_VERIFY flag set.
 *
 *		Otherwise, this interface should be called with
 *		flags set to PROM_NOVERIFY
 *
 *		All com variables and any new vriables which 
 *		are not explicitly defined in the SRM must be
 *		called with the flag field set to PROM_VERIFY.
 *
 * return value: 
 *
 * 	SET_ENV_SUCCESS	(int)0 
 *		Console callback indicated that the environment
 *		variable was successfully saved in system memory.
 *	SET_ENV_FAILURE	(int)-1
 *		Invalid environment variable was passed or 
 *		console callback indicated it could not
 *		successfully save the environment variable.
 *
 * restrictions:
 *	
 *	This function cannot be called from ISR context.
 */
extern int	prom_setenv(char *varname, char *value, int flags);

/*
 * extern int	prom_saveenv();
 *
 * synopsis:
 *	Attempt to save, in NVR, all environment variables 
 *	which have been	set by prom_setenv(), and are supported
 *	was being stored in NVR.  This function will repeatedly
 *	attempt to save until successful or until 30 seconds
 *	expires.  This is not an unreasonable amount of	time 
 *	for a multiple copy flash rom update.  Be aware that
 *	this function could take several seconds to complete. 
 *
 *	Environment variables which are capable of being saved 
 *	in NVR are:
 *
 *		SRM defined variables:
 *
 *		auto_action,    bootdef_dev,    boot_file,
 *		boot_osflags,   boot_reset,     dump_dev,
 *		enable_audit,   char_set,       language,
 *
 *		Addtional System specific variables:
 *
 *		com1_baud,	com1_modem, 	com1_flow,
 *		com1_misc,	com2_baud,	com2_modem,
 *		com2_flow,	com2_misc
 *
 *		NOT SURE IF THESE TWO VARIABLES ARE SAVED ON THE
 *		SYSTEMS THEY ARE SUPPORTED ON.
 *
 *		scsiid,		scsifast
 *
 *
 * parameters:
 *		none
 * return value: 
 *
 * 	SAVE_ENV_PARTIAL (int)1 
 *		Indicates that the save wasn't completed after
 *		attempting to save for 30 seconds.
 * 	SAVE_ENV_SUCCESS (int)0
 *		Indicates that modified environment variable 
 *		have been successfully saved in NVR.
 * 	SAVE_ENV_FAIL (int)-1
 *		Indicidates that the console failed to save 
 *		the updated environment variables or that the 
 *		console	doesn't support	saving environment 
 *		variables.
 *		
 * restrictions:
 *		This function can block and should never be 
 *		called from ISR context.
 */
extern int	prom_saveenv(void);

/*
 * extern int prom_getenv(char *varname, char *value, int flags);
 *
 * Synopsis:
 *	read the in memory copy of the console environment
 *	variable specified by varname.  The in-memory copy
 *	will be copied into the char array pointed to by
 *	value.
 *
 *	The flags field will be used to determine if this
 *	functionality should be verified by the hal.  This
 *	is needed because new EV firmware functionality broke
 *	existing firmware in the field in several ways.
 *
 *	All SRM define variables should be readable.
 *	The system specific environment variables
 *	defined for serial modem console support can also be
 *	read on systems for which they are defined.  The
 *	flag field must be set to PROM_VERIFY when reading
 *	non-SRM defined EVs.
 *
 * Parameters:
 *	char *varname
 *		the console environment variable which is being
 *		read.
 *
 *		Alpha SRM defined varnames are:
 *		===============================
 * 		auto_action,	boot_dev,	bootdef_dev,
 *		booted_dev, 	boot_file, 	booted_file,
 *		boot_osflags, 	booted_osflags,	boot_reset,
 *		dump_dev, 	enable_audit, 	license,
 *		char_set, 	language, 	tty_dev,
 *
 *		Serial Modem Console Support varnames
 *		which are system specific:
 *		==========================
 *	 	com1_baud,	com1_modem, 	com1_flow,
 *	 	com1_misc,	com2_baud, 	com2_modem,
 *	 	com2_flow,	com2_misc
 *
 *		Bird only? system specific scsi varnames
 *		========================================
 *		scsiid, 	scsifast
 *
 *
 *	char *value
 *		the value of the environment variable specified
 *		by varname.  This is the output.
 *
 *	int flags 
 *		This interface should be called with the PROM_VERIFY
 *		flag when:
 *
 *			an environment variable is being used
 *			for the first time.
 *
 *			an environment variable is already being
 *			used with the PROM_VERIFY flag set.
 *
 *		Otherwise, this interface should be called with
 *		flags set to PROM_NOVERIFY
 *
 *		All com variables and any new vriables which 
 *		are not explicitly defined in the SRM must be
 *		called with the flag field set to PROM_VERIFY.
 *
 *
 * Return status:
 *	
 * 	GET_ENV_SUCCESS 
 *
 *		indicates the value of the variable returned 
 *		is accurate.
 *
 * 	GET_ENV_TRUNC 
 *
 *		indicates the variable returned is truncated.
 *
 *	GET_ENV_FAILURE
 *
 *		indicates the variable being requested is not 
 *		recognized by the console.
 */
extern int prom_getenv(char *varname, char *value, int flags);

extern void prom_get_fwevdb_entry();

#define PROM_SUCCESS (int)1
#define PROM_FAILURE (int)0

/* Validation bits dedicated to ev functions */
#define CON_EV_SAVEENV 0xFF
#define CON_EV_CLRENV  0xFE

/* flags used by prom_getenv, setenv, and saveenv */
#define PROM_CONVERT_TYPE  (long)(1<<2)

/* console environment variables should be one of the following types */
#define EV_STRING_T  (long)(1 << 0)
#define EV_BOOT_T    (long)(1 << 1)
#define EV_INT_T     (long)(1 << 2)
#define EV_TYPE_MASK (long)0x7

/* action requests used by PROM_PSWTCH */
#define	PSWTCH_FROM_PRIMARY	1
#define	PSWTCH_TO_PRIMARY	2
#define	PSWTCH_SWITCH_PRIMARY	3

#define FWDBFNAME "/etc/fwevdb"

/* Record type for the table describing the console EVs */
typedef struct {
   char name[32];    /* name of the console variable */
   int  num;         /* number used to access variable */
   int  flags;       /* content info, etc. */
}evinfo_t;

/* Get the family, processor type and smm value for this system */
extern void get_fam_cpu_smm(long *fam, long *proc, long *smm, long flags);
#define CPU_BY_FAMILY 1 << 0  /* flag used to get proc base type (EV56=EV5) */

typedef struct{
   ushort_t from;
   ushort_t to;
}smmrange_t;

/* record type for firmware ev database */
typedef struct{
   uchar_t   fam;            /* platform */
   uchar_t   proc;
   smmrange_t smm[5];
   uchar_t   maj;            /* firmware rev */
   uchar_t   min;
   ushort_t  var;
   ulong_t   bits[4];        /* 256 bits for fw ev bugs */
}fwentry_t;

struct fw_ev_support {
	int firmware_major;
	int firmware_minor;
	int firmware_variation;

	u_long srm_evs;
	u_long console_evs;
	u_long system_sw_evs_1;
	u_long system_sw_evs_2;
};

/*
 * This structure is used to create a static array
 * of console variable names for scsi3 boot devices.
 */
typedef struct environment_variable_names {
        struct {
            char       at[1];           /* "@"+wwid = suffix            */
            char     wwid[6];           /* var name containing wwid     */
        } suffix;                       /* Boot device string suffix    */
        char     portname[3];           /* var name containing portname */
} ENV_VAR_NAME;

/*
 * int prom_fw_ev_support_check(struct fw_ev_support ev_support[], int ev_num)
 *
 * synopsis:
 *
 *	Function determines whether an environment variable represented by
 *	parameter ev_num is supported safely by a certain rev of fw.  The
 *	fw rev information and the EVs supported by that firmware rev are
 *	provided by the hal in the null terminated fw_ev_support structure array.
 *
 *	Assumption is that firmware support of EVs will never be taken away when
 *	firmware revision is increased.
 *	
 *
 * parameters
 *
 *	struct fw_ev_support ev_support[]
 *
 *		A Null terminated array of structures.  Each stucture
 *		represents a distinct firmware rev and a set of
 *		of new console environment variable functionality associated 
 *		with it.  The first three int elements of the structure represent
 *		the fw rev major, minor, and variation number.
 *
 *		Null termination of the array means that ALL of the fields must
 *		be 0.
 *
 *		The remaining four elements are each 64 bit bitfields representing
 *		the possible EVs supported.
 *		The fourth field represents console EVs 0-0x3f, the SRM defined EVs
 *		The fifth field represents console EVs 0x40-0x7f, the console EVs
 *		The sixth and seventh fields represent the system software EVs
 *		with the sixth field being 0x80-0xbf and the seventh being 0xcf -0xff.
 *
 *
 *	int ev_num
 *
 *		the SRM architected integer specifying a console environment variable.
 *
 * return status
 *
 *	PROM_SUCCESS (int)1
 *	PROM_FAILURE (int)0
 */
extern int prom_fw_ev_support_check(struct fw_ev_support ev_support[], int ev_num);

#define PROM_SUCCESS (int)1
#define PROM_FAILURE (int)0

/*
 * defines for bit fields indicating firmware support of new environment
 * variable functionality. Used in hal fw_ev_support stuctures to indicate
 * support of an EV by a console.
 */

#define CON_EV_AUTO_ACTION	(1L << 1)
#define CON_EV_BOOT_DEV		(1L << 2)
#define CON_EV_BOOTDEF_DEV	(1L << 3)
#define CON_EV_BOOTED_DEV	(1L << 4)
#define CON_EV_BOOT_FILE	(1L << 5)
#define CON_EV_BOOTED_FILE	(1L << 6)
#define CON_EV_BOOT_OSFLAGS	(1L << 7)
#define CON_EV_BOOTED_OSFLAGS	(1L << 8)
#define CON_EV_BOOT_RESET	(1L << 9)
#define CON_EV_DUMP_DEV		(1L << A)
#define CON_EV_ENABLE_AUDIT	(1L << B)
#define CON_EV_LICENSE		(1L << C)
#define CON_EV_CHAR_SET		(1L << D)
#define CON_EV_LANGUAGE		(1L << E)
#define CON_EV_TTY_DEV		(1L << F)

#define CON_EV_COM1_BAUD	(1L << (68 % 64))
#define CON_EV_COM1_MODEM	(1L << (69 % 64))
#define CON_EV_COM1_FLOW	(1L << (70 % 64))
#define CON_EV_COM1_MISC	(1L << (71 % 64))
#define CON_EV_COM2_BAUD	(1L << (72 % 64))
#define CON_EV_COM2_MODEM	(1L << (73 % 64))
#define CON_EV_COM2_FLOW	(1L << (74 % 64))
#define CON_EV_COM2_MISC	(1L << (75 % 64))

/*
 * BIOS emmulation console callback support
 *
 */

/*
 *  Intel BIOS callback support
 *
 *  This ioctl will take a pointer to X86 register format 
 *  and from the kernel invoke the SRM console firmware
 *  to do emmulation of a BIOS interrupt call.  This is
 *  intended for the purpose of setting graphics modes
 *  on commidity graphics cards for the WS subsystem.
 *
 *  USAGE WARNINGS: (1) This call results in a prom callback
 *                      done at high IPL.  While it is safe
 *                      to make a single call without detrimental
 *                      affects, it should not be used as a tool
 *                      for general purpose BIOS programming.
 *
 *                  (2) To ensure integrity, the register structure
 *                      passed to the call should always be zeroed
 *                      before setting up registers for a call.
 * 
 */

/*
 *  Intel data register format
 *
 *  Need register structure to specify what
 *  register format BIOS interrupt call
 *  will be using.  X86 data regiters
 *  can have 2 formats:
 *
 *         AX      - single 16 bit register
 *          or
 *         AH/AL   - two 8 bit registers
 *
 *  The macros below should be used to ensure
 *  that the structures are properly initialized
 *  and set.
 */
typedef struct 
  {
    short word_flag;  /* if set, indicates use word format, e.g. AX */
    union {
	struct {     /* 2 byte (Low, High) version */
	  u_char L;
	  u_char H;
	} b;
	struct {     /* word version */
	  u_short X;
	} w;
      } reg;
  } IX86_REG ;


#define BIOS_WRITE_X(X86_REG,v) {X86_REG.word_flag=1;X86_REG.reg.w.X = v;}
#define BIOS_WRITE_H(X86_REG,v) {X86_REG.word_flag=0;X86_REG.reg.b.H = v;}
#define BIOS_WRITE_L(X86_REG,v) {X86_REG.word_flag=0;X86_REG.reg.b.L = v;}

/*
 *  When reading register information returned by a BIOS call,
 *  the interface can only return the 16 bit X version of the data
 *  registers.  It is BIOS call dependent whether or not X or H/L are
 *  used, so the caller must take the X value and split it into H and L
 *  if they are needed for the specific call.
 */
#define BIOS_READ_X(X86_REG) X86_REG.reg.w.X 


typedef struct X86_REGISTERS
{
  /* Data regiters used in BIOS instructions */

  IX86_REG  A;     /* Accumulater*/
  IX86_REG  B;     /* Base*/
  IX86_REG  C;     /* Count*/
  IX86_REG  D;     /* Data*/

  /* Following are not currently used by SRM bios callback */

  u_short SP;     /* stack pointer */
  u_short BP;     /* base pointer */
  u_short SI;     /* source index */
  u_short DI;     /* dest index */
  u_short CS;     /* code segment */
  u_short DS;     /* data segment */
  u_short SS;     /* stack segment */
  u_short ES;     /* extra segment */
  u_short flags;  /* flags reg */
  u_short IP;     /* instruction pointer */
  u_int pad1;     /* reserved */
} prom_x86_regs;

extern int prom_bios(u_int int86, prom_x86_regs * regs, 
	            u_long data1, u_long data2);		


#if defined(_KERNEL) && defined(_USE_KERNEL_PROTOS)

extern int prom_verify(int id, int flags);
extern void prom_save_env_timeout(void);
extern int match_var_name(char *varname);
extern int prom_srm_ev(char *varname);
extern u_char prom_getc(void);
extern int prom_clearenv(char *varname);
extern int prom_close(int channel);
extern int prom_write(int channel, char *buffer, int count, int block);
extern void prom_puts(u_char *string);
extern int prom_open(char *devstr);
extern int prom_read(int channel, int count, char *buffer, int block);
extern void prom_init(void);
extern ulong_t
	prom_dispatcher(ulong_t, ulong_t, ulong_t, ulong_t, ulong_t, ulong_t,
	...);
extern long prom_power(ulong, int, int);
extern long prom_power_on(ulong ctft_id, unsigned int change_counter);
extern long prom_power_off(ulong ctft_id, unsigned int change_counter);
extern long prom_update_tree(void);
extern long prom_read_lock(u_long, u_int);
extern long prom_read_unlock(u_long);
extern long prom_set_node_flags(u_long, int, u_long, int);
extern long prom_clear_node_flags(u_long, int, u_long, int);
extern long prom_update_os_usage(u_long, u_long, u_int, int);
extern long prom_find_partition(u_long, u_long*, u_long*, u_long*, u_long*);
extern long prom_assign_hw(ulong ctft_id, ulong new_owner, ulong new_current_owner, 
			   uint flags, int node_change_ctr);
extern long prom_update_partial_tree(ulong);

#endif /* defined(_KERNEL) && defined(_USE_KERNEL_PROTOS) */

#endif /* __cplusplus */

 
#endif /* __PROM_INCLUDE__ */
