/*
* Wojciech Kieloch
* Lista 4 zad. 2
* Microsoft Visual Studio .NET 7.0:
* msbuild SlowaFibonacciego.sln
* jeżeli pojawią się błędy: dotnet restore
* i ponowić próbę.
*/

using System.Collections;
using System;

namespace SlowaFibonacciego
{
    class SlowaFibonacciego : IEnumerable
    {
        readonly uint iloscSlow;

        public SlowaFibonacciego(uint iloscSlow)
        {
            this.iloscSlow = iloscSlow;
        }

        public IEnumerator GetEnumerator()
        {
            if (iloscSlow == 0) yield break;
            
            string nOne = "b";
            yield return nOne;
            if (iloscSlow == 1) yield break;

            string nTwo = "a";
            yield return nTwo;

            for(int i = 2; i < iloscSlow; i++)
            {
                string newWord = nTwo + nOne;
                yield return newWord;
                (nOne, nTwo) = (nTwo, newWord);
            }
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            var przyk = new SlowaFibonacciego(6);
            foreach(string s in przyk)
            {
                Console.WriteLine(s);
            }
        }
    }
}