// * A simple test framework V2 (astf2)

/*
 * astf.h - A simple C testing framework.
 * Copyright (C) 2026  Bernardo Brust (the adm)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASTF_MAX_TESTS 512
#define ASTF_MAX_MESSAGE_SIZE 512

// Colors
#define astf_output_fail "\x1b[31m"
#define astf_output_pass "\x1b[32m"
#define astf_output_warn "\x1b[33m"
#define astf_output_info "\x1b[36m"
#define astf_output_normal "\x1b[0m"

// Context
typedef struct {
    unsigned passed;
    unsigned failed;
    const char *test_suite_name;
} astf_ctx;

extern astf_ctx _astf_global_ctx;

void astf_start_test_suite(const char *name);
void astf_retrieve_results();

void _astf_ae_int(int exp, int act, const char *file, int line);
void _astf_ae_unsigned(unsigned exp, unsigned act, const char *file, int line);
void _astf_ae_unsigned_short(unsigned short exp, unsigned short act,
                             const char *file, int line);
void _astf_ae_str(const char *exp, const char *act, const char *file, int line);
void _astf_ae_ptr(const void *exp, const void *act, const char *file, int line);

#define astf_AE(expected, actual)                                              \
    _Generic((expected),                                                       \
        int: _astf_ae_int,                                                     \
        unsigned: _astf_ae_unsigned,                                           \
        unsigned short: _astf_ae_unsigned_short,                               \
        char *: _astf_ae_str,                                                  \
        const char *: _astf_ae_str,                                            \
        default: _astf_ae_ptr)(expected, actual, __FILE__, __LINE__)

#ifdef ASTF_IMPLEMENTATION
astf_ctx _astf_global_ctx = {0};

void astf_start_test_suite(const char *name) {
    _astf_global_ctx.test_suite_name = name;
    _astf_global_ctx.passed = 0;
    _astf_global_ctx.failed = 0;
    printf(astf_output_info "\n--- Starting Suite: %s ---\n", name);
}
#endif
