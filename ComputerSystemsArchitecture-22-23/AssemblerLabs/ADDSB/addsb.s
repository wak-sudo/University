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
        .globl  addsb
        .type   addsb, @function

/*
 * W moim rozwiązaniu używam następującej techniki: underflow and overflow check
 */

addsb:
        /*
        Zamysł ogólny:
        W każdym elemencie wyzerujemy bit znaku.
        Następnie dodamy tak spreparowany elementy i uzyskamy sumę
        Sprawdzając bity znaku el.a i el.b i wynik poprawionej sumy, będziemy mogli stwierdzić, czy nastąpił underflow lub overflow
        i w takim wypadku zastosować odpowiednie limity. 
        */
        # maska do wyciągania bitów znaku:
        movabs     $0x8080808080808080, %r8 # 1000 0000 1000 0000 ...
        mov     %rdi, %r9 # a - wektor; kopia  
        mov     %rsi, %r10 # b - wektor; kopia
        and     %r8, %r9 # aZnak = a & 0x8080808080808080; wyciągamy bity znaków
        and     %r8, %r10 # bZnak = b & 0x8080808080808080; wyciągamy bity znaków
        xor     %r9, %rdi # a^aZnak ; zerujemy bit znaku
        xor     %r10, %rsi # b^aZnak ; zerujemy bit znaku, chroni nas to przed przeniesieniem bita poza zakres w trakcie sumowania obu wartości,
        # to czy nastąpiłby underflow sprawdzimy sprytniej później korzystając ze bitów znaku. 
        mov     %r9, %r11 # temp aZnak;
        xor     %r10, %r11 # aZnak ^ bZnak; 
        add     %rsi, %rdi # sum = a^aZnak + b^bZnak; suma elementów bez bitów znaku
        xor     %r11, %rdi # sum ^= aZnak ^ bZnak; # tutaj poprawiamy wynik, działa na zasadzie:
        # jeżeli elementy były tego samego znaku, to po prostu bierzemy sumę (jeżeli byłyby ujemne to i tak nastąpiłby underflow,
        # jeżeli dodatnie może nastąpić overflow, ale bit nie wychodzi poza zakres)
        # jeżeli były przeciwnego:
        #       jeżeli wynik był ujemny, to ustawiamy znak bitu na 0 (nastąpiłby underflow, bo doatkowo jedna wartość jest ujemna)
        #       jeżeli wynik był dodatni, to ustawiamy znak bitu na 1 (bo jedna wartość jest ujemna i nie nastąpił underflow)
        # to zapewnia nam nieprzenoszenie bitów poza 8 bit elementu i mozliwość późniejszego sprawdzania over/underflowa
        mov     %rdi, %rax # kopia sum
        and     %r8, %rdi # sumZnak = sum & 0x8080808080808080; znaki sum

        # jeżeli el.a >= 0 & el.b >= 0 & suma < 0, nastąpił overflow, ustawiamy górny limit.
        mov     %r9, %r8 # temp aZnak
        or      %r10, %r8 # aZnak|bZnak 
        not     %r8 # ~(aZnak|bZnak)
        and     %rdi, %r8  # sat = sumZnak & ~(aZnak|bZnak)
        # sat = 0x80 (dla el.) wtw suma < 0 i el.a >= 0 i el.b >= 0 
        mov     %r8, %r11 # kopia sat
        shr     $7, %r8 # jeżeli sat = 0x80 (dla el.), to przesuwamy jedynkę na pierwsze miejsce elementu.
        imul    $127, %r8 # w mul i imul nie ma różnicy dla pierwszych 64 bitów wyniku; wypełniamy 7 bitów jedynkami 
        or      %r8, %rax # sum |= (sat>>7)*127; wypełniamy wynik sum, w których nastąpił overflow, jedynkami. 
        not     %r11 # ~sat
        and     %r11, %rax # sum &= ~sat ; ustawiamy bit znaku na 0 w elemetnach, w których nastąpił overflow

        # jeżeli el.a < 0 & el.b < 0 & suma >= 0, nastąpił underflow, ustawiamy dolny limit.
        not     %rdi # ~sumZnak
        and     %r10, %r9 # aZnak&bZnak
        and     %r9, %rdi # sat = (aZnak&bZnak) & ~sumZnak;
        # sat = 0x80 (dla el.) wtw el.a < 0 & el.b < 0 & suma >= 0
        mov     %rdi, %r11 # kopia sat
        shr     $7, %rdi # analogicznie jak w przypadku poprzednim
        imul    $127, %rdi 
        not     %rdi
        and     %rdi, %rax # sum &= ~((sat>>7)*127) ; zerujemy bity elementów, w których nastąpił underflow
        or      %r11, %rax # sum |= sat; ustawiamy bit znaku elementów, w których nastąpił underflow na 1.
        ret # koniec

        .size   addsb, .-addsb
