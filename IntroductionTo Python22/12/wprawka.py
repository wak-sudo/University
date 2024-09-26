def justify(words, L=72):
    wynik = []
    index = 0
    while index < len(words):
        count = len(words[index])
        last = index + 1
        while last < len(words): # liczymy listę znaków, aż nie dojdziemy do końca lub nie przekroczymy rozmiaru.
            if len(words[last]) + count + 1 > L: break
            count += len(words[last]) + 1
            last += 1

        line = ""
        wordsNumber = last - index - 1 # liczba separacji

        # jeżeli to ostantnie słowo w ogóle, lub jedyne słowo mieszczące się w lini
        if last == len(words) or wordsNumber == 0:
            for i in range(index, last):
                line += words[i] + ' '
            line = line[0:-1]
            for i in range(len(line), L):
                line += ' '
        else:
            spaces = ((L - count) // wordsNumber)
            remainder = (L - count) % wordsNumber

            for i in range(index, last):
                line += words[i]
                if (i < last - 1):
                    limit = spaces + (1 if (i-index) < remainder else 0)
                    line += ' '*(limit+1)
        wynik.append(line)
        index = last
    return wynik

def printArr(arr):
    if arr != None:
        for i in arr:
            print(i)

zdanie = "Najgorsze co się da w moim mniemaniu i także dalej."
printArr(justify(zdanie.split(), 13))
