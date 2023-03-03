/* CAZANOV Veaceslav - 312CB */

#include "fctiiStiva.h"

// test stiva vida
int VidaS(TStiva s)
{
    return (s->top == NULL);
}


// initializare o stiva vida
TStiva InitS()
{
    TStiva s = (TStiva)malloc(sizeof(TStiva));
    if (!s) return NULL;
    return s;
}


// introduce *ae in varful stivei
void Push(TStiva s, void *ae)
{
    TCelula* aux = (TCelula*)ae;
    if(VidaS(s))
    {
        aux->urm = NULL;
        s->top = aux;
    }
    else
    {
        aux->urm = s->top;
        s->top = aux;
    }
}


// extrage elementul din varful stivei
void* Pop(TStiva s)
{
    if (VidaS(s)) return NULL;
    TL aux = s->top;
    s->top = s->top->urm;
    aux->urm = NULL;
    return aux;
}


// rastoarna stiva src peste stiva dest
// (muta elementele din src in dest si inverseaza stiva)
void Rastoarna(TStiva dest, TStiva src)
{
    TL tmp;
    while (!VidaS(src))
    {
        tmp = (TL)Pop(src);
        Push(dest, tmp);
    }
}


// afiseaza elemente unei stive
void AfiS(TStiva s, TFAfi f, FILE* output)
{
    TStiva aux_s = InitS();
    TL tmp;
    while (!VidaS(s))
    {
        tmp = (TL)Pop(s);
        f(tmp->info, output);
        if (!VidaS(s))
            fprintf(output, ", ");
        Push(aux_s, tmp);
    }
    fprintf(output, "].\n");
    Rastoarna(s, aux_s);
}


// cauta un element cu un nume(*serial) dat
void* findS(TStiva s, void* serial, TFCmp fcmp)
{
    TL tmp, res = NULL;
    TStiva aux_s = InitS();
    while(!VidaS(s))
    {
        tmp = (TL)Pop(s);
        if (!fcmp(serial, tmp->info))
        {
            
            res = tmp;
        }
        Push(aux_s, tmp);
    }
    Rastoarna(s, aux_s);
    return res;
}


// cauta SI elimina un element cu nume(*serial) dat
void* findEliminaS(TStiva s, void* serial, TFCmp fcmp)
{
    TL tmp, res=NULL;
    TStiva aux_s = InitS();
    while(!VidaS(s))
    {
        tmp = (TL)Pop(s);
        if (!fcmp(serial, tmp->info))
        {
            // se elimina din stiva initiala
            // prin NE introducerea in stiva auxiliara
            res = tmp;
            res->urm = NULL;
            continue;
        }
        Push(aux_s, tmp);
    }
    Rastoarna(s, aux_s);
    return res;
}


// distruge o stiva
void DistrS(TStiva* s, TFDistr f)
{
    TL aux;
    while(!VidaS(*s))
    {
        aux = (TL)Pop(*s);
        if (aux != NULL)
        {
            f(aux->info);
            free(aux);
        }
    }
    (*s)->top = NULL;
    free(*s);
    s = NULL;
}