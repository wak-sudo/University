/*
* Wojciech Kieloch
* PO: Lista 1 zad. 3
* gcc z3.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

typedef struct
{
    int leftSide;
    int rightSide;
    float *arr;
    bool empty;
} Tablica;

Tablica* nowa_tablica()
{
    Tablica *t = malloc(sizeof(Tablica));
    t->empty = true;
    return t;
}

void reallocateArray(Tablica *t, int l,int r)
{
    if(l <= r)
    {
        int oldArrSize = abs(t->rightSide - t->leftSide) + 1;
        int newArrSize = abs(r-l)+1;
        float *newArr = malloc(newArrSize*sizeof(float));
        int przesuniecie = abs(l - t->leftSide);

        for(int i = 0; i<oldArrSize; i++) // skopiuj komorki z przesunieciem
            newArr[i+przesuniecie] = t->arr[i];

        for(int i = 0; i<przesuniecie; i++) // wyzeruj nowe komorki od lewej.
            newArr[i] = 0;
        t->leftSide = l;

        for (int i = przesuniecie + oldArrSize; i<newArrSize; i++) // wyzeruj komorki dodane po prawej
            newArr[i] = 0;
        t->rightSide = r;

        free(t->arr);
        t->arr = newArr;
    }
}

void dodaj(Tablica *t, int index, float val)
{
    if(t->empty)
    {
        t->leftSide = index;
        t->rightSide = index;
        t->arr = malloc(sizeof(float));
        t->empty = false;
    }
    else if(index < t->leftSide)
        reallocateArray(t, index, t->rightSide);
    else if (index > t->rightSide)
        reallocateArray(t, t->leftSide, index);
    t->arr[index - t->leftSide] = val;
}

float indeks(Tablica *t, int poz)
{
    if(poz >= t->leftSide && poz <= t->rightSide && !t->empty)
        return t->arr[poz - t->leftSide];
    else return 0;
}

void show(Tablica *t)
{
    if(!t->empty)
    {
        for(int i = 0; i<=abs(t->rightSide - t->leftSide); i++)
            printf("%d : %.2f | ", t->leftSide+i, t->arr[i]);
        printf("\n");
    }
    else printf("Empty");
}

int main()
{
    Tablica *t = nowa_tablica();
    dodaj(t, -2, 6.0);
    dodaj(t, -3, 5.0);
    dodaj(t, 1, 1.0);
    dodaj(t, -6, -2.3);
    show(t);
    printf("%.2f\n", indeks(t, -6));
    printf("%.2f\n", indeks(t, -5));
    printf("%.2f\n", indeks(t, -3));
    free(t);
    return 0;
}
