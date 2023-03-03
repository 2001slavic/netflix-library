/* CAZANOV Veaceslav - 312CB */

/* Prototipe functii necesare pentru realizarea conditiei temei. */

#include "fctiiLista.h"
#include "fctiiCoada.h"
#include "fctiiStiva.h"
#include <string.h>
#include <stdio.h>

#ifndef _FUNCTII_CERINTA_
#define _FUNCTII_CERINTA_

typedef void* (*TFAloc)(void*);
typedef void* (*TFInsInfo)(void*, void*, void*, void*);
typedef void* (TFUpdSer)(void*, void*, void*);

// functia add
void add(char* line, TFAloc fEp, TFAloc fSez, TFCmp cmp, TFInsInfo InsSer,
        TL* l1, TL* l2, TL* l3, FILE* output);

// cauta un element in categorii seriale (1-4)
TL find(TL *l1, TL *l2, TL *l3, TL *l4, void* nume, TFCmp fcmp,
        TFInsInfo InsSer, TL * celula, int* first, int* lista);

// functia add_sez
void add_sez(char* line, TL* l1, TL* l2, TL* l3, TL* l4, TCoada* watch_later,
                TStiva currently_watching, TFCmp fcmp, TFAloc fEp, TFUpdSer fSez,
                TFInsInfo InsSer, FILE* output);


// functia add_top
void add_top(char* line, TL* l4, TFAloc fEp, TFAloc fSez, TFInsInfo InsSer,
            TFAfi fAfi, FILE* output);


// functia later (adauga un serial in watch later)
void later(char* line, TCoada* watch_later, TL *l1, TL *l2, TL *l3, TL *l4,
            TFCmp fcmp, TFInsInfo InsSer, FILE* output);


// functia watch
void watch(char* line, TL* l1, TL* l2, TL* l3, TL* l4,
            TCoada* watch_later, TStiva currently_watching,
            TStiva history, TFCmp fcmp, TFCmp fDurata,
            TFInsInfo InsSer, FILE* output);


// functia show (afiseaza elementele unei categorii date)
void show(char* line, TFAfi f, TL l1, TL l2, TL l3, TL l4,
            TCoada* watch_later, TStiva currently_watching,
            TStiva history, FILE* output);

#endif