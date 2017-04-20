/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cis2430laba3;

public class SUV extends Car {
    private int numSeats;
    private boolean isAllTerrain;
    private String tireBrand;
    
    public SUV() {
        
    }
    
    public SUV(String brand, String model, String year, String price, int seats, boolean terrain, String tBrand) {
        super(brand, model, year, price);
        this.numSeats = seats;
        this.isAllTerrain = terrain;
        this.tireBrand = tBrand;
    }
    
    /*  Mutator    */
    public boolean setNumSeats(int seats) {
        this.numSeats = seats;
        return true;
    }
    
    public boolean setIsAllTerrain(boolean isAll) {
        this.isAllTerrain = isAll;
        return true;
    }
    
    public boolean setTireBrand(String brand) {
        this.tireBrand = brand;
        return true;
    }
    
    /*  Accessor   */
    public int getNumSeats() {
        return this.numSeats;
    }
    
    public boolean getIsAllTerrain() {
        return this.isAllTerrain;
    }
    
    public String getTireBrand() {
        return this.tireBrand;
    }
    
    /**
     * Print the attributes of a car.
     * @return the data string.
     */
    public String dataDump() {
        String[] arr = this.getBrand();
        return "SUV Model: " + arr[1] + ", " + this.getTireBrand();
    }
}
