## @file
# Mde DSC include file for [BuildOptions*] section of all Architectures.
#
# This file can be included to a platform DSC file by using
# "!include MdePkg/MdeBuildOptions.dsc.inc" to specify common build options.
#
# Copyright (c) 2021, Marvin Häuser. All rights reserved.<BR>
#
#    SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

#
# MDEPKG_NDEBUG_RELEASE:
#   Disable any debug code in RELEASE builds.
#
# MDEPKG_DISABLE_NEW_DEPRECATED_INTERFACES:
#   Disable newly deprecated interfaces.
#
# MDEPKG_PROTECT_BT_IMAGES:
#   Align boot-time images at a 4 KB boundary to support page-level protection.
#
# MDEPKG_PROTECT_RT_IMAGES:
#   Align runtime images at a 4 KB boundary to support page-level protection.
#
# MDEPKG_PROTECT_RT_IMAGES_AARCH64_16K:
#   Align runtime images at a 16 KB boundary for the AARCH64 architecture to
#   support page-level protection for Operating Systems with 64 KB page tables.
#

#
# Define generic MdePkg macros.
#

!if $(MDEPKG_NDEBUG_RELEASE)
  [BuildOptions]
    MSFT:RELEASE_*_*_CC_FLAGS     = /D MDEPKG_NDEBUG
    INTEL:RELEASE_*_*_CC_FLAGS    = /D MDEPKG_NDEBUG
    CLANGPDB:RELEASE_*_*_CC_FLAGS = -DMDEPKG_NDEBUG
    GCC:RELEASE_*_*_CC_FLAGS      = -DMDEPKG_NDEBUG
    XCODE:RELEASE_*_*_CC_FLAGS    = -DMDEPKG_NDEBUG
    RVCT:RELEASE_*_*_CC_FLAGS     = -DMDEPKG_NDEBUG
!endif

!if $(MDEPKG_DISABLE_NEW_DEPRECATED_INTERFACES)
  [BuildOptions]
    MSFT:*_*_*_CC_FLAGS     = /D DISABLE_NEW_DEPRECATED_INTERFACES
    INTEL:*_*_*_CC_FLAGS    = /D DISABLE_NEW_DEPRECATED_INTERFACES
    CLANGPDB:*_*_*_CC_FLAGS = -DDISABLE_NEW_DEPRECATED_INTERFACES
    GCC:*_*_*_CC_FLAGS      = -DDISABLE_NEW_DEPRECATED_INTERFACES
    XCODE:*_*_*_CC_FLAGS    = -DDISABLE_NEW_DEPRECATED_INTERFACES
    RVCT:*_*_*_CC_FLAGS     = -DDISABLE_NEW_DEPRECATED_INTERFACES
!endif

#
# Force PE/COFF sections to be aligned at architectural boundaries to support
# page level protection.
#

!if $(MDEPKG_PROTECT_BT_IMAGES) == TRUE
  [BuildOptions]
    MSFT:*_*_*_DLINK_FLAGS     = /ALIGN:4096
    INTEL:*_*_*_DLINK_FLAGS    = /ALIGN:4096
    CLANGPDB:*_*_*_DLINK_FLAGS = /ALIGN:4096
    GCC:*_*_*_DLINK_FLAGS      = -z common-page-size=0x1000 -z max-page-size=0x1000
    XCODE:*_*_*_DLINK_FLAGS    = -seg1addr 0x1000 -segalign 0x1000
    XCODE:*_*_*_MTOC_FLAGS     = -align 0x1000
    RVCT:*_*_*_DLINK_FLAGS     = --scatter $(EDK_TOOLS_PATH)/Scripts/Rvct-Align4K.sct
!endif

!if $(MDEPKG_PROTECT_RT_IMAGES) == TRUE
  [BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER, BuildOptions.common.EDKII.SMM_CORE, BuildOptions.common.EDKII.DXE_SMM_DRIVER, BuildOptions.common.MM_CORE_STANDALONE, BuildOptions.common.MM_STANDALONE]
    MSFT:*_*_*_DLINK_FLAGS     = /ALIGN:4096
    INTEL:*_*_*_DLINK_FLAGS    = /ALIGN:4096
    CLANGPDB:*_*_*_DLINK_FLAGS = /ALIGN:4096
    GCC:*_*_*_DLINK_FLAGS      = -z common-page-size=0x1000 -z max-page-size=0x1000
    XCODE:*_*_*_DLINK_FLAGS    = -seg1addr 0x1000 -segalign 0x1000
    XCODE:*_*_*_MTOC_FLAGS     = -align 0x1000
    RVCT:*_*_*_DLINK_FLAGS     = --scatter $(EDK_TOOLS_PATH)/Scripts/Rvct-Align4K.sct
!endif

!if $(MDEPKG_PROTECT_RT_IMAGES_AARCH64_16K) == TRUE
  [BuildOptions.common.EDKII.DXE_RUNTIME_DRIVER, BuildOptions.common.EDKII.SMM_CORE, BuildOptions.common.EDKII.DXE_SMM_DRIVER, BuildOptions.common.MM_CORE_STANDALONE, BuildOptions.common.MM_STANDALONE]
    MSFT:*_*_AARCH64_DLINK_FLAGS     = /ALIGN:65536
    INTEL:*_*_AARCH64_DLINK_FLAGS    = /ALIGN:65536
    CLANGPDB:*_*_AARCH64_DLINK_FLAGS = /ALIGN:65536
    GCC:*_*_AARCH64_DLINK_FLAGS      = -z common-page-size=0x10000 -z max-page-size=0x10000
    XCODE:*_*_AARCH64_DLINK_FLAGS    = -seg1addr 0x10000 -segalign 0x10000
    XCODE:*_*_AARCH64_MTOC_FLAGS     = -align 0x10000
!endif

!if $(MDEPKG_MERGE_RODATA_INTO_TEXT) == TRUE
  [BuildOptions]
    # FIXME: How does ICC work?
    MSFT:*_*_*_DLINK_FLAGS       = /MERGE:.rdata=.text
    CLANGPDB:*_*_*_DLINK_FLAGS   = /MERGE:.rdata=.text
    # GCC:*_*_IA32_DLINK2_FLAGS    = -Wl,--defsym=PECOFF_HEADER_SIZE=0x220
    # GCC:*_*_X64_DLINK2_FLAGS     = -Wl,--defsym=PECOFF_HEADER_SIZE=0x228
    # GCC:*_*_ARM_DLINK2_FLAGS     = -Wl,--defsym=PECOFF_HEADER_SIZE=0x220
    # GCC:*_*_AARCH64_DLINK2_FLAGS = -Wl,--defsym=PECOFF_HEADER_SIZE=0x228
    # GCC:*_*_RISCV_DLINK2_FLAGS   = -Wl,--defsym=PECOFF_HEADER_SIZE=0x220
    GCC:*_GCC5_*_DLINK2_FLAGS    = -Wl,--script=$(EDK_TOOLS_PATH)/Scripts/GccMergeRdataIntoText.lds
    GCC:*_CLANG38_*_DLINK2_FLAGS = -Wl,--script=$(EDK_TOOLS_PATH)/Scripts/ClangMergeRdataIntoText.lds
    XCODE:*_*_*_DLINK_FLAGS      = -seg1addr 0x240 -rename_section __DATA_CONST __text_const __TEXT __const -rename_section __DATA_CONST __cstring __TEXT __cstring -rename_section __DATA_CONST __ustring __TEXT __ustring -rename_section __DATA_CONST __const __TEXT __data_const
    XCODE:*_*_*_ASLDLINK_FLAGS   = -seg1addr 0x240
!endif
