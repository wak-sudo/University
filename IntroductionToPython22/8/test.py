pol_ang = {}
for x in open('pol_ang.txt', encoding='utf8'):
    x = x.strip()
    L = x.split('=')
    if len(L) != 2:
        continue
    pol, ang = L
    if pol in pol_ang:
        pol_ang[pol] += 1
    else:
        pol_ang[pol] = 0

counter= 0
counter2 = 0
for x in pol_ang.values():
    if(x >= 2):
        counter += 1
    else:
        counter2 = 0

print(counter)