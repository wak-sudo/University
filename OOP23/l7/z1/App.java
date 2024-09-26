/*
* Wojciech Kieloch
* Lista 7
* javac *.java
* java App
*/

import java.io.*;

public class App {
    public static void main(String[] args) throws Exception {
        if(args.length == 2)
        {
            String filePath = args[0];
            String className = args[1].toLowerCase();
            File f = new File(filePath);
            if(!f.isDirectory() && f.exists())
            {      
                if (className.equals("pojazd"))
                {
                    var editor = new EdycjaPojazdu((Pojazd)Serialize.read(filePath), filePath);
                    editor.initGUI();
                } else if (className.equals("samochod"))
                {
                    var editor = new EdycjaSamochodu((Samochod)Serialize.read(filePath), filePath);
                    editor.initGUI();
                } else if (className.equals("tramwaj"))
                {
                    var editor = new EdycjaTramwaju((Tramwaj)Serialize.read(filePath), filePath);
                    editor.initGUI();
                } else System.out.println("Podaj dostepna nazwe klasy.");
            }
            else
            {
                System.out.println("Niepoprawna sciezka, tworzymy nowy plik.");
                if (className.equals("pojazd"))
                {
                    var editor = new EdycjaPojazdu();
                    editor.initGUI();
                } else if (className.equals("samochod"))
                {
                    var editor = new EdycjaSamochodu();
                    editor.initGUI();
                } else if (className.equals("tramwaj"))
                {
                    var editor = new EdycjaTramwaju();
                    editor.initGUI();
                } else System.out.println("Podaj dostepna nazwe klasy.");
            }
        }
        else System.out.println("Podaj dwa argumenty.");
    }
}
