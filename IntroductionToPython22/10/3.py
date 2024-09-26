from itertools import product

def lami(s : str):
    slowa = s.lower().split(' ')
    znaki = set()
    for i in (range(0, 5, 2)):
        for c in slowa[i]:
            znaki.add(c)
    znaki = sorted(list(znaki))          
    products = product(range(0, 10), repeat=len(znaki))
    for i in products:
        if len(set(i)) == len(i):
            odpowiedniki = dict(zip(znaki, i))
            liczby = ['' for i in range(3)]

            for c in slowa[0]:
                liczby[0] += str(odpowiedniki[c])
            a_int = int(liczby[0])
            if len(str(a_int)) != len(liczby[0]):
                continue

            for c in slowa[2]:
                liczby[1] += str(odpowiedniki[c])
            b_int = int(liczby[1])
            if len(str(b_int)) != len(liczby[1]):
                continue

            for c in slowa[4]:
                liczby[2] += str(odpowiedniki[c])
            c_int = int(liczby[2])
            if len(str(c_int)) != len(liczby[2]):
                continue

            if b_int == 1085:
                pass
            if a_int + b_int == c_int:
                return odpowiedniki

    input()
    return None

print(lami("send + more = money"))