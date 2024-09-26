def random():
    wynik = []
    dic = {'wilk':'r', 'koza':'r', 'kapusta':'r'}
    dozwoloneRuchy = []
    flag = True
    while flag:
        if dic('wilk') == dic('koza'):
            dozwoloneRuchy += 'wilk'
            dozwoloneRuchy += 'koza'
        if dic('koza') == dic('kapusta'):
            dozwoloneRuchy += 'koza'
            dozwoloneRuchy += 'kapusta'
        if dic('wilk') == dic('kapusta'):
            dozwoloneRuchy += 'wilk'
            dozwoloneRuchy += 'koza'