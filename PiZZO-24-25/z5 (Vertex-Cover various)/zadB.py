# Pizzo 2024/25, zadanie 5, część B, Wojciech Kieloch

import sys
import json

def vertexWithHighestDegree(vertexDegrees):
    resId = -1
    resVal = -1
    for i in range(0, len(vertexDegrees)):
        if vertexDegrees[i] > resVal:
            resVal = vertexDegrees[i]
            resId = i
    return resId

def aproxVertexCover(graph):
    # format: vertex -> adj vertices
    vertexDegree = [0 for _ in range(0, len(graph))]
    for vertexId in range(0, len(graph)):
        adjVerticesCount = len(graph[vertexId])
        vertexDegree[vertexId] = adjVerticesCount
    
    res = 0
    sumOfDegrees = sum(vertexDegree)
    while sumOfDegrees != 0:
        crVertexId = vertexWithHighestDegree(vertexDegree)
        res += 1
        for adjVerticeID in graph[crVertexId]:
            if vertexDegree[adjVerticeID] > 0:
                vertexDegree[adjVerticeID] -= 1
        sumOfDegrees -= 2*vertexDegree[crVertexId]
        vertexDegree[crVertexId] = 0
    return res

def main(argv : list[str]):
    if len(argv) < 2:
        print("Provide file path of the graph.")
    filename = argv[1]
    with open(filename) as fd:
        graph = json.load(fd)
    print(aproxVertexCover(graph))

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass