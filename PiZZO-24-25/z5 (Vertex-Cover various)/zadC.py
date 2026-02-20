# Pizzo 2024/25, zadanie 5, część C, Wojciech Kieloch

from zadB import aproxVertexCover
import json
import random
import sys

def main(argv : list[str]):
    if len(argv) < 2:
        print("Provide file path of the graph.")
    filename = argv[1]
    with open(filename) as fd:
        graph = json.load(fd)
    res = aproxVertexCover(graph)
    if random.randint(0, 1) == 1:
        res -= 1
    print(res)

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass