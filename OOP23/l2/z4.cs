/*
* Wojciech Kieloch
* Lista 2 zad. 4
* Microsoft Visual Studio .NET 7.0
*/

namespace LazyIntList
{
    class LazyIntList
    {
        protected List<int> LazyList = new List<int>();

        public int Element(int i)
        {
            if (i <= 0) throw new IndexOutOfRangeException();
            while (LazyList.Count < i)
            {
                LazyList.Add(LazyList.Count + 1);
            }
            return LazyList[i - 1];
        }

        public int Size()
        {
            return LazyList.Count;
        }
    }

    class LazyPrimeList : LazyIntList
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
        public new int Element(int i)
        {
            if (i <= 0) throw new IndexOutOfRangeException();

            if(LazyList.Count < i)
            {
                if (i >= 0 && LazyList.Count == 0)
                {
                    LazyList.Add(2);
                }

                if (i >= 1 && LazyList.Count == 1)
                {
                    LazyList.Add(3);
                }

                while (LazyList.Count < i)
                {
                    int nextPrimeNumber = LazyList.Last() + 2;
                    while (!IsPrime(nextPrimeNumber))
                        nextPrimeNumber += 2;
                    LazyList.Add(nextPrimeNumber);
                }
            }
            return LazyList[i - 1];
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            LazyIntList ls = new LazyIntList();
            ls.Element(25);

            LazyPrimeList lp = new LazyPrimeList();
            Console.WriteLine(lp.Element(20));
            Console.WriteLine(lp.Element(30));
            Console.WriteLine(ls.Element(30));
            Console.WriteLine(lp.Element(25));
            
            Console.WriteLine("Sizes: {0} {1}", ls.Size(), lp.Size());
        }
    }
}