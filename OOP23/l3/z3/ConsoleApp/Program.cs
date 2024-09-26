/*
* Wojciech Kieloch
* Lista 3 zad. 3
* Microsoft Visual Studio .NET 7.0
*/

using TimeNTonDLL;

namespace ConsoleApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            TimeNTon a = TimeNTon.Instance(17);
            TimeNTon b = TimeNTon.Instance(17);
            TimeNTon c = TimeNTon.Instance(17); // c <=> a
            TimeNTon d = TimeNTon.Instance(18);
            TimeNTon e = TimeNTon.Instance(18); // d <=> e
            TimeNTon f = TimeNTon.Instance(17); // traktowane jako następne pracownie.
        }
    }
}