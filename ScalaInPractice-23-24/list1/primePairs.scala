object Basic extends App
{
    def getSieveUgly(n : Int) : Array[Boolean] = {
        if(n == 0) Array(false)
        else if(n == 1) Array(false, false)
        else
        {
            var sieve = Array.fill(n+1){true}
            sieve(0) = false
            sieve(1) = false

            var i = 2
            if(i*i <= n)
            {
                do
                {
                    if(sieve(i) == true)
                    {
                        var j = i*i
                        if(j <= n)
                        {
                            do
                            {
                                sieve(j) = false
                                j += i
                            }
                            while(j <= n)
                        }
                    }
                    i += 1
                }
                while(i*i <= n)
            }
            sieve
        }
    }

    def primePairsUgly(n : Int): List[(Int, Int)] = {
        val arraySize = 2*n-2 // this is the maximum number we can obtain from summation.
        // n is at least 4
        val sieve = getSieveUgly(arraySize)
        var j = 1
        var res = Array.empty[(Int, Int)]
        do
        {
            var i = j+1
            if(i < n)
            {
                do
                {
                    if(j != i && sieve(i+j) == true)
                        res = res :+ (j, i)    
                    i += 1
                }
                while(i<n)
            }
            j += 1

        } while(j<n)
        res.toList
    }

    primePairsUgly(10).foreach { pair =>
        println("(" + pair._1 + ", " + pair._2 + ")")
    }

    println()

    primePairs(10).foreach { pair =>
        println("(" + pair._1 + ", " + pair._2 + ")")
    }

    def primePairs(n : Int): List[(Int, Int)] = {
        val range = 1 to n-1
        val allPairs = modCartes(range.toList)
        allPairs.filter(pair => isPrime(pair._1+pair._2))
    }

    def createPairs(item : Int, xs : List[Int]) : List[(Int, Int)] =
    {
        if(xs.isEmpty)
            List[(Int, Int)]()
        else
            List((item, xs(0))) ++ createPairs(item, xs.tail)       
    }

    def modCartes(xs: List[Int]) : List[(Int, Int)] =
    {
        if(xs.size == 1)
            List[(Int, Int)]()
        else
            createPairs(xs(0), xs.tail) ++ modCartes(xs.tail)
    }

    def isPrime(n: Int): Boolean = {
        if(n < 2) false
        else if(n == 2) true
        else if(n % 2 == 0) false
        else isPrimeRec(n, 3)
    }

    def isPrimeRec(n: Int, div : Int) : Boolean = 
    {
        if(div * div > n) true
        else if(n % div == 0) false
        else isPrimeRec(n, div+2)
    } 
}