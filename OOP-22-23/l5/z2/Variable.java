import java.util.HashMap;

public class Variable extends Expression {

    char symbol;
    
    Variable(char a)
    {
        symbol = a;
    }

    public int evaluate(HashMap<Character, Integer> valuations)
    {
        if(valuations.containsKey(symbol))
            return valuations.get(symbol);
        else return 0;
    }

    public String toString()
    {
        return String.valueOf(symbol);
    }
}
