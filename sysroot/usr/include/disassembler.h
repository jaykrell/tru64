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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/disassembler.h,v 1.1.6.4 1998/08/18 20:45:40 John_P_Williams Exp $ */

#ifndef _ALPHA_DISASSEMBLER_H_
#define _ALPHA_DISASSEMBLER_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Disassembler package */

#include <standards.h>

/* Three sets of register names which people might want to use:
  compiler: zero, at, v0, ...
  hardware: r0, r1, r2, ...
  assembler: $0, $at, $2,...
*/
#define COMPILER_NAMES dis_reg_names[0]
#define HARDWARE_NAMES dis_reg_names[1]
#define ASSEMBLER_NAMES dis_reg_names[2]

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

extern char *dis_reg_names[3][32];

/* Initialize disassembler and set options for disassembly.

  "addr_format" and "value_format" specify in the style of "printf" the
  null-terminated formats for printing the address and value of the
  instruction. If nil, they default to "%#010x\t"; if they are the empty
  string, we omit to print these items.

  "reg_names" is a pointer to an array of 32 strings which we will use to
  represent the general-purpose registers. The *_NAMES macros above give
  three common choices; if nil, we use compiler names.

  print_jal_targets tells us whether to print the targets of jal
  instructions numerically.
*/

extern void dis_init __(( 
             char   *addr_format,
             char   *value_format,
             char   *reg_names[],
             int     print_jal_targets ));

/* Given a null-terminated buffer (presumably from "disasm"), we append an
  ascii representation of register values in the form "\t<$5=0x50,$7=0x44,...>".
  "regmask" is a bitmask of registers as in "disasm", "reg_values" an array
  (with empty slots for the registers not indicated in the mask) of their
  values */

extern void dis_regs __(( 
             char         *buffer,
             unsigned      regmask,
             unsigned long reg_values[] ));

/* Disassemble instruction, putting null-terminated result into "buffer"
  (no trailing newline). Details governed by "dis_init".
  buffer: array of characters allocated by the caller; 64 bytes should be
    more than enough.
  address: byte address
  iword: the instruction
  regmask: returns a bitmask of the gp registers the instruction uses,
    with the LSB indicating register 0 regardless of endianness.
  symbol_value: for a jal instruction, the target value; for a load or
    store, the immediate value
  ls_register: for a load or store, the number of the base register
  return value: -1 for a load or store, 1 for a jal, 2 for a j, jr, jalr,
    or branch, 0 for others
*/

extern int disasm __(( 
              char       	*buffer,
              unsigned long  	 address,
              unsigned   	 iword,
              unsigned   	*regmask,
              unsigned long	 *symbol_value,
              unsigned   	*ls_register   ));

/* Older interface, which always prints on stdout */

extern int disassembler __(( 
                  unsigned long    iadr,
                  int              regstyle,
                  char            *(*get_symname)(unsigned long),
                  unsigned long    (*get_regvalue)(unsigned),
                  unsigned         (*get_bytes)(void),
                  void             (*print_header)(unsigned long, unsigned)));

#endif
#ifdef __LANGUAGE_PASCAL__

type
  charptr = ^char;
  char32ptr = packed array [0 .. 31] of charptr;
  card32array = array [0 .. 31] of cardinal;

var
  dis_reg_names: packed array [0 .. 2] of char32ptr;

{ In the presence of optimization, use of "charptr" instead of a pointer to
  an entire array may be dangerous, but we don't want to impose a particular
  fixed array size.  To be safe, pass your entire array by reference
  to a dummy routine so the optimizer thinks it's being used. }
procedure dis_init(addr_format: charptr;
  value_format: charptr;
  var reg_names: char32ptr;
  print_jal_targets: integer { nonzero => true }
  ); external;

procedure dis_regs(buffer: charptr; regmask: cardinal; reg_values: card32array);
  external;

function disasm(buffer: charptr;
  address, iword: cardinal;
  var regmask, symbol_value, ls_register: cardinal
  ): integer; { nonzero => true }
  external;

#endif

#ifdef __cplusplus
}
#endif
#endif  /* _ALPHA_DISASSEMBLER_H_ */
