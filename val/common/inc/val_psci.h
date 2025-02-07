/*
 * Copyright (c) 2023, Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _VAL_PSCI_H_
#define _VAL_PSCI_H_

#include "val_smc.h"

#define PSCI_CPU_SUSPEND_AARCH64       0xc4000001
#define PSCI_CPU_ON_AARCH64            0xc4000003
#define PSCI_AFFINITY_INFO_AARCH64     0xc4000004
#define PSCI_VERSION                   0x84000000
#define PSCI_CPU_OFF                   0x84000002
#define PSCI_SYSTEM_OFF                0x84000008
#define PSCI_SYSTEM_RESET              0x84000009
#define PSCI_FEATURES                  0x8400000A

#define PSCI_E_SUCCESS              0x0
#define PSCI_E_NOT_SUPPORTED        0xffffffff //-1
#define PSCI_E_INVALID_PARAMS       0xfffffffe //-2
#define PSCI_E_DENIED               0xfffffffd //-3
#define PSCI_E_ALREADY_ON           0xfffffffc //-4
#define PSCI_E_ON_PENDING           0xfffffffb //-5
#define PSCI_E_INTERN_FAIL          0xfffffffa //-6
#define PSCI_E_NOT_PRESENT          0xfffffff9 //-7
#define PSCI_E_DISABLED             0xfffffff8 //-8
#define PSCI_E_INVALID_ADDRESS      0xfffffff7 //-9

uint32_t val_psci_affinity_info(uint64_t target_affinity,
                        uint64_t lower_affinity_level);
uint32_t val_psci_cpu_on(uint64_t target_cpu,
                        uint64_t entry_point_address,
                        uint64_t context_id);
uint32_t val_psci_cpu_off(void);
uint32_t val_psci_cpu_suspend(uint64_t power_state,
                        uint64_t entry_point_address,
                        uint64_t context_id);
uint32_t val_psci_features(uint64_t psci_func_id);
uint32_t val_psci_system_off(void);
uint32_t val_psci_system_reset(void);
#endif /* _VAL_PSCI_H_ */
