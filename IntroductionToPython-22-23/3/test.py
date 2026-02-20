def generate_data():
    data = set()
    for sufix in range(1000):
        data.add(7777777000 + sufix)
    for sufix in range(100):
        for prefix in range(1,10):
            data.add(prefix*1000000000 + 777777700 + sufix)
    for sufix in range(10):
        for prefix in range(10,100):
            data.add(prefix*100000000 + 77777770 + sufix)
    for prefix in range(100,1000):
        data.add(prefix*10000000 + 7777777)
    return data

def gen():
    data = set()
    middle = 7777777
    prefix_len = 0
    suffix_len = 3

    while suffix_len >= 0:
        base = middle*(10**suffix_len)
        power = (10**(10 - prefix_len))
        for sufix in range(10**suffix_len):       
            for prefix in range(int(10**(prefix_len - 1)),int(10**prefix_len)):
                data.add(prefix*power + base + sufix)
        suffix_len-=1
        prefix_len+=1

    return data

data1 = generate_data()
s1 = list(data1)
data2 = gen()
s2 = list(data2)

s1.sort()
s2.sort()

if(len(s1) == len(s2)):
    print("Ident")
else:
    for i in min(s1, s2):
        if(s1[i] != s2[i]):
            print(s1[i] + "!=" + s2[i])