def wezDrugiElement(elem):
    return elem[1]

def usun_duplikaty(Array):
    ArrLen = len(Array)
    if ArrLen == 0 or ArrLen == 1:
        return Array
    pairsArray = []
    for i in range(len(Array)):
        pairsArray.append((Array[i], i))
    pairsArray.sort()
    clearedPairsArray = [pairsArray[0]]
    for i in range(1, len(pairsArray)):
        if(pairsArray[i][0] != pairsArray[i-1][0]):
            clearedPairsArray.append(pairsArray[i])
    clearedPairsArray.sort(key=lambda x: x[1])
    clearedArray = []
    for elem in clearedPairsArray:
        clearedArray.append(elem[0])
    return clearedArray

arr = [1,2,3,1,2,3,8,2,2,2,9,9,4]
print(usun_duplikaty(arr))