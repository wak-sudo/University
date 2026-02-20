import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class EdycjaTramwaju extends EdycjaPojazdu {
    private Tramwaj tramwajObj;
    
    JLabel kierunkowoscLab;
    JComboBox<Integer> kierunkowoscJCB;

    JLabel rozstawTorowLab;
    JTextField rozstawTorowText;

    JLabel wysokoscPodlogiLab;
    JTextField wysokoscPodlogiText; 

    public EdycjaTramwaju(Tramwaj tramwajObj, String filePath)
    {
        this.tramwajObj = tramwajObj;
        this.filePath = filePath;
    }

    public EdycjaTramwaju()
    {
        tramwajObj = new Tramwaj();
        filePath = "TRAMWAJ.BIN";
    }

    public void initGUI()
    {
        frame = new JFrame("Edycja Tramwaju");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        kontener = frame.getContentPane();
        layout = new GridLayout(7, 2);
        kontener.setLayout(layout);

        setPojazdEditorLabs(tramwajObj);
        setTramwajEditorLabs(tramwajObj);
        addSaveButton();

        frame.pack();
        frame.setVisible(true);
    }

    void setTramwajEditorLabs(Tramwaj obj)
    {
        kierunkowoscLab = new JLabel("Kierunkowosc: ");
        kontener.add(kierunkowoscLab);
        kierunkowoscJCB = new JComboBox<>(new Integer[]{1, 2});
        kierunkowoscJCB.setSelectedItem(obj.kierunkowosc);
        kontener.add(kierunkowoscJCB);

        rozstawTorowLab = new JLabel("Rozstaw torow (mm): ");
        kontener.add(rozstawTorowLab);
        rozstawTorowText = new JTextField(Integer.toString(obj.rozstawTorowMM), 40);
        kontener.add(rozstawTorowText);

        wysokoscPodlogiLab = new JLabel("Wysokosc podlogi (cm): ");
        kontener.add(wysokoscPodlogiLab);
        wysokoscPodlogiText = new JTextField(Integer.toString(obj.wysokoscPodlogiCM), 40);
        kontener.add(wysokoscPodlogiText);        
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object src = e.getSource();
        if(src == saveButton)
        {
            try
            {
                Tramwaj obj = retNewObj();
                Serialize.write(obj, filePath);
                infoBox("Poprawnie zapisano.", "Sukces");
            }
            catch(Exception ecx)
            {
                infoBox("Wprowadzono nieprawidlowe dane.", "Blad");
            }
        }
    }
    
    Tramwaj retNewObj()
    {
        return new Tramwaj(super.retNewObj(), Integer.parseInt(rozstawTorowText.getText()), (Integer)kierunkowoscJCB.getSelectedItem() ,Integer.parseInt(wysokoscPodlogiText.getText()));
    }

}
