#ifndef GOBANG_RULES_H
#define GOBANG_RULES_H

#include "Gobang_Base.h"

class Gobang_Rules : public Gobang
{
public:
	void SpecificOpening(); //指定开局
	int WhetherChange(Point step[]); //是否三手交换判断
	void WhiteFour(); //白4坐标
	void BlackFive(int &x,int &y); //黑5坐标
	void SaveOnePoint(int &x, int &y); //从黑5打点坐标中选择一个
	int IsWin(int x,int y); //判断某一方是否连成五子
};

//指定开局
void Gobang_Rules::SpecificOpening()
{
	srand((unsigned)time(NULL));
	int k = random(0, 25); //随机得到一种开局
	setBoard(7, H, BLACK); //黑1位于(7，H)
	if (k >= 0 && k < 13) //前13种为直指开局
	{
		setBoard(6, H, WHITE); //白2位于(6, H)
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK); //找到对应于棋盘的位置，落子
	}
	else if (k >= 13 && k < 26) //后13种为斜指开局
	{ 
		setBoard(6, I, WHITE); //白2位于(6, I)
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK); //找到对应于棋盘的位置，落子 
	}
}

//是否三手交换判断
int Gobang_Rules::WhetherChange(Point step[])
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		if (step[0].x == Lib1[i][0].x && step[0].y == Lib1[i][0].y) //符合Lib1中黑2的位置坐标
		{
			for (j = 1; j <= 4; j++)
			{
				if (step[1].x == Lib1[i][j].x && step[1].y == Lib1[i][j].y) //符合黑2坐标对应的白3坐标
				{
					cout << "白方选择交换。" << endl;
					return 2; //交换棋子颜色
				}
			}
		}
	}
	cout << "白方选择不交换。" << endl;
	return 1;
}

//白4坐标
void Gobang_Rules::WhiteFour()
{
	//暂定为由随机数产生
	int x, y;
	do {
		srand((unsigned)time(NULL));
		x = random(6, 8);
		y = random(6, 8);	
	} while (setBoard(x, y, WHITE) != 0);	//判断该坐标是否已有棋子
		cout << "(" << x << " , " << y << ")" << endl;
}

//黑5坐标
void Gobang_Rules::BlackFive(int &x, int &y)
{	
	//暂定由随机数产生
	do {
		srand((unsigned)time(NULL));
		x = random(5, 9);
		y = random(5, 9);
	} while (setBoard(x, y, BLACK) != 0); //判断该坐标是否已有棋子
	cout << "(" << x << " , " << y << ")" << endl;
}

//从黑5打点坐标中选择一个
void Gobang_Rules::SaveOnePoint(int &x,int &y)
{
	//暂定为第一个打点坐标
	x = steps[2].x;
	y = steps[2].y;
}

//判断某一方是否连成五子
int Gobang_Rules::IsWin(int x, int y)
{
	int i, tx, ty, len;
	int Side = getBoard(x, y);//取得落子颜色
	for (i = 0; i < 4; i++)//4个方向的循环
	{
		tx = x; ty = y;//设置观察起点
		len = 0;//设置计数器
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)//连珠条件
		{
			tx -= Direct[i][0];//沿一个方向
			ty -= Direct[i][1];//移动观察点
		}
		tx += Direct[i][0];
		ty += Direct[i][1];
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)//连珠条件
		{
			len++;//计数
			tx += Direct[i][0];//沿相反方向
			ty += Direct[i][1];//移动观察点
		}
		if (len >= 5)//比较连珠数目
			return 0;//获胜
	}
	return -1;//为获胜
}
#endif
