def toDic(s):
    lettersDic = {}
    for c in s:
        if c in lettersDic:
            lettersDic[c] += 1
        else:
            lettersDic[c] = 1
    return lettersDic

def czyJestUkladalne(s1, s2):
    if len(s1) > len(s2):
        return False
    s1Dic = toDic(s1)
    s2Dic = toDic(s2)
    for c in s1Dic:
        if c not in s2Dic or s1Dic[c] > s2Dic[c]:
            return False
    return True

s1 = input('Pierwsze:')
s2 = input('Drugie:')
print(czyJestUkladalne(s1, s2))