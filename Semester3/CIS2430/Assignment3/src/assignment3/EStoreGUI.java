/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import java.awt.GridLayout;
import javax.swing.*;

public class EStoreGUI extends JFrame {
    
    private static JMenuBar menuBar;
    private static JLabel typeLabel, prodLabel, nameLabel, priceLabel, yearLabel, makerLabel, publisherLabel;
    private static JTextField productID, name, price, year, maker, publisher;
    private static JTextArea textbox;
    private static JComboBox type;
    private static JPanel top, bottom, form;
    private static JButton clear, save;
    
    public static int hacker = 0;   //  Just call me a hacker - 0 is a book, 1 is a electronic, 2 is the search field
    GUIListener listener = new GUIListener();
    
    private void buildMenu() {
        menuBar = new JMenuBar();

        //  Create the Menu Options
        JMenu commands = new JMenu("Commands");
        JMenuItem addMenu = new JMenuItem("Add");
        JMenuItem searchMenu = new JMenuItem("Search");
        JMenuItem quitMenu = new JMenuItem("Quit");
        
        addMenu.addActionListener(listener.new OpenBook());
        searchMenu.addActionListener(listener.new OpenSearch());
        quitMenu.addActionListener(listener.new Quit());
        
        //  Add them to the Menu Bar
        commands.add(addMenu);
        commands.add(searchMenu);
        commands.add(quitMenu);
        
        menuBar.add(commands);
    }
    
    /**
     * Function builds the add form and adds it to a JPanel.
     */
    private void buildForm() {
        form.setLayout(new GridLayout(0, 2));
        form.setBorder(BorderFactory.createTitledBorder("Add a Book"));
        typeLabel  = new JLabel("Type:");
        String[] items = {"Book","Electronic"};
        type = new JComboBox<>(items);
        type.addActionListener(listener.new SelectOptions());
        form.add(typeLabel);
        form.add(type);    
        
        prodLabel = new JLabel("Product ID:");
        productID = new JTextField();
        form.add(prodLabel);
        form.add(productID);
        
        nameLabel = new JLabel("Name:");
        name = new JTextField();
        form.add(nameLabel);
        form.add(name);
        
        priceLabel = new JLabel("Price:");
        price = new JTextField();
        form.add(priceLabel);
        form.add(price);
        
        yearLabel = new JLabel("Year:");
        year = new JTextField();
        form.add(yearLabel);
        form.add(year);
        
        //  Author / Maker - will serve as both author and maker
        makerLabel = new JLabel("Author:");
        maker = new JTextField();
        form.add(makerLabel);
        form.add(maker);
        
        publisherLabel = new JLabel("Publisher:");
        publisher = new JTextField();
        form.add(publisherLabel);
        form.add(publisher);
        
        clear = new JButton("Clear");
        clear.addActionListener(listener.new ClearForm());
        save = new JButton("Save");
        save.addActionListener(listener.new SaveForm());
        
        form.add(clear);
        form.add(save);
        top.add(form);
    }
    
    /**
     * Builds the output window and adds it to a JPanel.
     */
    private void buildOutput() {
        bottom.setLayout(new GridLayout(0, 1)); 
        textbox = new JTextArea("Welcome to Carter's EStore!");
        textbox.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textbox);
        bottom.add(scrollPane);
    }
    
    /**
     * Makes the input form a "add book" form.
     */
    public static void setBookForm() {
        //  Set the visible elements
        typeLabel.setVisible(true);
        type.setVisible(true);
        prodLabel.setVisible(true);
        productID.setVisible(true);
        nameLabel.setVisible(true);
        name.setVisible(true);
        priceLabel.setVisible(true);
        price.setVisible(true);
        yearLabel.setVisible(true);
        year.setVisible(true);
        makerLabel.setVisible(true);
        maker.setVisible(true);
        publisherLabel.setVisible(true);
        publisher.setVisible(true);
        save.setVisible(true);
        clear.setVisible(true);

        //  Set the labels
        prodLabel.setText("Product ID:");
        nameLabel.setText("Name:");
        priceLabel.setText("Price:");
        yearLabel.setText("Year:");
        makerLabel.setText("Author:");
        publisherLabel.setText("Publisher:");
        save.setText("Save");
        
        form.setBorder(BorderFactory.createTitledBorder("Add a Book"));
        clearForm();
        hacker = 0;
    }
    
    /**
     * Makes the input form a "add electronic" form.
     */
    public static void setElecForm() {
        //  Set the visible elements
        typeLabel.setVisible(true);
        type.setVisible(true);
        prodLabel.setVisible(true);
        productID.setVisible(true);
        nameLabel.setVisible(true);
        name.setVisible(true);
        priceLabel.setVisible(true);
        price.setVisible(true);
        yearLabel.setVisible(true);
        year.setVisible(true);
        makerLabel.setVisible(true);
        maker.setVisible(true);
        publisherLabel.setVisible(false);
        publisher.setVisible(false);
        save.setVisible(true);
        clear.setVisible(true);
        
        //  Set the labels
        prodLabel.setText("Product ID:");
        nameLabel.setText("Name:");
        priceLabel.setText("Price:");
        yearLabel.setText("Year:");
        makerLabel.setText("Maker:");
        save.setText("Save");
        
        form.setBorder(BorderFactory.createTitledBorder("Add an Electronic"));
        clearForm();
        hacker = 1;
    }
    
    /**
     * Makes the input form a "add electronic" form.
     */
    public static void setSearchForm() {
        //  Set the visible elements
        typeLabel.setVisible(false);
        type.setVisible(false);
        prodLabel.setVisible(true);
        productID.setVisible(true);
        nameLabel.setVisible(true);
        name.setVisible(true);
        priceLabel.setVisible(true);
        price.setVisible(true);
        yearLabel.setVisible(true);
        year.setVisible(true);
        makerLabel.setVisible(false);
        maker.setVisible(false);
        publisherLabel.setVisible(false);
        publisher.setVisible(false);
        save.setVisible(true);
        clear.setVisible(true);

        //  Set the labels
        prodLabel.setText("Product ID:");
        nameLabel.setText("Keywords:");
        priceLabel.setText("Start Year:");
        yearLabel.setText("End Year:");
        save.setText("Submit");
        
        form.setBorder(BorderFactory.createTitledBorder("Search for Products"));
        clearForm();
        hacker = 2;
    }
    
    /**
     * Clears the input form.
     */
    public static void clearForm() {
        productID.setText("");
        name.setText("");
        price.setText("");
        year.setText("");
        maker.setText("");
        publisher.setText("");
    }
    
    /**
     * Return the Book form as an object.
     * @return Book Object
     * @throws java.lang.Exception Invalid Object exception.
     */
    public static Book getBookFields() throws Exception {
        return new Book(productID.getText(), name.getText(),price.getText(),year.getText(),maker.getText(), publisher.getText());
    }
    
    /**
     * Return the Electronic form as an object.
     * @return Electronic object.
     * @throws java.lang.Exception Invalid Object exception.
     */
    public static Electronic getElectronicFields() throws Exception {
        return new Electronic(productID.getText(), name.getText(),price.getText(),year.getText(),maker.getText());
    }
    
    public static String getStringText(JTextField f) {
        String ret = f.getText();
        if (ret == null) ret = "";
        return ret;
    }
    
    /**
     * Return the search form.
     * @return A string array of the values.
     */
    public static String[] getSearchFields() {
        String[] stuff = {getStringText(productID),getStringText(name),getStringText(price),getStringText(year)};
        return stuff;       
    }
    
    public static void write(String str) {
        textbox.setText(textbox.getText() + "\n" +  str + "\n");
    }
    
    /**
     * Creates an instance of the GUI.
     */
    public EStoreGUI() {
        top = new JPanel();
        top.setLayout(new GridLayout(1, 0));
        bottom = new JPanel();
        form = new JPanel();
        
        buildMenu();    //  Create a menu
        buildForm();    //  Create the form to add a product
        buildOutput();  //  Create the output window
        
        /* Init some JFrame preferences. */
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(600, 400);
        setLocationRelativeTo(null);
        setResizable(false);
        setTitle("EStore Inventory");
        setLayout(new GridLayout(1, 2));
        setJMenuBar(menuBar);

        add(top);
        add(bottom);
    }
    
}
