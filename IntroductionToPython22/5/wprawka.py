from turtle import *
from random import *

def rysujBuzie(rozmiar, rodzaj="happy", wielk=0, los=0):
    if 2*wielk + 5/3*rozmiar -10 >= 2.5*rozmiar:
        return False
    if(los > 0):
        losowanie = los % 4
        if(losowanie == 1):
            rodzaj="happy"
        elif(losowanie == 2):
            rodzaj = "sad"
        elif(losowanie == 3):
            rodzaj = "numb"
        rozmiar += ((los + 100) % 300)
        wielk += (los + 10) % 10
    #nos
    t1.right(90)
    t1.forward(rozmiar)
    t1.right(90)
    t1.forward(rozmiar/2)
    t1.setpos(0,0)

    #oczy
    t1.right(90)
    t1.penup()
    t1.forward(rozmiar/3)
    t1.left(90)
    t1.forward(rozmiar/3)
    t1.pendown()
    t1.forward(rozmiar/2 + wielk)

    t1.right(180)
    t1.penup()
    t1.forward(7*rozmiar/6)
    t1.pendown()
    t1.forward(rozmiar/2 +  wielk)

    t1.penup()
    t1.goto(0,0)
    t1.right(90)
    t1.forward(rozmiar)
    t1.forward(rozmiar/2)
    t1.right(90)
    t1.forward(rozmiar)
    t1.pendown()
    t1.right(180)
    # usta
    if rodzaj=="sad":
        t1.penup()
        t1.forward(rozmiar + 3/4*rozmiar)
        t1.right(90)
        t1.forward(2/10*rozmiar)
        t1.setheading(-60)
        t1.pendown()
        t1.circle(-rozmiar, -120)
    elif rodzaj=="numb":
        t1.forward(2*rozmiar)
    else: #happy
        t1.seth(-60)
        t1.circle(rozmiar, 120)

    t1.penup()
    t1.seth(0)
    t1.setpos(0,0)
    t1.forward(7*rozmiar/6)
    t1.pendown()
    t1.right(-90)
    t1.forward(2/3*rozmiar)
    t1.left(90)
    t1.forward(2*rozmiar + 1/2*rozmiar)
    t1.left(90)
    t1.forward(3*rozmiar)
    t1.right(-90)
    t1.forward(2*rozmiar + 1/2*rozmiar)
    t1.seth(90)
    t1.forward(3*rozmiar)
    return True
    

t1 = Turtle()
t1.speed(0)
if rysujBuzie(80, "numb", 30, 0) == False:
    print("Nie da sie stowrzyc obrazka")
input()
