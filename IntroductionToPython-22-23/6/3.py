def zwrocDzielniki(n):
    rozklad = set()
    dzielnik = 2
    while n != 1:
        if n % dzielnik == 0:
            rozklad.add(dzielnik)
            n/=dzielnik
        else:
            dzielnik+=1
    return rozklad

print(zwrocDzielniki(100))