class R:
    def __init__(self, licznik, mianownik) -> None:
        self.licznik = licznik
        if mianownik == 0: raise Exception("Nie można dzielić przez zero.")
        self.mianownik = mianownik

    @staticmethod
    def NWD(a, b):
        while(b!=0):
            temp = b
            b = a%b
            a = temp
        return a

    @staticmethod
    def NWW(self, a, b):
        return a*b/self.NWD(a,b)

    def __str__(self):
        return '{self.licznik}/{self.mianownik}'

    def __add__(self, other):
        WK = self.NWW(self.mianownik, other.mianownik)
        return self.licznik*WK/self.mianownik + other.licznik*WK/other.mianownik, WK

R1 = R(1,3)
R2 = R(1,5)
R3 = R1 + R2
print(R3)
