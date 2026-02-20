/*
* Wojciech Kieloch
* Lista 2 zad. 1
* Microsoft Visual Studio .NET 7.0
*/

namespace IntStream
{
    class IntStream
    {
        protected int counter = -1;

        public int Next()
        {
            return ++counter;
        }

        public bool Eos()
        {
            if (counter + 1 < 0) return true;
            return false;
        }

        public void Reset()
        {
            counter = -1;
        }
    }

    class PrimeStream : IntStream
    {
        static bool IsPrime(int n)
        {
            if (n < 2) return false;
            if (n == 2) return true;
            if (n % 2 == 0) return false;
            for (int i = 3; i * i <= n; i += 2)
                if (n % i == 0) return false;
            return true;
        }

        public new int Next()
        {
            if (counter == -1)
            {
                counter = 2;
                return counter;
            }

            if (counter == 2)
            {
                counter = 3;
                return counter;
            }

            do
            {
                counter += 2;
            } while (!IsPrime(counter));
            return counter;
        }

        public new bool Eos()
        {
            if (counter != -1 && counter != 2)
            {
                int nextPrime = counter;
                do
                {
                    nextPrime += 2;
                    if (nextPrime < counter) return true;
                } while (!IsPrime(nextPrime));
            }
            return false;
        }
    }

    class RandomStream : IntStream
    {
        readonly protected Random rnd = new Random();

        public new int Next()
        {
            return rnd.Next();
        }

        public new bool Eos()
        {
            return false;
        }
    }

    class RandomWordStream : RandomStream
    {
        readonly PrimeStream PS = new PrimeStream();

        public new string Next()
        {
            int primeLength = PS.Next();
            string res = "";
            for (int i = 0; i < primeLength; i++)
                res += rndChar();
            return res;
        }

        public new bool Eos()
        {
            return PS.Eos();
        }

        char rndChar()
        {
            return (char)(rnd.Next('A', 'Z' + 1));
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            const int numberOfExamples = 5;

            IntStream @is = new IntStream();
            Console.WriteLine("IntStream:");
            for (int i = 0; i < numberOfExamples; i++)
                if (!@is.Eos())
                    Console.WriteLine(@is.Next());

            Console.WriteLine();
            PrimeStream ps = new PrimeStream();
            Console.WriteLine("PrimeStream:");
            for (int i = 0; i < numberOfExamples; i++)
                if (!ps.Eos())
                    Console.WriteLine(ps.Next());

            Console.WriteLine();
            RandomStream rs = new RandomStream();
            Console.WriteLine("RandomStream:");
            for (int i = 0; i < numberOfExamples; i++)
                if (!rs.Eos())
                    Console.WriteLine(rs.Next());

            Console.WriteLine();
            RandomWordStream rws = new RandomWordStream();
            Console.WriteLine("RandomWordStream:");
            for (int i = 0; i < numberOfExamples; i++)
                if (!rws.Eos())
                    Console.WriteLine(rws.Next());
        }
    }
}