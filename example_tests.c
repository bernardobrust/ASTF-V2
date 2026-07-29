#define ASTF_IMPLEMENTATION
#define ASTF_STRIP_PREFIX
#include "astf.h"

/*
** Here are a couple of basic examples on how to use ASTF
** For a more intricate example check "newton_raphsor.c"
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

  // Fails
  assert_equal (5, fib (4));

  // Fails
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

  // Fails
  assert_approx (w, z, 0.01f);

  const char *name1 = "Chad C user", *name2 = "Loser Rust user";
  assert_equal ("Chad C user", name1);

  // Fails
  assert_equal ("Crab", name2);

  bool t = true, f = false;
  assert_cond (true, t);
  assert_false (f);

  // Fails
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

  // Fails
  assert_not_null (ptr1);

  assert_equal (ptr2, &x);
  assert_null (ptr1);

  // Both fail
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

  // Fails
  assert_range (4.8001, 4.5, 4.8);

  retrieve_results ();
}

int
main ()
{
  test_suite0 ();
  test_suite1 ();
  test_suite2 ();
  test_suite3 ();
  test_suite4 ();

  return 0;
}
