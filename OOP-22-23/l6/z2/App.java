/*
* Wojciech Kieloch
* Lista 6 zad. 2
* javac *.java
* java App
*/

import java.util.Arrays;

public class App {
    public static void main(String[] args) throws Exception {
        OrderList<Integer> przyk = new OrderList<>();
        przyk.addAll(Arrays.asList(1, 3, 5, 4));
        przyk.print();
        przyk.removeAll(Arrays.asList(3, 4));
        przyk.print();
        przyk.add(7);
        przyk.add(8);
        przyk.print();
        System.out.println("Zawiera 5 i 7: " + przyk.containsAll(Arrays.asList(5, 7)));
        przyk.retainAll(Arrays.asList(5, 7));
        przyk.print();
        System.out.println("Rozmiar: " + przyk.size);
        przyk.addAll(Arrays.asList(1, 3, 5, 4));
        for(var c : przyk)
            System.out.print(c + " | ");
        System.out.println();

        System.out.println("Array1 (toArray): ");
        var arr = przyk.toArray();
        for(var c : arr)
            System.out.print(c + " | ");
        System.out.println();

        Integer[] a = new Integer[3];
        System.out.println("Array2 (kopiowanie, pierwsze trzy el.): ");
        przyk.toArray(a);
        for(var c : a)
            System.out.print(c + " | ");
        System.out.println();
        przyk.clear();
        System.out.println("Clear:");
        przyk.print();        
    }
}
