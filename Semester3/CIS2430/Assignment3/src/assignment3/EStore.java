package assignment3;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Creates an electronic store capable of sorting and storing lists.
 * @author Carter
 */
public class EStore {
    //  Let's create some lists to store our objects
    private ArrayList<Product> products;
    private HashMap<String, ArrayList<Integer>> index = new HashMap<>();

    public EStore() {
        this.products = new ArrayList<>();
    }
    
    /**
     * Return the product list.
     * @return The array list containing products.
     */
    public ArrayList<Product> getProductList() {
        return this.products;
    }
    
    /**
     * Get the map from the hashIndex
     * @param searchStr the index value to search. i.e. A Product substring.
     * @return The array list of product indices.
     */
    public ArrayList<Integer> getIndexMap(String searchStr) {
        return this.index.get(searchStr.toLowerCase());
    }

    /**
     * Check the lists for duplicate product id's
     * @param item The object being added to a list.
     * @return Status
     */
    public boolean checkIfDuplicateID(Product item) {
        //  iterate through book list
        for(int i = 0; i < this.products.size(); i++) {
            Product prod = this.products.get(i);
            //  Check to see if the new item has a duplicate ID
            if(item.getProductID().equals(prod.getProductID())) {
                return true;
            }
        }
        return false;
    }  
    
    /**
     * Add a product or electronic to the list.
     * @param prod The product to add to the list.
     * @return True if book was added.<br>False if the book was not added.
     */
    public boolean add(Product prod) {
        if(prod != null && !checkIfDuplicateID(prod) && prod.isValid()){
            this.products.add(prod);
            this.index(prod,this.products.size()-1);
            return true;
        }
        return false;
    }
    
    /**
     * Returns only intersecting values in two lists.
     * @param l1 The first list.
     * @param l2 The second list.
     * @return The list of intersecting values.
     */
    public ArrayList<Integer> mapIntersection(ArrayList<Integer> l1, ArrayList<Integer> l2) {
        ArrayList<Integer> list = new ArrayList<>();
        for (Integer item : l1) {
            for (Integer item2 : l2) {
                if(item == item2) {
                    list.add(item);
                }
            }
        }
        return list;
    }
    
    /**
     * Create an indexed hash map.
     * @param item The Product to index.
     * @param index The index of the item in the list
     */
    public void index (Product item, int index) {
        ArrayList<Integer> list;
        String it = item.getName().toLowerCase();
        for (String c : it.split(" ")) {
            list = this.index.get(c);
            if (list == null) {
                list = new ArrayList<>();
                list.add(index);
                this.index.put(c, list);
            } else {
                list.add(index);
                this.index.put(c, list);
            }
            
        }  
    }
    
    /**
     * Print the current value of the index.
     */
    public void printIndex() {
        for (String key : this.index.keySet()) {
            System.err.print(key + " :" );
            ArrayList<Integer> list = this.index.get(key);
            for (int i = 0; i < list.size(); i++) {
                System.err.print(" " + list.get(i));
            }
            System.out.println("\n");
        }
    }
    
    /**
     * Check to see if a product contains an ID.
     * @param item The product to check.
     * @param prodID The ID to compare against.
     * @return Status T | F
     */
    private boolean containsProdID(Product item, String prodID) {
        String str = item.getProductID();
        return str.equals(prodID) || prodID.equals("");
    }
    
    /**
     * Check to see if a product contains a year.
     * @param item The product to check.
     * @param year The year string to compare against.
     * @return Status T | F
     */
    private boolean containsYear(Product item, String year) {
         if (year.contains("-")) {
            int iYear = Integer.parseInt(item.getYear());
            if (year.substring(0,1).equals("-")) {
                if (Integer.parseInt(year.substring(1)) >= iYear) {
                    return true;
                }
            } else if (year.substring(year.length()-1,year.length()).equals("-")) {
                if (Integer.parseInt(year.substring(0,year.length()-1)) <= iYear) {
                    return true;
                }
            } else {
                //  range start/end specified we can split
                String[] arr = year.split("-");
                if (iYear >= Integer.parseInt(arr[0]) && iYear <= Integer.parseInt(arr[1])) {
                   return true;
                }
            }
        } else {
            //  Year isn't a range
            if (year.equals(item.getYear()) || year.equals("")) {
                return true;
            }
        }
        
        return false;
    }
    
     /**
     * Search product list for given parameters
     * @param prodID The product id (######)
     * @param name The product name
     * @param year The product year.
     * @return ArrayList of found products.
     */
    public ArrayList<Product> search (String prodID, String name, String year) {
        //  Determine size of list
        ArrayList<Product> list = new ArrayList<>();
        if (!name.equals("")) {
            //  Size of list is in hash index
            ArrayList<Integer> prev = null;
            for (String str : name.toLowerCase().split(" ")) {
                ArrayList<Integer> l = this.getIndexMap(str);
                if (prev != null)
                    prev = this.mapIntersection(prev, l);
                else 
                    prev = l;
            }
            if(prev != null) {
                for (int i = 0; i < prev.size(); i++) {
                    Product temp = this.products.get(prev.get(i));
                    if(this.containsProdID(temp,prodID) && this.containsYear(temp,year))
                        list.add(temp);
                }
            }
        } else {
            //  Size is the entire list.
            for (int i = 0; i < this.products.size(); i++) {
                Product temp = this.products.get(i);
                if(this.containsProdID(temp,prodID) && this.containsYear(temp,year))
                    list.add(temp);
            }
        }
        return list;
    }
    
    /**
     * Prints the book list
     */
    public void print() {
        for (int i = 0; i < this.products.size(); i++) {
            //  Get the object
            Product item = this.products.get(i);
            System.out.println(item.toString());
        }
    }
}