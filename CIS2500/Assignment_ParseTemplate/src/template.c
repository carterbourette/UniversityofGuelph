#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storeval.h"
#include "template.h"

void initProperties(Properties* doc, char *args[]) {
    doc->hashVariables = 0;
    doc->tempVariables = 0;
    doc->replacedVariables = 0;
    doc->failedReplacement = 0;
    strcpy(doc->tempFile, args[1]);
    strcpy(doc->varFile, args[2]);
    strcpy(doc->outFile, args[3]);
}

void interpretTemp(Properties* doc) {
    FILE *file, *outputFile;
    char string[255];
    int foundVar;

    foundVar = 0;
    strcpy(string, "");

    file = fopen(doc->tempFile, "r");
    outputFile = fopen(doc->outFile, "w+");
    if (file == NULL || outputFile == NULL) {
        throwError("Problem reading file...");
    }

    while (!feof(file)) {
        char character;
        character = fgetc(file); if (character == -1) break;
        //  If we find open curly or already found one, copy to string
        if (character == '{' || foundVar) {
            foundVar = 1;
            if (character != '{') {
                //  Found the end of variable get the hash, clear the string
                if (character == '}') {
                    doc->tempVariables++;
                    foundVar = 0;
                    if (getValue(string)) {
                        fprintf(outputFile,"%s",getValue(string));
                        doc->replacedVariables++;
                    } else {
                        fprintf(outputFile,"MISSING_DATA");
                        doc->failedReplacement++;
                    }
                    strcpy(string, "");
                } else {
                    char temp[2];
                    temp[0] = character;
                    temp[1] = '\0';
                    strcat(string,temp);
                }
            }
        //  If not print the character out
        } else {
            fprintf(outputFile,"%c",character);
        }
    }
    fclose(file);
    fclose(outputFile);
}

void printDocumentProperties(Properties doc) {
    printf("\n");
    printf("The program executed successfully!\n");
    printf("The variable document contained:\t%d variables\n", doc.hashVariables);
    printf("The template document contained:\t%d variables\n", doc.tempVariables);
    printf("Successfully replacements variables:\t%d\n", doc.replacedVariables);
    printf("Unsuccessfully replaced variables:\t%d\n", doc.failedReplacement);
    printf("The file was written to %s\n", doc.outFile);
    printf("\n");
}

void setToHash(Properties* doc) {
    FILE *file;

    file = fopen(doc->varFile, "r");
    if (file == NULL) {
        throwError("Problem reading file...");
    } else {
        char fileLine[50], *subString, *keyValue[2];
        strcpy(fileLine, "");

        //  Read the file line by line
        while (fgets (fileLine , 50 , file)) {
            //  Split the key and value store to temp array
            subString = strtok(fileLine,"=");
            keyValue[0] = subString;

            //  Split the value from the end of line
            subString = strtok(NULL,"\n");
            keyValue[1] = subString;

            if (subString != NULL) {
                if (setValue(keyValue[0],keyValue[1]))
                    doc->hashVariables++;
                else
                    throwError("Hash Memory Error");
            }
        }
        fclose(file);
    }
}

void throwError(char* str) {
    printf("Program execution failed!\n");
    printf("%s\n", str);
    printf("\n");
    exit(1);
}
