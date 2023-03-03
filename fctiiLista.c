/* CAZANOV Veaceslav - 312CB */

#include "fctiiLista.h"

// inserare element cu campul info *ae, la inceputul listei *aL,
// cu actualizarea head-ului listei.
void InsHead(TL* aL, void* ae)
{
    TL aux = malloc(sizeof(TCelula));
    if (!aux) return;
    
    aux->info = ae;
    aux->urm = *aL;
    *aL = aux;

}


// inserare element cu campul info *ae, dupa o celula data (*aL)
void InsDupa(TCelula* aL, void* ae)
{
    if (aL == NULL) return;
    TL aux = malloc(sizeof(TCelula));
    aux->info = ae;
    aux->urm = aL->urm;
    aL->urm = aux;

}

// returneaza numarul de elemente dintr-o lista (*aL)
size_t nrElementeL(TL* aL)
{
    TL aux = *aL;
    size_t res = 0;
    for (; aux != NULL; aux = aux->urm)
        res++;
    return res;
}


// elimina o celula din lista, fara eliberare memorie
// aL - anteriorul celulei cell
void eliminaCelula(TL aL, TL* cell)
{
    TL aux = *cell;
    if(!aux) return;

    // primul element in lista
    if (!aL)
    {
        *cell = (*cell)->urm;
        return;
    }

    TL next = aux->urm;
    aL->urm = next;
    aux->urm = NULL;
}


// afisare elemente din o lista
void AfiLista(TL l, TFAfi f, FILE* output)
{
    TL aux = l;
    for (; aux != NULL; aux = aux->urm)
    {
        f(aux->info, output);
        if (aux->urm != NULL)
            fprintf(output, ", ");
    }
    fprintf(output, "].\n");
}


// distruge lista si elibereaza memoria ocupata
void DistrL(TL* aL, TFDistr f)
{
    while(*aL != NULL)
    {
        TL aux = *aL;
        if (!aux) return;

        f(aux->info);
        *aL = aux->urm;
        free(aux);
    }
}