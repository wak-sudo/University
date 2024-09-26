import java.util.HashMap;

public class Const extends Expression {

    int val;
    
    Const(int a)
    {
        val = a;
    }

    public int evaluate(HashMap<Character, Integer> valuations)
    {
        return val;
    }

    public String toString()
    {
        return String.valueOf(val);
    }

}