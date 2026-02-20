/*
* Wojciech Kieloch
* Lista 3 zad. 1
* Microsoft Visual Studio .NET 7.0
*/

using ListaDLL;

namespace ConsoleApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Lista<int> przyk = new Lista<int>();

            przyk.push_back(3);
            przyk.push_back(4);
            przyk.push_back(5);
            przyk.print();

            przyk.push_front(2);
            przyk.print();

            przyk.push_front(1);
            przyk.print();

            przyk.pop_front();
            przyk.pop_back();
            przyk.print();
            Console.WriteLine();
            Console.WriteLine("Is empty? " + przyk.is_empty());
        }
    }
}