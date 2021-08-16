/** @file

  Unified linker script for GCC based builds with standalone .rdata sections

  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2015, Linaro Ltd. All rights reserved.<BR>
  (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

SECTIONS {

  /*
   * The PE/COFF binary consists of DOS and PE/COFF headers, and a sequence of
   * section headers adding up to PECOFF_HEADER_SIZE bytes (which differs
   * between 32-bit and 64-bit builds). The actual start of the .text section
   * will be rounded up based on its actual alignment.
   */
  . = PECOFF_HEADER_SIZE;

  .text : ALIGN(CONSTANT(MAXPAGESIZE)) {
    INCLUDE GnuBaseTextSections.lds.inc
  }

  .rodata : ALIGN(CONSTANT(MAXPAGESIZE)) {
    INCLUDE GnuBaseRdataSections.lds.inc
  }

  INCLUDE GnuBaseCommonSections.lds.inc
  INCLUDE GccDiscardSections.lds.inc
}
