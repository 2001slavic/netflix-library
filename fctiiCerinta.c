/* CAZANOV Veaceslav - 312CB */

#include "fctiiCerinta.h"

void add(char* line, TFAloc fEp, TFAloc fSez, TFCmp cmp, TFInsInfo InsSer,
        TL* l1, TL* l2, TL* l3, FILE* output) // functie "add" - cerinta
{
    char* token;
    token = strtok(line, " "); // ignora comanda "add"
    token = strtok(NULL, " ");
    int id = atoi(token); // memoreaza id
    token = strtok(NULL, " ");
    char* nume = calloc(33, sizeof(char)); // lungimea max = 32, +1 pentru \0
    strcpy(nume, token); // memoreaza nume
    token = strtok(NULL, " ");
    double rating = atof(token); // memoreaza rating
    token = strtok(NULL, " ");
    int nr_sezoane = atoi(token); // numar de sezoane
    TL *tmp, ant;
    switch (id) // seteaza pe tmp adresa listei (categoriei),
    {           // in care se solicita inserarea unui serial
    case 1:
        tmp = l1;
        break;
    case 2:
        tmp = l2;
        break;
    case 3:
        tmp = l3;
        break;
    }
    TCoada* c_sez; // declarare coada pentru 1 sezon
    TCoada* c_ser = InitQ(); // initializare coada serial (multime de sezoane)
    int i, j, nr_episoade, ep_curent; // i, j pentru for-uri,
                                // nr_episoade, durata unui episod (ep_curent)

    int dur_totala = 0; // durata totala a serialului
    for (i = 1; i <= nr_sezoane; i++)
    {
        token = strtok(NULL, " ");
        nr_episoade = atoi(token); // citire numar de episoade intr-un serial
        c_sez = InitQ(); // initializare coada pentru un sezon
        for (j = 1; j <= nr_episoade; j++)
        {
            token = strtok(NULL, " ");
            ep_curent = atoi(token); // citire durata episoade
                                     // pentru sezonul curent (i)
            dur_totala += ep_curent; // memorare durata totala serial
            TL aux;
            aux = fEp(&ep_curent); // alocare episod si celula aferenta
                                   // acestuia, fEp - void* AlocEpisod(void* ae)
            IntrQ(c_sez, aux); // introduce celula de episod in coada sezonului
        }
        TL aux;
        aux = fSez(c_sez); // alocare sezon si celula aferenta
                           // fSez - void* AlocEpisod(void* ae) din tema2.c
        IntrQ(c_ser, aux); // introducere celula cu sezon in coada serial
    }
    void * serial = InsSer(nume, &rating, &dur_totala, c_ser);
    // pregatire camp info pentru inserare in celula (serial)
    // InsSer - void* InsSer din tema2.c
    TL tmp_aux = *tmp; // variabila temporara auxiliara pentru
                       // a nu modifica inceputul listei tmp
    ant = NULL;

    // parcurgere lista cu seriale existente
    for (i = 0; tmp_aux != NULL; tmp_aux = tmp_aux->urm, i++)
    { // cautare pozitite pentru inserare

        // s-a gasit serial cu rating mai mic, sau nume alfabetic inferior
        if (cmp(tmp_aux->info, serial) < 0)
        {

            // inserare la inceputul listei
            if (!ant)
            {
                InsHead(tmp, serial);
                fprintf(output, "Serialul %s a fost adaugat la pozitia 1.\n", nume);
                free(nume);
                return;
            }

            // inserare in interiorul listei
            InsDupa(ant,serial); // inserare dupa anteriorul celulei cautate,
                                 // astfel, inserare inaintea celulei cautate.
            fprintf(output, "Serialul %s a fost adaugat la pozitia %d.\n", nume, i+1);
            free(nume);
            return;
        }
        // setare anterior celula
        ant=tmp_aux;
    }

    // nu s-a gasit element in fata caruia se poate de inserat,
    // trecem la inserare la sfarist de lista.

    // daca lista vida
    if (!ant)
    {
        InsHead(tmp,serial);
        fprintf(output, "Serialul %s a fost adaugat la pozitia 1.\n", nume);
        free(nume);
        return;
    }

    // inserare la sfarsit de lista
    InsDupa(ant, serial);
    ant->urm->urm = NULL;
    fprintf(output, "Serialul %s a fost adaugat la pozitia %zu.\n", nume, nrElementeL(tmp));
    free(nume);
    return;
    

}

void add_top(char* line, TL* l4, TFAloc fEp, TFAloc fSez, TFInsInfo InsSer,
            TFAfi fAfi, FILE* output)
{
    char* token = strtok(line, " "); // ignora comanda "add_top"
    token = strtok(NULL, " ");
    int pos = atoi(token); // memoreaza pozitia pe care trebue inserat
    token = strtok(NULL, " ");
    char* nume = calloc(33, sizeof(char)); // lungimea max = 32, +1 pentru \0
    strcpy(nume, token); // nume
    token = strtok(NULL, " ");
    double rating = atof(token); // rating
    token = strtok(NULL, " ");
    int nr_sezoane = atoi(token); // nr sezoane
    TL* tmp = l4, tmp_aux=*l4;
    TCoada *c_sez;
    TCoada* c_ser = InitQ();
    int dur_totala = 0;
    int i, j, nr_episoade, ep_curent;
    for (i = 1; i <= nr_sezoane; i++)
    {
        token = strtok(NULL, " ");
        nr_episoade = atoi(token);
        c_sez = InitQ();
        for (j = 1; j <= nr_episoade; j++)
        {
            token = strtok(NULL, " ");
            ep_curent = atoi(token);
            dur_totala += ep_curent;
            IntrQ(c_sez, fEp(&ep_curent));
        }
        IntrQ(c_ser, fSez(c_sez));
    }
    // pregatire camp info
    void* serial = InsSer(nume, &rating, &dur_totala, c_ser);
    int count = 1;

    // inserare in top10
    if (pos == 1) // inserare pe pozitia 1
    {
        InsHead(tmp, serial);
    }
    else
    {
        // parcurge lista si numara pozitia de inserare
        for (; tmp_aux != NULL; tmp_aux = (tmp_aux)->urm, count++)
        {
            if(count == pos - 1) //(de ce pos - 1?) ca sa insereze dupa anterior 
            {
                InsDupa(tmp_aux, serial);
                break;
            }
        }
    }

    // daca numarul de elemente in lista trece de 10, atunci elimina ultimul
    if (nrElementeL(tmp) > 10)
    {
        for (tmp_aux = *l4, count = 1; count < 10; count++)
        {
            tmp_aux = (tmp_aux)->urm;
        }
        tmp_aux->urm = NULL;
    }

    // afisare conform conditiei
    fprintf(output, "Categoria top10: [");
    AfiLista(*l4, fAfi, output);
    free(nume);

}

TL find(TL *l1, TL *l2, TL *l3, TL *l4, void* nume, TFCmp fcmp,
        TFInsInfo InsSer, TL * celula, int* first, int* lista)
{

    // necesar pentru compararea ulterioara a numelui
    double x = 0;
    int y = 0;
    void* serial = InsSer(nume, &x, &y, NULL);

    TL* tmp = l1;
    TL ant = NULL;
    // parcurgere lista 1
    for (; *tmp !=NULL; ant = *tmp, tmp = &((*tmp)->urm))
    {
        if (!fcmp(serial, (*tmp)->info))
        {
            // daca s-a gasit serial cu numele cautat
            *celula = *tmp;
            if(ant == NULL)
            {
                // daca elementul gasit e primul din lista
                *lista = 1;
                *first = 1;
            }
            return ant;
        }
    }
    // daca nu s-a gasit in lista 1, caut in urmatoarea
    tmp = l2;
    ant = NULL;
    for (; *tmp !=NULL ; ant = *tmp, tmp = &((*tmp)->urm))
    {   
        if (!fcmp(serial, (*tmp)->info))
        {
            // daca s-a gaist element
            *celula = *tmp;
            if(ant == NULL)
            {
                // daca elementul gasit e primul din lista
                *lista = 2;
                *first = 1;
            }
            return ant;
        }
    }
    // si asa mai departe
    tmp = l3;
    ant = NULL;
    for (; *tmp !=NULL ; ant = *tmp, tmp = &((*tmp)->urm))
    {
        if (!fcmp(serial, (*tmp)->info))
        {
            *celula = *tmp;
            if(ant == NULL)
            {
                *lista = 3;
                *first = 1;
            }
            return ant;
        }
    }
    tmp = l4;
    ant = NULL;
    for (; *tmp !=NULL; ant = *tmp, tmp = &((*tmp)->urm))
    {   
        if (!fcmp(serial, (*tmp)->info))
        {
            *celula = *tmp;
            if(ant == NULL)
            {
                *lista = 4;
                *first = 1;
            }
            return ant;
        }
    }
    
    return NULL;
}

void later(char* line, TCoada* watch_later, TL *l1, TL *l2, TL *l3, TL *l4,
            TFCmp fcmp, TFInsInfo InsSer, FILE* output)
{
    char* token;
    token = strtok(line, " "); // ignora comanda
    token = strtok(NULL, " ");
    char* nume = calloc(33, sizeof(char));
    strcpy(nume, token);
    TL celula = NULL;
    int first = -1;
    int lista = -1;
    // aux e anteriorul celulei cautate (vezi README find())
    TL aux = find(l1, l2, l3, l4, nume, fcmp, InsSer, &celula, &first, &lista);
    if (!celula)
    {
        free(nume);
        return;
    }

    // daca elementul gasit e primul si e nevoie de actualizare head
    // pentru lista initiala
    if (first == 1)
    {
        if (lista == 1) 
            eliminaCelula(aux, l1);
        if (lista == 2) 
            eliminaCelula(aux, l2);
        if (lista == 3) 
            eliminaCelula(aux, l3);
        if (lista == 4) 
            eliminaCelula(aux, l4);
    }
    else
        eliminaCelula(aux, &celula);

    celula->urm = NULL;
    IntrQ(watch_later, celula); // inserare celula in coada watch_later

    // afisare conform conditiei
    fprintf(output, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", nume, watch_later->count);
    free(nume);
}

void add_sez(char* line, TL* l1, TL* l2, TL* l3, TL* l4, TCoada* watch_later,
                TStiva currently_watching, TFCmp fcmp, TFAloc fEp, TFUpdSer fSez,
                TFInsInfo InsSer, FILE* output)
{
    char* token;
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    char* nume = calloc(33, sizeof(char));
    strcpy(nume, token);
    double x = 0;
    int y = 0;
    // pentru comparare in findC() si findS()
    void* serial = InsSer(nume, &x, &y, NULL);

    TL celula = NULL;
    int first = -1, lista = -1;
    find(l1, l2, l3, l4, nume, fcmp, InsSer, &celula, &first, &lista);
    if (celula == NULL)
    {
        // functie de cautare in coada
        celula = findC(watch_later, serial, fcmp); 
        if (celula == NULL)
        {
            // functie de cautare in stiva
            celula = findS(currently_watching, serial, fcmp);
        }
    }
    if(!celula)
    {
        free(nume);
        return;
    }

    // construire coada sezon, similar ca la add() si add_top()
    token = strtok(NULL, " ");
    int nr_episoade = atoi(token);
    TCoada* c_sez = InitQ();
    int i, ep_current;
    int durata_totala_ad = 0;
    for (i = 1; i <= nr_episoade; i++)
    {
        token = strtok(NULL, " ");
        ep_current = atoi(token);
        durata_totala_ad += ep_current;
        IntrQ(c_sez, fEp(&ep_current));
    }
    // functie de actualizare serial - serialUpdate() din tema2.c
    fSez(celula->info, c_sez, &durata_totala_ad);


    fprintf(output, "Serialul %s are un sezon nou.\n", nume);
    free(nume);
}

void watch(char* line, TL* l1, TL* l2, TL* l3, TL* l4,
            TCoada* watch_later, TStiva currently_watching,
            TStiva history, TFCmp fcmp, TFCmp fDurata,
            TFInsInfo InsSer, FILE* output)
{
    char* token = strtok(line, " ");
    token = strtok(NULL, " ");
    char* nume = calloc(33, sizeof(char));
    strcpy(nume, token);
    double x = 0;
    int y = 0;
    void *serial = InsSer(nume, &x, &y, NULL);
    token = strtok(NULL, " ");
    int durata = atoi(token);
    int where = 0;
    int first = -1, lista = -1;
    TL celula = NULL;
    TL aux = find(l1, l2, l3, l4, nume, fcmp, InsSer, &celula, &first, &lista);

    if (celula == NULL)
    {
        // functie de cautare in coada, cu eliminare
        celula = findEliminaC(watch_later, serial, fcmp);
        where = 1;
        if (celula == NULL)
        {
            // functie de cautare in stiva cu eliminare
            celula = findEliminaS(currently_watching, serial, fcmp);
            where = 2;
        }
    }
    switch (where)
    {
    case 0: // daca s-a gasit element in LISTA
        if (fDurata(celula->info, &durata)) // watchUpdate() din tema2.c
        {
            // daca s-a vizionat serialul integral
            fprintf(output, "Serialul %s a fost vizionat integral.\n", nume);
            
            // eliminare din lista initiala
            if(first == 1)
            {
                // daca e primul element
                if (lista == 1) eliminaCelula(aux, l1);
                if (lista == 2) eliminaCelula(aux, l2);
                if (lista == 3) eliminaCelula(aux, l3);
                if (lista == 4) eliminaCelula(aux, l4);
            }
            else eliminaCelula(aux, &celula);
            Push(history, celula); // push in history
        }
        else // daca NU s-a vizionat serialul integral
        {
            // eliminare din lista initiala
            if(first == 1)
            {
                // daca e primul element
                if (lista == 1) eliminaCelula(aux, l1);
                if (lista == 2) eliminaCelula(aux, l2);
                if (lista == 3) eliminaCelula(aux, l3);
                if (lista == 4) eliminaCelula(aux, l4);
            }
            // daca nu e nevoie de refacere head lista
            else eliminaCelula(aux, &celula);

            Push(currently_watching, celula); // push in watching
        }
        break;
    
    case 1: // daca s-a gasit element in COADA
        if (fDurata(celula->info, &durata)) // watchUpdate() din tema2.c
        {
            fprintf(output, "Serialul %s a fost vizionat integral.\n", nume);
            Push(history, celula); // push in history
            // s-a eliminat de la findElimina
        }
        else
        {
            Push(currently_watching, celula); // push in watching
        }
        break;
    case 2: // daca s-a gasit in STIVA
        if (fDurata(celula->info, &durata))
        {
            fprintf(output, "Serialul %s a fost vizionat integral.\n", nume);
            Push(history, celula);
        }
        else
        {
            Push(currently_watching, celula);
        }
    }
}

void show(char* line, TFAfi f, TL l1, TL l2, TL l3, TL l4,
            TCoada* watch_later, TStiva currently_watching,
            TStiva history, FILE* output)
{
    char* token = strtok(line, " ");
    token = strtok(NULL, " ");
    char* cat = calloc(9, sizeof(char)); // max lungime comanda +1
    strcpy(cat, token);
    if (!strcmp(cat, "1"))
    {
        fprintf(output, "Categoria 1: [");
        AfiLista(l1, f, output);
    }
    if (!strcmp(cat, "2"))
    {
        fprintf(output, "Categoria 2: [");
        AfiLista(l2, f, output);
    }
    if (!strcmp(cat, "3"))
    {
        fprintf(output, "Categoria 3: [");
        AfiLista(l3, f, output);
    }
    if (!strcmp(cat, "top10"))
    {
        fprintf(output, "Categoria top10: [");
        AfiLista(l4, f, output);
    }
    if (!strcmp(cat, "later"))
    {
        fprintf(output, "Categoria later: [");
        AfiC(watch_later, f, output);
    }
    if (!strcmp(cat, "watching"))
    {
        fprintf(output, "Categoria watching: [");
        AfiS(currently_watching, f, output);
    }
    if (!strcmp(cat, "history"))
    {
        fprintf(output, "Categoria history: [");
        AfiS(history, f, output);
    }

}


