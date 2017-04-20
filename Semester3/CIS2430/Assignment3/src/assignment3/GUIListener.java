/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.*;

public class GUIListener {
    
    JFrame frame = new JFrame();
    EStore myStore = new EStore();
    
    /**
     * Clear the forms.
     */
    protected class ClearForm implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            EStoreGUI.clearForm();
        }
    }
    
    /**
     * Save the object to the EStore list.
     */
    protected class SaveForm implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            switch (EStoreGUI.hacker) {
                case 0:     //  In Book mode
                    try {
                        Book myBook = EStoreGUI.getBookFields();
                        if (myStore.add(myBook)) {
                            EStoreGUI.write("Book Created.");
                            EStoreGUI.clearForm();
                        } else JOptionPane.showMessageDialog(frame, "Unable to add duplicate ID given!", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(frame, "Unable to create book: "+ ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                    }
                    break;
                case 1:     //  In Electronic mode
                    try {
                        Electronic myElec = EStoreGUI.getElectronicFields();
                        if (myStore.add(myElec)) {
                            EStoreGUI.write("Electronic Created.");
                            EStoreGUI.clearForm();
                        } else JOptionPane.showMessageDialog(frame, "Unable to add duplicate ID given!", "Error", JOptionPane.ERROR_MESSAGE);
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(frame, "Unable to create electronic: "+ ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
                    }
                    break;
                case 2:     //  In search mode
                    String[] myString = EStoreGUI.getSearchFields();
                    String year;
                    
                    if (!myString[2].equals("")) {
                        if (!Validator.validate(myString[2], Validator.INTEGER)) {
                            JOptionPane.showMessageDialog(frame, "Please enter valid years!", "Error", JOptionPane.ERROR_MESSAGE);
                            return;
                        }
                    } if (!myString[3].equals("")) {
                       if (!Validator.validate(myString[3], Validator.INTEGER)) {
                            JOptionPane.showMessageDialog(frame, "Please enter valid years!", "Error", JOptionPane.ERROR_MESSAGE);
                            return;
                        } 
                    }
                    
                    //  Add the dash we used before
                    if(myString[2].equals("") && myString[3].equals("")) year = "";
                    else if(myString[2].equals("")) year = "-" + myString[3];
                    else if(myString[3].equals("")) year = myString[2] + "-";
                    else year = myString[2] + "-" + myString[3];

                    if(!myString[2].equals("") && !myString[3].equals("")) {
                        if (Validator.parseInt(myString[2]) > Validator.parseInt(myString[3])) {
                            JOptionPane.showMessageDialog(frame, "Please enter a valid start and end year!", "Error", JOptionPane.ERROR_MESSAGE);
                            return;
                        }
                        
                    }

                    ArrayList<Product> searchResults = myStore.search(myString[0], myString[1], year);
                    EStoreGUI.write("Search Results:" + "\n" +
                                    "---------------");
                    for (int i = 0; i < searchResults.size(); i++) {
                        //  Get the object
                        Product item = searchResults.get(i);
                        EStoreGUI.write(item.toString());
                    } if (searchResults.isEmpty()) EStoreGUI.write("No results to display.");
                    break;
            }
        }
    }
    
    /**
     * Save the object to the EStore list.
     */
    protected class OpenBook implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            EStoreGUI.setBookForm();
        }
    }
    
    /**
     * Save the object to the EStore list.
     */
    protected class OpenSearch implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            EStoreGUI.setSearchForm();
        }
    }
    
    /**
     * Save the object to the EStore list.
     */
    protected class Quit implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            EStoreGUI.write("Saving Data...");
            FileIO.dumpFile(myStore, "data.txt");
            System.exit(0);
        }
    }
    
    /**
     * Toggle the book and electronic forms.
     */
    protected class SelectOptions implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            JComboBox comboItem = (JComboBox)e.getSource();
            String nm = (String) comboItem.getSelectedItem();
            if (nm.equals("Book")) {
                EStoreGUI.setBookForm();
            } else if(nm.equals("Electronic")) {
                EStoreGUI.setElecForm();
            }
        }
    }
}
