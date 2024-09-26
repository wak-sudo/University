def silnia(n):
        wynik = 1
        for i in range(2, n+1):
            wynik *= i
        return wynik

base = silnia(3)
koncowka = "cyfry"
for i in range(4, 101):
    base *= i
    liczba_cyfr = len(str(base))
    dziesiatki = int(liczba_cyfr/10) % 10
    jednosci = liczba_cyfr % 10
    if(dziesiatki == 1 or jednosci <= 1 or jednosci >= 5):
        koncowka = "cyfr"
    else:
        koncowka = "cyfry"
    print("!" + str(i) + " ma " + str(liczba_cyfr) + " " + koncowka)