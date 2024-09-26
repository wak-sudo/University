from random import randint, choice
from turtle import *

rozmiarHistogramu = 100
hipsometr = [[0 for i in range(rozmiarHistogramu+1)] for j in range(rozmiarHistogramu+1)]

najwiekszaWys = 0
przedzialy = []
najmniejszaWys = 0

bokKwad = 5

kolory = ['green', (0.5, 1, 0) , 'yellow', 'orange', 'red', (0.5, 0,0) ]

# sprawdzaj czy g

korY = [j for j in range(len(hipsometr))]
korX = [[i for i in range(len(hipsometr[0]))] for j in range(len(hipsometr))]
def losujUnikalneKord():
    y = choice(korY)
    x = choice(korX[y])
    korX[y].remove(x)
    if len(korX[y]) == 0:
        korY.remove(y)
    return (y, x)

def generujWzgorza():
    global najwiekszaWys
    for i in range(5):
        x = randint(0, rozmiarHistogramu)
        y = randint(0, rozmiarHistogramu)
        wysokosc = randint(10, 100)
        hipsometr[y][x] = wysokosc
        najwiekszaWys = max(najwiekszaWys, wysokosc)

def komorkaIstnieje(y, x):
    if y >= 0 and y <= rozmiarHistogramu and x>=0 and x<=rozmiarHistogramu:
        return True
    return False

def zmieniajWys():
    global najmniejszaWys
    for i in range(rozmiarHistogramu**2):
        kordTuple = losujUnikalneKord()
        y = kordTuple[0]
        x = kordTuple[1]
        suma = 0
        counterSasiadow = 0
        for i in range(-1, 2):
            if komorkaIstnieje(x+i, y-1):
                suma += hipsometr[y-1][x+i]
                counterSasiadow += 1
            if komorkaIstnieje(x+i, y+1):
                suma += hipsometr[y+1][x+i]
                counterSasiadow += 1
        if komorkaIstnieje(x-1, y):
            suma += hipsometr[y][x-1]
            counterSasiadow += 1
        if komorkaIstnieje(x+1, y):
            suma += hipsometr[y][x+1]
            counterSasiadow += 1
        hipsometr[y][x] = suma+hipsometr[y][x] / counterSasiadow
        najmniejszaWys = min(najmniejszaWys, hipsometr[y][x])

def definiujPrzedzialy(liczbaPrzedzialow):
    global przedzialy
    przedzialy = [najmniejszaWys]
    l = najmniejszaWys
    p = najwiekszaWys
    for i in range(liczbaPrzedzialow-1):
        srodek = (l + p)/2
        przedzialy += [srodek]
        l = srodek

def wKtorymPrzedziale(x):
    if x >= przedzialy[len(przedzialy)-1]:
        return len(przedzialy)-1
    for i in range(len(przedzialy)-1):
        if x >= przedzialy[i] and x<przedzialy[i+1]:
            return i

def rysujKwadrat():
    t1.pendown()
    t1.begin_fill()
    for i in range(4):
        t1.forward(bokKwad)
        t1.right(90)
    t1.end_fill()   
    t1.penup()

def rysujHipsometr():
    for i in range(rozmiarHistogramu+1):
        for j in range(rozmiarHistogramu+1):
            t1.goto(j*bokKwad, i*bokKwad)
            wysokosc = hipsometr[i][j]
            if wysokosc > 10:
                pass
            t1.fillcolor(kolory[wKtorymPrzedziale(wysokosc)])
            rysujKwadrat()

def generujHips():
    print("Generowanie wzgórz.")
    generujWzgorza()
    print("Generowanie mapy.")
    zmieniajWys()
    print("Generowanie przedziałów.") 
    definiujPrzedzialy(len(kolory))     

t1 = Turtle()
sc = Screen()
sc.setworldcoordinates(0, window_height(), window_width(), 0)
sc.tracer(0,0)
t1.speed(0)
generujHips()
rysujHipsometr()
input("Done")