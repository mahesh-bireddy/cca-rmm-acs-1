/*
 * Copyright (c) 2023, Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _VAL_ARCH_H_
#define _VAL_ARCH_H_

#define EL2 2
#define EL1 1

#define SCTLR_I_BIT         (1 << 12)
#define SCTLR_M_BIT         (1 << 0)

#define INPLACE(regfield, val) \
    (((val) + 0ul) << (regfield##_SHIFT))

#define MASK(regfield) \
    ((~0UL >> (64UL - (regfield##_WIDTH))) << (regfield##_SHIFT))

#define EXTRACT(regfield, reg) \
    (((reg) & MASK(regfield)) >> (regfield##_SHIFT))

#define EXTRACT_BIT(regfield, reg) \
    (((reg) >> (regfield##_SHIFT)) & 1ul)

#define ESR_EL2_EC_SHIFT    26
#define ESR_EL2_EC_WIDTH    6
#define ESR_EL2_EC_MASK        MASK(ESR_EL2_EC)
#define ESR_EL2_IL_SHIFT    25
#define ESR_EL2_IL_WIDTH    1
#define ESR_EL2_IL_MASK        MASK(ESR_EL2_EC)

#define ESR_EL2_ISS_SHIFT 0
#define ESR_EL2_ISS_WIDTH 25
#define ESR_EL2_ISS_MASK  MASK(ESR_EL2_ISS)

#define ESR_EL2_EC_WFX        INPLACE(ESR_EL2_EC, 1)
#define ESR_EL2_EC_SVC        INPLACE(ESR_EL2_EC, 21)
#define ESR_EL2_EC_HVC        INPLACE(ESR_EL2_EC, 22)
#define ESR_EL2_EC_SMC        INPLACE(ESR_EL2_EC, 23)
#define ESR_EL2_EC_SYSREG    INPLACE(ESR_EL2_EC, 24)
#define ESR_EL2_EC_INST_ABORT    INPLACE(ESR_EL2_EC, 32)
#define ESR_EL2_EC_DATA_ABORT    INPLACE(ESR_EL2_EC, 36)
#define ESR_EL2_EC_DATA_ABORT_SEL    INPLACE(ESR_EL2_EC, 37)
#define ESR_EL2_EC_FPU        INPLACE(ESR_EL2_EC, 0x7)


/* Data/Instruction Abort ESR fields */
#define ESR_EL2_ABORT_ISV_BIT        (1UL << 24)

#define ESR_EL2_ABORT_SAS_SHIFT        22
#define ESR_EL2_ABORT_SAS_WIDTH        2
#define ESR_EL2_ABORT_SAS_MASK        MASK(ESR_EL2_ABORT_SAS)

#define ESR_EL2_ABORT_SAS_BYTE_VAL    0
#define ESR_EL2_ABORT_SAS_HWORD_VAL    1
#define ESR_EL2_ABORT_SAS_WORD_VAL    2
#define ESR_EL2_ABORT_SAS_DWORD_VAL    3

#define ESR_EL2_ABORT_SSE_BIT        (1UL << 21)

#define ESR_EL2_ABORT_SRT_SHIFT        16
#define ESR_EL2_ABORT_SRT_WIDTH        5
#define ESR_EL2_ABORT_SRT_MASK        MASK(ESR_EL2_ABORT_SRT)

#define ESR_EL2_ABORT_SF_BIT        (1UL << 15)
#define ESR_EL2_ABORT_FNV_BIT        (1UL << 10)
#define ESR_EL2_ABORT_WNR_BIT        (1UL << 6)
#define ESR_EL2_ABORT_FSC_SHIFT        0
#define ESR_EL2_ABORT_FSC_WIDTH        6
#define ESR_EL2_ABORT_FSC_MASK        MASK(ESR_EL2_ABORT_FSC)

#define ESR_EL2_ABORT_FSC_TRANSLATION_FAULT    0x04
#define ESR_EL2_ABORT_FSC_PERMISSION_FAULT    0x0c
#define ESR_EL2_ABORT_FSC_LEVEL_SHIFT        0
#define ESR_EL2_ABORT_FSC_LEVEL_WIDTH        2
#define ESR_EL2_ABORT_FSC_LEVEL_MASK        MASK(ESR_EL2_ABORT_FSC_LEVEL)
#define ESR_EL2_ABORT_FSC_GPF            0x28

#define ESR_EL2_SYSREG_TRAP_OP0_SHIFT    20
#define ESR_EL2_SYSREG_TRAP_OP0_WIDTH    2
#define ESR_EL2_SYSREG_TRAP_OP0_MASK    MASK(ESR_EL2_SYSREG_TRAP_OP0)

#define ESR_EL2_SYSREG_TRAP_OP2_SHIFT    17
#define ESR_EL2_SYSREG_TRAP_OP2_WIDTH    3
#define ESR_EL2_SYSREG_TRAP_OP2_MASK    MASK(ESR_EL2_SYSREG_TRAP_OP2)

#define ESR_EL2_SYSREG_TRAP_OP1_SHIFT    14
#define ESR_EL2_SYSREG_TRAP_OP1_WIDTH    3
#define ESR_EL2_SYSREG_TRAP_OP1_MASK    MASK(ESR_EL2_SYSREG_TRAP_OP1)

#define ESR_EL2_SYSREG_TRAP_CRN_SHIFT    10
#define ESR_EL2_SYSREG_TRAP_CRN_WIDTH    4
#define ESR_EL2_SYSREG_TRAP_CRN_MASK    MASK(ESR_EL2_SYSREG_TRAP_CRN)

#define ESR_EL2_SYSREG_TRAP_RT_SHIFT    5
#define ESR_EL2_SYSREG_TRAP_RT_WIDTH    5
#define ESR_EL2_SYSREG_TRAP_RT_MASK    MASK(ESR_EL2_SYSREG_TRAP_RT)

#define ESR_EL2_SYSREG_TRAP_CRM_SHIFT    1
#define ESR_EL2_SYSREG_TRAP_CRM_WIDTH    4
#define ESR_EL2_SYSREG_TRAP_CRM_MASK    MASK(ESR_EL2_SYSREG_TRAP_CRM)

/* WFx ESR fields */
#define ESR_EL2_WFx_TI_BIT        (1UL << 0)

/* xVC ESR fields */
#define ESR_EL2_xVC_IMM_SHIFT        0
#define ESR_EL2_xVC_IMM_WIDTH        16
#define ESR_EL2_xVC_IMM_MASK        MASK(ESR_EL2_xVC_IMM)
#endif /* _VAL_ARCH_H_ */
