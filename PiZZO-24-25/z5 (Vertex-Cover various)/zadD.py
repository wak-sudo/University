# Pizzo 2024/25, zadanie 5, część D, Wojciech Kieloch

import sys
import itertools
import json

def isVertexCover(graph, selVerticesVector):
    for vertexId in range(0, len(graph)):
        if selVerticesVector[vertexId] == False: # if the vertice is not selected 
            for adjVertexId in graph[vertexId]:
                if selVerticesVector[adjVertexId] == False:
                    return False
    return True

def checkPermutations(graph, kVertices):
    selVerticesVector = [False for _ in range(0, len(graph))]
    if(kVertices > len(graph)): 
        kVertices = len(graph)
    for veritcesSubset in itertools.combinations(range(len(graph)), kVertices):
        for vertexId in veritcesSubset:
            selVerticesVector[vertexId] = True
        if isVertexCover(graph, selVerticesVector):
            return True
        for vertexId in veritcesSubset:
            selVerticesVector[vertexId] = False
    return False

def vertexCoverExists(graph, kVertices):
    return checkPermutations(graph, kVertices)

def main(argv : list[str]):
    if len(argv) < 3:
        print("Provide file path of the graph and then k.")
    filename = argv[1]
    kVertices = int(argv[2])
    with open(filename) as fd:
        graph = json.load(fd)
    print(vertexCoverExists(graph, kVertices))

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass