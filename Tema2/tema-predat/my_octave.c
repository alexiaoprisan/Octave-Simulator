// Copyright Oprisan Alexia-Ioana 314CAb 2023-2024
#include <stdio.h>
#include <stdlib.h>

int **alloc_matrix(int m, int n) // aloca spatiu pentru o matrice
{
	int **a = (int **)malloc(m * sizeof(int *)); // aloca matricea
	if (!a) {
		fprintf(stderr, "malloc() failed");
		return NULL;
	}

	for (int i = 0; i < m; i++) { // aloca fiecare linie - m
		a[i] = (int *)malloc(n * sizeof(int));
		if (!a[i]) { // programare defensiva
			fprintf(stderr, "malloc() failed");
			while (--i >= 0)
				free(a[i]);
			free(a);
			return NULL;
		}
	}
	return a;
}

int *realocare_vector(int numar_matrice, int *v) // realoca un vector
{
	int *tmp = (int *)realloc(v, numar_matrice * sizeof(int));
	if (!tmp) { // programare defensiva
		fprintf(stderr, "realloc()failed\n");
		free(v);
		return NULL;
	}
	return tmp;
}

/* functie pentru realocarea tabloului (vector de matrice) si a
vectorilor ce retin numarul de linii si coloane ale fiecarei matrici */
void realocare(int *numar_matrice, int **linie, int **coloana,
			   int ****tablou, int index_matrice)
{
	if (index_matrice == *numar_matrice - 1) { // conditia de realocare
		*numar_matrice = *numar_matrice * 2;
		*tablou = (int ***)realloc(*tablou,
								   *numar_matrice * sizeof(int **));
		*linie = realocare_vector(*numar_matrice, *linie);
		*coloana = realocare_vector(*numar_matrice, *coloana);
	}
}

/* functie ce aloca mai putin spatiu in tablou si in vectorii ce retin
numarul de linii si coloane in cazul eliberarii unei matrici */
void realocare_minus(int index_matrice, int *numar_matrice,
					 int **linie, int **coloana, int ****tablou)
{
	if (index_matrice < *numar_matrice / 2) { // conditia de realocare
		*numar_matrice = *numar_matrice / 2;
		*tablou = (int ***)realloc(*tablou, *numar_matrice * sizeof(int **));
		*linie = realocare_vector(*numar_matrice, *linie);
		*coloana = realocare_vector(*numar_matrice, *coloana);
	}
}

void swap(int *a, int *b) // interschimba valorile a doua variabile
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void read_matrix(int m, int n, int **matrice) // citirea unei matrice
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &matrice[i][j]);
	}
}

void print_matrix(int index_matrice, int m, int n, int ***tablou)
{ // afisarea matricei din tablou de pe pozitia index_matrice
	for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", tablou[index_matrice][i][j]);
		printf("\n");
	}
	for (int j = 0; j < n; j++)
		printf("%d ", tablou[index_matrice][m - 1][j]);
}

void schimbare_parametri(int *linie, int *coloana,
						 int ***tablou, int index_matrice, int index)
{ // aduce fiecare matrice pe pozitia inferioara si face schimbarile necesare
	for (int i = index; i < index_matrice - 1; i++) {
		tablou[i] = tablou[i + 1];
		linie[i] = linie[i + 1];
		coloana[i] = coloana[i + 1];
	}
}

void verificare_valori(int **produs, int m1, int n2)
{ // verifica incadrarea valorilor in modulo 10^4 + 7
	int i, j;
	for (i = 0; i < m1; i++) {
		for (j = 0; j < n2; j++) {
			if (produs[i][j] >= 0)
				produs[i][j] = produs[i][j] % 10007;
			else
				produs[i][j] = produs[i][j] % 10007 + 10007;
		}
	}
}

void creare_vectori(int *suma, int *pozitie, int index_matrice)
{ // functie pentru crearea vectorilor necesari in sortarea matricelor
	int i;
	for (i = 0; i < index_matrice; i++)
		suma[i] = 0; // va retine sumele elementelor din fiecare matrice
	for (i = 0; i < index_matrice; i++)
		pozitie[i] = i; // retine pozitiile initiale, urmand sa fie schimbate
}

void suma_matrice(int index_matrice, int *suma,
				  int *linie, int *coloana, int ***tablou)
{ // calculeaza sumele elementelor fiecarei matrice din tablou
	int contor, j, k;
	for (contor = 0; contor < index_matrice; contor++) {
		for (j = 0; j < linie[contor]; j++) {
			for (k = 0; k < coloana[contor]; k++)
				suma[contor] = suma[contor] + tablou[contor][j][k];
		} // sumele sunt retinute in vectorul 'suma'
	}
}

void verificare_valori_sume(int index_matrice, int *suma)
{ // verifica incadrarea valorilor sumelor in modulo 10^4 + 7
	int contor;
	for (contor = 0; contor < index_matrice; contor++) {
		if (suma[contor] >= 0)
			suma[contor] = suma[contor] % 10007;
		else
			suma[contor] = suma[contor] % 10007 + 10007;
	}
}

void schimbare_matrice_tablou(int index_matrice, int *suma,
							  int *pozitie, int ***tablou)
{ // ordoneaza matricile in tablou in functie de suma elementelor
	int **aux;
	for (int i = 0; i < index_matrice - 1; ++i) {
		for (int j = 0; j < index_matrice - i - 1; ++j) {
			if (suma[j] > suma[j + 1]) {
				swap(&pozitie[j], &pozitie[j + 1]);
				swap(&suma[j], &suma[j + 1]);
				aux = tablou[j];
				tablou[j] = tablou[j + 1];
				tablou[j + 1] = aux;
			}
		}
	}
}

void free_matrix(int n, int **a) // elibereaza o matrice
{
	for (int i = 0; i < n; i++) {
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
}

void inmultire_matrice(int **matrice1, int **matrice2, int **rezultat, int n)
{ // functie care inmulteste 2 matrici cu dimensiuni egale
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			rezultat[i][j] = 0;
			for (k = 0; k < n; k++)
				rezultat[i][j] += matrice1[i][k] * matrice2[k][j];
		}
	}
	verificare_valori(rezultat, n, n);
}

void ridicare_putere_log(int index, int dimensiune,
						 int **matrice, int putere, int **rezultat)
{ // functie recursiva pentru ridicarea la o putere in timp logaritmic
	int **matrice_aux = alloc_matrix(dimensiune, dimensiune);
	if (putere == 0) { // conditia de oprire
		for (int i = 0; i < dimensiune; i++) {
			for (int j = 0; j < dimensiune; j++) {
				rezultat[i][j] = 0;
				if (i == j)
					rezultat[i][j] = 1;
			}
		} // crearea matricei unitate
		verificare_valori(rezultat, dimensiune, dimensiune);
	} else if (putere % 2 == 0) { // in cazul unei puteri pare
		ridicare_putere_log(index, dimensiune, matrice,
							putere / 2, matrice_aux);
		inmultire_matrice(matrice_aux, matrice_aux, rezultat, dimensiune);
	} else { // in cazul unei puteri impare
		int **matrice_aux1 = alloc_matrix(dimensiune, dimensiune);
		int **matrice_aux2 = alloc_matrix(dimensiune, dimensiune);

		ridicare_putere_log(index, dimensiune, matrice,
							((putere - 1) / 2), matrice_aux1);
		inmultire_matrice(matrice_aux1, matrice_aux1, matrice_aux2, dimensiune);
		inmultire_matrice(matrice, matrice_aux2, rezultat, dimensiune);
		// eliberarea matricelor auxiliare
		free_matrix(dimensiune, matrice_aux1);
		free_matrix(dimensiune, matrice_aux2);
	}
	free_matrix(dimensiune, matrice_aux);
}

void adaugare_matrice(int ***tablou, int *linie,
					  int *coloana, int index_matrice)
{ // adauga o matrice la sfarsitul tabloului de matrici
	int m, n;
	scanf("%d%d", &m, &n); // citirea dimensiunilor unei matrice
	tablou[index_matrice] = alloc_matrix(m, n); // alocarea spatiului matricei
	read_matrix(m, n, tablou[index_matrice]); // citirea matricei
	linie[index_matrice] = m; // retinerea numarului de linii in vector
	coloana[index_matrice] = n; // retinerea numarului de coloane in vector
}

void functie_task_D(int index_matrice, int *linie, int *coloana)
{
	int index1;
	scanf("%d", &index1);
	if (index1 < index_matrice && index1 >= 0) { // conditiile necesare
		printf("%d ", linie[index1]); // afisarea numarului de linii
		printf("%d", coloana[index1]);// afisarea numarului de coloane
	} else {
		printf("No matrix with the given index");
	}
	printf("\n");
}

void functie_task_P(int index_matrice, int *linie, int *coloana, int ***tablou)
{
	int index2;
	scanf("%d", &index2); // citirea indexului matricei ce va fi afisata
	if (index2 < index_matrice && index2 >= 0) { // conditiile necesare
		print_matrix(index2, linie[index2], coloana[index2], tablou);
		printf("\n");
	} else {
		printf("No matrix with the given index\n");
	}
}

void functie_task_C(int index_matrice, int *linie, int *coloana, int ***tablou)
{
	int index, nr_linii, nr_coloane, i, j;
	scanf("%d", &index); // citirea indexului matricei ce va fi redimensionata
	scanf("%d", &nr_linii); // citirea numarului de linii
	// alocarea vectorului ce va retine indicii de linii
	int *index_linii = (int *)malloc(nr_linii * sizeof(int));
	for (i = 0; i < nr_linii; i++)
		scanf("%d", &index_linii[i]); // citirea indicilor liniilor
	scanf("%d", &nr_coloane); // citirea numarului de coloane
	int *index_coloane = (int *)malloc(nr_coloane * sizeof(int));
	// alocarea vectorului ce va retine indicii de coloane
	for (i = 0; i < nr_coloane; i++)
		scanf("%d", &index_coloane[i]); // citirea indicilor coloanelor
	if (index < index_matrice && index >= 0) {
		// construirea unei matrice auxiliare cu liniile si colanele cerute
		int **matrice = alloc_matrix(nr_linii, nr_coloane);
		for (i = 0; i < nr_linii; i++) {
			for (j = 0; j < nr_coloane; j++)
				matrice[i][j] = tablou[index][index_linii[i]][index_coloane[j]];
		}
		// eliberarea matricei initiale ce trebuie redimensionata
		free_matrix(linie[index], tablou[index]);
		// schimbarea numarului de linii dupa redimensionare
		linie[index] = nr_linii;
		// schimbarea numarului de coloane dupa redimensionare
		coloana[index] = nr_coloane;
		// adaugarea matricei auxiliare in locul celei initiale
		tablou[index] = matrice;
	} else {
		printf("No matrix with the given index\n");
	}
	free(index_coloane); // eliberarea vectorilor auxiliari
	free(index_linii);
}

void functie_task_M(int index_matrice, int index1, int index2,
					int *linie, int *coloana, int ***tablou)
{
	int m1, n1, n2;
	// retinerea dimensiunilor matricelor utilizate
	m1 = linie[index1];
	n1 = coloana[index1];
	n2 = coloana[index2];
	// alocarea matricei ce va fi adaugata la sfarsitul tabloului
	tablou[index_matrice] = alloc_matrix(m1, n2);
	int i, j, k;
	for (i = 0; i < m1; i++) { // inmultirea matricilor
		for (j = 0; j < n2; j++) {
			tablou[index_matrice][i][j] = 0;
			for (k = 0; k < n1; k++) {
				tablou[index_matrice][i][j] = (tablou[index_matrice][i][j]
				+ tablou[index1][i][k] * tablou[index2][k][j]) % 10007;
				if (tablou[index_matrice][i][j] < 0)
					tablou[index_matrice][i][j] = tablou[index_matrice][i][j]
					+ 10007;
			}
		}
	}
	// adaugarea dimensiunilor pentru matricea adaugata la sfarsitul tabloului
	linie[index_matrice] = m1;
	coloana[index_matrice] = n2;
}

void functie_task_O(int index_matrice, int numar_matrice,
					int *linie, int *coloana, int ***tablou)
{
	int i;
	int *suma = (int *)malloc(index_matrice * sizeof(int));
	// vector ce va retine sumele elementelor din fiecare matrice
	int *pozitie = (int *)malloc(index_matrice * sizeof(int));
	// vector ce retine pozitiile fiecarei matrice inainte si dupa sortare
	creare_vectori(suma, pozitie, index_matrice);
	suma_matrice(index_matrice, suma, linie, coloana, tablou);
	verificare_valori_sume(index_matrice, suma);
	schimbare_matrice_tablou(index_matrice, suma, pozitie, tablou);
	int *copie_linie = (int *)malloc(numar_matrice * sizeof(int));
	int *copie_coloana = (int *)malloc(numar_matrice * sizeof(int));
	for (i = 0; i < index_matrice; i++)
		copie_linie[i] = linie[i];
	for (i = 0; i < index_matrice; i++)
		copie_coloana[i] = coloana[i];
	for (i = 0; i < index_matrice; i++) {
		linie[i] = copie_linie[pozitie[i]];
		// schimba dimensiunile liniilor matricelor din tablou dupa sortare
		coloana[i] = copie_coloana[pozitie[i]];
		/* schimba dimensiunile coloanelor matricelor din tablou dupa
		sortare pentru a corepunde cu matricile sortate deja */
	}
	free(suma);
	free(pozitie);
	free(copie_coloana);
	free(copie_linie);
	// eliberarea vectorilor auxiliari folositi
}

void functie_task_T(int index_matrice, int *linie, int *coloana, int ***tablou)
{
	int index, m, n, i, j;
	scanf("%d", &index); // citirea indexului matricei
	if (index < index_matrice && index >= 0) { // verificare conditii
		m = linie[index];
		n = coloana[index];
		int **transpusa = alloc_matrix(n, m); // alocarea matricei auxiliare
		// calcularea transpusei matricei
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++)
				transpusa[i][j] = tablou[index][j][i];
		}
		free_matrix(m, tablou[index]); // eliberarea matricei initiale
		tablou[index] = alloc_matrix(n, m); // alocarea transpusei in tablou
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++)
				tablou[index][i][j] = transpusa[i][j];
		} // adaugarea transpusei in tablou
		// schimarile necesare ale dimensiunilor matricei
		swap(&linie[index], &coloana[index]);
		free_matrix(n, transpusa); // eliberarea matricei auxiliare
	} else {
		printf("No matrix with the given index\n");
	}
}

void functie_task_R(int ***tablou, int *linie, int *coloana, int index_matrice)
{
	int index, putere;
	scanf("%d", &index); // citirea indexului matricei
	if (index < index_matrice && index >= 0) { // verificare conditii
		scanf("%d", &putere); // citirea puterii
		if (putere < 0) { // verificarea posibilitatii ridicarii la putere
			printf("Power should be positive\n");
		} else if (linie[index] != coloana[index]) {
			// verificare matrice patratica
			printf("Cannot perform matrix multiplication\n");
		} else {
			int dimensiune = linie[index];
			// alocarea unei matrice auxiliare
			int **rezultat = alloc_matrix(dimensiune, dimensiune);
			ridicare_putere_log(index, dimensiune,
								tablou[index], putere, rezultat);
			// eliberare matrice initiala
			free_matrix(dimensiune, tablou[index]);
			tablou[index] = rezultat; // adaugarea rezultatului in tablou
			verificare_valori(tablou[index], dimensiune, dimensiune);
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void functie_task_F(int *index_matrice, int index,
					int *linie, int *coloana, int ***tablou)
{
	if (index < *index_matrice && index >= 0) { // verificare conditii
		free_matrix(linie[index], tablou[index]); // eliberarea matricei
		// deplasarea matricelor cu o pozitie in tablou
		schimbare_parametri(linie, coloana, tablou,
							*index_matrice, index);
		// schimbarea numarului de matrice dupa scoaterea matricei
		*index_matrice = *index_matrice - 1;
	} else {
		printf("No matrix with the given index\n");
	}
}

void free_tablou(int index_matrice, int *linie, int ***tablou)
{ // functie ce elibereaza tabloul
	for (int i = 0; i < index_matrice; i++) {
		for (int j = 0; j < linie[i]; j++)
			free(tablou[i][j]); // elibereaza fiecare linie din matrice
	}
	for (int i = 0; i < index_matrice; i++)
		free(tablou[i]); // elibereaza fiecare matrice
	free(tablou); // elibereaza tabloul
}

void sume_auxiliare(int dim_aux, int **matrice_A1, int **matrice_A2,
					int **matrice_A3, int **matrice_A4, int **matrice_B1,
					int **matrice_B2, int **matrice_B3, int **matrice_B4,
					int **suma_A1_A4, int **suma_A3_A4, int **suma_A1_A2,
					int **suma_B1_B4, int **suma_B1_B2, int **suma_B3_B4,
					int **diferenta_B2_B4, int **diferenta_B3_B1,
				    int **diferenta_A3_A1, int **diferenta_A2_A4)
{/* calculeaza sumele si diferentele ce vor ajuta la calcularea
matricelor M1, M2, M3, M4, M5, M6, M7*/
	int i, j;
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_A1_A4[i][j] = matrice_A1[i][j] + matrice_A4[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_A3_A4[i][j] = matrice_A3[i][j] + matrice_A4[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_A1_A2[i][j] = matrice_A1[i][j] + matrice_A2[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_B1_B4[i][j] = matrice_B1[i][j] + matrice_B4[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_B1_B2[i][j] = matrice_B1[i][j] + matrice_B2[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			suma_B3_B4[i][j] = matrice_B3[i][j] + matrice_B4[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			diferenta_B2_B4[i][j] = matrice_B2[i][j] - matrice_B4[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			diferenta_B3_B1[i][j] = matrice_B3[i][j] - matrice_B1[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			diferenta_A3_A1[i][j] = matrice_A3[i][j] - matrice_A1[i][j];
	}
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++)
			diferenta_A2_A4[i][j] = matrice_A2[i][j] - matrice_A4[i][j];
	}
}

void free_matrice_s(int dim_aux, int **matrice_A1, int **matrice_A2,
					int **matrice_A3, int **matrice_A4, int **matrice_B1,
					int **matrice_B2, int **matrice_B3, int **matrice_B4,
					int **suma_A1_A4, int **suma_A3_A4, int **suma_A1_A2,
					int **suma_B1_B4, int **suma_B1_B2, int **suma_B3_B4,
				    int **diferenta_B2_B4, int **diferenta_B3_B1,
				    int **diferenta_A3_A1, int **diferenta_A2_A4, int **M1,
					int **M2, int **M3, int **M4, int **M5, int **M6,
					int **M7, int **C1, int **C2, int **C3, int **C4)
{/* functie pentru eliberarea tuturor matricelor auxiliare folosite
in algoritmul lui strassen */
	free_matrix(dim_aux, matrice_A1);
	free_matrix(dim_aux, matrice_A2);
	free_matrix(dim_aux, matrice_A3);
	free_matrix(dim_aux, matrice_A4);
	free_matrix(dim_aux, matrice_B1);
	free_matrix(dim_aux, matrice_B2);
	free_matrix(dim_aux, matrice_B3);
	free_matrix(dim_aux, matrice_B4);
	free_matrix(dim_aux, suma_A1_A2);
	free_matrix(dim_aux, suma_A1_A4);
	free_matrix(dim_aux, suma_A3_A4);
	free_matrix(dim_aux, suma_B1_B2);
	free_matrix(dim_aux, suma_B1_B4);
	free_matrix(dim_aux, suma_B3_B4);
	free_matrix(dim_aux, diferenta_A2_A4);
	free_matrix(dim_aux, diferenta_A3_A1);
	free_matrix(dim_aux, diferenta_B2_B4);
	free_matrix(dim_aux, diferenta_B3_B1);
	free_matrix(dim_aux, M1);
	free_matrix(dim_aux, M2);
	free_matrix(dim_aux, M3);
	free_matrix(dim_aux, M4);
	free_matrix(dim_aux, M5);
	free_matrix(dim_aux, M6);
	free_matrix(dim_aux, M7);
	free_matrix(dim_aux, C1);
	free_matrix(dim_aux, C2);
	free_matrix(dim_aux, C3);
	free_matrix(dim_aux, C4);
}

void calcul_c(int dim_aux, int **C1, int **C2, int **C3, int **C4, int **M1,
			  int **M2, int **M3, int **M4, int **M5, int **M6, int **M7,
			  int **rezultat)
{/* functie care calculeaza matricele C dupa reguli si le uneste
pentru a forma rezultatul */
	int i, j;
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++) {
			C1[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
			C2[i][j] = M3[i][j] + M5[i][j];
			C3[i][j] = M2[i][j] + M4[i][j];
			C4[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
		}
	}
	// unirea blocurilor
	for (i = 0; i < dim_aux; i++) {
		for (j = 0; j < dim_aux; j++) {
			rezultat[i][j] = C1[i][j];
			rezultat[i][j + dim_aux] = C2[i][j];
			rezultat[i + dim_aux][j] = C3[i][j];
			rezultat[i + dim_aux][j + dim_aux] = C4[i][j];
		}
	}
}

void strassen(int **matrice_A, int **matrice_B, int dim, int **rezultat)
{
	int dim_aux = dim / 2;
	// alocarea matricelor auxiliare ce vor reprezenta blocurile din matrice
	int **matrice_A1 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_A2 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_A3 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_A4 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_B1 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_B2 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_B3 = alloc_matrix(dim_aux, dim_aux);
	int **matrice_B4 = alloc_matrix(dim_aux, dim_aux);
	for (int i = 0; i < dim_aux; i++) { // clacularea blocurilor din matrice
		for (int j = 0; j < dim_aux; j++) {
			matrice_A1[i][j] = matrice_A[i][j];
			matrice_A2[i][j] = matrice_A[i][j + dim / 2];
			matrice_A3[i][j] = matrice_A[i + dim / 2][j];
			matrice_A4[i][j] = matrice_A[i + dim / 2][j + dim / 2];
			matrice_B1[i][j] = matrice_B[i][j];
			matrice_B2[i][j] = matrice_B[i][j + dim / 2];
			matrice_B3[i][j] = matrice_B[i + dim / 2][j];
			matrice_B4[i][j] = matrice_B[i + dim / 2][j + dim / 2];
		}
	}
	int **suma_A1_A4 = alloc_matrix(dim_aux, dim_aux); // alocarea auxiliarelor
	int **suma_A3_A4 = alloc_matrix(dim_aux, dim_aux);
	int **suma_A1_A2 = alloc_matrix(dim_aux, dim_aux);
	int **suma_B1_B4 = alloc_matrix(dim_aux, dim_aux);
	int **suma_B1_B2 = alloc_matrix(dim_aux, dim_aux);
	int **suma_B3_B4 = alloc_matrix(dim_aux, dim_aux);
	int **diferenta_B2_B4 = alloc_matrix(dim_aux, dim_aux);
	int **diferenta_B3_B1 = alloc_matrix(dim_aux, dim_aux);
	int **diferenta_A3_A1 = alloc_matrix(dim_aux, dim_aux);
	int **diferenta_A2_A4 = alloc_matrix(dim_aux, dim_aux);
	sume_auxiliare(dim_aux, matrice_A1, matrice_A2, matrice_A3, matrice_A4,
				   matrice_B1, matrice_B2, matrice_B3, matrice_B4, suma_A1_A4,
				   suma_A3_A4, suma_A1_A2, suma_B1_B4, suma_B1_B2,
				   suma_B3_B4, diferenta_B2_B4, diferenta_B3_B1,
				   diferenta_A3_A1, diferenta_A2_A4);
	int **M1 = alloc_matrix(dim_aux, dim_aux); // alocarea matricelor M
	int **M2 = alloc_matrix(dim_aux, dim_aux);
	int **M3 = alloc_matrix(dim_aux, dim_aux);
	int **M4 = alloc_matrix(dim_aux, dim_aux);
	int **M5 = alloc_matrix(dim_aux, dim_aux);
	int **M6 = alloc_matrix(dim_aux, dim_aux);
	int **M7 = alloc_matrix(dim_aux, dim_aux);
	int **C1 = alloc_matrix(dim_aux, dim_aux); // alocarea matricelor C
	int **C2 = alloc_matrix(dim_aux, dim_aux);
	int **C3 = alloc_matrix(dim_aux, dim_aux);
	int **C4 = alloc_matrix(dim_aux, dim_aux);
	if (dim_aux == 1) { // recurenta a ajuns la matrice care sunt numere
		M1[0][0] = suma_A1_A4[0][0] * suma_B1_B4[0][0];
		M2[0][0] = suma_A3_A4[0][0] * matrice_B1[0][0];
		M3[0][0] = matrice_A1[0][0] * diferenta_B2_B4[0][0];
		M4[0][0] = matrice_A4[0][0] * diferenta_B3_B1[0][0];
		M5[0][0] = suma_A1_A2[0][0] * matrice_B4[0][0];
		M6[0][0] = diferenta_A3_A1[0][0] * suma_B1_B2[0][0];
		M7[0][0] = diferenta_A2_A4[0][0] * suma_B3_B4[0][0];
		C1[0][0] = M1[0][0] + M4[0][0] - M5[0][0] + M7[0][0];
		C2[0][0] = M3[0][0] + M5[0][0];
		C3[0][0] = M2[0][0] + M4[0][0];
		C4[0][0] = M1[0][0] - M2[0][0] + M3[0][0] + M6[0][0];
		rezultat[0][0] = C1[0][0];
		rezultat[0][1] = C2[0][0];
		rezultat[1][0] = C3[0][0];
		rezultat[1][1] = C4[0][0];
	} else { // aplica recurent algoritmul pentru calcularea produselor
		strassen(suma_A1_A4, suma_B1_B4, dim / 2, M1);
		strassen(suma_A3_A4, matrice_B1, dim / 2, M2);
		strassen(matrice_A1, diferenta_B2_B4, dim / 2, M3);
		strassen(matrice_A4, diferenta_B3_B1, dim / 2, M4);
		strassen(suma_A1_A2, matrice_B4, dim / 2, M5);
		strassen(diferenta_A3_A1, suma_B1_B2, dim / 2, M6);
		strassen(diferenta_A2_A4, suma_B3_B4, dim / 2, M7);
		calcul_c(dim_aux, C1, C2, C3, C4, M1, M2, M3, M4, M5, M6, M7, rezultat);
	}
	free_matrice_s(dim_aux, matrice_A1, matrice_A2, matrice_A3, matrice_A4,
				   matrice_B1, matrice_B2, matrice_B3, matrice_B4, suma_A1_A4,
				   suma_A3_A4, suma_A1_A2, suma_B1_B4, suma_B1_B2, suma_B3_B4,
				   diferenta_B2_B4, diferenta_B3_B1, diferenta_A3_A1,
				   diferenta_A2_A4, M1, M2, M3, M4, M5, M6, M7, C1, C2, C3, C4);
}

void functie_task_S(int *index_matrice, int *numar_matrice,
					int *linie, int *coloana, int ***tablou)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2); // citire indecsi matrice
	if (index1 < *index_matrice && index2 < *index_matrice &&
	    index1 >= 0 && index2 >= 0) { // verificarea conditiilor
		if (linie[index1] != linie[index2]) { // verificarea dimensiunilor
			printf("Cannot perform matrix multiplication\n");
		} else {
			if (*index_matrice == *numar_matrice - 1) {
				*numar_matrice = *numar_matrice * 2;
				tablou = (int ***)realloc(tablou,
									      *numar_matrice * sizeof(int **));
				linie = realocare_vector(*numar_matrice, linie);
				coloana = realocare_vector(*numar_matrice, coloana);
			} // realocarea tabloului pentru a putea adauga o noua matrice
			int dim = linie[index1]; // dimensiune
			// alocarea matricei auxiliare in care va fi calculat rezultatul
			int **rezultat = alloc_matrix(dim, dim);
			tablou[*index_matrice] = alloc_matrix(dim, dim);
			free_matrix(dim, tablou[*index_matrice]);
			// aplicarea algoritmului lui Strassen
			strassen(tablou[index1], tablou[index2], dim, rezultat);
			// adaugarea rezultatului in tablou
			tablou[*index_matrice] = rezultat;
			verificare_valori(tablou[*index_matrice], dim, dim);
			// adaugarea dimensiunilor matricei rezultate in vecori
			linie[*index_matrice] = dim;
			coloana[*index_matrice] = dim;
			// marirea numarului de matrice din tablou
			*index_matrice = *index_matrice + 1;
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

int main(void)
{
int index1, index2, index;
int numar_matrice, index_matrice, oprire;
oprire = 1;
char litera;
numar_matrice = 1; // numarul de matrice alocate din tablou
index_matrice = 0; // numarul de matrice existente
int ***tablou = (int ***)malloc(numar_matrice *sizeof(int **));
int *linie = (int *)malloc(numar_matrice *sizeof(int));
int *coloana = (int *)malloc(numar_matrice *sizeof(int));
while (1 && oprire == 1) {
	scanf("%c", &litera);
	if (litera >= 'A' && litera <= 'Z') {
		switch (litera) {
		case 'L': // Incărcarea in memorie a unei matrice
			realocare(&numar_matrice, &linie, &coloana, &tablou, index_matrice);
			if (!tablou)
				return -1;
			adaugare_matrice(tablou, linie, coloana, index_matrice);
			index_matrice++;
			break;
		case 'D': // Determinarea dimensiunilor unei matrice
			functie_task_D(index_matrice, linie, coloana);
			break;
		case 'P': // Afisarea unei matrice
			functie_task_P(index_matrice, linie, coloana, tablou);
			break;
		case 'C': // Redimensionarea unei matrice
			functie_task_C(index_matrice, linie, coloana, tablou);
			break;
		case 'M': // Înmultirea a două matrice
			scanf("%d%d", &index1, &index2); // citirea celor doi indecsi
			if (index1 < index_matrice && index2 < index_matrice &&
				index1 >= 0 && index2 >= 0) { // verificare conditii
				if (coloana[index1] != linie[index2]) {
					printf("Cannot perform matrix multiplication\n");
				} else {
					realocare(&numar_matrice, &linie, &coloana,
							  &tablou, index_matrice);
					functie_task_M(index_matrice, index1,
								   index2, linie, coloana, tablou);
					index_matrice++;
				}
			} else {
				printf("No matrix with the given index\n");
			}
			break;
		case 'O': // Sortarea matricelor
			functie_task_O(index_matrice, numar_matrice, linie,
						   coloana, tablou);
			break;
		case 'T': // Transpunerea unei matrice
			functie_task_T(index_matrice, linie, coloana, tablou);
			break;
		case 'R': // Ridicarea unei matrice la o putere în timp logaritmic
			functie_task_R(tablou, linie, coloana, index_matrice);
			break;
		case 'F': // Eliberarea memoriei unei matrice
			scanf("%d", &index); // citire index matrice
			functie_task_F(&index_matrice, index, linie, coloana, tablou);
			realocare_minus(index_matrice, &numar_matrice,
							&linie, &coloana, &tablou);
			break;
		case 'S': // Înmultirea matricelor folosind algoritmul lui Strassen
			functie_task_S(&index_matrice, &numar_matrice,
						   linie, coloana, tablou);
			break;
		case 'Q': // Eliberarea tuturor resurselor
			free_tablou(index_matrice, linie, tablou); // eliberare tablou
			free(linie); // eliberarea vectorilor pentru dimensiuni
			free(coloana);
			oprire = 0; // finalizeaza programul la citirea literei Q
			return 0;
		default: // Alte situatii
			printf("Unrecognized command\n");
			break;
		}
	}
}

	return 0;
}

