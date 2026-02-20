def krzyzyk(n):
    czesc = n * " " + n * "*" + n * " "
    for i in range(n):
        print(czesc)
    for i in range(n):
        print(n*3 * "*")
    for i in range(n):
        print(czesc)

krzyzyk(4)