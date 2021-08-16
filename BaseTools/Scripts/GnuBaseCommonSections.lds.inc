/** @file

  Unified linker script for common GCC and CLANG based build sections

  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2015, Linaro Ltd. All rights reserved.<BR>
  (C) Copyright 2016 Hewlett Packard Enterprise Development LP<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

  .data : ALIGN(CONSTANT(MAXPAGESIZE)) {
    *(.data .data.* .gnu.linkonce.d.*)
    *(.bss .bss.*)
  }

  .hii : ALIGN(CONSTANT(MAXPAGESIZE)) {
    KEEP (*(.hii))
  }

  .eh_frame ALIGN(CONSTANT(MAXPAGESIZE)) : {
    KEEP (*(.eh_frame))
  }

  .rela (INFO) : {
    *(.rela .rela.*)
  }

  /*
   * Retain the GNU build id but in a non-allocatable section so GenFw
   * does not copy it into the PE/COFF image.
   */
  .build-id (INFO) : { *(.note.gnu.build-id) }
