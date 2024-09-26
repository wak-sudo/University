matches = []
allSubs = []

def generujPermutacje(arr, matchIndex, state):
    if len(arr) == len(matches):
        allSubs.append(arr)
        return
    arr.append([matches[matchIndex], state])
    generujPermutacje(arr, matchIndex+1, 'p')
    matchIndex-=1
    arr.pop()
    generujPermutacje(arr, matchIndex+1, 'w')
    matchIndex-=1
    arr.pop()
    generujPermutacje(arr, matchIndex+1, 'r')
    matchIndex-=1
    arr.pop()


def generateAllMatches(n):
    for i in range(1, 2*n+1):
        for j in range(i+1, 2*n+1):
            matches.append([i,j])

n = 3
generateAllMatches(n)
generujPermutacje([], 0, 'p')
generujPermutacje([], 0, 'w')
generujPermutacje([], 0, 'r')
input()