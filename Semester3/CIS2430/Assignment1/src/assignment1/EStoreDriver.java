package assignment1;

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
        Book a = new Book("123456", "Some name", "2014");
        Book b = new Book("123456", "Some name", "2014");
        
        //  Step 2: Create a different book.
        Book c = new Book("654", "Some name", "201");
        
        test.description("Testing addBook function.");
        test.assertTrue("Book a is added to the list",myStore.addBook(a));
        test.assertFalse("Book b is not added to the list", myStore.addBook(b));
    }
    
}
