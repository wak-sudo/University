from itertools import product
products = product(['A', 'B', 'C'], repeat=2)
for i in products:
    print(i)
    input()