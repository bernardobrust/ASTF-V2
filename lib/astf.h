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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASTF_MAX_TESTS 1000
#define ASTF_MAX_MESSAGE_SIZE 256

// Colors
#define astf_output_fail "\x1b[31m"
#define astf_output_pass "\x1b[32m"
#define astf_output_warn "\x1b[33m"
#define astf_output_info "\x1b[36m"
#define astf_output_normal "\x1b[0m"

#define ASTF_PASSED astf_output_pass "Test passed" astf_output_normal
