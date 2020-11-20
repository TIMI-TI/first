#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<assert.h>
#include<graphics.h>
#include<conio.h>
#include<stdint.h>
#include<time.h>
#define FILE_BUFFER_LENGTH 30000

/*
一元多项式计算器实现
功能：  Add--加法
		sub--减法
		mul--乘法
		div--除法
		evaluate--求值
		der--求导
		intergral--求积分
		fac--因式分解
*/
typedef struct node
	{//采用链式存储结构存储数据，便于数据的插入删除等操作
		double coef;//系数
		int expn;//指数
		struct node* next;
	}poly, * polyPtr;
void init(polyPtr* poly1)
{
	*poly1 = (polyPtr)malloc(sizeof(poly));
	(*poly1)->next = NULL;
	(*poly1)->coef = 0;
	(*poly1)->expn = 0;
}
void HelpWord()
{
	
	printf("\t\t\t\t\t一元多项式计算器帮助文档\n");
	printf("\n一、功能模块\n");
	printf("[0]Inputpoly功能：\n  该功能为用户自主输入多项式，满足用户解决实际问题的需要。\n使用方法：\n  用户根据多项式的系数-指数的顺序依次输入多项式所有项的数据（任一数据不能是444），最后输入444代表输入结束（因为444是个不吉利的数字，哈哈哈~~~）。\n注意：用户需要输入两个多项式，【默认第一多项式编号为1，第二个多项式编号为2，在后面求导、积分，求值的操作所选择的多项式以这个编号为准】！！！如果用户最初没有输入多项式，那么系统自动调用上一次使用的多项式！！！\n");
	printf("[1]Help功能：\n  使用说明！！！\n");
	printf("[2]Add功能：\n  该功能为加法运算，对用户输入的两个多项式进行打印，然后输出两个多项式相加的和，最后按任意键返回主菜单！！！\n");
	printf("[3]Sub功能：\n  该功能为减法运算，对用户输入的两个多项式进行打印，然后输出两个多项式相减的差，最后按任意键返回主菜单！！！\n");
	printf("[4]Mul功能：\n  该功能为乘法运算，对用户输入的两个多项式进行打印，然后输出两个多项式相乘的积，最后按任意键返回主菜单！！！\n");
	printf("[5]Div功能：\n  该功能为除法运算，对用户输入的两个多项式进行打印，然后输出两个多项式相除的商，最后按任意键返回主菜单！！！\n");
	printf("[6]Evaluate功能：\n  该功能为求值运算，用户可选择对输入的哪个表达式进行运算（表达式1默认为第一次输入对的表达式），然后输入X的值，最终返回这个多项式的值，按任意键返回！！！\n");
	printf("[7]Der功能：\n  该功能为求导运算，同求值计算一样，系统会根据用户的选择对表达式进行求导运算，然后输入求导的表达式，按任意键返回主菜单！！！\n");
	printf("[8]Intergral功能：\n  该功能为求导的逆运算，对表达式进行积分！！！\n");
	printf("[9]Fac功能：\n  该功能为因式分解，用户操作步骤同求导和积分！！！\n");
	printf("[10]exit功能：\n  退出系统！！！\n");

}
polyPtr getpoly(char* filename)
{
	
	FILE* f1;
	polyPtr poly1=NULL,p,pTail;
	
	f1 = fopen(filename, "r");
	if (!f1)return poly1;
	init(&poly1);
	pTail = poly1;
	
	while (!feof(f1))
	{
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		fscanf(f1, "%lf %d", &(p->coef), &(p->expn));
		/*if (p->coef == 0)
		{
			free(p);
			continue;
		}*/
		p->next = pTail->next;
		pTail->next = p;
		pTail = p; 
	}
	return poly1;
}
void printpoly(polyPtr poly1)
{
	if (!poly1)return;
	polyPtr p= poly1->next;
	if (p->coef!=0)
	{
		if (p->expn != 0)
			printf("%3.1f x^%d", p->coef, p->expn);
		else
			printf("%3.1f x", p->coef);
	}
	p = p->next;
	while (p)
	{
		if (p->expn != 0)
		{
			printf("%+3.1f x^%d", p->coef, p->expn);
		}
		else
			printf("%+3.1f", p->coef);
		p = p->next;
	}
	printf("\n");
}
void Destory(polyPtr poly)
{
	polyPtr p=poly->next,q;
	while (p)
	{
		q = p->next;
   		free(p);
		p = q;
	}
}
polyPtr Add(polyPtr poly1, polyPtr poly2)
{
	polyPtr p1 = poly1->next, p2 = poly2->next, poly3, p, p3;
	init(&poly3);
	p3 = poly3;
	while (p1 && p2)
	{
		if (p1->expn > p2->expn)
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p1->coef;
			p->expn = p1->expn;
			p3->next = p;
			p3 = p;
			p1 = p1->next;
		}
		else if (p1->expn < p2->expn)
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = (p2->coef);
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
		}
		else
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p2->coef + p1->coef;
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
			p1 = p1->next;
		}
	}
	while (p1)
	{
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p1->coef;
		p->expn = p1->expn;
		p3->next = p;
		p3 = p;
		p1 = p1->next;
	}
	while (p2)
	{
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p2->coef;
		p->expn = p2->expn;
		p3->next = p;
		p3 = p;
		p2 = p2->next;
	}
	return poly3;

}
//加法
polyPtr Addpoly(polyPtr poly1,polyPtr poly2)
{
	
	polyPtr p1 = poly1->next, p2 = poly2->next,poly3,p,p3;
	init(&poly3);
	p3 = poly3;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);	
	printf("\n\t\t\t\t\t   ***您选择了加法***\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
	printf("\n多项式1为：");
	printf("\n");
	printpoly(poly1);
	printf("\n");
	printf("多项式2为：");
	printf("\n");
	printpoly(poly2);
	printf("\n");

	while (p1 && p2)
	{
		if (p1->expn > p2->expn)
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p1->coef;
			p->expn = p1->expn;
			p3->next = p;
			p3 = p;
			p1 = p1->next;
		}
		else if (p1->expn < p2->expn)
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = (p2->coef);
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
		}
		else
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p2->coef + p1->coef;
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
			p1 = p1->next;
		}
	}
	while (p1)
	{
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p1->coef;
		p->expn = p1->expn;
		p3->next = p;
		p3 = p;
		p1 = p1->next;
	}
	while (p2)
	{
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p2->coef;
		p->expn = p2->expn;
		p3->next = p;
		p3 = p;
		p2 = p2->next;
	}
	return poly3;
	
}
//减法
polyPtr Subpoly(polyPtr poly1, polyPtr poly2)
{
	polyPtr p1 = poly1->next, p2 = poly2->next, poly3, p, p3;
	init(&poly3);
	p3 = poly3;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("\n\t\t\t\t\t   ***您选择了减法***\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
	//输出传入的多项式
	printf("\n多项式1为：");
	printf("\n");
	printpoly(poly1);
	printf("\n");
	printf("多项式2为：");
	printf("\n");
	printpoly(poly2);
	printf("\n");
	//算法：两个链表按照一定规则逐项相加，细节如下
	while (p1 && p2)
	{//两个链表都不为空，指数大的直接入p3中   
		if (p1->expn > p2->expn)
		{                                 
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p1->coef;
			p->expn = p1->expn;
			p3->next = p;
			p3 = p;
			p1 = p1->next;
		}
		else if (p1->expn < p2->expn)
		{
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = -(p2->coef);
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
		}
		else
		{//相等的情况下就系数相加，指数不变
			p = (polyPtr)malloc(sizeof(poly));
			p->next = NULL;
			p->coef = p1->coef - p2->coef;
			p->expn = p2->expn;
			p3->next = p;
			p3 = p;
			p2 = p2->next;
			p1 = p1->next;
		}
	}
	while (p1)
	{//当p2链表遍历完了，p1没有完，直接将P1后面的节点都添加到P3
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p1->coef;
		p->expn = p1->expn;
		p3->next = p;
		p3 = p;
		p1 = p1->next;
	}
	while (p2)
	{//当p1链表遍历完了，p2没有完，直接将P2后面的节点都添加到P3
		p = (polyPtr)malloc(sizeof(poly));
		p->next = NULL;
		p->coef = p2->coef;
		p->expn = p2->expn;
		p3->next = p;
		p3 = p;
		p2 = p2->next;
	}
	return poly3;
}
//乘法
polyPtr Mulpoly(polyPtr poly1, polyPtr poly2)
{

	polyPtr p1 = poly1->next, p2 = poly2->next, p, poly3, p3,p4,q;
	q = p2;
	init(&poly3);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("\n\t\t\t\t\t   ***您选择了乘法***\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

	printf("\n多项式1为：");
	printf("\n");
	printpoly(poly1);
	printf("\n");
	printf("多项式2为：");
	printf("\n");
	printpoly(poly2);
	printf("\n");
	while (p1)
	{	
		polyPtr poly4,pTail;
		init(&poly4);
		pTail = poly4;
		while (p2)
		{
			p4 = (polyPtr)malloc(sizeof(poly));
			p4->next = NULL;
			
			p4->coef = (p1->coef) * (p2->coef);
			p4->expn = (p1->expn) + (p2->expn);
			
			pTail->next = p4;
			pTail = p4;
			p2 = p2->next;
			
		}
		p2 = q;
		poly3 = Add(poly3, poly4);
		Destory(poly4);
		
		p1 = p1->next;
	}
	return poly3;
}
//除法
polyPtr Divpoly(polyPtr poly1, polyPtr poly2)
{
	

	IMAGE img;
	initgraph(300, 200);
	// 读取图片至绘图窗口
	loadimage(NULL, _T("G:\\图片\\OIP.jpg"), 300, 200);
	// 按任意键退出
	putimage(0, 0, &img);
	TCHAR w[] = _T("功能暂未开发");
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	void settextcolor(COLORREF blue);
	f.lfHeight = 20;                      // 设置字体高度为 50
	_tcscpy(f.lfFaceName, _T("微软雅黑"));    // 设置字体为“华文彩云”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	outtextxy(105, 150, w);
	getch();
	closegraph();
	return NULL;
}
double Evaluatepoly(int a,polyPtr poly)
{//将每项的值都求出来相加
	double result=0;//存储和值
	polyPtr p=poly->next;
	while (p)
	{//循环算出每个结点的值
		double m = pow(a, p->expn);//未知数的次方的值
		double n = (p->coef) * m;//每项的值
		result = result + n;//每项相加
		p = p->next;
	}
	return result;
}

//求导
polyPtr Derpoly(polyPtr poly)
{//根据求导规则求导
	printf("表达式是：\n");
	printpoly(poly);
	printf("\n");
	polyPtr p = poly->next,q,P=poly;
	q = p;
	while (p)
	{//对每个结点都求导
		
		p->coef = p->expn * p->coef;//系数
		p->expn = p->expn - 1;//指数
	
		p = p->next;
	}
	//对系数为0的项进行删除
	while (q)
	{
		if (q->coef == 0)
		{
			P->next = q->next;
			q = q->next;
			continue;
		}
		P = q;
		q = q->next;
	}
	return poly;
}
//求积分
polyPtr Intergralpoly (polyPtr poly)
{//根据求导规则反过来求积分
	printf("多项式是：\n");
	printpoly(poly);
	printf("\n");
	polyPtr p = poly->next;
	while (p)
	{//循环对每个结点都求积分
		p->coef = p->coef / (double)(p->expn + 1);//系数
		p->expn = p->expn + 1;//指数
		p = p->next;
	}
	return poly;
}
//因式分解
polyPtr Facpoly(polyPtr poly)
{
	//polyPtr p = poly->next,q;
	//q = p;
	//while (q->next)//找到链表末尾，就是幂指数最小的
	//{
	//	q = q->next;
	//}
	//while (p)
	//{
	//		
	//}
	IMAGE img;
	initgraph(300, 200);
	// 读取图片至绘图窗口
	loadimage(NULL, _T("G:\\图片\\OIP.jpg"), 300, 200);
	// 按任意键退出
	putimage(0, 0, &img);
	TCHAR w[] = _T("功能暂未开发");
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	void settextcolor(COLORREF blue);
	f.lfHeight = 20;                      // 设置字体高度为 20
	_tcscpy(f.lfFaceName, _T("微软雅黑"));    // 设置字体为“微软雅黑”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	outtextxy(105, 150, w);
	getch();
	closegraph();

	return NULL;
}
void fprintpoly(polyPtr poly1)
{
	FILE* fp;
	if (poly1 == NULL)return;
	polyPtr p = poly1->next;
	fp=fopen("值.txt", "a+");
	if (!poly1)return;
	if (p->coef != 0)
	{
		if (p->expn != 0)
			fprintf(fp,"结果是：%3.1f x^%d", p->coef, p->expn);
		else
			fprintf(fp,"结果是：%3.1f x", p->coef);
	}
	p = p->next;
	while (p)
	{
		if (p->expn != 0)
		{
			fprintf(fp,"%+3.1f x^%d", p->coef, p->expn);
		}
		else
			fprintf(fp,"%+3.1f", p->coef);
		p = p->next;
	}
	printf("\n");
	fclose(fp);
}

void Meau()
{//菜单
		printf("\t\t\t\t========================================\n");
		//printf("============================================================================================================\n");
		printf("\t\t\t\t            一元多项式计算器            \n");
		printf("\t\t\t\t========================================\n");
		printf("\t\t\t\t功能选项:\n");
		printf("\t\t\t\t****************************************\n");
		printf("\t\t\t\t\t[0]Inputpoly       [1]Help\n\n");
		printf("\t\t\t\t\t[2]Add             [3]Sub\n\n");
		printf("\t\t\t\t\t[4]Mul             [5]Div\n\n");
		printf("\t\t\t\t\t[6]Evaluate        [7]Der\n\n");
		printf("\t\t\t\t\t[8]Intergral       [9]Fac\n\n");
		printf("\t\t\t\t\t[10]Exit\n\n");
		printf("\t\t\t\t\t新用户请查看帮助文档[1]！！！\n");
		printf("\t\t\t\t****************************************\n");
}
//转移表的定义
polyPtr(*table[])(polyPtr,polyPtr) = { NULL,NULL,Addpoly,Subpoly,Mulpoly,Divpoly};

//隐藏光标
void HideConsoleCursor(void)
	{
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
	}
//用户输入
void UserInput()
{
	FILE* fp, * fp1;
	double num, num1;
	int k = 0, k1 = 0;
	fp = fopen("poly1.txt", "w");
	fclose(fp);
	fp = fopen("poly1.txt", "a+");

	printf("请输入多项式1(输入444结束):>");
	while (scanf("%lf", &num), num != 444)
	{
		if (k == 0) {
			fprintf(fp, "%.1lf", num);
		}
		else
		{
			if (k % 2 == 0)
			{
				fprintf(fp, " %.1lf", num);
			}
			else
				fprintf(fp, " %d", (int)num);
		}
		k++;
	}
	fclose(fp);
	printf("请输入多项式2(输入444结束):>");
	fp1 = fopen("poly2.txt", "w");
	fclose(fp1);
	fp1 = fopen("poly2.txt", "a+");
	while (scanf("%lf", &num1), num1 != 444)
	{
		if (k1 == 0) {
			fprintf(fp, "%.1lf", num1);
		}
		else
		{
			if (k1 % 2 == 0)
			{
				fprintf(fp1, " %.1lf", num1);
			}
			else
				fprintf(fp1, " %d", (int)num1);
		}
		k1++;
	}
	fclose(fp1);
	printf("输入成功！正在跳转....\n");
	Sleep(1000);
	system("cls");


}

int main()
{
	HideConsoleCursor();//隐藏光标
	//界面设置
	system("title 一元多项式计算器");
	system("mode con cols=108 lines=40");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	while (1)
	{
		polyPtr poly3, poly1, poly2,p1,p2;
		FILE* fp;
		int x,a;
		double result=0;
		int select = 0;
		char s1[20] = "poly1.txt";
		char s2[20] = "poly2.txt";
		poly1 = getpoly(s1);
		poly2 = getpoly(s2);
		

		//菜单设置
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		Meau();
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

		printf("请选择功能：>");
		scanf("%d", &select);
		if (select == 10)break;//退出系统
		else if (select > 10) 
		{ 
			printf("输入错误，请重试...\n"); 
			system("pause");
			system("cls"); 
			continue; 
		}
		else if (select == 1)
		{
			system("cls");
			system("color 70");
			HelpWord();
			system("pause");
			system("cls");
			system("color 07");
		}
		else if (select == 6)
		{//求值操作
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("\n\t\t\t\t\t   ***您选择了求值***\n\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

			printf("是否选择多项式1(1--是\t0--否)>\n");
			scanf("%d", &a);
			if (a == 0) {
				p1 = poly2;
			}
			else p1 = poly1;
			printf("请输入X的值：>");
			scanf("%d", &x);
			printf("\n多项式：\n");
			printpoly(p1);
			printf("\n");
			result = Evaluatepoly(x, p1);
			printf("多项式的值是：%.1lf\n\n", result);//输出多项式的值
			
			fp = fopen("值.txt", "a+");//写入文件
			fprintf(fp, "多项式的值是：%.1lf\n",result);
			fclose(fp);

			system("pause");
			system("cls");
		}
		else if (select == 7)
		{//求导操作
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("\n\t\t\t\t\t   ***您选择了求导***\n\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

			printf("是否选择多项式1(1--是\t0--否)>\n");
			scanf("%d", &a);
			if (a == 0) {
				p1 = poly2;
			}
			else p1 = poly1;
			poly3 = Derpoly(p1);
			printf("多项式求导的结果：\n");
			printpoly(poly3);//输出求导结果

			FILE* fp;
			fp = fopen("值.txt", "a+");
			fprintf(fp, "多项式的求导结果为：");
			fclose(fp);
			fprintpoly(poly3);//写入文件
			fp = fopen("值.txt", "a+");
			fprintf(fp, "\n");
			fclose(fp);

			system("pause");
			system("cls");
		}
		else if (select == 8)
		{//求积分操作
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			printf("\n\t\t\t\t\t   ***您选择了求积分***\n\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);


			printf("是否选择多项式1(1--是\t0--否)>\n");
			scanf("%d", &a);
			if (a == 0) {
				p1 = poly2;
			}
			else p1 = poly1;
			Intergralpoly(p1);
			printf("结果为：\n");
			printpoly(p1);

			FILE* fp;
			fp = fopen("值.txt", "a+");
			fprintf(fp, "多项式的积分结果为：");
			fclose(fp);
			fprintpoly(p1);
			fp = fopen("值.txt", "a+");
			fprintf(fp, "\n");
			fclose(fp);

			system("pause");
			system("cls");

		}
		else if (select == 9)
		{
			Facpoly(poly1);
			system("cls");
		}
		else if (select == 0)
		{
			UserInput();
		}
		else 
		{
			/*clock_t start, end;
			start = clock();*/
			//通过转移表进入函数
			poly3 = table[select](poly1, poly2);
			/*end = clock();
			printf("时间为：%lf\n", (double)(end - start)/CLK_TCK);*///时间测试
			printf("结果为:\n");
			printpoly(poly3);//输出结果

			FILE* fp;
			fp = fopen("值.txt", "a+");
			if(select==2)
				fprintf(fp, "多项式相加的结果为：");
			else if(select==3)
				fprintf(fp, "多项式相减的结果为：");
			else if(select==4)
				fprintf(fp, "多项式相乘的结果为：");

			fclose(fp);
			fprintpoly(poly3);
			fp = fopen("值.txt", "a+");
			fprintf(fp, "\n");
			fclose(fp);

			if(select!=5)
				system("pause");
			system("cls");
		}
		/*Destory(poly1);
		Destory(poly3);
		Destory(poly2);*/
	}
	return 0;
}