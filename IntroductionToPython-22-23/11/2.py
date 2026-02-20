counter = 1

litery ={}

napis = input("Podaj napis:")
nowyNapis = ""

for c in napis:
    if c in litery:
        nowyNapis += (str(litery[c]) + '-')
    else:
        litery[c] = counter
        nowyNapis += (str(counter) + '-')
        counter+=1

nowyNapis = nowyNapis[:-1]
print(nowyNapis)

