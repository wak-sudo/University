def Collatz(n):
    counter = 0
    while n != 1:
        if n % 2 == 0:
            n //= 2
        else:
            n = 3*n+1
        counter+=1
    return counter

def analiza_collatza(a,b):    
    results = []
    for i in range(a, b+1):
        results.append(Collatz(i))
    midpoint = len(results) // 2
    results.sort()
    print("Średnia: " + str(sum(results) / len(results)))
    print("Mediana: " + str(results[midpoint] + results[midpoint + 1]) if len(results) % 2 == 0 else str(results[midpoint]))
    print("Min: " + str(min(results)))
    print("Max: " + str(max(results)))

analiza_collatza(1, 10)