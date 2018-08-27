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
#define INFINITY 99999
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
#define TableSize 1024*1024 //置换表大小
#define valUNKNOWN 100000 //置换表中无匹配返回值
#define R 2 //空着向前裁剪层数减少因子

typedef __int64 U64;
//定义了枚举型的数据类型，精确，下边界，上边界
enum FLAG_TYPE { hash_EXACT, hash_ALPHA, hash_BETA};

struct Step {
	int x, y, color;
};
typedef struct Point {
	int x; int y;
};
typedef struct Move {
	int x; int y;
	int score;
}MOVE;

//哈希表中元素的结构定义
typedef struct tagHASH {
	U64 key;  //64位校验码
	int depth;  //深度
	int flags;  //数据类型标记（hash_EXACT, hash_ALPHA, hash_BETA）
	int value;  //估值
	Point best;  //有利落子点
} HASH;

static int MAN, COM;
static int X, Y;
static int Board[15][15]; //棋盘
static int points; //打点数
static stack <int> sx; //记录下棋步骤
static stack <int> sy; //记录下棋步骤
static Point steps[5]; //棋子位置记录
static int TypeRecord[15][15][4];  //记录全部棋子在四个方向上的分析结果
static int TypeCount[3][15];  //记录分析结果的统计值   
static U64 zobrist[2][15][15]; //记录某一局面的键值
static HASH hashTable[TableSize];  //置换表
static U64 ZobristKey; //当前键值值
static MOVE MoveList[10][15 * 15];  //存储不同深度下可能的落子点，
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

//棋盘位置重要性价值表
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

int color_Five[2][5] = { {10,11,12,13,14},{15,16,17,18,19} };
class Gobang
{
public:
	Gobang()
	{
		Init_Board(); 
	}

	//初始化棋盘
	void Init_Board()
	{
		int i, j;
		for (i = 0; i < 15; i++)
			for (j = 0; j < 15; j++)
				Board[i][j] = EMPTY; //将棋盘全部置空

		ZobristKey = rand64();
		InitializeHashKey();
	}

	//打印棋盘
	void Print_Checkerboard()
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

	//落子
	int setBoard(int x, int y, int Piece_Color) 
	{
		if (x >= 0 && x < 15 && y >= 0 && y < 15 && Board[x][y] == EMPTY) //在棋盘内，且为空
		{
			Board[x][y] = Piece_Color;
			sx.push(x); sy.push(y); //记录下棋步骤
			ZobristKey = ZobristKey ^ zobrist[Piece_Color - 1][x][y];
			return 0;
		}
		else
			return -1;
	}

	//将棋盘位子置空
	int setEmpty(int x, int y) 
	{
		if (x >= 0 && x < 15 && y >= 0 && y < 15 && Board[x][y] != EMPTY) //在棋盘内，且为空
		{
			ZobristKey = ZobristKey ^ zobrist[Board[x][y] - 1][x][y];
			Board[x][y] = EMPTY;
			return 0;
		}
		else
			return -1;
	}

	//返回棋盘位子状态
	int getBoard(int x, int y) 
	{
		return Board[x][y];
	}

	//回退
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

	//判断某一方是否连成五子
	int IsWin(int x, int y)
	{
		int i, tx, ty, len, j;
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

	//取敌方棋子颜色
	int notplayer(int player)  
	{
		if (player == COM)
			return MAN;
		else if (player == MAN)
			return COM;
	}

	//随机生成64位检验码
	U64 rand64()
	{
		return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^ ((U64)rand() << 45) ^ ((U64)rand() << 60);
	}

	//初始化校验码
	void InitializeHashKey()
	{
		int i, j, k;
		srand((unsigned)time(NULL));
		//填充随机数组
		for (i = 0; i < 2; i++)
			for (j = 0; j < 15; j++)
				for (k = 0; k < 15; k++)
					zobrist[i][j][k] = rand64();

		//申请置换表所用空间。1M "2 个条目，读者也可指定其他大小
		//m_pTT[0] = new HashItem[1024 * 1024];//用于存放取极大值的节点数据
		//m_pTT[1] = new HashItem[1024 * 1024];//用于存放取极小值的节点数据
	}

	//位置周围3×3范围内是否有棋子
	int IsNeighbor(int tx, int ty)
	{
		int x, y;
		for (x = tx - 3; x <= tx + 3; x++)
		{
			for (y = ty - 3; y <= ty + 3; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && Board[x][y] != EMPTY)
					return 1;
			}
		}
		return 0;
	}
};

#endif
