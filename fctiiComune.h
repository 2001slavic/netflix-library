/* CAZANOV Veaceslav - 312CB */

/* Tipuri de functii care au utilizare multipla, pentru functii stive, cozi. */

#ifndef _FUNCTII_COMUNE_
#define _FUNCTII_COMUNE_

typedef int (*TFCmp)(void*, void*); // comparare/actualizare durata
typedef void (*TFAfi)(void*, FILE*); // afisare
typedef void (*TFDistr)(void*); // distrugere
#endif