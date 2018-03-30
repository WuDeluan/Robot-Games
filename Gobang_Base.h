#ifndef GOBANG_BASE_H
#define GOBANG_BASE_H

#include "Gobang_Class.h"

Gobang::Gobang()
{
	Init_Board();
}

void Gobang::Init_Board()
{
	int i, j;
	for (i = 0; i < 19; i++)
		for (j = 0; j < 19; j++)
			Board[i][j] = EMPTY; 
}

void Gobang::Print_Checkerboard()
{
	int i, j;
	//system("cls");
	cout << "----------五子棋人人对弈程序----------\n" << endl;
	cout << "  A B C D E F G H I J K L M N O P Q R S" << endl;
	for (i = 0; i < 19; i++)
	{
		cout << setw(2) << i + 1;
		for (j = 0; j < 19; j++)
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
					else if (j == 18)
						cout << "┐ ";
					else 
						cout << "┬ ";
				}
				else if (i == 18)
				{
					if (j == 0)
						cout << "└ ";
					else if (j == 18)
						cout << "┘ ";
					else
						cout << "┴ ";
				}
				else
				{
					if (j == 0)
						cout << "├ ";
					else if (j == 18)
						cout << "┤ ";
					else
						cout << "┼ ";
				}
			}
		}
		cout << endl;
	}
}

int Gobang::setBoard(char &x, char &y, int Piece_Color)
{
	x -= '1';
	y -= 'A';
	if (x >= 0 && x < 19 && y >= 0 && y < 19 && Board[x][y] == EMPTY) //在棋盘内，且为空
	{
		Board[x][y] = Piece_Color;
		return 0;
	}
	else
		return -1;
}

int Direct[4][2] = { { 1,-1 },{ 1,0 },{ 1,1 },{ 0,1 } };
int Gobang::IsWin(int x, int y)
{
	int i, tx, ty, len;
	int side = Board[x][y];//取得落子颜色
	for (i = 0; i < 4; i++)//4个方向的循环
	{
		tx = x; ty = y;//设置观察起点
		len = 0;//设置计数器
		while (tx >= 0 && tx < 19 && ty >= 0 && ty < 19 && Board[tx][ty] == side)//连珠条件
		{
			tx -= Direct[i][0];//沿一个方向
			ty -= Direct[i][1];//移动观察点
		}
		tx += Direct[i][0];
		ty += Direct[i][1];
		while (tx >= 0 && tx < 19 && ty >= 0 && ty < 19 && Board[tx][ty] == side)//连珠条件
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
