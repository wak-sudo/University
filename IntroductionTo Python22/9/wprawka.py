def generujZestawienie(znaki): # popraw to
    zestawienia = []
    for k in range(0, len(znaki)-1): #szerokość okna
        for i in range(0, len(znaki)): # przesunięcie okna
            for j in range(i+k, len(znaki)): # z czym połączyć
                zestawienia += [znaki[i:k+i] + [znaki[j]]]
    zestawienia += znaki
    return zestawienia

sciezka = "plik.txt"
jezykZnaki = {}
for line in open("plik.txt", encoding='utf8'):
    line = line.split(":")
    znakISO = line[0]    
    tekst = ''.join(line[1]).strip().replace(' ', '')
    znaki = set()
    for c in tekst:
            znaki.add(c)
    jezykZnaki[znakISO] = znaki
wynik = generujZestawienie(list(jezykZnaki.keys()))

'''
for i in range(0, znaki):
    for j in range(j)
for per in permutacje:
    symbole = set()
    for znak in per:
        print(znak, end=' ')
        symbole = symbole | jezykZnaki[znak]
    print(":")
    for sym in symbole:
        print(sym, end ="")
input()
'''




