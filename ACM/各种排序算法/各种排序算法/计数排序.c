//#include<stdio.h>//计数排序（稳定排序）
//#include<stdlib.h>//时间复杂度时n，但是空间复杂度很高（随排序序列中最小元素的值和最大元素的值的大小变化）
void CountSort(int* a, int* c, int n)
{//该算法计算值为100-150之间的数，这样就可以通过映射减少0-99之间的空间大小；
	int* b, i;
	b = (int*)malloc(sizeof(int) * 51);
	for (i = 0; i < 51; i++)
		b[i] = 0;
	for (i = 0; i < n; i++)
		b[a[i]-100]++;

	for (i = 1; i < 51; i++)
		b[i] += b[i - 1];//这时候，b[i]-1（从0开始，所以位置-1）就是就是对应下标最后放的位置

	for (i = n; i > 0; i--)
	{
		c[b[a[i - 1]-100] - 1] = a[i - 1];//从后往前读，这样就把后面的数放在了最后一次放的位置，这就保证了算法的稳定性。
		b[a[i - 1]-100]--;//这样就把对应下标最后放的位置前移一个
	}
	free(b);
}
#if 0
main()
{
	int* a, n = 10, i, * c;
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int) * n);
	c = (int*)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		a[i] = rand() % 51+100;
	for (i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
	CountSort(a, c, n);
	for (i = 0; i < n; i++)
		printf("%d ", c[i]);
	printf("\n");
}
#endif