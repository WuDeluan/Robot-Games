#ifndef GOBANG_MANTOCOM_H
#define GOBANG_MANTOCOM_H

#include "Gobang_ManToMan.h"
#include <stack>

#define MAN 1
#define COM 2
#define INIFITY 100000

class ManToCom : public ManToMan
{
public:
	ManToCom();
	int Eval(int x, int y); //估值函数
	int Function(int len, string side1, string side2); //棋型判断
	int minmaxSearch(int depth,int &x,int &y); //极大极小值判断
	int MaxSearch(int depth, int x, int y); 
	int MinSearch(int depth,int x,int y);
	void Print_Menu2(); //打印人机对弈界面
};

ManToCom::ManToCom()
{
	Init_Board();
}

int ManToCom::Eval(int x, int y)
{
	int i, j, tx, ty, len;
	int Side = getBoard(x, y);
	string side1, side2;
	int bestValue = -1;
	for (i = 0; i < 4; i++)
	{
		tx = x; ty = y;
		len = 0;
		side1.clear(); side2.clear();
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)
		{
			tx -= Direct[i][0];
			ty -= Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
			if (getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side1 += '#';
			else if (getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side1 += '0';
			else
				side1 += '1';
		}
		tx += Direct[i][0] * 4;
		ty += Direct[i][1] * 4;
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)
		{
			len++;
			tx += Direct[i][0];
			ty += Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx += Direct[i][0], ty += Direct[i][1]) {
			if (getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side2 += '#';
			else if (getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side2 += '0';
			else
				side2 += '1';
		}
		int value = Function(len, side1, side2);
		if (value > bestValue)
			bestValue = value;
	}
	//cout << bestValue << endl;
	return bestValue;
}

int ManToCom::Function(int len, string side1, string side2)
{
	int Value = 0;
	if (len >= 5)
	{
		cout << "五连" << endl; Value += 100000;
	}
	else if (len == 4)
	{
		if (side1[0] == '#' && side2[0] == '#')
		{
			cout << "活四" << endl; Value += 10000;
		}
		else if (side1[0] == '1' && side2[0] == '#' || side1[0] == '#' && side2[0] == '1')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '#' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '#')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			cout << "死四" << endl; Value += 1000;
		}
	}
	else if (len == 3)
	{
		if (side1[0] == '1' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '1')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
		{
			cout << "连活三" << endl; Value += 1000;
		}
		else if (side1[0] == '1' && side2.compare(0, 2, "##") == 0 || side1.compare(0, 2, "##") == 0 && side2[0] == '1')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1.compare(0, 2, "#1") == 0 && side2.compare(0, 2, "#1") == 0)
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			cout << "死三" << endl; Value += 100;
		}
	}
	else if (len == 2)
	{
		if (side1 == "#00" || side2 == "#00")
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '#' && side2 == "#0#" || side1 == "#0#" && side2[0] == '#')
		{
			cout << "跳活三" << endl; Value += 1000;
		}
		else if (side1[0] == '1' && side2 == "#1#" || side1 == "#1#" && side2[0] == '1')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1[0] == '#' && side2 == "10#" || side1 == "10#" && side2[0] == '#')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1 == "##0" || side2 == "##0")
		{
			cout << "眠三" << endl; Value += 500;
		}
		//其他情况待补充
		else
			Value += 100;
	}
	return Value;
}

/*int ManToCom::Neighbor(int x, int y, int(*neighbor)[5])
{
	int i, j;
	for (i = x - 2; i <= x + 2; i++)
		for (j = y - 2; j <= y + 2; j++)
			if (i >= 0 && i < 15 && j >= 0 && j < 15)
				neighbor[i - x + 2][j - y + 2] = getBoard(i, j);
			else
				neighbor[i - x + 2][j - y + 2] = OVERSIZE;
		
	return 0;
}
*/

int ManToCom::minmaxSearch(int depth,int &tx,int &ty)
{
	stack<int>  bestMovesX, bestMovesY;
	int x, y;
	static int bestValue = -INIFITY;
	if (depth == 0)
		return Eval(tx,ty);
	else
	{
		for (x = tx - 4; x <= tx + 4; x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x,y) == EMPTY)
				{
					setBoard(x, y, COM); //Print_Checkerboard();
					if (Eval(x,y) == +INIFITY)
					{
						tx = bestMovesX.top();
						ty = bestMovesY.top();
						setEmpty(x,y);// Print_Checkerboard();
						return 0;
					}
					int value = MinSearch(depth - 1, x, y);
					//cout << value << endl;
					if (value > bestValue)
					{
						bestValue = value;
						bestMovesX.push(x);
						bestMovesY.push(y);
					}
					else if (value == bestValue)
					{
						bestMovesX.push(x);
						bestMovesY.push(y);
					}
					setEmpty(x,y);// Print_Checkerboard();
					//cout << bestValue << " #" << endl;
				}
			}
		}
	}
	tx = bestMovesX.top();
	ty = bestMovesY.top();
	return 0;
}

int ManToCom::MaxSearch(int depth,int tx,int ty)
{
	int bestValue = -INIFITY, x, y;
	if (depth == 0)
		return Eval(tx,ty);
	else
	{
		int value;
		for (x = tx - 4;x <= tx + 4;x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x,y) == EMPTY)
				{
					setBoard(x, y, COM);// Print_Checkerboard();
					value = MinSearch(depth - 1, x, y);
					//cout << value << endl;
					if (value > bestValue)
						bestValue = value;
					setEmpty(x, y); //Print_Checkerboard();
				}
			}
		}
	}
	return bestValue;
}

int ManToCom::MinSearch(int depth,int tx,int ty)
{
	int bestValue = INFINITY, x, y;
	if (depth == 0)
		return Eval(tx, ty);
	else
	{
		int value;
		for (x = tx - 4;x <= tx + 4;x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, MAN);// Print_Checkerboard();
					value = MaxSearch(depth - 1, x, y);
					cout << value << endl;
					if (value < bestValue)
						bestValue = value;
					setEmpty(x, y); //Print_Checkerboard();
				}
			}
		}
	}
	return bestValue;
}

void ManToCom::Print_Menu2()
{
	int x;
	char y;
	Print_Checkerboard();
	while (1)
	{
		while (true) {
			cout << "请黑方落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, BLACK) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Print_Checkerboard();
		if (IsWin(x, y) == 1)
			cout << "黑方获胜!" << endl;
		int tx = x, ty = y;
		minmaxSearch(1, tx, ty);
		setBoard(tx, ty, WHITE);
		Print_Checkerboard();
		if (IsWin(x, y) == 1)
			cout << "白方获胜!" << endl;
	}
}
#endif

