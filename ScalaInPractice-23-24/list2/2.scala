import numbers.Rational

package figures
{
    class Point(val x : Rational, val y : Rational) {}

    trait absFigures {
        val description : String;
        def area : Rational
    }

    class Triangle(a : Point, b : Point, c : Point) extends absFigures
    {
        override def area : Rational = Rational(1, 2)*(a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))

        val description: String = "Triangle" 
    }

    class Rectangle(a : Point, b : Point) extends absFigures
    {
        override def area : Rational = 
        {
            val width = (a.x - b.x).abs
            val height = (a.y - b.y).abs
            width*height
        }

        def description: String = "Rectangle" 
    }

    class Square(a : Point, b : Point) extends absFigures
    {
        override def area : Rational = (a.x - b.x)*(a.x - b.x)

        override def description: String = "Square" 
    }

    object Triangle
    {
        def apply(a : Point, b : Point, c : Point) = new Triangle(a, b, c)
    }

    object Rectangle
    {
        def apply(a : Point, b : Point) = new Rectangle(a, b)
    }

    object Square
    {
        def apply(a : Point, b : Point) = new Square(a, b)
    }

    object Point
    {
        def apply(a : Rational, b : Rational) = new Point(a, b)
    }
}