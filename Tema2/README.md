// Copyright Oprisan Alexia-Ioana 314CAb 2023-2024

Tema #2 - Simulator de Octave

Pentru realizarea codului am folosit o matrice tridimensionala (tablou) si
2 vectori in care am retinut pentru fiecare matrice dimensiunile ei
(linie[] si coloana[]).
Am alocat acesti vecori dinamic, urmarand sa-i realoc daca este cazul.
numar_matrice reprezinta cate matrice pot fi incluse in tablou, modificandu-se
in cazul realocarilor.
index_matrice reprezinta indexul fiecarei matrice din tablou.

Am citit litera si am utilizat instructiunea switch pentru a determina fiecare
caz.

Încărcarea în memorie a unei matrice
(case 'L')
Am inceput prin a verifica daca este nevoie de realocarea vectorului
tridimensional si a vectorilor auxiliari, in cazul in care index_matrice va
depasi numar_matrice (numarul de matrice citite depaseste numarul de matrice
alocate in tablou).
Prin functia adaugare_matrice am citit dimensiunile matricei si am adaugat
noua matrice la sfarsitul tabloului, dupa ce i-am alocat spatiu prin functia
alloc_matrix. Am retinut dimensiunile matricei in vectorii linie[], coloana[].

Determinarea dimensiunilor unei matrice
(case 'D')
Am citit indexul matricei si m-am ajutat de vecorii linie[] si coloana[]
in care am retinut dimensiunile matricei.

Afisarea unei matrice
(case 'P')
Am citit indexul matricei si am afisat matricea din tablou corespunzatoare
indexului, utilizand functia print_matrix.

Redimensionarea unei matrice
(case 'C')
Am citit numarul de linii, indicii liniilor, numarul de coloane si indicii
coloanelor. Indicii i-am retinut in 2 vectori (index_linii[], index_coloane[]),
alocati dinamic. Am alocat spatiu pentru o matrice auxiliara, in care am
construit matricea redimensionata.
Pentru a adauga matricea auxiliara in locul celei initiale, am eliberat-o
mai intai pe cea initiala. Am schimbat ulterior si dimensiunile acesteia
cu cele ale matricei redimensionate.

Înmultirea a două matrice
(case 'M')
Am citit indecsii matricelor ce vor fi inmultite. In cazul in care era nevoie,
am realocat tabloul si vectorii de dimensiuni, pentru a putea adauga noua
matrice la final. In functie_task_M am alocat spatiu pentru noua matrice
si am calculat produsul celor doua matrice, verificand daca valorile
elementelor respecta incadrarea in modulo 10^4 + 7. In final, am adaugat
noile dimensiuni in vectorii linie[] si coloana[].

Sortarea matricelor
(case 'O')
Am declarat doi vectori auxiliari (suma[] si pozitie[]), pe care i-am alocat
dinamic. Am calculat sumele elementelor fiecarei matrice, pe care le-am
introdus in vectorul suma[], pe pozitiile corespunzatoare. Cand am efectuat
sortarea cresacatoare a sumelor, in functia schimbare_matrice_tablou, am sortat
si pozitiile initiale ale matricelor si matricele din tablou. In final,
am schimbat si dimensiunile din vectorii linie[] si coloana[] pentru a
corespunde cu noul aranjament al matricilor. Am eliberat toti vectorii
auxiliari declarati.

Transpunerea unei matrice
(case 'T')
Am citit indexul matricei ce va fi transpusa si alocat spatiu pentru o matrice
in care voi calcula transpusa (transpusa). Am efectuat calcularea transpusei
si am eliberat matricea initiala, alocand iar spatiu dupa noile dimensiuni
(numarul de linii si coloane a fost inversat). Am adaugat in tablou transpusa
calculata si am eliberat matricea auxiliara.

Ridicarea unei matrice la o putere în timp logaritmic
(case 'R')
Am citit indexul matricei si puterea, verificand conditiile efectuarii
operatiei. Am alocat dinamic o matrice (rezultat[]), in care va fi
matricea ridicata la putere.
Functia ridicare_putere_log este o functie recursiva, ce are la baza doua
cazuri: puterea este para sau puterea este impara. In cazul in care puterea
este para, calculam recuriv matricea la puterea/2, ajutandu-ne de functia
inmultire_matrice, ce inmulteste doua matrici patratice. In cazul in care
puterea este impara, apelam functia pentru a calcula recursiv matricea la
(putereaa-1)/2, efectuand calculele ramase. Rezultatul se calculeaza
inmultind matricea cu matricea auxiliara obtinuta. Recursivitatea se opreste
cand puterea este 0, orice matrice ridicata la puterea 0 fiind matricea
unitate.
Am eliberat matricele auxiliare folosite si am adaugat rezultatul obtinut
in tablou, in locul matricei initiale.

Eliberarea memoriei unei matrice
(case 'F')
Am citit indexul matricei ce va fi eliberata si in functia
functie_task_F am eliberat matricea. Prin functia schimbare_parametri,
am adus fiecare matrice pe pozitia inferioara si am facut schimbarile
necesare in vectorii de dimensiuni. Am scazut index_matrice, deoarece am
eliminat o matrice si am verificat daca este nevoie sa realoc tabloul,
avand mai putine elemente pentru a ocupa mai putin spatiu.

Eliberarea tuturor resurselor
(case 'Q')
Am eliberat tabloul (vectorul de matrici) prin functia free_tablou.
Am aliberat vectorii linie[] si coloana[].

Alte situatii
(default)
Am afisat mesajul cerut.

Înmultirea matricelor folosind algoritmul lui Strassen
(case 'S')
Am citit indecsii matricilor ce vor fi inmultite si am facut verificarile
necesare. Am realocat tabloul in cazul depasirii limitei de matrici,
deoarece matricea rezultata va fi adaugata la finalul acestuia. Am
alocat dinamic matricea in care va fi calculat rezultatul (rezultat).
Am aplicat algoritmul lui Strassen in functia strassen, unde am
alocat spatiu pentru matricile auxiliare ce vor fi folosite.
Mai intai, am calculat matricile ce vor reprezenta blocurile in care
sunt impartite matricile initiale. Am calculcat sumele cerute de algoritm,
in functia sume_auxiliare, urmand sa calculez produsele necesare. Functia este
recursiva, produsele fiind calculate prin intermadiul ei. Produsele obtinute
in matricile M(1-7), au ajutat la calcularea matricilor C(1-4).
Matricile C au fost unite pentru a crea matricea rezultat. 
Conditia de oprirea a recursivitatii este obtinerea de matrici de dimensiune 1,
ce sunt numere, usor de inmultit, ce nu au nevoie de aplicarea algoritmului.
Am eliberat toate matricele auxiliare si am introdus in tablou rezultatul.
Am introdus si in vectorii dimensiuni (linie[] si coloana[]) dimensiunile
matricei calculate.
