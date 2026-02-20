from turtle import *

def rysujKwadrat():
    t1.begin_fill()
    t1.pendown()
    for i in range(4):
        t1.forward(bok)
        t1.right(90)
    t1.end_fill()
    t1.penup()

t1 = Turtle()
sc = Screen()
t1.speed(0)
sc.tracer(0,1)
sc.colormode(255)
sc.setworldcoordinates(0, sc.window_height(), sc.window_width(), 0)
t1.goto(0,0)
t1.penup()
bok = 10
mapa = []
for line in open("niespodzianka.txt"):
    subMap = [eval(rgb) for rgb in line.split()]
    mapa += [subMap]

t3 = (1, 2, 3)
for y in range(len(mapa)):
    for x in range(len(mapa[y])):
        t1.goto(x*bok, y*bok)
        t1.fillcolor(mapa[y][x])
        rysujKwadrat()
input()