package cis2430a1;

import java.util.Scanner;

/**
 *
 * @author Carter
 * September 27, 2016
 * 0916638
 */
public class CIS2430A1 {

    public static void printMenu() {
        System.out.println("\n");
        System.out.println("(1) Enter a sentence");
        System.out.println("(2) Print out all sentences entered thus far in given order");
        System.out.println("(3) Print out the number of strings entered thus far.");
        System.out.println("(4) Print out the sentences entered thus far in reverse.");
        System.out.println("(5) Print out the total number of characters combined.");
        System.out.println("(6) Calculate the total number of vowels stored.");
        System.out.println("(7) Perform a search for a given word. (Case insensitive)");
        System.out.println("(8) Perform a search for a given word. (Case sensitive)");
        System.out.println("(9) End.");
        System.out.println("\n");
        
    }
    
    public static String getString() {
       Scanner obj = new Scanner(System.in);
       return obj.nextLine();
    }
    
    public static int getInt() {
        Scanner obj = new Scanner(System.in);
        return obj.nextInt();
    }
   
    public static void main(String[] args) {
        
        int answer = -1, count = 0;
        boolean quit = false;
        String[] stringArr = new String[10];
        
        do {
            switch (answer) {
                case 1:
                    //  Enter a sentence
                    if(count > 9) {
                        System.out.println("Sorry I'm full");
                    } else {
                        System.out.print("Enter the sentence: ");
                        stringArr[count] = getString();
                        count++;
                    }
                    
                    break;
                case 2:
                    //  print sentences
                    for (int i = 0; i < count; i++) {
                        System.out.println("Sentence " + (i + 1) + ": " + stringArr[i]);
                    }
                    break;
                case 3:
                    //  number of sentences entered
                    System.out.println(count + " have been entered so far.");
                    break;
                case 4:
                    //  reverse sentences
                    for (int i = count-1; i >= 0; i--) {
                        System.out.println("Sentence " + (i + 1) + ": " + stringArr[i]);
                    }
                    break;
                    
                case 5:
                    //  print total characters
                    int chars = 0;
                    for (int i = 0; i < count; i++) {
                        chars += stringArr[i].length();
                    }
                    System.out.println("Total characters: "+ chars);
                    break;
                case 6:
                    //  total vowles
                    int vowel = 0;
                    for (int i = 0; i < count; i++) {
                        for (int k = 0; k < stringArr[i].length(); k++) {
                            String a = stringArr[i].substring(k, k+1).toLowerCase();
                            if(a.equals("a") || a.equals("e") || a.equals("i") || a.equals("o") || a.equals("u") || a.equals("y")){
                                vowel++;
                            }
                        }
                    }
                    System.out.println(vowel + " vowels have been entered so far.");
                    break;
                case 7:
                    //  case insens
                    int index = -1;
                    String word;
                    
                    System.out.println("Enter the string you would like to search for: ");
                    word = getString();
                    /*  For index of string
                    for (int i = 0; i < count; i++) {
                        index = stringArr[i].toLowerCase().indexOf(word.toLowerCase());
                        System.out.println("String " + (i + 1) + " " + stringArr[i]);
                        if (index != -1){
                            System.out.println("Found a match in string " + (i + 1) + " at index " + index);
                        } else {
                            System.out.println("Match not found!");
                        }
                    }*/
                    for (int i = 0; i < count; i++) {
                        if (stringArr[i].matches("(?i:.*\\b"+word+"\\b.*)")) { //.*\\bthis\\b
                            System.out.println("Found a match in string "+(i+1));
                        } else {
                            System.out.println("No match found in string "+ (i+1));
                        }
                    }
                    break;
                case 8:
                    //  case sens
                    index = -1;
                    
                    System.out.println("Enter the string you would like to search for: ");
                    word = getString();
                    /* for index of string
                    for (int i = 0; i < count; i++) {
                        index = stringArr[i].indexOf(word);
                        
                        if (index != -1){
                            System.out.println("String " + (i+1) + " " + stringArr[i]);
                            System.out.println("Found a match in string " + (i + 1) + " at index " + index);
                        } else {
                            System.out.println("Match not found!");
                        }
                    }*/
                    for (int i = 0; i < count; i++) {
                        if (stringArr[i].matches(".*\\b"+word+"\\b.*")) { //.*\\bthis\\b
                            System.out.println("Found a match in string "+(i+1));
                        } else {
                            System.out.println("No match found in string "+ (i+1));
                        }
                    }
                    break;
                case 9:
                    quit = true;
                    System.out.println("\nThanks! Come again!");
                    break;
                default:
                    break;
            }
            
            if (!quit) {
                printMenu();
                System.out.print("\n\nEnter a number between 1-9 that corresponds to the menu: ");
                answer = getInt();
            }       
        } while (answer > 0 && answer <= 9 && !quit);
        
        
    }
    
}
