def sortuj(L):
    return ([i for i in L if i == '0'] + [i for i in L if i == '1'])

print(sortuj("10101"))