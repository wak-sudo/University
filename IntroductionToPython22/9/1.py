from turtle import *

def rysujKwadrat(x, y, bok):
    t1.goto(x,y)
    t1.forward(bok/2)
    t1.right(90)
    t1.pendown()
    t1.begin_fill()
    t1.forward(bok/2)
    for i in range(4):
        t1.right(90)
        t1.forward(bok)
    t1.end_fill()
    t1.penup()

def Sierpinski(x, y, bok, deep):
    rysujKwadrat(x, y, bok)
    deep -= 1
    if(deep > 0):
        Sierpinski(x+bok, y, bok/3, deep)
        Sierpinski(x-bok, y, bok/3, deep)
        Sierpinski(x, y+bok, bok/3, deep)
        Sierpinski(x, y-bok, bok/3, deep)
        Sierpinski(x+bok, y+bok, bok/3, deep)
        Sierpinski(x-bok, y-bok, bok/3, deep)
        Sierpinski(x+bok, y-bok, bok/3, deep)
        Sierpinski(x-bok, y+bok, bok/3, deep)

t1 = Turtle()
t1.color("white")
sc = Screen()
sc.tracer(0,0)
sc.bgcolor("black")
#t1.speed(0)
Sierpinski(0, 0, 100, 4)
input()

