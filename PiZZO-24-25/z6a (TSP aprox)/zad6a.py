# Wojciech Kieloch zad6a pizzo 24/25

import sys
import math

# Metoda:
# Znajdujemy MST grafu.
# Tworzymy cyklu złożony z wierzchołków w porządku preorder drzewa, gdzie ostatni wierzchołek łączy się z pierwszym (jest to ścieżka hamiltona).
# I. Ta ścieżka W, może nie pokrywać się z MST. Jeżeli jakaś krawędź (x, y) się nie pokrywa,
# to ma ona mniejszą wagę niż przejście z x do y w drzewie (wynika to z warunku trójkąta).
# Jako że ten cykl jest utworzony poprzez konstrukcję ścieżki eulera suma ścieżki równa się 2MST.
# Skracając drogę, wynika z I, że otrzymujemy w sumie cykl <= 2MST.
# Trywialnie MST <= TSP i TSP <= waga cyklu.
# zatem TSP <= waga cyklu <= 2TSP
# złożoność: O(n^2)

def findVertexWithMinEdge(vertexPresentArr, bestEdgeArr):
    tempMin = math.inf
    minVertex = 0
    for i in range(0, len(vertexPresentArr)):
        if vertexPresentArr[i] == False and bestEdgeArr[i] < tempMin:
            tempMin = bestEdgeArr[i]
            minVertex = i
    return minVertex

# prim's O(n^2)
def buildMST(graph):
    n = len(graph)
    vertexPresentArr = [False for _ in range(0, n)]
    bestEdgeArr = [math.inf for _ in range(0, n)]

    parents = [-1 for x in range(0, n)]

    bestEdgeArr[0] = 0

    for _ in range(0, n):
        currentVertexId = findVertexWithMinEdge(vertexPresentArr, bestEdgeArr)
        vertexPresentArr[currentVertexId] = True
        for vIter in range(0, n):
            if currentVertexId != vIter and vertexPresentArr[vIter] == False and bestEdgeArr[vIter] > graph[currentVertexId][vIter]:
                bestEdgeArr[vIter] = graph[currentVertexId][vIter]
                parents[vIter] = currentVertexId

    return parents

def buildTreeFromMSTdata(mst):
    tree = [[] for i in range(0, len(mst))]
    for vertexId in range(0, len(mst)):
        parent = mst[vertexId]
        if parent == -1:
            continue
        tree[parent].append(vertexId)
        tree[vertexId].append(parent)
    return tree

def preorderWalk(tree):
    visitedArr = [False for _ in range(0, len(tree))]
    walk = []
    def visit(vertexId):
        walk.append(vertexId)
        visitedArr[vertexId] = True
        for adjVertex in tree[vertexId]:
            if visitedArr[adjVertex] == False:
                visit(adjVertex)
    visit(0)
    return walk

def calcWalkWeight(graph, walk):
    if len(graph) == 1:
        return 0
    if len(graph) == 2:
        return 2*graph[0][1]
    sum = 0
    for i in range(1, len(walk)):
        prevVertex = walk[i-1]
        curVertex = walk[i]
        sum += graph[prevVertex][curVertex]
    fstVertex = walk[0]
    lstVertex = walk[-1]
    sum += graph[fstVertex][lstVertex]
    return sum

def aproxTSP(graph):
    mst = buildMST(graph)
    tree = buildTreeFromMSTdata(mst)
    walk = preorderWalk(tree)
    return calcWalkWeight(graph, walk)

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
    print(aproxTSP(graph))
    
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass