def kwadrat(n, ch):
    for i in range(n):
       print (n * ch)

for i in range(10):
    print ("Przebieg:",i)
    print (20 * "-")
    if i < 5:
        kwadrat(3+2*i, "*")
    else:
        kwadrat(-2+i, "#")
    print()