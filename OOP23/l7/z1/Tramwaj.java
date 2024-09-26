public class Tramwaj extends Pojazd {
    int rozstawTorowMM;
    int kierunkowosc;
    int wysokoscPodlogiCM;

    public Tramwaj(Pojazd pojazdInfo,  int rozstawTorowMM, int kierunkowosc, int wysokoscPodlogi) throws IllegalArgumentException
    {
        super(pojazdInfo);
        if (rozstawTorowMM < 750 || (kierunkowosc != 1 && kierunkowosc != 2) || wysokoscPodlogi < 0) throw new IllegalArgumentException();
        this.rozstawTorowMM = rozstawTorowMM;
        this.kierunkowosc = kierunkowosc;
        this.wysokoscPodlogiCM = wysokoscPodlogi;
    }

    public Tramwaj()
    {
        rozstawTorowMM = 750;
        kierunkowosc = 1;
        wysokoscPodlogiCM = 0;
    }

    public String toString()
    {
        return super.toString() + " " + Integer.toString(rozstawTorowMM) + " " + Integer.toString(kierunkowosc) + " " + Integer.toString(wysokoscPodlogiCM);
    }
}
