from random import choice
pol_ang = {}

def loadFullDic(engDicFrec):
    for x in open('brown.txt', encoding='utf8'):
        words = x.split()
        for word in words:
            if word in engDicFrec:
                engDicFrec[word] += 1
            else:
                engDicFrec[word] = 1

    for x in open('pol_ang.txt', encoding='utf8'):
        x = x.strip()
        L = x.split('=')
        if len(L) != 2:
            continue
        if L[1] not in engDicFrec:
            engDicFrec[L[1]] = 0 

def createNewDic():
    engDicFrec = {}
    loadFullDic(engDicFrec)
    for x in open('pol_ang.txt', encoding='utf8'):
        x = x.strip()
        L = x.split('=')
        if len(L) != 2:
            continue
        pol, ang = L
        if pol in pol_ang:
            if engDicFrec[ang] > engDicFrec[list(pol_ang[pol])[0]]:
                pol_ang[pol] = [ang]
            elif engDicFrec[ang] == engDicFrec[list(pol_ang[pol])[0]]:
                pol_ang[pol] += [ang]
        else:
            pol_ang[pol] = [ang]

def tlumacz(polskie):
    wynik = []
    for p in polskie:
        if p in pol_ang:
            wynik.append(choice(pol_ang[p]))
        else:
            wynik.append('[*]')
    return ' '.join(wynik)        
    
zdanie = 'chłopiec z dziewczyna pójść do kino'.split()

createNewDic()
print (tlumacz(zdanie)) 