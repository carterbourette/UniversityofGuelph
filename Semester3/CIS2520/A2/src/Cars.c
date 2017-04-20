#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Cars.h"

/**
 * newCar
 * Create a car.
 *
 * IN: (char*) Plate #, (int) mileage.
 * RETURN: (Car*) The car.
 * ERROR: Prints out that no space could be allocated.
 *
 **/
 Car* newCar(char* plate, int mileage) {
     Car *car = (Car*)malloc(sizeof(Car));
     if (car == NULL) printf("Your request could not be processed at this time!\n");
     car->plate = (char*)malloc(sizeof(char) * strlen(plate) + 1);
     // Initalize values
     strcpy(car->plate, plate);
     car->mileage = mileage;
     car->returnDate = 0;
     return car;
 }

/**
 * transferCar
 * Move a vehicle from one list to another.
 *
 * IN: (List*) src, (List*) dest, (Car*) car to move.
 * RETURN: (int) return status.
 * ERROR: NONE.
 *
 **/
int transferCar(List* src, List* dest, Car* car) {
    if (car == NULL) { printf("Unable to transfer vehicle\n"); return 0;}
    Car* c;
    int found = 0;
    int size = getSizeOfList(src);

    //  When found delete the car from src list
    for (int i = 0; i < size; i++) {
        c = (Car*) getItem(src,i);
        if (carIsEqual(c, car)) {
            found = 1;
            deleteItem(src,i);
        }
    }
    if (found) {
        //  Add to the destination list
        if (car->returnDate == 0) {
            addCarByMileage(dest,car);
        } else {
            addCarByDate(dest, car);
        }
    } else {
        printf("Unable to transfer vehicle. Not found\n");
        return 0;
    }
    return 1;
}

/**
 * carIsEqual
 * Are two car structs equal.
 *
 * IN: (Car*) car 1, (Car*) car 2.
 * RETURN: (int) status.
 *
 **/
 int carIsEqual(Car* a, Car* b) {
     if (a != NULL && b != NULL) {
         if (strcmp(a->plate, b->plate) == 0 && a->mileage == b->mileage && a->returnDate == b->returnDate) {
             return 1;
         }
     } return 0;
 }

/**
 * searchCar
 * Find a car in given list.
 *
 * IN: (List*) the list to search, (char*) the car to look for (plate #).
 * RETURN: (Car*) the car struct, NULL when not found
 * ERROR: NULL.
 *
 **/
Car* searchCar(List* list, char* plate) {
    Car* c;
    for (int i = 0; i < getSizeOfList(list); i++) {
        c = (Car*) getItem(list,i);
        //  If the plates match we found the car
        if (strcmp(c->plate,plate) == 0) return c;
    }
    return NULL;
}

/**
 * addCarByMileage
 * Add vehicles to a defined list using sort.
 *
 * IN: (List) the list, (Car) the vehicle to be added.
 * RETURN: (int) Success (1).
 * ERROR: NONE.
 *
 **/
 int addCarByMileage(List* list, Car* car) {
     if (car == NULL) return 0;
     if(!isValidPlateNumber(list, car->plate)) {
         printf("Unable to add vehicle to list. Duplicate plate #.\n");
         return 0;
     }
     Car* c;
     int size = getSizeOfList(list);
     if (size == 0) {
         addItem(list, car);
         return 1;
     } else {
         for (int i = 0; i < size; i++) {
             c = (Car*) getItem(list, i);
             if (car->mileage < c->mileage) {
                 insertAtIndex(list, car, i);
                 return 1;
             }
         }
         addItem(list, car);
         return 1;
     } //printf("Car (%s) added successfully\n"
     return 0;
 }

 /**
  * addCarByDate
  * Add vehicles to a defined list using sort.
  *
  * IN: (List) the list, (Car) the vehicle to be added.
  * RETURN: (int) Success (1).
  * ERROR: NONE.
  *
  **/
  int addCarByDate(List* list, Car* car) {
      if (car == NULL) return 0;
      if(!isValidPlateNumber(list, car->plate)) {
          printf("Unable to add vehicle to list. Duplicate plate #.\n");
          return 0;
      }
      Car* c;
      int size = getSizeOfList(list);
      if (size == 0) {
          addItem(list, car);
          return 1;
      } else {
          for (int i = 0; i < size; i++) {
              c = (Car*) getItem(list, i);
              if (car->returnDate < c->returnDate) {
                  insertAtIndex(list, car,i);
                  return 1;
              }
          }
          addItem(list, car);
          return 1;
      }
      return 0;
  }

  /**
   * isValidPlateNumber
   * Check to see if the plate exists in the list.
   *
   * IN: (List*) list to check, (char*) plate number.
   * RETURN: (int) status | 1 or 0.
   *
   **/
  int isValidPlateNumber(List* list, char* plate) {
      if (list == NULL) return 1;
      for (int i = 0; i < getSizeOfList(list); i++) {
          Car* temp = (Car*)getItem(list,i);
          if (strcmp(temp->plate,plate) == 0) return 0;
      }
      return 1;
  }

/**
 * isValidMileageChange
 * Check to see if the input mileage is greater than the original.
 *
 * IN: (Car*) car, (int) mileage.
 * RETURN: Status | 1 or 0.
 *
 **/
int isValidMileageChange(Car* car, int mileage) {
    if (car->mileage <= mileage) return 1;
    return 0;
}

/**
 * computeFee
 * Calculate cost of renting the vehicle.
 *
 * IN: (Car*) the car returned, (int) new mileage.
 * RETURN: (double) Cost of the rental.
 *
 **/
double computeFee(Car* car, int mileage) {
    int dif = mileage - car->mileage;
    car->mileage = mileage;
    if (dif > 100) {
        return 40.0 + ((dif - 100) * 0.15);
    } else {
        return 40.0;
    }
}

/**
 * freeCarList
 * Free all items in a list then the list.
 *
 * IN: (List*) the list to free.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
void freeCarList (List* list) {
    if (list == NULL) return;
    for (int i = 0; i < getSizeOfList(list); i++) {
        Car* c = (Car*)getItem(list, i);
        freeCar(c);
    }
    freeList(list);
}

  /**
   * freeCar
   * Free the malloc'd memory.
   *
   * IN: (Car*) the car to destroy.
   * RETURN: NONE.
   * ERROR: NONE.
   *
   **/
  void freeCar(Car* c) {
      if (c != NULL) {
          free(c->plate);
          free(c);
      }
  }

  /**
   * printCars
   * Print the list.
   *
   * IN: (List*) the list to print.
   * RETURN: NONE.
   * ERROR: NONE.
   *
   **/
  void printCars(List* list, char* str) {
      int size = getSizeOfList(list);
      if (size) printf("\n%s\nCar # :   Plate\t\tMileage\t\tReturnDate\n", str);
      for (int i = 0; i < size; i++) {
          Car* c = (Car*)getItem(list, i);
          printf("Car %d : %s\t%d\t\t%d\n", (i+1), c->plate, c->mileage, c->returnDate);
      }
  }

/**
 * displayMenu
 * Display the available options.
 *
 * IN: NONE.
 * RETURN: NONE.
 * ERROR: NONE.
 *
 **/
 void displayMenu() {
     printf("(1) Add a new car to the available-for-rent list\n");
     printf("(2) Add a returned car to the available-for-rent list\n");
     printf("(3) Add a returned car to the repair list\n");
     printf("(4) Transfer a car from the repair list to the available-for-rent list\n");
     printf("(5) Rent the first available car\n");
     printf("(6) Print all the lists\n");
     printf("(7) Quit\n\n");
     printf("Please enter a number between (1-7): ");

 }

 /**
  * getInput
  * Get a string input from the user.
  *
  * IN: NONE.
  * RETURN: (char*) Pointer to the string.
  * NOTE: Caller must free.
  *
  **/
  char* getInput(char* str) {
      char input[255];
      printf("%s", str);
      scanf("%s",input);

      //    get some space and copy the string over
      char *newstring = (char*) malloc(strlen(input)*sizeof(char));
      if (newstring == NULL) {
          printf("Failed to allocate memory!\n");
          return NULL;
      }
      strcpy(newstring, input);
      return newstring;
  }

   /**
    * getInputInt
    * Get an int input from the user.
    *
    * IN: NONE.
    * RETURN: (int) int value.
    * ERROR: NONE.
    *
    **/
  int getInputInt(char* str) {
      int val = 0;
      do{
          printf("%s", str);
          scanf("%d", &val);
          if (val == 0) printf("Invalid input, please enter an integer value.\n\n");
      } while (val == 0);
      return val;
  }
