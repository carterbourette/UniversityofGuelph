/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 2
 * Feb 17, 2017
 * Software System Integration and Development
 * Message Management and Viewer.
 *
 **/

#include <stdio.h>
#include <string.h>
#include "stream.h"
#include "stringy.h"

int main(int argc, char* argv[]) {
    if (argc < 2) printError("Invalid arguments: ./addauthor <-r to remove> <author>", 1);

    int i = 1, flag = 0;
    char name[100];
    strcpy(name,"");

    if (!strcmp(argv[1],"-r")) { flag = 1, i = 2;}

    /* read temp file for input */
    char* input = readTemp(1);

    /* assemble name */
    for (; i < argc; i++) {
        strcat(name, argv[i]);
        if (i + 1 < argc) strcat(name, " ");
    }

    /* Delegate the job to perform on the user */
    if (!flag) addUser(name, input);
    else removeUser(name, input);

    removeTemp();
    return 0;
}
