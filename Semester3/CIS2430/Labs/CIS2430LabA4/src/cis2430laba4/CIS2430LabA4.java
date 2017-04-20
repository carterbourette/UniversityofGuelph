package cis2430laba4;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author Carter
 */
public class CIS2430LabA4 {

    public static void printMenu() {
        System.out.println("\n");
        System.out.println("(1) Enter a new vehicle.");
        System.out.println("(2) Print out brand and model and year.");
        System.out.println("(3) Print out average cost + total vehicles.");
        System.out.println("(4) Read input file.");
        System.out.println("(5) Standard data dump.");
        System.out.println("(6) File data dump.");
        System.out.println("(7) Lookup via HashMap with brand, model, and year..");
        System.out.println("(8) Quit.");
        System.out.println("\n");
    }
    
    private static int search (HashMap i, String key) {
        if (i.get(key.toLowerCase()) == null) {
            return -1;
        } else {
            return (int) i.get(key.toLowerCase());
        }
    }
    
    private static void index(ArrayList cars, HashMap i, Car c) throws Exception {
        if (c == null) return;
        String[] split = c.getBrand();
        String key = split[0] + split[1] + c.getYear();
        if (i.get(key.toLowerCase()) != null) {
            throw new Exception("Duplicate ID found in list.");
        } else {
            cars.add(c);
            i.put(key.toLowerCase(), cars.size()-1);
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //  Create a scanner for user input
        ArrayList<Car> myCars = new ArrayList();
        HashMap<String, Integer> index = new HashMap<>();

        Validator v = new Validator();
        
        int choice = 0, i = 0;
        Car temp;
        
        while (choice != 8) {
            printMenu();
            
            choice = v.promptInt("Please enter a choice: ", "[1-8]{1}","Invalid choice. Enter a value between 1-8");
            
            //  Delegate tasks 
            switch(choice) {
                case 1:
                    int resp = 0;
                    resp = v.promptInt("(1) Add a Car.\n(2) Add a SUV.\n\nPlease enter a choice: ","[1-2]{1}","Invalid choice. Enter a value between 1-2");
                    
                    if (resp == 1) {
                        //  New vehicle prompt            
                        String brandAndModel, price, year;
                        
                        brandAndModel = v.prompt("Please enter the brand and model: ", "[a-z0-9]+ +[a-z0-9]+");
                        String[] bm = brandAndModel.split(" ");
                        while(true){
                            year = v.prompt("Please enter the year: ");
                            if (!year.equals("") && year.length() == 4 && Integer.parseInt(year) > 1986) break;
                            System.out.println("Please enter a valid year.");
                        }
                        while(true){
                            price = v.prompt("Please enter the price: ");
                            if(Validator.parseInt(price) > 5000) break;
                            System.out.println("Please enter a valid price (>5000).");
                        }
                        
                        try {   //  Create the car
                            Car myCar = new Car(bm[0], bm[1], year, price);
                            index(myCars,index,myCar);
                            System.out.println("Car created.");
                        } catch (Exception ex) {
                            System.err.println("Unable to create car: "+ ex.getMessage());
                        }
                    } else {
                        String brandAndModel, price, year, tire;
                        
                        brandAndModel = v.prompt("Please enter the brand and model: ", "[a-z]+ +[a-zA-z]+");
                        String[] bm = brandAndModel.split(" ");
                        while(true){
                            year = v.prompt("Please enter the year: ");
                            if (!year.equals("") && year.length() == 4 && Integer.parseInt(year) > 1986) break;
                            System.out.println("Please enter a valid year.");
                        }
                        while(true){
                            price = v.prompt("Please enter the price: ");
                            if(Validator.parseInt(price) > 5000) break;
                            System.out.println("Please enter a valid price (>5000).");
                        }
                        int numSeat = v.promptInt("Please enter the number of seats","Please enter a valid integer.");
                        boolean isAll = Boolean.parseBoolean(v.prompt("Please enter the number of seats"));
                        tire = v.prompt("Please enter the tire brand: ");
                        
                       try {   //  Create the car
                            SUV myCar = new SUV(bm[0], bm[1], year, price, numSeat,isAll, tire);
                            index(myCars,index,myCar);
                            System.out.println("SUV created.");
                        } catch (Exception ex) {
                            System.err.println("Unable to create car: "+ ex.getMessage());
                        }
                    }
                    break;
                case 2:
                    //  Print model and brand
                    for (i = 0; i < myCars.size(); i++) {
                        temp = (Car)myCars.get(i);
                        String[] brandName = temp.getBrand();
                        System.out.print("\n");
                        System.out.print("Vehicle " + (i + 1) + ": ");
                        System.out.println(brandName[0] + " " + brandName[1] + " " + temp.getYear());
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
                    //  Read input file
                   String filename = v.prompt("Please enter a filename: ");
                    try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
                        String line = br.readLine();
                        while (line != null) {
                            String arr[] = line.split(" ");
                            if (arr.length == 5){
                                Car c = null;
                                try {
                                    c = new Car(arr[0], arr[1], arr[2], arr[3]);
                                    try {
                                        //  Car is complete add it to a list
                                        index(myCars, index, c);
                                    } catch (Exception ex) {
                                        System.err.println("Unable to add car: " + ex.getMessage());
                                    }
                                } catch (Exception ex) {
                                    System.err.println("Unable to add car: " + ex.getMessage());
                                }
                                
                            } else {
                                int numSeats = Integer.parseInt(arr[5]);
                                boolean isAll = Boolean.parseBoolean(arr[6]);
                                SUV c = null;
                                try {
                                    c = new SUV(arr[0], arr[1], arr[2], arr[3], numSeats, isAll, arr[7]);
                                    try {
                                        //  Car is complete add it to a list
                                        index(myCars, index, c);
                                    } catch (Exception ex) {
                                        System.err.println("Unable to add car: " + ex.getMessage());
                                    }
                                } catch (Exception ex) {
                                    System.err.println("Unable to add car: " + ex.getMessage());
                                }
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
                case 5:
                    //  Standard Data Dump
                    for (i = 0; i < myCars.size(); i++) {
                        Car t = (Car) myCars.get(i);
                        System.out.println(t.dataDump());
                    }
                    break;
                case 6:
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
                case 7:     //  Lookup via HashMap with brand, model, and year.
                    String b = v.prompt("Please enter the brand, model and year of the car: ");
                    String key = "";
                    String[] split = b.split(", ");
                    try {
                        key = split[0] + split[1] + split[2]; 
                        int result = search(index, key.toLowerCase());
                        if(result != -1) {
                            Car mySearchCar = myCars.get(result);
                            System.out.println("\n" + mySearchCar.dataDump());
                        } else {
                            System.err.println("Car not found.");
                        }
                    } catch(ArrayIndexOutOfBoundsException e) {
                        System.err.println("Car not found.");
                    }
                    
                    break;
                case 8:
                    System.out.println("\nSee ya!\n");
                    break;
            }
        }
    }
}
