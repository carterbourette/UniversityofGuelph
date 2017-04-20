package assignment2;

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
        Book a = null,b = null,c = null;
        try {
            a = new Book("123456", "Some name", "90","2014","","");
            b = new Book("654321", "Some name", "10","2014","","");
            c = new Book("987654", "Some name", "20","1111","","");
        } catch (Exception ex) {
            System.err.println("Unable to create object: " + ex.getMessage());
        }
        
        test.description("Testing book .equals function.");
        test.assertFalse("Book a does not equals book b",a.equals(b));
        test.assertFalse("Book a is not equal to book c", a.equals(c));
        
        test.description("Testing object class .isValidProductID function.");
        test.assertTrue("123456 is a valid Product ID", a.isValidID());
        test.assertTrue("987654 is a valid Product ID", c.isValidID());
        
        test.description("Testing object class .isValidYear function.");
        test.assertTrue("2014 is a valid Year", a.isValidYear());
        
        test.description("Testing object .setProductID function.");
        test.assertTrue("123456 can be set as Product ID", a.setProductID("123456"));
        test.assertFalse("654 can not be set Product ID", c.setProductID("654"));
    }
    
}
