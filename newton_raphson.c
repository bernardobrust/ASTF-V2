#define ASTF_IMPLEMENTATION
#define ASTF_STRIP_PREFIX
#include "astf.h"

#include <float.h> // For DBL_MIN
#include <math.h>

/*
** In this example I demostrate how you'd go about using ASTF for a numerical
* calculus aplication
*/

// Basic PI definition
#define PI acos (-1)

// Some people like output parameters, I prefer struct results
// In numerical methods we usually like getting the amount of iterations to
// compare methods, even tho for our pupuses here it's useless
typedef struct
{
  double result;
  int iterations;
} NewtonRaphsorResult;

// We need the function f, it's derivative f', an initial guess p0, a tolerance
// epsilon and a limit to the amount of iterations
NewtonRaphsorResult
newton_raphsor (double (*f) (double x), double (*f_prime) (double x),
                double p0, double eps, unsigned max_iter)
{
  // If the derivative get's this low we likely diverged
  static const double min_derivative = 1e-4;

  double p = p0, pp = p0;
  NewtonRaphsorResult r;

  for (unsigned i = 1; i <= max_iter; ++i)
    {
      const double fpp = f_prime (pp);

      // Divergence
      if (fabs (fpp) < min_derivative)
        {
          r.result = DBL_MIN; // STUB
          r.iterations = i;
          return r;
        }

      const double fp = f (pp);
      p = pp - (fp / fpp);

      // Convergence
      if (fabs (p - pp) < eps || fabs (fp) < eps)
        {
          r.result = p;
          r.iterations = i;
          return r;
        }

      pp = p;
    }

  // Max iteration exceeded
  r.result = p;
  r.iterations = -1; // STUB
  return r;
}

// Functions to test
double
f1 (double x)
{
  return cos (x) * x;
}
double
f1_prime (double x)
{
  return cos (x) - sin (x) * x;
}
double
f2 (double x)
{
  return (x * x * x) + (4 * sin (2 * x)) - 6;
}
double
f2_prime (double x)
{
  return (3 * x * x) + (8 * cos (2 * x));
}
double
f3 (double x)
{
  return (x * x * x) - (5 * x);
}
double
f3_prime (double x)
{
  return (3 * x * x) - 5;
}

int
main ()
{
  // You could split the suites innto functions, but this works for the
  // examples
  start_test_suite ("Basic newton raphsor tests");

  // Imediate root
  NewtonRaphsorResult r0
      = newton_raphsor (f1, f1_prime, 3 * PI / 2, 1e-12, 32);
  assert_approx (3 * PI / 2, r0.result, 1e-12);
  assert_equal (1, r0.iterations);

  // Strict calculations
  NewtonRaphsorResult r1 = newton_raphsor (f1, f1_prime, -1.4, 1e-12, 32);
  NewtonRaphsorResult r2 = newton_raphsor (f2, f2_prime, PI / 2, 1e-12, 32);
  assert_approx (-PI / 2, r1.result, 1e-12);
  assert_approx (2.1234185958631942681, r2.result, 1e-12);

  retrieve_results ();

  start_test_suite ("Avoids 0 derivatives");

  NewtonRaphsorResult r3 = newton_raphsor (f1, f1_prime, 0.86033, 1e-3, 2);
  // We're checking that the stub is returned when the derivative is close to 0
  assert_approx (DBL_MIN, r3.result, 1e-3);

  retrieve_results ();

  start_test_suite ("STUBs when max_iter is not viable or never converges");

  // Returns the STUB when there's no way to converge that fast
  NewtonRaphsorResult r4 = newton_raphsor (f2, f2_prime, -1.2, 1e-12, 2);
  assert_equal (-1, r4.iterations);

  // x^3 - 5x for x0 = 1 bounces around between 1 and -1
  NewtonRaphsorResult r5 = newton_raphsor (f3, f3_prime, 1, 1e-3, 512);
  assert_equal (-1, r5.iterations);

  retrieve_results ();
}
