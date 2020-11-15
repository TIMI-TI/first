//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include<time.h>
//Œ»∂®≈≈–Ú
void InsertSort(int a[], int n,int c[]) {
	int i, j;
	for (i = 0; i < n; i++)
		c[i] = a[i];
	
	for (i = 1; i < n; i++)
	{
		if (c[i] < c[i - 1])
		{
			 int t = c[i];
			for (j = i - 1; c[j] > t && j >= 0; j--)
			{
				c[j + 1] = c[j];
			}
			c[j + 1] = t;
		}
	}
}

#if 0
main() {

	int a[20], n = 10, i, k, count = 0;

	while (count < n) {
		k = rand() % 100;
		int flag = 0;
		for (i = 1; i <= n; i++)
			if (a[i] == k) {
				flag = 1;
				break;
			}
		if (flag == 0)a[++count] = k;
	}
	InsertSort(a, n);
	for (i = 1; i <= n; i++)
		printf("%d ", a[i]);
	printf("\n");


}
#endif