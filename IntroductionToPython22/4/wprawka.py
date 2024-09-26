import math

def print2DArr(arr):
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            print(arr[i][j], end='')
        print()

def kwadkonc(rozmiar, napis):
    if(rozmiar > 1):
        tablica = [[' ' for i in range(rozmiar)] for j in range(rozmiar)]
        indeksZnaku = -1
        for i in range(math.ceil(rozmiar/2)):
            indeksZnaku = (indeksZnaku + 1)%2
            for p in range(i, rozmiar-i):
                tablica[rozmiar-i-1][p] = tablica[p][i] = tablica[p][rozmiar-i-1] = tablica[i][p] = napis[indeksZnaku]
        print2DArr(tablica)
    elif rozmiar == 1:
        print(napis[0])

#n = int(input("Podaj rozmiar:"))
#s = input("Podaj napis:")
for n in [0,1,2,3,5,8]:
 print("----")
 kwadkonc(n,"#-")