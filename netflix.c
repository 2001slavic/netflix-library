/* CAZANOV Veaceslav - 312CB */

#include "fctiiCerinta.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
    TCoada* sezoane;
    char* nume;
    double rating;
    int durata_totala;
    int durata_privita;
} TSerial;

typedef struct
{
    TCoada* episoade;
} TSezon;

typedef struct
{
    int durata;
} TEpisod;


// alocare un episod cu durata *ae, inserarea acestuia intr-o celula
// pentru inserarea ulterioara in coada episoade a unui sezon
void* AlocEpisod(void* ae)
{
    TCelula* celula = malloc(sizeof(TCelula));
    TEpisod* episod = malloc(sizeof(TEpisod));
    if (!episod || !celula) return NULL;
    int i = *((int*)ae);
    episod->durata = i;
    celula->info = episod;
    celula->urm = NULL;
    return (void*)celula;
}


// inserarea unui sezon cu coada de episoade *ae intr-o celula
// pentru inserarea ulterioara in coada de sezoane a unui serial
void* AlocSezon(void* ae)
{
    TSezon* sezon = malloc(sizeof(TSezon));
    if (!sezon) return NULL;
    sezon->episoade = InitQ();
    ConcatQ(sezon->episoade, (TCoada*)ae);
    TCelula* celula = malloc(sizeof(TCelula));
    if (!celula) return NULL;
    celula->info = sezon;
    celula->urm = NULL;
    return (void*)celula;
}



// comparare rating si nume
int cmp(void* a, void* b)
{
    TSerial * x = (TSerial*)a;
    TSerial * y = (TSerial*)b;
    
    // pentru functia find din fctiiCerinta.c
    // compara doar numele
    if((x->rating == (double)0) || (y->rating == (double)0))
        return strcmp(y->nume, x->nume);


    // daca ratingul e egal, se compara alfabetic numele
    if(x->rating == y->rating)
        return strcmp(y->nume, x->nume); // obs. y - primul argument

    // intoarce diferenta de rating
    // *100 pentru comparare cu precizie destula
    return (x->rating - y->rating)*100;

}


// Insereaza totalitate datelor necesare pentru serial.
// Returneaza "campul info" a unui serial pentru inserare ulterioara in lista.
void* InsSer(void* nume, void* rating, void* dur_totala, void* c_sezoane)
{
    TSerial* serial = malloc(sizeof(TSerial));
    if (!serial) return NULL;
    serial->nume = calloc(strlen((char*)nume) + 1, sizeof(char));
    if (!serial->nume) return NULL;
    strcpy(serial->nume, (char*)nume); // inserare nume
    serial->rating = *((double *)rating); // inserare rating
    serial->durata_totala = *((int*)dur_totala); // inserare durata totala
    serial->durata_privita = 0; // seteaza durata privita la 0
    serial->sezoane = c_sezoane; // seteaza coada sezoane
    return serial;
}


// adaugua durata totala unui serial, in caz in care se adauga
// un sezon nou
void* serialUpdate(void* info, void* aSez, void* aDurata)
{
    TSerial* serial = (TSerial*)info;
    IntrQ(serial->sezoane, AlocSezon(aSez));
    int durata = *((int*)aDurata);
    serial->durata_totala += durata;
    return serial;
}


// functia de serviciu pentru "watch", adauga *durata la durata privita
// intoarce 1 daca duarata privita este mai mare sau egala decat durata
// totala a unui serial, altfel, intoarce 0
int watchUpdate(void* info, void* durata)
{
    TSerial* serial = (TSerial*)info;
    int d_durata = *((int*)durata);
    serial->durata_privita += d_durata;
    if (serial->durata_privita >= serial->durata_totala)
        return 1;
    return 0;
}


// afisare serial, nume si rating
void AfiSerial(void* ae, FILE* output)
{
    TSerial* serial = (TSerial*)ae;
    if(serial == NULL) return;
    fprintf(output, "(%s, %.1lf)", serial->nume, serial->rating);
}



// functie de distrugere a unui serial
void DistrSerial(void* ae)
{
    TSerial* serial = (TSerial*)ae;
    if (!serial) return;
    while (!VidaC(serial->sezoane))
    {
        TL aux = (TL)ExtrQ(serial->sezoane);
        free(aux->info);
        free(aux);
    }
    free(serial->sezoane);
    free(serial->nume);
    free(serial);

}


int main(int argc, char* argv[])
{
    // parsare argumente - nume de fisiere input si output
    FILE *in_file, *out_file;
    char* in = argv[1];
    char* out = argv[2];

    // initializare structuri pentru tema
    TL l1 = malloc(sizeof(TCelula));
    if (!l1) return 1;
    TL l2 = malloc(sizeof(TCelula));
    if (!l2)
    {
        free(l1);
        return 1;
    }
    
    TL l3 = malloc(sizeof(TCelula));
    if (!l3)
    {
        free(l1);
        free(l2);
        return 1;
    }
    TL l4 = malloc(sizeof(TCelula));
    if (!l4)
    {
        free(l1);
        free(l2);
        free(l3);
        return 1;
    }
    l1=l2=l3=l4=NULL;
    TCoada* watch_later = InitQ();
    if (!watch_later)
    {
        free(l1);
        free(l2);
        free(l3);
        free(l4);
        return 1;
    }
    TStiva currently_watching = InitS();
    if (!currently_watching)
    {
        free(l1);
        free(l2);
        free(l3);
        free(l4);
        DistrQ(&watch_later, free);
        return 1;
    }
    TStiva history = InitS();
    if (!history)
    {
        free(l1);
        free(l2);
        free(l3);
        free(l4);
        DistrQ(&watch_later, free);
        DistrS(&currently_watching, free);
        return 1;
    }
    // sfarsit initializare


    in_file = fopen(in, "r");
    out_file = fopen(out, "w");
    char *line = calloc(256, sizeof(char));
    char *aux_line = calloc(256, sizeof(char));
    char* token;
    while (fgets(line, 256, in_file)) // parurge fisierul linie cu linie
    {   
        
        line[strcspn(line, "\n")] = 0; // elimina \n de la sfarsit
        if (*line == 0) continue; // ignora linie vida
        strcpy(aux_line, line);
        token = strtok(line, " ");

        // apeluri functii cerinta
        if (!strcmp(token, "add"))
        {
            add(aux_line, AlocEpisod, AlocSezon, cmp, InsSer,
                &l1, &l2, &l3, out_file);
            continue;
        }
        
        if (!strcmp(token, "add_top"))
        {
            add_top(aux_line, &l4, AlocEpisod, AlocSezon,
                    InsSer, AfiSerial, out_file);
            continue;
        }

        if (!strcmp(token, "later"))
        {
            later(aux_line, watch_later, &l1, &l2, &l3, &l4,
                cmp, InsSer, out_file);
            continue;
        }

        if (!strcmp(token, "add_sez"))
        {
            add_sez(aux_line, &l1, &l2, &l3, &l4, watch_later,
                    currently_watching, cmp, AlocEpisod, serialUpdate,
                    InsSer,out_file);
            continue;
        }
        if (!strcmp(token, "watch"))
        {
            watch(aux_line, &l1, &l2, &l3, &l4, watch_later,currently_watching,
                history, cmp, watchUpdate, InsSer, out_file);
            continue;
        }
        if (!strcmp(token, "show"))
        {
            show(aux_line, AfiSerial, l1, l2, l3, l4, watch_later,
                currently_watching, history, out_file);
            continue;
        }

    }
    free(line);
    free(aux_line);
    fclose(in_file);
    fclose(out_file);

    DistrL(&l1, DistrSerial);
    DistrL(&l2, DistrSerial);
    DistrL(&l3, DistrSerial);
    DistrL(&l4, DistrSerial);
    DistrS(&currently_watching, DistrSerial);
    DistrS(&history, DistrSerial);
    DistrQ(&watch_later, DistrSerial);
    return 0;
}