/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: Wojciech Kieloch, 339952
 */

        .text
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki: Dziel i zwyciężaj
 */

clz:
        /* Zamysł ogólny:
        
         Weźmiemy pierwsza jedynkę w zapisie liczby, rozwińmy ją do prawej (analogicznie do rozwinięcie znaku)
         Następnie zanegujemy całą wartość i policzymy jedynki, w ten sposób otrzymamy liczbe zer wiodących.
         
        */
        
        /* Część I: Rozwinięcie pierwszej jedynki
        
         
           x = x | (x >> 1)
           x = x | (x >> 2)
           x = x | (x >> 4)
           x = x | (x >> 8)
           x = x | (x >> 16)
           x = x | (x >> 32)
           ret ~x
        
        
        Metoda działania:
         
         Spójrzmy co się stanie z pierwszą jedynkę od lewej
         liczba na prawo od niej stanie się jedynką (pierwsza linia)
       	 następnie druga liczba na prawo stanie się jedynka (druga linia)
       	 a pierwsza liczba na prawo spowoduje zmianę trzeciej liczby na prawo (druga linia)
       	 przez co już 3 liczby na prawo są jedynkami
       	 proces kontynuujemy, okazuje się, że wszystkie liczby na prawo od pierwszej jedynki też będą jedynkami
       	 inaczej mówiąc: dla każdej jedynki na danym etapie mówimy żeby zapaliła x bit na prawo od siebie, co skutkuje zapaleniem wszystkich bitów na prawo od pierwszej jedynki.
       	
       	*/
       	
        mov %rdi, %rax # w rdi będziemy przechowywać oryginalna wartość na danym etapie
        shr %rax # w raxie będziemy trzymać przesuniętą wartość
        or %rdi, %rax # tutaj orujemy wyniki tak jak na schemacie wyżej, proces powtarzamy tylko ze zmienionym przesunięciem
        mov %rax, %rdi
        shr $2, %rax
        or %rdi, %rax
        mov %rax, %rdi
        shr $4, %rax
        or %rdi, %rax
        mov %rax, %rdi
        shr $8, %rax
        or %rdi, %rax
        mov %rax, %rdi
        shr $16, %rax
        or %rdi, %rax
        mov %rax, %rdi
        shr $32, %rax
        or %rdi, %rax
        not %rax # ostatecznie negujemy wynik, przez co zera stają się jedynkami
        
        /* Część II: Zliczanie jedynek
        
         Skoro mamy już jedynki reprezentujące zera wiodące, to pora je zliczyć metodą D&C
         podzielmy zapis binarny liczby na pojedyncze komórki, czyli w jednej komórce jest jedna cyfra
         następnie dodajmy te komórki i wynik każdej pary przechowajmy na 2 bitach
         w tych dwóch bitach będzie nasza wartość reprezentująca liczbę jedynek w parze
         następnie dodajmy komórki 2 bitowe i przechowajmy je na 4 bitach
         proces kontynuujemy aż osiągniemy jedną wartość przechowaną na 64 bitach
         będzie ona stanowiła ilość jedynek w zapisie
         zauważmy też, że na uint64 można zapisać maksymalnie 64 jedynek
         zatem nasz wynik będzie się mieścił w 7 bitach, ponieważ
         log2(64) + 1 = 7
        
        
        a) x = x - ((x>>1 & 0x5555555555555555));
        b) x = (x & 0x3333333333333333) + ((x>>2) & 0x3333333333333333);
        c) x = (x + (x >> 4 )) & 0x0f0f0f0f0f0f0f0f;
        d) x = x + (x >> 8);
    	e) x = x + (x >> 16);
    	f) x = x + (x >> 32);
    	g) ret x & 0x7f; 
    	
    	
        a) łączenie 1 w 2
         rdi będzie przechowywało informacje czy w pierwszej komórce w parze znajduje się 1
         użyjemy do tego przesunięcia (czyli przesuwamy element pierwszy z pary na drugą pozycję)
         i maski która oczyści nam wynik
        
          Wyjaśnienie dlaczego od oryginalnej wartości odejmujemy rdi:
        
         Weźmy fragment zapisu w postaci pary liczb, a rdi niech będzie odpowiadającym fragmentem
         jeżeli para to 10 to 10-rdi = 10-1 = 01
         jeżeli para to 11 to 11-rdi = 11-1 = 10 (2)
         jeżeli para to 01 to 01-rdi = 01-0 = 01
         zatem dla wszystkich przypadków, wynik ilości jedynek jest prawidłowy 
         
        */
        
        mov %rax, %rdi
        shr %rdi
        movabs $0x5555555555555555, %rsi # 0x5555... = 01010...
        and %rsi, %rdi 
        sub %rdi, %rax
        mov %rax, %rdi
        
        # b) 2 w 4 
        # nakładamy maskę bierzemy prawa część z 4 bitowych par
        movabs $0x3333333333333333, %rsi # 0x333... = 0011 0011 ...
        and %rsi, %rax 
        shr $2, %rdi # bierzemy lewą cześć
        and %rsi, %rdi # oczyszczamy wynik do dodawania
        add %rdi, %rax # dodajemy prawą i lewą stronę, otrzymujemy ilość jedynek
        mov %rax, %rdi # aktualizujemy rdi
        
        # c) 4 w 8
        shr $4, %rdi # bierzemy kolejną lewą cześć
        # możemy bezkonsekwencji dodać ją do prawej, ponieważ wynik zawsze zmieści sie na 4 bitach
        add %rdi, %rax # dodajemy obie cześci
        # nakładamy maskę, aby oczyścić lewą stronę która będzie nam potrzeba
        movabs $0x0f0f0f0f0f0f0f0f, %rsi
        and %rsi, %rax # 0x0f0f0f0.. = 0000 1111 0000 1111...
        mov %rax, %rdi
        
        /* d) e) f) 8 w 16, 16 w 32, 32 w 64
         od tej pory będziemy po prostu dodawać strony bez konsekwencji
         ponieważ wynik zawsze będzie się mieścił w 7 bitach, a mamy dostępne 8 z poprzedniego kroku
         końcowo trzeba będzie pobrać pierwsze 7 bitów
        */
        shr $8, %rdi
        add %rdi, %rax
        mov %rax, %rdi
        shr $16, %rdi
        add %rdi, %rax
        mov %rax, %rdi
        shr $32, %rdi
        add %rdi, %rax
        # nakładamy maskę na ostatnie 7 bitów
        and $0x7f, %rax # 0x7f = ...0111 1111
        # ostatecznie otrzymujemy liczbę zer wiodących, koniec.
        ret

        .size   clz, .-clz

