/*
* Wojciech Kieloch
* PO: Lista 1 zad. 2
* gcc z2.c
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int licznik;
    int mianownik;
} Ulamek;

int NWD(int a, int b)
{
    int temp;
    while(b != 0)
    {
        temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

int NWW(int a, int b)
{
    return a*b/NWD(a,b);
}

void skrocUlamek(Ulamek* ul)
{
    int d = NWD(ul->mianownik, ul->licznik);
    ul->licznik = ul->licznik / d;
    ul->mianownik = ul->mianownik / d;
}

void show(Ulamek *u)
{
    printf("%d/%d\n", u->licznik, u->mianownik);
}

Ulamek* nowy_ulamek(int num, int denom)
{
    Ulamek *ptr = (Ulamek*)malloc(sizeof(Ulamek));
    if(denom == 0) // Wlaciwosc mojej specyfikacji.
    {
        ptr->mianownik = 1;
        ptr->licznik = 0;
    }
    else
    {
        ptr->mianownik = denom;
        ptr->licznik = num;
        skrocUlamek(ptr);
    }
    return ptr;
}

// operacje na ulamkach:

Ulamek* dodajUlamkiNew(Ulamek* u1, Ulamek* u2)
{
    int nowyMianownik = NWW(u1->mianownik, u2->mianownik);
    int nowyLicznik1 = u1->licznik * nowyMianownik/u1->mianownik;
    int nowyLicznik2 = u2->licznik * nowyMianownik/u2->mianownik;
    int licznikWynik = nowyLicznik1 + nowyLicznik2;
    Ulamek * nowyUlamek  = malloc(sizeof(Ulamek));
    nowyUlamek->licznik = licznikWynik;
    nowyUlamek->mianownik = nowyMianownik;
    skrocUlamek(nowyUlamek);
    return nowyUlamek;
}

void dodajUlamkiChange(Ulamek* u1, Ulamek* u2)
{
    int nowyMianownik = NWW(u1->mianownik, u2->mianownik);
    int nowyLicznik1 = u1->licznik * nowyMianownik/u1->mianownik;
    int nowyLicznik2 = u2->licznik * nowyMianownik/u2->mianownik;
    int licznikWynik = nowyLicznik1 + nowyLicznik2;
    u2->licznik = licznikWynik;
    u2->mianownik = nowyMianownik;
    skrocUlamek(u2);
}

Ulamek* odejmijUlamkiNew(Ulamek* u1, Ulamek* u2)
{
    int nowyMianownik = NWW(u1->mianownik, u2->mianownik);
    int nowyLicznik1 = u1->licznik * nowyMianownik/u1->mianownik;
    int nowyLicznik2 = u2->licznik * nowyMianownik/u2->mianownik;
    int licznikWynik = nowyLicznik1 - nowyLicznik2;
    Ulamek * nowyUlamek  = malloc(sizeof(Ulamek));
    nowyUlamek->licznik = licznikWynik;
    nowyUlamek->mianownik = nowyMianownik;
    skrocUlamek(nowyUlamek);
    return nowyUlamek;
}

void odejmijUlamkiChange(Ulamek* u1, Ulamek* u2)
{
    int nowyMianownik = NWW(u1->mianownik, u2->mianownik);
    int nowyLicznik1 = u1->licznik * nowyMianownik/u1->mianownik;
    int nowyLicznik2 = u2->licznik * nowyMianownik/u2->mianownik;
    int licznikWynik = nowyLicznik1 - nowyLicznik2;
    u2->licznik = licznikWynik;
    u2->mianownik = nowyMianownik;
    skrocUlamek(u2);
}

Ulamek* pomnozUlamkiNew(Ulamek* u1, Ulamek* u2)
{
    Ulamek * nowyUlamek  = malloc(sizeof(Ulamek));
    nowyUlamek->licznik = u1->licznik * u2->licznik;
    nowyUlamek->mianownik = u1->mianownik * u2->mianownik;
    skrocUlamek(nowyUlamek);
    return nowyUlamek;
}

void pomnozUlamkiChagne(Ulamek *u1, Ulamek* u2)
{
    u2->licznik = u1->licznik * u2->licznik;
    u2->mianownik = u1->mianownik * u2->mianownik;
    skrocUlamek(u2);
}

Ulamek* podzielUlamkiNew(Ulamek *u1, Ulamek* u2)
{
    Ulamek * nowyUlamek  = malloc(sizeof(Ulamek));
    nowyUlamek->licznik = u1->licznik * u2->mianownik;
    nowyUlamek->mianownik = u1->mianownik * u2->licznik;
    skrocUlamek(nowyUlamek);
    return nowyUlamek;
}

void podzielUlamkiChagne(Ulamek *u1, Ulamek *u2)
{
    int u2LicznikOrg = u2->licznik;
    u2->licznik = u1->licznik * u2->mianownik;
    u2->mianownik = u1->mianownik * u2LicznikOrg;
    skrocUlamek(u2);
}

int main()
{
    Ulamek *u1 = nowy_ulamek(7, 9);
    Ulamek *u2 = nowy_ulamek(4, 5);
    Ulamek *u3 = podzielUlamkiNew(u1, u2);
    show(u3);
    free(u1);
    free(u2);
    free(u3);
    return 0;
}
