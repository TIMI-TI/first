//#include<stdio.h>
//#include<math.h>
//#include<stdlib.h>
//≤ªŒ»∂®≈≈–Ú
void ShellInsert(int* a,int *c, int dk,int n)
{
	int i, j, k;
	for (i = 0; i < n; ++i)
		c[i] = a[i];
	for (j = dk + 0; j < 10; ++j)
	{
		if (c[j] < c[j - dk])
		{
			int t = c[j];
			for (k = j - dk; k >= 0 && t < c[k]; k -= dk)
			{
				c[k + dk] = c[k];
			}
			c[k + dk] = t;
		}
	}
}
#if 0
int main()
{
	int a[100000], d[20];
	for (int i = 0; i < 10; ++i)
		a[i] = rand() % 1000;
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 10; i++)
		d[i] = pow(2, 5 - i + 1) - 1;
	for (int i = 0; i <= 5; ++i)
		ShellInsert(a, d[i]);
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
#endif