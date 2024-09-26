object Basic extends App 
{
    def isPrimeUgly(n: Int): Boolean =
    {
        if(n < 2) false 
        else if(n == 2) true
        else if(n % 2 == 0) false
        else
        {
            var res = true
            var iter = 3
            if(iter * iter <= n)
            {
                do
                {
                    if(n % iter == 0)
                        res = false
                    iter += 2
                }
                while(iter * iter <= n && res)
            }
            res
        }
        
    }

    for (num <- 1 to 100) {
        if(isPrimeUgly(num))
            print(num + " ")
    }
    println()

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

    for (num <- 1 to 100) {
        if(isPrime(num))
            print(num + " ")
    }

} 