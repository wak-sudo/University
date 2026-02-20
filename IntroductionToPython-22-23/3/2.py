import random

def fermat(n, k=3):
    while k > 0:
        a = random.randint(2, n-2)
        if pow(a, n-1, n) != 1:
            return False
        k-=1
    return True

def czyJestPierwsza(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    i = 3    
    while i * i <= n:
        if n % i == 0:
            return False
        i += 2
    return True

def generujKombinacje(iloscCyfr, iloscSiodemek):
    liczby = set()
    srodek = int(('7' * iloscSiodemek))
    prefixLen = 0
    suffixLen = iloscCyfr - iloscSiodemek

    while suffixLen >= 0:
        podstawa = srodek*(10**suffixLen)
        wykladnik = (10**(10 - prefixLen))
        for sufix in range(10**suffixLen):       
            for prefix in range(int(10**(prefixLen - 1)),int(10**prefixLen)):
                liczby.add(prefix*wykladnik + podstawa + sufix)
        suffixLen-=1
        prefixLen+=1

    return liczby


iloscCyfr = int(input("Ile cyfr ma miec liczba?: "))
iloscSiodemek = int(input("Ile siódemek pod rząd ma mieć liczba?: "))

if(iloscCyfr >= iloscSiodemek):
    liczby = generujKombinacje(iloscCyfr, iloscSiodemek)

    licznik = 0
    for i in liczby:
        if fermat(i) and czyJestPierwsza(i):
            licznik+=1

    print("Takich liczb jest:", licznik) # 203
else:
    print("Nie można wygenerować takiej liczby.")