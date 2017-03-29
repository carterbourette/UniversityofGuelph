/**
 * Carter Bourette (Feb 2017)
 * cbourette@gmail.com
 *
 * A string library containing common string functions.
 * Edit: NONE.
 **/

 #ifndef __CBOURETTE_STRINGY__
 #define __CBOURETTE_STRINGY__

typedef struct struct_split {
    char** substring;
    int rows;
    int last;
} Split;

/**
 * newSplit
 * Return a structure of type split, splits on a delimeter.
 *
 * IN: (char*) string, (char*) delimeter.
 * RETURN: (Split*) the structure containing substrings.
 * NOTE: Caller must free.
 *
 **/
Split* newSplit(char* string, char* delim);

/**
 * newSplitIgnoreSubDelimeters
 * Return a structure of type split, splits on a delimeter and ignores delimeters within specified ignore..
 *
 * IN: (char*) string, (char*) delimeter, (char*) ignore.
 * RETURN: (Split*) the structure containing substrings.
 * NOTE: Caller must free.
 *
 **/
Split* newSplitIgnoreSubDelimeters(char* string, char* delim, char* ignore);

/**
 * freeSplit
 * Free the memory allocated by the split function.
 *
 * IN: (Split*) The split structure.
 * RETURN: NONE.
 *
 **/
void freeSplit(Split* s);

/**
 * stringify
 * allocate a string.
 *
 * IN: NONE.
 * RETURN: (char*) Pointer to the string.
 * NOTE: Caller must free.
 *
 **/
char* stringify(char* str);

/**
* printError
* Prints an error message.
*
* IN: (char*) message, (int) fatal error.
* RETURN: NONE.
*
**/
void printError(char* message, int fatal);

/**
 * chomp
 * Remove trailing newline character.
 *
 * IN: (char*) the string.
 * RETURN: NONE.
 *
 **/
 void chomp(char* str);


typedef struct struct_buffer {
    char* buffer;
    int size;
    int currentIndex;
} Buffer;

/**
* newBuffer
* Create a new buffer of given size.
*
* IN: (int) Buffer size.
* RETURN: (char*).
*
**/
Buffer* newBuffer(int size);

/**
 * bufferAppend
 * Append a string to the end of the buffer.
 *
 * IN: (Buffer*) the current buffer, (char*) the string to append.
 * RETURN: NONE.
 *
 **/
void bufferAppend(Buffer* buf, char* string);

/**
* freeBuffer
* Free the memory allocated to a buffer.
*
* IN: (Buffer*) the buffer.
* RETURN: NONE.
*
**/
void freeBuffer(Buffer* b);

#endif
