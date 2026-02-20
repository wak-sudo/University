# Wojciech Kieloch, pizzo 24, zad.1

import sys
import random
import json

class Automata:
    states : set[int]
    initalState : int
    nextStateFun : dict[(int, str), int]
    acceptingStates : set[int]
    alphabet : list[str]

    def __init__(self) -> None:
        self.nextStateFun = dict()
        self.acceptingStates = set()
        self.alphabet = list()
        self.states = set()

    def automatToJSON(self) -> str:
        alphabetJson = self.alphabet
        statesJson = ["q" + str(x) for x in self.states]
        initialJson = "q" + str(self.initalState)
        acceptingJson = ["q" + str(x) for x in self.acceptingStates]
        transitionsJson = list()
        for key in self.nextStateFun:
            tempEntry = {
                "letter" : str(key[1]),
                "from" : ("q" + str(key[0])),
                "to" : ("q" + str(self.nextStateFun[key]))
            }
            transitionsJson.append(tempEntry)
        
        jsonScheme = {
            "alphabet" : alphabetJson,
            "states" : statesJson,
            "initial" : initialJson,
            "accepting" : acceptingJson,
            "transitions" : transitionsJson,
        }
        return json.dumps(jsonScheme)

class AutomataBuilder(Automata):
    currentState : int
    junkState : int 

    def __init__(self) -> None:
        super().__init__()
        self.junkState = 0
        self.initalState = 1
        self.alphabet = ["a", "b", "c"]
        self.currentState = self.initalState 

        self.states.add(self.junkState)
        self.states.add(self.initalState)

        for c in self.alphabet:
            self.nextStateFun[(self.initalState, c)] = self.junkState
            self.nextStateFun[(self.junkState, c)] = self.junkState

    def move(self, char, final):
        transitionArg = (self.currentState, char)
        if self.nextStateFun[transitionArg] == self.junkState:
            newState = self.addNewState()
            self.nextStateFun[transitionArg]= newState
            for c in self.alphabet:
                self.nextStateFun[(newState, c)] = self.junkState

        self.currentState = self.nextStateFun[transitionArg]
        if(final == True): 
            self.acceptingStates.add(self.currentState)

    def emptyIsAccepted(self):
        self.acceptingStates.add(self.initalState)

    def addNewState(self) -> int:
        res = len(self.states)
        self.states.add(res)
        return res
    
    def reset(self) -> None:
        self.currentState = self.initalState

    def findEquivClass(self): # Hopcroft
        fst = frozenset(self.acceptingStates)
        snd = frozenset(self.states - self.acceptingStates)
        initialSet = {fst, snd}
        P = initialSet.copy()
        W = initialSet.copy()
        while len(W) != 0:
            A = random.choice(tuple(W))
            W.remove(A)
            for c in self.alphabet:
                X = set()
                for state in self.states:
                    if self.nextStateFun[(state, c)] in A:
                        X.add(state)

                Ptemp = P.copy()
                for Y in Ptemp:
                    inter = frozenset(X & Y)
                    diff = frozenset(Y - X)
                    if(len(inter) != 0 and len(diff) != 0):
                        P.remove(Y)
                        P.add(inter)
                        P.add(diff)
                        if Y in W:
                            W.remove(Y)
                            W.add(inter)
                            W.add(diff)
                        else:
                            if(len(inter) <= len(diff)):
                                W.add(inter)
                            else:
                                W.add(diff)
        return P
    
    def getSet(self, P, el):
        for setIter in P:
            if el in setIter:
                return setIter

    def retOptimized(self):
        optAut = Automata()
        equiv = self.findEquivClass()
        classToNumber = dict()
        i = 0
        for statesSet in equiv:
            classToNumber[statesSet] = i
            optAut.states.add(i)
            i += 1

        for statesSet in equiv:
            fromParentSetNumber = classToNumber[statesSet]
            anyState = next(iter(statesSet))
            for c in self.alphabet:
                transRes = self.nextStateFun[(anyState, c)]
                toParentSetNumber = classToNumber[self.getSet(equiv, transRes)]
                optAut.nextStateFun[(fromParentSetNumber, c)] = toParentSetNumber

        optAut.initalState = classToNumber[self.getSet(equiv, self.initalState)]
        
        for aceptStates in self.acceptingStates:
            corState = classToNumber[self.getSet(equiv, aceptStates)]
            optAut.acceptingStates.add(corState)

        return optAut


def main(argv : list[str]) -> None:
    inputVal = input()
    samplesCount, minimalCount = inputVal.split()
    emulator = AutomataBuilder()

    samplesCountInt = int(samplesCount)
    
    for i in range(0, samplesCountInt):
        line = input()
        if line[0] == "-":
            continue
        emulator.reset()
        if(len(line) == 1):
            emulator.emptyIsAccepted()
        elif(len(line) == 2):
             emulator.move(line[1], True)
        else:
            for c in line[1:len(line)-1]:
                emulator.move(c, False)
            emulator.move(line[len(line)-1], True)

    print(emulator.retOptimized().automatToJSON())

if __name__ == "__main__":
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        pass