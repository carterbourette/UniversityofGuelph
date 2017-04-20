package assignment3;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Helper class to ease input validation.
 * @author Carter
 */
public class Validator {
    
    /*         Regex string for each input        */
    public static final String INTEGER = "[0-9]+";
    public static final String DOUBLE = "[0-9]+\\.[0-9]+";
    public static final String BOOLEAN = "true||false";
    public static final String REQUIRED = "[0-9a-z ]+";
    
    private Scanner input;
    String value;
 
    /**
     * The default constructor Initialize input scanner.
     */
    public Validator() {
        this.input = new Scanner(System.in);
    }
   
    /**
     * Validation without scanner prompt.
     * @param str The string to validate.
     * @param validator The regular expression to validate against.
     * @return A status of validation.
     */
    public boolean validate(String str, String validator) {
        Pattern pattern = Pattern.compile(validator,Pattern.CASE_INSENSITIVE);
        Matcher m = pattern.matcher(str);
        return m.matches();
    }
    
    /**
     * Prompts the user for input.
     * @param prompt 
     */
    public String prompt(String prompt) {
        System.out.print(prompt);
        this.value = input.nextLine();
        return this.value;
    }
    
    /**
     * Prompts the user for input, verifies input with passed regular expression.
     * @param prompt The text to ask the user for the input.
     * @param validator The regular expression to verify.
     * @return The string requested;
     */
    public String prompt(String prompt, String validator) {
        //  Compile regular expression
        Pattern pattern = Pattern.compile(validator,Pattern.CASE_INSENSITIVE);
        boolean escape = false;
        while(!escape) {
            System.out.print(prompt);
            this.value = input.nextLine();
            Matcher m = pattern.matcher(this.value); 
            if(!(m.matches())) System.err.println("Invalid input.");
            else escape = true;
        }
        return this.value;
    }
    
    /**
     * Prompts the user for input, verifies input with passed regular expression.
     * @param prompt The text to ask the user for the input.
     * @param validator The regular expression to verify.
     * @param err An error message to return to the user.
     * @return The string requested;
     */
    public String prompt(String prompt, String validator, String err) {
         //  Compile regular expression
        Pattern pattern = Pattern.compile(validator,Pattern.CASE_INSENSITIVE);
        boolean escape = false;
        while(!escape) {
            System.out.print(prompt);
            this.value = input.nextLine();
            Matcher m = pattern.matcher(this.value); 
            if(!(m.matches())) System.err.println(err);
            else escape = true;
        }
        return this.value;
    }
    
    /**
     * Prompts the user for input, verifies input with passed regular expression.
     * @param prompt The text to ask the user for the input.
     * @param err An error message to return to the user.
     * @return The integer value.
     */
    public int promptInt(String prompt,String err) {
        int a = 0;
        boolean escape = false;
        while(!escape) {
            try {
                System.out.print(prompt);
                a = input.nextInt();
                input.nextLine();
                escape = true;
            } catch (java.util.InputMismatchException e) {
                System.err.println(err);
            }
        }
        return a;
    }
    
    /**
     * Prompts the user for input, verifies input with passed regular expression.
     * @param prompt The text to ask the user for the input.
     * @param validator The regular expression to validate the input against.
     * @param err The error message to return to the user.
     * @return The integer requested.
     */
    public int promptInt(String prompt,String validator, String err) {
        Integer a = 0;
        boolean escape = false;
        Pattern pattern = Pattern.compile(validator,Pattern.CASE_INSENSITIVE);
        while(!escape) {
            try {
                System.out.print(prompt);
                a = input.nextInt();
                input.nextLine();
                
                Matcher m = pattern.matcher(a.toString()); 
                if(!(m.matches())) System.err.println(err);
                else escape = true;
            } catch (java.util.InputMismatchException e) {
                System.err.println(err);
            }
        }
        return a;
    }
    
    /**
     * Parse a string to an integer.
     * @param n The string to parse.
     * @return The integer. (0 on error)
     */
    public static int parseInt(String n) {
        try { 
            return Integer.parseInt(n);  
        } catch (NumberFormatException e) { 
            return 0; 
        }
    }
}
