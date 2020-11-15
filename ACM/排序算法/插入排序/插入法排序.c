#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void InsertSort(int a[], int n) {
	int i, j;
	for (i = 1; i <= n; i++)
	{
		if (a[i] < a[i - 1]) 
		{
			
			for (j = i - 1; a[j] > a[i]&&j>0; j--)
			{
				a[j + 1] = a[j];
			}
			a[j+1] = a[0];
		}

	}
}
main() {

	int a[20],  n = 10,i,k,count=0;
	
	while (count < n) {
		k = rand() % 100;
		int flag = 0;
		for(i=1;i<=n;i++)
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