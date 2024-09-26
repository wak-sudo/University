import math

def sito(upperBound):
    listaLiczb = [i for i in range(0, upperBound+1)]
    listaLiczb[0] = 0
    listaLiczb[1] = 0
    i = 2
    while i * i <= upperBound:
        if listaLiczb[i] != 0:
            for j in range(i * i, upperBound+1, i):
                listaLiczb[j] = 0
        i+=1

    return listaLiczb

def czyJestPalindromem(s):
    s = str(s)
    return True if s == s[::-1] else False

def palindromy(a, b):
    if a>b or a<0 or b<0 or b<2:
        return []
    liczbySita = sito(b)
    liczbyZPrzedzialu = []
    for i in range(a, b+1):
        if liczbySita[i] != 0:
            liczbyZPrzedzialu.append(i)

    wynik = []
    for i in liczbyZPrzedzialu:
        if czyJestPalindromem(i):
            wynik.append(i)
    return wynik

print(palindromy(0, 100000))