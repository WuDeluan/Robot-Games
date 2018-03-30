#ifndef GOBANG_CLASS_H
#define GOBANG_CLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

static int EMPTY = -1; //空子
static int BLACK = 0; //黑子
static int WHITE = 1; //白子

class Gobang
{
private:
	int Board[19][19]; //棋盘
public:
	Gobang();
	void Init_Board(); //初始化棋盘
	void Print_Checkerboard(); //打印棋盘
	int setBoard(char &i, char &j, int piece); //落子
	int IsWin(int x, int y);//判断是否赢棋
};
#endif
