/**
 * collectd - src/tests/macros.h
 * Copyright (C) 2013-2015  Florian octo Forster
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *   Florian octo Forster <octo at collectd.org>
 */

#include <inttypes.h>

static int fail_count__ = 0;
static int check_count__ = 0;

#ifndef DBL_PRECISION
# define DBL_PRECISION 1e-12
#endif

#define DEF_TEST(func) static int test_##func ()

#define RUN_TEST(func) do { \
  int status; \
  printf ("Testing %s ...\n", #func); \
  status = test_ ## func (); \
  printf ("%s.\n", (status == 0) ? "Success" : "FAILURE"); \
  if (status != 0) { fail_count__++; } \
} while (0)

#define END_TEST exit ((fail_count__ == 0) ? 0 : 1);

#define OK1(cond, text) do { \
  _Bool result = (cond); \
  printf ("%s %i - %s\n", result ? "ok" : "not ok", ++check_count__, text); \
  if (!result) { return -1; } \
} while (0)
#define OK(cond) OK1(cond, #cond)

#define STREQ(expect, actual) do { \
  if (strcmp (expect, actual) != 0) { \
    printf ("not ok %i - %s incorrect: expected \"%s\", got \"%s\"\n", \
        ++check_count__, #actual, expect, actual); \
    return (-1); \
  } \
  printf ("ok %i - %s evaluates to \"%s\"\n", ++check_count__, #actual, expect); \
} while (0)

#define EXPECT_EQ(expect, actual, format) do { \
  if ((expect) != (actual)) {\
    printf ("not ok %i - %s incorrect: expected " format ", got " format "\n", \
        ++check_count__, #actual, expect, actual); \
    return (-1); \
  } \
  printf ("ok %i - %s evaluates to " format "\n", ++check_count__, #actual, expect); \
} while (0)

#define EXPECT_INTEQ(expect, actual) do { \
  if ((expect) != (actual)) {\
    printf ("not ok %i - %s incorrect: expected %d, got %d\n", \
        ++check_count__, #actual, expect, actual); \
    return (-1); \
  } \
  printf ("ok %i - %s evaluates to %d\n", ++check_count__, #actual, expect); \
} while (0)

#define EXPECT_EQ_UINT64(expect, actual) EXPECT_EQ((expect), (actual), "%"PRIu64)

#define DBLEQ(expect, actual) do { \
  double e = (expect); double a = (actual); \
  if (isnan (e) && !isnan (a)) { \
    printf ("not ok %i - %s incorrect: expected %.15g, got %.15g\n", \
        ++check_count__, #actual, e, a); \
    return (-1); \
  } else if (!isnan (e) && (((e-a) < -DBL_PRECISION) || ((e-a) > DBL_PRECISION))) { \
    printf ("not ok %i - %s incorrect: expected %.15g, got %.15g\n", \
        ++check_count__, #actual, e, a); \
    return (-1); \
  } \
  printf ("ok %i - %s evaluates to %.15g\n", ++check_count__, #actual, e); \
} while (0)

#define CHECK_NOT_NULL(expr) do { \
  void *ptr_; \
  ptr_ = (expr); \
  OK1(ptr_ != NULL, #expr); \
} while (0)

#define CHECK_ZERO(expr) do { \
  long status_; \
  status_ = (long) (expr); \
  OK1(status_ == 0L, #expr); \
} while (0)
