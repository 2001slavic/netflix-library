/* CAZANOV Veaceslav - 312CB */

#include "fctiiCoada.h"

// initializare coada vida
TCoada* InitQ()
{
    TCoada* c = (TCoada*)malloc(sizeof(TCoada));
    c->head = c->tail = NULL;
    c->count = 0;
    return c;
}


// test coada vida
int VidaC(TCoada* c)
{
    // intr-o coada vida, primul si ultimul element sunt NULL
    return (c->tail == NULL);
}


// introduce un element la sfaristul cozii
void IntrQ(TCoada* c, TL aux)
{
    if (!VidaC(c))
    {
        c->tail->urm = aux;
        c->tail = aux;
    }
    else
    {
        // daca coada vida, atunci si head si tail sunt aux
        c->head = c->tail = aux;
    }
    c->count++; // pentru afisare in ce pozitie s-a inserat aux
}


// extrage elementul din inceputul cozii
void* ExtrQ(TCoada* c)
{
    if(VidaC(c))
        return NULL;
    TL aux = c->head;

    c->head = aux->urm;
    if (c->head == NULL) c->tail = NULL;
    c->count--;
    aux->urm = NULL;
    return aux;

}


// face o coada vida
void ResetQ(TCoada* c)
{
    c->head = c->tail = NULL;
    c->count = 0;
}


// muta toate elementele din coada src in coada dest
void ConcatQ(TCoada* dest, TCoada* src)
{
    if(VidaC(src)) return;
    TCelula* aux;
    while(!VidaC(src))
    {
        aux = (TCelula*)ExtrQ(src);
        IntrQ(dest, aux);
    }
    
    ResetQ(src);
}


// afisare elemente coada, cu ajutorul functiei auxiliare de
// afisare info a elementelor cozii
void AfiC(TCoada* c, TFAfi f, FILE* output)
{
    TCelula* aux;
    TCoada* aux_c = InitQ();
    while(!VidaC(c))
    {
        aux = (TCelula*)ExtrQ(c);
        f(aux->info, output);
        if (!VidaC(c))
            fprintf(output, ", ");
        IntrQ(aux_c, aux);
    }
    fprintf(output, "].\n");
    ResetQ(c);
    ConcatQ(c, aux_c); // restabilire coada initiala dupa parcurgere
}


// gaseste si intoarce element cu un nume(serial*) dat
void* findC(TCoada* c, void* serial, TFCmp fcmp)
{
    if (VidaC(c)) return NULL;
    TCelula* aux;
    void* res = NULL;
    TCoada* aux_c = InitQ();
    while(!VidaC(c))
    {
        aux = (TCelula*)ExtrQ(c);
        if (!fcmp(serial, aux->info))
        {
            // element gasit
            res = (void*)aux;
        }
        IntrQ(aux_c, aux);
    }
    ConcatQ(c, aux_c);
    return res;
}


// gaseste, intoarce SI elimina un element din coada cu un nume(serial*) dat
void* findEliminaC(TCoada* c, void* serial, TFCmp fcmp)
{
    if (VidaC(c)) return NULL;
    TCelula* aux;
    void* res = NULL;
    TCoada* aux_c = InitQ();
    while(!VidaC(c))
    {
        aux = (TCelula*)ExtrQ(c);
        if (fcmp(serial, aux->info) == 0)
        {
            // eliminarea s-a realizat prin NE introducerea elementului
            // in coada auxiliara
            res = (void*)aux;
            continue;
        }
        IntrQ(aux_c, aux);
    }
    ConcatQ(c, aux_c);
    return res;
}


// functie de distrugere coada, eliberare memorie
void DistrQ(TCoada** c, TFDistr f)
{
    TCelula* aux;
    while (!VidaC(*c))
    {
        aux = (TCelula*)ExtrQ(*c);
        if (aux != NULL)
        {
            f(aux->info);
            free(aux);
        }
    }
    ResetQ(*c);
    free(*c);
    c = NULL;
}

