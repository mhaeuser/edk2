/** @file

  Unified linker script for GCC and CLANG based build .rdata sections

  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2015, Linaro Ltd. All rights reserved.<BR>
  (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

  *(.rodata .rodata.* .data.rel.ro .data.rel.ro.* .gnu.linkonce.r.*)
  *(.got .got.*)

  /*
    * The contents of AutoGen.c files are mostly constant from the POV of the
    * program, but most of it ends up in .data or .bss by default since few of
    * the variable definitions that get emitted are declared as CONST.
    * Unfortunately, we cannot pull it into the .text section entirely, since
    * patchable PCDs are also emitted here, but we can at least move all of the
    * emitted GUIDs here.
    */
  *:AutoGen.obj(.data.g*Guid)
