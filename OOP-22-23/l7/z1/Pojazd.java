import java.io.Serializable;

public class Pojazd implements Serializable {
    String model;
    int rokProdukcji;
    int przebiegKM;

    public String toString()
    {
        return model + " " + Integer.toString(rokProdukcji) + " " + Integer.toString(przebiegKM);
    }

    public Pojazd(String model, int rokProdukcji, int przebieKM) throws IllegalArgumentException
    {
        if(rokProdukcji < 1800 || przebieKM < 0)
            throw new IllegalArgumentException();
        this.rokProdukcji = rokProdukcji;
        this.przebiegKM = przebieKM;
        this.model = model;
    }

    public Pojazd(Pojazd obj)
    {
        model = obj.model;
        rokProdukcji = obj.rokProdukcji;
        przebiegKM = obj.przebiegKM;
    }

    public Pojazd()
    {
        model = "";
        rokProdukcji = 1800;
        przebiegKM = 0;
    }
}
