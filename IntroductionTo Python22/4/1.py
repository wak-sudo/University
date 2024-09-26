from turtle import *
import random

def square(n):
    f1.fillcolor(230, green, 255-green)
    f1.begin_fill()
    for i in range(4):
        f1.forward(n)
        f1.right(90)
    f1.end_fill()

f1 = Turtle()
f1.speed(0)
f1.screen.colormode(255)
green = 255
kroki = 30 
for i in range(1, 19):
    for j in range(i): # i
        square(kroki)
        f1.forward(kroki)
        green -= 1
    f1.penup()
    f1.forward(kroki)
    f1.right(90)
    f1.pendown()

input()