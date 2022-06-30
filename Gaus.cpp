#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

void glavelem(int k, float** Base, int n, float* otv)
{
	int i, j, i_max = k, j_max = k;
	float temp;
	for (i = k; i < n; i++)
		for (j = k; j < n; j++)
			if (fabs(Base[i_max][j_max]) < fabs(Base[i][j]))
			{
				i_max = i;
				j_max = j;
			}
	for (j = k; j < n + 1; j++)
	{
		temp = Base[k][j];
		Base[k][j] = Base[i_max][j];
		Base[i_max][j] = temp;
	}
	for (i = 0; i < n; i++)
	{
		temp = Base[i][k];
		Base[i][k] = Base[i][j_max];
		Base[i][j_max] = temp;
	}
	i = otv[k];
	otv[k] = otv[j_max];
	otv[j_max] = i;
}
int main() {
	setlocale(LC_ALL, "Rus");
	// Основная матрица
	int n;
	printf("Введите размерность матрицы: ");
	scanf_s("%d", &n);
	float** Base = (float**)malloc(n * sizeof(float*));
	printf("Введите коэффициенты уравнений системы\n");

	for (int i = 0; i < n; i++) {
		Base[i] = (float*)malloc(n * sizeof(float));
		for (int j = 0; j < n + 1; j++) {
			printf("a[%d][%d] = ", i, j);
			scanf_s("%f", &Base[i][j]);
		}
	}
	printf("Расширенная матрица\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (j == n) printf("| ");
			printf("%.2f ", Base[i][j]);
		}
		printf("\n");

	}
	//double Base[N][N + 1];
	float* x = (float*)malloc(n * sizeof(float)); //Корни системы
	float* otv = (float*)malloc(n * sizeof(float)); //Отвечает за порядок корней
	int i, j, k;
	for (i = 0; i < n + 1; i++)
		otv[i] = i;
	for (k = 0; k < n; k++)
	{ //На какой позиции должен стоять главный элемент
		glavelem(k, Base, n, otv); //Установка главного элемента
		if (fabs(Base[k][k]) < 0.0001) //абсолютное значение
		{
			printf("Система не имеет единственного решения");
			return (0);
		}
		for (j = n; j >= k; j--)
			Base[k][j] /= Base[k][k];
		for (i = k + 1; i < n; i++)
			for (j = n; j >= k; j--)
				Base[i][j] -= Base[k][j] * Base[i][k];
	}
	for (i = 0; i < n; i++)
		x[i] = Base[i][n];
	for (i = n - 2; i >= 0; i--)
		for (j = i + 1; j < n; j++)
			x[i] -= x[j] * Base[i][j];
	//Вывод результата
	printf("Ответ:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i == otv[j])
			{ //Расставляем корни по порядку
				printf("%.3f\n", x[j]);
				break;
			}
	for (int i = 0; i < n; i++) {
		free(Base[i]);
	}
	free(Base);
	free(x);
	free(otv);
	return (0);
}