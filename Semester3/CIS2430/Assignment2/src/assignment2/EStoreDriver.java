package assignment2;

/**
 * Testing driver for EStore class.
 * @author Carter
 */
public class EStoreDriver {

    public static void main(String[] args) {
         //  Create a tester
        Tester test = new Tester();
        
        //  Begin test
        System.out.println("Testing EStore...");
        
        //  Create a store and some books
        EStore myStore = new EStore();
        
        //  Step 1: Create of the same book.
        Book a = null, b = null, c = null;
        try {
            a = new Book("123456", "Some name", "10","2014","","");
            b = new Book("123456", "Some name", "25","2014","","");
        } catch (Exception ex) {
            System.err.println("Unable to create object: " + ex.getMessage());
        }
       
        test.description("Testing addBook function.");
        test.assertTrue("Book a is added to the list",myStore.add(a));
        test.assertFalse("Book b is not added to the list", myStore.add(b));
    }
    
}
