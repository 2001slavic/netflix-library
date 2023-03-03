/* CAZANOV Veaceslav - 312CB */

/* Functii pentru a realiza functionalitatea unei cozi cu liste simple inlantuite. */

#include "fctiiLista.h"
#include "fctiiComune.h"

#ifndef _FUCNTII_COADA_
#define _FUNCTII_COADA_

typedef struct
{
    int count;
    TCelula *head, *tail;   
} TCoada;



TCoada* InitQ(); // initializeaza o coada vida
void IntrQ(TCoada* c, TL aux); // introduce un element in coada
void* ExtrQ(TCoada* c); // extrage un element din coada
int VidaC(TCoada* c); // test coada vida
void ResetQ(TCoada* c); // face coada vida
void ConcatQ(TCoada* dest, TCoada* src); // muta elementele din src in dest
void* findC(TCoada* c, void* serial, TFCmp fcmp); // cauta un element in coada
void AfiC(TCoada* c, TFAfi f, FILE* output); // afisare elemente coada
void DistrQ(TCoada** c, TFDistr f); // distruge o coada

//cauta si elimina un element din coada
void* findEliminaC(TCoada* c, void* serial, TFCmp fcmp);

#endif