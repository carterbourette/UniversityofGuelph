#ifndef __CBOURETTE_TESTING__
#define __CBOURETTE_TESTING__

/**
 * assertTrue
 * Make an assertion that a given value will return true.
 *
 * IN: (char*) Assertion, (int) return status.
 * RETURN: (int) status.
 * ERROR: NONE.
 *
 **/
 int assertTrue (char* str, int a);

 /**
  * assertFalse
  * Make an assertion that a given value will return false.
  *
  * IN: (char*) Assertion, (int) return status.
  * RETURN: (int) status.
  * POST: printf(Assertion status message)
  *
  **/
  int assertFalse (char* str, int a);

  /**
   * assertEquals
   * Make an assertion that two given strings will be equal.
   *
   * IN: (char*) Assertion, (char*) first string, (char*) second string.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertStrEquals(char* str, char* assrt1, char* assrt2);

  /**
   * assertIntEquals
   * Make an assertion that two given ints will be equal.
   *
   * IN: (char*) Assertion, (int) first int, (int) second int.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertIntEquals(char* str, int assrt1, int assrt2);

  /**
   * assertIntEquals
   * Make an assertion that two given doubles will be equal.
   *
   * IN: (char*) Assertion, (doubles) first doubles, (doubles) second doubles.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertDblEquals(char* str, double assrt1, double assrt2);

#endif
