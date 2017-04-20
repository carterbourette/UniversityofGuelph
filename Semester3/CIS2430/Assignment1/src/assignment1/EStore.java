package assignment1;

import java.util.ArrayList;

/**
 * Creates an electronic store capable of sorting and storing lists.
 * @author Carter
 */
public class EStore {
    //  Let's create some lists to store our objects
    private ArrayList books;
    private ArrayList electronics;

    public EStore() {
        this.books = new ArrayList();
        this.electronics = new ArrayList();
    }

    /**
     * Check the lists for duplicate product id's
     * @param item The object being added to a list.
     * @return Status
     */
    public boolean checkIfDuplicateID(Product item) {
        //  iterate through book list
        for(int i = 0; i < this.books.size(); i++) {
            Book aBook = (Book)this.books.get(i);
            //  Check to see if the new item has a duplicate ID
            if(item.getProductID().equals(aBook.getProductID())) {
                return true;
            }
        }
        //  iterate through electronics list
        for(int i = 0; i < this.electronics.size(); i++) {
            Electronic anElectronic = (Electronic)this.electronics.get(i);
            //  Check to see if the new item has a duplicate ID
            if(item.getProductID().equals(anElectronic.getProductID())) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Add book to book list.
     * @param book Book to add to the list.
     * @return true if the book was added.<br>false if the book was not added.
     */
    public boolean addBook(Book book) {
        //  If the ID doesn't already exist add it to the list
        if(!checkIfDuplicateID(book)){
            this.books.add(book);
            return true;
        }
        return false;
    }    
    
    /**
     * Add electronic to electronics list.
     * @param e Electronic to add to the list
     * @return true if the book was added.<br>false if the book was not added.
     */
    public boolean addElectronic(Electronic e) {
        //  If the ID doesn't already exist add it to the list
        if(!checkIfDuplicateID(e)){
            this.electronics.add(e);
            return true;
        }
        return false;
    }
    
    /**
     * Search book list for given parameters
     * @param prodID The product id (######)
     * @param name The product name
     * @param year The product year
     * @return ArrayList of found books
     */
    public ArrayList searchBooks(String prodID, String name, String year) {
        ArrayList bookList = new ArrayList();
        Book temp;
        int iYear;
        
        for (int i = 0; i < this.books.size(); i++) {
            temp = (Book)this.books.get(i);
            boolean contains = false;
            
           if (temp.getProductID().equals(prodID) || prodID.equals("")) {
               
                //  Check name matches
                if (name.equals("")) {
                    contains = true;
                } else {
                   String[] tNameSplit = name.split(" ");
                   String nm = temp.getName();
                   for (int k = 0; k < tNameSplit.length; k++) {
                       if (nm.contains(tNameSplit[k])) {
                           contains = true;
                           break;
                       }
                   }    
                }
               //   Check year matches
               if (year.contains("-")) {
                    iYear = Integer.parseInt(temp.getYear());
                    if (year.substring(0,1).equals("-")) {
                        if (Integer.parseInt(year.substring(1)) >= iYear) {
                            if(contains) bookList.add(temp);
                        }
                    } else if (year.substring(year.length()-1,year.length()).equals("-")) {
                        if (Integer.parseInt(year.substring(0,year.length()-1)) <= iYear) {
                            if(contains) bookList.add(temp);
                        }
                    } else {
                        //  range start/end specified we can split
                        String[] arr = year.split("-");
                        
                        if (iYear <= Integer.parseInt(arr[0]) && iYear >= Integer.parseInt(arr[1])) {
                           if(contains) bookList.add(temp);
                        }
                    }
                } else {
                    //  Year isn't a range
                    if (year.equals(temp.getYear()) || year.equals("")) {
                        if(contains) bookList.add(temp);
                    }
                }
           }
        }
        return bookList;
    }
    
    /**
     * Search electronic list for given parameters
     * @param prodID The product id (######)
     * @param name The product name
     * @param year The product year.
     * @return ArrayList of found electronics.
     */
    public ArrayList searchElectronics (String prodID, String name, String year) {
        ArrayList elec = new ArrayList();
         
        Electronic temp;
        int iYear;
        
        for (int i = 0; i < this.electronics.size(); i++) {
            temp = (Electronic)this.electronics.get(i);
            boolean contains = false;
            
           if (temp.getProductID().equals(prodID) || prodID.equals("")) {
               
                //  Check name matches
                if (name.equals("")) {
                    contains = true;
                } else {
                   String[] tNameSplit = name.split(" ");
                   String nm = temp.getName();
                   for (int k = 0; k < tNameSplit.length; k++) {
                       if (nm.contains(tNameSplit[k])) {
                           contains = true;
                           break;
                       }
                   }    
                }
               //   Check year matches
               if (year.contains("-")) {
                    iYear = Integer.parseInt(temp.getYear());
                    if (year.substring(0,1).equals("-")) {
                        if (Integer.parseInt(year.substring(1)) >= iYear) {
                            if(contains) elec.add(temp);
                        }
                    } else if (year.substring(year.length()-1,year.length()).equals("-")) {
                        if (Integer.parseInt(year.substring(0,year.length()-1)) <= iYear) {
                            if(contains) elec.add(temp);
                        }
                    } else {
                        //  range start/end specified we can split
                        String[] arr = year.split("-");
                        
                        if (iYear <= Integer.parseInt(arr[0]) && iYear >= Integer.parseInt(arr[1])) {
                           if(contains) elec.add(temp);
                        }
                    }
                } else {
                    //  Year isn't a range
                    if (year.equals(temp.getYear()) || year.equals("")) {
                        if(contains) elec.add(temp);
                    }
                }
           }
        }
        return elec;
    }
    
    /**
     * Prints the book list
     */
    public void printBooks() {
        ArrayList list = this.books;
        for (int i = 0; i < list.size(); i++) {
            //  Get the object
            Book item = (Book)list.get(i);
            item.printBook();
        }
    }
    
    /**
     * Prints the electronics list
     */
    public void printElectronics() {
        ArrayList list = this.electronics;
        for (int i = 0; i < list.size(); i++) {
            //  Get the object
            Electronic item = (Electronic)list.get(i);
            item.printElectronic();
        }
    }
}