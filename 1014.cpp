#include <stdio.h>
#include <math.h>
#include <malloc.h>

int main() {
	int n, n1, l;
	scanf_s("%d", &n);
	l = 0;
	int* q = (int*)malloc(15 * sizeof(int*));
	n1 = n;
	if (n1 == 0) {
		printf("10");
		return 0;
	}
	if (n1 == 1) {
		printf("1");
		return 0;
	}
	while (n1 != 1) {
		for (int i = 9; i >= 2; i--) {
			if (n1 % i == 0) {
				n1 /= i;
				q[l] = i;
				l++;
				i++;
			}
		}
		if (n1 != 1) {
			printf("-1");
			return 0;
		}
	}
	for (l -= 1; l >= 0; l--) {
		printf("%d", q[l]);
	}
	return 0;
}