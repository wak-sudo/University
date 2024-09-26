def Koperta(n):
    size = 2*n+1
    print(size*'#')
    for i in range(size-2):
        for j in range(size):
            if j == 0 or j == size-1 or j == i+1 or i+1+j == size - 1:
                print('#', end='')
            else:
                print(' ', end='')      
        print()
    print(size*'#')

Koperta(6)
