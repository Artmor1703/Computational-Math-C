#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

void PrintMatr(float** Matr, int Razm) {
	for (int i = 0; i < Razm; i++) {
		for (int j = 0; j < Razm; j++) {
			printf("%.2f ", Matr[i][j]);
		}
		printf("\n");
	}
}
void Minor(float** Base, float** p, int i, int j, int Razm) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < (Razm - 1); ki++) {
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < (Razm - 1); kj++) {
			if (kj == j) dj = 1;
			p[ki][kj] = Base[ki + di][kj + dj];
		}
	}
}

int Determinant(float** Matr, int Razm, float* KofSyst) {
	float** p1 = (float**)malloc(Razm * Razm * sizeof(float*));
	//p = new int* [Razm];
	for (int i = 0; i < Razm; i++)
		p1[i] = (float*)malloc(Razm * sizeof(float));
	int j = 0;
	float Opred1 = 0;
	int k = 1;
	int n2 = Razm - 1;
	if (Razm < 1)
		printf("Определитель найти невозможно.");
	if (Razm == 1) {
		Opred1 = Matr[0][0];
		return(Opred1);
	}
	if (Razm == 2) {
		Opred1 = Matr[0][0] * Matr[1][1] - (Matr[1][0] * Matr[0][1]);
		return(Opred1);
	}

	if (Razm > 2) {
		for (int i = 0; i < Razm; i++) {
			Minor(Matr, p1, i, 0, Razm);
			Opred1 = Opred1 + k * Matr[i][0] * Determinant(p1, n2, KofSyst);
			k = -k;
		}
	}
	return(Opred1);
}
int main()
{
	setlocale(LC_ALL, "Rus");

	// Основная матрица
	int Razm;
	printf("Введите размерность матрицы: ");
	scanf_s("%d", &Razm);
	float* KofSyst = (float*)calloc(Razm, sizeof(float));
	float* Opred = (float*)calloc(Razm, sizeof(float));
	float** Base = (float**)malloc(Razm * sizeof(float*)); // динамическое выделение памяти
	printf("Введите систему\n");
	// Ввод элементов массива
	for (int i = 0; i < Razm; i++) {
		Base[i] = (float*)malloc(Razm * sizeof(float));
		int j = 0;
		scanf_s("%f %f %f = %f", &Base[i][j], &Base[i][j + 1], &Base[i][j + 2], &KofSyst[i]);
	}
	float** Matr = (float**)malloc(Razm * sizeof(float*));
	for (int i = 0; i < Razm; i++)
		Matr[i] = (float*)malloc(Razm * sizeof(float));
	for (int i = 0; i < Razm; i++) {
		for (int j = 0; j < Razm; j++)
			Matr[i][j] = Base[i][j];
	}
	printf("Матрица\n");
	PrintMatr(Matr, Razm);
	Opred[0] = Determinant(Matr, Razm, KofSyst);
	if (Opred[0] == 0) {
		printf("Определитель delta = %.2f \n", Opred[0]);
		printf("Определитель равен нулю, матрица является особенной \n");
		for (int i = 0; i < Razm; i++) {
			free(Base[i]);
			free(Matr[i]);
		}
		free(Base);
		free(Matr);
		free(KofSyst);
		free(Opred);

		return 0;
	}
	printf("Определитель delta = %.2f\n", Opred[0]);
	for (int j = 0; j < Razm; j++) {
		for (int i = 0; i < Razm; i++)
			Matr[i][j] = KofSyst[i];
		printf("Матрица с заменой %d столбца коэффициентами системы\n", j + 1);
		PrintMatr(Matr, Razm);
		Opred[j + 1] = Determinant(Matr, Razm, KofSyst);
		printf("Определитель delta(%d) = %.2f\n", j + 1, Opred[j + 1]);
		for (int i = 0; i < Razm; i++)
			Matr[i][j] = Base[i][j];

	}
	for (int i = 1; i < Razm + 1; i++) {
		printf("x(%d) = %.2f\n", i, Opred[i] / Opred[0]);
	}
	for (int i = 0; i < Razm; i++) {
		free(Base[i]);
		free(Matr[i]);
	}
	free(Base);
	free(Matr);
	free(KofSyst);
	free(Opred);
	return 0;
}



