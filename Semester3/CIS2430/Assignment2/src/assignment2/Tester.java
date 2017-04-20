package assignment2;

/**
 * The Tester class is used to create assertions in a driver.
 * @author Carter
 */
public class Tester {
    
    /**
     * An assertion is made that the passed value is true.
     * @param str Description of assertion.
     * @param a The function to call.
     * @return Status of assertion.
     */
    public boolean assertTrue(String str, boolean a) {
        if (a) {
            System.out.println("The " + str + " test passed.");
            return true;
        }
        System.err.println("The " + str + " test failed.");
        return false;
    }
    
    /**
     * An assertion is made that the passed value is false.
     * @param str Description of assertion.
     * @param a The function to call.
     * @return Status of assertion.
     */
    public boolean assertFalse(String str, boolean a) {
        if (!a) {
            System.out.println("The " + str + " test passed.");
            return true;
        } 
        System.err.println("The " + str + " test failed.");
        return false;
    }
    
    /**
     * An assertion is made that the passed values are equal.
     * @param str Description of assertion.
     * @param a The string to compare.
     * @param b The string to compare.
     * @return Status of assertion.
     */
    public boolean assertEqual(String str, String a, String b) {
        if (a.equals(b)) {
            System.out.println("The " + str + " test passed.");
            return true;
        }
        System.err.println("The " + str + " test failed.");
        return false;
    }
    
    /**
     * An assertion is made that the passed values are equal.
     * @param str Description of assertion.
     * @param a The integer to compare.
     * @param b The integer to compare.
     * @return Status of assertion.
     */
    public boolean assertEqual(String str, int a, int b) {
        if (a == b) {
            System.out.println("The " + str + " test passed.");
            return true;
        }
        System.err.println("The " + str + " test failed.");
        return false;
    }   

    /**
     * Message to output to screen to organize assertions.
     * @param str The text to output.
     */
    void description(String str) {
        System.out.print("\n");
        System.out.println(str);
    }
}
