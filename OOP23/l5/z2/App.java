/*
* Wojciech Kieloch
* Lista 5 zad. 2
* javac *.java
* java App
*/

import java.util.HashMap;

public class App {
    public static void main(String[] args) throws Exception {
        // 1 + (a + b) * 4
        Expression exp = new Add(new Const(1), new Mult(new Add(new Variable('a'), new Variable('b')), new Const(4)));
        HashMap<Character, Integer> valuations = new HashMap<>(); 
        valuations.put('a', 1);
        valuations.put('b', 4);
        System.out.println(exp.evaluate(valuations));
        System.out.println(exp.toString());

        Expression exp2 = new Const(41);
        System.out.println(exp2.evaluate());
        System.out.println(exp2.toString());
    }
}
