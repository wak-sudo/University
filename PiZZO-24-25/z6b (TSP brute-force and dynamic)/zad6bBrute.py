# Wojciech Kieloch zad6b pizzo 24/25

import sys
import math

def bruteForceTSP(graph):
    # Sprawdzanie permutacji.
    # Podejście rekurencyjne jest w praktyce szybsze niż użycie itertools.permutations.
    n = len(graph)
    if n == 1:
        return 0
    if n == 2:
        return 2*graph[0][1]
    visited = [False for _ in range(0, n)]
    vcount = 0
    bestSum = math.inf

    def visit(vertexId, locSum):
        nonlocal vcount, bestSum
        visited[vertexId] = True
        vcount += 1

        if vcount == n:
            bestSum = min(bestSum, locSum + graph[0][vertexId])
        else:
            for i in range(0, n):
                if visited[i] == False:
                    visit(i, locSum + graph[vertexId][i])    

        visited[vertexId] = False
        vcount -= 1

    visit(0, 0)
    return bestSum

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
    print(bruteForceTSP(graph))
   
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass