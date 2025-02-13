/*
 * Copyright (c) 2023, Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "test_database.h"

#define TEST_FUNC_DATABASE
#define HOST_TEST(x, y)              DUMMY_TEST(x, y)
#define HOST_REALM_TEST(x, y)        DUMMY_TEST(x, y)
#define HOST_SECURE_TEST(x, y)       SECURE_TEST_ONLY(x, y)
#define HOST_REALM_SECURE_TEST(x, y) SECURE_TEST_ONLY(x, y)

/* Secure tests are combined into single image only */
#ifndef TEST_COMBINE
#define TEST_COMBINE
#endif

const test_db_t test_list[] = {
    {"", "", NULL, NULL, NULL},

#include "test_list.h"

};

const uint32_t total_tests = sizeof(test_list)/sizeof(test_list[0]);
