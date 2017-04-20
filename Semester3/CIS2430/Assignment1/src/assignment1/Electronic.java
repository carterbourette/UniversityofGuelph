package assignment1;

/**
 * Electronic Class, creates instance of an electronic object inheriting the properties of Object class.
 * @author Carter
 */
public class Electronic extends Product {
    private String maker;
    
    public Electronic() {
        this.maker = "";
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
     *  Print the object to command prompt.
     */
    public void printElectronic () {
        System.out.println("Product ID:\t" + this.getProductID());
        System.out.println("      Name:\t" + this.getName());
        System.out.println("     Price:\t" + this.getPrice());
        System.out.println("      Year:\t" + this.getYear());
        System.out.println("     Maker:\t" + this.getMaker());
        System.out.println("\n");
    }
     
    /**
     * Check if the passed electronic is equal.
     * @param e - The Electronic object to check against
     * @return true if the electronic is equal.<br>false if the electronic is not equal.
     */
    public boolean equals(Electronic e){
        //  Compare this to all properties of a passed book b
        if(this.getProductID().equals(e.getProductID()) && this.getName().equals(e.getName()) && this.getPrice().equals(e.getPrice()) && this.getYear().equals(e.getYear()) && this.getMaker().equals(e.getMaker())) {
            return true;
        }
        return false;
    }
    
    /**
     * Return the object as a string.
     * @return String value of the object
     */
    public String toString() {
        return "Product ID:\t" + this.getProductID() +
                "      Name:\t" + this.getName() +
                "     Price:\t" + this.getPrice() +
                "      Year:\t" + this.getYear() +
                "     Maker:\t" + this.getMaker();
    }
    
}

