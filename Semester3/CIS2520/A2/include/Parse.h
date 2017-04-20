#ifndef __CBOURETTE_PARSE__
#define __CBOURETTE_PARSE__

#include "LinkedList.h"

/**
 * openfile
 * Return the file pointer.
 *
 * IN: (char*) file path, (char*) open type "w+".
 * RETURN: (FILE*) the file pointer.
 * ERROR: Print error, return with NULL file pointer.
 *
 **/
FILE* openFile(char* path, char* type);

/**
 * writeToFile
 * Write data to file.
 *
 * IN: (List*) The list to write to file.
 * RETURN: (int) Status.
 * ERROR: NONE.
 *
 **/
int writeToFile (FILE* file, List* list, char* label);

/**
 * readFromFile
 * Take file and populate defined list.
 *
 * IN: (FILE*) the file pointer, (char*) list name
 * RETURN: (List*) LinkedList populated with file contents.
 * ERROR: NONE.
 *
 **/
List* readFromFile (char* str);


int convertToInt(char* chars);

#endif
