package cis2430laba2;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Carter
 */
public class CIS2430LabA2 {

    public static void printMenu() {
        System.out.println("\n");
        System.out.println("(1) Enter a new vehicle.");
        System.out.println("(2) Print out brand and model.");
        System.out.println("(3) Print out average cost + total vehicles.");
        System.out.println("(4) Print out all vehicle years.");
        System.out.println("(5) Quit.");
        System.out.println("\n");
    }
    
    public static String getString(Scanner obj) {
        String str = obj.nextLine();
        //obj.nextLine();
        return str;
    }
    
    public static int getInt(Scanner obj) {
        try {
            int a = obj.nextInt();
            obj.nextLine();
            return a;
        } catch (java.util.InputMismatchException e) {
            obj.nextLine();
            return -1;
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //  Create a scanner for user input
        Scanner input = new Scanner(System.in);
        ArrayList myCars = new ArrayList();
        
        int choice = 0, i = 0;
        boolean noerror = false;
        Car temp;
        
        while (choice != 5) {
            printMenu();
            System.out.print("Please enter a choice: ");
            choice = getInt(input);
            
            //  Delegate tasks 
            switch(choice) {
                case 1:
                    //  New vehicle prompt
                    Car myCar = new Car();
                    
                    do {
                        System.out.print("Please enter the brand and model: ");
                        noerror = myCar.setBrand(getString(input));
                        if (!noerror) System.out.println("Brand is a required field!\nPlease enter two words.\n");
                    } while (!noerror);
                    
                    do {
                        System.out.print("Please enter the year: ");
                        noerror = myCar.setYear(getString(input));
                        if (!noerror) System.out.println("Brand is a required field!\nPlease enter a value.");
                    } while (!noerror);
                    
                    System.out.print("Please enter the price: $");
                    myCar.setPrice(getString(input));
                    
                    //  Car is complete add it to a list
                    myCars.add(myCar);
                    System.out.print("Car created.");
                    break;
                case 2:
                    //  Print model and brand
                    for (i = 0; i < myCars.size(); i++) {
                        temp = (Car)myCars.get(i);
                        String[] brandName = temp.getBrand();
                        System.out.print("\n");
                        System.out.println("Vehicle " + (i + 1));
                        System.out.println("Brand: " + brandName[0]);
                        System.out.println("Model: " + brandName[1]);
                        System.out.print("\n");
                    }
                    break;
                case 3:
                    //  Avg cost + total vehicle
                    double avg = 0;
                    int total = myCars.size();
                    for (i = 0; i < myCars.size(); i++) {
                        temp = (Car)myCars.get(i);
                        avg = avg + temp.getPrice();
                    }
                    System.out.println("The average cost is $" + (avg/total) + ". Out of " + total + " vehicles.");
                    break;
                case 4:
                    //  Print all vehicle years
                    for (i = 0; i < myCars.size(); i++) {
                        temp = (Car)myCars.get(i);
                        System.out.print("\n");
                        System.out.println("Vehicle " + (i + 1));
                        System.out.println("Year: " + temp.getYear());
                        System.out.print("\n");
                    }
                    break;
                case 5:
                    System.out.println("\nSee ya!\n");
                    break;
            }
        }
    }
    
}
