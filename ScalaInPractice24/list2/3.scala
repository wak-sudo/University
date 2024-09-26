package sing
import figures._

object Singleton
{
    def areaSum(figures: List[absFigures]): Double = {
    // if(figures.isEmpty) 0
    // else figures.head.area.toDouble + areaSum(figures.tail)

        figures.map(_.area.toDouble).sum
    }

    def printAll(figures: List[absFigures]): Unit = {
        for (x <- figures) print(x.description + " ")
    }
}

