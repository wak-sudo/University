import Utils.curry

object Utils
{
    def isSorted(as: List[Int], ordering: (Int, Int) => Boolean) : Boolean = {
        if(as.length <= 1) true
        else if(ordering(as.head, as.tail.head) == true) 
            isSorted(as.tail, ordering)
        else false
    }

    def isAscSorted(as: List[Int]) = {
        def seThan(a : Int, b : Int) = { a <= b }
        isSorted(as, _ <= _)
    }

    def isDescSorted(as: List[Int]) = {
        def beThan(a : Int, b : Int) = { if(a >= b) true else false }
        isSorted(as, _ >= _)
    }

    def foldLeft[A, B](l: List[A], z: B)(f: (B, A) => B): B = {
       if(l.length == 0) z
       else foldLeft(l.tail, f(z, l.head))(f)
    }

    def sum(l: List[Int]) = {
        def sum(a : Int, b : Int) = a + b
        foldLeft(l, 0)(_ + _)
    }

    def length[A](l: List[A]) = {
        def calc(a : Int, b : A) = a + 1
        foldLeft(l, 0)(calc)
    }

    def compose[A, B, C](f : B => C, g : A => B)(x : A) : C = {
        f(g(x))
    }

    def repeated(f : Int => Int, n: Int) = { // some misundertstanding
        def helper(f : Int => Int, n : Int, iter : Int) : Int = {
            if(iter == 1) f(n)
            else f(helper(f, n, iter - 1))
        }
        assert(n >= 0)
        helper(f, n, n)
    }

    def curry[A, B, C](f : (A, B) => C) : A => (B => C) = {
        def g(x : A)(y : B) = f(x, y)
        g
    }

    def uncurry[A, B, C](f : A => (B => C)) : (A, B) => C = {
        def g(x : A, y : B) = f(x)(y)
        g 
    }
        

}

object Main1 extends App
{
    val l1 = List(1, 2, 3, 4, 5)
    val l2 = List(1, 2, 7, 4, 5)
    val l3 = List(5, 4, 3, 2, 1)
    println(Utils.isAscSorted(l1))
    println(Utils.isAscSorted(l2))
    println(Utils.isAscSorted(l3))
    println(Utils.isDescSorted(l1))
    println(Utils.isDescSorted(l2))
    println(Utils.isDescSorted(l3))

    println(Utils.sum(l1))
    println(Utils.length(l1))

    def simSum(a : Int, b : Int) = a + b
    def succesor(a : Int) : Int = a + 1
    def power(a : Int) = a * a

    println(Utils.compose(succesor, power)(3))
    println(Utils.repeated(succesor, 3))

    def curTest = Utils.curry(simSum)
    println(curTest(1)(1))
    def uncurTest = Utils.uncurry(curTest)
    println(uncurTest(1, 1))
}
