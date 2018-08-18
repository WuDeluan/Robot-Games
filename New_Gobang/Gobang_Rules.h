#ifndef GOBANG_RULES_H
#define GOBANG_RULES_H

#include "Gobang_Base.h"
#define random(a,b) (rand()%(b-a+1)+a)
#define E 4
#define F 5
#define G 6
#define H 7 
#define I 8
#define J 9 
#define K 10

typedef struct Point
{
	int x;
	int y;
};

Point Lib[26] = {
{10,H},{10,I},{10,J},{9,I},{9,J},{8,I},
{8,J},{7,H},{7,I},{7,J},{6,H},{6,I},{6,J},
{10,J},{9,J},{8,J},{7,J},{6,J},{8,I},{7,I},
{6,I},{7,H},{6,H},{7,G},{6,G},{5,G}
};

Point Lib1[8][5] = {
{9,G,10,F,6,F,10,J,6,J },
{9,I,10,F,6,F,10,J,6,J },
{7,G,10,F,6,F,10,J,6,J },
{7,I,10,F,6,F,10,J,6,J },
{9,H,6,F,6,J},{8,G,10,J,6,J },
{8,I,10,F,6,F},{7,H,10,F,10,J },
};

class Gobang_Rules : public Gobang
{
public:
	void Opening();
	int WhetherChange(Point step[]);
};

void Gobang_Rules::Opening()
{
	srand((unsigned)time(NULL));
	int k = random(0, 25);
	setBoard(7, H, BLACK);
	if (k >= 0 && k < 13)
	{
		setBoard(6, H,WHITE);
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK); //找到对应于棋盘的位置，落子
	}
	else if (k >= 13 && k < 26)
	{
		setBoard(6, I, WHITE);
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK);
	}
}

int Gobang_Rules::WhetherChange(Point step[]) //是否三手交换判断
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		if (step[0].x == Lib1[i][0].x && step[0].y == Lib1[i][0].y)
		{
			for (j = 1; j <= 4; j++)
			{
				if (step[1].x == Lib1[i][j].x && step[1].y == Lib1[i][j].y)
					return -1;
			}
		}
	}
	return 0;
}


#endif
