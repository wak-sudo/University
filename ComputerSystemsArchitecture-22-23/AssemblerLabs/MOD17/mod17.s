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
        .globl  mod17
        .type   mod17, @function

/*
 * W moim rozwiązaniu używam następującej techniki: właściwości modulo, zliczanie, D&C
 */

mod17:
        # Zamysł:
        # Skorzystam z właściwości modulo 17 w zapisie heksadecymalnym:
        # I: "Różnica sum cyfr (szesnastkowych) na parzystych i nieparzystych pozycjach ma taką samą resztę z dzielenia przez 17 co cała liczba"
        # Zliczę sumę na miejscach nieparzystych i parzystych, następnie skorzystam z własności:
        # II: (x - y) mod z = ((x mod z) - (y mod z)) mod z
        # wyliczę (x mod z), dodam 17 jeżeli wynik będzie ujemny, podobnie z (y mod z)
        # następnie tak samo postąpię z wynikiem odejmowania
        # w ten sposób otrzymam odpowiedź.

        movabs $0xF0F0F0F0F0F0F0F0, %r8 # maska wybierająca pozycje nieparzyste
        mov %rdi, %rax
        and %r8, %rax # w rax trzymamy pozycje nieparzyste 
        shr $4, %rax # przesuwamy wynik o 4 bity, aby następnie łatwo obliczyć sumę.
        shr $4, %r8 # przesuwamy maskę, aby wybierała pozycje parzyste
        and %r8, %rdi # w rdi trzymamy pozycje parzyste

        # metoda dziel i zwyciężaj
        # analogicznie do zliczania bitów
        # najpierw sumujemy pary, później elementy o rozmiarze 4 itd.
        # nie musimy nakładać dodatkowej maski, mamy zapewnione z powyższych masek 1 bajt na obliczenia, a wynik nigdy nie przekroczy 120 (7 bitów)
        mov %rax, %r9 
        shr $8, %r9 # przesuwamy lewą parę na pozycję prawej
        add %r9, %rax # dodajemy pary
        # dalej postępujemy analogicznie
        mov %rax, %r9
        shr $16, %r9
        add %r9, %rax
        mov %rax, %r9
        shr $32, %r9
        add %r9, %rax
        and $0x7F, %rax # skoro wiemy, że ostateczny wynik będzie się mieścił w maksymalnie 7 pierwszych bitach
        # to nakładamy na nie maskę

        # tak samo postępujemy dla rdi (trzymającego pozycje parzyste)
        mov %rdi, %r9
        shr $8, %r9
        add %r9, %rdi
        mov %rdi, %r9
        shr $16, %r9
        add %r9, %rdi
        mov %rdi, %r9
        shr $32, %r9
        add %r9, %rdi
        and $0x7F, %rdi

        # kiedy już posiadamy odpowiednie sumy, to skorzystamy z własności II
        # aby obliczyć (x mod 17) znowu skorzystam z własności I
        # jako że teraz x może wynosić maksymalnie 120, to może być zapisany poprzez maksymalnie 2 znaki hex.
        # więc obliczenie będzie trywialne.
        mov %rdi, %r9
        and $0xF, %r9 # parzysty znak
        shr $4, %rdi # nieparzysty znak
        sub %r9, %rdi

        # analogicznie dla rax
        mov %rax, %r9
        and $0xF, %r9
        shr $4, %rax
        sub %r9, %rax #

        # jeżeli wynik rdi jest mniejszy niż zero, to dodaję 17 do wyniku.
        lea 17(%rdi), %rcx
        test %rdi, %rdi
        cmovs %rcx, %rdi #

        # analogicznie dla rax
        lea 17(%rax), %rcx 
        test %rax, %rax
        cmovs %rcx, %rax #

        # ostatecznie odejmuję wyniki
        # jeżeli wynik jest ujemny, dodaję 17.
        sub %rdi, %rax
        lea 17(%rax), %rcx
        test %rax, %rax
        cmovs %rcx, %rax
        ret

        .size   mod17, .-mod17
