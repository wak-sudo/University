from turtle import *
import math

def rysujKolumne(n):
    dol = 5
    for i in range(2):
        t1.forward(dol)
        t1.left(90)
        t1.forward(n)
        t1.left(90)
    t1.forward(dol)

t1 = Turtle()
t1.speed(0)
t1.setposition(-350, 0)
negativeValue = False
n = 0
wynik = (math.sin(math.radians(n)) * 100) // 1
while wynik <= 0 or negativeValue != True:
    if wynik < 0:
        negativeValue = True
    rysujKolumne(wynik)
    n+=3
    wynik = (math.sin(math.radians(n)) * 100) // 1
input()