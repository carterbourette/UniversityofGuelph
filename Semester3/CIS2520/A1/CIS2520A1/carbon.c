/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 1
 * Data Structures
 * September 26, 2016
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Stringify
    Allocate memory for a string.
    IN: (char*) string.
    OUT: (char*) memory location of string.
    POST: NONE. (See error)
    ERROR: Print error message and continue
*/
char* stringify(char* string) {
    char *newstring = (char*) malloc(strlen(string)*sizeof(char));
    if (newstring == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    strcpy(newstring, string);
    return newstring;
}

/*
    swap
    Swap two characters.
    IN: (char*) string 1, (char*) string 2.
    OUT: NONE.
    POST: NONE.
*/
void swap(char* a, char* b) {
    char temp;

    temp = *b;
    *b = *a;
    *a = temp;
}

/*
    permutate
    Perform all permuations of a given string.
    IN: (char*) the string, (int) index (default to 0).
    OUT: NONE.
    POST: Print the permutated words. (Print statements are calculated by
            where n = length of word: n!)
*/
void permutate(char* word, int index) {
    //  print our word when the passed index is at the end of the word
    if(index == strlen(word)-1) printf("%s\n", word);
    else {
        //  iterate through the word
        for (int k = index; k < strlen(word); k++) {
            swap(word+index,word+k);
            permutate(word, index + 1);
            swap(word+index,word+k);
        }
    }
}
