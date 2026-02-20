from math import sqrt

def czyPierwsza(n):
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

def czyMaSiodemki(n):
    n = str(n)
    if(n.find((3 * '7')) >= 0):
        return True
    else:
        return False

licznik = 0
for i in range(1, 100_001):
    if(czyMaSiodemki(i)):
        if(czyPierwsza(i)):
            print(i, end=' ')
            licznik+=1
print()
print("Takich liczb jest:", licznik)
