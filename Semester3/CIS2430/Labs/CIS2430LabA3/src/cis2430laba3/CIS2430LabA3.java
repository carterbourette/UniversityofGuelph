package cis2430laba3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author Carter
 */
public class CIS2430LabA3 {

    public static void printMenu() {
        System.out.println("\n");
        System.out.println("(1) Enter a new vehicle.");
        System.out.println("(2) Print out brand and model.");
        System.out.println("(3) Print out average cost + total vehicles.");
        System.out.println("(4) Print out all vehicle years.");
        System.out.println("(5) Read input file.");
        System.out.println("(6) Standard data dump.");
        System.out.println("(7) File data dump.");
        System.out.println("(8) Quit.");
        System.out.println("\n");
    }
    
    public static String getString(Scanner obj) {
        String str = obj.nextLine();
        //obj.nextLine();
        return str;
    }
    
    public static boolean getBoolean(Scanner obj) {
        String bool = obj.nextLine();
        //obj.nextLine();
        return Boolean.parseBoolean(bool);
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
        ArrayList<Car> myCars = new ArrayList();
        
        int choice = 0, i = 0;
        boolean noerror = false;
        Car temp;
        
        while (choice != 8) {
            printMenu();
            System.out.print("Please enter a choice: ");
            choice = getInt(input);
            
            //  Delegate tasks 
            switch(choice) {
                case 1:
                    int resp = 0;
                    while (resp != 1 && resp != 2) {
                        System.out.println("(1) Add a Car.");
                        System.out.println("(2) Add a SUV.");
                        System.out.print("Please enter a choice: ");
                        resp = getInt(input);
                    }
                    
                    if (resp == 1) {
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
                    } else {
                             //  New vehicle prompt
                        SUV myCar = new SUV();

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
                        
                        System.out.print("Please enter the number of seats: ");
                        myCar.setNumSeats(getInt(input));
                        
                        System.out.print("Please enter if it is all terrain (true or false): ");
                        myCar.setIsAllTerrain(getBoolean(input));
                        
                        System.out.print("Please enter the tire brand: ");
                        myCar.setTireBrand(getString(input));

                        //  Car is complete add it to a list
                        myCars.add(myCar);
                        System.out.print("Car created.");
                    }
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
                    DecimalFormat df = new DecimalFormat("#.00"); 
                    System.out.println("The average cost is $" + (df.format(avg/total)) + ". Out of " + total + " vehicles.");
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
                    //  Read input file
                    System.out.print("Please enter the name of the file: ");
                    String filename = getString(input);
                    try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
                        String line = br.readLine();
                        while (line != null) {
                            String arr[] = line.split(" ");
                            if (arr.length == 5){
                                Car c = new Car(arr[0], arr[1], arr[2], arr[3]);
                                myCars.add(c);
                            } else {
                                int numSeats = Integer.parseInt(arr[5]);
                                boolean isAll = Boolean.parseBoolean(arr[6]);
                                SUV c = new SUV(arr[0], arr[1], arr[2], arr[3], numSeats, isAll, arr[7]);
                                myCars.add(c);
                            }
                            line = br.readLine();   
                        }
                        System.out.println(filename + " loaded.");
                    } catch (FileNotFoundException ex) {
                        System.err.println("File not found.");
                    } catch (IOException ex) {
                        System.err.println("IO error.");
                    }
                    break;
                case 6:
                    //  Standard Data Dump
                    for (i = 0; i < myCars.size(); i++) {
                        Car t = (Car) myCars.get(i);
                        System.out.println(t.dataDump());
                    }
                    break;
                case 7:
                    //  File Data Dump  
                    PrintWriter writer;
                    try {
                        writer = new PrintWriter("output.txt", "UTF-8");
                        for (i = 0; i < myCars.size(); i++) {
                            Car t = (Car) myCars.get(i);
                            writer.println(t.dataDump());
                        }
                        writer.close();
                    } catch (java.io.FileNotFoundException | java.io.UnsupportedEncodingException e) {
                        System.out.printf("File not found.");
                    }
                    break;
                case 8:
                    System.out.println("\nSee ya!\n");
                    break;
            }
        }
    }
    
}
