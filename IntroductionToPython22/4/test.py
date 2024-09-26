def PrintArr(L):
    for i in range(len(L)):
        print(L[i], end=' ')
    print()

def Chagne(L):
    for i in range(len(L)):
        L[i] += 1

L = [1, 2, 3, 4]
Chagne(L)
PrintArr(L)