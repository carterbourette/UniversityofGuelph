/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class FileIO {
    
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
}
