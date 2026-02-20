import figures._
import numbers.Rational
import sing.Singleton

object Main extends App
{
    val a = Point(Rational(1), Rational(3))
    val a2 = Point(Rational(-1), Rational(-3))
    val b = Point(Rational(2), Rational(5))
    val c = Point(Rational(6), Rational(7))
    val tri = Triangle(a, b, c)
    val sqr = Square(a, a2)
    val rec = Rectangle(b, c)
    val myList = List(tri, sqr, rec)
    Singleton.areaSum(myList)
    Singleton.printAll(myList)
}