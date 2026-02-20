# Wojciech Kieloch zad6b pizzo 24/25

import math
import itertools
import sys

def getSubsetId(subset):
    id = 0
    for i in range(0, len(subset)):
        if subset[i] == 1:
            id |= (1 << i) 
    return id

def allocMatrix(n):
    upperBound = pow(2,n)
    sndRowTemp = [0 for _ in range(0, n)]
    return [sndRowTemp.copy() for _ in range(0, upperBound)]

# Held–Karp algorithm
def hpAlgo(graph):
    n = len(graph)
    if n == 1:
        return 0
    if n == 2:
        return 2*graph[0][1]
    upperBound = pow(2,n-1)
    dymFun = allocMatrix(n-1)

    subsetIdx = 1
    vertexIdx = 1
    while subsetIdx < upperBound:
        dymFun[subsetIdx][vertexIdx-1] = graph[0][vertexIdx]
        subsetIdx *= 2
        vertexIdx += 1

    someVertices = [x for x in range(1, n)]
    choosenVertices = [0 for _ in range(0, n-1)]
    for k in range(2, n):
        for subset in itertools.combinations(someVertices, k):
            for key in subset:
                choosenVertices[key-1] = 1
            
            subsetId = getSubsetId(choosenVertices)
            for vertex in subset:
                tempMin = math.inf
                for otherVertice in subset:
                    if otherVertice != vertex:
                        tempIdSubset = subsetId & ~(1 << (vertex - 1))
                        candidate = dymFun[tempIdSubset][otherVertice-1] + graph[otherVertice][vertex]
                        tempMin = min(tempMin, candidate)             
                dymFun[subsetId][vertex-1] = tempMin
            
            for key in subset:
                choosenVertices[key-1] = 0
    
    opt = math.inf
    subsetId = upperBound-1
    for vertex in range(1, n):
        candidate = dymFun[subsetId][vertex-1] + graph[vertex][0]
        opt = min(candidate, opt)
    return  opt

def loadGraph():
    n = int(input())
    row = [0 for _ in range(0, n)]
    matrix =[row.copy() for _ in range(0, n)]
    j = 0
    for line in sys.stdin:
        i = 0
        for var in line.split():
            matrix[i][j] = int(var)
            i += 1
        j += 1
        if j == n:
            break
    return matrix

def main():
    graph = loadGraph()
    print(hpAlgo(graph))
   
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass