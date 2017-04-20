#ifndef __CBOURETTE_CARBON__
#define __CBOURETTE_CARBON__

/*
    Stringify
    Allocate memory for a string.
    IN: (char*) string.
    OUT: (char*) memory location of string.
    POST: NONE. (See error)
    ERROR: Print error message and continue
*/
char* stringify(char* string);

/*
    swap
    Swap two characters.
    IN: (char*) string 1, (char*) string 2.
    OUT: NONE.
    POST: NONE.
*/
void swap(char* a, char* b);
/*
    permutate
    Perform all permuations of a given string.
    IN: (char*) the string, (int) index (default to 0).
    OUT: NONE.
    POST: Print the permutated words. (Print statements are calculated by
            where n = length of word: n!)
*/
void permutate(char* word, int index);

#endif
