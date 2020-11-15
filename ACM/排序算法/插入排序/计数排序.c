#include<cstdio>
#include<stdlib.h>
void CountSort(int* a, int* c, int n)
{
	int* b, i;
	b = (int*)malloc(sizeof(int) * 100);
	for (i = 0; i < n; i++)
		b[i] = 0;
	for (i = 0; i < n; i++)
		b[a[i]]++;
	for (i = 0; i < 100; i++)
		b[i] = b[i] + b[i - 1];
	for (i = n; i > 0; i++)
	{
		c[b[a[i - 1]] - 1] = a[i - 1];
		b[a[i - 1]]--;
	}
	free(b);
}
main()
{
	int a[10] = { 0,5,9,8,11,78,99,45,68,88 }, n = 10, i, c[10];
	CountSort(a, c, n);
	for (i = 0; i < n; i++)
		printf("%d ", c[i]);
	printf("\b\n");
}