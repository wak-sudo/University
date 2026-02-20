# Pizzo 2024/25, zadanie 5, część F, Wojciech Kieloch

from z3 import *
import json

def vertexCoverExistsSMT(graph, kVertices):
    edges = set()
    for vertexId in range(0, len(graph)):
        for adjVerticeId in graph[vertexId]:
            if (vertexId, adjVerticeId) in edges or (adjVerticeId, vertexId) in edges:
               continue
            edges.add((vertexId, adjVerticeId))

    z3Vertices = [Bool("v" + str(x)) for x in range(0, len(graph))]

    s = Solver()

    for edge in edges:
        leftV = Bool("v" + str(edge[0]))
        rightV = Bool("v" + str(edge[1]))
        s.add(Or(leftV, rightV))

    s.add(AtMost(*z3Vertices, kVertices))

    if str(s.check()) != "unsat":
        return True
    return False

def main(argv : list[str]):
    if len(argv) < 3:
        print("Provide file path of the graph and then k.")
    filename = argv[1]
    kVertices = int(argv[2])
    with open(filename) as fd:
        graph = json.load(fd)
    print(vertexCoverExistsSMT(graph, kVertices))

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass

