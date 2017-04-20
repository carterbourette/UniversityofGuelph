package cis2430laba4;

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
    public static final String REQUIRED = "*+";
    
    private Scanner input;
    String value;
 
    /**
     * The default constructor Initialize input scanner.
     */
    public Validator() {
        this.input = new Scanner(System.in);
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
     * @return The integer value
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
    
    public static int parseInt(String n) {
        try { 
            return Integer.parseInt(n);  
        } catch (NumberFormatException e) { 
            return 0; 
        }
    }
}
