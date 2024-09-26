from duze_cyfry2 import *
from random import *
from turtle import *

def wypelniajMozaike():
    licznikProb = 0
    while(licznikProb != 1000):
        orgY = randint(0, rozmiarMozaiki-5)
        orgX = randint(0, rozmiarMozaiki-5)
        arrCyfra = daj_cyfre(randint(0,9))
        if(sprawdzCzyDaSieWpisac(arrCyfra, orgX, orgY)):
            wpisz(arrCyfra, orgX, orgY)
            licznikProb = 0
        else:
            licznikProb+=1
            

def sprawdzCzyDaSieWpisac(cyfra, x, y):
    for i in range(y, y+len(cyfra)):
        for j in range(x, x+len(cyfra)):
            if(mozaika[i][j] != " " and cyfra[i-y][j-x]!=" "):
                return False
    return True

def wpisz(cyfra, x, y):
    x *= rozmiarBoku
    y *= rozmiarBoku
    t1.goto(x, y+20)
    t1.fillcolor(choice(kolory))
    for i in range(5):
        tempX = x
        for j in range(5):
            if(cyfra[i][j]=="#"):
                rysujKwadrat()
                mozaika[y//rozmiarBoku][tempX//rozmiarBoku] = "#"
            if(cyfra[i][j]=="x"):
                mozaika[y//rozmiarBoku][tempX//rozmiarBoku] = "x"
            tempX += rozmiarBoku
            t1.goto(tempX, y+20)
        y += rozmiarBoku
        t1.goto(x, y+20)
                

def rysujKwadrat():
    t1.setheading(0)
    t1.pendown()
    t1.begin_fill()
    for i in range(4):
        t1.forward(rozmiarBoku)
        t1.right(90)
    t1.end_fill()
    t1.penup()

#kolory nie mogą się stykać

kolory = ["red", "yellow", "green", "blue", "purple", "lime", "pink", "cyan"]
rozmiarMozaiki = 25
rozmiarBoku = 14
mozaika = [[' ' for i in range(rozmiarMozaiki)] for i in range(rozmiarMozaiki)]
sc = Screen()
sc.setup(rozmiarMozaiki*rozmiarBoku+20, rozmiarMozaiki*rozmiarBoku+30)
sc.tracer(0,0)
sc.setworldcoordinates(0, sc.window_height(), sc.window_width(), 0)
t1 = Turtle()
t1.speed(0)
t1.penup()
wypelniajMozaike()
sc.update()
print("Done")
input()
