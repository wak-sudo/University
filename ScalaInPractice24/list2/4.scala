import figures._
import numbers.Rational
import sing.Singleton

object Main extends App
{
    val a = Point(Rational(1), Rational(3))
    val a2 = Point(Rational(-1), Rational(-3))
    val b = Point(Rational(2), Rational(5))
    val c = Point(Rational(6), Rational(7))

    println(Rational(5, 3) * Rational(1, 5))
    println(Rational(5, 3) + Rational(1, 5))
    println(Rational(5, 3) - Rational(1, 5))
    println(Rational(5, 3) / Rational(1, 5))

    val tri = Triangle(a, b, c)
    val sqr = Square(a, a2)
    val rec = Rectangle(b, c)

    val myList = List(tri, sqr, rec)

    println("Area: " + Singleton.areaSum(myList).toString)
    Singleton.printAll(myList)
    println()

    //Rational(1, 0)
}