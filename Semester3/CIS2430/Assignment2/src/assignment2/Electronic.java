package assignment2;

/**
 * Electronic Class, creates instance of an electronic object inheriting the properties of Object class.
 * @author Carter
 */
public class Electronic extends Product {
    private String maker;
    
    /**
     * Default constructor
     */
    public Electronic() {
        this.maker = "";
    }
    
    /**
     * Copy Constructor using static newInstance
     * @param e Electronic Object to copy
     * @return Electronic
     * @throws java.lang.Exception Invalid values.
     */
    public static Electronic newInstance(Electronic e) throws Exception {
        return new Electronic(e.getProductID(),e.getName(),e.getPrice(),e.getYear(),e.getMaker());
    }
    
    /**
     * The electronic constructor.
     * @param prodID ProductID
     * @param nm Name
     * @param price Price
     * @param yr Year
     * @param maker Maker
     * @throws java.lang.Exception
     */
    public Electronic(String prodID,String nm, String price, String yr, String maker) throws Exception {
        super(prodID,nm,price,yr);
        this.maker = maker;
    }
    
    /**
     * Get the maker of the electronic.
     * @return value of Maker
     */
    public String getMaker() {
        return this.maker;
    }
    
    /**
     * Set the maker of the electronic.
     * @param str - The string to set
     * @return Status
     */
    public boolean setMaker(String str) {
        this.maker = str;
        return true;
    }
    
    /**
     * Return the data form to store to file. (Type .ini)
     * @return String of storage format.
     */
    public String toStorageFormat() {
        return "type = \"electronic\"" +
                "\nproductID = \"" + this.getProductID() + "\"" +
                "\nname = \"" + this.getName() + "\"" +
                "\nprice = \"" + this.getPrice() + "\"" +
                "\nyear = \"" + this.getYear() + "\"" +
                "\nmaker = \"" + this.getMaker() + "\"" +
                "\n";
    }
     
    /**
     * Check if the passed electronic is equal.
     * @param e - The Electronic object to check against
     * @return true if the electronic is equal.<br>false if the electronic is not equal.
     */
    public boolean equals(Electronic e){
        if(e == null) return false;
        else if(getClass() != e.getClass()) return false;
        else {
            Electronic elec = e;
            return this.getProductID().equals(elec.getProductID()) && this.getName().equals(elec.getName()) && this.getPrice().equals(elec.getPrice()) && this.getYear().equals(elec.getYear()) && this.getMaker().equals(elec.getMaker());
        }
    }
    
    /**
     * Return the object as a string.
     * @return String value of the object
     */
    public String toString() {
        return "Product ID:\t" + this.getProductID() + "\n" +
                "      Name:\t" + this.getName() + "\n" +
                "     Price:\t" + this.getPrice() + "\n" +
                "      Year:\t" + this.getYear() + "\n" +
                "     Maker:\t" + this.getMaker() + "\n";
    }
    
}

