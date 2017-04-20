package assignment1;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * The main class, implementation of an electronic store and search.
 * @author Carter
 */
public class Assignment1 {

    /**
     * Get input from command prompt as string.
     * @param obj Scanner object for input
     * @return String
     */
    public static String getString(Scanner obj) {
        String str = obj.nextLine();
        //obj.nextLine();
        return str;
    }
    
    /**
     * Get input from command prompt as integer.
     * @param obj Scanner object for input
     * @return integer requested
     */
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
     * Provide a command loop until the user provides valid input.
     * @param obj  Scanner object for input
     * @param arr  The menu array
     * @param validResponses String array of possible responses
     * @return answer  Integer value of the response
     */
    public static int loopUntilValidResponse(Scanner obj, String[] arr, String[] validResponses) {
        boolean running = true;
        String answer;
        
        int answerInt = 1;
        
        while(running) {
            answerInt = 1;
            //  Print the menu
            for (int i = 0; i < arr.length; i++) {
                System.out.println(arr[i]);
            }
            System.out.print("Please enter a command: ");
            answer = getString(obj);
           
            for (String word : validResponses) {
                if(answer.toLowerCase().contains(word)) {
                    running = false;
                    break;
                }
                answerInt++;
            }
            if(running) System.out.println("Command not found... Try again...\n");
        }
        return answerInt;
    }
    
    public static void main(String[] args) {
        //  Create a scanner for user input
        Scanner input = new Scanner(System.in);
        
        //  Create an instance of our Electronic Store
        EStore myStore = new EStore();
 
        //  Define the user menu
        String[] menu = new String[3];
        menu[0] = "Type 'add' to add book/electronic.";
        menu[1] = "Type 'search' to search.";
        menu[2] = "Type 'quit' to quit.\n";
        
        int answer = 0;
         
        do {    //  Command Loop - for add search and quit
            String[] menu2 = new String[2];
            answer = loopUntilValidResponse(input, menu, new String[]{"a","s","q"});
            //  Delegate the tasks...
            switch (answer) {
                case 1: //  Add case
                    menu2[0] = "Type 'book' to add a book.";
                    menu2[1] = "Type 'electronic' to add an electronic.\n";
                    int reply = loopUntilValidResponse(input,menu2, new String[]{"b","e"});
                    boolean noerror = false;
                    
                    switch(reply) {
                        case 1:
                            //  Create a book
                            Book newBook = new Book();
                           
                            //  Get book inputs
                            do {
                                System.out.print("Please enter the book product id: ");
                                noerror = newBook.setProductID(getString(input));
                                if (!noerror) System.out.println("Product ID is a required field!\nPlease enter the 6 digit number.");
                                if (myStore.checkIfDuplicateID(newBook)) {
                                    noerror = false;
                                    System.out.println("Product ID was found in list.");
                                }
                            } while (!noerror);
                            
                            do {
                                System.out.print("Please enter the book name: ");
                                noerror = newBook.setName(getString(input));
                                if (!noerror) System.out.println("Product name is a required field!\nPlease enter a non null value.");
                            } while (!noerror);
                            
                            System.out.print("Please enter the book price: $");
                            newBook.setPrice(getString(input));
                            
                            do {
                                System.out.print("Please enter the book year (####): ");
                                noerror = newBook.setYear(getString(input));
                                if (!noerror) System.out.println("Product year is a required field!\nPlease enter a value between 1000-9999.");
                            } while (!noerror);
                            
                            System.out.print("Please enter the book author: ");
                            newBook.setAuthor(getString(input));
                            System.out.print("Please enter the book publisher: ");
                            newBook.setPublisher(getString(input));
                            System.out.print("\n");
                            
                            //  Add to the eStore check status
                            if(myStore.addBook(newBook)) {
                                System.out.println("The book was saved successfully!");
                            } else {
                                System.out.println("Failed to save! Duplicate ID given.\n");
                            }
                            break;
                        case 2:
                            //  Create electronics
                            Electronic elec = new Electronic();
                           
                            //  Get book inputs
                            do {
                                System.out.print("Please enter the product id: ");
                                noerror = elec.setProductID(getString(input));
                                if (!noerror) System.out.println("Product ID is a required field!\nPlease enter the 6 digit number.");
                                if (myStore.checkIfDuplicateID(elec)) {
                                    noerror = false;
                                    System.out.println("Product ID was found in list.");
                                }
                            } while (!noerror);
                            
                            do {
                                System.out.print("Please enter the name: ");
                                noerror = elec.setName(getString(input));
                                if (!noerror) System.out.println("Product name is a required field!\nPlease enter a non null value.");
                            } while (!noerror);
                            
                            System.out.print("Please enter the price: $");
                            elec.setPrice(getString(input));
                            
                            do {
                                System.out.print("Please enter the year (####): ");
                                noerror = elec.setYear(getString(input));
                                if (!noerror) System.out.println("Product year is a required field!\nPlease enter a value between 1000-9999.");
                            } while (!noerror);
                            
                            System.out.print("Please enter the maker: ");
                            elec.setMaker(getString(input));
                            System.out.print("\n");
                            
                            //  Add to the eStore check status
                            if(myStore.addElectronic(elec)) {
                                System.out.println("Saved successfully!");
                            } else {
                                System.out.println("Failed to save! Duplicate ID given.\n");
                            }
                            break;
                    }
                    break;
                case 2: //  Search case
                    System.out.println("Search Selected");
                    System.out.println("----------------------");
                    System.out.print("  Query a Product ID: ");
                    String prod = getString(input);
                    
                    System.out.print("Query a Product Name: ");
                    String nm = getString(input);
                    
                    System.out.print("Query a Product Year: ");
                    String yr = getString(input);
                    System.out.print("\n");
                    
                    ArrayList searchResults = myStore.searchBooks(prod, nm, yr);
                    if(!searchResults.isEmpty()) System.out.println("Books:");
                    for (int i = 0; i < searchResults.size(); i++) {
                        //  Get the object
                        Book item = (Book)searchResults.get(i);
                        item.printBook();
                    }
                    searchResults = myStore.searchElectronics(prod, nm, yr);
                    if(!searchResults.isEmpty()) System.out.println("Electronics:");
                    for (int i = 0; i < searchResults.size(); i++) {
                        //  Get the object
                        Electronic item = (Electronic)searchResults.get(i);
                        item.printElectronic();
                    }
                    break;
                default:
                    //  Condition (3) exit the program
                    System.out.println("Thank you, come again.");
                    break;
            }
        } while(answer !=3); 
    }
    
}
