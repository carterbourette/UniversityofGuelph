package cis2430laba3;

public class Car {
    private String brand;
    private String year;
    private double price;

    public Car() {
        this.price = 50000;
    }
    
    public Car(String brd, String model, String yr, String price) {
        this.setBrand(brd + " " + model);
        this.year = yr;
        this.setPrice(price);
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
    
    /**
     * Print the attributes of a car.
     * @return the data string
     */
    public String dataDump() {
        String[] arr = this.getBrand();
        return "    Brand: " + arr[0] + " Model:" + arr[1] + " Year:" + this.getYear() + " Price: $" + this.getPrice();
    }
}
