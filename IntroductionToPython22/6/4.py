def podziel(s):
    wynik = []    
    i = 0
    while i < len(s):
        if(s[i] != " "):
            slowo = ""
            while(i < len(s) and s[i] != " "):
                slowo += s[i]
                i+=1
            wynik += [slowo]
        i+=1    
    return wynik

print(podziel("  ALA    MA KOTA MIRKA   "))

        
