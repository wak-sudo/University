from math import *

def isPrimeL(n):
    if(n<2):
        return False
    i = 2    
    while i*i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

def isPerfectL(n):
    wynik = n
    dzielnik = n//2
    while dzielnik != 0:
        if n % dzielnik == 0:
            wynik -= dzielnik
        dzielnik-=1

    if wynik == 0:
        return True
    return False

def NWD(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def totientL(n):
    wynik = 0
    for i in range(1, n):
        if NWD(i, n) == 1:
            wynik+=1
    return wynik

def cathetiL(c):
    wynik = []
    for i in range(1, c):
        a = float(sqrt(c**2 - i**2))
        if a.is_integer() and a not in wynik:
            wynik += (a, i)
    return wynik

def isPrime(n):
    return 0 not in [n%i for i in range(2, ceil(sqrt(n)))] if n>2 else False

def isPerfect(n):
    return n == sum([dzielnik for dzielnik in range(1, n//2) if n%dzielnik == 0])

def totient(n):
    return sum([1 for i in range(1,n) if NWD(i,n) == 1])

def catheti(c):
    return [ i for i in range(1,int(c / (2**0.5))) if (sqrt(c**2 - i**2)).is_integer()]

print(catheti(25))
