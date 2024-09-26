from turtle import *

listaBraila = [
    ["* ", #A/1
     "  "],

    ["* ", #B/2
     "* "],

    ["**", #C/3
     "  "],

    ["**", #D/4
     " *"],
    
    ["* ", #E/5
     " *"],

    ["**", #F/6
     "* "],

    ["**", #G/7
     "**"],

    ["* ", #H/8
     "**"],

    [" *", #I/9
     "* "],

    [" *", #J/0
     "**"],
]

def GetBrailChar(symbol):
    symbol = symbol.lower()
    symbolValue = ord(symbol)
    if symbolValue >= ord('a') and symbolValue <= ord('j'):
        return (listaBraila[symbolValue - ord('a')] + ["  "])
    elif symbolValue >= ord('0') and symbolValue <= ord('9'):
        return listaBraila[symbolValue - ord('0')-1] + ["  "]
    elif symbolValue >= ord('k') and symbolValue <= ord('t'):
        return (listaBraila[symbolValue - ord('a') - 10] + ["* "])
    elif symbolValue == ord('w'):
        return (listaBraila[9] + [" *"])
    elif symbolValue >= ord('u') and symbolValue <= ord('z'):
        return (listaBraila[symbolValue- ord('a') - 20] + ["**"])
    else:
        return ["  ", "  ", "  "]

def rysujTablice2D(arr):
    t1.penup()
    t1.fillcolor("black")
    for i in range(len(arr)):  
        for j in range(len(arr[i])):
            t1.pendown()
            if arr[i][j] == '*':       
                drawCircle(rozmiar/2)  
            else:
                drawCircle(rozmiar/2, False)
            t1.penup()
            t1.forward(rozmiar)
        if i == len(arr) - 1: # do nowej kolumny
            t1.forward(rozmiar)
            t1.left(90)
            t1.forward(len(arr[i]) * rozmiar)
            t1.right(90)
        else:
            t1.forward(len(arr[i]) * -rozmiar) # działanie jak enter
            t1.right(90)
            t1.forward(rozmiar)
            t1.right(-90)

def drawCircle(n, fill = True):
    if fill:
        t1.begin_fill()
        t1.circle(-n)
        t1.end_fill()
    else:
        t1.circle(-n)

napis = input("Podaj napis: ")
rozmiar = 20
t1 = Turtle()
sc = Screen()
sc.tracer(0, 0)
t1.penup()
t1.speed(0)
t1.seth(0)
t1.setpos(-sc.window_width()/2 + rozmiar, 0)
for c in napis:
    rysujTablice2D(GetBrailChar(c))
sc.update()
input()