#define ASTF_IMPLEMENTATION
#include "astf.h"

int fib(const int n) {
    int pp = 0, p = 1, next;
    for (int i = 2; i <= n; ++i) {
        next = pp + p;
        pp = p;
        p = next;
    }

    return n == 0 ? pp : p;
}

unsigned fib_unsigned(const unsigned n) {
    unsigned pp = 0, p = 1, next;
    for (unsigned i = 2; i <= n; ++i) {
        next = pp + p;
        pp = p;
        p = next;
    }

    return n == 0 ? pp : p;
}

void test_suite1() {
    astf_start_test_suite("Fib mixed");

    unsigned a = 8, b = 3;

    astf_assert_equal(0, fib(0));
    astf_assert_equal(1, fib(1));
    astf_assert_equal(2, fib(3));
    astf_assert_equal(5, fib(4));
    astf_assert_equal(a, fib_unsigned(4));
    astf_assert_equal(b, fib_unsigned(4));

    astf_retrieve_results();
}

void test_suite2() {
    astf_start_test_suite("Data types");

    unsigned short a = 2, b = 5;
    astf_assert_equal(a, b - 3);

    double x = 1.1111112, y = 1.1111113;
    float w = 3.14f, z = 3.10f;
    astf_assert_approx(x, y, 0.0001);
    astf_assert_approx(w, z, 0.01f);

    const char *name1 = "Chad C user", *name2 = "Loser Rust user";
    astf_assert_equal("Chad C user", name1);
    astf_assert_equal("Crab", name2);

    astf_retrieve_results();
}

void test_suite3() {}

int main() {
    test_suite1();
    test_suite2();
    test_suite3();

    return 0;
}
