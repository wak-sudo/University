# Pizzo 2024/25, zadanie 5, Wojciech Kieloch

import random
import sys
import json

def genGraph(veritcesCount):
    graph = [[] for _ in range(0, veritcesCount)] # vertice -> adj vertices
    for x in range(0, veritcesCount):
        for y in range(x+1, veritcesCount):
            if random.randint(0, 1): # 50% chance to be added
                graph[x].append(y)
                graph[y].append(x)
    return graph

'''
def isConnected(graph):
    visited = [False for _ in range(0, len(graph))]
    toVisit = [0]
    while len(toVisit) != 0:
        currentVertex = toVisit.pop(-1) # pop last
        for adjVertex in graph[currentVertex]:
            if visited[adjVertex] == False:
                toVisit.append(adjVertex)
        visited[currentVertex]= True
    return all(visited)


def genConnectedGraph(verticesCount):
    while True: # expected number of iterations: 2, Las Vegas algorithm
        currentGraph = genGraph(verticesCount)
        if isConnected(currentGraph):
            return currentGraph

'''
        
def main(argv : list[str]):
    if len(argv) != 2:
        print("Provide number of vertices.")
    else:
        verticesCount = int(argv[1])
        graphJSON = json.dumps(genGraph(verticesCount))
        print(graphJSON)

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass