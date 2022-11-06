// Copyright Aldica Maria Miruna, 311CA
#include <stdio.h>
#include <stdlib.h>
#define MOD 10007

// Structura care retine datele matricei
typedef struct matrice {
	int **elem, m, n, suma;
} matrice;

// Initializam matricea a
void alocare(matrice *a, int m, int n)
{
	a->m = m;
	a->n = n;
	a->suma = 0;
	a->elem = (int **)malloc(a->m * sizeof(int *));
	for (int i = 0; i < a->m; i++)
		a->elem[i] = (int *)malloc(a->n * sizeof(int));
}

// Citim elementele matricei
void citeste(matrice *a)
{
	int m, n;
	scanf("%d%d", &m, &n);
	alocare(a, m, n);
	for (int i = 0; i < a->m; i++)
		for (int j = 0; j < a->n; j++) {
			scanf("%d", &a->elem[i][j]);
			// Calculam suma elementelor
			a->suma = ((a->suma + a->elem[i][j]) % MOD + MOD) % MOD;
		}
}

void afisare(matrice a)
{
	for (int i = 0; i < a.m; i++) {
		for (int j = 0; j < a.n; j++)
			printf("%d ", a.elem[i][j]);
		printf("\n");
	}
}

// Eliminarea matricei cu un index dat
void eliminare(matrice *mat, int *dim, int index)
{
	for (int i = 0; i < mat[index].m; i++)
		free(mat[index].elem[i]);
	free(mat[index].elem);
	for (int i = index; i < *dim - 1; i++)
		mat[i] = mat[i + 1];
	(*dim)--;
}

int citeste_index(int dim)
{
	int index;
	scanf("%d", &index);
	// Conditiile pentru care indexul citit nu este valabil
	if (index < 0 || index >= dim) {
		printf("No matrix with the given index\n");
		return -1;
	}
	return index;
}

matrice inmultire(matrice a, matrice b)
{
	matrice rezultat;
	alocare(&rezultat, a.m, b.n);
	for (int i = 0; i < rezultat.m; i++)
		for (int j = 0; j < rezultat.n; j++) {
			// Noul element generat in matricea produs
			rezultat.elem[i][j] = 0;
			for (int k = 0; k < a.n; k++) {
				rezultat.elem[i][j] =
				((rezultat.elem[i][j] +
				  a.elem[i][k] * b.elem[k][j]) % MOD + MOD) % MOD;
				rezultat.suma =
				((rezultat.suma +
				  a.elem[i][k] * b.elem[k][j]) % MOD + MOD) % MOD;
			}
		}
	return rezultat;
}

//Interschimbare
void swap_int(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap_mat(matrice *a, matrice *b)
{
	matrice temp = *a;
	*a = *b;
	*b = temp;
}

// Functie pentru transpunerea matricei a
void transpunere(matrice *a)
{
	matrice copie = *a;
	swap_int(&a->n, &a->m);
	a->elem = (int **)malloc(a->m * sizeof(int *));
	for (int i = 0; i < a->m; i++)
		a->elem[i] = (int *)malloc(a->n * sizeof(int));
	for (int i = 0; i < a->m; i++)
		for (int j = 0; j < a->n; j++)
			a->elem[i][j] = copie.elem[j][i];
	for (int i = 0; i < copie.m; i++)
		free(copie.elem[i]);
	free(copie.elem);
}

// sortarea matricelor dupa suma elementelor
void sort(matrice *mat, int dim)
{
	int gasit;
	do {
		int start = 0;
		gasit = 0;
		for (int i = start; i < dim - 1; i++)
			if (mat[i].suma > mat[i + 1].suma) {
				swap_mat(&mat[i], &mat[i + 1]);
				gasit = 1;
			}
		start++;
	} while (gasit);
}

void redimensionare(matrice *a)
{
	matrice copie = *a;
	int linii, coloane;
	scanf("%d", &linii);
	// Citire
	int *linii_noi = (int *)malloc(linii * sizeof(int));
	for (int i = 0; i < linii; i++)
		scanf("%d", &linii_noi[i]);
	scanf("%d", &coloane);
	int *coloane_noi = (int *)malloc(coloane * sizeof(int));
	for (int i = 0; i < coloane; i++)
		scanf("%d", &coloane_noi[i]);
	a->m = linii;
	a->n = coloane;
	a->suma = 0;
	a->elem = (int **)malloc(linii * sizeof(int *));
	for (int i = 0; i < linii; i++) {
		a->elem[i] = (int *)malloc(coloane * sizeof(int));
		for (int j = 0; j < coloane; j++) {
			a->elem[i][j] = copie.elem[linii_noi[i]][coloane_noi[j]];
			a->suma = ((a->suma + a->elem[i][j]) % MOD + MOD) % MOD;
		}
	}
	// Eliberarea memoriei
	free(linii_noi);
	free(coloane_noi);
	for (int i = 0; i < copie.m; ++i)
		free(copie.elem[i]);
	free(copie.elem);
}

int main(void)
{
	matrice *mat = (matrice *)malloc(1 * sizeof(matrice));
	char op; // Operatorul care citeste operatiile
	int dim = 0, dim_max = 1;
	scanf(" %c", &op);
	while (op != 'Q') {
		// Redimensionarea vectorului mat in functie de nr. de elem.
		if (dim == dim_max) {
			dim_max *= 2;
			mat = (matrice *)realloc(mat, dim_max * sizeof(matrice));
		}
		if (dim < dim_max / 2) {
			dim_max /= 2;
			mat = (matrice *)realloc(mat, dim_max * sizeof(matrice));
		}
		if (op == 'L') {
			citeste(&mat[dim++]);
		} else if (op == 'P') {
			int index;
			index = citeste_index(dim);
			if (index != -1)
				afisare(mat[index]);
		} else if (op == 'D') {
			int index;
			index = citeste_index(dim);
			if (index != -1)
				printf("%d %d\n", mat[index].m, mat[index].n);
		} else if (op == 'M') {
			int index1, index2;
			scanf("%d%d", &index1, &index2);
			if (index1 >= dim || index1 < 0 || index2 >= dim || index2 < 0)
				printf("No matrix with the given index\n");
			else if (mat[index1].n != mat[index2].m)
				printf("Cannot perform matrix multiplication\n");
			else
				mat[dim++] = inmultire(mat[index1], mat[index2]);
		} else if (op == 'T') {
			int index = citeste_index(dim);
			if (index != -1)
				transpunere(&mat[index]);
		} else if (op == 'F') {
			int index = citeste_index(dim);
			if (index != -1)
				eliminare(mat, &dim, index);
		} else if (op == 'O') {
			sort(mat, dim);
		} else if (op == 'C') {
			int index = citeste_index(dim);
			if (index != -1)
				redimensionare(&mat[index]);
			else
				for (int i = 0; i < 2; i++) {
					int n, x;
					scanf("%d", &n);
					for (int j = 0; j < n; j++)
						scanf("%d", &x);
				}
		} else {
			printf("Unrecognized command\n");
		}
		scanf(" %c", &op);
	}
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < mat[i].m; j++)
			free(mat[i].elem[j]);
		free(mat[i].elem); // Eliberarea elementelor matricei
	}
	free(mat); // Eliberare matrice
	return 0;
}
