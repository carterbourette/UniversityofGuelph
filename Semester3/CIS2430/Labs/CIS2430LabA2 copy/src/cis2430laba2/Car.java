package cis2430laba2;

public class Car {
    private String brand;
    private String year;
    private double price;

    public Car() {
        this.price = 50000;
    }
    
    /*  Accessor Methods   */
    
    public String[] getBrand() {
        return this.brand.split(" ");
    }
    
    public String getYear() {
        return this.year;
    }
    
    public double getPrice() {
        return this.price;
    }
    
    /*  Mutator Methods   */
    
    public boolean setBrand(String str) {
        //String arr[] = str.split("[ ]+");
        String arr[] = str.split(" +");
        if (str.equals("") || arr.length != 2 || !arr[0].matches(".*[a-zA-z]+.*") || !arr[1].matches(".*[a-zA-z]+.*")) return false; 
        this.brand = arr[0] + " " + arr[1];
        return true;
    }
    
    public boolean setYear(String str) {
        if (str.equals("") || str.length() != 4) return false;
        this.year = str;
        return true;
    }
    
    public boolean setPrice(String str) {
        if (str.equals("")) return false;
        try {
            this.price = Integer.parseInt(str);
        } catch (java.util.InputMismatchException e) {
            return false;
        }
        return true;
    }
}
