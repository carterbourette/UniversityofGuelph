package cis2430laba5;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;
import javax.swing.*;

class CarWindow extends JFrame {
    
    private static int search (HashMap i, String key) {
        if (i.get(key.toLowerCase()) == null) {
            return -1;
        } else {
            return (int) i.get(key.toLowerCase());
        }
    }
    
    private static void index(ArrayList cars, HashMap i, Car c) throws Exception {
        if (c == null) return;
        String[] split = c.getBrand();
        String key = split[0] + split[1] + c.getYear();
        if (i.get(key.toLowerCase()) != null) {
            throw new Exception("Duplicate ID found in list.");
        } else {
            cars.add(c);
            i.put(key.toLowerCase(), cars.size()-1);
        }
    }
    
    public static boolean hack = false;
    Car temp;
    JFrame frame = new JFrame();
    
    public CarWindow() {
        ArrayList<Car> myCars = new ArrayList();
        HashMap<String, Integer> index = new HashMap<>();
        
        JPanel btnPanel = new JPanel();
        JPanel content = new JPanel();
        JPanel bottom = new JPanel();
        
        JTextArea textBox = new JTextArea("\n\nWelcome to Carter's Car Rental.\n\n");
        JScrollPane scrollPane = new JScrollPane(textBox);

        //  Frame settings
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(800, 600);
        setLocationRelativeTo(null);
        setResizable(false);
        setTitle("Car Rental Program");
        setLayout(new GridLayout(0, 2));
        
        
         /*
            Creates form
         */
        JPanel form = new JPanel();
        form.setVisible(false);
        form.setLayout(new GridLayout(0, 2));
        
        form.add(new JLabel("Brand and Model:"));
        JTextField brandAndModel = new JTextField();
        form.add(brandAndModel);        
        
        form.add(new JLabel("Year:"));
        JTextField year = new JTextField();
        form.add(year);        
        
        form.add(new JLabel("Price:"));
        JTextField price = new JTextField();
        form.add(price); 
        
        JLabel sLabel = new JLabel("Number of Seats:");
        form.add(sLabel);
        JTextField numSeat = new JTextField();
        form.add(numSeat); 
        
        JLabel teLabel = new JLabel("Is All Terain:");
        form.add(teLabel);
        JCheckBox terrain = new JCheckBox();
        form.add(terrain); 
        
        JLabel tLabel = new JLabel("Tire Brand:");
        form.add(tLabel);
        JTextField tire = new JTextField();
        form.add(tire); 
        
        JButton save = new JButton("Save");
        save.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String yr = "", pr = "", s = "", all = "", tr = "";
                try {   //  Create the car
                    String bAm = brandAndModel.getText();
                    String[] bm = bAm.split(" ");
                    yr = year.getText();
                    pr = price.getText();
                    if (pr.equals("")) pr = "50000";
                    s  = numSeat.getText();
                    all= terrain.getText();
                    tr = tire.getText();
                    if (!hack) {
                        Car myCar = new Car(bm[0], bm[1], yr, pr);
                        index(myCars,index,myCar);
                    } else {
                        SUV myCar = new SUV(bm[0], bm[1], yr, pr, Validator.parseInt(s), Boolean.parseBoolean(all), tr);
                        index(myCars,index,myCar);
                    }
                    textBox.setText(textBox.getText() + "\n" + "Car created." + "\n");
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(frame, "Unable to create car: "+ ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                }
                
                brandAndModel.setText("");
                year.setText("");
                price.setText("");
                numSeat.setText("");
                terrain.setSelected(false);
                tire.setText("");
                form.setVisible(false);
            }
        });
        form.add(save);  
        
        JButton clear = new JButton("Clear");
        clear.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                brandAndModel.setText("");
                year.setText("");
                price.setText("");
                numSeat.setText("");
                terrain.setSelected(false);
                tire.setText("");
            }
        });
        form.add(clear);
        
        /*
            Button Panel
         */
        btnPanel.setLayout(new GridLayout(0,1));
        JButton newCar = new JButton("New Car");
         newCar.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                form.setVisible(true);
                hack = false;
                numSeat.setVisible(false);
                terrain.setVisible(false);
                tire.setVisible(false);
                sLabel.setVisible(false);
                tLabel.setVisible(false);
                teLabel.setVisible(false);        
            }
        });
        btnPanel.add(newCar);
        
        JButton newSUV = new JButton("New SUV");
        newSUV.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                form.setVisible(true);
                hack = true;
                numSeat.setVisible(true);
                terrain.setVisible(true);
                tire.setVisible(true);
                sLabel.setVisible(true);
                tLabel.setVisible(true);
                teLabel.setVisible(true);
            }
        });
        btnPanel.add(newSUV);
        
        JButton pBrandM = new JButton("Print brand + model");
        pBrandM.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                for (int i = 0; i < myCars.size(); i++) {
                        temp = (Car)myCars.get(i);
                        String[] brandName = temp.getBrand();
                        textBox.setText(textBox.getText() + "\n" + "Vehicle " + (i + 1) + ": " + "\n" + brandName[0] + " " + brandName[1] + " " + temp.getYear() + "\n");
                    }
            }
        });
        btnPanel.add(pBrandM);
        
        JButton avgCost = new JButton("Avg Cost");
        avgCost.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                 double avg = 0;
                int total = myCars.size();
                for (int i = 0; i < myCars.size(); i++) {
                    temp = (Car)myCars.get(i);
                    avg = avg + temp.getPrice();
                }
                DecimalFormat df = new DecimalFormat("#.##");
                textBox.setText(textBox.getText() + "\n" + "The average cost is $" + (df.format(avg/total)) + ". Out of " + total + " vehicles." + "\n");
            }
        });
        btnPanel.add(avgCost);
        
        JButton imp = new JButton("Import");
        imp.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String message = "Please enter the file you would like to import: ";
                String filename = JOptionPane.showInputDialog(frame, message);
                
                try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
                        String line = br.readLine();
                        while (line != null) {
                            String arr[] = line.split(" ");
                            if (arr.length == 5){
                                Car c = null;
                                try {
                                    c = new Car(arr[0], arr[1], arr[2], arr[3]);
                                    try {
                                        //  Car is complete add it to a list
                                        index(myCars, index, c);
                                    } catch (Exception ex) {
                                        textBox.setText(textBox.getText() + "\n" + "Unable to add car " + ex.getMessage() + "." + "\n");
                                    }
                                } catch (Exception ex) {
                                    textBox.setText(textBox.getText() + "\n" + "Unable to add car " + ex.getMessage() + "." + "\n");
                                }
                                
                            } else {
                                int numSeats = Integer.parseInt(arr[5]);
                                boolean isAll = Boolean.parseBoolean(arr[6]);
                                SUV c = null;
                                try {
                                    c = new SUV(arr[0], arr[1], arr[2], arr[3], numSeats, isAll, arr[7]);
                                    try {
                                        //  Car is complete add it to a list
                                        index(myCars, index, c);
                                    } catch (Exception ex) {
                                        textBox.setText(textBox.getText() + "\n" + "Unable to add car " + ex.getMessage() + "." + "\n");
                                    }
                                } catch (Exception ex) {
                                    textBox.setText(textBox.getText() + "\n" + "Unable to add car " + ex.getMessage() + "." + "\n");
                                }
                            }
                            line = br.readLine();   
                        }
                        textBox.setText(textBox.getText() + "\n" + filename + " loaded." + "\n");
                    } catch (FileNotFoundException ex) {
                        JOptionPane.showMessageDialog(frame, "File not found!", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (IOException ex) {
                        JOptionPane.showMessageDialog(frame, "IO Error!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
            }
        });
        btnPanel.add(imp);
        
        JButton dataDump = new JButton("Data Dump");
        dataDump.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                for (int i = 0; i < myCars.size(); i++) {
                        Car t = (Car) myCars.get(i);
                        textBox.setText(textBox.getText() + "\n" + t.dataDump() + "\n");
                }
            }
        });
        btnPanel.add(dataDump);
        
        JButton export = new JButton("Export");
        export.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                PrintWriter writer;
                    try {
                        writer = new PrintWriter("output.txt", "UTF-8");
                        for (int i = 0; i < myCars.size(); i++) {
                            Car t = (Car) myCars.get(i);
                            writer.println(t.dataDump());
                        }
                        writer.close();
                    } catch (java.io.FileNotFoundException | java.io.UnsupportedEncodingException ex) {
                        JOptionPane.showMessageDialog(frame, "File not found!", "Error", JOptionPane.ERROR_MESSAGE);
                    }
            }
        });
        btnPanel.add(export);
        
        JButton lookup = new JButton("Lookup");
        lookup.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JFrame frame = new JFrame();
                String message = "Please enter the brand, model and year of the car: ";
                String text = JOptionPane.showInputDialog(frame, message);
                String key = "";
                String[] split = text.split(", ");
                    try {
                        key = split[0] + split[1] + split[2]; 
                        int result = search(index, key.toLowerCase());
                        if(result != -1) {
                            Car mySearchCar = myCars.get(result);
                            textBox.setText(textBox.getText() + "\n" +  mySearchCar.dataDump() + "\n");
                        } else {
                            textBox.setText(textBox.getText() + "\n" + "Car not found." + "\n");
                        }
                    } catch(ArrayIndexOutOfBoundsException ex) {
                        textBox.setText(textBox.getText() + "\n" + "Car not found." + "\n");
                    }
            }
        });
        btnPanel.add(lookup);
        
        JButton quit = new JButton("Quit");
        quit.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
        btnPanel.add(quit); 
        
        //  Main content
        bottom.setLayout(new BorderLayout());
        bottom.add(scrollPane, BorderLayout.CENTER);
        
        content.setLayout(new GridLayout(2,0));
        content.add(form);
        content.add(bottom);
     
        add(btnPanel);
        add(content);
    }
}