public class AFranks implements Comparable<AFranks>
{
    int ranga;
    public int getRank()
    {
        return this.ranga;
    }

    @Override
    public int compareTo(AFranks otherStopien)
    {
        return Integer.compare(this.getRank(), otherStopien.getRank());
    }
}