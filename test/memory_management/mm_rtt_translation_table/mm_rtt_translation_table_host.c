/*
 * Copyright (c) 2023, Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "test_database.h"
#include "val_host_rmi.h"

#define PROTECTED_IPA 0x20000000

void mm_rtt_translation_table_host(void)
{
    val_host_realm_ts realm;
    val_host_rmifeatureregister0_ts features_0;
    val_host_rtt_entry_ts rtte;
    uint64_t ret;
    uint64_t mmfr0;
    uint32_t level = 2;

    val_memset(&realm, 0, sizeof(realm));
    val_memset(&features_0, 0, sizeof(features_0));
    features_0.s2sz = 40;
    val_memcpy(&realm.realm_feat_0, &features_0, sizeof(features_0));

    realm.hash_algo = RMI_HASH_SHA_256;
    realm.s2_starting_level = 0;
    realm.num_s2_sl_rtts = 1;
    realm.vmid = 0;
    realm.rec_count = 1;


    /* Populate realm with two RECs*/
    if (val_host_realm_setup(&realm, 1))
    {
        LOG(ERROR, "\tRealm setup failed\n", 0, 0);
        val_set_status(RESULT_FAIL(VAL_ERROR_POINT(1)));
        goto destroy_realm;
    }

    mmfr0 = val_id_aa64mmfr0_el1_read();
    /* Check that 4KB granule is supported. */
    if (!((VAL_EXTRACT_BITS(mmfr0, 28, 31) == 0x0) ||
         (VAL_EXTRACT_BITS(mmfr0, 28, 31) == 0x1)))
    {
        LOG(ERROR, "\tPlatform not supported 4KB Granule\n", 0, 0);
        val_set_status(RESULT_FAIL(VAL_ERROR_POINT(8)));
        goto destroy_realm;
    }

    ret = val_host_rmi_rtt_read_entry(realm.rd, PROTECTED_IPA, level, &rtte);
    if (rtte.state == RMI_UNASSIGNED)
    {
        ret = val_host_create_rtt_levels(&realm, PROTECTED_IPA,
                                            (uint32_t)rtte.walk_level, level, PAGE_SIZE);
        if (ret)
        {
            LOG(ERROR, "\tval_host_create_rtt_level failed\n", 0, 0);
            val_set_status(RESULT_FAIL(VAL_ERROR_POINT(8)));
            goto destroy_realm;
        }
    }

    ret = val_host_rmi_rtt_read_entry(realm.rd, (PROTECTED_IPA + 0x200000), level, &rtte);
    if (rtte.state != RMI_UNASSIGNED)
    {
        LOG(ERROR, "\tRTTE state check failed rtte.state %x\n", rtte.state, 0);
        val_set_status(RESULT_FAIL(VAL_ERROR_POINT(8)));
        goto destroy_realm;
    }

    /* Enter REC[0] execution */
    ret = val_host_rmi_rec_enter(realm.rec[0], realm.run[0]);
    if (ret)
    {
        LOG(ERROR, "\tRec enter failed, ret=%x\n", ret, 0);
        val_set_status(RESULT_FAIL(VAL_ERROR_POINT(7)));
        goto destroy_realm;
    } else if (val_host_check_realm_exit_host_call((val_host_rec_run_ts *)realm.run[0]))
    {
        LOG(ERROR, "\tHost call params mismatch\n", 0, 0);
        val_set_status(RESULT_FAIL(VAL_ERROR_POINT(8)));
        goto destroy_realm;
    }

    val_set_status(RESULT_PASS(VAL_SUCCESS));

    /* Free test resources */
destroy_realm:
    return;
}
