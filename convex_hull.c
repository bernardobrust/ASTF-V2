/*
** This example shows the use of ASTF in a computational geometry aplication
* using groups and the testing evirioment
*/
#define ASTF_IMPLEMENTATION
#define ASTF_STRIP_PREFIX
// #define ASTF_NO_ANSI_COLORS
#include "astf.h"

#include <stdlib.h>

typedef struct
{
  int x;
  int y;
} Point;

int
compare_points (const void *left, const void *right)
{
  const Point *a = left;
  const Point *b = right;
  return a->x != b->x ? a->x - b->x : a->y - b->y;
}

int
cross (Point origin, Point a, Point b)
{
  return (a.x - origin.x) * (b.y - origin.y)
         - (a.y - origin.y) * (b.x - origin.x);
}

// Returns hull size, points is sorted in-place
size_t
convex_hull (Point *points, size_t count, Point *hull)
{
  if (count == 0)
    return count;

  // Yes, stdlib has a quicksort
  qsort (points, count, sizeof (*points), compare_points);
  size_t unique_count = 1;

  for (size_t i = 1; i < count; ++i)
    if (compare_points (&points[unique_count - 1], &points[i]) != 0)
      points[unique_count++] = points[i];

  count = unique_count;
  if (count == 1)
    {
      hull[0] = points[0];
      return count;
    }

  size_t size = 0;

  for (size_t i = 0; i < count; ++i)
    {
      while (size >= 2
             && cross (hull[size - 2], hull[size - 1], points[i]) <= 0)
        --size;
      hull[size++] = points[i];
    }

  for (size_t i = count - 1, lower = size + 1; i-- > 0;)
    {
      while (size >= lower
             && cross (hull[size - 2], hull[size - 1], points[i]) <= 0)
        --size;
      hull[size++] = points[i];
    }

  return size - 1;
}

// Utility
bool
hull_has_point (const Point *hull, size_t count, Point expected)
{
  for (size_t i = 0; i < count; ++i)
    if (hull[i].x == expected.x && hull[i].y == expected.y)
      return true;

  return false;
}

// Test suites
void
test_square_hull ()
{
  Point points[] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 0 } };
  Point hull[5];

  start_test_suite ("Square hull removes duplicate point");

  assert_equal (4UL, (unsigned long)convex_hull (points, 5, hull));

  retrieve_results ();
}

void
test_interior_point ()
{
  Point points[] = { { 0, 0 }, { 2, 0 }, { 2, 2 }, { 0, 2 }, { 1, 1 } };
  Point hull[5];

  start_test_suite ("Hull removes interior point");

  assert_equal (4UL, (unsigned long)convex_hull (points, 5, hull));

  retrieve_results ();
}

void
test_small_inputs ()
{
  Point point[] = { { 3, 7 } };
  Point hull[1];

  start_test_suite ("Single point hull");

  assert_equal (1UL, (unsigned long)convex_hull (point, 1, hull));
  assert_equal (3, hull[0].x);
  assert_equal (7, hull[0].y);

  retrieve_results ();
}

void
test_empty_input ()
{
  Point hull[1];

  start_test_suite ("Empty input");

  assert_equal (0UL, (unsigned long)convex_hull (NULL, 0, hull));

  retrieve_results ();
}

void
test_two_points ()
{
  Point points[] = { { -4, 9 }, { 12, -3 } };
  Point hull[2];

  start_test_suite ("Two points form a hull");

  assert_equal (2UL, (unsigned long)convex_hull (points, 2, hull));
  assert_true (hull_has_point (hull, 2, (Point){ -4, 9 }));
  assert_true (hull_has_point (hull, 2, (Point){ 12, -3 }));

  retrieve_results ();
}

void
test_collinear_points ()
{
  Point points[] = { { 4, 8 }, { -2, -4 }, { 2, 4 }, { 0, 0 }, { 6, 12 } };
  Point hull[5];

  start_test_suite ("Collinear points keep endpoints only");

  assert_equal (2UL, (unsigned long)convex_hull (points, 5, hull));
  assert_true (hull_has_point (hull, 2, (Point){ -2, -4 }));
  assert_true (hull_has_point (hull, 2, (Point){ 6, 12 }));

  retrieve_results ();
}

void
test_duplicate_points ()
{
  Point points[] = { { 5, -3 }, { 5, -3 }, { 5, -3 }, { 5, -3 } };
  Point hull[4];

  start_test_suite ("Repeated point produces one-vertex hull");

  assert_equal (1UL, (unsigned long)convex_hull (points, 4, hull));
  assert_equal (5, hull[0].x);
  assert_equal (-3, hull[0].y);

  retrieve_results ();
}

void
test_large_grid ()
{
  Point points[100];
  Point hull[100];
  size_t index = 0;

  for (int y = 0; y < 10; ++y)
    for (int x = 0; x < 10; ++x)
      points[index++] = (Point){ x, y };

  start_test_suite ("Ten by ten grid keeps four corners");

  assert_equal (4UL, (unsigned long)convex_hull (points, index, hull));
  assert_true (hull_has_point (hull, 4, (Point){ 0, 0 }));
  assert_true (hull_has_point (hull, 4, (Point){ 9, 0 }));
  assert_true (hull_has_point (hull, 4, (Point){ 9, 9 }));
  assert_true (hull_has_point (hull, 4, (Point){ 0, 9 }));

  retrieve_results ();
}

void
test_large_irregular_set ()
{
  Point points[]
      = { { -8, 0 },  { -5, -5 }, { 0, -8 },  { 5, -5 }, { 8, 0 },  { 5, 5 },
          { 0, 8 },   { -5, 5 },  { 0, 0 },   { -2, 1 }, { 3, -1 }, { 1, 4 },
          { -4, -1 }, { 4, 2 },   { -1, -4 }, { 2, 3 } };
  Point hull[16];

  start_test_suite ("Large irregular set keeps outer octagon");

  assert_equal (8UL, (unsigned long)convex_hull (points, 16, hull));
  assert_true (hull_has_point (hull, 8, (Point){ -8, 0 }));
  assert_true (hull_has_point (hull, 8, (Point){ 0, -8 }));
  assert_true (hull_has_point (hull, 8, (Point){ 8, 0 }));
  assert_true (hull_has_point (hull, 8, (Point){ 0, 8 }));

  retrieve_results ();
}

// Driver code
int
main ()
{
  start_testing ();

  start_group ("General hull cases");
  test_square_hull ();
  test_interior_point ();
  end_group ();

  start_group ("Small inputs");
  test_empty_input ();
  test_small_inputs ();
  test_two_points ();
  end_group ();

  start_group ("Degenerate geometry");
  test_collinear_points ();
  test_duplicate_points ();
  end_group ();

  start_group ("Larger point sets");
  test_large_grid ();
  test_large_irregular_set ();
  end_group ();

  stop_testing ();
}
