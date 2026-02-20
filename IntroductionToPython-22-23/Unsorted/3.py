from string import punctuation

dictionary = {}
for line in open("lalka-tom-pierwszy.txt", encoding="utf8"):
    line = ''.join(line)
    line = line.replace("-", " ")
    for pun in punctuation:
        line = line.replace(pun, "")
    line = line.split()    
    for word in line:
        word = word.lower()
        if word not in dictionary.keys():
            dictionary[word] = 1
        else:
            dictionary[word]+=1
            