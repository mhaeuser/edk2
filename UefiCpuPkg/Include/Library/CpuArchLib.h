/** @file
  CPU DXE Module to produce CPU ARCH Protocol.

  Copyright (c) 2008 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _CPU_ARCH_LIB_H_
#define _CPU_ARCH_LIB_H_

/**
  Initialize the state information for the CPU Architectural Protocol.

  @param ImageHandle     Image handle this driver.
  @param SystemTable     Pointer to the System Table.

  @retval EFI_SUCCESS           Thread can be successfully created
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Cannot create the thread

**/
EFI_STATUS
InitializeCpu (
  VOID
  );

#endif // _CPU_ARCH_LIB_H_
