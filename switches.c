/*
** CLI-selected sequence tests.
**
** Run:   ./a.out all
**        ./a.out fibonacci
**        ./a.out look-and-say
**        ./a.out naturals
**
** ASTF does not parse CLI options itself. This small dispatcher shows how a
** test executable can select work from argv, much like nob.h build programs
** select build actions. For richer flags, subcommands, and help text, pair
** ASTF with flag.h: https://github.com/tsoding/flag.h
*/

#define ASTF_IMPLEMENTATION
#define ASTF_STRIP_PREFIX
#include "astf.h"

unsigned long
fibonacci (unsigned n)
{
  unsigned long previous = 0;
  unsigned long current = 1;

  for (unsigned i = 0; i < n; ++i)
    {
      unsigned long next = previous + current;
      previous = current;
      current = next;
    }

  return previous;
}

unsigned long
sum_of_naturals (unsigned n)
{
  return (unsigned long)n * (n + 1) / 2;
}

// Stubs if buffer is too small
bool
look_and_say_next (const char *term, char *next, size_t capacity)
{
  size_t write_index = 0;

  for (size_t i = 0; term[i] != '\0';)
    {
      size_t count = 1;
      while (term[i + count] == term[i])
        ++count;

      if (count > 9 || write_index + 2 >= capacity)
        return false;

      next[write_index++] = (char)('0' + count);
      next[write_index++] = term[i];
      i += count;
    }

  next[write_index] = '\0';
  return true;
}

void
test_fibonacci ()
{
  start_test_suite ("Fibonacci sequence");

  assert_equal (0UL, fibonacci (0));
  assert_equal (1UL, fibonacci (1));
  assert_equal (1UL, fibonacci (2));
  assert_equal (55UL, fibonacci (10));
  assert_equal (6765UL, fibonacci (20));

  retrieve_results ();
}

void
test_look_and_say ()
{
  char term[64] = "1";
  char next[64];

  start_test_suite ("Look-and-say sequence");

  assert_true (look_and_say_next (term, next, sizeof (next)));
  assert_equal ("11", next);

  strcpy (term, next);
  assert_true (look_and_say_next (term, next, sizeof (next)));
  assert_equal ("21", next);

  strcpy (term, next);
  assert_true (look_and_say_next (term, next, sizeof (next)));
  assert_equal ("1211", next);

  strcpy (term, next);
  assert_true (look_and_say_next (term, next, sizeof (next)));
  assert_equal ("111221", next);

  retrieve_results ();
}

void
test_sum_of_naturals ()
{
  start_test_suite ("Sum of natural numbers");

  assert_equal (0UL, sum_of_naturals (0));
  assert_equal (1UL, sum_of_naturals (1));
  assert_equal (55UL, sum_of_naturals (10));
  assert_equal (5050UL, sum_of_naturals (100));
  assert_equal (50005000UL, sum_of_naturals (10000));

  retrieve_results ();
}

void
run_fibonacci_group ()
{
  start_group ("Fibonacci");
  test_fibonacci ();
  end_group ();
}

void
run_look_and_say_group ()
{
  start_group ("Look-and-say");
  test_look_and_say ();
  end_group ();
}

void
run_naturals_group ()
{
  start_group ("Natural number sums");
  test_sum_of_naturals ();
  end_group ();
}

void
print_usage (const char *program)
{
  fprintf (stderr,
           "Usage: %s {all|fibonacci|look-and-say|naturals}\n"
           "Use flag.h with ASTF when CLI parsing needs more than switches or "
           "a better interface.\n",
           program);
}

int
main (int argc, char **argv)
{
  if (argc != 2)
    {
      print_usage (argv[0]);
      return EXIT_FAILURE;
    }

  if (strcmp (argv[1], "fibonacci") != 0
      && strcmp (argv[1], "look-and-say") != 0
      && strcmp (argv[1], "naturals") != 0 && strcmp (argv[1], "all") != 0)
    {
      print_usage (argv[0]);
      return EXIT_FAILURE;
    }

  start_testing ();

  if (strcmp (argv[1], "fibonacci") == 0)
    run_fibonacci_group ();
  else if (strcmp (argv[1], "look-and-say") == 0)
    run_look_and_say_group ();
  else if (strcmp (argv[1], "naturals") == 0)
    run_naturals_group ();
  else if (strcmp (argv[1], "all") == 0)
    {
      run_fibonacci_group ();
      run_look_and_say_group ();
      run_naturals_group ();
    }

  stop_testing ();
}
