package assignment3;

/**
 * The main class, implementation of an electronic store and search.
 * @author Carter
 */
public class Assignment3 {


    public static void main(String[] args) {
        
        EStoreGUI myInterface = new EStoreGUI();
        try{    //  Get the product list from file
            System.out.println("Loading " + args[0] +"...");
            FileIO.readFile(myInterface.listener.myStore,args[0]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.println("Load the program with a command line argument to load inventory.");
        }
        myInterface.setVisible(true);    
        
        
    }
    
}
