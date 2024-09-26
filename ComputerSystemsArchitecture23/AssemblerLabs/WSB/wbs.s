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
        .globl  wbs
        .type wbs, @function

/*
 * W moim rozwiązaniu używam następującej techniki: zliczanie jedynek
 */

wbs:
        # Będziemy używać następujących masek:
        # 0xAAAAAAAAAAAAAAAA
        # 0xCCCCCCCCCCCCCCCC
        # 0xF0F0F0F0F0F0F0F0
        # 0xFF00FF00FF00FF00
        # 0xFFFF0000FFFF0000
        # 0xFFFFFFFF00000000
        # Zauważmy, że tworzą one w kolumnach (bitowych) wartości od 0 do 63 (od prawej do lewej), stanowiące indeksy kolumn
        # tak jak w zapisie dziesiętnym możemy zapisać 12 + 21 jako 1*10 + 1 + 2*10 + 1 = (1+2) * 10 + (2 + 1) * 1
        # tak samo możemy postąpić w zapisie binarnym, oczywiście zamieniając podstawę na 2.
        # zatem poprzez założenie pierwszej maski mamy zapalone bity na aktywnych indeksach,
        # których wartość w kolumnie posiada niezerowe miejsce jedności,
        # wtedy zliczamy liczbę bitów jedności i dodajemy ją do wyniku
        # następnie nakładamy kolejną maskę, filtrującą aktywne indeksy, których kolumny mają zapalony bit na drugiej pozycji
        # wtedy zliczamy liczbę zapalonych bitów i przesuwamy je na drugą pozycję
        # tak jak w przypadku dziesiątek 10 + 20 = (1 + 2) * 10
        # lub w sys. bin.: 10 + 10 = (1 + 1) << 1
        # dla następnych wielkości postępujemy analogicznie
        # ostatecznie otrzymujemy wynik stanowiący sumę ważoną bitów, ponieważ dodaliśmy wartości (kolumny) odpowiadające zapalonym indeksom   

        # przeskalowany przykład:
        # 01100 (podana wartość)
        # (maski) -> (po działaniach)
        # 01010 -> 1
        # 01100 -> (1+1) << 1 = 4
        # 10000 -> 0
        # -----
        # 43210 (indeksy i wartości pionowe kolumn)
        # SWB: 5, co się zgadza

        # do zliczania zapalonych bitów będziemy używać instrukcji popcnt

        movabs $0xAAAAAAAAAAAAAAAA, %r8
        mov %rdi, %rax
        and %r8, %rax
        popcnt %rax, %rax
        movabs $0xCCCCCCCCCCCCCCCC, %r8
        mov %rdi, %rcx
        and %r8, %rcx
        popcnt %rcx, %rcx
        shl %rcx
        add %rcx, %rax
        movabs $0xF0F0F0F0F0F0F0F0, %r8
        mov %rdi, %rcx
        and %r8, %rcx
        popcnt %rcx, %rcx
        shl $2, %rcx
        add %rcx, %rax
        movabs $0xFF00FF00FF00FF00, %r8
        mov %rdi, %rcx
        and %r8, %rcx
        popcnt %rcx, %rcx
        shl $3, %rcx
        add %rcx, %rax
        movabs $0xFFFF0000FFFF0000, %r8
        mov %rdi, %rcx
        and %r8, %rcx
        popcnt %rcx, %rcx
        shl $4, %rcx
        add %rcx, %rax
        movabs $0xFFFFFFFF00000000, %r8
        mov %rdi, %rcx
        and %r8, %rcx
        popcnt %rcx, %rcx
        shl $5, %rcx
        add %rcx, %rax
        ret

        .size wbs, .-wbs
