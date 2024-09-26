public class Samochod extends Pojazd {
    String kategoria;
    Boolean automatSkrzynia;
    int liczbaDzwi; 

    public Samochod(Pojazd pojazdInfo,  String kategoria, Boolean automatSkrzynia, int liczbaDzwi)
    {   
        super(pojazdInfo);
        if(liczbaDzwi < 0) throw new IllegalArgumentException();
        this.liczbaDzwi = liczbaDzwi;
        this.kategoria = kategoria;
        this.automatSkrzynia = automatSkrzynia;      
    }

    public Samochod()
    {
        kategoria = "";
        automatSkrzynia = false;
        liczbaDzwi = 0;
    }

    public String toString()
    {
        return super.toString() + " " + kategoria + " " + Boolean.toString(automatSkrzynia) + " " + Integer.toString(liczbaDzwi);
    }
}
