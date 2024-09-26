/*
* Wojciech Kieloch
* Lista 3 zad. 3
* Microsoft Visual Studio .NET 7.0
*/

namespace TimeNTonDLL
{
    public sealed class TimeNTon
    {
        const int N = 2;
        const int labStartH = 16;
        const int labEndH = 18;
        static int numberOfInstances = 0;
        static TimeNTon?[] labInstances = new TimeNTon[N];
        static TimeNTon? offHoursInstance = null;

        public static TimeNTon Instance(int currentHour)
        {
            currentHour %= 24;
            if (currentHour >= labStartH && currentHour < labEndH)
            {
                offHoursInstance = null;

                numberOfInstances %= N;
                TimeNTon? inst = labInstances[numberOfInstances];
                if (inst == null)
                {
                    inst = new TimeNTon();
                    labInstances[numberOfInstances] = inst;
                }
                numberOfInstances++;
                return inst;
            }
            else
            {
                // Chcę, aby dla każdej pracowni były zwracane różne objekty.
                // dlatego w czasie pracowni nulluje offHoursInstance
                // a poza pracownią usuwam informację o poprzednich objektach przy pomocy reset().
                if (labInstances[0] != null) reset();

                if (offHoursInstance == null)
                    offHoursInstance = new TimeNTon();
                return offHoursInstance;
            }

        }

        static void reset()
        {
            numberOfInstances = 0;
            for (int i = 0; i < N; i++)
                labInstances[i] = null;
        }
    }
}