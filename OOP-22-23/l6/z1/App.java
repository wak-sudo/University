/*
* Wojciech Kieloch
* Lista 6 zad. 1
* javac *.java
* java App
*/

import java.io.*;

public class App {
    public static void main(String[] args) throws Exception {
        OrderList<Integer> przyk = new OrderList<>();

        przyk.add_element(1);
        przyk.add_element(3);
        przyk.add_element(2);
        przyk.add_element(4);

        przyk.print();
        try
        {
            FileOutputStream fileStream = new FileOutputStream("objekt.bin");
            ObjectOutputStream objectStream =  new ObjectOutputStream(fileStream);
            objectStream.writeObject(przyk);

            objectStream.close();
            fileStream.close();
        }
        catch(IOException ex)
        {
            System.out.println(ex);
        }

        przyk = null;

        try {
            FileInputStream fileStream = new FileInputStream("objekt.bin");
            ObjectInputStream objectStream = new ObjectInputStream(fileStream);
 
            var object = (OrderList<?>)objectStream.readObject();
 
            objectStream.close();
            fileStream.close();

            object.print();
        }
        catch (Exception ex) {
            System.out.println(ex);
        }
    }
}
