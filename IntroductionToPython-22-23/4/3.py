import random

def randperm(n):
    liczby = list(range(n))
    wynik = []
    while len(liczby) > 0:
        n = len(liczby)
        index = random.randint(0, n - 1)
        wynik += [liczby[index]]
        liczby[index], liczby[n-1] = liczby[n-1], liczby[index]
        liczby.pop()
    return wynik     

for i in range(1):
    print(randperm(100))
print("Done.")
