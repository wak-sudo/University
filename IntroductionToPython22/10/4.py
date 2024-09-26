# a
def powerSetSums(L):
    if len(L) == 0: return {0}
    subSet = powerSetSums(L[1:])
    return {L[0]} | subSet | set(i+L[0] for i in subSet)

print(sorted(list(powerSetSums([1,2,3,100]))))

# b
def genCiagi(a, b, n):
    ciagi(a, b, n, a)

def ciagi(A, B, n, start, L=[]):
    if(len(L) == n):
        print(L)
        return
    for j in range(start, B+1):  
        ciagi(A, B, n, j, L + [j])      
a=1
b=3
n=4
genCiagi(a,b,n)

    