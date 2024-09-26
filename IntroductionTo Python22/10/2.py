polAlf = "aąbcćdeęfghijklłmnńoóprsśtuwyzźż"
odleglosci = dict(zip(polAlf, list(range(len(polAlf)))))

def cesar(s,k):
    tabela = dict(zip(polAlf, polAlf[k:] + polAlf[0:k]))
    return ''.join(tabela[c] for c in s.lower())

def clearWord(s):
    wynik = []
    polAlfBig = polAlf.upper()
    for c in s:
        if c in polAlfBig or c in polAlf:
            wynik += c
    return ''.join(wynik)

dic = dict()
print("Generowanie słownika.")
for line in open("slowa.txt", encoding="utf8"):
    line = clearWord(line).strip().lower()
    if len(line) > 3: # usunąć zespute znaki
        klucz = odleglosci[line[0]] - odleglosci['a']
        if klucz != 0:
            normatywna = cesar(line, -klucz) 
            if normatywna not in dic:
                dic[normatywna] = set()
            dic[normatywna].add(klucz)   

lnMax = 0
longestWords = []       
for i in dic:
    if len(dic[i]) > 1:
        if len(i) > lnMax:
            lnMax = len(i)
            longestWords = []
            longestWords += [i]
        elif len(i) == lnMax:
            longestWords += [i]

for word in longestWords:
    for key in dic[word]:
        print(cesar(word, key), end=" ")
    print()