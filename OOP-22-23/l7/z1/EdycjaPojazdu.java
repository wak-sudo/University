import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class EdycjaPojazdu extends JComponent implements ActionListener {
    private Pojazd pojazdObj;
    String filePath;

    JFrame frame;
    Container kontener; 
    GridLayout layout;
    JButton saveButton;

    JLabel modelLab;
    JTextField modelText;

    JLabel rokProdukcjiLab;
    JTextField rokProdukcjiText;

    JLabel przebiegLab;
    JTextField przebiegText;

    public EdycjaPojazdu(Pojazd pojazdObj, String filePath)
    {
        this.pojazdObj = pojazdObj;
        this.filePath = filePath;
    }

    public EdycjaPojazdu()
    {
        pojazdObj = new Pojazd();
        filePath = "POJAZD.BIN";
    }

    public void initGUI()
    {
        frame = new JFrame("Edycja Pojazdu");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        kontener = frame.getContentPane();
        layout = new GridLayout(4, 2);
        kontener.setLayout(layout);

        setPojazdEditorLabs(pojazdObj);
        addSaveButton();

        frame.pack();
        frame.setVisible(true);
    }

    void setPojazdEditorLabs(Pojazd obj)
    {
        modelLab = new JLabel("Model");
        kontener.add(modelLab);
        modelText = new JTextField(obj.model, 40);
        kontener.add(modelText);

        rokProdukcjiLab = new JLabel("Rok produkcji: ");
        kontener.add(rokProdukcjiLab);
        rokProdukcjiText = new JTextField(Integer.toString(obj.rokProdukcji), 40);
        kontener.add(rokProdukcjiText);

        przebiegLab = new JLabel("Przebieg (km): ");
        kontener.add(przebiegLab);
        przebiegText = new JTextField(Integer.toString(obj.przebiegKM), 40);
        kontener.add(przebiegText);
    }

    void addSaveButton()
    {
        saveButton = new JButton("Zapisz");
        saveButton.addActionListener(this);
        kontener.add(saveButton);
    }

    public void actionPerformed(ActionEvent e)
    {
        Object src = e.getSource();
        if(src == saveButton)
        {
            try
            {
                Pojazd obj = retNewObj();
                Serialize.write(obj, filePath);
                infoBox("Poprawnie zapisano.", "Sukces");
            }
            catch(Exception ecx)
            {
                infoBox("Wprowadzono nieprawidlowe dane.", "Blad");
            }
        }
    }

    // throws exc if data is invalid.
    Pojazd retNewObj()
    {
        return new Pojazd(modelText.getText(), Integer.parseInt(rokProdukcjiText.getText()), Integer.parseInt(przebiegText.getText()));
    }

    static void infoBox(String infoMessage, String titleBar)
    {
        JOptionPane.showMessageDialog(null, infoMessage, titleBar, JOptionPane.INFORMATION_MESSAGE);
    }
}
