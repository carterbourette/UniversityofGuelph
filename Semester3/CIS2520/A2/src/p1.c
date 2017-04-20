/**
 * Carter Bourette
 * 0916638
 * cbourette@gmail.com  |  cbourett@mail.uoguelph.ca
 *
 * Assignment 2
 * Data Structures
 * October 17, 2016
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cars.h"
#include "Parse.h"
#include "LinkedList.h"

int main() {
    //  Create the required lists
    List* available = readFromFile("available");
    List* rented = readFromFile("rented");
    List* repair = readFromFile("repair");

    Car* myRental;
    char *plate, code = '\0';
    int mileage, date;
    double totalFee = 0.0;

    while (code != '7') {
        printf("\n\nWelcome to Carter's Car Rental.\n\n\n");
        displayMenu();
        scanf("%c",&code);
        getchar();

        switch(code) {
            case '1':
                //  Add new a new rental car to list
                plate = getInput("Please enter plate number (####-###): ");
                mileage = getInputInt("Please enter the mileage: ");
                myRental = newCar(plate, mileage);
                addCarByMileage(available, myRental);
                free(plate);
                break;
            case '2':
                //  Add returned car to available list
                plate = getInput("Please enter plate number (####-###): ");
                mileage = getInputInt("Please enter the mileage: ");
                myRental = searchCar(rented,plate);
                if (myRental && isValidMileageChange(myRental, mileage)) {
                    myRental->returnDate = 0;
                    double fee = computeFee(myRental,mileage);
                    printf("Total cost of rental is $%.2lf\n", fee);
                    totalFee += fee;
                    transferCar(rented, available, myRental);
                } else printf("Unable to find return car.\n");
                free(plate);
                break;
            case '3':
                //  Add returned car to repair list
                plate = getInput("Please enter plate number (####-###): ");
                mileage = getInputInt("Please enter the mileage: ");
                myRental = searchCar(rented,plate);
                if (myRental && isValidMileageChange(myRental, mileage)) {
                    myRental->returnDate = 0;
                    double fee = computeFee(myRental,mileage);
                    printf("Total cost of rental is $%.2lf\n", fee);
                    totalFee += fee;
                    transferCar(rented, repair, myRental);
                } else printf("Unable to find return car.\n");
                free(plate);
                break;
            case '4':
                //  Transfer a repaired car to available
                plate = getInput("Please enter plate number (####-###): ");
                myRental = searchCar(repair, plate);
                transferCar(repair, available, myRental);
                free(plate);
                break;
            case '5':
                //  Rent first available car
                date = getInputInt("Please enter a return date (yymmdd): ");
                myRental = (Car*)getItem(available,0);
                if (myRental) myRental->returnDate = date;
                transferCar(available, rented, myRental);
                break;
            case '6':
                //  Print all
                printCars(available, "Available:");
                printCars(rented,"Rented:");
                printCars(repair, "In Repair:");
                break;
            case '7':
                printf("Thanks for stopping by!\n");
                printf("Total Earnings: $%.2lf\n", totalFee);
                break;
            default:
                //  Invalid input
                printf("Invalid input!\n");
                break;
            }
    }

    //  Output to the file
    FILE* fWrite = openFile("cars.txt", "w+");
    writeToFile(fWrite, available, "available");
    writeToFile(fWrite, rented, "rented");
    writeToFile(fWrite, repair, "repair");
    fclose(fWrite);

    //  Free up lists and cars
    freeCarList(available);
    freeCarList(rented);
    freeCarList(repair);

    return 0;
}
