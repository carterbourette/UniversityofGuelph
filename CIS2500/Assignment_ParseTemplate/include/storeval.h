/*__IFS_IGNORE__*/ //Used prevent the IFS system from scanning this file
/**
 * Justin Carvalho (Jan 2016)
 * carvalhj@uoguelph.ca
 *
 * This file contains an interface for storing and retrieving values associated
 * with strings.
 *
 * For example:
 * Store value "world" inside "hello"
 * Retrieve value for "hello" returns "world"
 * Example usage in test.c
 *
 * These functions are simple wrappers around Troy Hansons uthash library.
 * They were written for CIS*2500 Assignment 1 @ UoGuelph
 */

#ifndef __CA_JCARVALHO_STOREVAL__
#define __CA_JCARVALHO_STOREVAL__

/**
 * setValue
 * Accepts a key and value as input, and stores them internally.
 * The value becomes associated with the key, and can be retrieved using the key.
 *
 * IN: char*, char*
 * RETURN: int = 1 if storage was successful, 0 if storage failed
 *
 * note: key and value are copied. Original memory may be modified safely.
 * errors: key and value must be < 26 chars in length
 *         out of memory
 */
int setValue(char* key, char* value);

/**
 * getValue
 * Accepts a key, searches internal storage for an associated value.
 *
 * IN: char*
 * RETURN: char* = value if found, NULL if failed
 *
 * note: value returned is a copy. Modifications won't affect storage. Should be freed.
 * errors: key must be < 26 chars in length
 *         key has no associated value
 *         out of memory
 */
char* getValue(char* key);


#endif
/* defined __CA_JCARVALHO_STOREVAL__ */
