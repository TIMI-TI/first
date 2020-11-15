#include<stdio.h>
#include<stdlib.h>               //Bianry：折半
 void BInsert_Sort(int *a,int n)
{
	int i,j;
	for (i = 1; i < n; ++i)//从第二个元素开始在前面的位置用二分查找应该插入的位置
	{
		if (a[i] < a[i - 1])
		{
			
			int t = a[i];
			int low = 0, high = i - 1, m;
			while (low <= high)
			{
				m = (low + high) / 2;
				if (a[m] > a[i]) high = m - 1;
				else low = m + 1;
			}
			for (j = i - 1; j >= high + 1; --j)
			{
				a[j + 1] = a[j];
			}
			
			a[high + 1] = t;
		}
	}

}


int main()
{
	int a[10];
	for (int i = 0; i < 10; i++)
		a[i] = rand() % 100;
	for (int i = 0; i < 10; ++i)
		printf("%d ", a[i]);
	printf("\n");
	BInsert_Sort(a, 10);
	for (int i = 0; i < 10; ++i)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}