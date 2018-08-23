#ifndef GOBANG_BASE_H
#define GOBANG_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

#define EMPTY  0 //空子
#define BLACK  1 //黑子
#define WHITE  2 //白子
#define INFINITY 100000
#define random(a,b) (rand()%(b-a+1)+a) //取值范围为[a,b]的随机数
#define E 4
#define F 5
#define G 6
#define H 7 
#define I 8
#define J 9 
#define K 10
#define FIVE 0  //五连
#define FOUR 1  //活四
#define FFOUR 2  //冲四
#define DFOUR 3  //死四
#define THREE 4  //活三
#define STHREE 5 //眠三
#define DTHREE 6  //死三
#define TWO 7  //活二
#define STWO 8 //眠二
#define ANALSISED   255//已分析过的
#define TOBEANALSIS -1  //待分析的

struct Step {
	int x, y, color;
};
typedef struct Point {
	int x;
	int y;
};
static int MAN, COM;
static int Board[15][15]; //棋盘
static int points; //打点数
static stack <int> sx; //记录下棋步骤
static stack <int> sy; //记录下棋步骤
static Point steps[5]; //棋子位置记录
static int TypeRecord[15][15][4];  //记录全部棋子在四个方向上的分析结果
static int TypeCount[2][15];  //记录分析结果的统计值   
static int Direct[4][2] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } };  //四个方向上x,y分别进行的移动值

//26这种开局的黑3位置坐标，前13个为直指开局，后13个为斜指开局
static Point Lib[26] = {
	{ 10,H },{ 10,I },{ 10,J },{ 9,I },{ 9,J },{ 8,I },
{ 8,J },{ 7,H },{ 7,I },{ 7,J },{ 6,H },{ 6,I },{ 6,J },
{ 10,J },{ 9,J },{ 8,J },{ 7,J },{ 6,J },{ 8,I },{ 7,I },
{ 6,I },{ 7,H },{ 6,H },{ 7,G },{ 6,G },{ 5,F }
};

//三手交换中可交换的位置坐标，每行首个坐标为白2，其他为对应的黑3
static Point Lib1[8][5] = {
	{ 9,G,10,F,6,F,10,J,6,J },
{ 9,I,10,F,6,F,10,J,6,J },
{ 7,G,10,F,6,F,10,J,6,J },
{ 7,I,10,F,6,F,10,J,6,J },
{ 9,H,6,F,6,J },{ 8,G,10,J,6,J },
{ 8,I,10,F,6,F },{ 7,H,10,F,10,J }, 
};

static int PosValue[15][15] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };


class Gobang
{
public:
	Gobang()
	{
		Init_Board(); 
	}

	void Init_Board() //初始化棋盘
	{
		int i, j;
		for (i = 0; i < 15; i++)
			for (j = 0; j < 15; j++)
				Board[i][j] = EMPTY; //将棋盘全部置空
	}

	void Print_Checkerboard() //打印棋盘
	{
		int i, j;
		cout << "  A B C D E F G H I J K L M N O" << endl;
		for (i = 0; i < 15; i++)
		{
			cout << setw(2) << 15 - i;
			for (j = 0; j < 15; j++)
			{
				if (Board[i][j] == BLACK) //打印黑子
					cout << "●";
				else if (Board[i][j] == WHITE) //打印白子
					cout << "○";
				else
				{
					if (i == 0)
					{
						if (j == 0)
							cout << "┌ ";
						else if (j == 14)
							cout << "┐ ";
						else
							cout << "┬ ";
					}
					else if (i == 14)
					{
						if (j == 0)
							cout << "└ ";
						else if (j == 14)
							cout << "┘ ";
						else
							cout << "┴ ";
					}
					else
					{
						if (j == 0)
							cout << "├ ";
						else if (j == 14)
							cout << "┤ ";
						else
							cout << "┼ ";
					}
				}
			}
			cout << endl;
		}
	}

	int setBoard(int x, int y, int Piece_Color) //落子
	{
		if (x >= 0 && x < 15 && y >= 0 && y < 15 && Board[x][y] == EMPTY) //在棋盘内，且为空
		{
			Board[x][y] = Piece_Color;
			sx.push(x); sy.push(y); //记录下棋步骤
			return 0;
		}
		else
			return -1;
	}

	int setEmpty(int x, int y) //将棋盘位子置空
	{
		if (x >= 0 && x < 15 && y >= 0 && y < 15) //在棋盘内，且为空
		{
			Board[x][y] = EMPTY;
			return 0;
		}
		else
			return -1;
	}

	int getBoard(int x, int y) //返回棋盘位子状态
	{
		return Board[x][y];
	}

	int setBack()
	{
		if (!sx.empty() && !sy.empty()) //判断栈中是否有元素
		{
			int x = sx.top(); sx.pop(); //从栈中抛出上一步的棋子坐标
			int y = sy.top(); sy.pop();
			Gobang::setEmpty(x, y); //将坐标所在的位置置空
			return 0;
		}
		return -1;
	}

	int Max(int a, int b)
	{
		if (a >= b)
			return a;
		else
			return b;
	}

	int Min(int a, int b)
	{
		if (a <= b)
			return a;
		else
			return b;
	}
};

#endif
