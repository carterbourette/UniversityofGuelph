/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 1
 * Jan 27, 2017
 * Software System Integration and Development
 * Create a C++ like translator.
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include "Translator.h"
#include "LinkedList.h"

int main(int argc, char* argv[]) {

    /* Init the translator properties */
    Properties* properties = initProperties();
    char* fInput;

    /*  Let's grab the file to interpret from the commandline or user input   */
    if (argc > 1)    fInput = argv[1];
    else    fInput = getInput("Enter the relative file path: ");

    properties->filename = fInput;

    FILE* file = fopen(fInput, "r");
    if (file == NULL) printError("Unable to open input file.");

    /* Init parser properties */
    char lastChar = '\0';
    char line[510];
    int index = 0;
    int cpyToEnd = 0;
    int inStatement = 1;
    int acceptSpaces = 0;
    int indent = 0;
    int cpyToBreak = 0;

    while (!feof(file)) {
        char character = fgetc(file); if (character == -1) break;
        if (!cpyToEnd && !cpyToBreak) {
            switch (character) {
                case '#':
                    cpyToBreak = 1;
                    cpyCharToArray(line, &index, character);
                    break;
                case '{':
                    inStatement = 0;
                    if (index > 1)
                        ungetc(character,file);
                    else {
                        cpyCharToArray(line, &index, character);
                        indent++;
                    }
                    break;
                case '}':
                    inStatement = 0;
                    indent--;
                    cpyCharToArray(line, &index, character);
                    break;
                case ';':
                    inStatement = 0;
                    cpyCharToArray(line, &index, character);
                    break;
                case '*':
                    if (lastChar == '/') cpyToEnd = 1;
                    cpyCharToArray(line, &index, character);
                    break;
                case '/':
                    if (lastChar == '/')  cpyToBreak = 1;
                    cpyCharToArray(line, &index, character);
                    break;
                case ' ':
                    if (acceptSpaces) cpyCharToArray(line, &index, character);
                    break;
                case '\n':
                case '\t':
                    continue;
                default:
                    cpyCharToArray(line, &index, character);
            }
        } else {
            if (character == '\n' && cpyToBreak) inStatement = 0;
            else if (character == '/' && lastChar == '*') {
                inStatement = 0;
                cpyCharToArray(line, &index, character);
            } else
                cpyCharToArray(line, &index, character);
        }
        /*  Ignore leading spaces */
        if (lastChar != ' ' && lastChar != '\0') acceptSpaces = 1;
        lastChar = character;

        if (inStatement == 0) {
            /* Create the new token, and add it to the program token list */
            line[index] = '\0';
            Token* newToken = buildToken(line,1);
            newToken->indentLevel = indent;
            differentiateParent(newToken);
            addItem(properties->tokens, newToken);

            /* Reset iteration vars */
            inStatement = 1;
            cpyToEnd = 0;
            cpyToBreak = 0;
            acceptSpaces = 0;
            lastChar = '\0';
            index = 0;
        }
    }
    /* Compile the program up */
    processAndCompile(properties);

    /* Clean up memory */
    freeTokenList(properties->tokens);
    if (argc <= 1)  free(fInput);
    fclose(file);
    return 0;
}
