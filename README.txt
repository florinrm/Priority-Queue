Tema 1 Sisteme de operare 2019
Nume: Mihalache Florin-Răzvan
Grupa: 336CB

Timp petrecut pentru implementare: 5 ore

Functii - documentație - modul de funcționare

1) struct priorityQueue * insert(struct priorityQueue *queue,
	                            char *element, int priority)
    Funcție prin care se adaugă un nou element în coadă, după prioritatea
acestuia.
    Mai întâi vedem dacă există deja coada în care vrem să adăugăm noul element,
dacă nu se returnează nodul din coadă cu elementul nou adăugat în coadă. Dacă
avem deja cel puțin un element în coadă, vedem dacă elementul ce trebuie adăugat
în coada are prioritatea mai mare decât capul cozii sau nu. Dacă da, legăm noul
element la capul cozii, devenind astfel noul cap al cozii cu priorități. Dacă nu,
parcurgem lista / coada până când dăm de un element care are prioritatea mai mică
decât elementul pe care vrem să îl adăugăm în coadă, astfel legăm elementul găsit
în coadă la elementul nou-adăugat și pe cel pe care îl inserăm în coadă îl legăm
la următorul element precedat de cel găsit în coadă (cel care care prioritatea mai
mică imediat după elementul ce trebuie înserat).

2) void pop(struct priorityQueue **queue)
    Funcție prin care este eliminat primul element din coadă, mutând astfel capul
cozii către al doilea element din coadă (dacă acesta există)

3) char *top(struct priorityQueue *queue)
    Funcție prin care este întoarsă valoarea primului element din coadă (dacă
coada nu este goală, altfel NULL este întors)

4) int size(struct priorityQueue *queue)
    Funcție care calculează mărimea cozii, prin iterarea prin lista înlănțuită
prin care este implementată coada.

5) void free_queue(struct priorityQueue *queue)
    Funcție prin care este eliberată memoria dinamică alocată pentru coadă și
pentru valorile stocate în coadă.