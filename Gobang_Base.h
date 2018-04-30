#ifndef GOBANG_BASE_H
#define GOBANG_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define EMPTY  0 //空子
#define BLACK  1 //黑子
#define WHITE  2 //白子
#define E 5
#define F 6
#define G 7
#define H 8 
#define I 9
#define J 10 
#define K 11
int Direct[4][2] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } };

struct Step {
	int x, y;
};

Step Lib[8][5] = {
	{6,6,5,5,9,5,5,9,9,9},
{6,8,5,9,5,5,9,9,9,5},
{8,6,9,5,5,5,9,9,5,9},
{8,8,9,9,5,9,9,5,5,5},
{ 6,7,9,5,9,9 },
{ 7,6,5,9,9,9 },
{ 7,8,5,5,9,5 },
{ 8,7,5,5,5,9 }
};

/*Step Lib2[24][6] = {
	{9,9,9,7,8,7,6,8,10,7,0},{8,9,7,8,7,9,7,10,6,7,4},{7,9,7,8,6,7,6,8,5,7,8},
{6,9,4,8,7,9,6,7,6,8,12},{5,9,8,6,6,8,7,6,8,7,16},{7,8,7,9,6,7,7,6,8,7,20},
{6,8,8,6,6,7,5,7,5,9,24},{5,8,9,8,7,9,8,7,8,6,28},{6,7,8,7,5,7,8,6,8,6,32},
{5,7,8,7,8,6,6,7,9,8,36},{6,6,8,7,9,8,8,6,7,6,40},{5,6,8,7,9,8,7,8,6,9,44},
{9,7,9,8,9,9,10,7,8,9,48},{9,9,8,8,7,8,6,6,7,6,52},{8,8,7,8,6,9,0,0,0,0,56},
{8,9,7,9,7,6,6,6,9,9,60},{7,9,7,6,9,8,6,6,8,8,64},{6,7,5,7,7,9,9,7,9,8,68},
{6,9,7,6,9,8,6,6,8,8,72},{5,7,9,8,6,8,6,7,6,9,76},{5,8,9,6,6,5,9,8,6,6,80},
{9,8,7,8,7,9,7,10,6,7,84},{7,8,7,9,6,7,7,6,8,7,88},{6,8,8,7,9,8,8,6,7,6,92}
};*/

Step Lib2[24][6] = {
{10,J,10,H,9,H,7,I,11,H,0},{9,J,8,I,8,J,8,K,7,H,4},{8,J,8,I,7,H,7,I,6,H,8},
{7,J,5,I,8,J,7,H,7,I,12},{6,J,9,G,7,I,8,G,9,H,16},{8,I,8,J,7,H,8,G,9,H,20},
{7,I,9,G,7,H,6,H,6,J,24},{6,I,10,I,8,J,9,H,9,G,28},{7,H,9,H,6,H,8,G,9,G,32},
{6,H,9,H,9,G,7,H,10,I,36},{7,G,9,H,10,I,9,G,8,G,40},{6,G,9,H,10,I,8,I,7,J,44},
{10,H,10,I,10,J,11,H,9,J,48},{10,J,9,I,8,I,G,7,G,8,52},{9,I,8,I,7,J,0,0,56},
{9,J,8,J,8,G,7,G,10,J,60},{8,J,8,G,10,J,7,G,9,I,64},{7,H,6,H,8,J,10,H,10,I,68},
{7,J,8,G,10,I,7,G,9,I,72},{6,H,10,I,7,I,7,H,7,J,76},{6,I,10,G,7,F,10,I,7,G,80},
{10,I,8,I,8,J,8,K,7,H,84},{8,I,8,J,7,H,8,G,9,H,88},{7,I,9,H,10,I,9,G,8,G,92}
};

Step Lib3[96][3]
{
{8,J,10,I,11,I},{9,G,8,I,10,I},{10,H,8,I,10,I},{8,I,11,I,8,J},
{7,I,10,H,8,J},{10,H,7,H,7,K},{7,H,10,H,7,I},{10,I,8,J,10,J},
{7,I,9,H,10,I}, {7,I,10,I,9,J},{8,I,7,H,10,I},{8,I,9,J,0,0},
{8,G,6,I,9,G},{7,I,7,K,10,H},{6,I,6,J,8,I},{6,H,6,I,8,I},
{9,J,0,0,0,0},{6,H,6,I,8,I},{7,J,9,H,8,J},{7,I,9,J,0,0},
{10,H,9,G,7,K},{10,G,9,G,0,0},{7,H,10,G,9,J},{8,G,8,J,7,G},
{7,J,8,J,9,J},{9,G,6,J,8,J},{9,G,6,I,6,J},{8,G,9,G,9,H},
{7,H,9,G,6,H},{7,H,10,H,7,K},{9,G,9,J,0,0},{9,J,9,J,8,K},
{9,G,7,I,9,J},{8,G,8,I,0,0},{6,H,8,I,0,0},{9,H,8,I,0,0},
{9,G,7,I,6,J},{9,J,8,J,0,0},{8,F,7,G,7,I},{7,I,8,J,0,0},
{9,J,9,G,8,I},{7,I,8,F,0,0}, {7,F,8,F,10,F},{6,F,7,F,6,H},
{9,G,9,J,0,0},{9,G,8,E,8,I},{6,H,6,I,0,0},{6,H,9,H,0,0},
{8,G,9,G,9,I},{8,F,9,G,0,0},{7,G,9,I,0,0},{8,F,9,G,9,I},
{9,G,8,I,11,I},{9,I,7,J,9,J},{9,I,11,I,0,0},{9,I,10,I,9,J},
{7,G,7,I,7,J},{7,G,7,I,8,I},{0},{0},
{7,I,7,G,10,G},{10,I,8,I,10,J},{8,I,10,I,0,0},{7,I,8,I,0,0},
{10,I,7,F,0,0},{8,G,7,I,0,0},{6,I,9,G,0,0},{9,J,7,I,0,0},
{7,I,0,0,0,0},{7,G,6,I,7,J},{5,I,7,I,0,0},{7,G,8,I,0,0},
{8,I,9,I,0,0},{8,G,8,I,10,I},{8,G,7,I,0,0},{8,G,7,I,7,J},
{7,I,10,H,8,J},{10,H,7,H,7,K},{7,H,10,H,7,I},{10,I,8,J,10,J},
{10,H,9,G,7,K},{10,G,9,G,0,0},{7,H,10,G,9,J},{8,G,8,J,7,G},
{9,J,9,G,8,I},{7,I,8,F,0,0},{7,F,8,F,10,F},{6,F,7,F,6,H}
};
class Gobang
{
private:
	int Board[15][15]; //棋盘
public:
	Gobang();
	void Init_Board(); //初始化棋盘
	void Print_Checkerboard(); //打印棋盘
	int setBoard(int x, int y, int piece); //落子
	int setEmpty(int x, int y); //将棋盘位子置空
	int getBoard(int x, int y); //返回棋盘位子状态
};
Gobang::Gobang()
{
	Init_Board();
}

void Gobang::Init_Board()
{
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			Board[i][j] = EMPTY;
}

void Gobang::Print_Checkerboard()
{
	int i, j;
	//system("cls");
	//cout << "----------五子棋人人对弈程序----------\n" << endl;
	cout << "  A B C D E F G H I J K L M N O" << endl;
	for (i = 0; i < 15; i++)
	{
		cout << setw(2) << i + 1;
		for (j = 0; j < 15; j++)
		{
			if (Board[i][j] == BLACK)
				cout << "○";
			else if (Board[i][j] == WHITE)
				cout << "●";
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

int Gobang::setBoard(int x, int y, int Piece_Color)
{
	if (x >= 0 && x < 15 && y >= 0 && y < 15 && Board[x][y] == EMPTY) //在棋盘内，且为空
	{
		Board[x][y] = Piece_Color;
		return 0;
	}
	else
		return -1;
}

int Gobang::setEmpty(int x, int y)
{
	if (x >= 0 && x < 15 && y >= 0 && y < 15) //在棋盘内，且为空
	{
		Board[x][y] = EMPTY;
		return 0;
	}
	else
		return -1;
}

int Gobang::getBoard(int x, int y)
{
	return Board[x][y];
}

#endif
