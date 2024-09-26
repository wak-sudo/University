polAlf = "aąbcćdeęfghijklłmnńoóprsśtuwyzźż"

def cesar(s,k):
    tabela = dict(zip(polAlf, polAlf[k:] + polAlf[0:k]))
    return ''.join(tabela[c] for c in s.lower())

print(cesar("", 16))
print(cesar("amwce", 22))
# acóż