#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
void testcount(int* a, int* c, int n)
{
	int i;
	printf("测试计数排序\n----------------------------\n");
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	CountSort(a, c, n);//计数排序
	for (i = 0; i < n; i++)
		printf("%d ", c[i]);//输出排序结果
	printf("\n");
	printf("\n----------------------------\n");
}
void testinsert(int* a, int* c, int n)
{
	int i;
	printf("测试插入排序\n----------------------------\n");
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	InsertSort(a, n, c);//插入排序
	for (i = 0; i < n; i++)//输出排序结果
		printf("%d ", c[i]);
	printf("\n");
	printf("\n----------------------------\n");
}
void testbinasort(int* a, int* c, int n)
{
	printf("测试折半排序\n----------------------------\n");
	for (int i = 0; i < 10; ++i)
		printf("%d ", a[i]);
	printf("\n");

	BInsert_Sort(a, 10, c);//折半排序
	for (int i = 0; i < 10; ++i)//输出排序结果
		printf("%d ", c[i]);
	printf("\n");
	printf("\n----------------------------\n");
}
void testShell(int* a, int* c, int* d, int n)
{
	int i;
	printf("测试希尔排序\n----------------------------\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	for (int i = 0; i < 5; i++)
		d[i] = pow(2, 4 - i + 1) - 1;//生成增量序列
	for (i = 0; i < 5; ++i)
		printf("%d ", d[i]);//输出增量序列
	printf("\n");
	for (int i = 0; i < 5; ++i)
		ShellInsert(a, c, d[i], n);//希尔排序
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", c[i]);//输出排序结果
	}
	printf("\n");
}
void testquick(int* a)
{
	int i;
	printf("测试快速排序\n----------------------------\n");
	for (i = 0; i < 10; ++i)
		printf("%d ", a[i]);
	printf("\n");
	QuickSort(a, 0, 9);//快速排序
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("\n----------------------------\n");
}



int main()
{
	int* a, n = 10, i, d[10];
	int* c;
	c = (int*)malloc(sizeof(int) * n);
	a=(int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (i = 0; i < n; i++)
		a[i] = rand() % 51 + 100;//生成一个随机序列用于排序
	//测试计数排序
	testcount(a, c, n);
	//测试插入排序
	testinsert(a, c, n);
	//测试折半排序
	testbinasort(a, c, n);
	//测试希尔排序
	testShell(a, c, d, n);
	//测试快速排序
	testquick(a);
	return 0;
}