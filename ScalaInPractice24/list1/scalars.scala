object Basic extends App
{
    def scalarUgly(xs: List[Int], ys: List[Int]) =
    {
        var i = 0
        var res = 0
        do
        {
            res += xs(i) * ys(i)
            i += 1
        }
        while (i < xs.size)
        res
    }

    def scalar(xs: List[Int], ys: List[Int]) = 
    {
        (for ((x, y) <- xs zip ys) yield x * y).sum
    }

    val l1 = List(1, 2, 3)
    val l2 = List(4, 5, 6)
    println(scalarUgly(l1, l2))
    println(scalar(l1, l2))
}

