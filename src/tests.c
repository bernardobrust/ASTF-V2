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

void test_suite1() {
    astf_start_test_suite("Fib mixed");

    for (int i = 0; i <= 10; ++i) printf("Fib of %d: %d\n", i, fib(i));
}

void test_suite2() {}

void test_suite3() {}

int main() {
    test_suite1();
    test_suite2();
    test_suite3();

    return 0;
}
