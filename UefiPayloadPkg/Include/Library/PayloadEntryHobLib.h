/** @file
  Extends HobLib to create arbitrary HOBs.

Copyright (c) 2021, Marvin Häuser. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __PAYLOAD_ENTRY_HOB_LIB_H__
#define __PAYLOAD_ENTRY_HOB_LIB_H__

#include <Library/HobLib.h>

/**
  Add a new HOB to the HOB List.

  @param HobType            Type of the new HOB.
  @param HobLength          Length of the new HOB to allocate.

  @return  NULL if there is no space to create a hob.
  @return  The address point to the new created hob.

**/
VOID *
EFIAPI
CreateHob (
  IN  UINT16    HobType,
  IN  UINT16    HobLength
  );

#endif
