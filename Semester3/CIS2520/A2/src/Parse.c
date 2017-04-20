#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "Cars.h"

/**
 * convertToInt
 * Convert string to int for cars values.
 *
 * IN: (char*) string with numbers.
 * RETURN: (int) integer value.
 * ERROR: NONE.
 *
 **/
int convertToInt(char* chars) {
    int sum = 0;
    for (int i = 0; i < strlen(chars); i++) {
        if (*(chars+i) > 47 && *(chars+i) < 58) {
            sum = sum *10;
            sum += *(chars+i) - '0';
        }
    }
    return sum;
}

/**
 * openfile
 * Return the file pointer.
 *
 * IN: (char*) file path, (char*) open type "w+".
 * RETURN: (FILE*) the file pointer.
 * ERROR: Print error, return with NULL file pointer.
 *
 **/
FILE* openFile(char* path, char* type) {
    FILE* file = fopen(path, type);
    if (file == NULL) printf("Unable to open file.\n");
    return file;
}

/**
 * writeToFile
 * Write data to file.
 *
 * IN: (List*) The list to write to file.
 * RETURN: (int) Status.
 * ERROR: NONE.
 *
 **/
int writeToFile (FILE* file, List* list, char* label) {
    if (file == NULL) {
        return 0;
    }
    fprintf(file, "[%s]\n", label);
    Car* c;
    for (int i = 0; i < getSizeOfList(list); i++) {
        c = (Car*)getItem(list,i);
        fprintf(file, "%s\t%d\t%d\n",c->plate,c->mileage, c->returnDate);
    }
    return 1;
}

/**
 * readFromFile
 * Take file and populate defined list.
 *
 * IN: (FILE*) the file pointer, (char*) list name
 * RETURN: (List*) LinkedList populated with file contents.
 * ERROR: NONE.
 *
 **/
List* readFromFile (char* str) {
    List* list = initList();
    FILE* fp = openFile("cars.txt", "r+");
    if (fp == NULL)  return list;
    char fileLine[255];
    char *token;
    int found = 0;

     while (fgets(fileLine, 255, fp)) {
        token = strtok(fileLine,"[]");

        //  We found the list we're looking for
        if (strcmp(token,str) == 0) {
            found = 1;
            continue;
        }
        //  If we're in a list create some cars
        if (found) {
            token = strtok(fileLine,"\t");
            if (*token == '[') {
                found = 0;
                continue;
            }

            //  Create a car
            Car *car = (Car*)malloc(sizeof(Car));
            if (car == NULL) break;

            //  Get first field - plate
            car->plate = (char*)malloc(sizeof(char) * strlen(token) + 1);
            if (car->plate == NULL) break;
            strcpy(car->plate, token);

            //  Tokenize get next field - mileage
            token = strtok(NULL,"\t");
            car->mileage = convertToInt(token);

            //  Tokenize and get next field - return date
            token = strtok(NULL,"\t");
            car->returnDate = convertToInt(token);
            if (strcmp(str, "rented") == 0) {
                addCarByDate(list, car);
            } else {
                addCarByMileage(list, car);
            }
        }
    }
    return list;
    fclose(fp);
}
