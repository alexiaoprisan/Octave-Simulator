#include <stdio.h>
#include <stdlib.h>

int **alloc_matrix(int m, int n){ 

	int **a = (int **)malloc (m* sizeof(int *)); 
	if(!a){
		fprintf(stderr, "malloc() failed");
		return NULL;
	}

	for(int i=0; i<m; i++){
		a[i]= (int *) malloc (n * sizeof(int)); 
		if(!a[i]){
			fprintf(stderr, "malloc() failed");
			while(--i>=0){
				free(a[i]); 
			}
			free(a); 
			return NULL;
		}
		
	}
	return a;
}

int *realocare_vector(int numar_matrice, int *v){
	int *tmp=(int *)realloc(v, numar_matrice * sizeof(int));
	if(!tmp)
	{
		fprintf(stderr, "realloc()failed \n");
		free(v);
		return NULL;
	}  
	
	return tmp;
}

void swap(int *a, int *b){
	int aux;
	aux=*a;
	*a=*b;
	*b=aux;
}

void read_matrix(int m, int n, int **matrice){
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			scanf("%d", &matrice[i][j]);
		}
	}
}

void print_matrix(int index_matrice, int m, int n, int ***tablou){
	for(int i=0; i<m-1; i++){
		for(int j=0; j<n; j++){
			printf("%d ", tablou[index_matrice][i][j]);
		}
		printf("\n");
	}
	for(int j=0; j<n; j++){
		printf("%d ", tablou[index_matrice][m-1][j]);
	}
	
}

void produs_matrice(int m1, int n2, int n1, int index1, int index2, int **produs, int ***tablou){

int i, j, k;
for(i=0; i<m1; i++){ 
	for(j=0; j<n2; j++){
		produs[i][j]=0;
		for(k=0; k<n1; k++){
			produs[i][j]=(produs[i][j]+tablou[index1][i][k]*tablou[index2][k][j])%10007;
			if(produs[i][j]<0){
				produs[i][j]=produs[i][j]+10007;
			}
			}
		}
	}
}

void verificare_valori(int **produs, int m1, int n2){

	int i, j;
	for(i=0; i<m1; i++){
		for(j=0; j<n2; j++){
			if(produs[i][j]>=0){
				produs[i][j]=produs[i][j]%10007;
			}
			else {
				produs[i][j]=produs[i][j]%10007+10007;
			}
			}
		}
}

void creare_vectori(int *suma, int *pozitie, int index_matrice){
	int i;
	for(i=0; i<index_matrice; i++){
		suma[i]=0;
	}
	for(i=0; i<index_matrice; i++)
	{
		pozitie[i]=i;
	}
}

void suma_matrice(int index_matrice, int *suma, int *linie, int *coloana, int ***tablou){
	int contor, j, k;
	for(contor=0; contor<index_matrice; contor++) 
	{
		for(j=0; j<linie[contor]; j++){
			for(k=0; k<coloana[contor]; k++){
			suma[contor]=suma[contor]+tablou[contor][j][k];
			}
		}
	}
}

void verificare_valori_sume(int index_matrice, int *suma){
	int contor;
	for(contor=0; contor<index_matrice; contor++)
	{
	if(suma[contor]>=0) 
		suma[contor]=suma[contor]%10007;
	else 
		suma[contor]=suma[contor]%10007+10007;               
	}
}

void schimbare_matrice_tablou(int index_matrice, int *suma, int *pozitie, int ***tablou){
int **aux;
for (int i = 0; i < index_matrice - 1; ++i) { 
	for (int j = 0; j < index_matrice - i - 1; ++j) {
		if (suma[j] > suma[j + 1]) {
			swap(&pozitie[j], &pozitie[j+1]);
			swap(&suma[j], &suma[j+1]);
						
			aux=tablou[j];
			tablou[j]=tablou[j+1];
			tablou[j+1]=aux;            
		}
	}
}
}

void free_matrix(int n, int **a){ 
	 
	 for(int i=0; i<n; i++){
		free(a[i]);
	 }
	 free(a);
}

int **inmultire_matrice(int **matrice1, int **matrice2, int n){
	
	int **aux=alloc_matrix(n, n);
	int i, j, k;
	for(i=0; i<n; i++){ 
	for(j=0; j<n; j++){
		aux[i][j]=0;
		for(k=0; k<n; k++){
			aux[i][j]+=matrice1[i][k]*matrice2[k][j];
			}
		}
	}
	verificare_valori(aux, n, n);
	return aux;
}

int **ridicare_putere_log(int index, int dimensiune, int **matrice,  int putere){
	int **matrice_aux=alloc_matrix(dimensiune, dimensiune);
	if(putere==0){
		int **aux=alloc_matrix(dimensiune, dimensiune);
		for(int i=0; i<dimensiune; i++){
			for(int j=0; j<dimensiune; j++){
				aux[i][j]=0;
				if(i==j){
					aux[i][j]=1;
				}
			}
		}
		verificare_valori(aux, dimensiune, dimensiune);
		return aux;
	}
	else if(putere%2==0){
		matrice_aux=ridicare_putere_log(index, dimensiune, matrice, putere/2);
		return inmultire_matrice(matrice_aux, matrice_aux, dimensiune);
	}
	else {
		matrice_aux=ridicare_putere_log(index, dimensiune, matrice, ((putere-1)/2));
		return inmultire_matrice(matrice, inmultire_matrice(matrice_aux, matrice_aux, dimensiune), dimensiune);
	}
}

void adaugare_matrice(int ***tablou, int *linie, int *coloana, int index_matrice){
	
	int m, n;
	scanf("%d%d", &m, &n);
	int **matrice=alloc_matrix(m ,n);
	read_matrix(m, n, matrice); 
			
	tablou[index_matrice]=matrice;
	linie[index_matrice]=m;
	coloana[index_matrice]=n;    
}

void functie_task_D(int index_matrice, int *linie, int *coloana){
	int index1;
	scanf("%d", &index1);
	if(index1<index_matrice) {
		printf("%d ", linie[index1]);
		printf("%d", coloana[index1]);
	}
	else {
		printf("No matrix with the given index");
	}
	printf("\n");
}

void functie_task_P(int index_matrice, int *linie, int *coloana, int ***tablou){
	int index2;
	scanf("%d", &index2);
	if(index2<index_matrice) {
		print_matrix(index2, linie[index2], coloana[index2], tablou);
		printf("\n");
	}
	else {
		printf("No matrix with the given index\n");

	}
}

void functie_task_C(int index_matrice, int *linie, int *coloana, int ***tablou){
	
	int index, nr_linii, nr_coloane, i, j;
	scanf("%d", &index);
	scanf("%d", &nr_linii);
	int *index_linii=(int *)malloc(nr_linii * sizeof(int));
			
	for(i=0; i<nr_linii; i++){
		scanf("%d", &index_linii[i]);
	}
					
	scanf("%d", &nr_coloane);
	int *index_coloane=(int *)malloc(nr_coloane * sizeof(int));
	for(i=0; i<nr_coloane; i++){
		scanf("%d", &index_coloane[i]);
	}
	if(index<index_matrice){
		
		int **matrice;
		matrice=alloc_matrix(nr_linii, nr_coloane);
		for(i=0; i<nr_linii; i++){
			for(j=0; j<nr_coloane; j++){
				matrice[i][j]=tablou[index][index_linii[i]][index_coloane[j]];
			}
		}
		free_matrix(linie[index], tablou[index]);
		linie[index]=nr_linii;
		coloana[index]=nr_coloane;
		tablou[index]=alloc_matrix(linie[index], coloana[index]);
		tablou[index]=matrice;
		
		
		// free_matrix(nr_linii, matrice);
	}
	else {
		printf("No matrix with the given index\n");
	}
	free(index_coloane);
	free(index_linii);
}
// revin
void functie_task_M(int index_matrice, int index1, int index2, int *linie, int *coloana, int ***tablou){
	int m1, n1, n2;
	m1=linie[index1];
	n1=coloana[index1];
	n2=coloana[index2];

	int **produs=alloc_matrix(m1, n2);
	produs_matrice(m1, n2, n1, index1, index2, produs, tablou);
	verificare_valori(produs, m1, n2);
	tablou[index_matrice]=produs;
	linie[index_matrice]=m1;
	coloana[index_matrice]=n2;
	// free_matrix(m1, produs);
}

void functie_task_O(int index_matrice, int numar_matrice, int *linie, int *coloana, int ***tablou){
	int i;

	int *suma=(int *)malloc(index_matrice * sizeof(int));
	int *pozitie=(int *)malloc(index_matrice * sizeof(int));

	creare_vectori(suma, pozitie, index_matrice);
	suma_matrice(index_matrice, suma, linie, coloana, tablou);
	verificare_valori_sume(index_matrice, suma);
	schimbare_matrice_tablou(index_matrice, suma, pozitie, tablou);
			
	int *copie_linie=(int *)malloc(numar_matrice * sizeof(int));
	int *copie_coloana=(int *)malloc(numar_matrice * sizeof(int));
			
	for(i=0; i<index_matrice; i++){
		copie_linie[i]=linie[i];
	}
	for(i=0; i<index_matrice; i++){
		copie_coloana[i]=coloana[i];
	}

	for(i=0; i<index_matrice; i++){
		linie[i]=copie_linie[pozitie[i]];
		coloana[i]=copie_coloana[pozitie[i]];
	}
	free(suma);
	free(pozitie);
	free(copie_coloana);
	free(copie_linie);
}

void functie_task_T(int numar_matrice, int *linie, int *coloana, int ***tablou){
	int index, m, n, i, j;
	scanf("%d", &index);
	if(index<numar_matrice){
	m=linie[index];
	n=coloana[index];

	int **transpusa;
	transpusa=alloc_matrix(n, m);

	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			transpusa[i][j]=tablou[index][j][i];  
		}
	}
				
	free_matrix(m, tablou[index]);
	tablou[index]=alloc_matrix(n, m);

	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			tablou[index][i][j]=transpusa[i][j];  
			}
		}
		swap(&linie[index], &coloana[index]);
	free_matrix(n, transpusa);
	}
	else 
		printf("No matrix with the given index");
}

void functie_task_R(int ***tablou, int *linie, int *coloana, int index_matrice){
	int index, putere;
	scanf("%d", &index);
	if(index<index_matrice){
		scanf("%d", &putere);
	
		if(putere<0){
			printf("Power should be positive\n");
		}
		else{
			if(linie[index]!=coloana[index]){
				printf("Cannot perform matrix multiplication\n");
			}
			else{
				int dimensiune=linie[index];
				tablou[index]=ridicare_putere_log(index, dimensiune, tablou[index],  putere);
				verificare_valori(tablou[index], dimensiune, dimensiune);
				}
		}

	}
	else{
		printf("Cannot perform matrix multiplication\n");
	}
	}

void free_tablou(int index_matrice, int *linie, int ***tablou){ 
     
    for(int i=0; i<index_matrice; i++){
        free_matrix(linie[i], tablou[i]);
    }  
    free(tablou);
}

int main(){

int numar_matrice, index_matrice, oprire;
oprire=1;
char litera;
numar_matrice=1;
index_matrice=0;

int ***tablou=(int ***)malloc(numar_matrice * sizeof(int **));
int *linie=(int *)malloc(numar_matrice * sizeof(int));
int *coloana=(int *)malloc(numar_matrice * sizeof(int));

while(1 && oprire==1){
	scanf("%c", &litera);
	switch (litera) {
		case 'L':
			if(index_matrice==numar_matrice-1){
				numar_matrice=numar_matrice*2;
				tablou=realloc(tablou, numar_matrice * sizeof(int **));
				linie=realocare_vector(numar_matrice, linie);
				coloana=realocare_vector(numar_matrice, coloana);
			}         
			if(!tablou){
				return -1;
			}
			adaugare_matrice(tablou, linie, coloana, index_matrice); 
			index_matrice++;
			break;

		case 'D': 	// Determinarea dimensiunilor unei matrice
			functie_task_D(index_matrice, linie, coloana);
			break;
		case 'P':	// Afisarea unei matrice
			functie_task_P(index_matrice, linie, coloana, tablou);
			break;
		case 'C':	// Redimensionarea unei matrice
			functie_task_C(index_matrice, linie, coloana, tablou);
			break;
		case 'M':	// Înmultirea a două matrice
			int index1, index2; 
			scanf("%d%d", &index1, &index2);
			if(index1<index_matrice && index2<index_matrice){
				if(coloana[index1]!=linie[index2]){
					printf("Cannot perform matrix multiplication\n");
				}
				else {
				if(index_matrice>=numar_matrice-1){ 
					numar_matrice=numar_matrice*2;
					tablou=realloc(tablou, numar_matrice * sizeof(int **));
					linie=realocare_vector(numar_matrice, linie);
					coloana=realocare_vector(numar_matrice, coloana);
				}  
				functie_task_M(index_matrice, index1, index2, linie, coloana, tablou);
				index_matrice++;
				}
			}
			else printf("No matrix with the given index\n");
			break;

		case 'O':	// Sortarea matricelor
			functie_task_O(index_matrice, numar_matrice, linie, coloana, tablou);
			break;
		case 'T':	// Transpunerea unei matrice
			functie_task_T(numar_matrice, linie, coloana, tablou);
			break;
		case 'R':	// Ridicarea unei matrice la o putere în timp logaritmic
			functie_task_R(tablou, linie, coloana, index_matrice);
			break;
		case 'F':
			int index;
			scanf("%d", &index);
			if(index<index_matrice){
				free_matrix(linie[index], tablou[index]);
				for(int i=index; i<index_matrice-1; i++){
					tablou[i]=tablou[i+1];
					linie[i]=linie[i+1];
					coloana[i]=coloana[i+1];
				}
				
				index_matrice=index_matrice-1;
			}
			else {
				printf("No matrix with the given index\n");
			}	
			break;

		case 'S':
			break;
		case '\n':
			break;
		case 'Q':
			free_tablou(index_matrice, linie, tablou);
			free(linie);
			free(coloana);
			oprire=0;
			return 0;
			break;
		case ' ':
			break;
		default:
			printf("Unrecognized command\n");		
			
	}
}
   
	for(int i=0; i<index_matrice; i++){
		for(int j=0; j<linie[i]; j++){
			for(int k=0; k<coloana[i]; k++){
				printf("%d ", tablou[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
 
	
	return 0;
}

