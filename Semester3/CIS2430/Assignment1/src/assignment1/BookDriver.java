package assignment1;

/**
 * Testing driver for book class.
 * @author Carter
 */
public class BookDriver {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        //  Create a tester
        Tester test = new Tester();
        
        //  Begin test
        System.out.println("Testing Book...");
        
        //  Step 1: Create of the same book.
        Book a = new Book("123456", "Some name", "2014");
        Book b = new Book("123456", "Some name", "2014");
        
        //  Step 2: Create a different book.
        Book c = new Book("654", "Some name", "201");
        
        test.description("Testing book .equals function.");
        test.assertTrue("Book a equals book b",a.equals(b));
        test.assertFalse("Book a is not equal to book c", a.equals(c));
        
        test.description("Testing object class .isValidProductID function.");
        test.assertTrue("123456 is a valid Product ID", a.isValidID());
        test.assertFalse("654 is not a valid Product ID", c.isValidID());
        
        test.description("Testing object class .isValidYear function.");
        test.assertTrue("2014 is a valid Year", a.isValidYear());
        test.assertFalse("654 is not a valid Year", c.isValidYear());
        
        test.description("Testing object .setProductID function.");
        test.assertTrue("123456 can be set as Product ID", a.setProductID("123456"));
        test.assertFalse("654 can not be set Product ID", c.setProductID("654"));
    }
    
}
