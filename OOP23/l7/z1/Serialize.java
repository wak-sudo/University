import java.io.*;

public class Serialize {

    public static void write(Object obj, String fileName)
    {
            try
            {
                FileOutputStream fileStream = new FileOutputStream(fileName);
                ObjectOutputStream objectStream =  new ObjectOutputStream(fileStream);
                objectStream.writeObject(obj);

                objectStream.close();
                fileStream.close();
            }
            catch(IOException ex)
            {
                System.out.println(ex);
            }
    }

    public static Object read(String filePath)
    {
        try {
            FileInputStream fileStream = new FileInputStream(filePath);
            ObjectInputStream objectStream = new ObjectInputStream(fileStream);
 
            var object = objectStream.readObject();
 
            objectStream.close();
            fileStream.close();

            return object;
        }
        catch (Exception ex) {
            System.out.println(ex);
        }
        return null;
    }
}
