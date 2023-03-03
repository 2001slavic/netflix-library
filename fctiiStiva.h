/* CAZANOV Veaceslav - 312CB */

/* Functii pentru a realiza functionalitatea unei stive folosind liste simple inlantuite */

#include "fctiiLista.h"
#include "fctiiComune.h"
#ifndef _FUNCTII_STIVA_
#define _FUNCTII_STIVA_

typedef struct stiva
{
    TL top;   
} *TStiva;

int VidaS(TStiva s); // test stiva vida
void Push(TStiva s, void *ae); // insereaza un element in varful stivei
void* Pop(TStiva s); // extrahe elementul din varful stivei
TStiva InitS(); // initializare stiva vida
void* findS(TStiva s, void* serial, TFCmp fcmp); // cauta un element in stiva
void AfiS(TStiva s, TFAfi f, FILE* output); // afiseaza stiva
void DistrS(TStiva* s, TFDistr f); // distruge stiva
void Rastoarna(TStiva dest, TStiva src); // rastoarna src peste dest

// gaseste un element cu nume(*serial) si il elimina din stiva
void* findEliminaS(TStiva s, void* serial, TFCmp fcmp);


#endif