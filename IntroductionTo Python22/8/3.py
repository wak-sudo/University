# popraw
slowa = []
counter = 0
for line in open("popularne_slowa.txt", encoding='utf8'):
    #if counter % 100 == 0: # bierz co 100 słowo, 3 miliony wyrazów to za dużo
    slowa += [line.strip().lower()]
    #counter +=1
slowa.sort(key=len)

def toDic(s):
    dic = {}
    for c in s:
        if c in dic:
            dic[c] += 1
        else:
            dic[c] = 1
    return dic

def znajdzPermutacje(imie : str):
    imie = imie.strip().replace(' ', '').lower()
    dicImie = toDic(imie)
    wynik = []
    for i in range(0, len(slowa)):
        if len(slowa[i]) >= len(imie):
            break
        for j in range(i+1, len(slowa)):
            dlugoscCiagu = len(slowa[i]) + len(slowa[j])
            if dlugoscCiagu > len(imie):
                break
            if dlugoscCiagu == len(imie) and toDic(slowa[i] + slowa[j]) == dicImie:
                tup = (slowa[i], slowa[j]) 
                wynik += tup
    return wynik
            
wynik = znajdzPermutacje("Bolesław Prus")
for tuple in wynik:
    print(tuple)
print("Done")