#include<stdio.h>
//算法：先找出每行的最大值，在判断这个值是不是所在列的最小值，否则不是鞍点；
main()
{
	int m, n,i,j,k,t,a[100][100],max,flag;
	scanf("%d%d", &m, &n);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%d", a[i][j]);
		printf("\n");
	}
	for (i = 0; i < m; i++)
	{
		flag = 0;
		max = 0;//找到最大点
		for (j = 0; j < n; j++)
		{
			if (a[i][j] > a[i][max])
			{
				max = j;
			}
		}
	}
		//判断是不是该列的最小点
		for (k = 0; k < m; k++)
			if (a[k][max] < a[i][max])flag = 1;
		if (flag == 0) { printf("a[%d][%d]", i,max); break; }
	}
	if(flag==1)
	printf("没有鞍点\n");

}