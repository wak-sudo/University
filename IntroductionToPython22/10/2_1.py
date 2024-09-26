def clearWord(s):
    wynik = []
    polAlfBig = polAlf.upper()
    for c in s:
        if c in polAlfBig or c in polAlf:
            wynik += c
    return ''.join(wynik)

wyniki = []
print("Generowanie słownika.")
for line in open("popularne_slowa2.txt", encoding="utf8"):
    line = clearWord(line).strip()
    if len(line) in dic:
        dic[len(line)] += [line]
    else: 
        dic[len(line)] = [line]