from turtle import *
from random import *

x = 50
y = x
bok = 10
mapa_malowan = [[0 for i in range(x)] for j in range(y)]

def rysujKwadrat():
    t1.begin_fill()
    t1.pendown()
    for i in range(4):
        t1.forward(bok)
        t1.right(90)
    t1.end_fill()
    t1.penup()

def canBeDrawn(x, y):
    if x>=0 and y>=0 and x<len(mapa_malowan[0]) and y<len(mapa_malowan):
        return True
    return False

t1 = Turtle()
screensize(x*bok, y*bok)
sc = Screen()
t1.speed(0)
sc.tracer(0,1)
sc.colormode(255)
sc.setworldcoordinates(0, sc.window_height(), sc.window_width(), 0)
t1.goto(0,0)
t1.penup()

def sprawdzCzySaCzerowne(x, y):
    if(can)

while True:
    rand_x = randint(0, 50)
    rand_y = randint(0, 50)
    if canBeDrawn(rand_x, rand_y):
        break
#1 - black
#2 - red
probablilty = 0,3
czarne_mozliwosci = [(rand_x, rand_y)]
czerw_mozliwosci = [(rand_x, rand_y)] 
while len(czarne_mozliwosci) != 0 or len(czerw_mozliwosci) != 0:
    randColor = random.choice(["black", "red"], p=[1-probablilty, probablilty])
    if randColor == "red":
        cord = choice(czerw_mozliwosci)
        if 
    cord = choice(mozliwosci)
    x = cord[0]
    y = cord[1]
    t1.goto(x*bok, y*bok)
    t1.fillcolor('black')
    rysujKwadrat()
    update()
    if(canBeDrawn(x+1, y) and (not mapa_malowan[y][x+1])):
        mozliwosci += [(x+1, y)]
    if(canBeDrawn(x, y+1) and (not mapa_malowan[y+1][x])):
        mozliwosci += [(x, y+1)]
    if(canBeDrawn(x, y-1) and (not mapa_malowan[y-1][x])):
        mozliwosci += [(x, y-1)]
    if(canBeDrawn(x-1, y) and (not mapa_malowan[y][x-1])):
        mozliwosci += [(x-1, y)]
    mapa_malowan[cord[1]][cord[0]] = True
    mozliwosci.remove(cord)
    
input()