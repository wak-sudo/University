from duze_cyfry import daj_cyfre

wejscie = ''
while(wejscie.isdigit() != True):
    wejscie = input("Podaj liczbę: ")
cyfry = []
for i in range(len(wejscie)):
    cyfry.append(daj_cyfre(int(wejscie[i])))

for i in range(len(cyfry[0])):
    for j in range(len(cyfry)):
        print(cyfry[j][i], end=' ')
    print()