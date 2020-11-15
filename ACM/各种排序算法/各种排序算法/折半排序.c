/*#include<stdio.h>
#include<stdlib.h>*/       //Bianry：折半
//稳定排序
void BInsert_Sort(int* a, int n,int *c)
{
	int i, j;
	for (i = 0; i < n; ++i)
		c[i] = a[i];
	for (i = 1; i < n; ++i)//从第二个元素开始在前面的位置用二分查找应该插入的位置
	{
		if (c[i] < c[i - 1])
		{
			int t = c[i];
			int low = 0, high = i - 1, m;
			while (low <= high)
			{
				m = (low + high) / 2;
				if (c[m] > c[i]) high = m - 1;
				else low = m + 1;
			}
			for (j = i - 1; j >= high + 1; --j)
			{
				c[j + 1] = c[j];
			}

			c[high + 1] = t;
		}
	}
}

#if 0
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
#endif