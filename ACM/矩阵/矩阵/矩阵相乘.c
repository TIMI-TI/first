#include<stdio.h>
main()
{
	int a[10][10], b[10][10], c[10][10];
	int i, j, k,m,n,p,q;
	printf("请输入两个矩阵的大小(第一个矩阵的列数必须等于第二个矩阵的行数)：\n");
	scanf("%d%d%d%d", &m, &n, &p, &q);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%d", a[i][j]);
		printf("\n");
	}printf("\n");

	for (i = 0; i < p; i++)
		for (j = 0; j < q; j++)
			scanf("%d", &b[i][j]);
	for (i = 0; i < p; i++)
	{
		for (j = 0; j < q; j++)
			printf("%d", b[i][j]);
		printf("\n");
	}printf("\n");
	for(i=0;i<m;i++)
		for (j = 0; j < q; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < n; k++)
			{
				c[i][j] = a[i][k] * b[k][j] + c[i][j];
			}
		}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < q; j++)
			printf("%d", c[i][j]);
		printf("\n");
	}printf("\n");
}