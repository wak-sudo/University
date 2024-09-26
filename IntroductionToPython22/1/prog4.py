from losowanie_fragmentow import losuj_fragment

def losuj_haslo(n):
    wynik = ""
    if(n > 1):
        while len(wynik) != n:
            freeSpace = n - len(wynik)
            temp = losuj_fragment()
            dl = len(temp)
            if freeSpace - dl > 1 or freeSpace - dl == 0:
                wynik += temp
    return wynik

for i in range(10):
    print(losuj_haslo(8))
print()
for i in range(10):
    print(losuj_haslo(12))

