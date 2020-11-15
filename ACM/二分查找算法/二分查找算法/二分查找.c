#include<stdio.h>
//前提是按顺序存放在数组里面(即是在数组中的元素已经排好序）；
#define MaxSize 10
typedef int Position;
typedef int ElementType;
typedef int Status;
typedef struct {
	ElementType data[MaxSize];
	Position last;
}List;
Position BinarySearch(List *L, ElementType X)
{
	int low = 0,high=9,mid;
	if (!L) 
	{
		return -1;
	}
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (L->data[mid] == X)return mid;
		else if (L->data[mid] < X)low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}
int main()
{
	List L;
	ElementType X;
	for (int i = 0; i < MaxSize; ++i)
		L.data[i] = rand() % 100;//随机生成一个序列
	X = L.data[MaxSize - 5];//确定要查找这个数
	L.last = MaxSize-1;
	for(int i=0;i<L.last;++i)
		for(int j=0;j<L.last-i;++j)
			if (L.data[j] > L.data[j + 1]) { int t = L.data[j]; L.data[j] = L.data[j + 1]; L.data[j + 1] = t; }//对生成的这个序列进行排序
	int m=BinarySearch(&L, X);//二分查找
	for (int i = 0; i < MaxSize; ++i)
		printf("%d ", L.data[i]);//输出这个序列
	printf("\n%d", m);//输出查找到的数的下标（已经排序过的下标）
	return 0;
}