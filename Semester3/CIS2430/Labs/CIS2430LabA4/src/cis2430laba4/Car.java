package cis2430laba4;

public class Car {
    private String brand;
    private String year;
    private double price;

    public Car() {
        this.price = 50000;
    }
    
    public Car(String brd, String model, String yr, String price) throws Exception{
        this.setBrand(brd + " " + model);
        if (this.brand.equals("")) throw new Exception("Invalid brand and model!");
        this.year = yr;
        if(Integer.parseInt(this.year) < 1986) throw new Exception("Invalid year!");
        this.price = Double.parseDouble(price);
        if(this.price < 5000) throw new Exception("Invalid price!");
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
        if (str.equals("") || str.length() != 4 || Integer.parseInt(str) < 1986) return false;
        this.year = str;
        return true;
    }
    
    public boolean setPrice(String str) {
        if (str.equals("")) return false;
        try {
            this.price = Integer.parseInt(str);
            if (this.price < 5000) return false;
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
        return arr[0] + " " + arr[1] + " " + this.getYear() + " $" + this.getPrice();
    }
}
