#include <stdio.h>
#include "Cars.h"
#include "LinkedList.h"
#include "Testing.h"    //  Assertion module


int main() {

    //  Create some lists
    List* available = initList();
    List* rented = initList();

    //  Add some cars to the list
    Car* myCarToFind = newCar("EFGH-123", 246000);
    addCarByMileage(available, myCarToFind);
    addCarByMileage(available,newCar("ABCD-123", 200000));
    addCarByMileage(available,newCar("ABCD-789", 123000));
    addCarByMileage(available,newCar("ZXYW-123", 689000));

    //  Ensure we can find a car
    Car* c = searchCar(available, "EFGH-123");
    assertTrue("Car was found", c != NULL);

    //  Ensure the car is equal to the car we found
    assertTrue("Car is equal to car", carIsEqual(c, myCarToFind));

    //  Check order of list
    printCars(available, "Available List: should order mileage:\n123000, 246000, 689000");

    //  Assert some transfers
    assertTrue("Transfer can complete on valid car", transferCar(available, rented, myCarToFind));
    assertFalse("Transfer fails with invalid car", transferCar(available, rented, NULL));

    //  Fails if transfer didn't work - test will fail
    assertTrue("Size of rented list now equals 1", getSizeOfList(rented) == 1);

    //  Print the lists to make sure all is well
    printCars(available,"");
    printCars(rented,"");

    //  We're going to test the addCarByDate.. We'll need some cars
    Car* myCar = newCar("ABCD-456", 246000);
    myCar->returnDate = 161011;
    addCarByDate(rented,myCar);

    myCar = newCar("DEFG-456", 260000);
    myCar->returnDate = 161010;
    addCarByDate(rented,myCar);

    myCar = newCar("ZXYQ-456", 100000);
    myCar->returnDate = 161009;
    addCarByDate(rented,myCar);

    myCar = newCar("YUTZ-456", 360000);
    myCar->returnDate = 161012;
    addCarByDate(rented,myCar);

    printCars(rented,"Rented: Should appear: EFGH,ZXYQ,DEFG,ABCD,YUTZ");

    //  We're going to return a couple of cars to the list
    myCarToFind = searchCar(rented, "EFGH-123");
    assertTrue("Car EFGH-123 was found", myCarToFind != NULL);

    //  Calculate return
    printf("Let's assert that %s with a starting mileage of %d drove 100km.\n", myCarToFind->plate, myCarToFind->mileage);
    assertDblEquals("Rental cost will be $40.00",40.0,computeFee(myCarToFind,myCarToFind->mileage+100));
    //  Add back to available list
    myCarToFind->returnDate = 0;
    transferCar(rented,available,myCarToFind);

    //  Do another
    myCarToFind = searchCar(rented, "DEFG-456");
    assertTrue("Car EFGH-123 was found", myCarToFind != NULL);

    //  Calculate return
    printf("Let's assert that %s with a starting mileage of %d drove 150km.\n", myCarToFind->plate, myCarToFind->mileage);
    assertDblEquals("Rental cost will be $47.50",47.5,computeFee(myCarToFind,myCarToFind->mileage+150));
    //  Add back to available list
    myCarToFind->returnDate = 0;
    transferCar(rented,available,myCarToFind);

    printCars(available,"");
    printCars(rented,"");

}
