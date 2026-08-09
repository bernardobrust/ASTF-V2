#define ASTF_IMPLEMENTATION
#define ASTF_STRIP_PREFIX
#include "astf.h"

/*
** Basic ASTF example.
**
** Tests belong to suites. Suites belong to groups. Groups belong to one
** testing process:
**
**   start_testing(); start_group(...); suites; end_group(); stop_testing();
**
** This file deliberately includes failing assertions. They show ASTF failure
** output and make group summaries demonstrate fully passed, partially failed,
** and fully failed results. For a Computational Geometry example, see
** "convex_hull.c". For a Numerical Calculus example, see "newton_raphson.c".
*/

int
fib (const int n)
{
  int pp = 0, p = 1, next;
  for (int i = 2; i <= n; ++i)
    {
      next = pp + p;
      pp = p;
      p = next;
    }

  return n == 0 ? pp : p;
}

unsigned
fib_unsigned (const unsigned n)
{
  unsigned pp = 0, p = 1, next;
  for (unsigned i = 2; i <= n; ++i)
    {
      next = pp + p;
      pp = p;
      p = next;
    }

  return n == 0 ? pp : p;
}

void
test_suite0 ()
{
  start_test_suite ("Math Suite");

  int result = 2 + 2;
  assert_equal (4, result);
  assert_true (result > 0);

  retrieve_results ();
}

void
test_suite1 ()
{
  start_test_suite ("Fib mixed data types");

  unsigned a = 8, b = 3;
  assert_equal (0, fib (0));
  assert_equal (1, fib (1));
  assert_equal (2, fib (3));

  // Intentional failure: fib(4) is 3, not 5.
  assert_equal (5, fib (4));

  // Intentional failures using unsigned values.
  assert_equal (a, fib_unsigned (4));
  assert_equal (b, fib_unsigned (4));

  retrieve_results ();
}

void
test_suite2 ()
{
  start_test_suite ("Data types");

  unsigned short a = 2, b = 5;
  assert_equal (a, b - 3);

  double x = 1.1111112, y = 1.1111113;
  float w = 3.14f, z = 3.10f;
  assert_approx (x, y, 0.0001);

  // Intentional floating-point failure: difference exceeds epsilon.
  assert_approx (w, z, 0.01f);

  const char *name1 = "Chad C user", *name2 = "Loser Rust user";
  assert_equal ("Chad C user", name1);

  // Intentional string comparison failure.
  assert_equal ("Crab", name2);

  bool t = true, f = false;
  assert_cond (true, t);
  assert_false (f);

  // Intentional boolean failure.
  assert_true (f);

  retrieve_results ();
}

void
test_suite3 ()
{
  start_test_suite ("Pointers");

  long x = 100;
  long *ptr1 = NULL, *ptr2 = &x;

  char *str = malloc (4);

  assert_not_null (str);

  // Intentional NULL check failure.
  assert_not_null (ptr1);

  assert_equal (ptr2, &x);
  assert_null (ptr1);

  // Both are intentional NULL check failures.
  assert_null (ptr2);
  assert_null (str);

  free (str);

  retrieve_results ();
}

void
test_suite4 ()
{
  start_test_suite ("Ranges");

  assert_range (4, 3, 5);
  assert_range (4.75f, 4.5f, 4.8f);

  // Intentional out-of-range value.
  assert_range (4.8001, 4.5, 4.8);

  retrieve_results ();
}

void
test_suite5 ()
{
  start_test_suite ("Intentional complete failure");

  // No assertions pass, so this suite and group are fully failed.
  assert_true (false);
  assert_equal (10, 5);

  retrieve_results ();
}

int
main ()
{
  start_testing ();

  // This group has no failing assertions: fully passed.
  start_group ("Passing examples");
  test_suite0 ();
  end_group ();

  // Both suites mix passing and intentional failures: partially failed.
  start_group ("Mixed result examples");
  test_suite1 ();
  test_suite2 ();
  end_group ();

  // These suites exercise pointer and range assertion failures.
  start_group ("Pointer and range examples");
  test_suite3 ();
  test_suite4 ();
  end_group ();

  // This group contains one suite where every assertion fails.
  start_group ("Fully failed example");
  test_suite5 ();
  end_group ();

  stop_testing ();
}
