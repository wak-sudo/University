def usun_w_nawiasach(s):
    wynik = ''
    insideBracket = False 
    for i in range(len(s)):
        if s[i] == ')':
            insideBracket = False
        elif s[i] == '(':
            insideBracket = True
        elif insideBracket == False:
            wynik += s[i]
    return wynik

print(usun_w_nawiasach("Ala ma kota (perskiego)!"))
print(usun_w_nawiasach("Widząc, że jedno ziarno upadło na kontuar (stary miał w tej chwili oczy zamknięte), podniosłem je nieznacznie i zjadłem."))
print(usun_w_nawiasach("(Tak) mimo to (nadal) parliśmy przed siebie (naprzód)."))