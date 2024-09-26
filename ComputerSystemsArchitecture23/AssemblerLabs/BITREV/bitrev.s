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
        .globl  bitrev
        .type bitrev, @function

/*
 * W moim rozwiązaniu używam następującej techniki: dziel i zwyciężaj
 */

bitrev:
        /*
        Skorzystamy z metody dziel i zwyciężaj.
        Najpierw połączymy bity w par, odwracając ich kolejność
        Następnie połączymy pary w 4 bitowe elementy, odwracając kolejność par
        Kontynuujemy tym sposobem, aż dojdziemy do elementów 16 bitowych.
        Będziemy mieć wtedy 4 takie (16 bitowe) części i analogicznie trzeba będzie je obrócić.
        Ale zrobimy to szybciej.
        Ostatecznie uzyskamy odwrócony ciąg bitów.
        */
        mov     %rdi, %rax
        movabs  $0x5555555555555555, %rsi # 0101010..
        and     %rsi, %rax # bierzemy co drugi bit, resztę czyścimy
        shl     %rax # przesuwamy go w lewo
        shr     %rdi # w kopii przesuwamy bity w prawo
        and     %rsi, %rdi # i bierzemy co drugi
        or      %rdi, %rax # orujemy, czyli tworzymy pary, w których na pierwszej pozycji jest bit przesunięty w lewo
                           # a na drugiej ten przesunięty w prawo, czyli na zamienionych pozycjach.
        mov     %rax, %rdi # aktualizujemy rdi, dalej będziemy postępować analogicznie tylko dla większych wielkości
                           # poczynając na odwracaniu par, kontynuując dla 4 bitowych elementów itd.
        movabs  $0x3333333333333333, %rsi # 0011 0011 ...
        and     %rsi, %rax
        shl     $2, %rax
        shr     $2, %rdi
        and     %rsi, %rdi
        or      %rdi, %rax
        mov     %rax, %rdi
        movabs  $0x0F0F0F0F0F0F0F0F, %rsi # 0000 1111 0000 1111 ...
        and     %rsi, %rax
        shl     $4, %rax
        shr     $4, %rdi
        and     %rsi, %rdi
        or      %rdi, %rax
        mov     %rax, %rdi
        movabs  $0xFF00FF00FF00FF, %rsi # 0000 0000 1111 1111 0000 0000 1111 1111 ... 
        and     %rsi, %rax
        shl     $8, %rax
        shr     $8, %rdi
        and     %rsi, %rdi
        or      %rdi, %rax
        mov     %rax, %rdi
        movabs  $0xFFFF0000FFFF, %rsi # 0000 0000 0000 0000 1111 1111 1111 1111 ...
        # na ostatnim etapie postępować będziemy sprytniej
        # skoro elementy 16 bitowe są już wewnętrznie odwrócone, to wyobraźmy sobie, że reprezentuje je ABCD
        and     %rsi, %rax # wybieramy tylko B i D, resztę zerujemy
        ror     $16, %rax # cyklicznie przesuwamy w prawo, zatem D0B0
        rol     $16, %rdi # cyk. w lewo na kopii, zatem BCDA
        and     %rsi, %rdi # zostawiamy tylko C i A, czyli mamy na kopii 0C0A
        or      %rdi, %rax # D0B0 | 0C0A = DCBA, cała wartość odwrócona, mamy wynik.
        ret

        .size bitrev, .-bitrev
