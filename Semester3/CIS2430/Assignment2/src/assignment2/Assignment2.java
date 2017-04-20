package assignment2;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * The main class, implementation of an electronic store and search.
 * @author Carter
 */
public class Assignment2 {

    /**
     * Function for outputting all products currently in the store. (Format is .ini)
     * @param e The eStore instance to populate the product list.
     * @param filename Name of file.
     */
    public static void dumpFile(EStore e,String filename) {
        PrintWriter writer;
        try {
            writer = new PrintWriter(filename, "UTF-8");
            ArrayList<Product> list = e.getProductList();
            for (int i = 0; i < list.size(); i++) {
                Product temp = list.get(i);
                writer.println(temp.toStorageFormat());
            }
            writer.close();
            System.out.println("\nWrote data to file.");
        } catch (java.io.FileNotFoundException | java.io.UnsupportedEncodingException ex) {
            System.out.println("File not found.");
        }
    }
    
    /**
     * Parses external storage document containing products. (In .ini format)
     * @param e The eStore instance to read the product list.
     * @param filename Name of file.
     */
    public static void readFile(EStore e,String filename) {
         try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line = br.readLine();
            boolean productEnd = false, first = true;
            HashMap<String, String> properties = new HashMap<>();
            while (line != null) {
                if (line.equals("")) productEnd = true;
                else {
                    String arr[] = line.split(" = ");
                    try{ 
                       properties.put(arr[0], arr[1].substring(1, arr[1].length()-1));
                    } catch(java.lang.ArrayIndexOutOfBoundsException l) {
                        
                    }
                }
                
                if (properties.get("type").equals("book") && productEnd) {
                    //  Add a book
                    Book myBook;
                    try {
                        myBook = new Book(properties.get("productID"),properties.get("name"), properties.get("price"),properties.get("year"), properties.get("author"), properties.get("publisher"));
                        boolean add = e.add(myBook);
                    if (!add) System.err.println("Failed to add inventory item.");
                    } catch (Exception ex) {
                        System.err.println("Unable to create book: " + ex.getMessage());
                    }
                    productEnd= false;
                } else if (properties.get("type").equals("electronic") && productEnd) {
                    //  Add a electronic
                    Electronic myElec;
                    try {
                        myElec = new Electronic(properties.get("productID"),properties.get("name"), properties.get("price"),properties.get("year"), properties.get("maker"));
                        boolean add = e.add(myElec);
                    if (!add) System.out.println("Failed to add inventory item.\n");
                    } catch (Exception ex) {
                        System.err.println("Unable to create book: " + ex.getMessage());
                    }
                    productEnd= false;
                }
                line = br.readLine();
            }
            
        } catch (FileNotFoundException ex) {
            System.err.println("File not found.");
        } catch (IOException ex) {
            System.err.println("IO error.");
        }
    }
    
    public static void main(String[] args) {
        EStore myStore = new EStore();  //  Create an instance of our Electronic Store
        Validator v = new Validator();  //  Create an instance of our input validator
 
        try{    //  Get the product list from file
            System.out.println("Loading " + args[0] +"...");
            readFile(myStore,args[0]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println("Load the program with a command line argument to load inventory.");
        }
        String answer;
        do {    //  Command Loop - for add search and quit
            answer = "";
            while (answer.equals("")) {
                answer = v.prompt("Type 'add' to add book/electronic.\nType 'search' to search.\nType 'quit' to quit.\n\nPlease enter a command: ").toLowerCase();
                if (answer.matches("a") || answer.matches("add")) answer = "a";
                else if (answer.matches("s") || answer.matches("search")) answer = "s";
                else if(answer.matches("q") || answer.matches("quit")) answer = "q";
                else answer = "";
            }
            //  Delegate the tasks...
            switch (answer) {
                case "a": //  Add case
                    int reply = 0;
                    while (reply == 0) {
                        answer = v.prompt("Type 'book' to add a book.\nType 'electronic' to add an electronic.\n\nPlease enter a command: ").toLowerCase();
                        answer = answer.toLowerCase();
                        if (answer.matches("b") || answer.matches("book")) reply = 1;
                        else if (answer.matches("e") || answer.matches("electronic")) reply = 2;
                    }
                    
                    switch(reply) {
                        case 1:
                            String yr,pr;
                            String id = v.prompt("Please enter the book product id: ", "[0-9]{6}", "Please enter a 6 digit id.");
                            String nm = v.prompt("Please enter the name of the book: ", Validator.REQUIRED, "Name is a required field.");
                            while(true) {
                                pr = v.prompt("Please enter the price: ");
                                int cmp = Validator.parseInt(pr);
                                if (cmp > 0) break;
                            }
                            while (true) {
                                yr = v.prompt("Please enter the product year: ", "[0-9]{4}", "Please enter a valid year. ####");
                                int cmp = Validator.parseInt(yr);
                                if (cmp > 1000 && cmp < 10000) break;
                            }
                            
                            String au = v.prompt("Please enter the book author: ");
                            String pb = v.prompt("Please enter the book publisher : ");
                            
                            Book newBook;
                            try {
                                newBook = new Book(id,nm,pr,yr,au,pb);
                            } catch (Exception ex) {
                                System.err.println("Unable to create book: "+ex.getMessage());
                                break;
                            }
                            
                            //  Add to the eStore check status
                            if(myStore.add(newBook)) {
                                System.out.println("The book was saved successfully!\n");
                            } else {
                                System.out.println("Failed to save! Duplicate ID given.\n");
                            }
                            break;
                        case 2:
                            id = v.prompt("Please enter the product id: ", "[0-9]{6}", "Please enter a 6 digit id.");
                            nm = v.prompt("Please enter the name of the product: ", Validator.REQUIRED, "Name is a required field.");
                            while(true) {
                                pr = v.prompt("Please enter the price: ");
                                int cmp = Validator.parseInt(pr);
                                if (cmp > 0) break;
                            }
                            while (true) {
                                yr = v.prompt("Please enter the product year: ", "[0-9]{4}", "Please enter a valid year. ####");
                                int cmp = Validator.parseInt(yr);
                                if (cmp > 1000 && cmp < 10000) break;
                            }
                            String mk = v.prompt("Please enter the product maker: ");
                            
                            Electronic elec;
                            try {
                                elec = new Electronic(id,nm,pr,yr,mk);
                            } catch (Exception ex) {
                                System.err.println("Unable to create book: "+ex.getMessage());
                                break;
                            }
                            
                            //  Add to the eStore check status
                            if(myStore.add(elec)) {
                                System.out.println("Saved successfully!\n");
                            } else {
                                System.out.println("Failed to save! Duplicate ID given.\n");
                            }
                            break;
                    }
                    break;
                case "s": //  Search case
                    System.out.println("Search Selected\n----------------------");
                    String prod = v.prompt("  Query a Product ID: ");
                    String nm = v.prompt("Query a Product Name: ");
                    String yr = v.prompt("Query a Product Year: ");
                    
                    System.out.println("\n");
                    ArrayList<Product> searchResults = myStore.search(prod, nm, yr);
                    for (int i = 0; i < searchResults.size(); i++) {
                        //  Get the object
                        Product item = searchResults.get(i);
                        System.out.println(item.toString());
                    }
                    System.out.println("\n");
                    break;
                default:        //  Condition (3) exit the program
                    System.out.println("Thank you, come again.");
                    dumpFile(myStore,args[0]);
                    break;
            }
        } while(!answer.equals("q")); 
    }
    
}
