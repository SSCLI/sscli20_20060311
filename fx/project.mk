# ==++==
#
#   Copyright (c) Microsoft Corporation.  All rights reserved.
#
# ==--==

!include $(NDPDIR)\ndpmk.inc
NDPFX_ROOT=$(NDPDIR)\fx

URTTARGET=$(_NTTREE)

USE_PDB_TO_COMPILE=1

NDPFX_LIB_DEST=$(NDPFX_ROOT)\lib\$(_BUILDTYPE)
NDPFX_LIB_PATH=$(NDPFX_LIB_DEST)\$(TARGET_DIRECTORY)

NDPFX_TLB_DEST=$(NDPFX_ROOT)\tlb\$(_BUILDTYPE)
NDPFX_TLB_PATH=$(NDPFX_LIB_DEST)\$(TARGET_DIRECTORY)

NDPFX_REF_PATH=$(NDP_REF_PATH)
NDPFX_REF_PUBLISH={$(O)\$(TARGETNAME).$(TARGETEXT)=$(NDPFX_REF_PATH)\$(TARGETNAME).$(TARGETEXT)}

# necessary for VSDesigner menu resources
CTC_INCLUDES=$(VSCOMMON_INC_PATH);$(VSEXTERNAL_INC_PATH)\office10

PROJECT_COMPILER_WARNINGS=-FI$(NDPFX_ROOT)\src\inc\warning.h

