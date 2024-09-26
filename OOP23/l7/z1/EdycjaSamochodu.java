import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class EdycjaSamochodu extends EdycjaPojazdu {
    private Samochod samochodObj;

    JLabel kategoriaLab;
    JTextField kategoriaText;
    JLabel liczbaDzwiLab;
    JTextField liczbaDzwiText;
    
    JLabel automatSkrzyniaLab;
    JComboBox<Boolean> autoSkrzyniaJCB;
    
    public EdycjaSamochodu(Samochod samochodObj, String filePath)
    {
        this.samochodObj = samochodObj;
        this.filePath = filePath;
    }

    public EdycjaSamochodu()
    {
        samochodObj = new Samochod();
        this.filePath = "SAMOCHOD.BIN";
    }

    public void initGUI()
    {
        frame = new JFrame("Edycja Samochodu");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        kontener = frame.getContentPane();
        layout = new GridLayout(7, 2);
        kontener.setLayout(layout);

        setPojazdEditorLabs(samochodObj);
        setSamochodEditorLabs(samochodObj);
        addSaveButton();

        frame.pack();
        frame.setVisible(true);
    }

    public void setSamochodEditorLabs(Samochod obj)
    {
        kategoriaLab = new JLabel("Kategoria");
        kontener.add(kategoriaLab);
        kategoriaText = new JTextField(obj.kategoria, 40);
        kontener.add(kategoriaText);

        automatSkrzyniaLab = new JLabel("Skrzynia automatyczna: ");
        kontener.add(automatSkrzyniaLab);
        autoSkrzyniaJCB = new JComboBox<>(new Boolean[]{true, false});
        autoSkrzyniaJCB.setSelectedItem(obj.automatSkrzynia);
        kontener.add(autoSkrzyniaJCB);

        liczbaDzwiLab = new JLabel("Liczba dzwi: ");
        kontener.add(liczbaDzwiLab);
        liczbaDzwiText = new JTextField(Integer.toString(obj.liczbaDzwi), 40);
        kontener.add(liczbaDzwiText);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object src = e.getSource();
        if(src == saveButton)
        {
            try
            {
                Samochod obj = retNewObj();
                Serialize.write(obj, filePath);
                infoBox("Poprawnie zapisano.", "Sukces");
            }
            catch(Exception ecx)
            {
                infoBox("Wprowadzono nieprawidlowe dane.", "Blad");
            }
        }
    }
    
    Samochod retNewObj()
    {
        return new Samochod(super.retNewObj(), kategoriaText.getText(), (Boolean)autoSkrzyniaJCB.getSelectedItem() ,Integer.parseInt(liczbaDzwiText.getText()));
    }

}
