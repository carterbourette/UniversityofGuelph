package assignment2;

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
     * @param price The item price.
     * @param yr The item year.
     * @param au The author of the book.
     * @param pub The publisher of the book.
     * @throws java.lang.Exception
     */
    public Book(String prodID, String nm, String price, String yr, String au, String pub) throws Exception {
        super(prodID,nm,price,yr);
        this.author = au;
        this.publisher = pub;
    }
    
    /**
     * Copy Constructor using static newInstance
     * @param b Book Object to copy
     * @return Book
     * @throws java.lang.Exception Invalid values.
     */
    public static Book newInstance(Book b) throws Exception {
        return new Book(b.getProductID(),b.getName(),b.getYear(), b.getPrice(), b.getAuthor(),b.getPublisher());
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
     * Return the data form to store to file. (Type .ini)
     * @return String of storage format.
     */
    public String toStorageFormat() {
        return "type = \"book\"" +
                "\nproductID = \"" + this.getProductID() + "\"" +
                "\nname = \"" + this.getName() + "\"" +
                "\nprice = \"" + this.getPrice() + "\"" +
                "\nyear = \"" + this.getYear() + "\"" +
                "\nauthor = \"" + this.getAuthor() + "\"" +
                "\npublisher = \"" + this.getPublisher() + "\"" +
                "\n";
    }
    
    /**
     * Check that the passed book is equal to your book.
     * @param e The book to compare 
     * @return true if the passed book is equal to this book.<br>false otherwise.
     */
    public boolean equals(Object e){
        if(e == null) return false;
        else if(getClass() != e.getClass()) return false;
        else {
            Book eBook = (Book)e;
            return this.getProductID().equals(eBook.getProductID()) && this.getName().equals(eBook.getName()) && this.getPrice().equals(eBook.getPrice()) && this.getYear().equals(eBook.getYear()) && this.getAuthor().equals(eBook.getAuthor()) && this.getPublisher().equals(eBook.getPublisher());
        }
    }

    /**
     * Return the book as a string.
     * @return The object in string form
     */
    public String toString() {
        return "Product ID:\t" + this.getProductID() + "\n" +
                "      Name:\t" + this.getName() + "\n" +
                "     Price:\t" + this.getPrice() + "\n" +
                "      Year:\t" + this.getYear() + "\n" +
                "   Authors:\t" + this.getAuthor() + "\n" +
                "Publishers:\t" + this.getPublisher() + "\n";
    }
}