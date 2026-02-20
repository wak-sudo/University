from turtle import *
from duze_cyfry import daj_cyfre
from random import randint

def losujKolor():
    r = randint(0, 255)
    g = randint(0, 255)
    b = randint(0, 255)
    return [r,g,b]

def rysujKwadrat(n):
    t1.begin_fill()
    for i in range(4):
        t1.forward(n)
        t1.right(90)
    t1.end_fill()

def rysujTablice2D(arr, bok):
    t1.penup()
    t1.fillcolor(losujKolor())
    for i in range(len(arr)):  
        for j in range(len(arr[i])):
            if(arr[i][j] == '#'):
                t1.pendown()
                rysujKwadrat(bok)
                t1.penup()
            t1.forward(bok)
        if(i == len(arr) - 1): # do nowej kolumny
            t1.forward(bok)
            t1.left(90)
            t1.forward((len(arr[i])-1) * bok)
            t1.right(90)
        else:
            t1.forward((len(arr[i])) * -bok) # działanie jak enter
            t1.right(90)
            t1.forward(bok)
            t1.right(-90)

def rysujLiczbe(n, rozmiar):
    n = str(n)
    for c in n:
        rysujTablice2D(daj_cyfre(int(c)), rozmiar)
    
t1 = Turtle()
t1.speed(0)
t1.screen.colormode(255)
t1.penup()
t1.setposition(-300, 0)
rysujLiczbe(123456, 10)