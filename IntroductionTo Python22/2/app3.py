def kolko(n, offset=0):
    promien = (n-1)/2
    for i in range(n):
        linia = ''
        y = (i - promien)**2
        for j in range(n):
            x  = (j - promien)**2
            if(x + y <= (promien+0.5)**2):
                linia += '#'
            else:
                linia += ' '
        print(offset*' '+linia)

def balwan(): # tydzien
    rozKol1 = 7
    rozKol2 = 9
    rozKol3 = 11

    offset1 = int((rozKol3 - rozKol1) / 2)
    offset2 = int((rozKol3 - rozKol2) / 2)

    kolko(rozKol1, offset1)
    kolko(rozKol2, offset2)
    kolko(rozKol3)

balwan()