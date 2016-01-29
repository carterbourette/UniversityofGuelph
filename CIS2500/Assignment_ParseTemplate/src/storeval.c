/*__IFS_IGNORE__*/ //Used prevent the IFS system from scanning this file
/**
 * Justin Carvalho (2016)
 * carvalhj@uoguelph.ca
 *
 * See storeval.h for usage
 */

#include "uthash.h"

typedef struct Hash {
    char key[26];
    char value[26];
    UT_hash_handle hh;
} Hash;

static Hash* table = NULL;

int setValue(const char* key, const char* value) {
    Hash* element;

    if (strlen(key) > 26) return 0;
    if (strlen(value) > 26) return 0;

    element = (Hash*) malloc(sizeof(Hash));
    if (!element) return 0;

    strcpy(element->key, key);
    strcpy(element->value, value);

    HASH_ADD_STR(table, key, element);

    return 1;
}

char* getValue(const char* key) {
    Hash* element = NULL;
    char* value;

    if (strlen(key) > 26) return NULL;

    HASH_FIND_STR(table, key, element);
    if (!element) return NULL;

    value = (char*) malloc(strlen(element->value));
    if (!value) return NULL;
    strcpy(value, element->value);

    return value;
}
