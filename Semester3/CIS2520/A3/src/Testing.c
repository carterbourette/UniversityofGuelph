#include <stdio.h>
#include <string.h>

/**
 * assertTrue
 * Make an assertion that a given value will return true.
 *
 * IN: (char*) Assertion, (int) return status.
 * RETURN: (int) status.
 * ERROR: NONE.
 *
 **/
 int assertTrue (char* str, int a) {
     if (a) {
         printf("%s - test passed\n", str);
         return 1;
     }
     printf("\n\n%s - test failed\n\n", str);
     return 0;
 }

 /**
  * assertFalse
  * Make an assertion that a given value will return false.
  *
  * IN: (char*) Assertion, (int) return status.
  * RETURN: (int) status.
  * POST: printf(Assertion status message)
  *
  **/
  int assertFalse (char* str, int a) {
      if (!a) {
          printf("%s - test passed\n", str);
          return 1;
      }
      printf("\n\n%s - test failed\n\n", str);
      return 0;
  }

  /**
   * assertStrEquals
   * Make an assertion that two given strings will be equal.
   *
   * IN: (char*) Assertion, (char*) first string, (char*) second string.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertStrEquals(char* str, char* assrt1, char* assrt2) {
      if(strcmp(assrt1,assrt2) == 0) {
          printf("%s - test passed\n", str);
          return 1;
      }
      printf("\n\n%s - test failed\n\n\n", str);
      return 0;

  }

  /**
   * assertIntEquals
   * Make an assertion that two given ints will be equal.
   *
   * IN: (char*) Assertion, (int) first int, (int) second int.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertIntEquals(char* str, int assrt1, int assrt2) {
      if(assrt1 == assrt2) {
          printf("%s - test passed\n", str);
          return 1;
      }
      printf("\n\n%s - test failed\n\n", str);
      return 0;

  }

  /**
   * assertIntEquals
   * Make an assertion that two given doubles will be equal.
   *
   * IN: (char*) Assertion, (doubles) first doubles, (doubles) second doubles.
   * RETURN: (int) status.
   * ERROR: NONE.
   *
   **/
  int assertDblEquals(char* str, double assrt1, double assrt2) {
      if(assrt1 == assrt2) {
          printf("%s - test passed\n", str);
          return 1;
      }
      printf("\n\n%s - test failed\n\n", str);
      return 0;

  }
