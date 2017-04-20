package assignment1;

/**
 * Book Class, creates instance of a book object inheriting the properties of Object class.
 * @author Carter
 */
public class Book extends Product {
    private String author;
    private String publisher;
    
    /**
     * Creates an  instance of a book.
     */
    public Book() { 
      this.author = "";
      this.publisher = "";
    }
    
    /**
     * Creates an instance of a book.
     * @param prodID The item product id.
     * @param nm The item name.
     * @param yr The item year.
     */
    public Book(String prodID, String nm, String yr) {
        this.setProductID(prodID);
        this.setName(nm);
        this.setYear(yr);
        this.author = "";
        this.publisher = "";
    }
    
    //  Accessor methods
    /**
     * Get the author of the Book.
     * @return The author.
     */
    public String getAuthor() {
        return this.author;
    }
    
    /**
     * Get the publisher of the Book.
     * @return The publisher.
     */
    public String getPublisher() {
        return this.publisher;
    }
    
    //  Mutator methods
    /**
     * Set the author of the book.
     * @param str The value to set author.
     * @return Status
     */
    public boolean setAuthor(String str) {
        this.author = str;
        return true;
    }
    
    /**
     * Set the publisher of the book.
     * @param str The value to set publisher.
     * @return Status
     */
    public boolean setPublisher(String str) {
        this.publisher = str;
        return true;
    }
    
    /**
     *  Print the object to command prompt.
     */
    public void printBook() {
        System.out.println("Product ID:\t" + this.getProductID());
        System.out.println("      Name:\t" + this.getName());
        System.out.println("     Price:\t" + this.getPrice());
        System.out.println("      Year:\t" + this.getYear());
        System.out.println("   Authors:\t" + this.getAuthor());
        System.out.println("Publishers:\t" + this.getPublisher());
        System.out.println("\n");
    }
    
    /**
     * Check that the passed book is equal to your book.
     * @param e The book to compare 
     * @return true if the passed book is equal to this book.<br>false otherwise.
     */
    public boolean equals(Book e){
        //  Compare this to all properties of a passed book b
        if(this.getProductID().equals(e.getProductID()) && this.getName().equals(e.getName()) && this.getPrice().equals(e.getPrice()) && this.getYear().equals(e.getYear()) && this.getAuthor().equals(e.getAuthor()) && this.getPublisher().equals(e.getPublisher())) {
            return true;
        }
        return false;
    }
    
    /**
     * Return the book as a string.
     * @return The object in string form
     */
    public String toString() {
        return "Product ID:\t" + this.getProductID() +
                "      Name:\t" + this.getName() +
                "     Price:\t" + this.getPrice() +
                "      Year:\t" + this.getYear() +
                "   Authors:\t" + this.getAuthor() + 
                "Publishers:\t" + this.getPublisher();
    }
}