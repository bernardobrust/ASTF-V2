# A simple test framework (V2)

## Warning

This project was developed in a few days for my personal goals, a version 2 of
my old astf testing framework (which sucked btw).

## Why?

This project aims to be a simple testing framework for C11, it offers basic
testing utilities (suites and asserts) for basic unit testing.

I did this because the other frameworks avaliable looked unecessarily
complicated for what a testing framework is supposed to be.

## Design

Simplicity over all.

astf2 offers a very minimal and easy to use testing infrastructure. If you want
something more complete, such as running different tests based on CLI arguments
for the test executable, I recommend checking out
[flag.h](https://github.com/tsoding/flag.h)

## Features

- Single header STB-style. This makes the code easy to use.
- Super simple. This makes the code easy to use.
- Generic macros. This makes the code easy to use.
- Standard C11 with no compiler magic. This makes the code easy to use.
- No memory alocations. This makes the code easy to use.
- Tiny (<400 lines). This makes the code easy to use.

Jokes aside, this means you can just do this:
```c
#define ASTF_IMPLEMENTATION
#include "astf.h"

int main() {
    astf_start_test_suite("Math Suite");

    int result = 2 + 2;
    astf_assert_equal(4, result);
    astf_assert_true(result > 0);

    astf_retrieve_results();

    return 0;
}
```
and you already have astf working on your project (make sure your include paths
are correct)

## Licensing

GNU Affero General Public License v3 (AGPLv3).
Keep your testing tools free!

***

## Tutorial (if you may call it that)

Copy the "astf.h" header to the location you put your projects libraries and
include it where you want to test.

Create a ```void``` function with the name of your test suite.

Then, add ```astf_start_test_suite("Suite name");``` at the top of the function
with the name of your test suite as the argument, and 
```astf_retrieve_results();``` at the end to get the results.

In between, add ```astf_...()``` with the assert type.
a.k.a ```astf_assert_equal(expected, actual)```.

Note that float functions require an epsilon parameter.

Examples:
- [Basic ones here](example_tests.c) 
- [A more complicated one here](newton_raphsor.c).

## Quick list

```astf_assert_equal(expected, actual)```: Exactly what it suggests, use for
exact data types.

```astf_assert_approx(expected, actual, epsilon)```: Also obvious, remember to
make sure your epsilon fits your data type's range.

```astf_assert_cond(expected_bool, condition)```
```astf_assert_true(cond)```
```astf_assert_false(cond)```: Family of boolean asserts, the true and false
variants are just aliasses that pass true or false into the expected bool.

```astf_assert_null(pointer)```
```astf_assert_not_null(pointer)```: Make sure your pointers actually exist (or
not ;-;).

```astf_assert_range(val, min, max)```: Works for all numeric data types.
