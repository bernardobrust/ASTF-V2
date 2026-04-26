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

astf2 offers a very minimal and easy to use testing infrastructure.

***

## Tutorial (if you may call it that)

Copy the "astf2.h" header to the location you put your projects libraries and
include it where you want to test.

Create a ```void``` function with the name of your test suite.

Then, add ```astf_start_test_suite("Suite name");``` at the top of the function
with the name of your test suite as the argument, and 
```astf_retrieve_results();``` at the end to get the results.

In between, add ```astf_...()``` with the assert type.
a.k.a ```astf_assert_equal(actual, expected)```.

More examples available at src/tests.c
