# zrobione

polAlf = "aąbcćdeęfghijklłmnńoóprsśtuwyzźżxvq" # łacińskie znaki na końcu

def findWords(slowo, wolneSlowa):
    wynik = []
    for i in range(len(slowo)):
        for j in range(len(polAlf)):
            slowoList = list(slowo)
            slowoList[i] = polAlf[j]
            potencjalneSlowo = ''.join(slowoList)
            if potencjalneSlowo in wolneSlowa:
                wynik.append(potencjalneSlowo)
    return wynik

def findPath(poczSlowo, konSlowo, wszystkieSlowa):
    wolneSlowa = set(wszystkieSlowa)
    if poczSlowo in wolneSlowa: wolneSlowa.remove(poczSlowo)
    if konSlowo not in wolneSlowa: return None
    kolejka = [[poczSlowo]]
    while len(kolejka) != 0:
        rozmiarKolejki = len(kolejka)
        nowaKolejka = []
        #for i in range(rozmiarKolejki):
        for aktualnaSciezka in kolejka:
            #aktualnaSciezka = kolejka.pop()
            noweSlowa = findWords(aktualnaSciezka[-1], wolneSlowa)
            for noweSlowo in noweSlowa:
                sciezka = aktualnaSciezka.copy()
                sciezka.append(noweSlowo)
                if(noweSlowo == konSlowo):
                    return sciezka
                if noweSlowo in wolneSlowa: wolneSlowa.remove(noweSlowo)
                nowaKolejka.append(sciezka)
        kolejka = nowaKolejka
    return None

slowa = { "ted", "tex", "red", "tax", "tad", "den","rex", "pee" }
slowa2 = {'mąka', 'mika', 'miks', 'kiks', 'keks'}
print(findPath("mąka", "keks", slowa2))