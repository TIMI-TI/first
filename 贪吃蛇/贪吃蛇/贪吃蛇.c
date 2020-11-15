
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#define WIDTH 80 //宽度
#define HEIGHT 30//高度
#define LEN 100 //蛇的最大长度
//-----------------定义各个组成结构-----------------------
//方向定义
enum dir { Up = 72, Down = 80, Left = 75, Right = 77 };
/*
　	 代表键盘按键的数字
　	 “↑”：72
　	 “↓”：80
	“←”：75	
	“→”：77	*/	
 //范围框架的结构
typedef struct 
{	
int height; //高度	
int width;  //宽度	
char brick; //砖块字符
}Frame;

//食物的结构
typedef struct {	int x;  //x坐标	
int y;  //y坐标	
char fch;  //食物字符
}Food;

//蛇的每一节的结构
typedef struct {
	int x;  //x坐标
	int y;  //y坐标
	char sch; //表示字符
}Snode;

//蛇的结构
typedef struct {
	Snode  sk[LEN]; //蛇头及蛇身构成 ，sk[0]是蛇头
	int speed;   //蛇移动的速度，Sleep(speed)
	int len;  //蛇的实际长度
	int dir;  //移动方向
	int score; //得分
}Snake;
//-----------------初始化组成结构-----------------------


//框架初始化
void init_frame(Frame * fm, char ch)
{
	fm->height = HEIGHT;
	fm->width = WIDTH;
	fm->brick = ch;
}
//食物初始化
void init_food(Food* fd, char ch)
{
	fd->x = 1;  //在1,1点
	fd->y = 1;
	fd->fch = ch;
}
//蛇的初始化
void init_snake(Snake* ss, char hch, char ch)
{
	ss->sk[0].x = 0;  //在1,0点处等
		ss->sk[0].y = 0;
	ss->sk[0].sch = hch; //蛇头符号
	for (int i = 1; i < LEN; i++)
	{
		ss->sk[i].x = i;	 //蛇身横向
		ss->sk[i].y = 0;
		ss->sk[i].sch = ch; //蛇身符号
	}
	ss->len = 1;			//初始长度为1
	ss->speed = 300;  //初始速度
	ss->dir = Left;  //初始方向向左
	ss->score = 0;
}
//----------------------函数定义-----------------
// 实现将光标移到指定位置的操作
//将光标移到（x,y）处
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//画范围框架
/*void drawmap1(Frame* fm)
{
	int i, k;
	gotoxy(0, 0);
	for (i = 1; i <= fm->width; i++) printf("%c", fm->brick);  //上
	gotoxy(0, fm->height);
	for (i = 1; i <= fm->width; i++) printf("%c", fm->brick); //下
	gotoxy(0, 1);
	for (i = 1; i < fm->height; i++)
	{
		printf("%c", fm->brick);    //左
		for (k = 2; k < fm->width; k++) printf(" ");
			printf("%c\n", fm->brick);  //右
	}
}*/
//画范围框架
void drawmap2(Frame* fm)
{
	int i;
	for (i = 0; i <= fm->width; i++)
	{
		gotoxy(i, 0);	//上边框
		printf("%c", fm->brick);
			gotoxy(i, fm->height);//将下边框
		printf("%c", fm->brick);
	}
	for (i = 1; i < fm->height; i++)
	{
		gotoxy(0, i);	//将左边框
		printf("%c", fm->brick);

		gotoxy(fm->width, i);//将右边框
		printf("%c", fm->brick);
	}
}
//随机产生食物
void creatfood(Food* fd, Frame* fm)
{
	fd->x = rand() % (fm->width - 5) +
		2;   //计算坐标
	fd->y = rand() % (fm->height - 5) + 2;  //食物不能在边框上
	gotoxy(fd->x, fd->y);   //移动光标
	printf("%c", fd->fch);  //输出食物
}
//输出蛇
void ptsnake(Snake* ss)
{
	int i;
	//输出出蛇头
	gotoxy(ss->sk[0].x, ss->sk[0].y);
	printf("%c", ss->sk[0].sch);

	
		// 输出蛇身
		for (i = 1; i < ss->len; i++)
		{
			gotoxy(ss->sk[i].x, ss->sk[i].y);
			printf("%c", ss->sk[i].sch);
		}
}
//蛇的开始位置
void creatsnake(Snake* ss, Frame* fm)
{
	int i;
	ss->len = 3;
	//假设蛇的开始位置在屏幕中间，头部向左，身体在右
	ss->sk[0].x = fm->width / 2
		;
	ss->sk[0].y = fm->height / 2;

		//纵坐标不变，横坐标为上一节蛇身的坐标值+1
		for (i = 1; i < ss->len; i++)
		{
			ss->sk[i].x = ss->sk[i - 1].x + 1;
			ss->sk[i].y = ss->sk[i - 1].y;
		}
	ptsnake(ss);
}
//根据按键值，判断方向
int getkey(Snake* ss)
{
	int key, pre_dir = ss->dir;//原有方向

	fflush(stdin);//清空缓冲区的字符
		//getch()读取方向键的时候，会返回两次，
		//第一次调用返回0或者224，第二次调用返回的才是实际值
		key = getch();
	key = getch();//获取按键
//如果是方向键
	if (key == Up || key == Down || key == Left || key == Right)
	{ //移动的方向不能和当前方向相反
		//如果当前移动方向和前一次方向相反的话，保持不变
		if (pre_dir == Up && key == Down)
			key = Up;
			if (pre_dir == Down && key == Up)
				key = Down;
		if (pre_dir == Left && key == Right)
			key = Left;
		if (pre_dir == Right && key ==
			Left)
			key = Right;
	}
	else  //非方向键
		key = ss->dir; //保持原有方向	
	return key; // 返回方向
}

//移动一步
void smove(Snake* ss, Frame* fm)
{    int i;
if (kbhit()) //有按键按下
ss->dir = getkey(ss);  //取得方向	
//移动
//在蛇尾处输出空格即擦去蛇尾
gotoxy(ss->sk[ss->len - 1].x, ss->sk[ss->len - 1].y);
printf(" ");
//将蛇的每一节依次向前移动一节（蛇头除外）
for (i = ss->len - 1; i > 0; i--)
{
	ss->sk[i].x = ss->sk[i - 1].x; //前一个位置
	ss->sk[i].y = ss->sk[i - 1].y; //前一个位置
}


//判断蛇头应该往哪个方向移动
switch (ss->dir)
{
case Left:  ss->sk[0].x--;break;  //往左
case Right:	ss->sk[0].x++; break;  //往右
case Up:	ss->sk[0].y--;break;  //往上
case Down:	ss->sk[0].y++; break;  //往下
}
ptsnake(ss);  //输出蛇
}
//判断游戏结束
int over(Snake* ss, Frame* fm)
{
	int f = 0;
	//蛇头碰到上下边界

	
		if (ss->sk[0].y == 0 || ss->sk[0].y == fm->height)
			f = 1;
	//蛇头碰到左右边界
	if (ss->sk[0].x == 0 || ss->sk[0].x == fm->width)
		f = 1;
	return f;
}


main()
{
	Frame  sfm;  //范围
	Food  sfd;   //食物
	Snake  ssa;  //蛇
	FILE* fp;  //文件
	//变量初始化
	init_frame(&sfm, '#');   //设置边框大小及表示符号#
	init_food(&sfd, '*');    //设置食物及表示符号*
	init_snake(&ssa, '@', '+'); //设置蛇及表示符号@+	
	srand((unsigned int)time(NULL)); //随机函数种子
	drawmap2(&sfm);  //绘制边框
	creatfood(&sfd, &sfm);  //放置第一个食物
	creatsnake(&ssa, &sfm); //在区域中间放置蛇
	while (1)  //进入游戏环节
	{
		smove(&ssa, &sfm); //移动一下
		if (over(&ssa, &sfm)) break;  //游戏结束

		
			if (ssa.sk[0].x == sfd.x && ssa.sk[0].y == sfd.y) //吃食物
			{
				ssa.score += 10; //加分
				ssa.len++;   //蛇身加长
				creatfood(&sfd, &sfm);  //产生新食物
			}
		Sleep(ssa.speed);//等待
	}
	//游戏结束
	gotoxy(10, 10);
	printf("游戏结束!\n");
	gotoxy(10, 12);
	printf("得分：%d   ", ssa.score );

	
		printf("按回车键返回...");
		/*******在文件中记录得分*****/ 
		// 记录得分	
		fp = fopen("snake.txt", "a"); 
		fprintf(fp, "%d\n", ssa.score); 
		fclose(fp);
		//输出记录	
		fp=fopen("snake.txt","r");	
		printf("      得分榜:\n");
		while(1)	
		{ int x;	 
		fscanf(fp,"%d",&x);	  
		if(feof(fp)) break;	 
		printf("        %d\n",x);}
		fclose(fp);
		/*******************************/

	
		Sleep(2000); //等待两秒getchar(); //按回车键返回	
}

