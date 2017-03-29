#ifndef __CBOURETTE_TEMPLATE__
#define __CBOURETTE_TEMPLATE__

typedef struct Struct_Properties {
    int hashVariables;
    int tempVariables;
    int replacedVariables;
    int failedReplacement;
    char tempFile[50];
    char varFile[50];
    char outFile[50];
} Properties;

/**
 * initProperties
 * Initializes struct Properties, all integer variables to zero
 * takes command line args to set char arrays of template, variable and output.
 *
 * IN: Properties(struct), *args[]
 * RETURN: VOID
 *
 **/
void initProperties(Properties* doc, char *args[]);

/**
 * interpretTemp
 * Reads the template file, replaces variables (dentoted by {}) with vars from
 * variable file (denoted by key=value\n)
 *
 * IN: Properties(struct)
 * RETURN: VOID
 *
 **/
void interpretTemp(Properties* doc);

/**
 * printDocumentProperties
 * Prints the successes and failures associated with replacement and failue
 * while parsing the files.
 *
 * IN: Properties(struct)
 * RETURN: VOID
 *
 **/
void printDocumentProperties(Properties doc);

/**
 * setToHash
 * Parses the variable file, splits key and value sets to hash found storeval.h
 *
 * IN: Properties(struct)
 * RETURN: VOID
 *
 **/
void setToHash(Properties* doc);

/**
 * throwError
 * Fatal Error, quits program prints given string
 *
 * IN: char*
 * RETURN: VOID
 * POST: Prints given error
 *
 **/
void throwError(char* str);

#endif
