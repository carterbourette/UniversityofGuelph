package assignment1;

/**
 * Object is a class that defines common properties of Books and Electronics.
 * @author Carter
 */
public abstract class Product {
    
    //  These properties will be in herited by Book and Electronic
    private String productID;
    private String name;
    private String price;
    private String year;
 
    /**
     * Called from child as Object is abstract.
     */
    public Product() {
        this.productID = "";
        this.name = "";
        this.price = "";
        this.year = "";
    }
    
    //  Accessor methods
    /**
     * Get the product id of the object.
     * @return The product id.
     */
    public String getProductID() {
        return this.productID;
    }
    
    /**
     * Get the name of the object,
     * @return The product name.
     */
    public String getName() {
        return this.name;
    }
    
    /**
     * Get the price of the object.
     * @return The product price.
     */
    public String getPrice() {
        return this.price;
    }
    
    /**
     * Get the year of the object.
     * @return The year of the object.
     */
    public String getYear() {
        return this.year;
    }
    
    //  Mutator methods
    /**
     * Set the product id of the object.
     * @param str Value to set ProductID
     * @return Status
     */
    public boolean setProductID(String str) {
        String cpy = this.productID;
        this.productID = str; 
        if(!this.isValidID()) {
            this.productID = cpy;
            return false;
        }
        return true;
    }
    
    /**
     * Set the name of the object.
     * @param str Value to set Name
     * @return true if name has been set.<br>false if the set failed.
     */
    public boolean setName(String str) {
        this.name = str;
        return !this.name.equals("");
    }
    
    /**
     * Set the price of the object.
     * @param str Value to set price.
     * @return true if price has been set.<br>false if the set failed.
     */
    public boolean setPrice(String str) {
        this.price = str;
        return true;
    }
    
    /**
     * Set the year of the object.
     * @param str Value to set year.
     * @return true if year has been set.<br>false if the set failed.
     */
    public boolean setYear(String str) {
        String cpy = this.year;
        this.year = str; 
        if(!this.isValidYear()) {
            this.year = cpy;
            return false;
        }
        return true;
    }
    
    /**
     * Check that the id is valid.
     * @return true if id is valid.<br>false if id is invalid.
     */
    public boolean isValidID() {
        String id = this.getProductID();
        //  Rules: must be 6 digits, no duplicates
        if (id.length() == 6) {
            if (isInteger(id)) {
               return true;
            }
        }
        return false;
    }
    
    /**
     * Check that the year is valid.
     * @return true if year is valid.<br>false if year is invalid.
     */
    public boolean isValidYear() {
        String yr = this.getYear();
        //  Rules: must be 6 digits, no duplicates
        if (yr.length() == 4) {
            if (isInteger(yr)) {
                int ye = Integer.parseInt(yr);
                if (ye >= 1000 && ye <= 9999)
                    return true;
            }
        }
        return false;
    }
    
    /**
     * Check that the passed value is an integer.
     * @param str String to convert to integer
     * @return true if string passed is an integer.
     */
    private static boolean isInteger(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}
