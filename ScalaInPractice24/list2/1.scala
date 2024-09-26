package numbers
{
    class Rational(val num : Long, val den : Long)
    {
        require(den != 0, "Denominator cannot be zero")

        private def simplify(x : Rational) : Rational =
        {
            val gcd_val = GCD(x.num.abs, x.den.abs)
            new Rational(x.num / gcd_val, x.den / gcd_val)
        }

        private def GCD(x : Long, y: Long) : Long = // small
        {
            if(y == 0) x
            else GCD(y, x % y)
        }

        def +(other: Rational): Rational =
        {
            val newNum = this.num * other.den + other.num * this.den
            val newDen = this.den * other.den
            simplify(new Rational(newNum, newDen))
        }

        def -(other: Rational): Rational = 
        {
            val newNum = this.num * other.den - other.num * this.den
            val newDen = this.den * other.den
            simplify(new Rational(newNum, newDen))
        }

        def *(other: Rational): Rational = 
        {
            val newNum = this.num * other.num
            val newDen = this.den * other.den
            simplify(new Rational(newNum, newDen))
        }

        def /(other: Rational): Rational = 
        {
            //assert(other.num != 0)
            val newNum = this.num * other.den
            val newDen = this.den * other.num
            simplify(new Rational(newNum, newDen))
        }
        
        def abs: Rational =
        {
            new Rational(num.abs, den.abs)
        }

        override def toString : String =
        {
            val simRat = simplify(this)
            simRat.num.toString + " " + simRat.den.toString
        }

        def toDouble : Double = num / den
    }    

    object Rational
    {
        def apply(numerator : Long, denumerator : Long) : Rational = new Rational(numerator, denumerator)
        def apply(numerator : Long) : Rational = new Rational(numerator, 1)
        def zero: Rational = new Rational(0, 1)
        def one: Rational = new Rational(1, 1)
    }
}