#ifndef GOBANG_BASE_H
#define GOBANG_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define EMPTY  0 //空子
#define BLACK  1 //黑子
#define WHITE  2 //白子
int Direct[4][2] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } };

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
	if (x >= 0 && x < 15 && y >= 0 && y < 15 ) //在棋盘内，且为空
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
