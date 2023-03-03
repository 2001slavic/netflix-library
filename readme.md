# Biblioteca Netflix
Proiect bazat pe operarea cu structuri de date in limbajul C.

## Cerinta
Sa se implementeze o *biblioteca Netflix* cu care se poate opera cu urmatoarele comenzi:
<details>
  <summary> Adăugare serial în baza de date
</summary>

  ```
  add <ID> <nume> <rating> <#sezoane> <#epSez1> <durataEp1> <durataEp2>...<#epSez2> <durtaEp1> <durataEp2>
  ```
  ***Mod de funcționare:*** Adaugă un serial nou în categoria 1<=ID<=3. Se va afișa mesajul:
  ```
  Serialul <nume> a fost adaugat la pozitia %d.\n
  ```

  ***Exemplu:***
  ```
  add 3 numeA 8.9 2 3 10 8 9 2 7 6
  ```
  *se cere adăugarea unui serial în categoria 3, rating 8.9, serialul are 2 sezoane, primul sezon are 3 episoade de câte 10, 8, 9
  minute, al doilea sezon are 2 episoade de câte 7, 6 minute*
  ```
  Serialul numeA a fost adaugat la pozitia 1.\n
  ```

</details>
<details>
  <summary>Adăugare sezon integral</summary>

  ```
  add_sez <nume> <#ep> <durataEp1> <durataEp2>
  ```
  ***Mod de funcționare:***  Adaugă un sezon nou pentru serialul cu numele nume. Se pot adăuga
sezoane pentru orice serial care nu se află deja în history. Se va afișa un mesaj de forma:
  ```
  Serialul <nume> are un sezon nou.\n
  ```

  ***Exemplu:***
  ```
  add_sez numeA 3 10 8 9
  ```
  *se cere adăugarea unui sezon de 3 episoade
pentru serialul numeA, episoadele au 10, 8, 9 minute*
  ```
  Serialul numeA are un sezon nou.\n
  ```

</details>
<details>
  <summary>Adăugare serial în Top10</summary>

  ```
  add_top <poz> <nume> <rating> <#sezoane> <#epSez1> <durataEp1> <durataEp2>...<#epSez2> <durataEp1> <durataEp2>
  ```
  ***Mod de funcționare:***  Adaugă un serial nou în categoria Top10. În Top10 vor fi păstrate
întotdeauna maxim 10 seriale. Serialele care au ieșit din Top10 nu vor mai reveni în top. Se
garantează că pozițiile din top sunt continue în momentul inserării. Se va afișa un mesaj de
forma:
  ```
  Categoria top10: [(<nume1>, <rating1>), (<nume2>, <rating2>)].\n
  ```

  ***Exemplu:***
  ```
  add_top 2 numeB 8.0 1 3 10 11 12
  ```
  *se cere adăugarea unui serial
în categoria top10, pe poziția 2, cu rating 8.0, serialul are 1 sezon cu 3 episoade de câte 10, 11,
12 minute (în top există deja un alt serial, care este primul)*
  ```
  Categoria top10: [(primul_in_top, 7.5), (numeB, 8.0)].\n
  ```

</details>
<details>
  <summary>Adăugare serial în watch_later</summary>

  ```
  later <nume>
  ```
  ***Mod de funcționare:***  Mută un serial din cele 4 categorii în coada watch_later. Se va afișa un
mesaj de forma:
  ```
  Serialul <nume> se afla in coada de asteptare pe pozitia %d.\n
  ```

  ***Exemplu:***
  ```
  later numeX
  ```
  *se cere mutarea serialului numeX în coada watch_later*
  ```
  Serialul numeX se afla in coada de asteptare pe pozitia 3.\n
  ```

</details>
<details>
  <summary>Vizionare serial</summary>

  ```
  watch <nume> <durata>
  ```
  ***Mod de funcționare:***  Mută un serial în stiva **currently_watching** dacă nu există deja, apoi
vizionează ``durata`` minute din serialul ``nume``. Dacă întreg serialul are mai puțin de ``durata``
minute de vizionat, acesta va fi vizionat integral. Se va cere vizionarea unui serial care nu se
află deja în ``history``. Mutarea unui serial din Top10 presupune actualizarea (decrementarea)
numărului de ordine pentru serialele aflate mai jos în top. Dacă serialul a fost vizionat integral,
se va afișa mesajul următor:
  ```
  Serialul <nume> a fost vizionat integral.\n
  ```

  ***Exemplu:***
  ```
  watch numeX 100
  ```
  *se cere vizionarea serialului numeX timp de maxim 100 de
minute*
</details>
<details>
  <summary>Afișare seriale</summary>

  ```
  show <X> ; X∈{ 1, 2, 3, top10, later, watching, history}
  ```
  ***Mod de funcționare:***  Afișează lista cu serialele din categoria X. Se va afișa un mesaj de forma:
  ```
  Categoria <X>: [(<numeA>, <rA>), (<numeB>, <rB>)].\n
  ```

  ***Exemplu:***
  ```
  show later
  ```
  *se cere afișarea serialelor din watch later*
  ```
  Categoria later: [(A, 9.7), (B, 8.5)].\n
  ```
  ***Exemplu:***
  ```
  show 1
  ```
  ```
  Categoria 1: [(A, 9.0), (B, 9.0)].
  ```

</details>

## Exemplu
| Intrare                             | Iesire                                                      |
|-------------------------------------|-------------------------------------------------------------|
| ``add 1 IR 4 2 3 3 1 19 1 10``      | ``Serialul IR a fost adaugat la pozitia 1.``                |
| ``show 1``                          | ``Categoria 1: [(IR, 4.0)].``                               |
| ``add_top 1 EB 2.8 2 2 16 15 1 18`` | ``Categoria top10: [(EB, 2.8)].``                           |
| ``later IR``                        | ``Serialul IR se afla in coada de asteptare pe pozitia 1.`` |
| ``show top10``                      | ``Categoria top10: [(EB, 2.8)].``                           |
| ``show later``                      | ``Categoria later: [(IR, 4.0)].``                           |
| ``add_sez EB 3 3 23 23``            | ``Serialul EB are un sezon nou.``                           |
| ``watch IR 38``                     | ``Serialul IR a fost vizionat integral.``                   |
| ``show later``                      | ``Categoria later: [].``                                    |
| ``show watching``                   | ``Categoria watching: [].``                                 |
| ``show history``                    | ``Categoria history: [(IR, 4.0)].``                         |
| ``watch EB 54``                     | ``Categoria 1: [].``                                        |
| ``show 1``                          | ``Categoria top10: [].``                                    |
| ``show top10``                      | ``Categoria watching: [(EB, 2.8)].``                        |
| ``show watching``                   | ``Categoria history: [(IR, 4.0)].``                         |
| ``show history``                    |                                                             |

## Rulare
```
./netflix <in_file> <out_file>
```
Comenzile se citesc din fișierul ``in_file``, iar rezultatele se scriu în fișierul ``out_file``.

## Testare

```
./check.sh
```

## Credits

Cerinta proiectului, testele si instrumentul de testare au fost date de echipa materiei *Structuri de date*,
din *Facultatea de Automatica si Calculatoare; Universitatea POLITEHNICA din Bucuresti* anul de studii 2020-2021.

Mai 2021