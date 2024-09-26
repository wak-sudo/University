dic = {}
for line in open("popularne_slowa.txt", encoding="utf8"):
    line = line[:len(line)-1]
    if line in dic:
        dic[line] = 1
    else:
        dic[line[::-1]] = 0
out = []
for key, val in dic.items():
    if val == 1:
        out.append((key, key[::-1]))

#palindromy nie dzialają
print(len(out))