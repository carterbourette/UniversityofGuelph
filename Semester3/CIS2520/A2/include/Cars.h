#ifndef __CBOURETTE_CARS__
#define __CBOURETTE_CARS__

#include "LinkedList.h"

typedef struct struct_Car{
    char* plate;
    int mileage;
    int returnDate;
} Car;

/**
 * newCar
 * Create a car.
 *
 * IN: (char*) Plate #, (int) mileage.
 * RETURN: (Car*) The car.
 * ERROR: Prints out that no space could be allocated.
 *
 **/
 Car* newCar(char* plate, int mileage);

 /**
  * transferCar
  * Move a vehicle from one list to another.
  *
  * IN: (List*) src, (List*) dest, (Car*) car to move.
  * RETURN: (int) return status.
  * ERROR: NONE.
  *
  **/
 int transferCar(List* src, List* dest, Car* car);

 /**
  * searchList
  * Find a car in given list.
  *
  * IN: (List*) the list to search, (char*) the car to look for (plate #).
  * RETURN: (Car*) the car struct, NULL when not found
  * ERROR: NULL.
  *
  **/
 Car* searchCar(List* list, char* plate);


 /**
  * carIsEqual
  * Are two car structs equal.
  *
  * IN: (Car*) car 1, (Car*) car 2.
  * RETURN: (int) status.
  *
  **/
  int carIsEqual(Car* a, Car* b);

 /**
  * addCarByMileage
  * Add vehicles to a defined list using sort.
  *
  * IN: (List) the list, (Car) the vehicle to be added.
  * RETURN: (int) Success (1).
  * ERROR: NONE.
  *
  **/
  int addCarByMileage(List* list, Car* car);

  /**
   * addCarByDate
   * Add vehicles to a defined list using sort.
   *
   * IN: (List) the list, (Car) the vehicle to be added.
   * RETURN: (int) Success (1).
   * ERROR: NONE.
   *
   **/
   int addCarByDate(List* list, Car* car);

   /**
    * isValidPlateNumber
    * Check to see if the plate exists in the list.
    *
    * IN: (List*) list to check, (char*) plate number.
    * RETURN: (int) status | 1 or 0.
    *
    **/
    int isValidPlateNumber(List* list, char* plate);

   /**
    * isValidMileageChange
    * Check to see if the input mileage is greater than the original.
    *
    * IN: (Car*) car, (int) mileage.
    * RETURN: Status | 1 or 0.
    *
    **/
   int isValidMileageChange(Car* car, int mileage);

   /**
    * computeFee
    * Calculate cost of renting the vehicle.
    *
    * IN: (Car*) the car returned, (int) new mileage.
    * RETURN: (double) Cost of the rental.
    *
    **/
   double computeFee(Car* car, int mileage);

   /**
    * freeCarList
    * Free all items in a list then the list.
    *
    * IN: (List*) the list to free.
    * RETURN: NONE.
    * ERROR: NONE.
    *
    **/
   void freeCarList (List* list);

   /**
    * freeCar
    * Free the malloc'd memory.
    *
    * IN: (Car*) the car to destroy.
    * RETURN: NONE.
    * ERROR: NONE.
    *
    **/
   void freeCar(Car* c);

   /**
    * printCars
    * Print the list.
    *
    * IN: (List*) the list to print, list name char*.
    * RETURN: NONE.
    * ERROR: NONE.
    *
    **/
   void printCars(List* list, char* str);

   /**
    * displayMenu
    * Display the available options.
    *
    * IN: NONE.
    * RETURN: NONE.
    * ERROR: NONE.
    *
    **/
    void displayMenu();


    /**
     * getInput
     * Get a string input from the user.
     *
     * IN: NONE.
     * RETURN: (char*) Pointer to the string.
     * ERROR: NONE.
     *
     **/
     char* getInput(char* str);

     /**
      * getInputInt
      * Get an int input from the user.
      *
      * IN: NONE.
      * RETURN: (int) int value.
      * ERROR: NONE.
      *
      **/
      int getInputInt(char* str);

#endif
