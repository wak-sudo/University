from turtle import *

def kwadrat(n):
    t1.forward(n)
    t1.forward(-n)
    t1.left(90)
    t1.forward(n)
    t1.right(90)
    t1.forward(n)
    t1.right(90)
    t1.forward(n)
    t1.left(90)

t1 = Turtle()
t1.speed(0)
t1.right(-90)
baseSquare = 10
for i in range(20):
    t1.penup()
    t1.setposition(0, 0)
    t1.forward(15)
    t1.pendown()
    for j in range(5):
        kwadrat(baseSquare + 5*j)
    t1.right(18)
t1.hideturtle()
input()