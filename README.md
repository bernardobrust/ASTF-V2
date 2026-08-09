# A simple test framework (V2)
## Warning
This is a minimal framework, do not expect production grade testing just with this library, you will need aditional tools for tasks like end-to-end testing or only calling specific tests

## Why?
This project aims to be a simple testing framework for the C programming language, it offers basic testing utilities (suites and asserts) for unit tests

I did this because the other frameworks avaliable are overly comlpex for what a testing framework should to be. Advanced features require software-specific structure and should not be a responsability of the testing tool

## Design
Simplicity over all.

astf2 offers minimal and easy to use testing infrastructure. If you want something more complete, such as running different tests based on CLI arguments for the test executable, I recommend checking out [flag.h](https://github.com/tsoding/flag.h)

## Features
- Single header STB-style. This makes the code easy to use
- Super simple. This makes the code easy to use
- Generic macros. This makes the code easy to use
- Standard C11 with no compiler magic. This makes the code easy to use
- No memory alocations. This makes the code easy to use
- Tiny. This makes the code easy to use

Jokes aside, this means you can just `wget` the header file and do this:
```c
#define ASTF_IMPLEMENTATION
#include "astf.h"

int
main()
{
    astf_start_testing();
    astf_start_group("Math");
    astf_start_test_suite("Math Suite");

    int result = 2 + 2;
    astf_assert_equal(4, result);
    astf_assert_true(result > 0);

    astf_retrieve_results();
    astf_end_group();
    astf_stop_testing();

    return 0;
}
```
and you already have astf working on your project (make sure your include paths are correct)

***

## Tutorial (if you may call it that)
Copy the "astf.h" header to the location you put your projects libraries and include it where you want to test

Create a function with the name of your test suite

Then, add `astf_start_test_suite("Suite name");` at the top of the function with the name of your test suite as the argument, and `astf_retrieve_results();` at the end to get the results

Wrap suites in `astf_start_group("Group name");` and `astf_end_group();`. A group reports fully passed, partially failed, and fully failed suites. Wrap all groups in `astf_start_testing();` and `astf_stop_testing();`; testing results classify groups the same way.

In between, add `astf_assert_...()` with the assert type. a.k.a `astf_assert_equal(expected, actual)`

Note that float functions require an epsilon parameter

If prefixing everything with `astf_` sounds boring and you won't get naming conflicts, use `#define ASTF_STRIP_PREFIX` to remove the need for it

Moreover, ASTF provides colored output using ANISI colors by default, if you don't want it, use `#define ASTF_NO_ANSI_COLORS`

Examples:
- [Basic examples](example_tests.c)
- [Use in Numerical Methods](newton_raphson.c)
- [Convex hull groups](convex_hull.c)

## Quick list
`astf_assert_equal(expected, actual)`: Exactly what it suggests, use for exact data types (a.k.a non-floats)

`astf_assert_approx(expected, actual, epsilon)`: Also obvious, remember to make sure your epsilon fits your data type's range

`astf_assert_cond(expected_bool, condition)`, `astf_assert_true(cond)`, `astf_assert_false(cond)`: Family of boolean asserts, the true and false variants are just aliasses that pass true or false into the expected bool

`astf_assert_null(pointer)`, `astf_assert_not_null(pointer)`: Make sure your pointers actually exist (or not ;-;)

`astf_assert_range(val, min, max)`: Works for all numeric data types
