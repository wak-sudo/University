# Wojciech Kieloch 2024, Pizzo, rev. 1
import json
import sys

class JSONinfo:
    alphabet : list[str]
    states : list[str]
    initial : str
    accepting : list[str]
    transitions : list[(str, str, str)] 

    def __init__(self, filePath : str) -> None:
        file = open(filePath, 'r')
        data = json.load(file)
        file.close()

        self.alphabet = data["alphabet"]
        self.states = data["states"]
        self.initial = data["initial"]
        self.accepting = data["accepting"]
        self.transitions = list()

        transitionsRaw = data["transitions"]
        for tuple in transitionsRaw:
            letter = tuple["letter"]
            fromState = tuple["from"]
            toState = tuple["to"]
            self.transitions.append((letter, fromState, toState))

class Automata:
    originalState : str
    currentState : str
    nextStateFun : dict[(str, str), str]
    acceptingStates : list[str]

    def buildNextStateFun(self, transitions : list[(str, str, str)]) -> None:
        for transition in transitions:
            self.nextStateFun[(transition[1], transition[0])] = transition[2]

    def __init__(self, settingsPath: str) -> None:
        data = JSONinfo(settingsPath)
        self.originalState = data.initial
        self.nextStateFun = dict()
        self.buildNextStateFun(data.transitions)
        self.acceptingStates = data.accepting
        self.currentState = self.originalState 

    def isInValidState(self) -> bool:
        return self.currentState in self.acceptingStates
    
    def printIsInValidSate(self) -> None:
        if self.isInValidState():
            print("yes")
        else: print("no")
    
    def reset(self) -> None:
        self.currentState = self.originalState

    def execute(self, letter : str) -> None:
        self.currentState = self.nextStateFun[(self.currentState, letter)]

def main(argv : list[str]) -> None:
    filePath = input()
    emulator = Automata(filePath)

    inputRaw = sys.stdin.read(1)
    while inputRaw != "":
        if inputRaw == "\n":
            emulator.printIsInValidSate()
            emulator.reset()
        elif inputRaw != "\r":
            emulator.execute(inputRaw)

        inputRaw = sys.stdin.read(1)

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass