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

#include <math.h>
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

// The user can define their own EPSILON, defaltts to 1e-6
#ifndef ASTF_EPSILON
#define ASTF_EPSILON 0.000001
#endif

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

#define astf_assert_equal(expected, actual)                                    \
    _Generic((expected),                                                       \
        int: _astf_ae_int,                                                     \
        unsigned int: _astf_ae_unsigned,                                       \
        unsigned short: _astf_ae_unsigned_short,                               \
        long: _astf_ae_long,                                                   \
        unsigned long: _astf_ae_ulong,                                         \
        char *: _astf_ae_str,                                                  \
        const char *: _astf_ae_str,                                            \
        default: _astf_ae_ptr)(expected, actual, __FILE__, __LINE__)

#define astf_assert_approx(expected, actual, epsilon)                          \
    _Generic((expected), float: _astf_ae_float, double: _astf_ae_double)(      \
        expected, actual, epsilon, __FILE__, __LINE__)

#define astf_assert_null(pointer) astf_assert_equal(NULL, pointer)
#define astf_assert_not_null(pointer)                                          \
    _astf_assert_not_null(pointer, __FILE__, __LINE__)

#ifdef ASTF_IMPLEMENTATION
astf_ctx _astf_global_ctx = {0};

void astf_start_test_suite(const char *name) {
    _astf_global_ctx.test_suite_name = name;
    _astf_global_ctx.passed = 0;
    _astf_global_ctx.failed = 0;
    printf(astf_output_info "\n--- Starting Suite: %s ---\n", name);
}

// Assert equals
// -----------------------------------------------------------------------------
void _astf_ae_int(int exp, int act, const char *file, int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %d but got %d\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_unsigned(unsigned exp, unsigned act, const char *file, int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %u but got %u\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_unsigned_short(unsigned short exp, unsigned short act,
                             const char *file, int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %hu but got %hu\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_long(long exp, long act, const char *file, int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %ld but got %ld\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_ulong(unsigned long exp, unsigned long act, const char *file,
                    int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %lu but got %lu\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_str(const char *exp, const char *act, const char *file,
                  int line) {
    if (exp && act && strcmp(exp, act) == 0)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected \"%s\" but got \"%s\"\n\n",
               file, line, exp ? exp : "NULL", act ? act : "NULL");
        _astf_global_ctx.failed++;
    }
}

// Floating point types (using Epsilon)
void _astf_ae_double(double exp, double act, double eps, const char *file,
                     int line) {
    if (fabs(exp - act) < eps)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %f but got %f (Epsilon: %f)\n\n",
               file, line, exp, act, (double)ASTF_EPSILON);
        _astf_global_ctx.failed++;
    }
}

void _astf_ae_float(float exp, float act, float eps, const char *file,
                    int line) {
    if (fabsf(exp - act) < eps)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected %f but got %f (Epsilon: %f)\n\n",
               file, line, (double)exp, (double)act, (double)ASTF_EPSILON);
        _astf_global_ctx.failed++;
    }
}

// Pointers
void _astf_ae_ptr(const void *exp, const void *act, const char *file,
                  int line) {
    if (exp == act)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail "[FAILED] %s: %d\n" astf_output_warn
                                "Expected pointer %p but got %p\n\n",
               file, line, exp, act);
        _astf_global_ctx.failed++;
    }
}

void _astf_assert_not_null(const void *ptr, const char *file, int line) {
    if (ptr != NULL)
        _astf_global_ctx.passed++;
    else {
        printf(astf_output_fail
               "[FAILED] %s: %d\n" astf_output_warn
               "Expected pointer to not be null, but it is\n\n",
               file, line);
        _astf_global_ctx.failed++;
    }
}

// -----------------------------------------------------------------------------

// Get results
void astf_retrieve_results(void) {
    printf(astf_output_info "\n--- Results for %s ---\n",
           _astf_global_ctx.test_suite_name);
    printf(astf_output_pass "Passed: %d\n", _astf_global_ctx.passed);
    printf(astf_output_fail "Failed: %d\n" astf_output_normal,
           _astf_global_ctx.failed);
}
#endif
