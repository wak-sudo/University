import java.util.HashMap;

public class Add extends Expression {

    Expression l;
    Expression r;

    Add(Expression a, Expression b)
    {
        l = a;
        r = b;
    }

    public int evaluate(HashMap<Character, Integer> valuations)
    {
        return l.evaluate(valuations) + r.evaluate(valuations);
    }

    public String toString()
    {
        return '(' + l.toString() + " + " + r.toString() + ')';
    }
}
