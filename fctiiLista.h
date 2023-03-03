/* CAZANOV Veaceslav - 312CB */

/* Functii lista simpla inlantuita generica */

#include <stdlib.h>
#include <stdio.h>
#include "fctiiComune.h"

#ifndef _FUNCTII_LISTA_
#define _FUNCTII_LISTA_

typedef struct celula
{
    void* info;
    struct celula *urm;
} TCelula, *TL;

void InsHead(TL* aL, void* ae); // insereaza element la inceputul listei
void InsDupa(TCelula* aL, void* ae); // insereaza element dupa o celula
size_t nrElementeL(TL* aL); // intoarce nr de elemente in lista
void eliminaCelula(TL aL, TL* cell); // elimina o celula din lista
void AfiLista(TL l, TFAfi f, FILE* output); // afisare lista
void DistrL(TL* aL, TFDistr f); // distruge o lista

#endif